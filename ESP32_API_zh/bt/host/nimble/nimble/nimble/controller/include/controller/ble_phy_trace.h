/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_PHY_TRACE_
#define H_BLE_PHY_TRACE_

#include "os/os_trace_api.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BLE_PHY_TRACE_ID_START_TX       0
#define BLE_PHY_TRACE_ID_START_RX       1
#define BLE_PHY_TRACE_ID_DISABLE        2

#if MYNEWT_VAL(BLE_PHY_SYSVIEW)

extern uint32_t ble_phy_trace_off;

void ble_phy_trace_init(void);

static inline void
ble_phy_trace_void(unsigned id)
{
    os_trace_api_void(ble_phy_trace_off + id);
}

static inline void
ble_phy_trace_u32(unsigned id, uint32_t p1)
{
    os_trace_api_u32(ble_phy_trace_off + id, p1);
}

static inline void
ble_phy_trace_u32x2(unsigned id, uint32_t p1, uint32_t p2)
{
    os_trace_api_u32x2(ble_phy_trace_off + id, p1, p2);
}

static inline void
ble_phy_trace_u32x3(unsigned id, uint32_t p1, uint32_t p2, uint32_t p3)
{
    os_trace_api_u32x3(ble_phy_trace_off + id, p1, p2, p3);
}

#else

static inline void
ble_phy_trace_init(void)
{
}

static inline void
ble_phy_trace_void(unsigned id)
{
}

static inline void
ble_phy_trace_u32(unsigned id, uint32_t p1)
{
}

static inline void
ble_phy_trace_u32x2(unsigned id, uint32_t p1, uint32_t p2)
{
}

static inline void
ble_phy_trace_u32x3(unsigned id, uint32_t p1, uint32_t p2, uint32_t p3)
{
}

#endif

#ifdef __cplusplus
}
#endif

#endif /* H_BLE_PHY_TRACE_ */

