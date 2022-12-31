/*
 * uri。h——URI处理的助手函数
 *
 * 版权所有（C）2010-2020 Olaf Bergmann<bergmann@tzi.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

#ifndef COAP_URI_H_
#define COAP_URI_H_

#include <stdint.h>

#include "str.h"

/**
 * 方案说明符。安全方案的数值为奇数，其他为偶数。
 */
typedef enum coap_uri_scheme_t {
  COAP_URI_SCHEME_COAP = 0,
  COAP_URI_SCHEME_COAPS,     /* 1 */
  COAP_URI_SCHEME_COAP_TCP,  /* 2 */
  COAP_URI_SCHEME_COAPS_TCP, /* 3 */
  COAP_URI_SCHEME_HTTP,      /* 4仅代理Uri*/
  COAP_URI_SCHEME_HTTPS      /* 5仅代理Uri*/
} coap_uri_scheme_t;

/**此掩码可用于检查解析的URI方案是否安全。*/
#define COAP_URI_SCHEME_SECURE_MASK 0x01

/**
 * 已解析URI的表示形式。组件可以用coap_split_uri（）或coap_splid_proxy_uri（）从字符串中填充，并且可以用作选项创建函数的输入。
 */
typedef struct {
  coap_str_const_t host;  /**<URI的主机部分*/
  uint16_t port;          /**<主机字节顺序的端口*/
  coap_str_const_t path;  /**<第一个路径段的开始。使用coap_split_path（）创建Uri路径选项*/
  coap_str_const_t query; /**<查询部分（如果存在）*/

  /**已分析的方案说明符。*/
  enum coap_uri_scheme_t scheme;
} coap_uri_t;

static inline int
coap_uri_scheme_is_secure(const coap_uri_t *uri) {
  return uri && ((uri->scheme & COAP_URI_SCHEME_SECURE_MASK) != 0);
}

/**
 * 从指定的uri创建新的coap_uri_t对象。返回新对象或出错时返回NULL。必须使用coap_free（）释放新coap_uri_t分配的内存。
 *
 * @param uri 要复制的URI路径。
 * @param length uri的长度。
 *
 * @return 新URI对象或出错时为NULL。
 */
coap_uri_t *coap_new_uri(const uint8_t *uri, unsigned int length);

/**
 * 克隆指定的coap_uri_t对象。该函数分配足够的内存来保存coap_uri_t结构及其内容。必须使用coap_free（）释放对象。*/
coap_uri_t *coap_clone_uri(const coap_uri_t *uri);

/**
 * @defgroup uri_parse uri解析函数
 *
 * CoAP PDU包含标准化URI，其路径和查询分为多个段。此模块中的函数有助于拆分字符串@{
 */

/**
 * Parses a given string into URI components. The identified syntactic components are stored in the result parameter @p uri。未指定的可选URI组件将设置为｛0，0｝，但设置为协议默认端口的端口除外。此函数
 * returns @p 如果分析成功，则为0，否则为小于零的值。
 *
 * @param str_var 要拆分的字符串。
 * @param len     @p str_var的实际长度
 * @param uri     用于存储结果的coap_uri_t对象。
 *
 * @return        @c 0表示成功，或<0表示错误。
 *
 */
int coap_split_uri(const uint8_t *str_var, size_t len, coap_uri_t *uri);

/**
 * Parses a given string into URI components. The identified syntactic components are stored in the result parameter @p uri。未指定的可选URI组件将设置为｛0，0｝，但设置为协议默认端口的端口除外。此函数返回
 * @p 如果分析成功，则为0，否则为小于零的值。注意：此函数强制给定的字符串采用代理Uri格式，并支持不同的架构（如http）。
 *
 * @param str_var 要拆分的字符串。
 * @param len     @p str_var的实际长度
 * @param uri     用于存储结果的coap_uri_t对象。
 *
 * @return        @c 0表示成功，或<0表示错误。
 *
 */
int coap_split_proxy_uri(const uint8_t *str_var, size_t len, coap_uri_t *uri);

/**
 * 将给定的URI路径拆分为段。每个段前面都有一个选项伪标头，其delta值为0，以及百分比解码后相应段的实际长度。
 *
 * @param s      要拆分的路径字符串。
 * @param length @p s的实际长度。
 * @param buf    已分析段的结果缓冲区。
 * @param buflen @p buf的最大长度。将设置为成功时写入buf的实际字节数。
 *
 * @return       创建的段数或出现错误时的@c-1。
 */
int coap_split_path(const uint8_t *s,
                    size_t length,
                    unsigned char *buf,
                    size_t *buflen);

/**
 * 将给定的URI查询拆分为段。每个段前面都有一个选项伪标头，其delta值为0，以及相应查询项的实际长度。
 *
 * @param s      要拆分的查询字符串。
 * @param length @p s的实际长度。
 * @param buf    已分析段的结果缓冲区。
 * @param buflen @p buf的最大长度。将设置为成功时写入buf的实际字节数。
 *
 * @return       创建的段数或出现错误时的@c-1。
 *
 * @bug 此函数不会为delta>12保留额外空间。
 */
int coap_split_query(const uint8_t *s,
                     size_t length,
                     unsigned char *buf,
                     size_t *buflen);

/**
 * 根据6.5.8中的转义规则从请求PDU中提取查询字符串。
 * @param request 请求PDU。
 * @return        重新构造并转义了查询字符串部分，如果@p请求中不包含任何查询，则返回@c NULL。此函数返回的coap_string_t对象必须与coap_delete_string一起释放。
 */
coap_string_t *coap_get_query(const coap_pdu_t *request);

/**
 * 从请求PDU中提取uri_path字符串
 * @param request 请求PDU。
 * @return        重新构造并转义了uri路径字符串部分，如果@p请求中不包含uri路径，则返回@c NULL。此函数返回的coap_string_t对象必须与coap_delete_string一起释放。
 */
coap_string_t *coap_get_uri_path(const coap_pdu_t *request);

/** @} */

#endif /* COAP_URI_H_ */

