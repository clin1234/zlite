// Generates CRC-32 based on a polynomial from ITU V.42

uint32_t crc32(unsigned char* data)
{
  uint32_t crc32 = 0xffffffff;

  for (size_t i=0; data[i]; ++i)
  nLookupIndex ← (crc32 xor byte) and 0xFF;
   crc32 ← (crc32 shr 8) xor CRCTable[nLookupIndex] //CRCTable is an array of 256 32-bit constants

//Finalize the CRC-32 value by inverting all the bits
  crc32 =^ 0xffffffff;
  return crc32;
}
