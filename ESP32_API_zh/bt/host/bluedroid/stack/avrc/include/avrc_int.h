/******************************************************************************
 * 版权所有（C）2003-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * VRCP内部头文件。
 *
 ******************************************************************************/


#ifndef AVRC_INT_H
#define AVRC_INT_H

#include "avct_defs.h"
#include "stack/avrc_api.h"

#if (AVRC_INCLUDED == TRUE)
/*      DEBUG FLAGS
 *
 * #定义META_DEBUG_ENABLED
 */
/*****************************************************************************
**  常量
*****************************************************************************/

/* AVRC SDP记录中的属性数。*/
#define AVRC_NUM_ATTR            6

/* 协议元素列表中的协议元素数。*/
#define AVRC_NUM_PROTO_ELEMS     2

#ifndef AVRC_MIN_CMD_LEN
#define AVRC_MIN_CMD_LEN    20
#endif

#define AVRC_UNIT_OPRND_BYTES   5
#define AVRC_SUB_OPRND_BYTES    4
#define AVRC_SUBRSP_OPRND_BYTES 3
#define AVRC_SUB_PAGE_MASK      7
#define AVRC_SUB_PAGE_SHIFT     4
#define AVRC_SUB_EXT_CODE       7
#define AVRC_PASS_OP_ID_MASK    0x7F
#define AVRC_PASS_STATE_MASK    0x80
#define AVRC_CMD_OPRND_PAD      0xFF

#define AVRC_CTYPE_MASK         0x0F
#define AVRC_SUBTYPE_MASK       0xF8
#define AVRC_SUBTYPE_SHIFT      3
#define AVRC_SUBID_MASK         0x07
#define AVRC_SUBID_IGNORE       0x07

#define AVRC_SINGLE_PARAM_SIZE      1
#define AVRC_METADATA_PKT_TYPE_MASK 0x03
#define AVRC_PASS_THOUGH_MSG_MASK   0x80           /* msg_type的MSB表示PAS通过消息*/
#define AVRC_VENDOR_UNIQUE_MASK     0x70           /* 供应商唯一id*/


/* 公司ID是24位整数。我们不能在stack/bt_types中使用宏。小时*/
#define AVRC_CO_ID_TO_BE_STREAM(p, u32) {*(p)++ = (UINT8)((u32) >> 16); *(p)++ = (UINT8)((u32) >> 8); *(p)++ = (UINT8)(u32); }
#define AVRC_BE_STREAM_TO_CO_ID(u32, p) {u32 = (((UINT32)(*((p) + 2))) + (((UINT32)(*((p) + 1))) << 8) + (((UINT32)(*(p))) << 16)); (p) += 3;}

#define AVRC_AVC_HDR_SIZE           3   /* ctype，子单元*，操作码*/

#define AVRC_MIN_META_HDR_SIZE      4   /* pdu id（1）、数据包类型（1）和参数len（2）*/
#define AVRC_MIN_BROWSE_HDR_SIZE    3   /* pdu id（1），参数len（2）*/

#define AVRC_VENDOR_HDR_SIZE        6   /* ctype，子单元*，操作码，CO_ID*/
#define AVRC_MSG_VENDOR_OFFSET      23
#define AVRC_MIN_VENDOR_SIZE        (AVRC_MSG_VENDOR_OFFSET + BT_HDR_SIZE + AVRC_MIN_META_HDR_SIZE)

#define AVRC_PASS_THRU_SIZE         8
#define AVRC_MSG_PASS_THRU_OFFSET   25
#define AVRC_MIN_PASS_THRU_SIZE     (AVRC_MSG_PASS_THRU_OFFSET + BT_HDR_SIZE + 4)

#define AVRC_MIN_BROWSE_SIZE        (AVCT_BROWSE_OFFSET + BT_HDR_SIZE + AVRC_MIN_BROWSE_HDR_SIZE)

#define AVRC_CTRL_PKT_LEN(pf, pk)   {pf = (UINT8 *)((pk) + 1) + (pk)->offset + 2;}

#define AVRC_MAX_CTRL_DATA_LEN      (AVRC_PACKET_LEN)

/*****************************************************************************
**  类型定义
*****************************************************************************/

#if (AVRC_METADATA_INCLUDED == TRUE)
/* 元数据碎片控制块的类型*/
typedef struct {
    BT_HDR              *p_fmsg;        /* 支离破碎的消息*/
    UINT8               frag_pdu;       /* 用于分段的PDU ID*/
    BOOLEAN             frag_enabled;   /* 碎片标志*/
} tAVRC_FRAG_CB;

/* 元数据重新汇编控制块的类型*/
typedef struct {
    BT_HDR              *p_rmsg;        /* 收到的消息*/
    UINT16              rasm_offset;    /* 重新组装标志，开始片段的偏移量*/
    UINT8               rasm_pdu;       /* 用于重新组装的PDU ID*/
} tAVRC_RASM_CB;
#endif

typedef struct {
    tAVRC_CONN_CB       ccb[AVCT_NUM_CONN];
#if (AVRC_METADATA_INCLUDED == TRUE)
    tAVRC_FRAG_CB       fcb[AVCT_NUM_CONN];
    tAVRC_RASM_CB       rcb[AVCT_NUM_CONN];
#endif
    tAVRC_FIND_CBACK    *p_cback;       /* 指向应用程序回调的指针*/
    tSDP_DISCOVERY_DB   *p_db;          /* 指向发现数据库的指针*/
    UINT16              service_uuid;   /* 要搜索的服务UUID*/
    UINT8               trace_level;
} tAVRC_CB;



#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
** 主控制块
*******************************************************************************/
#if AVRC_DYNAMIC_MEMORY == FALSE
extern tAVRC_CB  avrc_cb;
#else
extern tAVRC_CB *avrc_cb_ptr;
#define avrc_cb (*avrc_cb_ptr)
#endif

extern BOOLEAN avrc_is_valid_pdu_id(UINT8 pdu_id);
extern BOOLEAN avrc_is_valid_player_attrib_value(UINT8 attrib, UINT8 value);
extern BT_HDR *avrc_alloc_ctrl_pkt (UINT8 pdu);
extern tAVRC_STS avrc_pars_pass_thru(tAVRC_MSG_PASS *p_msg, UINT16 *p_vendor_unique_id);
extern UINT8 avrc_opcode_from_pdu(UINT8 pdu);
extern BOOLEAN avrc_is_valid_opcode(UINT8 opcode);

#ifdef __cplusplus
}
#endif

#endif  ///AVRC_INCLUDED == TRUE

#endif /* AVRC_INT_H */

