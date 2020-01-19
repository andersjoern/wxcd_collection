#include "datafactory.h"
#include <wx/msgdlg.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <string>

const char *directory1 = "/Data";
const char *directory2 = "/cd_collection/";

DataFactory *DataFactory::instance = NULL;

void ReportDbError(const char *s)
{
	wxString sErr(s);
    wxMessageBox(sErr, _("Error..."));
}

DataFactory::DataFactory()
{
	const char *homedir;
    struct stat buffer;
    int res = 0;

	InitDB(ReportDbError);

	if ((homedir = getenv("HOME")) == NULL)
	{
		homedir = getpwuid(getuid())->pw_dir;
	}
	std::string s = std::string(homedir) + std::string(directory1);
	if (stat (s.c_str(), &buffer) != 0)
    {
        res = mkdir(s.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
    s += std::string(directory2);
	if (stat (s.c_str(), &buffer) != 0)
    {
        res = mkdir(s.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
}

DataFactory *DataFactory::Instance()
{
	if (instance == NULL)
		instance = new DataFactory;
	return instance;
}

void DataFactory::DestroyInstance()
{
	if (instance != NULL)
	{
		delete instance;
		instance = NULL;
	}
}

std::vector<wxCDRec> *DataFactory::GetCDRecords()
{
	wxCDRec cdr;

	cdrecords.clear();
    unique_ptr<CDrec> cdrec(CDrec::Instance());
	unique_ptr<TypeOfMusic> tomus(TypeOfMusic::Instance());

	while (cdrec->ReadNextRecord(0))
	{
		cdr.Id = cdrec->GetId();
		cdr.Title = wxString(cdrec->GetTitle().c_str(), wxConvUTF8);
		cdr.TypeOfMusicId = cdrec->GetTypeOfMusic();
		tomus->SetId(cdr.TypeOfMusicId);
		if (tomus->ReadRecord(0))
		{
			cdr.TypeOfMusic = wxString(tomus->GetTypeOfMusic().c_str(), wxConvUTF8);
		}
		else
		{
			cdr.TypeOfMusic = _("Unknown");
		}
		cdrecords.push_back(cdr);
	}

	return &cdrecords;
}

std::vector<wxCDRecTrackRec> *DataFactory::GetRecTrackRecords(int id)
{
	wxCDRecTrackRec recTrack;

	cdrectrackrecords.clear();

	unique_ptr<CDRecTrack> cdrectrack(CDRecTrack::Instance());
	unique_ptr<Artist> artist(Artist::Instance());
	unique_ptr<CDTrack> cdtrack(CDTrack::Instance());

	cdrectrack->ClearRecord();
	cdrectrack->SetCDId(id);
	cdrectrack->ReadRecord(0);

	while (cdrectrack->ReadNextRecord(0))
	{
		if (cdrectrack->GetCDId() == id)
		{
			recTrack.cdId = cdrectrack->GetCDId();
			recTrack.trackOnCD = cdrectrack->GetTrackOnCD();
			recTrack.trackId = cdrectrack->GetTRId();
			cdtrack->SetId(cdrectrack->GetTRId());
			if (cdtrack->ReadRecord(0))
			{
				recTrack.TrackTitle = wxString(cdtrack->GetTitle().c_str(), wxConvUTF8);
				artist->SetId(cdtrack->GetArtist());
				if (artist->ReadRecord(0))
					recTrack.ArtistLastName = wxString(artist->GetLastName().c_str(), wxConvUTF8);
				else
					recTrack.ArtistLastName = _("Unknown");
			}

			cdrectrackrecords.push_back(recTrack);
		}
		else
		{
			break;
		}
	}

	return &cdrectrackrecords;
}

bool DataFactory::UpdateCDRecord(wxCDRec *rec)
{
	bool retval = false;
	unique_ptr<CDrec> cdrec(CDrec::Instance());
	cdrec->SetId(rec->Id);
	if (cdrec->ReadRecord(0))
	{
		cdrec->SetTitle(std::string(rec->Title.mb_str(wxConvUTF8)));
		cdrec->SetTypeOfMusic(rec->TypeOfMusicId);
		retval = cdrec->UpdateRecord();
	}
	return retval;
}

bool DataFactory::NewCDRecord(wxCDRec *rec)
{
	bool retval = false;
	unique_ptr<CDrec> cdrec(CDrec::Instance());
	cdrec->SetId(rec->Id);
	if (!cdrec->ReadRecord(0))
	{
		cdrec->SetId(rec->Id);
		cdrec->SetTitle(std::string(rec->Title.mb_str(wxConvUTF8)));
		cdrec->SetTypeOfMusic(rec->TypeOfMusicId);
		retval = cdrec->WriteRecord();
	}

	return retval;
}

std::vector<wxTypeOfMusic> *DataFactory::GetTypeOfMusics()
{
	wxTypeOfMusic data;
	typeofmusics.clear();

    unique_ptr<TypeOfMusic> tomus(TypeOfMusic::Instance());
	while (tomus->ReadNextRecord(0))
	{
		data.Id = tomus->GetId();
		data.TypeOfMusic = wxString(tomus->GetTypeOfMusic().c_str(), wxConvUTF8);
		typeofmusics.push_back(data);
	}

	return &typeofmusics;
}

bool DataFactory::DeleteCDRec(int id)
{
	bool retval = false;
	unique_ptr<CDrec> cdrec(CDrec::Instance());
	unique_ptr<CDRecTrack> cdrectrack(CDRecTrack::Instance());
	cdrec->SetId(id);
	if (cdrec->ReadRecord(0))
	{
		if (cdrec->DeleteRecord())
		{
			while (cdrectrack->ReadNextRecord(0))
			{
				if (cdrectrack->GetCDId() == id)
				{
					cdrectrack->DeleteRecord();
					cdrectrack->ResetFilePos();
				}
			}
			cdrectrack->FlushFile();
			retval = true;
		}
	}
	return retval;
}

std::map<wxString, wxCDTrack> *DataFactory::GetSortedTracks()
{
	wxCDTrack data;
	tracks.clear();

	unique_ptr<CDTrack> cdtrack(CDTrack::Instance());
	unique_ptr<Artist> artist(Artist::Instance());

	while (cdtrack->ReadNextRecord(0))
	{
		data.id = cdtrack->GetId();
		data.artist = cdtrack->GetArtist();
		data.Title = wxString(cdtrack->GetTitle().c_str(), wxConvUTF8);
        data.typeOfMusic = cdtrack->GetTypeOfMusic();
		artist->SetId(cdtrack->GetArtist());
		if (artist->ReadRecord(0))
			data.ArtistLastName = wxString(artist->GetLastName().c_str(), wxConvUTF8);
		else
			data.ArtistLastName = _("Unknown");
		tracks[data.ArtistLastName + data.Title] = data;
	}

	return &tracks;
}

std::vector<wxCDTrack> *DataFactory::GetCDTracks()
{
	wxCDTrack data;

	cdtracks.clear();

	unique_ptr<CDTrack> cdtrack(CDTrack::Instance());
	unique_ptr<Artist> artist(Artist::Instance());

	while (cdtrack->ReadNextRecord(0))
	{
		data.id = cdtrack->GetId();
		data.artist = cdtrack->GetArtist();
		data.Title = wxString(cdtrack->GetTitle().c_str(), wxConvUTF8);
        data.typeOfMusic = cdtrack->GetTypeOfMusic();
		artist->SetId(cdtrack->GetArtist());
		if (artist->ReadRecord(0))
			data.ArtistLastName = wxString(artist->GetLastName().c_str(), wxConvUTF8);
		else
			data.ArtistLastName = _("Unknown");
		cdtracks.push_back(data);
	}

	return &cdtracks;
}

bool DataFactory::AddTrackToCD(wxTrackOnCD *trOnCD)
{
	bool retval = false;

    unique_ptr<CDRecTrack> cdrectrack(CDRecTrack::Instance());

    cdrectrack->SetCDId(trOnCD->cdId);
    cdrectrack->SetTrackOnCD(trOnCD->trackOnCD);
    cdrectrack->SetTRId(trOnCD->trackId);
    cdrectrack->SetPath(std::string(trOnCD->Path.mb_str(wxConvUTF8)));

    retval = cdrectrack->WriteRecord();

	return retval;
}

bool DataFactory::UpdateTrackOnCD(wxTrackOnCD *oldValues, wxTrackOnCD *newValues)
{
	bool retval = false;

    unique_ptr<CDRecTrack> cdrectrack(CDRecTrack::Instance());

    cdrectrack->SetCDId(oldValues->cdId);
    cdrectrack->SetTrackOnCD(oldValues->trackOnCD);
    cdrectrack->SetTRId(oldValues->trackId);
    if (cdrectrack->ReadRecord(0))
    {
        cdrectrack->SetCDId(newValues->cdId);
        cdrectrack->SetTrackOnCD(newValues->trackOnCD);
        cdrectrack->SetTRId(newValues->trackId);
        cdrectrack->SetPath(std::string(newValues->Path.mb_str(wxConvUTF8)));

        retval = cdrectrack->UpdateRecord();
    }

	return retval;
}

bool DataFactory::GetTrackOnCD(wxTrackOnCD *data)
{
	bool retval = false;

    unique_ptr<CDRecTrack> cdrectrack(CDRecTrack::Instance());

    cdrectrack->SetCDId(data->cdId);
    cdrectrack->SetTrackOnCD(data->trackOnCD);
    cdrectrack->SetTRId(data->trackId);

    if (cdrectrack->ReadRecord(0))
    {
        data->Path = wxString(cdrectrack->GetPath().c_str(), wxConvUTF8);
		retval = true;
    }
	else
		retval = false;

	return retval;
}

bool DataFactory::DeleteTrackOnCD(const int CDid, const int NoOnCD, const int TRid)
{
	bool retval = false;

    unique_ptr<CDRecTrack> cdrectrack(CDRecTrack::Instance());

    cdrectrack->SetCDId(CDid);
    cdrectrack->SetTrackOnCD(NoOnCD);
    cdrectrack->SetTRId(TRid);

	if (cdrectrack->ReadRecord(0))
	{
		retval = cdrectrack->DeleteRecord();
	}

	return retval;
}

std::vector<wxArtist> *DataFactory::GetArtists()
{
	wxArtist data;

	artists.clear();

	unique_ptr<Artist> artist(Artist::Instance());

	while (artist->ReadNextRecord(0))
	{
		data.Id = artist->GetId();
		data.FirstName = wxString(artist->GetFirstName().c_str(), wxConvUTF8);
		data.LastName = wxString(artist->GetLastName().c_str(), wxConvUTF8);
		artists.push_back(data);
	}

	return &artists;
}

bool DataFactory::NewCDTrack(wxCDTrack *data)
{
	bool retval = false;

	unique_ptr<CDTrack> cdtrack(CDTrack::Instance());
	cdtrack->SetId(data->id);
	cdtrack->SetTitle(std::string(data->Title.mb_str(wxConvUTF8)));
	cdtrack->SetArtist(data->artist);
	cdtrack->SetTypeOfMusic(data->typeOfMusic);

	retval = cdtrack->WriteRecord();

	return retval;
}

bool DataFactory::UpdateCDTrack(wxCDTrack *data)
{
	bool retval = false;

	unique_ptr<CDTrack> cdtrack(CDTrack::Instance());
	cdtrack->SetId(data->id);

	if (cdtrack->ReadRecord(0))
	{
		cdtrack->SetTitle(std::string(data->Title.mb_str(wxConvUTF8)));
		cdtrack->SetArtist(data->artist);
		cdtrack->SetTypeOfMusic(data->typeOfMusic);

		retval = cdtrack->UpdateRecord();
	}

	return retval;
}

bool DataFactory::DeleteCDTrack(int TrackId)
{
	bool retval = false;
	unique_ptr<CDTrack> cdtrack(CDTrack::Instance());

	cdtrack->SetId(TrackId);

	unique_ptr<CDRecTrack> cdrectrack(CDRecTrack::Instance());

	while (cdrectrack->ReadNextRecord(0))
	{
		if (cdrectrack->GetTRId() == TrackId)
		{
			cdrectrack->DeleteRecord();
			cdrectrack->ResetFilePos();
		}
	}
	cdrectrack->FlushFile();

	retval = cdtrack->DeleteRecord();

	return retval;
}

bool DataFactory::NewArtist(wxArtist *data)
{
	bool retval = false;

	unique_ptr<Artist> artist(Artist::Instance());
	artist->SetId(data->Id);
	artist->SetFirstName(std::string(data->FirstName.mb_str(wxConvUTF8)));
	artist->SetLastName(std::string(data->LastName.mb_str(wxConvUTF8)));

	retval = artist->WriteRecord();

	return retval;
}

bool DataFactory::UpdateArtist(wxArtist *data)
{
	bool retval = false;

	unique_ptr<Artist> artist(Artist::Instance());
	artist->SetId(data->Id);

	if (artist->ReadRecord(0))
	{
		artist->SetFirstName(std::string(data->FirstName.mb_str(wxConvUTF8)));
		artist->SetLastName(std::string(data->LastName.mb_str(wxConvUTF8)));

		retval = artist->UpdateRecord();
	}

	return retval;
}

bool DataFactory::DeleteArtist(int ArtistId)
{
	bool retval;
	unique_ptr<Artist> artist(Artist::Instance());
	artist->SetId(ArtistId);
	retval = artist->DeleteRecord();
	return retval;
}

bool DataFactory::NewTypeOfMusic(wxTypeOfMusic *data)
{
	bool retval = false;
	unique_ptr<TypeOfMusic> tomus(TypeOfMusic::Instance());
	tomus->SetId(data->Id);
	tomus->SetTypeOfMusic(std::string(data->TypeOfMusic.mb_str(wxConvUTF8)));

	retval = tomus->WriteRecord();

	return retval;
}

bool DataFactory::UpdateTypeOfMusic(wxTypeOfMusic *data)
{
	bool retval = false;

	unique_ptr<TypeOfMusic> tomus(TypeOfMusic::Instance());
	tomus->SetId(data->Id);

	if (tomus->ReadRecord(0))
	{
		tomus->SetTypeOfMusic(std::string(data->TypeOfMusic.mb_str(wxConvUTF8)));
		retval = tomus->UpdateRecord();
	}

	return retval;
}

bool DataFactory::DeleteTypeOfMusic(int Id)
{
	bool retval = false;

	unique_ptr<TypeOfMusic> tomus(TypeOfMusic::Instance());
	tomus->SetId(Id);
	retval = tomus->DeleteRecord();

	return retval;
}
