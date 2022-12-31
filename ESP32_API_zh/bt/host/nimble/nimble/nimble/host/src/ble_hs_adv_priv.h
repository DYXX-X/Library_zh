/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_HS_ADV_PRIV_
#define H_BLE_HS_ADV_PRIV_

#ifdef __cplusplus
extern "C" {
#endif

int ble_hs_adv_set_flat(uint8_t type, int data_len, const void *data,
                        uint8_t *dst, uint8_t *dst_len, uint8_t max_len);
int ble_hs_adv_find_field(uint8_t type, const uint8_t *data, uint8_t length,
                          const struct ble_hs_adv_field **out);

#ifdef __cplusplus
}
#endif

#endif

