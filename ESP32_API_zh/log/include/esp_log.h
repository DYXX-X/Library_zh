/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef __ESP_LOG_H__
#define __ESP_LOG_H__

#include <stdint.h>
#include <stdarg.h>
#include "sdkconfig.h"
#include "esp_rom_sys.h"
#if CONFIG_IDF_TARGET_ESP32
#include "esp32/rom/ets_sys.h" // 将在idf v5.0中删除
#elif CONFIG_IDF_TARGET_ESP32S2
#include "esp32s2/rom/ets_sys.h"
#elif CONFIG_IDF_TARGET_ESP32S3
#include "esp32s3/rom/ets_sys.h"
#elif CONFIG_IDF_TARGET_ESP32C3
#include "esp32c3/rom/ets_sys.h"
#elif CONFIG_IDF_TARGET_ESP32H2
#include "esp32h2/rom/ets_sys.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 日志级别
 *
 */
typedef enum {
    ESP_LOG_NONE,       /*!< 无日志输出*/
    ESP_LOG_ERROR,      /*!< 严重错误，软件模块无法自行恢复*/
    ESP_LOG_WARN,       /*!< 已采取恢复措施的错误条件*/
    ESP_LOG_INFO,       /*!< 描述正常事件流的信息消息*/
    ESP_LOG_DEBUG,      /*!< 正常使用不需要的额外信息（值、指针、大小等）。*/
    ESP_LOG_VERBOSE     /*!< 更大的调试信息块，或可能淹没输出的频繁消息。*/
} esp_log_level_t;

typedef int (*vprintf_like_t)(const char *, va_list);

/**
 * @brief 默认日志级别
 *
 * 这用于定义ESP_EARLY_LOGx宏。建议不要直接设置，而是调用esp_log_level_set（“”，level）。
 */
extern esp_log_level_t esp_log_default_level;

/**
 * @brief 设置给定标记的日志级别
 *
 * 如果已启用给定组件的日志记录，则更改以前的设置。
 *
 * 请注意，此函数不能将日志级别提高到使用menuconfig中的CONFIG_log_MAXIMUM_level设置设置的级别之上。
 *
 * 要将日志级别提高到给定文件的默认级别之上，请在包含ESP_log之前将log_LOCAL_level定义为ESP_log_值之一。h。
 *
 * @param tag 要启用的日志项的标记。必须是以零结尾的非NULL字符串。值“”将所有标记的日志级别重置为给定值。
 *
 * @param level  选择要启用的日志级别。仅显示此级别和较低详细级别的日志。
 */
void esp_log_level_set(const char* tag, esp_log_level_t level);

/**
 * @brief 获取给定标记的日志级别，可用于避免昂贵的日志语句
 *
 * @param tag 要查询当前级别的日志的标记。必须是以零结尾的非NULL字符串。
 *
 * @return 给定标记的当前日志级别
 */
esp_log_level_t esp_log_level_get(const char* tag);

/**
 * @brief 用于输出日志项的Set函数
 *
 * 默认情况下，日志输出转到UART0。此功能可用于将日志输出重定向到其他目标，如文件或网络。返回原始日志处理程序，这可能是将输出返回到上一个目标所必需的。
 *
 * @note 请注意，这里的函数回调必须是可重入的，因为它可以从多线程上下文并行调用。
 *
 * @param func 用于输出的新函数。必须具有与vprintf相同的签名。
 *
 * @return func-old用于输出的函数。
 */
vprintf_like_t esp_log_set_vprintf(vprintf_like_t func);

/**
 * @brief 返回要在日志输出中使用的时间戳的函数
 *
 * 此函数用于扩展ESP_LOGx宏。在第二阶段引导加载程序中，在应用程序启动的早期阶段，此函数使用CPU周期计数器作为时间源。稍后，当FreeRTOS调度器开始运行时，它将切换到FreeRTOS滴答计数。
 *
 * 现在，我们忽略毫秒计数器溢出。
 *
 * @return 时间戳，以毫秒为单位
 */
uint32_t esp_log_timestamp(void);

/**
 * @brief 返回要在日志输出中使用的系统时间戳的函数
 *
 * 此函数用于扩展ESP_LOGx宏，以将系统时间打印为“HH:MM:SS.sss”。系统时间在启动时初始化为0，可以使用SNTP同步将其设置为正确的时间，也可以使用标准POSIX时间函数手动设置。
 *
 * 目前，这不会用于二进制blob（即WiFi和蓝牙库）的日志记录，这些blob仍然会打印RTOS滴答时间。
 *
 * @return 时间戳，单位为“HH:MM:SS.sss”
 */
char* esp_log_system_timestamp(void);

/**
 * @brief 返回要在日志输出中使用的时间戳的函数
 *
 * 此功能使用HW循环计数器，不依赖于操作系统，因此在应用程序崩溃后可以安全使用。
 *
 * @return 时间戳，以毫秒为单位
 */
uint32_t esp_log_early_timestamp(void);

/**
 * @brief 将消息写入日志
 *
 * 此功能不打算直接使用。相反，请使用ESP_LOGE、ESP_LOGW、ESP_LLOGI、ESP_LOGD和ESP_LOGV宏之一。
 *
 * 此函数或这些宏不应在中断时使用。
 */
void esp_log_write(esp_log_level_t level, const char* tag, const char* format, ...) __attribute__ ((format (printf, 3, 4)));

/**
 * @brief 将消息写入日志，va_list变量
 * @see esp_log_write（）
 *
 * 提供此函数是为了简化与其他日志框架的集成，因此esp_log可以用作日志接收器。
 */
void esp_log_writev(esp_log_level_t level, const char* tag, const char* format, va_list args);

/**@秒*/

#include "esp_log_internal.h"

#ifndef LOG_LOCAL_LEVEL
#ifndef BOOTLOADER_BUILD
#define LOG_LOCAL_LEVEL  CONFIG_LOG_MAXIMUM_LEVEL
#else
#define LOG_LOCAL_LEVEL  CONFIG_BOOTLOADER_LOG_LEVEL
#endif
#endif

/**@结束秒*/

/**
 * @brief 记录指定级别的十六进制字节缓冲区，每行分为16个字节。
 *
 * @param  tag      描述标签
 * @param  buffer   指向缓冲区数组的指针
 * @param  buff_len 缓冲区长度（字节）
 * @param  level    日志的级别
 *
 */
#define ESP_LOG_BUFFER_HEX_LEVEL( tag, buffer, buff_len, level ) \
    do {\
        if ( LOG_LOCAL_LEVEL >= (level) ) { \
            esp_log_buffer_hex_internal( tag, buffer, buff_len, level ); \
        } \
    } while(0)

/**
 * @brief 记录指定级别的字符缓冲区，每行分隔为16个字节。缓冲区应仅包含可打印字符。
 *
 * @param  tag      描述标签
 * @param  buffer   指向缓冲区数组的指针
 * @param  buff_len 缓冲区长度（字节）
 * @param  level    日志的级别
 *
 */
#define ESP_LOG_BUFFER_CHAR_LEVEL( tag, buffer, buff_len, level ) \
    do {\
        if ( LOG_LOCAL_LEVEL >= (level) ) { \
            esp_log_buffer_char_internal( tag, buffer, buff_len, level ); \
        } \
    } while(0)

/**
 * @brief 将缓冲区转储到指定级别的日志。
 *
 * 转储日志如下所示：
 *
 *      W（195）log_example:00x3ffb4280 45 53 50 33 32 20 69 73 20 67 65 61 74 2c 20 | ESP32很棒，|W（195 log_exable:00x3ff b4290 77 6f 72 6b 69 6e 67 20 61 6c 6f 6 e 67 20 77 69 |与IDF一起工作|W（205）log_e xample:0x3ffb42a0 74 68 20 74 68 65 20 49 46 2e 00 ||
 *
 * 强烈建议使用文本宽度超过102的终端。
 *
 * @param tag 描述标签
 * @param buffer 指向缓冲区数组的指针
 * @param buff_len 缓冲区长度（字节）
 * @param level 日志的级别
 */
#define ESP_LOG_BUFFER_HEXDUMP( tag, buffer, buff_len, level ) \
    do { \
        if ( LOG_LOCAL_LEVEL >= (level) ) { \
            esp_log_buffer_hexdump_internal( tag, buffer, buff_len, level); \
        } \
    } while(0)

/**
 * @brief 在信息级别记录十六进制字节的缓冲区
 *
 * @param  tag      描述标签
 * @param  buffer   指向缓冲区数组的指针
 * @param  buff_len 缓冲区长度（字节）
 *
 * @see ``esp_log_buffer-hex_level``
 *
 */
#define ESP_LOG_BUFFER_HEX(tag, buffer, buff_len) \
    do { \
        if (LOG_LOCAL_LEVEL >= ESP_LOG_INFO) { \
            ESP_LOG_BUFFER_HEX_LEVEL( tag, buffer, buff_len, ESP_LOG_INFO ); \
        }\
    } while(0)

/**
 * @brief 记录信息级别的字符缓冲区。缓冲区应仅包含可打印字符。
 *
 * @param  tag      描述标签
 * @param  buffer   指向缓冲区数组的指针
 * @param  buff_len 缓冲区长度（字节）
 *
 * @see ``esp_log_buffer_char_level``
 *
 */
#define ESP_LOG_BUFFER_CHAR(tag, buffer, buff_len) \
    do { \
        if (LOG_LOCAL_LEVEL >= ESP_LOG_INFO) { \
            ESP_LOG_BUFFER_CHAR_LEVEL( tag, buffer, buff_len, ESP_LOG_INFO ); \
        }\
    } while(0)

/**@秒*/

//向后兼容
#define esp_log_buffer_hex      ESP_LOG_BUFFER_HEX
#define esp_log_buffer_char     ESP_LOG_BUFFER_CHAR


#if CONFIG_LOG_COLORS
#define LOG_COLOR_BLACK   "30"
#define LOG_COLOR_RED     "31"
#define LOG_COLOR_GREEN   "32"
#define LOG_COLOR_BROWN   "33"
#define LOG_COLOR_BLUE    "34"
#define LOG_COLOR_PURPLE  "35"
#define LOG_COLOR_CYAN    "36"
#define LOG_COLOR(COLOR)  "\033[0;" COLOR "m"
#define LOG_BOLD(COLOR)   "\033[1;" COLOR "m"
#define LOG_RESET_COLOR   "\033[0m"
#define LOG_COLOR_E       LOG_COLOR(LOG_COLOR_RED)
#define LOG_COLOR_W       LOG_COLOR(LOG_COLOR_BROWN)
#define LOG_COLOR_I       LOG_COLOR(LOG_COLOR_GREEN)
#define LOG_COLOR_D
#define LOG_COLOR_V
#else //CONFIG_LOG_COLORS
#define LOG_COLOR_E
#define LOG_COLOR_W
#define LOG_COLOR_I
#define LOG_COLOR_D
#define LOG_COLOR_V
#define LOG_RESET_COLOR
#endif //CONFIG_LOG_COLORS

#define LOG_FORMAT(letter, format)  LOG_COLOR_ ## letter #letter " (%u) %s: " format LOG_RESET_COLOR "\n"
#define LOG_SYSTEM_TIME_FORMAT(letter, format)  LOG_COLOR_ ## letter #letter " (%s) %s: " format LOG_RESET_COLOR "\n"

/**@结束秒*/

///在堆分配器和系统调用初始化之前，在启动代码中输出日志的宏。日志级别为``ESP_log_ERROR``@请参见``printf``、``ESP_LOGE``、` `ESP_DRAM_LOGE``
#define portGET_ARGUMENT_COUNT_INNER(zero, one, count, ...) count

/**
 * 在未来，我们希望切换到C++20。我们还希望与clang兼容。因此，我们提供了以下宏的两个版本，它们使用可变参数。第一个是使用GNU扩展名\#\#__VA_ARGS__。第二种是使用C++20特性__VA_OPT__（，）。这允许用户使用标准C++20而不是GNU扩展来编译代码。在C++20以下，我们还没有找到使用\#\#__VA_ARGS__的好方法。
 */
#if defined(__cplusplus) && (__cplusplus >  201703L)
#define ESP_EARLY_LOGE( tag, format, ... ) ESP_LOG_EARLY_IMPL(tag, format, ESP_LOG_ERROR,   E __VA_OPT__(,) __VA_ARGS__)
///宏以在“ESP_LOG_WARN”级别的启动代码中输出日志@请参见``ESP_EARLY_LOGE``、``ESP_LOGE`、`` printf``
#define ESP_EARLY_LOGW( tag, format, ... ) ESP_LOG_EARLY_IMPL(tag, format, ESP_LOG_WARN,    W __VA_OPT__(,) __VA_ARGS__)
///宏以在“`ESP_LOG_INFO`”级别的启动代码中输出日志@请参见``ESP_EARLY_LOGE``、``ESP_LOGE`、`` printf``
#define ESP_EARLY_LOGI( tag, format, ... ) ESP_LOG_EARLY_IMPL(tag, format, ESP_LOG_INFO,    I __VA_OPT__(,) __VA_ARGS__)
///宏以在“`ESP_LOG_DEBUG`”级别的启动代码中输出日志@请参见``ESP_EARLY_LOGE``、``ESP_LOGE`、`` printf``
#define ESP_EARLY_LOGD( tag, format, ... ) ESP_LOG_EARLY_IMPL(tag, format, ESP_LOG_DEBUG,   D __VA_OPT__(,) __VA_ARGS__)
///宏以在“`ESP_LOG_VERBOSE”级别的启动代码中输出日志@请参见``ESP_EARLY_LOGE``、``ESP_LOGE`、`` printf``
#define ESP_EARLY_LOGV( tag, format, ... ) ESP_LOG_EARLY_IMPL(tag, format, ESP_LOG_VERBOSE, V __VA_OPT__(,) __VA_ARGS__)
#else // !（定义（__cplusplus）&&（__cpplusplus>201703L））
#define ESP_EARLY_LOGE( tag, format, ... ) ESP_LOG_EARLY_IMPL(tag, format, ESP_LOG_ERROR,   E, ##__VA_ARGS__)
///宏以在“ESP_LOG_WARN”级别的启动代码中输出日志@请参见``ESP_EARLY_LOGE``、``ESP_LOGE`、`` printf``
#define ESP_EARLY_LOGW( tag, format, ... ) ESP_LOG_EARLY_IMPL(tag, format, ESP_LOG_WARN,    W, ##__VA_ARGS__)
///宏以在“`ESP_LOG_INFO`”级别的启动代码中输出日志@请参见``ESP_EARLY_LOGE``、``ESP_LOGE`、`` printf``
#define ESP_EARLY_LOGI( tag, format, ... ) ESP_LOG_EARLY_IMPL(tag, format, ESP_LOG_INFO,    I, ##__VA_ARGS__)
///宏以在“`ESP_LOG_DEBUG`”级别的启动代码中输出日志@请参见``ESP_EARLY_LOGE``、``ESP_LOGE`、`` printf``
#define ESP_EARLY_LOGD( tag, format, ... ) ESP_LOG_EARLY_IMPL(tag, format, ESP_LOG_DEBUG,   D, ##__VA_ARGS__)
///宏以在“`ESP_LOG_VERBOSE”级别的启动代码中输出日志@请参见``ESP_EARLY_LOGE``、``ESP_LOGE`、`` printf``
#define ESP_EARLY_LOGV( tag, format, ... ) ESP_LOG_EARLY_IMPL(tag, format, ESP_LOG_VERBOSE, V, ##__VA_ARGS__)
#endif // !（定义（__cplusplus）&&（__cpplusplus>201703L））

#ifdef BOOTLOADER_BUILD
#define _ESP_LOG_EARLY_ENABLED(log_level) (LOG_LOCAL_LEVEL >= (log_level))
#else
/* 对于早期日志，没有日志标记过滤。因此，我们只希望在log_LOCAL_LEVEL和当前配置的最小日志级别都高于日志级别时进行日志记录*/
#define _ESP_LOG_EARLY_ENABLED(log_level) (LOG_LOCAL_LEVEL >= (log_level) && esp_log_default_level >= (log_level))
#endif

#define ESP_LOG_EARLY_IMPL(tag, format, log_level, log_tag_letter, ...) do {                             \
        if (_ESP_LOG_EARLY_ENABLED(log_level)) {                                                         \
            esp_rom_printf(LOG_FORMAT(log_tag_letter, format), esp_log_timestamp(), tag, ##__VA_ARGS__); \
        }} while(0)

#ifndef BOOTLOADER_BUILD
#if defined(__cplusplus) && (__cplusplus >  201703L)
#define ESP_LOGE( tag, format, ... ) ESP_LOG_LEVEL_LOCAL(ESP_LOG_ERROR,   tag, format __VA_OPT__(,) __VA_ARGS__)
#define ESP_LOGW( tag, format, ... ) ESP_LOG_LEVEL_LOCAL(ESP_LOG_WARN,    tag, format __VA_OPT__(,) __VA_ARGS__)
#define ESP_LOGI( tag, format, ... ) ESP_LOG_LEVEL_LOCAL(ESP_LOG_INFO,    tag, format __VA_OPT__(,) __VA_ARGS__)
#define ESP_LOGD( tag, format, ... ) ESP_LOG_LEVEL_LOCAL(ESP_LOG_DEBUG,   tag, format __VA_OPT__(,) __VA_ARGS__)
#define ESP_LOGV( tag, format, ... ) ESP_LOG_LEVEL_LOCAL(ESP_LOG_VERBOSE, tag, format __VA_OPT__(,) __VA_ARGS__)
#else // !（定义（__cplusplus）&&（__cpplusplus>201703L））
#define ESP_LOGE( tag, format, ... ) ESP_LOG_LEVEL_LOCAL(ESP_LOG_ERROR,   tag, format, ##__VA_ARGS__)
#define ESP_LOGW( tag, format, ... ) ESP_LOG_LEVEL_LOCAL(ESP_LOG_WARN,    tag, format, ##__VA_ARGS__)
#define ESP_LOGI( tag, format, ... ) ESP_LOG_LEVEL_LOCAL(ESP_LOG_INFO,    tag, format, ##__VA_ARGS__)
#define ESP_LOGD( tag, format, ... ) ESP_LOG_LEVEL_LOCAL(ESP_LOG_DEBUG,   tag, format, ##__VA_ARGS__)
#define ESP_LOGV( tag, format, ... ) ESP_LOG_LEVEL_LOCAL(ESP_LOG_VERBOSE, tag, format, ##__VA_ARGS__)
#endif // !（定义（__cplusplus）&&（__cpplusplus>201703L））
#else

/**
 * 在ESP_LOG_ERROR级别输出日志的宏。
 *
 * @note 当中断被禁用或在ISR内部时，不能使用此宏@请参见``ESP_DRAM_LOGE``。
 *
 * @param tag 标记，可用于在运行时通过“esp_log_level_set”更改日志级别。
 *
 * @see ``打印f``
 */
#if defined(__cplusplus) && (__cplusplus >  201703L)
#define ESP_LOGE( tag, format, ... )  ESP_EARLY_LOGE(tag, format __VA_OPT__(,) __VA_ARGS__)
///宏以输出“`ESP_LOG_WARN`”级别的日志@请参见``ESP_LOGE``
#define ESP_LOGW( tag, format, ... )  ESP_EARLY_LOGW(tag, format __VA_OPT__(,) __VA_ARGS__)
///宏以输出``ESP_LOG_INFO``级别的日志@请参见``ESP_LOGE``
#define ESP_LOGI( tag, format, ... )  ESP_EARLY_LOGI(tag, format __VA_OPT__(,) __VA_ARGS__)
///宏以输出``ESP_LOG_DEBUG``级别的日志@请参见``ESP_LOGE``
#define ESP_LOGD( tag, format, ... )  ESP_EARLY_LOGD(tag, format __VA_OPT__(,) __VA_ARGS__)
///宏以输出``ESP_LOG_VERBOSE ``级别的日志@请参见``ESP_LOGE``
#define ESP_LOGV( tag, format, ... )  ESP_EARLY_LOGV(tag, format __VA_OPT__(,) __VA_ARGS__)
#else // !（定义（__cplusplus）&&（__cpplusplus>201703L））
#define ESP_LOGE( tag, format, ... )  ESP_EARLY_LOGE(tag, format, ##__VA_ARGS__)
///宏以输出“`ESP_LOG_WARN`”级别的日志@请参见``ESP_LOGE``
#define ESP_LOGW( tag, format, ... )  ESP_EARLY_LOGW(tag, format, ##__VA_ARGS__)
///宏以输出``ESP_LOG_INFO``级别的日志@请参见``ESP_LOGE``
#define ESP_LOGI( tag, format, ... )  ESP_EARLY_LOGI(tag, format, ##__VA_ARGS__)
///宏以输出``ESP_LOG_DEBUG``级别的日志@请参见``ESP_LOGE``
#define ESP_LOGD( tag, format, ... )  ESP_EARLY_LOGD(tag, format, ##__VA_ARGS__)
///宏以输出``ESP_LOG_VERBOSE ``级别的日志@请参见``ESP_LOGE``
#define ESP_LOGV( tag, format, ... )  ESP_EARLY_LOGV(tag, format, ##__VA_ARGS__)
#endif // !（定义（__cplusplus）&&（__cpplusplus>201703L））
#endif  // BOOTLOADER_BUILD

/** 在指定级别输出日志的运行时宏。
 *
 * @param tag 标记，可用于在运行时通过“esp_log_level_set”更改日志级别。
 * @param level 输出日志的级别。
 * @param format 输出日志的格式。参见``printf``
 * @param ... 要替换到日志中的变量。参见``printf``
 *
 * @see ``打印f``
 */
#if defined(__cplusplus) && (__cplusplus >  201703L)
#if CONFIG_LOG_TIMESTAMP_SOURCE_RTOS
#define ESP_LOG_LEVEL(level, tag, format, ...) do {                     \
        if (level==ESP_LOG_ERROR )          { esp_log_write(ESP_LOG_ERROR,      tag, LOG_FORMAT(E, format), esp_log_timestamp(), tag __VA_OPT__(,) __VA_ARGS__); } \
        else if (level==ESP_LOG_WARN )      { esp_log_write(ESP_LOG_WARN,       tag, LOG_FORMAT(W, format), esp_log_timestamp(), tag __VA_OPT__(,) __VA_ARGS__); } \
        else if (level==ESP_LOG_DEBUG )     { esp_log_write(ESP_LOG_DEBUG,      tag, LOG_FORMAT(D, format), esp_log_timestamp(), tag __VA_OPT__(,) __VA_ARGS__); } \
        else if (level==ESP_LOG_VERBOSE )   { esp_log_write(ESP_LOG_VERBOSE,    tag, LOG_FORMAT(V, format), esp_log_timestamp(), tag __VA_OPT__(,) __VA_ARGS__); } \
        else                                { esp_log_write(ESP_LOG_INFO,       tag, LOG_FORMAT(I, format), esp_log_timestamp(), tag __VA_OPT__(,) __VA_ARGS__); } \
    } while(0)
#elif CONFIG_LOG_TIMESTAMP_SOURCE_SYSTEM
#define ESP_LOG_LEVEL(level, tag, format, ...) do {                     \
        if (level==ESP_LOG_ERROR )          { esp_log_write(ESP_LOG_ERROR,      tag, LOG_SYSTEM_TIME_FORMAT(E, format), esp_log_system_timestamp(), tag __VA_OPT__(,) __VA_ARGS__); } \
        else if (level==ESP_LOG_WARN )      { esp_log_write(ESP_LOG_WARN,       tag, LOG_SYSTEM_TIME_FORMAT(W, format), esp_log_system_timestamp(), tag __VA_OPT__(,) __VA_ARGS__); } \
        else if (level==ESP_LOG_DEBUG )     { esp_log_write(ESP_LOG_DEBUG,      tag, LOG_SYSTEM_TIME_FORMAT(D, format), esp_log_system_timestamp(), tag __VA_OPT__(,) __VA_ARGS__); } \
        else if (level==ESP_LOG_VERBOSE )   { esp_log_write(ESP_LOG_VERBOSE,    tag, LOG_SYSTEM_TIME_FORMAT(V, format), esp_log_system_timestamp(), tag __VA_OPT__(,) __VA_ARGS__); } \
        else                                { esp_log_write(ESP_LOG_INFO,       tag, LOG_SYSTEM_TIME_FORMAT(I, format), esp_log_system_timestamp(), tag __VA_OPT__(,) __VA_ARGS__); } \
    } while(0)
#endif //配置_日志_时间戳_来源_xxx
#else // !（定义（__cplusplus）&&（__cpplusplus>201703L））
#if CONFIG_LOG_TIMESTAMP_SOURCE_RTOS
#define ESP_LOG_LEVEL(level, tag, format, ...) do {                     \
        if (level==ESP_LOG_ERROR )          { esp_log_write(ESP_LOG_ERROR,      tag, LOG_FORMAT(E, format), esp_log_timestamp(), tag, ##__VA_ARGS__); } \
        else if (level==ESP_LOG_WARN )      { esp_log_write(ESP_LOG_WARN,       tag, LOG_FORMAT(W, format), esp_log_timestamp(), tag, ##__VA_ARGS__); } \
        else if (level==ESP_LOG_DEBUG )     { esp_log_write(ESP_LOG_DEBUG,      tag, LOG_FORMAT(D, format), esp_log_timestamp(), tag, ##__VA_ARGS__); } \
        else if (level==ESP_LOG_VERBOSE )   { esp_log_write(ESP_LOG_VERBOSE,    tag, LOG_FORMAT(V, format), esp_log_timestamp(), tag, ##__VA_ARGS__); } \
        else                                { esp_log_write(ESP_LOG_INFO,       tag, LOG_FORMAT(I, format), esp_log_timestamp(), tag, ##__VA_ARGS__); } \
    } while(0)
#elif CONFIG_LOG_TIMESTAMP_SOURCE_SYSTEM
#define ESP_LOG_LEVEL(level, tag, format, ...) do {                     \
        if (level==ESP_LOG_ERROR )          { esp_log_write(ESP_LOG_ERROR,      tag, LOG_SYSTEM_TIME_FORMAT(E, format), esp_log_system_timestamp(), tag, ##__VA_ARGS__); } \
        else if (level==ESP_LOG_WARN )      { esp_log_write(ESP_LOG_WARN,       tag, LOG_SYSTEM_TIME_FORMAT(W, format), esp_log_system_timestamp(), tag, ##__VA_ARGS__); } \
        else if (level==ESP_LOG_DEBUG )     { esp_log_write(ESP_LOG_DEBUG,      tag, LOG_SYSTEM_TIME_FORMAT(D, format), esp_log_system_timestamp(), tag, ##__VA_ARGS__); } \
        else if (level==ESP_LOG_VERBOSE )   { esp_log_write(ESP_LOG_VERBOSE,    tag, LOG_SYSTEM_TIME_FORMAT(V, format), esp_log_system_timestamp(), tag, ##__VA_ARGS__); } \
        else                                { esp_log_write(ESP_LOG_INFO,       tag, LOG_SYSTEM_TIME_FORMAT(I, format), esp_log_system_timestamp(), tag, ##__VA_ARGS__); } \
    } while(0)
#endif //配置_日志_时间戳_来源_xxx
#endif // !（定义（__cplusplus）&&（__cpplusplus>201703L））

/** 在指定级别输出日志的运行时宏。同时使用``LOG_LOCAL_level``检查级别。
 *
 * @see ``打印``，``ESP_LOG_LEVEL``
 */
#define ESP_LOG_LEVEL_LOCAL(level, tag, format, ...) do {               \
        if ( LOG_LOCAL_LEVEL >= level ) ESP_LOG_LEVEL(level, tag, format, ##__VA_ARGS__); \
    } while(0)


/**
 * @brief 禁用缓存时输出日志的宏。日志级别为``ESP_log_ERROR``。
 *
 * @note 与常规日志记录宏不同，当中断被禁用或在ISR内部时，可以使用此宏。
 *
 * Similar to @see ``ESP_EARLY_LOGE``，不能更改每个标记的日志级别，但是ESP_log_level_set（“”，级别）将设置默认级别，该级别也控制这些日志行。
 *
 * 用法：`ESP_DRAM_LOGE（DRAM_STR（“my_tag”）、“format”或`ESP_DRAM_LOGE（tag，“format”，…）`，其中tag是指向DRAM中STR的字符。
 *
 * @note 在DRAM中放置日志字符串会减少可用的DRAM，因此只有在绝对必要时才使用。
 *
 * @see ``esp_rom_printf``，``esp_LOGE``
 */
#if defined(__cplusplus) && (__cplusplus >  201703L)
#define ESP_DRAM_LOGE( tag, format, ... ) ESP_DRAM_LOG_IMPL(tag, format, ESP_LOG_ERROR,   E __VA_OPT__(,) __VA_ARGS__)
///当缓存在“`ESP_LOG_WARN`”级别禁用时，宏输出日志@请参见``ESP_DRAM_LOGW``、``ESP_LOGW`、`` ESP_rom_printf``
#define ESP_DRAM_LOGW( tag, format, ... ) ESP_DRAM_LOG_IMPL(tag, format, ESP_LOG_WARN,    W __VA_OPT__(,) __VA_ARGS__)
///宏在“`ESP_LOG_INFO`”级别禁用缓存时输出日志@请参见``ESP_DRAM_LOGI``、``ESP_LOGI`、`` ESP_rom_printf``
#define ESP_DRAM_LOGI( tag, format, ... ) ESP_DRAM_LOG_IMPL(tag, format, ESP_LOG_INFO,    I __VA_OPT__(,) __VA_ARGS__)
///宏在“`ESP_LOG_DEBUG`”级别禁用缓存时输出日志@请参见``ESP_DRAM_LOGD``、``ESP_LOGD`、`` ESP_rom_printf``
#define ESP_DRAM_LOGD( tag, format, ... ) ESP_DRAM_LOG_IMPL(tag, format, ESP_LOG_DEBUG,   D __VA_OPT__(,) __VA_ARGS__)
///宏在“`ESP_LOG_VERBOSE”级别禁用缓存时输出日志@请参见``ESP_DRAM_LOGV``、``ESP_LOGV`、`` ESP_rom_printf``
#define ESP_DRAM_LOGV( tag, format, ... ) ESP_DRAM_LOG_IMPL(tag, format, ESP_LOG_VERBOSE, V __VA_OPT__(,) __VA_ARGS__)
#else // !（定义（__cplusplus）&&（__cpplusplus>201703L））
#define ESP_DRAM_LOGE( tag, format, ... ) ESP_DRAM_LOG_IMPL(tag, format, ESP_LOG_ERROR,   E, ##__VA_ARGS__)
///当缓存在“`ESP_LOG_WARN`”级别禁用时，宏输出日志@请参见``ESP_DRAM_LOGW``、``ESP_LOGW`、`` ESP_rom_printf``
#define ESP_DRAM_LOGW( tag, format, ... ) ESP_DRAM_LOG_IMPL(tag, format, ESP_LOG_WARN,    W, ##__VA_ARGS__)
///宏在“`ESP_LOG_INFO`”级别禁用缓存时输出日志@请参见``ESP_DRAM_LOGI``、``ESP_LOGI`、`` ESP_rom_printf``
#define ESP_DRAM_LOGI( tag, format, ... ) ESP_DRAM_LOG_IMPL(tag, format, ESP_LOG_INFO,    I, ##__VA_ARGS__)
///宏在“`ESP_LOG_DEBUG`”级别禁用缓存时输出日志@请参见``ESP_DRAM_LOGD``、``ESP_LOGD`、`` ESP_rom_printf``
#define ESP_DRAM_LOGD( tag, format, ... ) ESP_DRAM_LOG_IMPL(tag, format, ESP_LOG_DEBUG,   D, ##__VA_ARGS__)
///宏在“`ESP_LOG_VERBOSE”级别禁用缓存时输出日志@请参见``ESP_DRAM_LOGV``、``ESP_LOGV`、`` ESP_rom_printf``
#define ESP_DRAM_LOGV( tag, format, ... ) ESP_DRAM_LOG_IMPL(tag, format, ESP_LOG_VERBOSE, V, ##__VA_ARGS__)
#endif // !（定义（__cplusplus）&&（__cpplusplus>201703L））

/**@秒*/
#define _ESP_LOG_DRAM_LOG_FORMAT(letter, format)  DRAM_STR(#letter " %s: " format "\n")

#if defined(__cplusplus) && (__cplusplus >  201703L)
#define ESP_DRAM_LOG_IMPL(tag, format, log_level, log_tag_letter, ...) do {                                  \
        if (_ESP_LOG_EARLY_ENABLED(log_level)) {                                                             \
            esp_rom_printf(_ESP_LOG_DRAM_LOG_FORMAT(log_tag_letter, format), tag __VA_OPT__(,) __VA_ARGS__); \
        }} while(0)
#else // !（定义（__cplusplus）&&（__cpplusplus>201703L））
#define ESP_DRAM_LOG_IMPL(tag, format, log_level, log_tag_letter, ...) do {                       \
        if (_ESP_LOG_EARLY_ENABLED(log_level)) {                                                  \
            esp_rom_printf(_ESP_LOG_DRAM_LOG_FORMAT(log_tag_letter, format), tag, ##__VA_ARGS__); \
        }} while(0)
#endif // !（定义（__cplusplus）&&（__cpplusplus>201703L））
/**@结束秒*/

#ifdef __cplusplus
}
#endif


#endif /* __ESP_LOG_H__ */

