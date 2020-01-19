/***************************************************************
 * Name:      wxcd_collectionMain.h
 * Purpose:   Defines Application Frame
 * Author:    Anders J. Andersen (andersj.andersen@gmail.com)
 * Created:   2019-05-12
 * Copyright: Anders J. Andersen ()
 * License:
 **************************************************************/

#include "EditCDDialog.h"
#include "SelectTrack.h"
#include "EditTrack.h"
#include "EditArtist.h"
#include "EditTypeOfMusic.h"
#include "datafactory.h"
#include <algorithm>

#ifndef WXCD_COLLECTIONMAIN_H
#define WXCD_COLLECTIONMAIN_H

//(*Headers(wxcd_collectionFrame)
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/listctrl.h>
#include <wx/menu.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statusbr.h>
//*)


class CDTreeItemData
{
public:
	CDTreeItemData(const int id) : m_id(id) { }
	const int GetId() const { return m_id; }
private:
	int m_id;
};


class wxcd_collectionFrame: public wxFrame
{
    public:

        wxcd_collectionFrame(wxWindow* parent, wxWindowID id = -1);
        virtual ~wxcd_collectionFrame();

    private:
    	EditCDDialog *editCDDialog;
    	SelectTrack  *selectTrack;


    	std::vector<wxCDRec> *CDRecs;
    	std::vector<wxCDRecTrackRec> *CDRecTrackRec;
    	std::vector<wxCDTrack> *CDtracks;
    	std::vector<wxTypeOfMusic> *TypeOfMusics;
    	std::vector<wxArtist> *Artists;

    	wxCDRec *FindCDRec(const int id);
    	wxCDTrack *FindCDTrack(const int id);
    	wxArtist *FindArtist(const int id);
		wxTypeOfMusic *FindTypeOfMusic(const int id);

    	void GetCDData();
    	void GetCDTrackData(int id);
    	void GetTrackData();
    	void GetTypeOfMusicData();
    	void GetArtistData();

        //(*Handlers(wxcd_collectionFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnbtnNewCDClick(wxCommandEvent& event);
        void OnbtnUpdateCDClick(wxCommandEvent& event);
        void OnbtnDeleteCDClick(wxCommandEvent& event);
        void OnListViewCDItemSelect(wxListEvent& event);
        void OnbtnDeleteTrackClick(wxCommandEvent& event);
        void OnbtnAddTrackClick(wxCommandEvent& event);
        void OnbtnNewTrackClick(wxCommandEvent& event);
        void OnbtnUpdateTrackClick(wxCommandEvent& event);
        void OnbtnDeleteTrack1Click(wxCommandEvent& event);
        void OnbtnNewArtistClick(wxCommandEvent& event);
        void OnbtnUpdateArtistClick(wxCommandEvent& event);
        void OnbtnDeleteArtistClick(wxCommandEvent& event);
        void OnbtnNewTypeClick(wxCommandEvent& event);
        void OnbtnUpdateTypeClick(wxCommandEvent& event);
        void OnbtnDeleteTypeClick(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnbtnUpdateCDTrackClick(wxCommandEvent& event);
        void OnMenuPlaySelected(wxCommandEvent& event);
        //*)

        //(*Identifiers(wxcd_collectionFrame)
        static const long ID_LISTVIEW2;
        static const long ID_LISTVIEW1;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_BUTTON3;
        static const long ID_BUTTON4;
        static const long ID_BUTTON15;
        static const long ID_BUTTON5;
        static const long ID_PANEL1;
        static const long ID_LISTVIEW3;
        static const long ID_BUTTON6;
        static const long ID_BUTTON7;
        static const long ID_BUTTON8;
        static const long ID_PANEL2;
        static const long ID_LISTVIEW4;
        static const long ID_BUTTON9;
        static const long ID_BUTTON10;
        static const long ID_BUTTON11;
        static const long ID_PANEL3;
        static const long ID_LISTVIEW5;
        static const long ID_BUTTON12;
        static const long ID_BUTTON13;
        static const long ID_BUTTON14;
        static const long ID_PANEL4;
        static const long ID_NOTEBOOK1;
        static const long ID_MENUITEM1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(wxcd_collectionFrame)
        wxButton* btnAddTrack;
        wxButton* btnDeleteArtist;
        wxButton* btnDeleteCD;
        wxButton* btnDeleteTrack1;
        wxButton* btnDeleteTrack;
        wxButton* btnDeleteType;
        wxButton* btnNewArtist;
        wxButton* btnNewCD;
        wxButton* btnNewTrack;
        wxButton* btnNewType;
        wxButton* btnUpdateArtist;
        wxButton* btnUpdateCD;
        wxButton* btnUpdateCDTrack;
        wxButton* btnUpdateTrack;
        wxButton* btnUpdateType;
        wxFlexGridSizer* FlexGridSizer1;
        wxListView* ListViewArtists;
        wxListView* ListViewCD;
        wxListView* ListViewCDRecTracks;
        wxListView* ListViewTrackData;
        wxListView* ListViewTypeOfMusic;
        wxMenuItem* MenuItem3;
        wxNotebook* Notebook1;
        wxPanel* Panel1;
        wxPanel* Panel2;
        wxPanel* Panel3;
        wxPanel* Panel4;
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // WXCD_COLLECTIONMAIN_H
