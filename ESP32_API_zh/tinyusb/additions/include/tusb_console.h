// 2020浓缩咖啡系统（上海）有限公司版权所有。
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

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_err.h"

/**
 * @brief 将输出重定向到USB串行
 * @param cdc_intf -TinyUSB CDC的接口号
 *
 * @return esp_err_t-esp_OK、esp_FAIL或错误代码
 */
esp_err_t esp_tusb_init_console(int cdc_intf);

/**
 * @brief 将日志切换到默认输出
 * @param cdc_intf -TinyUSB CDC的接口号
 *
 * @return 电子邮箱地址
 */
esp_err_t esp_tusb_deinit_console(int cdc_intf);

#ifdef __cplusplus
}
#endif

