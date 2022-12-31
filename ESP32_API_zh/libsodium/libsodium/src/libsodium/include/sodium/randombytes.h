
#ifndef randombytes_H
#define randombytes_H

#include <stddef.h>
#include <stdint.h>

#include <sys/types.h>

#include "export.h"

#ifdef __cplusplus
# ifdef __GNUC__
#  pragma GCC diagnostic ignored "-Wlong-long"
# endif
extern "C" {
#endif

typedef struct randombytes_implementation {
    const char *(*implementation_name)(void); /* 必修的*/
    uint32_t    (*random)(void);              /* 必修的*/
    void        (*stir)(void);                /* 可选择的*/
    uint32_t    (*uniform)(const uint32_t upper_bound); /* 可选，如果为NULL，将使用默认实现*/
    void        (*buf)(void * const buf, const size_t size); /* 必修的*/
    int         (*close)(void);               /* 可选择的*/
} randombytes_implementation;

#define randombytes_BYTES_MAX SODIUM_MIN(SODIUM_SIZE_MAX, 0xffffffffUL)

#define randombytes_SEEDBYTES 32U
SODIUM_EXPORT
size_t randombytes_seedbytes(void);

SODIUM_EXPORT
void randombytes_buf(void * const buf, const size_t size)
            __attribute__ ((nonnull));

SODIUM_EXPORT
void randombytes_buf_deterministic(void * const buf, const size_t size,
                                   const unsigned char seed[randombytes_SEEDBYTES])
            __attribute__ ((nonnull));

SODIUM_EXPORT
uint32_t randombytes_random(void);

SODIUM_EXPORT
uint32_t randombytes_uniform(const uint32_t upper_bound);

SODIUM_EXPORT
void randombytes_stir(void);

SODIUM_EXPORT
int randombytes_close(void);

SODIUM_EXPORT
int randombytes_set_implementation(randombytes_implementation *impl)
            __attribute__ ((nonnull));

SODIUM_EXPORT
const char *randombytes_implementation_name(void);

/* --NaCl兼容性界面--*/

SODIUM_EXPORT
void randombytes(unsigned char * const buf, const unsigned long long buf_len)
            __attribute__ ((nonnull));

#ifdef __cplusplus
}
#endif

#endif

