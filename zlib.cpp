#include <cstddef>
#include <type_traits>
#ifdef __STDC_HOSTED__
#include <cstdint>
#include <map>
#include <cstdint>
#endif

using std::byte;
using std::conditional_t;
using std::map;
using std::uint32_t, std::uint8_t;

#include "zlib.hpp"

using zlite::compression_method;

namespace zlite
{
zlib::zlib() noexcept
{
}

map<const char *, unsigned char> zlib::compression_info()
{
    return map<const char *, unsigned char>{
        {"Compression method", compression_method::Deflate},
        {"Compression info", compression_field & 0xf0},
        {"Dictionary is preset", compression_field & 0b100000},
        {"Compression level", flags & 0xc0},
    };
}
}; // namespace zlite
