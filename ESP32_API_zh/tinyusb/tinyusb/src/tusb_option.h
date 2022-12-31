/*
 * MIT许可证（MIT）
 *
 * 版权所有（c）2019 Ha Thach（tinyusb.org）
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * 此文件是TinyUSB堆栈的一部分。
 */

#ifndef _TUSB_OPTION_H_
#define _TUSB_OPTION_H_

#define TUSB_VERSION_MAJOR     0
#define TUSB_VERSION_MINOR     9
#define TUSB_VERSION_REVISION  0
#define TUSB_VERSION_STRING    TU_STRING(TUSB_VERSION_MAJOR) "." TU_STRING(TUSB_VERSION_MINOR) "." TU_STRING(TUSB_VERSION_REVISION)

/** \defgroup group_mcu支持的mcu\ref CFG_TUSB_mcu必须定义为以下值之一
 *  @{ */

#define OPT_MCU_NONE                0

// LPC
#define OPT_MCU_LPC11UXX            1 ///<NXP LPC11Uxx
#define OPT_MCU_LPC13XX             2 ///<NXP LPC13xx
#define OPT_MCU_LPC15XX             3 ///<NXP LPC15xx
#define OPT_MCU_LPC175X_6X          4 ///<NXP LPC175x、LPC176x
#define OPT_MCU_LPC177X_8X          5 ///<NXP LPC177x、LPC178x
#define OPT_MCU_LPC18XX             6 ///<NXP LPC18xx
#define OPT_MCU_LPC40XX             7 ///<NXP LPC40xx
#define OPT_MCU_LPC43XX             8 ///<NXP LPC43xx
#define OPT_MCU_LPC51UXX            9 ///<NXP LPC51U6x
#define OPT_MCU_LPC54XXX           10 ///<NXP LPC54xxx
#define OPT_MCU_LPC55XX            11 ///<NXP LPC55xx

// NRF
#define OPT_MCU_NRF5X             100 ///<北欧nRF5x系列

// SAM
#define OPT_MCU_SAMD11            204 ///<MicroChip SAMD11
#define OPT_MCU_SAMD21            200 ///<MicroChip SAMD21
#define OPT_MCU_SAMD51            201 ///<MicroChip SAMD51
#define OPT_MCU_SAME5X            203 ///<MicroChip SAM E5x
#define OPT_MCU_SAMG              202 ///<MicroChip SAMDG系列
#define OPT_MCU_SAML22            205 ///<MicroChip SAML22

// STM32
#define OPT_MCU_STM32F0           300 ///< ST STM32F0
#define OPT_MCU_STM32F1           301 ///< ST STM32F1
#define OPT_MCU_STM32F2           302 ///< ST STM32F2
#define OPT_MCU_STM32F3           303 ///< ST STM32F3
#define OPT_MCU_STM32F4           304 ///< ST STM32F4
#define OPT_MCU_STM32F7           305 ///< ST STM32F7
#define OPT_MCU_STM32H7           306 ///< ST STM32H7
#define OPT_MCU_STM32L0           307 ///< ST STM32L0
#define OPT_MCU_STM32L1           308 ///< ST STM32L1
#define OPT_MCU_STM32L4           309 ///< ST STM32L4

// 索尼
#define OPT_MCU_CXD56             400 ///< SONY CXD56

// TI MSP430
#define OPT_MCU_MSP430x5xx        500 ///<TI MSP430x5xx

// ValentyUSB eptri公司
#define OPT_MCU_VALENTYUSB_EPTRI  600 ///<Fomu eptri配置

// 恩智浦iMX RT
#define OPT_MCU_MIMXRT10XX        700 ///<NXP iMX RT10xx

// 新唐科技
#define OPT_MCU_NUC121            800
#define OPT_MCU_NUC126            801
#define OPT_MCU_NUC120            802
#define OPT_MCU_NUC505            803

// Espressif公司
#define OPT_MCU_ESP32S2           900 ///<Espressif ESP32-S2
#define OPT_MCU_ESP32S3           901 ///<Espressif ESP32-S3

// 对话
#define OPT_MCU_DA1469X          1000 ///＜Dialog Semiconductor DA1469x＞

// 树莓皮
#define OPT_MCU_RP2040           1100 ///<树莓派RP2040

// 恩智浦Kinetis
#define OPT_MCU_MKL25ZXX         1200 ///<NXP MKL25Zxx

// 塞拉布
#define OPT_MCU_EFM32GG          1300 ///<Silabs EFM32GG
#define OPT_MCU_EFM32GG11        1301 ///<Silabs EFM32GG11
#define OPT_MCU_EFM32GG12        1302 ///<Silabs EFM32GG12

// 瑞萨RX
#define OPT_MCU_RX63X            1400 ///<瑞萨RX63N/631

/** @} */

/** \defgroup group_supported_os支持的RTOS\ref CFG_TUSB_os必须定义为以下值之一
 *  @{ */
#define OPT_OS_NONE       1  ///<无RTOS
#define OPT_OS_FREERTOS   2  ///<自由RTOS
#define OPT_OS_MYNEWT     3  ///<Mynewt操作系统
#define OPT_OS_CUSTOM     4  ///<自定义操作系统由应用程序实现
#define OPT_OS_PICO       5  ///<树莓皮Pico SDK
#define OPT_OS_RTTHREAD   6  ///<RT线程
/** @} */

// 允许使用命令行更改配置名称/位置
#ifdef CFG_TUSB_CONFIG_FILE
  #include CFG_TUSB_CONFIG_FILE
#else
  #include "tusb_config.h"
#endif

/** \添加组组配置
 *  @{ */


//--------------------------------------------------------------------
// RootHub模式配置
// CFG_TUSB_RHPORTx_MODE包含该端口的操作模式和速度
//--------------------------------------------------------------------

// 低4位为操作模式
#define OPT_MODE_NONE         0x00 ///<已禁用
#define OPT_MODE_DEVICE       0x01 ///<设备模式
#define OPT_MODE_HOST         0x02 ///<主机模式

// 较高的4位为最大运行速度（对应于tusb_speed_t）
#define OPT_MODE_FULL_SPEED   0x00 ///<最大全速
#define OPT_MODE_LOW_SPEED    0x10 ///<最大低速
#define OPT_MODE_HIGH_SPEED   0x20 ///<最大高速


#ifndef CFG_TUSB_RHPORT0_MODE
  #define CFG_TUSB_RHPORT0_MODE OPT_MODE_NONE
#endif


#ifndef CFG_TUSB_RHPORT1_MODE
  #define CFG_TUSB_RHPORT1_MODE OPT_MODE_NONE
#endif

#if (((CFG_TUSB_RHPORT0_MODE) & OPT_MODE_HOST  ) && ((CFG_TUSB_RHPORT1_MODE) & OPT_MODE_HOST  )) || \
    (((CFG_TUSB_RHPORT0_MODE) & OPT_MODE_DEVICE) && ((CFG_TUSB_RHPORT1_MODE) & OPT_MODE_DEVICE))
  #error "TinyUSB currently does not support same modes on more than 1 roothub port"
#endif

// 将哪个roothub端口配置为主机
#define TUH_OPT_RHPORT          ( ((CFG_TUSB_RHPORT0_MODE) & OPT_MODE_HOST) ? 0 : (((CFG_TUSB_RHPORT1_MODE) & OPT_MODE_HOST) ? 1 : -1) )
#define TUSB_OPT_HOST_ENABLED   ( TUH_OPT_RHPORT >= 0 )

// 哪个roothub端口配置为设备
#define TUD_OPT_RHPORT          ( ((CFG_TUSB_RHPORT0_MODE) & OPT_MODE_DEVICE) ? 0 : (((CFG_TUSB_RHPORT1_MODE) & OPT_MODE_DEVICE) ? 1 : -1) )

#if TUD_OPT_RHPORT == 0
#define TUD_OPT_HIGH_SPEED      ( (CFG_TUSB_RHPORT0_MODE) & OPT_MODE_HIGH_SPEED )
#else
#define TUD_OPT_HIGH_SPEED      ( (CFG_TUSB_RHPORT1_MODE) & OPT_MODE_HIGH_SPEED )
#endif

#define TUSB_OPT_DEVICE_ENABLED ( TUD_OPT_RHPORT >= 0 )

//--------------------------------------------------------------------+
// COMMON OPTIONS
//--------------------------------------------------------------------+

// 启用调试以打印错误消息
#ifndef CFG_TUSB_DEBUG
  #define CFG_TUSB_DEBUG 0
#endif

// 将数据放在usb控制器的可访问RAM中
#ifndef CFG_TUSB_MEM_SECTION
  #define CFG_TUSB_MEM_SECTION
#endif

#ifndef CFG_TUSB_MEM_ALIGN
  #define CFG_TUSB_MEM_ALIGN      TU_ATTR_ALIGNED(4)
#endif

#ifndef CFG_TUSB_OS
  #define CFG_TUSB_OS             OPT_OS_NONE
#endif

//--------------------------------------------------------------------
// DEVICE OPTIONS
//--------------------------------------------------------------------

#ifndef CFG_TUD_ENDPOINT0_SIZE
  #define CFG_TUD_ENDPOINT0_SIZE  64
#endif

#ifndef CFG_TUD_CDC
  #define CFG_TUD_CDC             0
#endif

#ifndef CFG_TUD_MSC
  #define CFG_TUD_MSC             0
#endif

#ifndef CFG_TUD_HID
  #define CFG_TUD_HID             0
#endif

#ifndef CFG_TUD_AUDIO
  #define CFG_TUD_AUDIO           0
#endif

#ifndef CFG_TUD_MIDI
  #define CFG_TUD_MIDI            0
#endif

#ifndef CFG_TUD_VENDOR
  #define CFG_TUD_VENDOR          0
#endif

#ifndef CFG_TUD_USBTMC
  #define CFG_TUD_USBTMC          0
#endif

#ifndef CFG_TUD_DFU_RUNTIME
  #define CFG_TUD_DFU_RUNTIME          0
#endif

#ifndef CFG_TUD_NET
  #define CFG_TUD_NET             0
#endif

#ifndef CFG_TUD_BTH
  #define CFG_TUD_BTH             0
#endif

//--------------------------------------------------------------------
// HOST OPTIONS
//--------------------------------------------------------------------
#if TUSB_OPT_HOST_ENABLED
  #ifndef CFG_TUSB_HOST_DEVICE_MAX
    #define CFG_TUSB_HOST_DEVICE_MAX 1
    #warning CFG_TUSB_HOST_DEVICE_MAX is not defined, default value is 1
  #endif

  //------------- HUB CLASS -------------//
  #if CFG_TUH_HUB && (CFG_TUSB_HOST_DEVICE_MAX == 1)
    #error there is no benefit enable hub with max device is 1. Please disable hub or increase CFG_TUSB_HOST_DEVICE_MAX
  #endif

  //------------- HID CLASS -------------//
  #define HOST_CLASS_HID   ( CFG_TUH_HID_KEYBOARD + CFG_TUH_HID_MOUSE + CFG_TUSB_HOST_HID_GENERIC )

  #ifndef CFG_TUSB_HOST_ENUM_BUFFER_SIZE
    #define CFG_TUSB_HOST_ENUM_BUFFER_SIZE 256
  #endif

  //------------- CLASS -------------//
#endif // TUSB_OPT_HOST_ENABLED

//--------------------------------------------------------------------+
// 端口选项
// TinyUSB端口的TUP（可重命名）
//--------------------------------------------------------------------+

// TUP_ARCH_STRICT_ALIGN（如果ARCH无法访问未对齐的内存）

// ARMv7+（M3-M7、M23-M33）可以访问未对齐的内存
#if (defined(__ARM_ARCH) && (__ARM_ARCH >= 7))
  #define TUP_ARCH_STRICT_ALIGN   0
#else
  #define TUP_ARCH_STRICT_ALIGN   1
#endif

//------------------------------------------------------------------
// 配置验证
//------------------------------------------------------------------
#if CFG_TUD_ENDPOINT0_SIZE > 64
  #error Control Endpoint Max Packet Size cannot be larger than 64
#endif

#endif /* _TUSB_OPTION_H_ */

/** @} */

