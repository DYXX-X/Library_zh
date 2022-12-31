/*
 * FreeRTOS内核V10.4.3版权所有（C）2020 Amazon。com，Inc.或其附属公司。保留所有权利。
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org https://github.com/FreeRTOS
 *
 */

#ifndef STACK_MACROS_H
#define STACK_MACROS_H

/*
 * 如果要交换的任务的堆栈当前溢出，或者看起来过去可能溢出，请调用堆栈溢出挂钩函数。
 *
 * 将configCHECK_FOR_STACK_OVERFLOW设置为1将导致宏仅检查当前堆栈状态-将当前堆栈顶部值与堆栈限制进行比较。将configCHECK_FOR_STACK_OVERFLOW设置为大于1还将导致检查最后几个堆栈字节，以确保创建任务时设置字节的值未被覆盖。注意，第二个测试不能保证溢出的堆栈始终被识别。
 */

/*-----------------------------------------------------------*/

#if( configCHECK_FOR_STACK_OVERFLOW == 0 )

    /* FreeRTO配置。h未设置为检查堆栈溢出。*/
    #define taskFIRST_CHECK_FOR_STACK_OVERFLOW()
    #define taskSECOND_CHECK_FOR_STACK_OVERFLOW()

#endif /* configCHECK_FOR_STACK_OVERFLOW==0*/
/*-----------------------------------------------------------*/

#if( configCHECK_FOR_STACK_OVERFLOW == 1 )

    /* FreeRTO配置。h仅设置为使用第一种溢出检查方法。*/
    #define taskSECOND_CHECK_FOR_STACK_OVERFLOW()

#endif
/*-----------------------------------------------------------*/

#if( ( configCHECK_FOR_STACK_OVERFLOW > 0 ) && ( portSTACK_GROWTH < 0 ) )

/* 仅检查当前堆栈状态。*/
    #define taskFIRST_CHECK_FOR_STACK_OVERFLOW()                                                        \
    {                                                                                                 \
        /* 当前保存的堆栈指针是否在堆栈限制内？*/                            \
        if( pxCurrentTCB[ xPortGetCoreID() ]->pxTopOfStack <= pxCurrentTCB[ xPortGetCoreID() ]->pxStack )                                       \
        {                                                                                             \
            vApplicationStackOverflowHook( ( TaskHandle_t ) pxCurrentTCB[ xPortGetCoreID() ], pxCurrentTCB[ xPortGetCoreID() ]->pcTaskName );   \
        }                                                                                             \
    }

#endif /* configCHECK_FOR_STACK_OVERFLOW>0*/
/*-----------------------------------------------------------*/

#if( ( configCHECK_FOR_STACK_OVERFLOW > 0 ) && ( portSTACK_GROWTH > 0 ) )

/* 仅检查当前堆栈状态。*/
    #define taskFIRST_CHECK_FOR_STACK_OVERFLOW()                                                        \
    {                                                                                                 \
                                                                                                      \
        /* 当前保存的堆栈指针是否在堆栈限制内？*/                            \
        if( pxCurrentTCB[ xPortGetCoreID() ]->pxTopOfStack >= pxCurrentTCB[ xPortGetCoreID() ]->pxEndOfStack )                                  \
        {                                                                                             \
            vApplicationStackOverflowHook( ( TaskHandle_t ) pxCurrentTCB[ xPortGetCoreID() ], pxCurrentTCB[ xPortGetCoreID() ]->pcTaskName );   \
        }                                                                                             \
    }

#endif /* configCHECK_FOR_STACK_OVERFLOW==1*/
/*-----------------------------------------------------------*/

#if ( ( configCHECK_FOR_STACK_OVERFLOW > 1 ) && ( portSTACK_GROWTH < 0 ) )

    #define taskSECOND_CHECK_FOR_STACK_OVERFLOW()                                                                                       \
    {                                                                                                 \
    static const uint8_t ucExpectedStackBytes[] = { tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE,     \
                                                    tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE,     \
                                                    tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE,     \
                                                    tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE,     \
                                                    tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE };   \
                                                                                                      \
                                                                                                                                        \
        /* 任务堆栈的末端是否已被重写？*/                                                               \
        if( memcmp( ( void * ) pxCurrentTCB[ xPortGetCoreID() ]->pxStack, ( void * ) ucExpectedStackBytes, sizeof( ucExpectedStackBytes ) ) != 0 )          \
        {                                                                                             \
            vApplicationStackOverflowHook( ( TaskHandle_t ) pxCurrentTCB[ xPortGetCoreID() ], pxCurrentTCB[ xPortGetCoreID() ]->pcTaskName );                                   \
        }                                                                                             \
    }

#endif /* #如果（configCHECK_FOR_STACK_OVERFLOW>1）*/
/*-----------------------------------------------------------*/

#if ( ( configCHECK_FOR_STACK_OVERFLOW > 1 ) && ( portSTACK_GROWTH > 0 ) )

    #define taskSECOND_CHECK_FOR_STACK_OVERFLOW()                                                                                       \
    {                                                                                                                                     \
        int8_t *pcEndOfStack = ( int8_t * ) pxCurrentTCB[ xPortGetCoreID() ]->pxEndOfStack;                                                                     \
        static const uint8_t ucExpectedStackBytes[] = { tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE,   \
                                                        tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE,   \
                                                        tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE,   \
                                                        tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE,   \
                                                        tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE }; \
                                                                                                                                          \
                                                                                                                                          \
        pcEndOfStack -= sizeof( ucExpectedStackBytes );                                                                                   \
                                                                                                                                          \
        /* 任务堆栈的末端是否已被重写？*/                                                                 \
        if( memcmp( ( void * ) pcEndOfStack, ( void * ) ucExpectedStackBytes, sizeof( ucExpectedStackBytes ) ) != 0 )                     \
        {                                                                                                                                 \
            vApplicationStackOverflowHook( ( TaskHandle_t ) pxCurrentTCB[ xPortGetCoreID() ], pxCurrentTCB[ xPortGetCoreID() ]->pcTaskName );                                   \
        }                                                                                                                                 \
    }

#endif /* #如果（configCHECK_FOR_STACK_OVERFLOW>1）*/

#endif /* STACK_MACROS_H */

