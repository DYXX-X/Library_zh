// 版权所有2010-2019 Espressif Systems（上海）私人有限公司
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

#ifndef __ASSEMBLER__
#include <stdint.h>
#include "esp_assert.h"
#endif

#include <esp_bit_defs.h>

#define PRO_CPU_NUM (0)
#define APP_CPU_NUM (1)


#define SOC_MAX_CONTIGUOUS_RAM_SIZE 0x400000 ///<地址空间中连续内存（DRAM或IRAM）的最大跨度


#define DR_REG_DPORT_BASE                       0x3ff00000
#define DR_REG_AES_BASE                         0x3ff01000
#define DR_REG_RSA_BASE                         0x3ff02000
#define DR_REG_SHA_BASE                         0x3ff03000
#define DR_REG_FLASH_MMU_TABLE_PRO              0x3ff10000
#define DR_REG_FLASH_MMU_TABLE_APP              0x3ff12000
#define DR_REG_DPORT_END                        0x3ff13FFC
#define DR_REG_UART_BASE                        0x3ff40000
#define DR_REG_SPI1_BASE                        0x3ff42000
#define DR_REG_SPI0_BASE                        0x3ff43000
#define DR_REG_GPIO_BASE                        0x3ff44000
#define DR_REG_GPIO_SD_BASE                     0x3ff44f00
#define DR_REG_FE2_BASE                         0x3ff45000
#define DR_REG_FE_BASE                          0x3ff46000
#define DR_REG_FRC_TIMER_BASE                   0x3ff47000
#define DR_REG_RTCCNTL_BASE                     0x3ff48000
#define DR_REG_RTCIO_BASE                       0x3ff48400
#define DR_REG_SENS_BASE                        0x3ff48800
#define DR_REG_RTC_I2C_BASE                     0x3ff48C00
#define DR_REG_IO_MUX_BASE                      0x3ff49000
#define DR_REG_HINF_BASE                        0x3ff4B000
#define DR_REG_UHCI1_BASE                       0x3ff4C000
#define DR_REG_I2S_BASE                         0x3ff4F000
#define DR_REG_UART1_BASE                       0x3ff50000
#define DR_REG_BT_BASE                          0x3ff51000
#define DR_REG_I2C_EXT_BASE                     0x3ff53000
#define DR_REG_UHCI0_BASE                       0x3ff54000
#define DR_REG_SLCHOST_BASE                     0x3ff55000
#define DR_REG_RMT_BASE                         0x3ff56000
#define DR_REG_PCNT_BASE                        0x3ff57000
#define DR_REG_SLC_BASE                         0x3ff58000
#define DR_REG_LEDC_BASE                        0x3ff59000
#define DR_REG_EFUSE_BASE                       0x3ff5A000
#define DR_REG_SPI_ENCRYPT_BASE                 0x3ff5B000
#define DR_REG_NRX_BASE                         0x3ff5CC00
#define DR_REG_BB_BASE                          0x3ff5D000
#define DR_REG_PWM0_BASE                        0x3ff5E000
#define DR_REG_TIMERGROUP0_BASE                 0x3ff5F000
#define DR_REG_TIMERGROUP1_BASE                 0x3ff60000
#define DR_REG_RTCMEM0_BASE                     0x3ff61000
#define DR_REG_RTCMEM1_BASE                     0x3ff62000
#define DR_REG_RTCMEM2_BASE                     0x3ff63000
#define DR_REG_SPI2_BASE                        0x3ff64000
#define DR_REG_SPI3_BASE                        0x3ff65000
#define DR_REG_SYSCON_BASE                      0x3ff66000
#define DR_REG_APB_CTRL_BASE                    0x3ff66000    /* SYSCON的旧名称，将被删除*/
#define DR_REG_I2C1_EXT_BASE                    0x3ff67000
#define DR_REG_SDMMC_BASE                       0x3ff68000
#define DR_REG_EMAC_BASE                        0x3ff69000
#define DR_REG_CAN_BASE                         0x3ff6B000
#define DR_REG_PWM1_BASE                        0x3ff6C000
#define DR_REG_I2S1_BASE                        0x3ff6D000
#define DR_REG_UART2_BASE                       0x3ff6E000
#define PERIPHS_SPI_ENCRYPT_BASEADDR            DR_REG_SPI_ENCRYPT_BASE

//寄存器操作{{
#define ETS_UNCACHED_ADDR(addr) (addr)
#define ETS_CACHED_ADDR(addr) (addr)


#ifndef __ASSEMBLER__

#define IS_DPORT_REG(_r) (((_r) >= DR_REG_DPORT_BASE) && (_r) <= DR_REG_DPORT_END)

#if !defined( BOOTLOADER_BUILD ) && defined( CONFIG_ESP32_DPORT_WORKAROUND ) && defined( ESP_PLATFORM )
#define ASSERT_IF_DPORT_REG(_r, OP)  TRY_STATIC_ASSERT(!IS_DPORT_REG(_r), (Cannot use OP for DPORT registers use DPORT_##OP));
#else
#define ASSERT_IF_DPORT_REG(_r, OP)
#endif

//将值写入寄存器
#define REG_WRITE(_r, _v) ({                                                                                           \
            ASSERT_IF_DPORT_REG((_r), REG_WRITE);                                                                      \
            (*(volatile uint32_t *)(_r)) = (_v);                                                                       \
        })

//从寄存器读取值
#define REG_READ(_r) ({                                                                                                \
            ASSERT_IF_DPORT_REG((_r), REG_READ);                                                                       \
            (*(volatile uint32_t *)(_r));                                                                              \
        })

//获取位或从寄存器中获取位
#define REG_GET_BIT(_r, _b)  ({                                                                                        \
            ASSERT_IF_DPORT_REG((_r), REG_GET_BIT);                                                                    \
            (*(volatile uint32_t*)(_r) & (_b));                                                                        \
        })

//设置位或将位设置到寄存器
#define REG_SET_BIT(_r, _b)  ({                                                                                        \
            ASSERT_IF_DPORT_REG((_r), REG_SET_BIT);                                                                    \
            (*(volatile uint32_t*)(_r) |= (_b));                                                                       \
        })

//寄存器的清除位或清除位
#define REG_CLR_BIT(_r, _b)  ({                                                                                        \
            ASSERT_IF_DPORT_REG((_r), REG_CLR_BIT);                                                                    \
            (*(volatile uint32_t*)(_r) &= ~(_b));                                                                      \
        })

//掩码控制寄存器的置位
#define REG_SET_BITS(_r, _b, _m) ({                                                                                    \
            ASSERT_IF_DPORT_REG((_r), REG_SET_BITS);                                                                   \
            (*(volatile uint32_t*)(_r) = (*(volatile uint32_t*)(_r) & ~(_m)) | ((_b) & (_m)));                         \
        })

//从寄存器中获取字段，使用字段_S&_V确定掩码
#define REG_GET_FIELD(_r, _f) ({                                                                                       \
            ASSERT_IF_DPORT_REG((_r), REG_GET_FIELD);                                                                  \
            ((REG_READ(_r) >> (_f##_S)) & (_f##_V));                                                                   \
        })

//从变量设置寄存器的字段，使用字段_S&_V确定掩码
#define REG_SET_FIELD(_r, _f, _v) ({                                                                                   \
            ASSERT_IF_DPORT_REG((_r), REG_SET_FIELD);                                                                  \
            (REG_WRITE((_r),((REG_READ(_r) & ~((_f##_V) << (_f##_S)))|(((_v) & (_f##_V))<<(_f##_S)))));                \
        })

//从变量中获取字段值，当_f未左移_f###_S时使用
#define VALUE_GET_FIELD(_r, _f) (((_r) >> (_f##_S)) & (_f))

//从变量中获取字段值，当_f左移_f###_S时使用
#define VALUE_GET_FIELD2(_r, _f) (((_r) & (_f))>> (_f##_S))

//将字段值设置为变量，当_f未左移_f###_S时使用
#define VALUE_SET_FIELD(_r, _f, _v) ((_r)=(((_r) & ~((_f) << (_f##_S)))|((_v)<<(_f##_S))))

//将字段值设置为变量，当_f左移_f###_S时使用
#define VALUE_SET_FIELD2(_r, _f, _v) ((_r)=(((_r) & ~(_f))|((_v)<<(_f##_S))))

//从字段值生成值，当_f未左移_f###_S时使用
#define FIELD_TO_VALUE(_f, _v) (((_v)&(_f))<<_f##_S)

//从字段值生成值，当_f左移_f###_S时使用
#define FIELD_TO_VALUE2(_f, _v) (((_v)<<_f##_S) & (_f))

//从寄存器读取值
#define READ_PERI_REG(addr) ({                                                                                         \
            ASSERT_IF_DPORT_REG((addr), READ_PERI_REG);                                                                \
            (*((volatile uint32_t *)ETS_UNCACHED_ADDR(addr)));                                                         \
        })

//将值写入寄存器
#define WRITE_PERI_REG(addr, val) ({                                                                                   \
            ASSERT_IF_DPORT_REG((addr), WRITE_PERI_REG);                                                               \
            (*((volatile uint32_t *)ETS_UNCACHED_ADDR(addr))) = (uint32_t)(val);                                       \
        })

//掩码控制寄存器的清除位
#define CLEAR_PERI_REG_MASK(reg, mask) ({                                                                              \
            ASSERT_IF_DPORT_REG((reg), CLEAR_PERI_REG_MASK);                                                           \
            WRITE_PERI_REG((reg), (READ_PERI_REG(reg)&(~(mask))));                                                     \
        })

//掩码控制寄存器的置位
#define SET_PERI_REG_MASK(reg, mask) ({                                                                                \
            ASSERT_IF_DPORT_REG((reg), SET_PERI_REG_MASK);                                                             \
            WRITE_PERI_REG((reg), (READ_PERI_REG(reg)|(mask)));                                                        \
        })

//获取掩码控制的寄存器位
#define GET_PERI_REG_MASK(reg, mask) ({                                                                                \
            ASSERT_IF_DPORT_REG((reg), GET_PERI_REG_MASK);                                                             \
            (READ_PERI_REG(reg) & (mask));                                                                             \
        })

//获取由最高位和最低位控制的寄存器位
#define GET_PERI_REG_BITS(reg, hipos,lowpos) ({                                                                        \
            ASSERT_IF_DPORT_REG((reg), GET_PERI_REG_BITS);                                                             \
            ((READ_PERI_REG(reg)>>(lowpos))&((1<<((hipos)-(lowpos)+1))-1));                                            \
        })

//由掩码和移位控制的寄存器的置位
#define SET_PERI_REG_BITS(reg,bit_map,value,shift) ({                                                                  \
            ASSERT_IF_DPORT_REG((reg), SET_PERI_REG_BITS);                                                             \
            (WRITE_PERI_REG((reg),(READ_PERI_REG(reg)&(~((bit_map)<<(shift))))|(((value) & bit_map)<<(shift)) ));      \
        })

//获取寄存器字段
#define GET_PERI_REG_BITS2(reg, mask,shift) ({                                                                         \
            ASSERT_IF_DPORT_REG((reg), GET_PERI_REG_BITS2);                                                            \
            ((READ_PERI_REG(reg)>>(shift))&(mask));                                                                    \
        })

#endif /* !__ASSEMBLER__ */
//}}

//外围时钟{{
#define  APB_CLK_FREQ_ROM                            ( 26*1000000 )
#define  CPU_CLK_FREQ_ROM                            APB_CLK_FREQ_ROM
#define  CPU_CLK_FREQ                                APB_CLK_FREQ       //这可能不正确，请参阅ESP32_DEFAULT_CPU_FREQ_MHZ
#define  APB_CLK_FREQ                                ( 80*1000000 )       //单位：Hz
#define  REF_CLK_FREQ                                ( 1000000 )
#define  UART_CLK_FREQ                               APB_CLK_FREQ
#define  WDT_CLK_FREQ                                APB_CLK_FREQ
#define  TIMER_CLK_FREQ                              (80000000>>4) //80MHz除以16
#define  SPI_CLK_DIV                                 4
#define  TICKS_PER_US_ROM                            26              // CPU为80MHz
#define  GPIO_MATRIX_DELAY_NS                        25
//}}

/* 总体内存映射*/
#define SOC_DROM_LOW            0x3F400000
#define SOC_DROM_HIGH           0x3F800000
#define SOC_DRAM_LOW            0x3FFAE000
#define SOC_DRAM_HIGH           0x40000000
#define SOC_IROM_LOW            0x400D0000
#define SOC_IROM_HIGH           0x40400000
#define SOC_IROM_MASK_LOW       0x40000000
#define SOC_IROM_MASK_HIGH      0x40064F00
#define SOC_CACHE_PRO_LOW       0x40070000
#define SOC_CACHE_PRO_HIGH      0x40078000
#define SOC_CACHE_APP_LOW       0x40078000
#define SOC_CACHE_APP_HIGH      0x40080000
#define SOC_IRAM_LOW            0x40080000
#define SOC_IRAM_HIGH           0x400A0000
#define SOC_RTC_IRAM_LOW        0x400C0000
#define SOC_RTC_IRAM_HIGH       0x400C2000
#define SOC_RTC_DRAM_LOW        0x3FF80000
#define SOC_RTC_DRAM_HIGH       0x3FF82000
#define SOC_RTC_DATA_LOW        0x50000000
#define SOC_RTC_DATA_HIGH       0x50002000
#define SOC_EXTRAM_DATA_LOW     0x3F800000
#define SOC_EXTRAM_DATA_HIGH    0x3FC00000

#define SOC_EXTRAM_DATA_SIZE (SOC_EXTRAM_DATA_HIGH - SOC_EXTRAM_DATA_LOW)

//D/IRAM区域的第一个和最后一个字，用于DRAM地址和IRAM别名。
#define SOC_DIRAM_IRAM_LOW    0x400A0000
#define SOC_DIRAM_IRAM_HIGH   0x400C0000
#define SOC_DIRAM_DRAM_LOW    0x3FFE0000
#define SOC_DIRAM_DRAM_HIGH   0x40000000
// D/IRAM区域的字节顺序在作为DRAM或IRAM访问之间颠倒
#define SOC_DIRAM_INVERTED    1

// 可通过DMA访问的内存区域。请参见esp_ptr_dma_capable（）。
#define SOC_DMA_LOW  0x3FFAE000
#define SOC_DMA_HIGH 0x40000000

// 字节可访问的内存区域。请参见esp_ptr_byte_accessible（）。
#define SOC_BYTE_ACCESSIBLE_LOW     0x3FF90000
#define SOC_BYTE_ACCESSIBLE_HIGH    0x40000000

//内部内存区域，与ESP32 CPU位于同一硅片上
//（不包括单独检查的RTC数据区域。）请参阅esp_ptr_internal（）。
#define SOC_MEM_INTERNAL_LOW        0x3FF90000
#define SOC_MEM_INTERNAL_HIGH       0x400C2000

// ROM引导堆栈的开始（最高地址），仅在早期引导期间相关
#define SOC_ROM_STACK_START         0x3ffe3f20

//中断硬件源表
//这张桌子是由硬件决定的，不要碰这个。
#define ETS_WIFI_MAC_INTR_SOURCE                0/**<WiFi MAC中断，级别*/
#define ETS_WIFI_MAC_NMI_SOURCE                 1/**<WiFi MAC、NMI中断，如果MAC在NMI中存在要修复的错误，请使用*/
#define ETS_WIFI_BB_INTR_SOURCE                 2/**<WiFi BB中断，级别，我们可以进行一些校准*/
#define ETS_BT_MAC_INTR_SOURCE                  3/**<将被取消*/
#define ETS_BT_BB_INTR_SOURCE                   4/**<BT BB中断，电平*/
#define ETS_BT_BB_NMI_SOURCE                    5/**<BT BB、NMI的中断，如果BB在NMI中存在要修复的错误，请使用*/
#define ETS_RWBT_INTR_SOURCE                    6/**<RWBT中断，电平*/
#define ETS_RWBLE_INTR_SOURCE                   7/**<RWBLE中断，电平*/
#define ETS_RWBT_NMI_SOURCE                     8/**<RWBT、NMI的中断，如果RWBT在NMI中存在要修复的错误，请使用*/
#define ETS_RWBLE_NMI_SOURCE                    9/**<RWBLE、NMI的中断，如果RWBT在NMI中存在要修复的错误，请使用*/
#define ETS_SLC0_INTR_SOURCE                    10/**<SLC0中断，电平*/
#define ETS_SLC1_INTR_SOURCE                    11/**<SLC1中断，电平*/
#define ETS_UHCI0_INTR_SOURCE                   12/**<UHCI0中断，电平*/
#define ETS_UHCI1_INTR_SOURCE                   13/**<UHCI1中断，电平*/
#define ETS_TG0_T0_LEVEL_INTR_SOURCE            14/**<TIMER_GROUP0，TIMER0，level的中断，如果允许，我们希望使用EDGE作为计时器*/
#define ETS_TG0_T1_LEVEL_INTR_SOURCE            15/**<TIMER_GROUP0，TIMER1，level的中断，如果允许，我们希望使用EDGE作为计时器*/
#define ETS_TG0_WDT_LEVEL_INTR_SOURCE           16/**<TIMER_GROUP0，WATCHDOG，电平中断*/
#define ETS_TG0_LACT_LEVEL_INTR_SOURCE          17/**<TIMER_GROUP0，LACT，电平中断*/
#define ETS_TG1_T0_LEVEL_INTR_SOURCE            18/**<TIMER_GROUP1，TIMER0，level的中断，如果允许，我们希望使用EDGE作为计时器*/
#define ETS_TG1_T1_LEVEL_INTR_SOURCE            19/**<TIMER_GROUP1，TIMER1，level的中断，如果允许，我们希望使用EDGE作为计时器*/
#define ETS_TG1_WDT_LEVEL_INTR_SOURCE           20/**<TIMER_GROUP1，WATCHDOG，电平中断*/
#define ETS_TG1_LACT_LEVEL_INTR_SOURCE          21/**<TIMER_GROUP1，LACT，电平中断*/
#define ETS_GPIO_INTR_SOURCE                    22/**<GPIO中断，电平*/
#define ETS_GPIO_NMI_SOURCE                     23/**<GPIO、NMI中断*/
#define ETS_FROM_CPU_INTR0_SOURCE               24/**<从CPU生成的中断0，级别*/ /* 用于FreeRTOS*/
#define ETS_FROM_CPU_INTR1_SOURCE               25/**<从CPU生成的中断1，级别*/ /* 用于FreeRTOS*/
#define ETS_FROM_CPU_INTR2_SOURCE               26/**<从CPU生成的中断2，级别*/ /* 用于IPC_ISR*/
#define ETS_FROM_CPU_INTR3_SOURCE               27/**<从CPU生成的中断3，级别*/ /* 用于IPC_ISR*/
#define ETS_SPI0_INTR_SOURCE                    28/**<SPI0的中断，级别，SPI0用于缓存访问，请勿使用此*/
#define ETS_SPI1_INTR_SOURCE                    29/**<SPI1的中断，级别，SPI1用于闪存读/写，请勿使用此*/
#define ETS_SPI2_INTR_SOURCE                    30/**<SPI2中断，电平*/
#define ETS_SPI3_INTR_SOURCE                    31/**<SPI3中断，电平*/
#define ETS_I2S0_INTR_SOURCE                    32/**<I2S0中断，电平*/
#define ETS_I2S1_INTR_SOURCE                    33/**<I2S1中断，电平*/
#define ETS_UART0_INTR_SOURCE                   34/**<UART0中断，电平*/
#define ETS_UART1_INTR_SOURCE                   35/**<UART1中断，电平*/
#define ETS_UART2_INTR_SOURCE                   36/**<UART2中断，电平*/
#define ETS_SDIO_HOST_INTR_SOURCE               37/**<SD/SDIO/MMC主机中断，级别*/
#define ETS_ETH_MAC_INTR_SOURCE                 38/**<以太网mac中断，级别*/
#define ETS_PWM0_INTR_SOURCE                    39/**<PWM0中断，电平，保留*/
#define ETS_PWM1_INTR_SOURCE                    40/**<PWM1中断，电平，保留*/
#define ETS_LEDC_INTR_SOURCE                    43/**<LED PWM中断，电平*/
#define ETS_EFUSE_INTR_SOURCE                   44/**<中断efuse，级别，不太可能使用*/
#define ETS_TWAI_INTR_SOURCE                    45/**<twai中断，级别*/
#define ETS_CAN_INTR_SOURCE                     ETS_TWAI_INTR_SOURCE
#define ETS_RTC_CORE_INTR_SOURCE                46/**<rtc核心中断，级别，包括rtc看门狗*/
#define ETS_RMT_INTR_SOURCE                     47/**<遥控器中断，级别*/
#define ETS_PCNT_INTR_SOURCE                    48/**<脉冲计数中断，电平*/
#define ETS_I2C_EXT0_INTR_SOURCE                49/**<I2C控制器1中断，电平*/
#define ETS_I2C_EXT1_INTR_SOURCE                50/**<I2C控制器0中断，电平*/
#define ETS_RSA_INTR_SOURCE                     51/**<RSA加速器中断，级别*/
#define ETS_SPI1_DMA_INTR_SOURCE                52/**<SPI1 DMA中断，SPI1用于闪存读/写，请勿使用*/
#define ETS_SPI2_DMA_INTR_SOURCE                53/**<SPI2 DMA中断，级别*/
#define ETS_SPI3_DMA_INTR_SOURCE                54/**<SPI3 DMA中断，级别*/
#define ETS_WDT_INTR_SOURCE                     55/**<将被取消*/
#define ETS_TIMER1_INTR_SOURCE                  56/**<将被取消*/
#define ETS_TIMER2_INTR_SOURCE                  57/**<将被取消*/
#define ETS_TG0_T0_EDGE_INTR_SOURCE             58/**<TIMER_GROUP0、TIMER0、EDGE中断*/
#define ETS_TG0_T1_EDGE_INTR_SOURCE             59/**<TIMER_GROUP0、TIMER1、EDGE中断*/
#define ETS_TG0_WDT_EDGE_INTR_SOURCE            60/**<TIMER_GROUP0、看门狗、EDGE的中断*/
#define ETS_TG0_LACT_EDGE_INTR_SOURCE           61/**<TIMER_GROUP0、LACT、EDGE中断*/
#define ETS_TG1_T0_EDGE_INTR_SOURCE             62/**<TIMER_GROUP1、TIMER0、EDGE中断*/
#define ETS_TG1_T1_EDGE_INTR_SOURCE             63/**<TIMER_GROUP1、TIMER1、EDGE中断*/
#define ETS_TG1_WDT_EDGE_INTR_SOURCE            64/**<TIMER_GROUP1、WATCHDOG、EDGE的中断*/
#define ETS_TG1_LACT_EDGE_INTR_SOURCE           65/**<TIMER_GROUP0、LACT、EDGE中断*/
#define ETS_MMU_IA_INTR_SOURCE                  66/**<MMU无效访问中断，LEVEL*/
#define ETS_MPU_IA_INTR_SOURCE                  67/**<中断MPU无效访问，LEVEL*/
#define ETS_CACHE_IA_INTR_SOURCE                68/**<缓存无效访问中断，LEVEL*/
#define ETS_MAX_INTR_SOURCE                     69/**<中断源总数*/

#if CONFIG_ESP_SYSTEM_CHECK_INT_LEVEL_5
//中断cpu使用表，请参阅核心isa.h
/*************************************************************************************************************
 *      Intr num Level Type PRO CPU使用率APP CPU uaage 0 1外部级别WMAC保留1 1外部级别BT/BLE主机HCI DMA BT/BLE主HCI DMA 2 1外部级别3 1外部级别4 1外部级别WBB 5 1外部级别6 1计时器FreeRTOS Tick（L1）FreeRTOS（L1）7 1软件BT/BLE VHCI BT/BLE VHFI 8 1外部级别BT/BLE BB（RX/TX）BT/BLE BB9 1外部级别10 1外部边缘11 3配置12 1外部级别13 1外部级别14 7 nmi保留15 3计时器FreeRTOS Tick（L3）FreeRTOS Tick（L3）16 5计时器保留17 1外部级别18 1外部级别19 2外部级别20 2外部级别21 2外部级别22 3外部边缘23 3外部级别24 4外部级别25 4外部级别BT/BLE控制器BT/BLE控制器26 5外部级别TG1_WDT&CACHEERR 27 3外部级别保留28 4外部边缘29 3软件BT/BLE hli BT/BLE heli 30 4外部边缘保留31 5外部级别IPC_ISR IPC_ISR
 *************************************************************************************************************
 */

//CPU0中断号码已保留，请勿触摸。
#define ETS_WMAC_INUM                           0
#define ETS_BT_HOST_INUM                        1
#define ETS_WBB_INUM                            4
#define ETS_TG0_T1_INUM                         10 /**<使用边缘中断*/
#define ETS_FRC1_INUM                           22
#define ETS_T1_WDT_CACHEERR_INUM                26
#define ETS_T1_WDT_INUM                         ETS_T1_WDT_CACHEERR_INUM
#define ETS_MEMACCESS_ERR_INUM                  ETS_T1_WDT_CACHEERR_INUM
/* 仅向后兼容，请改用ETS_MEMACCESS_ERR_INUM*/
#define ETS_CACHEERR_INUM                       ETS_MEMACCESS_ERR_INUM
#define ETS_IPC_ISR_INUM                        31

#elif CONFIG_ESP_SYSTEM_CHECK_INT_LEVEL_4

//中断cpu使用表，请参阅核心isa.h
/*************************************************************************************************************
 *      Intr num Level Type PRO CPU使用率APP CPU uaage 0 1外部级别WMAC保留1 1外部级别BT/BLE主机HCI DMA BT/BLE主HCI DMA 2 1外部级别3 1外部级别4 1外部级别WBB 5 1外部级别BT/BLE控制器BT/BLE控制器6 1计时器FreeRTOS Tick（L1）FreeRTOS Tick（L1）7 1软件BT/BLE VHCI BT/BLE VHCI8 1外部级别BT/BLE BB（RX/TX）BT/BLE BB（RX/TX）9 1外部级别10 1外部边缘11 3评测12 1外部级别13 1外部级别14 7 nmi保留15 3计时器FreeRTOS Tick（L3）FreeRTOS Thick（L3）16 5计时器17 1外部级别18 1外部级别19 2外部级别20 2外部级别21 2外部级别22 3外部边缘23 3外部级别24 4外部级别TG1_WDT 25 4外部级别CACHEERR 26 5外部级别27 3外部级别保留28 4外部边缘IPC_ISR IPC_ISR 29 3软件保留30 4外部边缘保留31 5外部级别
 *************************************************************************************************************
 */

//CPU0中断号码已保留，请勿触摸。
#define ETS_WMAC_INUM                           0
#define ETS_BT_HOST_INUM                        1
#define ETS_WBB_INUM                            4
#define ETS_TG0_T1_INUM                         10 /**<使用边缘中断*/
#define ETS_FRC1_INUM                           22
#define ETS_T1_WDT_INUM                         24
#define ETS_MEMACCESS_ERR_INUM                  25
/* 仅向后兼容，请改用ETS_MEMACCESS_ERR_INUM*/
#define ETS_CACHEERR_INUM                       ETS_MEMACCESS_ERR_INUM
#define ETS_IPC_ISR_INUM                        28

#endif /* CONFIG_ESP_SYSTEM_CHECK_INT_LEVEL_5 */

//ROM中使用的CPU0中断号，应在SDK中取消
#define ETS_SLC_INUM                            1
#define ETS_UART0_INUM                          5
#define ETS_UART1_INUM                          5
//其他中断号应由用户管理

//数字中断矩阵的中断无效
#define ETS_INVALID_INUM                        6

