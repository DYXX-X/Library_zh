/* 
 * MIT许可证（MIT）
 *
 * 版权所有（c）2019，Ha Thach（tinyusb.org）
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

#include "fsl_device_registers.h"

// 需要，因为iMX RT10xx SDK包含此文件用于板大小
#define BOARD_FLASH_SIZE (0x1000000U)

// LED
#define LED_PINMUX            IOMUXC_GPIO_11_GPIOMUX_IO11
#define LED_PORT              GPIO1
#define LED_PIN               11
#define LED_STATE_ON          0

// SW8按钮
#define BUTTON_PINMUX         IOMUXC_GPIO_SD_05_GPIO2_IO05
#define BUTTON_PORT           GPIO2
#define BUTTON_PIN            5
#define BUTTON_STATE_ACTIVE   0

// UART
#define UART_PORT             LPUART1
#define UART_RX_PINMUX        IOMUXC_GPIO_09_LPUART1_RXD
#define UART_TX_PINMUX        IOMUXC_GPIO_10_LPUART1_TXD

#endif /* BOARD_H_ */

