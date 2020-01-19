#ifndef EDITTYPEOFMUSIC_H
#define EDITTYPEOFMUSIC_H
#include "datafactory.h"

//(*Headers(EditTypeOfMusic)
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class EditTypeOfMusic: public wxDialog
{
	public:

		EditTypeOfMusic(wxWindow* parent, wxTypeOfMusic *data, wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~EditTypeOfMusic();

		//(*Declarations(EditTypeOfMusic)
		wxTextCtrl* TextCtrlId;
		wxTextCtrl* TextCtrlTypeOfMusic;
		wxStaticText* StaticText1;
		wxButton* btnOk;
		wxStaticText* StaticText2;
		wxButton* btnCancel;
		//*)

	protected:

		//(*Identifiers(EditTypeOfMusic)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:
		bool callUpdate;
		wxString m_Id;
		wxString m_TypeOfMusic;

		//(*Handlers(EditTypeOfMusic)
		void OnbtnOkClick(wxCommandEvent& event);
		void OnbtnCancelClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
