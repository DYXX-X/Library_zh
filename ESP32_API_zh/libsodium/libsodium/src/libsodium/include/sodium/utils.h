
#ifndef sodium_utils_H
#define sodium_utils_H

#include <stddef.h>

#include "export.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SODIUM_C99
# if defined(__cplusplus) || !defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L
#  define SODIUM_C99(X)
# else
#  define SODIUM_C99(X) X
# endif
#endif

SODIUM_EXPORT
void sodium_memzero(void * const pnt, const size_t len);

SODIUM_EXPORT
void sodium_stackzero(const size_t len);

/*
 * 警告：必须使用sodium_memcmp（）在恒定时间内验证两个密钥是否相等。如果键相等，则返回0；如果键不同，则返回-1。此函数不是为词典比较而设计的。
 */
SODIUM_EXPORT
int sodium_memcmp(const void * const b1_, const void * const b2_, size_t len)
            __attribute__ ((warn_unused_result));

/*
 * sodium_compare（）返回-1如果b1_<b2_，则返回1，如果b1_>b2_，并且返回0如果b1_==b2_它适用于字典比较，或者比较以小端格式存储的随机数和计数器。但是，它比sodium_memcmp（）慢。
 */
SODIUM_EXPORT
int sodium_compare(const unsigned char *b1_, const unsigned char *b2_,
                   size_t len) __attribute__ ((warn_unused_result));

SODIUM_EXPORT
int sodium_is_zero(const unsigned char *n, const size_t nlen);

SODIUM_EXPORT
void sodium_increment(unsigned char *n, const size_t nlen);

SODIUM_EXPORT
void sodium_add(unsigned char *a, const unsigned char *b, const size_t len);

SODIUM_EXPORT
void sodium_sub(unsigned char *a, const unsigned char *b, const size_t len);

SODIUM_EXPORT
char *sodium_bin2hex(char * const hex, const size_t hex_maxlen,
                     const unsigned char * const bin, const size_t bin_len)
            __attribute__ ((nonnull(1)));

SODIUM_EXPORT
int sodium_hex2bin(unsigned char * const bin, const size_t bin_maxlen,
                   const char * const hex, const size_t hex_len,
                   const char * const ignore, size_t * const bin_len,
                   const char ** const hex_end)
            __attribute__ ((nonnull(1)));

#define sodium_base64_VARIANT_ORIGINAL            1
#define sodium_base64_VARIANT_ORIGINAL_NO_PADDING 3
#define sodium_base64_VARIANT_URLSAFE             5
#define sodium_base64_VARIANT_URLSAFE_NO_PADDING  7

/*
 * 使用给定变量计算将BIN_LEN字节编码为base64字符串所需的长度。计算的长度包括尾随\0。
 */
#define sodium_base64_ENCODED_LEN(BIN_LEN, VARIANT) \
    (((BIN_LEN) / 3U) * 4U + \
    ((((BIN_LEN) - ((BIN_LEN) / 3U) * 3U) | (((BIN_LEN) - ((BIN_LEN) / 3U) * 3U) >> 1)) & 1U) * \
     (4U - (~((((VARIANT) & 2U) >> 1) - 1U) & (3U - ((BIN_LEN) - ((BIN_LEN) / 3U) * 3U)))) + 1U)

SODIUM_EXPORT
size_t sodium_base64_encoded_len(const size_t bin_len, const int variant);

SODIUM_EXPORT
char *sodium_bin2base64(char * const b64, const size_t b64_maxlen,
                        const unsigned char * const bin, const size_t bin_len,
                        const int variant) __attribute__ ((nonnull(1)));

SODIUM_EXPORT
int sodium_base642bin(unsigned char * const bin, const size_t bin_maxlen,
                      const char * const b64, const size_t b64_len,
                      const char * const ignore, size_t * const bin_len,
                      const char ** const b64_end, const int variant)
            __attribute__ ((nonnull(1)));

SODIUM_EXPORT
int sodium_mlock(void * const addr, const size_t len)
            __attribute__ ((nonnull));

SODIUM_EXPORT
int sodium_munlock(void * const addr, const size_t len)
            __attribute__ ((nonnull));

/* 警告：sodium_malloc（）和sodium_allocarray（）不是通用分配函数。
 *
 * 它们返回一个指针，指向一个填充了0xd0字节的区域，后面紧跟着一个保护页。因此，在请求的分配大小之后访问单个字节将有意触发分段错误。
 *
 * 如果检测到缓冲区下溢，则放置在区域开始之前的金丝雀和附加保护页也可能会终止进程。
 *
 * 内存布局为：[无保护区域大小（只读）][保护页（无访问）][无保护页（读/写）][防护页（无存取）]无保护页的布局为：〔可选填充〕〔16字节金丝雀〕〔用户区域〕
 *
 * 然而：
 * -这些功能明显低于标准功能
 * -每个分配需要3或4个附加页面
 * -如果分配大小不是所需对齐的倍数，则返回的地址将不会对齐。因此，这些函数被设计为存储数据，例如密钥和消息。
 *
 * sodium_malloc（）可用于分配任何libnaid数据结构。
 *
 * crypto_generichash_state结构被压缩，其长度为357或361字节。因此，当使用sodium_malloc（）分配crypto_generichash_state结构时，必须添加填充以确保正确对齐。crypto_generichash_statebytes（）返回四舍五入的结构大小，应该优先选择sizeof（）：state=sodium_malloc（crypto_generichash-statebytes））；
 */

SODIUM_EXPORT
void *sodium_malloc(const size_t size)
            __attribute__ ((malloc));

SODIUM_EXPORT
void *sodium_allocarray(size_t count, size_t size)
            __attribute__ ((malloc));

SODIUM_EXPORT
void sodium_free(void *ptr);

SODIUM_EXPORT
int sodium_mprotect_noaccess(void *ptr) __attribute__ ((nonnull));

SODIUM_EXPORT
int sodium_mprotect_readonly(void *ptr) __attribute__ ((nonnull));

SODIUM_EXPORT
int sodium_mprotect_readwrite(void *ptr) __attribute__ ((nonnull));

SODIUM_EXPORT
int sodium_pad(size_t *padded_buflen_p, unsigned char *buf,
               size_t unpadded_buflen, size_t blocksize, size_t max_buflen)
            __attribute__ ((nonnull(2)));

SODIUM_EXPORT
int sodium_unpad(size_t *unpadded_buflen_p, const unsigned char *buf,
                 size_t padded_buflen, size_t blocksize)
            __attribute__ ((nonnull(2)));

/* -------- */

int _sodium_alloc_init(void);

#ifdef __cplusplus
}
#endif

#endif

