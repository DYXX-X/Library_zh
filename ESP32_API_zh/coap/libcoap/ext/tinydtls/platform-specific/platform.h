/************************************************************************/
/* Contiki特定参数*/
/************************************************************************/

#ifndef _PLATFORM_H_
#define _PLATFORM_H_ 1

#ifdef CONTIKI
#define WITH_CONTIKI 1

#include "contiki.h"
#include "contiki-lib.h"
#include "contiki-net.h"

#include "contiki-conf.h"

/* 定义为此包的全名。*/
#define PACKAGE_NAME "tinydtls"

/* 定义为此包的版本。*/
#define PACKAGE_VERSION "0.8.6"

/* 支持TLS_ECDHE_ECDSA_WITH_AES_128_CCM_8*/
#ifndef DTLS_CONF_ECC
#define DTLS_CONF_ECC 1
#endif
#if DTLS_CONF_ECC
#define DTLS_ECC
#endif

/* 支持TLS_PSK_WITH_AES_128_CCM_8*/
#ifndef DTLS_CONF_PSK
#define DTLS_CONF_PSK 1
#endif
#if DTLS_CONF_PSK
#define DTLS_PSK
#endif

/* 禁用所有调试输出和断言*/
#ifndef DTLS_CONF_NDEBUG
#if DTLS_CONF_NDEBUG
#define NDEBUG
#endif
#endif

/* 孔蒂基断言。小时*/
#define HAVE_ASSERT_H 1

/* 运行Contiki的受约束设备的全局常量*/
#ifndef DTLS_PEER_MAX
/**DTLS对等体（即会话）的最大数量。*/
#  define DTLS_PEER_MAX 1
#endif

#ifndef DTLS_HANDSHAKE_MAX
/**并发DTLS握手的最大数量。*/
#  define DTLS_HANDSHAKE_MAX 1
#endif

#ifndef DTLS_SECURITY_MAX
/**同时使用的密码密钥的最大数量*/
#  define DTLS_SECURITY_MAX (DTLS_PEER_MAX + DTLS_HANDSHAKE_MAX)
#endif

#ifndef DTLS_HASH_MAX
/**可以并行使用的最大哈希函数数。*/
#  define DTLS_HASH_MAX (3 * DTLS_PEER_MAX)
#endif

/**不要使用uthash哈希表*/
#define DTLS_PEERS_NOHASH 1

/* sha2的BYTE_ORDER定义*/
#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN UIP_LITTLE_ENDIAN
#endif
#ifndef BIG_ENDIAN
#define BIG_ENDIAN    UIP_BIG_ENDIAN
#endif
#ifndef BYTE_ORDER
#define BYTE_ORDER    UIP_BYTE_ORDER
#endif

#ifndef SHA2_USE_INTTYPES_H
#define SHA2_USE_INTTYPES_H 1
#endif

#endif /* CONTIKI */

#endif /* _PLATFORM_H_ */

