#ifndef EDITTRACK_H
#define EDITTRACK_H
#include "datafactory.h"

//(*Headers(EditTrack)
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class EditTrack: public wxDialog
{
	public:

		EditTrack(wxWindow* parent, wxCDTrack *data, wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~EditTrack();

		//(*Declarations(EditTrack)
		wxButton* btnCancel;
		wxButton* btnOK;
		wxChoice* ChoiceArtists;
		wxChoice* ChoiceTypeOfMusics;
		wxStaticText* StaticText1;
		wxStaticText* StaticText2;
		wxStaticText* StaticText3;
		wxStaticText* StaticText4;
		wxTextCtrl* TextCtrlArtistId;
		wxTextCtrl* TextCtrlId;
		wxTextCtrl* TextCtrlTitle;
		wxTextCtrl* TextCtrlTypeOfMusicId;
		//*)

	protected:

		//(*Identifiers(EditTrack)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL3;
		static const long ID_CHOICE2;
		static const long ID_STATICTEXT4;
		static const long ID_TEXTCTRL4;
		static const long ID_CHOICE1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:
		bool callUpdate;
		wxString m_id;
		wxString m_Title;
		wxString m_ArtistId;
		wxString m_TypeOfMusicId;

        std::vector<wxArtist> *artists;
        std::vector<wxTypeOfMusic>  *typeofmusics;

		void GetArtists(const int id);
		void GetTypeOfMusic(const int id);

		//(*Handlers(EditTrack)
		void OnbtnOKClick(wxCommandEvent& event);
		void OnbtnCancelClick(wxCommandEvent& event);
		void OnChoiceArtistsSelect(wxCommandEvent& event);
		void OnChoiceTypeOfMusicsSelect(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
