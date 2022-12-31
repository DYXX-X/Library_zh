/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_HS_ID_PRIV_
#define H_BLE_HS_ID_PRIV_

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

void ble_hs_id_set_pub(const uint8_t *pub_addr);
int ble_hs_id_addr(uint8_t id_addr_type, const uint8_t **out_id_addr,
                   int *out_is_nrpa);
int ble_hs_id_use_addr(uint8_t addr_type);
void ble_hs_id_reset(void);
void ble_hs_id_rnd_reset(void);

#if MYNEWT_VAL(BLE_HOST_BASED_PRIVACY)
bool ble_hs_is_rpa(uint8_t *addr, uint8_t addr_type);
int ble_hs_id_set_pseudo_rnd(const uint8_t *);
int ble_hs_id_set_nrpa_rnd(void);
#endif
#ifdef __cplusplus
}
#endif

#endif

