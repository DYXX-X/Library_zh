/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _ESP_BLE_MESH_LOCAL_DATA_OPERATION_API_H_
#define _ESP_BLE_MESH_LOCAL_DATA_OPERATION_API_H_

#include "esp_ble_mesh_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief         获取模型发布周期，单位为毫秒。
 *
 * @param[in]     model: 模型实例指针。
 *
 * @return        成功时发布周期值，0或错误号中的（负）错误代码。h故障。
 *
 */
int32_t esp_ble_mesh_get_model_publish_period(esp_ble_mesh_model_t *model);

/**
 * @brief         获取主元素的地址。
 *
 * @return        成功时主元素的地址，或失败时ESP_BLE_MESH_ADDR_NASSIGNED，这意味着尚未配置设备。
 *
 */
uint16_t esp_ble_mesh_get_primary_element_address(void);

/**
 * @brief         检查型号是否订阅了给定的组地址。注意：例如，一旦接收到状态消息并且目标地址是组地址，模型就会使用此API来检查是否成功订阅了给定的组地址。
 *
 * @param[in]     model: 指向模型的指针。
 * @param[in]     group_addr: 组地址。
 *
 * @return        成功时指向模型订阅列表中的组地址的指针，失败时指向NULL，这意味着模型尚未订阅给定的组地址。注意：返回组地址的指针后，您可以将组地址重置为0x0000，以便从组中取消订阅该型号。
 *
 */
uint16_t *esp_ble_mesh_is_model_subscribed_to_group(esp_ble_mesh_model_t *model,
                                                    uint16_t group_addr);

/**
 * @brief         通过元素地址查找BLE Mesh元素指针。
 *
 * @param[in]     element_addr: 元素地址。
 *
 * @return        成功时指向元素的指针，失败时指向NULL。
 *
 */
esp_ble_mesh_elem_t *esp_ble_mesh_find_element(uint16_t element_addr);

/**
 * @brief         获取已注册的元素数。
 *
 * @return        元素数量。
 *
 */
uint8_t esp_ble_mesh_get_element_count(void);

/**
 * @brief        使用给定元素、公司ID和供应商型号ID查找特定于供应商的型号。
 *
 * @param[in]    element: 模型所属的元素。
 * @param[in]    company_id: 蓝牙SIG分配的16位公司标识符。
 * @param[in]    model_id: 16位供应商分配的型号标识符。
 *
 * @return       成功时指向供应商模型的指针，失败时指向NULL，这意味着找不到供应商模型。
 *
 */
esp_ble_mesh_model_t *esp_ble_mesh_find_vendor_model(const esp_ble_mesh_elem_t *element,
                                                     uint16_t company_id, uint16_t model_id);

/**
 * @brief        查找具有给定元素和模型id的SIG模型。
 *
 * @param[in]    element: 模型所属的元素。
 * @param[in]    model_id: SIG型号标识符。
 *
 * @return       成功时指向SIG模型的指针，失败时指向NULL，这意味着找不到SIG模型。
 *
 */
esp_ble_mesh_model_t *esp_ble_mesh_find_sig_model(const esp_ble_mesh_elem_t *element,
                                                  uint16_t model_id);

/**
 * @brief        获取已注册的合成数据。
 *
 * @return       成功时指向合成数据的指针，失败时指向NULL，这意味着合成数据未初始化。
 *
 */
const esp_ble_mesh_comp_t *esp_ble_mesh_get_composition_data(void);

/**
 * @brief        节点或配置器的本地模型订阅组地址。
 *
 * @note         在配置节点或启用配置程序之前，不得调用此功能。
 *
 * @param[in]    element_addr: 模型所属元素的单播地址。
 * @param[in]    company_id: 16位公司标识符。
 * @param[in]    model_id: 16位型号标识符。
 * @param[in]    group_addr: 要订阅的组地址。
 *
 * @return       成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_model_subscribe_group_addr(uint16_t element_addr, uint16_t company_id,
                                                  uint16_t model_id, uint16_t group_addr);

/**
 * @brief        节点或提供程序的本地模型取消订阅组地址。
 *
 * @note         在配置节点或启用配置程序之前，不得调用此功能。
 *
 * @param[in]    element_addr: 模型所属元素的单播地址。
 * @param[in]    company_id: 16位公司标识符。
 * @param[in]    model_id: 16位型号标识符。
 * @param[in]    group_addr: 订阅的组地址。
 *
 * @return       成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_model_unsubscribe_group_addr(uint16_t element_addr, uint16_t company_id,
                                                    uint16_t model_id, uint16_t group_addr);

/**
 * @brief         Node调用此函数以获取本地NetKey。
 *
 * @param[in]     net_idx: NetKey索引。
 *
 * @return        成功时为NetKey，失败时为NULL。
 *
 */
const uint8_t *esp_ble_mesh_node_get_local_net_key(uint16_t net_idx);

/**
 * @brief         Node调用此函数以获取本地AppKey。
 *
 * @param[in]     app_idx: AppKey索引。
 *
 * @return        成功时为AppKey，失败时为NULL。
 *
 */
const uint8_t *esp_ble_mesh_node_get_local_app_key(uint16_t app_idx);

/**
 * @brief         节点调用此函数以添加本地NetKey。
 *
 * @param[in]     net_key: 要添加的NetKey。
 * @param[in]     net_idx: NetKey索引。
 *
 * @note          只有在配置设备后才能调用此功能。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_node_add_local_net_key(const uint8_t net_key[16], uint16_t net_idx);

/**
 * @brief         Node调用此函数以添加本地AppKey。
 *
 * @param[in]     app_key: 要添加的AppKey。
 * @param[in]     net_idx: NetKey索引。
 * @param[in]     app_idx: AppKey索引。
 *
 * @note          net_idx必须是现有的。只有在配置设备后才能调用此功能。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_node_add_local_app_key(const uint8_t app_key[16], uint16_t net_idx, uint16_t app_idx);

/**
 * @brief         Node调用此函数将AppKey绑定到本地模型。
 *
 * @param[in]     element_addr: 节点本地元素地址
 * @param[in]     company_id: 节点本地公司id
 * @param[in]     model_id: 节点本地模型id
 * @param[in]     app_idx: 节点本地appkey索引
 *
 * @note          如果要将app_key与本地供应商模型绑定，则company_id应设置为0xFFFF。只有在配置设备后才能调用此功能。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_node_bind_app_key_to_local_model(uint16_t element_addr, uint16_t company_id,
                                                        uint16_t model_id, uint16_t app_idx);

#ifdef __cplusplus
}
#endif

#endif /* _ESP_BLE_MESH_LOCAL_DATA_OPERATION_API_H_ */

