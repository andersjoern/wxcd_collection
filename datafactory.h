#ifndef DATAFACTORY_H
#define DATAFACTORY_H

#include <wx/app.h>
#include <vector>
#include <map>
#include <memory>
#include <mutex>
#include "btree.h"
#include "artist.h"
#include "cdrec.h"
#include "cdtrack.h"
#include "cdrectrack.h"
#include "tomus.h"

class wxCDRec
{
	public:
		int Id;
		wxString Title;
		int TypeOfMusicId;
		wxString TypeOfMusic;
};

class wxCDRecTrackRec
{
	public:
		int cdId;
		int trackOnCD;
		int trackId;
		wxString TrackTitle;
		wxString ArtistLastName;
};

class wxTrackOnCD
{
	public:
		int cdId;
		int trackOnCD;
		int trackId;
		wxString Path;
};


class wxCDTrack
{
	public:
		int id;
		wxString ArtistLastName;
		wxString Title;
		int artist;
		int typeOfMusic;
};

class wxTypeOfMusic
{
public:
	int Id;
	wxString TypeOfMusic;
};

class wxArtist
{
public:
	int Id;
	wxString FirstName;
	wxString LastName;
};

class DataFactory
{
	public:
		std::vector<wxCDRec> *GetCDRecords();
		std::vector<wxCDRecTrackRec> *GetRecTrackRecords(int id);
		std::vector<wxTypeOfMusic>  *GetTypeOfMusics();
		std::vector<wxCDTrack> *GetCDTracks();
		std::vector<wxArtist> *GetArtists();
		std::map<wxString, wxCDTrack> *GetSortedTracks();

		bool UpdateCDRecord(wxCDRec *rec);
		bool NewCDRecord(wxCDRec *rec);
		bool DeleteCDRec(int id);
		bool NewCDTrack(wxCDTrack *data);
		bool UpdateCDTrack(wxCDTrack *data);
		bool DeleteCDTrack(int TrackId);
		bool NewArtist(wxArtist *data);
		bool UpdateArtist(wxArtist *data);
		bool DeleteArtist(int ArtistId);
		bool NewTypeOfMusic(wxTypeOfMusic *data);
		bool UpdateTypeOfMusic(wxTypeOfMusic *data);
		bool DeleteTypeOfMusic(int Id);
		bool AddTrackToCD(wxTrackOnCD *trOnCD);
		bool UpdateTrackOnCD(wxTrackOnCD *oldValues, wxTrackOnCD *newValues);
		bool DeleteTrackOnCD(const int CDid, const int NoOnCD, const int TRid);
		bool GetTrackOnCD(wxTrackOnCD *data);

		static DataFactory *Instance();
		static void DestroyInstance();
	protected:

		mutable std::mutex m;

        std::vector<wxCDRec> cdrecords;
        std::vector<wxCDRecTrackRec> cdrectrackrecords;
        std::vector<wxTypeOfMusic> typeofmusics;
        std::map<wxString, wxCDTrack> tracks;
        std::vector<wxCDTrack> cdtracks;
        std::vector<wxArtist> artists;
	private:
		DataFactory();

		static DataFactory *instance;
};

#endif // DATAFACTORY_H
