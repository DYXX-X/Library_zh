/*
 * coap_resource_internal。h——通用资源处理
 *
 * 版权所有（C）201020112014-2021 Olaf Bergmann<bergmann@tzi.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

/**
 * @file 协同资源_内部.h
 * @brief 通用资源内部处理
 */

#ifndef COAP_RESOURCE_INTERNAL_H_
#define COAP_RESOURCE_INTERNAL_H_

#include "uthash.h"

/**
 * @defgroup coap_resource_internal Resources（内部）不向应用程序公开的结构、枚举和函数@{
 */

/**
* 与资源相关的属性的抽象。
*/
struct coap_attr_t {
  struct coap_attr_t *next; /**<指向链中下一个的指针或NULL*/
  coap_str_const_t *name;   /**<属性的名称*/
  coap_str_const_t *value;  /**<属性的值（可以为NULL）*/
  int flags;
};

/**
* 可以附加到coap_context_t的资源的抽象。密钥是uri_path。
*/
struct coap_resource_t {
  unsigned int dirty:1;          /**如果资源已更改，则<设置为1*/
  unsigned int partiallydirty:1; /**如果某些订阅者尚未收到上次更改的通知，则<设置为1*/
  unsigned int observable:1;     /**<可以观察到*/
  unsigned int cacheable:1;      /**<可以缓存*/
  unsigned int is_unknown:1;     /**<为未知处理程序创建的资源*/
  unsigned int is_proxy_uri:1;   /**<为代理URI处理程序创建的资源*/

  /**
   * 用于存储七个coap方法@cGET、@cPOST、@cPUT的处理程序，
   * @c DELETE、@c FETCH、@c PATCH和@c IPATCH。coap_dispatch（）将传入请求传递给handle_request（），然后传递给与其请求方法相对应的处理程序，如果没有处理程序可用，则生成4.05响应。
   */
  coap_method_handler_t handler[7];

  UT_hash_handle hh;

  coap_attr_t *link_attr; /**<链接格式中包含的属性*/
  coap_subscription_t *subscribers;  /**<此资源的观察员列表*/

  /**
   * 请求此资源的URI路径。此字段将指向静态或分配的内存，这些内存必须在资源的持续时间内保持不变。
   */
  coap_str_const_t *uri_path;  /**<用于此资源的哈希查找的密钥*/
  int flags; /**<零个或多个COAP_REOURCE_FLAGS_*或一起*/

  /**
  * “观察”选项的下一个值。每次资源更改时，必须增加此字段。仅发送较低的24位。
  */
  unsigned int observe;

  /**
   * 指向“拥有”此资源的上下文的指针。
   */
  coap_context_t *context;

  /**
   * 此主机已知的有效名称计数（代理支持）
   */
  size_t proxy_name_count;

  /**
   * 此主机已知的数组有效名称（代理支持）
   */
  coap_str_const_t ** proxy_name_list;

  /**
   * 此指针由用户控制。它可以用于存储coap处理程序的上下文。
   */
  void *user_data;

};

/**
 * Deletes all resources from given @p 并释放其存储空间。
 *
 * @param context 具有要删除的资源的CoAP上下文。
 */
void coap_delete_all_resources(coap_context_t *context);

#define RESOURCES_ADD(r, obj) \
  HASH_ADD(hh, (r), uri_path->s[0], (obj)->uri_path->length, (obj))

#define RESOURCES_DELETE(r, obj) \
  HASH_DELETE(hh, (r), (obj))

#define RESOURCES_ITER(r,tmp)  \
  coap_resource_t *tmp, *rtmp; \
  HASH_ITER(hh, (r), tmp, rtmp)

#define RESOURCES_FIND(r, k, res) {                     \
    HASH_FIND(hh, (r), (k)->s, (k)->length, (res)); \
  }

/**
 * 删除属性。注意：这仅供内部使用，因为它不会从其链中删除。
 *
 * @param attr 指向先前创建的属性的指针。
 *
 */
void coap_delete_attr(coap_attr_t *attr);

coap_print_status_t coap_print_wellknown(coap_context_t *,
                                         unsigned char *,
                                         size_t *, size_t,
                                         coap_opt_t *);


/** @} */

#endif /* COAP_RESOURCE_INTERNAL_H_ */

