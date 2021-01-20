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

unordered_map<unsigned short, const char *> method{{8, "Deflate"},
                                                   {15, "Reserved"}};

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

  // public:
  unordered_map<const char *, uint32_t> compression_info();
  zlib() : compression_field(0), flags(0), compressed_data{}, adler_32(0) {}
  virtual zlib &compress(vector<byte> &data, unsigned char method = 8,
                         bool use_dictionary = false) = 0;
  virtual vector<byte> &decompress() = 0;
};

}; // namespace zlite

extern "C" {
#define Z_NO_FLUSH 0
#define Z_PARTIAL_FLUSH 1
#define Z_SYNC_FLUSH 2
#define Z_FULL_FLUSH 3
#define Z_FINISH 4
#define Z_BLOCK 5
#define Z_TREES 6
struct z_stream {
  const unsigned char *next_in; /* next input byte */
  unsigned avail_in;            /* number of bytes available at next_in */
  unsigned long total_in;       /* total number of input bytes read so far */
  unsigned char *next_out;      /* next output byte will go here */
  unsigned avail_out;           /* remaining free space at next_out */
  unsigned long total_out;      /* total number of bytes output so far */
  const char *msg;              /* last error message, NULL if no error */
  struct internal_state *state; /* not visible by applications */
  void *(*zalloc)(void *, unsigned,
                  unsigned);     /* used to allocate the internal state */
  void (*zfree)(void *, void *); /* used to free the internal state */
  void *opaque;   /* private data object passed to zalloc and zfree */
  int data_type;  /* best guess about the data type: binary or text
                for deflate, or the decoding state for inflate */
  uint32_t adler; /* Adler-32 or CRC-32 value of the uncompressed data */
  unsigned long reserved; /* reserved for future use */
};
int deflateInit(z_stream *strm, int level);
int deflate(z_stream *strm, int flush);
int deflateEnd(z_stream *strm);
int inflateInit(z_stream *strm);
int inflate(z_stream *strm, int flush);
int inflateEnd(z_stream *strm);
}
#endif
