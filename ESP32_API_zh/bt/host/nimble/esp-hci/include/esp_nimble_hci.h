/*
 * 版权所有2019 Espressif Systems（上海）私人有限公司
 *
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef __ESP_NIMBLE_HCI_H__
#define __ESP_NIMBLE_HCI_H__

#include "nimble/ble_hci_trans.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BLE_HCI_UART_H4_NONE        0x00
#define BLE_HCI_UART_H4_CMD         0x01
#define BLE_HCI_UART_H4_ACL         0x02
#define BLE_HCI_UART_H4_SCO         0x03
#define BLE_HCI_UART_H4_EVT         0x04

/**
 * @brief 初始化NimBLE主机和ESP蓝牙控制器之间的VHCI传输层
 *
 * 此函数初始化要在NimBLE主机和ESP控制器之间交换的传输缓冲区。它还向控制器注册所需的主机回调。
 *
 * @return
 *    -ESP_OK（如果初始化成功）
 *    -出现错误时，esp_err_t中的相应错误代码
 */
esp_err_t esp_nimble_hci_init(void);

/**
 * @brief 初始化NimBLE主机和ESP蓝牙控制器之间的ESP蓝牙控制器（链路层）和VHCI传输层
 *
 * 此功能将ESP控制器初始化为仅BLE模式，并在NimBLE主机和ESP控制器之间交换传输缓冲区。它还向控制器注册所需的主机回调。
 *
 * 以下是初始化/启用NimBLE主机和ESP控制器所需的API序列：
 *
 * @code{c}
 * void ble_host_task（void*param）
 * {
 *      nimble_port_run（）//此函数仅在执行nimble_port_stop（）时返回。
 *      nimble_port_freertos_deinit（）；
 * }
 *
 * int ret=esp_nimble_hci_and_controller_init（）；
 * 如果（ret！=ESP_OK）{
        ESP_LOGE（标记，“ESP_nimble_hci_and_controller_init（）失败，错误：%d”，ret）；
 *      回来
 * }
 *
 * nimble_port_init（）；
 *
 * //初始化NimBLE主机配置
 *
 * nimble_port_freertos_init（ble_host_task）；
 * @endcode
 *
 * nimble_port_freertos_init（）是一个可选调用，用于创建一个新任务，nimble主机将在其中运行。任务函数应该调用nimble_port_run（）。如果不需要单独的任务，则调用nimble_port_run（）将在当前任务中运行nimble主机。
 *
 * @return
 *    -ESP_OK（如果初始化成功）
 *    -出现错误时，esp_err_t中的相应错误代码
 */
esp_err_t esp_nimble_hci_and_controller_init(void);

/**
 * @brief 取消初始化NimBLE主机和ESP蓝牙控制器之间的VHCI传输层
 *
 * @note 应在NimBLE主机取消初始化后调用此函数。
 *
 * @return
 *    -ESP_OK（如果取消初始化成功）
 *    -出现错误时，esp_err_t中的相应错误代码
 */
esp_err_t esp_nimble_hci_deinit(void);

/**
 * @brief 取消初始化NimBLE主机和ESP蓝牙控制器之间的VHCI传输层，并禁用和取消初始化控制器
 *
 * @note 此功能不应在蓝牙主机任务的上下文中执行。
 *
 * @note 应在NimBLE主机取消初始化后调用此函数。
 *
 * 以下是要调用的API序列，以禁用/卸载NimBLE主机和ESP控制器：
 *
 * @code{c}
 * int ret=nimble_port_stop（）；
 * 如果（ret==0）{
 *      nimble_port_deinit（）；
 *
 *      ret=esp_nimble_hci_and_controller_deinit（）；
 *      如果（ret！=ESP_OK）{
            ESP_LOGE（标记，“ESP_nimble_hci_and_controller_deinit（）失败，错误为：%d”，ret）；
 *      }
 * }
 * @endcode
 *
 * 如果在初始化期间使用了nimble_port_freertos_init（），则应在主机任务中在nimble_port _run（）之后调用nimble_pport_freertos _deinit（）。
 *
 * @return
 *    -ESP_OK（如果取消初始化成功）
 *    -出现错误时，esp_err_t中的相应错误代码
 */
esp_err_t esp_nimble_hci_and_controller_deinit(void);

#ifdef __cplusplus
}
#endif

#endif /* __ESP_NIMBLE_HCI_H__ */

