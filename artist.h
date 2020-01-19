#ifndef ARTIST_H
#define ARTIST_H

#include "btfile.h"
#include <string>

using namespace std;

#define NAME_LEN 50

typedef struct
{
	int id;
	char FirstName[NAME_LEN];
	char LastName[NAME_LEN];
}__attribute__ ((packed))ArtistRecord;


class Artist : public BTFile
{
	public:
		virtual ~Artist();

		void SetId(int id);
		int GetId();
		void SetFirstName(string title);
		string GetFirstName();
		void SetLastName(string title);
		string GetLastName();

		void ClearRecord();

		void ResetFilePos();
		void FlushFile();
		bool ReadRecord(int knr);
		bool WriteRecord();
		bool UpdateRecord();
		bool DeleteRecord();
		bool ReadNextRecord(int knr);
		bool ReadPrevRecord(int knr);
        static Artist *Instance();
	protected:
		ArtistRecord record;
		ArtistRecord lastrec;
		DbFile dbFile;
		void OpenFile();
		void CloseFile();

	private:
	    static Artist *instance;
   		Artist();

};

#endif // ARTIST_H
