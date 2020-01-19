#include "cdrec.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

CDrec *CDrec::instance = NULL;

const char *CDrecFileName = "/Data/cd_collection/cdrecfile";

CDrec::CDrec()
{
	OpenFile();
}

CDrec *CDrec::Instance()
{
    if (instance == NULL)
    {
        instance = new CDrec;
    }
    return instance;
}

CDrec::~CDrec()
{
	CloseFile();
	instance = NULL;
}

void CDrec::SetId(int id)
{
	record.id = htobe32(id);
}

int CDrec::GetId()
{
	return be32toh(record.id);
}

void CDrec::SetTitle(string title)
{
	memset(record.title, 0, TITLE_LEN);
	strncpy(record.title, title.c_str(), TITLE_LEN);
}

string CDrec::GetTitle()
{
	char temp[TITLE_LEN + 1];
	memset(temp, 0, TITLE_LEN + 1);
	strncpy(temp, record.title, TITLE_LEN);

	return string(temp);
}

void CDrec::SetTypeOfMusic(int tOfMu)
{
	record.typeOfMusic = tOfMu;
}

int CDrec::GetTypeOfMusic()
{
	return record.typeOfMusic;
}

void CDrec::ClearRecord()
{
	memset(&record, 0, sizeof(record));
}


void CDrec::OpenFile()
{
	const char *homedir;

	if ((homedir = getenv("HOME")) == NULL)
	{
		homedir = getpwuid(getuid())->pw_dir;
	}

	if (!OpenDb(&dbFile, string(string(homedir) + string(CDrecFileName) + string(".db")).c_str()))
	{
		CreateDb(&dbFile, string(string(homedir) + string(CDrecFileName) + string(".db")).c_str(), sizeof(record), 4, 0);
	}
}

void CDrec::CloseFile()
{
	CloseDb(&dbFile);
}

void CDrec::ResetFilePos()
{
	ResetPos(&dbFile);
}

void CDrec::FlushFile()
{
	DBFlush(&dbFile);
}

bool CDrec::ReadRecord(int knr)
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

bool CDrec::WriteRecord()
{
	bool retval = false;

	retval = InsertRecord(&dbFile, (const char *) &record);
	if (retval)
		DBFlush(&dbFile);

	return retval;
}

bool CDrec::UpdateRecord()
{
	bool retval = false;
	retval = ReplaceRecord(&dbFile, (char *)&record);
	if (retval)
		DBFlush(&dbFile);
  	return retval;
}

bool CDrec::DeleteRecord()
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

bool CDrec::ReadNextRecord(int knr)
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

bool CDrec::ReadPrevRecord(int knr)
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
