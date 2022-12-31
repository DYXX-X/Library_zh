/**
 * 此文件由Apache newt版本1.9.0-dev生成
 */

#ifndef H_MYNEWT_SYSCFG_
#define H_MYNEWT_SYSCFG_

/**
 * 此宏的存在是为了确保代码在需要时包含此标头。如果代码通过ifdef直接检查设置是否存在，而不包含此标头，则设置宏将自动求值为0。相反，尝试使用这些宏而不包含该标头将导致编译器错误。
 */
#define MYNEWT_VAL(_name)                       MYNEWT_VAL_ ## _name
#define MYNEWT_VAL_CHOICE(_name, _val)          MYNEWT_VAL_ ## _name ## __ ## _val

#ifndef MYNEWT_VAL_RAM_RESIDENT
#define MYNEWT_VAL_RAM_RESIDENT (0)
#endif

#ifndef MYNEWT_VAL_MCU_GPIO_MAX_IRQ
#define MYNEWT_VAL_MCU_GPIO_MAX_IRQ (4)
#endif

#ifndef MYNEWT_VAL_MCU_GPIO_RETAINABLE_NUM
#define MYNEWT_VAL_MCU_GPIO_RETAINABLE_NUM (-1)
#endif

#ifndef MYNEWT_VAL_MCU_CLOCK_XTAL32M_SETTLE_TIME_US
#define MYNEWT_VAL_MCU_CLOCK_XTAL32M_SETTLE_TIME_US (2000)
#endif

#endif

