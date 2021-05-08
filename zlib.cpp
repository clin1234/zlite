#include <cstddef>
#include <type_traits>
#ifdef __STDC_HOSTED__
#include <cstdint>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#endif

using std::byte;
using std::conditional_t;
using std::uint32_t, std::uint8_t;
using std::unordered_map;
using std::vector;

#include "adler32.hpp"
#include "zlib.hpp"
#if __has_include("deflate.hpp")
#include "deflate.hpp"
#endif

// using zlite::compression_method;

namespace zlite {

struct Deflate_Compression : zlib {

  zlib &compress(vector<byte> &data, unsigned char method = 8,
                 bool use_dictionary = false) override {
    if (use_dictionary)
      flags |= 0b00'1'00000;
    if (method >= 0 || method < 15) {
      switch (method) {

      case 8:;
        deflate stream(data, compression_mode::With_dynamic_Huffman);
        break;
      default:
        break;
      }
    } else
      throw std::domain_error("Invalid compression method");
  }

  vector<byte> &decompress() override {
    if (adler_32 != adler32(compressed_data)) {
      throw std::runtime_error("Possible corruption on zlib stream\n\
                               Expected: " +
                               adler_32 + ", Got: " + adler32(compressed_data));
    }
  }
};

unordered_map<const char *, uint32_t> zlib::compression_info() {
  return unordered_map<const char *, uint32_t>{
      {"Compression method",
       static_cast<uint32_t>(method[compression_field & 0b1111])},
      {"Compression info", compression_field & 0xf0},
      {"Dictionary is preset", flags >> 5},
      {"Compression level", flags >> 6},
      {"Adler-32 of compressed data", adler_32}};
}
}; // namespace zlite

extern "C" {
int deflateInit(z_stream *strm, int lvl) {
  if (lvl < -1 || lvl > 9)
    return Z_STREAM_ERROR;
  else {
  };

  return Z_OK;
}

int deflate(z_stream *s, int flush) {
  s->next_out = nullptr;
  s->adler;
  switch (flush) {
    case Z_FULL_FLUSH:;
    case Z_NO_FLUSH:;
    case Z_PARTIAL_FLUSH:;
    case Z_SYNC_FLUSH:;
    case Z_FINISH:;
    case Z_BLOCK:;
    case Z_TREES:;
  }
}

int deflateEnd(z_stream* s)
{
    return Z_OK;
}

int inflateInit(z_stream* s)
{
    
}
int inflate(z_stream *s, int flush) {
  s->next_out = nullptr;
  s->adler;
  switch (flush) {
    case Z_FULL_FLUSH:;
    case Z_NO_FLUSH:;
    case Z_PARTIAL_FLUSH:;
    case Z_SYNC_FLUSH:;
    case Z_FINISH:;
    case Z_BLOCK:;
    case Z_TREES:;
  }
}
int inflateEnd(z_stream* s)
{
    return Z_OK;
}

int compress (unsigned char* d, unsigned long* dl, const unsigned char* s,
              unsigned long* sl)
{
    
}
}
