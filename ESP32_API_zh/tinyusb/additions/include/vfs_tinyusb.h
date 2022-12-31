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

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 使用路径在VFS注册TinyUSB CDC
 * @param cdc_intf -TinyUSB CDC的接口号
 * @param path -CDC将注册的路径，如果保留为NULL，将使用“/dev/tusb_CDC”。
 *
 * @return esp_err_t esp_OK或esp_FAIL
 */
esp_err_t esp_vfs_tusb_cdc_register(int cdc_intf, char const *path);

/**
 * @brief 从VFS注销TinyUSB CDC
 * @param path -如果使用NULL，CDC将被注销的路径`/dev/tusb_CDC`
 *
 * @return esp_err_t esp_OK或esp_FAIL
 */
esp_err_t esp_vfs_tusb_cdc_unregister(char const *path);

#ifdef __cplusplus
}
#endif

