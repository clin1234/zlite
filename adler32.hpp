#ifndef __include_adler
#define __include_adler

#include <cstddef>
#include <cstdint>
#include <initializer_list>

#ifdef __STDC_HOSTED__
#include <array>
#include <vector>
#include <cstdint>
#ifdef __cpp_lib_span
#include <span>

using std::span;
#endif

using std::array, std::vector;
#endif

using std::initializer_list;
using std::size_t, std::uint32_t;

namespace zlite {
template <size_t len> extern uint32_t adler32(const unsigned char (&)[len]);

extern uint32_t adler32(const initializer_list<unsigned char> &);
#ifdef __STDC_HOSTED__
template <size_t len> extern uint32_t adler32(const array<unsigned char, len> &);
extern uint32_t adler32(const vector<unsigned char> &);
#ifdef __cpp_lib_span
extern uint32_t adler32(const span<unsigned char> &);
#endif
#endif
}; // namespace zlite

#endif
