// 版权所有2018 Espressif Systems（上海）私人有限公司
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

#ifndef __ESP_SYS_SELECT_H__
#define __ESP_SYS_SELECT_H__

/* Newlib 2.2.0不提供sys/select。h、 并且fd_set在sys/types中定义。小时*/
#include <sys/types.h>
#ifndef fd_set
#include_next <sys/select.h>
#else // fd_设置
#include <sys/time.h>

#ifdef __cplusplus
extern "C" {
#endif

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds, struct timeval *timeout);

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // fd_设置

#if defined(FD_ISSET) || defined(FD_SET) || defined(FD_CLR)
#undef FD_SET
#undef FD_CLR
#undef FD_ISSET

#define __FD_SAFE_SET(n, code) do { if ((unsigned)(n) < FD_SETSIZE) { code; } } while(0)
#define __FD_SAFE_GET(n, code) (((unsigned)(n) < FD_SETSIZE) ? (code) : 0)

#define FD_SET(n, p)	__FD_SAFE_SET(n, ((p)->fds_bits[(n) / NFDBITS] |=  (1L << ((n) % NFDBITS))))
#define FD_CLR(n, p)	__FD_SAFE_SET(n, ((p)->fds_bits[(n) / NFDBITS] &= ~(1L << ((n) % NFDBITS))))
#define FD_ISSET(n, p)	__FD_SAFE_GET(n, ((p)->fds_bits[(n) / NFDBITS] &   (1L << ((n) % NFDBITS))))
#endif // FD_ISSET || FD_SET || FD_CLR

#endif //__ESP_SYS_SELECT_H__

