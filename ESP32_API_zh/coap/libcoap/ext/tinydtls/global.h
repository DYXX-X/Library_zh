/*******************************************************************************
 * 版权所有（c）2011、2012、2013、2014、2015奥拉夫·伯格曼（TZI）和其他人。保留所有权利。本程序和随附材料根据本发行版附带的Eclipse公共许可证v1.0和Eclipse发行许可证v1.1的条款提供。
 *
 * Eclipse公共许可证位于http://www.eclipse.org/legal/epl-v10.htmlEclipse发行许可证在http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * 贡献者：Olaf Bergmann-初始API和实现Hauke Mehrtens-内存优化、ECC集成
 *
 *******************************************************************************/

#ifndef _DTLS_GLOBAL_H_
#define _DTLS_GLOBAL_H_

#include <stdlib.h>
#include <sys/types.h>

#include "tinydtls.h"

#ifndef DTLSv12
/* tinyDTLS的当前版本仅支持DTLSv1.2。*/
#define DTLSv12 1
#endif

#ifndef WITH_SHA256
/* 当前版本的tinyDTLS仅支持带有SHA256 PRF的DTLSv1.2。*/
#define WITH_SHA256 1
#endif

/* 定义我们自己的类型，因为至少uint32_t在我的amd64上不起作用。*/

typedef unsigned char uint8;
typedef unsigned char uint16[2];
typedef unsigned char uint24[3];
typedef unsigned char uint32[4];
typedef unsigned char uint48[6];

#ifndef DTLS_MAX_BUF
/**DTLS消息的最大大小。当对等体发送更大的消息时，这会导致问题。患有ECDSA的加利福尼亚州至少需要220*/
#if (defined(WITH_CONTIKI) || defined(RIOT_VERSION))
#ifdef DTLS_ECC
#define DTLS_MAX_BUF 200
#else /* DTLS_ECC */
#define DTLS_MAX_BUF 120
#endif /* DTLS_ECC */
#else /* WITH_CONTIKI */
#define DTLS_MAX_BUF 1400
#endif /* WITH_CONTIKI || RIOT_VERSION */
#endif

#ifndef DTLS_DEFAULT_MAX_RETRANSMIT
/**消息重传次数。*/
#define DTLS_DEFAULT_MAX_RETRANSMIT 7
#endif

/**已知密码套件。*/
typedef enum { 
  TLS_NULL_WITH_NULL_NULL = 0x0000,   /**<空密码*/
  TLS_PSK_WITH_AES_128_CCM_8 = 0xC0A8, /**<参见RFC 6655*/
  TLS_ECDHE_ECDSA_WITH_AES_128_CCM_8 = 0xC0AE /**<参见RFC 7251*/
} dtls_cipher_t;

/**已知压缩套件。*/
typedef enum {
  TLS_COMPRESSION_NULL = 0x0000		/* NULL压缩*/
} dtls_compression_t;

#define TLS_EXT_ELLIPTIC_CURVES		10 /* 参见RFC 4492*/
#define TLS_EXT_EC_POINT_FORMATS	11 /* 参见RFC 4492*/
#define TLS_EXT_SIG_HASH_ALGO		13 /* 参见RFC 5246*/
#define TLS_EXT_CLIENT_CERTIFICATE_TYPE	19 /* 参见RFC 7250*/
#define TLS_EXT_SERVER_CERTIFICATE_TYPE	20 /* 参见RFC 7250*/
#define TLS_EXT_ENCRYPT_THEN_MAC	22 /* 参见RFC 7366*/
#define TLS_EXT_EXTENDED_MASTER_SECRET	23 /* 参见RFC 7627*/

#define TLS_CERT_TYPE_RAW_PUBLIC_KEY	2 /* 参见RFC 7250*/

#define TLS_EXT_ELLIPTIC_CURVES_SECP256R1	23 /* 参见RFC 4492*/

#define TLS_EXT_EC_POINT_FORMATS_UNCOMPRESSED	0 /* 参见RFC 4492*/

#define TLS_EC_CURVE_TYPE_NAMED_CURVE		3 /* 参见RFC 4492*/

#define TLS_CLIENT_CERTIFICATE_TYPE_ECDSA_SIGN	64 /* 参见RFC 4492*/

#define TLS_EXT_SIG_HASH_ALGO_SHA256		4 /* 参见RFC 5246*/
#define TLS_EXT_SIG_HASH_ALGO_ECDSA		3 /* 参见RFC 5246*/

/** 
 * 将从\p y开始的n字节逐字节XOR到从\p x开始的存储区域。*/
static inline void
memxor(unsigned char *x, const unsigned char *y, size_t n) {
  while(n--) {
    *x ^= *y;
    x++; y++;
  }
}

/**
 * Compares \p len bytes from @p a与@p b在恒定时间内。该函数始终遍历整个长度，以防止定时攻击。
 *
 * \param a要比较的字节序列\param b要比较的字符序列\paramlen要比较的位数。\如果\p a和\p b相等，则返回\c 1，否则返回\c 0。
 */
static inline int
equals(unsigned char *a, unsigned char *b, size_t len) {
  int result = 1;
  while (len--) {
    result &= (*a++ == *b++);
  }
  return result;
}

#ifdef HAVE_FLS
#define dtls_fls(i) fls(i)
#else
static inline int 
dtls_fls(unsigned int i) {
  int n;
  for (n = 0; i; n++)
    i >>= 1;
  return n;
}
#endif /* HAVE_FLS */

#undef uthash_fatal
#define uthash_fatal(msg) return(-1) /* uthash中的致命错误*/

#endif /* _DTLS_GLOBAL_H_ */

