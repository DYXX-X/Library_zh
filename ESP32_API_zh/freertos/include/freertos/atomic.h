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

/**
 * @file 原子.h
 * @brief FreeRTOS原子操作支持。
 *
 * 该文件通过全局禁用中断来实现原子功能。可以在每个编译器目录下提供具有特定于体系结构的原子指令的实现。
 */

#ifndef ATOMIC_H
#define ATOMIC_H

#ifndef INC_FREERTOS_H
    #error "include FreeRTOS.h must appear in source files before include atomic.h"
#endif

/* 标准包括。*/
#include <stdint.h>

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* *INDENT-ON* */

/*
 * 特定于端口的定义——进入/退出关键部分。请参阅模板--./lib/FreeRTOS/portable/Compoiler/Arch/portmacro.h
 *
 * 对ATOMIC_EXIT_CRITICAL（）的每次调用都必须与ATOMIC_ENTER_CRITICAL（。
 *
 */
#if defined( portSET_INTERRUPT_MASK_FROM_ISR )

/* 此端口支持嵌套中断方案。*/
    #define ATOMIC_ENTER_CRITICAL() \
    UBaseType_t uxCriticalSectionType = portSET_INTERRUPT_MASK_FROM_ISR()

    #define ATOMIC_EXIT_CRITICAL() \
    portCLEAR_INTERRUPT_MASK_FROM_ISR( uxCriticalSectionType )

#else

/* 此端口不支持嵌套中断方案。*/
    #define ATOMIC_ENTER_CRITICAL()    portENTER_CRITICAL()
    #define ATOMIC_EXIT_CRITICAL()     portEXIT_CRITICAL()

#endif /* 端口SET_INTERRUPT_MASK_FROM_ISR（）*/

/*
 * 特定于端口的定义——“总是内联”。内联是特定于编译器的，根据您的优化级别，可能不总是内联的。此外，内联被认为是原子的性能优化。因此，如果portmacro未提供portFORCE_INLINE。h、 而不是由此产生的错误，只需定义它。
 */
#ifndef portFORCE_INLINE
    #define portFORCE_INLINE
#endif

#define ATOMIC_COMPARE_AND_SWAP_SUCCESS    0x1U     /**<比较和交换成功，已交换。*/
#define ATOMIC_COMPARE_AND_SWAP_FAILURE    0x0U     /**<比较和交换失败，未交换。*/

/*-----------------------------交换和CAS------------------------------*/

/**
 * 原子比较和交换
 *
 * @brief 对指定值执行原子比较和交换操作。
 *
 * @param[in, out] pulDestination指向要加载和检查值的内存位置的指针。
 * @param[in] ulExchange         如果条件满足，则将此值写入内存。
 * @param[in] ulComparand        交换条件。
 *
 * @return 值为1或0的无符号整数。1表示已交换，0表示未交换。
 *
 * @note 如果上一个pulDestination值等于ulComparand，则此函数仅将*pulDestination与ulExchange交换。
 */
static portFORCE_INLINE uint32_t Atomic_CompareAndSwap_u32( uint32_t volatile * pulDestination,
                                                            uint32_t ulExchange,
                                                            uint32_t ulComparand )
{
    uint32_t ulReturnValue;

    ATOMIC_ENTER_CRITICAL();
    {
        if( *pulDestination == ulComparand )
        {
            *pulDestination = ulExchange;
            ulReturnValue = ATOMIC_COMPARE_AND_SWAP_SUCCESS;
        }
        else
        {
            ulReturnValue = ATOMIC_COMPARE_AND_SWAP_FAILURE;
        }
    }
    ATOMIC_EXIT_CRITICAL();

    return ulReturnValue;
}
/*-----------------------------------------------------------*/

/**
 * 原子交换（指针）
 *
 * @brief 原子地将*ppvDestination指向的地址设置为pvExchange的值。
 *
 * @param[in, out] ppvDestination指向要从中加载指针值并将其写回的内存位置的指针。
 * @param[in] pvExchange           要写入*ppvDestination的指针值。
 *
 * @return *ppvDestination的初始值。
 */
static portFORCE_INLINE void * Atomic_SwapPointers_p32( void * volatile * ppvDestination,
                                                        void * pvExchange )
{
    void * pReturnValue;

    ATOMIC_ENTER_CRITICAL();
    {
        pReturnValue = *ppvDestination;
        *ppvDestination = pvExchange;
    }
    ATOMIC_EXIT_CRITICAL();

    return pReturnValue;
}
/*-----------------------------------------------------------*/

/**
 * 原子比较和交换（指针）
 *
 * @brief 对指定的指针值执行原子比较和交换操作。
 *
 * @param[in, out] ppvDestination指向要从中加载和检查指针值的内存位置的指针。
 * @param[in] pvExchange           如果条件满足，则将此值写入内存。
 * @param[in] pvComparand          交换条件。
 *
 * @return 值为1或0的无符号整数。1表示已交换，0表示未交换。
 *
 * @note 如果先前的ppvDestination值等于pvComparand，则此函数仅将*ppvDestination与pvExchange交换。
 */
static portFORCE_INLINE uint32_t Atomic_CompareAndSwapPointers_p32( void * volatile * ppvDestination,
                                                                    void * pvExchange,
                                                                    void * pvComparand )
{
    uint32_t ulReturnValue = ATOMIC_COMPARE_AND_SWAP_FAILURE;

    ATOMIC_ENTER_CRITICAL();
    {
        if( *ppvDestination == pvComparand )
        {
            *ppvDestination = pvExchange;
            ulReturnValue = ATOMIC_COMPARE_AND_SWAP_SUCCESS;
        }
    }
    ATOMIC_EXIT_CRITICAL();

    return ulReturnValue;
}


/*-----------------------------算术------------------------------*/

/**
 * 原子添加
 *
 * @brief 原子地将计数添加到指定指针指向的值。
 *
 * @param[in,out] pulAddend  指向要从中加载和写回值的内存位置的指针。
 * @param[in] ulCount      要添加到*pulAddend的值。
 *
 * @return 上一个*pulAddend值。
 */
static portFORCE_INLINE uint32_t Atomic_Add_u32( uint32_t volatile * pulAddend,
                                                 uint32_t ulCount )
{
    uint32_t ulCurrent;

    ATOMIC_ENTER_CRITICAL();
    {
        ulCurrent = *pulAddend;
        *pulAddend += ulCount;
    }
    ATOMIC_EXIT_CRITICAL();

    return ulCurrent;
}
/*-----------------------------------------------------------*/

/**
 * 原子减法
 *
 * @brief 从指定指针指向的值中原子地减去计数。
 *
 * @param[in,out] pulAddend  指向要从中加载和写回值的内存位置的指针。
 * @param[in] ulCount      要从*pulAddend中减去的值。
 *
 * @return 上一个*pulAddend值。
 */
static portFORCE_INLINE uint32_t Atomic_Subtract_u32( uint32_t volatile * pulAddend,
                                                      uint32_t ulCount )
{
    uint32_t ulCurrent;

    ATOMIC_ENTER_CRITICAL();
    {
        ulCurrent = *pulAddend;
        *pulAddend -= ulCount;
    }
    ATOMIC_EXIT_CRITICAL();

    return ulCurrent;
}
/*-----------------------------------------------------------*/

/**
 * 原子增量
 *
 * @brief 原子递增指定指针指向的值。
 *
 * @param[in,out] pulAddend  指向要从中加载和写回值的内存位置的指针。
 *
 * @return *增量前的pulAddend值。
 */
static portFORCE_INLINE uint32_t Atomic_Increment_u32( uint32_t volatile * pulAddend )
{
    uint32_t ulCurrent;

    ATOMIC_ENTER_CRITICAL();
    {
        ulCurrent = *pulAddend;
        *pulAddend += 1;
    }
    ATOMIC_EXIT_CRITICAL();

    return ulCurrent;
}
/*-----------------------------------------------------------*/

/**
 * 原子减量
 *
 * @brief 原子递减指定指针指向的值
 *
 * @param[in,out] pulAddend  指向要从中加载和写回值的内存位置的指针。
 *
 * @return *减量前的pulAddend值。
 */
static portFORCE_INLINE uint32_t Atomic_Decrement_u32( uint32_t volatile * pulAddend )
{
    uint32_t ulCurrent;

    ATOMIC_ENTER_CRITICAL();
    {
        ulCurrent = *pulAddend;
        *pulAddend -= 1;
    }
    ATOMIC_EXIT_CRITICAL();

    return ulCurrent;
}

/*-----------------------------按位逻辑------------------------------*/

/**
 * 原子OR
 *
 * @brief 对指定值执行原子OR运算。
 *
 * @param [in, out]pulDestination指向要从中加载和写回值的内存位置的指针。
 * @param [in] ulValue值与*pulDestination进行“或”运算。
 *
 * @return *pulDestination的原始值。
 */
static portFORCE_INLINE uint32_t Atomic_OR_u32( uint32_t volatile * pulDestination,
                                                uint32_t ulValue )
{
    uint32_t ulCurrent;

    ATOMIC_ENTER_CRITICAL();
    {
        ulCurrent = *pulDestination;
        *pulDestination |= ulValue;
    }
    ATOMIC_EXIT_CRITICAL();

    return ulCurrent;
}
/*-----------------------------------------------------------*/

/**
 * 原子AND
 *
 * @brief 对指定值执行原子AND运算。
 *
 * @param [in, out]pulDestination指向要从中加载和写回值的内存位置的指针。
 * @param [in] ulValue要与*pulDestination进行AND运算的值。
 *
 * @return *pulDestination的原始值。
 */
static portFORCE_INLINE uint32_t Atomic_AND_u32( uint32_t volatile * pulDestination,
                                                 uint32_t ulValue )
{
    uint32_t ulCurrent;

    ATOMIC_ENTER_CRITICAL();
    {
        ulCurrent = *pulDestination;
        *pulDestination &= ulValue;
    }
    ATOMIC_EXIT_CRITICAL();

    return ulCurrent;
}
/*-----------------------------------------------------------*/

/**
 * 原子NAND
 *
 * @brief 对指定值执行原子NAND操作。
 *
 * @param [in, out]pulDestination指向要从中加载和写回值的内存位置的指针。
 * @param [in] ulValue值为NANDed，带有*pulDestination。
 *
 * @return *pulDestination的原始值。
 */
static portFORCE_INLINE uint32_t Atomic_NAND_u32( uint32_t volatile * pulDestination,
                                                  uint32_t ulValue )
{
    uint32_t ulCurrent;

    ATOMIC_ENTER_CRITICAL();
    {
        ulCurrent = *pulDestination;
        *pulDestination = ~( ulCurrent & ulValue );
    }
    ATOMIC_EXIT_CRITICAL();

    return ulCurrent;
}
/*-----------------------------------------------------------*/

/**
 * 原子异或
 *
 * @brief 对指定值执行原子XOR运算。
 *
 * @param [in, out]pulDestination指向要从中加载和写回值的内存位置的指针。
 * @param [in] ulValue值与*pulDestination进行异或。
 *
 * @return *pulDestination的原始值。
 */
static portFORCE_INLINE uint32_t Atomic_XOR_u32( uint32_t volatile * pulDestination,
                                                 uint32_t ulValue )
{
    uint32_t ulCurrent;

    ATOMIC_ENTER_CRITICAL();
    {
        ulCurrent = *pulDestination;
        *pulDestination ^= ulValue;
    }
    ATOMIC_EXIT_CRITICAL();

    return ulCurrent;
}

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* ATOMIC_H */

