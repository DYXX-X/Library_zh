// 2020浓缩咖啡系统（上海）有限公司版权所有。
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

#ifdef __cplusplus
extern "C" {
#endif

#define USB_ESPRESSIF_VID 0x303A
#define USB_STRING_DESCRIPTOR_ARRAY_SIZE 7

typedef enum{
    TINYUSB_USBDEV_0,
} tinyusb_usbdev_t;

typedef const char *tusb_desc_strarray_device_t[USB_STRING_DESCRIPTOR_ARRAY_SIZE];

#ifdef __cplusplus
}
#endif

