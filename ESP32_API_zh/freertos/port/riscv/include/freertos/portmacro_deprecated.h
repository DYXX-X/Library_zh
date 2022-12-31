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
 * @brief 用于初始化自旋锁的已弃用的占位符函数
 *
 * 目前什么都不做。
 *
 * @deprecated 此函数已弃用。如果在多核上，请改用spinlock_initialize（）
 * @param[in] mux 旋转锁
 */
static inline void __attribute__((deprecated)) __attribute__((always_inline)) vPortCPUInitializeMutex(portMUX_TYPE *mux)
{
    (void)mux;
}

/**
 * @brief 用于获取自旋锁的不推荐放置保持器函数
 *
 * 目前什么都不做。
 *
 * @deprecated 此函数已弃用。如果在多核上，请改用spinlock_acquire（）
 * @param[in] mux 旋转锁
 */
static inline void __attribute__((deprecated)) __attribute__((always_inline)) vPortCPUAcquireMutex(portMUX_TYPE *mux)
{
    (void)mux;
}

/**
 * @brief 不推荐使用占位符函数获取自旋锁，但具有指定的超时
 *
 * 当前仅返回true
 *
 * @deprecated 此函数已弃用。如果在多核上，请改用spinlock_acquire（）
 * @note 由于app_trace_util.c中的用法，没有弃用的属性
 * @param[in] mux 旋转锁
 * @param[in] timeout CPU周期数超时
 * @return true始终返回true
 */
static inline bool __attribute__((always_inline))  vPortCPUAcquireMutexTimeout(portMUX_TYPE *mux, int timeout_cycles)
{
    (void)mux;
    (void)timeout_cycles;
    return true;
}

/**
 * @brief 不推荐的放置保持器功能，用于释放旋转锁
 *
 * 目前什么都不做。
 *
 * @deprecated 此函数已弃用。如果在多核上，请改用spinlock_release（）
 * @note 由于app_trace_util.c中的用法，没有弃用的属性
 * @param[in] mux 旋转锁
 */
static inline void __attribute__((always_inline)) vPortCPUReleaseMutex(portMUX_TYPE *mux)
{
    (void)mux;
}

