/* coap_riot。h——libcoap的RIOT特定定义
 *
 * 版权所有（C）2019奥拉夫·伯格曼<bergmann@tzi.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

#ifndef COAP_RIOT_H_
#define COAP_RIOT_H_

#ifndef LIBCOAP_MSG_QUEUE_SIZE
/**
 * 用于在网络接口和coap堆栈之间传递消息的队列大小。*/
#define LIBCOAP_MSG_QUEUE_SIZE (32U)
#endif /* LIBCOAP_MSG_QUEUE_SIZE */

#ifndef LIBCOAP_MAX_SOCKETS
/**
 * 同时考虑用于读取或写入的套接字的最大数量。*/
#define LIBCOAP_MAX_SOCKETS (16U)
#endif /* LIBCOAP_MAX_SOCKETS */

/**
 * 必须在RIOT CoAP线程中调用此函数以进行RIOT特定的初始化。
 */
void coap_riot_startup(void);

#endif /* COAP_RIOT_H_ */

