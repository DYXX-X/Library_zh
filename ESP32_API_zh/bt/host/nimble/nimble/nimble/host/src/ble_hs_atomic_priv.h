/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_HS_ATOMIC_
#define H_BLE_HS_ATOMIC_

#include "ble_hs_conn_priv.h"

#ifdef __cplusplus
extern "C" {
#endif

int ble_hs_atomic_conn_delete(uint16_t conn_handle);
void ble_hs_atomic_conn_insert(struct ble_hs_conn *conn);
int ble_hs_atomic_conn_flags(uint16_t conn_handle,
                             ble_hs_conn_flags_t *out_flags);
int ble_hs_atomic_conn_set_flags(uint16_t conn_handle,
                                 ble_hs_conn_flags_t flags, int on);
uint16_t ble_hs_atomic_first_conn_handle(void);

#ifdef __cplusplus
}
#endif

#endif

