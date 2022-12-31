/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _ESP_BLE_MESH_PROVISIONING_API_H_
#define _ESP_BLE_MESH_PROVISIONING_API_H_

#include "esp_ble_mesh_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief: 事件、供应事件的事件代码；param，配置事件的参数*/
typedef void (* esp_ble_mesh_prov_cb_t)(esp_ble_mesh_prov_cb_event_t event,
                                        esp_ble_mesh_prov_cb_param_t *param);

/**
 * @brief         注册BLE Mesh配置回调。
 *
 * @param[in]     callback: 指向回调函数的指针。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_register_prov_callback(esp_ble_mesh_prov_cb_t callback);

/**
 * @brief         检查是否已配置设备。
 *
 * @return        如果设备已设置，则为TRUE；如果设备未设置，则返回FALSE。
 *
 */
bool esp_ble_mesh_node_is_provisioned(void);

/**
 * @brief         启用特定的配置承载以使设备准备好进行配置。
 *
 * @note          PB-ADV：发送未设置的设备信标。PB-GATT：发送可连接的广告包。
 *
 * @param         bearers: 配置承载的逐位OR。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_node_prov_enable(esp_ble_mesh_prov_bearer_t bearers);

/**
 * @brief         禁用特定的配置承载，以使设备无法进行配置。
 *
 * @param         bearers: 配置承载的逐位OR。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_node_prov_disable(esp_ble_mesh_prov_bearer_t bearers);

/**
 * @brief        未设置的设备设置自己的oob公钥和私钥对。
 *
 * @note         为了避免遭受暴力攻击（CVE-2020-26559）。蓝牙SIG建议潜在易受攻击的网格提供器使用带外机制来交换公钥。因此，作为未配置的设备，它应该使用此功能输入通过带外机制交换的公钥。
 *
 * @param[in]    pub_key_x:   未设置设备的公钥X
 * @param[in]    pub_key_y:   未设置设备的公钥Y
 * @param[in]    private_key: 未设置设备的私钥
 *
 * @return       成功时返回ESP_OK，否则返回错误代码。
 */
esp_err_t esp_ble_mesh_node_set_oob_pub_key(uint8_t pub_key_x[32], uint8_t pub_key_y[32],
                                            uint8_t private_key[32]);

/**
 * @brief        提供供应输入OOB编号。
 *
 * @note         如果用户已接收到ESP_BLE_MESH_NODE_PROV_INPUT_EVT，且ESP_BLE_MESH_ENDER_NUMBER作为动作，则将调用此命令。
 *
 * @param[in]    number: 设备输入的数字。
 *
 * @return       成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_node_input_number(uint32_t number);

/**
 * @brief        提供配置输入OOB字符串。
 *
 * @note         如果用户已接收到ESP_BLE_MESH_NODE_PROV_INPUT_EVT，且ESP_BLE_MESH_ENTER_STRING作为动作，则将调用此命令。
 *
 * @param[in]    string: 设备输入的字符串。
 *
 * @return       成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_node_input_string(const char *string);

/**
 * @brief        使用此功能，未配置的设备可以设置自己的设备名称，该名称将在其广告数据中广播。
 *
 * @param[in]    name: 未设置的设备名称
 *
 * @note         此API仅通过设置扫描响应数据的名称而适用于PB-GATT模式，不适用于PB-ADV模式。
 *
 * @return       成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_set_unprovisioned_device_name(const char *name);

/**
 * @brief        配置者输入未配置设备的oob公钥。
 *
 * @note         为了避免遭受暴力攻击（CVE-2020-26559）。蓝牙SIG建议潜在易受攻击的网格提供器使用带外机制来交换公钥。
 *
 * @param[in]    link_idx:   配置链接索引
 * @param[in]    pub_key_x:  未设置设备的公钥X
 * @param[in]    pub_key_y:  未设置设备的公钥Y
 *
 * @return       成功时返回ESP_OK，否则返回错误代码。
 */
esp_err_t esp_ble_mesh_provisioner_read_oob_pub_key(uint8_t link_idx, uint8_t pub_key_x[32],
                                                    uint8_t pub_key_y[32]);

/**
 * @brief        提供配置输入OOB字符串。
 *
 *               这是在使用esp_ble_mesh_ENTER_STRING作为操作调用esp_ble_mesh_prov_t prov_input_num回调后调用的。
 *
 * @param[in]    string:   Provisioner输入的字符串。
 * @param[in]    link_idx: 设置链接索引。
 *
 * @return       成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_provisioner_input_string(const char *string, uint8_t link_idx);

/**
 * @brief        提供供应输入OOB编号。
 *
 *               这是在使用esp_ble_mesh_ENTER_NUMBER作为操作调用esp_ble_mesh_prov_t prov_input_num回调后调用的。
 *
 * @param[in]    number:   Provisioner输入的编号。
 * @param[in]    link_idx: 设置链接索引。
 *
 * @return       成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_provisioner_input_number(uint32_t number, uint8_t link_idx);

/**
 * @brief        启用一个或多个配置承载。
 *
 * @param[in]    bearers: 配置承载的逐位OR。
 *
 * @note         PB-ADV：启用BLE扫描。PB-GATT：初始化相应的BLE网格代理信息。
 *
 * @return       成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_provisioner_prov_enable(esp_ble_mesh_prov_bearer_t bearers);

/**
 * @brief        禁用一个或多个配置承载。
 *
 * @param[in]    bearers: 配置承载的逐位OR。
 *
 * @note         PB-ADV：禁用BLE扫描。PB-GATT：断开任何现有的BLE网格配置连接。
 *
 * @return       成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_provisioner_prov_disable(esp_ble_mesh_prov_bearer_t bearers);

/**
 * @brief        将未配置的设备信息添加到未配置的dev队列。
 *
 * @param[in]    add_dev: 指向包含设备信息的结构的指针
 * @param[in]    flags: 标志表示对设备信息的若干操作
 *                      -配置设备后从队列中删除设备信息（BIT0）
 *                      -将设备添加到队列（BIT1）后立即开始配置
 *                      -如果设备队列已满，则可以删除设备（BIT2）
 *
 * @return       成功时返回ESP_OK，否则返回错误代码。
 *
 * @note:        1.目前地址类型只支持公共地址和静态随机地址。2.如果设备队列中已经存在设备UUID和/或设备地址以及地址类型，但承载与现有承载不同，则添加操作也将成功，并将更新设备支持的提供承载。3.例如，如果配置者希望在接收其未配置的设备信标或网格配置广告包之前添加未配置的装置信息，则配置者可以使用此API添加装置信息，同时添加装置UUID和装置地址中的每一个或两个。当配置器获取设备的广告数据包时，它将开始在内部配置设备。
 *                  -在这种情况下，配置器可以在启用ESP_BLE_MESH_PROV_ADV和ESP_BLE_MESH_PROV-GATT中的每一个或两个的情况下设置承载，并且不能在启用ADD_DEV_START_PROV_NOW_FLAG的情况下设定标志。4.另一个示例是当配置器接收到未配置设备的信标或网格配置广告包时，将使用由函数esp_ble_Mesh_register_prop_callback注册的回调将广告包报告给应用层。在回调中，Provisioner可以调用此API来开始配置设备。
 *                  -如果配置器使用PB-ADV进行配置，则可以添加设备UUID和设备地址中的一个或两个，承载应设置为启用ESP_BLE_MESH_PROV_ADV，标志应设置为禁用ADD_DEV_START_PROV_NOW_FLAG。
 *                  -如果配置器使用PB-GATT进行配置，则需要添加设备UUID和设备地址，应在启用ESP_BLE_MESH_PROV_GATT的情况下设置承载，并在启用ADD_DEV_START_PROV_NOW_FLAG的情况下设定标志。
 *                  -如果配置器只想在接收到其广告包时存储未配置的设备信息，并在下次开始配置（例如，再次接收其广告包后），那么它可以添加设备信息，其中包括设备UUID和设备地址中的一个或两个。可以在启用ESP_BLE_MESH_PROV_ADV和ESP_BLE_MESH_PROV-GATT中的一个或两个的情况下设置承载（建议启用将接收其广告数据包的承载，因为如果启用了另一个承载，则配置器不知道设备是否支持该承载），并且不能在启用ADD_DEV_START_PROV_NOW_FLAG的情况下设定标志。
 *                  -注意：不能同时启用ESP_BLE_MESH_PROV_ADV、ESP_BLE_MESH_PROV-GATT和ADD_DEV_START_PROV_NOW_FLAG。
 *
 */
esp_err_t esp_ble_mesh_provisioner_add_unprov_dev(esp_ble_mesh_unprov_dev_add_t *add_dev,
                                                  esp_ble_mesh_dev_add_flag_t flags);

/** @brief 提供未配置的设备，并提前为其分配固定的单播地址。
 *
 *  @param[in] uuid:         未配置设备的设备UUID
 *  @param[in] addr:         未配置设备的设备地址
 *  @param[in] addr_type:    未配置设备的设备地址类型
 *  @param[in] bearer:       Provisioner将使用的Provisioning承载
 *  @param[in] oob_info:     未配置设备的OOB信息
 *  @param[in] unicast_addr: 将为未配置的设备分配单播地址
 *
 *  @return 成功时为零，否则为（负）错误代码。
 *
 *  @note: 1.目前地址类型只支持公共地址和静态随机地址。2.承载必须等于ESP_BLE_MESH_PROV_ADV或ESP_BLE_MESH_PROV-GATT，因为一旦调用此功能，配置器将立即开始配置设备。并且输入承载必须与ESP_BLE_MESH_PROVISIONER_RECV_UNPROV_ADV_PKT_EVT事件参数内的承载相同。3.如果配置器使用此功能来配置设备，则应用程序应注意分配的单播地址，并避免不同节点的单播地址重叠。4.建议provisioner只使用函数“esp_ble_mesh_provisioner_add_unprov_dev”和“esp_ble _mesh_previsioner_prov_device_with_addr”之一。
 */
esp_err_t esp_ble_mesh_provisioner_prov_device_with_addr(const uint8_t uuid[16],
                                                         esp_ble_mesh_bd_addr_t addr,
                                                         esp_ble_mesh_addr_type_t addr_type,
                                                         esp_ble_mesh_prov_bearer_t bearer,
                                                         uint16_t oob_info, uint16_t unicast_addr);

/**
 * @brief        从队列中删除设备，并重置与该设备的当前配置链接。
 *
 * @note         如果设备在队列中，请将其从队列中删除；如果正在供应设备，则终止供应过程。设备地址或设备UUID中的任何一个都可以用作输入。
 *
 * @param[in]    del_dev: 指向包含设备信息的结构的指针。
 *
 * @return       成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_provisioner_delete_dev(esp_ble_mesh_device_delete_t *del_dev);

/**
 * @brief        从不在未配置设备队列中的未配置设备接收广告数据包的Provisioner的回调。
 *
 *               向应用程序报告未配置的设备信标和网格配置服务adv数据。
 *
 * @param[in]    addr: 指向未设置的设备地址的指针。
 * @param[in]    addr_type: 未设置的设备地址类型。
 * @param[in]    adv_type: Adv数据包类型（Adv_IND或Adv_ONCONN_IND）。
 * @param[in]    dev_uuid: 未设置设备UUID指针。
 * @param[in]    oob_info: 未配置设备的OOB信息。
 * @param[in]    bearer: 从PB-GATT或PB-Adv承载接收的Adv分组。
 *
 */
typedef void (*esp_ble_mesh_prov_adv_cb_t)(const esp_ble_mesh_bd_addr_t addr, const esp_ble_mesh_addr_type_t addr_type,
                                           const uint8_t adv_type, const uint8_t *dev_uuid,
                                           uint16_t oob_info, esp_ble_mesh_prov_bearer_t bearer);

/**
 * @brief         Provisioner调用此函数以设置设备UUID的一部分，以便在开始配置之前进行比较。
 *
 * @param[in]     match_val: 要与设备UUID部分进行比较的值。
 * @param[in]     match_len: 比较匹配值的长度。
 * @param[in]     offset: 要比较的设备UUID的偏移量（基于零）。
 * @param[in]     prov_after_match: 用于指示如果UUID的部分匹配，配置者是否应立即开始配置设备的标志。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_provisioner_set_dev_uuid_match(const uint8_t *match_val, uint8_t match_len,
                                                      uint8_t offset, bool prov_after_match);

/**
 * @brief         Provisioner调用此函数以在开始配置之前设置配置数据信息。
 *
 * @param[in]     prov_data_info: 指向包含net_idx或标志或iv_index的结构的指针。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_provisioner_set_prov_data_info(esp_ble_mesh_prov_data_info_t *prov_data_info);

/**
 * @brief         Provisioner调用此函数来设置用于配置的静态oob值。
 *
 * @note          蓝牙SIG建议网格实现在实现允许的情况下使用所有可用位强制执行随机选择的AuthValue。大的熵有助于确保AuthValue的蛮力，即使是静态AuthValue，也不能在合理的时间内正常完成（CVE-2020-26557）。
 *
 *                使用加密安全的随机数或伪随机数生成器选择的具有最大允许熵（128位）的AuthValue将是最难暴力的。熵降低或以可预测方式生成的AuthValues不会对该漏洞提供相同级别的保护。在每次配置尝试中选择一个新的AuthValue也会使攻击者更难通过每次配置尝试重新启动搜索来发起暴力攻击（CVE-2020-26556）。
 *
 * @param[in]     value:  指向静态oob值的指针。
 * @param[in]     length: 静态oob值的长度。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_provisioner_set_static_oob_value(const uint8_t *value, uint8_t length);

/**
 * @brief         Provisioner调用此函数以设置自己的Primary元素地址。
 *
 * @note          当BLE Mesh初始化成功完成时，必须调用此API，并且可以在启用Provisioner功能之前调用此API。成功调用此API后，将忽略结构esp_ble_mesh_prov_t中的prov_unicast_addr值，Provisioner将使用此地址作为其自己的主元素地址。如果分配给下一个未配置设备的单播地址小于输入地址+配置器的元素号，则将在内部重新计算下一个已配置设备的地址。
 *
 * @param[in]     addr: Provisioner的Primary元素的单播地址。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_provisioner_set_primary_elem_addr(uint16_t addr);

/**
 * @brief         调用此函数以在开始快速配置之前设置配置数据信息。
 *
 * @param[in]     fast_prov_info: 指向包含单播地址范围、net_idx等的结构的指针。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_set_fast_prov_info(esp_ble_mesh_fast_prov_info_t *fast_prov_info);

/**
 * @brief         调用此函数以启动/暂停/退出快速资源调配。
 *
 * @param[in]     action: 快速供应动作（即进入、暂停、退出）。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_set_fast_prov_action(esp_ble_mesh_fast_prov_action_t action);

#ifdef __cplusplus
}
#endif

#endif /* _ESP_BLE_MESH_PROVISIONING_API_H_ */

