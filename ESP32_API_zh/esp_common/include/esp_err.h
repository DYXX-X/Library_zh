/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include "esp_compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int esp_err_t;

/* 错误常数的定义。*/
#define ESP_OK          0       /*!< esp_err_t值表示成功（无错误）*/
#define ESP_FAIL        -1      /*!< 表示故障的通用esp_err_t代码*/

#define ESP_ERR_NO_MEM              0x101   /*!< 内存不足*/
#define ESP_ERR_INVALID_ARG         0x102   /*!< 参数无效*/
#define ESP_ERR_INVALID_STATE       0x103   /*!< 无效状态*/
#define ESP_ERR_INVALID_SIZE        0x104   /*!< 无效的大小*/
#define ESP_ERR_NOT_FOUND           0x105   /*!< 未找到请求的资源*/
#define ESP_ERR_NOT_SUPPORTED       0x106   /*!< 不支持操作或功能*/
#define ESP_ERR_TIMEOUT             0x107   /*!< 操作超时*/
#define ESP_ERR_INVALID_RESPONSE    0x108   /*!< 收到的响应无效*/
#define ESP_ERR_INVALID_CRC         0x109   /*!< CRC或校验和无效*/
#define ESP_ERR_INVALID_VERSION     0x10A   /*!< 版本无效*/
#define ESP_ERR_INVALID_MAC         0x10B   /*!< MAC地址无效*/
#define ESP_ERR_NOT_FINISHED        0x10C   /*!< 还有个项目需要检索*/


#define ESP_ERR_WIFI_BASE           0x3000  /*!< WiFi错误代码的起始数量*/
#define ESP_ERR_MESH_BASE           0x4000  /*!< MESH错误代码的起始数量*/
#define ESP_ERR_FLASH_BASE          0x6000  /*!< 闪存错误代码的起始数量*/
#define ESP_ERR_HW_CRYPTO_BASE      0xc000  /*!< 硬件加密模块错误代码的起始数量*/
#define ESP_ERR_MEMPROT_BASE        0xd000  /*!< 内存保护API错误代码的起始数量*/

/**
  * @brief 返回esp_err_t错误代码的字符串
  *
  * 此函数在预先生成的查找表中查找错误代码，并返回其字符串表示形式。
  *
  * 该函数由Python脚本工具/gen_esp_err_to_name生成。py，每次修改、创建或从IDF项目中删除esp_err_t错误时都应运行该命令。
  *
  * @param code esp_err_t错误代码
  * @return 字符串错误消息
  */
const char *esp_err_to_name(esp_err_t code);

/**
  * @brief 返回esp_err_t和系统错误代码的字符串
  *
  * 此函数在预先生成的esp_err_t错误查找表中查找错误代码，并返回其字符串表示形式。如果未找到错误代码，则尝试在系统错误中找到该错误代码。
  *
  * 该函数由Python脚本工具/gen_esp_err_to_name生成。py，每次修改、创建或从IDF项目中删除esp_err_t错误时都应运行该命令。
  *
  * @param code esp_err_t错误代码
  * @param[out] buf 应写入错误消息的缓冲区
  * @param buflen 缓冲区缓冲区大小。最多将buflen字节写入buf缓冲区（包括终止的空字节）。
  * @return 包含字符串错误消息的buf
  */
const char *esp_err_to_name_r(esp_err_t code, char *buf, size_t buflen);

/**@秒*/
void _esp_error_check_failed(esp_err_t rc, const char *file, int line, const char *function, const char *expression) __attribute__((noreturn));

/**@秒*/
void _esp_error_check_failed_without_abort(esp_err_t rc, const char *file, int line, const char *function, const char *expression);

#ifndef __ASSERT_FUNC
/* 这不会发生在IDF上，IDF在断言中定义__ASSERT_FUNC。h、 但在使用/usr/include/assert的主机上构建时确实会发生这种情况。h或等效值。
*/
#ifdef __ASSERT_FUNCTION
#define __ASSERT_FUNC __ASSERT_FUNCTION /* 在glibc断言中使用。小时*/
#else
#define __ASSERT_FUNC "??"
#endif
#endif
/**@结束秒*/

/**
 * 可用于检查错误代码的宏，如果代码不是ESP_OK，则终止程序。将错误代码、错误位置和失败语句打印到串行输出。
 *
 * 如果断言被禁用，则禁用。
 */
#ifdef NDEBUG
#define ESP_ERROR_CHECK(x) do {                                         \
        esp_err_t err_rc_ = (x);                                        \
        (void) sizeof(err_rc_);                                         \
    } while(0)
#elif defined(CONFIG_COMPILER_OPTIMIZATION_ASSERTIONS_SILENT)
#define ESP_ERROR_CHECK(x) do {                                         \
        esp_err_t err_rc_ = (x);                                        \
        if (unlikely(err_rc_ != ESP_OK)) {                              \
            abort();                                                    \
        }                                                               \
    } while(0)
#else
#define ESP_ERROR_CHECK(x) do {                                         \
        esp_err_t err_rc_ = (x);                                        \
        if (unlikely(err_rc_ != ESP_OK)) {                              \
            _esp_error_check_failed(err_rc_, __FILE__, __LINE__,        \
                                    __ASSERT_FUNC, #x);                 \
        }                                                               \
    } while(0)
#endif

/**
 * 可用于检查错误代码的宏。将错误代码、错误位置和失败语句打印到串行输出。与ESP_ERROR_CHECK（）相比，这将打印相同的错误消息，但不会终止程序。
 */
#if defined NDEBUG || defined CONFIG_COMPILER_OPTIMIZATION_ASSERTIONS_SILENT
#define ESP_ERROR_CHECK_WITHOUT_ABORT(x) ({                                         \
        esp_err_t err_rc_ = (x);                                                    \
        err_rc_;                                                                    \
    })
#else
#define ESP_ERROR_CHECK_WITHOUT_ABORT(x) ({                                         \
        esp_err_t err_rc_ = (x);                                                    \
        if (unlikely(err_rc_ != ESP_OK)) {                                          \
            _esp_error_check_failed_without_abort(err_rc_, __FILE__, __LINE__,      \
                                                  __ASSERT_FUNC, #x);               \
        }                                                                           \
        err_rc_;                                                                    \
    })
#endif //NDEBUG

#ifdef __cplusplus
}
#endif

