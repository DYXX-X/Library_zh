/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "sdkconfig.h"
#include "soc/cpu.h"
#include "hal/cpu_hal.h"
#include "soc/compare_set.h"

#if __XTENSA__
#include "xtensa/xtruntime.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_SPIRAM_WORKAROUND_NEED_VOLATILE_SPINLOCK
#define NEED_VOLATILE_MUX volatile
#else
#define NEED_VOLATILE_MUX
#endif

#define SPINLOCK_FREE          0xB33FFFFF
#define SPINLOCK_WAIT_FOREVER  (-1)
#define SPINLOCK_NO_WAIT        0
#define SPINLOCK_INITIALIZER   {.owner = SPINLOCK_FREE,.count = 0}
#define CORE_ID_REGVAL_XOR_SWAP (0xCDCD ^ 0xABAB)

typedef struct {
    NEED_VOLATILE_MUX uint32_t owner;
    NEED_VOLATILE_MUX uint32_t count;
}spinlock_t;

/**
 * @brief 将锁初始化为默认状态-解锁
 * @param lock -要初始化的spinlock对象
 */
static inline void __attribute__((always_inline)) spinlock_initialize(spinlock_t *lock)
{
    assert(lock);
#if !CONFIG_FREERTOS_UNICORE
    lock->owner = SPINLOCK_FREE;
    lock->count = 0;
#endif
}

/**
 * @brief 顶级旋转锁获取功能，旋转直到获得锁
 *
 * 该功能将：
 * -保存当前中断状态，然后禁用中断
 * -旋转直到获得锁定或超时
 * -恢复中断状态
 *
 * @note 自旋锁本身并不构成真正的关键部分（因为一旦获取自旋锁，该函数将重新启用中断）。对于关键部分，请使用操作系统提供的界面。
 * @param lock -目标自旋锁对象
 * @param timeout -循环等待，无限期传递SPINLOCK_wait_FOREVER blocs
 */
static inline bool __attribute__((always_inline)) spinlock_acquire(spinlock_t *lock, int32_t timeout)
{
#if !CONFIG_FREERTOS_UNICORE && !BOOTLOADER_BUILD
    uint32_t result;
    uint32_t irq_status;
    uint32_t ccount_start;
    uint32_t core_id, other_core_id;

    assert(lock);
    irq_status = XTOS_SET_INTLEVEL(XCHAL_EXCM_LEVEL);

    if(timeout != SPINLOCK_WAIT_FOREVER){
        RSR(CCOUNT, ccount_start);
    }

    /*旋转直到我们拥有核心*/
    RSR(PRID, core_id);

    /* 注：coreID是完整的32位核心ID（core_ID_REGVAL_PRO/core_ID_REGVAL_APP）*/

    other_core_id = CORE_ID_REGVAL_XOR_SWAP ^ core_id;
    do {

        /* lock->所有者应为SPINLOCK_FREE、CORE_ID_REGVAL_PRO、CORE_ID _REGVAL_APP之一：
         *  -如果是SPINLOCK_FREE，我们希望自动设置为“core_id”。
         *  -如果“我们的”core_id，我们可以立即通过。
         *  -如果“other_core_id”，我们在这里旋转。
         */
        result = core_id;

#if defined(CONFIG_ESP32_SPIRAM_SUPPORT)
        if (esp_ptr_external_ram(lock)) {
            compare_and_set_extram(&lock->owner, SPINLOCK_FREE, &result);
        } else {
#endif
        compare_and_set_native(&lock->owner, SPINLOCK_FREE, &result);
#if defined(CONFIG_ESP32_SPIRAM_SUPPORT)
        }
#endif
        if(result != other_core_id) {
            break;
        }

        if (timeout != SPINLOCK_WAIT_FOREVER) {
            uint32_t ccount_now;
            ccount_now = cpu_hal_get_cycle_count();
            if (ccount_now - ccount_start > (unsigned)timeout) {
                XTOS_RESTORE_INTLEVEL(irq_status);
                return false;
            }
        }
    }while(1);

    /* 任何其他值都表示内存损坏或未初始化多路复用器*/
    assert(result == core_id || result == SPINLOCK_FREE);
    assert((result == SPINLOCK_FREE) == (lock->count == 0)); /* 我们首先锁定iff计数为零*/
    assert(lock->count < 0xFF); /* 错误的计数值意味着内存损坏*/

    lock->count++;
    XTOS_RESTORE_INTLEVEL(irq_status);
    return true;

#else  // !CONFIG_FREERTOS_UNICORE
    return true;
#endif
}

/**
 * @brief 顶级自旋锁解锁功能，解锁先前锁定的自旋锁
 *
 * 该功能将：
 * -保存当前中断状态，然后禁用中断
 * -松开旋转锁
 * -恢复中断状态
 *
 * @note 自旋锁本身并不构成真正的关键部分（因为一旦获取自旋锁，该函数将重新启用中断）。对于关键部分，请使用操作系统提供的界面。
 * @param lock -目标，之前锁定，自旋锁定对象
 */
static inline void __attribute__((always_inline)) spinlock_release(spinlock_t *lock)
{
#if !CONFIG_FREERTOS_UNICORE && !BOOTLOADER_BUILD
    uint32_t irq_status;
    uint32_t core_id;

    assert(lock);
    irq_status = XTOS_SET_INTLEVEL(XCHAL_EXCM_LEVEL);

    RSR(PRID, core_id);
    assert(core_id == lock->owner); // 这是一个我们没有锁定的互斥锁，或者它已损坏
    lock->count--;

    if(!lock->count) {
        lock->owner = SPINLOCK_FREE;
    } else {
        assert(lock->count < 0x100); // 指示内存损坏
    }

    XTOS_RESTORE_INTLEVEL(irq_status);
#endif
}

#ifdef __cplusplus
}
#endif

