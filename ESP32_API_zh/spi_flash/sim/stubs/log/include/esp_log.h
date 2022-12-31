/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 *
 * 这是编译ESP-IDF以在主机系统上运行测试时使用的STUB FILE HEADER。通常用于ESP-IDF的头文件具有相同的名称，但位于其他位置。
 */
#pragma once

#include <stdint.h>
#include <stdio.h>

#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

#define strlcpy(a, b, c)
#define strlcat(a, b, c)

#define heap_caps_malloc(a, b)  NULL
#define MALLOC_CAP_INTERNAL     0
#define MALLOC_CAP_8BIT         0

#define LOG_LOCAL_LEVEL         CONFIG_LOG_DEFAULT_LEVEL

typedef enum {
    ESP_LOG_NONE,       /*!< 无日志输出*/
    ESP_LOG_ERROR,      /*!< 严重错误，软件模块无法自行恢复*/
    ESP_LOG_WARN,       /*!< 已采取恢复措施的错误条件*/
    ESP_LOG_INFO,       /*!< 描述正常事件流的信息消息*/
    ESP_LOG_DEBUG,      /*!< 正常使用不需要的额外信息（值、指针、大小等）。*/
    ESP_LOG_VERBOSE     /*!< 更大的调试信息块，或可能淹没输出的频繁消息。*/
} esp_log_level_t;

#define LOG_COLOR_E
#define LOG_COLOR_W
#define LOG_COLOR_I
#define LOG_COLOR_D
#define LOG_COLOR_V
#define LOG_RESET_COLOR

#undef _Static_assert
#define _Static_assert(cond, message)

uint32_t esp_log_timestamp(void);
void esp_log_write(esp_log_level_t level, const char* tag, const char* format, ...) __attribute__ ((format (printf, 3, 4)));

#define LOG_FORMAT(letter, format)  LOG_COLOR_ ## letter #letter " (%d) %s: " format LOG_RESET_COLOR "\n"

#define ESP_LOGE( tag, format, ... )  if (LOG_LOCAL_LEVEL >= ESP_LOG_ERROR)   { esp_log_write(ESP_LOG_ERROR,   tag, LOG_FORMAT(E, format), esp_log_timestamp(), tag, ##__VA_ARGS__); }

#define ESP_LOGW( tag, format, ... )  if (LOG_LOCAL_LEVEL >= ESP_LOG_WARN)    { esp_log_write(ESP_LOG_WARN,    tag, LOG_FORMAT(W, format), esp_log_timestamp(), tag, ##__VA_ARGS__); }

#define ESP_LOGI( tag, format, ... )  if (LOG_LOCAL_LEVEL >= ESP_LOG_INFO)    { esp_log_write(ESP_LOG_INFO,    tag, LOG_FORMAT(I, format), esp_log_timestamp(), tag, ##__VA_ARGS__); }

#define ESP_LOGD( tag, format, ... )  if (LOG_LOCAL_LEVEL >= ESP_LOG_DEBUG)   { esp_log_write(ESP_LOG_DEBUG,   tag, LOG_FORMAT(D, format), esp_log_timestamp(), tag, ##__VA_ARGS__); }

#define ESP_LOGV( tag, format, ... )  if (LOG_LOCAL_LEVEL >= ESP_LOG_VERBOSE) { esp_log_write(ESP_LOG_VERBOSE, tag, LOG_FORMAT(V, format), esp_log_timestamp(), tag, ##__VA_ARGS__); }

// 假设未启用闪存加密。放在分区.c中
// esp_log。h晚于esp_flash_encrypt.h。
#define esp_flash_encryption_enabled()      false

#ifdef __cplusplus
}
#endif

