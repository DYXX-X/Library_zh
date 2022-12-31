/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_STORE_
#define H_BLE_STORE_

#include <inttypes.h>
#include "nimble/ble.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BLE_STORE_OBJ_TYPE_OUR_SEC           1
#define BLE_STORE_OBJ_TYPE_PEER_SEC          2
#define BLE_STORE_OBJ_TYPE_CCCD              3
#define BLE_STORE_OBJ_TYPE_PEER_DEV_REC      4

/**未能保留记录；存储容量不足。*/
#define BLE_STORE_EVENT_OVERFLOW        1

/**即将执行可能因溢出而失败的过程。*/
#define BLE_STORE_EVENT_FULL            2

/**
 * 用作查找安全材料的密钥。此结构对应于以下存储对象类型：o BLE_store_OBY_TYPE_OUR_SEC o BLE_store _OBJ_TYPE_PEER_SEC
 */
struct ble_store_key_sec {
    /**
     * 按对等身份地址的密钥；peer_addr=BLE_addr_NONE表示不关闭对等机。
     */
    ble_addr_t peer_addr;

    /**由ediv提供的密钥；ediv_rand_present=0表示不关闭ediv。*/
    uint16_t ediv;

    /**按rand_num键；ediv_rand_present=0表示不关闭rand_num。*/
    uint64_t rand_num;

    unsigned ediv_rand_present:1;

    /**要跳过的结果数；0表示检索第一个匹配。*/
    uint8_t idx;
};

/**
 * 表示存储的安全材料。此结构对应于以下存储对象类型：o BLE_store_OBY_TYPE_OUR_SEC o BLE_store _OBJ_TYPE_PEER_SEC
 */
struct ble_store_value_sec {
    ble_addr_t peer_addr;

    uint8_t key_size;
    uint16_t ediv;
    uint64_t rand_num;
    uint8_t ltk[16];
    uint8_t ltk_present:1;

    uint8_t irk[16];
    uint8_t irk_present:1;

    uint8_t csrk[16];
    uint8_t csrk_present:1;

    unsigned authenticated:1;
    uint8_t sc:1;
};

/**
 * 用作查找存储的客户端特征配置描述符（CCCD）的密钥。此结构对应于BLE_STORE_OBY_TYPE_CCCD存储对象类型。
 */
struct ble_store_key_cccd {
    /**
     * 按对等身份地址的密钥；peer_addr=BLE_addr_NONE表示不关闭对等机。
     */
    ble_addr_t peer_addr;

    /**
     * 按特征值手柄键；chr_val_handle=0表示不关闭特征句柄。
     */
    uint16_t chr_val_handle;

    /**要跳过的结果数；0表示检索第一个匹配。*/
    uint8_t idx;
};

/**
 * 表示存储的客户端特征配置描述符（CCCD）。此结构对应于BLE_STORE_OBY_TYPE_CCCD存储对象类型。
 */
struct ble_store_value_cccd {
    ble_addr_t peer_addr;
    uint16_t chr_val_handle;
    uint16_t flags;
    unsigned value_changed:1;
};

/**
 * 用作存储查找的键。此联合必须随附对象类型代码，以指示哪个字段有效。
 */
union ble_store_key {
    struct ble_store_key_sec sec;
    struct ble_store_key_cccd cccd;
};

/**
 * 表示存储的数据。此联合必须随附对象类型代码，以指示哪个字段有效。
 */
union ble_store_value {
    struct ble_store_value_sec sec;
    struct ble_store_value_cccd cccd;
};

struct ble_store_status_event {
    /**
     * 报告的事件类型；BLE_STORE_EVENT_TYPE_[…]代码之一。
     */
    int event_code;

    /**
     * 与事件相关的其他数据；从obj_type、eventcode对推断出有效字段。
     */
    union {
        /**
         * 表示由于存储耗尽而失败的写入。对以下事件类型有效：o BLE_STORE_event_OVERFLOW
         */
        struct {
            /**未能写入的对象类型。*/
            int obj_type;

            /**未能写入的对象。*/
            const union ble_store_value *value;
        } overflow;

        /**
         * 表示由于存储耗尽而导致计划写入失败的可能性。对以下事件类型有效：o BLE_STORE_event_FULL
         */
        struct {
            /**可能无法写入的对象类型。*/
            int obj_type;

            /**提示写入的连接的句柄。*/
            uint16_t conn_handle;
        } full;
    };
};

/**
 * 在存储中搜索符合指定条件的对象。如果找到匹配项，将从存储中读取该项，并用检索到的对象填充dst参数。
 *
 * @param obj_type              要搜索的对象的类型；BLE_STORE_OBY_TYPE_[…]代码之一。
 * @param key                   指定要搜索的对象的属性。如果对象符合这些条件，则检索该对象。
 * @param dst                   成功后，将使用检索到的对象填充此对象。
 *
 * @return                      如果成功检索到对象，则为0；如果找不到匹配的对象，则返回BLE_HS_ENOENT；其他非零错误。
 */
typedef int ble_store_read_fn(int obj_type, const union ble_store_key *key,
                              union ble_store_value *dst);

/**
 * 将指定的对象写入存储区。如果存储中已存在具有相同标识的对象，则将替换该对象。如果存储空间不足，无法写入对象，则此函数可能会删除先前存储的值以腾出空间。
 *
 * @param obj_type              正在写入的对象的类型；BLE_STORE_OBY_TYPE_[…]代码之一。
 * @param val                   要持久化的对象。
 *
 * @return                      如果对象已成功写入，则为0；其他非零错误。
 */
typedef int ble_store_write_fn(int obj_type, const union ble_store_value *val);

/**
 * 在存储中搜索符合指定条件的第一个对象。如果找到匹配项，将从存储中删除。
 *
 * @param obj_type              要删除的对象的类型；BLE_STORE_OBY_TYPE_[…]代码之一。
 * @param key                   指定要搜索的对象的属性。如果对象符合这些条件，则将删除该对象。
 * @return                      如果成功检索到对象，则为0；如果找不到匹配的对象，则返回BLE_HS_ENOENT；其他非零错误。
 */
typedef int ble_store_delete_fn(int obj_type, const union ble_store_key *key);

/**
 * 表示无法执行存储操作。此回调应执行以下两项操作之一：o解决问题并返回0，表示存储操作应继续。o返回非零表示应中止存储操作。
 *
 * @param event                 描述要报告的存储事件。
 * @param arg                   可选用户参数。
 *
 * @return                      如果存储操作应继续，则为0；如果应中止存储操作，则为非零。
 */
typedef int ble_store_status_fn(struct ble_store_status_event *event,
                                void *arg);

int ble_store_read(int obj_type, const union ble_store_key *key,
                   union ble_store_value *val);
int ble_store_write(int obj_type, const union ble_store_value *val);
int ble_store_delete(int obj_type, const union ble_store_key *key);
int ble_store_overflow_event(int obj_type, const union ble_store_value *value);
int ble_store_full_event(int obj_type, uint16_t conn_handle);

int ble_store_read_our_sec(const struct ble_store_key_sec *key_sec,
                           struct ble_store_value_sec *value_sec);
int ble_store_write_our_sec(const struct ble_store_value_sec *value_sec);
int ble_store_delete_our_sec(const struct ble_store_key_sec *key_sec);
int ble_store_read_peer_sec(const struct ble_store_key_sec *key_sec,
                            struct ble_store_value_sec *value_sec);
int ble_store_write_peer_sec(const struct ble_store_value_sec *value_sec);
int ble_store_delete_peer_sec(const struct ble_store_key_sec *key_sec);

int ble_store_read_cccd(const struct ble_store_key_cccd *key,
                        struct ble_store_value_cccd *out_value);
int ble_store_write_cccd(const struct ble_store_value_cccd *value);
int ble_store_delete_cccd(const struct ble_store_key_cccd *key);

void ble_store_key_from_value_sec(struct ble_store_key_sec *out_key,
                                  const struct ble_store_value_sec *value);
void ble_store_key_from_value_cccd(struct ble_store_key_cccd *out_key,
                                   const struct ble_store_value_cccd *value);

void ble_store_key_from_value(int obj_type,
                              union ble_store_key *out_key,
                              const union ble_store_value *value);

typedef int ble_store_iterator_fn(int obj_type,
                                  union ble_store_value *val,
                                  void *cookie);

int ble_store_iterate(int obj_type,
                      ble_store_iterator_fn *callback,
                      void *cookie);

int ble_store_clear(void);

/***实用程序功能。*/

int ble_store_util_bonded_peers(ble_addr_t *out_peer_id_addrs,
                                int *out_num_peers,
                                int max_peers);
int ble_store_util_delete_all(int type, const union ble_store_key *key);
int ble_store_util_delete_peer(const ble_addr_t *peer_id_addr);
int ble_store_util_delete_oldest_peer(void);
int ble_store_util_count(int type, int *out_count);
int ble_store_util_status_rr(struct ble_store_status_event *event, void *arg);

#ifdef __cplusplus
}
#endif

#endif

