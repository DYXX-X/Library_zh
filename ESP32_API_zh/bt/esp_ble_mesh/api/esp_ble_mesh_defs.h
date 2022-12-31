/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _ESP_BLE_MESH_DEFS_H_
#define _ESP_BLE_MESH_DEFS_H_

#include <stdint.h>

#include "mesh_config.h"
#include "mesh_common.h"
#include "proxy_server.h"
#include "provisioner_main.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!< BLE Mesh消息的最大长度，包括Opcode、Payload和TransMIC*/
#define ESP_BLE_MESH_SDU_MAX_LEN            384

/*!< 短网眼MIC的长度。*/
#define ESP_BLE_MESH_MIC_SHORT              4

/*!< 长网眼MIC的长度。*/
#define ESP_BLE_MESH_MIC_LONG               8

/*!< BLE Mesh配置的节点名称的最大长度*/
#define ESP_BLE_MESH_NODE_NAME_MAX_LEN      31

/*!< BLE Mesh未配置设备名称的最大长度*/
#define ESP_BLE_MESH_DEVICE_NAME_MAX_LEN    DEVICE_NAME_SIZE

/*!< 设置用户id的最大长度*/
#define ESP_BLE_MESH_SETTINGS_UID_SIZE      20

/*!< 设置索引无效*/
#define ESP_BLE_MESH_INVALID_SETTINGS_IDX   0xFF

/*!< 定义BLE网格八位字节16字节大小*/
#define ESP_BLE_MESH_OCTET16_LEN    16
typedef uint8_t esp_ble_mesh_octet16_t[ESP_BLE_MESH_OCTET16_LEN];

/*!< 定义BLE Mesh八位字节大小*/
#define ESP_BLE_MESH_OCTET8_LEN     8
typedef uint8_t esp_ble_mesh_octet8_t[ESP_BLE_MESH_OCTET8_LEN];

/*!< 公司ID无效*/
#define ESP_BLE_MESH_CID_NVAL                     0xFFFF

/*!< 使用配置的默认TTL请求特殊TTL值*/
#define ESP_BLE_MESH_TTL_DEFAULT                  0xFF

/*!< 允许的最大TTL值*/
#define ESP_BLE_MESH_TTL_MAX                      0x7F

#define ESP_BLE_MESH_ADDR_UNASSIGNED              0x0000
#define ESP_BLE_MESH_ADDR_ALL_NODES               0xFFFF
#define ESP_BLE_MESH_ADDR_PROXIES                 0xFFFC
#define ESP_BLE_MESH_ADDR_FRIENDS                 0xFFFD
#define ESP_BLE_MESH_ADDR_RELAYS                  0xFFFE

#define ESP_BLE_MESH_KEY_UNUSED                   0xFFFF
#define ESP_BLE_MESH_KEY_DEV                      0xFFFE

#define ESP_BLE_MESH_KEY_PRIMARY                  0x0000
#define ESP_BLE_MESH_KEY_ANY                      0xFFFF

/*!< 主要网络密钥索引*/
#define ESP_BLE_MESH_NET_PRIMARY                  0x000

/*!< 继电器状态值*/
#define ESP_BLE_MESH_RELAY_DISABLED               0x00
#define ESP_BLE_MESH_RELAY_ENABLED                0x01
#define ESP_BLE_MESH_RELAY_NOT_SUPPORTED          0x02

/*!< 信标状态值*/
#define ESP_BLE_MESH_BEACON_DISABLED              0x00
#define ESP_BLE_MESH_BEACON_ENABLED               0x01

/*!< GATT代理状态值*/
#define ESP_BLE_MESH_GATT_PROXY_DISABLED          0x00
#define ESP_BLE_MESH_GATT_PROXY_ENABLED           0x01
#define ESP_BLE_MESH_GATT_PROXY_NOT_SUPPORTED     0x02

/*!< 好友状态值*/
#define ESP_BLE_MESH_FRIEND_DISABLED              0x00
#define ESP_BLE_MESH_FRIEND_ENABLED               0x01
#define ESP_BLE_MESH_FRIEND_NOT_SUPPORTED         0x02

/*!< 节点标识状态值*/
#define ESP_BLE_MESH_NODE_IDENTITY_STOPPED        0x00
#define ESP_BLE_MESH_NODE_IDENTITY_RUNNING        0x01
#define ESP_BLE_MESH_NODE_IDENTITY_NOT_SUPPORTED  0x02

/*!< 支持的功能*/
#define ESP_BLE_MESH_FEATURE_RELAY                BIT(0)
#define ESP_BLE_MESH_FEATURE_PROXY                BIT(1)
#define ESP_BLE_MESH_FEATURE_FRIEND               BIT(2)
#define ESP_BLE_MESH_FEATURE_LOW_POWER            BIT(3)
#define ESP_BLE_MESH_FEATURE_ALL_SUPPORTED        (ESP_BLE_MESH_FEATURE_RELAY |     \
                                                   ESP_BLE_MESH_FEATURE_PROXY |     \
                                                   ESP_BLE_MESH_FEATURE_FRIEND |    \
                                                   ESP_BLE_MESH_FEATURE_LOW_POWER)

#define ESP_BLE_MESH_ADDR_IS_UNICAST(addr)        ((addr) && (addr) < 0x8000)
#define ESP_BLE_MESH_ADDR_IS_GROUP(addr)          ((addr) >= 0xC000 && (addr) <= 0xFF00)
#define ESP_BLE_MESH_ADDR_IS_VIRTUAL(addr)        ((addr) >= 0x8000 && (addr) < 0xC000)
#define ESP_BLE_MESH_ADDR_IS_RFU(addr)            ((addr) >= 0xFF00 && (addr) <= 0xFFFB)

#define ESP_BLE_MESH_INVALID_NODE_INDEX           0xFFFF

/** @def    ESP_BLE_MESH_TRANSMIT
 *
 *  @brief  编码传输计数和间隔步长。
 *
 *  @note   例如，ESP_BLE_MESH_TRANSMIT（2，20）表示消息将被发送大约90ms（计数为3，步长为1，间隔为30ms，包括10ms的广告间隔随机延迟）。
 *
 *  @param  count   重传次数（排除第一次传输）。
 *  @param  int_ms  间隔步数（毫秒）。必须大于0和10的倍数。
 *
 *  @return BLE Mesh传输值，可用于配置模型数据的默认值。
 */
#define ESP_BLE_MESH_TRANSMIT(count, int_ms)    ((count) | (((int_ms / 10) - 1) << 3))

/** @def ESP_BLE_MESH_GET_TRANSMIT_COUNT
 *
 *  @brief 根据传输值解码传输计数。
 *
 *  @param transmit 编码传输计数和间隔值。
 *
 *  @return 传输计数（实际传输等于N+1）。
 */
#define ESP_BLE_MESH_GET_TRANSMIT_COUNT(transmit)   (((transmit) & (uint8_t)BIT_MASK(3)))

/** @def ESP_BLE_MESH_GET_TRANSMIT_INTERVAL
 *
 *  @brief 根据传输值解码传输间隔。
 *
 *  @param transmit 编码传输计数和间隔值。
 *
 *  @return 传输间隔（毫秒）。
 */
#define ESP_BLE_MESH_GET_TRANSMIT_INTERVAL(transmit)    ((((transmit) >> 3) + 1) * 10)

/** @def ESP_BLE_MESH_PUBLISH_TRANSMIT
 *
 *  @brief 编码发布重新传输计数和间隔步骤。
 *
 *  @param count   重传次数（排除第一次传输）。
 *  @param int_ms  间隔步数（毫秒）。必须大于0和50的倍数。
 *
 *  @return BLE Mesh传输值，可用于配置模型数据的默认值。
 */
#define ESP_BLE_MESH_PUBLISH_TRANSMIT(count, int_ms)    ESP_BLE_MESH_TRANSMIT(count, (int_ms) / 5)

/** @def ESP_BLE_MESH_GET_PUBLISH_TRANSMIT_COUNT
 *
 *  @brief 从给定值解码发布重新传输计数。
 *
 *  @param transmit 编码的发布重新传输计数和间隔值。
 *
 *  @return 重新传输计数（实际传输等于N+1）。
 */
#define ESP_BLE_MESH_GET_PUBLISH_TRANSMIT_COUNT(transmit)   ESP_BLE_MESH_GET_TRANSMIT_COUNT(transmit)

/** @def ESP_BLE_MESH_GET_PUBLISH_TRANSMIT_INTERVAL
 *
 *  @brief 从给定值解码发布重新传输间隔。
 *
 *  @param transmit 编码的发布重新传输计数和间隔值。
 *
 *  @return 传输间隔（毫秒）。
 */
#define ESP_BLE_MESH_GET_PUBLISH_TRANSMIT_INTERVAL(transmit)    ((((transmit) >> 3) + 1) * 50)

/*!< 不需要用户初始化的回调（设置为0，将在内部初始化）*/
typedef uint32_t esp_ble_mesh_cb_t;

typedef enum {
    ESP_BLE_MESH_TYPE_PROV_CB,
    ESP_BLE_MESH_TYPE_OUTPUT_NUM_CB,
    ESP_BLE_MESH_TYPE_OUTPUT_STR_CB,
    ESP_BLE_MESH_TYPE_INTPUT_CB,
    ESP_BLE_MESH_TYPE_LINK_OPEN_CB,
    ESP_BLE_MESH_TYPE_LINK_CLOSE_CB,
    ESP_BLE_MESH_TYPE_COMPLETE_CB,
    ESP_BLE_MESH_TYPE_RESET_CB,
} esp_ble_mesh_cb_type_t;

/*!< 此枚举值是设置身份验证oob方法*/
typedef enum {
    ESP_BLE_MESH_NO_OOB,
    ESP_BLE_MESH_STATIC_OOB,
    ESP_BLE_MESH_OUTPUT_OOB,
    ESP_BLE_MESH_INPUT_OOB,
} esp_ble_mesh_oob_method_t;

/*!< 此枚举值与mesh_main中的bt_mesh_output_action_t关联。小时*/
typedef enum {
    ESP_BLE_MESH_NO_OUTPUT       = 0,
    ESP_BLE_MESH_BLINK           = BIT(0),
    ESP_BLE_MESH_BEEP            = BIT(1),
    ESP_BLE_MESH_VIBRATE         = BIT(2),
    ESP_BLE_MESH_DISPLAY_NUMBER  = BIT(3),
    ESP_BLE_MESH_DISPLAY_STRING  = BIT(4),
} esp_ble_mesh_output_action_t;

/*!< 此枚举值与mesh_main中的bt_mesh_input_action_t关联。小时*/
typedef enum {
    ESP_BLE_MESH_NO_INPUT      = 0,
    ESP_BLE_MESH_PUSH          = BIT(0),
    ESP_BLE_MESH_TWIST         = BIT(1),
    ESP_BLE_MESH_ENTER_NUMBER  = BIT(2),
    ESP_BLE_MESH_ENTER_STRING  = BIT(3),
} esp_ble_mesh_input_action_t;

/*!< 此枚举值与mesh_main中的bt_mesh_prov_bearer_t相关联。小时*/
typedef enum {
    ESP_BLE_MESH_PROV_ADV   = BIT(0),
    ESP_BLE_MESH_PROV_GATT  = BIT(1),
} esp_ble_mesh_prov_bearer_t;

/*!< 此枚举值与mesh_main中的bt_mesh_prov_oob_info_t相关联。小时*/
typedef enum {
    ESP_BLE_MESH_PROV_OOB_OTHER     = BIT(0),
    ESP_BLE_MESH_PROV_OOB_URI       = BIT(1),
    ESP_BLE_MESH_PROV_OOB_2D_CODE   = BIT(2),
    ESP_BLE_MESH_PROV_OOB_BAR_CODE  = BIT(3),
    ESP_BLE_MESH_PROV_OOB_NFC       = BIT(4),
    ESP_BLE_MESH_PROV_OOB_NUMBER    = BIT(5),
    ESP_BLE_MESH_PROV_OOB_STRING    = BIT(6),
    /* 保留7-10*/
    ESP_BLE_MESH_PROV_OOB_ON_BOX    = BIT(11),
    ESP_BLE_MESH_PROV_OOB_IN_BOX    = BIT(12),
    ESP_BLE_MESH_PROV_OOB_ON_PAPER  = BIT(13),
    ESP_BLE_MESH_PROV_OOB_IN_MANUAL = BIT(14),
    ESP_BLE_MESH_PROV_OOB_ON_DEV    = BIT(15),
} esp_ble_mesh_prov_oob_info_t;

/*!< 静态OOB身份验证使用的最大值长度*/
#define ESP_BLE_MESH_PROV_STATIC_OOB_MAX_LEN    16

/*!< 输出OOB身份验证使用的字符串的最大长度*/
#define ESP_BLE_MESH_PROV_OUTPUT_OOB_MAX_LEN    8

/*!< 输出OOB身份验证使用的字符串的最大长度*/
#define ESP_BLE_MESH_PROV_INPUT_OOB_MAX_LEN     8

/*!< 用于定义消息操作码的宏*/
#define ESP_BLE_MESH_MODEL_OP_1(b0)         (b0)
#define ESP_BLE_MESH_MODEL_OP_2(b0, b1)     (((b0) << 8) | (b1))
#define ESP_BLE_MESH_MODEL_OP_3(b0, cid)    ((((b0) << 16) | 0xC00000) | (cid))

/*!< 此宏与MESH_access中的BLE_MESH_MODEL_CB关联。小时*/
#define ESP_BLE_MESH_SIG_MODEL(_id, _op, _pub, _user_data)          \
{                                                                   \
    .model_id = (_id),                                              \
    .op = _op,                                                      \
    .keys = { [0 ... (CONFIG_BLE_MESH_MODEL_KEY_COUNT - 1)] =       \
            ESP_BLE_MESH_KEY_UNUSED },                              \
    .pub = _pub,                                                    \
    .groups = { [0 ... (CONFIG_BLE_MESH_MODEL_GROUP_COUNT - 1)] =   \
            ESP_BLE_MESH_ADDR_UNASSIGNED },                         \
    .user_data = _user_data,                                        \
}

/*!< 此宏与MESH_access中的BLE_MESH_MODEL_VND_CB关联。小时*/
#define ESP_BLE_MESH_VENDOR_MODEL(_company, _id, _op, _pub, _user_data) \
{                                                                       \
    .vnd.company_id = (_company),                                       \
    .vnd.model_id = (_id),                                              \
    .op = _op,                                                          \
    .pub = _pub,                                                        \
    .keys = { [0 ... (CONFIG_BLE_MESH_MODEL_KEY_COUNT - 1)] =           \
            ESP_BLE_MESH_KEY_UNUSED },                                  \
    .groups = { [0 ... (CONFIG_BLE_MESH_MODEL_GROUP_COUNT - 1)] =       \
            ESP_BLE_MESH_ADDR_UNASSIGNED },                             \
    .user_data = _user_data,                                            \
}

/** @brief 帮助程序在数组中定义BLE Mesh元素。
 *
 *  如果元素没有SIG或Vendor模型，则可以改用帮助宏ESP_BLE_MESH_MODEL_NONE。
 *
 *  @note 此宏与MESH_access.h中的BLE_MESH_ELEM相关联
 *
 *  @param _loc       位置描述符。
 *  @param _mods      SIG模型阵列。
 *  @param _vnd_mods  供应商模型阵列。
 */
#define ESP_BLE_MESH_ELEMENT(_loc, _mods, _vnd_mods)    \
{                                                       \
    .location         = (_loc),                         \
    .sig_model_count  = ARRAY_SIZE(_mods),              \
    .sig_models       = (_mods),                        \
    .vnd_model_count  = ARRAY_SIZE(_vnd_mods),          \
    .vnd_models       = (_vnd_mods),                    \
}

#define ESP_BLE_MESH_PROV(uuid, sta_val, sta_val_len, out_size, out_act, in_size, in_act) { \
    .uuid           = uuid,         \
    .static_val     = sta_val,      \
    .static_val_len = sta_val_len,  \
    .output_size    = out_size,     \
    .output_action  = out_act,      \
    .input_size     = in_size,      \
    .input_action   = in_act,       \
}

typedef uint8_t UINT8;
typedef uint16_t UINT16;
typedef uint32_t UINT32;
typedef uint64_t UINT64;

#define BT_OCTET32_LEN    32
typedef UINT8 BT_OCTET32[BT_OCTET32_LEN];   /* 八位字节数组：大小32*/


#ifndef BD_ADDR_LEN
#define BD_ADDR_LEN     6
typedef uint8_t BD_ADDR[BD_ADDR_LEN];
#endif

typedef uint8_t esp_ble_mesh_bd_addr_t[BD_ADDR_LEN];

#define ESP_BLE_MESH_ADDR_TYPE_PUBLIC       0x00
#define ESP_BLE_MESH_ADDR_TYPE_RANDOM       0x01
#define ESP_BLE_MESH_ADDR_TYPE_RPA_PUBLIC   0x02
#define ESP_BLE_MESH_ADDR_TYPE_RPA_RANDOM   0x03
///BLE设备地址类型
typedef uint8_t esp_ble_mesh_addr_type_t;

/**BLE网格卸载参数*/
typedef struct {
    bool erase_flash;   /*!< 指示卸载网格堆栈时是否擦除闪存*/
} esp_ble_mesh_deinit_param_t;

typedef struct esp_ble_mesh_model esp_ble_mesh_model_t;

/** 描述BLE网格元素的抽象。此结构与mesh_access.h中的结构bt_mesh_elem相关联
 */
typedef struct {
    /**配置期间分配的元素地址。*/
    uint16_t element_addr;

    /**位置描述符（GATT蓝牙命名空间描述符）*/
    const uint16_t location;

    const uint8_t sig_model_count;      /*!< SIG型号计数*/
    const uint8_t vnd_model_count;      /*!< 供应商型号计数*/

    esp_ble_mesh_model_t *sig_models;   /*!< SIG模型*/
    esp_ble_mesh_model_t *vnd_models;   /*!< 供应商型号*/
} esp_ble_mesh_elem_t;

/** 描述模型发布上下文的抽象。此结构与mesh_access.h中的结构bt_mesh_model_pub相关联
 */
typedef struct {
    /**指向上下文所属模型的指针。已由堆栈初始化。*/
    esp_ble_mesh_model_t *model;

    uint16_t publish_addr;  /*!< 发布地址。*/
    uint16_t app_idx:12,    /*!< 发布AppKey索引。*/
             cred:1,        /*!< 友谊证书旗帜。*/
             send_rel:1;    /*!< 强制可靠发送（段ack）*/

    uint8_t  ttl;           /*!< 发布生存时间。*/
    uint8_t  retransmit;    /*!< 重新传输计数和间隔步骤。*/

    uint8_t  period;        /*!< 发布期间。*/
    uint8_t  period_div:4,  /*!< 期间的除数。*/
             fast_period:1, /*!< 使用FastPeriodDivisitor*/
             count:3;       /*!< 重新传输完毕。*/

    uint32_t period_start; /*!< 当前期间的开始时间。*/

    /** @brief 发布缓冲区，包含发布消息。
     *
     *  当使用ESP_BLE_MESH_MODEL_PUB_DEFINE宏定义发布上下文时，将正确创建此上下文。
     *
     *  ESP_BLE_MESH_MODEL_PUB_DEFINE（名称、大小）；
     */
    struct net_buf_simple *msg;

    /**用于更新发布消息的回调。已由堆栈初始化。*/
    esp_ble_mesh_cb_t update;

    /**发布时段计时器。已由堆栈初始化。*/
    struct k_delayed_work timer;

    /**要发布消息的设备的角色*/
    uint8_t dev_role;
} esp_ble_mesh_model_pub_t;

/** @def ESP_BLE_MESH_MODEL_PUB_DEFINE
 *
 *  定义模型发布上下文。
 *
 *  @param _name    给上下文的变量名。
 *  @param _msg_len 发布消息的长度。
 *  @param _role    包含模型的设备的角色。
 */
#define ESP_BLE_MESH_MODEL_PUB_DEFINE(_name, _msg_len, _role) \
    NET_BUF_SIMPLE_DEFINE_STATIC(bt_mesh_pub_msg_##_name, _msg_len); \
    static esp_ble_mesh_model_pub_t _name = { \
        .update = (uint32_t)NULL, \
        .msg = &bt_mesh_pub_msg_##_name, \
        .dev_role = _role, \
    }

/** @def ESP_BLE_MESH_MODEL_OP
 *
 *  定义模型操作上下文。
 *
 *  @param _opcode  消息操作码。
 *  @param _min_len 消息最小长度。
 */
#define ESP_BLE_MESH_MODEL_OP(_opcode, _min_len) \
{ \
    .opcode = _opcode, \
    .min_len = _min_len, \
    .param_cb = (uint32_t)NULL, \
}

/** 描述模型操作上下文的抽象。此结构与mesh_access.h中的结构bt_mesh_model_op相关联
 */
typedef struct {
    const uint32_t    opcode;   /*!< 消息操作码*/
    const size_t      min_len;  /*!< 消息最小长度*/
    esp_ble_mesh_cb_t param_cb; /*!< 用于处理消息的回调。已由堆栈初始化。*/
} esp_ble_mesh_model_op_t;

/** 定义模型操作表的终止符。每个模型操作结构数组必须使用此终止符作为操作单元的结束标记。
 */
#define ESP_BLE_MESH_MODEL_OP_END {0, 0, 0}

/** 描述模型回调结构的抽象。此结构与mesh_access.h中的结构bt_mesh_model_cb相关联。
 */
typedef struct {
    /**模型初始化期间使用的回调。已由堆栈初始化。*/
    esp_ble_mesh_cb_t init_cb;

#if CONFIG_BLE_MESH_DEINIT
    /**模型去初始化期间使用的回调。已由堆栈初始化。*/
    esp_ble_mesh_cb_t deinit_cb;
#endif /* CONFIG_BLE_MESH_DEINIT */
} esp_ble_mesh_model_cbs_t;

/** 描述网格模型实例的抽象。此结构与mesh_access.h中的结构bt_mesh_model相关联
 */
struct esp_ble_mesh_model {
    /**型号ID*/
    union {
        const uint16_t model_id; /*!< 16位型号标识符*/
        struct {
            uint16_t company_id; /*!< 16位公司标识符*/
            uint16_t model_id; /*!< 16位型号标识符*/
        } vnd; /*!< 用公司ID封装模型ID的结构*/
    };

    /**内部信息，主要用于持久性存储*/
    uint8_t  element_idx;   /*!< 属于第N个元素*/
    uint8_t  model_idx;     /*!< 是元素中的第N个模型*/
    uint16_t flags;         /*!< 有关已更改内容的信息*/

    /**此模型所属的元素*/
    esp_ble_mesh_elem_t *element;

    /**模型出版物*/
    esp_ble_mesh_model_pub_t *const pub;

    /**AppKey列表*/
    uint16_t keys[CONFIG_BLE_MESH_MODEL_KEY_COUNT];

    /**订阅列表（组或虚拟地址）*/
    uint16_t groups[CONFIG_BLE_MESH_MODEL_GROUP_COUNT];

    /**模型操作上下文*/
    esp_ble_mesh_model_op_t *op;

    /**模型回调结构*/
    esp_ble_mesh_model_cbs_t *cb;

    /**特定于型号的用户数据*/
    void *user_data;
};

/** 用于定义空模型数组的帮助程序。此结构与MESH_access.h中的BLE_MESH_MODEL_NONE关联
 */
#define ESP_BLE_MESH_MODEL_NONE ((esp_ble_mesh_model_t []){})

/** 消息发送上下文。此结构与mesh_access.h中的结构bt_mesh_msg_ctx相关联
 */
typedef struct {
    /**要通过其发送消息的子网的NetKey索引。*/
    uint16_t net_idx;

    /**消息加密的AppKey索引。*/
    uint16_t app_idx;

    /**远程地址。*/
    uint16_t addr;

    /**接收消息的目标地址。不用于发送。*/
    uint16_t recv_dst;

    /**接收分组的RSSI。不用于发送。*/
    int8_t   recv_rssi;

    /**收到TTL值。不用于发送。*/
    uint8_t  recv_ttl: 7;

    /**使用段确认强制可靠发送*/
    uint8_t  send_rel: 1;

    /**TTL或ESP_BLE_MESH_TTL_DEFAULT（默认TTL）。*/
    uint8_t  send_ttl;

    /**接收消息的操作码。不用于发送消息。*/
    uint32_t recv_op;

    /**消息对应的模型，发送消息前无需初始化*/
    esp_ble_mesh_model_t *model;

    /**指示消息是否由节点服务器模型发送，在发送消息之前无需初始化*/
    bool srv_send;
} esp_ble_mesh_msg_ctx_t;

/** 配置属性和功能。此结构与mesh_access.h中的结构bt_mesh_prov相关联
 */
typedef struct {
#if CONFIG_BLE_MESH_NODE
    /**作为未配置设备进行广告时使用的UUID*/
    const uint8_t *uuid;

    /** 可选URI。这将与未设置的信标分开发布，但是未设置的灯塔将包含其哈希值，因此两者可以由设置者关联。
     */
    const char *uri;

    /**带外信息字段。*/
    esp_ble_mesh_prov_oob_info_t oob_info;

    /* 注意：为了避免遭受暴力攻击（CVE-2020-26559）。蓝牙SIG建议潜在易受攻击的网格提供器支持带外机制来交换公钥。因此，作为一个未配置的设备，它应该使该标志支持使用带外机制交换公钥。
     */
    /**标志指示未配置的设备是否支持OOB公钥*/
    bool oob_pub_key;

    /**用于通知设置OOB公钥的回调。已由堆栈初始化。*/
    esp_ble_mesh_cb_t oob_pub_key_cb;

    /**静态OOB值*/
    const uint8_t *static_val;
    /**静态OOB值长度*/
    uint8_t        static_val_len;

    /**支持的输出OOB的最大大小*/
    uint8_t        output_size;
    /**支持的输出OOB操作*/
    uint16_t       output_actions;

    /**支持的最大输入OOB大小*/
    uint8_t        input_size;
    /**支持的输入OOB操作*/
    uint16_t       input_actions;

    /**用于输出数字的回调。已由堆栈初始化。*/
    esp_ble_mesh_cb_t  output_num_cb;
    /**用于输出字符串的回调。已由堆栈初始化。*/
    esp_ble_mesh_cb_t  output_str_cb;
    /**用于通知输入数字/字符串的回调。已由堆栈初始化。*/
    esp_ble_mesh_cb_t  input_cb;
    /**用于指示链接已打开的回调。已由堆栈初始化。*/
    esp_ble_mesh_cb_t  link_open_cb;
    /**用于指示链接已关闭的回调。已由堆栈初始化。*/
    esp_ble_mesh_cb_t  link_close_cb;
    /**用于指示配置已完成的回调。已由堆栈初始化。*/
    esp_ble_mesh_cb_t  complete_cb;
    /**用于指示节点已重置的回调。已由堆栈初始化。*/
    esp_ble_mesh_cb_t  reset_cb;
#endif /* CONFIG_BLE_MESH_NODE */

#ifdef CONFIG_BLE_MESH_PROVISIONER
    /**配置器设备UUID*/
    const uint8_t *prov_uuid;

    /**提供商的主要元素地址*/
    const uint16_t prov_unicast_addr;

    /**要分配给第一个设备的预增量单播地址值*/
    uint16_t       prov_start_address;

    /**设置邀请PDU中包含的注意计时器*/
    uint8_t        prov_attention;

    /**Provisioner的Provisioning算法*/
    uint8_t        prov_algorithm;

    /* 注意：为了避免遭受暴力攻击（CVE-2020-26559）。蓝牙SIG建议潜在易受攻击的网格提供器使用带外机制来交换公钥。
     */
    /**提供程序公钥oob*/
    uint8_t        prov_pub_key_oob;

    /**用于通知设置设备OOB公钥的回调。已由堆栈初始化。*/
    esp_ble_mesh_cb_t provisioner_prov_read_oob_pub_key;

    /* 注意：Bluetooth SIG建议网格实现在实现允许的情况下，使用所有可用位强制执行随机选择的AuthValue。大的熵有助于确保AuthValue的蛮力，即使是静态AuthValue，也不能在合理的时间内正常完成（CVE-2020-26557）。
     *
     * 使用加密安全的随机数或伪随机数生成器选择的具有最大允许熵（128位）的AuthValue将是最难暴力的。熵降低或以可预测方式生成的AuthValues不会对该漏洞提供相同级别的保护。在每次配置尝试中选择一个新的AuthValue也会使攻击者更难通过每次配置尝试重新启动搜索来发起暴力攻击（CVE-2020-26556）。
     */
    /**Provisioner静态oob值*/
    uint8_t        *prov_static_oob_val;
    /**Provisioner静态oob值长度*/
    uint8_t         prov_static_oob_len;

    /**用于通知输入数字/字符串的回调。已由堆栈初始化。*/
    esp_ble_mesh_cb_t provisioner_prov_input;
    /**用于输出数字/字符串的回调。已由堆栈初始化。*/
    esp_ble_mesh_cb_t provisioner_prov_output;

    /**密钥刷新和IV更新标志*/
    uint8_t        flags;

    /**IV指数*/
    uint32_t       iv_index;

    /**用于指示链接已打开的回调。已由堆栈初始化。*/
    esp_ble_mesh_cb_t  provisioner_link_open;
    /**用于指示链接已关闭的回调。已由堆栈初始化。*/
    esp_ble_mesh_cb_t  provisioner_link_close;
    /**用于指示设备已配置的回调。已由堆栈初始化。*/
    esp_ble_mesh_cb_t  provisioner_prov_comp;
#endif /* CONFIG_BLE_MESH_PROVISIONER */
} esp_ble_mesh_prov_t;

/** 节点合成数据上下文。此结构与mesh_access.h中的结构bt_mesh_comp相关联
 */
typedef struct {
    uint16_t cid;   /*!< 16位SIG分配的公司标识符*/
    uint16_t pid;   /*!< 16位供应商分配的产品标识符*/
    uint16_t vid;   /*!< 16位供应商分配的产品版本标识符*/

    size_t element_count;           /*!< 元素计数*/
    esp_ble_mesh_elem_t *elements;  /*!< 一系列元素*/
} esp_ble_mesh_comp_t;

/*!< 此枚举值是设备的角色*/
typedef enum {
    ROLE_NODE = 0,
    ROLE_PROVISIONER,
    ROLE_FAST_PROV,
} esp_ble_mesh_dev_role_t;

/*!< 将在添加设备时设置的标志。*/
typedef uint8_t esp_ble_mesh_dev_add_flag_t;
#define ADD_DEV_RM_AFTER_PROV_FLAG  BIT(0)  /*!< 成功设置后，将从队列中删除设备*/
#define ADD_DEV_START_PROV_NOW_FLAG BIT(1)  /*!< 立即启动资源调配设备*/
#define ADD_DEV_FLUSHABLE_DEV_FLAG  BIT(2)  /*!< 当队列已满且要添加新设备时，可以删除设备*/

/**要添加以进行配置的设备的信息。*/
typedef struct {
    esp_ble_mesh_bd_addr_t addr;                 /*!< 设备地址*/
    esp_ble_mesh_addr_type_t addr_type;      /*!< 设备地址类型*/
    uint8_t  uuid[16];                  /*!< 设备UUID*/
    uint16_t oob_info;                  /*!< 设备OOB信息*/
    /*!< 如果承载同时启用了PB-ADV和PB-GATT，则不应设置ADD_DEV_START_PROV_NOW_FLAG*/
    esp_ble_mesh_prov_bearer_t bearer;  /*!< 设置承载器*/
} esp_ble_mesh_unprov_dev_add_t;

#define DEL_DEV_ADDR_FLAG BIT(0)
#define DEL_DEV_UUID_FLAG BIT(1)
/**要删除的设备的信息。*/
typedef struct {
    union {
        struct {
            esp_ble_mesh_bd_addr_t addr;         /*!< 设备地址*/
            esp_ble_mesh_addr_type_t addr_type;  /*!< 设备地址类型*/
        };
        uint8_t uuid[16];                   /*!< 设备UUID*/
    };
    uint8_t flag;                           /*!< BIT0：设备地址；BIT1：设备UUID*/
} esp_ble_mesh_device_delete_t;

#define PROV_DATA_NET_IDX_FLAG  BIT(0)
#define PROV_DATA_FLAGS_FLAG    BIT(1)
#define PROV_DATA_IV_INDEX_FLAG BIT(2)
/**将要更新的提供商信息。*/
typedef struct {
    union {
        uint16_t net_idx;   /*!< NetKey索引*/
        uint8_t  flags;     /*!< 旗帜*/
        uint32_t iv_index;  /*!< IV索引*/
    };
    uint8_t flag;           /*!< BIT0:net_idx；BIT1：标志；比特2:iv_index*/
} esp_ble_mesh_prov_data_info_t;

/**已配置节点的信息*/
typedef struct {
    /* 设备信息*/
    esp_ble_mesh_bd_addr_t   addr;      /*!< 节点设备地址*/
    esp_ble_mesh_addr_type_t addr_type; /*!< 节点设备地址类型*/
    uint8_t  dev_uuid[16];  /*!< 设备UUID*/
    uint16_t oob_info;      /*!< 节点OOB信息*/

    /* 资源调配信息*/
    uint16_t unicast_addr;  /*!< 节点单播地址*/
    uint8_t  element_num;   /*!< 节点元素编号*/
    uint16_t net_idx;       /*!< 节点NetKey索引*/
    uint8_t  flags;         /*!< 节点密钥刷新标志和iv更新标志*/
    uint32_t iv_index;      /*!< 节点IV索引*/
    uint8_t  dev_key[16];   /*!< 节点设备密钥*/

    /* 其他信息*/
    char name[ESP_BLE_MESH_NODE_NAME_MAX_LEN + 1]; /*!< 节点名称*/
    uint16_t comp_length;  /*!< 成分数据长度*/
    uint8_t *comp_data;    /*!< 成分数据值*/
} __attribute__((packed)) esp_ble_mesh_node_t;

/**需要设置的快速供应上下文。*/
typedef struct {
    uint16_t unicast_min;   /*!< 用于快速配置的最小单播地址*/
    uint16_t unicast_max;   /*!< 用于快速配置的最大单播地址*/
    uint16_t net_idx;       /*!< 用于快速资源调配的网络密钥索引*/
    uint8_t  flags;         /*!< 用于快速资源调配的标志*/
    uint32_t iv_index;      /*!< IV用于快速资源调配的索引*/
    uint8_t  offset;        /*!< 要比较的UUID的偏移量*/
    uint8_t  match_len;     /*!< 要比较的UUID的长度*/
    uint8_t  match_val[16]; /*!< 要比较的UUID值*/
} esp_ble_mesh_fast_prov_info_t;

/*!< 此枚举值是快速配置的操作*/
typedef enum {
    FAST_PROV_ACT_NONE,
    FAST_PROV_ACT_ENTER,
    FAST_PROV_ACT_SUSPEND,
    FAST_PROV_ACT_EXIT,
    FAST_PROV_ACT_MAX,
} esp_ble_mesh_fast_prov_action_t;

/*!< 此枚举值是代理筛选器的类型*/
typedef enum {
    PROXY_FILTER_WHITELIST,
    PROXY_FILTER_BLACKLIST,
} esp_ble_mesh_proxy_filter_type_t;

/*!< Provisioner心跳过滤器类型*/
#define ESP_BLE_MESH_HEARTBEAT_FILTER_ACCEPTLIST    0x00
#define ESP_BLE_MESH_HEARTBEAT_FILTER_REJECTLIST    0x01

/*!< Provisioner心跳筛选器操作*/
#define ESP_BLE_MESH_HEARTBEAT_FILTER_ADD           0x00
#define ESP_BLE_MESH_HEARTBEAT_FILTER_REMOVE        0x01

/**要设置的Provisioner心跳筛选器信息的上下文*/
typedef struct {
    uint16_t hb_src;    /*!< 心跳源地址（单播地址）*/
    uint16_t hb_dst;    /*!< 心跳目标地址（单播地址或组地址）*/
} esp_ble_mesh_heartbeat_filter_info_t;

/*!< 此枚举值是节点/配置器/快速配置的事件*/
typedef enum {
    ESP_BLE_MESH_PROV_REGISTER_COMP_EVT,                        /*!< 初始化BLE Mesh配置功能和内部数据信息完成事件*/
    ESP_BLE_MESH_NODE_SET_UNPROV_DEV_NAME_COMP_EVT,             /*!< 设置未设置的设备名称完成事件*/
    ESP_BLE_MESH_NODE_PROV_ENABLE_COMP_EVT,                     /*!< 启用节点配置功能完成事件*/
    ESP_BLE_MESH_NODE_PROV_DISABLE_COMP_EVT,                    /*!< 禁用节点配置功能完成事件*/
    ESP_BLE_MESH_NODE_PROV_LINK_OPEN_EVT,                       /*!< 建立BLE Mesh链接事件*/
    ESP_BLE_MESH_NODE_PROV_LINK_CLOSE_EVT,                      /*!< 关闭BLE Mesh链接事件*/
    ESP_BLE_MESH_NODE_PROV_OOB_PUB_KEY_EVT,                     /*!< 生成节点输入OOB公钥事件*/
    ESP_BLE_MESH_NODE_PROV_OUTPUT_NUMBER_EVT,                   /*!< 生成节点输出编号事件*/
    ESP_BLE_MESH_NODE_PROV_OUTPUT_STRING_EVT,                   /*!< 生成节点输出字符串事件*/
    ESP_BLE_MESH_NODE_PROV_INPUT_EVT,                           /*!< 要求用户输入数字或字符串的事件*/
    ESP_BLE_MESH_NODE_PROV_COMPLETE_EVT,                        /*!< 设置完成事件*/
    ESP_BLE_MESH_NODE_PROV_RESET_EVT,                           /*!< 设置重置事件*/
    ESP_BLE_MESH_NODE_PROV_SET_OOB_PUB_KEY_COMP_EVT,            /*!< 节点集oob公钥完成事件*/
    ESP_BLE_MESH_NODE_PROV_INPUT_NUMBER_COMP_EVT,               /*!< 节点输入编号完成事件*/
    ESP_BLE_MESH_NODE_PROV_INPUT_STRING_COMP_EVT,               /*!< 节点输入字符串完成事件*/
    ESP_BLE_MESH_NODE_PROXY_IDENTITY_ENABLE_COMP_EVT,           /*!< 启用BLE Mesh代理身份广告完成事件*/
    ESP_BLE_MESH_NODE_PROXY_GATT_ENABLE_COMP_EVT,               /*!< 启用BLE Mesh GATT代理服务完成事件*/
    ESP_BLE_MESH_NODE_PROXY_GATT_DISABLE_COMP_EVT,              /*!< 禁用BLE Mesh GATT代理服务完成事件*/
    ESP_BLE_MESH_NODE_ADD_LOCAL_NET_KEY_COMP_EVT,               /*!< 节点添加NetKey本地完成事件*/
    ESP_BLE_MESH_NODE_ADD_LOCAL_APP_KEY_COMP_EVT,               /*!< 节点添加AppKey本地完成事件*/
    ESP_BLE_MESH_NODE_BIND_APP_KEY_TO_MODEL_COMP_EVT,           /*!< 节点将AppKey绑定到模型本地完成事件*/
    ESP_BLE_MESH_PROVISIONER_PROV_ENABLE_COMP_EVT,              /*!< 配置程序启用配置功能完成事件*/
    ESP_BLE_MESH_PROVISIONER_PROV_DISABLE_COMP_EVT,             /*!< 配置程序禁用配置功能完成事件*/
    ESP_BLE_MESH_PROVISIONER_RECV_UNPROV_ADV_PKT_EVT,           /*!< 配置器接收未配置的设备信标事件*/
    ESP_BLE_MESH_PROVISIONER_PROV_READ_OOB_PUB_KEY_EVT,         /*!< 配置程序读取未配置的设备OOB公钥事件*/
    ESP_BLE_MESH_PROVISIONER_PROV_INPUT_EVT,                    /*!< 设置过程事件的设置器输入值*/
    ESP_BLE_MESH_PROVISIONER_PROV_OUTPUT_EVT,                   /*!< 设置过程事件的设置器输出值*/
    ESP_BLE_MESH_PROVISIONER_PROV_LINK_OPEN_EVT,                /*!< Provisioner建立BLE Mesh链接事件*/
    ESP_BLE_MESH_PROVISIONER_PROV_LINK_CLOSE_EVT,               /*!< Provisioner关闭BLE Mesh链接事件*/
    ESP_BLE_MESH_PROVISIONER_PROV_COMPLETE_EVT,                 /*!< 配置程序配置完成事件*/
    ESP_BLE_MESH_PROVISIONER_ADD_UNPROV_DEV_COMP_EVT,           /*!< Provisioner将一个设备添加到列表中，该列表包含正在等待/将要配置完成事件的设备*/
    ESP_BLE_MESH_PROVISIONER_PROV_DEV_WITH_ADDR_COMP_EVT,       /*!< 配置程序开始配置未配置的设备完成事件*/
    ESP_BLE_MESH_PROVISIONER_DELETE_DEV_COMP_EVT,               /*!< 配置器从列表中删除设备，关闭与设备完成事件的配置链接*/
    ESP_BLE_MESH_PROVISIONER_SET_DEV_UUID_MATCH_COMP_EVT,       /*!< Provisioner设置要与未配置设备UUID完成事件的一部分进行比较的值*/
    ESP_BLE_MESH_PROVISIONER_SET_PROV_DATA_INFO_COMP_EVT,       /*!< 设置器设置用于设置完成事件的net_idx/flags/iv_index*/
    ESP_BLE_MESH_PROVISIONER_SET_STATIC_OOB_VALUE_COMP_EVT,     /*!< 设置器设置用于设置完成事件的静态oob值*/
    ESP_BLE_MESH_PROVISIONER_SET_PRIMARY_ELEM_ADDR_COMP_EVT,    /*!< 设置器设置主要元素完成事件的单播地址*/
    ESP_BLE_MESH_PROVISIONER_PROV_READ_OOB_PUB_KEY_COMP_EVT,    /*!< 提供程序读取未配置的设备OOB公钥完成事件*/
    ESP_BLE_MESH_PROVISIONER_PROV_INPUT_NUMBER_COMP_EVT,        /*!< Provisioner输入编号完成事件*/
    ESP_BLE_MESH_PROVISIONER_PROV_INPUT_STRING_COMP_EVT,        /*!< 配置程序输入字符串完成事件*/
    ESP_BLE_MESH_PROVISIONER_SET_NODE_NAME_COMP_EVT,            /*!< 配置程序集节点名称完成事件*/
    ESP_BLE_MESH_PROVISIONER_ADD_LOCAL_APP_KEY_COMP_EVT,        /*!< 配置程序添加本地应用程序密钥完成事件*/
    ESP_BLE_MESH_PROVISIONER_UPDATE_LOCAL_APP_KEY_COMP_EVT,     /*!< 配置程序更新本地应用程序密钥完成事件*/
    ESP_BLE_MESH_PROVISIONER_BIND_APP_KEY_TO_MODEL_COMP_EVT,    /*!< 提供程序将本地模型与本地应用程序密钥完成事件绑定*/
    ESP_BLE_MESH_PROVISIONER_ADD_LOCAL_NET_KEY_COMP_EVT,        /*!< 配置程序添加本地网络密钥完成事件*/
    ESP_BLE_MESH_PROVISIONER_UPDATE_LOCAL_NET_KEY_COMP_EVT,     /*!< 配置程序更新本地网络密钥完成事件*/
    ESP_BLE_MESH_PROVISIONER_STORE_NODE_COMP_DATA_COMP_EVT,     /*!< 配置程序存储节点合成数据完成事件*/
    ESP_BLE_MESH_PROVISIONER_DELETE_NODE_WITH_UUID_COMP_EVT,    /*!< 配置程序删除具有uuid完成事件的节点*/
    ESP_BLE_MESH_PROVISIONER_DELETE_NODE_WITH_ADDR_COMP_EVT,    /*!< 配置程序删除具有单播地址完成事件的节点*/
    ESP_BLE_MESH_PROVISIONER_ENABLE_HEARTBEAT_RECV_COMP_EVT,     /*!< 配置程序开始接收心跳消息完成事件*/
    ESP_BLE_MESH_PROVISIONER_SET_HEARTBEAT_FILTER_TYPE_COMP_EVT, /*!< 设置程序设置心跳筛选器类型完成事件*/
    ESP_BLE_MESH_PROVISIONER_SET_HEARTBEAT_FILTER_INFO_COMP_EVT, /*!< 设置器设置心跳筛选器信息完成事件*/
    ESP_BLE_MESH_PROVISIONER_RECV_HEARTBEAT_MESSAGE_EVT,         /*!< 配置程序接收心跳消息事件*/
    ESP_BLE_MESH_PROVISIONER_DRIECT_ERASE_SETTINGS_COMP_EVT,        /*!< Provisioner直接擦除设置完成事件*/
    ESP_BLE_MESH_PROVISIONER_OPEN_SETTINGS_WITH_INDEX_COMP_EVT,     /*!< 带有索引完成事件的配置程序打开设置*/
    ESP_BLE_MESH_PROVISIONER_OPEN_SETTINGS_WITH_UID_COMP_EVT,       /*!< 具有用户id完成事件的配置程序打开设置*/
    ESP_BLE_MESH_PROVISIONER_CLOSE_SETTINGS_WITH_INDEX_COMP_EVT,    /*!< 带有索引完成事件的配置程序关闭设置*/
    ESP_BLE_MESH_PROVISIONER_CLOSE_SETTINGS_WITH_UID_COMP_EVT,      /*!< 具有用户id完成事件的配置程序关闭设置*/
    ESP_BLE_MESH_PROVISIONER_DELETE_SETTINGS_WITH_INDEX_COMP_EVT,   /*!< 带有索引完成事件的配置程序删除设置*/
    ESP_BLE_MESH_PROVISIONER_DELETE_SETTINGS_WITH_UID_COMP_EVT,     /*!< 配置程序删除用户id完成事件的设置*/
    ESP_BLE_MESH_SET_FAST_PROV_INFO_COMP_EVT,                   /*!< 设置快速配置信息（例如单播地址范围、net_idx等）完成事件*/
    ESP_BLE_MESH_SET_FAST_PROV_ACTION_COMP_EVT,                 /*!< 设置快速配置操作完成事件*/
    ESP_BLE_MESH_HEARTBEAT_MESSAGE_RECV_EVT,                    /*!< 接收心跳消息事件*/
    ESP_BLE_MESH_LPN_ENABLE_COMP_EVT,                           /*!< 启用低功耗节点完成事件*/
    ESP_BLE_MESH_LPN_DISABLE_COMP_EVT,                          /*!< 禁用低功耗节点完成事件*/
    ESP_BLE_MESH_LPN_POLL_COMP_EVT,                             /*!< 低功耗节点发送好友轮询完成事件*/
    ESP_BLE_MESH_LPN_FRIENDSHIP_ESTABLISH_EVT,                  /*!< 低功耗节点建立友谊事件*/
    ESP_BLE_MESH_LPN_FRIENDSHIP_TERMINATE_EVT,                  /*!< 低功耗节点终止友谊事件*/
    ESP_BLE_MESH_FRIEND_FRIENDSHIP_ESTABLISH_EVT,               /*!< 好友节点建立友谊事件*/
    ESP_BLE_MESH_FRIEND_FRIENDSHIP_TERMINATE_EVT,               /*!< 朋友节点终止友谊事件*/
    ESP_BLE_MESH_PROXY_CLIENT_RECV_ADV_PKT_EVT,                 /*!< 代理客户端接收网络ID通告数据包事件*/
    ESP_BLE_MESH_PROXY_CLIENT_CONNECTED_EVT,                    /*!< 代理客户端成功建立连接事件*/
    ESP_BLE_MESH_PROXY_CLIENT_DISCONNECTED_EVT,                 /*!< 代理客户端成功终止连接事件*/
    ESP_BLE_MESH_PROXY_CLIENT_RECV_FILTER_STATUS_EVT,           /*!< 代理客户端接收代理筛选器状态事件*/
    ESP_BLE_MESH_PROXY_CLIENT_CONNECT_COMP_EVT,                 /*!< 代理客户端连接完成事件*/
    ESP_BLE_MESH_PROXY_CLIENT_DISCONNECT_COMP_EVT,              /*!< 代理客户端断开连接完成事件*/
    ESP_BLE_MESH_PROXY_CLIENT_SET_FILTER_TYPE_COMP_EVT,         /*!< 代理客户端设置筛选器类型完成事件*/
    ESP_BLE_MESH_PROXY_CLIENT_ADD_FILTER_ADDR_COMP_EVT,         /*!< 代理客户端添加筛选器地址完成事件*/
    ESP_BLE_MESH_PROXY_CLIENT_REMOVE_FILTER_ADDR_COMP_EVT,      /*!< 代理客户端删除筛选器地址完成事件*/
    ESP_BLE_MESH_PROXY_SERVER_CONNECTED_EVT,                    /*!< 代理服务器成功建立连接事件*/
    ESP_BLE_MESH_PROXY_SERVER_DISCONNECTED_EVT,                 /*!< 代理服务器成功终止连接事件*/
    ESP_BLE_MESH_MODEL_SUBSCRIBE_GROUP_ADDR_COMP_EVT,           /*!< 本地模型订阅组地址完成事件*/
    ESP_BLE_MESH_MODEL_UNSUBSCRIBE_GROUP_ADDR_COMP_EVT,         /*!< 本地模型取消订阅组地址完成事件*/
    ESP_BLE_MESH_DEINIT_MESH_COMP_EVT,                          /*!< 取消初始化BLE Mesh堆栈完成事件*/
    ESP_BLE_MESH_PROV_EVT_MAX,
} esp_ble_mesh_prov_cb_event_t;

/**
 * @brief BLE网格节点/配置器回调参数联合
 */
typedef union {
    /**
     * @brief ESP_BLE_MESH_PROV_REGISTER_COMP_EVT
     */
    struct ble_mesh_prov_register_comp_param {
        int err_code;                           /*!< 指示BLE网格初始化的结果*/
    } prov_register_comp;                       /*!< ESP_BLE_MESH_PROV_REGISTER_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_NODE_SET_UNPROV_DEV_NAME_COMP_EVT
     */
    struct ble_mesh_set_unprov_dev_name_comp_param {
        int err_code;                           /*!< 指示设置BLE Mesh设备名称的结果*/
    } node_set_unprov_dev_name_comp;            /*!< ESP_BLE_MESH_NODE_SET_UNPROV_DEV_NAME_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_NODE_PROV_ENABLE_COMP_EVT
     */
    struct ble_mesh_prov_enable_comp_param {
        int err_code;                           /*!< 指示启用BLE Mesh设备的结果*/
    } node_prov_enable_comp;                    /*!< ESP_BLE_MESH_NODE_PROV_ENABLE_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_NODE_PROV_DISABLE_COMP_EVT
     */
    struct ble_mesh_prov_disable_comp_param {
        int err_code;                           /*!< 指示禁用BLE Mesh设备的结果*/
    } node_prov_disable_comp;                   /*!< ESP_BLE_MESH_NODE_PROV_DISABLE_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_NODE_PROV_LINK_OPEN_EVT
     */
    struct ble_mesh_link_open_evt_param {
        esp_ble_mesh_prov_bearer_t bearer;      /*!< 设备链路打开时使用的承载类型*/
    } node_prov_link_open;                      /*!< ESP_BLE_MESH_NODE_PROV_LINK_OPEN_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_NODE_PROV_LINK_CLOSE_EVT
     */
    struct ble_mesh_link_close_evt_param {
        esp_ble_mesh_prov_bearer_t bearer;      /*!< 设备链路关闭时使用的承载类型*/
    } node_prov_link_close;                     /*!< ESP_BLE_MESH_NODE_PROV_LINK_CLOSE_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_NODE_PROV_OUTPUT_NUMBER_EVT
     */
    struct ble_mesh_output_num_evt_param {
        esp_ble_mesh_output_action_t action;    /*!< 输出OOB认证的动作*/
        uint32_t number;                        /*!< 输出OOB身份验证数*/
    } node_prov_output_num;                     /*!< ESP_BLE_MESH_NODE_PROV_OUTPUT_NUMBER_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_NODE_PROV_OUTPUT_STRING_EVT
     */
    struct ble_mesh_output_str_evt_param {
        char string[8];                         /*!< 输出OOB身份验证字符串*/
    } node_prov_output_str;                     /*!< ESP_BLE_MESH_NODE_PROV_OUTPUT_STRING_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_NODE_PROV_INPUT_EVT
     */
    struct ble_mesh_input_evt_param {
        esp_ble_mesh_input_action_t action;     /*!< 输入OOB认证的动作*/
        uint8_t size;                           /*!< 输入OOB身份验证的大小*/
    } node_prov_input;                          /*!< ESP_BLE_MESH_NODE_PROV_INPUT_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_NODE_PROV_COMPLETE_EVT
     */
    struct ble_mesh_provision_complete_evt_param {
        uint16_t net_idx;                       /*!< NetKey索引*/
        uint8_t  net_key[16];                   /*!< 网络密钥*/
        uint16_t addr;                          /*!< 主要地址*/
        uint8_t  flags;                         /*!< 旗帜*/
        uint32_t iv_index;                      /*!< IV索引*/
    } node_prov_complete;                       /*!< ESP_BLE_MESH_NODE_PROV_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_NODE_PROV_RESET_EVT
     */
    struct ble_mesh_provision_reset_param {

    } node_prov_reset;                          /*!< ESP_BLE_MESH_NODE_PROV_RESET_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_NODE_PROV_SET_OOB_PUB_KEY_COMP_EVT
     */
    struct ble_mesh_set_oob_pub_key_comp_param {
        int err_code;                           /*!< 指示设置OOB公钥的结果*/
    } node_prov_set_oob_pub_key_comp;           /*!< ESP_BLE_MESH_NODE_PROV_SET_OOB_PUB_KEY_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_NODE_PROV_INPUT_NUM_COMP_EVT
     */
    struct ble_mesh_input_number_comp_param {
        int err_code;                           /*!< 指示输入数字的结果*/
    } node_prov_input_num_comp;                 /*!< ESP_BLE_MESH_NODE_PROV_INPUT_NUM_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_NODE_PROV_INPUT_STR_COMP_EVT
     */
    struct ble_mesh_input_string_comp_param {
        int err_code;                           /*!< 指示输入字符串的结果*/
    } node_prov_input_str_comp;                 /*!< ESP_BLE_MESH_NODE_PROV_INPUT_STR_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_NODE_PROXY_IDENTITY_ENABLE_COMP_EVT
     */
    struct ble_mesh_proxy_identity_enable_comp_param {
        int err_code;                           /*!< 指示启用网格代理广告的结果*/
    } node_proxy_identity_enable_comp;          /*!< ESP_BLE_MESH_NODE_PROXY_IDENTITY_ENABLE_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_NODE_PROXY_GATT_ENABLE_COMP_EVT
     */
    struct ble_mesh_proxy_gatt_enable_comp_param {
        int err_code;                           /*!< 指示启用网格代理服务的结果*/
    } node_proxy_gatt_enable_comp;              /*!< ESP_BLE_MESH_NODE_PROXY_GATT_ENABLE_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_NODE_PROXY_GATT_DISABLE_COMP_EVT
     */
    struct ble_mesh_proxy_gatt_disable_comp_param {
        int err_code;                           /*!< 指示禁用网格代理服务的结果*/
    } node_proxy_gatt_disable_comp;             /*!< ESP_BLE_MESH_NODE_PROXY_GATT_DISABLE_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_NODE_ADD_LOCAL_NET_KEY_COMP_EVT
     */
    struct ble_mesh_node_add_local_net_key_comp_param {
        int err_code;                           /*!< 指示节点添加本地NetKey的结果*/
        uint16_t net_idx;                       /*!< NetKey索引*/
    } node_add_net_key_comp;                    /*!< ESP_BLE_MESH_NODE_ADD_LOCAL_NET_KEY_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_NODE_ADD_LOCAL_APP_KEY_COMP_EVT
     */
    struct ble_mesh_node_add_local_app_key_comp_param {
        int err_code;                           /*!< 指示节点添加本地AppKey的结果*/
        uint16_t net_idx;                       /*!< NetKey索引*/
        uint16_t app_idx;                       /*!< AppKey索引*/
    } node_add_app_key_comp;                    /*!< ESP_BLE_MESH_NODE_ADD_LOCAL_APP_KEY_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_NODE_BIND_APP_KEY_TO_MODEL_COMP_EVT
     */
    struct ble_mesh_node_bind_local_mod_app_comp_param {
        int err_code;                           /*!< 指示节点将AppKey与模型绑定的结果*/
        uint16_t element_addr;                  /*!< 元素地址*/
        uint16_t app_idx;                       /*!< AppKey索引*/
        uint16_t company_id;                    /*!< 公司ID*/
        uint16_t model_id;                      /*!< 型号ID*/
    } node_bind_app_key_to_model_comp;          /*!< ESP_BLE_MESH_NODE_BIND_APP_KEY_TO_MODEL_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_RECV_UNPROV_ADV_PKT_EVT
     */
    struct ble_mesh_provisioner_recv_unprov_adv_pkt_param {
        uint8_t  dev_uuid[16];                  /*!< 未配置设备的设备UUID*/
        esp_ble_mesh_bd_addr_t addr;            /*!< 未配置设备的设备地址*/
        esp_ble_mesh_addr_type_t addr_type;     /*!< 设备地址类型*/
        uint16_t oob_info;                      /*!< 未配置设备的OOB信息*/
        uint8_t  adv_type;                      /*!< 未配置设备的平均类型*/
        esp_ble_mesh_prov_bearer_t bearer;      /*!< 未配置设备的承载器*/
        int8_t   rssi;                          /*!< 接收到的广告包的RSSI*/
    } provisioner_recv_unprov_adv_pkt;          /*!< ESP_BLE_MESH_PROVISIONERRECV_UNPROV_ADV_PKT_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_PROV_ENABLE_COMP_EVT
     */
    struct ble_mesh_provisioner_prov_enable_comp_param {
        int err_code;                           /*!< 指示启用BLE Mesh Provisioner的结果*/
    } provisioner_prov_enable_comp;             /*!< ESP_BLE_MESH_PROVISIONER_PROV_ENABLE_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_PROV_DISABLE_COMP_EVT
     */
    struct ble_mesh_provisioner_prov_disable_comp_param {
        int err_code;                           /*!< 指示禁用BLE Mesh Provisioner的结果*/
    } provisioner_prov_disable_comp;            /*!< ESP_BLE_MESH_PROVISIONER_PROV_DISABLE_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_PROV_LINK_OPEN_EVT
     */
    struct ble_mesh_provisioner_link_open_evt_param {
        esp_ble_mesh_prov_bearer_t bearer;      /*!< 打开Provisioner链接时使用的承载类型*/
    } provisioner_prov_link_open;               /*!< ESP_BLE_MESH_PROVISIONER_PROV_LINK_OPEN_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_PROV_READ_OOB_PUB_KEY_EVT
     */
    struct ble_mesh_provisioner_prov_read_oob_pub_key_evt_param {
        uint8_t link_idx;                       /*!< 资源调配链接的索引*/
    } provisioner_prov_read_oob_pub_key;        /*!< ESP_BLE_MESH_PROVISIONER_PROV_READ_OOB_PUB_KEY_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_PROV_INPUT_EVT
     */
    struct ble_mesh_provisioner_prov_input_evt_param {
        esp_ble_mesh_oob_method_t method;       /*!< 设备输出OOB认证方法*/
        esp_ble_mesh_output_action_t action;    /*!< 设备输出OOB认证的操作*/
        uint8_t size;                           /*!< 设备大小输出OOB身份验证*/
        uint8_t link_idx;                       /*!< 资源调配链接的索引*/
    } provisioner_prov_input;                   /*!< ESP_BLE_MESH_PROVISIONER_PROV_INPUT_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_PROV_OUTPUT_EVT
     */
    struct ble_mesh_provisioner_prov_output_evt_param {
        esp_ble_mesh_oob_method_t method;       /*!< 设备输入OOB认证方法*/
        esp_ble_mesh_input_action_t action;     /*!< 设备输入OOB认证的动作*/
        uint8_t size;                           /*!< 设备大小输入OOB身份验证*/
        uint8_t link_idx;                       /*!< 资源调配链接的索引*/
        union {
            char string[8];                     /*!< 配置器输出的字符串*/
            uint32_t number;                    /*!< 配置器输出的数字*/
        };
    } provisioner_prov_output;                  /*!< ESP_BLE_MESH_PROVISIONER_PROV_OUTPUT_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_PROV_LINK_CLOSE_EVT
     */
    struct ble_mesh_provisioner_link_close_evt_param {
        esp_ble_mesh_prov_bearer_t bearer;      /*!< Provisioner链接关闭时使用的承载类型*/
        uint8_t reason;                         /*!< 关闭供应链接的原因*/
    } provisioner_prov_link_close;              /*!< ESP_BLE_MESH_PROVISIONER_PROV_LINK_CLOSE_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_PROV_COMPLETE_EVT
     */
    struct ble_mesh_provisioner_prov_comp_param {
        uint16_t node_idx;                      /*!< 已配置设备的索引*/
        esp_ble_mesh_octet16_t device_uuid;     /*!< 配置设备的设备UUID*/
        uint16_t unicast_addr;                  /*!< 配置设备的主地址*/
        uint8_t element_num;                    /*!< 配置设备的元素计数*/
        uint16_t netkey_idx;                    /*!< 配置设备的NetKey索引*/
    } provisioner_prov_complete;                /*!< ESP_BLE_MESH_PROVISIONER_PROV_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_ADD_UNPROV_DEV_COMP_EVT
     */
    struct ble_mesh_provisioner_add_unprov_dev_comp_param {
        int err_code;                           /*!< 指示配置程序将设备添加到队列的结果*/
    } provisioner_add_unprov_dev_comp;          /*!< ESP_BLE_MESH_PROVISIONER_ADD_UNPROV_DEV_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_PROV_DEV_WITH_ADDR_COMP_EVT
     */
    struct ble_mesh_provisioner_prov_dev_with_addr_comp_param {
        int err_code;                           /*!< 指示Provisioner开始配置设备的结果*/
    } provisioner_prov_dev_with_addr_comp;      /*!< ESP_BLE_MESH_PROVISIONER_PROV_DEV_WITH_ADDR_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_DELETE_DEV_COMP_EVT
     */
    struct ble_mesh_provisioner_delete_dev_comp_param {
        int err_code;                           /*!< 指示配置程序删除设备的结果*/
    } provisioner_delete_dev_comp;              /*!< ESP_BLE_MESH_PROVISIONER_DELETE_DEV_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_SET_DEV_UUID_MATCH_COMP_EVT
     */
    struct ble_mesh_provisioner_set_dev_uuid_match_comp_param {
        int err_code;                           /*!< 指示配置程序设置设备UUID匹配值的结果*/
    } provisioner_set_dev_uuid_match_comp;      /*!< ESP_BLE_MESH_PROVISIONER_SET_DEV_UUID_MATCH_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_SET_PROV_DATA_INFO_COMP_EVT
     */
    struct ble_mesh_provisioner_set_prov_data_info_comp_param {
        int err_code;                           /*!< 指示配置程序设置配置信息的结果*/
    } provisioner_set_prov_data_info_comp;      /*!< ESP_BLE_MESH_PROVISIONER_SET_PROV_DATA_INFO_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_SET_STATIC_OOB_VALUE_COMP_EVT
     */
    struct ble_mesh_provisioner_set_static_oob_val_comp_param {
        int err_code;                           /*!< 指示Provisioner设置静态oob值的结果*/
    } provisioner_set_static_oob_val_comp;      /*!< ESP_BLE_MESH_PROVISIONER_SET_STATIC_OOB_VALUE_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_SET_PRIMARY_ELEM_ADDR_COMP_EVT
     */
    struct ble_mesh_provisioner_set_primary_elem_addr_comp_param {
        int err_code;                           /*!< 指示Provisioner设置主元素单播地址的结果*/
    } provisioner_set_primary_elem_addr_comp;   /*!< ESP_BLE_MESH_PROVISIONER_SET_PRIMARY_ELEM_ADDR_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_PROV_READ_OOB_PUB_KEY_COMP_EVT
     */
    struct ble_mesh_provisioner_prov_read_oob_pub_key_comp_param {
        int err_code;                           /*!< 指示设置器设置OOB公钥的结果*/
    } provisioner_prov_read_oob_pub_key_comp;   /*!< ESP_BLE_MESH_PROVISIONER_PROV_READ_OOB_PUB_KEY_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_PROV_INPUT_NUMBER_COMP_EVT
     */
    struct ble_mesh_provisioner_prov_input_num_comp_param {
        int err_code;                           /*!< 指示配置者输入数字的结果*/
    } provisioner_prov_input_num_comp;          /*!< ESP_BLE_MESH_PROVISIONER_PROV_INPUT_NUMBER_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_PROV_INPUT_STRING_COMP_EVT
     */
    struct ble_mesh_provisioner_prov_input_str_comp_param {
        int err_code;                           /*!< 指示Provisioner输入字符串的结果*/
    } provisioner_prov_input_str_comp;          /*!< ESP_BLE_MESH_PROVISIONER_PROV_INPUT_STRING_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_SET_NODE_NAME_COMP_EVT
     */
    struct ble_mesh_provisioner_set_node_name_comp_param {
        int err_code;                           /*!< 指示配置程序设置配置设备名称的结果*/
        uint16_t node_index;                    /*!< 已配置设备的索引*/
    } provisioner_set_node_name_comp;           /*!< ESP_BLE_MESH_PROVISIONER_SET_NODE_NAME_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_ADD_LOCAL_APP_KEY_COMP_EVT
     */
    struct ble_mesh_provisioner_add_local_app_key_comp_param {
        int err_code;                           /*!< 指示Provisioner添加本地AppKey的结果*/
        uint16_t net_idx;                       /*!< NetKey索引*/
        uint16_t app_idx;                       /*!< AppKey索引*/
    } provisioner_add_app_key_comp;             /*!< ESP_BLE_MESH_PROVISIONER_ADD_LOCAL_APP_KEY_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_UPDATE_LOCAL_APP_KEY_COMP_EVT
     */
    struct ble_mesh_provisioner_update_local_app_key_comp_param {
        int err_code;                           /*!< 指示配置程序更新本地AppKey的结果*/
        uint16_t net_idx;                       /*!< NetKey索引*/
        uint16_t app_idx;                       /*!< AppKey索引*/
    } provisioner_update_app_key_comp;          /*!< ESP_BLE_MESH_PROVISIONER_UPDATE_LOCAL_APP_KEY_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_BIND_APP_KEY_TO_MODEL_COMP_EVT
     */
    struct ble_mesh_provisioner_bind_local_mod_app_comp_param {
        int err_code;                           /*!< 指示Provisioner将AppKey与模型绑定的结果*/
        uint16_t element_addr;                  /*!< 元素地址*/
        uint16_t app_idx;                       /*!< AppKey索引*/
        uint16_t company_id;                    /*!< 公司ID*/
        uint16_t model_id;                      /*!< 型号ID*/
    } provisioner_bind_app_key_to_model_comp;   /*!< ESP_BLE_MESH_PROVISIONER_BIND_APP_KEY_TO_MODEL_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_ADD_LOCAL_NET_KEY_COMP_EVT
     */
    struct ble_mesh_provisioner_add_local_net_key_comp_param {
        int err_code;                           /*!< 指示配置程序添加本地NetKey的结果*/
        uint16_t net_idx;                       /*!< NetKey索引*/
    } provisioner_add_net_key_comp;             /*!< ESP_BLE_MESH_PROVISIONER_ADD_LOCAL_NET_KEY_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_UPDATE_LOCAL_NET_KEY_COMP_EVT
     */
    struct ble_mesh_provisioner_update_local_net_key_comp_param {
        int err_code;                           /*!< 指示配置程序更新本地NetKey的结果*/
        uint16_t net_idx;                       /*!< NetKey索引*/
    } provisioner_update_net_key_comp;          /*!< ESP_BLE_MESH_PROVISIONER_UPDATE_LOCAL_NET_KEY_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_STORE_NODE_COMP_DATA_COMP_EVT
     */
    struct ble_mesh_provisioner_store_node_comp_data_comp_param {
        int err_code;                           /*!< 指示Provisioner存储节点组成数据的结果*/
        uint16_t addr;                          /*!< 节点元素地址*/
    } provisioner_store_node_comp_data_comp;    /*!< ESP_BLE_MESH_PROVISIONERSTORE_NODE_COMP_DATA_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_DELETE_NODE_WITH_UUID_COMP_EVT
     */
    struct ble_mesh_provisioner_delete_node_with_uuid_comp_param {
        int err_code;                           /*!< 指示配置程序删除uuid为的节点的结果*/
        uint8_t uuid[16];                       /*!< 节点设备uuid*/
    } provisioner_delete_node_with_uuid_comp;   /*!< ESP_BLE_MESH_PROVISIONER_DELETE_NODE_WITH_UUID_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_DELETE_NODE_WITH_ADDR_COMP_EVT
     */
    struct ble_mesh_provisioner_delete_node_with_addr_comp_param {
        int err_code;                           /*!< 指示配置程序删除具有单播地址的节点的结果*/
        uint16_t unicast_addr;                  /*!< 节点单播地址*/
    } provisioner_delete_node_with_addr_comp;   /*!< ESP_BLE_MESH_PROVISIONER_DELETE_NODE_WITH_ADDR_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_ENABLE_HEARTBEAT_RECV_COMP_EVT
     */
    struct {
        int err_code;                           /*!< 指示配置程序启用/禁用接收心跳消息的结果*/
        bool enable;                            /*!< 指示启用或禁用接收心跳消息*/
    } provisioner_enable_heartbeat_recv_comp;   /*!< ESP_BLE_MESH_PROVISIONER_ENABLE_HEARTBEAT_RECV_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_SET_HEARTBEAT_FILTER_TYPE_COMP_EVT
     */
    struct {
        int err_code;                               /*!< 指示Provisioner设置心跳筛选器类型的结果*/
        uint8_t type;                               /*!< 用于接收心跳消息的筛选器的类型*/
    } provisioner_set_heartbeat_filter_type_comp;   /*!< ESP_BLE_MESH_PROVISIONER_SET_HEARTBEAT_FILTER_TYPE_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_SET_HEARTBEAT_FILTER_INFO_COMP_EVT
     */
    struct {
        int err_code;                               /*!< 指示Provisioner设置心跳筛选器地址的结果*/
        uint8_t  op;                                /*!< 操作（添加、删除、清洁）*/
        uint16_t hb_src;                            /*!< 心跳源地址*/
        uint16_t hb_dst;                            /*!< 心跳目标地址*/
    } provisioner_set_heartbeat_filter_info_comp;   /*!< ESP_BLE_MESH_PROVISIONER_SET_HEARTBEAT_FILTER_INFO_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_RECV_HEARTBEAT_MESSAGE_EVT
     */
    struct {
        uint16_t hb_src;            /*!< 心跳源地址*/
        uint16_t hb_dst;            /*!< 心跳目标地址*/
        uint8_t  init_ttl;          /*!< 心跳初始化TTL*/
        uint8_t  rx_ttl;            /*!< 心跳RxTTL*/
        uint8_t  hops;              /*!< 心跳跃点（InitTTL-RxTTL+1）*/
        uint16_t feature;           /*!< 节点当前活动特征的位字段*/
        int8_t   rssi;              /*!< 心跳消息的RSSI*/
    } provisioner_recv_heartbeat;   /*!< ESP_BLE_MESH_PROVISIONER_RECV_HEARTBEAT_MESSAGE_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_DRIECT_ERASE_SETTINGS_COMP_EVT
     */
    struct {
        int err_code;                           /*!< 指示配置程序直接删除设置的结果*/
    } provisioner_direct_erase_settings_comp;   /*!< ESP_BLE_MESH_PROVISIONER_DRIECT_ERASE_SETTINGS_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_OPEN_SETTINGS_WITH_INDEX_COMP_EVT
     */
    struct {
        int err_code;                               /*!< 指示配置程序使用索引打开设置的结果*/
        uint8_t index;                              /*!< Provisioner设置索引*/
    } provisioner_open_settings_with_index_comp;    /*!< ESP_BLE_MESH_PROVISIONER_OPEN_SETTINGS_WITH_INDEX_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_OPEN_SETTINGS_WITH_UID_COMP_EVT
     */
    struct {
        int err_code;                                   /*!< 指示Provisioner使用用户id打开设置的结果*/
        uint8_t index;                                  /*!< Provisioner设置索引*/
        char uid[ESP_BLE_MESH_SETTINGS_UID_SIZE + 1];   /*!< 配置程序设置用户id*/
    } provisioner_open_settings_with_uid_comp;          /*!< ESP_BLE_MESH_PROVISIONER_OPEN_SETTINGS_WITH_UID_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_CLOSE_SETTINGS_WITH_INDEX_COMP_EVT
     */
    struct {
        int err_code;                               /*!< 指示Provisioner使用索引关闭设置的结果*/
        uint8_t index;                              /*!< Provisioner设置索引*/
    } provisioner_close_settings_with_index_comp;   /*!< ESP_BLE_MESH_PROVISIONER_CLOSE_SETTINGS_WITH_INDEX_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_CLOSE_SETTINGS_WITH_UID_COMP_EVT
     */
    struct {
        int err_code;                                   /*!< 指示Provisioner使用用户id关闭设置的结果*/
        uint8_t index;                                  /*!< Provisioner设置索引*/
        char uid[ESP_BLE_MESH_SETTINGS_UID_SIZE + 1];   /*!< 配置程序设置用户id*/
    } provisioner_close_settings_with_uid_comp;         /*!< ESP_BLE_MESH_PROVISIONER_CLOSE_SETTINGS_WITH_UID_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_DELETE_SETTINGS_WITH_INDEX_COMP_EVT
     */
    struct {
        int err_code;                               /*!< 指示配置程序删除带有索引的设置的结果*/
        uint8_t index;                              /*!< Provisioner设置索引*/
    } provisioner_delete_settings_with_index_comp;  /*!< ESP_BLE_MESH_PROVISIONER_DELETE_SETTINGS_WITH_INDEX_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_DELETE_SETTINGS_WITH_UID_COMP_EVT
     */
    struct {
        int err_code;                                   /*!< 指示配置程序删除用户id为的设置的结果*/
        uint8_t index;                                  /*!< Provisioner设置索引*/
        char uid[ESP_BLE_MESH_SETTINGS_UID_SIZE + 1];   /*!< 配置程序设置用户id*/
    } provisioner_delete_settings_with_uid_comp;        /*!< ESP_BLE_MESH_PROVISIONER_DELETE_SETTINGS_WITH_UID_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_SET_FAST_PROV_INFO_COMP_EVT
     */
    struct ble_mesh_set_fast_prov_info_comp_param {
        uint8_t status_unicast;                 /*!< 指示设置快速配置的单播地址范围的结果*/
        uint8_t status_net_idx;                 /*!< 指示设置快速资源调配的NetKey索引的结果*/
        uint8_t status_match;                   /*!< 指示设置快速配置的匹配设备UUID的结果*/
    } set_fast_prov_info_comp;                  /*!< ESP_BLE_MESH_SET_FAST_PROV_INFO_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_SET_FAST_PROV_ACTION_COMP_EVT
     */
    struct ble_mesh_set_fast_prov_action_comp_param {
        uint8_t status_action;                  /*!< 指示设置快速资源调配操作的结果*/
    } set_fast_prov_action_comp;                /*!< ESP_BLE_MESH_SET_FAST_PROV_ACTION_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_HEARTBEAT_MESSAGE_RECV_EVT
     */
    struct ble_mesh_heartbeat_msg_recv_param {
        uint8_t  hops;                          /*!< 心跳跃点（InitTTL-RxTTL+1）*/
        uint16_t feature;                       /*!< 节点当前活动特征的位字段*/
    } heartbeat_msg_recv;                       /*!< ESP_BLE_MESH_HEARTBEAT_MESSAGE_RECV_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_LPN_ENABLE_COMP_EVT
     */
    struct ble_mesh_lpn_enable_comp_param {
        int err_code;                           /*!< 指示启用LPN功能的结果*/
    } lpn_enable_comp;                          /*!< ESP_BLE_MESH_LPN_ENABLE_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_LPN_DISABLE_COMP_EVT
     */
    struct ble_mesh_lpn_disable_comp_param {
        int err_code;                           /*!< 指示禁用LPN功能的结果*/
    } lpn_disable_comp;                         /*!< ESP_BLE_MESH_LPN_DISABLE_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_LPN_POLL_COMP_EVT
     */
    struct ble_mesh_lpn_poll_comp_param {
        int err_code;                           /*!< 指示发送好友投票的结果*/
    } lpn_poll_comp;                            /*!< ESP_BLE_MESH_LPN_POLL_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_LPN_FRIENDSHIP_ESTABLISH_EVT
     */
    struct ble_mesh_lpn_friendship_establish_param {
        uint16_t friend_addr;                   /*!< 朋友节点单播地址*/
    } lpn_friendship_establish;                 /*!< ESP_BLE_MESH_LPN_RIENDSHIP_ESTABLISH_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_LPN_FRIENDSHIP_TERMINATE_EVT
     */
    struct ble_mesh_lpn_friendship_terminate_param {
        uint16_t friend_addr;                   /*!< 朋友节点单播地址*/
    } lpn_friendship_terminate;                 /*!< ESP_BLE_MESH_LPN_RIENDSHIP_TERMINATE_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_FRIEND_FRIENDSHIP_ESTABLISH_EVT
     */
    struct ble_mesh_friend_friendship_establish_param {
        uint16_t lpn_addr;                      /*!< 低功耗节点单播地址*/
    } frnd_friendship_establish;                /*!< ESP_BLE_MESH_FRIEND_FRIENDSHIP_ESTABLISH_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_FRIEND_FRIENDSHIP_TERMINATE_EVT
     */
    struct ble_mesh_friend_friendship_terminate_param {
        uint16_t lpn_addr;                      /*!< 低功耗节点单播地址*/
        /**此枚举值是朋友节点端友谊终止的原因*/
        enum {
            ESP_BLE_MESH_FRND_FRIENDSHIP_TERMINATE_ESTABLISH_FAIL,  /*!< 已发送好友邀请，但1秒内未收到好友邀请，友谊无法建立*/
            ESP_BLE_MESH_FRND_FRIENDSHIP_TERMINATE_POLL_TIMEOUT,    /*!< 友谊已建立，PollTimeout计时器过期，未收到好友轮询/子添加/子删除*/
            ESP_BLE_MESH_FRND_FRIENDSHIP_TERMINATE_RECV_FRND_REQ,   /*!< 从现有低功耗节点接收好友请求*/
            ESP_BLE_MESH_FRND_FRIENDSHIP_TERMINATE_RECV_FRND_CLEAR, /*!< 从其他好友节点接收好友清除*/
            ESP_BLE_MESH_FRND_FRIENDSHIP_TERMINATE_DISABLE,         /*!< 好友功能已禁用或相应的NetKey已删除*/
        } reason;                               /*!< 友谊终止原因*/
    } frnd_friendship_terminate;                /*!< ESP_BLE_MESH_FRIEND_FRIENDSHIP_TERMINATE_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROXY_CLIENT_RECV_ADV_PKT_EVT
     */
    struct ble_mesh_proxy_client_recv_adv_pkt_param {
        esp_ble_mesh_bd_addr_t addr;            /*!< 设备地址*/
        esp_ble_mesh_addr_type_t addr_type;     /*!< 设备地址类型*/
        uint16_t net_idx;                       /*!< 与网络ID相关的NetKey索引*/
        uint8_t  net_id[8];                     /*!< 广告数据包中包含的网络ID*/
        int8_t   rssi;                          /*!< 接收到的广告包的RSSI*/
    } proxy_client_recv_adv_pkt;                /*!< ESP_BLE_MESH_PROXY_CLIENT_RECV_ADV_PKT_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROXY_CLIENT_CONNECTED_EVT
     */
    struct ble_mesh_proxy_client_connected_param {
        esp_ble_mesh_bd_addr_t addr;            /*!< 代理服务器的设备地址*/
        esp_ble_mesh_addr_type_t addr_type;     /*!< 设备地址类型*/
        uint8_t conn_handle;                    /*!< 代理连接句柄*/
        uint16_t net_idx;                       /*!< 对应的NetKey索引*/
    } proxy_client_connected;                   /*!< ESP_BLE_MESH_PROXY_CLIENT_CONNECTED_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROXY_CLIENT_DISCONNECTED_EVT
     */
    struct ble_mesh_proxy_client_disconnected_param {
        esp_ble_mesh_bd_addr_t addr;            /*!< 代理服务器的设备地址*/
        esp_ble_mesh_addr_type_t addr_type;     /*!< 设备地址类型*/
        uint8_t conn_handle;                    /*!< 代理连接句柄*/
        uint16_t net_idx;                       /*!< 对应的NetKey索引*/
        uint8_t reason;                         /*!< 代理断开原因*/
    } proxy_client_disconnected;                /*!< ESP_BLE_MESH_PROXY_CLIENT_DISCONNECTED_VT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROXY_CLIENT_RECV_FILTER_STATUS_EVT
     */
    struct ble_mesh_proxy_client_recv_filter_status_param {
        uint8_t  conn_handle;                   /*!< 代理连接句柄*/
        uint16_t server_addr;                   /*!< 代理服务器主元素地址*/
        uint16_t net_idx;                       /*!< 对应的NetKey索引*/
        uint8_t  filter_type;                   /*!< 代理服务器筛选器类型（白名单或黑名单）*/
        uint16_t list_size;                     /*!< 代理服务器筛选器列表中的地址数*/
    } proxy_client_recv_filter_status;          /*!< ESP_BLE_MESH_PROXY_CLIENT_RECV_FILTER_STATUS_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROXY_CLIENT_CONNECT_COMP_EVT
     */
    struct ble_mesh_proxy_client_connect_comp_param {
        int err_code;                           /*!< 指示代理客户端连接的结果*/
        esp_ble_mesh_bd_addr_t addr;            /*!< 代理服务器的设备地址*/
        esp_ble_mesh_addr_type_t addr_type;     /*!< 设备地址类型*/
        uint16_t net_idx;                       /*!< 对应的NetKey索引*/
    } proxy_client_connect_comp;                /*!< ESP_BLE_MESH_PROXY_CLIENT_CONNECT_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROXY_CLIENT_DISCONNECT_COMP_EVT
     */
    struct ble_mesh_proxy_client_disconnect_comp_param {
        int err_code;                           /*!< 指示代理客户端断开连接的结果*/
        uint8_t conn_handle;                    /*!< 代理连接句柄*/
    } proxy_client_disconnect_comp;             /*!< ESP_BLE_MESH_PROXY_CLIENT_DISCONNECT_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROXY_CLIENT_SET_FILTER_TYPE_COMP_EVT
     */
    struct ble_mesh_proxy_client_set_filter_type_comp_param {
        int err_code;                           /*!< 指示代理客户端集筛选器类型的结果*/
        uint8_t conn_handle;                    /*!< 代理连接句柄*/
        uint16_t net_idx;                       /*!< 对应的NetKey索引*/
    } proxy_client_set_filter_type_comp;        /*!< ESP_BLE_MESH_PROXY_CLIENT_SET_FILTER_TYPE_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROXY_CLIENT_ADD_FILTER_ADDR_COMP_EVT
     */
    struct ble_mesh_proxy_client_add_filter_addr_comp_param {
        int err_code;                           /*!< 指示代理客户端添加筛选器地址的结果*/
        uint8_t conn_handle;                    /*!< 代理连接句柄*/
        uint16_t net_idx;                       /*!< 对应的NetKey索引*/
    } proxy_client_add_filter_addr_comp;        /*!< ESP_BLE_MESH_PROXY_CLIENT_ADD_FILTER_ADDR_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROXY_CLIENT_REMOVE_FILTER_ADDR_COMP_EVT
     */
    struct ble_mesh_proxy_client_remove_filter_addr_comp_param {
        int err_code;                           /*!< 指示代理客户端删除筛选器地址的结果*/
        uint8_t conn_handle;                    /*!< 代理连接句柄*/
        uint16_t net_idx;                       /*!< 对应的NetKey索引*/
    } proxy_client_remove_filter_addr_comp;     /*!< ESP_BLE_MESH_PROXY_CLIENT_REMOVE_FILTER_ADDR_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROXY_SERVER_CONNECTED_EVT
     */
    struct ble_mesh_proxy_server_connected_param {
        uint8_t conn_handle;                    /*!< 代理连接句柄*/
    } proxy_server_connected;                   /*!< ESP_BLE_MESH_PROXY_SERVER_CONNECTED_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_PROXY_SERVER_DISCONNECTED_EVT
     */
    struct ble_mesh_proxy_server_disconnected_param {
        uint8_t conn_handle;                    /*!< 代理连接句柄*/
        uint8_t reason;                         /*!< 代理断开原因*/
    } proxy_server_disconnected;                /*!< ESP_BLE_MESH_PROXY_SERVER_DISCONNECTED_VT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_MODEL_SUBSCRIBE_GROUP_ADDR_COMP_EVT
     */
    struct ble_mesh_model_sub_group_addr_comp_param {
        int err_code;                           /*!< 指示本地模型订阅组地址的结果*/
        uint16_t element_addr;                  /*!< 元素地址*/
        uint16_t company_id;                    /*!< 公司ID*/
        uint16_t model_id;                      /*!< 型号ID*/
        uint16_t group_addr;                    /*!< 组地址*/
    } model_sub_group_addr_comp;                /*!< ESP_BLE_MESH_MODEL_SUBSCRIBE_GROUP_ADDR_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_MODEL_UNSUBSCRIBE_GROUP_ADDR_COMP_EVT
     */
    struct ble_mesh_model_unsub_group_addr_comp_param {
        int err_code;                           /*!< 指示本地模型取消订阅组地址的结果*/
        uint16_t element_addr;                  /*!< 元素地址*/
        uint16_t company_id;                    /*!< 公司ID*/
        uint16_t model_id;                      /*!< 型号ID*/
        uint16_t group_addr;                    /*!< 组地址*/
    } model_unsub_group_addr_comp;              /*!< ESP_BLE_MESH_MODEL_UNSUBSCRIBE_GROUP_ADDR_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_DEINIT_MESH_COMP_EVT
     */
    struct ble_mesh_deinit_mesh_comp_param {
        int err_code;                           /*!< 指示BLE网格去初始化的结果*/
    } deinit_mesh_comp;                         /*!< ESP_BLE_MESH_DEINIT_MESH_COMP_EVT的事件参数*/
} esp_ble_mesh_prov_cb_param_t;

/**
 * @brief BLE网格模型相关模型ID和操作码定义
 */

/*!< 基础模型*/
#define ESP_BLE_MESH_MODEL_ID_CONFIG_SRV                            0x0000
#define ESP_BLE_MESH_MODEL_ID_CONFIG_CLI                            0x0001
#define ESP_BLE_MESH_MODEL_ID_HEALTH_SRV                            0x0002
#define ESP_BLE_MESH_MODEL_ID_HEALTH_CLI                            0x0003

/*!< 网格模型规范中的模型*/
#define ESP_BLE_MESH_MODEL_ID_GEN_ONOFF_SRV                         0x1000
#define ESP_BLE_MESH_MODEL_ID_GEN_ONOFF_CLI                         0x1001
#define ESP_BLE_MESH_MODEL_ID_GEN_LEVEL_SRV                         0x1002
#define ESP_BLE_MESH_MODEL_ID_GEN_LEVEL_CLI                         0x1003
#define ESP_BLE_MESH_MODEL_ID_GEN_DEF_TRANS_TIME_SRV                0x1004
#define ESP_BLE_MESH_MODEL_ID_GEN_DEF_TRANS_TIME_CLI                0x1005
#define ESP_BLE_MESH_MODEL_ID_GEN_POWER_ONOFF_SRV                   0x1006
#define ESP_BLE_MESH_MODEL_ID_GEN_POWER_ONOFF_SETUP_SRV             0x1007
#define ESP_BLE_MESH_MODEL_ID_GEN_POWER_ONOFF_CLI                   0x1008
#define ESP_BLE_MESH_MODEL_ID_GEN_POWER_LEVEL_SRV                   0x1009
#define ESP_BLE_MESH_MODEL_ID_GEN_POWER_LEVEL_SETUP_SRV             0x100a
#define ESP_BLE_MESH_MODEL_ID_GEN_POWER_LEVEL_CLI                   0x100b
#define ESP_BLE_MESH_MODEL_ID_GEN_BATTERY_SRV                       0x100c
#define ESP_BLE_MESH_MODEL_ID_GEN_BATTERY_CLI                       0x100d
#define ESP_BLE_MESH_MODEL_ID_GEN_LOCATION_SRV                      0x100e
#define ESP_BLE_MESH_MODEL_ID_GEN_LOCATION_SETUP_SRV                0x100f
#define ESP_BLE_MESH_MODEL_ID_GEN_LOCATION_CLI                      0x1010
#define ESP_BLE_MESH_MODEL_ID_GEN_ADMIN_PROP_SRV                    0x1011
#define ESP_BLE_MESH_MODEL_ID_GEN_MANUFACTURER_PROP_SRV             0x1012
#define ESP_BLE_MESH_MODEL_ID_GEN_USER_PROP_SRV                     0x1013
#define ESP_BLE_MESH_MODEL_ID_GEN_CLIENT_PROP_SRV                   0x1014
#define ESP_BLE_MESH_MODEL_ID_GEN_PROP_CLI                          0x1015
#define ESP_BLE_MESH_MODEL_ID_SENSOR_SRV                            0x1100
#define ESP_BLE_MESH_MODEL_ID_SENSOR_SETUP_SRV                      0x1101
#define ESP_BLE_MESH_MODEL_ID_SENSOR_CLI                            0x1102
#define ESP_BLE_MESH_MODEL_ID_TIME_SRV                              0x1200
#define ESP_BLE_MESH_MODEL_ID_TIME_SETUP_SRV                        0x1201
#define ESP_BLE_MESH_MODEL_ID_TIME_CLI                              0x1202
#define ESP_BLE_MESH_MODEL_ID_SCENE_SRV                             0x1203
#define ESP_BLE_MESH_MODEL_ID_SCENE_SETUP_SRV                       0x1204
#define ESP_BLE_MESH_MODEL_ID_SCENE_CLI                             0x1205
#define ESP_BLE_MESH_MODEL_ID_SCHEDULER_SRV                         0x1206
#define ESP_BLE_MESH_MODEL_ID_SCHEDULER_SETUP_SRV                   0x1207
#define ESP_BLE_MESH_MODEL_ID_SCHEDULER_CLI                         0x1208
#define ESP_BLE_MESH_MODEL_ID_LIGHT_LIGHTNESS_SRV                   0x1300
#define ESP_BLE_MESH_MODEL_ID_LIGHT_LIGHTNESS_SETUP_SRV             0x1301
#define ESP_BLE_MESH_MODEL_ID_LIGHT_LIGHTNESS_CLI                   0x1302
#define ESP_BLE_MESH_MODEL_ID_LIGHT_CTL_SRV                         0x1303
#define ESP_BLE_MESH_MODEL_ID_LIGHT_CTL_SETUP_SRV                   0x1304
#define ESP_BLE_MESH_MODEL_ID_LIGHT_CTL_CLI                         0x1305
#define ESP_BLE_MESH_MODEL_ID_LIGHT_CTL_TEMP_SRV                    0x1306
#define ESP_BLE_MESH_MODEL_ID_LIGHT_HSL_SRV                         0x1307
#define ESP_BLE_MESH_MODEL_ID_LIGHT_HSL_SETUP_SRV                   0x1308
#define ESP_BLE_MESH_MODEL_ID_LIGHT_HSL_CLI                         0x1309
#define ESP_BLE_MESH_MODEL_ID_LIGHT_HSL_HUE_SRV                     0x130a
#define ESP_BLE_MESH_MODEL_ID_LIGHT_HSL_SAT_SRV                     0x130b
#define ESP_BLE_MESH_MODEL_ID_LIGHT_XYL_SRV                         0x130c
#define ESP_BLE_MESH_MODEL_ID_LIGHT_XYL_SETUP_SRV                   0x130d
#define ESP_BLE_MESH_MODEL_ID_LIGHT_XYL_CLI                         0x130e
#define ESP_BLE_MESH_MODEL_ID_LIGHT_LC_SRV                          0x130f
#define ESP_BLE_MESH_MODEL_ID_LIGHT_LC_SETUP_SRV                    0x1310
#define ESP_BLE_MESH_MODEL_ID_LIGHT_LC_CLI                          0x1311

/**
 * esp_ble_mesh_opcode_config_client_get_t属于esp_ble_mesh_opcode，此typedef仅用于查找esp_ble-mesh_config_cclient_get_state使用的操作码。以下操作码仅在esp_ble_mesh_config_client_get_state函数中使用。
 */
typedef uint32_t esp_ble_mesh_opcode_config_client_get_t;

#define ESP_BLE_MESH_MODEL_OP_BEACON_GET                            ESP_BLE_MESH_MODEL_OP_2(0x80, 0x09) /*!< 配置信标获取*/
#define ESP_BLE_MESH_MODEL_OP_COMPOSITION_DATA_GET                  ESP_BLE_MESH_MODEL_OP_2(0x80, 0x08) /*!< 配置组成数据获取*/
#define ESP_BLE_MESH_MODEL_OP_DEFAULT_TTL_GET                       ESP_BLE_MESH_MODEL_OP_2(0x80, 0x0C) /*!< 配置默认TTL获取*/
#define ESP_BLE_MESH_MODEL_OP_GATT_PROXY_GET                        ESP_BLE_MESH_MODEL_OP_2(0x80, 0x12) /*!< 配置GATT代理获取*/
#define ESP_BLE_MESH_MODEL_OP_RELAY_GET                             ESP_BLE_MESH_MODEL_OP_2(0x80, 0x26) /*!< 配置继电器获取*/
#define ESP_BLE_MESH_MODEL_OP_MODEL_PUB_GET                         ESP_BLE_MESH_MODEL_OP_2(0x80, 0x18) /*!< 配置模型发布获取*/
#define ESP_BLE_MESH_MODEL_OP_FRIEND_GET                            ESP_BLE_MESH_MODEL_OP_2(0x80, 0x0F) /*!< 配置好友获取*/
#define ESP_BLE_MESH_MODEL_OP_HEARTBEAT_PUB_GET                     ESP_BLE_MESH_MODEL_OP_2(0x80, 0x38) /*!< 配置心跳发布获取*/
#define ESP_BLE_MESH_MODEL_OP_HEARTBEAT_SUB_GET                     ESP_BLE_MESH_MODEL_OP_2(0x80, 0x3a) /*!< 配置心跳订阅获取*/
#define ESP_BLE_MESH_MODEL_OP_NET_KEY_GET                           ESP_BLE_MESH_MODEL_OP_2(0x80, 0x42) /*!< 配置NetKey获取*/
#define ESP_BLE_MESH_MODEL_OP_APP_KEY_GET                           ESP_BLE_MESH_MODEL_OP_2(0x80, 0x01) /*!< 配置AppKey获取*/
#define ESP_BLE_MESH_MODEL_OP_NODE_IDENTITY_GET                     ESP_BLE_MESH_MODEL_OP_2(0x80, 0x46) /*!< 配置节点标识获取*/
#define ESP_BLE_MESH_MODEL_OP_SIG_MODEL_SUB_GET                     ESP_BLE_MESH_MODEL_OP_2(0x80, 0x29) /*!< 配置SIG型号订阅获取*/
#define ESP_BLE_MESH_MODEL_OP_VENDOR_MODEL_SUB_GET                  ESP_BLE_MESH_MODEL_OP_2(0x80, 0x2B) /*!< 配置供应商型号订阅获取*/
#define ESP_BLE_MESH_MODEL_OP_SIG_MODEL_APP_GET                     ESP_BLE_MESH_MODEL_OP_2(0x80, 0x4B) /*!< 配置SIG模型应用程序获取*/
#define ESP_BLE_MESH_MODEL_OP_VENDOR_MODEL_APP_GET                  ESP_BLE_MESH_MODEL_OP_2(0x80, 0x4D) /*!< 配置供应商模型应用程序获取*/
#define ESP_BLE_MESH_MODEL_OP_KEY_REFRESH_PHASE_GET                 ESP_BLE_MESH_MODEL_OP_2(0x80, 0x15) /*!< 配置密钥刷新阶段获取*/
#define ESP_BLE_MESH_MODEL_OP_LPN_POLLTIMEOUT_GET                   ESP_BLE_MESH_MODEL_OP_2(0x80, 0x2D) /*!< 配置低功耗节点轮询超时获取*/
#define ESP_BLE_MESH_MODEL_OP_NETWORK_TRANSMIT_GET                  ESP_BLE_MESH_MODEL_OP_2(0x80, 0x23) /*!< 配置网络传输获取*/

/**
 * esp_ble_mesh_opcode_config_client_set_t属于esp_ble_mesh_opcode，此typedef仅用于查找esp_ble-mesh_config_cclient_set_state使用的操作码。以下操作码仅在esp_ble_mesh_config_client_set_state函数中使用。
 */
typedef uint32_t esp_ble_mesh_opcode_config_client_set_t;

#define ESP_BLE_MESH_MODEL_OP_BEACON_SET                            ESP_BLE_MESH_MODEL_OP_2(0x80, 0x0A) /*!< 配置信标集*/
#define ESP_BLE_MESH_MODEL_OP_DEFAULT_TTL_SET                       ESP_BLE_MESH_MODEL_OP_2(0x80, 0x0D) /*!< 配置默认TTL设置*/
#define ESP_BLE_MESH_MODEL_OP_GATT_PROXY_SET                        ESP_BLE_MESH_MODEL_OP_2(0x80, 0x13) /*!< 配置GATT代理集*/
#define ESP_BLE_MESH_MODEL_OP_RELAY_SET                             ESP_BLE_MESH_MODEL_OP_2(0x80, 0x27) /*!< 配置继电器设置*/
#define ESP_BLE_MESH_MODEL_OP_MODEL_PUB_SET                         ESP_BLE_MESH_MODEL_OP_1(0x03)       /*!< 配置模型发布集*/
#define ESP_BLE_MESH_MODEL_OP_MODEL_SUB_ADD                         ESP_BLE_MESH_MODEL_OP_2(0x80, 0x1B) /*!< 配置模型订阅添加*/
#define ESP_BLE_MESH_MODEL_OP_MODEL_SUB_VIRTUAL_ADDR_ADD            ESP_BLE_MESH_MODEL_OP_2(0x80, 0x20) /*!< 配置模型订阅虚拟地址添加*/
#define ESP_BLE_MESH_MODEL_OP_MODEL_SUB_DELETE                      ESP_BLE_MESH_MODEL_OP_2(0x80, 0x1C) /*!< 配置模型订阅删除*/
#define ESP_BLE_MESH_MODEL_OP_MODEL_SUB_VIRTUAL_ADDR_DELETE         ESP_BLE_MESH_MODEL_OP_2(0x80, 0x21) /*!< 配置模型订阅虚拟地址删除*/
#define ESP_BLE_MESH_MODEL_OP_MODEL_SUB_OVERWRITE                   ESP_BLE_MESH_MODEL_OP_2(0x80, 0x1E) /*!< 配置模型订阅覆盖*/
#define ESP_BLE_MESH_MODEL_OP_MODEL_SUB_VIRTUAL_ADDR_OVERWRITE      ESP_BLE_MESH_MODEL_OP_2(0x80, 0x22) /*!< 配置模型订阅虚拟地址覆盖*/
#define ESP_BLE_MESH_MODEL_OP_NET_KEY_ADD                           ESP_BLE_MESH_MODEL_OP_2(0x80, 0x40) /*!< 配置NetKey添加*/
#define ESP_BLE_MESH_MODEL_OP_APP_KEY_ADD                           ESP_BLE_MESH_MODEL_OP_1(0x00)       /*!< 配置AppKey添加*/
#define ESP_BLE_MESH_MODEL_OP_MODEL_APP_BIND                        ESP_BLE_MESH_MODEL_OP_2(0x80, 0x3D) /*!< 配置模型应用程序绑定*/
#define ESP_BLE_MESH_MODEL_OP_NODE_RESET                            ESP_BLE_MESH_MODEL_OP_2(0x80, 0x49) /*!< 配置节点重置*/
#define ESP_BLE_MESH_MODEL_OP_FRIEND_SET                            ESP_BLE_MESH_MODEL_OP_2(0x80, 0x10) /*!< 配置好友集*/
#define ESP_BLE_MESH_MODEL_OP_HEARTBEAT_PUB_SET                     ESP_BLE_MESH_MODEL_OP_2(0x80, 0x39) /*!< 配置心跳发布集*/
#define ESP_BLE_MESH_MODEL_OP_HEARTBEAT_SUB_SET                     ESP_BLE_MESH_MODEL_OP_2(0x80, 0x3B) /*!< 配置心跳订阅集*/
#define ESP_BLE_MESH_MODEL_OP_NET_KEY_UPDATE                        ESP_BLE_MESH_MODEL_OP_2(0x80, 0x45) /*!< 配置NetKey更新*/
#define ESP_BLE_MESH_MODEL_OP_NET_KEY_DELETE                        ESP_BLE_MESH_MODEL_OP_2(0x80, 0x41) /*!< 配置NetKey删除*/
#define ESP_BLE_MESH_MODEL_OP_APP_KEY_UPDATE                        ESP_BLE_MESH_MODEL_OP_1(0x01)       /*!< 配置AppKey更新*/
#define ESP_BLE_MESH_MODEL_OP_APP_KEY_DELETE                        ESP_BLE_MESH_MODEL_OP_2(0x80, 0x00) /*!< 配置AppKey删除*/
#define ESP_BLE_MESH_MODEL_OP_NODE_IDENTITY_SET                     ESP_BLE_MESH_MODEL_OP_2(0x80, 0x47) /*!< 配置节点标识集*/
#define ESP_BLE_MESH_MODEL_OP_KEY_REFRESH_PHASE_SET                 ESP_BLE_MESH_MODEL_OP_2(0x80, 0x16) /*!< 配置密钥刷新阶段集*/
#define ESP_BLE_MESH_MODEL_OP_MODEL_PUB_VIRTUAL_ADDR_SET            ESP_BLE_MESH_MODEL_OP_2(0x80, 0x1A) /*!< 配置模型发布虚拟地址集*/
#define ESP_BLE_MESH_MODEL_OP_MODEL_SUB_DELETE_ALL                  ESP_BLE_MESH_MODEL_OP_2(0x80, 0x1D) /*!< 配置模型订阅全部删除*/
#define ESP_BLE_MESH_MODEL_OP_MODEL_APP_UNBIND                      ESP_BLE_MESH_MODEL_OP_2(0x80, 0x3F) /*!< 配置模型应用程序解除绑定*/
#define ESP_BLE_MESH_MODEL_OP_NETWORK_TRANSMIT_SET                  ESP_BLE_MESH_MODEL_OP_2(0x80, 0x24) /*!< 配置网络传输集*/

/**
 * esp_ble_mesh_opcode_config_status_t属于esp_ble_mesh_opccode_t，此typedef仅用于查找配置模型消息使用的操作码。ble mesh配置服务器模型内部使用以下操作码来响应配置客户端模型的请求消息。
 */
typedef uint32_t esp_ble_mesh_opcode_config_status_t;

#define ESP_BLE_MESH_MODEL_OP_BEACON_STATUS                         ESP_BLE_MESH_MODEL_OP_2(0x80, 0x0B)
#define ESP_BLE_MESH_MODEL_OP_COMPOSITION_DATA_STATUS               ESP_BLE_MESH_MODEL_OP_1(0x02)
#define ESP_BLE_MESH_MODEL_OP_DEFAULT_TTL_STATUS                    ESP_BLE_MESH_MODEL_OP_2(0x80, 0x0E)
#define ESP_BLE_MESH_MODEL_OP_GATT_PROXY_STATUS                     ESP_BLE_MESH_MODEL_OP_2(0x80, 0x14)
#define ESP_BLE_MESH_MODEL_OP_RELAY_STATUS                          ESP_BLE_MESH_MODEL_OP_2(0x80, 0x28)
#define ESP_BLE_MESH_MODEL_OP_MODEL_PUB_STATUS                      ESP_BLE_MESH_MODEL_OP_2(0x80, 0x19)
#define ESP_BLE_MESH_MODEL_OP_MODEL_SUB_STATUS                      ESP_BLE_MESH_MODEL_OP_2(0x80, 0x1F)
#define ESP_BLE_MESH_MODEL_OP_SIG_MODEL_SUB_LIST                    ESP_BLE_MESH_MODEL_OP_2(0x80, 0x2A)
#define ESP_BLE_MESH_MODEL_OP_VENDOR_MODEL_SUB_LIST                 ESP_BLE_MESH_MODEL_OP_2(0x80, 0x2C)
#define ESP_BLE_MESH_MODEL_OP_NET_KEY_STATUS                        ESP_BLE_MESH_MODEL_OP_2(0x80, 0x44)
#define ESP_BLE_MESH_MODEL_OP_NET_KEY_LIST                          ESP_BLE_MESH_MODEL_OP_2(0x80, 0x43)
#define ESP_BLE_MESH_MODEL_OP_APP_KEY_STATUS                        ESP_BLE_MESH_MODEL_OP_2(0x80, 0x03)
#define ESP_BLE_MESH_MODEL_OP_APP_KEY_LIST                          ESP_BLE_MESH_MODEL_OP_2(0x80, 0x02)
#define ESP_BLE_MESH_MODEL_OP_NODE_IDENTITY_STATUS                  ESP_BLE_MESH_MODEL_OP_2(0x80, 0x48)
#define ESP_BLE_MESH_MODEL_OP_MODEL_APP_STATUS                      ESP_BLE_MESH_MODEL_OP_2(0x80, 0x3E)
#define ESP_BLE_MESH_MODEL_OP_SIG_MODEL_APP_LIST                    ESP_BLE_MESH_MODEL_OP_2(0x80, 0x4C)
#define ESP_BLE_MESH_MODEL_OP_VENDOR_MODEL_APP_LIST                 ESP_BLE_MESH_MODEL_OP_2(0x80, 0x4E)
#define ESP_BLE_MESH_MODEL_OP_NODE_RESET_STATUS                     ESP_BLE_MESH_MODEL_OP_2(0x80, 0x4A)
#define ESP_BLE_MESH_MODEL_OP_FRIEND_STATUS                         ESP_BLE_MESH_MODEL_OP_2(0x80, 0x11)
#define ESP_BLE_MESH_MODEL_OP_KEY_REFRESH_PHASE_STATUS              ESP_BLE_MESH_MODEL_OP_2(0x80, 0x17)
#define ESP_BLE_MESH_MODEL_OP_HEARTBEAT_PUB_STATUS                  ESP_BLE_MESH_MODEL_OP_1(0x06)
#define ESP_BLE_MESH_MODEL_OP_HEARTBEAT_SUB_STATUS                  ESP_BLE_MESH_MODEL_OP_2(0x80, 0x3C)
#define ESP_BLE_MESH_MODEL_OP_LPN_POLLTIMEOUT_STATUS                ESP_BLE_MESH_MODEL_OP_2(0x80, 0x2E)
#define ESP_BLE_MESH_MODEL_OP_NETWORK_TRANSMIT_STATUS               ESP_BLE_MESH_MODEL_OP_2(0x80, 0x25)

/**
 * 此typedef仅用于指示某些Configuration Server Model状态消息中包含的状态代码。
 */
typedef uint8_t esp_ble_mesh_cfg_status_t;

#define ESP_BLE_MESH_CFG_STATUS_SUCCESS                             0x00
#define ESP_BLE_MESH_CFG_STATUS_INVALID_ADDRESS                     0x01
#define ESP_BLE_MESH_CFG_STATUS_INVALID_MODEL                       0x02
#define ESP_BLE_MESH_CFG_STATUS_INVALID_APPKEY                      0x03
#define ESP_BLE_MESH_CFG_STATUS_INVALID_NETKEY                      0x04
#define ESP_BLE_MESH_CFG_STATUS_INSUFFICIENT_RESOURCES              0x05
#define ESP_BLE_MESH_CFG_STATUS_KEY_INDEX_ALREADY_STORED            0x06
#define ESP_BLE_MESH_CFG_STATUS_INVALID_PUBLISH_PARAMETERS          0x07
#define ESP_BLE_MESH_CFG_STATUS_NOT_A_SUBSCRIBE_MODEL               0x08
#define ESP_BLE_MESH_CFG_STATUS_STORAGE_FAILURE                     0x09
#define ESP_BLE_MESH_CFG_STATUS_FEATURE_NOT_SUPPORTED               0x0A
#define ESP_BLE_MESH_CFG_STATUS_CANNOT_UPDATE                       0x0B
#define ESP_BLE_MESH_CFG_STATUS_CANNOT_REMOVE                       0x0C
#define ESP_BLE_MESH_CFG_STATUS_CANNOT_BIND                         0x0D
#define ESP_BLE_MESH_CFG_STATUS_TEMP_UNABLE_TO_CHANGE_STATE         0x0E
#define ESP_BLE_MESH_CFG_STATUS_CANNOT_SET                          0x0F
#define ESP_BLE_MESH_CFG_STATUS_UNSPECIFIED_ERROR                   0x10
#define ESP_BLE_MESH_CFG_STATUS_INVALID_BINDING                     0x11

/**
 * esp_ble_mesh_opcode_health_client_get_t属于esp_ble_mesh_opcode，此typedef仅用于查找esp_ble-mesh_health_client_get_state使用的操作码。以下操作码仅在esp_ble_mesh_health_client_get_state函数中使用。
 */
typedef uint32_t esp_ble_mesh_opcode_health_client_get_t;

#define ESP_BLE_MESH_MODEL_OP_HEALTH_FAULT_GET                      ESP_BLE_MESH_MODEL_OP_2(0x80, 0x31) /*!< 运行状况故障获取*/
#define ESP_BLE_MESH_MODEL_OP_HEALTH_PERIOD_GET                     ESP_BLE_MESH_MODEL_OP_2(0x80, 0x34) /*!< 健康期获取*/
#define ESP_BLE_MESH_MODEL_OP_ATTENTION_GET                         ESP_BLE_MESH_MODEL_OP_2(0x80, 0x04) /*!< 健康注意事项*/

/**
 * esp_ble_mesh_opcode_health_client_set_t属于esp_ble_mesh_opcode，此typedef仅用于查找esp_ble-mesh_health_client_set_state使用的操作码。以下操作码仅在esp_ble_mesh_health_client_set_state函数中使用。
 */
typedef uint32_t esp_ble_mesh_opcode_health_client_set_t;

#define ESP_BLE_MESH_MODEL_OP_HEALTH_FAULT_CLEAR                    ESP_BLE_MESH_MODEL_OP_2(0x80, 0x2F) /*!< 运行状况故障清除*/
#define ESP_BLE_MESH_MODEL_OP_HEALTH_FAULT_CLEAR_UNACK              ESP_BLE_MESH_MODEL_OP_2(0x80, 0x30) /*!< 运行状况故障清除未确认*/
#define ESP_BLE_MESH_MODEL_OP_HEALTH_FAULT_TEST                     ESP_BLE_MESH_MODEL_OP_2(0x80, 0x32) /*!< 健康故障测试*/
#define ESP_BLE_MESH_MODEL_OP_HEALTH_FAULT_TEST_UNACK               ESP_BLE_MESH_MODEL_OP_2(0x80, 0x33) /*!< 健康故障测试未确认*/
#define ESP_BLE_MESH_MODEL_OP_HEALTH_PERIOD_SET                     ESP_BLE_MESH_MODEL_OP_2(0x80, 0x35) /*!< 健康期设置*/
#define ESP_BLE_MESH_MODEL_OP_HEALTH_PERIOD_SET_UNACK               ESP_BLE_MESH_MODEL_OP_2(0x80, 0x36) /*!< 健康期设置未确认*/
#define ESP_BLE_MESH_MODEL_OP_ATTENTION_SET                         ESP_BLE_MESH_MODEL_OP_2(0x80, 0x05) /*!< 健康注意事项集*/
#define ESP_BLE_MESH_MODEL_OP_ATTENTION_SET_UNACK                   ESP_BLE_MESH_MODEL_OP_2(0x80, 0x06) /*!< 健康注意集未确认*/

/**
 * esp_ble_mesh_health_model_status_t属于esp_ble_mesh_opcode_t，此typedef仅用于查找health model消息使用的操作码。BLE Mesh Health Server模型内部使用以下操作码来响应Health Client模型的请求消息。
 */
typedef uint32_t esp_ble_mesh_health_model_status_t;

#define ESP_BLE_MESH_MODEL_OP_HEALTH_CURRENT_STATUS                 ESP_BLE_MESH_MODEL_OP_1(0x04)
#define ESP_BLE_MESH_MODEL_OP_HEALTH_FAULT_STATUS                   ESP_BLE_MESH_MODEL_OP_1(0x05)
#define ESP_BLE_MESH_MODEL_OP_HEALTH_PERIOD_STATUS                  ESP_BLE_MESH_MODEL_OP_2(0x80, 0x37)
#define ESP_BLE_MESH_MODEL_OP_ATTENTION_STATUS                      ESP_BLE_MESH_MODEL_OP_2(0x80, 0x07)

/**
 * esp_ble_mesh_generic_message_opcode_t属于esp_ble_mesh_opcode _t，此typedef仅用于查找函数esp_ble-mesh_generic客户端get_state和esp_ble.mesh_generric_client_set_state使用的操作码。
 */
typedef uint32_t esp_ble_mesh_generic_message_opcode_t;

/*!< 通用开/关消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_GET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x01)
#define ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_SET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x02)
#define ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_SET_UNACK                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x03)
#define ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_STATUS                      ESP_BLE_MESH_MODEL_OP_2(0x82, 0x04)

/*!< 通用级消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_GEN_LEVEL_GET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x05)
#define ESP_BLE_MESH_MODEL_OP_GEN_LEVEL_SET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x06)
#define ESP_BLE_MESH_MODEL_OP_GEN_LEVEL_SET_UNACK                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x07)
#define ESP_BLE_MESH_MODEL_OP_GEN_LEVEL_STATUS                      ESP_BLE_MESH_MODEL_OP_2(0x82, 0x08)
#define ESP_BLE_MESH_MODEL_OP_GEN_DELTA_SET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x09)
#define ESP_BLE_MESH_MODEL_OP_GEN_DELTA_SET_UNACK                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x0A)
#define ESP_BLE_MESH_MODEL_OP_GEN_MOVE_SET                          ESP_BLE_MESH_MODEL_OP_2(0x82, 0x0B)
#define ESP_BLE_MESH_MODEL_OP_GEN_MOVE_SET_UNACK                    ESP_BLE_MESH_MODEL_OP_2(0x82, 0x0C)

/*!< 通用默认转换时间消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_GEN_DEF_TRANS_TIME_GET                ESP_BLE_MESH_MODEL_OP_2(0x82, 0x0D)
#define ESP_BLE_MESH_MODEL_OP_GEN_DEF_TRANS_TIME_SET                ESP_BLE_MESH_MODEL_OP_2(0x82, 0x0E)
#define ESP_BLE_MESH_MODEL_OP_GEN_DEF_TRANS_TIME_SET_UNACK          ESP_BLE_MESH_MODEL_OP_2(0x82, 0x0F)
#define ESP_BLE_MESH_MODEL_OP_GEN_DEF_TRANS_TIME_STATUS             ESP_BLE_MESH_MODEL_OP_2(0x82, 0x10)

/*!< 通用电源开关消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_GEN_ONPOWERUP_GET                     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x11)
#define ESP_BLE_MESH_MODEL_OP_GEN_ONPOWERUP_STATUS                  ESP_BLE_MESH_MODEL_OP_2(0x82, 0x12)

/*!< 通用电源开/关设置消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_GEN_ONPOWERUP_SET                     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x13)
#define ESP_BLE_MESH_MODEL_OP_GEN_ONPOWERUP_SET_UNACK               ESP_BLE_MESH_MODEL_OP_2(0x82, 0x14)

/*!< 通用功率电平消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_GEN_POWER_LEVEL_GET                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x15)
#define ESP_BLE_MESH_MODEL_OP_GEN_POWER_LEVEL_SET                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x16)
#define ESP_BLE_MESH_MODEL_OP_GEN_POWER_LEVEL_SET_UNACK             ESP_BLE_MESH_MODEL_OP_2(0x82, 0x17)
#define ESP_BLE_MESH_MODEL_OP_GEN_POWER_LEVEL_STATUS                ESP_BLE_MESH_MODEL_OP_2(0x82, 0x18)
#define ESP_BLE_MESH_MODEL_OP_GEN_POWER_LAST_GET                    ESP_BLE_MESH_MODEL_OP_2(0x82, 0x19)
#define ESP_BLE_MESH_MODEL_OP_GEN_POWER_LAST_STATUS                 ESP_BLE_MESH_MODEL_OP_2(0x82, 0x1A)
#define ESP_BLE_MESH_MODEL_OP_GEN_POWER_DEFAULT_GET                 ESP_BLE_MESH_MODEL_OP_2(0x82, 0x1B)
#define ESP_BLE_MESH_MODEL_OP_GEN_POWER_DEFAULT_STATUS              ESP_BLE_MESH_MODEL_OP_2(0x82, 0x1C)
#define ESP_BLE_MESH_MODEL_OP_GEN_POWER_RANGE_GET                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x1D)
#define ESP_BLE_MESH_MODEL_OP_GEN_POWER_RANGE_STATUS                ESP_BLE_MESH_MODEL_OP_2(0x82, 0x1E)

/*!< 通用功率电平设置消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_GEN_POWER_DEFAULT_SET                 ESP_BLE_MESH_MODEL_OP_2(0x82, 0x1F)
#define ESP_BLE_MESH_MODEL_OP_GEN_POWER_DEFAULT_SET_UNACK           ESP_BLE_MESH_MODEL_OP_2(0x82, 0x20)
#define ESP_BLE_MESH_MODEL_OP_GEN_POWER_RANGE_SET                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x21)
#define ESP_BLE_MESH_MODEL_OP_GEN_POWER_RANGE_SET_UNACK             ESP_BLE_MESH_MODEL_OP_2(0x82, 0x22)

/*!< 通用电池消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_GEN_BATTERY_GET                       ESP_BLE_MESH_MODEL_OP_2(0x82, 0x23)
#define ESP_BLE_MESH_MODEL_OP_GEN_BATTERY_STATUS                    ESP_BLE_MESH_MODEL_OP_2(0x82, 0x24)

/*!< 通用位置消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_GEN_LOC_GLOBAL_GET                    ESP_BLE_MESH_MODEL_OP_2(0x82, 0x25)
#define ESP_BLE_MESH_MODEL_OP_GEN_LOC_GLOBAL_STATUS                 ESP_BLE_MESH_MODEL_OP_1(0x40)
#define ESP_BLE_MESH_MODEL_OP_GEN_LOC_LOCAL_GET                     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x26)
#define ESP_BLE_MESH_MODEL_OP_GEN_LOC_LOCAL_STATUS                  ESP_BLE_MESH_MODEL_OP_2(0x82, 0x27)

/*!< 通用位置设置消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_GEN_LOC_GLOBAL_SET                    ESP_BLE_MESH_MODEL_OP_1(0x41)
#define ESP_BLE_MESH_MODEL_OP_GEN_LOC_GLOBAL_SET_UNACK              ESP_BLE_MESH_MODEL_OP_1(0x42)
#define ESP_BLE_MESH_MODEL_OP_GEN_LOC_LOCAL_SET                     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x28)
#define ESP_BLE_MESH_MODEL_OP_GEN_LOC_LOCAL_SET_UNACK               ESP_BLE_MESH_MODEL_OP_2(0x82, 0x29)

/*!< 通用制造商属性消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_GEN_MANUFACTURER_PROPERTIES_GET       ESP_BLE_MESH_MODEL_OP_2(0x82, 0x2A)
#define ESP_BLE_MESH_MODEL_OP_GEN_MANUFACTURER_PROPERTIES_STATUS    ESP_BLE_MESH_MODEL_OP_1(0x43)
#define ESP_BLE_MESH_MODEL_OP_GEN_MANUFACTURER_PROPERTY_GET         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x2B)
#define ESP_BLE_MESH_MODEL_OP_GEN_MANUFACTURER_PROPERTY_SET         ESP_BLE_MESH_MODEL_OP_1(0x44)
#define ESP_BLE_MESH_MODEL_OP_GEN_MANUFACTURER_PROPERTY_SET_UNACK   ESP_BLE_MESH_MODEL_OP_1(0x45)
#define ESP_BLE_MESH_MODEL_OP_GEN_MANUFACTURER_PROPERTY_STATUS      ESP_BLE_MESH_MODEL_OP_1(0x46)

/*!< 通用管理属性消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_GEN_ADMIN_PROPERTIES_GET              ESP_BLE_MESH_MODEL_OP_2(0x82, 0x2C)
#define ESP_BLE_MESH_MODEL_OP_GEN_ADMIN_PROPERTIES_STATUS           ESP_BLE_MESH_MODEL_OP_1(0x47)
#define ESP_BLE_MESH_MODEL_OP_GEN_ADMIN_PROPERTY_GET                ESP_BLE_MESH_MODEL_OP_2(0x82, 0x2D)
#define ESP_BLE_MESH_MODEL_OP_GEN_ADMIN_PROPERTY_SET                ESP_BLE_MESH_MODEL_OP_1(0x48)
#define ESP_BLE_MESH_MODEL_OP_GEN_ADMIN_PROPERTY_SET_UNACK          ESP_BLE_MESH_MODEL_OP_1(0x49)
#define ESP_BLE_MESH_MODEL_OP_GEN_ADMIN_PROPERTY_STATUS             ESP_BLE_MESH_MODEL_OP_1(0x4A)

/*!< 通用用户属性消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_GEN_USER_PROPERTIES_GET               ESP_BLE_MESH_MODEL_OP_2(0x82, 0x2E)
#define ESP_BLE_MESH_MODEL_OP_GEN_USER_PROPERTIES_STATUS            ESP_BLE_MESH_MODEL_OP_1(0x4B)
#define ESP_BLE_MESH_MODEL_OP_GEN_USER_PROPERTY_GET                 ESP_BLE_MESH_MODEL_OP_2(0x82, 0x2F)
#define ESP_BLE_MESH_MODEL_OP_GEN_USER_PROPERTY_SET                 ESP_BLE_MESH_MODEL_OP_1(0x4C)
#define ESP_BLE_MESH_MODEL_OP_GEN_USER_PROPERTY_SET_UNACK           ESP_BLE_MESH_MODEL_OP_1(0x4D)
#define ESP_BLE_MESH_MODEL_OP_GEN_USER_PROPERTY_STATUS              ESP_BLE_MESH_MODEL_OP_1(0x4E)

/*!< 通用客户端属性消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_GEN_CLIENT_PROPERTIES_GET             ESP_BLE_MESH_MODEL_OP_1(0x4F)
#define ESP_BLE_MESH_MODEL_OP_GEN_CLIENT_PROPERTIES_STATUS          ESP_BLE_MESH_MODEL_OP_1(0x50)

/**
 * esp_ble_mesh_sensor_message_opcode_t属于esp_ble_mesh_opcodet，此typedef仅用于查找函数esp_ble-mesh_sensor_client_get_state和esp_ble/mesh_sensor-client_set_state使用的操作码。
 */
typedef uint32_t esp_ble_mesh_sensor_message_opcode_t;

/*!< 传感器消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_SENSOR_DESCRIPTOR_GET                 ESP_BLE_MESH_MODEL_OP_2(0x82, 0x30)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_DESCRIPTOR_STATUS              ESP_BLE_MESH_MODEL_OP_1(0x51)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_GET                            ESP_BLE_MESH_MODEL_OP_2(0x82, 0x31)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_STATUS                         ESP_BLE_MESH_MODEL_OP_1(0x52)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_COLUMN_GET                     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x32)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_COLUMN_STATUS                  ESP_BLE_MESH_MODEL_OP_1(0x53)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_SERIES_GET                     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x33)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_SERIES_STATUS                  ESP_BLE_MESH_MODEL_OP_1(0x54)

/*!< 传感器设置消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_SENSOR_CADENCE_GET                    ESP_BLE_MESH_MODEL_OP_2(0x82, 0x34)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_CADENCE_SET                    ESP_BLE_MESH_MODEL_OP_1(0x55)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_CADENCE_SET_UNACK              ESP_BLE_MESH_MODEL_OP_1(0x56)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_CADENCE_STATUS                 ESP_BLE_MESH_MODEL_OP_1(0x57)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_SETTINGS_GET                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x35)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_SETTINGS_STATUS                ESP_BLE_MESH_MODEL_OP_1(0x58)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_SETTING_GET                    ESP_BLE_MESH_MODEL_OP_2(0x82, 0x36)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_SETTING_SET                    ESP_BLE_MESH_MODEL_OP_1(0x59)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_SETTING_SET_UNACK              ESP_BLE_MESH_MODEL_OP_1(0x5A)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_SETTING_STATUS                 ESP_BLE_MESH_MODEL_OP_1(0x5B)

/**
 * esp_ble_mesh_time_scene_message_opcode_t属于esp_ble_mesh_opcode_t，此typedef仅用于查找函数esp_ble-mesh_time_scene_client_get_state和esp_ble/mesh_times_cene_client_set_state使用的操作码。
 */
typedef uint32_t esp_ble_mesh_time_scene_message_opcode_t;

/*!< 时间消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_TIME_GET                              ESP_BLE_MESH_MODEL_OP_2(0x82, 0x37)
#define ESP_BLE_MESH_MODEL_OP_TIME_SET                              ESP_BLE_MESH_MODEL_OP_1(0x5C)
#define ESP_BLE_MESH_MODEL_OP_TIME_STATUS                           ESP_BLE_MESH_MODEL_OP_1(0x5D)
#define ESP_BLE_MESH_MODEL_OP_TIME_ROLE_GET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x38)
#define ESP_BLE_MESH_MODEL_OP_TIME_ROLE_SET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x39)
#define ESP_BLE_MESH_MODEL_OP_TIME_ROLE_STATUS                      ESP_BLE_MESH_MODEL_OP_2(0x82, 0x3A)
#define ESP_BLE_MESH_MODEL_OP_TIME_ZONE_GET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x3B)
#define ESP_BLE_MESH_MODEL_OP_TIME_ZONE_SET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x3C)
#define ESP_BLE_MESH_MODEL_OP_TIME_ZONE_STATUS                      ESP_BLE_MESH_MODEL_OP_2(0x82, 0x3D)
#define ESP_BLE_MESH_MODEL_OP_TAI_UTC_DELTA_GET                     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x3E)
#define ESP_BLE_MESH_MODEL_OP_TAI_UTC_DELTA_SET                     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x3F)
#define ESP_BLE_MESH_MODEL_OP_TAI_UTC_DELTA_STATUS                  ESP_BLE_MESH_MODEL_OP_2(0x82, 0x40)

/*!< 场景消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_SCENE_GET                             ESP_BLE_MESH_MODEL_OP_2(0x82, 0x41)
#define ESP_BLE_MESH_MODEL_OP_SCENE_RECALL                          ESP_BLE_MESH_MODEL_OP_2(0x82, 0x42)
#define ESP_BLE_MESH_MODEL_OP_SCENE_RECALL_UNACK                    ESP_BLE_MESH_MODEL_OP_2(0x82, 0x43)
#define ESP_BLE_MESH_MODEL_OP_SCENE_STATUS                          ESP_BLE_MESH_MODEL_OP_1(0x5E)
#define ESP_BLE_MESH_MODEL_OP_SCENE_REGISTER_GET                    ESP_BLE_MESH_MODEL_OP_2(0x82, 0x44)
#define ESP_BLE_MESH_MODEL_OP_SCENE_REGISTER_STATUS                 ESP_BLE_MESH_MODEL_OP_2(0x82, 0x45)

/*!< 场景设置消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_SCENE_STORE                           ESP_BLE_MESH_MODEL_OP_2(0x82, 0x46)
#define ESP_BLE_MESH_MODEL_OP_SCENE_STORE_UNACK                     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x47)
#define ESP_BLE_MESH_MODEL_OP_SCENE_DELETE                          ESP_BLE_MESH_MODEL_OP_2(0x82, 0x9E)
#define ESP_BLE_MESH_MODEL_OP_SCENE_DELETE_UNACK                    ESP_BLE_MESH_MODEL_OP_2(0x82, 0x9F)

/*!< 调度程序消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_SCHEDULER_ACT_GET                     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x48)
#define ESP_BLE_MESH_MODEL_OP_SCHEDULER_ACT_STATUS                  ESP_BLE_MESH_MODEL_OP_1(0x5F)
#define ESP_BLE_MESH_MODEL_OP_SCHEDULER_GET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x49)
#define ESP_BLE_MESH_MODEL_OP_SCHEDULER_STATUS                      ESP_BLE_MESH_MODEL_OP_2(0x82, 0x4A)

/*!< 调度程序设置消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_SCHEDULER_ACT_SET                     ESP_BLE_MESH_MODEL_OP_1(0x60)
#define ESP_BLE_MESH_MODEL_OP_SCHEDULER_ACT_SET_UNACK               ESP_BLE_MESH_MODEL_OP_1(0x61)

/**
 * esp_ble_mesh_light_message_opcode_t属于esp_ble_mesh_opcodet，此typedef仅用于查找函数esp_ble-mesh_light_client_get_state和esp_ble/mesh_light_client_set_state使用的操作码。
 */
typedef uint32_t esp_ble_mesh_light_message_opcode_t;

/*!< 灯光亮度消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_GET                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x4B)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_SET                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x4C)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_SET_UNACK             ESP_BLE_MESH_MODEL_OP_2(0x82, 0x4D)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_STATUS                ESP_BLE_MESH_MODEL_OP_2(0x82, 0x4E)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_LINEAR_GET            ESP_BLE_MESH_MODEL_OP_2(0x82, 0x4F)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_LINEAR_SET            ESP_BLE_MESH_MODEL_OP_2(0x82, 0x50)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_LINEAR_SET_UNACK      ESP_BLE_MESH_MODEL_OP_2(0x82, 0x51)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_LINEAR_STATUS         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x52)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_LAST_GET              ESP_BLE_MESH_MODEL_OP_2(0x82, 0x53)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_LAST_STATUS           ESP_BLE_MESH_MODEL_OP_2(0x82, 0x54)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_DEFAULT_GET           ESP_BLE_MESH_MODEL_OP_2(0x82, 0x55)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_DEFAULT_STATUS        ESP_BLE_MESH_MODEL_OP_2(0x82, 0x56)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_RANGE_GET             ESP_BLE_MESH_MODEL_OP_2(0x82, 0x57)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_RANGE_STATUS          ESP_BLE_MESH_MODEL_OP_2(0x82, 0x58)

/*!< 灯光亮度设置消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_DEFAULT_SET           ESP_BLE_MESH_MODEL_OP_2(0x82, 0x59)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_DEFAULT_SET_UNACK     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x5A)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_RANGE_SET             ESP_BLE_MESH_MODEL_OP_2(0x82, 0x5B)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_RANGE_SET_UNACK       ESP_BLE_MESH_MODEL_OP_2(0x82, 0x5C)

/*!< 轻型CTL消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_GET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x5D)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_SET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x5E)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_SET_UNACK                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x5F)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_STATUS                      ESP_BLE_MESH_MODEL_OP_2(0x82, 0x60)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_TEMPERATURE_GET             ESP_BLE_MESH_MODEL_OP_2(0x82, 0x61)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_TEMPERATURE_RANGE_GET       ESP_BLE_MESH_MODEL_OP_2(0x82, 0x62)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_TEMPERATURE_RANGE_STATUS    ESP_BLE_MESH_MODEL_OP_2(0x82, 0x63)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_TEMPERATURE_SET             ESP_BLE_MESH_MODEL_OP_2(0x82, 0x64)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_TEMPERATURE_SET_UNACK       ESP_BLE_MESH_MODEL_OP_2(0x82, 0x65)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_TEMPERATURE_STATUS          ESP_BLE_MESH_MODEL_OP_2(0x82, 0x66)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_DEFAULT_GET                 ESP_BLE_MESH_MODEL_OP_2(0x82, 0x67)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_DEFAULT_STATUS              ESP_BLE_MESH_MODEL_OP_2(0x82, 0x68)

/*!< 灯光CTL设置消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_DEFAULT_SET                 ESP_BLE_MESH_MODEL_OP_2(0x82, 0x69)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_DEFAULT_SET_UNACK           ESP_BLE_MESH_MODEL_OP_2(0x82, 0x6A)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_TEMPERATURE_RANGE_SET       ESP_BLE_MESH_MODEL_OP_2(0x82, 0x6B)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_TEMPERATURE_RANGE_SET_UNACK ESP_BLE_MESH_MODEL_OP_2(0x82, 0x6C)

/*!< 轻HSL消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_GET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x6D)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_HUE_GET                     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x6E)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_HUE_SET                     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x6F)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_HUE_SET_UNACK               ESP_BLE_MESH_MODEL_OP_2(0x82, 0x70)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_HUE_STATUS                  ESP_BLE_MESH_MODEL_OP_2(0x82, 0x71)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_SATURATION_GET              ESP_BLE_MESH_MODEL_OP_2(0x82, 0x72)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_SATURATION_SET              ESP_BLE_MESH_MODEL_OP_2(0x82, 0x73)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_SATURATION_SET_UNACK        ESP_BLE_MESH_MODEL_OP_2(0x82, 0x74)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_SATURATION_STATUS           ESP_BLE_MESH_MODEL_OP_2(0x82, 0x75)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_SET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x76)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_SET_UNACK                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x77)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_STATUS                      ESP_BLE_MESH_MODEL_OP_2(0x82, 0x78)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_TARGET_GET                  ESP_BLE_MESH_MODEL_OP_2(0x82, 0x79)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_TARGET_STATUS               ESP_BLE_MESH_MODEL_OP_2(0x82, 0x7A)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_DEFAULT_GET                 ESP_BLE_MESH_MODEL_OP_2(0x82, 0x7B)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_DEFAULT_STATUS              ESP_BLE_MESH_MODEL_OP_2(0x82, 0x7C)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_RANGE_GET                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x7D)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_RANGE_STATUS                ESP_BLE_MESH_MODEL_OP_2(0x82, 0x7E)

/*!< 轻型HSL设置消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_DEFAULT_SET                 ESP_BLE_MESH_MODEL_OP_2(0x82, 0x7F)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_DEFAULT_SET_UNACK           ESP_BLE_MESH_MODEL_OP_2(0x82, 0x80)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_RANGE_SET                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x81)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_RANGE_SET_UNACK             ESP_BLE_MESH_MODEL_OP_2(0x82, 0x82)

/*!< 轻xyL消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_GET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x83)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_SET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x84)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_SET_UNACK                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x85)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_STATUS                      ESP_BLE_MESH_MODEL_OP_2(0x82, 0x86)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_TARGET_GET                  ESP_BLE_MESH_MODEL_OP_2(0x82, 0x87)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_TARGET_STATUS               ESP_BLE_MESH_MODEL_OP_2(0x82, 0x88)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_DEFAULT_GET                 ESP_BLE_MESH_MODEL_OP_2(0x82, 0x89)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_DEFAULT_STATUS              ESP_BLE_MESH_MODEL_OP_2(0x82, 0x8A)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_RANGE_GET                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x8B)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_RANGE_STATUS                ESP_BLE_MESH_MODEL_OP_2(0x82, 0x8C)

/*!< 轻xyL设置消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_DEFAULT_SET                 ESP_BLE_MESH_MODEL_OP_2(0x82, 0x8D)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_DEFAULT_SET_UNACK           ESP_BLE_MESH_MODEL_OP_2(0x82, 0x8E)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_RANGE_SET                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x8F)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_RANGE_SET_UNACK             ESP_BLE_MESH_MODEL_OP_2(0x82, 0x90)

/*!< 灯光控制消息操作码*/
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_MODE_GET                     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x91)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_MODE_SET                     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x92)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_MODE_SET_UNACK               ESP_BLE_MESH_MODEL_OP_2(0x82, 0x93)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_MODE_STATUS                  ESP_BLE_MESH_MODEL_OP_2(0x82, 0x94)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_OM_GET                       ESP_BLE_MESH_MODEL_OP_2(0x82, 0x95)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_OM_SET                       ESP_BLE_MESH_MODEL_OP_2(0x82, 0x96)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_OM_SET_UNACK                 ESP_BLE_MESH_MODEL_OP_2(0x82, 0x97)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_OM_STATUS                    ESP_BLE_MESH_MODEL_OP_2(0x82, 0x98)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_LIGHT_ONOFF_GET              ESP_BLE_MESH_MODEL_OP_2(0x82, 0x99)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_LIGHT_ONOFF_SET              ESP_BLE_MESH_MODEL_OP_2(0x82, 0x9A)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_LIGHT_ONOFF_SET_UNACK        ESP_BLE_MESH_MODEL_OP_2(0x82, 0x9B)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_LIGHT_ONOFF_STATUS           ESP_BLE_MESH_MODEL_OP_2(0x82, 0x9C)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_PROPERTY_GET                 ESP_BLE_MESH_MODEL_OP_2(0x82, 0x9D)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_PROPERTY_SET                 ESP_BLE_MESH_MODEL_OP_1(0x62)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_PROPERTY_SET_UNACK           ESP_BLE_MESH_MODEL_OP_1(0x63)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_PROPERTY_STATUS              ESP_BLE_MESH_MODEL_OP_1(0x64)

typedef uint32_t esp_ble_mesh_opcode_t;
/*!< esp_ble_mesh_opcode_t的定义结束*/

/**
 * 此typedef仅用于指示某些服务器模型（例如通用服务器模型）状态消息中包含的状态代码。
 */
typedef uint8_t esp_ble_mesh_model_status_t;

#define ESP_BLE_MESH_MODEL_STATUS_SUCCESS                           0x00
#define ESP_BLE_MESH_MODEL_STATUS_CANNOT_SET_RANGE_MIN              0x01
#define ESP_BLE_MESH_MODEL_STATUS_CANNOT_SET_RANGE_MAX              0x02

/**
 * @brief BLE Mesh客户端模型相关定义
 */

/**客户端模型获取/设置消息操作码和相应的状态消息操作码*/
typedef struct {
    uint32_t cli_op;        /*!< 客户端消息操作码*/
    uint32_t status_op;     /*!< 与客户端消息操作码相对应的服务器状态操作码*/
} esp_ble_mesh_client_op_pair_t;

/**客户端模型用户数据上下文。*/
typedef struct {
    esp_ble_mesh_model_t *model;                    /*!< 指向客户端模型的指针。已由堆栈初始化。*/
    int op_pair_size;                               /*!< op_pair的大小*/
    const esp_ble_mesh_client_op_pair_t *op_pair;   /*!< 包含获取/设置消息操作码和相应状态消息操作码的表*/
    uint32_t publish_status;                        /*!< 用于处理收到的未经请求的消息的回调。已由堆栈初始化。*/
    void *internal_data;                            /*!< 指向客户端模型内部数据的指针*/
    uint8_t msg_role;                               /*!< 要发送消息的设备（节点/配置器）的角色*/
} esp_ble_mesh_client_t;

/**客户端模型发送的消息的公共参数。*/
typedef struct {
    esp_ble_mesh_opcode_t opcode;   /*!< 消息操作码*/
    esp_ble_mesh_model_t *model;    /*!< 指向客户端模型结构的指针*/
    esp_ble_mesh_msg_ctx_t ctx;     /*!< 用于发送消息的上下文*/
    int32_t msg_timeout;            /*!< 获取发送消息响应的超时值（毫秒）*/
    /*!< 注意：如果在menuconfig中使用默认超时值，请确保将该值设置为0*/
    uint8_t msg_role;               /*!< 设备的角色-节点/配置器*/
} esp_ble_mesh_client_common_param_t;

/**
 * @brief BLE Mesh服务器模型相关定义
 */

/**此枚举值是转换计时器操作的标志*/
enum {
    ESP_BLE_MESH_SERVER_TRANS_TIMER_START,  /* 已启动适当的过渡计时器*/
    ESP_BLE_MESH_SERVER_FLAG_MAX,
};

/**服务器模型状态转换的参数*/
typedef struct {
    bool just_started;          /*!< 指示状态转换是否刚刚开始*/

    uint8_t  trans_time;        /*!< 状态转换时间*/
    uint8_t  remain_time;       /*!< 状态转换剩余时间*/
    uint8_t  delay;             /*!< 启动状态转换前的延迟*/
    uint32_t quo_tt;            /*!< 每个分段过渡步骤的持续时间*/
    uint32_t counter;           /*!< 划分过渡持续时间的步骤数*/
    uint32_t total_duration;    /*!< 状态转换总持续时间*/
    int64_t  start_timestamp;   /*!< 状态转换开始的时间*/

    /**
     * 用于指示转换计时器是否已在内部启动的标志。
     *
     * 如果包含esp_ble_mesh_state_transition_t的模型将“set_auto_rsp”设置为esp_ble_mesh_SERVER_rsp_BY_APP，则计时器的处理程序应由用户初始化。
     *
     * 用户可以使用此标志来指示计时器是否启动。
     */
    BLE_MESH_ATOMIC_DEFINE(flag, ESP_BLE_MESH_SERVER_FLAG_MAX);
    struct k_delayed_work timer;    /*!< 用于状态转换的计时器*/
} esp_ble_mesh_state_transition_t;

/**服务器模型的参数收到了最后一条相同的设置消息。*/
typedef struct {
    uint8_t  tid;       /*!< 最后一条消息的事务处理号*/
    uint16_t src;       /*!< 最后一条消息的源地址*/
    uint16_t dst;       /*!< 最后一条消息的目标地址*/
    int64_t  timestamp; /*!< 收到最后一条消息的时间*/
} esp_ble_mesh_last_msg_info_t;

#define ESP_BLE_MESH_SERVER_RSP_BY_APP  0   /*!< 需要在应用程序中发送响应*/
#define ESP_BLE_MESH_SERVER_AUTO_RSP    1   /*!< 响应将在内部发送*/

/**服务器模型响应控件的参数*/
typedef struct {
    /**
     * @brief BLE Mesh服务器响应选项1.如果get_auto_rsp设置为ESP_BLE_Mesh_Server_rsp_BY_APP，则客户端获取消息的响应需要由应用程序回复；2.如果get_auto_rsp设置为ESP_BLE_MESH_SERVER_auto_rsp，则客户端获取消息的响应将由服务器模型回复；3.如果set_auto_rsp设置为ESP_BLE_MESH_SERVER_rsp_BY_APP，则客户端设置消息的响应需要由应用程序回复；4.如果set_auto_rsp设置为ESP_BLE_MESH_SERVER_auto_rsp，则客户端设置消息的响应将由服务器模型回复；5.如果status_auto_rsp设置为ESP_BLE_MESH_SERVER_rsp_BY_APP，则应用程序需要回复服务器状态消息的响应；6.如果status_auto_rsp设置为ESP_BLE_MESH_SERVER_auto_rsp，则服务器模型将回复服务器状态消息的响应；
     */
    uint8_t get_auto_rsp : 1,       /*!< 客户端Get消息的响应控制*/
            set_auto_rsp : 1,       /*!< 客户端集消息的响应控制*/
            status_auto_rsp : 1;    /*!< 服务器状态消息的响应控制*/
} esp_ble_mesh_server_rsp_ctrl_t;

/**
 * @brief 服务器模型状态值联合
 */
typedef union {
    struct {
        uint8_t onoff;          /*!< Generic OnOff状态的值*/
    } gen_onoff;                /*!< 通用开/关状态*/
    struct {
        int16_t level;          /*!< “通用级别”状态的值*/
    } gen_level;                /*!< 通用级别状态*/
    struct {
        uint8_t onpowerup;      /*!< Generic OnPowerUp状态的值*/
    } gen_onpowerup;            /*!< Generic OnPowerUp状态*/
    struct {
        uint16_t power;         /*!< 通用功率实际状态的值*/
    } gen_power_actual;         /*!< 通用功率实际状态*/
    struct {
        uint16_t lightness;     /*!< “Light Lightness Actual”状态的值*/
    } light_lightness_actual;   /*!< 灯光亮度实际状态*/
    struct {
        uint16_t lightness;     /*!< “灯光亮度线性”状态的值*/
    } light_lightness_linear;   /*!< 光线亮度线性状态*/
    struct {
        uint16_t lightness;     /*!< 灯光CTL亮度状态的值*/
    } light_ctl_lightness;      /*!< 灯光CTL亮度状态*/
    struct {
        uint16_t temperature;   /*!< 灯光CTL温度状态的值*/
        int16_t  delta_uv;      /*!< 灯光CTL增量UV状态的值*/
    } light_ctl_temp_delta_uv;  /*!< 光CTL温度和增量UV状态*/
    struct {
        uint16_t lightness;     /*!< 灯光HSL亮度状态的值*/
        uint16_t hue;           /*!< 灯光HSL色调状态的值*/
        uint16_t saturation;    /*!< 光HSL饱和状态的值*/
    } light_hsl;                /*!< 轻型HSL复合状态*/
    struct {
        uint16_t lightness;     /*!< 灯光HSL亮度状态的值*/
    } light_hsl_lightness;      /*!< 光HSL亮度状态*/
    struct {
        uint16_t hue;           /*!< 灯光HSL色调状态的值*/
    } light_hsl_hue;            /*!< 轻HSL色调状态*/
    struct {
        uint16_t saturation;    /*!< 光HSL饱和状态的值*/
    } light_hsl_saturation;     /*!< 轻HSL饱和状态*/
    struct {
        uint16_t lightness;     /*!< 灯光xyL亮度状态的值*/
    } light_xyl_lightness;      /*!< 灯光xyL亮度状态*/
    struct {
        uint8_t onoff;          /*!< Light LC Light OnOff状态的值*/
    } light_lc_light_onoff;     /*!< 灯LC灯开关状态*/
} esp_ble_mesh_server_state_value_t;

/**此枚举值是服务器模型状态的类型*/
typedef enum {
    ESP_BLE_MESH_GENERIC_ONOFF_STATE,
    ESP_BLE_MESH_GENERIC_LEVEL_STATE,
    ESP_BLE_MESH_GENERIC_ONPOWERUP_STATE,
    ESP_BLE_MESH_GENERIC_POWER_ACTUAL_STATE,
    ESP_BLE_MESH_LIGHT_LIGHTNESS_ACTUAL_STATE,
    ESP_BLE_MESH_LIGHT_LIGHTNESS_LINEAR_STATE,
    ESP_BLE_MESH_LIGHT_CTL_LIGHTNESS_STATE,
    ESP_BLE_MESH_LIGHT_CTL_TEMP_DELTA_UV_STATE,
    ESP_BLE_MESH_LIGHT_HSL_STATE,
    ESP_BLE_MESH_LIGHT_HSL_LIGHTNESS_STATE,
    ESP_BLE_MESH_LIGHT_HSL_HUE_STATE,
    ESP_BLE_MESH_LIGHT_HSL_SATURATION_STATE,
    ESP_BLE_MESH_LIGHT_XYL_LIGHTNESS_STATE,
    ESP_BLE_MESH_LIGHT_LC_LIGHT_ONOFF_STATE,
    ESP_BLE_MESH_SERVER_MODEL_STATE_MAX,
} esp_ble_mesh_server_state_type_t;

/*!< 此枚举值是未定义SIG模型和供应商模型的事件*/
typedef enum {
    ESP_BLE_MESH_MODEL_OPERATION_EVT,                   /*!< 用户定义的模型从对等设备接收消息（例如获取、设置、状态等）事件*/
    ESP_BLE_MESH_MODEL_SEND_COMP_EVT,                   /*!< 用户定义的模型发送消息完成事件*/
    ESP_BLE_MESH_MODEL_PUBLISH_COMP_EVT,                /*!< 用户定义的模型发布消息完成事件*/
    ESP_BLE_MESH_CLIENT_MODEL_RECV_PUBLISH_MSG_EVT,     /*!< 用户定义的客户端模型接收发布消息事件*/
    ESP_BLE_MESH_CLIENT_MODEL_SEND_TIMEOUT_EVT,         /*!< 无法从对等服务器模型接收响应的用户定义客户端模型的超时事件*/
    ESP_BLE_MESH_MODEL_PUBLISH_UPDATE_EVT,              /*!< 当模型配置为定期发布消息时，此事件将在每个发布期间发生*/
    ESP_BLE_MESH_SERVER_MODEL_UPDATE_STATE_COMP_EVT,    /*!< 服务器模型更新状态值完成事件*/
    ESP_BLE_MESH_MODEL_EVT_MAX,
} esp_ble_mesh_model_cb_event_t;

/**
 * @brief BLE Mesh模型回调参数联合
 */
typedef union {
    /**
     * @brief ESP_BLE_MESH_MODEL_OPERATION_EVT
     */
    struct ble_mesh_model_operation_evt_param {
        uint32_t opcode;                /*!< 接收消息的操作码*/
        esp_ble_mesh_model_t *model;    /*!< 指向接收消息的模型的指针*/
        esp_ble_mesh_msg_ctx_t *ctx;    /*!< 指向接收消息上下文的指针*/
        uint16_t length;                /*!< 收到消息的长度*/
        uint8_t *msg;                   /*!< 收到消息的值*/
    } model_operation;                  /*!< ESP_BLE_MESH_MODEL_OPERATION_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_MODEL_SEND_COMP_EVT
     */
    struct ble_mesh_model_send_comp_param {
        int err_code;                   /*!< 指示发送消息的结果*/
        uint32_t opcode;                /*!< 消息的操作码*/
        esp_ble_mesh_model_t *model;    /*!< 指向发送消息的模型的指针*/
        esp_ble_mesh_msg_ctx_t *ctx;    /*!< 消息的上下文*/
    } model_send_comp;                  /*!< ESP_BLE_MESH_MODEL_SEND_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_MODEL_PUBLISH_COMP_EVT
     */
    struct ble_mesh_model_publish_comp_param {
        int err_code;                   /*!< 指示发布消息的结果*/
        esp_ble_mesh_model_t *model;    /*!< 指向发布消息的模型的指针*/
    } model_publish_comp;               /*!< ESP_BLE_MESH_MODEL_PUBLISH_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_CLIENT_MODEL_RECV_PUBLISH_MSG_EVT
     */
    struct ble_mesh_mod_recv_publish_msg_param {
        uint32_t opcode;                /*!< 未经请求的接收消息的操作码*/
        esp_ble_mesh_model_t *model;    /*!< 指向接收消息的模型的指针*/
        esp_ble_mesh_msg_ctx_t *ctx;    /*!< 指向消息上下文的指针*/
        uint16_t length;                /*!< 收到消息的长度*/
        uint8_t *msg;                   /*!< 收到消息的值*/
    } client_recv_publish_msg;          /*!< ESP_BLE_MESH_CLIENT_MODEL_RECV_PUBLISH_MSG_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_CLIENT_MODEL_SEND_TIMEOUT_EVT
     */
    struct ble_mesh_client_model_send_timeout_param {
        uint32_t opcode;                /*!< 先前发送消息的操作码*/
        esp_ble_mesh_model_t *model;    /*!< 指向发送前一消息的模型的指针*/
        esp_ble_mesh_msg_ctx_t *ctx;    /*!< 指向上一条消息上下文的指针*/
    } client_send_timeout;              /*!< ESP_BLE_MESH_CLIENT_MODEL_SEND_TIMEOUT_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_MODEL_PUBLISH_UPDATE_EVT
     */
    struct ble_mesh_model_publish_update_evt_param {
        esp_ble_mesh_model_t *model;    /*!< 指向要更新其发布消息的模型的指针*/
    } model_publish_update;             /*!< ESP_BLE_MESH_MODEL_PUBLISH_UPDATE_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_SERVER_MODEL_UPDATE_STATE_COMP_EVT
     */
    struct ble_mesh_server_model_update_state_comp_param {
        int err_code;                           /*!< 指示更新服务器模型状态的结果*/
        esp_ble_mesh_model_t *model;            /*!< 指向状态值已更新的服务器模型的指针*/
        esp_ble_mesh_server_state_type_t type;  /*!< 更新的服务器状态的类型*/
    } server_model_update_state;                /*!< ESP_BLE_MESH_SERVER_MODEL_UPDATE_STATE_COMP_EVT的事件参数*/
} esp_ble_mesh_model_cb_param_t;

#ifdef __cplusplus
}
#endif

#endif /* _ESP_BLE_MESH_DEFS_H_ */

