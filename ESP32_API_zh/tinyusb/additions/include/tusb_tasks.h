// 版权所有2020 Espressif Systems（上海）私人有限公司
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

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 此助手函数创建并启动一个包装“tud_task（）”的任务。
 *
 * 包装器函数基本上包装tud_task和一些日志。默认参数：堆栈大小和配置的优先级，参数=NULL，不固定到任何核心。如果您对此任务有更多要求，可以创建自己的任务，该任务调用tud_task作为最后一步。
 *
 * @retval ESP_OK成功运行tinyusb主任务
 * @retval 由于内部错误，ESP_FAIL运行tinyusb主任务失败
 * @retval ESP_ERR_INVALID_STATE tinyusb主任务之前已创建
 */
esp_err_t tusb_run_task(void);

/**
 * @brief 此助手函数停止并销毁由`tusb_run_task（）创建的任务`
 *
 * @retval ESP_OK停止和卸载tinyusb主任务成功
 * @retval ESP_ERR_INVALID_STATE tinyusb主任务尚未创建
 */
esp_err_t tusb_stop_task(void);

#ifdef __cplusplus
}
#endif

