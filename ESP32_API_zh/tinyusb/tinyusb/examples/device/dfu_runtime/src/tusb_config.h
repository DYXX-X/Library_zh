/*
 * 用户配置h
 *
 *  创建日期：2019年10月28日作者：Sylvain Munaut
 */

#ifndef TUSB_CONFIG_H_
#define TUSB_CONFIG_H_

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------
// COMMON CONFIGURATION
//--------------------------------------------------------------------

// 由board.mk定义
#ifndef CFG_TUSB_MCU
  #error CFG_TUSB_MCU must be defined
#endif

// 用于设备的RH端口号可由板定义。mk，默认为端口0
#ifndef BOARD_DEVICE_RHPORT_NUM
  #define BOARD_DEVICE_RHPORT_NUM     0
#endif

// RHPort最大运行速度可由board.mk定义
// 对于具有内部高速PHY的MCU，默认为高速（可以是端口特定的），否则为全速
#ifndef BOARD_DEVICE_RHPORT_SPEED
  #if (CFG_TUSB_MCU == OPT_MCU_LPC18XX || CFG_TUSB_MCU == OPT_MCU_LPC43XX || CFG_TUSB_MCU == OPT_MCU_MIMXRT10XX || \
       CFG_TUSB_MCU == OPT_MCU_NUC505  || CFG_TUSB_MCU == OPT_MCU_CXD56)
    #define BOARD_DEVICE_RHPORT_SPEED   OPT_MODE_HIGH_SPEED
  #else
    #define BOARD_DEVICE_RHPORT_SPEED   OPT_MODE_FULL_SPEED
  #endif
#endif

// 设备模式，rhport和速度由board.mk定义
#if   BOARD_DEVICE_RHPORT_NUM == 0
  #define CFG_TUSB_RHPORT0_MODE     (OPT_MODE_DEVICE | BOARD_DEVICE_RHPORT_SPEED)
#elif BOARD_DEVICE_RHPORT_NUM == 1
  #define CFG_TUSB_RHPORT1_MODE     (OPT_MODE_DEVICE | BOARD_DEVICE_RHPORT_SPEED)
#else
  #error "Incorrect RHPort configuration"
#endif

#ifndef CFG_TUSB_OS
#define CFG_TUSB_OS               OPT_OS_NONE
#endif

// CFG_TUSB_DEBUG由编译器在DEBUG构建中定义
// #定义CFG_TUSB_DEBUG 0

/* 某些MCU上的USB DMA只能访问特定的SRAM区域，但对对齐有限制。Tinyusb使用以下宏声明传输内存，以便将它们放入特定的部分。例如
 * -CFG_TUSB_MEM节：__attribute__（节（“.usb_ram”））
 * -CFG_TUSB_MEM_ALIGN:__属性__（对齐（4））
 */
#ifndef CFG_TUSB_MEM_SECTION
#define CFG_TUSB_MEM_SECTION
#endif

#ifndef CFG_TUSB_MEM_ALIGN
#define CFG_TUSB_MEM_ALIGN          __attribute__ ((aligned(4)))
#endif

//--------------------------------------------------------------------
// DEVICE CONFIGURATION
//--------------------------------------------------------------------

#ifndef CFG_TUD_ENDPOINT0_SIZE
#define CFG_TUD_ENDPOINT0_SIZE    64
#endif

//------------- CLASS -------------//

#define CFG_TUD_DFU_RUNTIME 1

#ifdef __cplusplus
 }
#endif

#endif /* TUSB_CONFIG_H_ */

