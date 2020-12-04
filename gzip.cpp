#include <ctime>
#include <fstream>
#include <cstdlib>
#include <cwchar>
#include <string>
#include <ios>
#include <list>
#if __has_include(<format>)
#include <format>
#endif

#include "gzip.hpp"
#include "deflate.hpp"
#include "crc32.hpp"

using std::size_t;
using std::ifstream, std::ofstream;

namespace zlite
{
	gz_member::gz_member(const char* path, mode)
	{
		fstream& file(path, mode | binary);
		if(file.failbit)
		{
			throw failure(string("Unable to open "+path));
		}
	}
	gz_member::gzmember()
	{
		
	}
	

	//gz_member::read()
	//auto& operator >>
	gz_file::read()
	{
		
	}
	gz_file::open(const char* path, mode)
	{
		
	}
	gz_file::write()
	{
		
	}
}

extern "C"
{
	gzFile gzopen (const char *path, const char *mode);
	bool gzbuffer (gzFile file, unsigned size);
	int gzread (gzFile file, void* buf, unsigned len)
	size_t gzfread (void* buf, size_t size, size_t nitems, gzFile file);
	int gzwrite (gzFile file, void* buf, unsigned len);
	size_t gzfwrite (void* buf, size_t size, size_t nitems, gzFile file);
	short gzprintf (gzFile file, const char* format, ...);
	int gzputs (gzFile file, const char* string);
	int gzgets (gzFile file, const char* s);
	int gzputc (gzFile file, unsigned char c);
	int gzgetc (gzFile file)
	int gzungetc (unsigned char c, gzFile file);
	
	int gzclose (gzFile file);	
}
