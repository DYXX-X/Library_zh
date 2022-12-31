/*
 * coap_pdu_内部。h——CoAP PDU结构
 *
 * 版权所有（C）2010-2021 Olaf Bergmann<bergmann@tzi.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

/**
 * @file coap_pdu_内部.h
 * @brief CoAP PDU内部信息
 */

#ifndef COAP_COAP_PDU_INTERNAL_H_
#define COAP_COAP_PDU_INTERNAL_H_

#ifdef WITH_LWIP
#include <lwip/pbuf.h>
#endif

#include <stdint.h>

/**
 * @defgroup pdu_internal pdu（内部）不向应用程序公开的CoAP pdu结构、枚举和函数@{
 */

#define COAP_DEFAULT_VERSION      1 /* 支持的CoAP版本*/

/* TCP消息格式常量，不修改*/
#define COAP_MESSAGE_SIZE_OFFSET_TCP8 13
#define COAP_MESSAGE_SIZE_OFFSET_TCP16 269 /* 13 + 256 */
#define COAP_MESSAGE_SIZE_OFFSET_TCP32 65805 /* 269 + 65536 */

/* 派生邮件大小限制*/
#define COAP_MAX_MESSAGE_SIZE_TCP0 (COAP_MESSAGE_SIZE_OFFSET_TCP8-1) /* 12 */
#define COAP_MAX_MESSAGE_SIZE_TCP8 (COAP_MESSAGE_SIZE_OFFSET_TCP16-1) /* 268 */
#define COAP_MAX_MESSAGE_SIZE_TCP16 (COAP_MESSAGE_SIZE_OFFSET_TCP32-1) /* 65804 */
#define COAP_MAX_MESSAGE_SIZE_TCP32 (COAP_MESSAGE_SIZE_OFFSET_TCP32+0xFFFFFFFF)

#ifndef COAP_DEBUG_BUF_SIZE
#if defined(WITH_CONTIKI) || defined(WITH_LWIP)
#define COAP_DEBUG_BUF_SIZE 128
#else /* 已定义（WITH_CONTIKI）||已定义（WIH_LWIP）*/
/* 1024源自RFC7252 4.6.消息大小最大有效负载*/
#define COAP_DEBUG_BUF_SIZE (8 + 1024 * 2)
#endif /* 已定义（WITH_CONTIKI）||已定义（WIH_LWIP）*/
#endif /* COAP_DEBUG_BUF_SIZE */

#ifndef COAP_DEFAULT_MAX_PDU_RX_SIZE
#if defined(WITH_CONTIKI) || defined(WITH_LWIP)
#define COAP_DEFAULT_MAX_PDU_RX_SIZE (COAP_MAX_MESSAGE_SIZE_TCP16+4UL)
#else
/* 8 MiB最大邮件大小加上一些选项空间*/
#define COAP_DEFAULT_MAX_PDU_RX_SIZE (8UL*1024*1024+256)
#endif
#endif /* COAP_DEFAULT_MAX_PDU_RX_SIZE */

/**
 * 指示响应被抑制。如果通过IP多播接收到请求，则错误响应将发生这种情况。
 */
#define COAP_DROPPED_RESPONSE -2

#define COAP_PDU_DELAYED -3

#define COAP_PAYLOAD_START 0xFF /* 有效载荷标记*/

#define COAP_PDU_IS_EMPTY(pdu)     ((pdu)->code == 0)
#define COAP_PDU_IS_REQUEST(pdu)   (!COAP_PDU_IS_EMPTY(pdu) && (pdu)->code < 32)
#define COAP_PDU_IS_RESPONSE(pdu)  ((pdu)->code >= 64 && (pdu)->code < 224)
#define COAP_PDU_IS_SIGNALING(pdu) ((pdu)->code >= 224)

#define COAP_PDU_MAX_UDP_HEADER_SIZE 4
#define COAP_PDU_MAX_TCP_HEADER_SIZE 6

/**
 * CoAP PDU令牌的结构（如果有）遵循固定大小的报头，然后是选项，直到有效负载标记（0xff），然后是有效负载（如果内联存储）。内存布局为：<--header--->|<--token--><--options--->0xff<--payload--->标头以负偏移量寻址到token，其最大大小为max_hdr_size。选项从token开始+token_length有效负载从data开始，其长度为used_size-（data-token）
 */

struct coap_pdu_t {
  coap_pdu_type_t type;     /**<消息类型*/
  coap_pdu_code_t code;     /**<请求方法（值1-31）或响应代码（值64-255）*/
  coap_mid_t mid;           /**<message id（如果有），按常规主机字节顺序*/
  uint8_t max_hdr_size;     /**<为协议特定标头保留的空间*/
  uint8_t hdr_size;         /**<用于协议特定标头的实际大小*/
  uint8_t token_length;     /**<令牌长度*/
  uint16_t max_opt;         /**<PDU中的最高选项编号*/
  size_t alloc_size;        /**<为令牌、选项和负载分配的存储*/
  size_t used_size;         /**<令牌、选项和有效负载的已用存储字节数*/
  size_t max_size;          /**<令牌、选项和有效负载的最大大小，或可变大小pdu为零*/
  uint8_t *token;           /**<令牌的第一个字节（如果有）或选项*/
  uint8_t *data;            /**<有效载荷的第一字节（如果有）*/
#ifdef WITH_LWIP
  struct pbuf *pbuf;        /**<lwIP PBUF。包数据将始终驻留在pbuf的有效负载内，但必须保留此指针，因为无法给出确切的偏移量。不能从外部访问此字段，因为当pbuf被分配给pdu时，pbuf的引用计数被检查为1，并且pbuf对*这个pdu保持独占。*/
#endif
  const uint8_t *body_data; /**<保留ptr以重新组装数据或NULL*/
  size_t body_length;       /**<保留正文数据长度*/
  size_t body_offset;       /**<保留正文数据偏移量*/
  size_t body_total;        /**<保存正文数据总大小*/
  coap_lg_xmit_t *lg_xmit;  /**<如果发送一组块，则将ptr保存到lg_xmit*/
};

/**
 * Dynamically grows the size of @p pdu到@p new_size。新大小不得超过PDU的配置最大大小。成功时，此函数返回1，否则返回0。
 *
 * @param pdu      要调整大小的PDU。
 * @param new_size 以字节为单位的新大小。
 * @return         如果操作成功，则为1，否则为0。
 */
int coap_pdu_resize(coap_pdu_t *pdu, size_t new_size);

/**
 * Dynamically grows the size of @p pdu到@p new_size（如果需要）。新大小不得超过PDU配置的最大大小。成功时，此函数返回1，否则返回0。
 *
 * @param pdu      要调整大小的PDU。
 * @param new_size 以字节为单位的新大小。
 * @return         如果操作成功，则为1，否则为0。
 */
int coap_pdu_check_resize(coap_pdu_t *pdu, size_t new_size);

/**
* Interprets @p 数据以确定标头中的字节数。
* This function returns @c 错误时为0，成功时为大于零的数字。
*
* @param proto  会话的协议
* @param data   要解析为CoAP PDU的原始数据的第一个字节。
*
* @return       成功时大于零，错误时大于@c 0。
*/
size_t coap_pdu_parse_header_size(coap_proto_t proto,
                                 const uint8_t *data);

/**
 * Parses @p 数据以提取消息大小。
 * @p 长度必须至少为coap_pdu_pare_header_size（proto，data）。
 * This function returns @c 错误时为0，成功时为大于零的数字。
 *
 * @param proto  会话的协议
 * @param data   要解析为CoAP PDU的原始数据。
 * @param length @p数据的实际大小。
 *
 * @return       成功时大于零，错误时大于@c 0。
 */
size_t coap_pdu_parse_size(coap_proto_t proto,
                           const uint8_t *data,
                           size_t length);

/**
 * 解码指定PDU的协议特定标头。
 * @param pdu 新接收的PDU。
 * @param proto 目标有线协议。
 * @return 1表示成功，0表示错误。
 */

int coap_pdu_parse_header(coap_pdu_t *pdu, coap_proto_t proto);

/**
 * 验证给定CoAP PDU结构的一致性并定位数据。
 * This function returns @c 错误时为0，成功时为大于零的数字。此函数只解析令牌和选项，直到有效负载开始标记。
 *
 * @param pdu     要检查的PDU结构。
 *
 * @return       成功时为1，错误时为@c 0。
 */
int coap_pdu_parse_opt(coap_pdu_t *pdu);

/**
* Parses @p 将数据转换为@p result中给出的CoAP PDU结构。目标pdu必须足够大
* This function returns @c 错误时为0，成功时为大于零的数字。
*
* @param proto   会话的协议
* @param data    要解析为CoAP PDU的原始数据。
* @param length  @p数据的实际大小。
* @param pdu     要填充的PDU结构。请注意，该结构必须提供空间以至少容纳消息的令牌和选项部分。
*
* @return       成功时为1，错误时为@c 0。
*/
int coap_pdu_parse(coap_proto_t proto,
                   const uint8_t *data,
                   size_t length,
                   coap_pdu_t *pdu);

/**
 * Clears any contents from @p pdu并重置@c used_size，
 * and @c 数据指针@c max_size设置为@p大小，任意
 * other field is set to @c 0。请注意，@p pdu必须是指向例如由coap_pdu_init（）创建的coap_pdu_t对象的有效指针。
 *
 * @param pdu   要清除的PDU。
 * @param size  PDU的最大大小。
 */
void coap_pdu_clear(coap_pdu_t *pdu, size_t size);

/**
 * 从@p pdu中删除给定数字的（第一个）选项。
 *
 * @param pdu   要从中删除选项的PDU。
 * @param number 要删除的CoAP选项的编号（仅第一个已删除）。
 *
 * @return @c 1如果成功，否则@c 0如果错误。
 */
int coap_remove_option(coap_pdu_t *pdu, coap_option_num_t number);

/**
 * Inserts option of given number in the @p 具有适当数据的pdu。该选项将插入pdu中选项的适当位置。
 *
 * @param pdu    要插入选项的PDU。
 * @param number 新选项的编号。
 * @param len    新选项的长度。
 * @param data   新选项的数据。
 *
 * @return 选项的总长度或失败时的@c 0。
 */
size_t coap_insert_option(coap_pdu_t *pdu, coap_option_num_t number,
                          size_t len, const uint8_t *data);

/**
 * 使用新数据更新@ppdu中给定数字的现有第一个选项。
 *
 * @param pdu    要更新选项的PDU。
 * @param number 要更新的选项的编号（仅第一次更新）。
 * @param len    更新选项的长度。
 * @param data   更新选项的数据。
 *
 * @return 更新选项的总长度或失败时的@c 0。
 */
size_t coap_update_option(coap_pdu_t *pdu,
                          coap_option_num_t number,
                          size_t len,
                          const uint8_t *data);

/**
 * 为指定的PDU编写协议特定的标头。
 *
 * @param pdu 新组成的PDU。
 * @param proto 目标有线协议。
 *
 * @return 在pdu->标记之前预加的标头字节数，或出错时为0。
 */

size_t coap_pdu_encode_header(coap_pdu_t *pdu, coap_proto_t proto);

 /**
 * Updates token in @p 长度为@plen和@p数据的pdu。
 * This function returns @c 错误时为0，成功时为大于零的值。
 *
 * @param pdu  要更新令牌的PDU。
 * @param len  新令牌的长度。
 * @param data 要添加的令牌。
 *
 * @return     成功时大于零，错误时大于@c 0。
 */
int coap_update_token(coap_pdu_t *pdu,
                      size_t len,
                      const uint8_t *data);

/** @} */

#endif /* COAP_COAP_PDU_INTERNAL_H_ */

