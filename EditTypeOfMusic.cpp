#include "EditTypeOfMusic.h"
#include "wx/valtext.h"

//(*InternalHeaders(EditTypeOfMusic)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(EditTypeOfMusic)
const long EditTypeOfMusic::ID_STATICTEXT1 = wxNewId();
const long EditTypeOfMusic::ID_TEXTCTRL1 = wxNewId();
const long EditTypeOfMusic::ID_STATICTEXT2 = wxNewId();
const long EditTypeOfMusic::ID_TEXTCTRL2 = wxNewId();
const long EditTypeOfMusic::ID_BUTTON1 = wxNewId();
const long EditTypeOfMusic::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(EditTypeOfMusic,wxDialog)
	//(*EventTable(EditTypeOfMusic)
	//*)
END_EVENT_TABLE()

EditTypeOfMusic::EditTypeOfMusic(wxWindow* parent, wxTypeOfMusic *data, wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(EditTypeOfMusic)
	wxFlexGridSizer* FlexGridSizer1;
	wxBoxSizer* BoxSizer1;

	Create(parent, id, _("Edit type of Music"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(3, 2, 0, 0);
	FlexGridSizer1->AddGrowableCol(1);
	FlexGridSizer1->AddGrowableRow(1);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Id:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlId = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_NUMERIC, &m_Id), _T("ID_TEXTCTRL1"));
	FlexGridSizer1->Add(TextCtrlId, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Type of Music:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlTypeOfMusic = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_NONE, &m_TypeOfMusic), _T("ID_TEXTCTRL2"));
	FlexGridSizer1->Add(TextCtrlTypeOfMusic, 1, wxALL|wxEXPAND, 5);
	FlexGridSizer1->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	btnOk = new wxButton(this, ID_BUTTON1, _("Ok"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer1->Add(btnOk, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnCancel = new wxButton(this, ID_BUTTON2, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer1->Add(btnCancel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EditTypeOfMusic::OnbtnOkClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EditTypeOfMusic::OnbtnCancelClick);
	//*)

	if (data != NULL)
	{
		callUpdate = true;
		m_Id = wxString::Format(_("%i"), data->Id);
		TextCtrlId->Enable(false);
		m_TypeOfMusic = data->TypeOfMusic;
	}
	else
	{
		callUpdate = false;
	}
}

EditTypeOfMusic::~EditTypeOfMusic()
{
	//(*Destroy(EditTypeOfMusic)
	//*)
}

void EditTypeOfMusic::OnbtnOkClick(wxCommandEvent& event)
{
	long lId = 0L;
	wxTypeOfMusic data;
	TransferDataFromWindow();
	m_Id.ToLong(&lId);
	data.Id = lId;
	data.TypeOfMusic = m_TypeOfMusic;

	if (callUpdate)
		DataFactory::Instance()->UpdateTypeOfMusic(&data);
	else
		DataFactory::Instance()->NewTypeOfMusic(&data);

	EndModal(wxOK);
}

void EditTypeOfMusic::OnbtnCancelClick(wxCommandEvent& event)
{
	EndModal(wxCANCEL);
}
