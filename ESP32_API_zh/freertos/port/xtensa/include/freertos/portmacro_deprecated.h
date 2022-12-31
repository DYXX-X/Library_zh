/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/* ----------------------------------------------------弃用------------------------------------------------------
 * -应该在v5.0中弃用的宏或函数，然后在下一个主要版本中删除
 * -保持不变，以免造成重大变化
 * -在portmacro.h末尾包含此标头
 * ------------------------------------------------------------------------------------------------------------------ */

/**
 * @brief 以嵌套方式禁用中断
 *
 * 执行与portSET_INTERRUPT_MASK_FROM_ISR（）完全相同的操作
 *
 * @deprecated 此函数已弃用。改为调用端口SET_INTERRUPT_MASK_FROM_ISR（）
 */
static inline __attribute__((deprecated)) UBaseType_t portENTER_CRITICAL_NESTED(void) {
    return portSET_INTERRUPT_MASK_FROM_ISR();
}

/**
 * @brief 以嵌套方式重新启用中断
 *
 * 执行与portCLEAR_INTERRUPT_MASK_FROM_ISR（）完全相同的操作
 *
 * @deprecated 此函数已弃用。改为调用端口CLEAR_INTERRUPT_MASK_FROM_ISR（）
 */
static inline void __attribute__((deprecated)) portEXIT_CRITICAL_NESTED(UBaseType_t prev_level)
{
    portCLEAR_INTERRUPT_MASK_FROM_ISR(prev_level);
}

/* ----------------------旋转锁---------------------*/

/**
 * @brief 初始化自旋锁
 *
 * 执行与spinlock_initialize（）完全相同的操作；
 *
 * @deprecated 此函数已弃用。改为调用spinlock_initialize（）
 * @param[in] mux 旋转锁
 */
static inline void __attribute__((deprecated)) __attribute__((always_inline)) vPortCPUInitializeMutex(portMUX_TYPE *mux)
{
    spinlock_initialize(mux);
}

/**
 * @brief 获取自旋锁
 *
 * 执行与无限超时的spinlock_acquire（）完全相同的操作
 *
 * @deprecated 此函数已弃用。改为调用spinlock_acquire（）
 * @param[in] mux 旋转锁
 */
static inline void __attribute__((deprecated)) __attribute__((always_inline)) vPortCPUAcquireMutex(portMUX_TYPE *mux)
{
    spinlock_acquire(mux, portMUX_NO_TIMEOUT);
}

/**
 * @brief 获取自旋锁
 *
 * 使用指定的超时执行与spinlock_acquire（）完全相同的操作
 *
 * @deprecated 此函数已弃用。改为调用spinlock_acquire（）
 * @note 由于app_trace_util.c中的用法，没有弃用的属性
 * @param[in] mux 旋转锁
 * @param timeout
 * @return 已获取true Spinlock
 * @return false超时
 */
static inline bool __attribute__((always_inline)) vPortCPUAcquireMutexTimeout(portMUX_TYPE *mux, int timeout)
{
    return (spinlock_acquire(mux, timeout));
}

/**
 * @brief 释放自旋锁
 *
 * 执行与spinlock_release（）完全相同的操作
 *
 * @deprecated 此函数已弃用。改为调用spinlock_release（）
 * @note 由于app_trace_util.c中的用法，没有弃用的属性
 * @param[in] mux 旋转锁
 */
static inline void __attribute__((always_inline)) vPortCPUReleaseMutex(portMUX_TYPE *mux)
{
    spinlock_release(mux);
}

