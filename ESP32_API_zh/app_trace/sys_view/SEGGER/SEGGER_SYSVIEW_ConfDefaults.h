/*********************************************************************
*                SEGGER微控制器GmbH&Co.KG*嵌入式专家
**********************************************************************
*                                                                    *（c）2015-2017 SEGGER微控制器股份有限公司
*                                                                    *
*       网址：www.segger。com支持：support@segger.com               *
*                                                                    *
**********************************************************************
*                                                                    *
*       SEGGER SystemView*实时应用程序分析*
*                                                                    *
**********************************************************************
*                                                                    *
* 保留所有权利*
*                                                                    *
* SEGGER强烈建议不要对本软件的源代码进行任何更改*或修改，以便与RTT协议和J-Link保持兼容。
*                                                                    *
* 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否经过修改：
*                                                                    *
* o源代码的重新分发必须保留上述版权*声明、本条件列表和以下免责声明。
*                                                                    *
* o二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述*版权声明、本条件列表和以下免责声明。
*                                                                    *
* o未经事先书面许可，不得使用SEGGER Microcontroller GmbH&Co.KG*的名称或其贡献者的名称来支持或推广源自本软件的产品。
*                                                                    *
* 本软件由版权持有人和贡献者“按原样”提供，不承担任何明示或暗示的保证，包括但不限于适销性和特定用途适用性的暗示保证。在任何情况下，SEGGER微控制器对任何直接、间接、附带、特殊、惩戒性或后果性损害（包括但不限于购买替代商品或服务；使用、数据或利润损失；或业务中断）均不承担责任，无论是由何原因引起的，也不以任何责任理论为依据，或因使用本软件而以任何方式产生的侵权行为（包括疏忽或其他），即使已告知此类损害的可能性。
*                                                                    *
**********************************************************************
*                                                                    *
*       SystemView版本：V2.42*
*                                                                    *
**********************************************************************
--------------------------结束标题--------------------------文件：SEGGER_SYSVIEW_ConfDefaults。hPurpose:定义SEGGER SystemView中使用的可配置定义的默认值。版本：$Rev:3734$
*/

#ifndef SEGGER_SYSVIEW_CONFDEFAULTS_H
#define SEGGER_SYSVIEW_CONFDEFAULTS_H

/*********************************************************************
* #包含部分
*
**********************************************************************
*/

#include "SEGGER_SYSVIEW_Conf.h"
#include "SEGGER_RTT_Conf.h"

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************
* 配置默认值
*
**********************************************************************
*/

// SystemView用于缓冲区的字节数。
#ifndef   SEGGER_SYSVIEW_RTT_BUFFER_SIZE
  #define SEGGER_SYSVIEW_RTT_BUFFER_SIZE    1024
#endif

// SystemView将使用的RTT频道。
#ifndef   SEGGER_SYSVIEW_RTT_CHANNEL
  #define SEGGER_SYSVIEW_RTT_CHANNEL        0
#endif
// RTT通道的卫生检查
#if (SEGGER_SYSVIEW_RTT_CHANNEL == 0) && (SEGGER_RTT_MAX_NUM_UP_BUFFERS < 2)
  #error "SEGGER_RTT_MAX_NUM_UP_BUFFERS in SEGGER_RTT_Conf.h has to be > 1!"
#elif (SEGGER_SYSVIEW_RTT_CHANNEL >= SEGGER_RTT_MAX_NUM_UP_BUFFERS)
  #error "SEGGER_RTT_MAX_NUM_UP_BUFFERS  in SEGGER_RTT_Conf.h has to be > SEGGER_SYSVIEW_RTT_CHANNEL!"
#endif

// 将SystemView缓冲区放入其自己的/RTT部分
#if !(defined SEGGER_SYSVIEW_BUFFER_SECTION) && (defined SEGGER_RTT_SECTION)
  #define SEGGER_SYSVIEW_BUFFER_SECTION            SEGGER_RTT_SECTION
#endif

// 检索系统时间戳。这将获得Cortex-M循环计数器。
#ifndef   SEGGER_SYSVIEW_GET_TIMESTAMP
  #error "SEGGER_SYSVIEW_GET_TIMESTAMP has to be defined in SEGGER_SYSVIEW_Conf.h!"
#endif

// 定义时钟源提供的低位有效位数。
#ifndef   SEGGER_SYSVIEW_TIMESTAMP_BITS
  #define SEGGER_SYSVIEW_TIMESTAMP_BITS     32
#endif

// 应用程序报告的最低Id。
#ifndef   SEGGER_SYSVIEW_ID_BASE
  #define SEGGER_SYSVIEW_ID_BASE            0
#endif

// 为节省带宽而移动ID的位数
#ifndef   SEGGER_SYSVIEW_ID_SHIFT
  #define SEGGER_SYSVIEW_ID_SHIFT           0
#endif

#ifndef   SEGGER_SYSVIEW_GET_INTERRUPT_ID
  #error "SEGGER_SYSVIEW_GET_INTERRUPT_ID has to be defined in SEGGER_SYSVIEW_Conf.h!"
#endif

#ifndef   SEGGER_SYSVIEW_MAX_ARGUMENTS
  #define SEGGER_SYSVIEW_MAX_ARGUMENTS      16
#endif

#ifndef   SEGGER_SYSVIEW_MAX_STRING_LEN
  #define SEGGER_SYSVIEW_MAX_STRING_LEN     128
#endif

// 对数据包使用静态缓冲区而不是堆栈上的缓冲区
#ifndef   SEGGER_SYSVIEW_USE_STATIC_BUFFER
  #define SEGGER_SYSVIEW_USE_STATIC_BUFFER  1
#endif

// SystemView用于静态缓冲区的最大数据包大小
#ifndef   SEGGER_SYSVIEW_MAX_PACKET_SIZE
  #define SEGGER_SYSVIEW_MAX_PACKET_SIZE   SEGGER_SYSVIEW_INFO_SIZE + SEGGER_SYSVIEW_MAX_STRING_LEN + 2 * SEGGER_SYSVIEW_QUANTA_U32 + SEGGER_SYSVIEW_MAX_ARGUMENTS * SEGGER_SYSVIEW_QUANTA_U32
#endif

// 使用事后分析而不是实时分析
#ifndef   SEGGER_SYSVIEW_POST_MORTEM_MODE
  #define SEGGER_SYSVIEW_POST_MORTEM_MODE   0
#endif

// 配置发送同步的频率
#ifndef   SEGGER_SYSVIEW_SYNC_PERIOD_SHIFT
  #define SEGGER_SYSVIEW_SYNC_PERIOD_SHIFT  8
#endif

// 锁定系统视图（嵌套）
#ifndef   SEGGER_SYSVIEW_LOCK
  #define SEGGER_SYSVIEW_LOCK()             SEGGER_RTT_LOCK()
#endif

// 解锁SystemView（可嵌套）
#ifndef   SEGGER_SYSVIEW_UNLOCK
  #define SEGGER_SYSVIEW_UNLOCK()           SEGGER_RTT_UNLOCK()
#endif

#ifdef __cplusplus
}
#endif

#endif

/***************************文件结尾****************************/

