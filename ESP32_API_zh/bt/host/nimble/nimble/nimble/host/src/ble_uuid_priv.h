/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_UUID_PRIV_
#define H_BLE_UUID_PRIV_

#include "host/ble_uuid.h"

#ifdef __cplusplus
extern "C" {
#endif

struct os_mbuf;

int ble_uuid_init_from_att_mbuf(ble_uuid_any_t *uuid, struct os_mbuf *om,
                                int off, int len);
int ble_uuid_init_from_att_buf(ble_uuid_any_t *uuid, const void *buf,
                               size_t len);

int ble_uuid_to_any(const ble_uuid_t *uuid, ble_uuid_any_t *uuid_any);
int ble_uuid_to_mbuf(const ble_uuid_t *uuid, struct os_mbuf *om);
int ble_uuid_flat(const ble_uuid_t *uuid, void *dst);
int ble_uuid_length(const ble_uuid_t *uuid);

#ifdef __cplusplus
}
#endif

#endif

