/*
 * subscribe.h—CoAP的订阅处理，请参阅RFC7641
 *
 * 版权所有（C）2010-122014-2021 Olaf Bergmann<bergmann@tzi.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

/**
 * @file 订阅.h
 * @brief 定义应用程序可见的订阅信息
 */

#ifndef COAP_SUBSCRIBE_H_
#define COAP_SUBSCRIBE_H_

/**
 * @defgroup 用于与观测处理接口的观测资源观测API函数（RFC7641）@{
 */

/**
 * GET/FETCH请求选项COAP_option_OBSERVE中的值COAP_OBSERVE_UESTABLE表示请求了新的观察关系（发送方地址、令牌）。
 */
#define COAP_OBSERVE_ESTABLISH 0

/**
 * GET/FETCH请求选项COAP_option_OBSERVE中的值COAP_OBSERVE_CANCEL表示必须取消（发送方地址、令牌）的观察关系。
 */
#define COAP_OBSERVE_CANCEL 1

/**
 * Set whether a @p 资源是可观察的。如果资源是可观察的，并且客户端在请求包中设置了COAP_OPTION_OBSERVE，那么每当资源的状态发生变化（调用COAP_resource_trigger_OBSERVE（））时，就会发送一个观察者响应。
 *
 * @param resource 要使用的CoAP资源。
 * @param mode     @如果要设置Observable，则为c 1，否则为@c 0。
 *
 */
void coap_resource_set_get_observable(coap_resource_t *resource, int mode);

/**
 * 为所有@p资源的观察者启动Observe数据包的发送，如果不是NULL，可以选择匹配@p查询
 *
 * @param resource 要使用的CoAP资源。
 * @param query    要匹配的查询或NULL
 *
 * @return         @如果已触发观察，则为c 1，否则为@c 0。
 */
int
coap_resource_notify_observers(coap_resource_t *resource,
                               const coap_string_t *query);

/** @} */

#endif /* COAP_SUBSCRIBE_H_ */

