// 版权所有2021浓缩咖啡系统（上海）有限公司
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
// 许可证下的限制

#pragma once

#include <stddef.h>
#include <sys/types.h>

#include "esp_err.h"

#define EFD_SUPPORT_ISR (1 << 4)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Eventfd vfs初始化设置
 */
typedef struct {
    size_t max_fds;     /*!< 支持的最大事件数*/
} esp_vfs_eventfd_config_t;

#define ESP_VFS_EVENTD_CONFIG_DEFAULT() (esp_vfs_eventfd_config_t) { \
      .max_fds = 5, \
};

/**
 * @brief  注册事件vfs。
 *
 * @return  如果成功，则ESP_OK；如果注册了太多VFSE，则ESP_ERR_NO_MEM。
 */
esp_err_t esp_vfs_eventfd_register(const esp_vfs_eventfd_config_t *config);

/**
 * @brief  注销事件vfs。
 *
 * @return 如果成功，则ESP_OK；如果尚未注册给定前缀的VFS，则ESP_ERR_INVALID_STATE
 */
esp_err_t esp_vfs_eventfd_unregister(void);

/*
 * @brief 创建事件文件描述符。
 *
 * 读取、写入和选择的行为与未指定EFD_SEMAPHORE的man（2）eventfd相同。添加了新标志EFD_SUPPORT_ISR。此标志是写入中断处理程序中的事件fds所必需的。使用EFD_SUPPORT_ISR访问事件fd的控制块将导致中断被暂时阻止（例如，在读取、写入以及选择的开始和结束期间）。
 *
 * @return 如果成功，则返回文件描述符；如果发生错误，则返回-1。
 */
int eventfd(unsigned int initval, int flags);

#ifdef __cplusplus
}
#endif

