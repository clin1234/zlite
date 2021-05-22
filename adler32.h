#ifndef __adler32_h
#define __adler32_h

#include <stdint.h>

extern uint32_t adler32(unsigned long adler, const unsigned char *data,
                           unsigned int len);
extern uint32_t adler32_z(unsigned long adler, const unsigned char* data,
                             size_t len);
extern uint32_t adler32_combine(unsigned long adler1, unsigned long adler2,
                                   unsigned long long len);

#endif
