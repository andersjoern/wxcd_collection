#ifndef TOMUS_H
#define TOMUS_H

#include "btfile.h"
#include <string>

using namespace std;

#define T_LEN     30

typedef struct
{
	int id;
	char TOfMusic[T_LEN];
}__attribute__ ((packed))TypeOfMusicRecord;

class TypeOfMusic : public BTFile
{
	public:
		virtual ~TypeOfMusic();

		void SetId(int id);
		int GetId();
		void SetTypeOfMusic(string tofm);
		string GetTypeOfMusic();

		void ClearRecord();

		void ResetFilePos();
		void FlushFile();
		bool ReadRecord(int knr);
		bool WriteRecord();
		bool UpdateRecord();
		bool DeleteRecord();
		bool ReadNextRecord(int knr);
		bool ReadPrevRecord(int knr);

		static TypeOfMusic *Instance();

	protected:
		TypeOfMusicRecord record;
		TypeOfMusicRecord lastrec;
		DbFile dbFile;
		void OpenFile();
		void CloseFile();

	private:
	    static TypeOfMusic *instance;
		TypeOfMusic();

};

#endif // TOMUS_H
