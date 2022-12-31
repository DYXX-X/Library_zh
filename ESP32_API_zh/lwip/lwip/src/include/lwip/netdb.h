/**
 * @file NETDB API（套接字）
 */

/*
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Simon Goldschmidt
 *
 */
#ifndef LWIP_HDR_NETDB_H
#define LWIP_HDR_NETDB_H

#include "lwip/opt.h"

#if LWIP_DNS && LWIP_SOCKET

#include "lwip/arch.h"
#include "lwip/inet.h"
#include "lwip/sockets.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 一些很少使用的选项*/
#ifndef LWIP_DNS_API_DECLARE_H_ERRNO
#define LWIP_DNS_API_DECLARE_H_ERRNO  1
#endif

#ifndef LWIP_DNS_API_DEFINE_ERRORS
#define LWIP_DNS_API_DEFINE_ERRORS    1
#endif

#ifndef LWIP_DNS_API_DEFINE_FLAGS
#define LWIP_DNS_API_DEFINE_FLAGS     1
#endif

#ifndef LWIP_DNS_API_DECLARE_STRUCTS
#define LWIP_DNS_API_DECLARE_STRUCTS  1
#endif

#if LWIP_DNS_API_DEFINE_ERRORS
/**DNS API函数使用的错误，h_errno可以是其中之一*/
#define EAI_NONAME      200
#define EAI_SERVICE     201
#define EAI_FAIL        202
#define EAI_MEMORY      203
#define EAI_FAMILY      204

#define HOST_NOT_FOUND  210
#define NO_DATA         211
#define NO_RECOVERY     212
#define TRY_AGAIN       213
#endif /* LWIP_DNS_API_DEFINE_ERRORS */

#if LWIP_DNS_API_DEFINE_FLAGS
/* 结构addrinfo的输入标志*/
#define AI_PASSIVE      0x01
#define AI_CANONNAME    0x02
#define AI_NUMERICHOST  0x04
#define AI_NUMERICSERV  0x08
#define AI_V4MAPPED     0x10
#define AI_ALL          0x20
#define AI_ADDRCONFIG   0x40
#endif /* LWIP_DNS_API_DEFINE_FLAGS */

#if LWIP_DNS_API_DECLARE_STRUCTS
struct hostent {
    char  *h_name;      /* 主机的正式名称。*/
    char **h_aliases;   /* 指向替代主机名的指针数组的指针，以空指针结尾。*/
    int    h_addrtype;  /* 地址类型。*/
    int    h_length;    /* 地址的长度（以字节为单位）。*/
    char **h_addr_list; /* 指向指向主机网络地址（按网络字节顺序）的指针数组的指针，以空指针结尾。*/
#define h_addr h_addr_list[0] /* 用于向后兼容*/
};

struct addrinfo {
    int               ai_flags;      /* 输入标志。*/
    int               ai_family;     /* 套接字的地址系列。*/
    int               ai_socktype;   /* 插座类型。*/
    int               ai_protocol;   /* 套接字协议。*/
    socklen_t         ai_addrlen;    /* 套接字地址的长度。*/
    struct sockaddr  *ai_addr;       /* 套接字的套接字地址。*/
    char             *ai_canonname;  /* 服务位置的规范名称。*/
    struct addrinfo  *ai_next;       /* 指向列表中下一个的指针。*/
};
#endif /* LWIP_DNS_API_DECLARE_STRUCTS */

#define NETDB_ELEM_SIZE           (sizeof(struct addrinfo) + sizeof(struct sockaddr_storage) + DNS_MAX_NAME_LENGTH + 1)

#if LWIP_DNS_API_DECLARE_H_ERRNO
/* DNS API函数设置的应用程序可访问错误代码*/
extern int h_errno;
#endif /* LWIP_DNS_API_DECLARE_H_ERRNO*/

struct hostent *lwip_gethostbyname(const char *name);
int lwip_gethostbyname_r(const char *name, struct hostent *ret, char *buf,
                size_t buflen, struct hostent **result, int *h_errnop);
void lwip_freeaddrinfo(struct addrinfo *ai);
int lwip_getaddrinfo(const char *nodename,
       const char *servname,
       const struct addrinfo *hints,
       struct addrinfo **res);

#if LWIP_COMPAT_SOCKETS
#if ESP_SOCKET
#if LWIP_COMPAT_SOCKET_ADDR == 1
/* 某些库在inet_…作为宏时存在问题，因此请使用此定义来声明正常函数*/
static inline int gethostbyname_r(const char *name, struct hostent *ret, char *buf, size_t buflen, struct hostent **result, int *h_errnop)
{ return lwip_gethostbyname_r(name, ret, buf, buflen, result, h_errnop); }
static inline struct hostent *gethostbyname(const char *name)
{ return lwip_gethostbyname(name); }
static inline void freeaddrinfo(struct addrinfo *ai)
{ lwip_freeaddrinfo(ai); }
static inline int getaddrinfo(const char *nodename, const char *servname, const struct addrinfo *hints, struct addrinfo **res)
{ return lwip_getaddrinfo(nodename, servname, hints, res); }
#else
/* 默认情况下，回退到原始inet_…宏*/

/**@ingroup netdbapi*/
#define gethostbyname(name) lwip_gethostbyname(name)
/**@ingroup netdbapi*/
#define gethostbyname_r(name, ret, buf, buflen, result, h_errnop) \
       lwip_gethostbyname_r(name, ret, buf, buflen, result, h_errnop)
/**@ingroup netdbapi*/
#define freeaddrinfo(addrinfo) lwip_freeaddrinfo(addrinfo)
/**@ingroup netdbapi*/
#define getaddrinfo(nodname, servname, hints, res) \
       lwip_getaddrinfo(nodname, servname, hints, res)
#endif /* LWIP_COMPAT_SOCKET_ADDR == 1 */

#else /* ESP_SOCKET */

/**@ingroup netdbapi*/
#define gethostbyname(name) lwip_gethostbyname(name)
/**@ingroup netdbapi*/
#define gethostbyname_r(name, ret, buf, buflen, result, h_errnop) \
       lwip_gethostbyname_r(name, ret, buf, buflen, result, h_errnop)
/**@ingroup netdbapi*/
#define freeaddrinfo(addrinfo) lwip_freeaddrinfo(addrinfo)
/**@ingroup netdbapi*/
#define getaddrinfo(nodname, servname, hints, res) \
       lwip_getaddrinfo(nodname, servname, hints, res)

#endif /* ESP_SOCKET */
#endif /* LWIP_COMPAT_SOCKETS */

#ifdef __cplusplus
}
#endif

#endif /* LWIP_DNS && LWIP_SOCKET */

#endif /* LWIP_HDR_NETDB_H */

