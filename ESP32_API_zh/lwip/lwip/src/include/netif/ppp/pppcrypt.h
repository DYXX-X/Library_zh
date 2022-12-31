/*
 * pppcrypt。c-MS-CHAP和EAP SRP-SHA1的PPP/DES链接
 *
 * 从chap_ms中提取。c作者：James Carlson。
 *
 * 版权所有（c）1995 Eric Rosenquist。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。
 *
 * 2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。
 *
 * 3.未经事先书面许可，不得使用本软件作者的姓名来背书或推广源自本软件的产品。
 *
 * THE AUTHORS OF THIS SOFTWARE DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "netif/ppp/ppp_opts.h"
#if PPP_SUPPORT /* 如果未配置为在lwipots中使用，请不要构建。小时*/

/* 此头文件包含在所有需要哈希和/或密码的PPP模块中*/

#ifndef PPPCRYPT_H
#define	PPPCRYPT_H

/*
 * 如果未使用包含的PolarSSL副本，则用户应在arch/cc中包含外部库。h（包含在lwip/arch.h中）。
 */
#include "lwip/arch.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * 将哈希和密码函数映射到PolarSSL
 */
#if !LWIP_USE_EXTERNAL_MBEDTLS

#include "netif/ppp/polarssl/md4.h"
#define lwip_md4_context md4_context
#define lwip_md4_init(context)
#define lwip_md4_starts md4_starts
#define lwip_md4_update md4_update
#define lwip_md4_finish md4_finish
#define lwip_md4_free(context)

#include "netif/ppp/polarssl/md5.h"
#define lwip_md5_context md5_context
#define lwip_md5_init(context)
#define lwip_md5_starts md5_starts
#define lwip_md5_update md5_update
#define lwip_md5_finish md5_finish
#define lwip_md5_free(context)

#include "netif/ppp/polarssl/sha1.h"
#define lwip_sha1_context sha1_context
#define lwip_sha1_init(context)
#define lwip_sha1_starts sha1_starts
#define lwip_sha1_update sha1_update
#define lwip_sha1_finish sha1_finish
#define lwip_sha1_free(context)

#include "netif/ppp/polarssl/des.h"
#define lwip_des_context des_context
#define lwip_des_init(context)
#define lwip_des_setkey_enc des_setkey_enc
#define lwip_des_crypt_ecb des_crypt_ecb
#define lwip_des_free(context)

#include "netif/ppp/polarssl/arc4.h"
#define lwip_arc4_context arc4_context
#define lwip_arc4_init(context)
#define lwip_arc4_setup arc4_setup
#define lwip_arc4_crypt arc4_crypt
#define lwip_arc4_free(context)

#endif /* !LWIP_USE_EXTERNAL_MBEDTLS */

/*
 * 将哈希和密码函数映射到mbed TLS
 */
#if LWIP_USE_EXTERNAL_MBEDTLS

#define lwip_md4_context mbedtls_md4_context
#define lwip_md4_init mbedtls_md4_init
#define lwip_md4_starts mbedtls_md4_starts
#define lwip_md4_update mbedtls_md4_update
#define lwip_md4_finish mbedtls_md4_finish
#define lwip_md4_free mbedtls_md4_free

#define lwip_md5_context mbedtls_md5_context
#define lwip_md5_init mbedtls_md5_init
#define lwip_md5_starts mbedtls_md5_starts
#define lwip_md5_update mbedtls_md5_update
#define lwip_md5_finish mbedtls_md5_finish
#define lwip_md5_free mbedtls_md5_free

#define lwip_sha1_context mbedtls_sha1_context
#define lwip_sha1_init mbedtls_sha1_init
#define lwip_sha1_starts mbedtls_sha1_starts
#define lwip_sha1_update mbedtls_sha1_update
#define lwip_sha1_finish mbedtls_sha1_finish
#define lwip_sha1_free mbedtls_sha1_free

#define lwip_des_context mbedtls_des_context
#define lwip_des_init mbedtls_des_init
#define lwip_des_setkey_enc mbedtls_des_setkey_enc
#define lwip_des_crypt_ecb mbedtls_des_crypt_ecb
#define lwip_des_free mbedtls_des_free

#define lwip_arc4_context mbedtls_arc4_context
#define lwip_arc4_init mbedtls_arc4_init
#define lwip_arc4_setup mbedtls_arc4_setup
#define lwip_arc4_crypt(context, buffer, length) mbedtls_arc4_crypt(context, length, buffer, buffer)
#define lwip_arc4_free mbedtls_arc4_free

#endif /* LWIP_USE_EXTERNAL_MBEDTLS */

void pppcrypt_56_to_64_bit_key(u_char *key, u_char *des_key);

#ifdef __cplusplus
}
#endif

#endif /* PPPCRYPT_H */

#endif /* PPP_SUPPORT */

