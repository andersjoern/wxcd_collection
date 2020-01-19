#include "cdrectrack.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

CDRecTrack *CDRecTrack::instance = NULL;

const char *CDRTFileName = "/Data/cd_collection/cdrectrackfile";

CDRecTrack::CDRecTrack()
{
	OpenFile();
}

CDRecTrack *CDRecTrack::Instance()
{
    if (instance == NULL)
    {
        instance = new CDRecTrack;
    }
    return instance;
}

CDRecTrack::~CDRecTrack()
{
	CloseFile();
	instance = NULL;
}

void CDRecTrack::SetCDId(int id)
{
	record.cdid = htobe32(id);
}

int CDRecTrack::GetCDId()
{
	return be32toh(record.cdid);
}

void CDRecTrack::SetTRId(int id)
{
	record.tracid = htobe32(id);
}

int CDRecTrack::GetTRId()
{
	return be32toh(record.tracid);
}

void CDRecTrack::SetTrackOnCD(int id)
{
	record.trackOnCD = htobe32(id);
}

int CDRecTrack::GetTrackOnCD()
{
	return be32toh(record.trackOnCD);
}

std::string CDRecTrack::GetPath()
{
    char c[PATH_LEN + 1];
    memset(c, 0, PATH_LEN + 1);
    strncpy(c, record.path, PATH_LEN);
    return std::string(c);
}

void CDRecTrack::SetPath(std::string p)
{
    memset(record.path, 0, PATH_LEN);
    strncpy(record.path, p.c_str(), PATH_LEN);
}

void CDRecTrack::ClearRecord()
{
	memset(&record, 0, sizeof(record));
}

void CDRecTrack::OpenFile()
{
	const char *homedir;

	if ((homedir = getenv("HOME")) == NULL)
	{
		homedir = getpwuid(getuid())->pw_dir;
	}

	if (!OpenDb(&dbFile, string(string(homedir) + string(CDRTFileName) + string(".db")).c_str()))
	{
		CreateDb(&dbFile, string(string(homedir) + string(CDRTFileName) + string(".db")).c_str(), sizeof(record), sizeof(int) * 3, 0);
	}
}

void CDRecTrack::CloseFile()
{
	CloseDb(&dbFile);
}

void CDRecTrack::ResetFilePos()
{
	ResetPos(&dbFile);
}

void CDRecTrack::FlushFile()
{
	DBFlush(&dbFile);
}

bool CDRecTrack::ReadRecord(int knr)
{
	bool retval = false;
	switch (knr)
	{
		case 0:
			retval = GetRecord(&dbFile, (char *)&record);
			break;
	}

	if (retval)
		lastrec = record;

	return retval;
}

bool CDRecTrack::WriteRecord()
{
	bool retval = false;

	retval = InsertRecord(&dbFile, (const char *) &record);
	if (retval)
		DBFlush(&dbFile);

	return retval;
}

bool CDRecTrack::UpdateRecord()
{
	bool retval = false;
	CDRTRecord tmpRec;
	tmpRec = record;
	record = lastrec;
	retval = DeleteRecord();
	if (retval)
	{
		record = tmpRec;
		retval = WriteRecord();
		if (!retval)
		{
			record = lastrec;
			WriteRecord();
		}
	}
  	return retval;
}

bool CDRecTrack::DeleteRecord()
{
	bool retval = false;

	if (GetRecord(&dbFile, (char *)&record))
	{
		retval = RemoveRecord(&dbFile, (char *)&record);
		if (retval)
			DBFlush(&dbFile);
  	}
  	return retval;
}

bool CDRecTrack::ReadNextRecord(int knr)
{
	bool retval = false;
	switch (knr)
	{
		case 0:
			retval = NextRecord(&dbFile, (char *)&record);
			break;
  	}
  	if (retval)
  		lastrec = record;
  	return retval;
}

bool CDRecTrack::ReadPrevRecord(int knr)
{
	bool retval = false;
	switch (knr)
	{
		case 0:
			retval = PrevRecord(&dbFile, (char *)&record);
			break;
  	}
  	if (retval)
  		lastrec = record;
  	return retval;
}
