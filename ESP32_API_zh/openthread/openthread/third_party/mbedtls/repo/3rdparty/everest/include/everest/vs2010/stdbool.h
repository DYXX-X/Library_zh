/*
 *  自定义stdbool。h for VS2010 KreMLin需要这些定义，但VS2010没有提供这些定义。
 *
 *  版权所有2016-2018 INRIA和Microsoft Corporation SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 *  此文件是mbed TLS的一部分(https://tls.mbed.org)
 */

#ifndef _STDBOOL_H_VS2010
#define _STDBOOL_H_VS2010

typedef int bool;

static bool true = 1;
static bool false = 0;

#endif

