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

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PERIPH_LEDC_MODULE = 0,
    PERIPH_UART0_MODULE,
    PERIPH_UART1_MODULE,
    PERIPH_USB_DEVICE_MODULE,
    PERIPH_I2C0_MODULE,
    PERIPH_I2S1_MODULE,
    PERIPH_TIMG0_MODULE,
    PERIPH_TIMG1_MODULE,
    PERIPH_UHCI0_MODULE,
    PERIPH_RMT_MODULE,
    PERIPH_SPI_MODULE,  //SPI1
    PERIPH_SPI2_MODULE, //SPI2
    PERIPH_TWAI_MODULE,
    PERIPH_RNG_MODULE,
    PERIPH_WIFI_MODULE,
    PERIPH_BT_MODULE,
    PERIPH_WIFI_BT_COMMON_MODULE,
    PERIPH_BT_BASEBAND_MODULE,
    PERIPH_BT_LC_MODULE,
    PERIPH_RSA_MODULE,
    PERIPH_AES_MODULE,
    PERIPH_SHA_MODULE,
    PERIPH_HMAC_MODULE,
    PERIPH_DS_MODULE,
    PERIPH_GDMA_MODULE,
    PERIPH_SYSTIMER_MODULE,
    PERIPH_SARADC_MODULE,
    PERIPH_MODULE_MAX
} periph_module_t;

typedef enum {
    ETS_WIFI_MAC_INTR_SOURCE = 0,               /**<WiFi MAC中断，级别*/
    ETS_WIFI_MAC_NMI_SOURCE,                    /**<WiFi MAC、NMI中断，如果MAC在NMI中存在要修复的错误，请使用*/
    ETS_WIFI_PWR_INTR_SOURCE,                   /**< */
    ETS_WIFI_BB_INTR_SOURCE,                    /**<WiFi BB中断，级别，我们可以进行一些校准*/
    ETS_BT_MAC_INTR_SOURCE,                     /**<将被取消*/
    ETS_BT_BB_INTR_SOURCE,                      /**<BT BB中断，电平*/
    ETS_BT_BB_NMI_SOURCE,                       /**<BT BB、NMI的中断，如果BB在NMI中存在要修复的错误，请使用*/
    ETS_RWBT_INTR_SOURCE,                       /**<RWBT中断，电平*/
    ETS_RWBLE_INTR_SOURCE,                      /**<RWBLE中断，电平*/
    ETS_RWBT_NMI_SOURCE,                        /**<RWBT、NMI的中断，如果RWBT在NMI中存在要修复的错误，请使用*/
    ETS_RWBLE_NMI_SOURCE,                       /**<RWBLE、NMI的中断，如果RWBT在NMI中存在要修复的错误，请使用*/
    ETS_I2C_MASTER_SOURCE,                      /**<I2C主机中断，电平*/
    ETS_SLC0_INTR_SOURCE,                       /**<SLC0中断，电平*/
    ETS_SLC1_INTR_SOURCE,                       /**<SLC1中断，电平*/
    ETS_APB_CTRL_INTR_SOURCE,                   /**<APB ctrl中断？*/
    ETS_UHCI0_INTR_SOURCE,                      /**<UHCI0中断，电平*/
    ETS_GPIO_INTR_SOURCE,                       /**<GPIO中断，电平*/
    ETS_GPIO_NMI_SOURCE,                        /**<GPIO、NMI中断*/
    ETS_SPI1_INTR_SOURCE,                       /**<SPI1的中断，级别，SPI1用于闪存读/写，请勿使用此*/
    ETS_SPI2_INTR_SOURCE,                       /**<SPI2中断，电平*/
    ETS_I2S1_INTR_SOURCE,                       /**<I2S1中断，电平*/
    ETS_UART0_INTR_SOURCE,                      /**<UART0中断，电平*/
    ETS_UART1_INTR_SOURCE,                      /**<UART1中断，电平*/
    ETS_LEDC_INTR_SOURCE,                       /**<LED PWM中断，电平*/
    ETS_EFUSE_INTR_SOURCE,                      /**<中断efuse，级别，不太可能使用*/
    ETS_TWAI_INTR_SOURCE,                        /**<罐中断，液位*/
    ETS_USB_SERIAL_JTAG_INTR_SOURCE,                        /**<USB中断，级别*/
    ETS_RTC_CORE_INTR_SOURCE,                   /**<rtc核心中断，级别，包括rtc看门狗*/
    ETS_RMT_INTR_SOURCE,                        /**<遥控器中断，级别*/
    ETS_I2C_EXT0_INTR_SOURCE,                   /**<I2C控制器1中断，电平*/
    ETS_TIMER1_INTR_SOURCE,
    ETS_TIMER2_INTR_SOURCE,
    ETS_TG0_T0_LEVEL_INTR_SOURCE,               /**<TIMER_GROUP0、TIMER0、电平中断*/
    ETS_TG0_WDT_LEVEL_INTR_SOURCE,              /**<TIMER_GROUP0，看门狗，电平中断*/
    ETS_TG1_T0_LEVEL_INTR_SOURCE,               /**<TIMER_GROUP1、TIMER0、电平中断*/
    ETS_TG1_WDT_LEVEL_INTR_SOURCE,              /**<TIMER_GROUP1，WATCHDOG，电平中断*/
    ETS_CACHE_IA_INTR_SOURCE,                   /**<缓存无效访问中断，LEVEL*/
    ETS_SYSTIMER_TARGET0_EDGE_INTR_SOURCE,      /**<系统定时器0中断，EDGE*/
    ETS_SYSTIMER_TARGET1_EDGE_INTR_SOURCE,      /**<系统定时器1中断，EDGE*/
    ETS_SYSTIMER_TARGET2_EDGE_INTR_SOURCE,      /**<系统定时器2中断，EDGE*/
    ETS_SPI_MEM_REJECT_CACHE_INTR_SOURCE,       /**<SPI0缓存访问中断和SPI1访问被拒绝，LEVEL*/
    ETS_ICACHE_PRELOAD0_INTR_SOURCE,            /**<ICache perload操作中断，LEVEL*/
    ETS_ICACHE_SYNC0_INTR_SOURCE,               /**<指令缓存同步完成中断，LEVEL*/
    ETS_APB_ADC_INTR_SOURCE,                    /**<APB ADC中断，LEVEL*/
    ETS_DMA_CH0_INTR_SOURCE,                    /**<一般DMA通道0的中断，LEVEL*/
    ETS_DMA_CH1_INTR_SOURCE,                    /**<一般DMA通道1的中断，LEVEL*/
    ETS_DMA_CH2_INTR_SOURCE,                    /**<一般DMA通道2的中断，LEVEL*/
    ETS_RSA_INTR_SOURCE,                        /**<RSA加速器中断，级别*/
    ETS_AES_INTR_SOURCE,                        /**<AES加速器中断，级别*/
    ETS_SHA_INTR_SOURCE,                        /**<SHA加速器中断，级别*/
    ETS_FROM_CPU_INTR0_SOURCE,                  /**<从CPU生成的中断0，级别*/ /* 用于FreeRTOS*/
    ETS_FROM_CPU_INTR1_SOURCE,                  /**<从CPU生成的中断1，级别*/ /* 用于FreeRTOS*/
    ETS_FROM_CPU_INTR2_SOURCE,                  /**<从CPU生成的中断2，级别*/
    ETS_FROM_CPU_INTR3_SOURCE,                  /**<从CPU生成的中断3，级别*/
    ETS_ASSIST_DEBUG_INTR_SOURCE,               /**<辅助调试模块中断，LEVEL*/
    ETS_DMA_APBPERI_PMS_INTR_SOURCE,
    ETS_CORE0_IRAM0_PMS_INTR_SOURCE,
    ETS_CORE0_DRAM0_PMS_INTR_SOURCE,
    ETS_CORE0_PIF_PMS_INTR_SOURCE,
    ETS_CORE0_PIF_PMS_SIZE_INTR_SOURCE,
    ETS_BAK_PMS_VIOLATE_INTR_SOURCE,
    ETS_CACHE_CORE0_ACS_INTR_SOURCE,
    ETS_MAX_INTR_SOURCE,
} periph_interrput_t;

#ifdef __cplusplus
}
#endif

