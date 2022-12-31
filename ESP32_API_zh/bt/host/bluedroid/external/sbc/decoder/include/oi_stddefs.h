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
#ifndef OI_STDDEFS_H
#define OI_STDDEFS_H
/**
 * @file 此文件包含BM3标准类型定义。
 *
 */

/**********************************************************************************
  $版本：#1$
***********************************************************************************/

#include "oi_cpu_dep.h"

/**\addtogroup其他杂项API*/
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef FALSE
#define FALSE 0         /**<此define语句将FALSE设置为0的预处理器别名。*/
#endif

#ifndef TRUE
#define TRUE (!FALSE)  /**<此define语句将TRUE设置为的预处理器别名！错误的*/
#endif

#ifdef HEW_TOOLCHAIN
#ifdef NULL
#undef NULL         /**<覆盖HEW工具链NULL定义*/
#endif
#define NULL 0          /**<HEW工具链不允许我们将（void*）类型与函数指针进行比较*/
#else
#ifndef NULL
#define NULL ((void*)0) /**<此define语句将NULL设置为（void*）0的预处理器别名*/
#endif
#endif

/**
 * @name  基本类型的最大值和最小值@{
 */
#define OI_INT8_MIN   ((OI_INT8)0x80)          /**<十进制值：-128*/
#define OI_INT8_MAX   ((OI_INT8)0x7F)          /**<十进制值：127*/
#define OI_INT16_MIN  ((OI_INT16)0x8000)       /**<十进制值：-32768*/
#define OI_INT16_MAX  ((OI_INT16)0x7FFF)       /**<十进制值：32767*/
#define OI_INT32_MIN  ((OI_INT32)0x80000000)   /**<十进制值：-2147483648*/
#define OI_INT32_MAX  ((OI_INT32)0x7FFFFFFF)   /**<十进制值：2147483647*/
#define OI_UINT8_MIN  ((OI_UINT8)0)            /**<十进制值：0*/
#define OI_UINT8_MAX  ((OI_UINT8)0xFF)         /**<十进制值：255*/
#define OI_UINT16_MIN ((OI_UINT16)0)           /**<十进制值：0*/
#define OI_UINT16_MAX ((OI_UINT16)0xFFFF)      /**<十进制值：65535*/
#define OI_UINT32_MIN ((OI_UINT32)0)           /**<十进制值：0*/
#define OI_UINT32_MAX ((OI_UINT32)0xFFFFFFFF)  /**<十进制值：4294967295*/

/**
 * @}
 */

/**
 * @name  服务发现协议所需的整数类型@{
 */

/**无符号64位整数作为两个无符号32位整数的结构*/
typedef struct {
    OI_UINT32 I1; /**<最高有效32位*/
    OI_UINT32 I2; /**<最低有效32位*/
} OI_UINT64;

#define OI_UINT64_MIN { (OI_UINT32)0x00000000, (OI_UINT32)0x00000000 }
#define OI_UINT64_MAX { (OI_UINT32)0XFFFFFFFF, (OI_UINT32)0XFFFFFFFF }

/**有符号64位整数，一个无符号32位整数和一个有符号32位整型的结构*/
typedef struct {
    OI_INT32  I1; /**<最高有效32位作为有符号整数*/
    OI_UINT32 I2; /**<作为无符号整数的最低有效32位*/
} OI_INT64;

#define OI_INT64_MIN { (OI_INT32)0x80000000, (OI_UINT32)0x00000000 }
#define OI_INT64_MAX { (OI_INT32)0X7FFFFFFF, (OI_UINT32)0XFFFFFFFF }

/**无符号128位整数作为四个无符号32位整数的结构*/
typedef struct {
    OI_UINT32 I1; /**<最高有效32位*/
    OI_UINT32 I2; /**<第二高有效32位*/
    OI_UINT32 I3; /**<第三最高有效32位*/
    OI_UINT32 I4; /**<最低有效32位*/
} OI_UINT128;

#define OI_UINT128_MIN { (OI_UINT32)0x00000000, (OI_UINT32)0x00000000,  (OI_UINT32)0x00000000, (OI_UINT32)0x00000000 }
#define OI_UINT128_MAX { (OI_UINT32)0XFFFFFFFF, (OI_UINT32)0XFFFFFFFF,  (OI_UINT32)0XFFFFFFFF, (OI_UINT32)0XFFFFFFFF }

/**有符号128位整数，由三个无符号32位整数和一个有符号32位整型组成*/
typedef struct {
    OI_INT32  I1;  /**<最高有效32位作为有符号整数*/
    OI_UINT32 I2;  /**<第二高有效32位（无符号整数）*/
    OI_UINT32 I3;  /**<作为无符号整数的第三最高有效32位*/
    OI_UINT32 I4;  /**<作为无符号整数的最低有效32位*/
} OI_INT128;

#define OI_INT128_MIN { (OI_UINT32)0x80000000, (OI_UINT32)0x00000000,  (OI_UINT32)0x00000000, (OI_UINT32)0x00000000 }
#define OI_INT128_MAX { (OI_UINT32)0X7FFFFFFF, (OI_UINT32)0XFFFFFFFF,  (OI_UINT32)0XFFFFFFFF, (OI_UINT32)0XFFFFFFFF }

/**
 * @}
 */


/**
 * ASCII字符数据项的类型
 */
typedef char OI_CHAR;

/**
 * 双字节字符数据项的类型
 */
typedef OI_UINT16 OI_CHAR16;

/**
 * UTF编码字符串的类型。
 */
typedef OI_UINT8  OI_UTF8;
typedef OI_UINT16 OI_UTF16;
typedef OI_UINT32 OI_UTF32;


/**
 * @name 单位操作宏@{在这些宏中，x是要测试或设置位的数据项，y指定要测试或设定的位。
 */

/**如果在数据项x中设置了y指定的位，则此宏的值为TRUE。*/
#define OI_BIT_TEST(x,y)   ((x) & (y))

/**如果数据项x中未设置y指定的位，则此宏的值为TRUE。*/
#define OI_BIT_CLEAR_TEST(x,y)  (((x) & (y)) == 0)

/**此宏设置数据项x中y指定的位。*/
#define OI_BIT_SET(x,y)    ((x) |= (y))

/**此宏清除数据项x中y指定的位。*/
#define OI_BIT_CLEAR(x,y)  ((x) &= ~(y))

/** @} */

/**
 * OI_ARRAYSIZE宏设置为数组中的元素数（而不是由sizeof（）返回的字节数）。
 */

#ifndef OI_ARRAYSIZE
#define OI_ARRAYSIZE(a) (sizeof(a)/sizeof(a[0]))
#endif

/**
 * @name 单个位位置的预处理器别名仅在尚未定义位时才在此处定义位@{
 */

#ifndef BIT0

#define BIT0   0x00000001  /**＜设置了位0的32位值的预处理器别名，用于指定此单个位*/
#define BIT1   0x00000002  /**＜设置了位1的32位值的预处理器别名，用于指定此单个位*/
#define BIT2   0x00000004  /**＜设置了位2的32位值的预处理器别名，用于指定此单个位*/
#define BIT3   0x00000008  /**＜设置了位3的32位值的预处理器别名，用于指定此单个位*/
#define BIT4   0x00000010  /**＜设置了位4的32位值的预处理器别名，用于指定此单个位*/
#define BIT5   0x00000020  /**＜设置了位5的32位值的预处理器别名，用于指定此单个位*/
#define BIT6   0x00000040  /**＜设置了位6的32位值的预处理器别名，用于指定此单个位*/
#define BIT7   0x00000080  /**＜设置了位7的32位值的预处理器别名，用于指定此单个位*/
#define BIT8   0x00000100  /**＜设置了位8的32位值的预处理器别名，用于指定此单个位*/
#define BIT9   0x00000200  /**＜设置了位9的32位值的预处理器别名，用于指定此单个位*/
#define BIT10  0x00000400  /**＜设置了位10的32位值的预处理器别名，用于指定此单个位*/
#define BIT11  0x00000800  /**＜设置了位11的32位值的预处理器别名，用于指定此单个位*/
#define BIT12  0x00001000  /**＜设置了位12的32位值的预处理器别名，用于指定此单个位*/
#define BIT13  0x00002000  /**＜设置了位13的32位值的预处理器别名，用于指定此单个位*/
#define BIT14  0x00004000  /**＜设置了位14的32位值的预处理器别名，用于指定此单个位*/
#define BIT15  0x00008000  /**＜设置了位15的32位值的预处理器别名，用于指定此单个位*/
#define BIT16  0x00010000  /**＜设置了位16的32位值的预处理器别名，用于指定此单个位*/
#define BIT17  0x00020000  /**＜设置了位17的32位值的预处理器别名，用于指定此单个位*/
#define BIT18  0x00040000  /**＜设置了位18的32位值的预处理器别名，用于指定此单个位*/
#define BIT19  0x00080000  /**＜设置了位19的32位值的预处理器别名，用于指定此单个位*/
#define BIT20  0x00100000  /**＜设置了位20的32位值的预处理器别名，用于指定此单个位*/
#define BIT21  0x00200000  /**＜设置了位21的32位值的预处理器别名，用于指定此单个位*/
#define BIT22  0x00400000  /**＜设置了位22的32位值的预处理器别名，用于指定此单个位*/
#define BIT23  0x00800000  /**＜设置了位23的32位值的预处理器别名，用于指定此单个位*/
#define BIT24  0x01000000  /**＜设置了位24的32位值的预处理器别名，用于指定此单个位*/
#define BIT25  0x02000000  /**＜设置了位25的32位值的预处理器别名，用于指定此单个位*/
#define BIT26  0x04000000  /**＜设置了位26的32位值的预处理器别名，用于指定此单个位*/
#define BIT27  0x08000000  /**＜设置了位27的32位值的预处理器别名，用于指定此单个位*/
#define BIT28  0x10000000  /**＜设置了位28的32位值的预处理器别名，用于指定此单个位*/
#define BIT29  0x20000000  /**＜设置了位29的32位值的预处理器别名，用于指定此单个位*/
#define BIT30  0x40000000  /**＜设置了位30的32位值的预处理器别名，用于指定此单个位*/
#define BIT31  0x80000000  /**＜设置了位31的32位值的预处理器别名，用于指定此单个位*/

#endif  /* BIT0等人*/


/** @} */


#ifdef __cplusplus
}
#endif

/**@}*/

/*****************************************************************************/
#endif /* OI_STDDEFS_H */

