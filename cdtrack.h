#ifndef CDTRACK_H
#define CDTRACK_H

#include "btfile.h"
#include <string>

#define TITLE_LEN  50

using namespace std;

typedef struct
{
	int id;
	char title[TITLE_LEN];
	int artist;
	int typeOfMusic;
}__attribute__ ((packed))CDTRecord;

typedef struct
{
	int artist;
	int id;
}__attribute__ ((packed))CDTRecord1;

class CDTrack : public BTFile
{
	public:
		virtual ~CDTrack();

		void SetId(int id);
		int GetId();
		void SetTitle(string title);
		string GetTitle();
		void SetTypeOfMusic(int tOfMu);
		int GetTypeOfMusic();
		void SetArtist(int art);
		int GetArtist();

		void ClearRecord();

		virtual void OpenFile();
		virtual void CloseFile();
		virtual bool ReadRecord(int knr);
		virtual bool WriteRecord();
		virtual bool UpdateRecord();
		virtual bool DeleteRecord();
		virtual bool ReadNextRecord(int knr);
		virtual bool ReadPrevRecord(int knr);
		virtual void FlushFile();
		void ResetFilePos(int knr);
        static CDTrack *Instance();

	protected:
		CDTRecord record;
		CDTRecord lastrec;
		DbFile dbFile;

		CDTRecord1 record1;
		CDTRecord1 lastrec1;
		DbFile dbFile1;
	private:
	    static CDTrack *instance;
   		CDTrack();

};

#endif // CDTRACK_H
