/*
 * pdu。h——CoAP消息结构
 *
 * 版权所有（C）2010-2014 Olaf Bergmann<bergmann@tzi.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

/**
 * @file pdu.小时
 * @brief 反映CoAP默认值的预定义常量
 */

#ifndef COAP_PDU_H_
#define COAP_PDU_H_

#include "uri.h"
#include "option.h"

#ifdef WITH_LWIP
#include <lwip/pbuf.h>
#endif

#include <stdint.h>

/**
 * @defgroup pdu的pdu pdu API函数@{
 */

#define COAP_DEFAULT_PORT      5683 /* CoAP默认UDP/TCP端口*/
#define COAPS_DEFAULT_PORT     5684 /* 用于安全传输的CoAP默认UDP/TCP端口*/
#define COAP_DEFAULT_MAX_AGE     60 /* 默认最大对象生存时间（秒）*/
#ifndef COAP_DEFAULT_MTU
#define COAP_DEFAULT_MTU       1152
#endif /* COAP_DEFAULT_MTU */

#ifndef COAP_DEFAULT_HOP_LIMIT
#define COAP_DEFAULT_HOP_LIMIT       16
#endif /* COAP_DEFAULT_HOP_LIMIT */

#define COAP_DEFAULT_SCHEME  "coap" /* CoAP URI的默认方案*/

/**已知资源URI*/
#define COAP_DEFAULT_URI_WELLKNOWN ".well-known/core"

/* CoAP消息类型*/

/**
 * CoAP PDU消息类型定义
 */
typedef enum coap_pdu_type_t {
  COAP_MESSAGE_CON,  /* 0可确认消息（需要ACK/RST）*/
  COAP_MESSAGE_NON,  /* 1条不可确认消息（一次性消息）*/
  COAP_MESSAGE_ACK,  /* 2用于确认可确认消息*/
  COAP_MESSAGE_RST   /* 3表示收到的消息中有错误*/
} coap_pdu_type_t;

/**
 * CoAP PDU请求方法
 */
typedef enum coap_request_t {
  COAP_REQUEST_GET = 1,
  COAP_REQUEST_POST,      /* 2 */
  COAP_REQUEST_PUT,       /* 3 */
  COAP_REQUEST_DELETE,    /* 4 */
  COAP_REQUEST_FETCH,     /* 5 RFC 8132 */
  COAP_REQUEST_PATCH,     /* 6 RFC 8132 */
  COAP_REQUEST_IPATCH,    /* 7 RFC 8132 */
} coap_request_t;

/*
 * CoAP选项编号（添加选项时，务必更新CoAP_option_check_critical（）和CoAP_add_option（）
 */

/*
 * C、U和N标志分别表示属性Critical、Unsafe和NoCacheKey。如果设置了U，则N根据https://tools.ietf.org/html/rfc7252#section-5.10，并设置为-。
 *
 * 另外，R表示可重复的选项
 *
 * 选项的最低有效字节设置如下：https://tools.ietf.org/html/rfc7252#section-5.4.6
 *
 *   0   1   2   3   4   5   6   7
 * --+---+---+---+---+---+---+---+|无缓存密钥|U|C|
 * --+---+---+---+---+---+---+---+
 *
 * https://tools.ietf.org/html/rfc8613#section-4继续分别定义E、I和U属性Encrypted和Integrity Protected、Integrity Protection Only和Unprotected。当前未使用“仅受完整性保护”。
 *
 * 选项标记为CUNREIU，如果未设置，则用_替换任何字母，如果设置了U，则用-替换N（见上文），以帮助理解选项。
 */

#define COAP_OPTION_IF_MATCH        1 /* C__RE__，不透明，0-8 B，RFC7252*/
#define COAP_OPTION_URI_HOST        3 /* CU-___U，字符串，1-255 B，RFC7252*/
#define COAP_OPTION_ETAG            4 /* ___RE__，不透明，1-8 B，RFC7252*/
#define COAP_OPTION_IF_NONE_MATCH   5 /* C___E__，空，0 B，RFC7252*/
#define COAP_OPTION_OBSERVE         6 /* _U-_E_U，空/uint，0/0-3 B，RFC7641*/
#define COAP_OPTION_URI_PORT        7 /* CU-___U，uint，0-2 B，RFC7252*/
#define COAP_OPTION_LOCATION_PATH   8 /* ___RE__，字符串，0-255 B，RFC7252*/
#define COAP_OPTION_OSCORE          9 /* C_____U, *,       0-255 B, RFC8613 */
#define COAP_OPTION_URI_PATH       11 /* CU-RE_，字符串，0-255 B，RFC7252*/
#define COAP_OPTION_CONTENT_FORMAT 12 /* ____E__，uint，0-2 B，RFC7252*/
#define COAP_OPTION_CONTENT_TYPE COAP_OPTION_CONTENT_FORMAT
/* COAP_OPTION_MAXAGE默认60秒（如果未设置）*/
#define COAP_OPTION_MAXAGE         14 /* _U-_E_U，uint，0-4 B，RFC7252*/
#define COAP_OPTION_URI_QUERY      15 /* CU-RE_，字符串，1-255 B，RFC7252*/
#define COAP_OPTION_HOP_LIMIT      16 /* ______U、 uint，1 B，RFC8768*/
#define COAP_OPTION_ACCEPT         17 /* C___E__，单位，0-2 B，RFC7252*/
#define COAP_OPTION_LOCATION_QUERY 20 /* ___RE__，字符串，0-255 B，RFC7252*/
#define COAP_OPTION_BLOCK2         23 /* CU-E_U，uint，0-3 B，RFC7959*/
#define COAP_OPTION_BLOCK1         27 /* CU-E_U，uint，0-3 B，RFC7959*/
#define COAP_OPTION_SIZE2          28 /* __N_E_U，uint，0-4 B，RFC7959*/
#define COAP_OPTION_PROXY_URI      35 /* CU-___U，字符串，1-1034 B，RFC7252*/
#define COAP_OPTION_PROXY_SCHEME   39 /* CU-___U，字符串，1-255 B，RFC7252*/
#define COAP_OPTION_SIZE1          60 /* __N_E_U，uint，0-4 B，RFC7252*/
#define COAP_OPTION_NORESPONSE    258 /* _U-_E_U，单位，0-1 B，RFC7967*/

#define COAP_MAX_OPT            65535 /**<我们知道的最高选项编号*/

/* CoAP结果代码（HTTP代码/100*40+HTTP代码%100）*/

/* 从draft-ietf-core-coap-04开始，响应代码被编码到基32，即，三个高位确定响应类别，而其余五个细粒度信息特定于该类别。
 */
#define COAP_RESPONSE_CODE(N) (((N)/100 << 5) | (N)%100)

/* 确定响应代码C的类别*/
#define COAP_RESPONSE_CLASS(C) (((C) >> 5) & 0xFF)

#ifndef SHORT_ERROR_RESPONSE
/**
 * 返回指定CoAP响应@p代码的可读响应短语。如果找不到，此函数将返回@c NULL。
 *
 * @param code 应检索其文字短语的响应代码。
 *
 * @return     描述错误的以零结尾的字符串，如果找不到，则返回@c NULL。
 */
const char *coap_response_phrase(unsigned char code);

#define COAP_ERROR_PHRASE_LENGTH   32 /**<错误短语的最大长度*/

#else
#define coap_response_phrase(x) ((char *)NULL)

#define COAP_ERROR_PHRASE_LENGTH    0 /**<错误短语的最大长度*/
#endif /* SHORT_ERROR_RESPONSE */

#define COAP_SIGNALING_CODE(N) (((N)/100 << 5) | (N)%100)

typedef enum coap_pdu_signaling_proto_t {
  COAP_SIGNALING_CSM =     COAP_SIGNALING_CODE(701),
  COAP_SIGNALING_PING =    COAP_SIGNALING_CODE(702),
  COAP_SIGNALING_PONG =    COAP_SIGNALING_CODE(703),
  COAP_SIGNALING_RELEASE = COAP_SIGNALING_CODE(704),
  COAP_SIGNALING_ABORT =   COAP_SIGNALING_CODE(705),
} coap_pdu_signaling_proto_t;

/* 适用于COAP_SIGNALING_CSM*/
#define COAP_SIGNALING_OPTION_MAX_MESSAGE_SIZE 2
#define COAP_SIGNALING_OPTION_BLOCK_WISE_TRANSFER 4
/* 适用于COAP_SIGNALING_PING/COAP_SIGNALING_PONG*/
#define COAP_SIGNALING_OPTION_CUSTODY 2
/* 适用于COAP_SIGNALING_RELEASE*/
#define COAP_SIGNALING_OPTION_ALTERNATIVE_ADDRESS 2
#define COAP_SIGNALING_OPTION_HOLD_OFF 4
/* 适用于COAP_SIGNALING_ABORT*/
#define COAP_SIGNALING_OPTION_BAD_CSM_OPTION 2

/* CoAP媒体类型编码*/

#define COAP_MEDIATYPE_TEXT_PLAIN                 0 /* 文本/纯文本（UTF-8）*/
#define COAP_MEDIATYPE_APPLICATION_LINK_FORMAT   40 /* 应用程序/链接格式*/
#define COAP_MEDIATYPE_APPLICATION_XML           41 /* 应用程序/xml*/
#define COAP_MEDIATYPE_APPLICATION_OCTET_STREAM  42 /* 应用程序/八位字节流*/
#define COAP_MEDIATYPE_APPLICATION_RDF_XML       43 /* 应用程序/rdf+xml*/
#define COAP_MEDIATYPE_APPLICATION_EXI           47 /* 应用程序/exi*/
#define COAP_MEDIATYPE_APPLICATION_JSON          50 /* 应用程序/json*/
#define COAP_MEDIATYPE_APPLICATION_CBOR          60 /* 应用程序/cbor*/
#define COAP_MEDIATYPE_APPLICATION_CWT           61 /* 应用/cwt，RFC 8392*/

/* RFC 8152中的内容格式*/
#define COAP_MEDIATYPE_APPLICATION_COSE_SIGN     98 /* 应用/cose；cose type=“cose符号”*/
#define COAP_MEDIATYPE_APPLICATION_COSE_SIGN1    18 /* 应用/cose；cose type=“cose-sign1”*/
#define COAP_MEDIATYPE_APPLICATION_COSE_ENCRYPT  96 /* 应用/cose；cose type=“cose加密”*/
#define COAP_MEDIATYPE_APPLICATION_COSE_ENCRYPT0 16 /* 应用/cose；cose type=“cose-encrypt0”*/
#define COAP_MEDIATYPE_APPLICATION_COSE_MAC      97 /* 应用/cose；cose type=“cose mac”*/
#define COAP_MEDIATYPE_APPLICATION_COSE_MAC0     17 /* 应用/cose；cose type=“cose-mac0”*/

#define COAP_MEDIATYPE_APPLICATION_COSE_KEY     101 /* 应用程序/cose密钥*/
#define COAP_MEDIATYPE_APPLICATION_COSE_KEY_SET 102 /* 应用程序/cose密钥集*/

/* RFC 8428中的内容格式*/
#define COAP_MEDIATYPE_APPLICATION_SENML_JSON   110 /* 应用程序/senml+json*/
#define COAP_MEDIATYPE_APPLICATION_SENSML_JSON  111 /* 应用程序/sensml+json*/
#define COAP_MEDIATYPE_APPLICATION_SENML_CBOR   112 /* 应用程序/senml+cbor*/
#define COAP_MEDIATYPE_APPLICATION_SENSML_CBOR  113 /* 应用程序/传感器+cbor*/
#define COAP_MEDIATYPE_APPLICATION_SENML_EXI    114 /* 应用程序/senml exi*/
#define COAP_MEDIATYPE_APPLICATION_SENSML_EXI   115 /* 应用程序/传感器exi*/
#define COAP_MEDIATYPE_APPLICATION_SENML_XML    310 /* 应用程序/senml+xml*/
#define COAP_MEDIATYPE_APPLICATION_SENSML_XML   311 /* 应用程序/sensml+xml*/

/* RFC 8782中的内容格式*/
#define COAP_MEDIATYPE_APPLICATION_DOTS_CBOR    271 /* 应用程序/dots+cbor*/

/* 请注意，已注册媒体类型的标识符在0-65535范围内。我们在这里使用未分配的类型，并希望得到最好的结果。*/
#define COAP_MEDIATYPE_ANY                         0xff /* 任何媒体类型*/

/**
 * coap_mid_ t用于存储coap PDU的coap消息ID。有效的消息ID为0到2^16。负值为错误代码。
 */
typedef int coap_mid_t;

/**指示无效的消息id。*/
#define COAP_INVALID_MID -1

/**
 * 指示无效的消息id。
 * @deprecated 请改用COAP_INVALID_MID。
 */
#define COAP_INVALID_TID COAP_INVALID_MID

/**
 * @deprecated 请改用coap_optlist_t。
 *
 * 更方便处理选项的结构。（与有序coap_list_t一起使用。）选项的数据将添加到coap_option结构的末尾（请参阅宏coap_option_data）。
 */
COAP_DEPRECATED typedef struct {
  uint16_t key;           /* 选项键（无增量编码）*/
  unsigned int length;
} coap_option;

#define COAP_OPTION_KEY(option) (option).key
#define COAP_OPTION_LENGTH(option) (option).length
#define COAP_OPTION_DATA(option) ((unsigned char *)&(option) + sizeof(coap_option))

#ifdef WITH_LWIP
/**
 * Creates a CoAP PDU from an lwIP @p pbuf，其引用传递给该函数。
 *
 * 检查pbuf是否连续，是否只有一个引用。该引用存储在PDU中，当PDU被释放时将被释放。
 *
 * （目前，这些都是致命错误；将来可能会分配一个新的pbuf，复制数据并释放传递的pbuf）。
 *
 * 这类似于coap_pdu_init（0，0，0、pbuf->tot_len），然后将pbuf的内容复制到pdu。
 *
 * @return 指向新PDU对象的指针或出错时的@c NULL。
 */
coap_pdu_t * coap_pdu_from_pbuf(struct pbuf *pbuf);
#endif

/**
* CoAP协议类型
*/
typedef enum coap_proto_t {
  COAP_PROTO_NONE = 0,
  COAP_PROTO_UDP,
  COAP_PROTO_DTLS,
  COAP_PROTO_TCP,
  COAP_PROTO_TLS,
} coap_proto_t;

/**
 * PDU可用的代码集。
 */
typedef enum coap_pdu_code_t {
  COAP_EMPTY_CODE          = 0,

  COAP_REQUEST_CODE_GET    = COAP_REQUEST_GET,
  COAP_REQUEST_CODE_POST   = COAP_REQUEST_POST,
  COAP_REQUEST_CODE_PUT    = COAP_REQUEST_PUT,
  COAP_REQUEST_CODE_DELETE = COAP_REQUEST_DELETE,
  COAP_REQUEST_CODE_FETCH  = COAP_REQUEST_FETCH,
  COAP_REQUEST_CODE_PATCH  = COAP_REQUEST_PATCH,
  COAP_REQUEST_CODE_IPATCH = COAP_REQUEST_IPATCH,

  COAP_RESPONSE_CODE_CREATED                    = COAP_RESPONSE_CODE(201),
  COAP_RESPONSE_CODE_DELETED                    = COAP_RESPONSE_CODE(202),
  COAP_RESPONSE_CODE_VALID                      = COAP_RESPONSE_CODE(203),
  COAP_RESPONSE_CODE_CHANGED                    = COAP_RESPONSE_CODE(204),
  COAP_RESPONSE_CODE_CONTENT                    = COAP_RESPONSE_CODE(205),
  COAP_RESPONSE_CODE_CONTINUE                   = COAP_RESPONSE_CODE(231),
  COAP_RESPONSE_CODE_BAD_REQUEST                = COAP_RESPONSE_CODE(400),
  COAP_RESPONSE_CODE_UNAUTHORIZED               = COAP_RESPONSE_CODE(401),
  COAP_RESPONSE_CODE_BAD_OPTION                 = COAP_RESPONSE_CODE(402),
  COAP_RESPONSE_CODE_FORBIDDEN                  = COAP_RESPONSE_CODE(403),
  COAP_RESPONSE_CODE_NOT_FOUND                  = COAP_RESPONSE_CODE(404),
  COAP_RESPONSE_CODE_NOT_ALLOWED                = COAP_RESPONSE_CODE(405),
  COAP_RESPONSE_CODE_NOT_ACCEPTABLE             = COAP_RESPONSE_CODE(406),
  COAP_RESPONSE_CODE_INCOMPLETE                 = COAP_RESPONSE_CODE(408),
  COAP_RESPONSE_CODE_CONFLICT                   = COAP_RESPONSE_CODE(409),
  COAP_RESPONSE_CODE_PRECONDITION_FAILED        = COAP_RESPONSE_CODE(412),
  COAP_RESPONSE_CODE_REQUEST_TOO_LARGE          = COAP_RESPONSE_CODE(413),
  COAP_RESPONSE_CODE_UNSUPPORTED_CONTENT_FORMAT = COAP_RESPONSE_CODE(415),
  COAP_RESPONSE_CODE_UNPROCESSABLE              = COAP_RESPONSE_CODE(422),
  COAP_RESPONSE_CODE_TOO_MANY_REQUESTS          = COAP_RESPONSE_CODE(429),
  COAP_RESPONSE_CODE_INTERNAL_ERROR             = COAP_RESPONSE_CODE(500),
  COAP_RESPONSE_CODE_NOT_IMPLEMENTED            = COAP_RESPONSE_CODE(501),
  COAP_RESPONSE_CODE_BAD_GATEWAY                = COAP_RESPONSE_CODE(502),
  COAP_RESPONSE_CODE_SERVICE_UNAVAILABLE        = COAP_RESPONSE_CODE(503),
  COAP_RESPONSE_CODE_GATEWAY_TIMEOUT            = COAP_RESPONSE_CODE(504),
  COAP_RESPONSE_CODE_PROXYING_NOT_SUPPORTED     = COAP_RESPONSE_CODE(505),
  COAP_RESPONSE_CODE_HOP_LIMIT_REACHED          = COAP_RESPONSE_CODE(508),

  COAP_SIGNALING_CODE_CSM                       = COAP_SIGNALING_CSM,
  COAP_SIGNALING_CODE_PING                      = COAP_SIGNALING_PING,
  COAP_SIGNALING_CODE_PONG                      = COAP_SIGNALING_PONG,
  COAP_SIGNALING_CODE_RELEASE                   = COAP_SIGNALING_RELEASE,
  COAP_SIGNALING_CODE_ABORT                     = COAP_SIGNALING_ABORT
} coap_pdu_code_t;

/**
 * 创建一个新的CoAP PDU，该PDU至少有足够的存储空间用于给定的
 * @p size最大邮件大小。该函数在成功时返回指向节点coap_pdu_t对象的指针，在错误时返回@c NULL。如果没有调用coap_send（），则必须使用coap_delete_pdu（）释放为结果分配的存储。
 *
 * @param type PDU的类型（COAP_MESSAGE_CON、COAP_MESSAGE_NON、COAP/MESSAGE_ACK、COAP-MESSAGE_RST之一）。
 * @param code PDU的消息代码。
 * @param mid  要设置的消息id，如果未知/不适用，则为0。
 * @param size 消息允许的最大字节数。
 * @return     指向新PDU对象的指针或出错时的@c NULL。
 */
coap_pdu_t *coap_pdu_init(coap_pdu_type_t type, coap_pdu_code_t code,
                          coap_mid_t mid, size_t size);

/**
 * 创建新的CoAP PDU。
 *
 * @param type PDU的类型（COAP_MESSAGE_CON、COAP_MESSAGE_NON、COAP/MESSAGE_ACK、COAP-MESSAGE_RST之一）。
 * @param code PDU的消息代码。
 * @param session 将使用此PDU的会话
 *
 * @return 骨架PDU或@c NULL（如果失败）。
 */
coap_pdu_t *coap_new_pdu(coap_pdu_type_t type, coap_pdu_code_t code,
                         coap_session_t *session);

/**
 * 处置CoAP PDU并释放相关存储。一般来说，您不应该直接调用此函数。当使用coap_send（）发送PDU时，将自动为您调用coap_delete_PDU（）。
 *
 * @param pdu PDU免费关闭。
 */
void coap_delete_pdu(coap_pdu_t *pdu);

/**
 * 复制现有PDU。可以忽略特定选项，而不复制。PDU数据有效负载未跨复制。
 *
 * @param old_pdu      要复制的PDU
 * @param session      将使用此PDU的会话。
 * @param token_length 要在此重复PDU中使用的令牌的长度。
 * @param token        要在此重复PDU中使用的令牌。
 * @param drop_options 不复制到复制PDU的选项列表。
 *                     If @c NULL，则复制所有选项。
 *
 * @return 重复的PDU或@c NULL（如果失败）。
 */
coap_pdu_t *
coap_pdu_duplicate(const coap_pdu_t *old_pdu,
                   coap_session_t *session,
                   size_t token_length,
                   const uint8_t *token,
                   coap_opt_filter_t *drop_options);

/**
 * Adds token of length @p len到@p pdu。添加令牌会破坏pdu的任何以下内容。因此，必须在调用coap_add_token（）之后添加选项和数据。在@p pdu中，
 * length is set to @p len+@c 4，max_delta设置为@c 0。此函数
 * returns @c 错误时为0，成功时为大于零的值。
 *
 * @param pdu  要添加令牌的PDU。
 * @param len  新令牌的长度。
 * @param data 要添加的令牌。
 *
 * @return     成功时大于零，错误时大于@c 0。
 */
int coap_add_token(coap_pdu_t *pdu,
                  size_t len,
                  const uint8_t *data);

/**
 * 将给定数字的选项添加到作为第一个参数传递的pdu。coap_add_option（）会破坏PDU的数据，因此必须在添加所有选项后调用coap_add_data（）。由于coap_add_token（）破坏了标记后面的选项，因此必须在调用coap_add_option（）之前添加标记。此函数返回写入的字节数或出错时的@c 0。
 *
 * 注意：在可能的情况下，需要将选项数据去掉前导零（大端），以减少PDU中所需的数据量，并且在某些情况下，如果不去掉，可能会超过光电二极管的最大数据大小，因此是非法的。这是通过使用coap_encode_var_safe（）或coap_encode _var_ssafe8（）完成的。
 *
 * @param pdu    要添加选项的PDU。
 * @param number 新选项的编号。
 * @param len    新选项的长度。
 * @param data   新选项的数据。
 *
 * @return 选项的总长度或失败时的@c 0。
 */
size_t coap_add_option(coap_pdu_t *pdu,
                       coap_option_num_t number,
                       size_t len,
                       const uint8_t *data);

/**
 * 将给定数据添加到作为第一个参数传递的pdu。注意，PDU的数据被coap_add_option（）破坏。每个PDU只能调用coap_add_data（）一次，否则结果未定义。
 *
 * @param pdu    要添加数据的PDU。
 * @param len    数据的长度。
 * @param data   要添加的数据。
 *
 * @return @c 1如果成功，否则@c 0如果失败。
 */
int coap_add_data(coap_pdu_t *pdu,
                  size_t len,
                  const uint8_t *data);

/**
 * 将给定数据添加到作为第一个参数传递但不复制的pdu。注意，PDU的数据被coap_add_option（）破坏。coap_add_data（）必须为此PDU调用一次，否则结果未定义。必须在返回的位置复制实际数据。
 *
 * @param pdu    要添加数据的PDU。
 * @param len    数据的长度。
 *
 * @return 将len的数据复制到哪里，或者@c NULL是错误的。
 */
uint8_t *coap_add_data_after(coap_pdu_t *pdu, size_t len);

/**
 * 检索指定PDU的长度和数据指针。出现错误时返回0，如果len和data的值正确，则返回1。请注意，这些值是用pdu销毁的。
 *
 * @param pdu    指定的PDU。
 * @param len    返回当前数据的长度
 * @param data   返回当前数据的指针
 *
 * @return @c 1如果len和数据填写正确，否则
 *         @c 如果没有数据，则为0。
 */
int coap_get_data(const coap_pdu_t *pdu,
                  size_t *len,
                  const uint8_t **data);

/**
 * 从PDU中检索数据，支持跨越多个PDU的大量数据。
 *
 * 注意：当PDU被销毁时，返回时指向的数据将被销毁。
 *
 * @param pdu    指定的PDU。
 * @param len    返回当前数据的长度
 * @param data   返回当前数据的指针
 * @param offset 返回当前数据从包含多个块的主体开始的偏移量（RFC7959）
 * @param total  返回正文的总大小。如果偏移量+长度<总长度，则有更多数据要遵循。
 *
 * @return @c 1如果len、data、offset和total正确填写，否则
 *         @c 如果没有数据，则为0。
 */
int coap_get_data_large(const coap_pdu_t *pdu,
                        size_t *len,
                        const uint8_t **data,
                        size_t *offset,
                        size_t *total);

/**
 * 获取与@p PDU关联的PDU代码。
 *
 * @param pdu PDU对象。
 *
 * @return PDU代码。
 */
coap_pdu_code_t coap_pdu_get_code(const coap_pdu_t *pdu);

/**
 * 设置@p PDU中的PDU代码。
 *
 * @param pdu PDU对象。
 * @param code 要在PDU中设置的代码。
 */
void coap_pdu_set_code(coap_pdu_t *pdu, coap_pdu_code_t code);

/**
 * 获取与@p PDU关联的PDU类型。
 *
 * @param pdu PDU对象。
 *
 * @return PDU类型。
 */
coap_pdu_type_t coap_pdu_get_type(const coap_pdu_t *pdu);

/**
 * 设置@p PDU中的PDU类型。
 *
 * @param pdu PDU对象。
 * @param type 要为PDU设置的类型。
 */
void coap_pdu_set_type(coap_pdu_t *pdu, coap_pdu_type_t type);

/**
 * 获取与@p pdu关联的令牌。
 *
 * @param pdu PDU对象。
 *
 * @return 令牌信息。
 */
coap_bin_const_t coap_pdu_get_token(const coap_pdu_t *pdu);

/**
 * 获取与@p pdu关联的消息id。
 *
 * @param pdu PDU对象。
 *
 * @return 消息id。
 */
coap_mid_t coap_pdu_get_mid(const coap_pdu_t *pdu);

/**
 * 设置@p pdu中的消息id。
 *
 * @param pdu PDU对象。
 * @param mid 要在PDU中设置的消息id值。
 *
 */
void coap_pdu_set_mid(coap_pdu_t *pdu, coap_mid_t mid);

/** @} */

#endif /* COAP_PDU_H_ */

