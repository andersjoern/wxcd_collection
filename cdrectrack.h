#ifndef CDRECRTRACK_H
#define CDRECRTRACK_H

#include "btfile.h"
#include <string>

#define TITLE_LEN     50
#define PATH_LEN    200

using namespace std;

typedef struct
{
	int cdid;
	int trackOnCD;
	int tracid;
	char path[PATH_LEN];
}__attribute__ ((packed))CDRTRecord;


class CDRecTrack : public BTFile
{
	public:
		virtual ~CDRecTrack();

		void SetCDId(int id);
		int GetCDId();
		void SetTRId(int id);
		int GetTRId();
		void SetTrackOnCD(int id);
		int GetTrackOnCD();
		std::string GetPath();
		void SetPath(std::string p);

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
		void ResetFilePos();
        static CDRecTrack *Instance();

	protected:
		CDRTRecord record;
		CDRTRecord lastrec;
		DbFile dbFile;
	private:
	    static CDRecTrack *instance;
		CDRecTrack();

};

#endif // CDTRACK_H
