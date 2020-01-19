#ifndef _BTREE
#define _BTREE

#include <ctype.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#define MAXHEIGHT 20
#define NO  0
#define YES 1
#define FNLEN 60

typedef unsigned char BTREE_BOOL;

typedef  struct {
         uint16_t Pos;
         int32_t  Ref;
        }__attribute__ ((packed)) Path;

typedef struct {
         int32_t        Root;
         int32_t        DelRec;
         uint16_t       KeyLen;
         uint16_t       KeyPos;
         uint16_t       RecLen;
         uint16_t       TimeStamp;
         int            BtFd;
         char           FileName[FNLEN];
         int            PP;
         Path           PagePath[MAXHEIGHT * 2];
        }__attribute__ ((packed)) DbFile, *DbFPtr;


#ifdef __cplusplus
extern "C" {
#endif


/* User interface  */

void InitDB(void (*ErrorHandler)(const char *));
void CloseDb(DbFPtr db);
BTREE_BOOL OpenDb(DbFPtr db, const char *);
void CreateDb(DbFPtr db, const char *fname,  uint16_t reclen, uint16_t keylen, uint16_t keypos);
void ResetPos(DbFPtr db);
BTREE_BOOL NextRecord(DbFPtr db, char *);
BTREE_BOOL PrevRecord(DbFPtr db, char *);
BTREE_BOOL GetRecord(DbFPtr db, char *);
BTREE_BOOL InsertRecord(DbFPtr db, const char *);
BTREE_BOOL RemoveRecord(DbFPtr db, const char *);
BTREE_BOOL ReplaceRecord(DbFPtr db, const char *);
void DBFlush(DbFPtr db);

#ifdef __cplusplus
 }
#endif

#endif
