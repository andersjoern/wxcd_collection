
#include "btfile.h"
#include <endian.h>


/*

uint32_t htobe32(uint32_t host_32bits);           // host to big-endian encoding
uint32_t htole32(uint32_t host_32bits);           // host to lil-endian encoding
uint32_t be32toh(uint32_t big_endian_32bits);     // big-endian to host encoding
uint32_t le32toh(uint32_t little_endian_32bits);  // lil-endian to host encoding

*/

BTFile::BTFile()
{

}

uint16_t BTFile::BigEndian(uint16_t data)
{
	uint16_t result;

	result = htobe16(data);
	return result;
}

uint32_t  BTFile::BigEndian(uint32_t data)
{
	uint32_t result;

	result = htobe32(data);
	return result;
}

uint64_t BTFile::BigEndian(uint64_t data)
{
	uint64_t result;

	result = htobe64(data);
	return result;
}


