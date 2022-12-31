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
#ifndef TUSB_VERIFY_H_
#define TUSB_VERIFY_H_

#include <stdbool.h>
#include <stdint.h>
#include "tusb_option.h"
#include "tusb_compiler.h"

/*------------------------------------------------------------------*/
/* 为了简化代码，该文件使用高级宏技术将默认参数模拟为C++。当心一个令人头疼的宏观操作，你被告知要远离它。
 *
 * 这包含VERIFY和ASSERT的宏：
 * 
 *   验证：当存在非MCU故障的错误情况时使用。例如，通过USB发送到micro的数据的边界检查应使用此功能。另一个例子是检查缓冲区溢出，从活动函数返回会导致NAK。
 * 
 *   评估：用于MCU固件错误导致的错误情况。这用于更快地发现代码中的错误。一个例子是在库函数调用中添加断言，以确认函数的（未标记的）参数是否有效。
 * 
 * 行为的不同之处在于ASSERT触发断点，而verify不触发断点。
 *
 *   #如果（cond）返回false，则定义TU_VERIFY（cond#如果（cond）返回ret，则定义TU_VERIFY（cond，ret）；
 *   
 *   #定义TU_VERIFY_HDLR（cond，handler）if（cond）｛handler；return false；｝#定义TU_VERIFY_HDLR（cond，ret，handler）if（cond）｛handler；return ret；｝
 *
 *   #如果（cond）｛_MESS_FAILED（）；TU_BREAKPOINT（），返回false；｝#定义TU_ASSERT（cond，ret）if（cond）｛_MESS_FAILED（）；TU_BREAKPOINT（），返回ret；｝
 *  
 *------------------------------------------------------------------*/

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------+
// TU_VERIFY帮助程序
//--------------------------------------------------------------------+

#if CFG_TUSB_DEBUG
  #include <stdio.h>
  #define _MESS_ERR(_err)   tu_printf("%s %d: failed, error = %s\r\n", __func__, __LINE__, tusb_strerr[_err])
  #define _MESS_FAILED()    tu_printf("%s %d: assert failed\r\n", __func__, __LINE__)
#else
  #define _MESS_ERR(_err) do {} while (0)
  #define _MESS_FAILED() do {} while (0)
#endif

// 命中错误时停止CPU（断点），仅适用于Cortex M3、M4、M7
#if defined(__ARM_ARCH_7M__) || defined (__ARM_ARCH_7EM__)
  #define TU_BREAKPOINT() do                                                                                \
  {                                                                                                         \
    volatile uint32_t* ARM_CM_DHCSR =  ((volatile uint32_t*) 0xE000EDF0UL); /* Cortex M核心调试->DHCSR*/ \
    if ( (*ARM_CM_DHCSR) & 1UL ) __asm("BKPT #0\n"); /* 仅在连接调试器时停止mcu*/            \
  } while(0)

#elif defined(__riscv)
  #define TU_BREAKPOINT() do { __asm("ebreak\n"); } while(0)

#else
  #define TU_BREAKPOINT() do {} while (0)
#endif

/*------------------------------------------------------------------*/
/* 宏生成器
 *------------------------------------------------------------------*/

// 帮助程序实现TU_VERIFY宏族的可选参数
#define GET_3RD_ARG(arg1, arg2, arg3, ...)        arg3
#define GET_4TH_ARG(arg1, arg2, arg3, arg4, ...)  arg4

/*-------------TU_VERIFY和TU_VERIFY_HDLR的发电机-------------*/
#define TU_VERIFY_DEFINE(_cond, _handler, _ret)  do            \
{                                                              \
  if ( !(_cond) ) { _handler; return _ret;  }                  \
} while(0)

/*------------------------------------------------------------------*/
/* TU_VERIFY
 * -TU_VERIFY_1ARGS：如果失败，则返回false
 * -TU_VERIFY_2ARGS：如果失败，则返回提供的值
 *------------------------------------------------------------------*/
#define TU_VERIFY_1ARGS(_cond)                         TU_VERIFY_DEFINE(_cond, , false)
#define TU_VERIFY_2ARGS(_cond, _ret)                   TU_VERIFY_DEFINE(_cond, , _ret)

#define TU_VERIFY(...)                   GET_3RD_ARG(__VA_ARGS__, TU_VERIFY_2ARGS, TU_VERIFY_1ARGS, UNUSED)(__VA_ARGS__)


/*------------------------------------------------------------------*/
/* TU_VERIFY WITH HANDLER
 * -TU_VERIFY_HDLR_2ARGS：执行处理程序，失败时返回false
 * -TU_VERIFY_HDLR_3ARGS：执行处理程序，失败时返回提供的错误
 *------------------------------------------------------------------*/
#define TU_VERIFY_HDLR_2ARGS(_cond, _handler)           TU_VERIFY_DEFINE(_cond, _handler, false)
#define TU_VERIFY_HDLR_3ARGS(_cond, _handler, _ret)     TU_VERIFY_DEFINE(_cond, _handler, _ret)

#define TU_VERIFY_HDLR(...)              GET_4TH_ARG(__VA_ARGS__, TU_VERIFY_HDLR_3ARGS, TU_VERIFY_HDLR_2ARGS,UNUSED)(__VA_ARGS__)

/*------------------------------------------------------------------*/
/* ASSERT基本上是TU_VERIFY，TU_BREAKPOINT（）作为处理程序
 * -1参数：失败时返回false
 * -2参数：失败时返回错误
 *------------------------------------------------------------------*/
#define ASSERT_1ARGS(_cond)            TU_VERIFY_DEFINE(_cond, _MESS_FAILED(); TU_BREAKPOINT(), false)
#define ASSERT_2ARGS(_cond, _ret)      TU_VERIFY_DEFINE(_cond, _MESS_FAILED(); TU_BREAKPOINT(), _ret)

#ifndef TU_ASSERT
#define TU_ASSERT(...)             GET_3RD_ARG(__VA_ARGS__, ASSERT_2ARGS, ASSERT_1ARGS,UNUSED)(__VA_ARGS__)
#endif

// TODO稍后删除TU_ASSERT_ERR（）

/*-------------TU_VERIFY_ERR和TU_VERIFY_ERR_HDLR的发电机-------------*/
#define TU_VERIFY_ERR_DEF2(_error, _handler)  do               \
{                                                              \
  uint32_t _err = (uint32_t)(_error);                          \
  if ( 0 != _err ) { _MESS_ERR(_err); _handler; return _err; } \
} while(0)

#define TU_VERIFY_ERR_DEF3(_error, _handler, _ret) do          \
{                                                              \
  uint32_t _err = (uint32_t)(_error);                          \
  if ( 0 != _err ) { _MESS_ERR(_err); _handler; return _ret; } \
} while(0)

/*------------------------------------------------------------------*/
/* ASSERT错误基本上是TU_VERIFY错误，TU_BREAKPOINT（）作为处理程序
 *------------------------------------------------------------------*/
#define ASSERT_ERR_1ARGS(_error)         TU_VERIFY_ERR_DEF2(_error, TU_BREAKPOINT())
#define ASSERT_ERR_2ARGS(_error, _ret)   TU_VERIFY_ERR_DEF3(_error, TU_BREAKPOINT(), _ret)

#ifndef TU_ASSERT_ERR
#define TU_ASSERT_ERR(...)         GET_3RD_ARG(__VA_ARGS__, ASSERT_ERR_2ARGS, ASSERT_ERR_1ARGS,UNUSED)(__VA_ARGS__)
#endif

/*------------------------------------------------------------------*/
/* ASSERT HDLR
 *------------------------------------------------------------------*/

#ifdef __cplusplus
 }
#endif

#endif /* TUSB_VERIFY_H_ */

