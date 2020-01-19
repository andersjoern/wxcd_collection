#include "EditTrack.h"
#include "wx/valtext.h"

//(*InternalHeaders(EditTrack)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(EditTrack)
const long EditTrack::ID_STATICTEXT1 = wxNewId();
const long EditTrack::ID_TEXTCTRL1 = wxNewId();
const long EditTrack::ID_STATICTEXT2 = wxNewId();
const long EditTrack::ID_TEXTCTRL2 = wxNewId();
const long EditTrack::ID_STATICTEXT3 = wxNewId();
const long EditTrack::ID_TEXTCTRL3 = wxNewId();
const long EditTrack::ID_CHOICE2 = wxNewId();
const long EditTrack::ID_STATICTEXT4 = wxNewId();
const long EditTrack::ID_TEXTCTRL4 = wxNewId();
const long EditTrack::ID_CHOICE1 = wxNewId();
const long EditTrack::ID_BUTTON1 = wxNewId();
const long EditTrack::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(EditTrack,wxDialog)
	//(*EventTable(EditTrack)
	//*)
END_EVENT_TABLE()

EditTrack::EditTrack(wxWindow* parent, wxCDTrack *data, wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(EditTrack)
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer3;

	Create(parent, id, _("Edit Track"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxTAB_TRAVERSAL, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(5, 2, 0, 0);
	FlexGridSizer1->AddGrowableRow(1);
	FlexGridSizer1->AddGrowableRow(2);
	FlexGridSizer1->AddGrowableRow(3);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Id:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlId = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_NUMERIC, &m_id), _T("ID_TEXTCTRL1"));
	FlexGridSizer1->Add(TextCtrlId, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Title:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlTitle = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_NONE, &m_Title), _T("ID_TEXTCTRL2"));
	FlexGridSizer1->Add(TextCtrlTitle, 1, wxALL|wxEXPAND, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Artist:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer1->Add(StaticText3, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer2->AddGrowableCol(1);
	TextCtrlArtistId = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_NUMERIC, &m_ArtistId), _T("ID_TEXTCTRL3"));
	TextCtrlArtistId->Disable();
	FlexGridSizer2->Add(TextCtrlArtistId, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ChoiceArtists = new wxChoice(this, ID_CHOICE2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
	FlexGridSizer2->Add(ChoiceArtists, 1, wxALL|wxEXPAND, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxEXPAND, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Type Of Music:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer1->Add(StaticText4, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer3->AddGrowableCol(1);
	TextCtrlTypeOfMusicId = new wxTextCtrl(this, ID_TEXTCTRL4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_NUMERIC, &m_TypeOfMusicId), _T("ID_TEXTCTRL4"));
	TextCtrlTypeOfMusicId->Disable();
	FlexGridSizer3->Add(TextCtrlTypeOfMusicId, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ChoiceTypeOfMusics = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	FlexGridSizer3->Add(ChoiceTypeOfMusics, 1, wxALL|wxEXPAND, 5);
	FlexGridSizer1->Add(FlexGridSizer3, 1, wxALL|wxEXPAND, 5);
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

	Connect(ID_CHOICE2,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&EditTrack::OnChoiceArtistsSelect);
	Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&EditTrack::OnChoiceTypeOfMusicsSelect);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EditTrack::OnbtnOKClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EditTrack::OnbtnCancelClick);
	//*)


	if (data != NULL)
	{
		callUpdate = true;
		m_id = wxString::Format(_("%i"), data->id);
		TextCtrlId->Enable(false);
		m_Title = data->Title;
		m_ArtistId = wxString::Format(_("%i"), data->artist);
		m_TypeOfMusicId = wxString::Format(_("%i"), data->typeOfMusic);
		GetArtists(data->artist);
		GetTypeOfMusic(data->typeOfMusic);
	}
	else
	{
		callUpdate = false;
		GetArtists(-1);
		GetTypeOfMusic(-1);
	}
}

EditTrack::~EditTrack()
{
	//(*Destroy(EditTrack)
	//*)
}

void EditTrack::GetArtists(const int id)
{
	long lId = 0L;
	long counter = 0;
	long select = -1;

	ChoiceArtists->Clear();
	artists = DataFactory::Instance()->GetArtists();
	std::vector<wxArtist>::iterator it;
	for (it = artists->begin(); it != artists->end(); it++)
	{
		lId = it->Id;
		ChoiceArtists->Append(it->FirstName + _(" ") + it->LastName, (void *)lId);
		if (callUpdate && (long)id == lId)
			select = counter;
		counter++;
	}
	if (select >= 0)
		ChoiceArtists->Select(select);
}

void EditTrack::GetTypeOfMusic(const int id)
{
	long lId = 0L;
	int counter = 0;
	int select = -1;
	ChoiceTypeOfMusics->Clear();
	typeofmusics = DataFactory::Instance()->GetTypeOfMusics();
	std::vector<wxTypeOfMusic>::iterator it;
	for (it = typeofmusics->begin(); it != typeofmusics->end(); it++)
	{
		lId = it->Id;
		ChoiceTypeOfMusics->Append(it->TypeOfMusic, (void *)lId);
		if (callUpdate && (long)id == lId)
			select = counter;
		counter++;
	}
	if (select >= 0)
		ChoiceTypeOfMusics->Select(select);
}

void EditTrack::OnbtnOKClick(wxCommandEvent& event)
{
	long lId;
	wxCDTrack data;

	TransferDataFromWindow();

	m_id.ToLong(&lId);
	data.id = lId;
	data.Title = m_Title;
	m_TypeOfMusicId.ToLong(&lId);
	data.typeOfMusic = lId;
	m_ArtistId.ToLong(&lId);
	data.artist = lId;

	if (callUpdate)
	{
		DataFactory::Instance()->UpdateCDTrack(&data);
	}
	else
	{
		DataFactory::Instance()->NewCDTrack(&data);
	}
    EndModal( wxOK );
}

void EditTrack::OnbtnCancelClick(wxCommandEvent& event)
{
	EndModal( wxCANCEL );
}

void EditTrack::OnChoiceArtistsSelect(wxCommandEvent& event)
{
	long sel;
	sel = (long)ChoiceArtists->GetClientData(event.GetSelection());
	m_ArtistId = wxString::Format(wxT("%i"), (int)sel);
	TransferDataToWindow();
}

void EditTrack::OnChoiceTypeOfMusicsSelect(wxCommandEvent& event)
{
	long sel;
	sel = (long)ChoiceTypeOfMusics->GetClientData(event.GetSelection());
	m_TypeOfMusicId = wxString::Format(wxT("%i"), (int)sel);
	TransferDataToWindow();
}
