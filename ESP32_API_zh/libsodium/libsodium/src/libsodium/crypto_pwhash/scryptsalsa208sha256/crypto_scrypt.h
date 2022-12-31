/*-
 * 版权所有2009 Colin Percival版权所有2013 Alexander Peslyak保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 该文件最初由Colin Percival作为Tarsnap在线备份系统的一部分编写。
 */
#ifndef crypto_scrypt_H
#define crypto_scrypt_H

#include <limits.h>
#include <stddef.h>
#include <stdint.h>

#if SIZE_MAX > 0xffffffffULL
#define ARCH_BITS 64
#else
#define ARCH_BITS 32
#endif

#define crypto_pwhash_scryptsalsa208sha256_STRPREFIXBYTES 14
#define crypto_pwhash_scryptsalsa208sha256_STRSETTINGBYTES 57
#define crypto_pwhash_scryptsalsa208sha256_STRSALTBYTES 32
#define crypto_pwhash_scryptsalsa208sha256_STRSALTBYTES_ENCODED 43
#define crypto_pwhash_scryptsalsa208sha256_STRHASHBYTES 32
#define crypto_pwhash_scryptsalsa208sha256_STRHASHBYTES_ENCODED 43

#define BYTES2CHARS(bytes) ((((bytes) *8) + 5) / 6)

typedef struct {
    void * base, *aligned;
    size_t size;
} escrypt_region_t;

typedef union {
    uint64_t d[8];
    uint32_t w[16];
} escrypt_block_t;

typedef escrypt_region_t escrypt_local_t;

extern int escrypt_init_local(escrypt_local_t *__local);

extern int escrypt_free_local(escrypt_local_t *__local);

extern void *alloc_region(escrypt_region_t *region, size_t size);
extern int free_region(escrypt_region_t *region);

typedef int (*escrypt_kdf_t)(escrypt_local_t *__local, const uint8_t *__passwd,
                             size_t __passwdlen, const uint8_t *__salt,
                             size_t __saltlen, uint64_t __N, uint32_t __r,
                             uint32_t __p, uint8_t *__buf, size_t __buflen);

extern int escrypt_kdf_nosse(escrypt_local_t *__local, const uint8_t *__passwd,
                             size_t __passwdlen, const uint8_t *__salt,
                             size_t __saltlen, uint64_t __N, uint32_t __r,
                             uint32_t __p, uint8_t *__buf, size_t __buflen);

extern int escrypt_kdf_sse(escrypt_local_t *__local, const uint8_t *__passwd,
                           size_t __passwdlen, const uint8_t *__salt,
                           size_t __saltlen, uint64_t __N, uint32_t __r,
                           uint32_t __p, uint8_t *__buf, size_t __buflen);

extern uint8_t *escrypt_r(escrypt_local_t *__local, const uint8_t *__passwd,
                          size_t __passwdlen, const uint8_t *__setting,
                          uint8_t *__buf, size_t __buflen);

extern uint8_t *escrypt_gensalt_r(uint32_t __N_log2, uint32_t __r, uint32_t __p,
                                  const uint8_t *__src, size_t __srclen,
                                  uint8_t *__buf, size_t __buflen);

extern const uint8_t *escrypt_parse_setting(const uint8_t *setting,
                                            uint32_t *N_log2_p, uint32_t *r_p,
                                            uint32_t *p_p);

#endif /* !_CRYPTO_SCRYPT_H_ */

