/**
 * @file pbuf API
 */

/*
 * 版权所有（c）2001-2004瑞典计算机科学研究所。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Adam Dunkels<adam@sics.se>
 *
 */

#ifndef LWIP_HDR_PBUF_H
#define LWIP_HDR_PBUF_H

#include "lwip/opt.h"
#include "lwip/err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**LWIP_SUPPORT_CUSTOM_PBUF==1：自定义PBUF的行为与它们的PBUF类型非常相似，但它们是由外部代码分配的（通过调用PBUF_alloced_CUSTOM（）初始化），当PBUF_free放弃最后一个引用时，通过调用PBUF_CUSTOM->CUSTOM_free_function（）释放它们。目前，除非外部驱动程序/应用程序代码需要，否则仅IP_FRAG的一个特定配置需要pbuf_custom代码。*/
#ifndef LWIP_SUPPORT_CUSTOM_PBUF
#define LWIP_SUPPORT_CUSTOM_PBUF ((IP_FRAG && !LWIP_NETIF_TX_SINGLE_PBUF) || (LWIP_IPV6 && LWIP_IPV6_FRAG))
#endif

/**@ingroup pbuf pbuf_NEEDS_COPY（p）：返回一个布尔值，该值指示是否需要复制给定的pbuf，以便将其保留在当前调用堆栈之外，而不会有损坏的风险。默认设置提供了安全性：它将复制不完全由pbuf_ROM类型pbufs组成的任何pbuf链。例如，对于具有零拷贝支持的设置，它可以被重新定义为在所有情况下都为真。然而，这样做也会对应用程序端产生影响：任何未复制的缓冲区在传递到lwIP后也不能被应用程序重用。例如，当将PBUF_NEEDS_COPY设置为（0）时，在将udp_send（）与PBUF_RAM PBUF一起使用后，应用程序必须立即释放PBUF，而不是将其重新用于其他目的。有关这方面的更多背景信息，请参阅任务#6735和#7896，以及错误#11400和#49914。*/
#ifndef PBUF_NEEDS_COPY
#define PBUF_NEEDS_COPY(p)  ((p)->type_internal & PBUF_TYPE_FLAG_DATA_VOLATILE)
#endif /* PBUF_NEEDS_COPY */

/* @todo：我们需要一种机制来防止在每个pbuf中浪费内存（TCP与UDP、IPv4与IPv6：UDP/IPv4数据包可能会浪费多达28个字节）*/

#define PBUF_TRANSPORT_HLEN 20
#if LWIP_IPV6
#define PBUF_IP_HLEN        40
#else
#define PBUF_IP_HLEN        20
#endif

/**
 * @ingroup pbuf层的枚举
 */
typedef enum {
  /** 包括传输层报头（例如UDP报头）的备用空间。如果要将pbuf传递给udp_send（）等函数，请使用此选项。
   */
  PBUF_TRANSPORT = PBUF_LINK_ENCAPSULATION_HLEN + PBUF_LINK_HLEN + PBUF_IP_HLEN + PBUF_TRANSPORT_HLEN,
  /** 包括IP总管的备用空间。如果要将pbuf传递给raw_send（）等函数，请使用此选项。
   */
  PBUF_IP = PBUF_LINK_ENCAPSULATION_HLEN + PBUF_LINK_HLEN + PBUF_IP_HLEN,
  /** 包括链路层报头（以太网报头）的备用空间。如果要将pbuf传递给ethernet_output（）等函数，请使用此选项。
   * @see PBUF_LINK_HLEN
   */
  PBUF_LINK = PBUF_LINK_ENCAPSULATION_HLEN + PBUF_LINK_HLEN,
  /** 在以太网报头（例如802.11）之前包括额外封装报头的备用空间。如果要将pbuf传递给netif->linkoutput（）等函数，请使用此选项。
   * @see PBUF_LINK_ENCAPSULATION_HLEN
   */
  PBUF_RAW_TX = PBUF_LINK_ENCAPSULATION_HLEN,
  /**当在最常见的情况下调用netif->input（）时，请将此用于netif驱动程序中的输入数据包-以太网层netif驱动。*/
  PBUF_RAW = 0
} pbuf_layer;


/* pbuf_type定义的基本标志：*/

/**指示有效负载直接跟随结构pbuf。这使得@ref pbuf_header可以双向工作。*/
#define PBUF_TYPE_FLAG_STRUCT_DATA_CONTIGUOUS       0x80
/**指示存储在此pbuf中的数据可以更改。如果此pbuf需要排队，则必须复制/复制它。*/
#define PBUF_TYPE_FLAG_DATA_VOLATILE                0x40
/**为16个分配源（例如，堆、池1、池2等）保留了4个位。在内部，我们使用：0=heap，1=MEMP_PBUF，2=MEMP_PBUF_POOL->13个类型空闲*/
#define PBUF_TYPE_ALLOC_SRC_MASK                    0x0F
/**表示此pbuf用于RX（如果未设置，则表示用于TX）。该信息可用于保留一些备用RX缓冲区，例如用于接收TCP ACK以解除连接）*/
#define PBUF_ALLOC_FLAG_RX                          0x0100
/**指示应用程序需要pbuf有效负载为一体*/
#define PBUF_ALLOC_FLAG_DATA_CONTIGUOUS             0x0200

#define PBUF_TYPE_ALLOC_SRC_MASK_STD_HEAP           0x00
#define PBUF_TYPE_ALLOC_SRC_MASK_STD_MEMP_PBUF      0x01
#define PBUF_TYPE_ALLOC_SRC_MASK_STD_MEMP_PBUF_POOL 0x02
/**应用程序的第一个pbuf分配类型*/
#define PBUF_TYPE_ALLOC_SRC_MASK_APP_MIN            0x03
/**应用程序的最后一个pbuf分配类型*/
#define PBUF_TYPE_ALLOC_SRC_MASK_APP_MAX            PBUF_TYPE_ALLOC_SRC_MASK

/**
 * @ingroup pbuf pbuf类型的枚举
 */
typedef enum {
  /**pbuf数据存储在RAM中，主要用于TX，结构pbuf及其有效载荷分配在一块连续内存中（因此第一个有效载荷字节可以从结构pbuf）。pbuf_alloc（）将pbuf_RAM pbufs分配为未约束的pbufs（尽管在将来的版本中可能会改变）。这应用于所有输出数据包（TX）。*/
  PBUF_RAM = (PBUF_ALLOC_FLAG_DATA_CONTIGUOUS | PBUF_TYPE_FLAG_STRUCT_DATA_CONTIGUOUS | PBUF_TYPE_ALLOC_SRC_MASK_STD_HEAP),
  /**pbuf数据存储在ROM中，即结构pbuf及其有效载荷位于完全不同的内存区域中。由于它指向ROM，所以在排队等待传输时不必复制有效负载。*/
  PBUF_ROM = PBUF_TYPE_ALLOC_SRC_MASK_STD_MEMP_PBUF,
  /**pbuf来自pbuf池。与PBUF_ROM很相似，但有效载荷可能会发生变化，因此在传输前排队时必须复制，这取决于谁对其有“引用”。*/
  PBUF_REF = (PBUF_TYPE_FLAG_DATA_VOLATILE | PBUF_TYPE_ALLOC_SRC_MASK_STD_MEMP_PBUF),
  /**pbuf有效载荷指的是RAM。这个来自一个池，应该用于RX。有效载荷可以是链式的（散点聚集RX），但与PBUF_RAM一样，结构PBUF及其有效载荷被分配在一块连续内存中（因此第一个有效载荷字节可以从结构PBUF）。不要将此用于TX，如果池变空，例如由于TCP排队，则无法接收TCP ACK！*/
  PBUF_POOL = (PBUF_ALLOC_FLAG_RX | PBUF_TYPE_FLAG_STRUCT_DATA_CONTIGUOUS | PBUF_TYPE_ALLOC_SRC_MASK_STD_MEMP_PBUF_POOL)
} pbuf_type;


/**指示此数据包的数据应立即传递给应用程序*/
#define PBUF_FLAG_PUSH      0x01U
/**表示这是一个自定义pbuf:pbuff_free在释放最后一个引用时调用pbuf_custom->custom_free_function（）（加上自定义pbuf_RAM无法修剪）*/
#define PBUF_FLAG_IS_CUSTOM 0x02U
/**指示此pbuf是要环回的UDP多播*/
#define PBUF_FLAG_MCASTLOOP 0x04U
/**表示此pbuf已作为链路级广播接收*/
#define PBUF_FLAG_LLBCAST   0x08U
/**表示此pbuf是作为链路级多播接收的*/
#define PBUF_FLAG_LLMCAST   0x10U
/**表示此pbuf包含TCP FIN标志*/
#define PBUF_FLAG_TCP_FIN   0x20U

/**主数据包缓冲区结构*/
struct pbuf {
  /**单链pbuf链中的下一个pbuf*/
  struct pbuf *next;

  /**指向缓冲区中实际数据的指针*/
  void *payload;

  /**
   * 该缓冲区和链中属于同一数据包的所有下一个缓冲区的总长度。
   *
   * 对于非队列数据包链，这是不变的：p->tot_len==p->len+（p->next？p->next->tot_len:0）
   */
  u16_t tot_len;

  /**此缓冲区的长度*/
  u16_t len;

  /** 指示pbuf类型和分配源的位字段（参见pbuf_type_FLAG_、pbuf_ALLOC_FLAG_和pbuf_TTYPE_ALLOC_SRC_MASK）
    */
  u8_t type_internal;

  /**杂项标志*/
  u8_t flags;

  /**
   * 引用计数始终等于引用此pbuf的指针数。这可以是来自应用程序、堆栈本身的指针，也可以是来自链的pbuf->next指针。
   */
  LWIP_PBUF_REF_T ref;

  /**对于传入的数据包，它包含输入netif的索引*/
  u8_t if_idx;

  /**如果用户需要将数据自定义数据存储在pbuf上*/
  LWIP_PBUF_CUSTOM_DATA
#if ESP_PBUF
  struct netif *l2_owner;
  void *l2_buf;
#endif
};


/** 仅用于常量正确性的帮助程序结构。这个函数的唯一含义是为PBUF_ROM类型提供常量有效负载指针。
 */
struct pbuf_rom {
  /**单链pbuf链中的下一个pbuf*/
  struct pbuf *next;

  /**指向缓冲区中实际数据的指针*/
  const void *payload;
};

#if LWIP_SUPPORT_CUSTOM_PBUF
/**释放自定义pbuf的函数原型*/
typedef void (*pbuf_free_custom_fn)(struct pbuf *p);

/**自定义pbuf：类似于pbuf，但遵循函数指针来释放它。*/
struct pbuf_custom {
  /**实际pbuf*/
  struct pbuf pbuf;
  /**当pbuf_free释放此pbuf（_custom）时调用此函数*/
  pbuf_free_custom_fn custom_free_function;
};
#endif /* LWIP_SUPPORT_CUSTOM_PBUF */

/**将其定义为0以防止在PBUF_POOL为空时释放ooseq pbufs*/
#ifndef PBUF_POOL_FREE_OOSEQ
#define PBUF_POOL_FREE_OOSEQ 1
#endif /* PBUF_POOL_FREE_OOSEQ */
#if LWIP_TCP && TCP_QUEUE_OOSEQ && NO_SYS && PBUF_POOL_FREE_OOSEQ
extern volatile u8_t pbuf_free_ooseq_pending;
void pbuf_free_ooseq(void);
/**当不使用sys_check_timeouts（）时，从主级别定期调用PBUF_check_FREE_OSEQ（），以检查是否需要释放OOSEQ pbufs！*/
#define PBUF_CHECK_FREE_OOSEQ() do { if(pbuf_free_ooseq_pending) { \
  /* pbuf_alloc（）报告pbuf_POOL为空->现在尝试释放一些排队的pbuf*/ \
  pbuf_free_ooseq(); }}while(0)
#else /* LWIP_TCP && TCP_QUEUE_OOSEQ && NO_SYS && PBUF_POOL_FREE_OOSEQ */
  /* 否则声明一个空PBUF_CHECK_FREE_OSEQ*/
  #define PBUF_CHECK_FREE_OOSEQ()
#endif /* LWIP_TCP && TCP_QUEUE_OOSEQ && NO_SYS && PBUF_POOL_FREE_OOSEQ*/

/* 初始化pbuf模块。此呼叫目前为空，但将来可能不会。*/
#define pbuf_init()

struct pbuf *pbuf_alloc(pbuf_layer l, u16_t length, pbuf_type type);
struct pbuf *pbuf_alloc_reference(void *payload, u16_t length, pbuf_type type);
#if LWIP_SUPPORT_CUSTOM_PBUF
struct pbuf *pbuf_alloced_custom(pbuf_layer l, u16_t length, pbuf_type type,
                                 struct pbuf_custom *p, void *payload_mem,
                                 u16_t payload_mem_len);
#endif /* LWIP_SUPPORT_CUSTOM_PBUF */
void pbuf_realloc(struct pbuf *p, u16_t size);
#define pbuf_get_allocsrc(p)          ((p)->type_internal & PBUF_TYPE_ALLOC_SRC_MASK)
#define pbuf_match_allocsrc(p, type)  (pbuf_get_allocsrc(p) == ((type) & PBUF_TYPE_ALLOC_SRC_MASK))
#define pbuf_match_type(p, type)      pbuf_match_allocsrc(p, type)
u8_t pbuf_header(struct pbuf *p, s16_t header_size);
u8_t pbuf_header_force(struct pbuf *p, s16_t header_size);
u8_t pbuf_add_header(struct pbuf *p, size_t header_size_increment);
u8_t pbuf_add_header_force(struct pbuf *p, size_t header_size_increment);
u8_t pbuf_remove_header(struct pbuf *p, size_t header_size);
struct pbuf *pbuf_free_header(struct pbuf *q, u16_t size);
void pbuf_ref(struct pbuf *p);
u8_t pbuf_free(struct pbuf *p);
u16_t pbuf_clen(const struct pbuf *p);
void pbuf_cat(struct pbuf *head, struct pbuf *tail);
void pbuf_chain(struct pbuf *head, struct pbuf *tail);
struct pbuf *pbuf_dechain(struct pbuf *p);
err_t pbuf_copy(struct pbuf *p_to, const struct pbuf *p_from);
u16_t pbuf_copy_partial(const struct pbuf *p, void *dataptr, u16_t len, u16_t offset);
void *pbuf_get_contiguous(const struct pbuf *p, void *buffer, size_t bufsize, u16_t len, u16_t offset);
err_t pbuf_take(struct pbuf *buf, const void *dataptr, u16_t len);
err_t pbuf_take_at(struct pbuf *buf, const void *dataptr, u16_t len, u16_t offset);
struct pbuf *pbuf_skip(struct pbuf* in, u16_t in_offset, u16_t* out_offset);
struct pbuf *pbuf_coalesce(struct pbuf *p, pbuf_layer layer);
struct pbuf *pbuf_clone(pbuf_layer l, pbuf_type type, struct pbuf *p);
#if LWIP_CHECKSUM_ON_COPY
err_t pbuf_fill_chksum(struct pbuf *p, u16_t start_offset, const void *dataptr,
                       u16_t len, u16_t *chksum);
#endif /* LWIP_CHECKSUM_ON_COPY */
#if LWIP_TCP && TCP_QUEUE_OOSEQ && LWIP_WND_SCALE
void pbuf_split_64k(struct pbuf *p, struct pbuf **rest);
#endif /* LWIP_TCP && TCP_QUEUE_OOSEQ && LWIP_WND_SCALE */

u8_t pbuf_get_at(const struct pbuf* p, u16_t offset);
int pbuf_try_get_at(const struct pbuf* p, u16_t offset);
void pbuf_put_at(struct pbuf* p, u16_t offset, u8_t data);
u16_t pbuf_memcmp(const struct pbuf* p, u16_t offset, const void* s2, u16_t n);
u16_t pbuf_memfind(const struct pbuf* p, const void* mem, u16_t mem_len, u16_t start_offset);
u16_t pbuf_strstr(const struct pbuf* p, const char* substr);

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_PBUF_H */

