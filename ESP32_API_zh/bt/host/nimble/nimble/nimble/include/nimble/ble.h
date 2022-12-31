/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_
#define H_BLE_

#include <inttypes.h>
#include <string.h>
#include "syscfg/syscfg.h"
#include "os/os.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 广告实例数*/
#define BLE_ADV_INSTANCES    (MYNEWT_VAL(BLE_MULTI_ADV_INSTANCES) + 1)

/* BLE加密块定义*/
#define BLE_ENC_BLOCK_SIZE       (16)

/* 4字节报头+251字节有效载荷。*/
#define BLE_ACL_MAX_PKT_SIZE     255

struct ble_encryption_block
{
    uint8_t     key[BLE_ENC_BLOCK_SIZE];
    uint8_t     plain_text[BLE_ENC_BLOCK_SIZE];
    uint8_t     cipher_text[BLE_ENC_BLOCK_SIZE];
};

/*
 * BLE MBUF结构：
 *
 * BLE mbuf结构如下。注意，此结构适用于数据包头mbuf（而不是属于“数据包链”的mbuf）：structos_mbuf（16）structos-mbuf_pkthdr（8）structble_mbuf_hdr（8）数据缓冲区（有效负载大小，以字节为单位）
 *
 * BLE mbuf标头包含以下内容：flags：bitfield，值如下0x01：如果白名单上有匹配项，则设置0x02：如果在接收到pdu时发送了连接请求，则设置为0x04：设置第一次发送pdu的时间（用于检测重试）。信道：逻辑BLE信道PHY信道#（0-39）crcok：表示CRC校验通过（1）或失败（0）的标志。rssi：rssi，单位dBm。
 */
struct ble_mbuf_hdr_rxinfo
{
    uint16_t flags;
    uint8_t channel;
    uint8_t handle;
    int8_t  rssi;
    /* 三十： 我们可以只使用单个phy_mode字段*/
    int8_t  phy;
    uint8_t phy_mode;
#if MYNEWT_VAL(BLE_LL_CFG_FEAT_LL_PRIVACY)
    int8_t  rpa_index;
#endif
#if MYNEWT_VAL(BLE_LL_CFG_FEAT_LL_EXT_ADV)
    void *user_data;
#endif
};

/* rxinfo的标志定义*/
#define BLE_MBUF_HDR_F_IGNORED          (0x8000)
#define BLE_MBUF_HDR_F_SCAN_REQ_TXD     (0x4000)
#define BLE_MBUF_HDR_F_INITA_RESOLVED   (0x2000)
#define BLE_MBUF_HDR_F_TARGETA_RESOLVED (0x2000)
#define BLE_MBUF_HDR_F_EXT_ADV_SEC      (0x1000)
#define BLE_MBUF_HDR_F_EXT_ADV          (0x0800)
#define BLE_MBUF_HDR_F_RESOLVED         (0x0400)
#define BLE_MBUF_HDR_F_AUX_PTR_WAIT     (0x0200)
#define BLE_MBUF_HDR_F_AUX_INVALID      (0x0100)
#define BLE_MBUF_HDR_F_CRC_OK           (0x0080)
#define BLE_MBUF_HDR_F_DEVMATCH         (0x0040)
#define BLE_MBUF_HDR_F_MIC_FAILURE      (0x0020)
#define BLE_MBUF_HDR_F_SCAN_RSP_TXD     (0x0010)
#define BLE_MBUF_HDR_F_SCAN_RSP_RXD     (0x0008)
#define BLE_MBUF_HDR_F_RXSTATE_MASK     (0x0007)

/* 传输信息。注：未定义标志*/
struct ble_mbuf_hdr_txinfo
{
    uint8_t flags;
    uint8_t offset;
    uint8_t pyld_len;
    uint8_t hdr_byte;
};

struct ble_mbuf_hdr
{
    union {
        struct ble_mbuf_hdr_rxinfo rxinfo;
        struct ble_mbuf_hdr_txinfo txinfo;
    };
    uint32_t beg_cputime;
    uint32_t rem_usecs;
};

#define BLE_MBUF_HDR_IGNORED(hdr) \
    (!!((hdr)->rxinfo.flags & BLE_MBUF_HDR_F_IGNORED))

#define BLE_MBUF_HDR_SCAN_REQ_TXD(hdr) \
    (!!((hdr)->rxinfo.flags & BLE_MBUF_HDR_F_SCAN_REQ_TXD))

#define BLE_MBUF_HDR_EXT_ADV_SEC(hdr) \
    (!!((hdr)->rxinfo.flags & BLE_MBUF_HDR_F_EXT_ADV_SEC))

#define BLE_MBUF_HDR_EXT_ADV(hdr) \
    (!!((hdr)->rxinfo.flags & BLE_MBUF_HDR_F_EXT_ADV))

#define BLE_MBUF_HDR_DEVMATCH(hdr) \
    (!!((hdr)->rxinfo.flags & BLE_MBUF_HDR_F_DEVMATCH))

#define BLE_MBUF_HDR_SCAN_RSP_RXD(hdr) \
    (!!((hdr)->rxinfo.flags & BLE_MBUF_HDR_F_SCAN_RSP_RXD))

#define BLE_MBUF_HDR_AUX_INVALID(hdr) \
    (!!((hdr)->rxinfo.flags & BLE_MBUF_HDR_F_AUX_INVALID))

#define BLE_MBUF_HDR_WAIT_AUX(hdr)      \
    (!!((hdr)->rxinfo.flags & BLE_MBUF_HDR_F_AUX_PTR_WAIT))

#define BLE_MBUF_HDR_CRC_OK(hdr)        \
    (!!((hdr)->rxinfo.flags & BLE_MBUF_HDR_F_CRC_OK))

#define BLE_MBUF_HDR_MIC_FAILURE(hdr)   \
    (!!((hdr)->rxinfo.flags & BLE_MBUF_HDR_F_MIC_FAILURE))

#define BLE_MBUF_HDR_RESOLVED(hdr)      \
    (!!((hdr)->rxinfo.flags & BLE_MBUF_HDR_F_RESOLVED))

#define BLE_MBUF_HDR_INITA_RESOLVED(hdr)      \
    (!!((hdr)->rxinfo.flags & BLE_MBUF_HDR_F_INITA_RESOLVED))

#define BLE_MBUF_HDR_TARGETA_RESOLVED(hdr)      \
    (!!((hdr)->rxinfo.flags & BLE_MBUF_HDR_F_TARGETA_RESOLVED))

#define BLE_MBUF_HDR_RX_STATE(hdr)      \
    ((uint8_t)((hdr)->rxinfo.flags & BLE_MBUF_HDR_F_RXSTATE_MASK))

#define BLE_MBUF_HDR_PTR(om)            \
    (struct ble_mbuf_hdr *)((uint8_t *)om + sizeof(struct os_mbuf) + \
                            sizeof(struct os_mbuf_pkthdr))

/* 每个包头mbuf的BLE mbuf开销*/
#define BLE_MBUF_PKTHDR_OVERHEAD        \
    (sizeof(struct os_mbuf_pkthdr) + sizeof(struct ble_mbuf_hdr))

#define BLE_MBUF_MEMBLOCK_OVERHEAD      \
    (sizeof(struct os_mbuf) + BLE_MBUF_PKTHDR_OVERHEAD)

/* 主机用户标头的长度。仅包含对等方的连接句柄。*/
#define BLE_MBUF_HS_HDR_LEN     (2)

#define BLE_DEV_ADDR_LEN        (6)
extern uint8_t g_dev_addr[BLE_DEV_ADDR_LEN];
extern uint8_t g_random_addr[BLE_DEV_ADDR_LEN];

/* BLE错误代码（Core v4.2第2卷D部分）*/
enum ble_error_codes
{
    /* “错误”代码0x0表示成功*/
    BLE_ERR_SUCCESS             = 0x00,
    BLE_ERR_UNKNOWN_HCI_CMD     = 0x01,
    BLE_ERR_UNK_CONN_ID         = 0x02,
    BLE_ERR_HW_FAIL             = 0x03,
    BLE_ERR_PAGE_TMO            = 0x04,
    BLE_ERR_AUTH_FAIL           = 0x05,
    BLE_ERR_PINKEY_MISSING      = 0x06,
    BLE_ERR_MEM_CAPACITY        = 0x07,
    BLE_ERR_CONN_SPVN_TMO       = 0x08,
    BLE_ERR_CONN_LIMIT          = 0x09,
    BLE_ERR_SYNCH_CONN_LIMIT    = 0x0a,
    BLE_ERR_ACL_CONN_EXISTS     = 0x0b,
    BLE_ERR_CMD_DISALLOWED      = 0x0c,
    BLE_ERR_CONN_REJ_RESOURCES  = 0x0d,
    BLE_ERR_CONN_REJ_SECURITY   = 0x0e,
    BLE_ERR_CONN_REJ_BD_ADDR    = 0x0f,
    BLE_ERR_CONN_ACCEPT_TMO     = 0x10,
    BLE_ERR_UNSUPPORTED         = 0x11,
    BLE_ERR_INV_HCI_CMD_PARMS   = 0x12,
    BLE_ERR_REM_USER_CONN_TERM  = 0x13,
    BLE_ERR_RD_CONN_TERM_RESRCS = 0x14,
    BLE_ERR_RD_CONN_TERM_PWROFF = 0x15,
    BLE_ERR_CONN_TERM_LOCAL     = 0x16,
    BLE_ERR_REPEATED_ATTEMPTS   = 0x17,
    BLE_ERR_NO_PAIRING          = 0x18,
    BLE_ERR_UNK_LMP             = 0x19,
    BLE_ERR_UNSUPP_REM_FEATURE  = 0x1a,
    BLE_ERR_SCO_OFFSET          = 0x1b,
    BLE_ERR_SCO_ITVL            = 0x1c,
    BLE_ERR_SCO_AIR_MODE        = 0x1d,
    BLE_ERR_INV_LMP_LL_PARM     = 0x1e,
    BLE_ERR_UNSPECIFIED         = 0x1f,
    BLE_ERR_UNSUPP_LMP_LL_PARM  = 0x20,
    BLE_ERR_NO_ROLE_CHANGE      = 0x21,
    BLE_ERR_LMP_LL_RSP_TMO      = 0x22,
    BLE_ERR_LMP_COLLISION       = 0x23,
    BLE_ERR_LMP_PDU             = 0x24,
    BLE_ERR_ENCRYPTION_MODE     = 0x25,
    BLE_ERR_LINK_KEY_CHANGE     = 0x26,
    BLE_ERR_UNSUPP_QOS          = 0x27,
    BLE_ERR_INSTANT_PASSED      = 0x28,
    BLE_ERR_UNIT_KEY_PAIRING    = 0x29,
    BLE_ERR_DIFF_TRANS_COLL     = 0x2a,
    /* BLE_ERR_RESERVED=0x2b*/
    BLE_ERR_QOS_PARM            = 0x2c,
    BLE_ERR_QOS_REJECTED        = 0x2d,
    BLE_ERR_CHAN_CLASS          = 0x2e,
    BLE_ERR_INSUFFICIENT_SEC    = 0x2f,
    BLE_ERR_PARM_OUT_OF_RANGE   = 0x30,
    /* BLE_ERR_RESERVED=0x31*/
    BLE_ERR_PENDING_ROLE_SW     = 0x32,
    /* BLE_ERR_RESERVED=0x33*/
    BLE_ERR_RESERVED_SLOT       = 0x34,
    BLE_ERR_ROLE_SW_FAIL        = 0x35,
    BLE_ERR_INQ_RSP_TOO_BIG     = 0x36,
    BLE_ERR_SEC_SIMPLE_PAIR     = 0x37,
    BLE_ERR_HOST_BUSY_PAIR      = 0x38,
    BLE_ERR_CONN_REJ_CHANNEL    = 0x39,
    BLE_ERR_CTLR_BUSY           = 0x3a,
    BLE_ERR_CONN_PARMS          = 0x3b,
    BLE_ERR_DIR_ADV_TMO         = 0x3c,
    BLE_ERR_CONN_TERM_MIC       = 0x3d,
    BLE_ERR_CONN_ESTABLISHMENT  = 0x3e,
    BLE_ERR_MAC_CONN_FAIL       = 0x3f,
    BLE_ERR_COARSE_CLK_ADJ      = 0x40,
    BLE_ERR_TYPE0_SUBMAP_NDEF   = 0x41,
    BLE_ERR_UNK_ADV_INDENT      = 0x42,
    BLE_ERR_LIMIT_REACHED       = 0x43,
    BLE_ERR_OPERATION_CANCELLED = 0x44,
    BLE_ERR_PACKET_TOO_LONG     = 0x45,
    BLE_ERR_MAX                 = 0xff
};

/* 硬件错误代码*/
#define BLE_HW_ERR_DO_NOT_USE           (0) /* 三十： 现在就预订这个*/
#define BLE_HW_ERR_HCI_SYNC_LOSS        (1)

/* 自己的蓝牙设备地址类型*/
#define BLE_OWN_ADDR_PUBLIC                  (0x00)
#define BLE_OWN_ADDR_RANDOM                  (0x01)
#define BLE_OWN_ADDR_RPA_PUBLIC_DEFAULT      (0x02)
#define BLE_OWN_ADDR_RPA_RANDOM_DEFAULT      (0x03)

/* 蓝牙设备地址类型*/
#define BLE_ADDR_PUBLIC      (0x00)
#define BLE_ADDR_RANDOM      (0x01)
#define BLE_ADDR_PUBLIC_ID   (0x02)
#define BLE_ADDR_RANDOM_ID   (0x03)

#define BLE_ADDR_ANY (&(ble_addr_t) { 0, {0, 0, 0, 0, 0, 0} })

#define BLE_ADDR_IS_RPA(addr)     (((addr)->type == BLE_ADDR_RANDOM) && \
                                   ((addr)->val[5] & 0xc0) == 0x40)
#define BLE_ADDR_IS_NRPA(addr)    (((addr)->type == BLE_ADDR_RANDOM) && \
                                   ((addr)->val[5] & 0xc0) == 0x00)
#define BLE_ADDR_IS_STATIC(addr)  (((addr)->type == BLE_ADDR_RANDOM) && \
                                   ((addr)->val[5] & 0xc0) == 0xc0)

typedef struct {
    uint8_t type;
    uint8_t val[6];
} ble_addr_t;


static inline int ble_addr_cmp(const ble_addr_t *a, const ble_addr_t *b)
{
    int type_diff;

    type_diff = a->type - b->type;
    if (type_diff != 0) {
        return type_diff;
    }

    return memcmp(a->val, b->val, sizeof(a->val));
}

#ifdef __cplusplus
}
#endif

#endif /* H_BLE_ */

