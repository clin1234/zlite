// Plain (and also slow) implementation of the Adler-32 checksum.
#include <cstddef> // One stupid extra header just for size_t...
#include <cstdint>
#ifdef __STDC_HOSTED__
#include <algorithm>
#include <array>
#include <vector>

using std::array;
using std::begin, std::end, std::move;
#endif

using std::size_t, std::uint32_t, std::byte, std::to_integer;

static const uint16_t modulus = 65521;

namespace zlite {
template <size_t len>
uint32_t adler32(const
#ifdef __STDC_HOSTED__
                 std::vector<byte> &data
#else
                 byte (&data)[len]
#endif
) {
  uint32_t a = 1, b = 0;

  // Process each byte of the data in order
  for (const auto &byte : data) {
    a = (a + to_integer(byte)) % modulus;
    b = (b + a) % modulus;
  }

  return (b << 16) | a;
}
uint32_t combine_adler32(uint32_t adler1, uint32_t adler2,
                         unsigned long long len) {
  // In zlib, if len < 0, the function returns 0xffff ffff.
  if (len < 0)
    return 0;

  unsigned rem = (len %= modulus);
  uint32_t sum1 = adler1 & 0xffff;
  uint32_t sum2 = rem * sum1;
  sum2 %= modulus;
  sum1 += (adler2 & 0xffff) + modulus - 1;
  sum2 += ((adler1 >> 16) & 0xffff) + ((adler2 >> 16) & 0xffff) + modulus - rem;
  if (sum1 >= modulus)
    sum1 -= modulus;
  if (sum2 >= ((unsigned long)modulus << 1))
    sum2 -= ((unsigned long)modulus << 1);
  if (sum2 >= modulus)
    sum2 -= modulus;
  return sum1 | (sum2 << 16);
}
extern "C" {
/* TODO: is it static or reinterpret cast to convert between unsigned char
and std::byte arrays? */
uint32_t adler32(unsigned long adler, const unsigned char *data,
                 unsigned int len) {
#ifdef __STDC_HOSTED__
  const std::vector<byte, len> style;
  std::copy(std::begin(data), std::end(data), style.begin());
#else
  reinterpret_cast<const byte *>(data);
#endif
}
uint32_t adler32_z(unsigned long adler, const unsigned char data[],
                   size_t len) {
#ifdef __STDC_HOSTED__
#else
  zlite::adler32(reinterpret_cast<const byte *>(data));
#endif
}
uint32_t adler32_combine(unsigned long adler1, unsigned long adler2,
                         unsigned long long len) {
  zlite::combine_adler32(adler1, adler2, len);
}
}
} // namespace zlite
