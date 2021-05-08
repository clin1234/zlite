#ifndef __include_crc32
#define __include_crc32

template <size_t len> 
uint32_t crc32(const byte (&data)[len]);

uint32_t combine_crc32(uint32_t crc1, uint32_t crc2, unsigned long long len);

#endif
