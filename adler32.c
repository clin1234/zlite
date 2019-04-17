// Plain (and also slow) implementation of the Adler-32 checksum.
#include <stdint.h>
#include <stddef.h> // One stupid extra header just for size_t...

const uint16_t modulus = 65521;

uint32_t adler32(unsigned char* data, size_t len)
{
    uint32_t a = 1, b = 0;

    // Process each byte of the data in order
    for (size_t index = 0; index < len; ++index)
    {
        a = (a + data[index]) % modulus;
        b = (b + a) % modulus;
    }

    return (b << 16) | a;
}
