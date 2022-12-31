// 版权所有2019 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#pragma once

#include "soc/soc.h"
//包括soc相关（生成的）定义
#include "soc/soc_caps.h"

#if SOC_RTCIO_INPUT_OUTPUT_SUPPORTED
#include "soc/rtc_io_channel.h"
#include "soc/rtc_io_reg.h"
#include "soc/rtc_io_struct.h"
#endif

#include "soc/rtc_cntl_reg.h"
#include "soc/rtc_cntl_struct.h"

#if SOC_ADC_RTC_CTRL_SUPPORTED
#include "soc/sens_struct.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#if SOC_RTCIO_INPUT_OUTPUT_SUPPORTED

/**
 * @brief 单个RTCIO焊盘的引脚功能信息。
 *
 * 这是驱动程序的内部功能，通常不适用于外部使用。
 */
typedef struct {
    uint32_t reg;       /*!< RTC焊盘寄存器，如果不是RTC GPIO，则为0*/
    uint32_t mux;       /*!< 用于选择数字焊盘或RTC焊盘的位掩码*/
    uint32_t func;      /*!< 极板功能移位（FUN_SEL）字段*/
    uint32_t ie;        /*!< 输入启用掩码*/
    uint32_t pullup;    /*!< 上拉启用掩码*/
    uint32_t pulldown;  /*!< 下拉启用掩码*/
    uint32_t slpsel;    /*!< 如果设置了slpsel位，slpie将在睡眠模式下用作焊盘输入启用信号*/
    uint32_t slpie;     /*!< 睡眠模式下的输入启用掩码*/
    uint32_t slpoe;     /*!< 休眠模式下的输出启用掩码*/
    uint32_t hold;      /*!< 保持启用掩码*/
    uint32_t hold_force;/*!< RTC_CNTL_hold_REG中RTC IO的hold_force位掩码*/
    uint32_t drv_v;     /*!< 驱动能力掩码*/
    uint32_t drv_s;     /*!< 驱动能力偏移*/
    int rtc_num;        /*!< GPIO编号（对应于RTC焊盘）*/
} rtc_io_desc_t;

/**
 * @brief 提供对RTC I/O引脚功能信息常量表的访问。表的索引是rtcio的索引。
 *
 * 这是驱动程序的内部功能，通常不适用于外部使用。
 */
extern const rtc_io_desc_t rtc_io_desc[SOC_RTCIO_PIN_COUNT];

/**
 * @brief 提供一个常量表，以获取带有gpio编号的rtc io编号
 *
 * 这是驱动程序的内部功能，通常不适用于外部使用。
 */
extern const int rtc_io_num_map[SOC_GPIO_PIN_COUNT];

#ifdef CONFIG_RTCIO_SUPPORT_RTC_GPIO_DESC
/**
 * @brief 单个GPIO焊盘RTC功能的引脚功能信息。
 *
 * 这是驱动程序的内部功能，通常不适用于外部使用。
 */
typedef struct {
    uint32_t reg;       /*!< RTC焊盘寄存器，如果不是RTC GPIO，则为0*/
    uint32_t mux;       /*!< 用于选择数字焊盘或RTC焊盘的位掩码*/
    uint32_t func;      /*!< 极板功能移位（FUN_SEL）字段*/
    uint32_t ie;        /*!< 输入启用掩码*/
    uint32_t pullup;    /*!< 上拉启用掩码*/
    uint32_t pulldown;  /*!< 下拉启用掩码*/
    uint32_t slpsel;    /*!< 如果设置了slpsel位，slpie将在睡眠模式下用作焊盘输入启用信号*/
    uint32_t slpie;     /*!< 睡眠模式下的输入启用掩码*/
    uint32_t hold;      /*!< 保持启用掩码*/
    uint32_t hold_force;/*!< RTC_CNTL_hold_force_REG中RTC IO的hold_force位掩码*/
    uint32_t drv_v;     /*!< 驱动能力掩码*/
    uint32_t drv_s;     /*!< 驱动能力偏移*/
    int rtc_num;        /*!< RTC IO编号，如果不是RTC GPIO，则为-1*/
} rtc_gpio_desc_t;

/**
 * @brief 提供对RTC I/O引脚功能信息常量表的访问。
 *
 * 这是驱动程序的内部功能，通常不适用于外部使用。
 */
extern const rtc_gpio_desc_t rtc_gpio_desc[SOC_GPIO_PIN_COUNT];

#endif // CONFIG_RTCIO_SUPPORT_RTC_GPIO_DESC

#endif // SOC_RTCIO_INPUT_OUTPUT_SUPPORTED

#ifdef __cplusplus
}
#endif

