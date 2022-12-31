/*********************************************************************
*                SEGGER微控制器GmbH&Co.KG*嵌入式专家
**********************************************************************
*                                                                    *（c）2015-2017 SEGGER微控制器股份有限公司
*                                                                    *
*       www.segger.com支持：support@segger.com               *
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
---------------------------END-OF-HEADER------------------------------文件：SEGGER_RTT.h目的：实现SEGGER实时传输，允许在CPU运行时在支持调试器内存访问的目标上进行实时通信。版本：$Rev:5626$
----------------------------------------------------------------------
*/

#ifndef SEGGER_RTT_H
#define SEGGER_RTT_H

#include "SEGGER_RTT_Conf.h"

/*********************************************************************
* 定义，固定
*
**********************************************************************
*/

/*********************************************************************
* 类型
*
**********************************************************************
*/

//
// 循环缓冲区（也称为“环形缓冲区”）的描述
// 用作上行缓冲区（T->H）
//
typedef struct {
  const     char*    sName;         // 可选名称。到目前为止，标准名称为：“终端”、“SysView”、“J-Scope_t4i4”
            char*    pBuffer;       // 指向缓冲区起点的指针
            unsigned SizeOfBuffer;  // 缓冲区大小（字节）。请注意，一个字节丢失了，因为此实现不会填满缓冲区，以避免无法区分满和空的问题。
            unsigned WrOff;         // 任一目标要写入的下一项的位置。
  volatile  unsigned RdOff;         // 主机要读取的下一项的位置。必须是易失性的，因为它可能被主机修改。
            unsigned Flags;         // 包含配置标志
} SEGGER_RTT_BUFFER_UP;

//
// 循环缓冲区（也称为“环形缓冲区”）的描述
// 用作下缓冲区（H->T）
//
typedef struct {
  const     char*    sName;         // 可选名称。到目前为止，标准名称为：“终端”、“SysView”、“J-Scope_t4i4”
            char*    pBuffer;       // 指向缓冲区起点的指针
            unsigned SizeOfBuffer;  // 缓冲区大小（字节）。请注意，一个字节丢失了，因为此实现不会填满缓冲区，以避免无法区分满和空的问题。
  volatile  unsigned WrOff;         // 主机要写入的下一项的位置。必须是易失性的，因为它可能被主机修改。
            unsigned RdOff;         // 目标要读取的下一个项目的位置（向下缓冲区）。
            unsigned Flags;         // 包含配置标志
} SEGGER_RTT_BUFFER_DOWN;

//
// 描述可用缓冲区数量的RTT控制块
// 以及每个缓冲区的配置
//
//
typedef struct {
  char                    acID[16];                                 // 已初始化为“SEGGER RTT”
  int                     MaxNumUpBuffers;                          // 已初始化为SEGGER_RTT_MAX_NUM_UP_BUFFERS（类型.2）
  int                     MaxNumDownBuffers;                        // 已初始化为SEGGER_RTT_MAX_NUM_DOWN_BUFFERS（类型.2）
  SEGGER_RTT_BUFFER_UP    aUp[SEGGER_RTT_MAX_NUM_UP_BUFFERS];       // 向上缓冲区，通过调试探针将信息从目标向上传输到主机
  SEGGER_RTT_BUFFER_DOWN  aDown[SEGGER_RTT_MAX_NUM_DOWN_BUFFERS];   // 向下缓冲区，通过调试探针将信息从主机向下传输到目标
} SEGGER_RTT_CB;

/*********************************************************************
* 全局数据
*
**********************************************************************
*/
extern SEGGER_RTT_CB _SEGGER_RTT;

/*********************************************************************
* RTT API函数
*
**********************************************************************
*/
#ifdef __cplusplus
  extern "C" {
#endif
int          SEGGER_RTT_AllocDownBuffer         (const char* sName, void* pBuffer, unsigned BufferSize, unsigned Flags);
int          SEGGER_RTT_AllocUpBuffer           (const char* sName, void* pBuffer, unsigned BufferSize, unsigned Flags);
int          SEGGER_RTT_ConfigUpBuffer          (unsigned BufferIndex, const char* sName, void* pBuffer, unsigned BufferSize, unsigned Flags);
int          SEGGER_RTT_ConfigDownBuffer        (unsigned BufferIndex, const char* sName, void* pBuffer, unsigned BufferSize, unsigned Flags);
int          SEGGER_RTT_GetKey                  (void);
unsigned     SEGGER_RTT_HasData                 (unsigned BufferIndex);
int          SEGGER_RTT_HasKey                  (void);
void         SEGGER_RTT_Init                    (void);
unsigned     SEGGER_RTT_Read                    (unsigned BufferIndex,       void* pBuffer, unsigned BufferSize);
unsigned     SEGGER_RTT_ReadNoLock              (unsigned BufferIndex,       void* pData,   unsigned BufferSize);
int          SEGGER_RTT_SetNameDownBuffer       (unsigned BufferIndex, const char* sName);
int          SEGGER_RTT_SetNameUpBuffer         (unsigned BufferIndex, const char* sName);
int          SEGGER_RTT_SetFlagsDownBuffer      (unsigned BufferIndex, unsigned Flags);
int          SEGGER_RTT_SetFlagsUpBuffer        (unsigned BufferIndex, unsigned Flags);
int          SEGGER_RTT_WaitKey                 (void);
unsigned     SEGGER_RTT_Write                   (unsigned BufferIndex, const void* pBuffer, unsigned NumBytes);
unsigned     SEGGER_RTT_WriteNoLock             (unsigned BufferIndex, const void* pBuffer, unsigned NumBytes);
unsigned     SEGGER_RTT_WriteSkipNoLock         (unsigned BufferIndex, const void* pBuffer, unsigned NumBytes);
unsigned     SEGGER_RTT_WriteString             (unsigned BufferIndex, const char* s);
void         SEGGER_RTT_WriteWithOverwriteNoLock(unsigned BufferIndex, const void* pBuffer, unsigned NumBytes);
void         SEGGER_RTT_ESP_FlushNoLock       (unsigned long min_sz, unsigned long tmo);
void         SEGGER_RTT_ESP_Flush             (unsigned long min_sz, unsigned long tmo);
//
// 用于性能优化的函数宏
//
// @AGv：此宏在SEGGER SystemView代码中使用。
// 对于ESP32，我们使用自己的RTT实现，因此该宏不应检查SEGGER的RTT缓冲区状态。
#define      SEGGER_RTT_HASDATA(n)       (1)

/*********************************************************************
* RTT“终端”API功能
*
**********************************************************************
*/
int     SEGGER_RTT_SetTerminal        (char TerminalId);
int     SEGGER_RTT_TerminalOut        (char TerminalId, const char* s);

/*********************************************************************
* RTT printf函数（需要SEGGER_RTT_printf.c）
*
**********************************************************************
*/
int SEGGER_RTT_printf(unsigned BufferIndex, const char * sFormat, ...);
#ifdef __cplusplus
  }
#endif

/*********************************************************************
* 定义
*
**********************************************************************
*/

//
// 操作模式。定义缓冲区已满时的行为（没有足够的空间容纳整个消息）
//
#define SEGGER_RTT_MODE_NO_BLOCK_SKIP         (0U)     // 跳过不阻塞，不输出任何内容。（默认）
#define SEGGER_RTT_MODE_NO_BLOCK_TRIM         (1U)     // 修剪：不要阻塞，尽可能多地输出。
#define SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL    (2U)     // 块：等待缓冲区中有空间。
#define SEGGER_RTT_MODE_MASK                  (3U)

//
// 控制序列，基于ANSI。
// 可用于控制颜色和清除屏幕
//
#define RTT_CTRL_RESET                "[0m"         // 重置为默认颜色
#define RTT_CTRL_CLEAR                "[2J"         // 清除屏幕，将光标重新定位到左上方

#define RTT_CTRL_TEXT_BLACK           "[2;30m"
#define RTT_CTRL_TEXT_RED             "[2;31m"
#define RTT_CTRL_TEXT_GREEN           "[2;32m"
#define RTT_CTRL_TEXT_YELLOW          "[2;33m"
#define RTT_CTRL_TEXT_BLUE            "[2;34m"
#define RTT_CTRL_TEXT_MAGENTA         "[2;35m"
#define RTT_CTRL_TEXT_CYAN            "[2;36m"
#define RTT_CTRL_TEXT_WHITE           "[2;37m"

#define RTT_CTRL_TEXT_BRIGHT_BLACK    "[1;30m"
#define RTT_CTRL_TEXT_BRIGHT_RED      "[1;31m"
#define RTT_CTRL_TEXT_BRIGHT_GREEN    "[1;32m"
#define RTT_CTRL_TEXT_BRIGHT_YELLOW   "[1;33m"
#define RTT_CTRL_TEXT_BRIGHT_BLUE     "[1;34m"
#define RTT_CTRL_TEXT_BRIGHT_MAGENTA  "[1;35m"
#define RTT_CTRL_TEXT_BRIGHT_CYAN     "[1;36m"
#define RTT_CTRL_TEXT_BRIGHT_WHITE    "[1;37m"

#define RTT_CTRL_BG_BLACK             "[24;40m"
#define RTT_CTRL_BG_RED               "[24;41m"
#define RTT_CTRL_BG_GREEN             "[24;42m"
#define RTT_CTRL_BG_YELLOW            "[24;43m"
#define RTT_CTRL_BG_BLUE              "[24;44m"
#define RTT_CTRL_BG_MAGENTA           "[24;45m"
#define RTT_CTRL_BG_CYAN              "[24;46m"
#define RTT_CTRL_BG_WHITE             "[24;47m"

#define RTT_CTRL_BG_BRIGHT_BLACK      "[4;40m"
#define RTT_CTRL_BG_BRIGHT_RED        "[4;41m"
#define RTT_CTRL_BG_BRIGHT_GREEN      "[4;42m"
#define RTT_CTRL_BG_BRIGHT_YELLOW     "[4;43m"
#define RTT_CTRL_BG_BRIGHT_BLUE       "[4;44m"
#define RTT_CTRL_BG_BRIGHT_MAGENTA    "[4;45m"
#define RTT_CTRL_BG_BRIGHT_CYAN       "[4;46m"
#define RTT_CTRL_BG_BRIGHT_WHITE      "[4;47m"


#endif

/***************************文件结尾****************************/

