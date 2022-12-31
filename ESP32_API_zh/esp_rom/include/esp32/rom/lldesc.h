// 版权所有2010-2016 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef _ROM_LLDESC_H_
#define _ROM_LLDESC_H_

#include <stdint.h>

#include "sys/queue.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LLDESC_TX_MBLK_SIZE                 268 /* */
#define LLDESC_RX_SMBLK_SIZE                64  /* 小块大小，用于小型mgmt框架*/
#define LLDESC_RX_MBLK_SIZE                 524 /* rx是大的sinec，我们希望在一个块中包含mgmt帧*/
#define LLDESC_RX_AMPDU_ENTRY_MBLK_SIZE    64  /* 它是一个小缓冲区，是一个循环链接*/
#define LLDESC_RX_AMPDU_LEN_MBLK_SIZE      256 /*用于ampdu条目*/
#ifdef ESP_MAC_5
#define LLDESC_TX_MBLK_NUM                  116  /* 64K / 256 */
#define LLDESC_RX_MBLK_NUM                  82 /* 64K / 512 MAX 172*/
#define LLDESC_RX_AMPDU_ENTRY_MBLK_NUM     4
#define LLDESC_RX_AMPDU_LEN_MLBK_NUM       12
#else
#ifdef SBUF_RXTX
#define LLDESC_TX_MBLK_NUM_MAX    (2 * 48) /* 23K / 260 - 8 */
#define LLDESC_RX_MBLK_NUM_MAX    (2 * 48) /* 23K / 524 */
#define LLDESC_TX_MBLK_NUM_MIN    (2 * 16) /* 23K / 260 - 8 */
#define LLDESC_RX_MBLK_NUM_MIN    (2 * 16) /* 23K / 524 */
#endif
#define LLDESC_TX_MBLK_NUM      10      //(2 * 32) /* 23K / 260 - 8 */

#ifdef IEEE80211_RX_AMPDU
#define LLDESC_RX_MBLK_NUM      30
#else
#define LLDESC_RX_MBLK_NUM      10
#endif /*IEEE80211_RX_AMPDU*/

#define LLDESC_RX_AMPDU_ENTRY_MBLK_NUM  4
#define LLDESC_RX_AMPDU_LEN_MLBK_NUM    8
#endif /* !ESP_MAC_5 */
/*
 *  SLC2 DMA描述结构，又名lldesc_t
 *
 * --------------------------------------------------------------|own|EoF|sub_sof|5'b0|长度[11:0]|大小[11:0]|
 * --------------------------------------------------------------|buf_ptr[31:0]|
 * --------------------------------------------------------------| next_desc_ptr[31:0]|
 * --------------------------------------------------------------
 */

/* 此位字段从LSB开始！！！*/
typedef struct lldesc_s {
    volatile uint32_t size  :12,
                        length:12,
                        offset: 5, /* h/w保留5位，s/w将其用作缓冲区中的偏移量*/
                        sosf  : 1, /* 子帧开始*/
                        eof   : 1, /* 框架末端*/
                        owner : 1; /* 硬件或软件*/
    volatile uint8_t *buf;       /* 指向缓冲区数据*/
    union{
        volatile uint32_t empty;
        STAILQ_ENTRY(lldesc_s) qe;  /* 指向下一个desc*/
    };
} lldesc_t;

typedef struct tx_ampdu_entry_s{
    uint32_t sub_len  :12,
              dili_num : 7,
                       : 1,
              null_byte: 2,
              data     : 1,
              enc      : 1,
              seq      : 8;
} tx_ampdu_entry_t;

typedef struct lldesc_chain_s {
    lldesc_t *head;
    lldesc_t *tail;
} lldesc_chain_t;

#ifdef SBUF_RXTX
enum sbuf_mask_s  {
    SBUF_MOVE_NO = 0,
    SBUF_MOVE_TX2RX,
    SBUF_MOVE_RX2TX,
} ;

#define SBUF_MOVE_STEP 8
#endif
#define LLDESC_SIZE  sizeof(struct lldesc_s)

/* SLC描述符*/
#define LLDESC_OWNER_MASK                  0x80000000
#define LLDESC_OWNER_SHIFT                         31
#define LLDESC_SW_OWNED                             0
#define LLDESC_HW_OWNED                             1

#define LLDESC_EOF_MASK                    0x40000000
#define LLDESC_EOF_SHIFT                           30

#define LLDESC_SOSF_MASK                   0x20000000
#define LLDESC_SOSF_SHIFT                          29

#define LLDESC_LENGTH_MASK                 0x00fff000
#define LLDESC_LENGTH_SHIFT                        12

#define LLDESC_SIZE_MASK                   0x00000fff
#define LLDESC_SIZE_SHIFT                           0

#define LLDESC_ADDR_MASK                    0x000fffff

void lldesc_build_chain(uint8_t *descptr, uint32_t desclen, uint8_t * mblkptr, uint32_t buflen, uint32_t blksz, uint8_t owner,
                          lldesc_t **head,
#ifdef TO_HOST_RESTART
                          lldesc_t ** one_before_tail,
#endif
                          lldesc_t **tail);

lldesc_t *lldesc_num2link(lldesc_t * head, uint16_t nblks);

lldesc_t *lldesc_set_owner(lldesc_t * head, uint16_t nblks, uint8_t owner);

static inline uint32_t lldesc_get_chain_length(lldesc_t *head)
{
    lldesc_t *ds = head;
    uint32_t len = 0;

    while (ds) {
        len += ds->length;
        ds = STAILQ_NEXT(ds, qe);
    }

    return len;
}

static inline void lldesc_config(lldesc_t *ds, uint8_t owner, uint8_t eof, uint8_t sosf, uint16_t len)
{
    ds->owner  = owner;
    ds->eof    = eof;
    ds->sosf   = sosf;
    ds->length = len;
}

#define LLDESC_CONFIG(_desc, _owner, _eof, _sosf, _len)        do { \
        (_desc)->owner  = (_owner); \
        (_desc)->eof    = (_eof);   \
        (_desc)->sosf   = (_sosf);  \
        (_desc)->length = (_len);   \
} while(0)

#define LLDESC_FROM_HOST_CLEANUP(ds) LLDESC_CONFIG((ds), LLDESC_HW_OWNED, 0, 0, 0)

#define LLDESC_MAC_RX_CLEANUP(ds) LLDESC_CONFIG((ds), LLDESC_HW_OWNED, 0, 0, (ds)->size)

#define LLDESC_TO_HOST_CLEANUP(ds) LLDESC_CONFIG((ds), LLDESC_HW_OWNED, 0, 0, 0)

#ifdef __cplusplus
}
#endif

#endif /* _ROM_LLDESC_H_ */

