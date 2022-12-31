// 版权所有2021 Espressif Systems（Shanghai）PTE LTD
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

#include <stdbool.h>
#include <stdint.h>

typedef struct esp_timer* esp_timer_handle_t;

typedef void (*esp_timer_cb_t)(void* arg);

typedef enum {
    ESP_TIMER_TASK,
} esp_timer_dispatch_t;

typedef struct {
    esp_timer_cb_t callback;        //!< 计时器过期时调用的函数
    void* arg;                      //!< 要传递给回调的参数
    esp_timer_dispatch_t dispatch_method;   //!< 从任务或ISR调用回调
    const char* name;               //!< 计时器名称，用于esp_Timer_dump函数
    bool skip_unhandled_events;     //!< 跳过定期计时器的未处理事件
} esp_timer_create_args_t;

esp_err_t esp_timer_create(const esp_timer_create_args_t* create_args,
                           esp_timer_handle_t* out_handle);
esp_err_t esp_timer_start_periodic(esp_timer_handle_t timer, uint64_t period);

esp_err_t esp_timer_stop(esp_timer_handle_t timer);

esp_err_t esp_timer_delete(esp_timer_handle_t timer);

