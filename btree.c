#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "btree.h"

static BTREE_BOOL underflow;

#ifndef BTTEST
#define BUFSIZE (2048 - (sizeof(int32_t) + sizeof(int32_t)))
#define MAXRECLEN ((BUFSIZE / 4) - sizeof(int32_t))
#define ORDER(recsize) ((int)(BUFSIZE / (recsize + sizeof(int32_t))))
#define RootSize(p) ((char *)&(p)->BtFd - (char *)&(p)->Root)
#endif

typedef struct
{
    int32_t ChildRec;
    char Data[MAXRECLEN];
} __attribute__ ((packed))DATAREC;


typedef struct
{
    int     Count;
    int32_t BwChild;
    char    buf[BUFSIZE];
} __attribute__ ((packed)) BTPAGE, *PAGEPTR;



static struct pagebuffers
{
    int     updated[MAXHEIGHT];
    int32_t addr[MAXHEIGHT];
    DbFPtr  Db[MAXHEIGHT];
    BTPAGE  btp[MAXHEIGHT];
} __attribute__ ((packed)) pagebuffers;

static int PageMap[MAXHEIGHT];


static void (*ErrorHandler)(const char *);
static BTREE_BOOL SearchNode(DbFPtr db, DATAREC *data, PAGEPTR Page, uint16_t *pos);
static void Split(DbFPtr db, DATAREC *data, int32_t RightChild, PAGEPTR OldPage,
                  DATAREC *promotedData, PAGEPTR NewPage, uint16_t Slot);
static void InsInPage(DbFPtr db, DATAREC *data, PAGEPTR Page, uint16_t toSlot);
static PAGEPTR GetNewPage(DbFPtr db, int32_t *Ref);
static void FlushPages(DbFPtr db);
static void PutRoot(DbFPtr db);
static void GetRoot(DbFPtr db);
static void PutPage(PAGEPTR page);
static BTREE_BOOL PushDown(DbFPtr     db,
                           int32_t    Ref,
                           DATAREC    *data,
                           DATAREC    *promo_data,
                           BTREE_BOOL *status);

static BTREE_BOOL RecDelete(DbFPtr db, DATAREC *data, int32_t Ref);
static void Successor(DbFPtr db, uint16_t slot, int32_t xRef, int32_t Ref);
static void Remove(DbFPtr db, PAGEPTR p, uint16_t slot);
static void Restore(DbFPtr db, PAGEPTR p, uint16_t slot);
static void MoveRight(DbFPtr db, PAGEPTR parent, PAGEPTR page, PAGEPTR sibling, uint16_t slot);
static void MoveLeft(DbFPtr db, PAGEPTR parent, PAGEPTR page, PAGEPTR sibling, uint16_t slot);
static void Combine(DbFPtr db, PAGEPTR parent, PAGEPTR page, PAGEPTR r_sib, uint16_t slot);
static void DelPage(PAGEPTR page);
static int GetPos(DbFPtr db, uint16_t Slot);
static DATAREC *GetDataRecFromPage(DbFPtr db, PAGEPTR Page, uint16_t Slot);
static void DbMove(DbFPtr db, PAGEPTR toPage, uint16_t toSlot, PAGEPTR fromPage, uint16_t fromSlot);


static void setmem(void *src, int len, char c)
{
    memset(src, c, len);
}

static void BTCrash(const char *s)
{
    if (ErrorHandler)
    {
        ErrorHandler(s);
        exit(1);
    }
    else
    {
        puts(s);
        getchar();
        exit(1);
    }
}

BTREE_BOOL OpenDb(DbFPtr db, const char *fname)
{
    strncpy(db->FileName, fname, FNLEN - 1);
    db->FileName[FNLEN - 1] = 0;
    db->BtFd = open(db->FileName, O_RDWR);
    db->PP   = 0;
    if (db->BtFd > -1)
    {
        GetRoot(db);
        if (db->RecLen > MAXRECLEN)
        {
            BTCrash("ERROR: RecLen > MAXRECLEN");
        }
        if (db->KeyLen > db->RecLen)
        {
            BTCrash("ERROR: Key length > Record length");
        }
        if (db->KeyPos + db->KeyLen > db->RecLen)
        {
            BTCrash("ERROR: Key length + key position > Record length");
        }
    }
    return (BTREE_BOOL) (db->BtFd > 0);
}

void CloseDb(DbFPtr db)
{
    int i;

    PutRoot(db);
    FlushPages(db);
    for (i = 0; i < MAXHEIGHT; i++)
    {
        if (db == pagebuffers.Db[i])
        {
            pagebuffers.addr[i]    = 0;
            pagebuffers.Db[i]      = NULL;
            pagebuffers.updated[i] = 0;
        }
    }
    close(db->BtFd);
}

void ResetPos(DbFPtr db)
{
    db->PP = 0;
}

static void GetRoot(DbFPtr db)
{
    lseek(db->BtFd, 0, SEEK_SET);
    if (read(db->BtFd, (void *) &db->Root, RootSize(db)) < RootSize(db))
    {
        BTCrash("Error: Unable to get root.");
    }
}

static void PutRoot(DbFPtr db)
{
    char temp[RootSize(db)];

    lseek(db->BtFd, 0, SEEK_SET);
    if (read(db->BtFd, (void *) temp, RootSize(db)) == RootSize(db))
    {
        if ((memcmp((void *) &db->Root, temp, RootSize(db))) == 0)
        {
            return;
        }
    }
    lseek(db->BtFd, 0L, SEEK_SET);
    if (write(db->BtFd, (void *) &db->Root, RootSize(db)) != RootSize(db))
    {
        BTCrash("ERROR: PutRoot");
    }
}

static int ReadPage(DbFPtr db, int32_t addr, PAGEPTR page)
{
    int s, i;

    s = sizeof(BTPAGE);
    lseek(db->BtFd, addr, SEEK_SET);
    i = read(db->BtFd, (void *)page, s);
    if (i != s)
    {
        BTCrash("Error: Read page");
    }
    return i;
}

static int WritePage(DbFPtr db, int32_t addr, PAGEPTR page_ptr)
{
    int s;

    s = sizeof(BTPAGE);

    lseek(db->BtFd, addr, SEEK_SET);
    if (write(db->BtFd, (void *)page_ptr, s) != s)
    {
        BTCrash("Error: Write page");
    }
    return s;
}

static void FlushPages(DbFPtr db)
{
    int i;

    for (i = 0; i < MAXHEIGHT; i++)
    {
        if (pagebuffers.updated[i] == 1 && db == pagebuffers.Db[i])
        {
            WritePage(pagebuffers.Db[i], pagebuffers.addr[i], &pagebuffers.btp[i]);
            pagebuffers.updated[i] = 0;
        }
    }
}

void CreateDb(DbFPtr db, const char *fname, uint16_t reclen, uint16_t keylen, uint16_t keypos)
{
    if (keylen > reclen)
    {
        BTCrash("ERROR: Key length > Record length");
    }
    if (keypos + keylen > reclen)
    {
        BTCrash("ERROR: Key length + key position > Record length");
    }
    if (reclen > MAXRECLEN)
    {
        BTCrash("ERROR: RecLen > MAXRECLEN");
    }

    strncpy(db->FileName, fname, FNLEN - 1);
    db->FileName[FNLEN - 1] = 0;

    db->BtFd = creat(db->FileName, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
    if (db->BtFd == -1)
    {
        BTCrash("ERROR: Cannot create Datafile ");
    }
    close(db->BtFd);
    db->BtFd      = open(db->FileName, O_RDWR);
    db->Root      = 0;
    db->DelRec    = 0;
    db->KeyLen    = keylen;
    db->RecLen    = reclen;
    db->KeyPos    = keypos;
    db->TimeStamp = 0;
    PutRoot(db);
}

void DBFlush(DbFPtr db)
{
    PutRoot(db);
    FlushPages(db);
    fsync(db->BtFd);
}

void InitDB(void (*ErrorH)(const char *))
{
    int i;

    for (i = 0; i < MAXHEIGHT; i++)
    {
        PageMap[i]             = i;
        pagebuffers.addr[i]    = 0;
        pagebuffers.Db[i]      = NULL;
        pagebuffers.updated[i] = NO;
    }
    ErrorHandler = ErrorH;
}

static void CreateRoot(DbFPtr db, DATAREC *data)
{
    PAGEPTR page;
    int32_t Ref;

    page = GetNewPage(db, &Ref);
    page->Count = 0;
    setmem(page->buf, sizeof(page->buf), 0);
    InsInPage(db, data, page, 0);
    page->BwChild = db->Root;
    PutPage(page);
    db->Root = Ref;
    PutRoot(db);
}

static int GetPos(DbFPtr db, uint16_t Slot)
{
    return (db->RecLen + sizeof(int32_t)) * Slot;
}

static DATAREC *GetDataRecFromPage(DbFPtr db, PAGEPTR Page, uint16_t Slot)
{
    int pos;

    pos = GetPos(db, Slot);

    return (DATAREC *) (Page->buf + pos);
}

static void DbMove(DbFPtr db, PAGEPTR toPage, uint16_t toSlot, PAGEPTR fromPage, uint16_t fromSlot)
{
    int fromPos;
    int toPos;
    int bytesToCopy;

    fromPos = GetPos(db, fromSlot);
    toPos = GetPos(db, toSlot);
    bytesToCopy = db->RecLen + sizeof(int32_t);

    memcpy(toPage->buf + toPos, fromPage->buf + fromPos, bytesToCopy);
    setmem(fromPage->buf + fromPos, bytesToCopy, 0);
}

static void PutPage(PAGEPTR page)
{
    pagebuffers.updated[page - &pagebuffers.btp[0]] = YES;
}

static void DelPage(PAGEPTR page)
{
    int i;

    i = page - &pagebuffers.btp[0];

    GetRoot(pagebuffers.Db[i]);
    lseek(pagebuffers.Db[i]->BtFd, pagebuffers.addr[i], SEEK_SET);
    if (write(pagebuffers.Db[i]->BtFd, (void *) &pagebuffers.Db[i]->DelRec, sizeof(int32_t)) != sizeof(int32_t))
    {
        BTCrash("ERROR: Delete page");
    }
    pagebuffers.Db[i]->DelRec = pagebuffers.addr[i];
    PutRoot(pagebuffers.Db[i]);
    pagebuffers.Db[i]      = NULL;
    pagebuffers.addr[i]    = 0L;
    pagebuffers.updated[i] = NO;
}

static void BTLast(int i)
{
    int k, j;

    for (k = 0; k < MAXHEIGHT - 1; k++)
    {
        if (i == PageMap[k])
        {
            break;
        }
    }
    for (j = k; j < MAXHEIGHT - 1; j++)
    {
        PageMap[j] = PageMap[j + 1];
    }
    PageMap[MAXHEIGHT - 1] = i;
}

static PAGEPTR GetPage(DbFPtr db, int32_t Ref)
{
    int i, found;

    found = NO;
    for (i = 0; i < MAXHEIGHT; i++)
    {
        if (Ref == pagebuffers.addr[i] && db == pagebuffers.Db[i])
        {
            found = YES;
            break;
        }
    }
    if (!found)
    {
        i = PageMap[0];
        if (pagebuffers.updated[i])
        {
            WritePage(pagebuffers.Db[i], pagebuffers.addr[i], &pagebuffers.btp[i]);
            pagebuffers.updated[i] = NO;
        }
        ReadPage(db, Ref, &pagebuffers.btp[i]);
        pagebuffers.Db[i]      = db;
        pagebuffers.addr[i]    = Ref;
        pagebuffers.updated[i] = NO;
    }
    BTLast(i);
    return &pagebuffers.btp[i];
}

static PAGEPTR GetNewPage(DbFPtr db, int32_t *Ref)
{
    int32_t addr;
    int  i;

    if (db->DelRec == 0)
    {
        addr = lseek(db->BtFd, 0, SEEK_END);
    }
    else
    {
        addr = db->DelRec;
        lseek(db->BtFd, db->DelRec, SEEK_SET);
        if (read(db->BtFd, (void *) &db->DelRec, sizeof(int32_t)) == sizeof(int32_t))
            PutRoot(db);
        else
            BTCrash("ERROR: GetNewPage");

    }
    *Ref = addr;
    i    = PageMap[0];
    if (pagebuffers.updated[i])
    {
        WritePage(pagebuffers.Db[i], pagebuffers.addr[i], &pagebuffers.btp[i]);
        pagebuffers.updated[i] = NO;
    }
    pagebuffers.Db[i]      = db;
    pagebuffers.addr[i]    = addr;
    pagebuffers.updated[i] = NO;
    WritePage(pagebuffers.Db[i], pagebuffers.addr[i], &pagebuffers.btp[i]);
    BTLast(i);
    return &pagebuffers.btp[i];
}

BTREE_BOOL ReplaceRecord(DbFPtr db, const char *Data)
{
    BTREE_BOOL retval = NO;
    PAGEPTR    page;
    DATAREC    *dr;
    static char buf[MAXRECLEN];

    memcpy(buf + db->KeyPos, Data + db->KeyPos, db->KeyLen);

    if (GetRecord(db, buf))
    {
        page = GetPage(db, db->PagePath[db->PP].Ref);

        dr = GetDataRecFromPage(db, page, db->PagePath[db->PP].Pos - 1);

        memcpy(dr->Data, Data, db->RecLen);

        PutPage(page);
        retval = YES;
    }
    else
    {
        retval = NO;
    }
    return retval;
}

BTREE_BOOL InsertRecord(DbFPtr db, const char *data)
{
    BTREE_BOOL     promoted, status;
    static DATAREC datarec;
    static DATAREC promo_data;

    datarec.ChildRec = 0;
    memcpy(&datarec.Data, data, db->RecLen);
    status   = YES;
    promoted = PushDown(db, db->Root, &datarec, &promo_data, &status);
    if (promoted)
    {
        CreateRoot(db, &promo_data);
    }
    return status;
}

static BTREE_BOOL PushDown(DbFPtr db, int32_t Ref, DATAREC *data, DATAREC *promo_data, BTREE_BOOL *status)
{
    PAGEPTR        page,  newpage;
    BTREE_BOOL     found, promoted;
    uint16_t       Slot;
    static DATAREC p_b_data;

    if (Ref == 0)
    {
        memcpy(promo_data, data, db->RecLen + sizeof(int32_t));
        promo_data->ChildRec = 0; // Right child
        return YES;
    }
    page  = GetPage(db, Ref);

    found = SearchNode(db, data, page, &Slot);
    if (found)
    {
        *status = NO;
        return NO;
    }

    if (Slot > 0)
    {
        DATAREC *dr = GetDataRecFromPage(db, page, Slot - 1);
        promoted = PushDown(db, dr->ChildRec, data, &p_b_data, status);
    }
    else
    {
        promoted = PushDown(db, page->BwChild, data, &p_b_data, status);
    }
    if (!promoted)
    {
        return NO;
    }
    page = GetPage(db, Ref);
    if (page->Count < ORDER(db->RecLen))
    {
        InsInPage(db, &p_b_data,  page, Slot);
        PutPage(page);
        return NO;
    }
    else
    {
        int32_t newPageRef;
        newpage = GetNewPage(db, &newPageRef);
        Split(db, &p_b_data, newPageRef, page, promo_data, newpage, Slot);
        PutPage(page);
        PutPage(newpage);
        return YES;
    }
}

static void InsInPage(DbFPtr db, DATAREC *data, PAGEPTR Page, uint16_t toSlot)
{
    int Slot;
    int toPos;
    int bytesToCopy;

    toPos = GetPos(db, toSlot);
    bytesToCopy = db->RecLen + sizeof(int32_t);

    for (Slot = Page->Count; Slot > toSlot; Slot--)
    {
        DbMove(db, Page, Slot, Page, Slot - 1);
    }
    Page->Count++;
    memcpy(Page->buf + toPos, data, bytesToCopy);
}

static void Split(DbFPtr db, DATAREC *data, int32_t RightChild, PAGEPTR OldPage,
                  DATAREC *promotedData, PAGEPTR NewPage, uint16_t Slot)
{
    int      i;
    uint16_t median;
    uint16_t minSlots;
    uint16_t order;
    int      bytesToHandle;

    order = ORDER(db->RecLen);

    minSlots = order / 2;

    median = Slot <= minSlots ? minSlots : minSlots + 1;

    for (i = median; i < order; i++)
    {
        DbMove(db, NewPage, i - median, OldPage, i);
    }

    NewPage->Count = order - median;
    OldPage->Count = median;

    if (Slot <= minSlots)
    {
        InsInPage(db, data, OldPage, Slot);
    }
    else
    {
        InsInPage(db, data, NewPage, (uint16_t)(Slot - median));
    }

    bytesToHandle = db->RecLen + sizeof(int32_t);

    memcpy(promotedData, OldPage->buf + GetPos(db, OldPage->Count - 1), bytesToHandle);
    NewPage->BwChild = promotedData->ChildRec;
    promotedData->ChildRec = RightChild;

    setmem(OldPage->buf + GetPos(db, OldPage->Count - 1), bytesToHandle, 0);
    OldPage->Count--;
}

static int KeyComp(char *key1, char *key2, int klen, uint16_t kpos)
{
    int  C;

    C = memcmp(key1 + kpos, key2 + kpos, klen);
    return C;
}

static BTREE_BOOL SearchNode(DbFPtr db, DATAREC *data, PAGEPTR Page, uint16_t *pos)
{
    int j, lower, upper, C;

    DATAREC *drec = NULL;

    upper = Page->Count;
    lower = 0;
    C = 1;
    if (upper == 0)
    {
        j = 0;
    }
    else
    {
        do
        {
            j = (lower + upper) / 2;
            if (j < Page->Count)
            {
                drec = GetDataRecFromPage(db, Page, (uint16_t) j);
                C = KeyComp(data->Data, drec->Data, db->KeyLen, db->KeyPos);
            }
            if (C == 0)
                break;
            if (C < 0)
                upper = j - 1;
            if (C > 0)
                lower = j + 1;
        }
        while (lower <= upper);

        if (C != 0)
        {
            while (j < Page->Count && KeyComp(data->Data, drec->Data,
                                              db->KeyLen, db->KeyPos) > 0 )
            {
                j++;
                if (j < Page->Count)
                    drec = GetDataRecFromPage(db, Page, (uint16_t) j);
            }
        }
    }

    *pos = j;
    return C == 0;
}

/* Delete functions */

BTREE_BOOL RemoveRecord(DbFPtr db, const char *record)
{
    BTREE_BOOL     status;
    PAGEPTR        page;
    int32_t        newroot;
    static DATAREC data;

    memcpy(&data.Data, record, db->RecLen);
    status    = YES;
    underflow = NO;
    if (!RecDelete(db, &data, db->Root))
    {
        status = NO;
        return status;
    }
    page    = GetPage(db, db->Root);
    newroot = page->BwChild;
    if (page->Count == 0)
    {
        DelPage(page);
        db->Root = newroot;
        PutRoot(db);
    }
    return status;
}

static BTREE_BOOL RecDelete(DbFPtr db, DATAREC *data, int32_t Ref)
{
    PAGEPTR    page;
    uint16_t   pos;
    BTREE_BOOL found;

    if (Ref == 0)
    {
        return NO;
    }
    page = GetPage(db, Ref);

    if ((found = SearchNode(db, data, page, &pos)) == YES)
    {
        if (page->BwChild != 0)
        {
            Successor(db, pos, Ref, GetDataRecFromPage(db, page, pos)->ChildRec);
            PutPage(page);
            pos++;
        }
        else
        {
            Remove(db, page, pos);
            PutPage(page);
        }
    }
    else
    {
        if (pos > 0)
            found = RecDelete(db, data, GetDataRecFromPage(db, page, pos - 1)->ChildRec);
        else
            found = RecDelete(db, data, page->BwChild);
    }
    page = GetPage(db, Ref);
    if (page->BwChild != 0)
    {
        if (underflow)
        {
            Restore(db, page, pos);
            PutPage(page);
        }
    }
    return found;
}

static void Remove(DbFPtr db, PAGEPTR p, uint16_t slot)
{
    int i;

    for (i = slot + 1; i < p->Count; i++)
    {
        DbMove(db, p, i - 1, p, i);
    }
    p->Count--;
    setmem(p->buf + GetPos(db, p->Count), db->RecLen + sizeof(int32_t), 0);
    underflow = p->Count < (ORDER(db->RecLen) / 2) ? YES : NO;
}

static void Successor(DbFPtr db, uint16_t slot, int32_t xRef, int32_t Ref)
{
    PAGEPTR page, xpage;

    if (Ref == 0)
    {
        return;
    }
    page = GetPage(db, Ref);
    if (page->BwChild != 0)
    {
        Successor(db, slot, xRef, page->BwChild);
    }
    else
    {
        xpage = GetPage(db, xRef);
        memcpy(GetDataRecFromPage(db, xpage, slot)->Data, GetDataRecFromPage(db, page, 0)->Data, db->RecLen);
        Remove(db, page, 0);
        PutPage(xpage);
        PutPage(page);
    }
    page = GetPage(db, Ref);
    if (page->BwChild != 0)
    {
        if (underflow)
        {
            Restore(db, page, 0);
            PutPage(page);
        }
    }
}

static void Restore(DbFPtr db, PAGEPTR p, uint16_t slot)
{
    PAGEPTR sibling, page;
    int32_t sRef,    pRef;

    underflow = NO;

    if (slot == 0)
    {
        pRef = p->BwChild;
        sRef = GetDataRecFromPage(db, p, slot)->ChildRec;
        page = GetPage(db, pRef);
        sibling = GetPage(db, sRef);
        if (sibling->Count > (ORDER(db->RecLen) / 2))
        {
            MoveLeft(db, p, page, sibling, slot);
            PutPage(page);
            PutPage(sibling);
        }
        else
        {
            Combine(db, p, page, sibling, slot);
            PutPage(page);
            DelPage(sibling);
        }
        return;
    }
    else if (slot == p->Count)
    {
        pRef = GetDataRecFromPage(db, p, slot - 1)->ChildRec;

        if (slot > 1)
        {
            sRef = GetDataRecFromPage(db, p, slot - 2)->ChildRec;
        }
        else
        {
            sRef = p->BwChild;
        }
        page = GetPage(db, pRef);
        sibling = GetPage(db, sRef);
        if (sibling->Count > (ORDER(db->RecLen) / 2))
        {
            MoveRight(db, p, page, sibling, (uint16_t)(slot - 1));
            PutPage(page);
            PutPage(sibling);
        }
        else
        {
            Combine(db, p, sibling, page, (uint16_t)(slot - 1));
            PutPage(sibling);
            DelPage(page);
        }
        return;
    }

    pRef = GetDataRecFromPage(db, p, slot - 1)->ChildRec;

    if (slot > 1)
    {
        sRef = GetDataRecFromPage(db, p, slot - 2)->ChildRec;
    }
    else
    {
        sRef = p->BwChild;
    }

    page = GetPage(db, pRef);
    sibling = GetPage(db, sRef);
    if (sibling->Count > (ORDER(db->RecLen) / 2))
    {
        MoveRight(db, p, page, sibling, (uint16_t)(slot - 1));
        PutPage(page);
        PutPage(sibling);
        return;
    }
    sRef    = GetDataRecFromPage(db, p, slot)->ChildRec;
    sibling = GetPage(db, sRef);
    if (sibling->Count > (ORDER(db->RecLen) / 2))
    {
        MoveLeft(db, p, page, sibling, slot);
        PutPage(page);
        PutPage(sibling);
    }
    else
    {
        Combine(db, p, page, sibling, slot);
        PutPage(page);
        DelPage(sibling);
    }
}

static void MoveRight(DbFPtr db, PAGEPTR parent, PAGEPTR page, PAGEPTR sibling, uint16_t slot)
{
    int32_t Ref;
    int c;

    for (c = page->Count; c > 0; c--)
    {
        DbMove(db, page, c, page, c - 1);
    }

    DbMove(db, page, 0, parent, slot);
    DbMove(db, parent, slot, sibling, sibling->Count - 1);
    Ref = page->BwChild;
    page->BwChild = GetDataRecFromPage(db, parent, slot)->ChildRec;
    GetDataRecFromPage(db, parent, slot)->ChildRec = GetDataRecFromPage(db, page, 0)->ChildRec;
    GetDataRecFromPage(db, page, 0)->ChildRec = Ref;

    sibling->Count--;
    page->Count++;
}

static void MoveLeft(DbFPtr db, PAGEPTR parent, PAGEPTR page, PAGEPTR sibling, uint16_t slot)
{
    int c;
    int32_t Ref;

    DbMove(db, page, page->Count, parent, slot);
    DbMove(db, parent, slot, sibling, 0);
    for (c = 0; c < sibling->Count - 1; c++)
    {
        DbMove(db, sibling, c, sibling, c + 1);
    }

    Ref = sibling->BwChild;
    sibling->BwChild = GetDataRecFromPage(db, parent, slot)->ChildRec;
    GetDataRecFromPage(db, parent, slot)->ChildRec = GetDataRecFromPage(db, page, page->Count)->ChildRec;
    GetDataRecFromPage(db, page, page->Count)->ChildRec = Ref;

    page->Count++;
    sibling->Count--;
}

static void Combine(DbFPtr db, PAGEPTR parent, PAGEPTR page, PAGEPTR r_sib, uint16_t slot)
{
    int c;

    DbMove(db, page, page->Count, parent, slot);
    GetDataRecFromPage(db, page, page->Count)->ChildRec = r_sib->BwChild;

    page->Count++;

    for (c = 0; c < r_sib->Count; c++)
    {
        DbMove(db, page, page->Count, r_sib, c);
        page->Count++;
    }
    for (c = slot; c < parent->Count - 1; c++)
    {
        DbMove(db, parent, c, parent, c + 1);
    }
    parent->Count--;
    underflow = parent->Count < (ORDER(db->RecLen) / 2)  ? YES : NO;
}


/* Search functions  */

BTREE_BOOL GetRecord(DbFPtr db, char *data)
{
    PAGEPTR    page;
    DATAREC    datarec;
    DATAREC    *dr;
    BTREE_BOOL found;
    uint16_t   slot;

    if (db->Root == 0)
    {
        return NO;
    }
    memcpy((char *)&datarec.Data, data, db->RecLen);
    datarec.ChildRec = 0;
    page  = GetPage(db, db->Root);

    found = SearchNode(db, &datarec, page, &slot);

    db->PP = 1;
    db->PagePath[db->PP].Ref = db->Root;
    db->PagePath[db->PP].Pos = slot;
    while (!found && page->BwChild != 0)
    {
        db->PP++;

        if (slot > 0)
        {
            dr = GetDataRecFromPage(db, page, slot - 1);
            db->PagePath[db->PP].Ref = dr->ChildRec;
            page = GetPage(db, dr->ChildRec);
        }
        else
        {
            db->PagePath[db->PP].Ref = page->BwChild;
            page = GetPage(db, page->BwChild);
        }
        found = SearchNode(db, &datarec, page, &slot);
        db->PagePath[db->PP].Pos = slot;
    }

    if (found)
    {
        DATAREC *dr = GetDataRecFromPage(db, page, slot);
        db->PagePath[db->PP].Pos++;
        memcpy(data, dr->Data, db->RecLen);
    }
    else
    {
        while (db->PP > 1 && db->PagePath[db->PP].Pos == 0)
        {
            db->PP--;
        }
        if (db->PagePath[db->PP].Pos == 0)
        {
            db->PP = 0;
        }
    }

    return found;
}

BTREE_BOOL NextRecord(DbFPtr db, char *data)
{
    int32_t    Ref;
    PAGEPTR    PagPtr;
    DATAREC    *dr;
    BTREE_BOOL found = NO;

    if (db->Root == 0)
    {
        return NO;
    }

    if (db->PP == 0)
    {
        Ref = db->Root;
    }
    else
    {
        PagPtr = GetPage(db, db->PagePath[db->PP].Ref);
        if (db->PagePath[db->PP].Pos > 0)
        {
            dr = GetDataRecFromPage(db, PagPtr, db->PagePath[db->PP].Pos - 1);
            Ref = dr->ChildRec;
        }
        else
        {
            Ref = PagPtr->BwChild;
        }
    }

    while (Ref != 0)
    {
        db->PP++;
        db->PagePath[db->PP].Ref = Ref;
        db->PagePath[db->PP].Pos = 0;
        PagPtr = GetPage(db, Ref);
        Ref    = PagPtr->BwChild;
    }
    if (db->PP != 0)
    {
        while (db->PP > 1 && db->PagePath[db->PP].Pos == PagPtr->Count)
        {
            db->PP--;
            PagPtr = GetPage(db, db->PagePath[db->PP].Ref);
        }
        if (db->PagePath[db->PP].Pos < PagPtr->Count)
        {
            dr = GetDataRecFromPage(db, PagPtr, db->PagePath[db->PP].Pos);
            memcpy(data, dr->Data, db->RecLen);
            db->PagePath[db->PP].Pos++;
            found = YES;
        }
        else
        {
            db->PP = 0;
            found = NO;
        }
    }
    return found;
}

BTREE_BOOL PrevRecord(DbFPtr db, char *data)
{
    int32_t    Ref;
    PAGEPTR    PagPtr;
    DATAREC    *dr;
    BTREE_BOOL found = NO;

    if (db->Root == 0)
    {
        return NO;
    }
    if (db->PP == 0)
    {
        Ref = db->Root;
    }
    else
    {
        PagPtr = GetPage(db, db->PagePath[db->PP].Ref);
        db->PagePath[db->PP].Pos--;
        if (db->PagePath[db->PP].Pos > 0)
        {
            dr = GetDataRecFromPage(db, PagPtr, db->PagePath[db->PP].Pos - 1);
            Ref = dr->ChildRec;
        }
        else
        {
            Ref = PagPtr->BwChild;
        }
    }
    while (Ref != 0)
    {
        PagPtr = GetPage(db, Ref);
        db->PP++;
        db->PagePath[db->PP].Ref = Ref;
        db->PagePath[db->PP].Pos = PagPtr->Count;
        dr = GetDataRecFromPage(db, PagPtr, db->PagePath[db->PP].Pos - 1);
        Ref = dr->ChildRec;
    }
    if (db->PP != 0)
    {
        while (db->PP > 1 && db->PagePath[db->PP].Pos == 0)
        {
            db->PP--;
            PagPtr = GetPage(db, db->PagePath[db->PP].Ref);
        }
        if (db->PagePath[db->PP].Pos > 0)
        {
            dr = GetDataRecFromPage(db, PagPtr, db->PagePath[db->PP].Pos - 1);
            memcpy(data, dr->Data, db->RecLen);
            found = YES;
        }
        else
        {
            db->PP = 0;
            found = NO;
        }
    }

    return found;
}
