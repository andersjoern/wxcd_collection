#include "EditCDDialog.h"
#include "wx/valtext.h"

//(*InternalHeaders(EditCDDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(EditCDDialog)
const long EditCDDialog::ID_STATICTEXT1 = wxNewId();
const long EditCDDialog::ID_TEXTCTRL1 = wxNewId();
const long EditCDDialog::ID_STATICTEXT2 = wxNewId();
const long EditCDDialog::ID_TEXTCTRL2 = wxNewId();
const long EditCDDialog::ID_STATICTEXT3 = wxNewId();
const long EditCDDialog::ID_TEXTCTRL3 = wxNewId();
const long EditCDDialog::ID_CHOICE1 = wxNewId();
const long EditCDDialog::ID_BUTTON1 = wxNewId();
const long EditCDDialog::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(EditCDDialog,wxDialog)
	//(*EventTable(EditCDDialog)
	//*)
END_EVENT_TABLE()

EditCDDialog::EditCDDialog(wxWindow* parent, wxCDRec *data, wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(EditCDDialog)
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer2;

	Create(parent, id, _("Edit CD"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(4, 2, 0, 0);
	FlexGridSizer1->AddGrowableCol(1);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Id:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(65,27), wxTE_RIGHT, wxTextValidator(wxFILTER_NUMERIC, &m_id), _T("ID_TEXTCTRL1"));
	TextCtrl1->SetMaxLength(5);
	FlexGridSizer1->Add(TextCtrl1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Title:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl2 = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(166,27), 0, wxTextValidator(wxFILTER_NONE, &m_Name), _T("ID_TEXTCTRL2"));
	TextCtrl2->SetMaxLength(50);
	FlexGridSizer1->Add(TextCtrl2, 1, wxALL|wxEXPAND, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Type of music:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer1->Add(StaticText3, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer2->AddGrowableCol(1);
	TextCtrl3 = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxSize(62,27), 0, wxTextValidator(wxFILTER_NUMERIC, &m_TypeOfMusicId), _T("ID_TEXTCTRL3"));
	TextCtrl3->Disable();
	FlexGridSizer2->Add(TextCtrl3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ChoiceTypeOfMusic = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	FlexGridSizer2->Add(ChoiceTypeOfMusic, 1, wxALL|wxEXPAND, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxEXPAND, 5);
	btnOk = new wxButton(this, ID_BUTTON1, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer1->Add(btnOk, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnCancel = new wxButton(this, ID_BUTTON2, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer1->Add(btnCancel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&EditCDDialog::OnChoiceTypeOfMusicSelect);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EditCDDialog::OnbtnOkClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EditCDDialog::OnbtnCancelClick);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&EditCDDialog::OnClose);
	//*)

	std::vector<wxTypeOfMusic> *typeOfMusics;

	if (data != NULL)
	{
		callUpdate = true;
		int select = 0;
		int counter = 0;
		m_id = wxString::Format(wxT("%i"), data->Id);
		m_Name = data->Title;
		m_TypeOfMusicId = wxString::Format(wxT("%i"), data->TypeOfMusicId);
		m_TypeOfMusic = data->TypeOfMusic;
		TextCtrl1->Enable(false);
		typeOfMusics = DataFactory::Instance()->GetTypeOfMusics();
		std::vector<wxTypeOfMusic>::iterator it;
		for (it = typeOfMusics->begin(); it != typeOfMusics->end(); it++)
		{
			long lId = it->Id;
			ChoiceTypeOfMusic->Append(it->TypeOfMusic, (void*)lId);
			if (it->Id == data->TypeOfMusicId)
				select = counter;
			counter++;
		}
		ChoiceTypeOfMusic->SetSelection(select);
	}
	else
	{
		callUpdate = false;
		typeOfMusics = DataFactory::Instance()->GetTypeOfMusics();
		std::vector<wxTypeOfMusic>::iterator it;
		for (it = typeOfMusics->begin(); it != typeOfMusics->end(); it++)
		{
			long lId = it->Id;
			ChoiceTypeOfMusic->Append(it->TypeOfMusic, (void*)lId);
		}
	}
}

EditCDDialog::~EditCDDialog()
{
	//(*Destroy(EditCDDialog)
	//*)
}

void EditCDDialog::OnbtnOkClick(wxCommandEvent& event)
{
	wxCDRec data1;

	if (Validate() && TransferDataFromWindow())
	{
		data1.Id = wxAtoi(m_id);
		data1.Title = m_Name;
		data1.TypeOfMusicId = wxAtoi(m_TypeOfMusicId);
		data1.TypeOfMusic = m_TypeOfMusic;
		if (callUpdate)
			DataFactory::Instance()->UpdateCDRecord(&data1);
		else
			DataFactory::Instance()->NewCDRecord(&data1);
	}

    EndModal( wxOK );
}

void EditCDDialog::OnbtnCancelClick(wxCommandEvent& event)
{
	EndModal( wxCANCEL );
}

void EditCDDialog::OnClose(wxCloseEvent& event)
{
	EndModal( wxCANCEL );
}

void EditCDDialog::OnChoiceTypeOfMusicSelect(wxCommandEvent& event)
{
	long sel;
	sel = (long)ChoiceTypeOfMusic->GetClientData(event.GetSelection());
	m_TypeOfMusicId = wxString::Format(wxT("%i"), (int)sel);
	TransferDataToWindow();
}
