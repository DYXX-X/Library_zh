/*
 * encode.h—CoAP数据类型的编码和解码
 *
 * 版权所有（C）2010-2012 Olaf Bergmann<bergmann@tzi.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

#ifndef COAP_ENCODE_H_
#define COAP_ENCODE_H_

#if (BSD >= 199103) || defined(WITH_CONTIKI) || defined(_WIN32)
# include <string.h>
#else
# include <strings.h>
#endif

#include <stdint.h>

#ifndef HAVE_FLS
/* 仅当fls（）不可用时才包含此项*/
extern int coap_fls(unsigned int i);
#else
#define coap_fls(i) fls(i)
#endif

#ifndef HAVE_FLSLL
 /* 仅当flsll（）不可用时才包含此项*/
extern int coap_flsll(long long i);
#else
#define coap_flsll(i) flsll(i)
#endif

/**
 * @defgroup 编码编码/解码API API函数，用于内接/解码CoAP选项@{
 */

/**
 * 解码多个长度字节序列@p buf指向输入字节
 * sequence of length @p 长返回最多4字节的解码值。
 *
 * @param buf 要解码的输入字节序列
 * @param length 输入字节序列的长度
 *
 * @return      解码值
 */
unsigned int coap_decode_var_bytes(const uint8_t *buf, size_t length);

/**
 * 解码多个长度字节序列@p buf指向输入字节
 * sequence of length @p 长返回最多8字节的解码值。
 *
 * @param buf 要解码的输入字节序列
 * @param length 输入字节序列的长度
 *
 * @return      解码值
 */
uint64_t coap_decode_var_bytes8(const uint8_t *buf, size_t length);

/**
 * Encodes multiple-length byte sequences. @p buf指向足够长的输出缓冲区，以存储编码的字节@p值是要编码的4字节值。返回用于编码@p值的字节数或出错时的0。
 *
 * @param buf    要编码到的输出缓冲区
 * @param length 要编码到的输出缓冲区大小（必须足够）
 * @param value  要编码到缓冲区中的值
 *
 * @return       错误时用于编码@p值或@c 0的字节数。
 */
unsigned int coap_encode_var_safe(uint8_t *buf,
                                  size_t length,
                                  unsigned int value);

/**
 * Encodes multiple-length byte sequences. @p buf指向足够长的输出缓冲区，以存储编码的字节@p值是要编码的8字节值。返回用于编码@p值的字节数或出错时的0。
 *
 * @param buf    要编码到的输出缓冲区
 * @param length 要编码到的输出缓冲区大小（必须足够）
 * @param value  要编码到缓冲区中的值
 *
 * @return       错误时用于编码@p值或@c 0的字节数。
 */
unsigned int coap_encode_var_safe8(uint8_t *buf,
                                  size_t length,
                                  uint64_t value);

/** @} */

/**
 * @deprecated 请改用coap_encode_var_safe（）。提供向后兼容性。由于@p值的最大值为0xffffffff，并且buf通常定义为数组，因此如果buf[]小于buf[4]，则继续使用此变量是不安全的。
 *
 * 例如char buf[1]，oops。。coap_encode_var_bytes（buf，0xfff）；会导致oop被覆盖。只有通过代码检查才能发现此错误。coap_encode_var_safe（buf，sizeof（buf），0xfff）；将在运行时捕获此错误，应改用。
 */
COAP_STATIC_INLINE COAP_DEPRECATED int
coap_encode_var_bytes(uint8_t *buf, unsigned int value
) {
  return (int)coap_encode_var_safe(buf, sizeof(value), value);
}

#endif /* COAP_ENCODE_H_ */

