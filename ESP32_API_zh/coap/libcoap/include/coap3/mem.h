/*
 * 内存。h—CoAP内存处理
 *
 * 版权所有（C）2010-20112014-2015奥拉夫·伯格曼<bergmann@tzi.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

#ifndef COAP_MEM_H_
#define COAP_MEM_H_

#include <stdlib.h>

#ifndef WITH_LWIP
/**
 * 初始化libcoap的内存管理。在coap_malloc（）可以在受约束的设备上使用之前，必须调用此函数一次。
 */
void coap_memory_init(void);
#endif /* WITH_LWIP */

/**
 * coap_malloc_Type（）的类型说明符。可以对内存对象进行类型化，以便于使用类型对象数组，而不是在受限设备上进行动态内存管理。
 */
typedef enum {
  COAP_STRING,
  COAP_ATTRIBUTE_NAME,
  COAP_ATTRIBUTE_VALUE,
  COAP_PACKET,
  COAP_NODE,
  COAP_CONTEXT,
  COAP_ENDPOINT,
  COAP_PDU,
  COAP_PDU_BUF,
  COAP_RESOURCE,
  COAP_RESOURCEATTR,
#ifdef HAVE_LIBTINYDTLS
  COAP_DTLS_SESSION,
#endif
  COAP_SESSION,
  COAP_OPTLIST,
  COAP_CACHE_KEY,
  COAP_CACHE_ENTRY,
  COAP_LG_XMIT,
  COAP_LG_CRCV,
  COAP_LG_SRCV,
} coap_memory_tag_t;

#ifndef WITH_LWIP

/**
 * Allocates a chunk of @p 大小字节，并返回指向新
 * allocated memory. The @p 类型用于在受约束的设备上选择适当的存储容器。coap_malloc_type（）分配的存储必须使用coap_free_type（（）释放。
 *
 * @param type 要存储的对象的类型。
 * @param size 请求的字节数。
 * @return     指向已分配存储的指针或出错时的@c NULL。
 */
void *coap_malloc_type(coap_memory_tag_t type, size_t size);

/**
 * Reallocates a chunk @p 由coap_malloc_type（）或coap_realloc_type（）创建的p字节，并返回指向新分配的内存的指针
 * @p 大小仅支持COAP_STRING类型。
 *
 * Note: If there is an error, @p p将需要通过coap_free_type（）单独释放。
 *
 * @param type 要存储的对象的类型。
 * @param p    coap_malloc_type（）分配的内存指针。
 * @param size 请求的字节数。
 * @return     指向已分配存储的指针或出错时的@c NULL。
 */
void *coap_realloc_type(coap_memory_tag_t type, void *p, size_t size);

/**
 * Releases the memory that was allocated by coap_malloc_type(). The type tag @p 类型必须与用于分配所指向对象的类型相同
 * @p .
 *
 * @param type 要释放的对象的类型。
 * @param p    coap_malloc_type（）分配的内存指针。
 */
void coap_free_type(coap_memory_tag_t type, void *p);

/**
 * coap_malloc_type（）的包装函数，以实现向后兼容性。
 */
COAP_STATIC_INLINE void *coap_malloc(size_t size) {
  return coap_malloc_type(COAP_STRING, size);
}

/**
 * 包装器函数到coap_free_type（）以实现向后兼容性。
 */
COAP_STATIC_INLINE void coap_free(void *object) {
  coap_free_type(COAP_STRING, object);
}

#endif /* 不是WITH_LWIP*/

#ifdef WITH_LWIP

#include <lwip/memp.h>

/* lwip不需要初始化（或者更准确地说：lwip必须在coap激活时完全初始化）*/
COAP_STATIC_INLINE void coap_memory_init(void) {}

/* 检查大小是否等于memp声明中给出的大小将是很好的，但我目前没有看到一种标准的方法来检查，而不需要定制memp池并依赖其语法
 */
#define coap_malloc_type(type, size) memp_malloc(MEMP_ ## type)
#define coap_free_type(type, p) memp_free(MEMP_ ## type, p)

/* 这些只是来做uri的。c happy，其中字符串分配没有条件化。
 */
COAP_STATIC_INLINE void *coap_malloc(size_t size) {
  LWIP_ASSERT("coap_malloc must not be used in lwIP", 0);
}

COAP_STATIC_INLINE void coap_free(void *pointer) {
  LWIP_ASSERT("coap_free must not be used in lwIP", 0);
}

#endif /* WITH_LWIP */

#endif /* COAP_MEM_H_ */

