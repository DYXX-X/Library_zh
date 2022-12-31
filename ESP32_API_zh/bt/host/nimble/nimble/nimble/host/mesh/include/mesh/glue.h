/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef _MESH_GLUE_
#define _MESH_GLUE_

#include <assert.h>
#include <errno.h>

#include "syscfg/syscfg.h"
#include "logcfg/logcfg.h"
#include "modlog/modlog.h"
#include "nimble/nimble_npl.h"

#include "os/os_mbuf.h"
#include "os/queue.h"

#include "nimble/ble.h"
#include "host/ble_hs.h"
#include "host/ble_uuid.h"
#include "../src/ble_sm_priv.h"
#include "../src/ble_hs_hci_priv.h"

#if MYNEWT_VAL(BLE_CRYPTO_STACK_MBEDTLS)
#include "mbedtls/aes.h"
#include "mbedtls/cipher.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/cmac.h"
#include "mbedtls/ecdh.h"
#include "mbedtls/ecp.h"

#else
#include "tinycrypt/aes.h"
#include "tinycrypt/constants.h"
#include "tinycrypt/utils.h"
#include "tinycrypt/cmac_mode.h"
#include "tinycrypt/ecc_dh.h"
#endif

#if MYNEWT_VAL(BLE_MESH_SETTINGS)
#include "config/config.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define u8_t    uint8_t
#define s8_t    int8_t
#define u16_t   uint16_t
#define s16_t   int16_t
#define u32_t   uint32_t
#define u64_t   uint64_t
#define s64_t   int64_t
#define s32_t   int32_t

/** @brief 帮助程序声明bt_data数组的元素
 *
 *  此宏主要用于创建结构bt_data元素数组，然后将其传递给bt_le_adv_start（）。
 *
 *  @param _type 广告数据字段的类型
 *  @param _data 指向数据字段有效负载的指针
 *  @param _data_len 数据指针后面的字节数（_D）
 */
#define BT_DATA(_type, _data, _data_len) \
    { \
        .type = (_type), \
        .data_len = (_data_len), \
        .data = (const u8_t *)(_data), \
    }

/** @brief 帮助程序声明bt_data数组的元素
 *
 *  此宏主要用于创建结构bt_data元素数组，然后将其传递给bt_le_adv_start（）。
 *
 *  @param _type 广告数据字段的类型
 *  @param _bytes 可变数量的单字节参数
 */
#define BT_DATA_BYTES(_type, _bytes...) \
    BT_DATA(_type, ((u8_t []) { _bytes }), \
        sizeof((u8_t []) { _bytes }))

/* EIR/AD数据类型定义*/
#define BT_DATA_FLAGS                   0x01 /* AD标志*/
#define BT_DATA_UUID16_SOME             0x02 /* 16位UUID，更多可用*/
#define BT_DATA_UUID16_ALL              0x03 /* 16位UUID，全部列出*/
#define BT_DATA_UUID32_SOME             0x04 /* 32位UUID，更多可用*/
#define BT_DATA_UUID32_ALL              0x05 /* 32位UUID，全部列出*/
#define BT_DATA_UUID128_SOME            0x06 /* 128位UUID，更多可用*/
#define BT_DATA_UUID128_ALL             0x07 /* 128位UUID，全部列出*/
#define BT_DATA_NAME_SHORTENED          0x08 /* 简称*/
#define BT_DATA_NAME_COMPLETE           0x09 /* 完整名称*/
#define BT_DATA_TX_POWER                0x0a /* Tx电源*/
#define BT_DATA_SOLICIT16               0x14 /* 请求UUID，16位*/
#define BT_DATA_SOLICIT128              0x15 /* 请求UUID，128位*/
#define BT_DATA_SVC_DATA16              0x16 /* 服务数据，16位UUID*/
#define BT_DATA_GAP_APPEARANCE          0x19 /* GAP外观*/
#define BT_DATA_SOLICIT32               0x1f /* 请求UUID，32位*/
#define BT_DATA_SVC_DATA32              0x20 /* 服务数据，32位UUID*/
#define BT_DATA_SVC_DATA128             0x21 /* 服务数据，128位UUID*/
#define BT_DATA_URI                     0x24 /* URI */
#define BT_DATA_MESH_PROV               0x29 /* 网格配置PDU*/
#define BT_DATA_MESH_MESSAGE            0x2a /* 网状网络PDU*/
#define BT_DATA_MESH_BEACON             0x2b /* 网状信标*/

#define BT_DATA_MANUFACTURER_DATA       0xff /* 制造商特定数据*/

#define BT_LE_AD_LIMITED                0x01 /* 有限的可发现性*/
#define BT_LE_AD_GENERAL                0x02 /* 一般可发现*/
#define BT_LE_AD_NO_BREDR               0x04 /* 不支持BR/EDR*/

#define sys_put_be16(a,b) put_be16(b, a)
#define sys_put_le16(a,b) put_le16(b, a)
#define sys_put_be32(a,b) put_be32(b, a)
#define sys_get_be16(a) get_be16(a)
#define sys_get_le16(a) get_le16(a)
#define sys_get_be32(a) get_be32(a)
#define sys_cpu_to_be16(a) htobe16(a)
#define sys_cpu_to_be32(a) htobe32(a)
#define sys_be32_to_cpu(a) be32toh(a)
#define sys_be16_to_cpu(a) be16toh(a)
#define sys_le16_to_cpu(a) le16toh(a)

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

#define CODE_UNREACHABLE __builtin_unreachable()
#define __ASSERT(code, str) \
    do {                          \
        if (!(code)) BT_ERR(str); \
        assert(code);             \
    } while (0);

#define __ASSERT_NO_MSG(test) __ASSERT(test, "")

/* 网眼布设计为不使用mbuf链条*/
#if BT_DBG_ENABLED
#define ASSERT_NOT_CHAIN(om) assert(SLIST_NEXT(om, om_next) == NULL)
#else
#define ASSERT_NOT_CHAIN(om) (void)(om)
#endif

#define __packed    __attribute__((__packed__))

#define MSEC_PER_SEC   (1000)
#define K_MSEC(ms)     (ms)
#define K_SECONDS(s)   K_MSEC((s) * MSEC_PER_SEC)
#define K_MINUTES(m)   K_SECONDS((m) * 60)
#define K_HOURS(h)     K_MINUTES((h) * 60)

#ifndef BIT
#define BIT(n)  (1UL << (n))
#endif

#define BIT_MASK(n) (BIT(n) - 1)

#define BT_GAP_ADV_FAST_INT_MIN_1               0x0030  /* 30毫秒*/
#define BT_GAP_ADV_FAST_INT_MAX_1               0x0060  /* 60毫秒*/
#define BT_GAP_ADV_FAST_INT_MIN_2               0x00a0  /* 100毫秒*/
#define BT_GAP_ADV_FAST_INT_MAX_2               0x00f0  /* 150毫秒*/
#define BT_GAP_ADV_SLOW_INT_MIN                 0x0640  /* 1秒*/
#define BT_GAP_ADV_SLOW_INT_MAX                 0x0780  /* 1.2秒*/

#ifndef MESH_LOG_MODULE
#define MESH_LOG_MODULE BLE_MESH_LOG
#endif

#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

#define BLE_MESH_LOG(lvl, ...) CAT(MESH_LOG_MODULE, CAT(_, lvl))(__VA_ARGS__)

#define BT_DBG(fmt, ...)    BLE_MESH_LOG(DEBUG, "%s: " fmt "\n", __func__, ## __VA_ARGS__);
#define BT_INFO(fmt, ...)   BLE_MESH_LOG(INFO, "%s: " fmt "\n", __func__, ## __VA_ARGS__);
#define BT_WARN(fmt, ...)   BLE_MESH_LOG(WARN, "%s: " fmt "\n", __func__, ## __VA_ARGS__);
#define BT_ERR(fmt, ...)    BLE_MESH_LOG(ERROR, "%s: " fmt "\n", __func__, ## __VA_ARGS__);
#define BT_GATT_ERR(_att_err)   (-(_att_err))

typedef ble_addr_t bt_addr_le_t;

#define k_fifo_init(queue) ble_npl_eventq_init(queue)
#define net_buf_simple_tailroom(buf) OS_MBUF_TRAILINGSPACE(buf)
#define net_buf_tailroom(buf) net_buf_simple_tailroom(buf)
#define net_buf_headroom(buf) ((buf)->om_data - &(buf)->om_databuf[buf->om_pkthdr_len])
#define net_buf_simple_headroom(buf) net_buf_headroom(buf)
#define net_buf_simple_tail(buf) ((buf)->om_data + (buf)->om_len)

struct net_buf_simple_state {
    /**数据指针从存储开始的偏移量*/
    u16_t offset;
    /**数据长度*/
    u16_t len;
};

static inline struct os_mbuf * NET_BUF_SIMPLE(uint16_t size)
{
    struct os_mbuf *buf;

    buf = os_msys_get(size, 0);
    assert(buf);

    return buf;
}

#define K_NO_WAIT (0)
#define K_FOREVER (-1)

#if MYNEWT_VAL(BLE_EXT_ADV)
#define BT_MESH_ADV_INST     (MYNEWT_VAL(BLE_MULTI_ADV_INSTANCES))

#if MYNEWT_VAL(BLE_MESH_PROXY)
/* 请注意，BLE_MULTI_ADV_INSTANCES包含许多其他实例。实例0始终存在
 */
#if MYNEWT_VAL(BLE_MULTI_ADV_INSTANCES) < 1
#error "Mesh needs at least BLE_MULTI_ADV_INSTANCES set to 1"
#endif
#define BT_MESH_ADV_GATT_INST     (MYNEWT_VAL(BLE_MULTI_ADV_INSTANCES) - 1)
#endif /* BLE_MESH_PROXY */
#endif /* BLE_EXT_ADV */

/* 这是故意的*/
static inline void net_buf_simple_init(struct os_mbuf *buf,
                                       size_t reserve_head)
{
    /* 这在初始化后的Zephyr中被调用。注意，在Mynewt的情况下，我们不在乎保留的头*/
    buf->om_data = &buf->om_databuf[buf->om_pkthdr_len] + reserve_head;
    buf->om_len = 0;
}

void net_buf_put(struct ble_npl_eventq *fifo, struct os_mbuf *buf);
void * net_buf_ref(struct os_mbuf *om);
void net_buf_unref(struct os_mbuf *om);
uint16_t net_buf_simple_pull_le16(struct os_mbuf *om);
uint16_t net_buf_simple_pull_be16(struct os_mbuf *om);
uint32_t net_buf_simple_pull_be32(struct os_mbuf *om);
uint32_t net_buf_simple_pull_le32(struct os_mbuf *om);
uint8_t net_buf_simple_pull_u8(struct os_mbuf *om);
void net_buf_simple_add_le16(struct os_mbuf *om, uint16_t val);
void net_buf_simple_add_be16(struct os_mbuf *om, uint16_t val);
void net_buf_simple_add_u8(struct os_mbuf *om, uint8_t val);
void net_buf_simple_add_be32(struct os_mbuf *om, uint32_t val);
void net_buf_simple_add_le32(struct os_mbuf *om, uint32_t val);
void net_buf_add_zeros(struct os_mbuf *om, uint8_t len);
void net_buf_simple_push_le16(struct os_mbuf *om, uint16_t val);
void net_buf_simple_push_be16(struct os_mbuf *om, uint16_t val);
void net_buf_simple_push_u8(struct os_mbuf *om, uint8_t val);
void *net_buf_simple_pull(struct os_mbuf *om, uint8_t len);
void *net_buf_simple_pull_mem(struct os_mbuf *om, uint8_t len);
void *net_buf_simple_add(struct os_mbuf *om, uint8_t len);
bool k_fifo_is_empty(struct ble_npl_eventq *q);
void *net_buf_get(struct ble_npl_eventq *fifo,s32_t t);
uint8_t *net_buf_simple_push(struct os_mbuf *om, uint8_t len);
void net_buf_reserve(struct os_mbuf *om, size_t reserve);

#define net_buf_add_mem(a,b,c) os_mbuf_append(a,b,c)
#define net_buf_simple_add_mem(a,b,c) os_mbuf_append(a,b,c)
#define net_buf_add_u8(a,b) net_buf_simple_add_u8(a,b)
#define net_buf_add(a,b) net_buf_simple_add(a,b)

#define net_buf_clone(a, b) os_mbuf_dup(a)
#define net_buf_add_be32(a, b) net_buf_simple_add_be32(a, b)
#define net_buf_add_be16(a, b) net_buf_simple_add_be16(a, b)
#define net_buf_pull(a, b) net_buf_simple_pull(a, b)
#define net_buf_pull_mem(a, b) net_buf_simple_pull_mem(a, b)
#define net_buf_pull_u8(a) net_buf_simple_pull_u8(a)
#define net_buf_pull_be16(a) net_buf_simple_pull_be16(a)
#define net_buf_skip(a, b) net_buf_simple_pull_mem(a, b)

#define BT_GATT_CCC_NOTIFY BLE_GATT_CHR_PROP_NOTIFY

/** 可编码为广告数据的不同数据类型的描述。用于形成传递给bt_le_adv_start（）函数的数组。
  */
struct bt_data {
    u8_t type;
    u8_t data_len;
    const u8_t *data;
};

struct bt_pub_key_cb {
    /** @brief 生成公钥的回调类型。
     *
     *  用于通知本地公钥或本地密钥不可用（由于读取失败或正在重新生成）。
     *
     *  @param key 本地公钥，如果没有密钥，则为NULL。
     */
    void (*func)(const u8_t key[64]);

    struct bt_pub_key_cb *_next;
};

typedef void (*bt_dh_key_cb_t)(const u8_t key[32]);
int bt_dh_key_gen(const u8_t remote_pk[64], bt_dh_key_cb_t cb);
int bt_pub_key_gen(struct bt_pub_key_cb *new_cb);
uint8_t *bt_pub_key_get(void);
int bt_rand(void *buf, size_t len);
const char * bt_hex(const void *buf, size_t len);
int bt_encrypt_be(const uint8_t *key, const uint8_t *plaintext, uint8_t *enc_data);
void bt_mesh_register_gatt(void);
int bt_le_adv_start(const struct ble_gap_adv_params *param,
                    const struct bt_data *ad, size_t ad_len,
                    const struct bt_data *sd, size_t sd_len);
int bt_le_adv_stop(bool proxy);

struct k_delayed_work {
    struct ble_npl_callout work;
};

void k_work_init(struct ble_npl_callout *work, ble_npl_event_fn handler);
void k_delayed_work_init(struct k_delayed_work *w, ble_npl_event_fn *f);
void k_delayed_work_cancel(struct k_delayed_work *w);
void k_delayed_work_submit(struct k_delayed_work *w, uint32_t ms);
int64_t k_uptime_get(void);
u32_t k_uptime_get_32(void);
void k_sleep(int32_t duration);
void k_work_submit(struct ble_npl_callout *w);
void k_work_add_arg(struct ble_npl_callout *w, void *arg);
void k_delayed_work_add_arg(struct k_delayed_work *w, void *arg);
uint32_t k_delayed_work_remaining_get(struct k_delayed_work *w);

static inline void net_buf_simple_save(struct os_mbuf *buf,
                       struct net_buf_simple_state *state)
{
    state->offset = net_buf_simple_headroom(buf);
    state->len = buf->om_len;
}

static inline void net_buf_simple_restore(struct os_mbuf *buf,
                                          struct net_buf_simple_state *state)
{
      buf->om_data = &buf->om_databuf[buf->om_pkthdr_len] + state->offset;
      buf->om_len = state->len;
}

static inline void sys_memcpy_swap(void *dst, const void *src, size_t length)
{
    __ASSERT(((src < dst && (src + length) <= dst) ||
          (src > dst && (dst + length) <= src)),
         "Source and destination buffers must not overlap");

    src += length - 1;

    for (; length > 0; length--) {
        *((u8_t *)dst++) = *((u8_t *)src--);
    }
}

#define popcount(x) __builtin_popcount(x)

static inline unsigned int find_lsb_set(u32_t op)
{
    return __builtin_ffs(op);
}

static inline unsigned int find_msb_set(u32_t op)
{
    if (!op)
        return 0;

    return 32 - __builtin_clz(op);
}

#define CONFIG_BT_MESH_FRIEND               BLE_MESH_FRIEND
#define CONFIG_BT_MESH_GATT_PROXY           BLE_MESH_GATT_PROXY
#define CONFIG_BT_MESH_IV_UPDATE_TEST       BLE_MESH_IV_UPDATE_TEST
#define CONFIG_BT_MESH_LOW_POWER            BLE_MESH_LOW_POWER
#define CONFIG_BT_MESH_LPN_AUTO             BLE_MESH_LPN_AUTO
#define CONFIG_BT_MESH_LPN_ESTABLISHMENT    BLE_MESH_LPN_ESTABLISHMENT
#define CONFIG_BT_MESH_PB_ADV               BLE_MESH_PB_ADV
#define CONFIG_BT_MESH_PB_GATT              BLE_MESH_PB_GATT
#define CONFIG_BT_MESH_PROV                 BLE_MESH_PROV
#define CONFIG_BT_MESH_PROXY                BLE_MESH_PROXY
#define CONFIG_BT_TESTING                   BLE_MESH_TESTING
#define CONFIG_BT_SETTINGS                  BLE_MESH_SETTINGS
#define CONFIG_SETTINGS                     BLE_MESH_SETTINGS
#define CONFIG_BT_MESH_PROVISIONER          BLE_MESH_PROVISIONER

/* 以上标志与IS_ENABLED宏一起使用*/
#define IS_ENABLED(config) MYNEWT_VAL(config)

#define CONFIG_BT_MESH_LPN_GROUPS           MYNEWT_VAL(BLE_MESH_LPN_GROUPS)
#define CONFIG_BT_MESH_ADV_BUF_COUNT        MYNEWT_VAL(BLE_MESH_ADV_BUF_COUNT)
#define CONFIG_BT_MESH_FRIEND_QUEUE_SIZE    MYNEWT_VAL(BLE_MESH_FRIEND_QUEUE_SIZE)
#define CONFIG_BT_MESH_FRIEND_RECV_WIN      MYNEWT_VAL(BLE_MESH_FRIEND_RECV_WIN)
#define CONFIG_BT_MESH_LPN_POLL_TIMEOUT     MYNEWT_VAL(BLE_MESH_LPN_POLL_TIMEOUT)
#define CONFIG_BT_MESH_MODEL_GROUP_COUNT    MYNEWT_VAL(BLE_MESH_MODEL_GROUP_COUNT)
#define CONFIG_BT_MESH_MODEL_KEY_COUNT      MYNEWT_VAL(BLE_MESH_MODEL_KEY_COUNT)
#define CONFIG_BT_MESH_NODE_ID_TIMEOUT      MYNEWT_VAL(BLE_MESH_NODE_ID_TIMEOUT)
#define CONFIG_BT_MAX_CONN                  MYNEWT_VAL(BLE_MAX_CONNECTIONS)
#define CONFIG_BT_MESH_SEQ_STORE_RATE       MYNEWT_VAL(BLE_MESH_SEQ_STORE_RATE)
#define CONFIG_BT_MESH_RPL_STORE_TIMEOUT    MYNEWT_VAL(BLE_MESH_RPL_STORE_TIMEOUT)
#define CONFIG_BT_MESH_APP_KEY_COUNT        MYNEWT_VAL(BLE_MESH_APP_KEY_COUNT)
#define CONFIG_BT_MESH_SUBNET_COUNT         MYNEWT_VAL(BLE_MESH_SUBNET_COUNT)
#define CONFIG_BT_MESH_STORE_TIMEOUT        MYNEWT_VAL(BLE_MESH_STORE_TIMEOUT)
#define CONFIG_BT_MESH_IVU_DIVIDER          MYNEWT_VAL(BLE_MESH_IVU_DIVIDER)
#define CONFIG_BT_DEVICE_NAME               MYNEWT_VAL(BLE_MESH_DEVICE_NAME)
#define CONFIG_BT_MESH_TX_SEG_MAX           MYNEWT_VAL(BLE_MESH_TX_SEG_MAX)
#define CONFIG_BT_MESH_LABEL_COUNT          MYNEWT_VAL(BLE_MESH_LABEL_COUNT)
#define CONFIG_BT_MESH_NODE_COUNT           MYNEWT_VAL(BLE_MESH_NODE_COUNT)

#define printk console_printf

#define CONTAINER_OF(ptr, type, field) \
	((type *)(((char *)(ptr)) - offsetof(type, field)))


#define k_sem ble_npl_sem

static inline void k_sem_init(struct k_sem *sem, unsigned int initial_count,
			      unsigned int limit)
{
	ble_npl_sem_init(sem, initial_count);
}

static inline int k_sem_take(struct k_sem *sem, s32_t timeout)
{
	uint32_t ticks;

	ble_npl_time_ms_to_ticks(timeout, &ticks);
	return - ble_npl_sem_pend(sem,  ticks);
}

static inline void k_sem_give(struct k_sem *sem)
{
	ble_npl_sem_release(sem);
}

/* 帮助访问存储阵列，因为此时我们无法再访问其类型。
 */

#define BUF_SIZE(pool) (pool->omp_pool->mp_block_size)

static inline int net_buf_id(struct os_mbuf *buf)
{
	struct os_mbuf_pool *pool = buf->om_omp;
	u8_t *pool_start = (u8_t *)pool->omp_pool->mp_membuf_addr;
	u8_t *buf_ptr = (u8_t *)buf;

	return (buf_ptr - pool_start) / BUF_SIZE(pool);
}

/* 三十： 我们不应该使用os_mbuf_pkthdr链来表示数据包列表，这是一种黑客。目前这不是问题，因为mesh不使用os_mbuf链。我们应该在未来改变这一点。
 */
STAILQ_HEAD(net_buf_slist_t, os_mbuf_pkthdr);

void net_buf_slist_init(struct net_buf_slist_t *list);
bool net_buf_slist_is_empty(struct net_buf_slist_t *list);
struct os_mbuf *net_buf_slist_peek_head(struct net_buf_slist_t *list);
struct os_mbuf *net_buf_slist_peek_next(struct os_mbuf *buf);
struct os_mbuf *net_buf_slist_get(struct net_buf_slist_t *list);
void net_buf_slist_put(struct net_buf_slist_t *list, struct os_mbuf *buf);
void net_buf_slist_remove(struct net_buf_slist_t *list, struct os_mbuf *prev,
			  struct os_mbuf *cur);
void net_buf_slist_merge_slist(struct net_buf_slist_t *list,
			       struct net_buf_slist_t *list_to_append);
#define NET_BUF_SLIST_FOR_EACH_NODE(head, var) STAILQ_FOREACH(var, head, omp_next)

#if MYNEWT_VAL(BLE_MESH_SETTINGS)

#define settings_load conf_load
int settings_bytes_from_str(char *val_str, void *vp, int *len);
char *settings_str_from_bytes(const void *vp, int vp_len,
			      char *buf, int buf_len);

#define snprintk snprintf
#define BT_SETTINGS_SIZE(in_size) ((((((in_size) - 1) / 3) * 4) + 4) + 1)
#define settings_save_one conf_save_one

#else

static inline int
settings_load(void)
{
	return 0;
}

#endif /* MYNEWT_VAL(MYNEWT_VAL_BLE_MESH_SETTINGS) */

#define BUILD_ASSERT(cond) _Static_assert(cond, "")

#ifdef __cplusplus
}
#endif

#endif /* _MESH_GLUE_ */

