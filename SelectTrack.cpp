#include "SelectTrack.h"
#include "wx/valtext.h"


//(*InternalHeaders(SelectTrack)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(SelectTrack)
const long SelectTrack::ID_STATICTEXT1 = wxNewId();
const long SelectTrack::ID_TEXTCTRL1 = wxNewId();
const long SelectTrack::ID_STATICTEXT2 = wxNewId();
const long SelectTrack::ID_TEXTCTRL2 = wxNewId();
const long SelectTrack::ID_LISTVIEW1 = wxNewId();
const long SelectTrack::ID_BUTTON1 = wxNewId();
const long SelectTrack::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SelectTrack,wxDialog)
	//(*EventTable(SelectTrack)
	//*)
END_EVENT_TABLE()

SelectTrack::SelectTrack(wxWindow* parent, const int cdId, wxTrackOnCD *data, wxWindowID id, const wxPoint& pos, const wxSize& size)
{
	//(*Initialize(SelectTrack)
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer3;

	Create(parent, id, _("Select track"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(3, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(1);
	FlexGridSizer2 = new wxFlexGridSizer(2, 2, 0, 0);
	FlexGridSizer2->AddGrowableCol(1);
	FlexGridSizer2->AddGrowableRow(1);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Track on CD:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlrackNoOnCD = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_NUMERIC, &m_trid), _T("ID_TEXTCTRL1"));
	FlexGridSizer2->Add(TextCtrlrackNoOnCD, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Path to Music:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer2->Add(StaticText2, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	TextPathToMusic = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(339,28), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	FlexGridSizer2->Add(TextPathToMusic, 1, wxALL|wxALIGN_LEFT, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxEXPAND, 5);
	lvTracks = new wxListView(this, ID_LISTVIEW1, wxDefaultPosition, wxDefaultSize, wxLC_REPORT, wxDefaultValidator, _T("ID_LISTVIEW1"));
	FlexGridSizer1->Add(lvTracks, 1, wxALL|wxEXPAND|wxFIXED_MINSIZE, 5);
	FlexGridSizer3 = new wxFlexGridSizer(0, 2, 0, 0);
	btnOK = new wxButton(this, ID_BUTTON1, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer3->Add(btnOK, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnCancel = new wxButton(this, ID_BUTTON2, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer3->Add(btnCancel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer3, 1, wxALL|wxEXPAND, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);
	Center();

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SelectTrack::OnbtnOKClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SelectTrack::OnbtnCancelClick);
	//*)

	m_cdId = cdId;

	if (data != NULL)
    {
        callUpdate = true;
		m_trid = wxString::Format(wxT("%i"), data->trackOnCD);
		iTrId = data->trackId;
		m_path = data->Path;
		TextPathToMusic->SetValue(m_path);
        NoOnCD = data->trackOnCD;
        oldValues = *data;
    }
    else
    {
        callUpdate = false;
    }

	GetTracks();
}

SelectTrack::~SelectTrack()
{
	//(*Destroy(SelectTrack)
	//*)
}

void SelectTrack::GetTracks()
{
	long itemCount = 0;
	long selected = 0;
	lvTracks->ClearAll();
    lvTracks->AppendColumn(_("TRId"), wxLIST_FORMAT_RIGHT);
    lvTracks->AppendColumn(_("Title"), wxLIST_FORMAT_LEFT, 300 );
	m_tracks = DataFactory::Instance()->GetSortedTracks();
	std::map<wxString, wxCDTrack>::iterator it;
	for (it = m_tracks->begin(); it != m_tracks->end(); it++)
	{
        lvTracks->InsertItem(itemCount, wxString::Format(_("%i"),it->second.id));
        lvTracks->SetItem(itemCount, 1, it->second.ArtistLastName + _(" ") + it->second.Title);
        lvTracks->SetItemData(itemCount, (long)it->second.id);
        if (iTrId == it->second.id)
        {
            selected = itemCount;
        }
        itemCount++;
	}
	if (callUpdate)
    {
        lvTracks->Select(selected);
        lvTracks->Focus(selected);
    }
}

void SelectTrack::OnbtnOKClick(wxCommandEvent& event)
{
    wxTrackOnCD data;
    int TRid;
    bool result;

	m_path = TextPathToMusic->GetValue();

	Validate();
	TransferDataFromWindow();

    m_trid.ToLong(&NoOnCD);

   	long sel = lvTracks->GetFirstSelected();

   	if (sel != wxNOT_FOUND)
	{
	    data.trackOnCD = NoOnCD;
	    data.Path = m_path;
		TRid = lvTracks->GetItemData(sel);
	    data.trackId = TRid;
	    data.cdId = m_cdId;
	    if (callUpdate)
            result = DataFactory::Instance()->UpdateTrackOnCD(&oldValues, &data);
        else
            result = DataFactory::Instance()->AddTrackToCD(&data);
	}
	EndModal( wxOK );
}

void SelectTrack::OnbtnCancelClick(wxCommandEvent& event)
{
	EndModal( wxCANCEL );
}
