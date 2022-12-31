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

#include <stdbool.h>
#include "tusb.h"
#include "tusb_option.h"
#include "tusb_config.h"
#include "tinyusb_types.h"


#ifdef __cplusplus
extern "C" {
#endif


/* tinyusb使用类型为uint8t[]的缓冲区，但在我们的驱动程序中，我们将它们读取为32位字*/
#if (CFG_TUD_ENDPOINT0_SIZE < 4)
#   define CFG_TUD_ENDPOINT0_SIZE 4
#   warning "CFG_TUD_ENDPOINT0_SIZE was too low and was set to 4"
#endif

#if TUSB_OPT_DEVICE_ENABLED

#   if CFG_TUD_HID
#      if (CFG_TUD_HID_BUFSIZE < 4)
#         define CFG_TUD_HID_BUFSIZE 4
#         warning "CFG_TUD_HID_BUFSIZE was too low and was set to 4"
#      endif
#   endif

#   if CFG_TUD_CDC
#      if (CFG_TUD_CDC_EP_BUFSIZE < 4)
#         define CFG_TUD_CDC_EP_BUFSIZE 4
#         warning "CFG_TUD_CDC_EP_BUFSIZE was too low and was set to 4"
#      endif
#   endif

#   if CFG_TUD_MSC
#      if (CFG_TUD_MSC_BUFSIZE < 4)
#         define CFG_TUD_MSC_BUFSIZE 4
#         warning "CFG_TUD_MSC_BUFSIZE was too low and was set to 4"
#      endif
#   endif

#   if CFG_TUD_MIDI
#       if (CFG_TUD_MIDI_EPSIZE < 4)
#          define CFG_TUD_MIDI_EPSIZE 4
#          warning "CFG_TUD_MIDI_EPSIZE was too low and was set to 4"
#       endif
#   endif

#   if CFG_TUD_CUSTOM_CLASS
#          warning "Please check that the buffer is more then 4 bytes"
#   endif
#endif

/**
 * @brief tinyUSB核心的配置结构
 */
typedef struct {
    tusb_desc_device_t *descriptor; /*!< 指向设备描述符的指针*/
    const char **string_descriptor; /*!< 指向字符串描述符数组的指针*/
    bool external_phy;              /*!< USB是否应使用外部PHY*/
} tinyusb_config_t;

/**
 * @brief 这是一个多功能助手功能，包括：1.USB设备驱动程序初始化2.描述符准备3.TinyUSB堆栈初始化4.创建并启动任务以处理USB事件
 *
 * @note 不要更改自定义描述符，但如果必须更改，建议定义如下以匹配接口关联描述符（IAD）：bDeviceClass=TUSB_CLASS_MISC，bDeviceSubClass=MISC_SUBCLASS_COMMON，
 *
 * @param config tinyusb堆栈特定配置
 * @retval 由于参数无效，ESP_ERR_INVALID_ARG安装驱动程序和tinyusb堆栈失败
 * @retval 由于内部错误，ESP_FAIL安装驱动程序和tinyusb堆栈失败
 * @retval ESP_OK成功安装驱动程序和tinyusb堆栈
 */
esp_err_t tinyusb_driver_install(const tinyusb_config_t *config);

// TODO esp_err_t tinyusb_driver_uninstall（无效）；（IDF-1474）

#ifdef __cplusplus
}
#endif

