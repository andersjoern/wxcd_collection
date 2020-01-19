#include "tomus.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

TypeOfMusic *TypeOfMusic::instance = NULL;

const char *TypeOfMusicFileName = "/Data/cd_collection/tofmfile";

TypeOfMusic::TypeOfMusic()
{
	OpenFile();
}

TypeOfMusic *TypeOfMusic::Instance()
{
    if (instance == NULL)
    {
       instance = new TypeOfMusic;
    }
    return instance;
}

TypeOfMusic::~TypeOfMusic()
{
	CloseFile();
	instance = NULL;
}

void TypeOfMusic::SetId(int id)
{
	record.id = htobe32(id);
}

int TypeOfMusic::GetId()
{
	return be32toh(record.id);
}

void TypeOfMusic::SetTypeOfMusic(string tofmu)
{
	memset(record.TOfMusic, 0, T_LEN);
	strncpy(record.TOfMusic, tofmu.c_str(), T_LEN);
}

string TypeOfMusic::GetTypeOfMusic()
{
	char temp[T_LEN + 1];
	memset(temp, 0, T_LEN + 1);
	strncpy(temp, record.TOfMusic, T_LEN);

	return string(temp);
}

void TypeOfMusic::ClearRecord()
{
	memset(&record, 0, sizeof(record));
}

void TypeOfMusic::OpenFile()
{
	const char *homedir;

	if ((homedir = getenv("HOME")) == NULL)
	{
		homedir = getpwuid(getuid())->pw_dir;
	}

	if (!OpenDb(&dbFile, string(string(homedir) + string(TypeOfMusicFileName) + string(".db")).c_str()))
	{
		CreateDb(&dbFile, string(string(homedir) + string(TypeOfMusicFileName) + string(".db")).c_str(), sizeof(record), 4, 0);
	}
}

void TypeOfMusic::CloseFile()
{
	CloseDb(&dbFile);
}

void TypeOfMusic::ResetFilePos()
{
	ResetPos(&dbFile);
}

void TypeOfMusic::FlushFile()
{
	DBFlush(&dbFile);
}

bool TypeOfMusic::ReadRecord(int knr)
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

bool TypeOfMusic::WriteRecord()
{
	bool retval = false;

	retval = InsertRecord(&dbFile, (const char *) &record);
	if (retval)
		DBFlush(&dbFile);

	return retval;
}

bool TypeOfMusic::UpdateRecord()
{
	bool retval = false;
	retval = ReplaceRecord(&dbFile, (char *)&record);
	if (retval)
		DBFlush(&dbFile);
  	return retval;
}

bool TypeOfMusic::DeleteRecord()
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

bool TypeOfMusic::ReadNextRecord(int knr)
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

bool TypeOfMusic::ReadPrevRecord(int knr)
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
