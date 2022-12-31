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
#define ULP_RISCV_REGISTER_OPS

#ifdef __cplusplus
extern "C" {
#endif


//寄存器操作{{

/*
 * 当COCPU访问RTC寄存器时，需要转换访问地址。当COCPU访问RTC内存时，不需要转换访问地址。
 */
#define WRITE_RTC_MEM(addr, val)    (*((volatile int*)(addr))) = (int) (val)
#define READ_RTC_MEM(addr)		    (*(volatile int*)(addr))

/*
 * 当COCPU访问RTC寄存器时，需要转换访问地址。当COCPU访问RTC内存时，不需要转换访问地址。
 */
#define RISCV_REG_CONV(addr)        (((addr&0xffff)<<3 & 0xe000) | (addr & 0x1fff) | 0x8000)
#define ETS_UNCACHED_ADDR(addr)     (RISCV_REG_CONV(addr))

#ifndef __ASSEMBLER__
#define BIT(nr)                 (1UL << (nr))
#else
#define BIT(nr)                 (1 << (nr))
#endif

//将值写入寄存器
#define REG_WRITE(_r, _v) ({                                                                                           \
            (*(volatile uint32_t *)RISCV_REG_CONV(_r)) = (_v);                                                                       \
        })

//从寄存器读取值
#define REG_READ(_r) ({                                                                                                \
            (*(volatile uint32_t *)RISCV_REG_CONV(_r));                                                                              \
        })

//获取位或从寄存器中获取位
#define REG_GET_BIT(_r, _b)  ({                                                                                        \
            (*(volatile uint32_t*)RISCV_REG_CONV(_r) & (_b));                                                                        \
        })

//设置位或将位设置到寄存器
#define REG_SET_BIT(_r, _b)  ({                                                                                        \
            (*(volatile uint32_t*)RISCV_REG_CONV(_r) |= (_b));                                                                       \
        })

//寄存器的清除位或清除位
#define REG_CLR_BIT(_r, _b)  ({                                                                                        \
            (*(volatile uint32_t*)RISCV_REG_CONV(_r) &= ~(_b));                                                                      \
        })

//掩码控制寄存器的置位
#define REG_SET_BITS(_r, _b, _m) ({                                                                                    \
            (*(volatile uint32_t*)RISCV_REG_CONV(_r) = (*(volatile uint32_t*)RISCV_REG_CONV(_r) & ~(_m)) | ((_b) & (_m)));                         \
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
// #定义GET_PERI_REG_BITS（REG，hipos，lowpos）({
//             ASSERT_IF_DPORT_REG（（REG），GET_PERI_REG_BITS）；
//             （（READ_PERI_REG（REG）>>（低位））&（（1UL<<（（低位）-（低位）+1））-1））；
//         })
#define GET_PERI_REG_BITS(reg, bit_map, shift)    ((READ_PERI_REG(reg))&((bit_map)<<(shift)))>>shift

//由掩码和移位控制的寄存器的置位
#define SET_PERI_REG_BITS(reg,bit_map,value,shift) ({                                                                  \
            (WRITE_PERI_REG((reg),(READ_PERI_REG(reg)&(~((bit_map)<<(shift))))|(((value) & bit_map)<<(shift)) ));      \
        })

//获取寄存器字段
#define GET_PERI_REG_BITS2(reg, mask,shift) ({                                                                         \
            ((READ_PERI_REG(reg)>>(shift))&(mask));                                                                    \
        })
//}}

#ifdef __cplusplus
}
#endif

