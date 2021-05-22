/* XXX: test with the GNU gzip */
#ifndef __include_gzip
#define __include_gzip

#include <cstddef>
#ifdef __STDC_HOSTED__
#include <cstdint>
#include <fstream>
#include <unordered_map>
#include <vector>

using std::byte;
using std::unordered_map;
using std::vector;
#endif

namespace zlite {
struct opt_extra_field {
  unsigned char subfield_id[2];
  std::uint16_t data_length;
  unsigned char *data;
};

class gz_file {
  const byte magic[2]{byte(0x1f), byte(0x8b)};
  byte method;
  byte flags = byte((0 << 7) & (0 << 6) & (0 << 5));
  // Guranteed epoch is Unix time since C++20 (00:00:00 Thursday 1 Jan 1970).
  // For C++17 and older, assume it is true.
  std::uint32_t modif_time;
  byte extra_flags;
  unsigned char os;
  std::uint16_t opt_extra_field_len;
  struct opt_extra_field oxf;
  unsigned char *opt_filename;
  unsigned char *opt_comment;
  std::uint16_t opt_hdr_crc16;
  unsigned char *data;
  std::uint32_t crc32;
  std::uint32_t input_size;

public:
  gz_file(vector<unsigned char>&);
  gz_file(const char *path, std::ios_base::openmode mode);
  explicit operator gzFile() const;
  gz_file() = default;
  void open(const char *path, std::ios_base::openmode mode);
  void read();
  void write();
};

enum class compression_method : unsigned char { Deflate = 8 };

enum class OS : unsigned char {
  FAT_filesystem,
  Amiga,
  VMS,
  Unix,
  VM_CMS,
  Atari_TOS,
  HPFS,
  Mac_OS,
  Z_System,
  CP_M,
  TOPS_20,
  NTFS,
  QDOS,
  RISC_OS,
  unknown = 255
};

const unordered_map<OS, const char *> mapper{
    {OS::FAT_filesystem, "FAT filesystem"},
    {OS::Amiga, "Amiga OS"},
    {OS::VMS, "VMS or OpemVMS"},
    {OS::Unix, "Unix or Unix-like OS"},
    {OS::VM_CMS, "VM/CMS"},
    {OS::Atari_TOS, "Atari TOS"},
    {OS::HPFS, "HPFS"},
    {OS::Z_System, "zSystem"},
    {OS::CP_M, "CP/M"},
    {OS::TOPS_20, "TOPS-20"},
    {OS::NTFS, "NTFS"},
    {OS::QDOS, "QDOS"},
    {OS::RISC_OS, "RISC OS"},
    {OS::unknown, "Unknown OS"}};
} // namespace zlite
#endif
