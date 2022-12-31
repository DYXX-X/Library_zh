/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#include <stdint.h>

uint32_t ble_ll_utils_calc_access_addr(void);
uint8_t ble_ll_utils_remapped_channel(uint8_t remap_index, const uint8_t *chanmap);
uint8_t ble_ll_utils_calc_dci_csa2(uint16_t event_cntr, uint16_t channel_id,
                                   uint8_t num_used_chans, const uint8_t *chanmap);
uint8_t ble_ll_utils_calc_num_used_chans(const uint8_t *chanmap);
uint32_t ble_ll_utils_calc_window_widening(uint32_t anchor_point,
                                           uint32_t last_anchor_point,
                                           uint8_t master_sca);

