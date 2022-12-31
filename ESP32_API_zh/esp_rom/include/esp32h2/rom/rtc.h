/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _ROM_RTC_H_
#define _ROM_RTC_H_

#include "ets_sys.h"

#include <stdbool.h>
#include <stdint.h>

#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/reset_reasons.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup rtc api、rtc寄存器和内存相关api
  * @brief rtc api
  */

/** @addtogroup rtc_api@{
  */

/**************************************************************************************
  *                                       注：*在ROM或内部库中使用了一些Rtc内存和寄存器。请不要使用保留或使用的rtc内存或寄存器。
  *                                                                                   *
  ************************************************************************************* RTC内存和存储寄存器使用
  *************************************************************************************
  *     rtc内存地址类型大小用法0x3f421000（0x50000000）慢size_CP协处理器代码/重置项0x3f431000+size_C慢8192-size_CP
  *
  *     0x3ff80000（0x40070000）快速8192深度睡眠进入代码
  *
  ************************************************************************************* RTC存储寄存器用法RTC_CNTL_STORE0_REG保留RTC_CNTL_STORE1_REG RTC_SLOW_CLK校准值RTC_CNTL-STORE2_REG引导时间、低字RTC_CNT_LSTORE3_REG引导时间，高字RTC_CNTL_STORE4_REG外部XTAL频率RTC_CNTL STORE5_REG APB总线频率RTC_CNT L_STORE6_REG FAST_RTC_MEMORY_ENTRY
  *************************************************************************************
  */

#define RTC_SLOW_CLK_CAL_REG    RTC_CNTL_STORE1_REG
#define RTC_BOOT_TIME_LOW_REG   RTC_CNTL_STORE2_REG
#define RTC_BOOT_TIME_HIGH_REG  RTC_CNTL_STORE3_REG
#define RTC_XTAL_FREQ_REG       RTC_CNTL_STORE4_REG
#define RTC_APB_FREQ_REG        RTC_CNTL_STORE5_REG
#define RTC_ENTRY_ADDR_REG      RTC_CNTL_STORE6_REG
#define RTC_RESET_CAUSE_REG     RTC_CNTL_STORE6_REG
#define RTC_MEMORY_CRC_REG      RTC_CNTL_STORE7_REG

#define RTC_DISABLE_ROM_LOG ((1 << 0) | (1 << 16)) //!< 从ROM代码禁用日志记录。


typedef enum {
    AWAKE = 0,             //<CPU ON
    LIGHT_SLEEP = BIT0,    //CPU等待，PLL开启。我们不需要明确设置此模式。
    DEEP_SLEEP  = BIT1     //CPU关闭，PLL关闭，只有特定的计时器才能唤醒
} SLEEP_MODE;

typedef enum {
    NO_MEAN                =  0,
    POWERON_RESET          =  1,    /**<1，Vbat上电复位*/
    RTC_SW_SYS_RESET       =  3,    /**<3，软件重置数字核心*/
    DEEPSLEEP_RESET        =  5,    /**<5，深度睡眠重置数字核心*/
    TG0WDT_SYS_RESET       =  7,    /**<7，定时器组0看门狗重置数字核心*/
    TG1WDT_SYS_RESET       =  8,    /**<8，定时器组1看门狗重置数字核心*/
    RTCWDT_SYS_RESET       =  9,    /**<9，RTC看门狗重置数字核心*/
    INTRUSION_RESET        = 10,    /**<10，测试仪器重置CPU*/
    TG0WDT_CPU_RESET       = 11,    /**<11，时间组0重置CPU*/
    RTC_SW_CPU_RESET       = 12,    /**<12，软件重置CPU*/
    RTCWDT_CPU_RESET       = 13,    /**<13，RTC看门狗重置CPU*/
    RTCWDT_BROWN_OUT_RESET = 15,    /**<15，当vdd电压不稳定时重置*/
    RTCWDT_RTC_RESET       = 16,    /**<16，RTC看门狗重置数字核心和RTC模块*/
    TG1WDT_CPU_RESET       = 17,    /**<17，时间组1重置CPU*/
    SUPER_WDT_RESET        = 18,    /**<18，超级看门狗重置数字核心和rtc模块*/
    GLITCH_RTC_RESET       = 19,    /**<19，故障复位数字核心和rtc模块*/
    EFUSE_RESET            = 20,    /**<20，efuse重置数字核心*/
    USB_UART_CHIP_RESET    = 21,    /**<21，usb uart重置数字核心*/
    USB_JTAG_CHIP_RESET    = 22,    /**<22，usb jtag重置数字核心*/
    POWER_GLITCH_RESET     = 23,    /**<23，电源故障复位数字核心和rtc模块*/
    JTAG_RESET             = 24,    /**<24，jtag重置CPU*/
} RESET_REASON;

// 检查ROM中定义的重置原因是否与soc/reset_reasons兼容。h
_Static_assert((soc_reset_reason_t)POWERON_RESET == RESET_REASON_CHIP_POWER_ON, "POWERON_RESET != RESET_REASON_CHIP_POWER_ON");
_Static_assert((soc_reset_reason_t)RTC_SW_SYS_RESET == RESET_REASON_CORE_SW, "RTC_SW_SYS_RESET != RESET_REASON_CORE_SW");
_Static_assert((soc_reset_reason_t)DEEPSLEEP_RESET == RESET_REASON_CORE_DEEP_SLEEP, "DEEPSLEEP_RESET != RESET_REASON_CORE_DEEP_SLEEP");
_Static_assert((soc_reset_reason_t)TG0WDT_SYS_RESET == RESET_REASON_CORE_MWDT0, "TG0WDT_SYS_RESET != RESET_REASON_CORE_MWDT0");
_Static_assert((soc_reset_reason_t)TG1WDT_SYS_RESET == RESET_REASON_CORE_MWDT1, "TG1WDT_SYS_RESET != RESET_REASON_CORE_MWDT1");
_Static_assert((soc_reset_reason_t)RTCWDT_SYS_RESET == RESET_REASON_CORE_RTC_WDT, "RTCWDT_SYS_RESET != RESET_REASON_CORE_RTC_WDT");
_Static_assert((soc_reset_reason_t)TG0WDT_CPU_RESET == RESET_REASON_CPU0_MWDT0, "TG0WDT_CPU_RESET != RESET_REASON_CPU0_MWDT0");
_Static_assert((soc_reset_reason_t)RTC_SW_CPU_RESET == RESET_REASON_CPU0_SW, "RTC_SW_CPU_RESET != RESET_REASON_CPU0_SW");
_Static_assert((soc_reset_reason_t)RTCWDT_CPU_RESET == RESET_REASON_CPU0_RTC_WDT, "RTCWDT_CPU_RESET != RESET_REASON_CPU0_RTC_WDT");
_Static_assert((soc_reset_reason_t)RTCWDT_BROWN_OUT_RESET == RESET_REASON_SYS_BROWN_OUT, "RTCWDT_BROWN_OUT_RESET != RESET_REASON_SYS_BROWN_OUT");
_Static_assert((soc_reset_reason_t)RTCWDT_RTC_RESET == RESET_REASON_SYS_RTC_WDT, "RTCWDT_RTC_RESET != RESET_REASON_SYS_RTC_WDT");
_Static_assert((soc_reset_reason_t)TG1WDT_CPU_RESET == RESET_REASON_CPU0_MWDT1, "TG1WDT_CPU_RESET != RESET_REASON_CPU0_MWDT1");
_Static_assert((soc_reset_reason_t)SUPER_WDT_RESET == RESET_REASON_SYS_SUPER_WDT, "SUPER_WDT_RESET != RESET_REASON_SYS_SUPER_WDT");
_Static_assert((soc_reset_reason_t)GLITCH_RTC_RESET == RESET_REASON_SYS_CLK_GLITCH, "GLITCH_RTC_RESET != RESET_REASON_SYS_CLK_GLITCH");
_Static_assert((soc_reset_reason_t)EFUSE_RESET == RESET_REASON_CORE_EFUSE_CRC, "EFUSE_RESET != RESET_REASON_CORE_EFUSE_CRC");
_Static_assert((soc_reset_reason_t)USB_UART_CHIP_RESET == RESET_REASON_CORE_USB_UART, "USB_UART_CHIP_RESET != RESET_REASON_CORE_USB_UART");
_Static_assert((soc_reset_reason_t)USB_JTAG_CHIP_RESET == RESET_REASON_CORE_USB_JTAG, "USB_JTAG_CHIP_RESET != RESET_REASON_CORE_USB_JTAG");
_Static_assert((soc_reset_reason_t)POWER_GLITCH_RESET == RESET_REASON_CORE_PWR_GLITCH, "POWER_GLITCH_RESET != RESET_REASON_CORE_PWR_GLITCH");
_Static_assert((soc_reset_reason_t)JTAG_RESET == RESET_REASON_CPU0_JTAG, "JTAG_RESET != RESET_REASON_CPU0_JTAG");

typedef enum {
    NO_SLEEP        = 0,
    EXT_EVENT0_TRIG = BIT0,
    EXT_EVENT1_TRIG = BIT1,
    GPIO_TRIG       = BIT2,
    TIMER_EXPIRE    = BIT3,
    SDIO_TRIG       = BIT4,
    MAC_TRIG        = BIT5,
    UART0_TRIG      = BIT6,
    UART1_TRIG      = BIT7,
    TOUCH_TRIG      = BIT8,
    SAR_TRIG        = BIT9,
    BT_TRIG         = BIT10,
    RISCV_TRIG      = BIT11,
    XTAL_DEAD_TRIG  = BIT12,
    RISCV_TRAP_TRIG = BIT13,
    USB_TRIG        = BIT14
} WAKEUP_REASON;

typedef enum {
    DISEN_WAKEUP       = NO_SLEEP,
    EXT_EVENT0_TRIG_EN = EXT_EVENT0_TRIG,
    EXT_EVENT1_TRIG_EN = EXT_EVENT1_TRIG,
    GPIO_TRIG_EN       = GPIO_TRIG,
    TIMER_EXPIRE_EN    = TIMER_EXPIRE,
    SDIO_TRIG_EN       = SDIO_TRIG,
    MAC_TRIG_EN        = MAC_TRIG,
    UART0_TRIG_EN      = UART0_TRIG,
    UART1_TRIG_EN      = UART1_TRIG,
    TOUCH_TRIG_EN      = TOUCH_TRIG,
    SAR_TRIG_EN        = SAR_TRIG,
    BT_TRIG_EN         = BT_TRIG,
    RISCV_TRIG_EN      = RISCV_TRIG,
    XTAL_DEAD_TRIG_EN  = XTAL_DEAD_TRIG,
    RISCV_TRAP_TRIG_EN = RISCV_TRAP_TRIG,
    USB_TRIG_EN        = USB_TRIG
} WAKEUP_ENABLE;

/**
  * @brief  获取CPU的重置原因。
  *
  * @param  int cpu_no:cpu编号。
  *
  * @return RESET_REASON
  */
RESET_REASON rtc_get_reset_reason(int cpu_no);

/**
  * @brief  获取CPU的唤醒原因。
  *
  * @param  int cpu_no:cpu编号。
  *
  * @return WAKEUP_REASON
  */
WAKEUP_REASON rtc_get_wakeup_cause(void);

/**
  * @brief 获取快速RTC内存的CRC。
  *
  * @param  uint32_t start_addr:0-0x7ff用于快速RTC内存。
  *
  * @param  uint32_t crc_len:0-0x7ff，0表示4字节，0x7ff表示0x2000字节。
  *
  * @return uint32_t:CRC32结果
  */
uint32_t calc_rtc_memory_crc(uint32_t start_addr, uint32_t crc_len);

/**
  * @brief 通过设置特定RTC控制寄存器抑制ROM日志。
  * @note 这不是ROM记录的永久禁用，因为芯片复位后RTC寄存器无法保留。
  *
  * @param  None
  *
  * @return 没有一个
  */
static inline void rtc_suppress_rom_log(void)
{
    /* 要禁用ROM中的日志记录，只使用寄存器的最低有效位，但由于该寄存器还用于存储主晶体的频率（RTC_XTAL_FREQ_REG），因此需要以相同的格式写入该寄存器。即，高位16位和低位应该相同。
     */
    REG_SET_BIT(RTC_CNTL_STORE4_REG, RTC_DISABLE_ROM_LOG);
}

/**
  * @brief 将快速RTC存储器0-0x7ff的CRC设置为RTC STORE7。
  *
  * @param  None
  *
  * @return 没有一个
  */
void set_rtc_memory_crc(void);

/**
  * @brief 从RTC内存和RTC STORE reg获取条目
  *
  * @param uint32_t *entry_addr：保存条目的地址
  *
  * @param RESET_REASON reset_reason：这次重置原因
  *
  * @return 没有一个
  */
void rtc_boot_control(uint32_t *entry_addr, RESET_REASON reset_reason);

/**
  * @brief 软件重置数字核心。
  *
  * 不建议在esp-idf中使用此函数，请改用esp_restart（）。
  *
  * @param  None
  *
  * @return 没有一个
  */
void software_reset(void);

/**
  * @brief 软件重置数字核心。
  *
  * 不建议在esp-idf中使用此函数，请改用esp_restart（）。
  *
  * @param  int cpu_no：要重置的cpu，0表示PRO cpu，1表示APP cpu。
  *
  * @return 没有一个
  */
void software_reset_cpu(int cpu_no);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* _ROM_RTC_H_ */

