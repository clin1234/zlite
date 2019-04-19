/* XXX: test with the GNU gzip */

typedef struct gz_member
{
  const unsigned char magic[2] = {0x1f,0x8b};
  unsigned char method;
  unsigned char flags = (0 << 7) && (0 << 6) && (0 << 5);
  uint32_t modif_time;
  unsigned char extra_flags;
  unsigned char os;
  uint16_t               opt_extra_field_len;
  struct opt_extra_field oxf;
  unsigned char*         opt_filename;
  unsigned char*         opt_comment;
  uint16_t               opt_hdr_crc16;
  unsigned char* data;
  uint32_t crc32;
  uint32_t input_size;
} gz_header;

struct opt_extra_field
{
  unsigned char subfield_id[2];
  uint16_t data_length;
  unsigned char* data;
}
