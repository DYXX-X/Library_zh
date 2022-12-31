// 版权所有2018-2019 Espressif Systems（Shanghai）PTE LTD
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef _ESP_PLATFORM_SYS_POLL_H_
#define _ESP_PLATFORM_SYS_POLL_H_

#define POLLIN      (1u << 0)      /* 可以在不阻塞的情况下读取高优先级以外的数据*/
#define POLLRDNORM  (1u << 1)      /* 正常数据可以在不阻塞的情况下读取*/
#define POLLRDBAND  (1u << 2)      /* 可以在不阻塞的情况下读取优先级数据*/
#define POLLPRI     (POLLRDBAND)   /* 高优先级数据可以在不阻塞的情况下读取*/
// 注意：POLLPRI等效于POLLRBAND，以便将所有这些事件放入一个字节
#define POLLOUT     (1u << 3)      /* 正常数据可以在不阻塞的情况下写入*/
#define POLLWRNORM  (POLLOUT)      /* 相当于POLLOUT*/
#define POLLWRBAND  (1u << 4)      /* 可以写入优先级数据*/
#define POLLERR     (1u << 5)      /* 发生了一些轮询错误*/
#define POLLHUP     (1u << 6)      /* 文件描述符已“挂起”*/
#define POLLNVAL    (1u << 7)      /* 指定的文件描述符无效*/

#ifdef __cplusplus
extern "C" {
#endif

struct pollfd {
    int fd;        /* 描述符。*/
    short events;  /* 此处指定了事件。*/
    short revents; /* 此处返回找到的事件。*/
};

typedef unsigned int nfds_t;

int poll(struct pollfd *fds, nfds_t nfds, int timeout);

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // _ESP_PLATFORM_SYS_POLL_H_

