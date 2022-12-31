/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_HS_PVCY_PRIV_
#define H_BLE_HS_PVCY_PRIV_

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const uint8_t ble_hs_pvcy_default_irk[16];

int ble_hs_pvcy_set_our_irk(const uint8_t *irk);
int ble_hs_pvcy_our_irk(const uint8_t **out_irk);
int ble_hs_pvcy_remove_entry(uint8_t addr_type, const uint8_t *addr);
int ble_hs_pvcy_add_entry(const uint8_t *addr, uint8_t addrtype,
                          const uint8_t *irk);
int ble_hs_pvcy_ensure_started(void);
int ble_hs_pvcy_set_mode(const ble_addr_t *addr, uint8_t priv_mode);
#if MYNEWT_VAL(BLE_HOST_BASED_PRIVACY)
bool ble_hs_pvcy_enabled(void);
#endif

#ifdef __cplusplus
}
#endif

#endif

