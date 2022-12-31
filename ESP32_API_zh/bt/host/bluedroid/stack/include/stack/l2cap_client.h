/******************************************************************************
 * 版权所有（C）2014谷歌公司。
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

#ifndef _L2CAP_CLIENT_H_
#define _L2CAP_CLIENT_H_
#if (defined(L2CAP_CLIENT_INCLUDED) && L2CAP_CLIENT_INCLUDED == TRUE)

//#包括<hardware/bluetooth.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct buffer_t buffer_t;
typedef struct l2cap_client_t l2cap_client_t;

typedef struct {
    void (*connected)(l2cap_client_t *client, void *context);
    void (*disconnected)(l2cap_client_t *client, void *context);
    void (*read_ready)(l2cap_client_t *client, buffer_t *packet, void *context);
    void (*write_ready)(l2cap_client_t *client, void *context);
} l2cap_client_callbacks_t;

// 返回一个新缓冲区，该缓冲区具有足够的空间来容纳L2CAP负载的|size|字节。
// |size|必须大于零。如果缓冲区
// 无法分配。必须使用|buffer_free释放返回的缓冲区|
// 当不再需要时。
buffer_t *l2cap_buffer_new(size_t size);

// 创建并返回新的L2CAP客户端对象|回调|不能为NULL，并且
// 必须指定事件发生时应调用的一组函数
// 在L2CAP连接上|context|可以为NULL，并将作为参数传递
// 到|l2cap_client_callback_t|中的所有回调。必须释放返回的对象
// 具有|l2cap_client_free |。
l2cap_client_t *l2cap_client_new(const l2cap_client_callbacks_t *callbacks, void *context);

// 释放分配有|L2CAP_client_new|的L2CAP客户端对象|client|可以为NULL。
void l2cap_client_free(l2cap_client_t *client);

// 尝试将|client|连接到|remote_bdaddr指定的对等设备|
// 使用|psm|协议说明符。如果连接
// 操作可以启动，并将通过“已连接”指示完成
// 回调（成功）或“断开连接”回调（失败）。
//
// 当连接操作正在进行或
// 而|l2cap_client_is_connected||client|和|remote_bdaddr|不能为NULL。
// |psm|必须大于零。
bool l2cap_client_connect(l2cap_client_t *client, const bt_bdaddr_t *remote_bdaddr, uint16_t psm);

// 断开连接的|客户端|。此函数是异步和幂等的。它
// 将使用“断开连接”回调指示完成|client|不能为NULL。
void l2cap_client_disconnect(l2cap_client_t *client);

// 如果|client|已连接并准备好接受写入其中的数据，则返回true。
// |client|不能为NULL。
bool l2cap_client_is_connected(const l2cap_client_t *client);

// 将|package|中包含的数据写入连接的|客户端|。此函数返回
// 如果数据包已成功排队等待传递，则为true；如果客户端无法
// 此时接受更多数据。如果此函数返回false，则调用者必须等待
// 用于“write_ready”回调以向客户端写入其他数据。也不
// |client|nor|package|不能为NULL。
bool l2cap_client_write(l2cap_client_t *client, buffer_t *packet);

#endif  ///（已定义（L2CAP_CLIENT_INCLUDED）&&L2CAP_CLINENT_INCLUTED==TRUE）

#endif /*_L2CAP_CLIENT_H_*/

