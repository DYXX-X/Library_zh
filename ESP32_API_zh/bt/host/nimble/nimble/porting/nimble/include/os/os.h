/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef _OS_H
#define _OS_H

#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef min
#define min(a, b) ((a)<(b)?(a):(b))
#endif

#ifndef max
#define max(a, b) ((a)>(b)?(a):(b))
#endif

#include "syscfg/syscfg.h"
#include "nimble/nimble_npl.h"

#define OS_ALIGN(__n, __a) (                             \
        (((__n) & ((__a) - 1)) == 0)                   ? \
            (__n)                                      : \
            ((__n) + ((__a) - ((__n) & ((__a) - 1))))    \
        )
#define OS_ALIGNMENT    (BLE_NPL_OS_ALIGNMENT)

typedef uint32_t os_sr_t;
#define OS_ENTER_CRITICAL(_sr) (_sr = ble_npl_hw_enter_critical())
#define OS_EXIT_CRITICAL(_sr) (ble_npl_hw_exit_critical(_sr))
#define OS_ASSERT_CRITICAL() assert(ble_npl_hw_is_in_critical())

/* Mynewt组件（未在NPL中抽象）*/
#include "os/endian.h"
#include "os/queue.h"
#include "os/os_error.h"
#include "os/os_mbuf.h"
#include "os/os_mempool.h"

#ifdef __cplusplus
}
#endif

#endif /* _OS_H */

