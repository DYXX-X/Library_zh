/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

/**
 * @brief 异步memcpy句柄的类型
 *
 */
typedef struct async_memcpy_context_t *async_memcpy_t;

/**
 * @brief 异步memcpy事件对象的类型
 *
 */
typedef struct {
    void *data; /*!< 事件数据*/
} async_memcpy_event_t;

/**
 * @brief 异步memcpy中断回调函数的类型
 *
 * @param mcp_hdl 异步memcpy的句柄
 * @param event 事件对象，包含相关数据，保留供将来使用
 * @param cb_args 用户定义的参数，从esp_async_memcpy函数传递
 * @return 回调函数是否唤醒高优先级任务
 *
 * @note 用户可以在回调函数中调用OS原语（信号量、互斥量等）。请记住，如果任何OS原语唤醒了高优先级任务，则回调应返回true。
 */
typedef bool (*async_memcpy_isr_cb_t)(async_memcpy_t mcp_hdl, async_memcpy_event_t *event, void *cb_args);

/**
 * @brief 异步memcpy配置的类型
 *
 */
typedef struct {
    uint32_t backlog;          /*!< 可同时处理的最大流数*/
    size_t sram_trans_align;   /*!< SRAM存储器的DMA传输对齐（大小和地址）*/
    size_t psram_trans_align;  /*!< PSRAM内存的DMA传输对齐（大小和地址）*/
    uint32_t flags;            /*!< 控制异步memcpy功能的额外标志*/
} async_memcpy_config_t;

/**
 * @brief 异步memcpy的默认配置
 *
 */
#define ASYNC_MEMCPY_DEFAULT_CONFIG() \
    {                                 \
        .backlog = 8,                 \
        .sram_trans_align = 0,        \
        .psram_trans_align = 0,       \
        .flags = 0,                   \
    }

/**
 * @brief 安装异步memcpy驱动程序
 *
 * @param[in] config 异步内存配置
 * @param[out] asmcp 从此API返回的异步memcpy的句柄。如果驱动程序安装失败，asmcp将被分配为NULL。
 * @return
 *      -ESP_OK:成功安装异步memcpy驱动程序
 *      -ESP_ERR_INVALID_ARG:由于参数无效，安装异步memcpy驱动程序失败
 *      -ESP_ERR_NO_MEM:由于内存不足，安装异步memcpy驱动程序失败
 *      -ESP_FAIL:由于其他错误，安装异步memcpy驱动程序失败
 */
esp_err_t esp_async_memcpy_install(const async_memcpy_config_t *config, async_memcpy_t *asmcp);

/**
 * @brief 卸载异步memcpy驱动程序
 *
 * @param[in] asmcp 从esp_async_memcpy_install返回的异步memcpy驱动程序的句柄
 * @return
 *      -ESP_OK:成功卸载异步memcpy驱动程序
 *      -ESP_ERR_INVALID_ARG:由于参数无效，卸载异步memcpy驱动程序失败
 *      -ESP_FAIL:由于其他错误，卸载异步memcpy驱动程序失败
 */
esp_err_t esp_async_memcpy_uninstall(async_memcpy_t asmcp);

/**
 * @brief 发送异步内存复制请求
 *
 * @param[in] asmcp 从esp_async_memcpy_install返回的异步memcpy驱动程序的句柄
 * @param[in] dst 目标地址（复制到）
 * @param[in] src 源地址（复制自）
 * @param[in] n 要复制的字节数
 * @param[in] cb_isr 在中断上下文中调用的回调函数。设置为NULL可以绕过回调。
 * @param[in] cb_args 要传递给回调函数的用户定义参数
 * @return
 *      -ESP_OK：成功发送内存复制请求
 *      -ESP_ERR_INVALID_ARG:由于参数无效，发送内存复制请求失败
 *      -ESP_FAIL:由于其他错误，发送内存复制请求失败
 *
 * @note 回调函数是在中断上下文中调用的，决不在回调中执行阻塞作业。
 */
esp_err_t esp_async_memcpy(async_memcpy_t asmcp, void *dst, void *src, size_t n, async_memcpy_isr_cb_t cb_isr, void *cb_args);

#ifdef __cplusplus
}
#endif

