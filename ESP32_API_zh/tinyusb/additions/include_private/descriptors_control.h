// 版权所有2020 Espressif Systems（上海）私人有限公司
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

#include <string.h>
#include "usb_descriptors.h"


/* 接口组合必须具有唯一的产品id，因为PC将在第一次插入后保存设备驱动程序。具有不同接口的相同VID/PID，例如MSC（首先），然后CDC（稍后）可能会导致PC上的系统错误。
 *
 * Auto ProductID布局的位图：[MSB]HID|MSC|CDC[LSB]
 */
#define EPNUM_MSC 0x03

#ifdef __cplusplus
extern "C" {
#endif
//-------------HID报告描述符-------------//
#if CFG_TUD_HID
enum {
    REPORT_ID_KEYBOARD = 1,
    REPORT_ID_MOUSE
};
#endif

//-------------配置描述符-------------//
enum {
#   if CFG_TUD_CDC
    ITF_NUM_CDC = 0,
    ITF_NUM_CDC_DATA,
#   endif

#   if CFG_TUD_MSC
    ITF_NUM_MSC,
#   endif

#   if CFG_TUD_HID
    ITF_NUM_HID,
#   endif

    ITF_NUM_TOTAL
};

enum {
    TUSB_DESC_TOTAL_LEN = TUD_CONFIG_DESC_LEN + CFG_TUD_CDC * TUD_CDC_DESC_LEN + CFG_TUD_MSC * TUD_MSC_DESC_LEN +
                       CFG_TUD_HID * TUD_HID_DESC_LEN
};

bool tusb_desc_set;
void tusb_set_descriptor(tusb_desc_device_t *desc, const char **str_desc);
tusb_desc_device_t *tusb_get_active_desc(void);
char **tusb_get_active_str_desc(void);
void tusb_clear_descriptor(void);

#ifdef __cplusplus
}
#endif

