/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef BLE_TGT_MISC_H
#define BLE_TGT_MISC_H

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "host/ble_hs.h"
#include "host/ble_uuid.h"
#include "host/ble_hs_adv.h"

#ifdef __cplusplus
extern "C" {
#endif

void rand_bytes(uint8_t *data, int len);

void print_bytes(const uint8_t *bytes, int len);

void print_addr(const void *addr);

void print_mbuf(const struct os_mbuf *om);

char *addr_str(const void *addr);

void print_uuid(const ble_uuid_t *uuid);

void print_conn_desc(const struct ble_gap_conn_desc *desc);

void print_adv_fields(const struct ble_hs_adv_fields *fields);

#ifdef __cplusplus
}
#endif

#endif //BLE_TGT_MISC_H

