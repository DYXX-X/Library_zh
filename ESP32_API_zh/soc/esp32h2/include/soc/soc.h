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

#ifndef __ASSEMBLER__
#include <stdint.h>
#include "esp_assert.h"
#include "esp_bit_defs.h"
#endif

#include "sdkconfig.h"

#define PRO_CPU_NUM (0)

#define DR_REG_SYSTEM_BASE                      0x600c0000
#define DR_REG_SENSITIVE_BASE                   0x600c1000
#define DR_REG_INTERRUPT_BASE                   0x600c2000
#define DR_REG_EXTMEM_BASE                      0x600c4000
#define DR_REG_MMU_TABLE                        0x600c5000

#define DR_REG_ITAG_TABLE                       0x600c6000
#define DR_REG_DTAG_TABLE                       0x600c8000
#define DR_REG_ECC_MULT_BASE                    0x60039000
#define DR_REG_AES_BASE                         0x6003a000
#define DR_REG_SHA_BASE                         0x6003b000
#define DR_REG_RSA_BASE                         0x6003c000
#define DR_REG_DIGITAL_SIGNATURE_BASE           0x6003d000
#define DR_REG_HMAC_BASE                        0x6003e000
#define DR_REG_GDMA_BASE                        0x6003f000

#define DR_REG_ASSIST_DEBUG_BASE                0x600ce000
#define DR_REG_DEDICATED_GPIO_BASE              0x600cf000
#define DR_REG_WORLD_CNTL_BASE                  0x600d0000
// #定义DR_REG_DPORT_END 0x600d3FFC
#define DR_REG_UART_BASE                        0x60000000
#define DR_REG_SPI1_BASE                        0x60002000
#define DR_REG_SPI0_BASE                        0x60003000
#define DR_REG_GPIO_BASE                        0x60004000
#define DR_REG_GPIO_SD_BASE                     0x60004f00
#define DR_REG_FE2_BASE                         0x60005000
#define DR_REG_FE_BASE                          0x60006000
#define DR_REG_FRC_TIMER_BASE                   0x60007000
#define DR_REG_RTCCNTL_BASE                     0x60008000
#define DR_REG_RTCIO_BASE                       0x60008400
#define DR_REG_SENS_BASE                        0x60008800
#define DR_REG_RTC_I2C_BASE                     0x60008C00
#define DR_REG_IO_MUX_BASE                      0x60009000
#define DR_REG_HINF_BASE                        0x6002B000
#define DR_REG_UHCI1_BASE                       0x6000C000
#define DR_REG_I2S_BASE                         0x6000F000
#define DR_REG_UART1_BASE                       0x60010000
#define DR_REG_BT_BASE                          0x60011000
#define DR_REG_I2C_EXT_BASE                     0x60013000
#define DR_REG_UHCI0_BASE                       0x60014000
#define DR_REG_SLCHOST_BASE                     0x60019000
#define DR_REG_RMT_BASE                         0x60016000
#define DR_REG_SLC_BASE                         0x6002D000
#define DR_REG_LEDC_BASE                        0x60019000
#define DR_REG_EFUSE_BASE                       0x6001A000
#define DR_REG_NRX_BASE                         0x6001CC00
#define DR_REG_BB_BASE                          0x6001D000
#define DR_REG_PWM_BASE                         0x6001E000
#define DR_REG_TIMERGROUP0_BASE                 0x6001F000
#define DR_REG_TIMERGROUP1_BASE                 0x60020000
#define DR_REG_RTC_SLOWMEM_BASE                 0x60021000
#define DR_REG_SYS_TIMER_BASE                   0x60023000
#define DR_REG_SPI2_BASE                        0x60024000
#define DR_REG_SPI3_BASE                        0x60025000
#define DR_REG_SYSCON_BASE                      0x60026000
#define DR_REG_I2C1_EXT_BASE                    0x60027000
#define DR_REG_SDMMC_BASE                       0x60028000
#define DR_REG_CAN_BASE                         0x6002B000
#define DR_REG_PWM1_BASE                        0x6002C000
#define DR_REG_I2S1_BASE                        0x6002D000
#define DR_REG_UART2_BASE                       0x6002E000
#define DR_REG_PWM2_BASE                        0x6002F000
#define DR_REG_PWM3_BASE                        0x60030000
#define DR_REG_SPI4_BASE                        0x60037000
#define DR_REG_USB_WRAP_BASE                    0x60039000
#define DR_REG_APB_SARADC_BASE                  0x60040000
#define DR_REG_LCD_CAM_BASE                     0x60041000
#define DR_REG_AES_XTS_BASE                     0x600CC000
#define DR_REG_USB_DEVICE_BASE                  0x60043000
#define DR_REG_CLKRST_BASE                      0x6004B000


#define REG_UHCI_BASE(i)         (DR_REG_UHCI0_BASE - (i) * 0x8000)
#define REG_UART_BASE( i )  (DR_REG_UART_BASE + (i) * 0x10000 + ( (i) > 1 ? 0xe000 : 0 ) )
#define REG_UART_AHB_BASE(i)  (0x60000000 + (i) * 0x10000 + ( (i) > 1 ? 0xe000 : 0 ) )
#define UART_FIFO_AHB_REG(i)  (REG_UART_AHB_BASE(i) + 0x0)
#define REG_I2S_BASE( i ) (DR_REG_I2S_BASE + (i) * 0x1E000)
#define REG_TIMG_BASE(i)              (DR_REG_TIMERGROUP0_BASE + (i)*0x1000)
#define REG_SPI_MEM_BASE(i)     (DR_REG_SPI0_BASE - (i) * 0x1000)
#define REG_I2C_BASE(i)    (DR_REG_I2C_EXT_BASE + (i) * 0x14000 )

//寄存器操作{{
#define ETS_UNCACHED_ADDR(addr) (addr)
#define ETS_CACHED_ADDR(addr) (addr)

#ifndef __ASSEMBLER__
#define BIT(nr)                 (1UL << (nr))
#else
#define BIT(nr)                 (1 << (nr))
#endif

#ifndef __ASSEMBLER__

//将值写入寄存器
#define REG_WRITE(_r, _v) ({                                                                                           \
            (*(volatile uint32_t *)(_r)) = (_v);                                                                       \
        })

//从寄存器读取值
#define REG_READ(_r) ({                                                                                                \
            (*(volatile uint32_t *)(_r));                                                                              \
        })

//获取位或从寄存器中获取位
#define REG_GET_BIT(_r, _b)  ({                                                                                        \
            (*(volatile uint32_t*)(_r) & (_b));                                                                        \
        })

//设置位或将位设置到寄存器
#define REG_SET_BIT(_r, _b)  ({                                                                                        \
            (*(volatile uint32_t*)(_r) |= (_b));                                                                       \
        })

//寄存器的清除位或清除位
#define REG_CLR_BIT(_r, _b)  ({                                                                                        \
            (*(volatile uint32_t*)(_r) &= ~(_b));                                                                      \
        })

//掩码控制寄存器的置位
#define REG_SET_BITS(_r, _b, _m) ({                                                                                    \
            (*(volatile uint32_t*)(_r) = (*(volatile uint32_t*)(_r) & ~(_m)) | ((_b) & (_m)));                         \
        })

//从寄存器中获取字段，使用字段_S&_V确定掩码
#define REG_GET_FIELD(_r, _f) ({                                                                                       \
            ((REG_READ(_r) >> (_f##_S)) & (_f##_V));                                                                   \
        })

//从变量设置寄存器的字段，使用字段_S&_V确定掩码
#define REG_SET_FIELD(_r, _f, _v) ({                                                                                   \
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
            (*((volatile uint32_t *)ETS_UNCACHED_ADDR(addr)));                                                         \
        })

//将值写入寄存器
#define WRITE_PERI_REG(addr, val) ({                                                                                   \
            (*((volatile uint32_t *)ETS_UNCACHED_ADDR(addr))) = (uint32_t)(val);                                       \
        })

//掩码控制寄存器的清除位
#define CLEAR_PERI_REG_MASK(reg, mask) ({                                                                              \
            WRITE_PERI_REG((reg), (READ_PERI_REG(reg)&(~(mask))));                                                     \
        })

//掩码控制寄存器的置位
#define SET_PERI_REG_MASK(reg, mask) ({                                                                                \
            WRITE_PERI_REG((reg), (READ_PERI_REG(reg)|(mask)));                                                        \
        })

//获取掩码控制的寄存器位
#define GET_PERI_REG_MASK(reg, mask) ({                                                                                \
            (READ_PERI_REG(reg) & (mask));                                                                             \
        })

//获取由最高位和最低位控制的寄存器位
#define GET_PERI_REG_BITS(reg, hipos,lowpos) ({                                                                        \
            ((READ_PERI_REG(reg)>>(lowpos))&((1<<((hipos)-(lowpos)+1))-1));                                            \
        })

//由掩码和移位控制的寄存器的置位
#define SET_PERI_REG_BITS(reg,bit_map,value,shift) ({                                                                  \
            (WRITE_PERI_REG((reg),(READ_PERI_REG(reg)&(~((bit_map)<<(shift))))|(((value) & bit_map)<<(shift)) ));      \
        })

//获取寄存器字段
#define GET_PERI_REG_BITS2(reg, mask,shift) ({                                                                         \
            ((READ_PERI_REG(reg)>>(shift))&(mask));                                                                    \
        })

#endif /* !__ASSEMBLER__ */
//}}

//外围时钟{{
#define  APB_CLK_FREQ_ROM                            ( 32*1000000 )
#define  CPU_CLK_FREQ_ROM                            APB_CLK_FREQ_ROM
#define  UART_CLK_FREQ_ROM                           ( 32*1000000)
#define  EFUSE_CLK_FREQ_ROM                          ( 20*1000000)
#define  CPU_CLK_FREQ                                APB_CLK_FREQ
#if CONFIG_IDF_ENV_FPGA
#define  APB_CLK_FREQ                                ( 32*1000000 )
#else
#define  APB_CLK_FREQ                                ( 48*1000000 )         //ESP32H2-TODO: IDF-3786
#endif
#define  REF_CLK_FREQ                                ( 1000000 )
#define  RTC_CLK_FREQ                                (17.5*1000000)
#define  XTAL_CLK_FREQ                               (32*1000000)
#define  UART_CLK_FREQ                               APB_CLK_FREQ
#define  WDT_CLK_FREQ                                APB_CLK_FREQ
#define  TIMER_CLK_FREQ                              (80000000>>4) //80MHz除以16
#define  SPI_CLK_DIV                                 4
#define  TICKS_PER_US_ROM                            40              // CPU为80MHz
#define  GPIO_MATRIX_DELAY_NS                        0
//}}

/* 总体内存映射*/
#define SOC_DROM_LOW    0x3C000000
#define SOC_DROM_HIGH   0x3C800000
#define SOC_IROM_LOW    0x42000000
#define SOC_IROM_HIGH   0x42800000
#define SOC_IROM_MASK_LOW  0x40000000
#define SOC_IROM_MASK_HIGH 0x40060000
#define SOC_DROM_MASK_LOW 0x3FF00000
#define SOC_DROM_MASK_HIGH 0x3FF20000
#define SOC_IRAM_LOW    0x4037C000
#define SOC_IRAM_HIGH   0x403E0000
#define SOC_DRAM_LOW    0x3FC80000
#define SOC_DRAM_HIGH   0x3FCE0000
#define SOC_RTC_IRAM_LOW  0x50000000 // ESP32-H2只有RTC慢速内存
#define SOC_RTC_IRAM_HIGH 0x50002000
#define SOC_RTC_DRAM_LOW  0x50000000
#define SOC_RTC_DRAM_HIGH 0x50002000
#define SOC_RTC_DATA_LOW  0x50000000
#define SOC_RTC_DATA_HIGH 0x50002000

//D/IRAM区域的第一个和最后一个字，用于DRAM地址和IRAM别名。
#define SOC_DIRAM_IRAM_LOW    0x40380000
#define SOC_DIRAM_IRAM_HIGH   0x403E0000
#define SOC_DIRAM_DRAM_LOW    0x3FC80000
#define SOC_DIRAM_DRAM_HIGH   0x3FCE0000

// 可通过DMA访问的内存区域。请参见esp_ptr_dma_capable（）。
#define SOC_DMA_LOW  0x3FC88000
#define SOC_DMA_HIGH 0x3FD00000

// 字节可访问的RAM区域。请参见esp_ptr_byte_accessible（）。
#define SOC_BYTE_ACCESSIBLE_LOW     0x3FC88000
#define SOC_BYTE_ACCESSIBLE_HIGH    0x3FD00000

//内部内存区域，与ESP32 CPU位于同一硅片上
//（不包括单独检查的RTC数据区域。）请参阅esp_ptr_internal（）。
#define SOC_MEM_INTERNAL_LOW        0x3FC80000
#define SOC_MEM_INTERNAL_HIGH       0x3FCE0000
#define SOC_MEM_INTERNAL_LOW1       0x40370000
#define SOC_MEM_INTERNAL_HIGH1      0x403E0000
#define SOC_MEM_INTERNAL_LOW2       0x600FE000
#define SOC_MEM_INTERNAL_HIGH2      0x60100000

#define SOC_MAX_CONTIGUOUS_RAM_SIZE (SOC_IRAM_HIGH - SOC_IRAM_LOW) ///<地址空间中连续内存（DRAM或IRAM）的最大跨度

// 存储外围设备的地址空间区域
#define SOC_PERIPHERAL_LOW 0x60000000
#define SOC_PERIPHERAL_HIGH 0x60100000

// 调试区域，软件未使用
#define SOC_DEBUG_LOW 0x20000000
#define SOC_DEBUG_HIGH 0x28000000

// ROM引导堆栈的开始（最高地址），仅在早期引导期间相关
#define SOC_ROM_STACK_START         0x3fcebf10

//在RISC-V CPU上，中断源都是外部中断，其类型、源和优先级由软件配置。
//没有HW NMI概念。SW应通过INT_THRESH_REG控制屏蔽电平。

//CPU0 riscv/vector中保留的中断号。S、 不要碰这个。
#define ETS_T1_WDT_INUM                         24
#define ETS_CACHEERR_INUM                       25
#define ETS_MEMPROT_ERR_INUM                    26
//CPU0最大有效中断数
#define ETS_MAX_INUM                            31

//ROM中使用的CPU0中断号，应在SDK中取消
#define ETS_SLC_INUM                            1
#define ETS_UART0_INUM                          5
#define ETS_UART1_INUM                          5
#define ETS_SPI2_INUM                           1
//CPU0中断号仅在调用模块初始化函数时在ROM代码中使用，此处应注意。
#define ETS_GPIO_INUM       4

//其他中断号应由用户管理

//数字中断矩阵的中断无效
#define ETS_INVALID_INUM                        0

//中断中等级别，例如用于INT WDT
#define SOC_INTERRUPT_LEVEL_MEDIUM              4

