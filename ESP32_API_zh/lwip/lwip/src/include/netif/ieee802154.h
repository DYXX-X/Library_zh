/**
 * @file IEEE 802.15.4 MAC帧的定义
 */

/*
 * 版权所有（c）2018 Simon Goldschmidt。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Simon Goldschmidt<goldsimon@gmx.de>
 *
 */
#ifndef LWIP_HDR_NETIF_IEEE802154_H
#define LWIP_HDR_NETIF_IEEE802154_H

#include "lwip/opt.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/bpstruct.h"
#endif
PACK_STRUCT_BEGIN
/** 通用MAC帧格式这显示了全功能标头，主要用于文档。一些字段被省略或缩短以实现帧压缩。
 */
struct ieee_802154_hdr {
  /**参见IEEE_802154_FC_*定义*/
  PACK_STRUCT_FIELD(u16_t frame_control);
  /**如果在frame_control中设置了IEEE_802154_FC_SEQNO_SUPPR，则省略序列号*/
  PACK_STRUCT_FLD_8(u8_t  sequence_number);
  /**如果目标寻址模式为0，则省略目标PAN ID*/
  PACK_STRUCT_FIELD(u16_t destination_pan_id);
  /**如果目标寻址模式为0，则省略目标地址*/
  PACK_STRUCT_FLD_8(u8_t destination_address[8]);
  /**如果源寻址模式为0或在帧控制中设置了IEEE_802154_FC_PANID_COMPR，则忽略源PAN ID*/
  PACK_STRUCT_FIELD(u16_t source_pan_id);
  /**如果源寻址模式为0，则忽略源地址*/
  PACK_STRUCT_FLD_8(u8_t source_address[8]);
  /* 其余的是可变的*/
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/epstruct.h"
#endif

/* 寻址模式（2位）*/
#define IEEE_802154_ADDR_MODE_NO_ADDR   0x00 /* PAN ID和地址字段不存在*/
#define IEEE_802154_ADDR_MODE_RESERVED  0x01 /* 保留*/
#define IEEE_802154_ADDR_MODE_SHORT     0x02 /* 地址字段包含短地址（16位）*/
#define IEEE_802154_ADDR_MODE_EXT       0x03 /* 地址字段包含扩展地址（64位）*/

/* IEEE 802.15.4帧控制定义（2字节；参见IEEE 802.15.4-2015 ch.7.2.1）*/
#define IEEE_802154_FC_FT_MASK             0x0007 /* 位0..2：帧类型*/
#define IEEE_802154_FC_FT_BEACON               0x00
#define IEEE_802154_FC_FT_DATA                 0x01
#define IEEE_802154_FC_FT_ACK                  0x02
#define IEEE_802154_FC_FT_MAC_CMD              0x03
#define IEEE_802154_FC_FT_RESERVED             0x04
#define IEEE_802154_FC_FT_MULTIPURPOSE         0x05
#define IEEE_802154_FC_FT_FRAG                 0x06
#define IEEE_802154_FC_FT_EXT                  0x07
#define IEEE_802154_FC_SEC_EN              0x0008 /* bit 3：安全启用*/
#define IEEE_802154_FC_FRAME_PEND          0x0010 /* 位4：帧挂起*/
#define IEEE_802154_FC_ACK_REQ             0x0020 /* 第5位：AR（需要ACK）*/
#define IEEE_802154_FC_PANID_COMPR         0x0040 /* bit 6:PAN ID压缩（src和dst相等，省略src PAN ID）*/
#define IEEE_802154_FC_RESERVED            0x0080
#define IEEE_802154_FC_SEQNO_SUPPR         0x0100 /* bit 8：序列号抑制*/
#define IEEE_802154_FC_IE_PRESENT          0x0200 /* 位9:IE存在*/
#define IEEE_802154_FC_DST_ADDR_MODE_MASK  0x0c00 /* 位10..11：目标寻址模式*/
#define IEEE_802154_FC_DST_ADDR_MODE_NO_ADDR   (IEEE_802154_ADDR_MODE_NO_ADDR << 10)
#define IEEE_802154_FC_DST_ADDR_MODE_SHORT     (IEEE_802154_ADDR_MODE_SHORT << 10)
#define IEEE_802154_FC_DST_ADDR_MODE_EXT       (IEEE_802154_ADDR_MODE_EXT << 10)
#define IEEE_802154_FC_FRAME_VERSION_MASK  0x3000 /* 位12..13：帧版本*/
#define IEEE_802154_FC_FRAME_VERSION_GET(x)    (((x) & IEEE_802154_FC_FRAME_VERSION_MASK) >> 12)
#define IEEE_802154_FC_SRC_ADDR_MODE_MASK  0xc000 /* 位14..15：源寻址模式*/
#define IEEE_802154_FC_SRC_ADDR_MODE_SHORT     (IEEE_802154_ADDR_MODE_SHORT << 14)
#define IEEE_802154_FC_SRC_ADDR_MODE_EXT       (IEEE_802154_ADDR_MODE_EXT << 14)

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_NETIF_IEEE802154_H */

