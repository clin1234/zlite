// Plain (and also slow) implementation of the Adler-32 checksum.
#include <stdint.h>
#include <stddef.h> // One stupid extra header just for size_t...

const uint16_t modulus = 65521;

uint32_t adler32(unsigned char *data, size_t len)
/*
    where data is the location of the data in physical memory and
    len is the length of the data in bytes
*/
{
    uint32_t a = 1, b = 0;
    size_t index;

    // Process each byte of the data in order
    for (index = 0; index < len; ++index)
    {
        a = (a + data[index]) % modulus;
        b = (b + a) % modulus;
    }

    return (b << 16) | a;
}
