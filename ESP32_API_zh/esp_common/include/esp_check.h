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

#include "esp_err.h"
#include "esp_log.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 可用于检查错误代码的宏。如果代码不是ESP_OK，则打印消息并返回。
 */
#if defined(CONFIG_COMPILER_OPTIMIZATION_CHECKS_SILENT)
#define ESP_RETURN_ON_ERROR(x, log_tag, format, ...) do {                                       \
        (void)log_tag;                                                                          \
        esp_err_t err_rc_ = (x);                                                                \
        if (unlikely(err_rc_ != ESP_OK)) {                                                      \
            return err_rc_;                                                                     \
        }                                                                                       \
    } while(0)

/**
 * 可以从ISR调用的ESP_RETURN_ON_ERROR（）宏版本。
 */
#define ESP_RETURN_ON_ERROR_ISR(x, log_tag, format, ...) do {                                   \
        (void)log_tag;                                                                          \
        esp_err_t err_rc_ = (x);                                                                \
        if (unlikely(err_rc_ != ESP_OK)) {                                                      \
            return err_rc_;                                                                     \
        }                                                                                       \
    } while(0)

/**
 * 可用于检查错误代码的宏。如果代码不是ESP_OK，它将打印消息，将本地变量“ret”设置为代码，然后跳转到“goto_tag”退出。
 */
#define ESP_GOTO_ON_ERROR(x, goto_tag, log_tag, format, ...) do {                               \
        (void)log_tag;                                                                          \
        esp_err_t err_rc_ = (x);                                                                \
        if (unlikely(err_rc_ != ESP_OK)) {                                                      \
            ret = err_rc_;                                                                      \
            goto goto_tag;                                                                      \
        }                                                                                       \
    } while(0)

/**
 * 可以从ISR调用的ESP_GOTO_ON_ERROR（）宏版本。
 */
#define ESP_GOTO_ON_ERROR_ISR(x, goto_tag, log_tag, format, ...) do {                           \
        (void)log_tag;                                                                          \
        esp_err_t err_rc_ = (x);                                                                \
        if (unlikely(err_rc_ != ESP_OK)) {                                                      \
            ret = err_rc_;                                                                      \
            goto goto_tag;                                                                      \
        }                                                                                       \
    } while(0)

/**
 * 可用于检查条件的宏。如果条件不是“true”，则打印消息并返回提供的“err_code”。
 */
#define ESP_RETURN_ON_FALSE(a, err_code, log_tag, format, ...) do {                             \
        (void)log_tag;                                                                          \
        if (unlikely(!(a))) {                                                                   \
            return err_code;                                                                    \
        }                                                                                       \
    } while(0)

/**
 * 可以从ISR调用的ESP_RETURN_ON_FALSE（）宏版本。
 */
#define ESP_RETURN_ON_FALSE_ISR(a, err_code, log_tag, format, ...) do {                         \
        (void)log_tag;                                                                          \
        if (unlikely(!(a))) {                                                                   \
            return err_code;                                                                    \
        }                                                                                       \
    } while(0)

/**
 * 可用于检查条件的宏。如果条件不为“true”，则打印消息，将本地变量“ret”设置为提供的“err_code”，然后跳转到“goto_tag”退出。
 */
#define ESP_GOTO_ON_FALSE(a, err_code, goto_tag, log_tag, format, ...) do {                     \
        (void)log_tag;                                                                          \
        if (unlikely(!(a))) {                                                                   \
            ret = err_code;                                                                     \
            goto goto_tag;                                                                      \
        }                                                                                       \
    } while (0)

/**
 * 可以从ISR调用的ESP_GOTO_ON_FALSE（）宏版本。
 */
#define ESP_GOTO_ON_FALSE_ISR(a, err_code, goto_tag, log_tag, format, ...) do {                 \
        (void)log_tag;                                                                          \
        if (unlikely(!(a))) {                                                                   \
            ret = err_code;                                                                     \
            goto goto_tag;                                                                      \
        }                                                                                       \
    } while (0)

#else // !CONFIG_COMPILER_OPTIMIZATION_CHECKS_SILENT

/**
 * 在未来，我们希望切换到C++20。我们还希望与clang兼容。因此，我们提供了以下宏的两个版本。第一个是使用GNU扩展名\#\#__VA_ARGS__。第二种是使用C++20特性__VA_OPT__（，）。这允许用户使用标准C++20而不是GNU扩展来编译代码。在C++20以下，我们还没有找到使用\#\#__VA_ARGS__的好方法。
 */
#if defined(__cplusplus) && (__cplusplus >  201703L)

/**
 * 可用于检查错误代码的宏。如果代码不是ESP_OK，则打印消息并返回。
 */
#define ESP_RETURN_ON_ERROR(x, log_tag, format, ...) do {                                                  \
        esp_err_t err_rc_ = (x);                                                                           \
        if (unlikely(err_rc_ != ESP_OK)) {                                                                 \
            ESP_LOGE(log_tag, "%s(%d): " format, __FUNCTION__, __LINE__ __VA_OPT__(,) __VA_ARGS__);        \
            return err_rc_;                                                                                \
        }                                                                                                  \
    } while(0)

/**
 * 可以从ISR调用的ESP_RETURN_ON_ERROR（）宏版本。
 */
#define ESP_RETURN_ON_ERROR_ISR(x, log_tag, format, ...) do {                                              \
        esp_err_t err_rc_ = (x);                                                                           \
        if (unlikely(err_rc_ != ESP_OK)) {                                                                 \
            ESP_EARLY_LOGE(log_tag, "%s(%d): " format, __FUNCTION__, __LINE__ __VA_OPT__(,) __VA_ARGS__);  \
            return err_rc_;                                                                                \
        }                                                                                                  \
    } while(0)

/**
 * 可用于检查错误代码的宏。如果代码不是ESP_OK，它将打印消息，将本地变量“ret”设置为代码，然后跳转到“goto_tag”退出。
 */
#define ESP_GOTO_ON_ERROR(x, goto_tag, log_tag, format, ...) do {                                          \
        esp_err_t err_rc_ = (x);                                                                           \
        if (unlikely(err_rc_ != ESP_OK)) {                                                                 \
            ESP_LOGE(log_tag, "%s(%d): " format, __FUNCTION__, __LINE__ __VA_OPT__(,) __VA_ARGS__);        \
            ret = err_rc_;                                                                                 \
            goto goto_tag;                                                                                 \
        }                                                                                                  \
    } while(0)

/**
 * 可以从ISR调用的ESP_GOTO_ON_ERROR（）宏版本。
 */
#define ESP_GOTO_ON_ERROR_ISR(x, goto_tag, log_tag, format, ...) do {                                      \
        esp_err_t err_rc_ = (x);                                                                           \
        if (unlikely(err_rc_ != ESP_OK)) {                                                                 \
            ESP_EARLY_LOGE(log_tag, "%s(%d): " format, __FUNCTION__, __LINE__ __VA_OPT__(,) __VA_ARGS__);  \
            ret = err_rc_;                                                                                 \
            goto goto_tag;                                                                                 \
        }                                                                                                  \
    } while(0)

/**
 * 可用于检查条件的宏。如果条件不是“true”，则打印消息并返回提供的“err_code”。
 */
#define ESP_RETURN_ON_FALSE(a, err_code, log_tag, format, ...) do {                                        \
        if (unlikely(!(a))) {                                                                              \
            ESP_LOGE(log_tag, "%s(%d): " format, __FUNCTION__, __LINE__ __VA_OPT__(,) __VA_ARGS__);        \
            return err_code;                                                                               \
        }                                                                                                  \
    } while(0)

/**
 * 可以从ISR调用的ESP_RETURN_ON_FALSE（）宏版本。
 */
#define ESP_RETURN_ON_FALSE_ISR(a, err_code, log_tag, format, ...) do {                                    \
        if (unlikely(!(a))) {                                                                              \
            ESP_EARLY_LOGE(log_tag, "%s(%d): " format, __FUNCTION__, __LINE__ __VA_OPT__(,) __VA_ARGS__);  \
            return err_code;                                                                               \
        }                                                                                                  \
    } while(0)

/**
 * 可用于检查条件的宏。如果条件不为“true”，则打印消息，将本地变量“ret”设置为提供的“err_code”，然后跳转到“goto_tag”退出。
 */
#define ESP_GOTO_ON_FALSE(a, err_code, goto_tag, log_tag, format, ...) do {                                \
        if (unlikely(!(a))) {                                                                              \
            ESP_LOGE(log_tag, "%s(%d): " format, __FUNCTION__, __LINE__ __VA_OPT__(,) __VA_ARGS__);        \
            ret = err_code;                                                                                \
            goto goto_tag;                                                                                 \
        }                                                                                                  \
    } while (0)

/**
 * 可以从ISR调用的ESP_GOTO_ON_FALSE（）宏版本。
 */
#define ESP_GOTO_ON_FALSE_ISR(a, err_code, goto_tag, log_tag, format, ...) do {                            \
        if (unlikely(!(a))) {                                                                              \
            ESP_EARLY_LOGE(log_tag, "%s(%d): " format, __FUNCTION__, __LINE__ __VA_OPT__(,) __VA_ARGS__);  \
            ret = err_code;                                                                                \
            goto goto_tag;                                                                                 \
        }                                                                                                  \
    } while (0)

#else // !（定义（__cplusplus）&&（__cpplusplus>201703L））

/**
 * 可用于检查错误代码的宏。如果代码不是ESP_OK，则打印消息并返回。
 */
#define ESP_RETURN_ON_ERROR(x, log_tag, format, ...) do {                                       \
        esp_err_t err_rc_ = (x);                                                                \
        if (unlikely(err_rc_ != ESP_OK)) {                                                      \
            ESP_LOGE(log_tag, "%s(%d): " format, __FUNCTION__, __LINE__, ##__VA_ARGS__);        \
            return err_rc_;                                                                     \
        }                                                                                       \
    } while(0)

/**
 * 可以从ISR调用的ESP_RETURN_ON_ERROR（）宏版本。
 */
#define ESP_RETURN_ON_ERROR_ISR(x, log_tag, format, ...) do {                                   \
        esp_err_t err_rc_ = (x);                                                                \
        if (unlikely(err_rc_ != ESP_OK)) {                                                      \
            ESP_EARLY_LOGE(log_tag, "%s(%d): " format, __FUNCTION__, __LINE__, ##__VA_ARGS__);  \
            return err_rc_;                                                                     \
        }                                                                                       \
    } while(0)

/**
 * 可用于检查错误代码的宏。如果代码不是ESP_OK，它将打印消息，将本地变量“ret”设置为代码，然后跳转到“goto_tag”退出。
 */
#define ESP_GOTO_ON_ERROR(x, goto_tag, log_tag, format, ...) do {                               \
        esp_err_t err_rc_ = (x);                                                                \
        if (unlikely(err_rc_ != ESP_OK)) {                                                      \
            ESP_LOGE(log_tag, "%s(%d): " format, __FUNCTION__, __LINE__, ##__VA_ARGS__);        \
            ret = err_rc_;                                                                      \
            goto goto_tag;                                                                      \
        }                                                                                       \
    } while(0)

/**
 * 可以从ISR调用的ESP_GOTO_ON_ERROR（）宏版本。
 */
#define ESP_GOTO_ON_ERROR_ISR(x, goto_tag, log_tag, format, ...) do {                           \
        esp_err_t err_rc_ = (x);                                                                \
        if (unlikely(err_rc_ != ESP_OK)) {                                                      \
            ESP_EARLY_LOGE(log_tag, "%s(%d): " format, __FUNCTION__, __LINE__, ##__VA_ARGS__);  \
            ret = err_rc_;                                                                      \
            goto goto_tag;                                                                      \
        }                                                                                       \
    } while(0)

/**
 * 可用于检查条件的宏。如果条件不是“true”，则打印消息并返回提供的“err_code”。
 */
#define ESP_RETURN_ON_FALSE(a, err_code, log_tag, format, ...) do {                             \
        if (unlikely(!(a))) {                                                                   \
            ESP_LOGE(log_tag, "%s(%d): " format, __FUNCTION__, __LINE__, ##__VA_ARGS__);        \
            return err_code;                                                                    \
        }                                                                                       \
    } while(0)

/**
 * 可以从ISR调用的ESP_RETURN_ON_FALSE（）宏版本。
 */
#define ESP_RETURN_ON_FALSE_ISR(a, err_code, log_tag, format, ...) do {                         \
        if (unlikely(!(a))) {                                                                   \
            ESP_EARLY_LOGE(log_tag, "%s(%d): " format, __FUNCTION__, __LINE__, ##__VA_ARGS__);  \
            return err_code;                                                                    \
        }                                                                                       \
    } while(0)

/**
 * 可用于检查条件的宏。如果条件不为“true”，则打印消息，将本地变量“ret”设置为提供的“err_code”，然后跳转到“goto_tag”退出。
 */
#define ESP_GOTO_ON_FALSE(a, err_code, goto_tag, log_tag, format, ...) do {                     \
        if (unlikely(!(a))) {                                                                   \
            ESP_LOGE(log_tag, "%s(%d): " format, __FUNCTION__, __LINE__, ##__VA_ARGS__);        \
            ret = err_code;                                                                     \
            goto goto_tag;                                                                      \
        }                                                                                       \
    } while (0)

/**
 * 可以从ISR调用的ESP_GOTO_ON_FALSE（）宏版本。
 */
#define ESP_GOTO_ON_FALSE_ISR(a, err_code, goto_tag, log_tag, format, ...) do {                 \
        if (unlikely(!(a))) {                                                                   \
            ESP_EARLY_LOGE(log_tag, "%s(%d): " format, __FUNCTION__, __LINE__, ##__VA_ARGS__);  \
            ret = err_code;                                                                     \
            goto goto_tag;                                                                      \
        }                                                                                       \
    } while (0)

#endif // !（定义（__cplusplus）&&（__cpplusplus>201703L））

#endif // !CONFIG_COMPILER_OPTIMIZATION_CHECKS_SILENT


#ifdef __cplusplus
}
#endif

