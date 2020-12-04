/* XXX: test with the GNU gzip */

class gz_member
{
  const unsigned char magic[2] {0x1f,0x8b};
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
};

enum class 
{
	
}

enum class compression_method : unsigned char{}
{
	Deflate = 8
};

class gz_file
{
	std::list<gz_memeber> members;
	public:
	read
	write
}

enum class OS : unsigned char {}
{
	FAT_filesystem,
	Amiga,
	VMS,
	Unix,
	VM_CMS;
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

struct opt_extra_field
{
  unsigned char subfield_id[2];
  uint16_t data_length;
  unsigned char* data;
};

#ifdef __cplusplus
extern "C" {
#endif
	gzFile gzopen (const char *path, const char *mode);
	bool gzbuffer (gzFile file, unsigned size);
	int gzread (gzFile file, void* buf, unsigned len);
	size_t gzfread (void* buf, size_t size, size_t nitems, gzFile file);
	int gzwrite (gzFile file, void* buf, unsigned len);
	size_t gzfwrite (void* buf, size_t size, size_t nitems, gzFile file);
	short gzprintf (gzFile file, const char* format, ...);
	int gzputs (gzFile file, const char* string);
	int gzgets (gzFile file, const char* s);
	int gzputc (gzFile file, unsigned char c);
	int gzgetc (gzFile file);
	int gzungetc (unsigned char c, gzFile file);
	int gzclose (gzFile file);
#ifdef __cplusplus
}
#endif
