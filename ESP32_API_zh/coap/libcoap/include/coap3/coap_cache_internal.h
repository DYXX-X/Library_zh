/*
 * coap_cache_内部。h—libcoap的缓存函数
 *
 * 版权所有（C）2019-2020奥拉夫·伯格曼<bergmann@tzi.org>和其他
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

/**
 * @file coap_cache_内部.h
 * @brief COAP缓存内部信息
 */

#ifndef COAP_CACHE_INTERNAL_H_
#define COAP_CACHE_INTERNAL_H_

#include "coap_io.h"

/**
 * @defgroup cache_internal cache Support（内部）CoAP缓存结构、枚举和不向应用程序公开的函数@{
 */

/* 以二进制格式保存摘要，通常为sha256，notls除外*/
typedef struct coap_digest_t {
  uint8_t key[32];
} coap_digest_t;

struct coap_cache_key_t {
  uint8_t key[32];
};

struct coap_cache_entry_t {
  UT_hash_handle hh;
  coap_cache_key_t *cache_key;
  coap_session_t *session;
  coap_pdu_t *pdu;
  void* app_data;
  coap_tick_t expire_ticks;
  unsigned int idle_timeout;
  coap_cache_app_data_free_callback_t callback;
};

/**
 * 使coap_cache_entry_t条目过期
 *
 * 内部功能。
 *
 * @param context 保存要退出的coap条目的上下文
 */
void coap_expire_cache_entries(coap_context_t *context);

typedef void coap_digest_ctx_t;

/**
 * 初始化coap_digest
 *
 * 内部功能。
 *
 * @return          摘要上下文或@c NULL（如果失败）。
 */
coap_digest_ctx_t *coap_digest_setup(void);

/**
 * 释放coap_digest_ctx_t。始终由coap_digest_final（）完成
 *
 * 内部功能。
 *
 * @param digest_ctx coap_digest上下文。
 */
void coap_digest_free(coap_digest_ctx_t *digest_ctx);

/**
 * 用下一块数据更新coap_digest信息
 *
 * 内部功能。
 *
 * @param digest_ctx coap_digest上下文。
 * @param data       指向数据的指针。
 * @param data_len   字节数。
 *
 * @return           @c 1成功，@c 0失败。
 */
int coap_digest_update(coap_digest_ctx_t *digest_ctx,
                      const uint8_t *data,
                      size_t data_len
                      );

/**
 * 将coap_digest信息最终确定为提供的
 * @p 消化缓冲区。
 *
 * 内部功能。
 *
 * @param digest_ctx    coap_digest上下文。
 * @param digest_buffer 指向要更新的摘要缓冲区的指针
 *
 * @return              @c 1成功，@c 0失败。
 */
int coap_digest_final(coap_digest_ctx_t *digest_ctx,
                      coap_digest_t *digest_buffer);

/** @} */

#endif /* COAP_CACHE_INTERNAL_H_ */

