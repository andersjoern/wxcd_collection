#include "cdtrack.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

CDTrack *CDTrack::instance = NULL;

const char *CDTFileName = "/Data/cd_collection/cdtrackfile";


CDTrack::CDTrack()
{
	OpenFile();
}

CDTrack *CDTrack::Instance()
{
    if (instance == NULL)
    {
       instance = new CDTrack;
    }
    return instance;
}

CDTrack::~CDTrack()
{
	CloseFile();
	instance = NULL;
}

void CDTrack::SetId(int id)
{
	record.id = htobe32(id);
}

int CDTrack::GetId()
{
	return be32toh(record.id);
}

void CDTrack::SetTitle(string title)
{
	memset(record.title, 0, TITLE_LEN);
	strncpy(record.title, title.c_str(), TITLE_LEN);
}

string CDTrack::GetTitle()
{
	char temp[TITLE_LEN + 1];
	memset(temp, 0, TITLE_LEN + 1);
	strncpy(temp, record.title, TITLE_LEN);

	return string(temp);
}

void CDTrack::SetTypeOfMusic(int tOfMu)
{
	record.typeOfMusic = tOfMu;
}

int CDTrack::GetTypeOfMusic()
{
	return record.typeOfMusic;
}

void CDTrack::SetArtist(int art)
{
	record.artist = art;
}

int CDTrack::GetArtist()
{
	return record.artist;
}

void CDTrack::ClearRecord()
{
	memset(&record, 0, sizeof(record));
}

void CDTrack::OpenFile()
{
	const char *homedir;
	bool exists = true;

	if ((homedir = getenv("HOME")) == NULL)
	{
		homedir = getpwuid(getuid())->pw_dir;
	}

	if (!OpenDb(&dbFile, string(string(homedir) + string(CDTFileName) + string(".db")).c_str()))
	{
		CreateDb(&dbFile, string(string(homedir) + string(CDTFileName) + string(".db")).c_str(), sizeof(record), 4, 0);
		exists = false;
	}

	if (!OpenDb(&dbFile1, string(string(homedir) + string(CDTFileName) + string(".db.1")).c_str()))
	{
		CreateDb(&dbFile1, string(string(homedir) + string(CDTFileName) + string(".db.1")).c_str(), sizeof(record1), sizeof(record1), 0);
		if (exists)
		{
			ResetFilePos(0);
			while (ReadNextRecord(0))
			{
				record1.id = record.id;
				record1.artist = htobe32(record.artist);
				InsertRecord(&dbFile1, (const char *) &record1);
			}
			DBFlush(&dbFile1);
		}
	}
}

void CDTrack::CloseFile()
{
	CloseDb(&dbFile);
	CloseDb(&dbFile1);
}

void CDTrack::ResetFilePos(int knr)
{
	if (knr == 0)
		ResetPos(&dbFile);
	if (knr == 1)
		ResetPos(&dbFile1);
}

void CDTrack::FlushFile()
{
	DBFlush(&dbFile);
	DBFlush(&dbFile1);
}

bool CDTrack::ReadRecord(int knr)
{
	bool retval = false;
	switch (knr)
	{
		case 0:
			retval = GetRecord(&dbFile, (char *)&record);
			break;
		case 1:
			record1.id = record.id;
			record1.artist = htobe32(record.artist);
			retval = GetRecord(&dbFile1, (char *)&record1);
			if (retval)
			{
				lastrec1 = record1;
				record.id = record1.id;
				retval = GetRecord(&dbFile, (char *)&record);
			}
			break;
	}

	if (retval)
		lastrec = record;

	return retval;
}

bool CDTrack::WriteRecord()
{
	bool retval = false;

	retval = InsertRecord(&dbFile, (const char *) &record);
	if (retval)
	{
		record1.id = record.id;
		record1.artist = htobe32(record.artist);
		InsertRecord(&dbFile1, (const char *) &record1);
		DBFlush(&dbFile);
		DBFlush(&dbFile1);
	}

	return retval;
}

bool CDTrack::UpdateRecord()
{
	bool retval = false;
	retval = ReplaceRecord(&dbFile, (char *)&record);
	if (retval)
	{
		DBFlush(&dbFile);
		if (record.artist != lastrec.artist)
		{
			record1.id = record.id;
			record1.artist = htobe32(lastrec.artist);
			RemoveRecord(&dbFile1, (char *)&record1);
			record1.id = record.id;
			record1.artist = htobe32(record.artist);
			InsertRecord(&dbFile1, (const char *) &record1);
			DBFlush(&dbFile1);
		}
	}
  	return retval;
}

bool CDTrack::DeleteRecord()
{
	bool retval = false;

	if (GetRecord(&dbFile, (char *)&record))
	{
		lastrec = record;
		retval = RemoveRecord(&dbFile, (char *)&record);
		if (retval)
		{
			record1.id = lastrec.id;
			record1.artist = htobe32(lastrec.artist);
			RemoveRecord(&dbFile1, (char *)&record1);
			DBFlush(&dbFile);
			DBFlush(&dbFile1);
		}
  	}
  	return retval;
}

bool CDTrack::ReadNextRecord(int knr)
{
	bool retval = false;
	switch (knr)
	{
		case 0:
			retval = NextRecord(&dbFile, (char *)&record);
			break;
		case 1:
			retval = NextRecord(&dbFile1, (char *)&record1);
			if (retval)
			{
				lastrec1 = record1;
				record.id = record1.id;
				retval = GetRecord(&dbFile, (char *)&record);
			}
			break;
  	}
  	if (retval)
  		lastrec = record;
  	return retval;
}

bool CDTrack::ReadPrevRecord(int knr)
{
	bool retval = false;
	switch (knr)
	{
		case 0:
			retval = PrevRecord(&dbFile, (char *)&record);
			break;
		case 1:
			retval = PrevRecord(&dbFile1, (char *)&record1);
			if (retval)
			{
				lastrec1 = record1;
				record.id = record1.id;
				retval = GetRecord(&dbFile, (char *)&record);
			}
			break;
  	}
  	if (retval)
  		lastrec = record;
  	return retval;
}
