#ifndef CDREC_H
#define CDREC_H

#include "btfile.h"
#include <string>

using namespace std;

#define TITLE_LEN     50

typedef struct
{
	int id;
	char title[TITLE_LEN];
	int typeOfMusic;
}__attribute__ ((packed))CDRecord;

class CDrec : public BTFile
{
	public:
		virtual ~CDrec();

		void SetId(int id);
		int GetId();
		void SetTitle(string title);
		string GetTitle();
		void SetTypeOfMusic(int tOfMu);
		int GetTypeOfMusic();

		void ClearRecord();

		void ResetFilePos();
		void FlushFile();
		bool ReadRecord(int knr);
		bool WriteRecord();
		bool UpdateRecord();
		bool DeleteRecord();
		bool ReadNextRecord(int knr);
		bool ReadPrevRecord(int knr);
		static CDrec *Instance();

	protected:
		CDRecord record;
		CDRecord lastrec;
		DbFile dbFile;
		void OpenFile();
		void CloseFile();

	private:
	    static CDrec *instance;
   		CDrec();

};

#endif // CDREC_H
