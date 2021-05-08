// Plain (and also slow) implementation of the Adler-32 checksum.
#include <cstddef> // One stupid extra header just for size_t...
#include <cstdint>
#include <initializer_list>
#ifdef __STDC_HOSTED__
#include <algorithm>
#include <array>
#include <vector>
#ifdef __cpp_lib_span
#include <span>

using std::span;
#endif

using std::array, std::vector;
#endif

#include "adler32.hpp"

using std::initializer_list;
using std::size_t, std::uint32_t;

static constexpr uint16_t modulus = 65521;

namespace zlite {
#ifdef __STDC_HOSTED__
template <size_t len>
uint32_t adler32(const array<unsigned char, len> &data) {
    return zlite::adler32(data.data());
}

uint32_t adler32(const vector<unsigned char> &data) {
    uint32_t a = 1, b = 0;
  if (data.empty())
    return 1;

  // Process each byte of the data in order
  for (const auto &byte : data) {
    a = (a + byte) % modulus;
    b = (b + a) % modulus;
  }

  return (b << 16) | a;
}

#ifdef __cpp_lib_span
uint32_t adler32(const span<const unsigned char> &data) {
  uint32_t a = 1, b = 0;
  if (data.empty())
    return 1;

  // Process each byte of the data in order
  for (const auto &byte : data) {
    a = (a + byte) % modulus;
    b = (b + a) % modulus;
  }

  return (b << 16) | a;
}
#endif
#endif
template <size_t len>
uint32_t adler32(const unsigned char (&data)[len]) {
  if (len == 0)
    return 1;
  uint32_t a = 1, b = 0;
  for (decltype(len) i = 0; i < len; i++) {
    a = (a + data[i]) % modulus;
    b = (b + a) % modulus;
  }

  return (b << 16) | a;
}
uint32_t adler32(initializer_list<unsigned char>& data) {
  if (data.size() == 0)
    return 1;
  uint32_t a = 1, b = 0;
  for (const auto &i : data) {
    a = (a + i) % modulus;
    b = (b + a) % modulus;
  }

  return (b << 16) | a;
}

uint32_t combine_adler32(uint32_t adler1, uint32_t adler2,
                                   long long len) {
  // In zlib, if len < 0, the function returns 0xffff ffff.
  constexpr auto invalid_adler{0xffffffff};
  if (len < 0)
    return invalid_adler;

  unsigned rem = (len %= modulus);
  uint32_t sum1 = adler1 & 0xffff;
  uint32_t sum2 = rem * sum1;
  sum2 %= modulus;
  sum1 += (adler2 & 0xffff) + modulus - 1;
  sum2 += ((adler1 >> 16) & 0xffff) + ((adler2 >> 16) & 0xffff) + modulus - rem;
  if (sum1 >= modulus)
    sum1 -= modulus;
  if (sum2 >= modulus << 1)
    sum2 -= (modulus << 1);
  if (sum2 >= modulus)
    sum2 -= modulus;
  return sum1 | (sum2 << 16);
}
} // namespace zlite
extern "C" {
uint32_t adler32_z(unsigned long adler, const unsigned char *data, size_t len) {
  (void)adler;
  return zlite::adler32({data[len]});
}
uint32_t adler32(unsigned long adler, const unsigned char *data,
                 unsigned int len) {
  return adler32_z(adler, data, len);
}
uint32_t adler32_combine(unsigned long adler1, unsigned long adler2,
                         unsigned long long len) {
  return zlite::combine_adler32(adler1, adler2, len);
}
}
