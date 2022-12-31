/*
 * MIT许可证（MIT）
 *
 * 版权所有（c）2021，Ha Thach（tinyusb.org）
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * 此文件是TinyUSB堆栈的一部分。
 */

#ifndef BOARD_H_
#define BOARD_H_

// 注意：对于USB主机演示，请安装JP4
// 警告：作为设备运行时不要安装JP4

#ifdef __cplusplus
 extern "C" {
#endif

// LED红色
#define LED_PORT      3
#define LED_PIN       7

// ISP按钮
#define BUTTON_PORT   0
#define BUTTON_PIN    7

#define UART_DEV      LPC_USART0

static inline void board_lpc18_pinmux(void)
{
  const PINMUX_GRP_T pinmuxing[] =
  {
    // LED指示灯
    { 0x6, 9 , SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | SCU_MODE_FUNC0 },
    { 0x6, 11, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | SCU_MODE_FUNC0 },

    // 按钮
    { 0x2, 7, SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC0 },

    // UART
    { 0x06, 4, SCU_MODE_PULLDOWN | SCU_MODE_FUNC2 },
    { 0x02, 1, SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC1 },

    // USB0
    //｛0x6，3，SCU_MODE_PULLUP | SCU_MODE_BUFF_EN | SCU_MODE _FUNC1｝，//P6_3 USB0_PWR_EN，USB0 VBus函数

    //｛0x9，5，SCU_MODE_PULLUP | SCU_MODE_BUFF_EN | SCU_MODE _FUNC2｝，//P9_5 USB1_VBUS_EN，USB1 VBUS函数
    //｛0x2，5，SCU_MODE_INACT|SCU_MODE_INBUFF_EN|SCU_MODE_ZIF_DIS|SCU_MODE _FUNC2}，//P2_5 USB1_VBUS，必须为USB1正常操作配置此信号
    {0x2, 5, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | SCU_MODE_FUNC4 },
  };

  Chip_SCU_SetPinMuxing(pinmuxing, sizeof(pinmuxing) / sizeof(PINMUX_GRP_T));
}

#ifdef __cplusplus
 }
#endif

#endif

