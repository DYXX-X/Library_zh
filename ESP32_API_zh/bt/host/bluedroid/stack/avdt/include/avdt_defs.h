/******************************************************************************
 * 版权所有（C）2002-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 其中包含AVDTP规范中的常量定义和其他信息。此文件仅供AVDT内部使用。
 *
 ******************************************************************************/
#ifndef AVDT_DEFS_H
#define AVDT_DEFS_H
#include "common/bt_target.h"

#if (AVDT_INCLUDED == TRUE)

/*****************************************************************************
** 常量
*****************************************************************************/

/* 信令分组类型*/
#define AVDT_PKT_TYPE_SINGLE        0       /* 单个数据包*/
#define AVDT_PKT_TYPE_START         1       /* 起始数据包*/
#define AVDT_PKT_TYPE_CONT          2       /* 继续数据包*/
#define AVDT_PKT_TYPE_END           3       /* 结束数据包*/

/* 信令消息类型*/
#define AVDT_MSG_TYPE_CMD           0       /* 命令*/
#define AVDT_MSG_TYPE_GRJ           1       /* 一般拒收*/
#define AVDT_MSG_TYPE_RSP           2       /* 响应接受*/
#define AVDT_MSG_TYPE_REJ           3       /* 响应拒绝*/

/* 信令消息*/
#define AVDT_SIG_DISCOVER           1       /* 发现*/
#define AVDT_SIG_GETCAP             2       /* 获取功能*/
#define AVDT_SIG_SETCONFIG          3       /* 集合配置*/
#define AVDT_SIG_GETCONFIG          4       /* 获取配置*/
#define AVDT_SIG_RECONFIG           5       /* 重新配置*/
#define AVDT_SIG_OPEN               6       /* 打开*/
#define AVDT_SIG_START              7       /* 开始*/
#define AVDT_SIG_CLOSE              8       /* 关*/
#define AVDT_SIG_SUSPEND            9       /* 悬*/
#define AVDT_SIG_ABORT              10      /* 中止*/
#define AVDT_SIG_SECURITY           11      /* 安全控制*/
#define AVDT_SIG_GET_ALLCAP         12      /* 获取所有功能*/
#define AVDT_SIG_DELAY_RPT          13      /* 延误报告*/

/* 最大信号值*/
#define AVDT_SIG_MAX                AVDT_SIG_DELAY_RPT

/* 用于一般拒收*/
#define AVDT_SIG_NONE               0

/* 信令消息的一些最大和最小大小*/
#define AVDT_DISCOVER_REQ_MIN       1
#define AVDT_DISCOVER_REQ_MAX       124

/* 服务类别信息元素字段值*/
#define AVDT_CAT_TRANS              1       /* 媒体传输*/
#define AVDT_CAT_REPORT             2       /* 报告*/
#define AVDT_CAT_RECOV              3       /* 恢复*/
#define AVDT_CAT_PROTECT            4       /* 内容保护*/
#define AVDT_CAT_HDRCMP             5       /* 收割台压缩*/
#define AVDT_CAT_MUX                6       /* 多路复用*/
#define AVDT_CAT_CODEC              7       /* 媒体编解码器*/
#define AVDT_CAT_DELAY_RPT          8       /* 延迟报告*/
#define AVDT_CAT_MAX_CUR            AVDT_CAT_DELAY_RPT

/* 服务类别信息元素的最小/最大长度*/
#define AVDT_LEN_TRANS_MIN          0
#define AVDT_LEN_REPORT_MIN         0
#define AVDT_LEN_RECOV_MIN          3
#define AVDT_LEN_PROTECT_MIN        2
#define AVDT_LEN_HDRCMP_MIN         1
#define AVDT_LEN_MUX_MIN            3
#define AVDT_LEN_CODEC_MIN          2
#define AVDT_LEN_DELAY_RPT_MIN      0

#define AVDT_LEN_TRANS_MAX          0
#define AVDT_LEN_REPORT_MAX         0
#define AVDT_LEN_RECOV_MAX          3
#define AVDT_LEN_PROTECT_MAX        255
#define AVDT_LEN_HDRCMP_MAX         1
#define AVDT_LEN_MUX_MAX            7
#define AVDT_LEN_CODEC_MAX          255
#define AVDT_LEN_DELAY_RPT_MAX      0

/* 配置或能力数据的最小可能大小*/
#define AVDT_LEN_CFG_MIN            2

/* 不同消息类型的最小和最大长度*/
#define AVDT_LEN_SINGLE             1
#define AVDT_LEN_SETCONFIG_MIN      2
#define AVDT_LEN_RECONFIG_MIN       1
#define AVDT_LEN_MULTI_MIN          1
#define AVDT_LEN_SECURITY_MIN       1
#define AVDT_LEN_DELAY_RPT          3

/* 不同数据包类型的报头长度*/
#define AVDT_LEN_TYPE_SINGLE        2       /* 单个数据包*/
#define AVDT_LEN_TYPE_START         3       /* 起始数据包*/
#define AVDT_LEN_TYPE_CONT          1       /* 继续数据包*/
#define AVDT_LEN_TYPE_END           1       /* 结束数据包*/

/* 一般拒绝消息的长度*/
#define AVDT_LEN_GEN_REJ            2

/* 恢复服务功能信息元素*/
#define AVDT_RECOV_MRWS_MIN         0x01    /* 最大恢复窗口的最小值*/
#define AVDT_RECOV_MRWS_MAX         0x18    /* 最大恢复窗口的最大值*/
#define AVDT_RECOV_MNMP_MIN         0x01    /* 最大媒体数据包数的最小值*/
#define AVDT_RECOV_MNMP_MAX         0x18    /* 最大媒体数据包数的最大值*/

/* SEID值范围*/
#define AVDT_SEID_MIN               0x01
#define AVDT_SEID_MAX               0x3E

/* 媒体包头的第一个字节*/
#define AVDT_MEDIA_OCTET1           0x80

/* 用于自适应层标头*/
#define AVDT_ALH_LCODE_MASK     0x03    /* 长度字段编码*/
#define AVDT_ALH_LCODE_NONE     0x00    /* 不存在长度字段。取l2cap的长度*/
#define AVDT_ALH_LCODE_16BIT    0x01    /* 16位长度字段*/
#define AVDT_ALH_LCODE_9BITM0   0x02    /* 9位长度字段，MSB=0，1个八位字节中有8个LSB*/
#define AVDT_ALH_LCODE_9BITM1   0x03    /* 9位长度字段，MSB=1，1个八位字节中有8个LSB*/

#define AVDT_ALH_FRAG_MASK      0x04    /* 将此设置为延续数据包*/

/*****************************************************************************
** 消息分析和生成宏
*****************************************************************************/

#define AVDT_MSG_PRS_HDR(p, lbl, pkt, msg) \
    lbl = *(p) >> 4; \
    pkt = (*(p) >> 2) & 0x03; \
    msg = *(p)++ & 0x03;

#define AVDT_MSG_PRS_DISC(p, seid, in_use, type, tsep) \
    seid = *(p) >> 2; \
    in_use = (*(p)++ >> 1) & 0x01; \
    type = *(p) >> 4; \
    tsep = (*(p)++ >> 3) & 0x01;

#define AVDT_MSG_PRS_SIG(p, sig) \
    sig = *(p)++ & 0x3F;

#define AVDT_MSG_PRS_SEID(p, seid) \
    seid = *(p)++ >> 2;

#define AVDT_MSG_PRS_PKT_TYPE(p, pkt) \
    pkt = (*(p) >> 2) & 0x03;

#define AVDT_MSG_PRS_OCTET1(p, o_v, o_p, o_x, o_cc) \
    o_v = *(p) >> 6; \
    o_p = (*(p) >> 5) & 0x01; \
    o_x = (*(p) >> 4) & 0x01; \
    o_cc = *(p)++ & 0x0F;

#define AVDT_MSG_PRS_RPT_OCTET1(p, o_v, o_p, o_cc) \
    o_v = *(p) >> 6; \
    o_p = (*(p) >> 5) & 0x01; \
    o_cc = *(p)++ & 0x1F;

#define AVDT_MSG_PRS_M_PT(p, m_pt, marker) \
    marker = *(p) >> 7; \
    m_pt = *(p)++ & 0x7F;

#define AVDT_MSG_BLD_HDR(p, lbl, pkt, msg) \
    *(p)++ = (UINT8) ((lbl) << 4) | ((pkt) << 2) | (msg);

#define AVDT_MSG_BLD_DISC(p, seid, in_use, type, tsep) \
    *(p)++ = (UINT8) (((seid) << 2) | ((in_use) << 1)); \
    *(p)++ = (UINT8) (((type) << 4) | ((tsep) << 3));

#define AVDT_MSG_BLD_SIG(p, sig) \
    *(p)++ = (UINT8) (sig);

#define AVDT_MSG_BLD_SEID(p, seid) \
    *(p)++ = (UINT8) ((seid) << 2);

#define AVDT_MSG_BLD_ERR(p, err) \
    *(p)++ = (UINT8) (err);

#define AVDT_MSG_BLD_PARAM(p, param) \
    *(p)++ = (UINT8) (param);

#define AVDT_MSG_BLD_NOSP(p, nosp) \
    *(p)++ = (UINT8) (nosp);

#endif  ///AVRC_INCLUDED == TRUE

#endif /* AVDT_DEFS_H */

