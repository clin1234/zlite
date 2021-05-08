/* Userspace header as a drop-in replacement for zlib. */
/*#include "conf.h"
enum flush_mode{
        no_flush, partial_flush, sync_flush, full_flush, finish, block, tree
};
enum return_code{
    ever = -6, ebuf, emem, edata, estream, errno, need_dict, stream_end, ok
};*/
#ifndef ___zlib
#define ___zlib

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "adler32.h"

#ifdef __cplusplus
}
#endif

#endif
