/*
 * coap_asn1_内部。h——ASN。libcoap的1个函数
 *
 * 版权所有（C）2020 Jon Shallow<supjps-libcoap@jpshallow.com>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

/**
 * @file coap_asn1_内部.h
 * @brief 煤层气。1内部信息
 */

#ifndef COAP_ASN1_INTERNAL_H_
#define COAP_ASN1_INTERNAL_H_


/**
 * @defgroup asn1 ASN。1支持（内部）CoAP ASN。1不向应用程序公开的结构、枚举和函数@{
 */

typedef enum {
  COAP_ASN1_NONE = 0,
  COAP_ASN1_INTEGER = 2,
  COAP_ASN1_BITSTRING = 3,
  COAP_ASN1_OCTETSTRING = 4,
  COAP_ASN1_IDENTIFIER = 6,
} coap_asn1_tag_t;

/**
 * 回调以验证asn1标记和数据。
 *
 * 内部功能。
 *
 * @param data  标记和数据的开始
 * @param size  标记和数据的大小
 *
 * @return @c 1如果通过，否则@c 0如果失败
 */
typedef int (*asn1_validate)(const uint8_t *data, size_t size);

/**
 * 从当前@p ptr获取asn1长度。
 *
 * 内部功能。
 *
 * @param ptr  当前asn。1个对象长度指针
 *
 * @return asn的长度。1个对象@p ptr被更新为在长度之后。
 */
size_t asn1_len(const uint8_t **ptr);

/**
 * 从当前的@pptr获取asn1标记。
 *
 * 内部功能。
 *
 * @param ptr  当前asn。1个对象标记指针
 * @param constructed  如果构建了当前标记，则为1
 * @param class  标记的当前类
 *
 * @return 标签value.@pptr被更新为在标记之后。
 */
coap_asn1_tag_t asn1_tag_c(const uint8_t **ptr, int *constructed, int *class);

/**
 * 从当前的@pptr获取asn1标记和数据。
 *
 * 内部功能。
 *
 * @param ltag 要查找的标记
 * @param ptr  当前asn。1个对象指针
 * @param tlen asn的剩余大小。1个数据
 * @param validate 调用validate验证标记数据或@c NULL
 *
 * @return asn。1个标记和数据，如果找不到，则为@c NULL
 */
coap_binary_t *get_asn1_tag(coap_asn1_tag_t ltag, const uint8_t *ptr,
                            size_t tlen, asn1_validate validate);

/** @} */

#endif /* COAP_ASN1_INTERNAL_H_ */

