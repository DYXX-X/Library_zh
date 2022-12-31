/**
 * @file 套接字API（从非TCPIP线程使用）
 */

/*
 * 版权所有（c）2001-2004瑞典计算机科学研究所。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Adam Dunkels<adam@sics.se>
 *
 */


#ifndef LWIP_HDR_SOCKETS_H
#define LWIP_HDR_SOCKETS_H

#include "lwip/opt.h"
#include "sys/poll.h"
#if LWIP_SOCKET /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#include "lwip/ip_addr.h"
#include "lwip/netif.h"
#include "lwip/err.h"
#include "lwip/inet.h"
#include "lwip/errno.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 如果您的端口已经typedef的sa_family_t，请定义sa_family_t_DEFINED以防止此代码重新定义它。*/
#if !defined(sa_family_t) && !defined(SA_FAMILY_T_DEFINED)
typedef u8_t sa_family_t;
#endif
/* 如果您的端口已经typedef的in_port_t，请定义in_port_t_DEFINED以防止此代码重新定义它。*/
#if !defined(in_port_t) && !defined(IN_PORT_T_DEFINED)
typedef u16_t in_port_t;
#endif

#if LWIP_IPV4
/* 成员按网络字节顺序排列*/
struct sockaddr_in {
  u8_t            sin_len;
  sa_family_t     sin_family;
  in_port_t       sin_port;
  struct in_addr  sin_addr;
#define SIN_ZERO_LEN 8
  char            sin_zero[SIN_ZERO_LEN];
};
#endif /* LWIP_IPV4 */

#if LWIP_IPV6
struct sockaddr_in6 {
  u8_t            sin6_len;      /* 该结构的长度*/
  sa_family_t     sin6_family;   /* AF_INET6                    */
  in_port_t       sin6_port;     /* 传输层端口#*/
  u32_t           sin6_flowinfo; /* IPv6流信息*/
  struct in6_addr sin6_addr;     /* IPv6地址*/
  u32_t           sin6_scope_id; /* 范围接口集*/
};
#endif /* LWIP_IPV6 */

struct sockaddr {
  u8_t        sa_len;
  sa_family_t sa_family;
  char        sa_data[14];
};

struct sockaddr_storage {
  u8_t        s2_len;
  sa_family_t ss_family;
  char        s2_data1[2];
  u32_t       s2_data2[3];
#if LWIP_IPV6
  u32_t       s2_data3[3];
#endif /* LWIP_IPV6 */
};

/* 如果您的端口已经typedef的socklen_t，请定义socklen_t_DEFINED以防止此代码重新定义它。*/
#if !defined(socklen_t) && !defined(SOCKLEN_T_DEFINED)
typedef u32_t socklen_t;
#endif

#if !defined IOV_MAX
#define IOV_MAX 0xFFFF
#elif IOV_MAX > 0xFFFF
#error "IOV_MAX larger than supported by LwIP"
#endif /* IOV_MAX */

#if !defined(iovec)
struct iovec {
  void  *iov_base;
  size_t iov_len;
};
#endif

struct msghdr {
  void         *msg_name;
  socklen_t     msg_namelen;
  struct iovec *msg_iov;
  int           msg_iovlen;
  void         *msg_control;
  socklen_t     msg_controllen;
  int           msg_flags;
};

/* 结构msghdr->msg_flags位字段值*/
#define MSG_TRUNC   0x04
#define MSG_CTRUNC  0x08

/* RFC 3542，第20节：辅助数据*/
struct cmsghdr {
  socklen_t  cmsg_len;   /* 字节数，包括标头*/
  int        cmsg_level; /* 始发协议*/
  int        cmsg_type;  /* 协议特定类型*/
};
/* 数据段跟随标头和可能的填充，通常称为无符号字符cmsg_Data[]；*/

/* cmsg标头/数据对齐。注意：我们对齐原生字大小（16位拱门上的双倍字大小），因此结构不会放置在未对齐的地址。16位拱门需要双字以确保32位对齐，因为socklen_t可以是32位。如果我们有64位变量的cmsg数据，对齐将需要增加longlong*/
#define ALIGN_H(size) (((size) + sizeof(long) - 1U) & ~(sizeof(long)-1U))
#define ALIGN_D(size) ALIGN_H(size)

#define CMSG_FIRSTHDR(mhdr) \
          ((mhdr)->msg_controllen >= sizeof(struct cmsghdr) ? \
           (struct cmsghdr *)(mhdr)->msg_control : \
           (struct cmsghdr *)NULL)

#define CMSG_NXTHDR(mhdr, cmsg) \
        (((cmsg) == NULL) ? CMSG_FIRSTHDR(mhdr) : \
         (((u8_t *)(cmsg) + ALIGN_H((cmsg)->cmsg_len) \
                            + ALIGN_D(sizeof(struct cmsghdr)) > \
           (u8_t *)((mhdr)->msg_control) + (mhdr)->msg_controllen) ? \
          (struct cmsghdr *)NULL : \
          (struct cmsghdr *)((void*)((u8_t *)(cmsg) + \
                                      ALIGN_H((cmsg)->cmsg_len)))))

#define CMSG_DATA(cmsg) ((void*)((u8_t *)(cmsg) + \
                         ALIGN_D(sizeof(struct cmsghdr))))

#define CMSG_SPACE(length) (ALIGN_D(sizeof(struct cmsghdr)) + \
                            ALIGN_H(length))

#define CMSG_LEN(length) (ALIGN_D(sizeof(struct cmsghdr)) + \
                           length)

/* 设置套接字选项参数*/
#define IFNAMSIZ NETIF_NAMESIZE
struct ifreq {
  char ifr_name[IFNAMSIZ]; /* 接口名称*/
};

/* 套接字协议类型（TCP/UDP/RAW）*/
#define SOCK_STREAM     1
#define SOCK_DGRAM      2
#define SOCK_RAW        3

/*
 * 每个套接字的选项标志。这些必须与ip中的SOF_标志匹配。h（在init.c中检查）
 */
#define SO_REUSEADDR   0x0004 /* 允许重复使用本地地址*/
#define SO_KEEPALIVE   0x0008 /* 保持连接活动*/
#define SO_BROADCAST   0x0020 /* 允许发送和接收广播消息（请参阅IP_SOF_broadcast选项）*/


/*
 * 其他选项，不保留在so_options中。
 */
#define SO_DEBUG        0x0001 /* 未实现：启用调试信息记录*/
#define SO_ACCEPTCONN   0x0002 /* 套接字有listen（）*/
#define SO_DONTROUTE    0x0010 /* 未实现：仅使用接口地址*/
#define SO_USELOOPBACK  0x0040 /* 未实施：可能时绕过硬件*/
#define SO_LINGER       0x0080 /* 如果数据存在，请等待关闭*/
#define SO_DONTLINGER   ((int)(~SO_LINGER))
#define SO_OOBINLINE    0x0100 /* 未执行：将收到的OOB数据保留在行中*/
#define SO_REUSEPORT    0x0200 /* 未实现：允许本地地址和端口重用*/
#define SO_SNDBUF       0x1001 /* 未实现：发送缓冲区大小*/
#define SO_RCVBUF       0x1002 /* 接收缓冲区大小*/
#define SO_SNDLOWAT     0x1003 /* 未执行：发送低水位标记*/
#define SO_RCVLOWAT     0x1004 /* 未实施：接收低水位标记*/
#define SO_SNDTIMEO     0x1005 /* 发送超时*/
#define SO_RCVTIMEO     0x1006 /* 接收超时*/
#define SO_ERROR        0x1007 /* 获取错误状态并清除*/
#define SO_TYPE         0x1008 /* 获取套接字类型*/
#define SO_CONTIMEO     0x1009 /* 未实现：连接超时*/
#define SO_NO_CHECK     0x100a /* 不创建UDP校验和*/
#define SO_BINDTODEVICE 0x100b /* 绑定到设备*/

/*
 * 用于操纵延迟选项的结构。
 */
struct linger {
  int l_onoff;                /* 选项打开/关闭*/
  int l_linger;               /* 延迟时间（秒）*/
};

/*
 * 要应用于套接字本身的（get/set）sockopt（）的级别号。
 */
#define  SOL_SOCKET  0xfff    /* 套接字级别选项*/


#define AF_UNSPEC       0
#define AF_INET         2
#if LWIP_IPV6
#define AF_INET6        10
#else /* LWIP_IPV6 */
#define AF_INET6        AF_UNSPEC
#endif /* LWIP_IPV6 */
#define PF_INET         AF_INET
#define PF_INET6        AF_INET6
#define PF_UNSPEC       AF_UNSPEC

#define IPPROTO_IP      0
#define IPPROTO_ICMP    1
#define IPPROTO_TCP     6
#define IPPROTO_UDP     17
#if LWIP_IPV6
#define IPPROTO_IPV6    41
#define IPPROTO_ICMPV6  58
#endif /* LWIP_IPV6 */
#define IPPROTO_UDPLITE 136
#define IPPROTO_RAW     255

/* 我们可以用于发送和接收的标志。*/
#define MSG_PEEK       0x01    /* 偷看传入的消息*/
#define MSG_WAITALL    0x02    /* 未实现：请求函数块直到可以返回请求的全部数据量*/
#define MSG_OOB        0x04    /* 未实现：请求带外数据。带外数据的意义和语义是特定于协议的*/
#define MSG_DONTWAIT   0x08    /* 仅此操作的非阻塞i/o*/
#define MSG_MORE       0x10    /* 发件人将发送更多*/
#define MSG_NOSIGNAL   0x20    /* 未实现：如果在不再连接的面向流的套接字上尝试发送，则请求不发送SIGPIPE信号。*/


/*
 * IPPROTO_IP级选项
 */
#define IP_TOS             1
#define IP_TTL             2
#define IP_PKTINFO         8

#if LWIP_TCP
/*
 * IPPROTO_TCP级别的选项
 */
#define TCP_NODELAY    0x01    /* 不要延迟发送以合并数据包*/
#define TCP_KEEPALIVE  0x02    /* 在pcb空闲时发送KEEPALIVE探测->keep_idle毫秒*/
#define TCP_KEEPIDLE   0x03    /* set pcb->keep_idle-与TCP_KEEPALIVE相同，但使用秒获取/setsockopt*/
#define TCP_KEEPINTVL  0x04    /* set pcb->keep_intvl-使用秒获取/setsockopt*/
#define TCP_KEEPCNT    0x05    /* set pcb->keep_cnt-使用为get/setsockopt发送的探测数*/
#endif /* LWIP_TCP */

#if LWIP_IPV6
/*
 * IPPROTO_IPV6级别的选项
 */
#define IPV6_CHECKSUM       7  /* RFC3542:计算并插入原始套接字的ICMPv6校验和。*/
#define IPV6_V6ONLY         27 /* RFC3493：布尔控制，将AF_INET6套接字仅限制为IPv6通信。*/
#endif /* LWIP_IPV6 */

#if LWIP_UDP && LWIP_UDPLITE
/*
 * IPPROTO_UDPLITE级别的选项
 */
#define UDPLITE_SEND_CSCOV 0x01 /* 发送方校验和覆盖*/
#define UDPLITE_RECV_CSCOV 0x02 /* 最小接收机校验和覆盖*/
#endif /* LWIP_UDP && LWIP_UDPLITE*/


#if LWIP_MULTICAST_TX_OPTIONS
/*
 * UDP多播流量处理的选项和类型
 */
#define IP_MULTICAST_TTL   5
#define IP_MULTICAST_IF    6
#define IP_MULTICAST_LOOP  7
#endif /* LWIP_MULTICAST_TX_OPTIONS */

#if LWIP_IGMP
/*
 * 与多播成员资格相关的选项和类型
 */
#define IP_ADD_MEMBERSHIP  3
#define IP_DROP_MEMBERSHIP 4

typedef struct ip_mreq {
    struct in_addr imr_multiaddr; /* 组的IP多播地址*/
    struct in_addr imr_interface; /* 接口的本地IP地址*/
} ip_mreq;
#endif /* LWIP_IGMP */

#if LWIP_IPV4
struct in_pktinfo {
  unsigned int   ipi_ifindex;  /* 接口索引*/
  struct in_addr ipi_addr;     /* 目标（来自标头）地址*/
};
#endif /* LWIP_IPV4 */

#if LWIP_IPV6_MLD
/*
 * 与IPv6多播成员资格相关的选项和类型
 */
#define IPV6_JOIN_GROUP      12
#define IPV6_ADD_MEMBERSHIP  IPV6_JOIN_GROUP
#define IPV6_LEAVE_GROUP     13
#define IPV6_DROP_MEMBERSHIP IPV6_LEAVE_GROUP

#if ESP_IPV6
#define IPV6_MULTICAST_IF    0x300
#define IPV6_MULTICAST_HOPS  0x301
#define IPV6_MULTICAST_LOOP  0x302
#endif

typedef struct ipv6_mreq {
  struct in6_addr ipv6mr_multiaddr; /*  IPv6多播地址*/
  unsigned int    ipv6mr_interface; /*  接口索引，或0*/
} ipv6_mreq;
#endif /* LWIP_IPV6_MLD */

/*
 * 服务类型提供所需服务质量的抽象参数的指示。当通过特定网络发送数据报时，这些参数将用于指导实际服务参数的选择。一些网络提供服务优先级，以某种方式将高优先级流量视为比其他流量更重要（通常在高负载时只接受高于某个优先级的流量）。主要的选择是在低延迟、高可靠性和高吞吐量之间进行三方权衡。延迟、吞吐量和可靠性指示的使用可能会增加服务的成本（在某种意义上）。在许多网络中，这些参数中的一个性能更好，另一个性能更差。除极不寻常的情况外，这三种指示中最多应设置两种。
 */
#define IPTOS_TOS_MASK          0x1E
#define IPTOS_TOS(tos)          ((tos) & IPTOS_TOS_MASK)
#define IPTOS_LOWDELAY          0x10
#define IPTOS_THROUGHPUT        0x08
#define IPTOS_RELIABILITY       0x04
#define IPTOS_LOWCOST           0x02
#define IPTOS_MINCOST           IPTOS_LOWCOST

/*
 * 网络控制优先级指定仅用于网络中。该名称的实际使用和控制取决于每个网络。网络间控制标识仅供网关控制发起者使用。如果这些优先标识的实际使用与特定网络有关，则该网络有责任控制这些优先标识。
 */
#define IPTOS_PREC_MASK                 0xe0
#define IPTOS_PREC(tos)                ((tos) & IPTOS_PREC_MASK)
#define IPTOS_PREC_NETCONTROL           0xe0
#define IPTOS_PREC_INTERNETCONTROL      0xc0
#define IPTOS_PREC_CRITIC_ECP           0xa0
#define IPTOS_PREC_FLASHOVERRIDE        0x80
#define IPTOS_PREC_FLASH                0x60
#define IPTOS_PREC_IMMEDIATE            0x40
#define IPTOS_PREC_PRIORITY             0x20
#define IPTOS_PREC_ROUTINE              0x00


/*
 * 用于ioctlsocket（）的命令，取自BSD文件fcntl.h.lwip_ioctl，目前仅支持FIONREAD和FIONBIO
 *
 * Ioctl的命令编码在低位字中，任何输入或输出参数的大小都在高位字中。高位字的高2位用于编码参数的输入/输出状态；目前，我们将参数限制为最多128字节。
 */
#if !defined(FIONREAD) || !defined(FIONBIO)
#define IOCPARM_MASK    0x7fU           /* 参数必须小于128字节*/
#define IOC_VOID        0x20000000UL    /* 无参数*/
#define IOC_OUT         0x40000000UL    /* 复制输出参数*/
#define IOC_IN          0x80000000UL    /* 复制入参数*/
#define IOC_INOUT       (IOC_IN|IOC_OUT)
                                        /* 0x20000000区分新旧ioctl*/
#define _IO(x,y)        ((long)(IOC_VOID|((x)<<8)|(y)))

#define _IOR(x,y,t)     ((long)(IOC_OUT|((sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y)))

#define _IOW(x,y,t)     ((long)(IOC_IN|((sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y)))
#endif /* !已定义（FIONREAD）||！定义（FIONBIO）*/

#ifndef FIONREAD
#define FIONREAD    _IOR('f', 127, unsigned long) /* 获取要读取的字节数*/
#endif
#ifndef FIONBIO
#define FIONBIO     _IOW('f', 126, unsigned long) /* 设置/清除非阻塞i/o*/
#endif

/* 套接字I/O控制：未实现*/
#ifndef SIOCSHIWAT
#define SIOCSHIWAT  _IOW('s',  0, unsigned long)  /* 设置高水位线*/
#define SIOCGHIWAT  _IOR('s',  1, unsigned long)  /* 获取高水位线*/
#define SIOCSLOWAT  _IOW('s',  2, unsigned long)  /* 设置低水位线*/
#define SIOCGLOWAT  _IOR('s',  3, unsigned long)  /* 获取低水位线*/
#define SIOCATMARK  _IOR('s',  7, unsigned long)  /* 在oob标记？*/
#endif

/* fnctl命令*/
#ifndef F_GETFL
#define F_GETFL 3
#endif
#ifndef F_SETFL
#define F_SETFL 4
#endif

/* fnctl的文件状态标志和文件访问模式，这些是int中的位。*/
#ifndef O_NONBLOCK
#define O_NONBLOCK  1 /* 非阻塞I/O*/
#endif
#ifndef O_NDELAY
#define O_NDELAY    O_NONBLOCK /* 与O_NONBLOCK相同，用于兼容性*/
#endif
#ifndef O_RDONLY
#define O_RDONLY    2
#endif
#ifndef O_WRONLY
#define O_WRONLY    4
#endif
#ifndef O_RDWR
#define O_RDWR      (O_RDONLY|O_WRONLY)
#endif

#ifndef SHUT_RD
  #define SHUT_RD   0
  #define SHUT_WR   1
  #define SHUT_RDWR 2
#endif

/* 用于lwip_select的FD_SET*/
#ifndef FD_SET
#undef  FD_SETSIZE
/* 使FD_SETSIZE与套接字中的NUM_SOCKETS匹配。c*/
#define FD_SETSIZE    MEMP_NUM_NETCONN
#define LWIP_SELECT_MAXNFDS (FD_SETSIZE + LWIP_SOCKET_OFFSET)
#define FDSETSAFESET(n, code) do { \
  if (((n) - LWIP_SOCKET_OFFSET < MEMP_NUM_NETCONN) && (((int)(n) - LWIP_SOCKET_OFFSET) >= 0)) { \
  code; }} while(0)
#define FDSETSAFEGET(n, code) (((n) - LWIP_SOCKET_OFFSET < MEMP_NUM_NETCONN) && (((int)(n) - LWIP_SOCKET_OFFSET) >= 0) ?\
  (code) : 0)
#define FD_SET(n, p)  FDSETSAFESET(n, (p)->fd_bits[((n)-LWIP_SOCKET_OFFSET)/8] = (u8_t)((p)->fd_bits[((n)-LWIP_SOCKET_OFFSET)/8] |  (1 << (((n)-LWIP_SOCKET_OFFSET) & 7))))
#define FD_CLR(n, p)  FDSETSAFESET(n, (p)->fd_bits[((n)-LWIP_SOCKET_OFFSET)/8] = (u8_t)((p)->fd_bits[((n)-LWIP_SOCKET_OFFSET)/8] & ~(1 << (((n)-LWIP_SOCKET_OFFSET) & 7))))
#define FD_ISSET(n,p) FDSETSAFEGET(n, (p)->fd_bits[((n)-LWIP_SOCKET_OFFSET)/8] &   (1 << (((n)-LWIP_SOCKET_OFFSET) & 7)))
#define FD_ZERO(p)    memset((void*)(p), 0, sizeof(*(p)))

typedef struct fd_set
{
  unsigned char fd_bits [(FD_SETSIZE+7)/8];
} fd_set;

#elif FD_SETSIZE < (LWIP_SOCKET_OFFSET + MEMP_NUM_NETCONN)
#error "external FD_SETSIZE too small for number of sockets"
#else
#define LWIP_SELECT_MAXNFDS FD_SETSIZE
#endif /* FD_SET */

/* 轮询相关的定义和类型*/
/* @todo：找到更好的方法来保护这些定义和类型的定义（如果已经定义）*/
#if !defined(POLLIN) && !defined(POLLOUT)
#define POLLIN     0x1
#define POLLOUT    0x2
#define POLLERR    0x4
#define POLLNVAL   0x8
/* 以下值未实现*/
#define POLLRDNORM 0x10
#define POLLRDBAND 0x20
#define POLLPRI    0x40
#define POLLWRNORM 0x80
#define POLLWRBAND 0x100
#define POLLHUP    0x200
#ifdef NO_POLLFD
typedef unsigned int nfds_t;
struct pollfd
{
  int fd;
  short events;
  short revents;
};
#endif/* NO_POLLFD*/
#endif

/**LWIP_TIMEVAL_PRIVATE：如果要使用系统提供的结构TIMEVAL，请将其设置为0并包含<sys/time。h> 单位cc。小时*/
#ifndef LWIP_TIMEVAL_PRIVATE
#define LWIP_TIMEVAL_PRIVATE 1
#endif

#if LWIP_TIMEVAL_PRIVATE
struct timeval {
  long    tv_sec;         /* 秒*/
  long    tv_usec;        /* 和微秒*/
};
#endif /* LWIP_TIMEVAL_PRIVATE */

#define lwip_socket_init() /* 兼容性定义，不需要初始化。*/
void lwip_socket_thread_init(void); /* LWIP_NETCONN_SEM_PER_THREAD==1：初始化线程本地信号量*/
void lwip_socket_thread_cleanup(void); /* LWIP_NETCONN_SEM_PER_THREAD==1：销毁线程本地信号量*/

#if LWIP_COMPAT_SOCKETS == 2
/* 这有助于代码解析器/代码完成，因为没有定义的COMPAT函数*/
#define lwip_accept       accept
#define lwip_bind         bind
#define lwip_shutdown     shutdown
#define lwip_getpeername  getpeername
#define lwip_getsockname  getsockname
#define lwip_setsockopt   setsockopt
#define lwip_getsockopt   getsockopt
#define lwip_close        closesocket
#define lwip_connect      connect
#define lwip_listen       listen
#define lwip_recv         recv
#define lwip_recvmsg      recvmsg
#define lwip_recvfrom     recvfrom
#define lwip_send         send
#define lwip_sendmsg      sendmsg
#define lwip_sendto       sendto
#define lwip_socket       socket
#if LWIP_SOCKET_SELECT
#define lwip_select       select
#endif
#if LWIP_SOCKET_POLL
#define lwip_poll         poll
#endif
#define lwip_ioctl        ioctlsocket
#define lwip_inet_ntop    inet_ntop
#define lwip_inet_pton    inet_pton

#if LWIP_POSIX_SOCKETS_IO_NAMES
#define lwip_read         read
#define lwip_readv        readv
#define lwip_write        write
#define lwip_writev       writev
#undef lwip_close
#define lwip_close        close
#define closesocket(s)    close(s)
int fcntl(int s, int cmd, ...);
#undef lwip_ioctl
#define lwip_ioctl        ioctl
#define ioctlsocket       ioctl
#endif /* LWIP_POSIX_SOCKETS_IO_NAMES */
#endif /* LWIP_COMPAT_SOCKETS == 2 */

int lwip_accept(int s, struct sockaddr *addr, socklen_t *addrlen);
int lwip_bind(int s, const struct sockaddr *name, socklen_t namelen);
int lwip_shutdown(int s, int how);
int lwip_getpeername (int s, struct sockaddr *name, socklen_t *namelen);
int lwip_getsockname (int s, struct sockaddr *name, socklen_t *namelen);
int lwip_getsockopt (int s, int level, int optname, void *optval, socklen_t *optlen);
int lwip_setsockopt (int s, int level, int optname, const void *optval, socklen_t optlen);
int lwip_close(int s);
int lwip_connect(int s, const struct sockaddr *name, socklen_t namelen);
int lwip_listen(int s, int backlog);
ssize_t lwip_recv(int s, void *mem, size_t len, int flags);
ssize_t lwip_read(int s, void *mem, size_t len);
ssize_t lwip_readv(int s, const struct iovec *iov, int iovcnt);
ssize_t lwip_recvfrom(int s, void *mem, size_t len, int flags,
      struct sockaddr *from, socklen_t *fromlen);
ssize_t lwip_recvmsg(int s, struct msghdr *message, int flags);
ssize_t lwip_send(int s, const void *dataptr, size_t size, int flags);
ssize_t lwip_sendmsg(int s, const struct msghdr *message, int flags);
ssize_t lwip_sendto(int s, const void *dataptr, size_t size, int flags,
    const struct sockaddr *to, socklen_t tolen);
int lwip_socket(int domain, int type, int protocol);
ssize_t lwip_write(int s, const void *dataptr, size_t size);
ssize_t lwip_writev(int s, const struct iovec *iov, int iovcnt);
#if LWIP_SOCKET_SELECT
int lwip_select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset,
                struct timeval *timeout);
#endif
#if LWIP_SOCKET_POLL
int lwip_poll(struct pollfd *fds, nfds_t nfds, int timeout);
#endif
int lwip_ioctl(int s, long cmd, void *argp);
int lwip_fcntl(int s, int cmd, int val);
const char *lwip_inet_ntop(int af, const void *src, char *dst, socklen_t size);
int lwip_inet_pton(int af, const char *src, void *dst);

#if LWIP_COMPAT_SOCKETS
#if LWIP_COMPAT_SOCKETS != 2

#if ESP_SOCKET
static inline int accept(int s,struct sockaddr *addr,socklen_t *addrlen)
{ return lwip_accept(s,addr,addrlen); }
static inline int bind(int s,const struct sockaddr *name, socklen_t namelen)
{ return lwip_bind(s,name,namelen); }
static inline int shutdown(int s,int how)
{ return lwip_shutdown(s,how); }
static inline int getpeername(int s,struct sockaddr *name,socklen_t *namelen)
{ return lwip_getpeername(s,name,namelen); }
static inline int getsockname(int s,struct sockaddr *name,socklen_t *namelen)
{ return lwip_getsockname(s,name,namelen); }
static inline int setsockopt(int s,int level,int optname,const void *opval,socklen_t optlen)
{ return lwip_setsockopt(s,level,optname,opval,optlen); }
static inline int getsockopt(int s,int level,int optname,void *opval,socklen_t *optlen)
{ return lwip_getsockopt(s,level,optname,opval,optlen); }
static inline int closesocket(int s)
{ return lwip_close(s); }
static inline int connect(int s,const struct sockaddr *name,socklen_t namelen)
{ return lwip_connect(s,name,namelen); }
static inline int listen(int s,int backlog)
{ return lwip_listen(s,backlog); }
static inline ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags)
{ return lwip_recvmsg(sockfd, msg, flags); } 
static inline ssize_t recv(int s,void *mem,size_t len,int flags)
{ return lwip_recv(s,mem,len,flags); }
static inline ssize_t recvfrom(int s,void *mem,size_t len,int flags,struct sockaddr *from,socklen_t *fromlen)
{ return lwip_recvfrom(s,mem,len,flags,from,fromlen); }
static inline ssize_t send(int s,const void *dataptr,size_t size,int flags)
{ return lwip_send(s,dataptr,size,flags); }
static inline ssize_t sendmsg(int s,const struct msghdr *message,int flags)
{ return lwip_sendmsg(s,message,flags); }
static inline ssize_t sendto(int s,const void *dataptr,size_t size,int flags,const struct sockaddr *to,socklen_t tolen)
{ return lwip_sendto(s,dataptr,size,flags,to,tolen); }
static inline int socket(int domain,int type,int protocol)
{ return lwip_socket(domain,type,protocol); }
#ifndef ESP_HAS_SELECT
static inline int select(int maxfdp1,fd_set *readset,fd_set *writeset,fd_set *exceptset,struct timeval *timeout)
{ return lwip_select(maxfdp1,readset,writeset,exceptset,timeout); }
#endif /* ESP_HAS_SELECT */
static inline int ioctlsocket(int s,long cmd,void *argp)
{ return lwip_ioctl(s,cmd,argp); }

#if LWIP_POSIX_SOCKETS_IO_NAMES
static inline ssize_t read(int s,void *mem,size_t len)
{ return lwip_read(s,mem,len); }
static inline ssize_t write(int s,const void *dataptr,size_t len)
{ return lwip_write(s,dataptr,len); }
static inline ssize_t writev(int s,const struct iovec *iov,int iovcnt)
{ return lwip_writev(s,iov,iovcnt); }
static inline int close(int s)
{ return lwip_close(s); }
static inline int fcntl(int s,int cmd,int val)
{ return lwip_fcntl(s,cmd,val); }
static inline int ioctl(int s,long cmd,void *argp)
{ return lwip_ioctl(s,cmd,argp); }
#endif /* LWIP_POSIX_SOCKETS_IO_NAMES */

#else

/**@in组插座*/
#define accept(s,addr,addrlen)                    lwip_accept(s,addr,addrlen)
/**@in组插座*/
#define bind(s,name,namelen)                      lwip_bind(s,name,namelen)
/**@in组插座*/
#define shutdown(s,how)                           lwip_shutdown(s,how)
/**@in组插座*/
#define getpeername(s,name,namelen)               lwip_getpeername(s,name,namelen)
/**@in组插座*/
#define getsockname(s,name,namelen)               lwip_getsockname(s,name,namelen)
/**@in组插座*/
#define setsockopt(s,level,optname,opval,optlen)  lwip_setsockopt(s,level,optname,opval,optlen)
/**@in组插座*/
#define getsockopt(s,level,optname,opval,optlen)  lwip_getsockopt(s,level,optname,opval,optlen)
/**@in组插座*/
#define closesocket(s)                            lwip_close(s)
/**@in组插座*/
#define connect(s,name,namelen)                   lwip_connect(s,name,namelen)
/**@in组插座*/
#define listen(s,backlog)                         lwip_listen(s,backlog)
/**@in组插座*/
#define recv(s,mem,len,flags)                     lwip_recv(s,mem,len,flags)
/**@in组插座*/
#define recvmsg(s,message,flags)                  lwip_recvmsg(s,message,flags)
/**@in组插座*/
#define recvfrom(s,mem,len,flags,from,fromlen)    lwip_recvfrom(s,mem,len,flags,from,fromlen)
/**@in组插座*/
#define send(s,dataptr,size,flags)                lwip_send(s,dataptr,size,flags)
/**@in组插座*/
#define sendmsg(s,message,flags)                  lwip_sendmsg(s,message,flags)
/**@in组插座*/
#define sendto(s,dataptr,size,flags,to,tolen)     lwip_sendto(s,dataptr,size,flags,to,tolen)
/**@in组插座*/
#define socket(domain,type,protocol)              lwip_socket(domain,type,protocol)
#if LWIP_SOCKET_SELECT
/**@in组插座*/
#define select(maxfdp1,readset,writeset,exceptset,timeout)     lwip_select(maxfdp1,readset,writeset,exceptset,timeout)
#endif
#if LWIP_SOCKET_POLL
/**@in组插座*/
#define poll(fds,nfds,timeout)                    lwip_poll(fds,nfds,timeout)
#endif
/**@in组插座*/
#define ioctlsocket(s,cmd,argp)                   lwip_ioctl(s,cmd,argp)

#if LWIP_POSIX_SOCKETS_IO_NAMES
/**@in组插座*/
#define read(s,mem,len)                           lwip_read(s,mem,len)
/**@in组插座*/
#define readv(s,iov,iovcnt)                       lwip_readv(s,iov,iovcnt)
/**@in组插座*/
#define write(s,dataptr,len)                      lwip_write(s,dataptr,len)
/**@in组插座*/
#define writev(s,iov,iovcnt)                      lwip_writev(s,iov,iovcnt)
/**@in组插座*/
#define close(s)                                  lwip_close(s)
/**@in组插座*/
#define fcntl(s,cmd,val)                          lwip_fcntl(s,cmd,val)
/**@in组插座*/
#define ioctl(s,cmd,argp)                         lwip_ioctl(s,cmd,argp)
#endif /* LWIP_POSIX_SOCKETS_IO_NAMES */

#endif /* ESP_SOCKET */
#endif /* LWIP_COMPAT_SOCKETS != 2 */

#if ESP_SOCKET                                                          
#if LWIP_COMPAT_SOCKET_INET == 1
/* 某些库在inet_…作为宏时存在问题，因此请使用此定义来声明正常函数*/
static inline const char *inet_ntop(int af, const void *src, char *dst, socklen_t size)
{ return lwip_inet_ntop(af, src, dst, size);  }
static inline int inet_pton(int af, const char *src, void *dst)
{ return lwip_inet_pton(af, src, dst); }   
#else
/* 默认情况下，回退到原始inet_…宏*/
# define inet_ntop(a,b,c,d) lwip_inet_ntop(a,b,c,d) 
# define inet_pton(a,b,c)   lwip_inet_pton(a,b,c)   
#endif /* LWIP_COMPAT_SOCKET_INET */

#endif /* ESP_SOCKET */
#endif /* LWIP_COMPAT_SOCKETS */

#ifdef __cplusplus
}
#endif

#endif /* LWIP_SOCKET */

#endif /* LWIP_HDR_SOCKETS_H */

