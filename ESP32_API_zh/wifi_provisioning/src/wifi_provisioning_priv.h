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

#include <protocomm.h>
#include <protocomm_security.h>

#include "wifi_provisioning/manager.h"
#include "wifi_provisioning/wifi_config.h"
#include "wifi_provisioning/wifi_scan.h"

/**
 * @brief   通知管理员已完成配置
 *
 * 停止配置。当状态为连接时，get_status_handler（）将调用此函数。如果主应用程序通过调用wifi_prov_mgr_disable_auto_stop（）禁用了完成时自动停止，则此操作无效
 *
 * @return
 *  -ESP_OK:将停止设置
 *  -ESP_FAIL:无法停止设置
 */
esp_err_t wifi_prov_mgr_done(void);

/**
 * @brief   启动Wi-Fi AP扫描
 *
 * @param[in] blocking        设置为true，仅在扫描完成后返回
 * @param[in] passive         设置为true以执行被动扫描而不是默认的主动扫描
 * @param[in] group_channels  一次扫描的频道数（设置为0可一次扫描所有频道）
 * @param[in] period_ms       每个通道的扫描时间（毫秒）
 *
 * @return
 *  -ESP_OK:已成功启动Wi-Fi扫描
 *  -ESP_FAIL:设置应用程序未运行
 */
esp_err_t wifi_prov_mgr_wifi_scan_start(bool blocking, bool passive,
                                        uint8_t group_channels,
                                        uint32_t period_ms);

/**
 * @brief   用于查询Wi-Fi扫描的状态
 *
 * @return
 *  -true:扫描完成
 *  -false:扫描正在运行
 */
bool wifi_prov_mgr_wifi_scan_finished(void);

/**
 * @brief   获取扫描列表中的结果计数
 *
 * @return
 *  -count：扫描时检测到的Wi-Fi接入点数
 */
uint16_t wifi_prov_mgr_wifi_scan_result_count(void);

/**
 * @brief   获取扫描列表结果中特定索引的AP记录
 *
 * @param[out] index  要获取的结果的索引
 *
 * @return
 *  -result:指向访问点记录的指针
 */
const wifi_ap_record_t *wifi_prov_mgr_wifi_scan_result(uint16_t index);

/**
 * @brief   获取wifi_config配置终结点的protocomm处理程序
 *
 * @param[out] ptr   指向要设置的结构的指针
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_ERR_INVALID_ARG：空参数
 */
esp_err_t get_wifi_prov_handlers(wifi_prov_config_handlers_t *ptr);

/**
 * @brief   获取wifi_scan配置终结点的protocomm处理程序
 *
 * @param[out] ptr   指向要设置的结构的指针
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_ERR_INVALID_ARG：空参数
 */
esp_err_t get_wifi_scan_handlers(wifi_prov_scan_handlers_t *ptr);

