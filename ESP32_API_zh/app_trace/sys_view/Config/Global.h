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
----------------------------------------------------------------------文件：全局。hPurpose:全局类型如果您的应用程序已经具有全局。h、 你应该合并这些文件。为了使用Segger代码，需要在Global中定义类型U8、U16、U32、I8、I16、I32。h；附加的定义并没有伤害。
---------------------------END-OF-HEADER------------------------------
*/

#ifndef GLOBAL_H            // 防止多重包含
#define GLOBAL_H

#define U8    unsigned char
#define U16   unsigned short
#define U32   unsigned long
#define I8    signed char
#define I16   signed short
#define I32   signed long

#ifdef _WIN32
  //
  // 与Microsoft VC6编译器相关
  //
  #define U64   unsigned __int64
  #define U128  unsigned __int128
  #define I64   __int64
  #define I128  __int128
  #if _MSC_VER <= 1200
    #define U64_C(x) x##UI64
  #else
    #define U64_C(x) x##ULL
  #endif
#else
  //
  // C99兼容编译器
  //
  #define U64   unsigned long long
  #define I64   signed long long
  #define U64_C(x) x##ULL
#endif

#endif                      // 避免多次包含

/***************************文件结尾****************************/
