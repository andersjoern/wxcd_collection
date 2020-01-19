/***************************************************************
 * Name:      wxcd_collectionMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Anders J. Andersen (andersj.andersen@gmail.com)
 * Created:   2019-05-12
 * Copyright: Anders J. Andersen ()
 * License:
 **************************************************************/

#include "wxcd_collectionMain.h"
#include "PlayTheMusic.h"
#include <wx/msgdlg.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>


//(*InternalHeaders(wxcd_collectionFrame)
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(wxcd_collectionFrame)
const long wxcd_collectionFrame::ID_LISTVIEW2 = wxNewId();
const long wxcd_collectionFrame::ID_LISTVIEW1 = wxNewId();
const long wxcd_collectionFrame::ID_BUTTON1 = wxNewId();
const long wxcd_collectionFrame::ID_BUTTON2 = wxNewId();
const long wxcd_collectionFrame::ID_BUTTON3 = wxNewId();
const long wxcd_collectionFrame::ID_BUTTON4 = wxNewId();
const long wxcd_collectionFrame::ID_BUTTON15 = wxNewId();
const long wxcd_collectionFrame::ID_BUTTON5 = wxNewId();
const long wxcd_collectionFrame::ID_PANEL1 = wxNewId();
const long wxcd_collectionFrame::ID_LISTVIEW3 = wxNewId();
const long wxcd_collectionFrame::ID_BUTTON6 = wxNewId();
const long wxcd_collectionFrame::ID_BUTTON7 = wxNewId();
const long wxcd_collectionFrame::ID_BUTTON8 = wxNewId();
const long wxcd_collectionFrame::ID_PANEL2 = wxNewId();
const long wxcd_collectionFrame::ID_LISTVIEW4 = wxNewId();
const long wxcd_collectionFrame::ID_BUTTON9 = wxNewId();
const long wxcd_collectionFrame::ID_BUTTON10 = wxNewId();
const long wxcd_collectionFrame::ID_BUTTON11 = wxNewId();
const long wxcd_collectionFrame::ID_PANEL3 = wxNewId();
const long wxcd_collectionFrame::ID_LISTVIEW5 = wxNewId();
const long wxcd_collectionFrame::ID_BUTTON12 = wxNewId();
const long wxcd_collectionFrame::ID_BUTTON13 = wxNewId();
const long wxcd_collectionFrame::ID_BUTTON14 = wxNewId();
const long wxcd_collectionFrame::ID_PANEL4 = wxNewId();
const long wxcd_collectionFrame::ID_NOTEBOOK1 = wxNewId();
const long wxcd_collectionFrame::ID_MENUITEM1 = wxNewId();
const long wxcd_collectionFrame::idMenuQuit = wxNewId();
const long wxcd_collectionFrame::idMenuAbout = wxNewId();
const long wxcd_collectionFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxcd_collectionFrame,wxFrame)
    //(*EventTable(wxcd_collectionFrame)
    //*)
END_EVENT_TABLE()

wxcd_collectionFrame::wxcd_collectionFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(wxcd_collectionFrame)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer3;
    wxFlexGridSizer* FlexGridSizer2;
    wxFlexGridSizer* FlexGridSizer3;
    wxFlexGridSizer* FlexGridSizer4;
    wxFlexGridSizer* FlexGridSizer5;
    wxGridSizer* GridSizer1;
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, wxID_ANY, _("CD collection"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(872,450));
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T("/home/anders/cprogr/wxcd_collection/classicmusic.png"))));
    	SetIcon(FrameIcon);
    }
    Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxPoint(32,16), wxSize(328,18), 0, _T("ID_NOTEBOOK1"));
    Panel1 = new wxPanel(Notebook1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    FlexGridSizer1 = new wxFlexGridSizer(2, 2, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableCol(1);
    FlexGridSizer1->AddGrowableRow(0);
    ListViewCD = new wxListView(Panel1, ID_LISTVIEW2, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL, wxDefaultValidator, _T("ID_LISTVIEW2"));
    FlexGridSizer1->Add(ListViewCD, 1, wxALL|wxEXPAND, 5);
    ListViewCDRecTracks = new wxListView(Panel1, ID_LISTVIEW1, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL, wxDefaultValidator, _T("ID_LISTVIEW1"));
    FlexGridSizer1->Add(ListViewCDRecTracks, 1, wxALL|wxEXPAND, 5);
    GridSizer1 = new wxGridSizer(0, 3, 0, 0);
    btnNewCD = new wxButton(Panel1, ID_BUTTON1, _("New CD"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    GridSizer1->Add(btnNewCD, 1, wxALL|wxEXPAND, 5);
    btnUpdateCD = new wxButton(Panel1, ID_BUTTON2, _("Update CD"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    GridSizer1->Add(btnUpdateCD, 1, wxALL|wxEXPAND, 5);
    btnDeleteCD = new wxButton(Panel1, ID_BUTTON3, _("Delete CD"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    GridSizer1->Add(btnDeleteCD, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer1->Add(GridSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
    btnAddTrack = new wxButton(Panel1, ID_BUTTON4, _("Add Track"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    FlexGridSizer2->Add(btnAddTrack, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnUpdateCDTrack = new wxButton(Panel1, ID_BUTTON15, _("Update Track"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON15"));
    FlexGridSizer2->Add(btnUpdateCDTrack, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnDeleteTrack = new wxButton(Panel1, ID_BUTTON5, _("Delete Track"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    FlexGridSizer2->Add(btnDeleteTrack, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(Panel1);
    FlexGridSizer1->SetSizeHints(Panel1);
    Panel2 = new wxPanel(Notebook1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    FlexGridSizer5 = new wxFlexGridSizer(2, 1, 0, 0);
    FlexGridSizer5->AddGrowableCol(0);
    FlexGridSizer5->AddGrowableRow(0);
    ListViewTrackData = new wxListView(Panel2, ID_LISTVIEW3, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL, wxDefaultValidator, _T("ID_LISTVIEW3"));
    FlexGridSizer5->Add(ListViewTrackData, 1, wxALL|wxEXPAND, 5);
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    btnNewTrack = new wxButton(Panel2, ID_BUTTON6, _("New Track"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    BoxSizer1->Add(btnNewTrack, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnUpdateTrack = new wxButton(Panel2, ID_BUTTON7, _("Update Track"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
    BoxSizer1->Add(btnUpdateTrack, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnDeleteTrack1 = new wxButton(Panel2, ID_BUTTON8, _("Delete Track"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON8"));
    BoxSizer1->Add(btnDeleteTrack1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer5->Add(BoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel2->SetSizer(FlexGridSizer5);
    FlexGridSizer5->Fit(Panel2);
    FlexGridSizer5->SetSizeHints(Panel2);
    Panel3 = new wxPanel(Notebook1, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    FlexGridSizer3 = new wxFlexGridSizer(2, 1, 0, 0);
    FlexGridSizer3->AddGrowableCol(0);
    FlexGridSizer3->AddGrowableRow(0);
    ListViewTypeOfMusic = new wxListView(Panel3, ID_LISTVIEW4, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL, wxDefaultValidator, _T("ID_LISTVIEW4"));
    FlexGridSizer3->Add(ListViewTypeOfMusic, 1, wxALL|wxEXPAND, 5);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    btnNewType = new wxButton(Panel3, ID_BUTTON9, _("New Type"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON9"));
    BoxSizer2->Add(btnNewType, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnUpdateType = new wxButton(Panel3, ID_BUTTON10, _("Update Type"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON10"));
    BoxSizer2->Add(btnUpdateType, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnDeleteType = new wxButton(Panel3, ID_BUTTON11, _("DeleteType"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON11"));
    BoxSizer2->Add(btnDeleteType, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(BoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel3->SetSizer(FlexGridSizer3);
    FlexGridSizer3->Fit(Panel3);
    FlexGridSizer3->SetSizeHints(Panel3);
    Panel4 = new wxPanel(Notebook1, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
    FlexGridSizer4 = new wxFlexGridSizer(2, 1, 0, 0);
    FlexGridSizer4->AddGrowableCol(0);
    FlexGridSizer4->AddGrowableRow(0);
    ListViewArtists = new wxListView(Panel4, ID_LISTVIEW5, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL, wxDefaultValidator, _T("ID_LISTVIEW5"));
    FlexGridSizer4->Add(ListViewArtists, 1, wxALL|wxEXPAND, 5);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    btnNewArtist = new wxButton(Panel4, ID_BUTTON12, _("New Artist"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON12"));
    BoxSizer3->Add(btnNewArtist, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnUpdateArtist = new wxButton(Panel4, ID_BUTTON13, _("Update Artist"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON13"));
    BoxSizer3->Add(btnUpdateArtist, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnDeleteArtist = new wxButton(Panel4, ID_BUTTON14, _("Delete Artist"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON14"));
    BoxSizer3->Add(btnDeleteArtist, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(BoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel4->SetSizer(FlexGridSizer4);
    FlexGridSizer4->Fit(Panel4);
    FlexGridSizer4->SetSizeHints(Panel4);
    Notebook1->AddPage(Panel1, _("Update CDs"), false);
    Notebook1->AddPage(Panel2, _("Update tracks"), false);
    Notebook1->AddPage(Panel3, _("Update Type of music"), false);
    Notebook1->AddPage(Panel4, _("Update Artists"), false);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu1, ID_MENUITEM1, _("&Play"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    Menu1->AppendSeparator();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(ID_LISTVIEW2,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&wxcd_collectionFrame::OnListViewCDItemSelect);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxcd_collectionFrame::OnbtnNewCDClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxcd_collectionFrame::OnbtnUpdateCDClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxcd_collectionFrame::OnbtnDeleteCDClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxcd_collectionFrame::OnbtnAddTrackClick);
    Connect(ID_BUTTON15,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxcd_collectionFrame::OnbtnUpdateCDTrackClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxcd_collectionFrame::OnbtnDeleteTrackClick);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxcd_collectionFrame::OnbtnNewTrackClick);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxcd_collectionFrame::OnbtnUpdateTrackClick);
    Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxcd_collectionFrame::OnbtnDeleteTrack1Click);
    Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxcd_collectionFrame::OnbtnNewTypeClick);
    Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxcd_collectionFrame::OnbtnUpdateTypeClick);
    Connect(ID_BUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxcd_collectionFrame::OnbtnDeleteTypeClick);
    Connect(ID_BUTTON12,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxcd_collectionFrame::OnbtnNewArtistClick);
    Connect(ID_BUTTON13,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxcd_collectionFrame::OnbtnUpdateArtistClick);
    Connect(ID_BUTTON14,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxcd_collectionFrame::OnbtnDeleteArtistClick);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxcd_collectionFrame::OnMenuPlaySelected);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxcd_collectionFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxcd_collectionFrame::OnAbout);
    //*)

    editCDDialog = NULL;
    GetCDData();
    if (ListViewCD->GetItemCount() > 0) ListViewCD->Select(0);
    GetTrackData();
    if (ListViewTrackData->GetItemCount() > 0) ListViewTrackData->Select(0);
    GetTypeOfMusicData();
    if (ListViewTypeOfMusic->GetItemCount() > 0) ListViewTypeOfMusic->Select(0);
    GetArtistData();
    if (ListViewArtists->GetItemCount() > 0) ListViewArtists->Select(0);

}

wxcd_collectionFrame::~wxcd_collectionFrame()
{
    //(*Destroy(wxcd_collectionFrame)
    //*)

    DataFactory::DestroyInstance();
}

void wxcd_collectionFrame::GetCDData()
{
	long itemCount = 0;
	ListViewCD->ClearAll();
    ListViewCD->AppendColumn(_("Id"), wxLIST_FORMAT_RIGHT);
    ListViewCD->AppendColumn(_("Title"), wxLIST_FORMAT_LEFT, 300 );
    std::vector<wxCDRec>::iterator it;
	CDRecs = DataFactory::Instance()->GetCDRecords();
	for (it = CDRecs->begin(); it != CDRecs->end(); it++)
	{
		ListViewCD->InsertItem(itemCount, wxString::Format(wxT("%i"), it->Id));
		ListViewCD->SetItem(itemCount, 1, it->Title);
		ListViewCD->SetItemData(itemCount, it->Id);
		itemCount++;
	}
}

void wxcd_collectionFrame::GetTrackData()
{
	long itemCount = 0;
	ListViewTrackData->ClearAll();
    ListViewTrackData->AppendColumn(_("Id"), wxLIST_FORMAT_RIGHT);
    ListViewTrackData->AppendColumn(_("Title"), wxLIST_FORMAT_LEFT, 400 );
    std::vector<wxCDTrack>::iterator it;
	CDtracks = DataFactory::Instance()->GetCDTracks();
	for (it = CDtracks->begin(); it != CDtracks->end(); it++)
	{
		ListViewTrackData->InsertItem(itemCount, wxString::Format(wxT("%i"), it->id));
		ListViewTrackData->SetItem(itemCount, 1, it->ArtistLastName +_(" ") + it->Title);
		ListViewTrackData->SetItemData(itemCount, it->id);
		itemCount++;
	}
}

void wxcd_collectionFrame::GetTypeOfMusicData()
{
	long itemCount = 0;
	ListViewTypeOfMusic->ClearAll();
    ListViewTypeOfMusic->AppendColumn(_("Id"), wxLIST_FORMAT_RIGHT);
    ListViewTypeOfMusic->AppendColumn(_("TypeOfMusic"), wxLIST_FORMAT_LEFT, 200);
    std::vector<wxTypeOfMusic>::iterator it;
	TypeOfMusics = DataFactory::Instance()->GetTypeOfMusics();
	for (it = TypeOfMusics->begin(); it != TypeOfMusics->end(); it++)
	{
		ListViewTypeOfMusic->InsertItem(itemCount, wxString::Format(wxT("%i"), it->Id));
		ListViewTypeOfMusic->SetItem(itemCount, 1,  it->TypeOfMusic);
		ListViewTypeOfMusic->SetItemData(itemCount, it->Id);
		itemCount++;
	}
}

void wxcd_collectionFrame::GetCDTrackData(int id)
{
	long itemCount = 0;
	ListViewCDRecTracks->ClearAll();
    ListViewCDRecTracks->AppendColumn(_("TRId"), wxLIST_FORMAT_RIGHT);
    ListViewCDRecTracks->AppendColumn(_("Title"), wxLIST_FORMAT_LEFT, 300);
    std::vector<wxCDRecTrackRec>::iterator it;
	CDRecTrackRec = DataFactory::Instance()->GetRecTrackRecords(id);
	for (it = CDRecTrackRec->begin(); it != CDRecTrackRec->end(); it++)
	{
		ListViewCDRecTracks->InsertItem(itemCount, wxString::Format(wxT("%i"), it->trackOnCD));
		ListViewCDRecTracks->SetItem(itemCount, 1, it->ArtistLastName + " " + it->TrackTitle);
		ListViewCDRecTracks->SetItemData(itemCount, (long)it->trackId);
		itemCount++;
	}
}

void wxcd_collectionFrame::GetArtistData()
{
	long itemCount = 0;
	ListViewArtists->ClearAll();
    ListViewArtists->AppendColumn(_("Id"), wxLIST_FORMAT_RIGHT);
    ListViewArtists->AppendColumn(_("Name"), wxLIST_FORMAT_LEFT, 300);
    std::vector<wxArtist>::iterator it;
	Artists = DataFactory::Instance()->GetArtists();
	for (it = Artists->begin(); it != Artists->end(); it++)
	{
		ListViewArtists->InsertItem(itemCount, wxString::Format(wxT("%i"), it->Id));
		ListViewArtists->SetItem(itemCount, 1, it->FirstName + " " + it->LastName);
		ListViewArtists->SetItemData(itemCount, (long)it->Id);
		itemCount++;
	}
}

void wxcd_collectionFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void wxcd_collectionFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = _("My CD collection 2019");//wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void wxcd_collectionFrame::OnbtnNewCDClick(wxCommandEvent& event)
{
	EditCDDialog editCDDialog(this, NULL);
	if (editCDDialog.ShowModal() == wxOK)
	{
		GetCDData();
	}
}

void wxcd_collectionFrame::OnbtnUpdateCDClick(wxCommandEvent& event)
{
	int id = 0;
	long sel = ListViewCD->GetFirstSelected();

	if (sel != wxNOT_FOUND)
    {
        id = ListViewCD->GetItemData(sel);
        wxCDRec *found = FindCDRec(id);
        EditCDDialog editCDDialog(this, found);
        if (editCDDialog.ShowModal() == wxOK)
        {
            GetCDData();
            ListViewCD->Select(sel);
            ListViewCD->EnsureVisible(sel);
        }
    }
}

void wxcd_collectionFrame::OnbtnDeleteCDClick(wxCommandEvent& event)
{
	int id = 0;

	long sel = ListViewCD->GetFirstSelected();
	id = ListViewCD->GetItemData(sel);
	wxCDRec *found = FindCDRec(id);

	int answer = wxMessageBox(found->Title, _("Delete this CD?"),
                               wxYES_NO, this);
    if (answer == wxYES)
	{
		DataFactory::Instance()->DeleteCDRec(id);
		GetCDData();
	}
}

wxCDRec *wxcd_collectionFrame::FindCDRec(const int id)
{
	wxCDRec *found = NULL;
	std::vector<wxCDRec>::iterator it;
	for (it = CDRecs->begin(); it != CDRecs->end(); it++)
	{
		if (it->Id == id)
		{
			found = &(*it);
			break;
		}
	}

	return found;
}

wxCDTrack *wxcd_collectionFrame::FindCDTrack(const int id)
{
	wxCDTrack *found = NULL;
	std::vector<wxCDTrack>::iterator it;
	for (it = CDtracks->begin(); it != CDtracks->end(); it++)
	{
		if (it->id == id)
		{
			found = &(*it);
			break;
		}
	}

	return found;
}

wxArtist *wxcd_collectionFrame::FindArtist(const int id)
{
	wxArtist *found = NULL;
	std::vector<wxArtist>::iterator it;
	for (it = Artists->begin(); it != Artists->end(); it++)
	{
		if (it->Id == id)
		{
			found = &(*it);
			break;
		}
	}

	return found;
}

wxTypeOfMusic *wxcd_collectionFrame::FindTypeOfMusic(const int id)
{
	wxTypeOfMusic *found = NULL;
	std::vector<wxTypeOfMusic>::iterator it;
	for (it = TypeOfMusics->begin(); it != TypeOfMusics->end(); it++)
	{
		if (it->Id == id)
		{
			found = &(*it);
			break;
		}
	}

	return found;
}

void wxcd_collectionFrame::OnListViewCDItemSelect(wxListEvent& event)
{
	int id;
	long sel = ListViewCD->GetFirstSelected();
	id = ListViewCD->GetItemData(sel);
	wxCDRec *found = FindCDRec(id);
	if (found != NULL)
	{
		GetCDTrackData(found->Id);
	}
}

void wxcd_collectionFrame::OnbtnDeleteTrackClick(wxCommandEvent& event)
{
	int answer;
	int CDid = 0;
	int TRid = 0;
	long NoOnCD = 0;

	wxString Title;

	long sel = ListViewCD->GetFirstSelected();
	CDid = ListViewCD->GetItemData(sel);

	sel = ListViewCDRecTracks->GetFirstSelected();
	if (sel != wxNOT_FOUND)
	{
		Title = ListViewCDRecTracks->GetItemText(sel, 1);
		answer = wxMessageBox(Title, _("Delete this Track?"), wxYES_NO, this);
		if (answer == wxYES)
		{

			TRid = ListViewCDRecTracks->GetItemData(sel);
			ListViewCDRecTracks->GetItemText(sel, 0).ToLong(&NoOnCD);
			DataFactory::Instance()->DeleteTrackOnCD(CDid, NoOnCD, TRid);
			GetCDTrackData(CDid);
		}
	}
}

void wxcd_collectionFrame::OnbtnAddTrackClick(wxCommandEvent& event)
{
	int CDid = 0;

	long sel = ListViewCD->GetFirstSelected();
	CDid = ListViewCD->GetItemData(sel);
	SelectTrack selectTrack(this, CDid, NULL);
	if (selectTrack.ShowModal() == wxOK)
	{
		GetCDTrackData(CDid);
	}
}

void wxcd_collectionFrame::OnbtnNewTrackClick(wxCommandEvent& event)
{
	//wxCDTrack data;
	EditTrack editTrack(this, NULL);
	if (editTrack.ShowModal() == wxOK)
	{
		GetTrackData();
	}
}

void wxcd_collectionFrame::OnbtnUpdateTrackClick(wxCommandEvent& event)
{
	wxCDTrack *data;

	int id = 0;
	long sel = ListViewTrackData->GetFirstSelected();
	if (sel != wxNOT_FOUND)
	{
		id = ListViewTrackData->GetItemData(sel);
		data = FindCDTrack(id);
		EditTrack editTrack(this, data);
		if (editTrack.ShowModal() == wxOK)
		{
			GetTrackData();
			ListViewTrackData->Select(sel);
			ListViewTrackData->EnsureVisible(sel);
		}
	}
}

void wxcd_collectionFrame::OnbtnDeleteTrack1Click(wxCommandEvent& event)
{
	int id = 0;

	long sel = ListViewTrackData->GetFirstSelected();
	if (sel != wxNOT_FOUND)
	{
		id = ListViewTrackData->GetItemData(sel);
		wxCDTrack *found = FindCDTrack(id);

		int answer = wxMessageBox(found->Title, _("Delete this Track?"), wxYES_NO, this);
		if (answer == wxYES)
		{
			DataFactory::Instance()->DeleteCDTrack(id);
			GetTrackData();
		}
	}
}

void wxcd_collectionFrame::OnbtnNewArtistClick(wxCommandEvent& event)
{
	EditArtist editArtist(this, NULL);
	if	(editArtist.ShowModal())
	{
		GetArtistData();
	}
}

void wxcd_collectionFrame::OnbtnUpdateArtistClick(wxCommandEvent& event)
{
	wxArtist *data;
	int id = 0;
	long sel = ListViewArtists->GetFirstSelected();
	if (sel != wxNOT_FOUND)
	{
		id = ListViewArtists->GetItemData(sel);
		data = FindArtist(id);
		EditArtist editArtist(this, data);
		if (editArtist.ShowModal() == wxOK)
		{
			GetArtistData();
			ListViewArtists->Select(sel);
			ListViewArtists->EnsureVisible(sel);
		}
	}
}

void wxcd_collectionFrame::OnbtnDeleteArtistClick(wxCommandEvent& event)
{
	int id = 0;

	long sel = ListViewArtists->GetFirstSelected();
	if (sel != wxNOT_FOUND)
	{
		id = ListViewArtists->GetItemData(sel);
		wxArtist *found = FindArtist(id);

		int answer = wxMessageBox(found->FirstName + _(" ") + found->LastName, _("Delete this artist?"), wxYES_NO, this);
		if (answer == wxYES)
		{
			DataFactory::Instance()->DeleteArtist(id);
			GetArtistData();
		}
	}
}

void wxcd_collectionFrame::OnbtnNewTypeClick(wxCommandEvent& event)
{
	EditTypeOfMusic editTypeOfMusic(this, NULL);
	if	(editTypeOfMusic.ShowModal())
	{
		GetTypeOfMusicData();
	}
}

void wxcd_collectionFrame::OnbtnUpdateTypeClick(wxCommandEvent& event)
{
	wxTypeOfMusic *data;
	int id = 0;
	long sel = ListViewTypeOfMusic->GetFirstSelected();
	if (sel != wxNOT_FOUND)
	{
		id = ListViewTypeOfMusic->GetItemData(sel);
		data = FindTypeOfMusic(id);
		EditTypeOfMusic editTypeOfMusic(this, data);
		if (editTypeOfMusic.ShowModal() == wxOK)
		{
			GetTypeOfMusicData();
			ListViewTypeOfMusic->Select(sel);
			ListViewTypeOfMusic->EnsureVisible(sel);
		}
	}
}

void wxcd_collectionFrame::OnbtnDeleteTypeClick(wxCommandEvent& event)
{
	int id = 0;

	long sel = ListViewTypeOfMusic->GetFirstSelected();
	if (sel != wxNOT_FOUND)
	{
		id = ListViewTypeOfMusic->GetItemData(sel);
		wxTypeOfMusic *found = FindTypeOfMusic(id);

		int answer = wxMessageBox(found->TypeOfMusic, _("Delete this music type?"), wxYES_NO, this);
		if (answer == wxYES)
		{
			DataFactory::Instance()->DeleteTypeOfMusic(id);
			GetTypeOfMusicData();
		}
	}
}

void wxcd_collectionFrame::OnbtnUpdateCDTrackClick(wxCommandEvent& event)
{
	int CDid = 0;
	int trackId = 0;
	int noOnCd = 0;
	wxTrackOnCD data;

	long sel = ListViewCD->GetFirstSelected();
    if (sel != wxNOT_FOUND)
    {
        CDid = ListViewCD->GetItemData(sel);
        data.cdId = CDid;
        sel = ListViewCDRecTracks->GetFirstSelected();
        if (sel != wxNOT_FOUND)
        {
            trackId = (long)ListViewCDRecTracks->GetItemData(sel);
            data.trackId = trackId;

            wxString temp = ListViewCDRecTracks->GetItemText (sel, 0);
            noOnCd = wxAtoi(temp);
            data.trackOnCD = noOnCd;
            if (DataFactory::Instance()->GetTrackOnCD(&data))
            {
                SelectTrack selectTrack(this, CDid, &data);
                if (selectTrack.ShowModal() == wxOK)
                {
                    GetCDTrackData(CDid);
                }
            }
        }
    }
}

void wxcd_collectionFrame::OnMenuPlaySelected(wxCommandEvent& event)
{
   	const char *homedir;

	if ((homedir = getenv("HOME")) == NULL)
	{
		homedir = getpwuid(getuid())->pw_dir;
	}

	wxTrackOnCD data;
	wxString homefolder(homedir);

	int CDid = 0;
	long sel = ListViewCD->GetFirstSelected();

	if (sel != wxNOT_FOUND)
    {
        CDid = ListViewCD->GetItemData(sel);

        int icount = ListViewCDRecTracks->GetItemCount();

        for (int c = 0; c < icount; c++)
        {
            int trackId = (long)ListViewCDRecTracks->GetItemData(c);
            data.cdId = CDid;
            data.trackId = trackId;
            data.trackOnCD = c + 1;
            if (DataFactory::Instance()->GetTrackOnCD(&data))
            {
                if (c > 0) ListViewCDRecTracks->Select(c - 1, false);
                ListViewCDRecTracks->Select(c);
                ListViewCDRecTracks->RefreshItem (c);
                ListViewCDRecTracks->Refresh();
                wxYield();
                PlayTheMusic play;
                play.Play((homefolder + _("/") + data.Path).mb_str(wxConvUTF8));
            }
        }
    }
}
