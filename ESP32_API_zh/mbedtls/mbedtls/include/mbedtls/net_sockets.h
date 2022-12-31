/**
 * \文件net_sockets.h
 *
 * \简单的网络套接字抽象层，将MbedTLS集成到BSD风格的套接字API中。
 *
 *          网络套接字模块提供了将Mbed TLS库集成到BSD套接字实现中的示例。该模块旨在作为一个示例，说明如何将Mbed TLS集成到网络堆栈中，以及为其支持的平台提供Mbed TLS的网络集成。
 *
 *          该模块仅用于Mbed TLS库，不用于第三方应用软件直接使用。
 *
 *          支持的平台如下：Microsoft Windows和Windows CE POSIX/Unix平台，包括Linux、OS X
 *
 */
/*
 *  版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */
#ifndef MBEDTLS_NET_SOCKETS_H
#define MBEDTLS_NET_SOCKETS_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/ssl.h"

#include <stddef.h>
#include <stdint.h>

/**无法打开套接字。*/
#define MBEDTLS_ERR_NET_SOCKET_FAILED                     -0x0042
/**与给定服务器/端口的连接失败。*/
#define MBEDTLS_ERR_NET_CONNECT_FAILED                    -0x0044
/**套接字绑定失败。*/
#define MBEDTLS_ERR_NET_BIND_FAILED                       -0x0046
/**无法侦听套接字。*/
#define MBEDTLS_ERR_NET_LISTEN_FAILED                     -0x0048
/**无法接受传入连接。*/
#define MBEDTLS_ERR_NET_ACCEPT_FAILED                     -0x004A
/**从套接字读取信息失败。*/
#define MBEDTLS_ERR_NET_RECV_FAILED                       -0x004C
/**通过套接字发送信息失败。*/
#define MBEDTLS_ERR_NET_SEND_FAILED                       -0x004E
/**对等方已重置连接。*/
#define MBEDTLS_ERR_NET_CONN_RESET                        -0x0050
/**无法获取给定主机名的IP地址。*/
#define MBEDTLS_ERR_NET_UNKNOWN_HOST                      -0x0052
/**缓冲区太小，无法容纳数据。*/
#define MBEDTLS_ERR_NET_BUFFER_TOO_SMALL                  -0x0043
/**上下文无效，例如因为它是free（）ed。*/
#define MBEDTLS_ERR_NET_INVALID_CONTEXT                   -0x0045
/**轮询网络上下文失败。*/
#define MBEDTLS_ERR_NET_POLL_FAILED                       -0x0047
/**输入无效。*/
#define MBEDTLS_ERR_NET_BAD_INPUT_DATA                    -0x0049

#define MBEDTLS_NET_LISTEN_BACKLOG         10 /**＜listen（）应该使用的backlog。*/

#define MBEDTLS_NET_PROTO_TCP 0 /**<TCP传输协议*/
#define MBEDTLS_NET_PROTO_UDP 1 /**<UDP传输协议*/

#define MBEDTLS_NET_POLL_READ  1 /**<在\c mbedtls_net_poll中用于检查挂起的数据*/
#define MBEDTLS_NET_POLL_WRITE 2 /**<在\c mbedtls_net_poll中用于检查是否可以写入*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 套接字的包装类型。
 *
 * 目前仅支持一个文件描述符，但将来可能会更多（例如，两个文件描述符用于IPv4+IPv6的组合支持，或用于手动UDP解复用的附加结构）。
 */
typedef struct mbedtls_net_context
{
    int fd;             /**<基础文件描述符*/
}
mbedtls_net_context;

/**
 * \brief初始化上下文只是使上下文可以安全地使用或释放。
 *
 * \param ctx要初始化的上下文
 */
void mbedtls_net_init( mbedtls_net_context *ctx );

/**
 * \brief在给定协议中启动与host:port的连接
 *
 * \param ctx套接字，用于使用\param host host连接到\param port端口，用于连接到\pparam proto协议：MBEDTLS_NET_proto_TCP或MBEDTLS_NET_proto_UDP
 *
 * \如果成功，则返回0，或以下之一：MBEDTLS_ERROR_NET_SOCKET_FAILED、MBEDTLS_ERROR_NET_UNKNOWN_HOST、MBEDLLS_ERROR_NET _CONNECT_FAILED
 *
 * \注意：即使使用UDP，也将套接字设置为连接模式。
 */
int mbedtls_net_connect( mbedtls_net_context *ctx, const char *host, const char *port, int proto );

/**
 * \brief在所选协议的bind_ip:port上创建一个接收套接字。如果bind_ip==NULL，则绑定所有接口。
 *
 * \param ctx要使用\param bind_ip ip绑定的套接字，可以为NULL \param port要使用的端口号\param proto协议：MBEDTLS_NET_proto_TCP或MBEDTLS_NET_proto_UDP
 *
 * \如果成功，则返回0，或以下值之一：MBEDTLS_ERROR_NET_SOCKET_FAILED、MBEDTLS_ERROR_NET_UNKNOWN_HOST、MBEDLLS_ERROR_NET _BIND_FAILED、MBETTLS_ERR_NET_LISTEN_FAILED
 *
 * \注意：无论协议如何，都会打开套接字并绑定它。此外，如果协议是TCP，则使套接字侦听。
 */
int mbedtls_net_bind( mbedtls_net_context *ctx, const char *bind_ip, const char *port, int proto );

/**
 * \brief接受来自远程客户端的连接
 *
 * \param bind_ctx相关套接字\param client_ctx将包含连接的客户端套接字\paramclient_ip将包含客户端ip地址，可以为NULL \param buf_size client_ip缓冲区的大小\param ip_len将接收写入的客户端ip的大小，如果client_ip为空，则可以为NULL
 *
 * \如果成功，则返回0；如果buf_size太小，则返回MBEDTLS_ERROR_NET_SOCKET_FAILED、MBEDTLS_ERROR_NET_BIND_FAILED、MBEDTLS_ERR_NET_ACCEPT_FAILED或MBEDTLS-ERR_NET_BUFFER_TOO_SMALL；如果BIND_fd设置为非阻塞，则MBEDTL_ERR_SSL_WANT_READ，并且ACCEPT（）将阻塞。
 */
int mbedtls_net_accept( mbedtls_net_context *bind_ctx,
                        mbedtls_net_context *client_ctx,
                        void *client_ip, size_t buf_size, size_t *ip_len );

/**
 * \brief检查并等待上下文准备好读/写
 *
 * \注意：此函数的当前实现使用select（），如果文件描述符为\c FD_SETSIZE或更大，则返回错误。
 *
 * \param ctx要检查的套接字\param rw位标志由MBEDTLS_NET_POLL_READ和MBEDTLS_NET_POLL-WRITE组成，指定要等待的事件：
 *                 -如果设置了MBEDTLS_NET_POLL_READ，则当网络上下文可供读取时，函数将立即返回。
 *                 -如果设置了MBEDTLS_NET_POLL_WRITE，则当网络上下文可用于写入时，函数将立即返回。\param timeout返回前等待的最大时间，以毫秒为单位。如果\c超时为零，函数将立即返回。如果\c超时
 *                 -1u，功能块可能无限期。
 *
 * \成功或超时时返回由MBEDTLS_NET_POLL_READ/WRITE组成的Bitmask，否则返回负返回码。
 */
int mbedtls_net_poll( mbedtls_net_context *ctx, uint32_t rw, uint32_t timeout );

/**
 * \brief设置套接字阻塞
 *
 * \param ctx要设置的套接字
 *
 * \如果成功，则返回0，或返回非零错误代码
 */
int mbedtls_net_set_block( mbedtls_net_context *ctx );

/**
 * \brief设置套接字不阻塞
 *
 * \param ctx要设置的套接字
 *
 * \如果成功，则返回0，或返回非零错误代码
 */
int mbedtls_net_set_nonblock( mbedtls_net_context *ctx );

/**
 * \简短的便携式usleep助手
 *
 * \param usec休眠的微秒数
 *
 * \注意实际睡眠时间不会小于select（）的超时粒度（通常为10ms）。
 */
void mbedtls_net_usleep( unsigned long usec );

/**
 * \brief最多读取“len”个字符。如果没有发生错误，则返回实际读取的金额。
 *
 * \param ctx套接字\param buf要写入的缓冲区\param len缓冲区的最大长度
 *
 * \返回接收的字节数或非零错误代码；对于非阻塞套接字，MBEDTLS_ERROR_SSL_WANT_READ表示READ（）将阻塞。
 */
int mbedtls_net_recv( void *ctx, unsigned char *buf, size_t len );

/**
 * \brief最多写“len”个字符。如果没有发生错误，则返回实际读取的金额。
 *
 * \param ctx Socket \param buf要从中读取的缓冲区\param len缓冲区的长度
 *
 * \返回发送的字节数或非零错误代码；对于非阻塞套接字，MBEDTLS_ERROR_SSL_WANT_WRITE表示WRITE（）将阻塞。
 */
int mbedtls_net_send( void *ctx, const unsigned char *buf, size_t len );

/**
 * \brief最多读取“len”个字符，最多阻塞“timeout”秒。如果没有发生错误，则返回实际读取的金额。
 *
 * \注意：此函数的当前实现使用select（），如果文件描述符为\c FD_SETSIZE或更大，则返回错误。
 *
 * \param ctx Socket \param buf要写入的缓冲区\param len缓冲区的最大长度\param timeout等待数据的最大毫秒数0表示没有超时（永远等待）
 *
 * \return如果成功，接收的字节数。如果操作超时，则返回MBEDTLS_ERROR_SSL_TIMEOUT。如果被信号中断，则MBEDTLS_ERROR_SSL_WANT_READ。其他故障的另一个负错误代码（MBEDTLS_error_NET_xxx）。
 *
 * \注意：即使套接字设置为非阻塞，该函数也会阻塞（直到数据可用或超时）。处理非阻塞读取超时需要不同的策略。
 */
int mbedtls_net_recv_timeout( void *ctx, unsigned char *buf, size_t len,
                      uint32_t timeout );

/**
 * \brief关闭连接并释放相关数据
 *
 * \param ctx要关闭的上下文
 */
void mbedtls_net_close( mbedtls_net_context *ctx );

/**
 * \短暂优雅地关闭连接并释放相关数据
 *
 * \param ctx要释放的上下文
 */
void mbedtls_net_free( mbedtls_net_context *ctx );

#ifdef __cplusplus
}
#endif

#endif /* 网络套接字.h*/

