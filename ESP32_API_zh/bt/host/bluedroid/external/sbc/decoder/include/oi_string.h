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
#ifndef OI_STRING_H
#define OI_STRING_H
/**
 * @file 此文件包含BM3提供的可移植字符串。h函数
 *
 */

/**********************************************************************************
  $版本：#1$
***********************************************************************************/

#include "oi_cpu_dep.h"
#include "oi_stddefs.h"

#if defined(USE_NATIVE_MEMCPY) || defined(USE_NATIVE_MALLOC)
#include <string.h>
#endif

/**\addtogroup其他杂项API*/
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif


/*
 * 如果我们使用的是Native malloc（），我们还必须使用Native Ansi字符串。h函数用于内存操作。
 */
#ifdef USE_NATIVE_MALLOC
#ifndef USE_NATIVE_MEMCPY
#define USE_NATIVE_MEMCPY
#endif
#endif

#ifdef USE_NATIVE_MEMCPY

#define OI_MemCopy(to, from, size)    memcpy((to), (from), (size))
#define OI_MemSet(block, val, size)   memset((block), (val), (size))
#define OI_MemZero(block, size)       memset((block), 0, (size))
#define OI_MemCmp(s1, s2, n)          memcmp((s1), (s2), (n))
#define OI_Strcpy(dest, src)          strcpy((dest),(src))
#define OI_Strcat(dest, src)          strcat((dest),(src))
#define OI_StrLen(str)                strlen((str))
#define OI_Strcmp(s1, s2)             strcmp((s1), (s2))
#define OI_Strncmp(s1, s2, n)         strncmp((s1), (s2), (n))

#else

/*
 * OI_Mem复制
 *
 * 将任意数量的字节从一个内存地址复制到另一个。底层实现是ANSI memmove（）或等效的，因此重叠的内存副本将正常工作。
 */
void OI_MemCopy(void *To, void const *From, OI_UINT32 Size);


/*
 * OI_模块集
 *
 * 将内存块中的所有字节设置为相同的值
 */
void OI_MemSet(void *Block, OI_UINT8 Val, OI_UINT32 Size);


/*
 * OI_MemZero（OI_Mem零点）
 *
 * 将内存块中的所有字节设置为零
 */
void OI_MemZero(void *Block, OI_UINT32 Size);


/*
 * OI_MemCmp（OI_MemCmd）
 *
 * 比较两块内存
 *
 * 返回：0，如果s1==s2<0，如果s1<s2>0，如果s2>s2
 */
OI_INT OI_MemCmp(void const *s1, void const *s2, OI_UINT32 n);

/*
 * OI_字符串
 *
 * 将以Null结尾的字符串从pStr复制到pDest，并返回pDest。
 */

OI_CHAR *OI_Strcpy(OI_CHAR *pDest,
                   OI_CHAR const *pStr);

/*
 * OI_分类
 *
 * 将pStr字符串连接到pDest的末尾，并返回pDest。
 */

OI_CHAR *OI_Strcat(OI_CHAR *pDest,
                   OI_CHAR const *pStr) ;

/*
 * OI_短镜头
 *
 * 计算pStr中OI_CHAR的数量（不包括Null终止符）并返回值。
 */
OI_UINT OI_StrLen(OI_CHAR const *pStr) ;

/*
 * OI_Strcmp
 *
 * 比较两个以Null结尾的字符串
 *
 * 返回：0，如果s1==s2<0，如果s1<s2>0，如果s2>s2
 */
OI_INT OI_Strcmp(OI_CHAR const *s1,
                 OI_CHAR const *s2);

/*
 * OI_字符串
 *
 * 比较字符串s1和s2的第一个“len”OI_CHAR。
 *
 * 返回：0，如果s1==s2<0，如果s1<s2>0，如果s2>s2
 */
OI_INT OI_Strncmp(OI_CHAR const *s1,
                  OI_CHAR const *s2,
                  OI_UINT32      len);


#endif /* USE_NATIVE_MEMCPY */

/*
 * OI_Strcmp不敏感
 *
 * 比较两个以Null结尾的字符串，将“A”到“Z”的大写和小写视为等同。
 *
 * 返回：0，如果s1==s2<0，如果s1<s2>0，如果s2>s2
 */
OI_INT OI_StrcmpInsensitive(OI_CHAR const *s1,
                            OI_CHAR const *s2);

/*
 * OI_Strncmp不敏感
 *
 * 比较字符串s1和s2的第一个“len”OI_CHAR，将“A”到“Z”的大写和小写视为等同。
 *
 * 返回：0，如果s1==s2<0，如果s1<s2>0，如果s2>s2
 */
OI_INT OI_StrncmpInsensitive(OI_CHAR const *s1,
                             OI_CHAR const *s2,
                             OI_UINT        len);



#ifdef __cplusplus
}
#endif

/** @} */

/*****************************************************************************/
#endif /* OI_STRING_H */

