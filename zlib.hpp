#ifndef __include_zlib
#define __include_zlib

#include <type_traits>

using std::conditional_t;

namespace zlite
{

enum class compression_method : unsigned char
{
    Deflate = 8,
    Reserved = 15
};

class zlib
{
    uint8_t compression_field;
    uint8_t flags;
    /* Not really idiomatic C++, but this will only insert this member in the
    class if the bit for a preset dictionary is set. If not, the compressed
    data will succeed the flags. */
    [[no_unique_address]]
    conditional_t<flags & (1 << 5), uint32_t, decltype([] {})> dict_adler_32;
    template <size_t len> byte (&compressed_data)[len];
    friend uint32_t adler_32;

  public:
    map<const char *, unsigned char> compression_info();
    zlib(byte (&uncompressed_data)[], function<, >)
      : adler32(uncompressed_data);
};

struct base
{
    virtual byte (&)[] compress(zlib &stream, byte (&data)[],
      unsigned char level = 2, _Bool use_dictionary)
    {
        stream.adler_32{adler32(data)};
    }
    virtual byte (&)[] decompress(zlib &stream, byte (&data)[]) = 0;
}
}; // namespace zlite
#endif
