#ifndef EDITARTIST_H
#define EDITARTIST_H
#include "datafactory.h"

//(*Headers(EditArtist)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class EditArtist: public wxDialog
{
	public:

		EditArtist(wxWindow* parent, wxArtist *data, wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~EditArtist();

		//(*Declarations(EditArtist)
		wxButton* btnCancel;
		wxButton* btnOK;
		wxStaticText* StaticText1;
		wxStaticText* StaticText2;
		wxStaticText* StaticText3;
		wxTextCtrl* TextCtrlFirstName;
		wxTextCtrl* TextCtrlId;
		wxTextCtrl* TextCtrlLastName;
		//*)

	protected:

		//(*Identifiers(EditArtist)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL3;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:
		bool callUpdate;
		wxString m_Id;
		wxString m_FirstName;
		wxString m_LastName;

		//(*Handlers(EditArtist)
		void OnbtnOKClick(wxCommandEvent& event);
		void OnbtnCancelClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
