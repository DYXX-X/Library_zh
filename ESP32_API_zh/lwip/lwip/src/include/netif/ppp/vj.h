/*
 * tcp压缩例程的定义。
 *
 * $Id:vj.h，v 1.7 2010/02/22 17:52:09 goldsimon Exp$
 *
 * 版权所有（c）1989加利福尼亚大学校长。保留所有权利。
 *
 * 允许以源代码和二进制形式重新分发和使用，前提是上述版权声明和本段以所有此类形式复制，并且与此类分发和使用相关的任何文档、广告材料和其他材料均承认该软件由加州大学伯克利分校开发。未经事先书面许可，不得使用大学的名称为本软件衍生的产品背书或推广。本软件按“原样”提供，没有任何明示或暗示的保证，包括但不限于对适销性和特定用途适用性的暗示保证。
 *
 * Van Jacobson (van@helios.ee.lbl.gov), 1989年12月31日：
 * -初始分配。
 */

#include "netif/ppp/ppp_opts.h"
#if PPP_SUPPORT && VJ_SUPPORT /* 如果未配置为在lwipopts.h中使用，则不要构建*/

#ifndef VJ_H
#define VJ_H

#include "lwip/ip.h"
#include "lwip/priv/tcp_priv.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_SLOTS 16 /* 必须大于2且小于256*/
#define MAX_HDR   128

/*
 * 压缩数据包格式：
 *
 * 第一个八位位组包含数据包类型（前3位）、TCP“推送”位以及指示4个TCP序列号中哪一个已更改的标志（后5位）。下一个八位字节是将保存的IP/TCP报头与压缩数据包相关联的会话编号。接下来的两个八位字节是来自原始数据报的TCP校验和。接下来的0到15个八位字节是序列号变化，在报头中每设置一个比特就发生一次变化（可能没有变化，并且有两种特殊情况下，接收机隐式地知道发生了什么变化——见下文）。
 *
 * 有5个数字可以更改（它们总是按以下顺序插入）：TCP紧急指针、窗口、确认、序列号和IP ID，更改使用可变长度编码，范围为1-255的数字使用一个八位字节，范围为256-6555或0的数字使用3个八位（0，MSB，LSB）。（如果序列号或ack的更改大于65535，则发送未压缩的数据包。）
 */

/*
 * 数据包类型（不得与IP协议版本冲突）
 *
 * 第一个八位字节的顶部半字节是分组类型。有三种可能的类型：IP（不是设置了控制标志之一的protoTCP或TCP）；未压缩的TCP（一个正常的IP/TCP数据包，但8位协议字段被8位连接id替换——这种类型的数据包使发送方和接收方同步）；以及压缩TCP（如上所述）。
 *
 * 4位字段的LSB是TCP“PUSH”位（一个毫无价值的时间错误），在逻辑上是随后的4位“changes”字段的一部分。前三位是实际的数据包类型。为了向后兼容并为了保存比特，选择了数字，因此通常出现在该半字节中的IP协议版本号（4）表示“IP包”。
 */

/* 数据包类型*/
#define TYPE_IP               0x40
#define TYPE_UNCOMPRESSED_TCP 0x70
#define TYPE_COMPRESSED_TCP   0x80
#define TYPE_ERROR            0x00

/* 压缩数据包的第一个八位字节中的位*/
#define NEW_C 0x40 /* 数据包中更改内容的标志位*/
#define NEW_I 0x20
#define NEW_S 0x08
#define NEW_A 0x04
#define NEW_W 0x02
#define NEW_U 0x01

/* 保留，以上的特殊情况值*/
#define SPECIAL_I (NEW_S|NEW_W|NEW_U) /* 回声交互交通*/
#define SPECIAL_D (NEW_S|NEW_A|NEW_W|NEW_U) /* 单向数据*/
#define SPECIALS_MASK (NEW_S|NEW_A|NEW_W|NEW_U)

#define TCP_PUSH_BIT 0x10


/*
 * 在线上每个活动tcp会话的“状态”数据。这基本上是我们从对话中看到的最后一个数据包中的整个IP/TCP报头的副本，以及线路的发送和接收端用来定位保存的报头的小标识符。
 */
struct cstate {
  struct cstate *cs_next; /* 下一个最近使用的状态（仅限xmit）*/
  u16_t cs_hlen;        /* hdr大小（仅接收）*/
  u8_t cs_id;           /* 与此状态关联的连接#*/
  u8_t cs_filler;
  union {
    char csu_hdr[MAX_HDR];
    struct ip_hdr csu_ip;     /* 来自最新数据包的ip/tcp-hdr*/
  } vjcs_u;
};
#define cs_ip vjcs_u.csu_ip
#define cs_hdr vjcs_u.csu_hdr


struct vjstat {
  u32_t vjs_packets;        /* 出站数据包*/
  u32_t vjs_compressed;     /* 出站压缩数据包*/
  u32_t vjs_searches;       /* 搜索连接状态*/
  u32_t vjs_misses;         /* 时报找不到康涅狄格州*/
  u32_t vjs_uncompressedin; /* 入站未压缩数据包*/
  u32_t vjs_compressedin;   /* 入站压缩数据包*/
  u32_t vjs_errorin;        /* 入站未知类型数据包*/
  u32_t vjs_tossed;         /* 由于错误而丢弃的入站数据包*/
};

/*
 * 一条串行线的所有状态数据（每行需要一个）。
 */
struct vjcompress {
  struct cstate *last_cs;          /* 最近使用的tstate*/
  u8_t last_recv;                /* 最后一个rcvd连接id*/
  u8_t last_xmit;                /* 上次发送的连接id*/
  u16_t flags;
  u8_t maxSlotIndex;
  u8_t compressSlot;             /* 指示确定压缩插槽ID的标志。*/
#if LINK_STATS
  struct vjstat stats;
#endif
  struct cstate tstate[MAX_SLOTS]; /* xmit连接状态*/
  struct cstate rstate[MAX_SLOTS]; /* 接收连接状态*/
};

/* 标志值*/
#define VJF_TOSS 1U /* 由于输入错误而丢弃rcvd帧*/

extern void  vj_compress_init    (struct vjcompress *comp);
extern u8_t  vj_compress_tcp     (struct vjcompress *comp, struct pbuf **pb);
extern void  vj_uncompress_err   (struct vjcompress *comp);
extern int   vj_uncompress_uncomp(struct pbuf *nb, struct vjcompress *comp);
extern int   vj_uncompress_tcp   (struct pbuf **nb, struct vjcompress *comp);

#ifdef __cplusplus
}
#endif

#endif /* VJ_H */

#endif /* PPP_SUPPORT && VJ_SUPPORT */

