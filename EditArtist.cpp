#include "EditArtist.h"
#include "wx/valtext.h"


//(*InternalHeaders(EditArtist)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(EditArtist)
const long EditArtist::ID_STATICTEXT1 = wxNewId();
const long EditArtist::ID_TEXTCTRL1 = wxNewId();
const long EditArtist::ID_STATICTEXT2 = wxNewId();
const long EditArtist::ID_TEXTCTRL2 = wxNewId();
const long EditArtist::ID_STATICTEXT3 = wxNewId();
const long EditArtist::ID_TEXTCTRL3 = wxNewId();
const long EditArtist::ID_BUTTON1 = wxNewId();
const long EditArtist::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(EditArtist,wxDialog)
	//(*EventTable(EditArtist)
	//*)
END_EVENT_TABLE()

EditArtist::EditArtist(wxWindow* parent, wxArtist *data, wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(EditArtist)
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, _("Edit Artist"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(4, 2, 0, 0);
	FlexGridSizer1->AddGrowableCol(1);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Id:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlId = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_NUMERIC, &m_Id), _T("ID_TEXTCTRL1"));
	FlexGridSizer1->Add(TextCtrlId, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("First name:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlFirstName = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_NONE, &m_FirstName), _T("ID_TEXTCTRL2"));
	FlexGridSizer1->Add(TextCtrlFirstName, 1, wxALL|wxEXPAND, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Last name:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer1->Add(StaticText3, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlLastName = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_NONE, &m_LastName), _T("ID_TEXTCTRL3"));
	FlexGridSizer1->Add(TextCtrlLastName, 1, wxALL|wxEXPAND, 5);
	FlexGridSizer1->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	btnOK = new wxButton(this, ID_BUTTON1, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer1->Add(btnOK, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnCancel = new wxButton(this, ID_BUTTON2, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer1->Add(btnCancel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EditArtist::OnbtnOKClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EditArtist::OnbtnCancelClick);
	//*)

	if (data != NULL)
	{
		callUpdate = true;
		m_Id = wxString::Format(_("%i"), data->Id);
		m_FirstName = data->FirstName;
		m_LastName = data->LastName;
		TextCtrlId->Enable(false);
	}
	else
	{
		callUpdate = false;
	}
}

EditArtist::~EditArtist()
{
	//(*Destroy(EditArtist)
	//*)
}

void EditArtist::OnbtnOKClick(wxCommandEvent& event)
{
	wxArtist data;
	long lId;
	TransferDataFromWindow();
	m_Id.ToLong(&lId);
	data.Id = lId;
	data.FirstName = m_FirstName;
	data.LastName = m_LastName;
	if (callUpdate)
	{
		DataFactory::Instance()->UpdateArtist(&data);
	}
	else
	{
		DataFactory::Instance()->NewArtist(&data);
	}
	EndModal(wxOK);
}

void EditArtist::OnbtnCancelClick(wxCommandEvent& event)
{
	EndModal(wxCANCEL);
}
