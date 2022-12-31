// 版权所有2010-2018 Espressif Systems（上海）私人有限公司
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
#include "esp_bit_defs.h"
#endif

#define PRO_CPU_NUM (0)

#define SOC_MAX_CONTIGUOUS_RAM_SIZE (SOC_EXTRAM_DATA_HIGH - SOC_EXTRAM_DATA_LOW) ///<地址空间中连续内存（DRAM或IRAM）的最大跨度

#define DR_REG_SYSTEM_BASE                      0x3f4c0000
#define DR_REG_SENSITIVE_BASE                   0x3f4c1000
#define DR_REG_INTERRUPT_BASE                   0x3f4c2000
#define DR_REG_DMA_COPY_BASE                    0x3f4c3000
#define DR_REG_EXTMEM_BASE                      0x61800000
#define DR_REG_MMU_TABLE                        0x61801000
#define DR_REG_ITAG_TABLE                       0x61802000
#define DR_REG_DTAG_TABLE                       0x61803000
#define DR_REG_AES_BASE                         0x6003a000
#define DR_REG_SHA_BASE                         0x6003b000
#define DR_REG_RSA_BASE                         0x6003c000
#define DR_REG_HMAC_BASE                        0x6003e000
#define DR_REG_DIGITAL_SIGNATURE_BASE           0x6003d000
#define DR_REG_CRYPTO_DMA_BASE                  0x6003f000
#define DR_REG_ASSIST_DEBUG_BASE                0x3f4ce000
#define DR_REG_DEDICATED_GPIO_BASE              0x3f4cf000
#define DR_REG_INTRUSION_BASE                   0x3f4d0000
#define DR_REG_DPORT_END                        0x3f4d3FFC
#define DR_REG_UART_BASE                        0x3f400000
#define DR_REG_SPI1_BASE                        0x3f402000
#define DR_REG_SPI0_BASE                        0x3f403000
#define DR_REG_GPIO_BASE                        0x3f404000
#define DR_REG_GPIO_SD_BASE                     0x3f404f00
#define DR_REG_FE2_BASE                         0x3f405000
#define DR_REG_FE_BASE                          0x3f406000
#define DR_REG_FRC_TIMER_BASE                   0x3f407000
#define DR_REG_RTCCNTL_BASE                     0x3f408000
#define DR_REG_RTCIO_BASE                       0x3f408400
#define DR_REG_SENS_BASE                        0x3f408800
#define DR_REG_RTC_I2C_BASE                     0x3f408C00
#define DR_REG_IO_MUX_BASE                      0x3f409000
#define DR_REG_HINF_BASE                        0x3f40B000
#define DR_REG_I2S_BASE                         0x3f40F000
#define DR_REG_UART1_BASE                       0x3f410000
#define DR_REG_I2C_EXT_BASE                     0x3f413000
#define DR_REG_UHCI0_BASE                       0x3f414000
#define DR_REG_SLCHOST_BASE                     0x3f415000
#define DR_REG_RMT_BASE                         0x3f416000
#define DR_REG_PCNT_BASE                        0x3f417000
#define DR_REG_SLC_BASE                         0x3f418000
#define DR_REG_LEDC_BASE                        0x3f419000
#define DR_REG_CP_BASE                          0x3f4c3000
#define DR_REG_EFUSE_BASE                       0x3f41A000
#define DR_REG_NRX_BASE                         0x3f41CC00
#define DR_REG_BB_BASE                          0x3f41D000
#define DR_REG_TIMERGROUP0_BASE                 0x3f41F000
#define DR_REG_TIMERGROUP1_BASE                 0x3f420000
#define DR_REG_RTC_SLOWMEM_BASE                 0x3f421000
#define DR_REG_SYSTIMER_BASE                    0x3f423000
#define DR_REG_SPI2_BASE                        0x3f424000
#define DR_REG_SPI3_BASE                        0x3f425000
#define DR_REG_SYSCON_BASE                      0x3f426000
#define DR_REG_APB_CTRL_BASE                    0x3f426000    /* SYSCON的旧名称，将被删除*/
#define DR_REG_I2C1_EXT_BASE                    0x3f427000
#define DR_REG_SPI4_BASE                        0x3f437000
#define DR_REG_USB_WRAP_BASE                    0x3f439000
#define DR_REG_APB_SARADC_BASE                  0x3f440000
#define DR_REG_USB_BASE                         0x60080000

#define REG_UHCI_BASE(i)         (DR_REG_UHCI0_BASE)
#define REG_UART_BASE( i )  (DR_REG_UART_BASE + (i) * 0x10000 )
#define REG_UART_AHB_BASE(i)  (0x60000000 + (i) * 0x10000 )
#define UART_FIFO_AHB_REG(i)  (REG_UART_AHB_BASE(i) + 0x0)
#define REG_I2S_BASE( i ) (DR_REG_I2S_BASE)
#define REG_TIMG_BASE(i)              (DR_REG_TIMERGROUP0_BASE + (i)*0x1000)
#define REG_SPI_MEM_BASE(i)     (DR_REG_SPI0_BASE - (i) * 0x1000)
#define REG_I2C_BASE(i)    (DR_REG_I2C_EXT_BASE + (i) * 0x14000 )

//在ulp-riscv项目中替换寄存器操作的便捷方式
//使用此文件
#ifndef ULP_RISCV_REGISTER_OPS

//寄存器操作{{
#define ETS_UNCACHED_ADDR(addr) (addr)
#define ETS_CACHED_ADDR(addr) (addr)

#ifndef __ASSEMBLER__
#define BIT(nr)                 (1UL << (nr))
#else
#define BIT(nr)                 (1 << (nr))
#endif

#ifndef __ASSEMBLER__

#define IS_DPORT_REG(_r) (((_r) >= DR_REG_DPORT_BASE) && (_r) <= DR_REG_DPORT_END)

#if !defined( BOOTLOADER_BUILD ) && !defined( CONFIG_FREERTOS_UNICORE ) && defined( ESP_PLATFORM )
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
#endif /* !ULP_RISCV_REGISTER_OPS */

//外围时钟{{
#define  APB_CLK_FREQ_ROM                            ( 40*1000000 )
#define  CPU_CLK_FREQ_ROM                            APB_CLK_FREQ_ROM
#define  UART_CLK_FREQ_ROM                           APB_CLK_FREQ_ROM
#define  CPU_CLK_FREQ                                APB_CLK_FREQ
#define  APB_CLK_FREQ                                ( 80*1000000 )       //单位：Hz
#define  REF_CLK_FREQ                                ( 1000000 )
#define  UART_CLK_FREQ                               APB_CLK_FREQ
#define  WDT_CLK_FREQ                                APB_CLK_FREQ
#define  TIMER_CLK_FREQ                              (80000000>>4) //80MHz除以16
#define  SPI_CLK_DIV                                 4
#define  TICKS_PER_US_ROM                            40              // CPU为80MHz
#define  GPIO_MATRIX_DELAY_NS                        0
//}}

/* 总体内存映射*/
#define SOC_DROM_LOW    0x3F000000/*icache的drom0低地址*/
#define SOC_DROM_HIGH   0x3FF80000/*dcache的dram0高地址*/
#define SOC_IROM_LOW    0x40080000
#define SOC_IROM_HIGH   0x40800000
#define SOC_IROM_MASK_LOW  0x40000000
#define SOC_IROM_MASK_HIGH 0x40020000
#define SOC_IRAM_LOW    0x40020000
#define SOC_IRAM_HIGH   0x40070000
#define SOC_DRAM_LOW    0x3FFB0000
#define SOC_DRAM_HIGH   0x40000000
#define SOC_RTC_IRAM_LOW  0x40070000
#define SOC_RTC_IRAM_HIGH 0x40072000
#define SOC_RTC_DRAM_LOW  0x3ff9e000
#define SOC_RTC_DRAM_HIGH 0x3ffa0000
#define SOC_RTC_DATA_LOW  0x50000000
#define SOC_RTC_DATA_HIGH 0x50002000
#define SOC_EXTRAM_DATA_LOW 0x3F500000
#define SOC_EXTRAM_DATA_HIGH 0x3FF80000

#define SOC_EXTRAM_DATA_SIZE (SOC_EXTRAM_DATA_HIGH - SOC_EXTRAM_DATA_LOW)

//D/IRAM区域的第一个和最后一个字，用于DRAM地址和IRAM别名。
#define SOC_DIRAM_IRAM_LOW    0x40020000
#define SOC_DIRAM_IRAM_HIGH   0x40070000
#define SOC_DIRAM_DRAM_LOW    0x3FFB0000
#define SOC_DIRAM_DRAM_HIGH   0x40000000

// 内部存储器中可通过DMA访问的存储器区域。请参见esp_ptr_dma_capable（）。
#define SOC_DMA_LOW  0x3FFB0000
#define SOC_DMA_HIGH 0x40000000

// 外部存储器中可通过DMA访问的存储器区域。请参见esp_ptr_dma_ext_capable（）。
#define SOC_DMA_EXT_LOW     0x3F500000
#define SOC_DMA_EXT_HIGH    0x3FF80000

// 字节可访问的内存区域。请参见esp_ptr_byte_accessible（）。
#define SOC_BYTE_ACCESSIBLE_LOW     0x3FF9E000
#define SOC_BYTE_ACCESSIBLE_HIGH    0x40000000

//内部内存区域，与ESP32 CPU位于同一硅片上
//（不包括单独检查的RTC数据区域。）请参阅esp_ptr_internal（）。
#define SOC_MEM_INTERNAL_LOW        0x3FF9E000
#define SOC_MEM_INTERNAL_HIGH       0x40072000

// ROM引导堆栈的开始（最高地址），仅在早期引导期间相关
#define SOC_ROM_STACK_START         0x3fffe70c

//中断cpu使用表，请参阅核心isa.h
/*************************************************************************************************************
 *      Intr num Level Type PRO CPU使用率0 1外部级别WMAC 1 1外部级别BT/BLE主机HCI DMA 2 1外部级别3 1外部级别4 1外部级别WBB 5 1外部级别BT/BLE控制器6 1计时器FreeRTOS Tick（L1）7 1软件BT/BLE VHCI 8 1外部级BT/BLE BB（RX/TX）9 1外部级别10 1外部边缘11 3评测12 1外部级别13 1外部级别14 7 nmi保留15 3计时器FreeRTOS Tick（L3）16 5计时器17 1外部级别18 1外部级别19 2外部级别20 2外部级别21 2外部级别22 3外部边缘23 3外部级别24 4外部级别TG1_WDT 25 4外部级别CACHEERR 26 5外部级别27 3外部级别保留28 4外部边缘保留29 3软件保留30 4外部边缘保存31 5外部级别
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

//ROM中使用的CPU0中断号，应在SDK中取消
#define ETS_SLC_INUM                            1
#define ETS_UART0_INUM                          5
#define ETS_UART1_INUM                          5
#define ETS_SPI2_INUM                           1
//CPU0中断号仅在调用模块初始化函数时在ROM代码中使用，此处应注意。
#define ETS_FRC_TIMER2_INUM 10 /* 使用边缘*/
#define ETS_GPIO_INUM       4

//其他中断号应由用户管理

//数字中断矩阵的中断无效
#define ETS_INVALID_INUM                        6

