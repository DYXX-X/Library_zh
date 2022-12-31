/*
 * MIT许可证（MIT）
 *
 * 版权所有（c）2020，Ha Thach（tinyusb.org）
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * 此文件是TinyUSB堆栈的一部分。
 */


#ifndef BOARD_MCU_H_
#define BOARD_MCU_H_

#include "tusb_option.h"

//--------------------------------------------------------------------+
// 低级MCU标头包括。TinyUSB堆栈和示例应为
// 与平台无关，大多数情况下不需要包含此文件。
// 然而，仍有某些情况需要此文件：
// -FreeRTO配置。h为ARM Cortex设置正确的时钟和NVIC中断
// -使用ITM_SendChar（）/ITM_ReceptChar（）记录Cortex M的SWO日志
//--------------------------------------------------------------------+

// OPT_MCU_编号后包含顺序
#if   CFG_TUSB_MCU == OPT_MCU_LPC11UXX   || CFG_TUSB_MCU == OPT_MCU_LPC13XX    || \
      CFG_TUSB_MCU == OPT_MCU_LPC15XX    || CFG_TUSB_MCU == OPT_MCU_LPC175X_6X || \
      CFG_TUSB_MCU == OPT_MCU_LPC177X_8X || CFG_TUSB_MCU == OPT_MCU_LPC18XX    || \
      CFG_TUSB_MCU == OPT_MCU_LPC40XX    || CFG_TUSB_MCU == OPT_MCU_LPC43XX
  #include "chip.h"

#elif CFG_TUSB_MCU == OPT_MCU_LPC51UXX || CFG_TUSB_MCU == OPT_MCU_LPC54XXX || \
      CFG_TUSB_MCU == OPT_MCU_LPC55XX  || CFG_TUSB_MCU == OPT_MCU_MKL25ZXX
  #include "fsl_device_registers.h"

#elif CFG_TUSB_MCU == OPT_MCU_NRF5X
  #include "nrf.h"

#elif CFG_TUSB_MCU == OPT_MCU_SAMD11 || CFG_TUSB_MCU == OPT_MCU_SAMD21 || \
      CFG_TUSB_MCU == OPT_MCU_SAMD51 || CFG_TUSB_MCU == OPT_MCU_SAME5X || \
      CFG_TUSB_MCU == OPT_MCU_SAML22
  #include "sam.h"

#elif CFG_TUSB_MCU == OPT_MCU_SAMG
  #undef LITTLE_ENDIAN // 黑客压制“LITTLE_ENDIAN”重新定义
  #include "sam.h"

#elif CFG_TUSB_MCU == OPT_MCU_STM32F0
  #include "stm32f0xx.h"

#elif CFG_TUSB_MCU == OPT_MCU_STM32F1
  #include "stm32f1xx.h"

#elif CFG_TUSB_MCU == OPT_MCU_STM32F2
  #include "stm32f2xx.h"

#elif CFG_TUSB_MCU == OPT_MCU_STM32F3
  #include "stm32f3xx.h"

#elif CFG_TUSB_MCU == OPT_MCU_STM32F4
  #include "stm32f4xx.h"

#elif CFG_TUSB_MCU == OPT_MCU_STM32F7
  #include "stm32f7xx.h"

#elif CFG_TUSB_MCU == OPT_MCU_STM32H7
  #include "stm32h7xx.h"

#elif CFG_TUSB_MCU == OPT_MCU_STM32L0
  #include "stm32l0xx.h"

#elif CFG_TUSB_MCU == OPT_MCU_STM32L1
  #include "stm32l1xx.h"

#elif CFG_TUSB_MCU == OPT_MCU_STM32L4
  #include "stm32l4xx.h"

#elif CFG_TUSB_MCU == OPT_MCU_CXD56
  // 不需要页眉

#elif CFG_TUSB_MCU == OPT_MCU_MSP430x5xx
  #include "msp430.h"

#elif CFG_TUSB_MCU == OPT_MCU_VALENTYUSB_EPTRI
  // 不需要页眉

#elif CFG_TUSB_MCU == OPT_MCU_MIMXRT10XX
  #include "fsl_device_registers.h"

#elif CFG_TUSB_MCU == OPT_MCU_NUC120
  #include "NUC100Series.h"

#elif CFG_TUSB_MCU == OPT_MCU_NUC121 || CFG_TUSB_MCU == OPT_MCU_NUC126
  #include "NuMicro.h"

#elif CFG_TUSB_MCU == OPT_MCU_NUC505
  #include "NUC505Series.h"

#elif CFG_TUSB_MCU == OPT_MCU_ESP32S2
  // 不需要页眉

#elif CFG_TUSB_MCU == OPT_MCU_ESP32S3
  // 不需要页眉

#elif CFG_TUSB_MCU == OPT_MCU_DA1469X
  #include "DA1469xAB.h"

#elif CFG_TUSB_MCU == OPT_MCU_RP2040
  #include "pico.h"
  
#elif CFG_TUSB_MCU == OPT_MCU_EFM32GG || CFG_TUSB_MCU == OPT_MCU_EFM32GG11 || CFG_TUSB_MCU == OPT_MCU_EFM32GG12
  #include "em_device.h"

#elif CFG_TUSB_MCU == OPT_MCU_RX63X
  // 不需要页眉

#else
  #error "Missing MCU header"
#endif


#endif /* BOARD_MCU_H_ */

