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
#ifndef _OI_UTILS_H
#define _OI_UTILS_H
/**
 * @file
 *
 * 此文件提供实用程序功能的接口。这些实用程序包括strlen（字符串长度）、strcmp（字符串比较）和其他字符串操作函数。这些是为stdlib中没有此功能的平台提供的。
 */

/**********************************************************************************
  $版本：#1$
***********************************************************************************/

#include <stdarg.h>
#include "oi_common.h"
#include "oi_string.h"
#include "oi_bt_spec.h"

/**\addtogroup其他杂项API*/
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 回调函数句柄的不透明类型。请参见OI_ScheduleCallbackFunction（）
 */
typedef OI_UINT32 OI_CALLBACK_HANDLE;


/**
 * 定时过程回调的函数原型。
 *
 * @param arg                 传递给OI_ScheduleCallback（）函数的值
 *
 */
typedef void (*OI_SCHEDULED_CALLBACK)(void *arg);


/**
 * 注册超时过期时要调用的函数。此API使用BLUEmagic的内部函数调度机制，因此广泛使用此功能的应用程序可能需要增加调度器配置块中DispatchTableSize的值（请参见oi_bt_stack_config.h）。
 *
 * @param callbackFunction    超时过期时将调用的函数
 *
 * @param arg                 将作为回调函数的参数返回的值。
 *
 * @param timeout             以OI_INTERVAL（十分之一秒）表示的超时。在这种情况下，将尽快调用回调函数。
 *
 * @param handle              NULL或指针接收回调句柄。
 *
 * @return                    OI_OK（如果函数已注册）或错误状态。
 */
OI_STATUS OI_ScheduleCallbackFunction(OI_SCHEDULED_CALLBACK callbackFunction,
                                      void                 *arg,
                                      OI_INTERVAL           timeout,
                                      OI_CALLBACK_HANDLE   *handle);


/**
 * 在计时器到期之前取消在OI_ScheduleCallbackFunction（）中注册的函数。
 *
 * @param handle              OI_ScheduleCallbackFunction（）返回的句柄。
 *
 * @return                    OI_OK（如果功能已取消）或错误状态。
 */
OI_STATUS OI_CancelCallbackFunction(OI_CALLBACK_HANDLE handle);


/**
 * 注册超时过期时要调用的函数。此版本不返回句柄，因此只能通过调用OI_CancelCallback（）来取消。
 *
 * @param callbackFunction    超时过期时将调用的函数
 *
 * @param arg                 将作为回调函数的参数返回的值。
 *
 * @param timeout             以OI_INTERVAL（十分之一秒）表示的超时。在这种情况下，将尽快调用回调函数。
 *
 * @return                    OI_OK（如果函数已注册）或错误状态。
 */
#define OI_ScheduleCallback(f, a, t)  OI_ScheduleCallbackFunction(f, a, t, NULL);


/**
 * 在计时器到期之前取消使用OI_ScheduleCallback（）注册的函数。此函数将取消与指定的回调函数指针匹配的第一个条目。
 *
 * @param callbackFunction    最初注册的函数
 *
 * @return                    OI_OK（如果功能已取消）或错误状态。
 */
OI_STATUS OI_CancelCallback(OI_SCHEDULED_CALLBACK callbackFunction);


/**
 * 从指定的字符串中分析蓝牙设备地址。
 *
 * @param str   要分析的字符串
 * @param addr  解析的地址（如果成功）
 *
 * @return 如果地址解析成功，则为TRUE，否则为FALSE
 */

OI_BOOL OI_ParseBdAddr(const OI_CHAR *str,
                       OI_BD_ADDR    *addr) ;

/**
 * 用于没有stdio或Printf可用的平台的Printf函数。OI_Printf支持基本格式类型，浮点类型除外。此外，OI_Printf支持BLUEmagic 3.0软件特有的几种格式：
 *
 * \%!   打印#OI_STATUS值的字符串。
 *       @code OI_Printf（“出现错误%！”，状态）@结束代码
 *
 * \%@   打印缓冲区的十六进制转储。需要指向缓冲区的指针和带符号整数长度（默认长度为0）。如果缓冲区很大，则只打印摘录。
 *       @code OI_Printf（“缓冲区%@的内容”，缓冲区，sizeof（缓冲区））@结束代码
 *
 * \%：以“HH:HH:HH:HH:HH:HH:HH”格式打印蓝牙地址。
 *       需要指向#OI_BD_ADDR的指针。
 *       @code OI_Printf（“蓝牙地址%：”，&baddr）@结束代码
 *
 * \%^将数据元素解码并打印为格式化的XML。
 *       需要指向#OI_DATAELEM的指针。
 *       @code OI_Printf（“服务属性列表为：\n%^”，&attributes）@结束代码
 *
 * \%/打印路径的基本文件名，即最后的子字符串
 *       后跟“/”或“\\”字符。需要指向null的指针
 *       终止字符串。
 *       @code OI_Printf（“文件%/”，“c:\\dir1\\dir2\\File.txt”）@结束代码
 *
 * \%~打印字符串，根据需要转义字符以显示
 *       ASCII。需要指向#OI_PSTR和#OI_UNICODE_ENCODING的指针
 *       参数
 *       @code OI_Printf（“标识符%~”，&id，OI_UNICODE_UTF16_BE）@结束代码
 *
 * \%[插入ANSI颜色转义序列。需要单个字符
 *       识别要选择的颜色。颜色为红色（r/r）、绿色（g/g）、绿色，
 *       蓝色（b/b）、黄色（y/y）、青色（c/c）、品红色（m/m）、白色（W）、，
 *       浅灰色（l/l）、深灰色（d/d）和黑色（0）。小写字母为
 *       暗，大写字母亮（浅灰色和
 *       其中亮和暗是相同的）。任何其他值将
 *       选择默认颜色。
 *       @code OI_Printf（“%[红色文本%[黑色%[正常\n”，'r'，'0'，0）；@endcode
 *
 * \%与\%s相同，但'\\r'和'\\n'输出为“<cr>”和“<lf>”。
 *       \%?a有效，但\%la无效。
 *
 * \%b打印基数为2的整数。
 *       @code OI_Printf（“位是%b”，I）@结束代码
 *
 * \%lb以2为基数打印一个长整数。
 *
 * \%?b打印整数（或长整数）的最低有效N位
 *       需要整数和长度N。
 *       @code OI_Printf（“底部4位为：%？b”，I，4）@结束代码
 *
 * \%B将整数打印为布尔文本，“TRUE”或“FALSE”。
 *       @code OI_Printf（“值0为%B，值1为%B”，0，1）@结束代码
 *
 * \%?s打印指定最大长度的子字符串。
 *       需要指向字符串的指针和长度参数。
 *       @code OI_Printf（“字符串前缀为%s”，str，3）@结束代码
 *
 * \%ls与\%S相同。
 *
 * \%S将UTF16字符串打印为UTF8（纯ASCII，加上8位字符序列
 *       如果需要）。需要指向#OI_CHAR16的指针。\%？S有效。这个
 *       长度参数为OI_CHAR16个字符。
 *
 * \%T打印时间，格式为“secs.msec”。
 *       需要指向#OI_TIME结构的指针，NULL指针打印当前时间。
 *       @code OI_Printf（“现在的时间是%T”，NULL）@结束代码
 *
 *  @param format   格式字符串
 *
 */
void OI_Printf(const OI_CHAR *format, ...);


/**
 * 变量参数版本OI_Printf
 *
 * @param format   与OI_Printf相同。
 *
 * @param argp     变量参数列表。
 */
void OI_VPrintf(const OI_CHAR *format, va_list argp);


/**
 * 将格式化字符串写入缓冲区。此函数支持与OI_Printf（）相同的格式说明符。
 *
 * @param buffer   格式化字符串的目标缓冲区。
 *
 * @param bufLen   目标缓冲区的长度。
 *
 * @param format   格式字符串
 *
 * @return   写入的字符数，如果出现错误，则为-1。
 */
OI_INT32 OI_SNPrintf(OI_CHAR *buffer,
                     OI_UINT16 bufLen,
                     const OI_CHAR *format, ...);


/**
 * 变量参数版本OI_SNPrintf
 *
 * @param buffer   格式化字符串的目标缓冲区。
 *
 * @param bufLen   目标缓冲区的长度。
 *
 * @param format   格式字符串
 *
 * @param argp     变量参数列表。
 *
 * @return   写入的字符数，如果出现错误，则为-1。
 */
OI_INT32 OI_VSNPrintf(OI_CHAR *buffer,
                      OI_UINT16 bufLen,
                      const OI_CHAR *format, va_list argp);


/**
 * 将字符串转换为整数。
 *
 * @param str  要分析的字符串
 *
 * @return 字符串的整数值，如果无法解析字符串，则为0
 */
OI_INT OI_atoi(const OI_CHAR *str);


/**
 * 分析字符串中的有符号整数。
 *
 * 跳过前导空格（仅空格和制表符）并解析十进制或十六进制字符串。十六进制字符串必须以“0x”为前缀。返回指向整数后第一个字符的指针。如果字符串不描述整数，则返回传入的指针。
 *
 * @param str    要分析的字符串。
 *
 * @param val    用于接收解析的整数值的指针。
 *
 * @return       指向整数后第一个字符的指针或传入的指针。
 */
const OI_CHAR *OI_ScanInt(const OI_CHAR *str,
                          OI_INT32 *val);


/**
 * 分析字符串中的无符号整数。
 *
 * 跳过前导空格（仅空格和制表符）并解析十进制或十六进制字符串。十六进制字符串必须以“0x”为前缀。返回指向整数后第一个字符的指针。如果字符串不描述整数，则返回传入的指针。
 *
 * @param str    要分析的字符串。
 *
 * @param val    用于接收已解析的无符号整数值的指针。
 *
 * @return       指向无符号整数后第一个字符的指针或传入的指针。
 */
const OI_CHAR *OI_ScanUInt(const OI_CHAR *str,
                           OI_UINT32 *val);

/**
 * 分析字符串中以空格分隔的子字符串。
 *
 * @param str     要分析的输入字符串。
 * @param outStr  返回子字符串的缓冲区
 * @param len     outStr的长度
 *
 *
 * @return       指向子字符串后面的第一个字符的指针或传入的指针。
 */
const OI_CHAR *OI_ScanStr(const OI_CHAR *str,
                          OI_CHAR *outStr,
                          OI_UINT16 len);


/**
 * 分析一组备选值之一的字符串。跳过前导空格（仅空格和制表符），并解析与其中一个可选字符串匹配的文本。返回指向匹配文本后面第一个字符的指针。
 *
 * @param str    要分析的字符串。
 *
 * @param alts   由“|”分隔的可选匹配字符串
 *
 * @param index  用于接收匹配替代项的索引的指针，如果不匹配，则返回值为-1。
 *
 * @return       指向匹配值后面的第一个字符的指针，如果没有匹配的文本，则返回传入的指针。
 */
const OI_CHAR *OI_ScanAlt(const OI_CHAR *str,
                          const OI_CHAR *alts,
                          OI_INT *index);

/**
 * 分析BD Addr的字符串。跳过前导空格（仅空格和制表符），并使用可选的冒号分隔的半字节来解析蓝牙设备地址。将指针返回到BD Addr后面的第一个字符。
 *
 * @param str    要分析的字符串。
 *
 * @param addr   用于接收蓝牙设备地址的指针
 *
 * @return       指向BD Addr后面的第一个字符的指针或传入的指针。
 */
const OI_CHAR *OI_ScanBdAddr(const OI_CHAR *str,
                             OI_BD_ADDR *addr);


/**从数字整数值（0-9）中获取字符。*/
#define OI_DigitToChar(d) ((d) + '0')

/**
 * 确定两个参数之间的最大值和最小值。
 *
 * @param a  第一个值
 * @param b  第二个值
 *
 * @return a和b之间的最大值或最小值
 */
#define OI_MAX(a, b) (((a) < (b)) ? (b) : (a) )
#define OI_MIN(a, b) (((a) > (b)) ? (b) : (a) )

/**
 * 比较两个BD_ADDR SAME_BD_ADDR-布尔值：如果它们是相同的地址，则为TRUE
 */

#define SAME_BD_ADDR(x, y)      (0 == OI_MemCmp((x),(y),OI_BD_ADDR_BYTE_SIZE) )

#ifdef __cplusplus
}
#endif

/**@}*/

#endif /* _OI_UTILS_H */

