/******************************************************************************
 * 版权所有（C）2014 Android开源项目版权所有2002-2004 Open Interface North America，Inc.保留所有权利。
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/
#ifndef _OI_OSINTERFACE_H
#define _OI_OSINTERFACE_H
/**
 @file该文件为实现特定于平台的功能提供了独立于平台的接口。
 *
 * 此头文件中的函数定义了BLUEmagic 3.0协议栈所需的操作系统或硬件服务。这些服务的实际实现依赖于平台。
 *
 */

/**********************************************************************************
  $版本：#1$
***********************************************************************************/

#include "oi_stddefs.h"
#include "oi_time.h"
#include "oi_status.h"
#include "oi_modules.h"

/**\addtogroup其他杂项API*/
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif


/**
 * 终止执行。
 *
 * @param reason  终止原因
 */
void OI_FatalError(OI_STATUS reason);

/**
 * 此函数记录错误。
 *
 * 当为发布模式构建时，BLUEmagic 3错误将记录到此函数中。（在调试模式下，通过OI_Print（）记录错误）。
 *
 * @param module 检测到错误的模块（请参阅oi_modules.h）
 * @param lineno 调用的C文件OI_SLOG_ERROR的行号
 * @param status 与错误事件关联的状态代码
 */
void OI_LogError(OI_MODULE module, OI_INT lineno, OI_STATUS status);

/**
 * 此函数初始化调试代码处理。
 *
 * 当为调试模式构建时，此函数执行依赖于平台的初始化，以处理通过OI_SetMsgCode（）传入的消息代码。
 */
void OI_InitDebugCodeHandler(void);


/**
 * 此函数从实时时钟读取时间。
 *
 * BM3中的所有定时都是相对的，通常5或10毫秒的粒度就足够了。
 *
 * @param[out] now  指向将返回当前时间的缓冲区的指针
 */
void OI_Time_Now(OI_TIME *now);

/**
 * 此函数使当前线程休眠指定的时间。必须在没有堆栈访问令牌的情况下调用此函数。
 *
 * @note BM3核心堆栈和配置文件从不挂起，也从不调用OI_Sleep。OI_Sleep的使用仅限于应用程序和特定于平台的代码。
 *
 * 如果您的端口和应用程序从未使用OI_Sleep，则可以不实现此函数。
 *
 * @param milliseconds  休眠毫秒数
 */
void OI_Sleep(OI_UINT32 milliseconds);


/**
 * 定义消息类型代码。
 */
#define OI_MSG_CODE_APPLICATION               0   /**<应用程序输出*/
#define OI_MSG_CODE_ERROR                     1   /**<错误消息输出*/
#define OI_MSG_CODE_WARNING                   2   /**<警告消息输出*/
#define OI_MSG_CODE_TRACE                     3   /**<用户API函数跟踪输出*/
#define OI_MSG_CODE_PRINT1                    4   /**<类别1调试打印输出*/
#define OI_MSG_CODE_PRINT2                    5   /**<类别2调试打印输出*/
#define OI_MSG_CODE_HEADER                    6   /**<错误/调试输出标头*/

/**
 * 此函数用于指示OI_Print（）输出的文本类型。对于Linux和Win32平台，它将设置文本的颜色。其他可能的用途可能是插入HTML样式的标记，添加一些其他消息类型指示，或者完全忽略。
 *
 * @param code  OI_MSG_CODE_*表示设置消息类型。
 */
void OI_SetMsgCode(OI_UINT8 code);

/**
 * OI_Printf（）的所有输出和所有调试输出都发送到OI_Print。通常，如果平台有控制台，则OI_Print（）被发送到stdout。嵌入式平台通常将OI_Print（）输出发送到串行端口。
 *
 * @param str  要打印的字符串
 */
void OI_Print(OI_CHAR const *str);

/**
 *  在OI_Print（）将输出发送到除控制台之外的日志文件的情况下，还需要将控制台输入输入到日志文件中。此函数可由控制台输入过程调用。
 *
 *  @note 这是一个可选的API，它严格位于特定于平台的stack_coconsole和osinterface模块之间。此API只需要在具有有用用途的平台上实现，例如win32。
 *
 * @param str  控制台输入字符串
 */

void OI_Print_ConsoleInput(OI_CHAR const *str);

/**
 *  此函数计算程序图像的CRC16。
 */
OI_UINT16  OI_ProgramImageCRC16(void);

/**
 * 以十六进制将整数写入标准输出。此宏用于在小内存配置中调试或其他无法使用OI_DBGPRINT的情况下选择性使用。
 *
 * @param n  要打印的整数
 */

#define OI_Print_Int(n) \
{ \
    static const OI_CHAR _digits[] = "0123456789ABCDEF"; \
    OI_CHAR _buf[9]; \
    OI_CHAR *_str = &_buf[8]; \
    OI_UINT32 _i = n; \
    *_str = 0; \
    do { *(--_str) = _digits[(_i & 0xF)]; _i >>= 4; } while (_i); \
    OI_Print(_str); \
}

/**
 *  应用程序动态内存分配。
 *
 *  这些API是为那些没有动态内存支持的平台上的应用程序提供的。内存从堆栈的内部内存管理器管理的基于池的堆中分配。
 */
void *OI_APP_Malloc(OI_INT32 size);
void OI_APP_Free(void *ptr);

/*****************************************************************************/
#ifdef __cplusplus
}
#endif

/**@}*/

#endif /* _OI_OSINTERFACE_H */

