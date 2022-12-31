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

/** \inggroup group_demo\defgroup group_Boards抽象层
 *  @{ */

#ifndef _BSP_BOARD_H_
#define _BSP_BOARD_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "ansi_escape.h"
#include "tusb.h"

#define CFG_BOARD_UART_BAUDRATE    115200

//--------------------------------------------------------------------+
// 板移植API
// 为简单起见，仅使用一个LED和一个按钮
//--------------------------------------------------------------------+

// 初始化车载外设：led、按钮、uart和USB
void board_init(void);

// 打开或关闭LED
void board_led_write(bool state);

// 获取按钮的当前状态
// “1”表示活动（按下），“0”表示不活动。
uint32_t board_button_read(void);

// 从UART获取字符
int board_uart_read(uint8_t* buf, int len);

// 向UART发送字符
int board_uart_write(void const * buf, int len);

#if CFG_TUSB_OS == OPT_OS_NONE
  // 获取当前毫秒数，必须在不使用RTOS时执行
  uint32_t board_millis(void);

#elif CFG_TUSB_OS == OPT_OS_FREERTOS
  static inline uint32_t board_millis(void)
  {
    return ( ( ((uint64_t) xTaskGetTickCount()) * 1000) / configTICK_RATE_HZ );
  }

#elif CFG_TUSB_OS == OPT_OS_MYNEWT
  static inline uint32_t board_millis(void)
  {
    return os_time_ticks_to_ms32( os_time_get() );
  }

#elif CFG_TUSB_OS == OPT_OS_PICO
#include "pico/time.h"
static inline uint32_t board_millis(void)
  {
    return to_ms_since_boot(get_absolute_time());
  }
#elif CFG_TUSB_OS == OPT_OS_RTTHREAD
  static inline uint32_t board_millis(void)
  {
    return (((uint64_t)rt_tick_get()) * 1000 / RT_TICK_PER_SECOND);
  }

#else
  #error "board_millis() is not implemented for this OS"
#endif

//--------------------------------------------------------------------+
// Helper函数
//--------------------------------------------------------------------+
static inline void board_led_on(void)
{
  board_led_write(true);
}

static inline void board_led_off(void)
{
  board_led_write(false);
}

// TODO删除
static inline void board_delay(uint32_t ms)
{
  uint32_t start_ms = board_millis();
  while (board_millis() - start_ms < ms)
  {
    #if TUSB_OPT_DEVICE_ENABLED
    // 抓住机会运行usb后台
    tud_task();
    #endif
  }
}

static inline int board_uart_getchar(void)
{
  uint8_t c;
  return board_uart_read(&c, 1) ? (int) c : (-1);
}

static inline int board_uart_putchar(uint8_t c)
{
  return board_uart_write(&c, 1);
}

#ifdef __cplusplus
 }
#endif

#endif /* _BSP_BOARD_H_ */

/** @} */

