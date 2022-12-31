/**
 * @file Posix Errno定义
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
#ifndef LWIP_HDR_ERRNO_H
#define LWIP_HDR_ERRNO_H

#include "lwip/opt.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef LWIP_PROVIDE_ERRNO

#define  EPERM            1  /* 不允许操作*/
#define  ENOENT           2  /* 没有这样的文件或目录*/
#define  ESRCH            3  /* 没有这样的过程*/
#define  EINTR            4  /* 中断的系统调用*/
#define  EIO              5  /* I/O错误*/
#define  ENXIO            6  /* 没有这样的设备或地址*/
#define  E2BIG            7  /* 参数列表太长*/
#define  ENOEXEC          8  /* Exec格式错误*/
#define  EBADF            9  /* 错误的文件编号*/
#define  ECHILD          10  /* 无子进程*/
#define  EAGAIN          11  /* 再试一次*/
#define  ENOMEM          12  /* 内存不足*/
#define  EACCES          13  /* 权限被拒绝*/
#define  EFAULT          14  /* 地址错误*/
#define  ENOTBLK         15  /* 需要阻止设备*/
#define  EBUSY           16  /* 设备或资源忙*/
#define  EEXIST          17  /* 文件已存在*/
#define  EXDEV           18  /* 跨设备链接*/
#define  ENODEV          19  /* 没有这样的设备*/
#define  ENOTDIR         20  /* 不是目录*/
#define  EISDIR          21  /* 是一个目录*/
#define  EINVAL          22  /* 参数无效*/
#define  ENFILE          23  /* 文件表溢出*/
#define  EMFILE          24  /* 打开的文件太多*/
#define  ENOTTY          25  /* 不是打字机*/
#define  ETXTBSY         26  /* 文本文件忙*/
#define  EFBIG           27  /* 文件太大*/
#define  ENOSPC          28  /* 设备上没有剩余空间*/
#define  ESPIPE          29  /* 非法搜索*/
#define  EROFS           30  /* 只读文件系统*/
#define  EMLINK          31  /* 链接太多*/
#define  EPIPE           32  /* 管道破裂*/
#define  EDOM            33  /* 数学参数超出func的域*/
#define  ERANGE          34  /* 数学结果不可表示*/
#define  EDEADLK         35  /* 将发生资源死锁*/
#define  ENAMETOOLONG    36  /* 文件名太长*/
#define  ENOLCK          37  /* 没有可用的记录锁*/
#define  ENOSYS          38  /* 功能未实现*/
#define  ENOTEMPTY       39  /* 目录不为空*/
#define  ELOOP           40  /* 遇到太多符号链接*/
#define  EWOULDBLOCK     EAGAIN  /* 操作将阻止*/
#define  ENOMSG          42  /* 没有所需类型的消息*/
#define  EIDRM           43  /* 标识符已删除*/
#define  ECHRNG          44  /* 通道编号超出范围*/
#define  EL2NSYNC        45  /* 2级未同步*/
#define  EL3HLT          46  /* 3级已停止*/
#define  EL3RST          47  /* 3级重置*/
#define  ELNRNG          48  /* 链接编号超出范围*/
#define  EUNATCH         49  /* 未连接协议驱动程序*/
#define  ENOCSI          50  /* 没有可用的CSI结构*/
#define  EL2HLT          51  /* 2级已停止*/
#define  EBADE           52  /* 无效的交换*/
#define  EBADR           53  /* 请求描述符无效*/
#define  EXFULL          54  /* Exchange已满*/
#define  ENOANO          55  /* 无阳极*/
#define  EBADRQC         56  /* 无效的请求代码*/
#define  EBADSLT         57  /* 插槽无效*/

#define  EDEADLOCK       EDEADLK

#define  EBFONT          59  /* 字体文件格式错误*/
#define  ENOSTR          60  /* 设备不是流*/
#define  ENODATA         61  /* 无可用数据*/
#define  ETIME           62  /* 计时器已过期*/
#define  ENOSR           63  /* 流出的资源*/
#define  ENONET          64  /* 计算机不在网络上*/
#define  ENOPKG          65  /* 未安装程序包*/
#define  EREMOTE         66  /* 对象是远程的*/
#define  ENOLINK         67  /* 链接已断开*/
#define  EADV            68  /* 播发错误*/
#define  ESRMNT          69  /* Srmount错误*/
#define  ECOMM           70  /* 发送时发生通信错误*/
#define  EPROTO          71  /* 协议错误*/
#define  EMULTIHOP       72  /* 已尝试多跳*/
#define  EDOTDOT         73  /* RFS特定错误*/
#define  EBADMSG         74  /* 不是数据消息*/
#define  EOVERFLOW       75  /* 值对于定义的数据类型太大*/
#define  ENOTUNIQ        76  /* 名称在网络上不唯一*/
#define  EBADFD          77  /* 文件描述符处于错误状态*/
#define  EREMCHG         78  /* 远程地址已更改*/
#define  ELIBACC         79  /* 无法访问所需的共享库*/
#define  ELIBBAD         80  /* 访问损坏的共享库*/
#define  ELIBSCN         81  /* a.out中的.lib节已损坏*/
#define  ELIBMAX         82  /* 试图链接太多的共享库*/
#define  ELIBEXEC        83  /* 无法直接执行共享库*/
#define  EILSEQ          84  /* 非法字节序列*/
#define  ERESTART        85  /* 应重新启动中断的系统调用*/
#define  ESTRPIPE        86  /* 流管道错误*/
#define  EUSERS          87  /* 用户太多*/
#define  ENOTSOCK        88  /* 非套接字上的套接字操作*/
#define  EDESTADDRREQ    89  /* 需要目标地址*/
#define  EMSGSIZE        90  /* 消息太长*/
#define  EPROTOTYPE      91  /* 套接字的协议类型错误*/
#define  ENOPROTOOPT     92  /* 协议不可用*/
#define  EPROTONOSUPPORT 93  /* 不支持协议*/
#define  ESOCKTNOSUPPORT 94  /* 不支持套接字类型*/
#define  EOPNOTSUPP      95  /* 传输终结点上不支持操作*/
#define  EPFNOSUPPORT    96  /* 不支持协议系列*/
#define  EAFNOSUPPORT    97  /* 协议不支持地址系列*/
#define  EADDRINUSE      98  /* 地址已在使用中*/
#define  EADDRNOTAVAIL   99  /* 无法分配请求的地址*/
#define  ENETDOWN       100  /* 网络已关闭*/
#define  ENETUNREACH    101  /* 网络无法访问*/
#define  ENETRESET      102  /* 由于重置，网络已断开连接*/
#define  ECONNABORTED   103  /* 软件导致连接中止*/
#define  ECONNRESET     104  /* 对等方重置连接*/
#define  ENOBUFS        105  /* 没有可用的缓冲区空间*/
#define  EISCONN        106  /* 传输终结点已连接*/
#define  ENOTCONN       107  /* 传输终结点未连接*/
#define  ESHUTDOWN      108  /* 传输终结点关闭后无法发送*/
#define  ETOOMANYREFS   109  /* 引用太多：无法拼接*/
#define  ETIMEDOUT      110  /* 连接超时*/
#define  ECONNREFUSED   111  /* 连接被拒绝*/
#define  EHOSTDOWN      112  /* 主机已关闭*/
#define  EHOSTUNREACH   113  /* 没有到主机的路由*/
#define  EALREADY       114  /* 操作已在进行中*/
#define  EINPROGRESS    115  /* 操作正在进行*/
#define  ESTALE         116  /* 过时的NFS文件句柄*/
#define  EUCLEAN        117  /* 结构需要清洁*/
#define  ENOTNAM        118  /* 不是XENIX命名类型文件*/
#define  ENAVAIL        119  /* 没有XENIX信号量可用*/
#define  EISNAM         120  /* 是命名类型文件*/
#define  EREMOTEIO      121  /* 远程I/O错误*/
#define  EDQUOT         122  /* 超出配额*/

#define  ENOMEDIUM      123  /* 未找到介质*/
#define  EMEDIUMTYPE    124  /* 介质类型错误*/

#ifndef errno
extern int errno;
#endif

#else /* LWIP_PROVIDE_ERRNO */

/* 如果要包含<ERRNO，请定义LWIP_ERRNO_STDINCLUDE。h> 这里*/
#ifdef LWIP_ERRNO_STDINCLUDE
#include <errno.h>
#else /* LWIP_ERRNO_STDINCLUDE */
/* 将LWIP_ERRNO_INCLUDE定义为等效的<ERRNO。h> 包含此处定义的错误*/
#ifdef LWIP_ERRNO_INCLUDE
#include LWIP_ERRNO_INCLUDE
#endif /* LWIP_ERRNO_INCLUDE */
#endif /* LWIP_ERRNO_STDINCLUDE */

#endif /* LWIP_PROVIDE_ERRNO */

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_ERRNO_H */

