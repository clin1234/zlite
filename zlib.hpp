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
  vector<unsigned char> compressed_data;
  uint32_t adler_32;

  // public:
  unordered_map<const char *, uint32_t> compression_info();
  zlib() : compression_field(0), flags(0), compressed_data{}, adler_32(0) {}
  virtual zlib &compress(vector<unsigned char> &data,
            unsigned char method = 8, bool use_dictionary = false) = 0;
  virtual vector<unsigned char> &decompress() = 0;
};

}; // namespace zlite

extern "C" {
enum {
  Z_NO_FLUSH,
  Z_PARTIAL_FLUSH,
  Z_SYNC_FLUSH,
  Z_FULL_FLUSH,
  Z_FINISH,
  Z_BLOCK,
  Z_TREES,
};
enum {
  Z_OK = 0,
  Z_STREAM_END = 1,
  Z_NEED_DICT = 2,
  Z_ERRNO = -1,
  Z_STREAM_ERROR = -2,
  Z_DATA_ERROR = -3,
  Z_MEM_ERROR = -4,
  Z_BUF_ERROR = -5,
  Z_VERSION_ERROR = -6
};
enum {
  Z_NO_COMPRESSION = 0,
  Z_BEST_SPEED = 1,
  Z_BEST_COMPRESSION = 9,
  Z_DEFAULT_COMPRESSION = -1,
};
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
int deflateInit(z_stream *, int);
int deflateInit2(z_stream *, int, int, int, int);
int deflate(z_stream *, int 
#ifdef __cplusplus
= Z_NO_FLUSH
#endif
);
int deflateEnd(z_stream *);
int inflateInit(z_stream *);
int inflate(z_stream *, int);
int inflateEnd(z_stream *);
}
#endif
