/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdlib.h>
#include <stdint.h>
#include "esp_err.h"
#include "usb_private.h"
#include "usbh.h"

#ifdef __cplusplus
extern "C" {
#endif

// ------------------------------------------------------类型--------------------------------------------------------

/**
 * @brief 集线器驱动程序配置
 */
typedef struct {
    usb_notif_cb_t notif_cb;            /**<通知回调*/
    void *notif_cb_arg;                 /**<通知回调参数*/
} hub_config_t;

// ----------------------------------------------集线器驱动程序功能-------------------------------------------------

/**
 * @brief 安装集线器驱动程序
 *
 * 条目：
 * -必须已安装USBH退出：
 * -安装集线器驱动程序内存资源
 * -初始化HCD根端口
 *
 * @param[in] hub_config 集线器驱动程序配置
 * @return 电子邮箱地址
 */
esp_err_t hub_install(hub_config_t *hub_config);

/**
 * @brief 卸载集线器驱动程序
 *
 * 在卸载USBH条目之前，必须调用此命令：
 * -必须已停止根端口退出：
 * -HCD根端口已取消初始化
 *
 * @return 电子邮箱地址
 */
esp_err_t hub_uninstall(void);

/**
 * @brief 启动集线器驱动程序的根端口
 *
 * 这将为根端口通电
 *
 * @return 电子邮箱地址
 */
esp_err_t hub_root_start(void);

/**
 * @brief 停止集线器驱动程序的根端口
 *
 * 这将关闭根端口的电源
 *
 * @return 电子邮箱地址
 */
esp_err_t hub_root_stop(void);

/**
 * @brief 集线器驱动程序的处理功能
 *
 * 必须重复调用集线器驱动程序处理功能以处理集线器驱动程序的事件。如果阻塞，则调用者可以阻塞源USB_NOTIF_source_HUB的通知回调以运行此函数。
 *
 * @return 电子邮箱地址
 */
esp_err_t hub_process(void);

#ifdef __cplusplus
}
#endif

