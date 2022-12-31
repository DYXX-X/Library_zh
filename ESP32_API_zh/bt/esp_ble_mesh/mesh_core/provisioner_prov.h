/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _PROVISIONER_PROV_H_
#define _PROVISIONER_PROV_H_

#include "mesh_main.h"
#include "mesh_bearer_adapt.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CONFIG_BLE_MESH_PBA_SAME_TIME
#define CONFIG_BLE_MESH_PBA_SAME_TIME   0
#endif

#ifndef CONFIG_BLE_MESH_PBG_SAME_TIME
#define CONFIG_BLE_MESH_PBG_SAME_TIME   0
#endif

#define RM_AFTER_PROV  BIT(0)
#define START_PROV_NOW BIT(1)
#define FLUSHABLE_DEV  BIT(2)

struct bt_mesh_unprov_dev_add {
    uint8_t  addr[6];
    uint8_t  addr_type;
    uint8_t  uuid[16];
    uint16_t oob_info;
    uint8_t  bearer;
};

struct bt_mesh_device_delete {
    uint8_t addr[6];
    uint8_t addr_type;
    uint8_t uuid[16];
};

#define NET_IDX_FLAG  BIT(0)
#define FLAGS_FLAG    BIT(1)
#define IV_INDEX_FLAG BIT(2)

struct bt_mesh_prov_data_info {
    union {
        uint16_t net_idx;
        uint8_t  flags;
        uint32_t iv_index;
    };
    uint8_t flag;
};

/* 以下API供主要provisioner内部使用*/

/**
 * @brief 此函数减少当前PB-GATT计数。
 *
 * @return 没有一个
 */
void bt_mesh_provisioner_pbg_count_dec(void);

/**
 * @brief 此函数清除正确设备的部分链接信息。
 *
 * @param[in] addr: 远程设备地址
 *
 * @return 没有一个
 */
void bt_mesh_provisioner_clear_link_info(const uint8_t addr[6]);

/**
 * @brief 此函数处理接收的PB-ADV PDU。
 *
 * @param[in] buf: 指向包含通用配置PDU的缓冲区的指针
 *
 * @return 零-成功，否则-失败
 */
void bt_mesh_provisioner_pb_adv_recv(struct net_buf_simple *buf);

/**
 * @brief 此函数发送配置邀请以开始配置此未配置的设备。
 *
 * @param[in] addr: 远程设备地址
 * @param[in] conn: 指向bt_conn结构的指针
 *
 * @return 零-成功，否则-失败
 */
int bt_mesh_provisioner_set_prov_conn(const uint8_t addr[6], struct bt_mesh_conn *conn);

/**
 * @brief 此函数发送配置邀请以开始配置此未配置的设备。
 *
 * @param[in] conn: 指向bt_conn结构的指针
 * @param[in] addr: 连接设备的地址
 *
 * @return 零-成功，否则-失败
 */
int bt_mesh_provisioner_pb_gatt_open(struct bt_mesh_conn *conn, uint8_t *addr);

/**
 * @brief 当相关连接终止时，此功能将重置使用的信息。
 *
 * @param[in] conn:   指向bt_conn结构的指针
 * @param[in] reason: 连接终止原因
 *
 * @return 零-成功，否则-失败
 */
int bt_mesh_provisioner_pb_gatt_close(struct bt_mesh_conn *conn, uint8_t reason);

/**
 * @brief 此函数处理接收的PB-GATT供应PDU。
 *
 * @param[in] conn: 指向bt_conn结构的指针
 * @param[in] buf:  指向包含提供PDU的缓冲区的指针
 *
 * @return 零-成功，否则-失败
 */
int bt_mesh_provisioner_pb_gatt_recv(struct bt_mesh_conn *conn, struct net_buf_simple *buf);

/**
 * @brief 此函数初始化提供程序的PB-GATT和PB-ADV相关信息。
 *
 * @param[in] prov_info: 指向应用程序初始化的提供程序信息的指针。
 *
 * @return 零-成功，否则-失败
 */
int bt_mesh_provisioner_prov_init(const struct bt_mesh_prov *prov_info);

int bt_mesh_provisioner_prov_reset(bool erase);

/**
 * @brief 此函数将取消初始化提供程序的PB-GATT和PB-ADV相关信息。
 *
 * @param[in] erase: 指示是否从闪存中擦除配置信息。
 *
 * @return 零-成功，否则-失败
 */
int bt_mesh_provisioner_prov_deinit(bool erase);

/**
 * @brief 此函数解析接收到的未配置设备信标广告包，如果选中，则开始使用PB-ADV承载配置此设备。
 *
 * @param[in] buf:  指向包含未配置设备信标的缓冲区的指针
 * @param[in] rssi: 接收到的未配置设备信标的RSSI
 *
 * @return 没有一个
 */
void bt_mesh_provisioner_unprov_beacon_recv(struct net_buf_simple *buf, int8_t rssi);

void bt_mesh_provisioner_prov_adv_recv(struct net_buf_simple *buf,
                                       const bt_mesh_addr_t *addr, int8_t rssi);

/**
 * @brief 此函数获取bt_mesh_prov指针。
 *
 * @return bt_mesh_prov指针（prov）
 */
const struct bt_mesh_prov *bt_mesh_provisioner_get_prov_info(void);

void bt_mesh_provisioner_restore_prov_info(uint16_t primary_addr, uint16_t alloc_addr);

/* 以下API用于主要配置程序应用程序*/

/** @brief 将未配置的设备信息添加到未配置的dev队列
 *
 *  @param[in] add_dev: 指向包含设备信息的结构的指针
 *  @param[in] flags:   标志表示设备信息的若干操作
 *                       -配置队列后从队列中删除设备信息（BIT0）
 *                       -将设备添加到队列（BIT1）后立即开始配置
 *                       -当设备队列已满时，可以刷新设备（BIT2）
 *
 *  @return 成功时为零，否则为（负）错误代码。
 *
 *  @note  1.目前地址类型只支持公共地址和静态随机地址。2.如果设备UUID和/或设备地址和地址类型已经存在于设备队列中，但承载不同于现有承载，则添加操作也将成功，并将更新设备支持的提供承载。
 */
int bt_mesh_provisioner_add_unprov_dev(struct bt_mesh_unprov_dev_add *add_dev, uint8_t flags);

/** @brief 提供具有固定单播地址的未配置设备。
 *
 *  @param[in] uuid:         未配置设备的设备UUID
 *  @param[in] addr:         未配置设备的设备地址
 *  @param[in] addr_type:    未配置设备的设备地址类型
 *  @param[in] bearer:       准备使用的承载
 *  @param[in] oob_info:     未配置设备的OOB信息
 *  @param[in] unicast_addr: 将为未配置的设备分配单播地址
 *
 *  @return 成功时为零，否则为（负）错误代码。
 *
 *  @note  1.目前地址类型只支持公共地址和静态随机地址。2.承载必须等于BLE_MESH_PROV_ADV或BLE_MESH-PROV_GATT
 */
int bt_mesh_provisioner_prov_device_with_addr(const uint8_t uuid[16], const uint8_t addr[6],
                                              uint8_t addr_type, bt_mesh_prov_bearer_t bearer,
                                              uint16_t oob_info, uint16_t unicast_addr);

/** @brief 从队列中删除设备，重置当前配置链接并重置节点
 *
 *  @param[in] del_dev: 指向包含设备信息的结构的指针
 *
 *  @return 成功时为零，否则为（负）错误代码。
 */
int bt_mesh_provisioner_delete_device(struct bt_mesh_device_delete *del_dev);

/**
 * @brief 此函数设置设备UUID的一部分，以便在开始配置设备之前进行比较。
 *
 * @param[in] offset: 要比较的设备UUID的偏移量
 * @param[in] length: 要比较的设备UUID的长度
 * @param[in] match:  要比较的值
 * @param[in] prov_flag: 标志指示是否接收到uuid_match广告数据包，之后将立即配置设备或将其报告给应用程序层
 *
 * @return 零-成功，否则-失败
 */
int bt_mesh_provisioner_set_dev_uuid_match(uint8_t offset, uint8_t length,
                                           const uint8_t *match, bool prov_flag);

/** @brief 从未配置设备队列中未配置的设备接收广告数据包的提供商的回调。
 *
 *  向应用层报告未配置的设备信标和网格配置服务广告数据
 *
 *  @param addr      未设置的设备地址指针
 *  @param addr_type 未设置的设备地址类型
 *  @param dev_uuid  未设置的设备UUID指针
 *  @param bearer    从PB-GATT或PB-ADV承载接收的广告包
 *  @param adv_type  Adv数据包类型，目前未使用，我们可以使用承载来设置Adv_type（Adv_IND或Adv_ONCONN_IND）。当支持扫描响应数据时，将使用此参数。
 *  @param rssi      接收到的广告包的RSSI
 *
 */
typedef void (*unprov_adv_pkt_cb_t)(const uint8_t addr[6], const uint8_t addr_type,
                                    const uint8_t adv_type, const uint8_t dev_uuid[16],
                                    uint16_t oob_info, bt_mesh_prov_bearer_t bearer, int8_t rssi);

/**
 * @brief 此函数注册回调，该回调向应用层通知接收到的网格配置或未配置设备信标通告数据包（来自未配置设备队列中的设备）。
 *
 * @param[in] cb: 通知adv pkts函数的回调
 *
 * @return 零-成功，否则-失败
 */
int bt_mesh_provisioner_adv_pkt_cb_register(unprov_adv_pkt_cb_t cb);

/**
 * @brief 此函数用于更改配置数据中使用的net_idx或标志或iv_index。
 *
 * @param[in] info: 包含net_idx或标志或iv_index的结构指针
 *
 * @return 零-成功，否则-失败
 */
int bt_mesh_provisioner_set_prov_data_info(struct bt_mesh_prov_data_info *info);

/**
 * @brief 此函数初始化Provisioner所需的配置信息，包括NetKey索引、标志、IV索引等。
 *
 * @return 零-成功，否则-失败
 */
int bt_mesh_provisioner_init_prov_info(void);

/**
 * @brief 此函数设置Provisioner使用的配置承载类型。
 *
 * @param[in] bearers: 设置承载类型
 * @param[in] clear:   指示是否清除相应的承载类型
 *
 * @return 没有一个
 */
void bt_mesh_provisioner_set_prov_bearer(bt_mesh_prov_bearer_t bearers, bool clear);

/**
 * @brief 此函数获取Provisioner使用的配置承载类型。
 *
 * @return 当前支持的配置承载类型
 */
bt_mesh_prov_bearer_t bt_mesh_provisioner_get_prov_bearer(void);

/**
 * @brief 此函数设置Provisioner使用的静态OOB值。
 *
 * @param[in] value:  静态OOB值
 * @param[in] length: 静态OOB值长度
 *
 * @return 零-成功，否则-失败
 */
int bt_mesh_provisioner_set_static_oob_value(const uint8_t *value, uint8_t length);

/**
 * @brief 此函数获取Provisioner的主要元素的单播地址。
 *
 * @return Provisioner主要元素的单播地址。
 */
uint16_t bt_mesh_provisioner_get_primary_elem_addr(void);

/**
 * @brief 此函数设置Provisioner的主要元素的单播地址。
 *
 * @param[in] addr: 主元素的单播地址
 *
 * @return 零-成功，否则-失败
 */
int bt_mesh_provisioner_set_primary_elem_addr(uint16_t addr);

/**
 * @brief 此函数用于由Provisioner更新下一个分配的地址。
 *
 * @note  此功能用于网格内部测试。
 *
 * @param[in] unicast_addr: 节点的单播地址
 * @param[in] element_num:  节点的元素计数
 *
 * @return 零-成功，否则-失败
 */
int bt_mesh_test_provisioner_update_alloc_addr(uint16_t unicast_addr, uint16_t element_num);

/**
 * @brief 调用此函数以输入未配置设备输出的数字/字符串。
 *
 * @param[in] idx       配置链接索引
 * @param[in] val       输入数字/字符串的指针
 * @param[in] num_flag  标志指示它是数字还是字符串
 *
 * @return 零-成功，否则-失败
 */
int bt_mesh_provisioner_set_oob_input_data(const uint8_t idx, const uint8_t *val, bool num_flag);

/**
 * @brief 调用此函数以输出将由未配置设备输入的数字/字符串。
 *
 * @param[in] idx       配置链接索引
 * @param[in] num       输出数字/字符串的指针
 * @param[in] size      输出编号/字符串的大小
 * @param[in] num_flag  标志指示它是数字还是字符串
 *
 * @return 零-成功，否则-失败
 */
int bt_mesh_provisioner_set_oob_output_data(const uint8_t idx, const uint8_t *num,
                                            uint8_t size, bool num_flag);

/**
 * @brief 调用此函数以读取未配置设备的oob公钥。
 *
 * @param[in] idx        配置链接索引
 * @param[in] pub_key_x  未设置设备的公钥X
 * @param[in] pub_key_y  未设置设备的公钥Y
 *
 * @return 零-成功，否则-失败
 */
int bt_mesh_provisioner_read_oob_pub_key(const uint8_t idx, const uint8_t pub_key_x[32],
                                         const uint8_t pub_key_y[32]);

/* 以下API用于快速资源调配*/

/**
 * @brief 调用此函数以设置fast_prov_flag。
 *
 * @param[in] enable: 启用或禁用快速资源调配
 *
 * @return 没有一个
 */
void bt_mesh_provisioner_fast_prov_enable(bool enable);

/**
 * @brief 调用此函数以设置用于快速配置的网络密钥索引。
 *
 * @param[in] net_idx: 网络密钥索引
 *
 * @return 没有一个
 */
void bt_mesh_provisioner_set_fast_prov_net_idx(uint16_t net_idx);

/**
 * @brief 调用此函数以获取用于快速配置的网络密钥索引。
 *
 * @return 快速供应的net_idx
 */
uint16_t bt_mesh_provisioner_get_fast_prov_net_idx(void);

/**
 * @brief 调用此函数以设置用于快速配置的单播地址范围。
 *
 * @param[in] min: 最小单播地址
 * @param[in] max: 最大单播地址
 *
 * @return 设置单播地址范围消息的状态
 */
uint8_t bt_mesh_set_fast_prov_unicast_addr_range(uint16_t min, uint16_t max);

/**
 * @brief 调用此函数以设置用于快速配置的标志&iv_index。
 *
 * @param[in] flags:    密钥刷新标志和iv更新标志
 * @param[in] iv_index: IV指数
 *
 * @return 没有一个
 */
void bt_mesh_set_fast_prov_flags_iv_index(uint8_t flags, uint32_t iv_index);

#ifdef __cplusplus
}
#endif

#endif /* _PROVISIONER_PROV_H_ */

