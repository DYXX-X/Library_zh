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
#ifndef _OI_ASSERT_H
#define _OI_ASSERT_H
/** @file 此文件为编译时和运行时断言提供宏和函数。

  定义OI_DEBUG预处理器值后，宏OI_ASSERT将编译到程序中，提供运行时断言失败检查。C_ASSERT是可用于执行编译时检查的宏。
*/
/**********************************************************************************
  $版本：#1$
***********************************************************************************/


/**\addtogroup调试调试API*/
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif


#ifdef OI_DEBUG

/** 宏OI_ASSERT采用条件参数。如果断言条件的计算结果不为真，则OI_ASSERT宏调用依赖于主机的函数OI_AssertFail（），该函数报告失败并生成运行时错误。
*/
void OI_AssertFail(char *file, int line, char *reason);


#define OI_ASSERT(condition) \
    { if (!(condition)) OI_AssertFail(__FILE__, __LINE__, #condition); }

#define OI_ASSERT_FAIL(msg) \
    { OI_AssertFail(__FILE__, __LINE__, msg); }

#else


#define OI_ASSERT(condition)
#define OI_ASSERT_FAIL(msg)

#endif


/**
   C_ASSERT（）可用于执行许多编译时断言：类型大小、字段偏移等。断言失败会导致编译时错误C2118：负下标。不幸的是，这个优雅的宏不适用于GCC，所以现在都被注释掉了。也许稍后。。。。。
*/

#ifndef C_ASSERT
// #定义C_ASSERT（e）typedef字符__C_ASSERT__[（e）？1:-1]
// #定义C_ASSERT（e）
#endif


/*****************************************************************************/
#ifdef __cplusplus
}
#endif

/**@}*/

#endif /* _OI_ASSERT_H */

