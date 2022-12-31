/*
 * 此文件受文件“LICENSE”中定义的条款和条件约束，该文件是源代码包的一部分。Tuan PM＜Tuan PM at live dot com＞
 */
#ifndef _ESP_PLATFORM_H__
#define _ESP_PLATFORM_H__

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

#include <sys/time.h>

char *platform_create_id_string(void);
int platform_random(int max);
long long platform_tick_get_ms(void);
void ms_to_timeval(int timeout_ms, struct timeval *tv);

#define ESP_MEM_CHECK(TAG, a, action) if (!(a)) {                                                      \
        ESP_LOGE(TAG,"%s(%d): %s",  __FUNCTION__, __LINE__, "Memory exhausted"); \
        action;                                                                                         \
        }

#define ESP_OK_CHECK(TAG, a, action) if ((a) != ESP_OK) {                                                     \
        ESP_LOGE(TAG,"%s(%d): %s", __FUNCTION__, __LINE__, "Failed with non ESP_OK err code"); \
        action;                                                                                               \
        }

#endif

