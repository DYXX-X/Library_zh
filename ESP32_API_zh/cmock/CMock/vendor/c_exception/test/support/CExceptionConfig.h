#ifndef _EXCEPTION_H
#define _EXCEPTION_H

#include "unity.h"

extern volatile int TestingTheFallback;
extern volatile int TestingTheFallbackId;

//可选地定义异常类型（类似于可以直接赋值的int）
#define CEXCEPTION_T    int

// 可选地定义表示无异常的保留值
#define CEXCEPTION_NONE (1234)

// （可选）为未处理的异常定义特殊处理程序
#define CEXCEPTION_NO_CATCH_HANDLER(id)             \
{                                                   \
    if (!TestingTheFallback)                        \
    {                                               \
        TEST_FAIL_MESSAGE("Unexpected Exception!"); \
    }                                               \
    else                                            \
    {                                               \
        TestingTheFallbackId = id;                  \
        TestingTheFallback--;                       \
    }                                               \
}

// 多任务环境需要定义几个宏来创建此库
// 正确处理多个异常堆栈。您需要包括和必填项
// 定义，然后定义以下宏：
//    EXCEPTION_GET_ID-返回索引为0的当前任务的ID（numtasks-1）
//    EXCEPTION_NUM_ID-返回可能返回的任务数
//
// 例如，Quadros可能包括以下实现：
#ifndef TEST
#include "OSAPI.h"
#define CEXCEPTION_GET_ID    (KS_GetTaskID())
#define CEXCEPTION_NUM_ID    (NTASKS + 1)
#endif

//这可能是定义/包含一些错误ID的好地方：
#define ERROR_ID_EVERYTHING_IS_BROKEN  (0x88)
#define ERROR_ID_ONLY_THIS_IS_BROKEN   (0x77)

#endif // _EXCEPTION_H

