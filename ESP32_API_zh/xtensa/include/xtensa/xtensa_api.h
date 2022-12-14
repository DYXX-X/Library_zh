/*******************************************************************************
版权所有（c）2006-2015 Cadence Design Systems Inc。

特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地使用本软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或出售本软件副本的权利，并允许向其提供本软件的人员这样做，符合以下条件：

上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OFMERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANYCLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THESOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
******************************************************************************/

/******************************************************************************
  用于RTOS端口的Xtensa特定API。
******************************************************************************/

#ifndef __XTENSA_API_H__
#define __XTENSA_API_H__

#include <stdbool.h>
#include <xtensa/hal.h>
#include "xtensa_context.h"


/* C可调用中断处理程序函数的Typedef*/
typedef void (*xt_handler)(void *);

/* C可调用异常处理程序函数的Typedef*/
typedef void (*xt_exc_handler)(XtExcFrame *);


/*
-------------------------------------------------------------------------------调用此函数为指定的异常设置处理程序。处理程序将安装在调用此函数的内核上。

    n-异常编号（类型）f-处理程序函数地址，NULL表示卸载处理程序。

  将向处理程序传递一个指向异常帧的指针，该异常帧是在导致异常的线程堆栈上创建的。

  如果处理程序返回，将恢复线程上下文，并重试出错的指令。异常帧中由处理程序修改的任何值都将作为上下文的一部分还原。有关异常帧结构的详细信息，请参阅extensa_context.h。
-------------------------------------------------------------------------------
*/
extern xt_exc_handler xt_set_exception_handler(int n, xt_exc_handler f);


/*
-------------------------------------------------------------------------------调用此函数为指定的中断设置处理程序。处理程序将安装在调用此函数的内核上。

    n-中断编号。f-处理程序函数地址，NULL表示卸载处理程序。arg-要传递给处理程序的参数。
-------------------------------------------------------------------------------
*/
extern xt_handler xt_set_interrupt_handler(int n, xt_handler f, void * arg);


/*
-------------------------------------------------------------------------------调用此函数以在运行此代码的内核上启用指定的中断。

    mask—要启用的中断的位掩码。
-------------------------------------------------------------------------------
*/
extern void xt_ints_on(unsigned int mask);


/*
-------------------------------------------------------------------------------调用此函数以禁用运行此代码的内核上的指定中断。

    mask—要禁用的中断位掩码。
-------------------------------------------------------------------------------
*/
extern void xt_ints_off(unsigned int mask);


/*
-------------------------------------------------------------------------------调用此函数以设置指定的中断。
-------------------------------------------------------------------------------
*/
static inline void xt_set_intset(unsigned int arg)
{
    xthal_set_intset(arg);
}


/*
-------------------------------------------------------------------------------调用此函数以清除指定的（s/w或边缘触发的）中断。
-------------------------------------------------------------------------------
*/
static inline void xt_set_intclear(unsigned int arg)
{
    xthal_set_intclear(arg);
}

/*
-------------------------------------------------------------------------------调用此函数以获取指定中断的处理程序参数。

    n-中断编号。
-------------------------------------------------------------------------------
*/
extern void * xt_get_interrupt_handler_arg(int n);

/*
-------------------------------------------------------------------------------调用此函数以检查指定的中断是否可以自由使用。

    intr—中断编号。cpu-cpu编号。
-------------------------------------------------------------------------------
*/
bool xt_int_has_handler(int intr, int cpu);

#endif /* __XTENSA_API_H__ */

