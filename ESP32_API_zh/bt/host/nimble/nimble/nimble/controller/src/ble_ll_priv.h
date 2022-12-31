/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_LL_PRIV_
#define H_BLE_LL_PRIV_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MYNEWT

#include "syscfg/syscfg.h"
#include "hal/hal_gpio.h"

#define BLE_LL_DEBUG_GPIO_INIT(_name)                                       \
    if (MYNEWT_VAL(BLE_LL_DEBUG_GPIO_ ## _name) >= 0) {                     \
        hal_gpio_init_out(MYNEWT_VAL(BLE_LL_DEBUG_GPIO_ ## _name), 0);      \
    }

#define BLE_LL_DEBUG_GPIO(_name, _val)                                      \
    if (MYNEWT_VAL(BLE_LL_DEBUG_GPIO_ ## _name) >= 0) {                     \
        hal_gpio_write(MYNEWT_VAL(BLE_LL_DEBUG_GPIO_ ## _name), !!(_val));  \
    }

#else
#define BLE_LL_DEBUG_GPIO_INIT(_name)       (void)(0)
#define BLE_LL_DEBUG_GPIO(_name, _val)      (void)(0)
#endif

#ifdef __cplusplus
}
#endif

#endif /* H_BLE_LL_PRIV_ */

