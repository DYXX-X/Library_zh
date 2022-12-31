/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _ESP_BLE_MESH_NETWORKING_API_H_
#define _ESP_BLE_MESH_NETWORKING_API_H_

#include "esp_ble_mesh_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief: 事件，用户定义模型事件的事件代码；param，用户定义模型事件的参数*/
typedef void (* esp_ble_mesh_model_cb_t)(esp_ble_mesh_model_cb_event_t event,
                                         esp_ble_mesh_model_cb_param_t *param);

/**
 * @brief         为用户定义模型的操作注册BLE Mesh回调。此回调可以报告为用户定义模型生成的以下事件：
 *                -将用户定义的客户端和服务器模型接收到的消息回调到应用层；
 *                -如果用户调用esp_ble_mesh_server/client_model_send，则此回调会通知应用程序层send_complete事件；
 *                -如果用户定义的客户端模型发送了需要响应的消息，并且在定时器到期后接收到响应消息，则响应消息将被报告给对等设备发布的应用层；
 *                -如果用户定义的客户端模型在指定的时间段内未能接收到响应消息，则将向应用程序层报告超时事件。
 *
 * @note          已在内部实现的客户端模型（即配置客户端模型、健康客户端模型、通用客户端模型、传感器客户端模型、场景客户端模型和照明客户端模型）具有其特定的寄存器功能。例如，esp_ble_mesh_register_config_client_callback是config client Model的注册函数。
 *
 * @param[in]     callback: 指向回调函数的指针。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_register_custom_model_callback(esp_ble_mesh_model_cb_t callback);

/**
 * @brief        在发送或发布模型消息之前，将消息操作码添加到模型消息的开头。
 *
 * @note         此API仅用于设置消息的操作码。
 *
 * @param[in]    data: 指向消息数据的指针。
 * @param[in]    opcode: 消息操作码。
 *
 * @return       成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_model_msg_opcode_init(uint8_t *data, uint32_t opcode);

/**
 * @brief         初始化用户定义的客户端模型。所有用户定义的客户端模型都应调用此函数来初始化客户端模型内部数据。节点：在调用此API之前，需要初始化客户端模型的user_data（使用esp_ble_mesh_client_t_定义）中可变的op_pair_size和op_pair。
 *
 * @param[in]     model: 消息所属的BLE Mesh客户端模型。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_client_model_init(esp_ble_mesh_model_t *model);

/**
 * @brief         取消初始化用户定义的客户端模型。
 *
 * @note          应在调用esp_ble_mesh_deinit（）之前调用此函数。
 *
 * @param[in]     model: 客户端模型的指针。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_client_model_deinit(esp_ble_mesh_model_t *model);

/**
 * @brief         发送服务器模型消息（如服务器模型状态消息）。
 *
 * @param[in]     model: 消息所属的BLE Mesh服务器模型。
 * @param[in]     ctx:   消息上下文，包括密钥、TTL等。
 * @param[in]     opcode: 消息操作码。
 * @param[in]     length: 消息长度（不包括消息操作码）。
 * @param[in]     data: 要发送的访问有效载荷参数（不包括消息操作码）。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_server_model_send_msg(esp_ble_mesh_model_t *model,
                                             esp_ble_mesh_msg_ctx_t *ctx,
                                             uint32_t opcode,
                                             uint16_t length, uint8_t *data);

/**
 * @brief         发送客户端模型消息（如模型获取、设置等）。
 *
 * @param[in]     model: 消息所属的BLE Mesh客户端模型。
 * @param[in]     ctx:   消息上下文，包括密钥、TTL等。
 * @param[in]     opcode: 消息操作码。
 * @param[in]     length: 消息长度（不包括消息操作码）。
 * @param[in]     data: 要发送的访问有效载荷的参数（不包括消息操作码）。
 * @param[in]     msg_timeout: 获取消息响应的时间（毫秒）。
 * @param[in]     need_rsp: 如果操作码要求对等设备应答，则为TRUE，否则为FALSE。
 * @param[in]     device_role: 发送消息的设备（节点/配置器）的角色。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_client_model_send_msg(esp_ble_mesh_model_t *model,
                                             esp_ble_mesh_msg_ctx_t *ctx,
                                             uint32_t opcode,
                                             uint16_t length, uint8_t *data,
                                             int32_t msg_timeout, bool need_rsp,
                                             esp_ble_mesh_dev_role_t device_role);

/**
 * @brief         发送模型发布消息。
 *
 * @note          在调用此函数之前，用户需要确保模型
 *                publication message (@ref esp_ble_mesh_model_pub_。msg）包含要发送的有效消息。如果用户希望更新发布消息，则应在ESP_BLE_MESH_MODEL_PUBLISH_update_EVT中调用此API，并更新消息。
 *
 *
 * @param[in]    model: 发布消息的网格（客户端）模型。
 * @param[in]    opcode: 消息操作码。
 * @param[in]    length: 消息长度（不包括消息操作码）。
 * @param[in]    data: 要发送的访问有效载荷的参数（不包括消息操作码）。
 * @param[in]    device_role: 发布esp_ble_mesh_dev_Role_t类型消息的设备（节点/提供商）的角色。
 *
 * @return       成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_model_publish(esp_ble_mesh_model_t *model, uint32_t opcode,
                                     uint16_t length, uint8_t *data,
                                     esp_ble_mesh_dev_role_t device_role);

/**
 * @brief        更新服务器模型状态值。如果模型发布状态设置正确（例如，发布地址设置为有效地址），它将发布相应的状态消息。
 *
 * @note         当前，此API用于更新绑定状态值，而不是用于所有服务器模型状态。
 *
 * @param[in]    model: 将更新状态的服务器模型。
 * @param[in]    type:  服务器模型状态类型。
 * @param[in]    value: 服务器模型状态值。
 *
 * @return       成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_server_model_update_state(esp_ble_mesh_model_t *model,
                                                 esp_ble_mesh_server_state_type_t type,
                                                 esp_ble_mesh_server_state_value_t *value);

/**
 * @brief         重置本地BLE Mesh节点的配置过程。
 *
 * @note          此节点中的所有设置信息都将被删除，需要重新设置该节点。需要调用API函数esp_ble_mesh_node_prov_enable（）来启动新的配置过程。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_node_local_reset(void);

/**
 * @brief        调用此函数以设置节点（配置的设备）名称。
 *
 * @param[in]    index: 节点队列中节点的索引。
 * @param[in]    name: 要为节点设置的名称（以“\0”结尾）。
 *
 * @note         从ESP_BLE_MESH_PROVISIONER_PROV_COMPLETE_EVT的参数获得索引。
 *
 * @return       成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_provisioner_set_node_name(uint16_t index, const char *name);

/**
 * @brief        调用此函数以获取节点（配置的设备）名称。
 *
 * @param[in]    index: 节点队列中节点的索引。
 *
 * @note         从ESP_BLE_MESH_PROVISIONER_PROV_COMPLETE_EVT的参数获得索引。
 *
 * @return       成功时为节点名，失败时为NULL。
 *
 */
const char *esp_ble_mesh_provisioner_get_node_name(uint16_t index);

/**
 * @brief        调用此函数以获取节点（已配置设备）索引。
 *
 * @param[in]    name: 节点的名称（以“\0”结尾）。
 *
 * @return       成功时为节点索引，失败时为无效值（0xFFFF）。
 *
 */
uint16_t esp_ble_mesh_provisioner_get_node_index(const char *name);

/**
 * @brief        调用此函数以存储节点的合成数据。
 *
 * @param[in]    unicast_addr: 节点的元素地址
 * @param[in]    data:         合成数据指针
 * @param[in]    length:       成分数据长度
 *
 * @return       成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_provisioner_store_node_comp_data(uint16_t unicast_addr,
                                                        uint8_t *data, uint16_t length);

/**
 * @brief        调用此函数以获取具有节点设备uuid的已配置节点信息。
 *
 * @param[in]    uuid: 节点的设备UUID
 *
 * @return       节点信息结构的指针或失败时为NULL。
 *
 */
esp_ble_mesh_node_t *esp_ble_mesh_provisioner_get_node_with_uuid(const uint8_t uuid[16]);

/**
 * @brief        调用此函数以获取具有节点单播地址的已配置节点信息。
 *
 * @param[in]    unicast_addr: 节点的单播地址
 *
 * @return       节点信息结构的指针或失败时为NULL。
 *
 */
esp_ble_mesh_node_t *esp_ble_mesh_provisioner_get_node_with_addr(uint16_t unicast_addr);

/**
 * @brief        调用此函数以获取具有节点名称的已配置节点信息。
 *
 * @param[in]    name: 节点的名称（以“\0”结尾）。
 *
 * @return       节点信息结构的指针或失败时为NULL。
 *
 */
esp_ble_mesh_node_t *esp_ble_mesh_provisioner_get_node_with_name(const char *name);

/**
 * @brief         Provisioner调用此函数以获取配置的节点计数。
 *
 * @return        配置的节点数。
 *
 */
uint16_t esp_ble_mesh_provisioner_get_prov_node_count(void);

/**
 * @brief         Provisioner调用此函数以获取节点表的条目。
 *
 * @note          在调用函数获取节点条目后，用户可以使用“for”循环和宏CONFIG_BLE_MESH_MAX_PROV_nodes来获取每个节点的信息。在尝试读取节点信息之前，用户需要检查节点是否存在，即（esp_ble_mesh_node_t节点）是否为NULL。例如：``const esp_ble_mesh_node_t entry=esp_ble_mesh_provisioner_get_node_table_entry（）；对于（int i=0；i<CONFIG_BLE_MESH_MAX_PROV_NODES；i++）｛const esp_BLE_MESH_node_t node=条目[i]；if（节点）｛…｝｝```
 *
 * @return        指向节点表开头的指针。
 *
 */
const esp_ble_mesh_node_t **esp_ble_mesh_provisioner_get_node_table_entry(void);

/**
 * @brief        调用此函数以删除具有节点设备uuid的已配置节点信息。
 *
 * @param[in]    uuid: 节点的设备UUID
 *
 * @return       成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_provisioner_delete_node_with_uuid(const uint8_t uuid[16]);

/**
 * @brief        调用此函数以删除具有节点单播地址的已配置节点信息。
 *
 * @param[in]    unicast_addr: 节点的单播地址
 *
 * @return       成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_provisioner_delete_node_with_addr(uint16_t unicast_addr);

/**
 * @brief         调用此函数为Provisioner添加本地AppKey。
 *
 * @param[in]     app_key: 要为本地BLE Mesh堆栈设置的应用程序密钥。
 * @param[in]     net_idx: 网络密钥索引。
 * @param[in]     app_idx: 应用程序密钥索引。
 *
 * @note          app_key：如果设置为NULL，将在内部生成app_key。net_idx：应该是现有的。app_idx：如果要在内部生成，则应将其设置为0xFFFF，并通过事件报告新的app_idx。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_provisioner_add_local_app_key(const uint8_t app_key[16],
                                                     uint16_t net_idx, uint16_t app_idx);

/**
 * @brief         此函数用于更新Provisioner的本地AppKey。
 *
 * @param[in]     app_key: AppKey的值。
 * @param[in]     net_idx: 对应的NetKey索引。
 * @param[in]     app_idx: AppKey索引
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_provisioner_update_local_app_key(const uint8_t app_key[16],
                                                        uint16_t net_idx, uint16_t app_idx);

/**
 * @brief         Provisioner调用此函数以获取本地应用程序密钥值。
 *
 * @param[in]     net_idx: 网络密钥索引。
 * @param[in]     app_idx: 应用程序密钥索引。
 *
 * @return        成功时为应用键，失败时为NULL。
 *
 */
const uint8_t *esp_ble_mesh_provisioner_get_local_app_key(uint16_t net_idx, uint16_t app_idx);

/**
 * @brief         Provisioner调用此函数以将自己的模型与适当的应用程序密钥绑定。
 *
 * @param[in]     element_addr: Provisioner本地元素地址
 * @param[in]     app_idx: Provisioner本地appkey索引
 * @param[in]     model_id: 配置程序本地模型id
 * @param[in]     company_id: Provisioner本地公司id
 *
 * @note          company_id：如果要将app_key与本地供应商模型绑定，company_id应设置为0xFFFF。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_provisioner_bind_app_key_to_local_model(uint16_t element_addr, uint16_t app_idx,
                                                               uint16_t model_id, uint16_t company_id);

/**
 * @brief         Provisioner调用此函数以添加本地网络密钥。
 *
 * @param[in]     net_key: 要添加到Provisioner本地BLE Mesh堆栈的网络密钥。
 * @param[in]     net_idx: 网络密钥索引。
 *
 * @note          net_key：如果设置为NULL，将在内部生成net_key。net_idx：如果要在内部生成，则应将其设置为0xFFFF，并通过事件报告新的net_idx。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_provisioner_add_local_net_key(const uint8_t net_key[16], uint16_t net_idx);

/**
 * @brief         Provisioner调用此函数以更新本地网络密钥。
 *
 * @param[in]     net_key: NetKey的值。
 * @param[in]     net_idx: NetKey索引。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_provisioner_update_local_net_key(const uint8_t net_key[16], uint16_t net_idx);

/**
 * @brief         Provisioner调用此函数以获取本地网络密钥值。
 *
 * @param[in]     net_idx: 网络密钥索引。
 *
 * @return        成功时为网络密钥，失败时为NULL。
 *
 */
const uint8_t *esp_ble_mesh_provisioner_get_local_net_key(uint16_t net_idx);

/**
 * @brief         Provisioner调用此函数以启用或禁用接收心跳消息。
 *
 * @note          如果成功启用接收心跳消息，则默认情况下过滤器将为空拒绝列表，这意味着Provisioner接收到的所有心跳消息都将报告给应用程序层。
 *
 * @param[in]     enable: 启用或禁用接收心跳消息。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_provisioner_recv_heartbeat(bool enable);

/**
 * @brief         Provisioner调用此函数来设置心跳过滤器类型。
 *
 * @note          1.如果过滤器类型与当前值不同，则将清除所有过滤器条目。2.如果之前的类型是rejectlist，并更改为acceptlist，则过滤器将是空的acceptlist（接受列表），这意味着不会报告心跳消息。用户需要将SRC或DST添加到过滤器条目中，然后将报告来自SRC或到DST的心跳消息。
 *
 * @param[in]     type: 心跳过滤器类型（接受列表或拒绝列表）。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_provisioner_set_heartbeat_filter_type(uint8_t type);

/**
 * @brief         Provisioner调用此函数以添加或删除心跳过滤器条目。
 *
 * @note          1.如果操作为“ADD”，则可以将“hb_src”设置为心跳消息的src（只能是单播地址），将“hb_dst”设置为dst（单播地址或组地址），至少需要设置其中一个。
 *                   -如果只设置了其中一个，则过滤器条目将仅使用配置的SRC或DST来过滤心跳消息。
 *                   -如果两者都被设置，SRC和DST都将用于决定是否处理心跳消息。
 *                   -如果SRC或DST已经存在于某个过滤器条目中，那么将首先清除相应的条目，然后分配一个新条目来存储信息。2.如果操作为“REMOVE”，则可以将“hb_src”设置为心跳消息的src（只能是单播地址），将“hb_dst”设置为dst（单播地址或组地址），至少需要设置其中一个。
 *                   -将删除具有相同SRC或DST的筛选器条目。
 *
 * @param[in]     op:   添加或删除
 * @param[in]     info: 心跳过滤器条目信息，包括：hb_src-心跳源地址；hb_dst-心跳目标地址；
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_provisioner_set_heartbeat_filter_info(uint8_t op, esp_ble_mesh_heartbeat_filter_info_t *info);

/**
 * @brief         Provisioner调用此函数以直接从nvs命名空间中删除网格信息。
 *
 * @note          当网格堆栈未初始化或已取消初始化时，可以调用此函数。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_provisioner_direct_erase_settings(void);

/**
 * @brief         Provisioner调用此函数以打开用于存储网格信息的nvs命名空间。
 *
 * @note          在打开另一个nvs命名空间之前，必须先关闭先前打开的nvs命名空间。
 *
 * @param[in]     index: 设置索引。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_provisioner_open_settings_with_index(uint8_t index);

/**
 * @brief         Provisioner调用此函数以打开用于存储网格信息的nvs命名空间。
 *
 * @note          在打开另一个nvs命名空间之前，必须先关闭先前打开的nvs命名空间。
 *
 * @param[in]     uid: 设置用户id。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_provisioner_open_settings_with_uid(const char *uid);

/**
 * @brief         Provisioner调用此函数以关闭先前为存储网格信息而打开的nvs命名空间。
 *
 * @note          1.在关闭nvs命名空间之前，必须将其打开。2.当调用该函数时，将首先禁用Provisioner功能，并且：a）如果“擦除”标志设置为false，将从网格堆栈中清除网格信息（例如删除NetKey、AppKey、节点等）。b） 如果“erase”标志设置为true，则存储在nvs命名空间中的网格信息除了从网格堆栈中清除外，还将被删除。3.如果Provisioner再次尝试正常工作，我们可以调用open函数来打开一个新的nvs命名空间或之前添加的命名空间，如果没有删除，则从中恢复网格信息。4.工作过程如下：a）打开设置a b）开始提供和控制节点c）关闭设置a d）打开设置b e）开始提供并控制其他节点f）关闭设置b g）。。。。。。
 *
 * @param[in]     index: 设置索引。
 * @param[in]     erase: 指示是否删除网格信息。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_provisioner_close_settings_with_index(uint8_t index, bool erase);

/**
 * @brief         Provisioner调用此函数以关闭先前为存储网格信息而打开的nvs命名空间。
 *
 * @note          1.在关闭nvs命名空间之前，必须将其打开。2.当调用该函数时，将首先禁用Provisioner功能，并且：a）如果“擦除”标志设置为false，将从网格堆栈中清除网格信息（例如删除NetKey、AppKey、节点等）。b） 如果“erase”标志设置为true，则存储在nvs命名空间中的网格信息除了从网格堆栈中清除外，还将被删除。3.如果Provisioner再次尝试正常工作，我们可以调用open函数来打开一个新的nvs命名空间或之前添加的命名空间，如果没有删除，则从中恢复网格信息。4.工作过程如下：a）打开设置a b）开始提供和控制节点c）关闭设置a d）打开设置b e）开始提供并控制其他节点f）关闭设置b g）。。。。。。
 *
 * @param[in]     uid: 设置用户id。
 * @param[in]     erase: 指示是否删除网格信息。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_provisioner_close_settings_with_uid(const char *uid, bool erase);

/**
 * @brief         Provisioner调用此函数以从nvs命名空间中删除网格信息和设置用户id。
 *
 * @note          调用此函数时，nvs命名空间不能打开。此功能用于清除当前未使用的网格信息和设置用户id。
 *
 * @param[in]     index: 设置索引。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_provisioner_delete_settings_with_index(uint8_t index);

/**
 * @brief         Provisioner调用此函数以从nvs命名空间中删除网格信息和设置用户id。
 *
 * @note          调用此函数时，nvs命名空间不能打开。此功能用于清除当前未使用的网格信息和设置用户id。
 *
 * @param[in]     uid: 设置用户id。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_provisioner_delete_settings_with_uid(const char *uid);

/**
 * @brief         Provisioner调用此函数以获取设置用户id。
 *
 * @param[in]     index: 设置索引。
 *
 * @return        成功时设置用户id，失败时设置为NULL。
 *
 */
const char *esp_ble_mesh_provisioner_get_settings_uid(uint8_t index);

/**
 * @brief         Provisioner调用此函数以获取设置索引。
 *
 * @param[in]     uid: 设置用户id。
 *
 * @return        设置索引。
 *
 */
uint8_t esp_ble_mesh_provisioner_get_settings_index(const char *uid);

/**
 * @brief         Provisioner调用此函数以获取可用设置用户id的数量。
 *
 * @return        可用设置用户id的数量。
 *
 */
uint8_t esp_ble_mesh_provisioner_get_free_settings_count(void);

/**
 * @brief         调用此函数以获取快速配置应用程序密钥。
 *
 * @param[in]     net_idx: 网络密钥索引。
 * @param[in]     app_idx: 应用程序密钥索引。
 *
 * @return        成功时为应用程序键，失败时为NULL。
 *
 */
const uint8_t *esp_ble_mesh_get_fast_prov_app_key(uint16_t net_idx, uint16_t app_idx);

#ifdef __cplusplus
}
#endif

#endif /* _ESP_BLE_MESH_NETWORKING_API_H_ */

