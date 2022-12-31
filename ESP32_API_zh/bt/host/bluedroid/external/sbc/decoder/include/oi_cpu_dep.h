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
#ifndef _OI_CPU_DEP_H
#define _OI_CPU_DEP_H
/**
 * @file 该文件包含目标CPU和编译器特性的定义，包括原始数据类型和端序。
 *
 * 该文件定义了各种CPU系列的字节顺序和基本数据类型。必须将预处理器符号“CPU”定义为适当的值，否则此标头将生成编译时错误。
 *
 * @note 此头文件的文档使用x86系列处理器作为CPU/编译器相关数据类型定义的示例。转到此头文件的源代码，查看每个平台的基本类型定义的详细信息。
 *
 * @ref data_types_docpage部分提供了其他信息。
 */

/**********************************************************************************
  $版本：#1$
***********************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**\addtogroup其他杂项API*/
/**@{*/

/** @name 指示目标OI_CPU_TYPE系列的定义@{
 */

#define OI_CPU_X86         1 /**<x86处理器系列*/
#define OI_CPU_ARM         2 /**< ARM处理器系列。
                                  @不推荐使用#OI_CPU_ARM7_END或#OI_CPU _ARM7_ END。*/
#define OI_CPU_ARC         3 /**< ARC处理器系列。
                                  @不推荐使用#OI_CPU_ARC_LEND或#OI_CPU _ARC_BEND。*/
#define OI_CPU_SH3         4 /**<Hitachi SH-3处理器系列*/
#define OI_CPU_H8          5 /**<Hitachi H8处理器系列*/
#define OI_CPU_MIPS        6 /**<MIPS处理器系列*/
#define OI_CPU_SPARC       7 /**<SPARC处理器系列*/
#define OI_CPU_M68000      8 /**<Motorola M68000处理器系列*/
#define OI_CPU_PPC         9 /**<PowerPC（PPC）处理器系列*/
#define OI_CPU_SH4_7750   10 /**<SH-4处理器系列中的日立SH7750系列*/
#define OI_CPU_SH2        11 /**<Hitachi SH-2处理器系列*/
#define OI_CPU_ARM7_LEND  12 /**<ARM7，小端序*/
#define OI_CPU_ARM7_BEND  13 /**<ARM7，大端*/
#define OI_CPU_GDM1202    14 /**< GCT GDM1202 */
#define OI_CPU_ARC_LEND   15 /**<ARC处理器系列，小端*/
#define OI_CPU_ARC_BEND   16 /**<ARC处理器系列，大端*/
#define OI_CPU_M30833F    17 /**<Mitsubishi M308处理器系列*/
#define OI_CPU_CR16C      18 /**<National Semiconductor 16位处理器系列*/
#define OI_CPU_M64111     19 /**<Renesas M64111处理器（M32R系列）*/
#define OI_CPU_ARMV5_LEND 20 //*<ARM5，小端序*/

#define OI_CPU_TYPE 12

#ifndef OI_CPU_TYPE
#error "OI_CPU_TYPE type not defined"
#endif

/**@}*/


/** @name 指示目标CPU字节顺序的定义@{
 */

#define OI_BIG_ENDIAN_BYTE_ORDER    0  /**<多字节值从最低地址的最高有效字节开始存储在内存中。*/
#define OI_LITTLE_ENDIAN_BYTE_ORDER 1  /**<多字节值从最低地址的最低有效字节开始存储在内存中。*/

/**@}*/


/** @name  CPU/编译器无关的基元数据类型定义@{
 */

typedef int             OI_BOOL;  /**<布尔值使用目标CPU的本机整数数据类型。*/
typedef int             OI_INT;   /**<整数值使用目标CPU的本机整数数据类型。*/
typedef unsigned int    OI_UINT;  /**<无符号整数值使用目标CPU的本机无符号整数数据类型。*/
typedef unsigned char   OI_BYTE;  /**<原始字节类型使用目标CPU的本机字符数据类型。*/

/**@}*/



/*********************************************************************************/

#if OI_CPU_TYPE==OI_CPU_X86

#define OI_CPU_BYTE_ORDER OI_LITTLE_ENDIAN_BYTE_ORDER  /**<x86平台字节排序是小端序*/

/** @name x86处理器系列的CPU/编译器相关基元数据类型定义@{
 */
typedef signed char     OI_INT8;   /**<8位有符号整数值使用x86处理器的本机有符号字符数据类型。*/
typedef signed short    OI_INT16;  /**<16位有符号整数值使用x86处理器的本机有符号短整数数据类型。*/
typedef signed long     OI_INT32;  /**<32位有符号整数值使用x86处理器的本机有符号长整数数据类型。*/
typedef unsigned char   OI_UINT8;  /**<8位无符号整数值使用x86处理器的本机无符号字符数据类型。*/
typedef unsigned short  OI_UINT16; /**<16位无符号整数值使用x86处理器的本机无符号短整数数据类型。*/
typedef unsigned long   OI_UINT32; /**<32位无符号整数值使用x86处理器的本机无符号长整数数据类型。*/

typedef OI_UINT32 OI_ELEMENT_UNION; /**＜联合的第一个元素的类型，以支持指针宽度以下的所有数据类型。*/

/**@}*/

#endif

/*********************************************************************************/

#if OI_CPU_TYPE==OI_CPU_ARM
/* 此CPU类型已弃用（不再使用）。相反，对于ARM7的小端或大端配置，分别使用OI_CPU_ARM7_END或OI_CPU-ARM7_BEND。*/
#error OI_CPU_ARM is deprecated
#endif

/*********************************************************************************/

#if OI_CPU_TYPE==OI_CPU_ARC
/* 此CPU类型已弃用（不再使用）。相反，对于ARC的小端或大端配置，分别使用OI_CPU_ARC_LEND或OI_CPU-ARC_BEND。*/
#error OI_CPU_ARC is deprecated
#endif

/*********************************************************************************/

#if OI_CPU_TYPE==OI_CPU_SH3
/* Hitachi SH C编译器定义_LIT或_BIG，具体取决于在命令行上为编译器指定的端序。*/
#if defined(_LIT)
#define OI_CPU_BYTE_ORDER OI_LITTLE_ENDIAN_BYTE_ORDER  /**<如果定义了_LIT，SH-3平台字节顺序为小端。*/
#elif defined(_BIG)
#define OI_CPU_BYTE_ORDER OI_BIG_ENDIAN_BYTE_ORDER     /**<如果定义了_BIG，SH-3平台字节顺序为大端。*/
#else
#error SH compiler endianness undefined
#endif

/** @name SH-3处理器系列的CPU/编译器相关基元数据类型定义@{
 */

typedef signed char     OI_INT8;   /**<8位有符号整数值使用SH-3处理器的本机有符号字符数据类型。*/
typedef signed short    OI_INT16;  /**<16位有符号整数值使用SH-3处理器的本机有符号短整数数据类型。*/
typedef signed long     OI_INT32;  /**<32位有符号整数值使用SH-3处理器的本机有符号长整数数据类型。*/
typedef unsigned char   OI_UINT8;  /**<8位无符号整数值使用SH-3处理器的本机无符号字符数据类型。*/
typedef unsigned short  OI_UINT16; /**<16位无符号整数值使用SH-3处理器的本机无符号短整数数据类型。*/
typedef unsigned long   OI_UINT32; /**<32位无符号整数值使用SH-3处理器的本机无符号长整数数据类型。*/

typedef OI_UINT32 OI_ELEMENT_UNION; /**＜联合的第一个元素的类型，以支持指针宽度以下的所有数据类型。*/

/**@}*/

#endif
/*********************************************************************************/

#if OI_CPU_TYPE==OI_CPU_SH2

#define OI_CPU_BYTE_ORDER OI_BIG_ENDIAN_BYTE_ORDER /**<SH-2平台字节顺序为大端。*/

/** @name  SH-2处理器系列的CPU/编译器相关基元数据类型定义@{
 */

typedef signed char     OI_INT8;   /**＜8位有符号整数值使用SH-2处理器的本机有符号字符数据类型。*/
typedef signed short    OI_INT16;  /**<16位有符号整数值使用SH-2处理器的本机有符号短整数数据类型。*/
typedef signed long     OI_INT32;  /**<32位有符号整数值使用SH-2处理器的本机有符号长整数数据类型。*/
typedef unsigned char   OI_UINT8;  /**<8位无符号整数值使用SH-2处理器的本机无符号字符数据类型。*/
typedef unsigned short  OI_UINT16; /**<16位无符号整数值使用SH-2处理器的本机无符号短整数数据类型。*/
typedef unsigned long   OI_UINT32; /**<32位无符号整数值使用SH-2处理器的本机无符号长整数数据类型。*/

typedef OI_UINT32 OI_ELEMENT_UNION; /**＜联合的第一个元素的类型，以支持指针宽度以下的所有数据类型。*/

/**@}*/

#endif
/*********************************************************************************/

#if OI_CPU_TYPE==OI_CPU_H8
#define OI_CPU_BYTE_ORDER OI_BIG_ENDIAN_BYTE_ORDER
#error basic types not defined
#endif

/*********************************************************************************/

#if OI_CPU_TYPE==OI_CPU_MIPS
#define OI_CPU_BYTE_ORDER OI_LITTLE_ENDIAN_BYTE_ORDER
/** @name  MIPS处理器系列的CPU/编译器相关基元数据类型定义@{
 */
typedef signed char     OI_INT8;   /**<8位有符号整数值使用ARM7处理器的本机有符号字符数据类型。*/
typedef signed short    OI_INT16;  /**<16位有符号整数值使用ARM7处理器的本机有符号短整数数据类型。*/
typedef signed long     OI_INT32;  /**<32位有符号整数值使用ARM7处理器的本机有符号长整数数据类型。*/
typedef unsigned char   OI_UINT8;  /**<8位无符号整数值使用ARM7处理器的本机无符号字符数据类型。*/
typedef unsigned short  OI_UINT16; /**<16位无符号整数值使用ARM7处理器的本机无符号短整数数据类型。*/
typedef unsigned long   OI_UINT32; /**<32位无符号整数值使用ARM7处理器的本机无符号长整数数据类型。*/

typedef OI_UINT32 OI_ELEMENT_UNION; /**＜联合的第一个元素的类型，以支持指针宽度以下的所有数据类型。*/

/**@}*/

#endif

/*********************************************************************************/

#if OI_CPU_TYPE==OI_CPU_SPARC
#define OI_CPU_BYTE_ORDER OI_LITTLE_ENDIAN_BYTE_ORDER
#error basic types not defined
#endif

/*********************************************************************************/

#if OI_CPU_TYPE==OI_CPU_M68000
#define OI_CPU_BYTE_ORDER OI_BIG_ENDIAN_BYTE_ORDER  /**<M68000平台字节顺序为大端。*/

/** @name  M68000处理器系列的CPU/编译器相关基元数据类型定义@{
 */

typedef signed char     OI_INT8;   /**<8位有符号整数值使用M68000处理器的本机有符号字符数据类型。*/
typedef signed short    OI_INT16;  /**<16位有符号整数值使用M68000处理器的本机有符号短整数数据类型。*/
typedef signed long     OI_INT32;  /**<32位有符号整数值使用M68000处理器的本机有符号长整数数据类型。*/
typedef unsigned char   OI_UINT8;  /**<8位无符号整数值使用M68000处理器的本机无符号字符数据类型。*/
typedef unsigned short  OI_UINT16; /**<16位无符号整数值使用M68000处理器的本机无符号短整数数据类型。*/
typedef unsigned long   OI_UINT32; /**<32位无符号整数值使用M68000处理器的本机无符号长整数数据类型。*/

typedef OI_UINT32 OI_ELEMENT_UNION; /**＜联合的第一个元素的类型，以支持指针宽度以下的所有数据类型。*/

/**@}*/

#endif

/*********************************************************************************/

#if OI_CPU_TYPE==OI_CPU_PPC
#define OI_CPU_BYTE_ORDER OI_BIG_ENDIAN_BYTE_ORDER


/** @name  PPC 8XX处理器系列的CPU/编译器相关基元数据类型定义@{
 */

typedef signed char     OI_INT8;   /**<8位有符号整数值使用PPC8XX处理器的本机有符号字符数据类型。*/
typedef signed short    OI_INT16;  /**<16位有符号整数值使用PPC8XX处理器的本机有符号短整数数据类型。*/
typedef signed long     OI_INT32;  /**<32位有符号整数值使用PPC8XX处理器的本机有符号长整数数据类型。*/
typedef unsigned char   OI_UINT8;  /**<8位无符号整数值使用PPC8XX处理器的本机无符号字符数据类型。*/
typedef unsigned short  OI_UINT16; /**<16位无符号整数值使用PPC8XX处理器的本机无符号短整数数据类型。*/
typedef unsigned long   OI_UINT32; /**<32位无符号整数值使用PPC8XX处理器的本机无符号长整数数据类型。*/

typedef OI_UINT32 OI_ELEMENT_UNION; /**＜联合的第一个元素的类型，以支持指针宽度以下的所有数据类型。*/

/**@}*/

#endif

/*********************************************************************************/

#if OI_CPU_TYPE==OI_CPU_SH4_7750
#define OI_CPU_BYTE_ORDER OI_BIG_ENDIAN_BYTE_ORDER  /**<SH7750平台字节顺序为大端。*/

/** @name   SH-4处理器系列SH7750处理器系列的CPU/编译器相关基元数据类型定义@{
 */

typedef signed char     OI_INT8;   /**＜8位有符号整数值使用SH7750 SH-4处理器的本机有符号字符数据类型。*/
typedef signed short    OI_INT16;  /**<16位有符号整数值使用SH7750 SH-4处理器的本机有符号短整数数据类型。*/
typedef signed long     OI_INT32;  /**<32位有符号整数值使用SH7750 SH-4处理器的本机有符号长整数数据类型。*/
typedef unsigned char   OI_UINT8;  /**<8位无符号整数值使用SH7750 SH-4处理器的本机无符号字符数据类型。*/
typedef unsigned short  OI_UINT16; /**<16位无符号整数值使用SH7750 SH-4处理器的本机无符号短整数数据类型。*/
typedef unsigned long   OI_UINT32; /**<32位无符号整数值使用SH7750 SH-4处理器的本机无符号长整数数据类型。*/

typedef OI_UINT32 OI_ELEMENT_UNION; /**＜联合的第一个元素的类型，以支持指针宽度以下的所有数据类型。*/

/**@}*/

#endif

/*********************************************************************************/

#if OI_CPU_TYPE==OI_CPU_ARM7_LEND
#define OI_CPU_BYTE_ORDER OI_LITTLE_ENDIAN_BYTE_ORDER

/** @name   ARM7处理器系列的小端CPU/编译器相关原语数据类型定义@{
 */

typedef signed char     OI_INT8;   /**<8位有符号整数值使用ARM7处理器的本机有符号字符数据类型。*/
typedef signed short    OI_INT16;  /**<16位有符号整数值使用ARM7处理器的本机有符号短整数数据类型。*/
typedef signed long     OI_INT32;  /**<32位有符号整数值使用ARM7处理器的本机有符号长整数数据类型。*/
typedef unsigned char   OI_UINT8;  /**<8位无符号整数值使用ARM7处理器的本机无符号字符数据类型。*/
typedef unsigned short  OI_UINT16; /**<16位无符号整数值使用ARM7处理器的本机无符号短整数数据类型。*/
typedef unsigned long   OI_UINT32; /**<32位无符号整数值使用ARM7处理器的本机无符号长整数数据类型。*/

typedef void *OI_ELEMENT_UNION;  /**＜联合的第一个元素的类型，以支持指针宽度以下的所有数据类型。*/

/**@}*/

#endif

/*********************************************************************************/

#if OI_CPU_TYPE==OI_CPU_ARM7_BEND
#define OI_CPU_BYTE_ORDER OI_BIG_ENDIAN_BYTE_ORDER
/** @name   ARM7处理器系列的大端CPU/编译器相关原语数据类型定义@{
 */
typedef signed char     OI_INT8;   /**<8位有符号整数值使用ARM7处理器的本机有符号字符数据类型。*/
typedef signed short    OI_INT16;  /**<16位有符号整数值使用ARM7处理器的本机有符号短整数数据类型。*/
typedef signed long     OI_INT32;  /**<32位有符号整数值使用ARM7处理器的本机有符号长整数数据类型。*/
typedef unsigned char   OI_UINT8;  /**<8位无符号整数值使用ARM7处理器的本机无符号字符数据类型。*/
typedef unsigned short  OI_UINT16; /**<16位无符号整数值使用ARM7处理器的本机无符号短整数数据类型。*/
typedef unsigned long   OI_UINT32; /**<32位无符号整数值使用ARM7处理器的本机无符号长整数数据类型。*/

typedef void *OI_ELEMENT_UNION;  /**＜联合的第一个元素的类型，以支持指针宽度以下的所有数据类型。*/

/**@}*/

#endif

/*********************************************************************************/

#if OI_CPU_TYPE==OI_CPU_GDM1202
#define OI_CPU_BYTE_ORDER OI_BIG_ENDIAN_BYTE_ORDER

typedef signed char     OI_INT8;   /**<8位有符号整数。*/
typedef signed short    OI_INT16;  /**<16位有符号整数。*/
typedef signed long     OI_INT32;  /**<32位有符号整数。*/
typedef unsigned char   OI_UINT8;  /**<8位无符号整数。*/
typedef unsigned short  OI_UINT16; /**<16位无符号整数。*/
typedef unsigned long   OI_UINT32; /**<32位无符号整数。*/

typedef OI_UINT32 OI_ELEMENT_UNION; /**＜联合的第一个元素的类型，以支持指针宽度以下的所有数据类型。*/

#endif

/*********************************************************************************/

#if OI_CPU_TYPE==OI_CPU_ARC_LEND

#define OI_CPU_BYTE_ORDER OI_LITTLE_ENDIAN_BYTE_ORDER

/** @name ARC处理器系列的CPU/编译器相关基元数据类型定义@{
 */

typedef signed char     OI_INT8;   /**<8位有符号整数值使用ARC处理器的本机有符号字符数据类型。*/
typedef signed short    OI_INT16;  /**<16位有符号整数值使用ARC处理器的本机有符号短整数数据类型。*/
typedef signed long     OI_INT32;  /**<32位有符号整数值使用ARC处理器的本机有符号长整数数据类型。*/
typedef unsigned char   OI_UINT8;  /**<8位无符号整数值使用ARC处理器的本机无符号字符数据类型。*/
typedef unsigned short  OI_UINT16; /**<16位无符号整数值使用ARC处理器的本机无符号短整数数据类型。*/
typedef unsigned long   OI_UINT32; /**<32位无符号整数值使用ARC处理器的本机无符号长整数数据类型。*/

typedef OI_UINT32 OI_ELEMENT_UNION; /**＜联合的第一个元素的类型，以支持指针宽度以下的所有数据类型。*/

/**@}*/
#endif

/*********************************************************************************/

#if OI_CPU_TYPE==OI_CPU_ARC_BEND

#define OI_CPU_BYTE_ORDER OI_BIG_ENDIAN_BYTE_ORDER

/** @name ARC处理器系列的CPU/编译器相关基元数据类型定义@{
 */

typedef signed char     OI_INT8;   /**<8位有符号整数值使用ARC处理器的本机有符号字符数据类型。*/
typedef signed short    OI_INT16;  /**<16位有符号整数值使用ARC处理器的本机有符号短整数数据类型。*/
typedef signed long     OI_INT32;  /**<32位有符号整数值使用ARC处理器的本机有符号长整数数据类型。*/
typedef unsigned char   OI_UINT8;  /**<8位无符号整数值使用ARC处理器的本机无符号字符数据类型。*/
typedef unsigned short  OI_UINT16; /**<16位无符号整数值使用ARC处理器的本机无符号短整数数据类型。*/
typedef unsigned long   OI_UINT32; /**<32位无符号整数值使用ARC处理器的本机无符号长整数数据类型。*/

typedef OI_UINT32 OI_ELEMENT_UNION; /**＜联合的第一个元素的类型，以支持指针宽度以下的所有数据类型。*/

/**@}*/
#endif

/*********************************************************************************/

#if OI_CPU_TYPE==OI_CPU_M30833F

#define OI_CPU_BYTE_ORDER OI_LITTLE_ENDIAN_BYTE_ORDER

/** @name 三菱M308处理器系列的CPU/编译器相关原语数据类型定义@{
 */

typedef signed char     OI_INT8;   /**<8位有符号整数值使用M308处理器的本机有符号字符数据类型。*/
typedef signed short    OI_INT16;  /**<16位有符号整数值使用M308处理器的本机有符号短整数数据类型。*/
typedef signed long     OI_INT32;  /**<32位有符号整数值使用M308处理器的本机有符号长整数数据类型。*/
typedef unsigned char   OI_UINT8;  /**<8位无符号整数值使用M308处理器的本机无符号字符数据类型。*/
typedef unsigned short  OI_UINT16; /**＜16位无符号整数值使用M308处理器的本机无符号短整数数据类型。*/
typedef unsigned long   OI_UINT32; /**<32位无符号整数值使用M308处理器的本机无符号长整数数据类型。*/

typedef OI_UINT32 OI_ELEMENT_UNION; /**＜联合的第一个元素的类型，以支持指针宽度以下的所有数据类型。*/

/**@}*/
#endif

/*********************************************************************************/

#if OI_CPU_TYPE==OI_CPU_CR16C

#define OI_CPU_BYTE_ORDER OI_LITTLE_ENDIAN_BYTE_ORDER

/** @name National Semiconductor处理器系列的CPU/编译器相关基元数据类型定义@{
 */

typedef signed char     OI_INT8;   /**＜8位有符号整数值使用CR16C处理器的本机有符号字符数据类型。*/
typedef signed short    OI_INT16;  /**<16位有符号整数值使用CR16C处理器的本机有符号短整数数据类型。*/
typedef signed long     OI_INT32;  /**<32位有符号整数值使用CR16C处理器的本机有符号长整数数据类型。*/
typedef unsigned char   OI_UINT8;  /**<8位无符号整数值使用CR16C处理器的本机无符号字符数据类型。*/
typedef unsigned short  OI_UINT16; /**<16位无符号整数值使用CR16C处理器的本机无符号短整数数据类型。*/
typedef unsigned long   OI_UINT32; /**<32位无符号整数值使用CR16C处理器的本机无符号长整数数据类型。*/

typedef OI_UINT32 OI_ELEMENT_UNION; /**＜联合的第一个元素的类型，以支持指针宽度以下的所有数据类型。*/

/**@}*/
#endif

/*********************************************************************************/

#if OI_CPU_TYPE==OI_CPU_M64111

#define OI_CPU_BYTE_ORDER OI_BIG_ENDIAN_BYTE_ORDER

/** @name Renesas M32R处理器系列的CPU/编译器相关原语数据类型定义@{
 */

typedef signed char     OI_INT8;   /**<8位有符号整数值使用M64111处理器的本机有符号字符数据类型。*/
typedef signed short    OI_INT16;  /**<16位有符号整数值使用M64111处理器的本机有符号短整数数据类型。*/
typedef signed long     OI_INT32;  /**<32位有符号整数值使用M64111处理器的本机有符号长整数数据类型。*/
typedef unsigned char   OI_UINT8;  /**<8位无符号整数值使用M64111处理器的本机无符号字符数据类型。*/
typedef unsigned short  OI_UINT16; /**<16位无符号整数值使用M64111处理器的本机无符号短整数数据类型。*/
typedef unsigned long   OI_UINT32; /**<32位无符号整数值使用M64111处理器的本机无符号长整数数据类型。*/

typedef OI_UINT32 OI_ELEMENT_UNION; /**＜联合的第一个元素的类型，以支持指针宽度以下的所有数据类型。*/

/**@}*/
#endif

/*********************************************************************************/

#if OI_CPU_TYPE==OI_CPU_ARMV5_LEND
#define OI_CPU_BYTE_ORDER OI_LITTLE_ENDIAN_BYTE_ORDER

/** @name   ARM7处理器系列的小端CPU/编译器相关原语数据类型定义@{
 */

typedef signed char     OI_INT8;   /**<8位有符号整数值使用ARM7处理器的本机有符号字符数据类型。*/
typedef signed short    OI_INT16;  /**<16位有符号整数值使用ARM7处理器的本机有符号短整数数据类型。*/
typedef signed long     OI_INT32;  /**<32位有符号整数值使用ARM7处理器的本机有符号长整数数据类型。*/
typedef unsigned char   OI_UINT8;  /**<8位无符号整数值使用ARM7处理器的本机无符号字符数据类型。*/
typedef unsigned short  OI_UINT16; /**<16位无符号整数值使用ARM7处理器的本机无符号短整数数据类型。*/
typedef unsigned long   OI_UINT32; /**<32位无符号整数值使用ARM7处理器的本机无符号长整数数据类型。*/

typedef OI_UINT32 OI_ELEMENT_UNION; /**＜联合的第一个元素的类型，以支持指针宽度以下的所有数据类型。*/

/**@}*/

#endif

/*********************************************************************************/


#ifndef OI_CPU_BYTE_ORDER
#error "Byte order (endian-ness) not defined"
#endif


/**@}*/

#ifdef __cplusplus
}
#endif

/*********************************************************************************/
#endif /* _OI_CPU_DEP_H */

