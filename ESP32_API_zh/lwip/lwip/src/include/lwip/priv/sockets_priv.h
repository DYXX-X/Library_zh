/**
 * @file 套接字API内部实现（不在应用程序代码中使用）
 */

/*
 * 版权所有（c）2017 Joel Cunningham，Garmin International，Inc<joel.cunningham@garmin.com>保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：乔尔·坎宁安<joel.cunningham@me.com>
 *
 */
#ifndef LWIP_HDR_SOCKETS_PRIV_H
#define LWIP_HDR_SOCKETS_PRIV_H

#include "lwip/opt.h"

#if LWIP_SOCKET /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NUM_SOCKETS MEMP_NUM_NETCONN

/** 这对于在同一套接字上选择超过255个线程的罕见情况是可重写的。。。
 */
#ifndef SELWAIT_T
#define SELWAIT_T u8_t
#endif

union lwip_sock_lastdata {
  struct netbuf *netbuf;
  struct pbuf *pbuf;
};

/**包含用于套接字的所有内部指针和状态*/
struct lwip_sock {
  /**套接字当前构建在netconn上，每个套接字都有一个netconn*/
  struct netconn *conn;
  /**上次读取留下的数据*/
  union lwip_sock_lastdata lastdata;
#if LWIP_SOCKET_SELECT || LWIP_SOCKET_POLL
  /**接收数据的次数，由event_callback（）设置，由receive和select函数测试*/
  s16_t rcvevent;
  /**数据被确认的次数（空闲发送缓冲区），由event_callback（）设置，由select测试*/
  u16_t sendevent;
  /**此套接字发生错误，由event_callback（）设置，由select测试*/
  u16_t errevent;
  /**使用select计算等待此套接字的线程数*/
  SELWAIT_T select_waiting;
#endif /* LWIP_SOCKET_SELECT || LWIP_SOCKET_POLL */
#if LWIP_NETCONN_FULLDUPLEX
  /* 使用结构lwip_sock（而不是“int”）的线程数计数器*/
  u8_t fd_used;
  /* 挂起的关闭/删除操作的状态*/
  u8_t fd_free_pending;
#define LWIP_SOCK_FD_FREE_TCP  1
#define LWIP_SOCK_FD_FREE_FREE 2
#endif

#if ESP_LWIP_LOCK
  sys_mutex_t lock;
#endif

};

#ifndef set_errno
#define set_errno(err) do { if (err) { errno = (err); } } while(0)
#endif

#if !LWIP_TCPIP_CORE_LOCKING
/**setsockopt/getsockopt使用的最大optlen*/
#define LWIP_SETGETSOCKOPT_MAXOPTLEN LWIP_MAX(16, sizeof(struct ifreq))

/**此结构用于将数据传递给在tcpip_thread上下文中运行的set/getsockoptit_internal函数（仅允许void*）*/
struct lwip_setgetsockopt_data {
  /**要更改选项的套接字索引*/
  int s;
  /**处理选项的级别*/
  int level;
  /**要处理的选项的名称*/
  int optname;
  /**set：value以设置要获取的选项：该选项的值存储在此处*/
#if LWIP_MPU_COMPATIBLE
  u8_t optval[LWIP_SETGETSOCKOPT_MAXOPTLEN];
#else
  union {
    void *p;
    const void *pc;
  } optval;
#endif
  /***optval的大小*/
  socklen_t optlen;
  /**如果发生错误，将临时存储在此处*/
  int err;
  /**唤醒调用任务的信号量*/
  void* completed_sem;
};
#endif /* !LWIP_TCPIP_CORE_LOCKING */

#ifdef __cplusplus
}
#endif

struct lwip_sock* lwip_socket_dbg_get_socket(int fd);

#if LWIP_SOCKET_SELECT || LWIP_SOCKET_POLL

#if LWIP_NETCONN_SEM_PER_THREAD
#define SELECT_SEM_T        sys_sem_t*
#define SELECT_SEM_PTR(sem) (sem)
#else /* LWIP_NETCONN_SEM_PER_THREAD */
#define SELECT_SEM_T        sys_sem_t
#define SELECT_SEM_PTR(sem) (&(sem))
#endif /* LWIP_NETCONN_SEM_PER_THREAD */

/**等待选择的任务的描述*/
struct lwip_select_cb {
  /**指向下一个等待任务的指针*/
  struct lwip_select_cb *next;
  /**指向上一个等待任务的指针*/
  struct lwip_select_cb *prev;
#if LWIP_SOCKET_SELECT
  /**传递给select的readset*/
  fd_set *readset;
  /**传递给select的写集*/
  fd_set *writeset;
  /**未实现：exceptset传递给select*/
  fd_set *exceptset;
#endif /* LWIP_SOCKET_SELECT */
#if LWIP_SOCKET_POLL
  /**投票表决通过；如果选择，则为NULL*/
  struct pollfd *poll_fds;
  /**nfds通过投票表决；如果选择，则为0*/
  nfds_t poll_nfds;
#endif /* LWIP_SOCKET_POLL */
  /**不要两次发出相同的信号：发出信号时设置为1*/
  int sem_signalled;
  /**用于唤醒等待选择的任务的信号灯*/
  SELECT_SEM_T sem;
};
#endif /* LWIP_SOCKET_SELECT || LWIP_SOCKET_POLL */

#endif /* LWIP_SOCKET */

#endif /* LWIP_HDR_SOCKETS_PRIV_H */

