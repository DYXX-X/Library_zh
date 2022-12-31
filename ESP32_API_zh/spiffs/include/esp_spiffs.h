// 版权所有2015-2017 Espressif Systems（上海）私人有限公司
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

#ifndef _ESP_SPIFFS_H_
#define _ESP_SPIFFS_H_

#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief esp_vfs_spiffs_register的配置结构
 */
typedef struct {
        const char* base_path;          /*!< 与文件系统关联的文件路径前缀。*/
        const char* partition_label;    /*!< 可选，要使用的SPIFFS分区的标签。如果设置为NULL，将使用subtype=spiffs的第一个分区。*/
        size_t max_files;               /*!< 同时可以打开的最大文件数。*/
        bool format_if_mount_failed;    /*!< 如果为true，则在装载失败时将格式化文件系统。*/
} esp_vfs_spiffs_conf_t;

/**
 * 使用给定的路径前缀将SPIFFS注册并安装到VFS。
 *
 * @param   conf                      指向esp_vfs_spiffs_conf_t配置结构的指针
 *
 * @return
 *          -ESP_OK（如果成功）
 *          -如果无法分配对象，则为ESP_ERR_NO_MEM
 *          -ESP_ERR_INVALID_STATE（如果已装载或分区已加密）
 *          -如果未找到SPIFFS的分区，则为ESP_ERR_NOT_FOUND
 *          -如果装载或格式化失败，则返回ESP_FAIL
 */
esp_err_t esp_vfs_spiffs_register(const esp_vfs_spiffs_conf_t * conf);

/**
 * 从VFS注销并卸载SPIFFS
 *
 * @param partition_label  与传递给esp_vfs_spiffs_register的标签相同。
 *
 * @return
 *          -ESP_OK（如果成功）
 *          -ESP_ERR_INVALID_STATE已注销
 */
esp_err_t esp_vfs_spiffs_unregister(const char* partition_label);

/**
 * 检查是否安装了SPIFFS
 *
 * @param partition_label  可选，要检查的分区的标签。如果未指定，则使用subtype=spiffs的第一个分区。
 *
 * @return
 *          -如果已安装，则为true
 *          -如果未安装，则为false
 */
bool esp_spiffs_mounted(const char* partition_label);

/**
 * 设置SPIFFS分区的格式
 *
 * @param partition_label  与传递给esp_vfs_spiffs_register的标签相同。
 * @return
 *          -ESP_OK（如果成功）
 *          -ESP_FAIL出错
 */
esp_err_t esp_spiffs_format(const char* partition_label);

/**
 * 获取SPIFFS信息
 *
 * @param partition_label           与传递给esp_vfs_spiffs_register的标签相同
 * @param[out] total_bytes          文件系统的大小
 * @param[out] used_bytes           文件系统中当前使用的字节数
 *
 * @return
 *          -ESP_OK（如果成功）
 *          -ESP_ERR_INVALID_STATE（如果未安装）
 */
esp_err_t esp_spiffs_info(const char* partition_label, size_t *total_bytes, size_t *used_bytes);

#ifdef __cplusplus
}
#endif

#endif /* _ESP_SPIFFS_H_ */

