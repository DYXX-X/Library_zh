#ifndef _CEXCEPTION_H
#define _CEXCEPTION_H

#include <setjmp.h>

#ifdef __cplusplus
extern "C"
{
#endif


#define CEXCEPTION_VERSION_MAJOR    1
#define CEXCEPTION_VERSION_MINOR    3
#define CEXCEPTION_VERSION_BUILD    2
#define CEXCEPTION_VERSION          ((CEXCEPTION_VERSION_MAJOR << 16) | (CEXCEPTION_VERSION_MINOR << 8) | CEXCEPTION_VERSION_BUILD)

//要使用CException，您有许多选项：
//1.只需包含它并使用默认值运行
//2.在命令行中定义以下任何符号以替代它们
//3.在CException之前包含头文件。h定义了其中任何一个
//4.创建异常。h，然后先定义EXCEPTION_USE_CONFIG_FILE

#ifdef CEXCEPTION_USE_CONFIG_FILE
#include "CExceptionConfig.h"
#endif

//这是在没有异常时要分配的值
#ifndef CEXCEPTION_NONE
#define CEXCEPTION_NONE      (0x5A5A5A5A)
#endif

//这是要跟踪的异常堆栈数（每个任务一个）
#ifndef CEXCEPTION_NUM_ID
#define CEXCEPTION_NUM_ID    (1) //默认情况下只有一个堆栈
#endif

//这是获取当前异常堆栈索引的方法（如果只有一个堆栈，则为0）
#ifndef CEXCEPTION_GET_ID
#define CEXCEPTION_GET_ID    (0) //始终使用第一个索引，因为反正只有一个索引
#endif

//用于存储异常值的类型。
#ifndef CEXCEPTION_T
#define CEXCEPTION_T         unsigned int
#endif

//当没有全局Catch时，这是可选的特殊处理程序
#ifndef CEXCEPTION_NO_CATCH_HANDLER
#define CEXCEPTION_NO_CATCH_HANDLER(id)
#endif

//这些钩子允许您将自定义代码注入到位置中，对于保存和恢复其他状态特别有用
#ifndef CEXCEPTION_HOOK_START_TRY
#define CEXCEPTION_HOOK_START_TRY
#endif
#ifndef CEXCEPTION_HOOK_HAPPY_TRY
#define CEXCEPTION_HOOK_HAPPY_TRY
#endif
#ifndef CEXCEPTION_HOOK_AFTER_TRY
#define CEXCEPTION_HOOK_AFTER_TRY
#endif
#ifndef CEXCEPTION_HOOK_START_CATCH
#define CEXCEPTION_HOOK_START_CATCH
#endif

//异常帧结构
typedef struct {
  jmp_buf* pFrame;
  CEXCEPTION_T volatile Exception;
} CEXCEPTION_FRAME_T;

//实际根帧存储（如果是单任务，则仅一个）
extern volatile CEXCEPTION_FRAME_T CExceptionFrames[];

//Try（请参见C文件了解解释）
#define Try                                                         \
    {                                                               \
        jmp_buf *PrevFrame, NewFrame;                               \
        unsigned int MY_ID = CEXCEPTION_GET_ID;                     \
        PrevFrame = CExceptionFrames[MY_ID].pFrame;                 \
        CExceptionFrames[MY_ID].pFrame = (jmp_buf*)(&NewFrame);     \
        CExceptionFrames[MY_ID].Exception = CEXCEPTION_NONE;        \
        CEXCEPTION_HOOK_START_TRY;                                  \
        if (setjmp(NewFrame) == 0) {                                \
            if (1)

//Catch（有关说明，请参阅C文件）
#define Catch(e)                                                    \
            else { }                                                \
            CExceptionFrames[MY_ID].Exception = CEXCEPTION_NONE;    \
            CEXCEPTION_HOOK_HAPPY_TRY;                              \
        }                                                           \
        else                                                        \
        {                                                           \
            e = CExceptionFrames[MY_ID].Exception;                  \
            (void)e;                                                \
            CEXCEPTION_HOOK_START_CATCH;                            \
        }                                                           \
        CExceptionFrames[MY_ID].pFrame = PrevFrame;                 \
        CEXCEPTION_HOOK_AFTER_TRY;                                  \
    }                                                               \
    if (CExceptionFrames[CEXCEPTION_GET_ID].Exception != CEXCEPTION_NONE)

//抛出错误
void Throw(CEXCEPTION_T ExceptionID);

//只需退出Try块并跳过Catch。
#define ExitTry() Throw(CEXCEPTION_NONE)

#ifdef __cplusplus
}   // 外部“C”
#endif


#endif // _CEXCEPTION_H

