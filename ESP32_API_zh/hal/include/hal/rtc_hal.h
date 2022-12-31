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

#include "soc/soc_caps.h"
#include "hal/gpio_types.h"
#include "hal/rtc_cntl_ll.h"
#if !CONFIG_IDF_TARGET_ESP32C3 && !CONFIG_IDF_TARGET_ESP32H2
#include "hal/rtc_io_ll.h"
#endif

typedef struct rtc_cntl_sleep_retent {
#if SOC_PM_SUPPORT_CPU_PD
    void     *cpu_pd_mem;   /* 用于cpu保留的内部ram地址*/
#endif // SOC_PM_SUPPORT_CPU_PD
#if SOC_PM_SUPPORT_TAGMEM_PD
    struct {
        void     *link_addr;  /* 标记保留的内部ram地址*/
        struct {
            uint32_t start_point: 8,    /* i-cache标记存储器的起始行*/
                     vld_size: 8,       /* i-cache标记内存的有效大小，单位：4个i-cache标记mem块*/
                     size: 8,           /* i-cache标记内存大小，单位：4个i-cache标记mem块*/
                     enable: 1;         /* 启用或禁用i-cache tagmem保留*/
        } icache;
        struct {
            uint32_t start_point: 9,    /* d-cache标记存储器的起始行*/
                     vld_size: 9,       /* d-cache标记内存的有效大小，单位：4个d-cache标记mem块*/
                     size: 9,           /* d-cache标记内存大小，单位：4个d-cache标记mem块*/
                     enable: 1;         /* 启用或禁用d-cache tagmem保留*/
        } dcache;
    } tagmem;
#endif // SOC_PM_SUPPORT_TAGMEM_PD
} rtc_cntl_sleep_retent_t;

#define RTC_HAL_DMA_LINK_NODE_SIZE      (16)

#if SOC_PM_SUPPORT_EXT_WAKEUP

#define rtc_hal_ext1_get_wakeup_pins()                    rtc_cntl_ll_ext1_get_wakeup_pins()

#define rtc_hal_ext1_set_wakeup_pins(mask, mode)          rtc_cntl_ll_ext1_set_wakeup_pins(mask, mode)

#define rtc_hal_ext1_clear_wakeup_pins()                  rtc_cntl_ll_ext1_clear_wakeup_pins()

#endif

#if SOC_GPIO_SUPPORT_DEEPSLEEP_WAKEUP

#define rtc_hal_gpio_get_wakeup_pins()                    rtc_cntl_ll_gpio_get_wakeup_pins()

#define rtc_hal_gpio_clear_wakeup_pins()                  rtc_cntl_ll_gpio_clear_wakeup_pins()

#define rtc_hal_gpio_set_wakeup_pins()                    rtc_cntl_ll_gpio_set_wakeup_pins()

#endif

#define rtc_hal_set_wakeup_timer(ticks)                   rtc_cntl_ll_set_wakeup_timer(ticks)

void * rtc_cntl_hal_dma_link_init(void *elem, void *buff, int size, void *next);

#if SOC_PM_SUPPORT_CPU_PD

void rtc_cntl_hal_enable_cpu_retention(void *addr);

void rtc_cntl_hal_disable_cpu_retention(void *addr);

#endif

#if SOC_PM_SUPPORT_TAGMEM_PD

void rtc_cntl_hal_enable_tagmem_retention(void *addr);

void rtc_cntl_hal_disable_tagmem_retention(void *addr);

#endif

/*
 * 启用ULP协处理器的唤醒。
 */
#define rtc_hal_ulp_wakeup_enable()                       rtc_cntl_ll_ulp_wakeup_enable()

