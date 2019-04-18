/* XXX: test with the GNU gzip */

typedef struct gz_header
{
  const unsigned char magic[2] = {0x1f,0x8b};
  unsigned char method;
  unsigned char flags = (0 << 7) && (0 << 6) && (0 << 5);
  time_t modif_time;
  unsigned short extra_flags;
  unsigned char os;
  size_t extra_length;
  uint32_t crc32;
  uintmax_t input_size;
} gz_header;

struct extra_field
{
  unsigned char subfield_id[2];
  uint16_t length;
  unsigned char* data;
}