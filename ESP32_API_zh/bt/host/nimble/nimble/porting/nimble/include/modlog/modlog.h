/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_MODLOG_
#define H_MODLOG_

#include <stdio.h>

#include "log/log.h"
#include "log_common/log_common.h"

#ifdef ESP_PLATFORM
#include "esp_log.h"
#include <stdio.h>
#include <stdarg.h>
#endif

#define MODLOG_MODULE_DFLT 255

#ifdef ESP_PLATFORM
#define MODLOG_ESP_LOCAL(level, ml_msg_, ...) do { \
    if (MYNEWT_VAL(BLE_HS_LOG_LVL) <= LOG_LOCAL_LEVEL) ESP_LOG_LEVEL_LOCAL(level, "NimBLE", ml_msg_, ##__VA_ARGS__); \
} while(0)

#define MODLOG_DEBUG(ml_mod_, ml_msg_, ...) \
    MODLOG_ESP_LOCAL(ESP_LOG_DEBUG, ml_msg_, ##__VA_ARGS__)

#define MODLOG_INFO(ml_mod_, ml_msg_, ...) \
    MODLOG_ESP_LOCAL(ESP_LOG_INFO, ml_msg_, ##__VA_ARGS__)

#define MODLOG_WARN(ml_mod_, ml_msg_, ...) \
    MODLOG_ESP_LOCAL(ESP_LOG_WARN, ml_msg_, ##__VA_ARGS__)

#define MODLOG_ERROR(ml_mod_, ml_msg_, ...) \
    MODLOG_ESP_LOCAL(ESP_LOG_ERROR, ml_msg_, ##__VA_ARGS__)

#define MODLOG_CRITICAL(ml_mod_, ml_msg_, ...) \
    MODLOG_ESP_LOCAL(ESP_LOG_ERROR, ml_msg_, ##__VA_ARGS__)

#else

#if MYNEWT_VAL(LOG_LEVEL) <= LOG_LEVEL_DEBUG || defined __DOXYGEN__
#define MODLOG_DEBUG(ml_mod_, ml_msg_, ...) \
    printf((ml_msg_), ##__VA_ARGS__)
#else
#define MODLOG_DEBUG(ml_mod_, ...) IGNORE(__VA_ARGS__)
#endif

#if MYNEWT_VAL(LOG_LEVEL) <= LOG_LEVEL_INFO || defined __DOXYGEN__
#define MODLOG_INFO(ml_mod_, ml_msg_, ...) \
    printf((ml_msg_), ##__VA_ARGS__)
#else
#define MODLOG_INFO(ml_mod_, ...) IGNORE(__VA_ARGS__)
#endif

#if MYNEWT_VAL(LOG_LEVEL) <= LOG_LEVEL_WARN || defined __DOXYGEN__
#define MODLOG_WARN(ml_mod_, ml_msg_, ...) \
    printf((ml_msg_), ##__VA_ARGS__)
#else
#define MODLOG_WARN(ml_mod_, ...) IGNORE(__VA_ARGS__)
#endif

#if MYNEWT_VAL(LOG_LEVEL) <= LOG_LEVEL_ERROR || defined __DOXYGEN__
#define MODLOG_ERROR(ml_mod_, ml_msg_, ...) \
    printf((ml_msg_), ##__VA_ARGS__)
#else
#define MODLOG_ERROR(ml_mod_, ...) IGNORE(__VA_ARGS__)
#endif

#if MYNEWT_VAL(LOG_LEVEL) <= LOG_LEVEL_CRITICAL || defined __DOXYGEN__
#define MODLOG_CRITICAL(ml_mod_, ml_msg_, ...) \
    printf((ml_msg_), ##__VA_ARGS__)
#else
#define MODLOG_CRITICAL(ml_mod_, ...) IGNORE(__VA_ARGS__)
#endif

#endif

#define MODLOG(ml_lvl_, ml_mod_, ...) \
    MODLOG_ ## ml_lvl_((ml_mod_), __VA_ARGS__)

#define MODLOG_DFLT(ml_lvl_, ...) \
    MODLOG(ml_lvl_, LOG_MODULE_DEFAULT, __VA_ARGS__)

#endif

