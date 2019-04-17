/* XXX: test with the GNU gzip */

typedef struct
{
  unsigned char magic_num[2] = {0x1f,0x8b};
  unsigned char method;
  unsigned char flags = (0 << 7) && (0 << 6) && (0 << 5);
  modif_time
} gz_header;
