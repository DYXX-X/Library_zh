/************************************************************************/
/* RIOT特定参数*/
/************************************************************************/


#ifndef _RIOT_BOARDS_H_
#define _RIOT_BOARDS_H_

/*
 * 设置TINYDTLS OVER RIOT在TINYDTLS的标准安装中，它们位于dtls_config.h只有主库使用的那些（而不是测试/或测试文件）在这里。
 *
 * 警告：动态内存在RIOT上运行得不太好。
 */


/* RIOT支持＜assert.h＞头文件。*/
#define HAVE_ASSERT_H 1

/* RIOT支持＜inttypes.h＞头文件。*/
#define HAVE_INTTYPES_H 1

/* RIOT未实现成员sin6_len*/
#undef HAVE_SOCKADDR_IN6_SIN6_LEN

/* RIOT支持<sys/time.h>头文件。*/
#define HAVE_SYS_TIME_H 1

/* RIOT支持＜time.h＞头文件。*/
#define HAVE_TIME_H 1

/* RIOT支持套接字*/
/* TODO注意：这应该由WITH_RIOT_SOCKETS启用*/

/* RIOT部分支持“vprintf”函数。*/
/* 危险删除会导致dtls_debug.h和dtls_debug.c出现问题*/
#define HAVE_VPRINTF 1


/*
 * 关于TINYDTLS的信息注意：这主要由dtls_debug使用
 */

/* 定义发送此包的错误报告的地址。*/
#define PACKAGE_BUGREPORT ""

/* 定义为此包的全名。*/
#define PACKAGE_NAME "tinydtls"

/* 定义此包的全名和版本。*/
#define PACKAGE_STRING "tinydtls 0.8.6.X"

/* 将此包的短名称定义为一个符号。*/
#define PACKAGE_TARNAME "tinydtls"

/* 定义到此包的主页。*/
#define PACKAGE_URL ""

/* 定义为此包的版本。*/
#define PACKAGE_VERSION "0.8.6.X"

/*
 * PERFORMANCE AND RESOURCES AVALIABLE TO THE MOTES FOR DTLS SESSIONS
 *
 * 它们与peer.c、crypto.c和hmac.c一起使用
 *
 * 注意：这些数字并非严格意义上的最小值。你可以随意调整。示例：iotlab-m3使用两个Peers会话进行测试。
 *
 * 警告：动态内存在RIOT上运行得不太好。因此，调整静态内存可以提高RIOT节点的性能。
 */

#ifndef DTLS_CONTEXT_MAX
/**同时DTLS上下文的最大数量。*/
#  define DTLS_CONTEXT_MAX 2
#endif

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

/* TODO:使其适应RIOT（当前仅适用于Contiki）*/
#ifndef DTLS_HASH_MAX
/**可以并行使用的最大哈希函数数。*/
#  define DTLS_HASH_MAX (3 * DTLS_PEER_MAX)
#endif

/**不要使用uthash的哈希表（这些表使用malloc/free）*/
#define DTLS_PEERS_NOHASH 1

/* 802.15.4 ACK可以引起具有高于1的值的非常快的重传。这是RIOT MAC暂时的不良行为
 */
#ifndef DTLS_DEFAULT_MAX_RETRANSMIT
# define DTLS_DEFAULT_MAX_RETRANSMIT 1
#endif


/*
 * INFORMATION SHA2/ LIBRARY VARIABLES
 *
 * TODO:澄清RIOT识别BYTE_ORDER的方式
 */

/*
 * RIOT支持＜inttypes.h＞头文件。注意：uintXX_t定义带有ANSI C标头，而不是自定义typedef
 */
#define SHA2_USE_INTTYPES_H 1

/* RIOT“支持”memset（）/memcpy（），但不支持bzero（）/mcopy（）。*/
#define SHA2_USE_MEMSET_MEMCPY 1


/*
 * 注Gcc是定义我们是大端还是小端的人。因为RIOT有__BYTE_ORDER__和BYTE_ORD，所以这里不清楚应该首选哪个。或者，如果sha2/sha2.h内部的#define应该完全删除。
 */
#ifndef BIG_ENDIAN
#if !defined(__BIG_ENDIAN__)
#    define BIG_ENDIAN    4321
#  else
#    define BIG_ENDIAN    __BIG_ENDIAN__
#  endif
#endif

#ifndef LITTLE_ENDIAN
#if !defined(__LITTLE_ENDIAN__)
#    define LITTLE_ENDIAN    1234
#  else
#    define LITTLE_ENDIAN    __LITTLE_ENDIAN__
#  endif
#endif

#endif /* _RIOT_BOARDS_H_ */

