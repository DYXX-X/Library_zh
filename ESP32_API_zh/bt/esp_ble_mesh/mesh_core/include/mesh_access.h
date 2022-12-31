/** @file
 *  @brief 蓝牙网格接入层API。
 */

/*
 * SPDX文件版权文本：2017 Intel Corporation SPDX FileContributor:2018-2021 Espressif Systems（Shanghai）CO LTD
 *
 * SPDX许可证标识符：Apache-2.0
 */
#ifndef _BLE_MESH_ACCESS_H_
#define _BLE_MESH_ACCESS_H_

#include "mesh_config.h"
#include "mesh_buf.h"
#include "mesh_timer.h"

/**
 * @brief 蓝牙网格接入层
 * @defgroup bt_mesh_access蓝牙网格访问层
 * @ingroup bt_网格@{
 */

#ifdef __cplusplus
extern "C" {
#endif

#define BLE_MESH_CID_NVAL          0xFFFF

#define BLE_MESH_ADDR_UNASSIGNED   0x0000
#define BLE_MESH_ADDR_ALL_NODES    0xffff
#define BLE_MESH_ADDR_PROXIES      0xfffc
#define BLE_MESH_ADDR_FRIENDS      0xfffd
#define BLE_MESH_ADDR_RELAYS       0xfffe

#define BLE_MESH_KEY_UNUSED        0xffff
#define BLE_MESH_KEY_DEV           0xfffe

/** 用于在数组中定义网格元素的助手。
 *
 *  如果元素没有SIG或Vendor模型，则可以改用帮助宏BLE_MESH_MODEL_NONE。
 *
 *  @param _loc       位置描述符。
 *  @param _mods      模型阵列。
 *  @param _vnd_mods  供应商模型阵列。
 */
#define BLE_MESH_ELEM(_loc, _mods, _vnd_mods)   \
{                                               \
    .loc              = (_loc),                 \
    .model_count      = ARRAY_SIZE(_mods),      \
    .models           = (_mods),                \
    .vnd_model_count  = ARRAY_SIZE(_vnd_mods),  \
    .vnd_models       = (_vnd_mods),            \
}

/**描述网格元素的抽象*/
struct bt_mesh_elem {
    /* 单播地址。在配置期间在运行时设置。*/
    uint16_t addr;

    /* 位置描述符（GATT蓝牙命名空间描述符）*/
    const uint16_t loc;

    const uint8_t model_count;
    const uint8_t vnd_model_count;

    struct bt_mesh_model *const models;
    struct bt_mesh_model *const vnd_models;
};

/* 基础模型*/
#define BLE_MESH_MODEL_ID_CFG_SRV                   0x0000
#define BLE_MESH_MODEL_ID_CFG_CLI                   0x0001
#define BLE_MESH_MODEL_ID_HEALTH_SRV                0x0002
#define BLE_MESH_MODEL_ID_HEALTH_CLI                0x0003

/* 网格模型规范中的模型*/
#define BLE_MESH_MODEL_ID_GEN_ONOFF_SRV             0x1000
#define BLE_MESH_MODEL_ID_GEN_ONOFF_CLI             0x1001
#define BLE_MESH_MODEL_ID_GEN_LEVEL_SRV             0x1002
#define BLE_MESH_MODEL_ID_GEN_LEVEL_CLI             0x1003
#define BLE_MESH_MODEL_ID_GEN_DEF_TRANS_TIME_SRV    0x1004
#define BLE_MESH_MODEL_ID_GEN_DEF_TRANS_TIME_CLI    0x1005
#define BLE_MESH_MODEL_ID_GEN_POWER_ONOFF_SRV       0x1006
#define BLE_MESH_MODEL_ID_GEN_POWER_ONOFF_SETUP_SRV 0x1007
#define BLE_MESH_MODEL_ID_GEN_POWER_ONOFF_CLI       0x1008
#define BLE_MESH_MODEL_ID_GEN_POWER_LEVEL_SRV       0x1009
#define BLE_MESH_MODEL_ID_GEN_POWER_LEVEL_SETUP_SRV 0x100a
#define BLE_MESH_MODEL_ID_GEN_POWER_LEVEL_CLI       0x100b
#define BLE_MESH_MODEL_ID_GEN_BATTERY_SRV           0x100c
#define BLE_MESH_MODEL_ID_GEN_BATTERY_CLI           0x100d
#define BLE_MESH_MODEL_ID_GEN_LOCATION_SRV          0x100e
#define BLE_MESH_MODEL_ID_GEN_LOCATION_SETUP_SRV    0x100f
#define BLE_MESH_MODEL_ID_GEN_LOCATION_CLI          0x1010
#define BLE_MESH_MODEL_ID_GEN_ADMIN_PROP_SRV        0x1011
#define BLE_MESH_MODEL_ID_GEN_MANUFACTURER_PROP_SRV 0x1012
#define BLE_MESH_MODEL_ID_GEN_USER_PROP_SRV         0x1013
#define BLE_MESH_MODEL_ID_GEN_CLIENT_PROP_SRV       0x1014
#define BLE_MESH_MODEL_ID_GEN_PROP_CLI              0x1015
#define BLE_MESH_MODEL_ID_SENSOR_SRV                0x1100
#define BLE_MESH_MODEL_ID_SENSOR_SETUP_SRV          0x1101
#define BLE_MESH_MODEL_ID_SENSOR_CLI                0x1102
#define BLE_MESH_MODEL_ID_TIME_SRV                  0x1200
#define BLE_MESH_MODEL_ID_TIME_SETUP_SRV            0x1201
#define BLE_MESH_MODEL_ID_TIME_CLI                  0x1202
#define BLE_MESH_MODEL_ID_SCENE_SRV                 0x1203
#define BLE_MESH_MODEL_ID_SCENE_SETUP_SRV           0x1204
#define BLE_MESH_MODEL_ID_SCENE_CLI                 0x1205
#define BLE_MESH_MODEL_ID_SCHEDULER_SRV             0x1206
#define BLE_MESH_MODEL_ID_SCHEDULER_SETUP_SRV       0x1207
#define BLE_MESH_MODEL_ID_SCHEDULER_CLI             0x1208
#define BLE_MESH_MODEL_ID_LIGHT_LIGHTNESS_SRV       0x1300
#define BLE_MESH_MODEL_ID_LIGHT_LIGHTNESS_SETUP_SRV 0x1301
#define BLE_MESH_MODEL_ID_LIGHT_LIGHTNESS_CLI       0x1302
#define BLE_MESH_MODEL_ID_LIGHT_CTL_SRV             0x1303
#define BLE_MESH_MODEL_ID_LIGHT_CTL_SETUP_SRV       0x1304
#define BLE_MESH_MODEL_ID_LIGHT_CTL_CLI             0x1305
#define BLE_MESH_MODEL_ID_LIGHT_CTL_TEMP_SRV        0x1306
#define BLE_MESH_MODEL_ID_LIGHT_HSL_SRV             0x1307
#define BLE_MESH_MODEL_ID_LIGHT_HSL_SETUP_SRV       0x1308
#define BLE_MESH_MODEL_ID_LIGHT_HSL_CLI             0x1309
#define BLE_MESH_MODEL_ID_LIGHT_HSL_HUE_SRV         0x130a
#define BLE_MESH_MODEL_ID_LIGHT_HSL_SAT_SRV         0x130b
#define BLE_MESH_MODEL_ID_LIGHT_XYL_SRV             0x130c
#define BLE_MESH_MODEL_ID_LIGHT_XYL_SETUP_SRV       0x130d
#define BLE_MESH_MODEL_ID_LIGHT_XYL_CLI             0x130e
#define BLE_MESH_MODEL_ID_LIGHT_LC_SRV              0x130f
#define BLE_MESH_MODEL_ID_LIGHT_LC_SETUP_SRV        0x1310
#define BLE_MESH_MODEL_ID_LIGHT_LC_CLI              0x1311

/**消息发送上下文。*/
struct bt_mesh_msg_ctx {
    /**要发送消息的子网的NetKey索引。*/
    uint16_t net_idx;

    /**用于加密消息的AppKey索引。*/
    uint16_t app_idx;

    /**远程地址。*/
    uint16_t addr;

    /**接收消息的目标地址。不用于发送。*/
    uint16_t recv_dst;

    /**接收分组的RSSI。不用于发送。*/
    int8_t  recv_rssi;

    /**收到TTL值。不用于发送。*/
    uint8_t  recv_ttl: 7;

    /**使用段确认强制可靠发送*/
    uint8_t  send_rel: 1;

    /**TTL或BLE_MESH_TTL_DEFAULT（默认TTL）。*/
    uint8_t  send_ttl;

    /**通过Espressif进行更改，即接收到的消息的操作码。不用于发送消息。*/
    uint32_t recv_op;

    /**Espressif更改，型号与消息对应*/
    struct bt_mesh_model *model;

    /**如果消息由服务器模型发送，则通过Espressif进行更改。不用于接收消息。*/
    bool srv_send;
};

struct bt_mesh_model_op {
    /* 使用BLE_MESH_MODEL_OP_*宏编码的OpCode*/
    const uint32_t  opcode;

    /* 所需的最小消息长度*/
    const size_t min_len;

    /* 操作码的消息处理程序*/
    void (*const func)(struct bt_mesh_model *model,
                       struct bt_mesh_msg_ctx *ctx,
                       struct net_buf_simple *buf);
};

#define BLE_MESH_MODEL_OP_1(b0)         (b0)
#define BLE_MESH_MODEL_OP_2(b0, b1)     (((b0) << 8) | (b1))
#define BLE_MESH_MODEL_OP_3(b0, cid)    ((((b0) << 16) | 0xc00000) | (cid))

#define BLE_MESH_MODEL_OP_END           { 0, 0, NULL }
#define BLE_MESH_MODEL_NO_OPS           ((struct bt_mesh_model_op []) \
                                        { BLE_MESH_MODEL_OP_END })

/**定义空模型数组的助手*/
#define BLE_MESH_MODEL_NONE             ((struct bt_mesh_model []){})

/**短网眼MIC的长度。*/
#define BLE_MESH_MIC_SHORT              4
/**长网眼MIC的长度。*/
#define BLE_MESH_MIC_LONG               8

/** @def BLE_MESH_MODEL_OP_LEN
 *
 * @brief 帮助程序确定操作码的长度。
 *
 * @param _op 操作码。
 */
#define BLE_MESH_MODEL_OP_LEN(_op) ((_op) <= 0xff ? 1 : (_op) <= 0xffff ? 2 : 3)

/** @def BLE_MESH_MODEL_BUF_LEN
 *
 * @brief 模型消息缓冲区长度的帮助程序。
 *
 * 返回Mesh模型消息缓冲区的长度，包括操作码长度和短MIC。
 *
 * @param _op 消息的操作码。
 * @param _payload_len 模型有效载荷的长度。
 */
#define BLE_MESH_MODEL_BUF_LEN(_op, _payload_len)                \
        (BLE_MESH_MODEL_OP_LEN(_op) + (_payload_len) + BLE_MESH_MIC_SHORT)

/** @def BLE_MESH_MODEL_BUF_LEN_LONG_MIC
 *
 * @brief 模型消息缓冲区长度的帮助程序。
 *
 * 返回Mesh模型消息缓冲区的长度，包括操作码长度和长MIC。
 *
 * @param _op 消息的操作码。
 * @param _payload_len 模型有效载荷的长度。
 */
#define BLE_MESH_MODEL_BUF_LEN_LONG_MIC(_op, _payload_len)       \
        (BLE_MESH_MODEL_OP_LEN(_op) + (_payload_len) + BLE_MESH_MIC_LONG)

/** @def BLE_MESH_MODEL_BUF_DEFINE
 *
 * @brief 使用@ref NET_BUF_SIMPLE_Define定义网格模型消息缓冲区。
 *
 * @param _buf 缓冲区名称。
 * @param _op 消息的操作码。
 * @param _payload_len 模型消息负载的长度。
 */
#define BLE_MESH_MODEL_BUF_DEFINE(_buf, _op, _payload_len)       \
        NET_BUF_SIMPLE_DEFINE(_buf, BLE_MESH_MODEL_BUF_LEN((_op), (_payload_len)))

/** @def BLE_MESH_MODEL_CB
 *
 *  @brief 具有回调函数的合成数据SIG模型条目。
 *
 *  @param _id        型号ID。
 *  @param _op        模型操作码处理程序数组。
 *  @param _pub       模型发布参数。
 *  @param _user_data 模型的用户数据。
 *  @param _cb        回调结构，或NULL以保持无回调。
 */
#define BLE_MESH_MODEL_CB(_id, _op, _pub, _user_data, _cb)          \
{                                                                   \
    .id = (_id),                                                    \
    .op = (_op),                                                    \
    .keys = { [0 ... (CONFIG_BLE_MESH_MODEL_KEY_COUNT - 1)] =       \
            BLE_MESH_KEY_UNUSED },                                  \
    .pub = (_pub),                                                  \
    .groups = { [0 ... (CONFIG_BLE_MESH_MODEL_GROUP_COUNT - 1)] =   \
            BLE_MESH_ADDR_UNASSIGNED },                             \
    .user_data = (_user_data),                                      \
    .cb = (_cb),                                                    \
}

/** @def BLE_MESH_MODEL_VND_CB
 *
 *  @brief 具有回调函数的合成数据供应商模型条目。
 *
 *  @param _company   公司ID。
 *  @param _id        型号ID。
 *  @param _op        模型操作码处理程序数组。
 *  @param _pub       模型发布参数。
 *  @param _user_data 模型的用户数据。
 *  @param _cb        回调结构，或NULL以保持无回调。
 */
#define BLE_MESH_MODEL_VND_CB(_company, _id, _op, _pub, _user_data, _cb) \
{                                                                   \
    .vnd.company = (_company),                                      \
    .vnd.id = (_id),                                                \
    .op = (_op),                                                    \
    .pub = (_pub),                                                  \
    .keys = { [0 ... (CONFIG_BLE_MESH_MODEL_KEY_COUNT - 1)] =       \
            BLE_MESH_KEY_UNUSED },                                  \
    .groups = { [0 ... (CONFIG_BLE_MESH_MODEL_GROUP_COUNT - 1)] =   \
            BLE_MESH_ADDR_UNASSIGNED },                             \
    .user_data = (_user_data),                                      \
    .cb = (_cb),                                                    \
}

/** @def BLE_MESH_TRANSMIT
 *
 *  @brief 编码传输计数和间隔步长。
 *
 *  @param count   重传次数（排除第一次传输）。
 *  @param int_ms  间隔步数（毫秒）。必须大于0和10的倍数。
 *
 *  @return 可以用于例如配置模型数据的默认值的网格传输值。
 */
#define BLE_MESH_TRANSMIT(count, int_ms) ((count) | ((((int_ms) / 10) - 1) << 3))

/** @def BLE_MESH_TRANSMIT_COUNT
 *
 *  @brief 根据传输值解码传输计数。
 *
 *  @param transmit 编码传输计数和间隔值。
 *
 *  @return 传输计数（实际传输为N+1）。
 */
#define BLE_MESH_TRANSMIT_COUNT(transmit) (((transmit) & (uint8_t)BIT_MASK(3)))

/** @def BLE_MESH_TRANSMIT_INT
 *
 *  @brief 根据传输值解码传输间隔。
 *
 *  @param transmit 编码传输计数和间隔值。
 *
 *  @return 传输间隔（毫秒）。
 */
#define BLE_MESH_TRANSMIT_INT(transmit) ((((transmit) >> 3) + 1) * 10)

/** @def BLE_MESH_PUB_TRANSMIT
 *
 *  @brief 编码发布重新传输计数和间隔步骤。
 *
 *  @param count   重传次数（排除第一次传输）。
 *  @param int_ms  间隔步数（毫秒）。必须大于0和50的倍数。
 *
 *  @return 可以用于例如配置模型数据的默认值的网格传输值。
 */
#define BLE_MESH_PUB_TRANSMIT(count, int_ms) BLE_MESH_TRANSMIT((count), (int_ms) / 5)

/** @def BLE_MESH_PUB_TRANSMIT_COUNT
 *
 *  @brief 从给定值解码发布重新传输计数。
 *
 *  @param transmit 编码的发布重新传输计数和间隔值。
 *
 *  @return 重新传输计数（实际传输为N+1）。
 */
#define BLE_MESH_PUB_TRANSMIT_COUNT(transmit) BLE_MESH_TRANSMIT_COUNT(transmit)

/** @def BLE_MESH_PUB_TRANSMIT_INT
 *
 *  @brief 从给定值解码发布重新传输间隔。
 *
 *  @param transmit 编码的发布重新传输计数和间隔值。
 *
 *  @return 传输间隔（毫秒）。
 */
#define BLE_MESH_PUB_TRANSMIT_INT(transmit) ((((transmit) >> 3) + 1) * 50)

/**模型发布上下文。*/
struct bt_mesh_model_pub {
    /**上下文所属的模型。由堆栈初始化。*/
    struct bt_mesh_model *mod;

    uint16_t addr;          /**<发布地址。*/
    uint16_t key:12,        /**<发布AppKey索引。*/
             cred:1,        /**<友谊证书标志。*/
             send_rel:1;    /**<强制可靠发送（段ack）*/

    uint8_t  ttl;           /**<发布生存时间。*/
    uint8_t  retransmit;    /**<重新传输计数和间隔步骤。*/
    uint8_t  period;        /**<发布期。*/
    uint8_t  period_div:4,  /**<本期除数。*/
             fast_period:1, /**<使用FastPeriodDivisior*/
             count:3;       /**<剩余重新传输。*/

    uint32_t period_start;  /**<本期开始。*/

    /** @brief 发布缓冲区，包含发布消息。
     *
     *  当使用BLE_MESH_MODEL_PUB_DEFINE宏定义发布上下文时，将正确创建此上下文。
     *
     *  BLE_MESH_MODE_PUB_DEFINE（名称、更新、大小）；
     */
    struct net_buf_simple *msg;

    /** @brief 用于更新发布缓冲区的回调。
     *
     *  设置为NULL时，假设模型不支持定期发布。当设置为非NULL时，将定期调用回调，并预期更新
     *  @ref bt_mesh_model_pub。带有有效发布消息的消息。
     *
     *  如果回调返回非零，则将跳过发布，并将在下一个定期发布间隔继续。
     *
     *  @param mod 发布上下文所属的模型。
     *
     *  @return 成功时为零，否则为（负）错误代码。
     */
    int (*update)(struct bt_mesh_model *mod);

    /**发布时段计时器。仅用于堆栈内部使用。*/
    struct k_delayed_work timer;

    /* Espressif的改变，发布消息的设备的角色*/
    uint8_t dev_role;
};

/** @def BLE_MESH_MODEL_PUB_DEFINE
 *
 *  定义模型发布上下文。
 *
 *  @param _name 给上下文的变量名。
 *  @param _update 可选消息更新回调（可能为NULL）。
 *  @param _msg_len 发布消息的长度。
 */
#define BLE_MESH_MODEL_PUB_DEFINE(_name, _update, _msg_len) \
    NET_BUF_SIMPLE_DEFINE_STATIC(bt_mesh_pub_msg_##_name, _msg_len); \
    static struct bt_mesh_model_pub _name = { \
        .update = _update, \
        .msg = &bt_mesh_pub_msg_##_name, \
    }

/**模型回调函数。*/
struct bt_mesh_model_cb {
    /** @brief 模型初始化回调。
     *
     *  在网格初始化期间对每个模型实例调用。
     *
     *  如果任何模型init回调返回错误，网格子系统初始化将被中止，错误将返回给@ref bt_mesh_init的调用者。
     *
     *  @param model 要初始化的模型。
     *
     *  @return 成功时为0，否则为错误。
     */
    int (*const init)(struct bt_mesh_model *model);

#if CONFIG_BLE_MESH_DEINIT
    /** @brief 模型卸载回调。
     *
     *  在网格去初始化期间对每个模型实例调用。将删除所有模型数据，模型应清除其状态。
     *
     *  如果任何模型去初始化回调返回错误，网格子系统去初始化将被中止，错误将返回给@ref bt_mesh_deinit的调用者。
     *
     *  @param model 要取消初始化的模型。
     */
    int (*const deinit)(struct bt_mesh_model *model);
#endif /* CONFIG_BLE_MESH_DEINIT */
};

/**描述网格模型实例的抽象*/
struct bt_mesh_model {
    union {
        const uint16_t id;
        struct {
            uint16_t company;
            uint16_t id;
        } vnd;
    };

    /* 内部信息，主要用于持久性存储*/
    uint8_t  elem_idx;  /* 属于第N个元素*/
    uint8_t  model_idx; /* 是元素中的第N个模型*/
    uint16_t flags;     /* 有关已更改内容的信息*/

    /* 此模型所属的元素*/
    struct bt_mesh_elem *elem;

    /* 模型出版物*/
    struct bt_mesh_model_pub *const pub;

    /* AppKey列表*/
    uint16_t keys[CONFIG_BLE_MESH_MODEL_KEY_COUNT];

    /* 订阅列表（组或虚拟地址）*/
    uint16_t groups[CONFIG_BLE_MESH_MODEL_GROUP_COUNT];

    /**操作码处理程序列表*/
    const struct bt_mesh_model_op *const op;

    /**模型回调结构。*/
    const struct bt_mesh_model_cb *const cb;

    /* 特定于型号的用户数据*/
    void *user_data;
};

struct bt_mesh_send_cb {
    void (*start)(uint16_t duration, int err, void *cb_data);
    void (*end)(int err, void *cb_data);
};

void bt_mesh_model_msg_init(struct net_buf_simple *msg, uint32_t opcode);

/**使用配置的默认TTL请求特殊TTL值*/
#define BLE_MESH_TTL_DEFAULT    0xff

/**允许的最大TTL值*/
#define BLE_MESH_TTL_MAX        0x7f

/**
 * @brief 发送接入层消息。
 *
 * @param model     消息所属的网格（客户端）模型。
 * @param ctx       消息上下文，包括密钥、TTL等。
 * @param msg       接入层有效载荷（要发送的实际消息）。
 * @param cb        可选的“消息已发送”回调。
 * @param cb_data   要传递给回调的用户数据。
 *
 * @return 成功时为0，失败时为（负）错误代码。
 */
int bt_mesh_model_send(struct bt_mesh_model *model,
                       struct bt_mesh_msg_ctx *ctx,
                       struct net_buf_simple *msg,
                       const struct bt_mesh_send_cb *cb,
                       void *cb_data);

/**
 * @brief 发送模型发布消息。
 *
 * 在调用此函数之前，用户需要确保模型
 * publication message (@ref bt_mesh_model_pub。msg）包含要发送的有效消息。请注意，此API仅用于非周期发布。对于定期发布，应用程序只需要
 * to make sure that @ref bt_mesh_model_pub。消息包含有效消息
 * whenever the @ref bt_mesh_model_pub。调用update回调。
 *
 * @param model  发布消息的网格（客户端）模型。
 *
 * @return 成功时为0，失败时为（负）错误代码。
 */
int bt_mesh_model_publish(struct bt_mesh_model *model);

/**
 * @brief 获取模型所属的元素。
 *
 * @param mod  网格模型。
 *
 * @return 指向给定模型所属元素的指针。
 */
struct bt_mesh_elem *bt_mesh_model_elem(struct bt_mesh_model *mod);

/** @brief 查找SIG模型。
 *
 *  @param elem 要在其中搜索模型的元素。
 *  @param id   模型的模型ID。
 *
 *  @return 指向与给定参数匹配的Mesh模型的指针，如果给定元素中不存在具有给定ID的SIG模型，则为NULL。
 */
struct bt_mesh_model *bt_mesh_model_find(struct bt_mesh_elem *elem, uint16_t id);

/** @brief 查找供应商模型。
 *
 *  @param elem    要在其中搜索模型的元素。
 *  @param company 模型的公司ID。
 *  @param id      模型的模型ID。
 *
 *  @return 指向与给定参数匹配的Mesh模型的指针，如果给定元素中不存在具有给定ID的供应商模型，则为NULL。
 */
struct bt_mesh_model *bt_mesh_model_find_vnd(struct bt_mesh_elem *elem,
                                             uint16_t company, uint16_t id);

/** @brief 获取模型是否在设备的主要元素中。
 *
 *  @param mod 网格模型。
 *
 *  @return 如果模型位于主元素上，则为true，否则为false。
 */
static inline bool bt_mesh_model_in_primary(const struct bt_mesh_model *mod)
{
    return (mod->elem_idx == 0);
}

/**节点组成*/
struct bt_mesh_comp {
    uint16_t cid;
    uint16_t pid;
    uint16_t vid;

    size_t elem_count;
    struct bt_mesh_elem *elem;
};

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* __BLE_MESH_ACCESS_H */

