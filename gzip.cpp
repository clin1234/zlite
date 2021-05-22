#include <climits>
#include <cstddef>
#include <cstdint>
#ifdef __STDC_HOSTED__
#include <chrono>
#include <cstdlib>
#include <cwchar>
#include <fstream>
#include <ios>
#include <iostream>
#include <list>
//#include <string>
#include <cstring>
#include <thread>
#include <vector>

using std::cerr;
using std::ifstream, std::ofstream, std::fstream;
using std::size_t;
// using std::string;
using std::thread;
using std::vector;
#else
#endif
#if __has_include(<format>)
#include <format>
#endif
using std::byte;
using std::uint32_t, std::uint16_t;

#include "crc32.hpp"
#include "deflate.hpp"
#include "gzip.hpp"
#include "zlib.hpp"

namespace zlite {

// gz_member::read()
// auto& operator >>
void gz_file::open(const char *path, std::ios_base ::openmode mode) {
  ifstream file(path, file.binary | mode);
  if (file.failbit) {
    cerr << "Unable to open " << path << '\n';
  }
  auto test = file.tellg();
  file.seekg(0, std::ios::beg);
  auto size = std::size_t(test - file.tellg());
  if (size == 0)
    return;

  vector<unsigned char> buf(size);
  /* Sigh... the canonical iostream approach to read and write binary files is
  to open a stream with std::ios::binary, then read(). However, since the most
  common specialization is basic_ifstream<char>, where char is the character
  type, and the first parameter of read() expects a char pointer, the
  reinterpret_cast is necessary.
  */
  file.read(reinterpret_cast<char *>(buf.data()), buf.size());
  if (buf[0] != 0x1f || buf[1] != 0x88)
    std::cerr << "Invalid gzip magic number: got " << buf[0] << "and "
              << buf[1];
  method = byte(buf[3]);
  modif_time = buf[4] | (buf[5] << 8) | (buf[6] << 16) | (buf[7] << 24);
  extra_flags = buf[9];
  OS cho = static_cast<OS>(buf[10]);
  // To be done when C++20 support matures
  // using enum OS;
  switch (cho) {
  case OS::FAT_filesystem:
    [[fallthrough]];
  case OS::Amiga:
    [[fallthrough]];
  case OS::VMS:
    [[fallthrough]];
  case OS::Unix:
    [[fallthrough]];
  case OS::VM_CMS:
    [[fallthrough]];
  case OS::Atari_TOS:
    [[fallthrough]];
  case OS::HPFS:
    [[fallthrough]];
  case OS::Mac_OS:
    [[fallthrough]];
  case OS::Z_System:
    [[fallthrough]];
  case OS::CP_M:
    [[fallthrough]];
  case OS::TOPS_20:
    [[fallthrough]];
  case OS::NTFS:
    [[fallthrough]];
  case OS::QDOS:
    [[fallthrough]];
  case OS::RISC_OS:
    [[fallthrough]];
  case OS::unknown:
    os = buf[10];
    break;
  default:
    std::cerr << "Unknown value for OS field: got " << buf[10];
  }
  // FTEXT
  if (to_integer<bool>(flags & byte{0x1f}) >> 0)
    ;

  // FEXTRA
  if (to_integer<bool>(flags & byte{0x1f}) >> 2) {
  }
  // FNAME
  if (to_integer<bool>(flags & byte{0x1f}) >> 3) {
  }
  // FCOMMENT
  if (to_integer<bool>(flags & byte{0x1f}) >> 4) {
  }
  // FHCRC
  if (to_integer<bool>(flags & byte{0x1f}) >> 1) {
  }
  thread s;

  s.join();
  file.close();
}
void gz_file::write() {}
gz_file::operator gzFile() const { return gz_file(); }
} // namespace zlite

extern "C" {
gzFile gzopen(const char *path, const char *mode) { return nullptr; }
int gzbuffer(gzFile file, unsigned size) {
  if (file == nullptr)
    return Z_STREAM_ERROR;
}
int gzread(gzFile file, void *buf, unsigned len) {
  if (file == nullptr)
    return Z_STREAM_ERROR;
}
size_t gzfread(void *buf, size_t size, size_t nitems, gzFile file) {
  if (file == nullptr || size == 0 || nitems == 0 ||
      (nitems * size) / size != nitems || buf == nullptr)
    return gzwrite(file, buf, nitems*size) / size;
}
int gzwrite(gzFile file, void *buf, unsigned len) {
  auto bytes_written{0};

  return bytes_written;
}
size_t gzfwrite(void *buf, size_t size, size_t nitems, gzFile file) {}
short gzprintf(gzFile file, const char *format, ...) {
  if (file == nullptr)
    return Z_STREAM_ERROR;
}
int gzputs(gzFile file, const char *string) {

  auto len{strlen(string)};
  if (file == nullptr || len > INT_MAX)
    return -1;
  gzwrite(file, &string, len);
  return len;
}
char *gzgets(gzFile file, char *buf, int len) {

  return buf;
  if (auto x{0}; x)
    return nullptr;
}
int gzputc(gzFile file, int c) {
  if (file == nullptr)
    return Z_STREAM_ERROR;
  return static_cast<unsigned char>(c);
  if (auto x{0}; x)
    return -1;
}
int gzgetc(gzFile file) {
  if (file == nullptr)
    return -1;
  unsigned char b[1];
  return gzread(file, b, 1);
}
int gzungetc(unsigned char c, gzFile file) {
  if (file == nullptr)
    return Z_STREAM_ERROR;
}
int gzflush(gzFile file, int flush) {
  if (file == nullptr)
    return Z_STREAM_ERROR;
}
z_off_t gzseek(gzFile file, z_off_t offset, int whence) {
  if (file == nullptr)
    return Z_STREAM_ERROR;
}
int gzrewind(gzFile file) {
  if (file == nullptr)
    return Z_STREAM_ERROR;
}
z_off_t gztell(gzFile file) {
  if (file == nullptr)
    return Z_STREAM_ERROR;
}
z_off_t gzoffset(gzFile file) {
  if (file == nullptr)
    return Z_STREAM_ERROR;
}
int gzeof(gzFile file) {
  if (file == nullptr)
    return Z_STREAM_ERROR;
}
bool gzdirect(gzFile file) {
  if (file == nullptr)
    return 0;
}
int gzclose(gzFile file) {
  if (file == nullptr)
    return Z_STREAM_ERROR;
}
const char *gzerror(gzFile file, int *errnum) {}
void gzclearerr(gzFile file) {}
}
