// 版权所有2010-2017 Espressif Systems（上海）私人有限公司
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

#ifndef _DPORT_ACCESS_H_
#define _DPORT_ACCESS_H_

#include <stdint.h>

#include "esp_attr.h"
#include "esp32/dport_access.h"

#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

//寄存器操作{{

// _DPORT_xxx寄存器读取宏直接访问DPORT内存（与
// 应用SMP安全保护的DPORT_REG_READ）。
//
// 有几种读取DPORT寄存器的方法：
// 1） 在IDF应用程序中使用DPORT_REG_READ版本以确保SMP安全。
//    此方法使用预读APB实现（*），而不暂停其他CPU。
//    这对单次读数有利。
// 2） 如果您想对缓冲区进行一系列DPORT读取，
//    使用dport_read_buffer（buff_out，地址，num_word），
//    这是一种更快的方法，它不会停止其他CPU。
// 3） 如果您想进行一系列DPORT读取，但不想停止其他CPU
//    如果您想更快地完成，则需要使用DPORT_SEQUENCE_REG_READ（）。
//    与第一种不同的是，用户自己必须在DPORT读取时禁用中断。
//    注意，只有当芯片有两个内核时，才需要禁用中断。
// 4） 如果要进行DPORT读取序列，
//    显式使用DPORT_STALL_OTHER_PU_START（）宏
//    然后在其他CPU停止时使用_DPORT_REG_READ宏。
//    完成读取操作后，使用DPORT_STALL_OTHER_PU_END（）。
//    此方法在读取DPORT寄存器时使用暂停其他CPU。
//    对兼容性以及大的连续读数有用。
//    此方法较慢，但如果ROM功能或
//    调用访问DPORT而无需任何其他解决方法的其他代码。
// *)读取DPORT寄存器之前的预读APB寄存器
//    有助于同步两个CPU的操作，
//    使得不同CPU上的读取不再导致随机错误APB寄存器。

// _DPORT_REG_WRITE和DPORT_REG-WRITE等效。
#define _DPORT_REG_READ(_r)        (*(volatile uint32_t *)(_r))
#define _DPORT_REG_WRITE(_r, _v)   (*(volatile uint32_t *)(_r)) = (_v)

// 将值写入DPORT寄存器（不需要保护）
#define DPORT_REG_WRITE(_r, _v)   _DPORT_REG_WRITE((_r), (_v))

/**
 * @brief 从寄存器读取值，SMP安全版本。
 *
 * 该方法在读取DPORT的寄存器之前使用APB寄存器的预读取。此实现对于读取DORT寄存器以进行单次读取而无需暂停其他CPU非常有用。存在禁用/启用中断。
 *
 * @param reg 注册地址
 * @return 价值
 */
static inline uint32_t IRAM_ATTR DPORT_REG_READ(uint32_t reg)
{
#if defined(BOOTLOADER_BUILD) || !defined(CONFIG_ESP32_DPORT_WORKAROUND) || !defined(ESP_PLATFORM)
    return _DPORT_REG_READ(reg);
#else
    return esp_dport_access_reg_read(reg);
#endif
}

/**
 * @brief 从寄存器读取值，而不是SMP安全版本。
 *
 * 该方法在读取DPORT的寄存器之前使用APB寄存器的预读取。没有禁用/启用中断。与DPORT_REG_READ（）的区别在于，用户自己必须在DPORT读取时禁用中断。这种实现对于在循环中读取DORT寄存器而不停止其他CPU非常有用。请注意用法示例。建议使用esp_dport_read_buffer（buff_out，address，num_words）方法按顺序读取寄存器，而不暂停其他CPU。它允许您读取缓冲区中的寄存器。
 *
 * \code｛c｝//此示例演示如何使用它。｛//使用大括号限制宏DPORT_INTERRUPT_DISABLE/RESTORE.DPORT_INTERRUPT_DDISABLE（）中变量的可见性；//仅在当前CPU上禁用中断。for（i=0；i<max；++i）｛array[i]=DPORT_SEQUENCE_REG_READ（地址+i 4）；//读取DPORT寄存器｝DPORT_INTERRUPT_RESTORE（）；//恢复上一中断级别｛\endcode
 *
 * @param reg 注册地址
 * @return 价值
 */
static inline uint32_t IRAM_ATTR DPORT_SEQUENCE_REG_READ(uint32_t reg)
{
#if defined(BOOTLOADER_BUILD) || !defined(CONFIG_ESP32_DPORT_WORKAROUND) || !defined(ESP_PLATFORM)
    return _DPORT_REG_READ(reg);
#else
    return esp_dport_access_sequence_reg_read(reg);
#endif
}

//获取位或从寄存器中获取位
#define DPORT_REG_GET_BIT(_r, _b)  (DPORT_REG_READ(_r) & (_b))

//设置位或将位设置到寄存器
#define DPORT_REG_SET_BIT(_r, _b)  DPORT_REG_WRITE((_r), (DPORT_REG_READ(_r)|(_b)))

//寄存器的清除位或清除位
#define DPORT_REG_CLR_BIT(_r, _b)  DPORT_REG_WRITE((_r), (DPORT_REG_READ(_r) & (~(_b))))

//掩码控制寄存器的置位
#define DPORT_REG_SET_BITS(_r, _b, _m) DPORT_REG_WRITE((_r), ((DPORT_REG_READ(_r) & (~(_m))) | ((_b) & (_m))))

//从寄存器中获取字段，使用字段_S&_V确定掩码
#define DPORT_REG_GET_FIELD(_r, _f) ((DPORT_REG_READ(_r) >> (_f##_S)) & (_f##_V))

//将字段设置为寄存器，当_f未左移_f###_S时使用
#define DPORT_REG_SET_FIELD(_r, _f, _v) DPORT_REG_WRITE((_r), ((DPORT_REG_READ(_r) & (~((_f##_V) << (_f##_S))))|(((_v) & (_f##_V))<<(_f##_S))))

//从变量中获取字段值，当_f未左移_f###_S时使用
#define DPORT_VALUE_GET_FIELD(_r, _f) (((_r) >> (_f##_S)) & (_f))

//从变量中获取字段值，当_f左移_f###_S时使用
#define DPORT_VALUE_GET_FIELD2(_r, _f) (((_r) & (_f))>> (_f##_S))

//将字段值设置为变量，当_f未左移_f###_S时使用
#define DPORT_VALUE_SET_FIELD(_r, _f, _v) ((_r)=(((_r) & ~((_f) << (_f##_S)))|((_v)<<(_f##_S))))

//将字段值设置为变量，当_f左移_f###_S时使用
#define DPORT_VALUE_SET_FIELD2(_r, _f, _v) ((_r)=(((_r) & ~(_f))|((_v)<<(_f##_S))))

//从字段值生成值，当_f未左移_f###_S时使用
#define DPORT_FIELD_TO_VALUE(_f, _v) (((_v)&(_f))<<_f##_S)

//从字段值生成值，当_f左移_f###_S时使用
#define DPORT_FIELD_TO_VALUE2(_f, _v) (((_v)<<_f##_S) & (_f))

//注册带有下划线前缀的读取宏可以直接访问DPORT内存。在IDF应用程序中，使用非下划线版本以确保SMP安全。
#define _DPORT_READ_PERI_REG(addr) (*((volatile uint32_t *)(addr)))
#define _DPORT_WRITE_PERI_REG(addr, val) (*((volatile uint32_t *)(addr))) = (uint32_t)(val)
#define _DPORT_REG_SET_BIT(_r, _b)  _DPORT_REG_WRITE((_r), (_DPORT_REG_READ(_r)|(_b)))
#define _DPORT_REG_CLR_BIT(_r, _b)  _DPORT_REG_WRITE((_r), (_DPORT_REG_READ(_r) & (~(_b))))

/**
 * @brief 从寄存器读取值，SMP安全版本。
 *
 * 该方法在读取DPORT的寄存器之前使用APB寄存器的预读取。此实现对于读取DORT寄存器以进行单次读取而无需暂停其他CPU非常有用。
 *
 * @param reg 注册地址
 * @return 价值
 */
static inline uint32_t IRAM_ATTR DPORT_READ_PERI_REG(uint32_t reg)
{
#if defined(BOOTLOADER_BUILD) || !defined(CONFIG_ESP32_DPORT_WORKAROUND) || !defined(ESP_PLATFORM)
    return _DPORT_REG_READ(reg);
#else
    return esp_dport_access_reg_read(reg);
#endif
}

//将值写入寄存器
#define DPORT_WRITE_PERI_REG(addr, val) _DPORT_WRITE_PERI_REG((addr), (val))

//掩码控制寄存器的清除位
#define DPORT_CLEAR_PERI_REG_MASK(reg, mask) DPORT_WRITE_PERI_REG((reg), (DPORT_READ_PERI_REG(reg)&(~(mask))))

//掩码控制寄存器的置位
#define DPORT_SET_PERI_REG_MASK(reg, mask)   DPORT_WRITE_PERI_REG((reg), (DPORT_READ_PERI_REG(reg)|(mask)))

//获取掩码控制的寄存器位
#define DPORT_GET_PERI_REG_MASK(reg, mask)   (DPORT_READ_PERI_REG(reg) & (mask))

//获取由最高位和最低位控制的寄存器位
#define DPORT_GET_PERI_REG_BITS(reg, hipos,lowpos)     ((DPORT_READ_PERI_REG(reg)>>(lowpos))&((1<<((hipos)-(lowpos)+1))-1))

//由掩码和移位控制的寄存器的置位
#define DPORT_SET_PERI_REG_BITS(reg,bit_map,value,shift) DPORT_WRITE_PERI_REG((reg), ((DPORT_READ_PERI_REG(reg)&(~((bit_map)<<(shift))))|(((value) & bit_map)<<(shift))))

//获取寄存器字段
#define DPORT_GET_PERI_REG_BITS2(reg, mask,shift)      ((DPORT_READ_PERI_REG(reg)>>(shift))&(mask))
//}}

#ifdef __cplusplus
}
#endif

#endif /* _DPORT_ACCESS_H_ */

