/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_OS_ERROR_
#define H_OS_ERROR_

#include "os/os.h"

enum os_error {
    OS_OK = 0,
    OS_ENOMEM = 1,
    OS_EINVAL = 2,
    OS_INVALID_PARM = 3,
    OS_MEM_NOT_ALIGNED = 4,
    OS_BAD_MUTEX = 5,
    OS_TIMEOUT = 6,
    OS_ERR_IN_ISR = 7,      /* 无法从ISR调用函数*/
    OS_ERR_PRIV = 8,        /* 特权访问错误*/
    OS_NOT_STARTED = 9,     /* 必须启动OS才能调用此函数，但不是*/
    OS_ENOENT = 10,         /* 没有这样的事*/
    OS_EBUSY = 11,          /* 资源繁忙*/
    OS_ERROR = 12,          /* 一般性错误*/
};

typedef enum os_error os_error_t;

#endif

