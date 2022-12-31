/*
 * str.h—要在CoAP库中使用的字符串
 *
 * 版权所有（C）2010-2011 Olaf Bergmann<bergmann@tzi.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

#ifndef COAP_STR_H_
#define COAP_STR_H_

#include <string.h>


/**
 * @defgroup 字符串处理支持用于处理字符串和二进制数据的API函数@{
 */

/*
 * 注意：字符串和二进制使用等效对象。字符串可能包含可读的文本信息，二进制则不会。
 */

/**
 * CoAP字符串数据定义
 */
typedef struct coap_string_t {
  size_t length;    /**<字符串长度*/
  uint8_t *s;       /**<字符串数据*/
} coap_string_t;

/**
 * 带常量数据的CoAP字符串数据定义
 */
typedef struct coap_str_const_t {
  size_t length;    /**<字符串长度*/
  const uint8_t *s; /**<只读字符串数据*/
} coap_str_const_t;

#define COAP_SET_STR(st,l,v) { (st)->length = (l), (st)->s = (v); }

/**
 * CoAP二进制数据定义
 */
typedef struct coap_binary_t {
  size_t length;    /**<二进制数据长度*/
  uint8_t *s;       /**<二进制数据*/
} coap_binary_t;

/**
 * 带常量数据的CoAP二进制数据定义
 */
typedef struct coap_bin_const_t {
  size_t length;    /**<二进制数据长度*/
  const uint8_t *s; /**<只读二进制数据*/
} coap_bin_const_t;

/**
 * 返回一个新的字符串对象，该对象分配的存储空间至少为+1字节。来电者有责任填写所有适当的信息。必须使用coap_delete_string（）释放字符串。
 *
 * @param size 要为字符串数据分配的大小。
 *
 * @return       指向新对象的指针或出错时的@c NULL。
 */
coap_string_t *coap_new_string(size_t size);

/**
 * 删除给定字符串并释放分配的所有内存。
 *
 * @param string 要释放的字符串。
 */
void coap_delete_string(coap_string_t *string);

/**
 * 返回一个新的常量字符串对象，该对象分配了至少+1字节的存储空间，并将提供的数据复制到字符串对象中。必须使用coap_delete_str_const（）释放字符串。
 *
 * @param data 要放入新字符串对象的数据。
 * @param size 为二进制字符串数据分配的大小。
 *
 * @return       指向新对象的指针或出错时的@c NULL。
 */
coap_str_const_t *coap_new_str_const(const uint8_t *data, size_t size);

/**
 * 删除给定的常量字符串并释放所有分配的内存。
 *
 * @param string 要释放的字符串。
 */
void coap_delete_str_const(coap_str_const_t *string);

/**
 * 返回一个新的二进制对象，分配的存储空间至少为字节。来电者有责任填写所有适当的信息。必须使用coap_delete_binary（）释放coap_binary_t对象。
 *
 * @param size 为二进制数据分配的大小。
 *
 * @return       指向新对象的指针或出错时的@c NULL。
 */
coap_binary_t *coap_new_binary(size_t size);

/**
 * 删除给定的coap_binary_t对象并释放分配的所有内存。
 *
 * @param binary 要释放的coap_binary_t对象。
 */
void coap_delete_binary(coap_binary_t *binary);

/**
 * 调整给定coap_binary_t对象的大小。来电者有责任填写所有适当的附加信息。
 *
 * Note: If there is an error, @p 二进制文件需要由coap_delete_binary（）单独释放。
 *
 * @param binary 要调整大小的coap_binary_t对象。
 * @param new_size 要为二进制数据分配的新大小。
 *
 * @return       指向新对象的指针或出错时的@c NULL。
 */
coap_binary_t *coap_resize_binary(coap_binary_t *binary, size_t new_size);

/**
 * 获取指定的字节数组（文本）并创建一个coap_bin_const_t*返回一个新的常量二进制对象，该对象至少分配了大小为字节的存储空间，并将提供的数据复制到二进制对象中。必须使用coap_delete_bin_const（）释放二进制数据。
 *
 * @param data 要放入新字符串对象的数据。
 * @param size 为二进制数据分配的大小。
 *
 * @return       指向新对象的指针或出错时的@c NULL。
 */
coap_bin_const_t *coap_new_bin_const(const uint8_t *data, size_t size);

/**
 * 删除给定的常量二进制数据并释放所有分配的内存。
 *
 * @param binary 要释放的二进制数据。
 */
void coap_delete_bin_const(coap_bin_const_t *binary);

#ifndef COAP_MAX_STR_CONST_FUNC
#define COAP_MAX_STR_CONST_FUNC 2
#endif /* COAP_MAX_STR_CONST_FUNC */

/**
 * 获取指定的字节数组（文本）并创建coap_str_const_t*
 *
 * 注意：数组有2个深度，因为函数调用中最多有两个coap_make_str_const调用。e、 g.coap_add_attr（）。警告：如果存在局部变量赋值，这些赋值将围绕变量[COAP_MAX_STR_CONST_FUNC]集合循环。目前没有这样的例子。
 *
 * @param string 要转换为coap_str_const_t的常量字符串*
 *
 * @return       指向包含coap_str_const_t结果的两个静态变量之一的指针
 */
coap_str_const_t *coap_make_str_const(const char *string);

/**
 * 比较两个字符串是否相等
 *
 * @param string1 第一个字符串。
 * @param string2 第二个字符串。
 *
 * @return         @如果字符串相等，则为c 1，否则为c 0。
 */
#define coap_string_equal(string1,string2) \
        ((string1)->length == (string2)->length && ((string1)->length == 0 || \
         ((string1)->s && (string2)->s && \
          memcmp((string1)->s, (string2)->s, (string1)->length) == 0)))

/**
 * 比较两个二进制数据是否相等
 *
 * @param binary1 第一个二进制数据。
 * @param binary2 第二个二进制数据。
 *
 * @return         @如果二进制数据等于，则为c1，否则为c0。
 */
#define coap_binary_equal(binary1,binary2) \
        ((binary1)->length == (binary2)->length && ((binary1)->length == 0 || \
         ((binary1)->s && (binary2)->s && \
          memcmp((binary1)->s, (binary2)->s, (binary1)->length) == 0)))

/** @} */

#endif /* COAP_STR_H_ */

