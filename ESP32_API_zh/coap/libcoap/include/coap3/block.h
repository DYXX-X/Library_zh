/*
 * 块h——分块传输
 *
 * 版权所有（C）2010-20122014-2015奥拉夫·伯格曼<bergmann@tzi.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

#ifndef COAP_BLOCK_H_
#define COAP_BLOCK_H_

#include "encode.h"
#include "option.h"
#include "pdu.h"

/**
 * @defgroup 使用CoAP block选项处理PDU的块块传输API函数@{
 */

#ifndef COAP_MAX_BLOCK_SZX
/**
 * 块选项中SZX组件的最大值。
 */
#define COAP_MAX_BLOCK_SZX      6
#endif /* COAP_MAX_BLOCK_SZX */

/**
 * 块选项的结构。
 */
typedef struct {
  unsigned int num;       /**<块编号*/
  unsigned int m:1;       /**如果后面有更多块，则<1，否则为0*/
  unsigned int szx:3;     /**<块大小*/
} coap_block_t;

#define COAP_BLOCK_USE_LIBCOAP  0x01 /* 使用libcoap执行块请求*/
#define COAP_BLOCK_SINGLE_BODY  0x02 /* 将数据作为一个整体交付*/

/**
 * Returns the value of the least significant byte of a Block option @p 选择对于零长度选项（即num==m==szx==0），COAP_OPT_BLOCK_LAST返回@c NULL。
 */
#define COAP_OPT_BLOCK_LAST(opt) \
  (coap_opt_length(opt) ? (coap_opt_value(opt) + (coap_opt_length(opt)-1)) : 0)

/**返回Block选项的More位的值@popt。*/
#define COAP_OPT_BLOCK_MORE(opt) \
  (coap_opt_length(opt) ? (*COAP_OPT_BLOCK_LAST(opt) & 0x08) : 0)

/**返回Block选项@p opt的SZX字段的值。*/
#define COAP_OPT_BLOCK_SZX(opt)  \
  (coap_opt_length(opt) ? (*COAP_OPT_BLOCK_LAST(opt) & 0x07) : 0)

/**
 * Returns the value of field @c 给定块选项@p block_opt中的num。
 */
unsigned int coap_opt_block_num(const coap_opt_t *block_opt);

/**
 * Checks if more than @p 对于块大小为1<<（@pszx+4）的数据，需要num个块来传递@pdata_len字节的数据。
 */
COAP_STATIC_INLINE int
coap_more_blocks(size_t data_len, unsigned int num, uint16_t szx) {
  return ((num+1) << (szx + 4)) < data_len;
}

#if 0
/**设置@p block_opt中的更多位*/
COAP_STATIC_INLINE void
coap_opt_block_set_m(coap_opt_t *block_opt, int m) {
  if (m)
    *(coap_opt_value(block_opt) + (coap_opt_length(block_opt) - 1)) |= 0x08;
  else
    *(coap_opt_value(block_opt) + (coap_opt_length(block_opt) - 1)) &= ~0x08;
}
#endif

/**
 * Initializes @p 来自@pdu的块@p编号必须是COAP_OPTION_BLOCK1
 * or COAP_OPTION_BLOCK2. When option @p 数字在@ppdu中找到，@p块用该选项中的值初始化，函数返回该值
 * @c 1.否则，返回@c 0。
 *
 * @param pdu    要搜索选项@p编号的pdu。
 * @param number 要搜索的选项编号（必须是COAP_option_BLOCK1或COAP_option_BLOCK2）。
 * @param block  要初始化的块结构。
 *
 * @return       @成功时为c 1，否则为@c 0。
 */
int coap_get_block(const coap_pdu_t *pdu, coap_option_num_t number,
                   coap_block_t *block);

/**
 * Writes a block option of type @p 消息@p pdu的编号。如果请求的块大小太大，无法容纳@p pdu，则会相应地减小。当需要更少的空间时，对最终块进行例外。资源的实际长度在@p data_length中指定。
 *
 * This function may change *block to reflect the values written to @p pdu。由于该函数考虑了剩余空间@ppdu，因此在coap_write_block_opt（）返回后，不应添加更多选项。
 *
 * @param block       要使用的块结构。返回时，此对象将根据已写入@ppdu的值进行更新。
 * @param number      COAP_OPTION_BLOCK1或COAP_OPTION_BLOCK2。
 * @param pdu         应写入块选项的消息。
 * @param data_length 将通过调用coap_add_block（）添加到@p pdu的实际数据的长度。
 *
 * @return            @c 1表示成功，或负值表示错误。
 */
int coap_write_block_opt(coap_block_t *block,
                         coap_option_num_t number,
                         coap_pdu_t *pdu,
                         size_t data_length);

/**
 * Adds the @p block_num块，大小为1<<（@pblock_szx+4），从源@p数据到@p pdu。
 *
 * @param pdu       要添加块的消息。
 * @param len       @p数据的长度。
 * @param data      要填充块的源数据。
 * @param block_num 实际块号。
 * @param block_szx 块的编码大小@p block_number。
 *
 * @return          @成功时为c 1，否则为@c 0。
 */
int coap_add_block(coap_pdu_t *pdu,
                   size_t len,
                   const uint8_t *data,
                   unsigned int block_num,
                   unsigned char block_szx);

/**
 * 将有效载荷重新组装到车身中
 *
 * @param body_data 到目前为止保存表示形式的主体的数据指针，如果是第一次，则为NULL。
 * @param length    @p数据的长度。
 * @param data      用于更新主体的有效负载数据。
 * @param offset    @p数据在正文中的偏移量。
 * @param total     身体的估计总尺寸。
 *
 * @return          正文的当前表示形式，如果错误，则为@c NULL。
 *                  If NULL, @p body_data将被取消分配。
 */
coap_binary_t *
coap_block_build_body(coap_binary_t *body_data, size_t length,
                      const uint8_t *data, size_t offset, size_t total);

/**
 * Adds the appropriate part of @p 数据发送到@p响应pdu。如果需要块，则将适当的块添加到PDU并发送。添加ETAG选项，该选项是整个数据的哈希值，如果数据将被拆分为请求处理程序使用的块。
 *
 * 注意：应用程序将被调用，以处理大型主体的每个数据包。考虑改用coap_add_data_response_larget（）。
 *
 * @param request    请求pdu。
 * @param response   响应pdu。
 * @param media_type 数据的格式。
 * @param maxage     数据的最长寿命。如果@c-1，则没有maxage。
 * @param length     数据的总长度。
 * @param data       要传输的整个数据块。
 *
 */
void
coap_add_data_blocked_response(const coap_pdu_t *request,
                               coap_pdu_t *response,
                               uint16_t media_type,
                               int maxage,
                               size_t length,
                               const uint8_t* data);

/**
 * Callback handler for de-allocating the data based on @p app_ptr提供给coap_add_data_large_（）函数。
 *
 * @param session 此数据关联的会话
 * @param app_ptr 应用程序提供的指针提供给coap_add_data_large_函数。
 */
typedef void (*coap_release_large_data_t)(coap_session_t *session,
                                          void *app_ptr);

/**
 * Associates given data with the @p 作为第二个参数传递的pdu。
 *
 * 如果所有数据都可以在一个PDU中传输，这在功能上与coap_add_data（）相同，但在数据传输后将调用@p release_func（如果不是NULL）。
 *
 * 用于客户端请求。
 *
 * 如果数据跨越多个PDU，则数据将使用BLOCK1选项和SIZE1选项进行传输。基础库将处理各个块的传输。一旦传输了数据体（或发生故障），则
 * @p release_func（如果不是NULL）将被调用，因此应用程序可以
 * de-allocate the @p 基于@papp_data的数据。在数据传输完成之前，应用程序有责任不更改@p数据的内容。
 *
 * 应用程序无需在
 * @p pdu。
 *
 * 每个PDU只能调用一次coap_add_data_large_request（）（或可选的coap_add_data_large_*（）函数），并且必须是传输PDU之前的最后一次PDU更新。当调用coap_send（）时，（潜在的）初始数据将被传输。
 *
 * 注意：COAP_BLOCK_USE_LIBCOAP必须由COAP_context_set_BLOCK_mode（）设置，以使LIBCOAP在使用此函数时正常工作。
 *
 * @param session  要关联数据的会话。
 * @param pdu      要与数据关联的PDU。
 * @param length   要传输的数据长度。
 * @param data     要传输的数据。
 * @param release_func 如果不需要函数，则调用该函数来取消分配@p数据或@c NULL。
 * @param app_ptr  调用release_func（）时应用程序可以提供的指针。
 *
 * @return @c 1如果添加成功，否则@c 0。
 */
int coap_add_data_large_request(coap_session_t *session,
                                coap_pdu_t *pdu,
                                size_t length,
                                const uint8_t *data,
                                coap_release_large_data_t release_func,
                                void *app_ptr);

/**
 * Associates given data with the @p 作为第四个参数传递的响应pdu。
 *
 * If all the data can be transmitted in a single PDU, this is functionally the same as coap_add_data() except @p release_func（如果不是NULL）将在数据传输后被调用。可以根据需要添加MEDIA_TYPE、MAXAGE和ETAG选项。
 *
 * 由服务器请求处理程序用于创建响应。
 *
 * 如果数据跨越多个PDU，则数据将使用BLOCK2（响应）选项以及SIZE2和ETAG选项进行传输。基础库将处理各个块的传输。一旦数据主体被传输（或
 * failure occurred), then @p release_func（如果不是NULL）将被调用
 * application can de-allocate the @p 基于@papp_data的数据。在数据传输完成之前，应用程序有责任不更改@p数据的内容。
 *
 * 应用程序无需在
 * @p pdu。
 *
 * coap_add_data_large_response（）（或可选的coap_add_data_large*（）函数）对于每个PDU只能调用一次，并且必须是从请求处理程序函数返回之前的最后一次PDU更新。
 *
 * 注意：COAP_BLOCK_USE_LIBCOAP必须由COAP_context_set_BLOCK_mode（）设置，以使LIBCOAP在使用此函数时正常工作。
 *
 * @param resource   与数据关联的资源。
 * @param session    coap会话。
 * @param request    请求pdu。
 * @param response   响应pdu。
 * @param query      从（原始）请求pdu获取的查询。
 * @param media_type 数据的格式。
 * @param maxage     数据的最长寿命。如果@c-1，则没有maxage。
 * @param etag       如果不是0，则使用ETag。
 * @param length     数据的总长度。
 * @param data       要传输的整个数据块。
 * @param release_func 要调用以取消分配@p数据的函数，如果不需要该函数，则为NULL。
 * @param app_ptr    调用release_func（）时应用程序可以提供的指针。
 *
 * @return @c 1如果添加成功，否则@c 0。
 */
int
coap_add_data_large_response(coap_resource_t *resource,
                             coap_session_t *session,
                             const coap_pdu_t *request,
                             coap_pdu_t *response,
                             const coap_string_t *query,
                             uint16_t media_type,
                             int maxage,
                             uint64_t etag,
                             size_t length,
                             const uint8_t *data,
                             coap_release_large_data_t release_func,
                             void *app_ptr);

/**
 * 设置用于处理RFC7959的上下文级别CoAP块处理位。当创建会话时，这些位流到会话，如果对等方不支持某些内容，则会话block_mode中可能会禁用适当的位。然后，会话block_mode向下流到coap_crcv_t或coap_srcv_t，在这里，适当的位可能再次被禁用。
 *
 * 注意：必须在设置会话之前调用此函数。
 *
 * 注意：如果LIBCOAP要执行所有块跟踪和请求，则必须设置COAP_BLOCK_USE_LIBCOAP，否则应用程序必须执行所有这些工作（如果未调用COAP_context_set_BLOCK_mode（），则为默认值）。
 *
 * @param context        coap_context_t对象。
 * @param block_mode     零个或多个COAP_BLOCK_或'd选项
 */
void coap_context_set_block_mode(coap_context_t *context,
                                  uint8_t block_mode);

/**
 * 取消客户端大型接收逻辑正在跟踪的观察。（必须调用coap_context_set_block_mode（））这将触发向服务器发送观察取消pdu。
 *
 * @param session  用于观察的会话。
 * @param token    用于启动观察的原始令牌。
 * @param message_type COAP_MESSAGE_类型（NON或CON）将观察取消pdu发送为。
 *
 * @return @c 1如果观察取消传输启动成功，否则@c 0。
 */
int coap_cancel_observe(coap_session_t *session, coap_binary_t *token,
                    coap_pdu_type_t message_type);

/**@}*/

#endif /* COAP_BLOCK_H_ */

