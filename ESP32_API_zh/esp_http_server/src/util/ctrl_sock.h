/*
 * SPDX文件版权文本：2018-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/**
 * \文件ctrl_sock。用于select（）唤醒的h \ brief控制插座
 *
 * LWIP不允许一种简单的机制来按需唤醒选择时休眠的线程。这是向网络服务器发送控制命令的常见要求。此控制套接字API有助于实现这一点。
 */
#ifndef _CTRL_SOCK_H_
#define _CTRL_SOCK_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 创建控制套接字
 *
 *      LWIP不允许一种简单的机制来按需唤醒选择时休眠的线程。这是向网络服务器发送控制命令的常见要求。此控制套接字API有助于实现这一点。
 *
 *      此API将在指定端口上创建UDP控制套接字。它将返回一个套接字描述符，然后可以在select（）中将其添加到fd_set中
 *
 * @param[in] port 控制套接字将侦听的本地端口
 *
 * @return -可以在select中添加到fd_set的套接字描述符。
 *         -如果小于零，则返回错误代码
 */
int cs_create_ctrl_sock(int port);

/**
 * @brief 释放控制插座
 *
 *      这将释放先前使用cs_create_ctrl_sock（）创建的控制套接字
 *
 * @param[in] fd 与此控制套接字关联的套接字描述符
 */
void cs_free_ctrl_sock(int fd);

/**
 * @brief 将数据发送到控制套接字
 *
 *      此API将数据发送到控制套接字。如果服务器在select（）上被控制套接字阻止，则此调用将唤醒该服务器。
 *
 * @param[in] send_fd 发送ctrl消息的套接字
 * @param[in] port 创建控制套接字的端口
 * @param[in] data 指向包含要在套接字上发送的数据的缓冲区的指针
 * @param[in] data_len 指向数据的缓冲区中包含的数据的长度
 *
 * @return  -发送到控制套接字的字节数
 *          -如果小于零，则返回错误代码
 */
int cs_send_to_ctrl_sock(int send_fd, int port, void *data, unsigned int data_len);

/**
 * @brief 从控制插座接收数据
 *
 *      此API接收发送到控制套接字的任何数据。这通常会从服务器线程调用，以处理此套接字上的任何命令。
 *
 * @param[in] fd 控制套接字的套接字描述符
 * @param[in] data 指向缓冲区的指针，该缓冲区将用于存储从控制套接字接收的数据
 * @param[in] data_len 可以存储在数据指向的缓冲区中的数据的最大长度
 *
 * @return  -从控制套接字接收的字节数
 *          -如果小于零，则返回错误代码
 */
int cs_recv_from_ctrl_sock(int fd, void *data, unsigned int data_len);

#ifdef __cplusplus
}
#endif

#endif /* ! _CTRL_SOCK_H_ */

