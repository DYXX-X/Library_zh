/*
 * coap_prng。h——伪随机数
 *
 * 版权所有（C）2010-2020 Olaf Bergmann<bergmann@tzi.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

/**
 * @file 凝结水
 * @brief 伪随机数
 */

#ifndef COAP_PRNG_H_
#define COAP_PRNG_H_

/**
 * @defgroup coap_prng伪随机数生成伪随机数的API函数@{
 */

#if defined(WITH_CONTIKI)
#include <string.h>

/**
 * 用长度随机字节填充缓冲区。这是coap_prng（）的默认实现。您可能需要更改contiki_prng_inmpl（），以便在特定平台上使用更好的prng。
 */
COAP_STATIC_INLINE int
contiki_prng_impl(unsigned char *buf, size_t len) {
  uint16_t v = random_rand();
  while (len > sizeof(v)) {
    memcpy(buf, &v, sizeof(v));
    len -= sizeof(v);
    buf += sizeof(v);
    v = random_rand();
  }

  memcpy(buf, &v, len);
  return 1;
}

#define coap_prng(Buf,Length) contiki_prng_impl((Buf), (Length))
#define coap_prng_init(Value) random_init((uint16_t)(Value))

#elif defined(WITH_LWIP) && defined(LWIP_RAND)

COAP_STATIC_INLINE int
lwip_prng_impl(unsigned char *buf, size_t len) {
  u32_t v = LWIP_RAND();
  while (len > sizeof(v)) {
    memcpy(buf, &v, sizeof(v));
    len -= sizeof(v);
    buf += sizeof(v);
    v = LWIP_RAND();
  }

  memcpy(buf, &v, len);
  return 1;
}

#define coap_prng(Buf,Length) lwip_prng_impl((Buf), (Length))
#define coap_prng_init(Value) (void)Value

#else

/**
 * 随机数生成器函数的数据类型。函数必须
 * fill @p len字节的随机数据输入缓冲区，从@pout开始。成功时，函数应返回1，否则返回0。
 */
typedef int (*coap_rand_func_t)(void *out, size_t len);

/**
 * 用默认函数@p rng替换当前的随机数生成函数。
 *
 * @param rng  要使用的随机数生成函数。
 */
void coap_set_prng(coap_rand_func_t rng);

/**
 * 使用给定的
 * @p 种子默认的随机数生成函数将使用getrandom（）（如果可用），忽略种子。
 *
 * @param seed  伪随机数生成器的种子。
 */
void coap_prng_init(unsigned int seed);

/**
 * Fills @p buf使用默认的伪随机数生成器生成@plen随机字节。可以使用coap_set_PRNG（）更改默认PRNG。当@p len随机字节已写入@p buf时，此函数返回1，否则返回0。
 *
 * @param buf  要用随机字节填充的缓冲区。
 * @param len  要写入@p buf的随机字节数。
 *
 * @return 成功时为1，否则为0。
 */
int coap_prng(void *buf, size_t len);

#endif /* POSIX */

/** @} */

#endif /* COAP_PRNG_H_ */

