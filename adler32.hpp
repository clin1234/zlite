#ifndef __include_adler
#define __include_adler

#include <cstddef>

using std::byte;

#ifdef __STDC_HOSTED__
#include <array>
#include <cstdint>
#include <vector>

using std::array;
#else
#endif

namespace zlite {
template <size_t len>
uint32_t adler32(
#ifdef __STDC_HOSTED__
    std::vector<byte> &data
#else
    byte (&data)[len]
#endif
);
}; // namespace zlite

extern "C" {
uint32_t adler32(unsigned long adler, const unsigned char *data,
                 unsigned int len);
uint32_t adler32_z(unsigned long adler, const unsigned char data[], size_t len);
uint32_t adler32_combine(unsigned long adler1, unsigned long adler2,
                         unsigned long long len);
}

#endif
