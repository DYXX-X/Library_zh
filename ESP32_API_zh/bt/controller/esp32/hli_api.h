// 版权所有2015-2021 Espressif Systems（Shanghai）CO LTD
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。


#pragma once

#include <stdint.h>
#include "esp_err.h"
#include "esp_intr_alloc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

#ifdef __cplusplus
extern "C" {
#endif

#if CONFIG_BTDM_CTRL_HLI

/***队列***/

struct hli_queue_t
{
    size_t elem_size;
    char* begin;
    char* end;
    const char* bufend;
    QueueHandle_t downstream;
    int flags;
    char buf[0];
};

/**
 * @brief 注册高级中断功能
 *
 * @param handler  中断处理程序函数
 * @param arg      要传递给中断处理程序的参数
 * @param intr_reg   包含中断状态的外围寄存器的地址，或从CPU interrupt寄存器获取状态的值0
 * @param intr_mask  中断状态寄存器中的中断掩码
 * @return
 *      -成功时ESP_OK
 *      -如果注册的处理程序太多，则为ESP_ERR_NO_MEM
 */
esp_err_t hli_intr_register(intr_handler_t handler, void* arg, uint32_t intr_reg, uint32_t intr_mask);

/**
 * @brief 屏蔽当前CPU上的所有中断（包括高级中断）
 *
 * @return uint32_t中断状态，将其传递给hli_intr_store
 */
uint32_t hli_intr_disable(void);

/**
 * @brief 重新启用中断
 *
 * @param state hl_intr_disable返回的值
 */
void hli_intr_restore(uint32_t state);

/**
 * @brief hli队列的类型
 */
typedef struct hli_queue_t* hli_queue_handle_t;

/**
 * @brief 初始化hli_queue模块。在使用hli队列API之前必须调用一次。
 */
void hli_queue_setup(void);

/**
 * @brief 关闭hli_queue模块。
 */
void hli_queue_shutdown(void);

/**
 * @brief 创建一个hli队列，包装一个FreeRTOS队列
 *
 * 此队列可以从高级中断中使用，但仅在调用了hli_queue_setup的CPU上使用。发送到此队列的值使用3级软件中断自动转发到“下游”FreeRTOS队列。
 *
 * @param nelem  队列中的元素数
 * @param elem_size  一个元素的大小；必须匹配下游队列的元素大小
 * @param downstream  将值发送到的FreeRTOS队列
 * @return hli_queue_handle_t已创建队列的句柄，或失败时为NULL
 */
hli_queue_handle_t hli_queue_create(size_t nelem, size_t elem_size, QueueHandle_t downstream);

/**
 * @brief 创建客户hli队列，包装FreeRTOS队列
 *
 * 此队列可以从高级中断中使用，但仅在调用了hli_queue_setup的CPU上使用。发送到此队列的值使用3级软件中断自动转发到“下游”FreeRTOS队列。
 *
 * @param nelem  队列中的元素数
 * @param elem_size  一个元素的大小；必须匹配下游队列的元素大小
 * @param downstream  将值发送到的FreeRTOS队列
 * @return hli_queue_handle_t已创建队列的句柄，或失败时为NULL
 */
hli_queue_handle_t hli_customer_queue_create(size_t nelem, size_t elem_size, QueueHandle_t downstream);

/**
 * @brief 创建一个hli队列，包装一个FreeRTOS信号量
 *
 * 请参阅有关hli_queue_create的说明。
 *
 * @param max_count  最大信号量计数
 * @param downstream  将调用转发到的FreeRTOS信号量
 * @return hli_queue_handle_t已创建队列的句柄，或失败时为NULL
 */
hli_queue_handle_t hli_semaphore_create(size_t max_count, SemaphoreHandle_t downstream);

/**
 * @brief 删除hli队列
 *
 * 在删除队列之前，请确保没有人使用队列。
 *
 * @param queue  hli_queue_create或hli_maphore_create返回的句柄
 */
void hli_queue_delete(hli_queue_handle_t queue);

/**
 * @brief 从hli队列中获取一个元素
 *
 * 通常不使用，值会自动发送到下游FreeRTOS队列。然而，如果下游队列为NULL，则可以使用此API从hli队列获取值。
 *
 * @param queue  队列句柄
 * @param out  存储元素的指针
 * @return 如果成功从队列中读取元素，则为true
 */
bool hli_queue_get(hli_queue_handle_t queue, void* out);

/**
 * @brief 将一个元素放入一个hli队列
 *
 * 这会将一个元素复制到队列中，并引发软件中断（级别3）。在中断中，该值被复制到FreeRTOS“下游”队列。
 *
 * 请注意，如果该值不适合下游队列，则不会返回任何错误，并且该值将丢失。
 *
 * @param queue 队列句柄
 * @param data  指向要发送的元素的指针
 * @return 如果成功将数据放入hli队列，则为true
 */
bool hli_queue_put(hli_queue_handle_t queue, const void* data);

/**
 * @brief “Give”一个由hli队列包装的信号量
 *
 * @param queue  hli_maphore_create返回的句柄
 * @return 如果事件成功发送到hli队列，则为true
 */
bool hli_semaphore_give(hli_queue_handle_t queue);

#endif /* CONFIG_BTDM_CTRL_HLI */

#ifdef __cplusplus
}
#endif

