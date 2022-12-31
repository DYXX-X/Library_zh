/*
 * coap_block_内部。h——不暴露于应用程序编程的结构、枚举和函数
 *
 * Copyright (C) 2010-2021 Olaf Bergmann <bergmann@tzi.org> 版权所有（C）2021 Jon Shallow<supjps-libcoap@jpshallow.com>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

/**
 * @file coap_block_内部.h
 * @brief COAP块内部信息
 */

#ifndef COAP_BLOCK_INTERNAL_H_
#define COAP_BLOCK_INTERNAL_H_

#include "coap_pdu_internal.h"
#include "resource.h"

/**
 * @defgroup block_internal块（内部）不向应用程序公开的结构、枚举和函数@{
 */

typedef enum {
  COAP_RECURSE_OK,
  COAP_RECURSE_NO
} coap_recurse_t;

struct coap_lg_range {
  uint32_t begin;
  uint32_t end;
};

#define COAP_RBLOCK_CNT 4
/**
 * 跟踪接收块的结构
 */
typedef struct coap_rblock_t {
  uint32_t used;
  uint32_t retry;
  struct coap_lg_range range[COAP_RBLOCK_CNT];
  coap_tick_t last_seen;
} coap_rblock_t;

/**
 * 跟踪区块1特定信息（请求）的结构
 */
typedef struct coap_l_block1_t {
  coap_binary_t *app_token; /**<原始PDU令牌*/
  uint8_t token[8];      /**<上次使用的令牌*/
  size_t token_length;   /**<令牌长度*/
  uint32_t count;        /**<为有效负载发送的数据包数*/
} coap_l_block1_t;

/**
 * 跟踪区块2特定信息的结构（响应）
 */
typedef struct coap_l_block2_t {
  coap_resource_t *resource; /**<关联资源*/
  coap_string_t *query;  /**<资源的关联查询*/
  uint64_t etag;         /**<ETag值*/
  coap_time_t maxage_expire; /**<此条目过期时*/
} coap_l_block2_t;

/**
 * 用于保存大体积（多块）传输信息的结构
 */
struct coap_lg_xmit_t {
  struct coap_lg_xmit_t *next;
  uint8_t blk_size;      /**<大块传输大小*/
  uint16_t option;       /**<大块传输CoAP选项*/
  int last_block;        /**<最后确认的块编号*/
  const uint8_t *data;   /**<大数据指针*/
  size_t length;         /**<大数据长度*/
  size_t offset;         /**<下一次传输的大数据偏移*/
  union {
    coap_l_block1_t b1;
    coap_l_block2_t b2;
  } b;
  coap_pdu_t pdu;        /**<骨架PDU*/
  coap_tick_t last_payload; /**<上次发送MAX_PAYLOAD的时间或0*/
  coap_tick_t last_used; /**<上次发送所有数据的时间或0*/
  coap_release_large_data_t release_func; /**<大数据去分配功能*/
  void *app_ptr;         /**＜application为de alloc函数提供ptr*/
};

/**
 * 用于容纳大量（多个块）客户端接收信息的结构
 */
struct coap_lg_crcv_t {
  struct coap_lg_crcv_t *next;
  uint8_t observe[3];    /**<观察数据（如果设置）（仅24位）*/
  uint8_t observe_length;/**<观测数据长度*/
  uint8_t observe_set;   /**<如果这是观察接收PDU，则设置*/
  uint8_t etag_set;      /**<设置ETag是否在接收PDU中*/
  uint8_t etag_length;   /**<ETag长度*/
  uint8_t etag[8];       /**<ETag用于块检查*/
  uint16_t content_format; /**<块集的内容格式*/
  uint8_t last_type;     /**<最后请求类型（CON/NON）*/
  uint8_t initial;       /**<如果设置，尚未使用*/
  uint8_t szx;           /**<单个块的大小*/
  size_t total_len;      /**<长度如SIZE2选项所示*/
  coap_binary_t *body_data; /**<用于重新组装整个车身*/
  coap_binary_t *app_token; /**<应用程序请求PDU令牌*/
  uint8_t base_token[8]; /**<已建立的基本PDU令牌*/
  size_t base_token_length; /**<令牌长度*/
  uint8_t token[8];      /**<上次使用的令牌*/
  size_t token_length;   /**<令牌长度*/
  coap_pdu_t pdu;        /**<骨架PDU*/
  coap_rblock_t rec_blocks; /**<接收块列表*/
  coap_tick_t last_used; /**<上次发送所有数据的时间或0*/
  uint16_t block_option; /**<使用中的块选项*/
};

/**
 * 用于容纳大型主体（多个块）服务器接收信息的结构
 */
struct coap_lg_srcv_t {
  struct coap_lg_srcv_t *next;
  uint8_t observe[3];    /**<观察数据（如果设置）（仅24位）*/
  uint8_t observe_length;/**<观测数据长度*/
  uint8_t observe_set;   /**<如果这是观察接收PDU，则设置*/
  uint8_t rtag_set;      /**<设置RTag是否在接收PDU中*/
  uint8_t rtag_length;   /**<RTag长度*/
  uint8_t rtag[8];       /**<RTag用于块检查*/
  uint16_t content_format; /**<块集的内容格式*/
  uint8_t last_type;     /**<最后请求类型（CON/NON）*/
  uint8_t szx;           /**<单个块的大小*/
  size_t total_len;      /**<长度由SIZE1选项指示*/
  coap_binary_t *body_data; /**<用于重新组装整个车身*/
  size_t amount_so_far;  /**<到目前为止看到的数据量*/
  coap_resource_t *resource; /**<关联资源*/
  coap_str_const_t *uri_path; /**如果资源未知，则设置为uri_path*/
  coap_rblock_t rec_blocks; /**<接收块列表*/
  uint8_t last_token[8]; /**<上次使用的令牌*/
  size_t last_token_length; /**<令牌长度*/
  coap_mid_t last_mid;   /**<此组数据包的上次接收时间*/
  coap_tick_t last_used; /**<上次发送数据的时间或0*/
  uint16_t block_option; /**<使用中的块选项*/
};

coap_lg_crcv_t * coap_block_new_lg_crcv(coap_session_t *session,
                                        coap_pdu_t *pdu);

void coap_block_delete_lg_crcv(coap_session_t *session,
                               coap_lg_crcv_t *lg_crcv);

coap_tick_t coap_block_check_lg_crcv_timeouts(coap_session_t *session,
                                              coap_tick_t now);

void coap_block_delete_lg_srcv(coap_session_t *session,
                               coap_lg_srcv_t *lg_srcv);

coap_tick_t coap_block_check_lg_srcv_timeouts(coap_session_t *session,
                                              coap_tick_t now);

int coap_handle_request_send_block(coap_session_t *session,
                                   coap_pdu_t *pdu,
                                   coap_pdu_t *response,
                                   coap_resource_t *resource,
                                   coap_string_t *query);

int coap_handle_request_put_block(coap_context_t *context,
                                  coap_session_t *session,
                                  coap_pdu_t *pdu,
                                  coap_pdu_t *response,
                                  coap_resource_t *resource,
                                  coap_string_t *uri_path,
                                  coap_opt_t *observe,
                                  coap_string_t *query,
                                  coap_method_handler_t h,
                                  int *added_block);

int coap_handle_response_send_block(coap_session_t *session, coap_pdu_t *rcvd);

int coap_handle_response_get_block(coap_context_t *context,
                                   coap_session_t *session,
                                   coap_pdu_t *sent,
                                   coap_pdu_t *rcvd,
                                   coap_recurse_t recursive);

void coap_block_delete_lg_xmit(coap_session_t *session,
                               coap_lg_xmit_t *lg_xmit);

coap_tick_t coap_block_check_lg_xmit_timeouts(coap_session_t *session,
                                              coap_tick_t now);

/**
 * 为coap_add_data_large*（）函数执行所有工作的函数。
 *
 * @param session  要关联数据的会话。
 * @param pdu      要与数据关联的PDU。
 * @param resource 与数据关联的资源（BLOCK2）。
 * @param query    与数据关联的查询（BLOCK2）。
 * @param maxage   数据的最长寿命。如果@c-1，则没有maxage（BLOCK2）。
 * @param etag     如果不是0（BLOCK2），则使用ETag。
 * @param length   要传输的数据长度。
 * @param data     要传输的数据。
 * @param release_func 要调用以取消分配@p数据的函数，如果不需要该函数，则为NULL。
 * @param app_ptr  调用release_func（）时应用程序可以提供的指针。
 *
 * @return @c 1如果传输启动成功，否则@c 0。
 */
int coap_add_data_large_internal(coap_session_t *session,
                        coap_pdu_t *pdu,
                        coap_resource_t *resource,
                        const coap_string_t *query,
                        int maxage,
                        uint64_t etag,
                        size_t length,
                        const uint8_t *data,
                        coap_release_large_data_t release_func,
                        void *app_ptr);

/**
 * 该函数检查由coap_add_data_large_response（）创建的新形成的lg_xmit中的代码是否已更新。
 *
 * @param session  会议
 * @param response 要检查的响应PDU
 * @param resource 请求的资源
 * @param query    请求的查询
 */
void coap_check_code_lg_xmit(coap_session_t *session, coap_pdu_t *response,
                             coap_resource_t *resource, coap_string_t *query);

/** @} */

#endif /* COAP_BLOCK_INTERNAL_H_ */

