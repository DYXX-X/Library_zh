/* ==========================================
    CMock项目-C版自动模拟生成版权所有（C）2007 Mike Karlesky，Mark VanderVoord，Greg Williams[根据MIT许可证发布。请参阅License.txt了解详细信息]
========================================== */

#ifndef CMOCK_FRAMEWORK_INTERNALS_H
#define CMOCK_FRAMEWORK_INTERNALS_H

#include "unity.h"

/* 这些是生成的模拟可以访问的常量*/
extern const char* CMockStringOutOfMemory;
extern const char* CMockStringCalledMore;
extern const char* CMockStringCalledLess;
extern const char* CMockStringCalledEarly;
extern const char* CMockStringCalledLate;
extern const char* CMockStringCallOrder;
extern const char* CMockStringIgnPreExp;
extern const char* CMockStringPtrPreExp;
extern const char* CMockStringPtrIsNULL;
extern const char* CMockStringExpNULL;
extern const char* CMockStringMismatch;

/* 定义CMOCK_MEM_DYNAMIC以根据需要使用malloc抓取内存。当您这样做时，CMOCK_MEM_SIZE用于增量大小而不是总大小*/
#ifdef CMOCK_MEM_STATIC
#undef CMOCK_MEM_DYNAMIC
#endif

#ifdef CMOCK_MEM_DYNAMIC
#include <stdlib.h>
#endif

/* 这在指针运算期间在内部使用。确保此类型与目标的指针类型大小相同*/
#ifndef CMOCK_MEM_PTR_AS_INT
#ifdef UNITY_POINTER_WIDTH
#ifdef UNITY_INT_WIDTH
#if UNITY_POINTER_WIDTH == UNITY_INT_WIDTH
#define CMOCK_MEM_PTR_AS_INT unsigned int
#endif
#endif
#endif
#endif

#ifndef CMOCK_MEM_PTR_AS_INT
#ifdef UNITY_POINTER_WIDTH
#ifdef UNITY_LONG_WIDTH
#if UNITY_POINTER_WIDTH == UNITY_LONG_WIDTH
#define CMOCK_MEM_PTR_AS_INT unsigned long
#endif
#if UNITY_POINTER_WIDTH > UNITY_LONG_WIDTH
#define CMOCK_MEM_PTR_AS_INT unsigned long long
#endif
#endif
#endif
#endif

#ifndef CMOCK_MEM_PTR_AS_INT
#define CMOCK_MEM_PTR_AS_INT unsigned long
#endif

/* 0表示无对齐，1表示16位，2表示32位，3表示64位*/
#ifndef CMOCK_MEM_ALIGN
  #ifdef UNITY_LONG_WIDTH
    #if (UNITY_LONG_WIDTH == 16)
      #define CMOCK_MEM_ALIGN (1)
    #elif (UNITY_LONG_WIDTH == 32)
      #define CMOCK_MEM_ALIGN (2)
    #elif (UNITY_LONG_WIDTH == 64)
      #define CMOCK_MEM_ALIGN (3)
    #else
      #define CMOCK_MEM_ALIGN (2)
    #endif
  #else
    #define CMOCK_MEM_ALIGN (2)
  #endif
#endif

/* 允许cmock在其内部堆中使用的内存量*/
#ifndef CMOCK_MEM_SIZE
#define CMOCK_MEM_SIZE (32768)
#endif

/* 自动计算defs以便于阅读*/
#define CMOCK_MEM_ALIGN_SIZE  (CMOCK_MEM_INDEX_TYPE)(1u << CMOCK_MEM_ALIGN)
#define CMOCK_MEM_ALIGN_MASK  (CMOCK_MEM_INDEX_TYPE)(CMOCK_MEM_ALIGN_SIZE - 1)
#define CMOCK_MEM_INDEX_SIZE  (CMOCK_MEM_INDEX_TYPE)(CMOCK_MEM_PTR_AS_INT)((sizeof(CMOCK_MEM_INDEX_TYPE) > CMOCK_MEM_ALIGN_SIZE) ? sizeof(CMOCK_MEM_INDEX_TYPE) : CMOCK_MEM_ALIGN_SIZE)


#endif /* CMOCK_FRAMEWORK_INTERNALS_H结束*/

