#include <limits.h>
#if defined(__VMS) || defined (VMS) || defined (__VMS__)
#include <unixio.h>
#else
#include <sys/types.h> // Windows has off_t
#endif

static_assert(CHAR_BIT == 8, "How is it possible in this day and age?");

/* Unconditional use of fixed integer types requires workarounds for C libraries
that do not define *int?_t types in <stdint.h>. */

typedef off_t off_t;
