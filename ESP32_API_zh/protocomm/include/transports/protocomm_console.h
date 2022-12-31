// 版权所有2018 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#pragma once

#include <protocomm.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PROTOCOMM_CONSOLE_DEFAULT_CONFIG() { \
    .stack_size     = 4096,                  \
    .task_priority  = tskIDLE_PRIORITY + 3,  \
}

/**
 * @brief   protocomm控制台的配置参数
 */
typedef struct {
    size_t   stack_size;        /*!< 控制台任务的堆栈大小*/
    unsigned task_priority;     /*!< 控制台任务的优先级*/
} protocomm_console_config_t;

/**
 * @brief   启动基于控制台的协议通信传输
 *
 * @note    这是一个单例。即Protocomm可以有多个实例，但只有一个实例可以绑定到基于控制台的传输层。
 *
 * @param[in] pc     从Protocomm_new（）获取的Protocomm实例指针
 * @param[in] config 协议通信控制台的配置参数结构
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_ERR_INVALID_ARG:空参数
 *  -ESP_ERR_NOT_SUPPORTED：传输层绑定到另一个协议命令实例
 *  -ESP_ERR_INVALID_STATE:传输层已绑定到此协议命令实例
 *  -ESP_FAIL:无法启动控制台线程
 */
esp_err_t protocomm_console_start(protocomm_t *pc, const protocomm_console_config_t *config);

/**
 * @brief   停止控制台协议通信传输
 *
 * @param[in] pc    传递给protocomm_console_start（）的相同protocomm实例
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_ERR_INVALID_ARG:空/不正确的协议命令实例指针
 */
esp_err_t protocomm_console_stop(protocomm_t *pc);

#ifdef __cplusplus
}
#endif

