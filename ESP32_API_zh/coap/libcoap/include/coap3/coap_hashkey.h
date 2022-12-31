/*
 * coap_hashkey。h——哈希键类型和助手函数的定义
 *
 * 版权所有（C）2010-2011 Olaf Bergmann<bergmann@tzi.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

/**
 * @file coap_hashkey.h
 * @brief 哈希键类型和助手函数的定义
 */

#ifndef COAP_HASHKEY_H_
#define COAP_HASHKEY_H_

#include "libcoap.h"
#include "uthash.h"
#include "str.h"

typedef unsigned char coap_key_t[4];

#ifndef coap_hash
/**
 * 对长度为@plen的给定字符串@ps计算快速哈希并存储
 * the result into @p h、 根据具体实现，此函数不能用作单向函数来检查消息完整性或类似功能。
 *
 * @param s   用于哈希计算的字符串。
 * @param len @p s的长度。
 * @param h   用于存储计算的哈希键的结果缓冲区。
 */
void coap_hash_impl(const unsigned char *s, size_t len, coap_key_t h);

#define coap_hash(String,Length,Result) \
  coap_hash_impl((String),(Length),(Result))

/* 这用于控制资源的预设哈希键。*/
#define COAP_DEFAULT_HASH
#else
#undef COAP_DEFAULT_HASH
#endif /* coap_hash*/

/**
 * Calls coap_hash() with given @c coap_string_t对象作为参数。
 *
 * @param Str 必须包含指向coap字符串对象的指针。
 * @param H   用于存储结果的coap_key_t对象。
 *
 * @hideinitializer
 */
#define coap_str_hash(Str,H) {               \
    assert(Str);                             \
    memset((H), 0, sizeof(coap_key_t));      \
    coap_hash((Str)->s, (Str)->length, (H)); \
  }

#endif /* COAP_HASHKEY_H_ */

