// 版权所有2019 Espressif Systems（上海）私人有限公司
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

/**RTCIO输出/输入模式类型。*/
typedef enum {
    RTC_GPIO_MODE_INPUT_ONLY ,  /*!< 极板输入*/
    RTC_GPIO_MODE_OUTPUT_ONLY,  /*!< 极板输出*/
    RTC_GPIO_MODE_INPUT_OUTPUT, /*!< 极板输入+输出*/
    RTC_GPIO_MODE_DISABLED,     /*!< 键盘（输出+输入）禁用*/
    RTC_GPIO_MODE_OUTPUT_OD,    /*!< 极板漏极开路输出*/
    RTC_GPIO_MODE_INPUT_OUTPUT_OD, /*!< 极板输入+漏极开路输出*/
} rtc_gpio_mode_t;

