#ifndef __include_zlib
#define __include_zlib

#include <cstddef>
#ifdef __STDC_HOSTED__
#include <type_traits>
#include <unordered_map>
#include <vector>

using std::conditional_t;
using std::unordered_map, std::vector;
#else
#endif

using std::byte;

namespace zlite {

unordered_map<unsigned short, const char *>
method{{8, "Deflate"}, {15, "Reserved"}};

// TODO: encapsulate
struct zlib {
  uint8_t compression_field;
  uint8_t flags;
  /* Not really idiomatic C++, but this will only insert this member in the
  class if the bit for a preset dictionary is set. If not, the compressed
  data will succeed the flags. */
  [[no_unique_address]] conditional_t<flags &(1 << 5), uint32_t,
                                      decltype([] {})>
      dict_adler_32;
  vector<byte> compressed_data;
  uint32_t adler_32;

//public:
  unordered_map<const char *, uint32_t> compression_info();
  zlib() : compression_field(0), flags(0), compressed_data{}, adler_32(0) {}
  virtual zlib &compress(vector<byte> &data, unsigned char method = 8,
                         bool use_dictionary = false) = 0;
  virtual vector<byte> &decompress() = 0;
};

}; // namespace zlite
#endif
