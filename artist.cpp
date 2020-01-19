#include "artist.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

const char *ArtistFileName = "/Data/cd_collection/artistfile";

Artist *Artist::instance = NULL;


Artist::Artist()
{
	OpenFile();
}

Artist::~Artist()
{
	CloseFile();
	instance = NULL;
}

Artist *Artist::Instance()
{
    if (instance == NULL)
    {
        instance = new Artist;
    }
    return instance;
}

void Artist::SetId(int id)
{
	record.id = htobe32(id);
}

int Artist::GetId()
{
	return be32toh(record.id);
}

void Artist::SetFirstName(string fname)
{
	memset(record.FirstName, 0, NAME_LEN);
	strncpy(record.FirstName, fname.c_str(), NAME_LEN);
}

string Artist::GetFirstName()
{
	char temp[NAME_LEN + 1];
	memset(temp, 0, NAME_LEN + 1);
	strncpy(temp, record.FirstName, NAME_LEN);

	return string(temp);
}

void Artist::SetLastName(string lname)
{
	memset(record.LastName, 0, NAME_LEN);
	strncpy(record.LastName, lname.c_str(), NAME_LEN);
}

string Artist::GetLastName()
{
	char temp[NAME_LEN + 1];
	memset(temp, 0, NAME_LEN + 1);
	strncpy(temp, record.LastName, NAME_LEN);

	return string(temp);
}

void Artist::ClearRecord()
{
	memset(&record, 0, sizeof(record));
}

void Artist::OpenFile()
{
	const char *homedir;

	if ((homedir = getenv("HOME")) == NULL)
	{
		homedir = getpwuid(getuid())->pw_dir;
	}

	if (!OpenDb(&dbFile, string(string(homedir) + string(ArtistFileName) + string(".db")).c_str()))
	{
		CreateDb(&dbFile, string(string(homedir) + string(ArtistFileName) + string(".db")).c_str(), sizeof(record), 4, 0);
	}
}

void Artist::CloseFile()
{
	CloseDb(&dbFile);
}

void Artist::ResetFilePos()
{
	ResetPos(&dbFile);
}

void Artist::FlushFile()
{
	DBFlush(&dbFile);
}

bool Artist::ReadRecord(int knr)
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

bool Artist::WriteRecord()
{
	bool retval = false;

	retval = InsertRecord(&dbFile, (const char *) &record);
	if (retval)
		DBFlush(&dbFile);

	return retval;
}

bool Artist::UpdateRecord()
{
	bool retval = false;
	retval = ReplaceRecord(&dbFile, (char *)&record);
	if (retval)
		DBFlush(&dbFile);
  	return retval;
}

bool Artist::DeleteRecord()
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

bool Artist::ReadNextRecord(int knr)
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

bool Artist::ReadPrevRecord(int knr)
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
