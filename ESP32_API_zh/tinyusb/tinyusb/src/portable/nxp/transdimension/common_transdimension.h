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

#ifndef COMMON_TRANSDIMENSION_H_
#define COMMON_TRANSDIMENSION_H_

#ifdef __cplusplus
 extern "C" {
#endif

// USBCMD
enum {
  USBCMD_RUN_STOP         = TU_BIT(0),
  USBCMD_RESET            = TU_BIT(1),
  USBCMD_SETUP_TRIPWIRE   = TU_BIT(13),
  USBCMD_ADD_QTD_TRIPWIRE = TU_BIT(14)  ///<此位用作信号量，以确保将新的dTD正确添加到活动（已启动）端点的链接列表中。在添加新的dTD的过程中，该位由软件设置和清除
// 中断阈值位23:16
};

// PORTSC1
#define PORTSC1_PORT_SPEED_POS    26

enum {
  PORTSC1_CURRENT_CONNECT_STATUS = TU_BIT(0),
  PORTSC1_FORCE_PORT_RESUME      = TU_BIT(6),
  PORTSC1_SUSPEND                = TU_BIT(7),
  PORTSC1_FORCE_FULL_SPEED       = TU_BIT(24),
  PORTSC1_PORT_SPEED             = TU_BIT(26) | TU_BIT(27)
};

// OTGSC
enum {
  OTGSC_VBUS_DISCHARGE          = TU_BIT(0),
  OTGSC_VBUS_CHARGE             = TU_BIT(1),
//  OTGSC_HWASSIST_AUTORESET    = TU_BIT(2),
  OTGSC_OTG_TERMINATION         = TU_BIT(3), ///<OTG进入设备模式时必须设置为1
  OTGSC_DATA_PULSING            = TU_BIT(4),
  OTGSC_ID_PULLUP               = TU_BIT(5),
//  OTGSC_HWASSIT_DATA_PULSE    = TU_BIT(6),
//  OTGSC_HWASSIT_BDIS_ACONN    = TU_BIT(7),
  OTGSC_ID                      = TU_BIT(8), ///<0=A设备，1=B设备
  OTGSC_A_VBUS_VALID            = TU_BIT(9),
  OTGSC_A_SESSION_VALID         = TU_BIT(10),
  OTGSC_B_SESSION_VALID         = TU_BIT(11),
  OTGSC_B_SESSION_END           = TU_BIT(12),
  OTGSC_1MS_TOGGLE              = TU_BIT(13),
  OTGSC_DATA_BUS_PULSING_STATUS = TU_BIT(14),
};

// USB模式
enum {
  USBMODE_CM_DEVICE = 2,
  USBMODE_CM_HOST   = 3,

  USBMODE_SLOM = TU_BIT(3),
  USBMODE_SDIS = TU_BIT(4),

  USBMODE_VBUS_POWER_SELECT = TU_BIT(5), // 需要在主机模式下为LPC18XX/43XX启用
};

// 设备寄存器
typedef struct
{
  //-------------ID+HW参数寄存器-------------//
  __I  uint32_t TU_RESERVED[64]; ///<对于iMX RT10xx，但LPC18XX/LCP43XX未使用

  //-------------能力寄存器-------------//
  __I  uint8_t  CAPLENGTH;       ///<能力寄存器长度
  __I  uint8_t  TU_RESERVED[1];
  __I  uint16_t HCIVERSION;      ///<主机控制器接口版本

  __I  uint32_t HCSPARAMS;       ///<主机控制器结构参数
  __I  uint32_t HCCPARAMS;       ///<主机控制器功能参数
  __I  uint32_t TU_RESERVED[5];

  __I  uint16_t DCIVERSION;      ///<设备控制器接口版本
  __I  uint8_t  TU_RESERVED[2];

  __I  uint32_t DCCPARAMS;       ///<设备控制器功能参数
  __I  uint32_t TU_RESERVED[6];

  //-------------操作寄存器-------------//
  __IO uint32_t USBCMD;          ///<USB命令寄存器
  __IO uint32_t USBSTS;          ///<USB状态寄存器
  __IO uint32_t USBINTR;         ///<中断启用寄存器
  __IO uint32_t FRINDEX;         ///<USB帧索引
  __I  uint32_t TU_RESERVED;
  __IO uint32_t DEVICEADDR;      ///<设备地址
  __IO uint32_t ENDPTLISTADDR;   ///<端点列表地址
  __I  uint32_t TU_RESERVED;
  __IO uint32_t BURSTSIZE;       ///<可编程突发大小
  __IO uint32_t TXFILLTUNING;    ///<TX FIFO填充调整
       uint32_t TU_RESERVED[4];
  __IO uint32_t ENDPTNAK;        ///<端点NAK
  __IO uint32_t ENDPTNAKEN;      ///<端点NAK启用
  __I  uint32_t TU_RESERVED;
  __IO uint32_t PORTSC1;         ///<端口状态和控制
  __I  uint32_t TU_RESERVED[7];
  __IO uint32_t OTGSC;           ///<On-The-Go状态和控制
  __IO uint32_t USBMODE;         ///<USB设备模式
  __IO uint32_t ENDPTSETUPSTAT;  ///<端点设置状态
  __IO uint32_t ENDPTPRIME;      ///<Endpoint Prime
  __IO uint32_t ENDPTFLUSH;      ///<端点刷新
  __I  uint32_t ENDPTSTAT;       ///<端点状态
  __IO uint32_t ENDPTCOMPLETE;   ///<端点完成
  __IO uint32_t ENDPTCTRL[8];    ///<端点控制0-7
} dcd_registers_t;

#ifdef __cplusplus
 }
#endif

#endif /* COMMON_TRANSDIMENSION_H_ */

