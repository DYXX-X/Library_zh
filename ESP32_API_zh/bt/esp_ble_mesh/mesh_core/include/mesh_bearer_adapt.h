/*
 * SPDX文件版权文本：2017 Nordic Semiconductor ASA SPDX File版权文本：2015-2017 Intel Corporation SPDX FileContributor:2018-2021 Espressif Systems（Shanghai）CO LTD
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _BLE_MESH_BEARER_ADAPT_H_
#define _BLE_MESH_BEARER_ADAPT_H_

#include <sys/types.h>
#include "mesh_config.h"
#include "mesh_types.h"
#include "mesh_util.h"
#include "mesh_uuid.h"
#include "mesh_buf.h"

#ifdef __cplusplus
extern "C" {
#endif

/* BLE网格最大连接计数*/
#ifdef CONFIG_BT_BLUEDROID_ENABLED
#define BLE_MESH_MAX_CONN   CONFIG_BT_ACL_CONNECTIONS
#endif

#ifdef CONFIG_BT_NIMBLE_ENABLED
#define BLE_MESH_MAX_CONN   CONFIG_BT_NIMBLE_MAX_CONNECTIONS
#endif

#define BLE_MESH_GAP_ADV_MAX_LEN    31

#define BLE_MESH_GATT_DEF_MTU_SIZE  23

/* BD ADDR类型*/
#define BLE_MESH_ADDR_PUBLIC         0x00
#define BLE_MESH_ADDR_RANDOM         0x01
#define BLE_MESH_ADDR_PUBLIC_ID      0x02
#define BLE_MESH_ADDR_RANDOM_ID      0x03

/* BD ADDR长度*/
#define BLE_MESH_ADDR_LEN                   0x06

/* 广告类型*/
#define BLE_MESH_ADV_IND                    0x00
#define BLE_MESH_ADV_DIRECT_IND             0x01
#define BLE_MESH_ADV_SCAN_IND               0x02
#define BLE_MESH_ADV_NONCONN_IND            0x03
#define BLE_MESH_ADV_DIRECT_IND_LOW_DUTY    0x04

/* 广告频道图*/
#define BLE_MESH_ADV_CHNL_37                BIT(0)
#define BLE_MESH_ADV_CHNL_38                BIT(1)
#define BLE_MESH_ADV_CHNL_39                BIT(2)

/* 广告筛选策略*/
#define BLE_MESH_AP_SCAN_CONN_ALL           0x00
#define BLE_MESH_AP_SCAN_WL_CONN_ALL        0x01
#define BLE_MESH_AP_SCAN_ALL_CONN_WL        0x02
#define BLE_MESH_AP_SCAN_CONN_WL            0x03

/* 扫描类型*/
#define BLE_MESH_SCAN_PASSIVE               0x00
#define BLE_MESH_SCAN_ACTIVE                0x01

/* 扫描操作*/
#define BLE_MESH_SCAN_DISABLE               0x00
#define BLE_MESH_SCAN_ENABLE                0x01

/* 扫描重复操作*/
#define BLE_MESH_SCAN_FILTER_DUP_DISABLE    0x00
#define BLE_MESH_SCAN_FILTER_DUP_ENABLE     0x01

/* 扫描筛选器策略*/
#define BLE_MESH_SP_ADV_ALL                 0x00
#define BLE_MESH_SP_ADV_WL                  0x01
#define BLE_MESH_SP_ADV_ALL_RPA_DIR_ADV     0x02
#define BLE_MESH_SP_ADV_WL_RPA_DIR_ADV      0x03

/* 错误响应PDU的错误代码*/
#define BLE_MESH_ATT_ERR_INVALID_HANDLE             0x01
#define BLE_MESH_ATT_ERR_READ_NOT_PERMITTED         0x02
#define BLE_MESH_ATT_ERR_WRITE_NOT_PERMITTED        0x03
#define BLE_MESH_ATT_ERR_INVALID_PDU                0x04
#define BLE_MESH_ATT_ERR_AUTHENTICATION             0x05
#define BLE_MESH_ATT_ERR_NOT_SUPPORTED              0x06
#define BLE_MESH_ATT_ERR_INVALID_OFFSET             0x07
#define BLE_MESH_ATT_ERR_AUTHORIZATION              0x08
#define BLE_MESH_ATT_ERR_PREPARE_QUEUE_FULL         0x09
#define BLE_MESH_ATT_ERR_ATTRIBUTE_NOT_FOUND        0x0a
#define BLE_MESH_ATT_ERR_ATTRIBUTE_NOT_LONG         0x0b
#define BLE_MESH_ATT_ERR_ENCRYPTION_KEY_SIZE        0x0c
#define BLE_MESH_ATT_ERR_INVALID_ATTRIBUTE_LEN      0x0d
#define BLE_MESH_ATT_ERR_UNLIKELY                   0x0e
#define BLE_MESH_ATT_ERR_INSUFFICIENT_ENCRYPTION    0x0f
#define BLE_MESH_ATT_ERR_UNSUPPORTED_GROUP_TYPE     0x10
#define BLE_MESH_ATT_ERR_INSUFFICIENT_RESOURCES     0x11

/* 常见配置文件错误代码（来自CSS）*/
#define BLE_MESH_ATT_ERR_WRITE_REQ_REJECTED         0xfc
#define BLE_MESH_ATT_ERR_CCC_IMPROPER_CONF          0xfd
#define BLE_MESH_ATT_ERR_PROCEDURE_IN_PROGRESS      0xfe
#define BLE_MESH_ATT_ERR_OUT_OF_RANGE               0xff

/* EIR/AD数据类型定义*/
#define BLE_MESH_DATA_FLAGS                 0x01 /* AD标志*/
#define BLE_MESH_DATA_UUID16_SOME           0x02 /* 16位UUID，更多可用*/
#define BLE_MESH_DATA_UUID16_ALL            0x03 /* 16位UUID，全部列出*/
#define BLE_MESH_DATA_UUID32_SOME           0x04 /* 32位UUID，更多可用*/
#define BLE_MESH_DATA_UUID32_ALL            0x05 /* 32位UUID，全部列出*/
#define BLE_MESH_DATA_UUID128_SOME          0x06 /* 128位UUID，更多可用*/
#define BLE_MESH_DATA_UUID128_ALL           0x07 /* 128位UUID，全部列出*/
#define BLE_MESH_DATA_NAME_SHORTENED        0x08 /* 简称*/
#define BLE_MESH_DATA_NAME_COMPLETE         0x09 /* 完整名称*/
#define BLE_MESH_DATA_TX_POWER              0x0a /* Tx电源*/
#define BLE_MESH_DATA_SOLICIT16             0x14 /* 请求UUID，16位*/
#define BLE_MESH_DATA_SOLICIT128            0x15 /* 请求UUID，128位*/
#define BLE_MESH_DATA_SVC_DATA16            0x16 /* 服务数据，16位UUID*/
#define BLE_MESH_DATA_GAP_APPEARANCE        0x19 /* GAP外观*/
#define BLE_MESH_DATA_SOLICIT32             0x1f /* 请求UUID，32位*/
#define BLE_MESH_DATA_SVC_DATA32            0x20 /* 服务数据，32位UUID*/
#define BLE_MESH_DATA_SVC_DATA128           0x21 /* 服务数据，128位UUID*/
#define BLE_MESH_DATA_URI                   0x24 /* URI */
#define BLE_MESH_DATA_MESH_PROV             0x29 /* 网格配置PDU*/
#define BLE_MESH_DATA_MESH_MESSAGE          0x2a /* 网状网络PDU*/
#define BLE_MESH_DATA_MESH_BEACON           0x2b /* 网状信标*/

#define BLE_MESH_DATA_MANUFACTURER_DATA     0xff /* 制造商特定数据*/

#define BLE_MESH_AD_LIMITED     0x01 /* 有限的可发现性*/
#define BLE_MESH_AD_GENERAL     0x02 /* 一般可发现*/
#define BLE_MESH_AD_NO_BREDR    0x04 /* 不支持BR/EDR*/

/* 客户端特征配置值*/

/** @def BLE_MESH_GATT_CCC_NOTIFY
 *  @brief 客户端特征配置通知。
 *
 *  如果设置，应通知特征值的变化。
 */
#define BLE_MESH_GATT_CCC_NOTIFY        0x0001

/** @def BLE_MESH_GATT_CCC_INDICATE
 *  @brief 客户端特征配置指示。
 *
 *  如果设置，应显示特征值的变化。
 */
#define BLE_MESH_GATT_CCC_INDICATE      0x0002

/**  @def BLE_MESH_GATT_ERR
  *  @brief 构造属性读和写回调的错误返回值。
  *
  *  @param _att_err ATT错误代码
  *
  *  @return 属性回调的相应错误代码。
  *
  */
#define BLE_MESH_GATT_ERR(_att_err)     (-(_att_err))

enum {
    BLE_MESH_GATT_ITER_STOP = 0,
    BLE_MESH_GATT_ITER_CONTINUE,
};

/* GATT属性权限位字段值*/
enum {
    /**不支持任何操作，例如仅用于通知*/
    BLE_MESH_GATT_PERM_NONE = 0,

    /**属性读取权限。*/
    BLE_MESH_GATT_PERM_READ = BIT(0),

    /**属性写入权限。*/
    BLE_MESH_GATT_PERM_WRITE = BIT(1),

    /** 具有加密的属性读取权限。
     *
     *  如果已设置，则需要对读取访问进行加密。
     */
    BLE_MESH_GATT_PERM_READ_ENCRYPT = BIT(2),

    /** 具有加密的属性写入权限。
     *
     *  如果已设置，则需要对写入访问进行加密。
     */
    BLE_MESH_GATT_PERM_WRITE_ENCRYPT = BIT(3),

    /** 具有身份验证的属性读取权限。
     *
     *  如果设置，则需要使用经过身份验证的链接密钥进行加密以进行读取访问。
     */
    BLE_MESH_GATT_PERM_READ_AUTHEN = BIT(4),

    /** 具有身份验证的属性写入权限。
     *
     *  如果已设置，则需要使用经过身份验证的链接密钥进行加密以进行写入访问。
     */
    BLE_MESH_GATT_PERM_WRITE_AUTHEN = BIT(5),

    /** 属性准备写入权限。
     *
     *  如果设置，则允许使用传递给写回调的BT_GATT_WRITE_FLAG_prepare来准备写操作。
     */
    BLE_MESH_GATT_PERM_PREPARE_WRITE = BIT(6),
};

/**广告选项*/
enum {
    /**未指定选项时的便利值。*/
    BLE_MESH_ADV_OPT_NONE = 0,

    /** 作为可连接的广告。通过提供SCAN_RSP数据和/或启用本地隐私支持来确定广告类型。
     */
    BLE_MESH_ADV_OPT_CONNECTABLE = BIT(0),

    /** 连接后不要尝试恢复可连接的广告。此选项仅在与BLE_MESH_ADV_OPT_CONNECTABLE一起使用时才有意义。如果设置，则当调用bt_le_adv_stop（）或发生传入（从属）连接时，将停止广告。如果未设置此选项，则即使发生连接，堆栈也会注意保持启用广告。
     */
    BLE_MESH_ADV_OPT_ONE_TIME = BIT(1),
};

/* 定义的间隙计时器*/
#define BLE_MESH_GAP_SCAN_FAST_INTERVAL     0x0060  /* 60毫秒*/
#define BLE_MESH_GAP_SCAN_FAST_WINDOW       0x0030  /* 30毫秒*/
#define BLE_MESH_GAP_SCAN_SLOW_INTERVAL_1   0x0800  /* 1.28秒*/
#define BLE_MESH_GAP_SCAN_SLOW_WINDOW_1     0x0012  /* 11.25毫秒*/
#define BLE_MESH_GAP_SCAN_SLOW_INTERVAL_2   0x1000  /* 2.56秒*/
#define BLE_MESH_GAP_SCAN_SLOW_WINDOW_2     0x0012  /* 11.25毫秒*/
#define BLE_MESH_GAP_ADV_FAST_INT_MIN_0     0x0020  /* 20毫秒*/
#define BLE_MESH_GAP_ADV_FAST_INT_MAX_0     0x0020  /* 20毫秒*/
#define BLE_MESH_GAP_ADV_FAST_INT_MIN_1     0x0030  /* 30毫秒*/
#define BLE_MESH_GAP_ADV_FAST_INT_MAX_1     0x0060  /* 60毫秒*/
#define BLE_MESH_GAP_ADV_FAST_INT_MIN_2     0x00a0  /* 100毫秒*/
#define BLE_MESH_GAP_ADV_FAST_INT_MAX_2     0x00f0  /* 150毫秒*/
#define BLE_MESH_GAP_ADV_SLOW_INT_MIN       0x0320  /* 500毫秒*/
#define BLE_MESH_GAP_ADV_SLOW_INT_MAX       0x0320  /* 500毫秒*/
#define BLE_MESH_GAP_INIT_CONN_INT_MIN      0x0018  /* 30毫秒*/
#define BLE_MESH_GAP_INIT_CONN_INT_MAX      0x0028  /* 50毫秒*/

/* 特征属性位字段值*/

/** @def BLE_MESH_GATT_CHRC_BROADCAST
 *  @brief 特色广播属性。
 *
 *  如果设置，则允许使用服务器特征配置描述符广播特征值。
 */
#define BLE_MESH_GATT_CHRC_BROADCAST              0x01

/** @def BLE_MESH_GATT_CHRC_READ
 *  @brief 特征读取属性。
 *
 *  如果设置，则允许读取特征值。
 */
#define BLE_MESH_GATT_CHRC_READ                   0x02

/** @def BLE_MESH_GATT_CHRC_WRITE_WITHOUT_RESP
 *  @brief 无响应属性的特征写入。
 *
 *  如果设置，则允许在无响应的情况下写入特征值。
 */
#define BLE_MESH_GATT_CHRC_WRITE_WITHOUT_RESP     0x04

/** @def BLE_MESH_GATT_CHRC_WRITE
 *  @brief 具有响应属性的特征写入。
 *
 *  如果设置，则允许写入具有响应的特征值。
 */
#define BLE_MESH_GATT_CHRC_WRITE                  0x08

/** @def BLE_MESH_GATT_CHRC_NOTIFY
 *  @brief 特征通知属性。
 *
 *  如果设置，则允许在没有确认的情况下通知特征值。
 */
#define BLE_MESH_GATT_CHRC_NOTIFY                 0x10

/** @def BLE_MESH_GATT_CHRC_INDICATE
 *  @brief 特征表示属性。
 *
 * 如果设置，则允许显示具有确认的特征值。
 */
#define BLE_MESH_GATT_CHRC_INDICATE               0x20

/** @def BLE_MESH_GATT_CHRC_AUTH
 *  @brief Characteristic Authenticated Signed Writes属性。
 *
 *  如果设置，则允许对特征值进行签名写入。
 */
#define BLE_MESH_GATT_CHRC_AUTH                   0x40

/** @def BLE_MESH_GATT_CHRC_EXT_PROP
 *  @brief Characteristic Extended Properties属性。
 *
 * 如果设置，则在特征扩展属性描述符中定义其他特征属性。
 */
#define BLE_MESH_GATT_CHRC_EXT_PROP               0x80

/** @brief 特征属性值。*/
struct bt_mesh_gatt_char {
    /**特征UUID。*/
    const struct bt_mesh_uuid *uuid;
    /**特性特性。*/
    uint8_t                    properties;
};

/** @brief GATT服务结构*/
struct bt_mesh_gatt_service {
    /**服务属性*/
    struct bt_mesh_gatt_attr *attrs;
    /**服务属性计数*/
    uint16_t                  attr_count;
    sys_snode_t               node;
};

typedef struct {
    uint8_t type;
    uint8_t val[6];
} bt_mesh_addr_t;

/** 可编码为广告数据的不同数据类型的描述。用于形成传递给bt_le_adv_start（）函数的数组。
  */
struct bt_mesh_adv_data {
    uint8_t type;
    uint8_t data_len;
    const uint8_t *data;
};

/** @brief 帮助程序声明bt_data数组的元素
 *
 *  此宏主要用于创建结构bt_mesh_adv_data元素数组，然后将其传递给bt_le_adv_start（）。
 *
 *  @param _type 广告数据字段的类型
 *  @param _data 指向数据字段有效负载的指针
 *  @param _data_len 数据指针后面的字节数（_D）
 */
#define BLE_MESH_ADV_DATA(_type, _data, _data_len)  \
    {                                               \
        .type = (_type),                            \
        .data_len = (_data_len),                    \
        .data = (const uint8_t *)(_data),           \
    }

/** @brief 帮助程序声明bt_data数组的元素
 *
 *  此宏主要用于创建结构bt_mesh_adv_data元素数组，然后将其传递给bt_le_adv_start（）。
 *
 *  @param _type 广告数据字段的类型
 *  @param _bytes 可变数量的单字节参数
 */
#define BLE_MESH_ADV_DATA_BYTES(_type, _bytes...)       \
    BLE_MESH_ADV_DATA(_type, ((uint8_t []) { _bytes }), \
        sizeof((uint8_t []) { _bytes }))

/* BLE网格广告参数*/
struct bt_mesh_adv_param {
    /**广告选项的位字段*/
    uint8_t  options;

    /**最小广告间隔（N*0.625）*/
    uint16_t interval_min;

    /**最大广告间隔（N*0.625）*/
    uint16_t interval_max;
};

#if CONFIG_BLE_MESH_SUPPORT_BLE_ADV
enum bt_mesh_ble_adv_priority {
    BLE_MESH_BLE_ADV_PRIO_LOW,
    BLE_MESH_BLE_ADV_PRIO_HIGH,
};

struct bt_mesh_ble_adv_param {
    uint16_t interval;         /* 广告时间间隔*/
    uint8_t  adv_type;         /* 广告类型*/
    uint8_t  own_addr_type;    /* 自己的地址类型*/
    uint8_t  peer_addr_type;   /* 对等地址类型*/
    uint8_t  peer_addr[6];     /* 对等地址*/
    uint16_t duration;         /* 持续时间为毫秒*/
    uint16_t period;           /* 周期（毫秒）*/
    uint16_t count;            /* 广告持续时间数*/
    uint8_t  priority:2;       /* BLE广告包的优先级*/
};

struct bt_mesh_ble_adv_data {
    uint8_t adv_data_len;      /* 广告数据长度*/
    uint8_t adv_data[31];      /* 广告数据*/
    uint8_t scan_rsp_data_len; /* 扫描响应数据长度*/
    uint8_t scan_rsp_data[31]; /* 扫描响应数据*/
};
#endif /* CONFIG_BLE_MESH_SUPPORT_BLE_ADV */

/* BLE网格扫描参数*/
struct bt_mesh_scan_param {
    /**扫描类型（BLE_MESH_Scan_ACTIVE或BLE_MES_Scan_PASSIVE）*/
    uint8_t  type;

    /** 重复过滤（BLE_MESH_SCAN_FILTER_DUP_ENABLE或BLE_MESS_SCAN_FITTER_DUP_DISABLE）
     */
    uint8_t  filter_dup;

    /**扫描间隔（N*0.625 ms）*/
    uint16_t interval;

    /**扫描窗口（N*0.625 ms）*/
    uint16_t window;

    /**BLE扫描筛选器策略*/
    uint8_t  scan_fil_policy;
};

struct bt_mesh_conn {
    uint16_t handle;
    bt_mesh_atomic_t ref;
};

/** @typedef bt_mesh_scan_cb_t
 *  @brief 用于报告LE扫描结果的回调类型。
 *
 *  这种类型的函数被赋予bt_le_scan_start（）函数，并将被任何发现的le设备调用。
 *
 *  @param addr 广告客户LE地址和类型。
 *  @param rssi 广告商信号的强度。
 *  @param adv_type 广告客户的广告响应类型。
 *  @param data 包含广告客户数据的缓冲区。
 */
typedef void bt_mesh_scan_cb_t(const bt_mesh_addr_t *addr, int8_t rssi,
                               uint8_t adv_type, struct net_buf_simple *buf);

/*  @typedef bt_mesh_dh_key_cb_t
 *  @brief DH Key计算的回调类型。
 *
 *  用于通知计算的DH密钥。
 *
 *  @param key 公钥。
 *  @param idx 设置链接索引，仅由Provisioner使用。
 *
 *  @return DH密钥，失败时为NULL。
 */
typedef void (*bt_mesh_dh_key_cb_t)(const uint8_t key[32], const uint8_t idx);

/** @typedef bt_mesh_gatt_attr_func_t
 *  @brief 属性迭代器回调。
 *
 *  @param attr 找到属性。
 *  @param user_data 给出数据。
 *
 *  @return BLE_MESH_GATT_ITER_CONTINUE如果应继续到下一个属性或BLE_MESG_GATT_ITER_STOP停止。
 */
typedef uint8_t (*bt_mesh_gatt_attr_func_t)(const struct bt_mesh_gatt_attr *attr,
                                            void *user_data);

/** @brief 连接回调结构。
 *
 *  This structure is used for tracking the state of a connection. It is registered with the help of the bt_mesh_gatts_conn_cb_register() API. It's permissible to register multiple instances of this @ref btconcb类型，以防应用程序的不同模块对跟踪连接状态感兴趣。如果回调对实例不感兴趣，则可以将其设置为NULL，因此不会用于该实例。
 */
struct bt_mesh_conn_cb {
    /** @brief 已建立新连接。
     *
     *  此回调通知应用程序新连接。如果err参数为非零，则表示连接建立失败。
     *
     *  @param conn 新建连接对象。
     *  @param err HCI错误。成功为零，否则为零。
     */
    void (*connected)(struct bt_mesh_conn *conn, uint8_t err);

    /** @brief 连接已断开。
     *
     *  此回调通知应用程序连接已断开。
     *
     *  @param conn 连接对象。
     *  @param reason 断开连接的HCI原因。
     */
    void (*disconnected)(struct bt_mesh_conn *conn, uint8_t reason);
};

struct bt_mesh_prov_conn_cb {
    void (*connected)(bt_mesh_addr_t *addr, struct bt_mesh_conn *conn, int id);

    void (*disconnected)(bt_mesh_addr_t *addr, struct bt_mesh_conn *conn, uint8_t reason);

    ssize_t (*prov_write_descr)(bt_mesh_addr_t *addr, struct bt_mesh_conn *conn);

    ssize_t (*prov_notify)(struct bt_mesh_conn *conn, uint8_t *data, uint16_t len);

    ssize_t (*proxy_write_descr)(bt_mesh_addr_t *addr, struct bt_mesh_conn *conn);

    ssize_t (*proxy_notify)(struct bt_mesh_conn *conn, uint8_t *data, uint16_t len);
};

/** @brief GATT属性结构。*/
struct bt_mesh_gatt_attr {
    /**属性UUID*/
    const struct bt_mesh_uuid *uuid;

    /** 属性读取回调
     *
     *  @param conn   请求读取的连接
     *  @param attr   正在读取的属性
     *  @param buf    用于放置读取结果的缓冲区
     *  @param len    要读取的数据长度
     *  @param offset 开始读取的偏移量
     *
     *  @return 读取的字节数，或在BLE_MESH_GATT_error（）错误的情况下，使用特定ATT错误代码。
     */
    ssize_t (*read)(struct bt_mesh_conn *conn,
                    const struct bt_mesh_gatt_attr *attr,
                    void *buf, uint16_t len,
                    uint16_t offset);

    /** 属性写入回调
     *
     *  @param conn   请求写入的连接
     *  @param attr   正在写入的属性
     *  @param buf    具有要写入的数据的缓冲区
     *  @param len    缓冲区中的字节数
     *  @param offset 开始写入的偏移量
     *  @param flags  标志（BT_GATT_WRITE_*）
     *
     *  @return 写入的字节数，或在出现错误BLE_MESH_GATT_error（）的情况下，使用特定ATT错误代码。
     */
    ssize_t (*write)(struct bt_mesh_conn *conn,
                     const struct bt_mesh_gatt_attr *attr,
                     const void *buf, uint16_t len,
                     uint16_t offset, uint8_t flags);

    /**属性用户数据*/
    void *user_data;
    /**属性句柄*/
    uint16_t handle;
    /**属性权限*/
    uint8_t  perm;
};

/** @def BLE_MESH_GATT_PRIMARY_SERVICE
 *  @brief 主要服务声明宏。
 *
 *  用于声明主服务属性的帮助程序宏。
 *
 *  @param _service 服务属性值。
 */
#define BLE_MESH_GATT_PRIMARY_SERVICE(_service)     \
{                                                   \
    .uuid = BLE_MESH_UUID_GATT_PRIMARY,             \
    .perm = BLE_MESH_GATT_PERM_READ,                \
    .read = bt_mesh_gatts_attr_read_service,        \
    .user_data = _service,                          \
}

/** @def BLE_MESH_GATT_SECONDARY_SERVICE
 *  @brief 辅助服务声明宏。
 *
 *  用于声明辅助服务属性的帮助程序宏。
 *
 *  @param _service 服务属性值。
 */
#define BLE_MESH_GATT_SECONDARY_SERVICE(_service)   \
{                                                   \
    .uuid = BLE_MESH_UUID_GATT_SECONDARY,           \
    .perm = BLE_MESH_GATT_PERM_READ,                \
    .read = bt_mesh_gatts_attr_read_service,        \
    .user_data = _service,                          \
}

/** @def BLE_MESH_GATT_INCLUDE_SERVICE
 *  @brief 包括服务声明宏。
 *
 *  用于声明数据库内部包含服务属性的帮助程序宏。
 *
 *  @param _service_incl 要包含的服务的第一个服务属性
 */
#define BLE_MESH_GATT_INCLUDE_SERVICE(_service_incl)    \
{                                                       \
    .uuid = BLE_MESH_UUID_GATT_INCLUDE,                 \
    .perm = BLE_MESH_GATT_PERM_READ,                    \
    .read = bt_mesh_gatts_attr_read_included,           \
    .user_data = _service_incl,                         \
}

/** @def BLE_MESH_GATT_CHARACTERISTIC
 *  @brief 特征声明宏。
 *
 *  用于声明特征属性的Helper宏。
 *
 *  @param _uuid 特征属性uuid。
 *  @param _props 特征属性属性。
 */
#define BLE_MESH_GATT_CHARACTERISTIC(_uuid, _props)             \
{                                                               \
    .uuid = BLE_MESH_UUID_GATT_CHRC,                            \
    .perm = BLE_MESH_GATT_PERM_READ,                            \
    .read = bt_mesh_gatts_attr_read_chrc,                       \
    .user_data = (&(struct bt_mesh_gatt_char) { .uuid = _uuid,  \
                           .properties = _props, }),            \
}

/** @def BLE_MESH_GATT_DESCRIPTOR
 *  @brief 描述符声明宏。
 *
 *  用于声明描述符属性的Helper宏。
 *
 *  @param _uuid 描述符属性uuid。
 *  @param _perm 描述符属性访问权限。
 *  @param _read 描述符属性读取回调。
 *  @param _write 描述符属性写入回调。
 *  @param _value 描述符属性值。
 */
#define BLE_MESH_GATT_DESCRIPTOR(_uuid, _perm, _read, _write, _value)   \
{                           \
    .uuid = _uuid,          \
    .perm = _perm,          \
    .read = _read,          \
    .write = _write,        \
    .user_data = _value,    \
}

/** @def BLE_MESH_GATT_SERVICE
 *  @brief 服务结构声明宏。
 *
 *  用于声明服务结构的帮助程序宏。
 *
 *  @param _attrs 服务属性。
 */
#define BLE_MESH_GATT_SERVICE(_attrs)   \
{                                       \
    .attrs = _attrs,                    \
    .attr_count = ARRAY_SIZE(_attrs),   \
}

int bt_mesh_host_init(void);

int bt_le_adv_start(const struct bt_mesh_adv_param *param,
                    const struct bt_mesh_adv_data *ad, size_t ad_len,
                    const struct bt_mesh_adv_data *sd, size_t sd_len);

#if CONFIG_BLE_MESH_SUPPORT_BLE_ADV
int bt_mesh_ble_adv_start(const struct bt_mesh_ble_adv_param *param,
                          const struct bt_mesh_ble_adv_data *data);
#endif

int bt_le_adv_stop(void);

int bt_le_scan_start(const struct bt_mesh_scan_param *param, bt_mesh_scan_cb_t cb);

int bt_le_scan_stop(void);

typedef enum {
    BLE_MESH_WHITELIST_REMOVE,
    BLE_MESH_WHITELIST_ADD,
} bt_mesh_wl_operation;

struct bt_mesh_white_list {
    bool add_remove;
    uint8_t remote_bda[BLE_MESH_ADDR_LEN];
    uint8_t addr_type;
    /* 对于Bluedroid主机，此回调用于通知更新白名单的结果。
     */
    void (*update_wl_comp_cb)(uint8_t status, bt_mesh_wl_operation wl_operation);
};

int bt_le_update_white_list(struct bt_mesh_white_list *wl);

void bt_mesh_gatts_conn_cb_register(struct bt_mesh_conn_cb *cb);
void bt_mesh_gatts_conn_cb_deregister(void);

int bt_mesh_gatts_disconnect(struct bt_mesh_conn *conn, uint8_t reason);

int bt_mesh_gatts_service_register(struct bt_mesh_gatt_service *svc);
int bt_mesh_gatts_service_deregister(struct bt_mesh_gatt_service *svc);

int bt_mesh_gatts_service_unregister(struct bt_mesh_gatt_service *svc);

ssize_t bt_mesh_gatts_attr_read_included(struct bt_mesh_conn *conn,
                                         const struct bt_mesh_gatt_attr *attr,
                                         void *buf, uint16_t len, uint16_t offset);

ssize_t bt_mesh_gatts_attr_read(struct bt_mesh_conn *conn,
                                const struct bt_mesh_gatt_attr *attr,
                                void *buf, uint16_t buf_len, uint16_t offset,
                                const void *value, uint16_t value_len);

ssize_t bt_mesh_gatts_attr_read_service(struct bt_mesh_conn *conn,
                                        const struct bt_mesh_gatt_attr *attr,
                                        void *buf, uint16_t len, uint16_t offset);

ssize_t bt_mesh_gatts_attr_read_chrc(struct bt_mesh_conn *conn,
                                     const struct bt_mesh_gatt_attr *attr,
                                     void *buf, uint16_t len, uint16_t offset);

int bt_mesh_gatts_notify(struct bt_mesh_conn *conn,
                         const struct bt_mesh_gatt_attr *attr,
                         const void *data, uint16_t len);

uint16_t bt_mesh_gatt_get_mtu(struct bt_mesh_conn *conn);

/**Espressif添加的API*/
int bt_mesh_gatts_service_stop(struct bt_mesh_gatt_service *svc);
int bt_mesh_gatts_service_start(struct bt_mesh_gatt_service *svc);

int bt_mesh_gatts_set_local_device_name(const char *name);

void bt_mesh_gattc_conn_cb_register(struct bt_mesh_prov_conn_cb *cb);
void bt_mesh_gattc_conn_cb_deregister(void);

uint8_t bt_mesh_gattc_get_free_conn_count(void);

uint16_t bt_mesh_gattc_get_service_uuid(struct bt_mesh_conn *conn);

int bt_mesh_gattc_conn_create(const bt_mesh_addr_t *addr, uint16_t service_uuid);

void bt_gattc_conn_close(struct bt_mesh_conn *conn);

void bt_mesh_gattc_exchange_mtu(uint8_t index);

uint16_t bt_mesh_gattc_get_mtu_info(struct bt_mesh_conn *conn);

int bt_mesh_gattc_write_no_rsp(struct bt_mesh_conn *conn,
                               const struct bt_mesh_gatt_attr *attr,
                               const void *data, uint16_t len);

void bt_mesh_gattc_disconnect(struct bt_mesh_conn *conn);

struct bt_mesh_conn *bt_mesh_conn_ref(struct bt_mesh_conn *conn);

void bt_mesh_conn_unref(struct bt_mesh_conn *conn);

void bt_mesh_gatt_init(void);
void bt_mesh_gatt_deinit(void);

void bt_mesh_adapt_init(void);

void bt_mesh_set_private_key(const uint8_t pri_key[32]);

const uint8_t *bt_mesh_pub_key_get(void);

bool bt_mesh_check_public_key(const uint8_t key[64]);

int bt_mesh_dh_key_gen(const uint8_t remote_pk[64], bt_mesh_dh_key_cb_t cb, const uint8_t idx);

int bt_mesh_encrypt_le(const uint8_t key[16], const uint8_t plaintext[16],
                       uint8_t enc_data[16]);

int bt_mesh_encrypt_be(const uint8_t key[16], const uint8_t plaintext[16],
                       uint8_t enc_data[16]);

enum {
    BLE_MESH_EXCEP_LIST_ADD = 0,
    BLE_MESH_EXCEP_LIST_REMOVE,
    BLE_MESH_EXCEP_LIST_CLEAN,
};

enum {
    BLE_MESH_EXCEP_INFO_ADV_ADDR = 0,
    BLE_MESH_EXCEP_INFO_MESH_LINK_ID,
    BLE_MESH_EXCEP_INFO_MESH_BEACON,
    BLE_MESH_EXCEP_INFO_MESH_PROV_ADV,
    BLE_MESH_EXCEP_INFO_MESH_PROXY_ADV,
};

enum {
    BLE_MESH_EXCEP_CLEAN_ADDR_LIST           = BIT(0),
    BLE_MESH_EXCEP_CLEAN_MESH_LINK_ID_LIST   = BIT(1),
    BLE_MESH_EXCEP_CLEAN_MESH_BEACON_LIST    = BIT(2),
    BLE_MESH_EXCEP_CLEAN_MESH_PROV_ADV_LIST  = BIT(3),
    BLE_MESH_EXCEP_CLEAN_MESH_PROXY_ADV_LIST = BIT(4),
    BLE_MESH_EXCEP_CLEAN_ALL_LIST            = 0xFFFF,
};

int bt_mesh_update_exceptional_list(uint8_t sub_code, uint8_t type, void *info);

#ifdef __cplusplus
}
#endif

#endif /* _BLE_MESH_BEARER_ADAPT_H_ */

