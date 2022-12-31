/* 原子操作*/

/*
 * SPDX文件版权文本：1997-2015 Wind River Systems，Inc。
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _BLE_MESH_ATOMIC_H_
#define _BLE_MESH_ATOMIC_H_

#include "mesh_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef bt_mesh_atomic_t bt_mesh_atomic_val_t;

/**
 * @defgroup atomic_apis原子服务API
 * @ingroup 内核_ pis@{
 */

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
#ifdef CONFIG_ATOMIC_OPERATIONS_BUILTIN
static inline bt_mesh_atomic_val_t bt_mesh_atomic_inc(bt_mesh_atomic_t *target)
{
    return bt_mesh_atomic_add(target, 1);
}
#else
extern bt_mesh_atomic_val_t bt_mesh_atomic_inc(bt_mesh_atomic_t *target);
#endif

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
#ifdef CONFIG_ATOMIC_OPERATIONS_BUILTIN
static inline bt_mesh_atomic_val_t bt_mesh_atomic_dec(bt_mesh_atomic_t *target)
{
    return bt_mesh_atomic_sub(target, 1);
}
#else
extern bt_mesh_atomic_val_t bt_mesh_atomic_dec(bt_mesh_atomic_t *target);
#endif

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
#ifdef CONFIG_ATOMIC_OPERATIONS_BUILTIN
static inline bt_mesh_atomic_val_t bt_mesh_atomic_get(const bt_mesh_atomic_t *target)
{
    return __atomic_load_n(target, __ATOMIC_SEQ_CST);
}
#else
extern bt_mesh_atomic_val_t bt_mesh_atomic_get(const bt_mesh_atomic_t *target);
#endif

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
#ifdef CONFIG_ATOMIC_OPERATIONS_BUILTIN
static inline bt_mesh_atomic_val_t bt_mesh_atomic_set(bt_mesh_atomic_t *target, bt_mesh_atomic_val_t value)
{
    /* 正如Intel所描述的，这种内置操作不是传统的测试和设置操作，而是原子交换操作。它将值写入ptr，并返回ptr之前的内容。
     */
    return __atomic_exchange_n(target, value, __ATOMIC_SEQ_CST);
}
#else
extern bt_mesh_atomic_val_t bt_mesh_atomic_set(bt_mesh_atomic_t *target, bt_mesh_atomic_val_t value);
#endif

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
#ifdef CONFIG_ATOMIC_OPERATIONS_BUILTIN
static inline bt_mesh_atomic_val_t bt_mesh_atomic_or(bt_mesh_atomic_t *target, bt_mesh_atomic_val_t value)
{
    return __atomic_fetch_or(target, value, __ATOMIC_SEQ_CST);
}
#else
extern bt_mesh_atomic_val_t bt_mesh_atomic_or(bt_mesh_atomic_t *target, bt_mesh_atomic_val_t value);
#endif

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
#ifdef CONFIG_ATOMIC_OPERATIONS_BUILTIN
static inline bt_mesh_atomic_val_t bt_mesh_atomic_and(bt_mesh_atomic_t *target, bt_mesh_atomic_val_t value)
{
    return __atomic_fetch_and(target, value, __ATOMIC_SEQ_CST);
}
#else
extern bt_mesh_atomic_val_t bt_mesh_atomic_and(bt_mesh_atomic_t *target, bt_mesh_atomic_val_t value);
#endif

/**
 * @cond INTERNAL_HIDDEN
 */

#define BLE_MESH_ATOMIC_BITS            (sizeof(bt_mesh_atomic_val_t) * 8)
#define BLE_MESH_ATOMIC_MASK(bit)       (1 << ((bit) & (BLE_MESH_ATOMIC_BITS - 1)))
#define BLE_MESH_ATOMIC_ELEM(addr, bit) ((addr) + ((bit) / BLE_MESH_ATOMIC_BITS))

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
#define BLE_MESH_ATOMIC_DEFINE(name, num_bits) \
        bt_mesh_atomic_t name[1 + ((num_bits) - 1) / BLE_MESH_ATOMIC_BITS]

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
static inline int bt_mesh_atomic_test_bit(const bt_mesh_atomic_t *target, int bit)
{
    bt_mesh_atomic_val_t val = bt_mesh_atomic_get(BLE_MESH_ATOMIC_ELEM(target, bit));

    return (1 & (val >> (bit & (BLE_MESH_ATOMIC_BITS - 1))));
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
static inline int bt_mesh_atomic_test_and_clear_bit(bt_mesh_atomic_t *target, int bit)
{
    bt_mesh_atomic_val_t mask = BLE_MESH_ATOMIC_MASK(bit);
    bt_mesh_atomic_val_t old;

    old = bt_mesh_atomic_and(BLE_MESH_ATOMIC_ELEM(target, bit), ~mask);

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
static inline int bt_mesh_atomic_test_and_set_bit(bt_mesh_atomic_t *target, int bit)
{
    bt_mesh_atomic_val_t mask = BLE_MESH_ATOMIC_MASK(bit);
    bt_mesh_atomic_val_t old;

    old = bt_mesh_atomic_or(BLE_MESH_ATOMIC_ELEM(target, bit), mask);

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
static inline void bt_mesh_atomic_clear_bit(bt_mesh_atomic_t *target, int bit)
{
    bt_mesh_atomic_val_t mask = BLE_MESH_ATOMIC_MASK(bit);

    (void)bt_mesh_atomic_and(BLE_MESH_ATOMIC_ELEM(target, bit), ~mask);
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
static inline void bt_mesh_atomic_set_bit(bt_mesh_atomic_t *target, int bit)
{
    bt_mesh_atomic_val_t mask = BLE_MESH_ATOMIC_MASK(bit);

    (void)bt_mesh_atomic_or(BLE_MESH_ATOMIC_ELEM(target, bit), mask);
}

/**
 * @brief 原子地将位设置为给定值。
 *
 * Atomically set bit number @a 目标值可以是单个原子变量或它们的数组。
 *
 * @param target 原子变量或数组的地址。
 * @param bit 位数（从0开始）。
 * @param val 1为true，0为false。
 *
 * @return N/A
 */
static inline void bt_mesh_atomic_set_bit_to(bt_mesh_atomic_t *target, int bit, bool val)
{
    bt_mesh_atomic_val_t mask = BLE_MESH_ATOMIC_MASK(bit);

    if (val) {
        (void)bt_mesh_atomic_or(BLE_MESH_ATOMIC_ELEM(target, bit), mask);
    } else {
        (void)bt_mesh_atomic_and(BLE_MESH_ATOMIC_ELEM(target, bit), ~mask);
    }
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* _BLE_MESH_ATOMIC_H_ */

