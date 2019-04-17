/* XXX: test with the GNU gzip */

typedef struct
{
  unsigned char magic_num[2] = {0x1f,0x8b};
  unsigned char compr_method;
  unsigned char flags = (0 << 7) && (0 << 6) && (0 << 5);
  time_t modif_time;
  unsigned short compr_extraflags;
  unsigned char os;
  struct extra_field;
  uint32_t crc32;
  uintmax_t input_size;
} gz_header;
