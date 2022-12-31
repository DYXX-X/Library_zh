/*
 * coap_tcp_内部。h—libcoap的TCP函数
 *
 * 版权所有（C）2019-2020奥拉夫·伯格曼<bergmann@tzi.org>和其他
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

/**
 * @file coap_tcp_内部.h
 * @brief COAP tcp内部信息
 */

#ifndef COAP_TCP_INTERNAL_H_
#define COAP_TCP_INTERNAL_H_

#include "coap_io.h"

/**
 * @defgroup tcp tcp支持（内部）不向应用程序公开的CoAP tcp结构、枚举和函数@{
 */

#if !COAP_DISABLE_TCP

/**
 * 创建新的TCP套接字并启动连接
 *
 * 内部功能。
 *
 * @param sock 填写插座信息的位置
 * @param local_if 要使用的本地地址或NULL
 * @param server 要连接到的地址
 * @param default_port 如果未在@p服务器中设置，则使用的端口
 * @param local_addr 连接启动后填写本地地址
 * @param remote_addr 使用远程地址启动连接后填写
 *
 * @return @c 1如果成功，@c 0如果失败
*/
int
coap_socket_connect_tcp1(coap_socket_t *sock,
                         const coap_address_t *local_if,
                         const coap_address_t *server,
                         int default_port,
                         coap_address_t *local_addr,
                         coap_address_t *remote_addr);

/**
 * 完成TCP连接
 *
 * 内部功能。
 *
 * @param sock 要使用的套接字信息
 * @param local_addr 填写最终本地地址
 * @param remote_addr 填写最终远程地址
 *
 * @return @c 1如果成功，@c 0如果失败
*/
int
coap_socket_connect_tcp2(coap_socket_t *sock,
                         coap_address_t *local_addr,
                         coap_address_t *remote_addr);

/**
 * 创建新的TCP套接字，然后侦听新的传入TCP会话
 *
 * 内部功能。
 *
 * @param sock 填写插座信息的位置
 * @param listen_addr 要侦听新传入会话的地址
 * @param bound_addr 填写TCP层正在侦听新传入TCP会话的地址
 *
 * @return @c 1如果成功，@c 0如果失败
*/
int
coap_socket_bind_tcp(coap_socket_t *sock,
                     const coap_address_t *listen_addr,
                     coap_address_t *bound_addr);

/**
 * 接受新的传入TCP会话
 *
 * 内部功能。
 *
 * @param server 用于接受TCP连接的套接字信息
 * @param new_client 用新的传入会话信息填充套接字信息
 * @param local_addr 填写当地地址
 * @param remote_addr 填写远程地址
 *
 * @return @c 1如果成功，@c 0如果失败
*/
int
coap_socket_accept_tcp(coap_socket_t *server,
                       coap_socket_t *new_client,
                       coap_address_t *local_addr,
                       coap_address_t *remote_addr);

#endif /* !COAP_DISABLE_TCP */

/** @} */

#endif /* COAP_TCP_INTERNAL_H_ */

