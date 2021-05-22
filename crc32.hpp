#ifndef __include_crc32
#define __include_crc32

#include "conf.h"

namespace zlite {
template <size_t len> 
uint32_t crc32(const byte (&data)[len]);

uint32_t combine_crc32(uint32_t crc1, uint32_t crc2, off_t len);
}

#endif
