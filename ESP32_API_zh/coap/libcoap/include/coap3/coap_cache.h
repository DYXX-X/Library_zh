/* coap_cache。h—CoAP请求的缓存
*
* 版权所有（C）2020 Olaf Bergmann<bergmann@tzi.org>
*
 * SPDX许可证标识符：BSD-2-Clause
 *
* 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
*/

/**
 * @file coap_cache.h
 * @brief 为CoAP请求提供简单的缓存请求存储
 */

#ifndef COAP_CACHE_H_
#define COAP_CACHE_H_

#include "coap_forward_decls.h"

/**
 * @defgroup 缓存缓存支持CoAP缓存的API函数@{
 */

/**
 * 当缓存条目被删除/释放时，回调以释放应用程序数据。
 *
 * @param data  要释放的应用程序数据。
 */
typedef void (*coap_cache_app_data_free_callback_t)(void *data);

typedef enum coap_cache_session_based_t {
  COAP_CACHE_NOT_SESSION_BASED,
  COAP_CACHE_IS_SESSION_BASED
} coap_cache_session_based_t;

typedef enum coap_cache_record_pdu_t {
  COAP_CACHE_NOT_RECORD_PDU,
  COAP_CACHE_RECORD_PDU
} coap_cache_record_pdu_t;

/**
 * 计算给定CoAP PDU的缓存密钥。看见https://tools.ietf.org/html/rfc7252#section-5.6，以了解CoAP缓存密钥的解释。
 *
 * 可以从缓存密钥中删除特定的CoAP选项。例如，BLOCK1和BLOCK2选项-将它们包含在客户端或服务器环境中没有实际意义，但应包含在代理缓存环境中，在该环境中按块缓存内容。这是通过调用coap_cache_ignore_options（）函数全局完成的。
 *
 * 注意：调用者需要通过调用coap_cache_delete_key（）释放返回的缓存密钥。
 *
 * @param session 如果设置了@p session_based，则要添加到缓存密钥中的会话。
 * @param pdu     要为其计算缓存密钥的CoAP PDU。
 * @param session_based 如果是基于会话的缓存密钥，则为COAP_CACHE_IS_SESSION_BASED，否则为COAP_ACHE_NOT_SESSION_BASED。
 *
 * @return        返回的缓存键或@c NULL（如果失败）。
 */
coap_cache_key_t *coap_cache_derive_key(const coap_session_t *session,
                                        const coap_pdu_t *pdu,
                                   coap_cache_session_based_t session_based);

/**
 * 计算给定CoAP PDU的缓存密钥。看见https://tools.ietf.org/html/rfc7252#section-5.6，以了解CoAP缓存密钥的解释。
 *
 * 可以从缓存密钥中删除特定的CoAP选项。例如，BLOCK1和BLOCK2选项-将它们包含在客户端或服务器环境中没有实际意义，但应包含在代理缓存环境中，在该环境中按块缓存内容。通过指定@p cache_ignore_count和
 * @p cache_ignore_options。
 *
 * 注意：调用者需要通过调用coap_cache_delete_key（）释放返回的缓存密钥。
 *
 * @param session 如果设置了@p session_based，则要添加到缓存密钥中的会话。
 * @param pdu     要为其计算缓存密钥的CoAP PDU。
 * @param session_based 如果是基于会话的缓存密钥，则为COAP_CACHE_IS_SESSION_BASED，否则为COAP_ACHE_NOT_SESSION_BASED。
 * @param ignore_options 要忽略的选项数组。
 * @param ignore_count   要忽略的选项数。
 *
 * @return        返回的缓存键或@c NULL（如果失败）。
 */
coap_cache_key_t *coap_cache_derive_key_w_ignore(const coap_session_t *session,
                                      const coap_pdu_t *pdu,
                                      coap_cache_session_based_t session_based,
                                      const uint16_t *ignore_options,
                                      size_t ignore_count);

/**
 * 删除缓存密钥。
 *
 * @param cache_key 要删除的缓存密钥。
 */
void coap_delete_cache_key(coap_cache_key_t *cache_key);

/**
 * 定义计算缓存密钥时不包括的CoAP选项。始终忽略定义为“非缓存”和“观察”选项的选项。
 *
 * @param context   保存忽略选项信息的上下文。
 * @param options   要忽略的选项数组。
 * @param count     要忽略的选项数。使用0重置选项匹配。
 *
 * @return          @如果成功，返回@c 1，否则返回@c 0。
 */
int coap_cache_ignore_options(coap_context_t *context,
                              const uint16_t *options, size_t count);

/**
 * 创建一个新的缓存条目哈希，该哈希由从PDU派生的缓存密钥键控。
 *
 * If @p 如果设置了sessionbased，则在释放会话时将删除该缓存条目。
 * If @p 如果设置了record_pdu，则在删除此缓存条目时，复制的pdu将被释放。
 *
 * 缓存条目保存在上下文哈希列表中。
 *
 * @param session   用于从中派生上下文的会话。
 * @param pdu       用于生成缓存密钥的pdu。
 * @param record_pdu COAP_CCACHE_RECORD_PDU（如果要获取PDU副本以供以后使用），否则COAP_CACHE_NOT_RECORD_ PDU。
 * @param session_based 若要将此缓存条目和会话（嵌入在缓存条目中）相关联，则为COAP_CCACHE_IS_SESSION_BASED，否则为COAP_ACHE_NOT_SESSION_BASED。
 * @param idle_time 缓存条目过期前的空闲时间（秒）。如果设置为0，则它不会过期（但如果会话被删除且基于会话，则会被删除）。
 *
 * @return          返回的缓存键或@c NULL（如果失败）。
 */
coap_cache_entry_t *coap_new_cache_entry(coap_session_t *session,
                                 const coap_pdu_t *pdu,
                                 coap_cache_record_pdu_t record_pdu,
                                 coap_cache_session_based_t session_based,
                                 unsigned int idle_time);

/**
 * 从哈希列表中删除一个缓存条目，并释放除app_data之外的所有适当内容。
 *
 * @param context     要使用的上下文。
 * @param cache_entry 要删除的缓存项。
 */
void coap_delete_cache_entry(coap_context_t *context,
                             coap_cache_entry_t *cache_entry);

/**
 * Searches for a cache-entry identified by @p cache_key。此函数返回相应的缓存项，如果未找到，则返回@c NULL。
 *
 * @param context    要使用的上下文。
 * @param cache_key  获取哈希coap项的缓存键。
 *
 * @return 如果找不到@p cache_key或@c NULL的缓存项。
 */
coap_cache_entry_t *coap_cache_get_by_key(coap_context_t *context,
                                          const coap_cache_key_t *cache_key);

/**
 * Searches for a cache-entry corresponding to @p pdu。此函数返回相应的缓存项，如果未找到，则返回@c NULL。
 *
 * @param session    要使用的会话。
 * @param pdu        要搜索的CoAP请求。
 * @param session_based 如果要使用基于会话的缓存密钥，则为COAP_CACHE_IS_SESSION_BASED，否则为COAP_ACHE_NOT_SESSION_BASED。
 *
 * @return 如果找不到@p请求的缓存项或@c NULL。
 */
coap_cache_entry_t *coap_cache_get_by_pdu(coap_session_t *session,
                                          const coap_pdu_t *pdu,
                                   coap_cache_session_based_t session_based);

/**
 * 返回存储在@p coap_cache项中的PDU信息。
 *
 * @param cache_entry CoAP缓存条目。
 *
 * @return 存储在cache_entry中的PDU信息，如果最初未复制PDU，则为NULL。
 */
const coap_pdu_t *coap_cache_get_pdu(const coap_cache_entry_t *cache_entry);

/**
 * Stores @p 具有给定缓存项的数据。此函数覆盖以前用@p cache_entry存储的任何值。
 *
 * @param cache_entry CoAP缓存条目。
 * @param data 要与缓存项一起存储的数据指针。请注意，此数据必须在@p cache_entry的生存期内有效。
 * @param callback 删除缓存项时调用以释放此数据的回调，如果不需要，则调用@c NULL。
 */
void coap_cache_set_app_data(coap_cache_entry_t *cache_entry, void *data,
                             coap_cache_app_data_free_callback_t callback);

/**
 * Returns any application-specific data that has been stored with @p cache_entry使用函数coap_cache_set_app_data（）。此功能将
 * return @c 如果未存储数据，则为NULL。
 *
 * @param cache_entry CoAP缓存条目。
 *
 * @return 先前存储的数据指针，如果未存储数据，则为@c NULL。
 */
void *coap_cache_get_app_data(const coap_cache_entry_t *cache_entry);

/** @} */

#endif  /* COAP_CACHE_H */

