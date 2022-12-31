/** @file
 *  @brief 蓝牙网格配置文件API。
 */

/*
 * SPDX文件版权文本：2017 Intel Corporation SPDX FileContributor:2018-2021 Espressif Systems（Shanghai）CO LTD
 *
 * SPDX许可证标识符：Apache-2.0
 */
#ifndef _BLE_MESH_MAIN_H_
#define _BLE_MESH_MAIN_H_

#include "mesh_access.h"

/**
 * @brief 蓝牙网格配置
 * @defgroup bt_mesh_prov蓝牙网格配置
 * @ingroup bt_网格@{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    BLE_MESH_NO_OUTPUT       = 0,
    BLE_MESH_BLINK           = BIT(0),
    BLE_MESH_BEEP            = BIT(1),
    BLE_MESH_VIBRATE         = BIT(2),
    BLE_MESH_DISPLAY_NUMBER  = BIT(3),
    BLE_MESH_DISPLAY_STRING  = BIT(4),
} bt_mesh_output_action_t;

typedef enum {
    BLE_MESH_NO_INPUT      = 0,
    BLE_MESH_PUSH          = BIT(0),
    BLE_MESH_TWIST         = BIT(1),
    BLE_MESH_ENTER_NUMBER  = BIT(2),
    BLE_MESH_ENTER_STRING  = BIT(3),
} bt_mesh_input_action_t;

typedef enum {
    BLE_MESH_PROV_ADV   = BIT(0),
    BLE_MESH_PROV_GATT  = BIT(1),
} bt_mesh_prov_bearer_t;

typedef enum {
    BLE_MESH_PROV_OOB_OTHER     = BIT(0),
    BLE_MESH_PROV_OOB_URI       = BIT(1),
    BLE_MESH_PROV_OOB_2D_CODE   = BIT(2),
    BLE_MESH_PROV_OOB_BAR_CODE  = BIT(3),
    BLE_MESH_PROV_OOB_NFC       = BIT(4),
    BLE_MESH_PROV_OOB_NUMBER    = BIT(5),
    BLE_MESH_PROV_OOB_STRING    = BIT(6),
    /* 保留7-10*/
    BLE_MESH_PROV_OOB_ON_BOX    = BIT(11),
    BLE_MESH_PROV_OOB_IN_BOX    = BIT(12),
    BLE_MESH_PROV_OOB_ON_PAPER  = BIT(13),
    BLE_MESH_PROV_OOB_IN_MANUAL = BIT(14),
    BLE_MESH_PROV_OOB_ON_DEV    = BIT(15),
} bt_mesh_prov_oob_info_t;

#define BLE_MESH_PROV_STATIC_OOB_MAX_LEN    16
#define BLE_MESH_PROV_OUTPUT_OOB_MAX_LEN    8
#define BLE_MESH_PROV_INPUT_OOB_MAX_LEN     8

/**配置属性和功能。*/
struct bt_mesh_prov {
#if CONFIG_BLE_MESH_NODE
    /**广告未设置时使用的UUID*/
    const uint8_t *uuid;

    /** 可选URI。这将与未设置的信标分开发布，但是未设置的灯塔将包含其哈希值，因此两者可以由设置者关联。
     */
    const char *uri;

    /**带外信息字段。*/
    bt_mesh_prov_oob_info_t oob_info;

    /**标志指示未配置的设备是否支持OOB公钥*/
    bool oob_pub_key;

    /** @brief 设置设备OOB公钥。
     *
     *  此回调通知应用程序设置OOB公钥和私钥对。
     */
    void (*oob_pub_key_cb)(void);

    /**静态OOB值*/
    const uint8_t *static_val;
    /**静态OOB值长度*/
    uint8_t        static_val_len;

    /**支持的输出OOB的最大大小*/
    uint8_t        output_size;
    /**支持的输出OOB操作*/
    uint16_t       output_actions;

    /* 支持的最大输入OOB大小*/
    uint8_t        input_size;
    /**支持的输入OOB操作*/
    uint16_t       input_actions;

    /** @brief 请求输出数字。
     *
     *  此回调通知应用程序使用给定的操作输出给定的数字。
     *
     *  @param act 用于输出数字的操作。
     *  @param num 要输出的数字。
     *
     *  @return 成功归零，否则为负错误代码
     */
    int         (*output_number)(bt_mesh_output_action_t act, uint32_t num);

    /** @brief 请求输出字符串。
     *
     *  此回调通知应用程序向用户显示给定的字符串。
     *
     *  @param str 要显示的字符串。
     *
     *  @return 成功归零，否则为负错误代码
     */
    int         (*output_string)(const char *str);

    /** @brief 请求输入。
     *
     *  此回调通知应用程序使用给定操作请求用户输入。请求的输入将是字符串或数字，因此，一旦从用户获取数据，应用程序就需要调用bt_mesh_input_string（）或bt_mesh_input_number（）函数。
     *
     *  @param act 输入数据的动作。
     *  @param num 输入数据的最大大小。
     *
     *  @return 成功归零，否则为负错误代码
     */
    int         (*input)(bt_mesh_input_action_t act, uint8_t size);

    /** @brief 设置链接已打开。
     *
     *  此回调通知应用程序已在给定的供应承载上打开供应链路。
     *
     *  @param bearer 提供承载。
     */
    void        (*link_open)(bt_mesh_prov_bearer_t bearer);

    /** @brief 设置链接已关闭。
     *
     *  此回调通知应用程序给定供应承载上的供应链路已关闭。
     *
     *  @param bearer 提供承载。
     */
    void        (*link_close)(bt_mesh_prov_bearer_t bearer);

    /** @brief 设置已完成。
     *
     *  此回调通知应用程序配置已成功完成，并且已为本地节点分配了指定的NetKeyIndex和主要元素地址。
     *
     *  @param net_idx  设置期间提供的NetKeyIndex。
     *  @param net_key  设置期间提供的NetKey。
     *  @param addr     主要元素地址。
     *  @param flags    密钥刷新和IV更新标志
     *  @param iv_index IV索引。
     */
    void        (*complete)(uint16_t net_idx, const uint8_t net_key[16], uint16_t addr, uint8_t flags, uint32_t iv_index);

    /** @brief 节点已重置。
     *
     *  此回调通知应用程序本地节点已重置，需要重新配置。节点不会自动通告为未配置，而是需要调用bt_mesh_prov_enable（）API以在一个或多个配置承载上启用未配置的通告。
     */
    void        (*reset)(void);
#endif /* CONFIG_BLE_MESH_NODE */

#if CONFIG_BLE_MESH_PROVISIONER
    /* Provisioner设备uuid*/
    const uint8_t *prov_uuid;

    /*
     * 提供程序的主要元素地址。无需对其进行初始化以实现快速资源调配。
     */
    const uint16_t prov_unicast_addr;

    /*
     * 开始分配单播地址。无需对其进行初始化以实现快速资源调配。
     */
    uint16_t prov_start_address;

    /* 设置邀请中包含的注意计时器*/
    uint8_t  prov_attention;

    /* 配置程序配置算法*/
    uint8_t  prov_algorithm;

    /* 提供程序公钥oob*/
    uint8_t  prov_pub_key_oob;

    /** @brief 请求输入。
     *
     *  此回调通知应用程序应该使用OOB读取设备的公钥
     *
     *  @param link_idx: 配置链接索引
     *
     *  @return 成功归零，否则为负错误代码
     */
    int  (*prov_pub_key_oob_cb)(uint8_t link_idx);

    /* Provisioner静态oob值*/
    uint8_t *prov_static_oob_val;

    /* Provisioner静态oob值长度*/
    uint8_t  prov_static_oob_len;

    /** @brief 配置器输入从设备输出读取的数字
     *
     *  此回调通知应用程序它应该输入设备提供的号码。
     *
     *  @param method:   OOB认证方法
     *  @param act:      设备的输出动作
     *  @param size:     设备的输出大小
     *  @param link_idx: 配置链接索引
     *
     *  @return 成功归零，否则为负错误代码
     */
    int  (*prov_input_num)(uint8_t method, bt_mesh_output_action_t act, uint8_t size, uint8_t link_idx);

    /** @brief 配置器向设备输出一个数字
     *
     *  此回调通知应用程序它应该向设备输出号码。
     *
     *  @param method:   OOB认证方法
     *  @param act:      设备的输入动作
     *  @param data:     设备的输入编号/字符串
     *  @param size:     设备的输入大小
     *  @param link_idx: 配置链接索引
     *
     *  @return 成功归零，否则为负错误代码
     */
    int  (*prov_output_num)(uint8_t method, bt_mesh_input_action_t act, void *data, uint8_t size, uint8_t link_idx);

    /*
     * 密钥刷新和IV更新标志。无需对其进行初始化以实现快速资源调配。
     */
    uint8_t  flags;

    /*
     * IV指数。无需对其进行初始化以实现快速资源调配。
     */
    uint32_t iv_index;

    /** @brief 设置器已打开设置链接。
     *
     *  此回调通知应用程序已在给定的供应承载上打开供应链路。
     *
     *  @param bearer 提供承载。
     */
    void (*prov_link_open)(bt_mesh_prov_bearer_t bearer);

    /** @brief 设置器已关闭设置链接。
     *
     *  此回调通知应用程序给定供应承载上的供应链路已关闭。
     *
     *  @param bearer 提供承载。
     *  @param reason 设置链接关闭原因（断开原因）
     */
    void (*prov_link_close)(bt_mesh_prov_bearer_t bearer, uint8_t reason);

    /** @brief 配置一个设备已完成。
     *
     *  此回调通知应用程序，配置器已成功配置设备，并且节点已分配指定的NetKeyIndex和主要元素地址。
     *
     *  @param node_idx     节点（配置的设备）队列中的节点索引。
     *  @param device_uuid  已设置设备uuid指针。
     *  @param unicast_addr 已设置设备分配的单播地址。
     *  @param element_num  配置的设备元件编号。
     *  @param netkey_idx   已配置设备分配的网络密钥索引。
     */
    void (*prov_complete)(uint16_t node_idx, const uint8_t device_uuid[16],
                          uint16_t unicast_addr, uint8_t element_num,
                          uint16_t netkey_idx);
#endif /* CONFIG_BLE_MESH_PROVISIONER */
};

enum ble_mesh_role {
    NODE = 0,
    PROVISIONER,
    FAST_PROV,
    ROLE_NVAL,
};

/* 以下API适用于BLE网格节点*/

/** @brief 提供配置输入OOB字符串。
 *
 *  这是在使用BLE_mesh_ENDER_STRING作为操作调用bt_mesh_prov输入回调后调用的。
 *
 *  @param str 一串
 *
 *  @return 成功时为零，否则为（负）错误代码。
 */
int bt_mesh_input_string(const char *str);

/** @brief 提供供应输入OOB编号。
 *
 *  这是在以BLE_mesh_ENDER_NUMBER作为操作调用bt_mesh_prov输入回调后调用的。
 *
 *  @param num 数字
 *
 *  @return 成功时为零，否则为（负）错误代码。
 */
int bt_mesh_input_number(uint32_t num);

/** @brief 启用特定的资源调配承载
 *
 *  启用一个或多个配置承载。
 *
 *  @param Bit-wise 或提供承载。
 *
 *  @return 成功时为零，否则为（负）错误代码。
 */
int bt_mesh_prov_enable(bt_mesh_prov_bearer_t bearers);

/** @brief 禁用特定配置承载
 *
 *  禁用一个或多个配置承载。
 *
 *  @param Bit-wise 或提供承载。
 *
 *  @return 成功时为零，否则为（负）错误代码。
 */
int bt_mesh_prov_disable(bt_mesh_prov_bearer_t bearers);

/* 以下API适用于BLE Mesh Provisioner*/

/** @brief 提供配置输入OOB字符串。
 *
 *  这是在使用BLE_mesh_ENDER_STRING作为操作调用bt_mesh_prov输入回调后调用的。
 *
 *  @param str 一串
 *
 *  @return 成功时为零，否则为（负）错误代码。
 */
int bt_mesh_prov_input_string(const char *str);

/** @brief 提供供应输入OOB编号。
 *
 *  这是在以BLE_mesh_ENDER_NUMBER作为操作调用bt_mesh_prov输入回调后调用的。
 *
 *  @param num 数字
 *
 *  @return 成功时为零，否则为（负）错误代码。
 */
int bt_mesh_prov_input_number(uint32_t num);

/** @brief 启用特定的资源调配承载
 *
 *  启用一个或多个配置承载。
 *
 *  @param bearers 配置承载的逐位OR。
 *
 *  @return 成功时为零，否则为（负）错误代码。
 */
int bt_mesh_provisioner_enable(bt_mesh_prov_bearer_t bearers);

/** @brief 禁用特定配置承载
 *
 *  禁用一个或多个配置承载。
 *
 *  @param bearers 配置承载的逐位OR。
 *
 *  @return 成功时为零，否则为（负）错误代码。
 */
int bt_mesh_provisioner_disable(bt_mesh_prov_bearer_t bearers);

/**
 * @}
 */

/**
 * @brief 蓝牙网格
 * @defgroup bt_mesh蓝牙网格
 * @ingroup 蓝牙@{
 */

/* 主要网络密钥索引*/
#define BLE_MESH_NET_PRIMARY                 0x000

#define BLE_MESH_RELAY_DISABLED              0x00
#define BLE_MESH_RELAY_ENABLED               0x01
#define BLE_MESH_RELAY_NOT_SUPPORTED         0x02

#define BLE_MESH_BEACON_DISABLED             0x00
#define BLE_MESH_BEACON_ENABLED              0x01

#define BLE_MESH_GATT_PROXY_DISABLED         0x00
#define BLE_MESH_GATT_PROXY_ENABLED          0x01
#define BLE_MESH_GATT_PROXY_NOT_SUPPORTED    0x02

#define BLE_MESH_FRIEND_DISABLED             0x00
#define BLE_MESH_FRIEND_ENABLED              0x01
#define BLE_MESH_FRIEND_NOT_SUPPORTED        0x02

#define BLE_MESH_NODE_IDENTITY_STOPPED       0x00
#define BLE_MESH_NODE_IDENTITY_RUNNING       0x01
#define BLE_MESH_NODE_IDENTITY_NOT_SUPPORTED 0x02

/* 特征*/
#define BLE_MESH_FEAT_RELAY                  BIT(0)
#define BLE_MESH_FEAT_PROXY                  BIT(1)
#define BLE_MESH_FEAT_FRIEND                 BIT(2)
#define BLE_MESH_FEAT_LOW_POWER              BIT(3)
#define BLE_MESH_FEAT_SUPPORTED              (BLE_MESH_FEAT_RELAY |     \
                                              BLE_MESH_FEAT_PROXY |     \
                                              BLE_MESH_FEAT_FRIEND |    \
                                              BLE_MESH_FEAT_LOW_POWER)

/** @brief 检查网格堆栈是否已初始化。
 *
 *  @return 真-是，假-不是。
 */
bool bt_mesh_is_initialized(void);

/** @brief 初始化网格支持
 *
 *  调用此API后，节点不会自动通告为未配置，而是需要调用bt_mesh_prov_enable（）API以在一个或多个配置承载上启用未配置的通告。
 *
 *  @param prov 节点配置信息。
 *  @param comp 节点组成。
 *
 *  @return 成功时为零，否则为（负）错误代码。
 */
int bt_mesh_init(const struct bt_mesh_prov *prov,
                 const struct bt_mesh_comp *comp);

/* BLE网格卸载参数*/
struct bt_mesh_deinit_param {
    bool erase; /* 指示卸载网格堆栈时是否擦除闪存*/
};

/** @brief 取消初始化网格支持
 *
 *  @param param BLE网格解编参数。
 *
 *  @return 成功时为零，否则为（负）错误代码。
 */
int bt_mesh_deinit(struct bt_mesh_deinit_param *param);

/** @brief 重置本地网格节点的状态。
 *
 *  重置节点的状态，这意味着需要重新配置它才能再次成为网状网络中的活动节点。
 *
 *  调用此API后，节点不会自动通告为未配置，而是需要调用bt_mesh_prov_enable（）API以在一个或多个配置承载上启用未配置的通告。
 *
 */
void bt_mesh_node_reset(void);

/** @brief 暂时挂起网格网络。
 *
 *  此API可用于节能目的，但用户应注意，让本地节点长时间挂起可能会导致其与Mesh网络永久断开连接。如果可能的话，应该使用友谊功能，将节点变成低功耗节点。
 *
 *  @return 成功时为0，失败时为（负）错误代码。
 */
int bt_mesh_suspend(void);

/** @brief 恢复挂起的网状网络。
 *
 *  在使用bt_mesh_suspend（）API暂停本地节点后，此API将恢复本地节点。
 *
 *  @return 成功时为0，失败时为（负）错误代码。
 */
int bt_mesh_resume(void);

/** @brief 设置本地网格节点。
 *
 *  应用程序通常不应直接使用此API。唯一的例外是出于测试目的，需要手动配置，而无需实际的外部配置程序。
 *
 *  @param net_key  网络密钥
 *  @param net_idx  网络密钥索引
 *  @param flags    设置标志
 *  @param iv_index IV索引
 *  @param addr     主要元素地址
 *  @param dev_key  设备密钥
 *
 *  @return 成功时为零，否则为（负）错误代码。
 */
int bt_mesh_provision(const uint8_t net_key[16], uint16_t net_idx,
                      uint8_t flags, uint32_t iv_index, uint16_t addr,
                      const uint8_t dev_key[16]);

/** @brief 检查该设备是否为未配置设备，并在配置后充当节点。
 *
 *  @return 真-是，假-不是。
 */
bool bt_mesh_is_node(void);

/** @brief 检查是否已配置本地节点。
 *
 *  此API可用于检查本地节点是否已配置。例如，确定闪存中是否存在存储的网络，即在调用settings_load（）后网络是否已恢复，这可能很有帮助。
 *
 *  @return 如果已配置节点，则为True。否则为False。
 */
bool bt_mesh_is_provisioned(void);

/** @brief 检查设备是否为Provisioner。
 *
 *  @return 真-是，假-不是。
 */
bool bt_mesh_is_provisioner(void);

/** @brief 检查Provisioner是否已启用
 *
 *  @return true-启用，false-禁用。
 */
bool bt_mesh_is_provisioner_en(void);

/** @brief 切换IV Update测试模式
 *
 *  只有在Kconfig中启用了IV Update测试模式时，此API才可用。它是通过大多数IV Update资格测试用例所必需的。
 *
 *  @param enable true表示启用IV Update测试模式，false表示禁用。
 */
void bt_mesh_iv_update_test(bool enable);

/** @brief 切换IV更新状态
 *
 *  只有在Kconfig中启用了IV Update测试模式时，此API才可用。它是通过大多数IV Update资格测试用例所必需的。
 *
 *  @return 如果进入IV Update In Progress状态，则为true，否则为false。
 */
bool bt_mesh_iv_update(void);

/** @brief 切换本地设备的低功耗功能
 *
 *  启用或禁用本地设备的低功耗功能。这是一个运行时功能，因为设备可能希望更改此功能，例如，基于插入稳定电源或使用电池电源运行。
 *
 *  @param enable  true表示启用LPN功能，false表示禁用LPN功能。
 *  @param force   当禁用LPN功能时，使用此标志指示是直接清除相应信息还是发送好友清除以禁用它。
 *
 *  @return 成功时为零，否则为（负）错误代码。
 */
int bt_mesh_lpn_set(bool enable, bool force);

/** @brief 发送朋友投票消息。
 *
 *  向此节点的好友发送好友轮询消息。如果没有建立友谊，函数将返回错误。
 *
 *  @return 成功时为零，否则为（负）错误代码。
 */
int bt_mesh_lpn_poll(void);

/** @brief 注册友谊更改的回调。
 *
 *  注册一个回调，当友谊建立或丢失时将调用该回调。
 *
 *  @param cb 当友谊状态更改时调用的函数。
 */
void bt_mesh_lpn_set_cb(void (*cb)(uint16_t friend_addr, bool established));

/** @brief 注册好友节点友谊更改的回调。
 *
 *  注册一个回调，当友谊建立或终止时将调用该回调。
 *
 *  @param cb 当朋友节点的友谊状态更改时调用的函数。
 */
void bt_mesh_friend_set_cb(void (*cb)(bool establish, uint16_t lpn_addr, uint8_t reason));

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* _BLE_MESH_MAIN_H_ */

