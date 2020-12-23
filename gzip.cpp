#include <cstdlib>
#include <ctime>
#include <cwchar>
#include <fstream>
#include <ios>
#include <list>
#include <string>
#ifdef __STDC_HOSTED__
#include <cstdint>

using std::uint32_t, std::uint16_t;
#else
#endif
#if __has_include(<format>)
#include <format>
#endif

#include "crc32.hpp"
#include "deflate.hpp"
#include "gzip.hpp"

using std::ifstream, std::ofstream, std::fstream;
using std::size_t;
using std::ios_base::binary;

namespace zlite {
gz_member::gz_member(const char *path, mode) {
  fstream &file(path, mode | binary);
  if (file.failbit) {
    throw failure(string("Unable to open " + path));
  }
}
gz_member::gzmember() {}

// gz_member::read()
// auto& operator >>
void gz_file::read() {}
void gz_file::open(const char *path, mode) {}
void gz_file::write() {}
} // namespace zlite
