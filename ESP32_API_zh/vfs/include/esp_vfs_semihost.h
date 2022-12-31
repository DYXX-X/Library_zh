// 版权所有2019 Espressif Systems（上海）私人有限公司
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

#include "esp_vfs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 添加虚拟文件系统半宿主驱动程序
 *
 * @param base_path 装载主机目录的VFS路径
 * @param host_path 要装载的主机路径；如果将使用NULL默认目录（请参阅OpenOCD配置）
 * @return
 *      -成功时ESP_OK
 *      -如果已为指定的vfs路径调用ESP_vfs_semihost_register，则为ESP_ERR_INVALID_ARG
 *      -如果没有用于注册新装载点的插槽，则为ESP_ERR_NO_MEM
 */
esp_err_t esp_vfs_semihost_register(const char* base_path, const char* host_path);

/**
 * @brief 从VFS中取消注册半宿主驱动程序
 *
 * @return
 *      -成功时ESP_OK
 *      -ESP_ERR_INVALID_ARG，如果半托管驱动程序未在该路径的VFS中注册
 */
esp_err_t esp_vfs_semihost_unregister(const char* base_path);

#ifdef __cplusplus
}
#endif

