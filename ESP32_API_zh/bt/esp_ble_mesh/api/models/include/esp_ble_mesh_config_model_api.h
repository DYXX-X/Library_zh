/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _ESP_BLE_MESH_CONFIG_MODEL_API_H_
#define _ESP_BLE_MESH_CONFIG_MODEL_API_H_

#include "esp_ble_mesh_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @def    ESP_BLE_MESH_MODEL_CFG_SRV
 *
 *  @brief  定义新的配置服务器模型。
 *
 *  @note   配置服务器模型只能包含在主元素中。
 *
 *  @param  srv_data 指向唯一配置服务器模型user_data的指针。
 *
 *  @return 新建配置服务器模型实例。
 */
#define ESP_BLE_MESH_MODEL_CFG_SRV(srv_data)                              \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_CONFIG_SRV,          \
                  NULL, NULL, srv_data)

/** @def    ESP_BLE_MESH_MODEL_CFG_CLI
 *
 *  @brief  定义新的配置客户端模型。
 *
 *  @note   配置客户端模型只能包含在主元素中。
 *
 *  @param  cli_data 指向唯一结构esp_ble_mesh_client_t的指针。
 *
 *  @return 新建配置客户端模型实例。
 */
#define ESP_BLE_MESH_MODEL_CFG_CLI(cli_data)                              \
        ESP_BLE_MESH_SIG_MODEL(ESP_BLE_MESH_MODEL_ID_CONFIG_CLI,          \
                  NULL, NULL, cli_data)

/**配置服务器模型上下文*/
typedef struct esp_ble_mesh_cfg_srv {
    esp_ble_mesh_model_t *model;    /*!< 指向配置服务器模型的指针*/

    uint8_t net_transmit;           /*!< 网络传输状态*/
    uint8_t relay;                  /*!< 继电器模式状态*/
    uint8_t relay_retransmit;       /*!< 继电器重新传输状态*/
    uint8_t beacon;                 /*!< 安全网络信标状态*/
    uint8_t gatt_proxy;             /*!< GATT代理国*/
    uint8_t friend_state;           /*!< 好友状态*/
    uint8_t default_ttl;            /*!< 默认TTL*/

    /**心跳发布*/
    struct {
        struct k_delayed_work timer;    /*!< 心跳发布计时器*/

        uint16_t dst;                   /*!< 心跳消息的目标地址*/
        uint16_t count;                 /*!< 要发送的心跳消息数*/
        uint8_t  period;                /*!< 发送心跳消息的时间段*/
        uint8_t  ttl;                   /*!< 发送心跳消息时使用的TTL*/
        uint16_t feature;               /*!< 指示更改时触发心跳消息的特征的位字段*/
        uint16_t net_idx;               /*!< 心跳发布使用的NetKey索引*/
    } heartbeat_pub;

    /**心跳订阅*/
    struct {
        int64_t  expiry;                /*!< 心跳订阅期到期时的时间戳*/

        uint16_t src;                   /*!< 心跳消息的源地址*/
        uint16_t dst;                   /*!< 心跳消息的目标地址*/
        uint16_t count;                 /*!< 接收的心跳消息数*/
        uint8_t  min_hops;              /*!< 接收心跳消息时的最小跳数*/
        uint8_t  max_hops;              /*!< 接收心跳消息时的最大跳数*/

        /**可选心跳订阅跟踪功能*/
        esp_ble_mesh_cb_t heartbeat_recv_cb;
    } heartbeat_sub;
} esp_ble_mesh_cfg_srv_t;

/**配置组成数据获取参数。*/
typedef struct {
    uint8_t page;                   /*!< 组成数据的页码。*/
} esp_ble_mesh_cfg_composition_data_get_t;

/**配置模型发布获取的参数。*/
typedef struct {
    uint16_t element_addr;          /*!< 元素地址*/
    uint16_t model_id;              /*!< 模型id*/
    uint16_t company_id;            /*!< 公司id（如果不是供应商型号）应设置为0xFFFF*/
} esp_ble_mesh_cfg_model_pub_get_t;

/**Config SIG Model Subscription Get的参数。*/
typedef struct {
    uint16_t element_addr;          /*!< 元素地址*/
    uint16_t model_id;              /*!< 模型id*/
} esp_ble_mesh_cfg_sig_model_sub_get_t;

/**配置供应商模型订阅获取的参数。*/
typedef struct {
    uint16_t element_addr;          /*!< 元素地址*/
    uint16_t model_id;              /*!< 模型id*/
    uint16_t company_id;            /*!< 公司id（如果不是供应商型号）应设置为0xFFFF*/
} esp_ble_mesh_cfg_vnd_model_sub_get_t;

/**Config AppKey Get的参数。*/
typedef struct {
    uint16_t net_idx;               /*!< 网络密钥索引*/
} esp_ble_mesh_cfg_app_key_get_t;

/**配置节点标识获取的参数。*/
typedef struct {
    uint16_t net_idx;               /*!< 网络密钥索引*/
} esp_ble_mesh_cfg_node_identity_get_t;

/**Config SIG Model App Get的参数。*/
typedef struct {
    uint16_t element_addr;          /*!< 元素地址*/
    uint16_t model_id;              /*!< 模型id*/
} esp_ble_mesh_cfg_sig_model_app_get_t;

/**配置供应商模型应用程序获取的参数。*/
typedef struct {
    uint16_t element_addr;          /*!< 元素地址*/
    uint16_t model_id;              /*!< 模型id*/
    uint16_t company_id;            /*!< 公司id（如果不是供应商型号）应设置为0xFFFF*/
} esp_ble_mesh_cfg_vnd_model_app_get_t;

/**获取配置密钥刷新阶段的参数。*/
typedef struct {
    uint16_t net_idx;               /*!< 网络密钥索引*/
} esp_ble_mesh_cfg_kr_phase_get_t;

/**配置低功耗节点轮询超时获取的参数。*/
typedef struct {
    uint16_t lpn_addr;              /*!< 低功耗节点的单播地址*/
} esp_ble_mesh_cfg_lpn_polltimeout_get_t;

/**配置信标集参数。*/
typedef struct {
    uint8_t beacon;                 /*!< 新的安全网络信标状态*/
} esp_ble_mesh_cfg_beacon_set_t;

/**配置默认TTL设置的参数。*/
typedef struct {
    uint8_t ttl;                    /*!< 默认TTL状态值*/
} esp_ble_mesh_cfg_default_ttl_set_t;

/**配置朋友集的参数。*/
typedef struct {
    uint8_t friend_state;           /*!< 好友状态值*/
} esp_ble_mesh_cfg_friend_set_t;

/**配置GATT代理集的参数。*/
typedef struct {
    uint8_t gatt_proxy;             /*!< GATT代理状态值*/
} esp_ble_mesh_cfg_gatt_proxy_set_t;

/**配置继电器组参数。*/
typedef struct {
    uint8_t relay;                  /*!< 继电器值*/
    uint8_t relay_retransmit;       /*!< 继电器重传值*/
} esp_ble_mesh_cfg_relay_set_t;

/**Config NetKey Add的参数。*/
typedef struct {
    uint16_t net_idx;               /*!< 网络密钥索引*/
    uint8_t  net_key[16];           /*!< 网络密钥值*/
} esp_ble_mesh_cfg_net_key_add_t;

/**Config AppKey Add的参数。*/
typedef struct {
    uint16_t net_idx;               /*!< 网络密钥索引*/
    uint16_t app_idx;               /*!< 应用程序密钥索引*/
    uint8_t  app_key[16];           /*!< 应用程序密钥值*/
} esp_ble_mesh_cfg_app_key_add_t;

/**配置模型应用程序绑定的参数。*/
typedef struct {
    uint16_t element_addr;          /*!< 元素地址*/
    uint16_t model_app_idx;         /*!< 要与模型绑定的应用程序密钥的索引*/
    uint16_t model_id;              /*!< 模型id*/
    uint16_t company_id;            /*!< 公司id（如果不是供应商型号）应设置为0xFFFF*/
} esp_ble_mesh_cfg_model_app_bind_t;

/**配置模型发布集的参数。*/
typedef struct {
    uint16_t element_addr;          /*!< 元素地址*/
    uint16_t publish_addr;          /*!< 发布地址的值*/
    uint16_t publish_app_idx;       /*!< 应用程序密钥的索引*/
    bool     cred_flag;             /*!< 友谊证书旗帜的价值*/
    uint8_t  publish_ttl;           /*!< 发布消息的默认TTL值*/
    uint8_t  publish_period;        /*!< 定期状态发布的周期*/
    uint8_t  publish_retransmit;    /*!< 重传次数和重传之间的50毫秒步数*/
    uint16_t model_id;              /*!< 模型id*/
    uint16_t company_id;            /*!< 公司id（如果不是供应商型号）应设置为0xFFFF*/
} esp_ble_mesh_cfg_model_pub_set_t;

/**配置模型订阅添加的参数。*/
typedef struct {
    uint16_t element_addr;          /*!< 元素地址*/
    uint16_t sub_addr;              /*!< 要添加到订阅列表的地址*/
    uint16_t model_id;              /*!< 模型id*/
    uint16_t company_id;            /*!< 公司id（如果不是供应商型号）应设置为0xFFFF*/
} esp_ble_mesh_cfg_model_sub_add_t;

/**配置模型订阅删除的参数。*/
typedef struct {
    uint16_t element_addr;          /*!< 元素地址*/
    uint16_t sub_addr;              /*!< 要从订阅列表中删除的地址*/
    uint16_t model_id;              /*!< 模型id*/
    uint16_t company_id;            /*!< 公司id（如果不是供应商型号）应设置为0xFFFF*/
} esp_ble_mesh_cfg_model_sub_delete_t;

/**配置模型订阅覆盖的参数。*/
typedef struct {
    uint16_t element_addr;          /*!< 元素地址*/
    uint16_t sub_addr;              /*!< 要添加到订阅列表的地址*/
    uint16_t model_id;              /*!< 模型id*/
    uint16_t company_id;            /*!< 公司id（如果不是供应商型号）应设置为0xFFFF*/
} esp_ble_mesh_cfg_model_sub_overwrite_t;

/**配置模型订阅虚拟地址添加的参数。*/
typedef struct {
    uint16_t element_addr;          /*!< 元素地址*/
    uint8_t  label_uuid[16];        /*!< 要添加到订阅列表的虚拟地址的标签UUID*/
    uint16_t model_id;              /*!< 模型id*/
    uint16_t company_id;            /*!< 公司id（如果不是供应商型号）应设置为0xFFFF*/
} esp_ble_mesh_cfg_model_sub_va_add_t;

/**配置模型订阅虚拟地址删除的参数。*/
typedef struct {
    uint16_t element_addr;          /*!< 元素地址*/
    uint8_t  label_uuid[16];        /*!< 要从订阅列表中删除的虚拟地址的标签UUID*/
    uint16_t model_id;              /*!< 模型id*/
    uint16_t company_id;            /*!< 公司id（如果不是供应商型号）应设置为0xFFFF*/
} esp_ble_mesh_cfg_model_sub_va_delete_t;

/**配置模型订阅虚拟地址覆盖的参数。*/
typedef struct {
    uint16_t element_addr;          /*!< 元素地址*/
    uint8_t  label_uuid[16];        /*!< 要添加到订阅列表的虚拟地址的标签UUID*/
    uint16_t model_id;              /*!< 模型id*/
    uint16_t company_id;            /*!< 公司id（如果不是供应商型号）应设置为0xFFFF*/
} esp_ble_mesh_cfg_model_sub_va_overwrite_t;

/**配置模型发布虚拟地址集的参数。*/
typedef struct {
    uint16_t element_addr;          /*!< 元素地址*/
    uint8_t  label_uuid[16];        /*!< 标签UUID发布地址的值*/
    uint16_t publish_app_idx;       /*!< 应用程序密钥的索引*/
    bool     cred_flag;             /*!< 友谊证书旗帜的价值*/
    uint8_t  publish_ttl;           /*!< 发布消息的默认TTL值*/
    uint8_t  publish_period;        /*!< 定期状态发布的周期*/
    uint8_t  publish_retransmit;    /*!< 重传次数和重传之间的50毫秒步数*/
    uint16_t model_id;              /*!< 模型id*/
    uint16_t company_id;            /*!< 公司id（如果不是供应商型号）应设置为0xFFFF*/
} esp_ble_mesh_cfg_model_pub_va_set_t;

/**配置模型订阅的参数全部删除。*/
typedef struct {
    uint16_t element_addr;          /*!< 元素地址*/
    uint16_t model_id;              /*!< 模型id*/
    uint16_t company_id;            /*!< 公司id（如果不是供应商型号）应设置为0xFFFF*/
} esp_ble_mesh_cfg_model_sub_delete_all_t;

/**配置NetKey更新的参数。*/
typedef struct {
    uint16_t net_idx;               /*!< 网络密钥索引*/
    uint8_t  net_key[16];           /*!< 网络密钥值*/
} esp_ble_mesh_cfg_net_key_update_t;

/**Config NetKey Delete的参数。*/
typedef struct {
    uint16_t net_idx;               /*!< 网络密钥索引*/
} esp_ble_mesh_cfg_net_key_delete_t;

/**配置AppKey更新的参数。*/
typedef struct {
    uint16_t net_idx;               /*!< 网络密钥索引*/
    uint16_t app_idx;               /*!< 应用程序密钥索引*/
    uint8_t  app_key[16];           /*!< 应用程序密钥值*/
} esp_ble_mesh_cfg_app_key_update_t;

/**Config AppKey Delete的参数。*/
typedef struct {
    uint16_t net_idx;               /*!< 网络密钥索引*/
    uint16_t app_idx;               /*!< 应用程序密钥索引*/
} esp_ble_mesh_cfg_app_key_delete_t;

/**配置节点标识集的参数。*/
typedef struct {
    uint16_t net_idx;               /*!< 网络密钥索引*/
    uint8_t  identity;              /*!< 新节点标识状态*/
} esp_ble_mesh_cfg_node_identity_set_t;

/**配置模型应用程序解除绑定的参数。*/
typedef struct {
    uint16_t element_addr;          /*!< 元素地址*/
    uint16_t model_app_idx;         /*!< 要与模型绑定的应用程序密钥的索引*/
    uint16_t model_id;              /*!< 模型id*/
    uint16_t company_id;            /*!< 公司id（如果不是供应商型号）应设置为0xFFFF*/
} esp_ble_mesh_cfg_model_app_unbind_t;

/**配置密钥刷新阶段集的参数。*/
typedef struct {
    uint16_t net_idx;               /*!< 网络密钥索引*/
    uint8_t  transition;            /*!< 新密钥刷新阶段转换*/
} esp_ble_mesh_cfg_kr_phase_set_t;

/**配置网络传输集的参数。*/
typedef struct {
    uint8_t net_transmit;           /*!< 网络传输状态*/
} esp_ble_mesh_cfg_net_transmit_set_t;

/**配置模型心跳发布集的参数。*/
typedef struct  {
    uint16_t dst;                   /*!< 心跳消息的目标地址*/
    uint8_t  count;                 /*!< 要发送的心跳消息数*/
    uint8_t  period;                /*!< 发送心跳消息的时间段*/
    uint8_t  ttl;                   /*!< 发送心跳消息时使用的TTL*/
    uint16_t feature;               /*!< 指示更改时触发心跳消息的特征的位字段*/
    uint16_t net_idx;               /*!< NetKey索引*/
} esp_ble_mesh_cfg_heartbeat_pub_set_t;

/**配置模型心跳订阅集的参数。*/
typedef struct {
    uint16_t src;                   /*!< 心跳消息的源地址*/
    uint16_t dst;                   /*!< 心跳消息的目标地址*/
    uint8_t  period;                /*!< 接收心跳消息的时间段*/
} esp_ble_mesh_cfg_heartbeat_sub_set_t;

/**
 * @brief 对于ESP_BLE_MESH_MODE_OP_BEACON_GET ESP_BLE-MESH_MODEL_OP_COMPOSITION_DATA_GET ESP-BLE_MES_MODEL_OP_DEFAULT_TTL_GET ESP_MESH_MODE E_OP_GATT_PROXY_GET ESP _BLE_MES H_MODEL_PUB_RELAY_GETesp_ble_mesh_config_client_get_state函数不应设置为NULL。
 */
typedef union {
    esp_ble_mesh_cfg_model_pub_get_t         model_pub_get;     /*!< 对于ESP_BLE_MESH_MODEL_OP_MODEL_PUB_GET。*/
    esp_ble_mesh_cfg_composition_data_get_t  comp_data_get;     /*!< 对于ESP_BLE_MESH_MODEL_OP_COMPOSITION_DATA_GET。*/
    esp_ble_mesh_cfg_sig_model_sub_get_t     sig_model_sub_get; /*!< 对于ESP_BLE_MESH_MODEL_OP_SIG_MODEL_SUB_GET*/
    esp_ble_mesh_cfg_vnd_model_sub_get_t     vnd_model_sub_get; /*!< 对于ESP_BLE_MESH_MODEL_OP_ENDOR_MODEL_SUB_GET*/
    esp_ble_mesh_cfg_app_key_get_t           app_key_get;       /*!< 对于ESP_BLE_MESH_MODEL_OP_APP_KEY_GET。*/
    esp_ble_mesh_cfg_node_identity_get_t     node_identity_get; /*!< 对于ESP_BLE_MESH_MODEL_OP_NODE_IDENTITY_GET。*/
    esp_ble_mesh_cfg_sig_model_app_get_t     sig_model_app_get; /*!< 对于ESP_BLE_MESH_MODEL_OP_SIG_MODEL_APP_GET*/
    esp_ble_mesh_cfg_vnd_model_app_get_t     vnd_model_app_get; /*!< 对于ESP_BLE_MESH_MODEL_OP_ENDOR_MODEL_APP_GET*/
    esp_ble_mesh_cfg_kr_phase_get_t          kr_phase_get;      /*!< 对于ESP_BLE_MESH_MODEL_OP_KEY_REFRESH_PHASE_GET*/
    esp_ble_mesh_cfg_lpn_polltimeout_get_t   lpn_pollto_get;    /*!< 对于ESP_BLE_MESH_MODEL_OP_LPN_POLLTIMEOUT_GET*/
} esp_ble_mesh_cfg_client_get_state_t;

/**
 * @brief 对于ESP_BLE_MESH_MODEL_OP_BECON_SET ESP_BLE_MESH_MODE_OP_DEFAULT_TTL_SET ESP-BLE_MES_MODEL_OP_GATT_PROXY_SET ESP.BLE_MESHMODEL_OP_RELAY_SET ESP _BLE_MES _MODEL_OP _MODEL_PUB_SET ESP_BLE-MESH_MODL_OP_MODEL_SUB_ADD _BLE_MESH_MODEL_OP_MODEL_SUB重写ESP_BLE_MESH_MODE_OP_MODEL_SUB_VIRTUAL_ADDR_OVERWRITE ESP_BLE_MESH_MODL_OP_NET_KEY_ADD ESP_BLE-MESH_MODEL_OP_APP_KEY_ADD ESP_BLE.MESH_MODAL_OP_MODEL_OP_MODEL_APP_BIND ESP_BLE ESP_MESH_MODE OP_NODE_RESET函数不应设置为NULL。
 */
typedef union {
    esp_ble_mesh_cfg_beacon_set_t             beacon_set;             /*!< 对于ESP_BLE_MESH_MODEL_OP_BECON_SET*/
    esp_ble_mesh_cfg_default_ttl_set_t        default_ttl_set;        /*!< 对于ESP_BLE_MESH_MODEL_OP_DEFULT_TTL_SET*/
    esp_ble_mesh_cfg_friend_set_t             friend_set;             /*!< 对于ESP_BLE_MESH_MODEL_OP_FRIEND_SET*/
    esp_ble_mesh_cfg_gatt_proxy_set_t         gatt_proxy_set;         /*!< 对于ESP_BLE_MESH_MODEL_OP_GATT_PROXY_SET*/
    esp_ble_mesh_cfg_relay_set_t              relay_set;              /*!< 对于ESP_BLE_MESH_MODEL_OP_LAY_SET*/
    esp_ble_mesh_cfg_net_key_add_t            net_key_add;            /*!< 对于ESP_BLE_MESH_MODEL_OP_NET_KEY_ADD*/
    esp_ble_mesh_cfg_app_key_add_t            app_key_add;            /*!< 对于ESP_BLE_MESH_MODEL_OP_APP_KEY_ADD*/
    esp_ble_mesh_cfg_model_app_bind_t         model_app_bind;         /*!< 对于ESP_BLE_MESH_MODEL_OP_MODEL_APP_BIND*/
    esp_ble_mesh_cfg_model_pub_set_t          model_pub_set;          /*!< 对于ESP_BLE_MESH_MODEL_OP_MODEL_PUB_SET*/
    esp_ble_mesh_cfg_model_sub_add_t          model_sub_add;          /*!< 对于ESP_BLE_MESH_MODEL_OP_MODEL_SUB_ADD*/
    esp_ble_mesh_cfg_model_sub_delete_t       model_sub_delete;       /*!< 对于ESP_BLE_MESH_MODEL_OP_MODEL_SUB_DELETE*/
    esp_ble_mesh_cfg_model_sub_overwrite_t    model_sub_overwrite;    /*!< 对于ESP_BLE_MESH_MODEL_OP_MODEL_SUB_OVERWRITE*/
    esp_ble_mesh_cfg_model_sub_va_add_t       model_sub_va_add;       /*!< 对于ESP_BLE_MESH_MODEL_OP_MODEL_SUB_VIRTUAL_ADDR_ADD*/
    esp_ble_mesh_cfg_model_sub_va_delete_t    model_sub_va_delete;    /*!< 对于ESP_BLE_MESH_MODEL_OP_MODEL_SUB_VIRTUAL_ADDR_DELETE*/
    esp_ble_mesh_cfg_model_sub_va_overwrite_t model_sub_va_overwrite; /*!< 对于ESP_BLE_MESH_MODEL_OP_MODEL_SUB_VIRTUAL_ADDR_OVERWRITE*/
    esp_ble_mesh_cfg_heartbeat_pub_set_t      heartbeat_pub_set;      /*!< 对于ESP_BLE_MESH_MODEL_OP_HEARTBAT_PUB_SET*/
    esp_ble_mesh_cfg_heartbeat_sub_set_t      heartbeat_sub_set;      /*!< 对于ESP_BLE_MESH_MODEL_OP_HEARTBEAT_SUB_SET*/
    esp_ble_mesh_cfg_model_pub_va_set_t       model_pub_va_set;       /*!< 对于ESP_BLE_MESH_MODEL_OP_MODEL_PUB_VIRTUAL_ADDR_SET*/
    esp_ble_mesh_cfg_model_sub_delete_all_t   model_sub_delete_all;   /*!< 对于ESP_BLE_MESH_MODEL_OP_MODEL_SUB_DELETE_ALL*/
    esp_ble_mesh_cfg_net_key_update_t         net_key_update;         /*!< 对于ESP_BLE_MESH_MODEL_OP_NET_KEY_UPDATE*/
    esp_ble_mesh_cfg_net_key_delete_t         net_key_delete;         /*!< 对于ESP_BLE_MESH_MODEL_OP_NET_KEY_DELETE*/
    esp_ble_mesh_cfg_app_key_update_t         app_key_update;         /*!< 对于ESP_BLE_MESH_MODEL_OP_APP_KEY_UPDATE*/
    esp_ble_mesh_cfg_app_key_delete_t         app_key_delete;         /*!< 对于ESP_BLE_MESH_MODEL_OP_APP_KEY_DELETE*/
    esp_ble_mesh_cfg_node_identity_set_t      node_identity_set;      /*!< 对于ESP_BLE_MESH_MODEL_OP_NODE_IDENTITY_SET*/
    esp_ble_mesh_cfg_model_app_unbind_t       model_app_unbind;       /*!< 对于ESP_BLE_MESH_MODEL_OP_MODEL_APP_UNBIND*/
    esp_ble_mesh_cfg_kr_phase_set_t           kr_phase_set;           /*!< 对于ESP_BLE_MESH_MODEL_OP_KEY_REFRESH_PHASE_SET*/
    esp_ble_mesh_cfg_net_transmit_set_t       net_transmit_set;       /*!< 对于ESP_BLE_MESH_MODEL_OP_NETWORK_TRANSMIT_SET*/
} esp_ble_mesh_cfg_client_set_state_t;

/**配置信标状态参数*/
typedef struct {
    uint8_t beacon;                     /*!< 安全网络信标状态值*/
} esp_ble_mesh_cfg_beacon_status_cb_t;

/**配置组成数据状态参数*/
typedef struct {
    uint8_t page;                              /*!< 成分数据页码*/
    struct net_buf_simple *composition_data;   /*!< 指向所标识页面的合成数据的指针*/
} esp_ble_mesh_cfg_comp_data_status_cb_t;

/**配置默认TTL状态参数*/
typedef struct {
    uint8_t default_ttl;                /*!< 默认TTL状态值*/
} esp_ble_mesh_cfg_default_ttl_status_cb_t;

/**配置GATT代理状态参数*/
typedef struct {
    uint8_t gatt_proxy;                 /*!< GATT代理状态值*/
} esp_ble_mesh_cfg_gatt_proxy_status_cb_t;

/**配置继电器状态参数*/
typedef struct {
    uint8_t relay;                      /*!< 继电器状态值*/
    uint8_t retransmit;                 /*!< 中继重传值（重传次数和重传之间的10毫秒步数）*/
} esp_ble_mesh_cfg_relay_status_cb_t;

/**配置模型发布状态参数*/
typedef struct {
    uint8_t  status;                    /*!< 请求消息的状态代码*/
    uint16_t element_addr;              /*!< 元素的地址*/
    uint16_t publish_addr;              /*!< 发布地址的值*/
    uint16_t app_idx;                   /*!< 应用程序密钥的索引*/
    bool     cred_flag;                 /*!< 友谊证书旗帜的价值*/
    uint8_t  ttl;                       /*!< 传出消息的默认TTL值*/
    uint8_t  period;                    /*!< 定期状态发布的周期*/
    uint8_t  transmit;                  /*!< 重传次数和重传之间的50毫秒步数*/
    uint16_t company_id;                /*!< 公司ID*/
    uint16_t model_id;                  /*!< 型号ID*/
} esp_ble_mesh_cfg_model_pub_status_cb_t;

/**配置模型订阅状态参数*/
typedef struct {
    uint8_t  status;                    /*!< 请求消息的状态代码*/
    uint16_t element_addr;              /*!< 元素的地址*/
    uint16_t sub_addr;                  /*!< 地址的值*/
    uint16_t company_id;                /*!< 公司ID*/
    uint16_t model_id;                  /*!< 型号ID*/
} esp_ble_mesh_cfg_model_sub_status_cb_t;

/**配置NetKey状态参数*/
typedef struct {
    uint8_t  status;                    /*!< 请求消息的状态代码*/
    uint16_t net_idx;                   /*!< NetKey索引*/
} esp_ble_mesh_cfg_net_key_status_cb_t;

/**Config AppKey状态参数*/
typedef struct {
    uint8_t  status;                    /*!< 请求消息的状态代码*/
    uint16_t net_idx;                   /*!< NetKey索引*/
    uint16_t app_idx;                   /*!< 应用程序密钥的索引*/
} esp_ble_mesh_cfg_app_key_status_cb_t;

/**配置模型应用程序状态参数*/
typedef struct {
    uint8_t  status;                    /*!< 请求消息的状态代码*/
    uint16_t element_addr;              /*!< 元素的地址*/
    uint16_t app_idx;                   /*!< 应用程序密钥的索引*/
    uint16_t company_id;                /*!< 公司ID*/
    uint16_t model_id;                  /*!< 型号ID*/
} esp_ble_mesh_cfg_mod_app_status_cb_t;

/**配置好友状态参数*/
typedef struct {
    uint8_t friend_state;               /*!< 好友状态值*/
} esp_ble_mesh_cfg_friend_status_cb_t;

/**配置心跳发布状态参数*/
typedef struct {
    uint8_t  status;                    /*!< 请求消息的状态代码*/
    uint16_t dst;                       /*!< 心跳消息的目标地址*/
    uint8_t  count;                     /*!< 剩余待发送的心跳消息数*/
    uint8_t  period;                    /*!< 发送心跳消息的时间段*/
    uint8_t  ttl;                       /*!< 发送心跳消息时使用的TTL*/
    uint16_t features;                  /*!< 更改时触发心跳消息的功能*/
    uint16_t net_idx;                   /*!< NetKey索引*/
} esp_ble_mesh_cfg_hb_pub_status_cb_t;

/**配置心跳订阅状态参数*/
typedef struct {
    uint8_t  status;                    /*!< 请求消息的状态代码*/
    uint16_t src;                       /*!< 心跳消息的源地址*/
    uint16_t dst;                       /*!< 心跳消息的目标地址*/
    uint8_t  period;                    /*!< 处理心跳消息的剩余时间段*/
    uint8_t  count;                     /*!< 接收的心跳消息数*/
    uint8_t  min_hops;                  /*!< 接收心跳消息时的最小跳数*/
    uint8_t  max_hops;                  /*!< 接收心跳消息时的最大跳数*/
} esp_ble_mesh_cfg_hb_sub_status_cb_t;

/**配置网络传输状态参数*/
typedef struct {
    uint8_t net_trans_count: 3;         /*!< 源自节点的每个网络PDU的传输数*/
    uint8_t net_trans_step : 5;         /*!< 接收心跳消息时的最大跳数*/
} esp_ble_mesh_cfg_net_trans_status_cb_t;

/**配置SIG/供应商订阅列表参数*/
typedef struct {
    uint8_t  status;                    /*!< 请求消息的状态代码*/
    uint16_t element_addr;              /*!< 元素的地址*/
    uint16_t company_id;                /*!< 公司ID*/
    uint16_t model_id;                  /*!< 型号ID*/
    struct net_buf_simple *sub_addr;    /*!< 订阅列表中所有地址的块*/
} esp_ble_mesh_cfg_model_sub_list_cb_t;

/**配置网络密钥列表的参数*/
typedef struct {
    struct net_buf_simple *net_idx;     /*!< 节点已知的NetKey索引列表*/
} esp_ble_mesh_cfg_net_key_list_cb_t;

/**配置AppKey列表的参数*/
typedef struct {
    uint8_t  status;                    /*!< 请求消息的状态代码*/
    uint16_t net_idx;                   /*!< AppKey绑定到的NetKey的NetKey索引*/
    struct net_buf_simple *app_idx;     /*!< 绑定到由NetKeyIndex标识的NetKey的AppKey索引列表*/
} esp_ble_mesh_cfg_app_key_list_cb_t;

/**配置节点标识状态参数*/
typedef struct {
    uint8_t  status;                    /*!< 请求消息的状态代码*/
    uint16_t net_idx;                   /*!< NetKey索引*/
    uint8_t  identity;                  /*!< 节点标识状态*/
} esp_ble_mesh_cfg_node_id_status_cb_t;

/**配置SIG/供应商模型应用程序列表参数*/
typedef struct {
    uint8_t  status;                    /*!< 请求消息的状态代码*/
    uint16_t element_addr;              /*!< 元素的地址*/
    uint16_t company_id;                /*!< 公司ID*/
    uint16_t model_id;                  /*!< 型号ID*/
    struct net_buf_simple *app_idx;     /*!< 绑定到模型的所有AppKey索引*/
} esp_ble_mesh_cfg_model_app_list_cb_t;

/**配置密钥刷新阶段状态参数*/
typedef struct {
    uint8_t  status;                    /*!< 请求消息的状态代码*/
    uint16_t net_idx;                   /*!< NetKey索引*/
    uint8_t  phase;                     /*!< 密钥刷新阶段状态*/
} esp_ble_mesh_cfg_kr_phase_status_cb_t;

/**配置低功耗节点轮询超时状态参数*/
typedef struct {
    uint16_t lpn_addr;                  /*!< 低功耗节点的单播地址*/
    int32_t  poll_timeout;              /*!< 低功耗节点的轮询超时计时器的当前值*/
} esp_ble_mesh_cfg_lpn_pollto_status_cb_t;

/**
 * @brief 配置客户端模型接收到消息联合
 */
typedef union {
    esp_ble_mesh_cfg_beacon_status_cb_t      beacon_status;         /*!< 信标状态值*/
    esp_ble_mesh_cfg_comp_data_status_cb_t   comp_data_status;      /*!< 合成数据状态值*/
    esp_ble_mesh_cfg_default_ttl_status_cb_t default_ttl_status;    /*!< default_ttl状态值*/
    esp_ble_mesh_cfg_gatt_proxy_status_cb_t  gatt_proxy_status;     /*!< gatt_proxy状态值*/
    esp_ble_mesh_cfg_relay_status_cb_t       relay_status;          /*!< 继电器状态值*/
    esp_ble_mesh_cfg_model_pub_status_cb_t   model_pub_status;      /*!< 模型发布状态值*/
    esp_ble_mesh_cfg_model_sub_status_cb_t   model_sub_status;      /*!< 模型订阅状态值*/
    esp_ble_mesh_cfg_net_key_status_cb_t     netkey_status;         /*!< 网络密钥状态值*/
    esp_ble_mesh_cfg_app_key_status_cb_t     appkey_status;         /*!< appkey状态值*/
    esp_ble_mesh_cfg_mod_app_status_cb_t     model_app_status;      /*!< 模型应用程序状态值*/
    esp_ble_mesh_cfg_friend_status_cb_t      friend_status;         /*!< 好友状态值*/
    esp_ble_mesh_cfg_hb_pub_status_cb_t      heartbeat_pub_status;  /*!< 心跳发布状态值*/
    esp_ble_mesh_cfg_hb_sub_status_cb_t      heartbeat_sub_status;  /*!< 心跳订阅状态值*/
    esp_ble_mesh_cfg_net_trans_status_cb_t   net_transmit_status;   /*!< 网络传输状态值*/
    esp_ble_mesh_cfg_model_sub_list_cb_t     model_sub_list;        /*!< 模型订阅列表值*/
    esp_ble_mesh_cfg_net_key_list_cb_t       netkey_list;           /*!< 网络密钥索引列表值*/
    esp_ble_mesh_cfg_app_key_list_cb_t       appkey_list;           /*!< 应用程序键索引列表值*/
    esp_ble_mesh_cfg_node_id_status_cb_t     node_identity_status;  /*!< 节点标识状态值*/
    esp_ble_mesh_cfg_model_app_list_cb_t     model_app_list;        /*!< 模型应用程序键索引列表值*/
    esp_ble_mesh_cfg_kr_phase_status_cb_t    kr_phase_status;       /*!< 密钥刷新阶段状态值*/
    esp_ble_mesh_cfg_lpn_pollto_status_cb_t  lpn_timeout_status;    /*!< 低功耗节点轮询超时状态值*/
} esp_ble_mesh_cfg_client_common_cb_param_t;

/**配置客户端模型回调参数*/
typedef struct {
    int error_code;                                         /*!< 适当的错误代码*/
    esp_ble_mesh_client_common_param_t       *params;       /*!< 客户端通用参数*/
    esp_ble_mesh_cfg_client_common_cb_param_t status_cb;    /*!< 配置状态消息回调值*/
} esp_ble_mesh_cfg_client_cb_param_t;

/**此枚举值是配置客户端模型的事件*/
typedef enum {
    ESP_BLE_MESH_CFG_CLIENT_GET_STATE_EVT,
    ESP_BLE_MESH_CFG_CLIENT_SET_STATE_EVT,
    ESP_BLE_MESH_CFG_CLIENT_PUBLISH_EVT,
    ESP_BLE_MESH_CFG_CLIENT_TIMEOUT_EVT,
    ESP_BLE_MESH_CFG_CLIENT_EVT_MAX,
} esp_ble_mesh_cfg_client_cb_event_t;

/**
 * @brief 配置服务器模型相关上下文。
 */

typedef struct {
    uint16_t element_addr;      /*!< 元素地址*/
    uint16_t pub_addr;          /*!< 发布地址*/
    uint16_t app_idx;           /*!< AppKey索引*/
    bool     cred_flag;         /*!< 友谊凭据标志*/
    uint8_t  pub_ttl;           /*!< 发布TTL*/
    uint8_t  pub_period;        /*!< 发布时间段*/
    uint8_t  pub_retransmit;    /*!< 发布重新传输*/
    uint16_t company_id;        /*!< 公司ID*/
    uint16_t model_id;          /*!< 型号ID*/
} esp_ble_mesh_state_change_cfg_mod_pub_set_t;

/**配置模型订阅添加参数*/
typedef struct {
    uint16_t element_addr;      /*!< 元素地址*/
    uint16_t sub_addr;          /*!< 订阅地址*/
    uint16_t company_id;        /*!< 公司ID*/
    uint16_t model_id;          /*!< 型号ID*/
} esp_ble_mesh_state_change_cfg_model_sub_add_t;

/**配置模型订阅删除参数*/
typedef struct {
    uint16_t element_addr;      /*!< 元素地址*/
    uint16_t sub_addr;          /*!< 订阅地址*/
    uint16_t company_id;        /*!< 公司ID*/
    uint16_t model_id;          /*!< 型号ID*/
} esp_ble_mesh_state_change_cfg_model_sub_delete_t;

/**Config NetKey Add参数*/
typedef struct {
    uint16_t net_idx;           /*!< NetKey索引*/
    uint8_t  net_key[16];       /*!< 网络密钥*/
} esp_ble_mesh_state_change_cfg_netkey_add_t;

/**配置NetKey更新参数*/
typedef struct {
    uint16_t net_idx;           /*!< NetKey索引*/
    uint8_t  net_key[16];       /*!< 网络密钥*/
} esp_ble_mesh_state_change_cfg_netkey_update_t;

/**Config NetKey Delete参数*/
typedef struct {
    uint16_t net_idx;           /*!< NetKey索引*/
} esp_ble_mesh_state_change_cfg_netkey_delete_t;

/**Config AppKey Add的参数*/
typedef struct {
    uint16_t net_idx;           /*!< NetKey索引*/
    uint16_t app_idx;           /*!< AppKey索引*/
    uint8_t  app_key[16];       /*!< 应用程序密钥*/
} esp_ble_mesh_state_change_cfg_appkey_add_t;

/**Config AppKey更新的参数*/
typedef struct {
    uint16_t net_idx;           /*!< NetKey索引*/
    uint16_t app_idx;           /*!< AppKey索引*/
    uint8_t  app_key[16];       /*!< 应用程序密钥*/
} esp_ble_mesh_state_change_cfg_appkey_update_t;

/**Config AppKey Delete参数*/
typedef struct {
    uint16_t net_idx;           /*!< NetKey索引*/
    uint16_t app_idx;           /*!< AppKey索引*/
} esp_ble_mesh_state_change_cfg_appkey_delete_t;

/**配置模型应用程序绑定的参数*/
typedef struct {
    uint16_t element_addr;      /*!< 元素地址*/
    uint16_t app_idx;           /*!< AppKey索引*/
    uint16_t company_id;        /*!< 公司ID*/
    uint16_t model_id;          /*!< 型号ID*/
} esp_ble_mesh_state_change_cfg_model_app_bind_t;

/**配置模型应用程序解除绑定的参数*/
typedef struct {
    uint16_t element_addr;      /*!< 元素地址*/
    uint16_t app_idx;           /*!< AppKey索引*/
    uint16_t company_id;        /*!< 公司ID*/
    uint16_t model_id;          /*!< 型号ID*/
} esp_ble_mesh_state_change_cfg_model_app_unbind_t;

/**配置密钥刷新阶段集的参数*/
typedef struct {
    uint16_t net_idx;           /*!< NetKey索引*/
    uint8_t  kr_phase;          /*!< 新密钥刷新阶段转换*/
} esp_ble_mesh_state_change_cfg_kr_phase_set_t;

/**
 * @brief Configuration Server模型状态更改值联合
 */
typedef union {
    /**
     * ctx中的recv_op可用于决定更改的状态。
     */
    esp_ble_mesh_state_change_cfg_mod_pub_set_t         mod_pub_set;        /*!< 配置模型发布集*/
    esp_ble_mesh_state_change_cfg_model_sub_add_t       mod_sub_add;        /*!< 配置模型订阅添加*/
    esp_ble_mesh_state_change_cfg_model_sub_delete_t    mod_sub_delete;     /*!< 配置模型订阅删除*/
    esp_ble_mesh_state_change_cfg_netkey_add_t          netkey_add;         /*!< 配置NetKey添加*/
    esp_ble_mesh_state_change_cfg_netkey_update_t       netkey_update;      /*!< 配置NetKey更新*/
    esp_ble_mesh_state_change_cfg_netkey_delete_t       netkey_delete;      /*!< 配置NetKey删除*/
    esp_ble_mesh_state_change_cfg_appkey_add_t          appkey_add;         /*!< 配置AppKey添加*/
    esp_ble_mesh_state_change_cfg_appkey_update_t       appkey_update;      /*!< 配置AppKey更新*/
    esp_ble_mesh_state_change_cfg_appkey_delete_t       appkey_delete;      /*!< 配置AppKey删除*/
    esp_ble_mesh_state_change_cfg_model_app_bind_t      mod_app_bind;       /*!< 配置模型应用程序绑定*/
    esp_ble_mesh_state_change_cfg_model_app_unbind_t    mod_app_unbind;     /*!< 配置模型应用程序解除绑定*/
    esp_ble_mesh_state_change_cfg_kr_phase_set_t        kr_phase_set;       /*!< 配置密钥刷新阶段集*/
} esp_ble_mesh_cfg_server_state_change_t;

/**
 * @brief Configuration Server模型回调值联合
 */
typedef union {
    esp_ble_mesh_cfg_server_state_change_t state_change;  /*!< ESP_BLE_MESH_CFG_SERVER_STATE_CHANGE_EVT */
} esp_ble_mesh_cfg_server_cb_value_t;

/**配置服务器模型回调参数*/
typedef struct {
    esp_ble_mesh_model_t  *model;   /*!< 指向服务器模型结构的指针*/
    esp_ble_mesh_msg_ctx_t ctx;     /*!< 收到消息的上下文*/
    esp_ble_mesh_cfg_server_cb_value_t value;   /*!< 收到的配置消息的值*/
} esp_ble_mesh_cfg_server_cb_param_t;

/**此枚举值是Configuration Server模型的事件*/
typedef enum {
    ESP_BLE_MESH_CFG_SERVER_STATE_CHANGE_EVT,
    ESP_BLE_MESH_CFG_SERVER_EVT_MAX,
} esp_ble_mesh_cfg_server_cb_event_t;

/**
 *  @brief 蓝牙网格配置客户端和服务器模型功能。
 */

/**
 * @brief   配置客户端模型回调函数类型
 * @param   event: 事件类型
 * @param   param: 指向回调参数的指针
 */
typedef void (* esp_ble_mesh_cfg_client_cb_t)(esp_ble_mesh_cfg_client_cb_event_t event,
                                              esp_ble_mesh_cfg_client_cb_param_t *param);

/**
 * @brief   配置服务器模型回调函数类型
 * @param   event: 事件类型
 * @param   param: 指向回调参数的指针
 */
typedef void (* esp_ble_mesh_cfg_server_cb_t)(esp_ble_mesh_cfg_server_cb_event_t event,
                                              esp_ble_mesh_cfg_server_cb_param_t *param);

/**
 * @brief         注册BLE Mesh Config Client Model回调。
 *
 * @param[in]     callback: 指向回调函数的指针。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_register_config_client_callback(esp_ble_mesh_cfg_client_cb_t callback);

/**
 * @brief         注册BLE Mesh配置服务器模型回调。
 *
 * @param[in]     callback: 指向回调函数的指针。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_register_config_server_callback(esp_ble_mesh_cfg_server_cb_t callback);

/**
 * @brief         使用Config Client Model Get消息获取Config Server Model状态的值。
 *
 * @note          如果要查找此API接受的操作码和相应含义，请参阅esp_ble_mesh_defs.h中的esp_ble_mesh_opcode_config_client_get_t
 *
 * @param[in]     params:    指向BLE Mesh公共客户端参数的指针。
 * @param[in]     get_state: 指向并集的指针，每种操作码对应于内部的一个结构。不应设置为NULL。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_config_client_get_state(esp_ble_mesh_client_common_param_t *params,
                                               esp_ble_mesh_cfg_client_get_state_t *get_state);

/**
 * @brief         使用配置客户端模型设置消息设置配置服务器模型状态的值。
 *
 * @note          如果要查找此API接受的操作码和相应含义，请参阅esp_ble_mesh_defs.h中的esp_ble_mesh_opcode_config_client_set_t
 *
 * @param[in]     params:    指向BLE Mesh公共客户端参数的指针。
 * @param[in]     set_state: 指向并集的指针，每种操作码对应于内部的一个结构。不应设置为NULL。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_config_client_set_state(esp_ble_mesh_client_common_param_t *params,
                                               esp_ble_mesh_cfg_client_set_state_t *set_state);

#ifdef __cplusplus
}
#endif

#endif /* _ESP_BLE_MESH_CONFIG_MODEL_API_H_ */

