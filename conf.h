#include <limits.h>

#if CHAR_BIT != 8
 #error Your system does not define one byte as 8 bits. How in the world is it\
 possible...
#endif

/* Unconditional use of fixed integer types requires workarounds for C libraries
that do not define *int?_t types in <stdint.h>. */
switch(unsigned char x = 2)
{
  case sizeof(x)==sizeof(unsigned short):
    typedef uint16_t unsigned short; break;
  case sizeof(x)==sizeof(unsigned int):
    typedef uint16_t unsigned int; break;
}

switch(unsigned char x = 4)
{
  case sizeof(x)==sizeof(unsigned short):
    typedef uint32_t unsigned short; break;
  case sizeof(x)==sizeof(unsigned int):
    typedef uint32_t unsigned int; break;
  case sizeof(x)==sizeof(unsigned long):
    typedef uint32_t unsigned long; break;
}
