// 版权所有2019-2020 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define USB_DESCRIPTOR_TYPE_ACM 0
#define USB_DESCRIPTOR_TYPE_DFU 1

void usb_set_current_descriptor(int descriptor_type);

bool usb_get_descriptor(uint16_t type_index, uint16_t lang_id,
                        int32_t *len, uint8_t **data);

#ifdef __cplusplus
}
#endif

