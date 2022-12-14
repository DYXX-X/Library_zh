/*
 * SPDX文件版权文本：2018-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _OSAL_H_
#define _OSAL_H_

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <unistd.h>
#include <stdint.h>
#include <esp_timer.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OS_SUCCESS ESP_OK
#define OS_FAIL    ESP_FAIL

typedef TaskHandle_t othread_t;

static inline int httpd_os_thread_create(othread_t *thread,
                                 const char *name, uint16_t stacksize, int prio,
                                 void (*thread_routine)(void *arg), void *arg,
                                 BaseType_t core_id)
{
    int ret = xTaskCreatePinnedToCore(thread_routine, name, stacksize, arg, prio, thread, core_id);
    if (ret == pdPASS) {
        return OS_SUCCESS;
    }
    return OS_FAIL;
}

/* 仅支持自删除*/
static inline void httpd_os_thread_delete(void)
{
    vTaskDelete(xTaskGetCurrentTaskHandle());
}

static inline void httpd_os_thread_sleep(int msecs)
{
    vTaskDelay(msecs / portTICK_RATE_MS);
}

static inline othread_t httpd_os_thread_handle(void)
{
    return xTaskGetCurrentTaskHandle();
}

#ifdef __cplusplus
}
#endif

#endif /* ! _OSAL_H_ */

