#include <cstddef>
#include <cstdlib>
#include <type_traits>
#ifdef __STDC_HOSTED__
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
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
      flaggers |= 0b00'1'0000;
    if (method >= 0 || method < 15) {
      switch (method) {

      case 8:;
        deflate stream(data, compression_mode::With_dynamic_Huffman);
        break;
      case 15:
        break;
      default:
        throw std::domain_error("Unimplemented method");
        break;
      }
    } else
      throw std::domain_error("Invalid compression method");
  }

  vector<byte> &decompress() override {
    if ((l * 256 + flaggers) % 31 != 0) {
      std::cerr << "Check bits failed: got " << (flaggers & 0b1111) << '\n';
      std::exit(EXIT_FAILURE);
    }
    bool preset{false};
    vector<unsigned char> dictionary;

    if ((flaggers >> 5) & 1) {
      preset = true;
      dictionary = p;
    }
    deflate comp{};
    if (adler_32 != adler32(compressed_data)) {
      std::cerr << "Possible corruption on zlib stream\nExpected: " << adler_32
                << ", Got: " << adler32(compressed_data) << '\n';
      std::exit(EXIT_FAILURE);
    }

    unsigned short lz77_window_size, decomp_lvl;
    switch (auto method{l & 0b1111}; method) {
    case 8:
      if (auto window{(l >> 4) & 0b1111}; window > 7) {
        std::cerr << "For Deflate method, got " << window
                  << "; highest allowed is 7\n";
        std::exit(EXIT_FAILURE);
      } else {
        lz77_window_size = 2 << (window + 8);
        decomp_lvl = (flaggers >> 6) & 0b11;
      }
    case 15:
      std::cerr << "Reserved method.\n";
      std::exit(EXIT_FAILURE);
    }
  }
};

auto zlib::compression_info() {
  using std::to_string, std::string;
  return unordered_map<const char *, const char *>{
      {"Compression method", method[l >> 4]},
      {"Compression info", to_string(l & 0xf0).c_str()},
      {"Dictionary is preset", flaggers >> 5 ? "yes" : "no"},
      {"Compression level", to_string(flaggers >> 6).c_str()},
      {"Adler-32 of compressed data", to_string(adler_32).c_str()}};
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

int deflateEnd(z_stream *s) { return Z_OK; }

int inflateInit(z_stream *s) {}
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
int inflateEnd(z_stream *s) { return Z_OK; }

int compress(unsigned char *d, unsigned long *dl, const unsigned char *s,
             unsigned long *sl) {}
}
