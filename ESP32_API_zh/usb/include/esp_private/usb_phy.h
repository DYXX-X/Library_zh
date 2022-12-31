/*
 * SPDX文件版权所有文本：2015-2022 Espressif Systems（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "soc/soc_caps.h"
#include "hal/usb_phy_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief USB PHY状态
 */
typedef enum {
    USB_PHY_STATUS_FREE,             /**<未使用PHY*/
    USB_PHY_STATUS_IN_USE,           /**<PHY正在使用*/
} usb_phy_status_t;

/**
 * @brief USB PHY可用操作
 */
typedef enum {
    USB_PHY_ACTION_HOST_ALLOW_CONN,             /**<作为OTG主机运行时启用物理连接*/
    USB_PHY_ACTION_HOST_FORCE_DISCONN,          /**<作为OTG主机运行时禁用物理连接*/
    USB_PHY_ACTION_MAX,
} usb_phy_action_t;

/**
 * @brief USB外部PHY iopin配置结构
 */
typedef struct {
    int vp_io_num;             /**<GPIO引脚至USB_EXTPHY_VP_IDX*/
    int vm_io_num;             /**<GPIO引脚至USB_EXTPHY_VM_IDX*/
    int rcv_io_num;            /**<GPIO引脚至USB_EXTPHY_RCV_IDX*/
    int oen_io_num;            /**<GPIO引脚至USB_EXTPHY_OEN_IDX*/
    int vpo_io_num;            /**<GPIO引脚至USB_EXTPHY_VPO_IDX*/
    int vmo_io_num;            /**<GPIO引脚至USB_EXTPHY_VMO_IDX*/
} usb_phy_gpio_conf_t;

/**
 * @brief USB PHY配置结构
 *
 * 至少必须初始化PHY控制器和PHY目标。
 */
typedef struct {
    usb_phy_controller_t controller;    /**<USB PHY控制器*/
    usb_phy_target_t target;            /**<USB PHY目标INT/EXT*/
    usb_otg_mode_t otg_mode;            /**<USB OTG模式*/
    usb_phy_speed_t otg_speed;          /**<USB OTG速度*/
    usb_phy_gpio_conf_t *gpio_conf;     /**<USB外部PHY iopin配置*/
} usb_phy_config_t;

typedef struct phy_context_t *usb_phy_handle_t;    /**<USB PHY上下文句柄*/

/**
 * @brief 初始化新的USB PHY至少配置PHY源。
 *
 * 此功能将启用OTG控制器
 *
 * @param[in] config USB PHY配置结构
 * @param[out] handle_ret USB PHY上下文句柄
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL USB PHY初始化错误。
 *     -未安装ESP_ERR_INVALID_STATE USB PHY。
 *     -由于没有内存，ESP_ERR_NO_MEM USB_OTG安装失败。
 */
esp_err_t usb_new_phy(const usb_phy_config_t *config, usb_phy_handle_t *handle_ret);

/**
 * @brief 为USB PHY配置OTG模式
 *
 * @param handle USB PHY上下文句柄指针
 * @param mode USB OTG模式
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误。
 *     -ESP_FAIL OTG设置模式失败。
 */
esp_err_t usb_phy_otg_set_mode(usb_phy_handle_t handle, usb_otg_mode_t mode);

/**
 * @brief 为作为OTG设备运行的USB PHY配置USB速度
 *
 * @param handle USB PHY上下文句柄指针
 * @param mode USB速度
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误。
 *     -ESP_FAIL OTG设置速度失败。
 */
esp_err_t usb_phy_otg_dev_set_speed(usb_phy_handle_t handle, usb_phy_speed_t speed);

/**
 * @brief 为USB PHY采取行动
 *
 * @param handle USB PHY上下文句柄指针
 * @param action USB PHY动作
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误。
 *     -无法执行ESP_FAIL操作。
 */
esp_err_t usb_phy_action(usb_phy_handle_t handle, usb_phy_action_t action);

/**
 * @brief 删除USB PHY
 *
 * @param handle USB PHY上下文句柄指针
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误。
 */
esp_err_t usb_del_phy(usb_phy_handle_t handle);

/**
 * @brief 获取USB PHY的状态
 *
 * @param[in] target 要检查的特定PHY目标
 * @param[out] status PHY的状态
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误。
 *     -未安装ESP_ERR_INVALID_STATE USB PHY。
 */
esp_err_t usb_phy_get_phy_status(usb_phy_target_t target, usb_phy_status_t *status);

#ifdef __cplusplus
}
#endif

