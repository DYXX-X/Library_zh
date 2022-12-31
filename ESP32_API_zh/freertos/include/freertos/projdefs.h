/*
 * FreeRTOS内核V10.4.3版权所有（C）2020 Amazon。com，Inc.或其附属公司。保留所有权利。
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org https://github.com/FreeRTOS
 *
 */

#ifndef PROJDEFS_H
#define PROJDEFS_H

/*
 * 定义任务函数必须符合的原型。在此文件中定义，以确保在可移植之前已知类型。h包括在内。
 */
typedef void (* TaskFunction_t)( void * );

/* 将以毫秒为单位的时间转换为以刻度为单位的。此宏可以被FreeRTOSConfig中定义的同名宏覆盖。h，以防此处的定义不适合您的应用。*/
#ifndef pdMS_TO_TICKS
    #define pdMS_TO_TICKS( xTimeInMs )    ( ( TickType_t ) ( ( ( TickType_t ) ( xTimeInMs ) * ( TickType_t ) configTICK_RATE_HZ ) / ( TickType_t ) 1000U ) )
#endif
#ifdef ESP_PLATFORM
#ifndef pdTICKS_TO_MS
    #define pdTICKS_TO_MS( xTicks )   ( ( TickType_t ) ( ( uint64_t ) ( xTicks ) * 1000 / configTICK_RATE_HZ ) )
#endif
#endif // ESP_PLATFORM

#define pdFALSE                                  ( ( BaseType_t ) 0 )
#define pdTRUE                                   ( ( BaseType_t ) 1 )

#define pdPASS                                   ( pdTRUE )
#define pdFAIL                                   ( pdFALSE )
#define errQUEUE_EMPTY                           ( ( BaseType_t ) 0 )
#define errQUEUE_FULL                            ( ( BaseType_t ) 0 )

/* FreeRTOS错误定义。*/
#define errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY    ( -1 )
#define errQUEUE_BLOCKED                         ( -4 )
#define errQUEUE_YIELD                           ( -5 )

/* 用于基本数据损坏检查的宏。*/
#ifndef configUSE_LIST_DATA_INTEGRITY_CHECK_BYTES
    #define configUSE_LIST_DATA_INTEGRITY_CHECK_BYTES    0
#endif

#if ( configUSE_16_BIT_TICKS == 1 )
    #define pdINTEGRITY_CHECK_VALUE    0x5a5a
#else
    #define pdINTEGRITY_CHECK_VALUE    0x5a5a5a5aUL
#endif

/* 以下errno值由FreeRTOS+组件使用，而不是FreeRTOS本身。*/
#define pdFREERTOS_ERRNO_NONE             0   /* 无错误*/
#define pdFREERTOS_ERRNO_ENOENT           2   /* 没有这样的文件或目录*/
#define pdFREERTOS_ERRNO_EINTR            4   /* 中断的系统调用*/
#define pdFREERTOS_ERRNO_EIO              5   /* I/O错误*/
#define pdFREERTOS_ERRNO_ENXIO            6   /* 没有这样的设备或地址*/
#define pdFREERTOS_ERRNO_EBADF            9   /* 错误的文件编号*/
#define pdFREERTOS_ERRNO_EAGAIN           11  /* 不再有进程*/
#define pdFREERTOS_ERRNO_EWOULDBLOCK      11  /* 操作将阻止*/
#define pdFREERTOS_ERRNO_ENOMEM           12  /* 内存不足*/
#define pdFREERTOS_ERRNO_EACCES           13  /* 权限被拒绝*/
#define pdFREERTOS_ERRNO_EFAULT           14  /* 地址错误*/
#define pdFREERTOS_ERRNO_EBUSY            16  /* 装载设备忙*/
#define pdFREERTOS_ERRNO_EEXIST           17  /* 文件已存在*/
#define pdFREERTOS_ERRNO_EXDEV            18  /* 跨设备链接*/
#define pdFREERTOS_ERRNO_ENODEV           19  /* 没有这样的设备*/
#define pdFREERTOS_ERRNO_ENOTDIR          20  /* 不是目录*/
#define pdFREERTOS_ERRNO_EISDIR           21  /* 是一个目录*/
#define pdFREERTOS_ERRNO_EINVAL           22  /* 参数无效*/
#define pdFREERTOS_ERRNO_ENOSPC           28  /* 设备上没有剩余空间*/
#define pdFREERTOS_ERRNO_ESPIPE           29  /* 非法搜索*/
#define pdFREERTOS_ERRNO_EROFS            30  /* 只读文件系统*/
#define pdFREERTOS_ERRNO_EUNATCH          42  /* 未连接协议驱动程序*/
#define pdFREERTOS_ERRNO_EBADE            50  /* 无效的交换*/
#define pdFREERTOS_ERRNO_EFTYPE           79  /* 文件类型或格式不正确*/
#define pdFREERTOS_ERRNO_ENMFILE          89  /* 没有更多文件*/
#define pdFREERTOS_ERRNO_ENOTEMPTY        90  /* 目录不为空*/
#define pdFREERTOS_ERRNO_ENAMETOOLONG     91  /* 文件或路径名太长*/
#define pdFREERTOS_ERRNO_EOPNOTSUPP       95  /* 传输终结点上不支持操作*/
#define pdFREERTOS_ERRNO_ENOBUFS          105 /* 没有可用的缓冲区空间*/
#define pdFREERTOS_ERRNO_ENOPROTOOPT      109 /* 协议不可用*/
#define pdFREERTOS_ERRNO_EADDRINUSE       112 /* 地址已在使用中*/
#define pdFREERTOS_ERRNO_ETIMEDOUT        116 /* 连接超时*/
#define pdFREERTOS_ERRNO_EINPROGRESS      119 /* 连接已在进行中*/
#define pdFREERTOS_ERRNO_EALREADY         120 /* 套接字已连接*/
#define pdFREERTOS_ERRNO_EADDRNOTAVAIL    125 /* 地址不可用*/
#define pdFREERTOS_ERRNO_EISCONN          127 /* 套接字已连接*/
#define pdFREERTOS_ERRNO_ENOTCONN         128 /* 插座未连接*/
#define pdFREERTOS_ERRNO_ENOMEDIUM        135 /* 未插入介质*/
#define pdFREERTOS_ERRNO_EILSEQ           138 /* 遇到无效的UTF-16序列。*/
#define pdFREERTOS_ERRNO_ECANCELED        140 /* 操作已取消。*/

/* 以下端值由FreeRTOS+组件使用，而不是FreeRTOS本身。*/
#define pdFREERTOS_LITTLE_ENDIAN          0
#define pdFREERTOS_BIG_ENDIAN             1

/* 为通用命名重新定义endian值。*/
#define pdLITTLE_ENDIAN                   pdFREERTOS_LITTLE_ENDIAN
#define pdBIG_ENDIAN                      pdFREERTOS_BIG_ENDIAN


#endif /* PROJDEFS_H */

