/*
 * 资源h——通用资源处理
 *
 * 版权所有（C）201020112014-2021 Olaf Bergmann<bergmann@tzi.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

/**
 * @file 资源.h
 * @brief 通用资源处理
 */

#ifndef COAP_RESOURCE_H_
#define COAP_RESOURCE_H_

#ifndef COAP_RESOURCE_CHECK_TIME
/**检查资源是否已更改的间隔（秒）。*/
#define COAP_RESOURCE_CHECK_TIME 2
#endif /* COAP_RESOURCE_CHECK_TIME */

#include "async.h"
#include "block.h"
#include "str.h"
#include "pdu.h"
#include "net.h"
#include "subscribe.h"

/**
 * @defgroup coap_resource用于设置资源的资源配置API函数@{
 */

/**
 * 消息处理程序函数的定义
 */
typedef void (*coap_method_handler_t)
  (coap_resource_t *,
   coap_session_t *,
   const coap_pdu_t * /* 要求*/,
   const coap_string_t * /* 查询字符串*/,
   coap_pdu_t * /* 回答*/);

#define COAP_ATTR_FLAGS_RELEASE_NAME  0x1
#define COAP_ATTR_FLAGS_RELEASE_VALUE 0x2

/**传递给coap_resource_init（）的URI由coap_delete_resource（）释放。*/
#define COAP_RESOURCE_FLAGS_RELEASE_URI 0x1

/**
 * 默认情况下，将发送不可确认的通知。RFC 7641第4.5节https://tools.ietf.org/html/rfc7641#section-4.5 Libcoap将始终发送每五个可确认的数据包。
 */
#define COAP_RESOURCE_FLAGS_NOTIFY_NON  0x0

/**
 * 通知将以可确认的方式发送。RFC 7641第4.5节https://tools.ietf.org/html/rfc7641#section-4.5
 */
#define COAP_RESOURCE_FLAGS_NOTIFY_CON  0x2

/**
 * 通知将始终以不可确认的方式发送。这违反了RFC 7641第4.5节https://tools.ietf.org/html/rfc7641#section-4.5，但DOTS信号信道协议需要，该协议需要在有损DDoS攻击环境中运行。https://tools.ietf.org/html/rfc8782#section-4.4.2.1
 */
#define COAP_RESOURCE_FLAGS_NOTIFY_NON_ALWAYS  0x4

/**
 * 创建新的资源对象并将链接字段初始化为字符串
 * @p uri路径。此函数返回新的coap_resource_t对象。
 *
 * If the string is going to be freed off by coap_delete_resource() when COAP_RESOURCE_FLAGS_RELEASE_URI is set in @p 标志，则coap_str_constt的“s”变量必须指向常量文本，或指向分配的coap_str-constt参数内的数据。
 *
 * @param uri_path 新资源的字符串URI路径。通常不需要前导“/”，例如“full/path/for/resources”。
 * @param flags    内存管理标志（特别是内存释放）。可能的值：@n
 *
 *                 COAP_REOURCE_FLAGS_RELEASE_URI如果设置了此标志，则传递给COAP_RESOURCE_init（）的URI将由COAP_delete_RESOURCE（）释放@n
 *
 *                 COAP_RESOURCE_FLAGS_NOTIFY_CON如果设置了此标志，则COAP观察通知将由default.@n
 *
 *                 COAP_REOURCE_FLAGS_NOTIFY_NON（默认）如果设置了此标志，COAP观察通知将由default.@n
 *
 *                  如果标志设置为0，则考虑COAP_RESOURCE_flags_NOTIFY_NON。
 *
 * @return         指向新对象的指针或出错时的@c NULL。
 */
coap_resource_t *coap_resource_init(coap_str_const_t *uri_path,
                                    int flags);


/**
 * 为支持PUT的未知资源处理程序创建新的资源对象。
 *
 * 与使用coap_register_handler（）将其他处理程序添加到coap_resource_init（）创建的资源相同，可以将POST、GET、DELETE等处理程序添加到此资源。应用程序负责通过使用coap_resource_init（）创建新资源（应该为资源删除指定DELETE处理程序）或维护活动资源列表来管理未知资源。
 *
 * 注意：每个上下文只能有一个未知资源处理程序-附加一个新的资源处理程序将覆盖先前的定义。
 *
 * 注意：无法通过GET请求观察未知资源
 *       -PUT（或POST）处理程序需要创建单独的资源，并使该资源可观察。
 *
 * 此函数返回新的coap_resource_t对象。
 *
 * @param put_handler 要向@p资源注册未知Uri路径的PUT处理程序。
 *
 * @return       指向新对象的指针或出错时的@c NULL。
 */
coap_resource_t *coap_resource_unknown_init(coap_method_handler_t put_handler);

/**
 * 创建用于处理代理URI的新资源对象。此函数返回新的coap_resource_t对象。
 *
 * 注意：每个上下文只能有一个代理资源处理程序-附加一个新的代理资源处理会覆盖先前的定义。
 *
 * @param handler 处理所有请求类型的PUT/POST/GET等处理程序。
 * @param host_name_count 提供的host_name_list条目数。必须至少提供1个。
 * @param host_name_list 此代理已知的深度host_name_count名称数组。
 *
 * @return         指向新对象的指针或出错时的@c NULL。
 */
coap_resource_t *coap_resource_proxy_uri_init(coap_method_handler_t handler,
                      size_t host_name_count, const char *host_name_list[]);

/**
 * Returns the resource identified by the unique string @p uri路径。如果找不到资源，此函数将返回@c NULL。
 *
 * @param context  查找此资源的上下文。
 * @param uri_path  资源的唯一字符串uri。
 *
 * @return         指向资源的指针，如果找不到，则返回@c NULL。
 */
coap_resource_t *coap_get_resource_from_uri_path(coap_context_t *context,
                                                coap_str_const_t *uri_path);

/**
 * 从@p资源获取uri_path。
 *
 * @param resource 要检查的CoAP资源。
 *
 * @return         uri_path（如果存在）或@c NULL（否则）。
 */
coap_str_const_t* coap_resource_get_uri_path(coap_resource_t *resource);

/**
 * 将resource@presource的通知消息类型设置为给定
 * @p 模式

 * @param resource 要更新的资源。
 * @param mode     必须是@c COAP_REOURCE_FLAGS_NOTIFY_NON之一
 *                 or @c COAP_RESOURCE_FLAGS_NOTIFY_CON.
 */
void coap_resource_set_mode(coap_resource_t *resource, int mode);

/**
 * 设置user_data。user_data仅由库用户使用，可以用作处理程序函数中用户定义的上下文。
 *
 * @param resource 要将数据附加到的资源
 * @param data     要附加到user_Data字段的数据。此指针仅用于存储，数据仍由用户控制
 */
void coap_resource_set_userdata(coap_resource_t *resource, void *data);

/**
 * 获取user_data。user_data仅由库用户使用，可以用作处理程序函数中的上下文。
 *
 * @param resource 要从中检索user_data的资源
 *
 * @return        user_data指针
 */
void *coap_resource_get_userdata(coap_resource_t *resource);

/**
 * 发布资源user_data回调函数的定义
 */
typedef void (*coap_resource_release_userdata_handler_t)(void *user_data);

/**
 * 定义在删除资源以释放资源的user_data中保存的数据时要使用的上下文范围回调。
 *
 * @param context  与释放回调关联的上下文
 * @param callback 当资源被删除或为NULL时要调用的回调
 *
 */
void coap_resource_release_userdata_handler(coap_context_t *context,
                          coap_resource_release_userdata_handler_t callback);

/**
 * Registers the given @p @p上下文的资源。资源必须由coap_resource_init（）或coap_resource_unknown_init（）创建，分配给资源的存储将由coap_delete_resource（）释放。
 *
 * @param context  要使用的上下文。
 * @param resource 要存储的资源。
 */
void coap_add_resource(coap_context_t *context, coap_resource_t *resource);

/**
 * Deletes a resource identified by @p 资源为该资源分配的存储将被释放，并从上下文中删除。
 *
 * @param context  存储资源的上下文。
 * @param resource 要删除的资源。
 *
 * @return         @如果找到（并销毁）资源，则为c 1，否则为@c 0。
 */
int coap_delete_resource(coap_context_t *context, coap_resource_t *resource);

/**
 * Registers the specified @p handler作为请求类型@p方法的消息处理程序
 *
 * @param resource 应为其注册处理程序的资源。
 * @param method   要处理的CoAP请求方法。
 * @param handler  要向@p资源注册的处理程序。
 */
void coap_register_handler(coap_resource_t *resource,
                           coap_request_t method,
                           coap_method_handler_t handler);

/**
 * Registers a new attribute with the given @p 资源由于属性的coap_str_const_字段将指向@p名称和@p值，因此调用者必须确保这些指针在属性的生存期内有效。

 * If the @p name和/或@p值字符串将在属性删除时通过在@p标志中设置COAP_ATTR_FLAGS_RELEASE_name或COAP_ATR_FLAGS_RELEAAE_value来释放，则COAP_str_const_t的“s”变量必须指向常量文本，或指向分配的COAP_str-const_t参数内的数据。
 *
 * @param resource 要向其注册属性的资源。
 * @param name     属性的名称作为字符串。
 * @param value    属性的值为字符串，如果没有，则为@c NULL。
 * @param flags    内存管理标志（特别是内存释放）。可能的值：@n
 *
 *                 COAP_ATTR_FLAGS_RELEASE_NAME如果设置了此标志，则当属性为deleted@n
 *
 *                 COAP_ATTR_FLAGS_RELEASE_VALUE如果设置了此标志，则当属性为deleted@n
 *
 * @return         指向新属性的指针或出错时的@c NULL。
 */
coap_attr_t *coap_add_attr(coap_resource_t *resource,
                           coap_str_const_t *name,
                           coap_str_const_t *value,
                           int flags);

/**
 * Returns @p 如果找到资源的coap_attr_t对象，则使用给定的@p名称，否则使用@c NULL。
 *
 * @param resource 要搜索属性@p名称的资源。
 * @param name     所请求属性的字符串名称。
 * @return         第一个具有指定的@p名称的属性，如果没有找到，则为@c NULL。
 */
coap_attr_t *coap_find_attr(coap_resource_t *resource,
                            coap_str_const_t *name);

/**
 * Returns @p 属性的值。
 *
 * @param attribute 指向属性的指针。
 *
 * @return 属性的值或@c NULL。
 */
coap_str_const_t *coap_attr_get_value(coap_attr_t *attribute);

/**
 * 状态字，用于编码条件打印或复制操作的结果，如coap_print_link（）。coap_print_status_t的低28位用于编码实际已打印的字符数，位28至31编码状态。设置COAP_PRINT_STATUS_ERROR时，输出过程中发生错误。在这种情况下，其他位未定义。COAP_PRINT_STATUS_TRUNC表示输出被截断，即打印将超过当前缓冲区。
 */
typedef unsigned int coap_print_status_t;

#define COAP_PRINT_STATUS_MASK  0xF0000000u
#define COAP_PRINT_OUTPUT_LENGTH(v) ((v) & ~COAP_PRINT_STATUS_MASK)
#define COAP_PRINT_STATUS_ERROR 0x80000000u
#define COAP_PRINT_STATUS_TRUNC 0x40000000u

/**
 * Writes a description of this resource in link-format to given text buffer. @p len必须初始化为@pbuf的最大长度，如果成功，将设置为实际写入的字符数。此函数
 * returns @c 成功时为1，错误时为@c 0。
 *
 * @param resource 要描述的资源。
 * @param buf      要将描述写入的输出缓冲区。
 * @param len      必须初始化为@p buf的长度，并将设置为打印链接说明的长度。
 * @param offset   资源描述中开始写入@p buf的偏移量。这对于处理Block2选项非常有用@p偏移在输出期间随着消耗而更新。
 *
 * @return 如果设置了COAP_PRINT_STATUS_ERROR，则发生错误。否则，较低的28位将指示实际输出到@p缓冲区的字符数。标志COAP_PRINT_STATUS_TRUNC表示输出已被截断。
 */
coap_print_status_t coap_print_link(const coap_resource_t *resource,
                                    unsigned char *buf,
                                    size_t *len,
                                    size_t *offset);

/** @} */

/**
 * Returns the resource identified by the unique string @p uri路径。如果找不到资源，此函数将返回@c NULL。
 *
 * @param context  查找此资源的上下文。
 * @param uri_path  资源的唯一字符串uri。
 *
 * @return         指向资源的指针，如果找不到，则返回@c NULL。
 */
coap_resource_t *coap_get_resource_from_uri_path(coap_context_t *context,
                                                coap_str_const_t *uri_path);

/**
 * @deprecated 请改用coap_resource_notify_observers（）。
 */
COAP_DEPRECATED int
coap_resource_set_dirty(coap_resource_t *r,
                        const coap_string_t *query);

#endif /* COAP_RESOURCE_H_ */

