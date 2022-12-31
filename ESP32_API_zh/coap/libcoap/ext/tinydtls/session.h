/*******************************************************************************
 * 版权所有（c）2011-2019 Olaf Bergmann（TZI）和其他人。保留所有权利。本程序和随附材料根据本发行版附带的Eclipse公共许可证v1.0和Eclipse发行许可证v1.1的条款提供。
 *
 * Eclipse公共许可证位于http://www.eclipse.org/legal/epl-v10.htmlEclipse发行许可证在http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * 贡献者：Olaf Bergmann-初始API和实现
 *
 *******************************************************************************/

#ifndef _DTLS_SESSION_H_
#define _DTLS_SESSION_H_

#include <string.h>

#include "tinydtls.h"
#include "global.h"

#ifdef WITH_CONTIKI
#include "ip/uip.h"
typedef struct {
  unsigned char size;
  uip_ipaddr_t addr;
  unsigned short port;
  int ifindex;
} session_t;
 /* TODO:添加对套接字上RIOT的支持*/
#elif defined(WITH_RIOT_GNRC)
#include "net/ipv6/addr.h"
typedef struct {
  unsigned char size;
  ipv6_addr_t addr;
  unsigned short port;
  int ifindex;
} session_t;
#else /* ! WITH_CONTIKI && ! WITH_RIOT_GNRC */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct {
  socklen_t size;		/**<地址大小*/
  union {
    struct sockaddr     sa;
    struct sockaddr_storage st;
    struct sockaddr_in  sin;
    struct sockaddr_in6 sin6;
  } addr;
  int ifindex;
} session_t;
#endif /* ! WITH_CONTIKI && ! WITH_RIOT_GNRC */

/** 
 * Resets the given session_t object @p sess设置为默认值。特别是，成员rlen必须初始化为可用于存储地址的大小。
 * 
 * @param sess 要初始化的session_t对象。
 */
void dtls_session_init(session_t *sess);

#if !(defined (WITH_CONTIKI)) && !(defined (RIOT_VERSION))
/**
 * 为给定地址创建新的：：session_t。
 *
 * @param addr 应存储在：：session_t中的地址。
 * @param addrlen @p地址的长度。
 * @return 出现错误时，新会话或@c为NULL。
 */
session_t* dtls_new_session(struct sockaddr *addr, socklen_t addrlen);

/**
 * 使用：：dtls_new_session释放为会话分配的内存。
 *
 * @param sess 指向应释放分配内存的会话的指针。
 */
void dtls_free_session(session_t *sess);

/**
 * 提取给定：：session_t的地址。
 *
 * @param sess 要提取地址的会话。
 * @param addrlen 指向应存储地址长度的内存位置的指针。
 * @return 地址或@c NULL（如果@p sess为@c NULL）。
 */
struct sockaddr* dtls_session_addr(session_t *sess, socklen_t *addrlen);
#endif /* !（定义（WITH_CONTIKI））&&！（定义（RIOT_VERSION））*/

/**
 * 比较给定的会话对象。此函数返回@c 0
 * when @p a和@p b不同，否则为@c 1。
 */
int dtls_session_equals(const session_t *a, const session_t *b);

#endif /* _DTLS_SESSION_H_ */

