/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

/* 原子操作*/

/*
 * 版权所有（c）1997-2015，Wind River Systems，Inc。
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef __ATOMIC_H__
#define __ATOMIC_H__

#ifdef __cplusplus
extern "C"
{
#endif

typedef int atomic_t;
typedef atomic_t atomic_val_t;

/**
 * @defgroup atomic_apis原子服务API
 * @ingroup 内核_ pis@{
 */

/**
 * @brief 原子比较和设置。
 *
 * 此例程执行原子比较并设置@a目标。如果当前
 * value of @a target等于@old_value，@target设置为@new_value。
 * If the current value of @a target不等于@aold_value，@target保持不变。
 *
 * @param target 原子变量的地址。
 * @param old_value 要比较的原始值。
 * @param new_value 要存储的新值。
 * @return 如果写入了@new_value，则为1，否则为0。
 */
static inline int atomic_cas(atomic_t *target, atomic_val_t old_value,
        atomic_val_t new_value)
{
    return __atomic_compare_exchange_n(target, &old_value, new_value,
            0, __ATOMIC_SEQ_CST,
            __ATOMIC_SEQ_CST);
}

/**
 *
 * @brief 原子添加。
 *
 * 此例程对@atarget执行原子加法。
 *
 * @param target 原子变量的地址。
 * @param value 要添加的值。
 *
 * @return @a target的上一个值。
 */
static inline atomic_val_t atomic_add(atomic_t *target, atomic_val_t value)
{
    return __atomic_fetch_add(target, value, __ATOMIC_SEQ_CST);
}

/**
 *
 * @brief 原子减法。
 *
 * 此例程对@atarget执行原子减法。
 *
 * @param target 原子变量的地址。
 * @param value 要减去的值。
 *
 * @return @a target的上一个值。
 */

static inline atomic_val_t atomic_sub(atomic_t *target, atomic_val_t value)
{
    return __atomic_fetch_sub(target, value, __ATOMIC_SEQ_CST);
}

/**
 *
 * @brief 原子增量。
 *
 * 此例程对@a目标执行原子增量1。
 *
 * @param target 原子变量的地址。
 *
 * @return @a target的上一个值。
 */

static inline atomic_val_t atomic_inc(atomic_t *target)
{
    return atomic_add(target, 1);
}

/**
 *
 * @brief 原子减量。
 *
 * 此例程对@目标执行原子减量1。
 *
 * @param target 原子变量的地址。
 *
 * @return @a target的上一个值。
 */

static inline atomic_val_t atomic_dec(atomic_t *target)
{
    return atomic_sub(target, 1);
}

/**
 *
 * @brief 原子获取。
 *
 * 此例程对@atarget执行原子读取。
 *
 * @param target 原子变量的地址。
 *
 * @return @a目标的值。
 */

static inline atomic_val_t atomic_get(const atomic_t *target)
{
    return __atomic_load_n(target, __ATOMIC_SEQ_CST);
}

/**
 *
 * @brief 原子获取和设置。
 *
 * This routine atomically sets @a target设置为@a值，并返回@a target的上一个值。
 *
 * @param target 原子变量的地址。
 * @param value 要写入@atarget的值。
 *
 * @return @a target的上一个值。
 */

static inline atomic_val_t atomic_set(atomic_t *target, atomic_val_t value)
{
    /* 正如Intel所描述的，这种内置操作不是传统的测试和设置操作，而是原子交换操作。它将值写入ptr，并返回ptr之前的内容。
     */
    return __atomic_exchange_n(target, value, __ATOMIC_SEQ_CST);
}

/**
 *
 * @brief 原子清晰。
 *
 * This routine atomically sets @a 目标设置为零并返回其上一个值。（因此，它相当于atomic_set（target，0）。）
 *
 * @param target 原子变量的地址。
 *
 * @return @a target的上一个值。
 */

static inline atomic_val_t atomic_clear(atomic_t *target)
{
    return atomic_set(target, 0);
}

/**
 *
 * @brief 原子位包含OR。
 *
 * This routine atomically sets @a 目标为
 * @a target和@a值。
 *
 * @param target 原子变量的地址。
 * @param value 值为OR。
 *
 * @return @a target的上一个值。
 */

static inline atomic_val_t atomic_or(atomic_t *target, atomic_val_t value)
{
    return __atomic_fetch_or(target, value, __ATOMIC_SEQ_CST);
}

/**
 *
 * @brief 原子位异或（XOR）。
 *
 * This routine atomically sets @a 目标为的位异或（XOR）
 * @a target和@a值。
 *
 * @param target 原子变量的地址。
 * @param value 要XOR的值
 *
 * @return @a target的上一个值。
 */

static inline atomic_val_t atomic_xor(atomic_t *target, atomic_val_t value)
{
    return __atomic_fetch_xor(target, value, __ATOMIC_SEQ_CST);
}

/**
 *
 * @brief 原子位AND。
 *
 * This routine atomically sets @a target到@a target的位AND
 * and @a 价值
 *
 * @param target 原子变量的地址。
 * @param value 值设置为AND。
 *
 * @return @a target的上一个值。
 */

static inline atomic_val_t atomic_and(atomic_t *target, atomic_val_t value)
{
    return __atomic_fetch_and(target, value, __ATOMIC_SEQ_CST);
}

/**
 *
 * @brief 原子位NAND。
 *
 * This routine atomically sets @a target到@a target的位NAND
 * and @a 价值（此操作相当于target=~（target&value）。）
 *
 * @param target 原子变量的地址。
 * @param value NAND值。
 *
 * @return @a target的上一个值。
 */

static inline atomic_val_t atomic_nand(atomic_t *target, atomic_val_t value)
{
    return __atomic_fetch_nand(target, value, __ATOMIC_SEQ_CST);
}

    /**
     * @brief 初始化原子变量。
     *
     * 此宏可用于初始化原子变量。例如
     * @code atomic_tmy_var=atomic_INIT（75）@结束代码
     *
     * @param i 要分配给原子变量的值。
     */
#define ATOMIC_INIT(i) (i)

    /**
     * @cond INTERNAL_HIDDEN
     */

#define ATOMIC_BITS (sizeof(atomic_val_t) * 8)
#define ATOMIC_MASK(bit) (1 << ((bit) & (ATOMIC_BITS - 1)))
#define ATOMIC_ELEM(addr, bit) ((addr) + ((bit) / ATOMIC_BITS))

    /**
     * INTERNAL_HIDDEN@结束秒
     */

    /**
     * @brief 定义原子变量数组。
     *
     * 此宏定义一个原子变量数组，其中至少包含
     * @a num_bits位。
     *
     * @note 如果从文件范围使用，数组的位将初始化为零；如果在函数中使用，则这些位将保持未初始化状态。
     *
     * @param name 原子变量数组的名称。
     * @param num_bits 需要的位数。
     */
#define ATOMIC_DEFINE(name, num_bits) \
	atomic_t name[1 + ((num_bits) - 1) / ATOMIC_BITS]

    /**
     * @brief 原子测试一点。
     *
     * This routine tests whether bit number @a 是否设置了@目标的位。目标可以是单个原子变量或它们的数组。
     *
     * @param target 原子变量或数组的地址。
     * @param bit 位数（从0开始）。
     *
     * @return 如果设置了位，则为1，如果未设置，则为0。
     */
    static inline int
    atomic_test_bit(const atomic_t *target, int bit)
    {
        atomic_val_t val = atomic_get(ATOMIC_ELEM(target, bit));

        return (1 & (val >> (bit & (ATOMIC_BITS - 1))));
    }

    /**
     * @brief 原子测试并清除一点。
     *
     * Atomically clear bit number @a 一位@target并返回其旧值。目标可以是单个原子变量或它们的数组。
     *
     * @param target 原子变量或数组的地址。
     * @param bit 位数（从0开始）。
     *
     * @return 如果设置了位，则为1，如果未设置，则为0。
     */
    static inline int
    atomic_test_and_clear_bit(atomic_t *target, int bit)
    {
        atomic_val_t mask = ATOMIC_MASK(bit);
        atomic_val_t old;

        old = atomic_and(ATOMIC_ELEM(target, bit), ~mask);

        return (old & mask) != 0;
    }

    /**
     * @brief 原子设置一点。
     *
     * Atomically set bit number @a 一位@target并返回其旧值。目标可以是单个原子变量或它们的数组。
     *
     * @param target 原子变量或数组的地址。
     * @param bit 位数（从0开始）。
     *
     * @return 如果设置了位，则为1，如果未设置，则为0。
     */
    static inline int
    atomic_test_and_set_bit(atomic_t *target, int bit)
    {
        atomic_val_t mask = ATOMIC_MASK(bit);
        atomic_val_t old;

        old = atomic_or(ATOMIC_ELEM(target, bit), mask);

        return (old & mask) != 0;
    }

    /**
     * @brief 原子清晰一点。
     *
     * Atomically clear bit number @a 有点像目标。目标可以是单个原子变量或它们的数组。
     *
     * @param target 原子变量或数组的地址。
     * @param bit 位数（从0开始）。
     *
     * @return N/A
     */
    static inline void
    atomic_clear_bit(atomic_t *target, int bit)
    {
        atomic_val_t mask = ATOMIC_MASK(bit);

        atomic_and(ATOMIC_ELEM(target, bit), ~mask);
    }

    /**
     * @brief 原子设置一点。
     *
     * Atomically set bit number @a 有点像目标。目标可以是单个原子变量或它们的数组。
     *
     * @param target 原子变量或数组的地址。
     * @param bit 位数（从0开始）。
     *
     * @return N/A
     */
    static inline void
    atomic_set_bit(atomic_t *target, int bit)
    {
        atomic_val_t mask = ATOMIC_MASK(bit);

        atomic_or(ATOMIC_ELEM(target, bit), mask);
    }

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __ATOMIC_H__ */

