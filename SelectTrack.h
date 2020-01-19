#ifndef SELECTTRACK_H
#define SELECTTRACK_H
#include "datafactory.h"
//(*Headers(SelectTrack)
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/listctrl.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class SelectTrack: public wxDialog
{
	public:

		SelectTrack(wxWindow* parent, const int cdId, wxTrackOnCD *data, wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~SelectTrack();

		//(*Declarations(SelectTrack)
		wxTextCtrl* TextPathToMusic;
		wxTextCtrl* TextCtrlrackNoOnCD;
		wxListView* lvTracks;
		wxStaticText* StaticText1;
		wxStaticText* StaticText2;
		wxButton* btnOK;
		wxButton* btnCancel;
		//*)

	protected:

		//(*Identifiers(SelectTrack)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		static const long ID_LISTVIEW1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:
		std::map<wxString, wxCDTrack> *m_tracks;
		void GetTracks();
		wxString m_trid;
		wxString m_path;

		long iTrId;

        long NoOnCD;
		bool callUpdate;
		int m_cdId;

		wxTrackOnCD oldValues;
		//(*Handlers(SelectTrack)
		void OnbtnOKClick(wxCommandEvent& event);
		void OnbtnCancelClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
