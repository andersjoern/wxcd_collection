
#ifndef _BTFILE
#define _BTFILE


#include <inttypes.h>
#include "btree.h"

class BTFile
{

	protected:
	    uint16_t BigEndian(uint16_t data);
	    uint32_t BigEndian(uint32_t data);
	    uint64_t BigEndian(uint64_t data);

	public:
		BTFile();
		virtual ~BTFile() { }
		virtual void OpenFile() = 0;
		virtual void CloseFile() = 0;
		virtual bool ReadRecord(int knr) = 0;
		virtual bool WriteRecord() = 0;
		virtual bool UpdateRecord() = 0;
		virtual bool DeleteRecord() = 0;
		virtual bool ReadNextRecord(int knr) = 0;
		virtual bool ReadPrevRecord(int knr) = 0;
		virtual void FlushFile() = 0;
};

#endif
