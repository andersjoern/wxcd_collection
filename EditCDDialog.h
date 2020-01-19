#ifndef EDIRCDDIALOG_H
#define EDIRCDDIALOG_H

#include "datafactory.h"

//(*Headers(EditCDDialog)
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class EditCDDialog: public wxDialog
{
	public:

		EditCDDialog(wxWindow* parent, wxCDRec *data, wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~EditCDDialog();


		//(*Declarations(EditCDDialog)
		wxButton* btnCancel;
		wxButton* btnOk;
		wxChoice* ChoiceTypeOfMusic;
		wxStaticText* StaticText1;
		wxStaticText* StaticText2;
		wxStaticText* StaticText3;
		wxTextCtrl* TextCtrl1;
		wxTextCtrl* TextCtrl2;
		wxTextCtrl* TextCtrl3;
		//*)

	protected:

		//(*Identifiers(EditCDDialog)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL3;
		static const long ID_CHOICE1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:
		bool callUpdate;
		wxString m_id;
		wxString m_Name;
		wxString m_TypeOfMusicId;
		wxString m_TypeOfMusic;

		//(*Handlers(EditCDDialog)
		void OnbtnOkClick(wxCommandEvent& event);
		void OnbtnCancelClick(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);
		void OnTextCtrl4Text(wxCommandEvent& event);
		void OnChoiceTypeOfMusicSelect(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
