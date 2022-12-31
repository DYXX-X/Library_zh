/** @file
 *  @brief 缓冲区管理。
 */

/*
 * SPDX文件版权文本：2015 Intel Corporation SPDX FileContributor:2018-2021 Espressif Systems（Shanghai）CO LTD
 *
 * SPDX许可证标识符：Apache-2.0
 */
#ifndef _BLE_MESH_BUF_H_
#define _BLE_MESH_BUF_H_

#include "mesh_config.h"
#include "mesh_types.h"
#include "mesh_slist.h"
#include "mesh_compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 未对齐的访问*/
#define UNALIGNED_GET(p)                    \
__extension__ ({                            \
    struct  __attribute__((__packed__)) {   \
        __typeof__(*(p)) __v;               \
    } *__p = (__typeof__(__p)) (p);         \
    __p->__v;                               \
})

#define BLE_MESH_NET_BUF_USER_DATA_SIZE     4

/**
 * @brief 网络缓冲库
 * @defgroup net_buf网络缓冲库
 * @ingroup 联网@{
 */

/* 缓冲区定义的各个部分需要对齐*/
#define __net_buf_align __aligned(sizeof(int))

/**
 *  @def NET_BUF_SIMPLE_DEFINE
 *  @brief 定义net_buf_simple堆栈变量。
 *
 *  这是一个助手宏，用于在堆栈上定义net_buf_simple对象。
 *
 *  @param _name net_buf_simple对象的名称。
 *  @param _size 缓冲区的最大数据存储。
 */
#define NET_BUF_SIMPLE_DEFINE(_name, _size) \
    uint8_t net_buf_data_##_name[_size];    \
    struct net_buf_simple _name = {         \
        .data  = net_buf_data_##_name,      \
        .len   = 0,                         \
        .size  = _size,                     \
        .__buf = net_buf_data_##_name,      \
    }

/**
 * @def NET_BUF_SIMPLE_DEFINE_STATIC
 * @brief 定义静态net_buf_simple变量。
 *
 * 这是一个辅助宏，用于定义静态net_buf_simple对象。
 *
 * @param _name net_buf_simple对象的名称。
 * @param _size 缓冲区的最大数据存储。
 */
#define NET_BUF_SIMPLE_DEFINE_STATIC(_name, _size)  \
    static uint8_t net_buf_data_##_name[_size];     \
    static struct net_buf_simple _name = {          \
        .data  = net_buf_data_##_name,              \
        .len   = 0,                                 \
        .size  = _size,                             \
        .__buf = net_buf_data_##_name,              \
    }

/**
 * @brief 简单的网络缓冲区表示。
 *
 * 这是net_buf对象的一个更简单的变体（实际上net_buf在内部使用net_buf_simple）。它不提供任何类型的引用计数、用户数据、动态分配，也不提供传递内核对象（如FIFOs）的能力。
 *
 * 这主要用于不需要普通net_buf的元数据并导致过多开销的场景。这可以是例如当缓冲区仅需要在堆栈上分配时，或者当缓冲区的访问和寿命受到良好控制和约束时。
 */
struct net_buf_simple {
    /**指向缓冲区中数据开头的指针。*/
    uint8_t *data;

    /**数据指针后面的数据长度。*/
    uint16_t len;

    /**此缓冲区可以存储的数据量。*/
    uint16_t size;

    /** 开始数据存储。不可直接访问（应改用数据指针）。
     */
    uint8_t *__buf;
};

/**
 * @def NET_BUF_SIMPLE
 * @brief 定义net_buf_simple堆栈变量并获取指向它的指针。
 *
 * 这是一个助手宏，用于在堆栈上定义net_buf_simple对象，并获取指向它的指针，如下所示：
 *
 * 结构net_buf_simple*my_buf=net_buf_simple（10）；
 *
 * 创建对象后，需要通过调用net_buf_simple_init（）对其进行初始化。
 *
 * @param _size 缓冲区的最大数据存储。
 *
 * @return 指向堆栈分配的net_buf_simple对象的指针。
 */
#define NET_BUF_SIMPLE(_size)                   \
    ((struct net_buf_simple *)(&(struct {       \
        struct net_buf_simple buf;              \
        uint8_t data[_size] __net_buf_align;    \
    }) {                                        \
        .buf.size = _size,                      \
        .buf.__buf = NULL,                      \
    }))

/**
 * @brief 初始化net_buf_simple对象。
 *
 * 这需要在使用net_buf_simple宏创建net_buf_simple对象后调用。
 *
 * @param buf 要初始化的缓冲区。
 * @param reserve_head 预留净空高度。
 */
static inline void net_buf_simple_init(struct net_buf_simple *buf,
                                       size_t reserve_head)
{
    if (!buf->__buf) {
        buf->__buf = (uint8_t *)buf + sizeof(*buf);
    }

    buf->data = buf->__buf + reserve_head;
    buf->len = 0;
}

/**
 * @brief 使用数据初始化net_buf_simple对象。
 *
 * 已使用外部数据初始化缓冲区对象。
 *
 * @param buf 要初始化的缓冲区。
 * @param data 外部数据指针
 * @param size 指向数据缓冲区的数据量（如果可以）。
 */
void net_buf_simple_init_with_data(struct net_buf_simple *buf,
                                   void *data, size_t size);

/**
 * @brief 重置缓冲区
 *
 * 重置缓冲区数据，使其可用于其他目的。
 *
 * @param buf 要重置的缓冲区。
 */
static inline void net_buf_simple_reset(struct net_buf_simple *buf)
{
    buf->len  = 0;
    buf->data = buf->__buf;
}

/**
 * 克隆缓冲区状态，使用相同的数据缓冲区。
 *
 * 初始化缓冲区以指向与现有缓冲区相同的数据。允许对相同数据进行操作，而不更改原始数据的长度和偏移量。
 *
 * @param original 要克隆的缓冲区。
 * @param clone 新克隆。
 */
void net_buf_simple_clone(const struct net_buf_simple *original,
                          struct net_buf_simple *clone);

/**
 * @brief 准备要添加到缓冲区末尾的数据
 *
 * 增加缓冲区的数据长度，以在结尾处容纳更多数据。
 *
 * @param buf 要更新的缓冲区。
 * @param len 用于增加长度的字节数。
 *
 * @return 缓冲区的原始尾部。
 */
void *net_buf_simple_add(struct net_buf_simple *buf, size_t len);

/**
 * @brief 将给定数量的字节从内存复制到缓冲区末尾
 *
 * 增加缓冲区的数据长度，以在结尾处容纳更多数据。
 *
 * @param buf 要更新的缓冲区。
 * @param mem 要添加的数据的位置。
 * @param len 要添加的数据长度
 *
 * @return 缓冲区的原始尾部。
 */
void *net_buf_simple_add_mem(struct net_buf_simple *buf, const void *mem,
                             size_t len);

/**
 * @brief 在缓冲区末尾添加（8位）字节
 *
 * 增加缓冲区的数据长度，以在结尾处容纳更多数据。
 *
 * @param buf 要更新的缓冲区。
 * @param val 要添加的字节值。
 *
 * @return 指向添加值的指针
 */
uint8_t *net_buf_simple_add_u8(struct net_buf_simple *buf, uint8_t val);

/**
 * @brief 在缓冲区末尾添加16位值
 *
 * 在缓冲区末尾添加小端字节格式的16位值。增加缓冲区的数据长度，以在结尾处容纳更多数据。
 *
 * @param buf 要更新的缓冲区。
 * @param val 要添加的16位值。
 */
void net_buf_simple_add_le16(struct net_buf_simple *buf, uint16_t val);

/**
 * @brief 在缓冲区末尾添加16位值
 *
 * 在缓冲区末尾添加16位的大端值。增加缓冲区的数据长度，以在结尾处容纳更多数据。
 *
 * @param buf 要更新的缓冲区。
 * @param val 要添加的16位值。
 */
void net_buf_simple_add_be16(struct net_buf_simple *buf, uint16_t val);

/**
 * @brief 在缓冲区末尾添加24位值
 *
 * 在缓冲区末尾以小端字节格式添加24位值。增加缓冲区的数据长度，以在结尾处容纳更多数据。
 *
 * @param buf 要更新的缓冲区。
 * @param val 要添加的24位值。
 */
void net_buf_simple_add_le24(struct net_buf_simple *buf, uint32_t val);

/**
 * @brief 在缓冲区末尾添加24位值
 *
 * 在缓冲区末尾添加24位的大端格式值。增加缓冲区的数据长度，以在结尾处容纳更多数据。
 *
 * @param buf 要更新的缓冲区。
 * @param val 要添加的24位值。
 */
void net_buf_simple_add_be24(struct net_buf_simple *buf, uint32_t val);

/**
 * @brief 在缓冲区末尾添加32位值
 *
 * 在缓冲区末尾添加小端字节格式的32位值。增加缓冲区的数据长度，以在结尾处容纳更多数据。
 *
 * @param buf 要更新的缓冲区。
 * @param val 要添加的32位值。
 */
void net_buf_simple_add_le32(struct net_buf_simple *buf, uint32_t val);

/**
 * @brief 在缓冲区末尾添加32位值
 *
 * 在缓冲区末尾添加32位大端格式的值。增加缓冲区的数据长度，以在结尾处容纳更多数据。
 *
 * @param buf 要更新的缓冲区。
 * @param val 要添加的32位值。
 */
void net_buf_simple_add_be32(struct net_buf_simple *buf, uint32_t val);

/**
 * @brief 在缓冲区末尾添加48位值
 *
 * 在缓冲区末尾添加小端字节格式的48位值。增加缓冲区的数据长度，以在结尾处容纳更多数据。
 *
 * @param buf 要更新的缓冲区。
 * @param val 要添加的48位值。
 */
void net_buf_simple_add_le48(struct net_buf_simple *buf, uint64_t val);

/**
 * @brief 在缓冲区末尾添加48位值
 *
 * 在缓冲区末尾以大端字节格式添加48位值。增加缓冲区的数据长度，以在结尾处容纳更多数据。
 *
 * @param buf 要更新的缓冲区。
 * @param val 要添加的48位值。
 */
void net_buf_simple_add_be48(struct net_buf_simple *buf, uint64_t val);

/**
 * @brief 在缓冲区末尾添加64位值
 *
 * 在缓冲区末尾添加小端字节格式的64位值。增加缓冲区的数据长度，以在结尾处容纳更多数据。
 *
 * @param buf 要更新的缓冲区。
 * @param val 要添加的64位值。
 */
void net_buf_simple_add_le64(struct net_buf_simple *buf, uint64_t val);

/**
 * @brief 在缓冲区末尾添加64位值
 *
 * 在缓冲区末尾添加64位的大端值。增加缓冲区的数据长度，以在结尾处容纳更多数据。
 *
 * @param buf 要更新的缓冲区。
 * @param val 要添加的64位值。
 */
void net_buf_simple_add_be64(struct net_buf_simple *buf, uint64_t val);

/**
 * @brief 将数据推送到缓冲区的开头。
 *
 * 修改数据指针和缓冲区长度，以在缓冲区的开始处考虑更多数据。
 *
 * @param buf 要更新的缓冲区。
 * @param len 要添加到开头的字节数。
 *
 * @return 缓冲区数据的新开始。
 */
void *net_buf_simple_push(struct net_buf_simple *buf, size_t len);

/**
 * @brief 将16位值推送到缓冲区的开头
 *
 * 在缓冲区的开头添加小端字节格式的16位值。
 *
 * @param buf 要更新的缓冲区。
 * @param val 16位值推送到缓冲器。
 */
void net_buf_simple_push_le16(struct net_buf_simple *buf, uint16_t val);

/**
 * @brief 将16位值推送到缓冲区的开头
 *
 * 在缓冲区的开头添加大端格式的16位值。
 *
 * @param buf 要更新的缓冲区。
 * @param val 16位值推送到缓冲器。
 */
void net_buf_simple_push_be16(struct net_buf_simple *buf, uint16_t val);

/**
 * @brief 将8位值推到缓冲区的开头
 *
 * 将8位值添加到缓冲区的开头。
 *
 * @param buf 要更新的缓冲区。
 * @param val 8位值推送到缓冲器。
 */
void net_buf_simple_push_u8(struct net_buf_simple *buf, uint8_t val);

/**
 * @brief 将24位值推送到缓冲区的开头
 *
 * 在缓冲区的开头添加小端格式的24位值。
 *
 * @param buf 要更新的缓冲区。
 * @param val 24位值推送到缓冲器。
 */
void net_buf_simple_push_le24(struct net_buf_simple *buf, uint32_t val);

/**
 * @brief 将24位值推送到缓冲区的开头
 *
 * 在缓冲区的开头添加大端格式的24位值。
 *
 * @param buf 要更新的缓冲区。
 * @param val 24位值推送到缓冲器。
 */
void net_buf_simple_push_be24(struct net_buf_simple *buf, uint32_t val);

/**
 * @brief 将32位值推送到缓冲区的开头
 *
 * 将小端字节格式的32位值添加到缓冲区的开头。
 *
 * @param buf 要更新的缓冲区。
 * @param val 要推送到缓冲区的32位值。
 */
void net_buf_simple_push_le32(struct net_buf_simple *buf, uint32_t val);

/**
 * @brief 将32位值推送到缓冲区的开头
 *
 * 在缓冲区的开头添加大端格式的32位值。
 *
 * @param buf 要更新的缓冲区。
 * @param val 要推送到缓冲区的32位值。
 */
void net_buf_simple_push_be32(struct net_buf_simple *buf, uint32_t val);

/**
 * @brief 将48位值推到缓冲区的开头
 *
 * 将小端字节格式的48位值添加到缓冲区的开头。
 *
 * @param buf 要更新的缓冲区。
 * @param val 48位值推送到缓冲器。
 */
void net_buf_simple_push_le48(struct net_buf_simple *buf, uint64_t val);

/**
 * @brief 将48位值推到缓冲区的开头
 *
 * 在缓冲区的开头添加大端格式的48位值。
 *
 * @param buf 要更新的缓冲区。
 * @param val 48位值推送到缓冲器。
 */
void net_buf_simple_push_be48(struct net_buf_simple *buf, uint64_t val);

/**
 * @brief 将64位值推送到缓冲区的开头
 *
 * 在缓冲区的开头添加小端字节格式的64位值。
 *
 * @param buf 要更新的缓冲区。
 * @param val 64位值推送到缓冲器。
 */
void net_buf_simple_push_le64(struct net_buf_simple *buf, uint64_t val);

/**
 * @brief 将64位值推送到缓冲区的开头
 *
 * 在缓冲区的开头添加大端格式的64位值。
 *
 * @param buf 要更新的缓冲区。
 * @param val 64位值推送到缓冲器。
 */
void net_buf_simple_push_be64(struct net_buf_simple *buf, uint64_t val);

/**
 * @brief 从缓冲区的开头删除数据。
 *
 * 通过修改数据指针和缓冲区长度，从缓冲区的开头删除数据。
 *
 * @param buf 要更新的缓冲区。
 * @param len 要删除的字节数。
 *
 * @return 缓冲区数据的新开始。
 */
void *net_buf_simple_pull(struct net_buf_simple *buf, size_t len);

/**
 * @brief 从缓冲区的开头删除数据。
 *
 * 通过修改数据指针和缓冲区长度，从缓冲区的开头删除数据。
 *
 * @param buf 要更新的缓冲区。
 * @param len 要删除的字节数。
 *
 * @return 指向缓冲区数据旧位置的指针。
 */
void *net_buf_simple_pull_mem(struct net_buf_simple *buf, size_t len);

/**
 * @brief 从缓冲区的开头删除8位值
 *
 * 与net_buf_simple_pull（）的想法相同，但它是操作8位值的助手。
 *
 * @param buf 缓冲区上的有效指针。
 *
 * @return 8位删除值
 */
uint8_t net_buf_simple_pull_u8(struct net_buf_simple *buf);

/**
 * @brief 删除并转换缓冲区开头的16位。
 *
 * 与net_buf_simple_pull（）的想法相同，但它是对16位小端数据进行操作的助手。
 *
 * @param buf 缓冲区上的有效指针。
 *
 * @return 16位值从小端序转换为主端序。
 */
uint16_t net_buf_simple_pull_le16(struct net_buf_simple *buf);

/**
 * @brief 删除并转换缓冲区开头的16位。
 *
 * 与net_buf_simple_pull（）的想法相同，但它是对16位大端数据进行操作的助手。
 *
 * @param buf 缓冲区上的有效指针。
 *
 * @return 16位值从大端序转换为主机端序。
 */
uint16_t net_buf_simple_pull_be16(struct net_buf_simple *buf);

/**
 * @brief 删除并转换缓冲区开头的24位。
 *
 * 与net_buf_simple_pull（）的想法相同，但它是对24位小端数据进行操作的助手。
 *
 * @param buf 缓冲区上的有效指针。
 *
 * @return 24位值从小端序转换为主端序。
 */
uint32_t net_buf_simple_pull_le24(struct net_buf_simple *buf);

/**
 * @brief 删除并转换缓冲区开头的24位。
 *
 * 与net_buf_simple_pull（）的想法相同，但它是操作24位大端数据的助手。
 *
 * @param buf 缓冲区上的有效指针。
 *
 * @return 24位值从大端序转换为主机端序。
 */
uint32_t net_buf_simple_pull_be24(struct net_buf_simple *buf);

/**
 * @brief 删除并转换缓冲区开头的32位。
 *
 * 与net_buf_simple_pull（）的想法相同，但它是对32位小端数据进行操作的助手。
 *
 * @param buf 缓冲区上的有效指针。
 *
 * @return 32位值从little endian转换为host endian。
 */
uint32_t net_buf_simple_pull_le32(struct net_buf_simple *buf);

/**
 * @brief 删除并转换缓冲区开头的32位。
 *
 * 与net_buf_simple_pull（）的想法相同，但它是操作32位大端数据的助手。
 *
 * @param buf 缓冲区上的有效指针。
 *
 * @return 32位值从big endian转换为host endian。
 */
uint32_t net_buf_simple_pull_be32(struct net_buf_simple *buf);

/**
 * @brief 删除并转换缓冲区开头的48位。
 *
 * 与net_buf_simple_pull（）的想法相同，但它是对48位小端数据进行操作的助手。
 *
 * @param buf 缓冲区上的有效指针。
 *
 * @return 48位值从小端字节转换为主机端字节。
 */
uint64_t net_buf_simple_pull_le48(struct net_buf_simple *buf);

/**
 * @brief 删除并转换缓冲区开头的48位。
 *
 * 与net_buf_simple_pull（）的想法相同，但它是对48位大端数据进行操作的助手。
 *
 * @param buf 缓冲区上的有效指针。
 *
 * @return 48位值从大端序转换为主机端序。
 */
uint64_t net_buf_simple_pull_be48(struct net_buf_simple *buf);

/**
 * @brief 删除并转换缓冲区开头的64位。
 *
 * 与net_buf_simple_pull（）的想法相同，但它是一个对64位小端数据进行操作的助手。
 *
 * @param buf 缓冲区上的有效指针。
 *
 * @return 64位值从小端序转换为主机端序。
 */
uint64_t net_buf_simple_pull_le64(struct net_buf_simple *buf);

/**
 * @brief 删除并转换缓冲区开头的64位。
 *
 * 与net_buf_simple_pull（）的想法相同，但它是对64位大端数据进行操作的助手。
 *
 * @param buf 缓冲区上的有效指针。
 *
 * @return 64位值从大端序转换为主机端序。
 */
uint64_t net_buf_simple_pull_be64(struct net_buf_simple *buf);

/**
 * @brief 获取缓冲区的尾部指针。
 *
 * 获取指向缓冲区中数据结尾的指针。
 *
 * @param buf 缓冲器
 *
 * @return 缓冲区的尾部指针。
 */
static inline uint8_t *net_buf_simple_tail(struct net_buf_simple *buf)
{
    return buf->data + buf->len;
}

/**
 * @brief 检查缓冲区净空。
 *
 * 检查缓冲区开头有多少可用空间。
 *
 * buf缓冲区上的有效指针
 *
 * @return 缓冲区开头可用的字节数。
 */
size_t net_buf_simple_headroom(struct net_buf_simple *buf);

/**
 * @brief 检查缓冲尾室。
 *
 * 检查缓冲区末端有多少可用空间。
 *
 * @param buf 缓冲区上的有效指针
 *
 * @return 缓冲区末尾可用的字节数。
 */
size_t net_buf_simple_tailroom(struct net_buf_simple *buf);

/**
 * @brief 正在分析缓冲区的状态。
 *
 * 这用于临时存储缓冲区的解析状态，同时将解析控制权交给我们无法控制的例程。
 */
struct net_buf_simple_state {
    /**数据指针从存储开始的偏移量*/
    uint16_t offset;
    /**数据长度*/
    uint16_t len;
};

/**
 * @brief 保存缓冲区的分析状态。
 *
 * 保存缓冲区的分析状态，以便稍后恢复。
 *
 * @param buf 应保存状态的缓冲区。
 * @param state 状态的存储。
 */
static inline void net_buf_simple_save(struct net_buf_simple *buf,
                                       struct net_buf_simple_state *state)
{
    state->offset = net_buf_simple_headroom(buf);
    state->len = buf->len;
}

/**
 * @brief 还原缓冲区的分析状态。
 *
 * 从net_buf_simple_save（）之前存储的状态恢复缓冲区的解析状态。
 *
 * @param buf 应将状态还原到的缓冲区。
 * @param state 存储状态。
 */
static inline void net_buf_simple_restore(struct net_buf_simple *buf,
                                          struct net_buf_simple_state *state)
{
    buf->data = buf->__buf + state->offset;
    buf->len = state->len;
}

/**
 * @brief 使用给定的净空初始化缓冲区。
 *
 * 调用此API时，缓冲区不应包含任何数据。
 *
 * @param buf 要初始化的缓冲区。
 * @param reserve 预留多少净空。
 */
void net_buf_simple_reserve(struct net_buf_simple *buf, size_t reserve);

/**
 * 指示缓冲区具有相关片段的标志。当缓冲区位于FIFO内时，仅由缓冲区处理代码在内部使用，这意味着net_buf API用户无需显式设置或取消设置。只要缓冲区在FIFO之外，即在实践中总是针对该API的用户，就应该使用buf->frags指针。
 */
#define NET_BUF_FRAGS        BIT(0)

/**
 * @brief 网络缓冲区表示。
 *
 * 此结构用于表示网络缓冲区。此类缓冲区通常通过NET_BUF_POOL__DEFINE（）API定义，并使用NET_BUF_alloc（）API分配。
 */
struct net_buf {
    union {
        /**允许将缓冲区放入sys_slist_t*/
        sys_snode_t node;

        /**与此缓冲区关联的片段。*/
        struct net_buf *frags;
    };

    /**引用计数。*/
    uint8_t ref;

    /**缓冲区标志的位字段。*/
    uint8_t flags;

    /**释放时缓冲区应该放在哪里。*/
    struct net_buf_pool *pool;

    /* 为了方便访问net_buf_simple成员，还保留了旧的API。
     */
    union {
        /* 此结构的ABI必须与net_buf_simple匹配*/
        struct {
            /**指向缓冲区中数据开头的指针。*/
            uint8_t *data;

            /**数据指针后面的数据长度。*/
            uint16_t len;

            /**此缓冲区可以存储的数据量。*/
            uint16_t size;

            /** 开始数据存储。不可直接访问（应改用数据指针）。
             */
            uint8_t *__buf;
        };

        struct net_buf_simple b;
    };

    /**此缓冲区的系统元数据。*/
    uint8_t user_data[BLE_MESH_NET_BUF_USER_DATA_SIZE] __net_buf_align;
};

struct net_buf_data_cb {
    uint8_t *(*alloc)(struct net_buf *buf, size_t *size, int32_t timeout);
    uint8_t *(*ref)(struct net_buf *buf, uint8_t *data);
    void   (*unref)(struct net_buf *buf, uint8_t *data);
};

struct net_buf_data_alloc {
    const struct net_buf_data_cb *cb;
    void *alloc_data;
};

struct net_buf_pool {
    /**池中的缓冲区数*/
    const uint16_t buf_count;

    /**未初始化缓冲区的数量*/
    uint16_t uninit_count;

#if defined(CONFIG_BLE_MESH_NET_BUF_POOL_USAGE)
    /**池中可用缓冲区的数量。*/
    int16_t avail_count;

    /**池的总大小。*/
    const uint16_t pool_size;

    /**池的名称。打印池信息时使用。*/
    const char *name;
#endif /* CONFIG_BLE_MESH_NET_BUF_POOL_USAGE */

    /**释放缓冲区时的可选销毁回调。*/
    void (*const destroy)(struct net_buf *buf);

    /**数据分配处理程序。*/
    const struct net_buf_data_alloc *alloc;

    /**访问存储开始的帮助程序（用于net_buf_pool_init）*/
    struct net_buf *const __bufs;
};

#if defined(CONFIG_BLE_MESH_NET_BUF_POOL_USAGE)
#define NET_BUF_POOL_INITIALIZER(_pool, _alloc, _bufs, _count, _destroy) \
    {                                                                   \
        .alloc = _alloc,                                                \
        .__bufs = (struct net_buf *)_bufs,                              \
        .buf_count = _count,                                            \
        .uninit_count = _count,                                         \
        .avail_count = _count,                                          \
        .destroy = _destroy,                                            \
        .name = STRINGIFY(_pool),                                       \
    }
#else
#define NET_BUF_POOL_INITIALIZER(_pool, _alloc, _bufs, _count, _destroy) \
    {                                                                   \
        .alloc = _alloc,                                                \
        .__bufs = (struct net_buf *)_bufs,                              \
        .buf_count = _count,                                            \
        .uninit_count = _count,                                         \
        .destroy = _destroy,                                            \
    }
#endif /* CONFIG_BLE_MESH_NET_BUF_POOL_USAGE */

struct net_buf_pool_fixed {
    size_t data_size;
    uint8_t *data_pool;
};

/**@第二个INTERNAL_HIDDEN*/
extern const struct net_buf_data_cb net_buf_fixed_cb;

/**
 * @def NET_BUF_POOL_FIXED_DEFINE
 * @brief 基于固定大小数据为缓冲区定义新池
 *
 * 定义net_buf_pool结构和所需缓冲区数量所需的内存存储（结构数组）。之后，可以通过net_buf_alloc从池中访问缓冲区。池被定义为静态变量，因此如果需要将其导出到当前模块外部，则需要借助单独的指针而不是外部声明来实现。
 *
 * 缓冲区的数据有效载荷将从固定大小块的字节数组中分配。这种类型的池不支持数据分配上的阻塞，因此在尝试分配数据时，传递给net_buf_alloc的超时将始终被视为K_NO_WAIT。这意味着必须始终干净地处理分配失败，即NULL返回。
 *
 * 如果提供了自定义销毁回调，则该回调负责最终调用net_buf_destroy（）以完成将缓冲区返回到池的过程。
 *
 * @param _name      池变量的名称。
 * @param _count     池中的缓冲区数。
 * @param _data_size 每个缓冲区的最大数据负载。
 * @param _destroy   释放缓冲区时的可选销毁回调。
 */
#define NET_BUF_POOL_FIXED_DEFINE(_name, _count, _data_size, _destroy)      \
    static struct net_buf net_buf_##_name[_count];                          \
    static uint8_t net_buf_data_##_name[_count][_data_size];                \
    static const struct net_buf_pool_fixed net_buf_fixed_##_name = {        \
        .data_size = _data_size,                                            \
        .data_pool = (uint8_t *)net_buf_data_##_name,                       \
    };                                                                      \
    static const struct net_buf_data_alloc net_buf_fixed_alloc_##_name = {  \
        .cb = &net_buf_fixed_cb,                                            \
        .alloc_data = (void *)&net_buf_fixed_##_name,                       \
    };                                                                      \
    struct net_buf_pool _name __net_buf_align                               \
            __in_section(_net_buf_pool, static, _name) =                    \
        NET_BUF_POOL_INITIALIZER(_name, &net_buf_fixed_alloc_##_name,       \
                    net_buf_##_name, _count, _destroy)

/**
 * @def NET_BUF_POOL_DEFINE
 * @brief 为缓冲区定义新池
 *
 * 定义net_buf_pool结构和所需缓冲区数量所需的内存存储（结构数组）。之后，可以通过net_buf_alloc从池中访问缓冲区。池被定义为静态变量，因此如果需要将其导出到当前模块外部，则需要借助单独的指针而不是外部声明来实现。
 *
 * 如果提供了自定义销毁回调，则该回调负责最终调用net_buf_destroy（）以完成将缓冲区返回到池的过程。
 *
 * @param _name     池变量的名称。
 * @param _count    池中的缓冲区数。
 * @param _size     每个缓冲区的最大数据大小。
 * @param _ud_size  要保留的用户数据空间量。
 * @param _destroy  释放缓冲区时的可选销毁回调。
 */
#define NET_BUF_POOL_DEFINE(_name, _count, _size, _ud_size, _destroy)   \
    NET_BUF_POOL_FIXED_DEFINE(_name, _count, _size, _destroy)

/**
 * @brief 获取缓冲区的从零开始的索引。
 *
 * 此函数将根据缓冲区在缓冲池中的位置将缓冲区转换为从零开始的索引。如果您想将元数据上下文的外部数组与池的缓冲区相关联，这可能很有用。
 *
 * @param buf  网络缓冲区。
 *
 * @return 缓冲区的从零开始的索引。
 */
int net_buf_id(struct net_buf *buf);

/**
 * @brief 从池中分配新的固定缓冲区。
 *
 * @param pool 从哪个池分配缓冲区。
 * @param timeout 影响池为空时采取的操作。如果K_NO_WAIT，则立即返回。如果K_FOREVER，则根据需要等待。否则，在超时前等待指定的毫秒数。注意，某些类型的数据分配器不支持阻塞（例如HEAP类型）。在这种情况下，net_buf_alloc（）仍然有可能失败（返回NULL），即使给定了K_FOREVER。
 *
 * @return 新缓冲区或空（如果缓冲区不足）。
 */
#if defined(CONFIG_BLE_MESH_NET_BUF_LOG)
struct net_buf *net_buf_alloc_fixed_debug(struct net_buf_pool *pool, int32_t timeout,
                                          const char *func, int line);
#define net_buf_alloc_fixed(_pool, _timeout) \
    net_buf_alloc_fixed_debug(_pool, _timeout, __func__, __LINE__)
#else
struct net_buf *net_buf_alloc_fixed(struct net_buf_pool *pool, int32_t timeout);
#endif

/**
 * @def net_buf_alloc
 *
 * @copydetails net_buf_alloc_fixed
 */
#define net_buf_alloc(pool, timeout) net_buf_alloc_fixed(pool, timeout)

/**
 *  @brief 重置缓冲区
 *
 *  重置缓冲区数据和标志，使其可用于其他目的。
 *
 *  @param buf 要重置的缓冲区。
 */
void net_buf_reset(struct net_buf *buf);

/**
 * @def 网_包_服务
 * @brief 使用给定的净空初始化缓冲区。
 *
 * 调用此API时，缓冲区不应包含任何数据。
 *
 * @param buf 要初始化的缓冲区。
 * @param reserve 预留多少净空。
 */
#define net_buf_reserve(buf, reserve) net_buf_simple_reserve(&(buf)->b, reserve)

/**
 *  @brief 将缓冲区放入列表
 *
 *  在列表末尾放置缓冲区。如果缓冲区包含后续片段，该函数将负责将它们插入列表。
 *
 *  @param list 要将缓冲区附加到的列表。
 *  @param buf 缓冲器
 */
void net_buf_slist_put(sys_slist_t *list, struct net_buf *buf);

/**
 *  @brief 从列表中获取缓冲区。
 *
 *  从列表中获取缓冲区。如果缓冲区有任何碎片，这些碎片也将自动从列表中恢复，并放置到缓冲区的碎片列表中。
 *
 *  @param list 从哪个列表获取缓冲区。
 *
 *  @return 如果FIFO为空，则为空。
 */
struct net_buf *net_buf_slist_get(sys_slist_t *list);

/**
 *  @brief 减少缓冲区的引用计数。
 *
 *  减少缓冲区的引用计数，如果计数为零，则将其放回池中。
 *
 *  @param buf 缓冲区上的有效指针
 */
#if defined(CONFIG_BLE_MESH_NET_BUF_LOG)
void net_buf_unref_debug(struct net_buf *buf, const char *func, int line);
#define net_buf_unref(_buf) \
        net_buf_unref_debug(_buf, __func__, __LINE__)
#else
void net_buf_unref(struct net_buf *buf);
#endif

/**
 *  @brief 增加缓冲区的引用计数。
 *
 *  @param buf 缓冲区上的有效指针
 *
 *  @return 新引用的缓冲区
 */
struct net_buf *net_buf_ref(struct net_buf *buf);

/**
 *  @brief 获取指向缓冲区用户数据的指针。
 *
 *  @param buf 缓冲区上的有效指针
 *
 *  @return 指向缓冲区用户数据的指针。
 */
static inline void *net_buf_user_data(struct net_buf *buf)
{
    return (void *)buf->user_data;
}

/**
 *  @def net_buf_add
 *  @brief 准备要添加到缓冲区末尾的数据
 *
 *  增加缓冲区的数据长度，以在结尾处容纳更多数据。
 *
 *  @param buf 要更新的缓冲区。
 *  @param len 用于增加长度的字节数。
 *
 *  @return 缓冲区的原始尾部。
 */
#define net_buf_add(buf, len) net_buf_simple_add(&(buf)->b, len)

/**
 *  @def net_buf_add_mem
 *  @brief 将字节从内存复制到缓冲区末尾
 *
 *  将给定字节数复制到缓冲区末尾。增加缓冲区的数据长度，以在结尾处容纳更多数据。
 *
 *  @param buf 要更新的缓冲区。
 *  @param mem 要添加的数据的位置。
 *  @param len 要添加的数据长度
 *
 *  @return 缓冲区的原始尾部。
 */
#define net_buf_add_mem(buf, mem, len) net_buf_simple_add_mem(&(buf)->b, mem, len)

/**
 *  @def net_buf_add_u8
 *  @brief 在缓冲区末尾添加（8位）字节
 *
 *  在缓冲区末尾添加一个字节。增加缓冲区的数据长度，以在结尾处容纳更多数据。
 *
 *  @param buf 要更新的缓冲区。
 *  @param val 要添加的字节值。
 *
 *  @return 指向添加值的指针
 */
#define net_buf_add_u8(buf, val) net_buf_simple_add_u8(&(buf)->b, val)

/**
 *  @def net_buf_add_le16
 *  @brief 在缓冲区末尾添加16位值
 *
 *  在缓冲区末尾添加小端字节格式的16位值。增加缓冲区的数据长度，以在结尾处容纳更多数据。
 *
 *  @param buf 要更新的缓冲区。
 *  @param val 要添加的16位值。
 */
#define net_buf_add_le16(buf, val) net_buf_simple_add_le16(&(buf)->b, val)

/**
 *  @def net_buf_add_be16
 *  @brief 在缓冲区末尾添加16位值
 *
 *  在缓冲区末尾添加16位的大端值。增加缓冲区的数据长度，以在结尾处容纳更多数据。
 *
 *  @param buf 要更新的缓冲区。
 *  @param val 要添加的16位值。
 */
#define net_buf_add_be16(buf, val) net_buf_simple_add_be16(&(buf)->b, val)

/**
 * @def net_buf_add_le24
 * @brief 在缓冲区末尾添加24位值
 *
 * 在缓冲区末尾以小端字节格式添加24位值。增加缓冲区的数据长度，以在结尾处容纳更多数据。
 *
 * @param buf 要更新的缓冲区。
 * @param val 要添加的24位值。
 */
#define net_buf_add_le24(buf, val) net_buf_simple_add_le24(&(buf)->b, val)

/**
 * @def 网络地址be24
 * @brief 在缓冲区末尾添加24位值
 *
 * 在缓冲区末尾添加24位的大端格式值。增加缓冲区的数据长度，以在结尾处容纳更多数据。
 *
 * @param buf 要更新的缓冲区。
 * @param val 要添加的24位值。
 */
#define net_buf_add_be24(buf, val) net_buf_simple_add_be24(&(buf)->b, val)

/**
 *  @def net_buf_add_le32
 *  @brief 在缓冲区末尾添加32位值
 *
 *  在缓冲区末尾添加小端字节格式的32位值。增加缓冲区的数据长度，以在结尾处容纳更多数据。
 *
 *  @param buf 要更新的缓冲区。
 *  @param val 要添加的32位值。
 */
#define net_buf_add_le32(buf, val) net_buf_simple_add_le32(&(buf)->b, val)

/**
 *  @def net_buf_add_be32
 *  @brief 在缓冲区末尾添加32位值
 *
 *  在缓冲区末尾添加32位大端格式的值。增加缓冲区的数据长度，以在结尾处容纳更多数据。
 *
 *  @param buf 要更新的缓冲区。
 *  @param val 要添加的32位值。
 */
#define net_buf_add_be32(buf, val) net_buf_simple_add_be32(&(buf)->b, val)

/**
 * @def net_buf_add_le48
 * @brief 在缓冲区末尾添加48位值
 *
 * 在缓冲区末尾添加小端字节格式的48位值。增加缓冲区的数据长度，以在结尾处容纳更多数据。
 *
 * @param buf 要更新的缓冲区。
 * @param val 要添加的48位值。
 */
#define net_buf_add_le48(buf, val) net_buf_simple_add_le48(&(buf)->b, val)

/**
 * @def net_buf_add_be48
 * @brief 在缓冲区末尾添加48位值
 *
 * 在缓冲区末尾以大端字节格式添加48位值。增加缓冲区的数据长度，以在结尾处容纳更多数据。
 *
 * @param buf 要更新的缓冲区。
 * @param val 要添加的48位值。
 */
#define net_buf_add_be48(buf, val) net_buf_simple_add_be48(&(buf)->b, val)

/**
 * @def net_buf_add_le64
 * @brief 在缓冲区末尾添加64位值
 *
 * 在缓冲区末尾添加小端字节格式的64位值。增加缓冲区的数据长度，以在结尾处容纳更多数据。
 *
 * @param buf 要更新的缓冲区。
 * @param val 要添加的64位值。
 */
#define net_buf_add_le64(buf, val) net_buf_simple_add_le64(&(buf)->b, val)

/**
 * @def net_buf_add_be64
 * @brief 在缓冲区末尾添加64位值
 *
 * 在缓冲区末尾添加64位的大端值。增加缓冲区的数据长度，以在结尾处容纳更多数据。
 *
 * @param buf 要更新的缓冲区。
 * @param val 要添加的64位值。
 */
#define net_buf_add_be64(buf, val) net_buf_simple_add_be64(&(buf)->b, val)

/**
 *  @def net_buf_push
 *  @brief 将数据推送到缓冲区的开头。
 *
 *  修改数据指针和缓冲区长度，以在缓冲区的开始处考虑更多数据。
 *
 *  @param buf 要更新的缓冲区。
 *  @param len 要添加到开头的字节数。
 *
 *  @return 缓冲区数据的新开始。
 */
#define net_buf_push(buf, len) net_buf_simple_push(&(buf)->b, len)

/**
 *  @def net_buf_push_le16
 *  @brief 将16位值推送到缓冲区的开头
 *
 *  在缓冲区的开头添加小端字节格式的16位值。
 *
 *  @param buf 要更新的缓冲区。
 *  @param val 16位值推送到缓冲器。
 */
#define net_buf_push_le16(buf, val) net_buf_simple_push_le16(&(buf)->b, val)

/**
 *  @def net_buf_push_be16
 *  @brief 将16位值推送到缓冲区的开头
 *
 *  在缓冲区的开头添加小端字节格式的16位值。
 *
 *  @param buf 要更新的缓冲区。
 *  @param val 16位值推送到缓冲器。
 */
#define net_buf_push_be16(buf, val) net_buf_simple_push_be16(&(buf)->b, val)

/**
 *  @def net_buf_push_u8
 *  @brief 将8位值推到缓冲区的开头
 *
 *  将8位值添加到缓冲区的开头。
 *
 *  @param buf 要更新的缓冲区。
 *  @param val 8位值推送到缓冲器。
 */
#define net_buf_push_u8(buf, val) net_buf_simple_push_u8(&(buf)->b, val)

/**
 * @def net_buf_push_le24
 * @brief 将24位值推送到缓冲区的开头
 *
 * 在缓冲区的开头添加小端格式的24位值。
 *
 * @param buf 要更新的缓冲区。
 * @param val 24位值推送到缓冲器。
 */
#define net_buf_push_le24(buf, val) net_buf_simple_push_le24(&(buf)->b, val)

/**
 * @def net_buf_push_be24
 * @brief 将24位值推送到缓冲区的开头
 *
 * 在缓冲区的开头添加小端格式的24位值。
 *
 * @param buf 要更新的缓冲区。
 * @param val 24位值推送到缓冲器。
 */
#define net_buf_push_be24(buf, val) net_buf_simple_push_be24(&(buf)->b, val)

/**
 * @def net_buf_push_le32
 * @brief 将32位值推送到缓冲区的开头
 *
 * 将小端字节格式的32位值添加到缓冲区的开头。
 *
 * @param buf 要更新的缓冲区。
 * @param val 要推送到缓冲区的32位值。
 */
#define net_buf_push_le32(buf, val) net_buf_simple_push_le32(&(buf)->b, val)

/**
 * @def net_buf_push_be32
 * @brief 将32位值推送到缓冲区的开头
 *
 * 将小端字节格式的32位值添加到缓冲区的开头。
 *
 * @param buf 要更新的缓冲区。
 * @param val 要推送到缓冲区的32位值。
 */
#define net_buf_push_be32(buf, val) net_buf_simple_push_be32(&(buf)->b, val)

/**
 * @def net_buf_push_le48
 * @brief 将48位值推到缓冲区的开头
 *
 * 将小端字节格式的48位值添加到缓冲区的开头。
 *
 * @param buf 要更新的缓冲区。
 * @param val 48位值推送到缓冲器。
 */
#define net_buf_push_le48(buf, val) net_buf_simple_push_le48(&(buf)->b, val)

/**
 * @def net_buf_push_be48
 * @brief 将48位值推到缓冲区的开头
 *
 * 将小端字节格式的48位值添加到缓冲区的开头。
 *
 * @param buf 要更新的缓冲区。
 * @param val 48位值推送到缓冲器。
 */
#define net_buf_push_be48(buf, val) net_buf_simple_push_be48(&(buf)->b, val)

/**
 * @def net_buf_push_le64
 * @brief 将64位值推送到缓冲区的开头
 *
 * 在缓冲区的开头添加小端字节格式的64位值。
 *
 * @param buf 要更新的缓冲区。
 * @param val 64位值推送到缓冲器。
 */
#define net_buf_push_le64(buf, val) net_buf_simple_push_le64(&(buf)->b, val)

/**
 * @def net_buf_push_be64
 * @brief 将64位值推送到缓冲区的开头
 *
 * 在缓冲区的开头添加小端字节格式的64位值。
 *
 * @param buf 要更新的缓冲区。
 * @param val 64位值推送到缓冲器。
 */
#define net_buf_push_be64(buf, val) net_buf_simple_push_be64(&(buf)->b, val)

/**
 *  @def net_buf_pull
 *  @brief 从缓冲区的开头删除数据。
 *
 *  通过修改数据指针和缓冲区长度，从缓冲区的开头删除数据。
 *
 *  @param buf 要更新的缓冲区。
 *  @param len 要删除的字节数。
 *
 *  @return 缓冲区数据的新开始。
 */
#define net_buf_pull(buf, len) net_buf_simple_pull(&(buf)->b, len)

/**
 * @def net_buf_pull_mem
 * @brief 从缓冲区的开头删除数据。
 *
 * 通过修改数据指针和缓冲区长度，从缓冲区的开头删除数据。
 *
 * @param buf 要更新的缓冲区。
 * @param len 要删除的字节数。
 *
 * @return 指向缓冲区数据旧开头的指针。
 */
#define net_buf_pull_mem(buf, len) net_buf_simple_pull_mem(&(buf)->b, len)

/**
 *  @def net_buf_pull_u8
 *  @brief 从缓冲区的开头删除8位值
 *
 *  与net_buf_pull（）的想法相同，但它是操作8位值的助手。
 *
 *  @param buf 缓冲区上的有效指针。
 *
 *  @return 8位删除值
 */
#define net_buf_pull_u8(buf) net_buf_simple_pull_u8(&(buf)->b)

/**
 *  @def net_buf_pull_le16
 *  @brief 删除并转换缓冲区开头的16位。
 *
 *  与net_buf_pull（）的想法相同，但它是对16位小端数据进行操作的助手。
 *
 *  @param buf 缓冲区上的有效指针。
 *
 *  @return 16位值从小端序转换为主端序。
 */
#define net_buf_pull_le16(buf) net_buf_simple_pull_le16(&(buf)->b)

/**
 *  @def net_buf_pull_be16
 *  @brief 删除并转换缓冲区开头的16位。
 *
 *  与net_buf_pull（）的想法相同，但它是对16位大端数据进行操作的助手。
 *
 *  @param buf 缓冲区上的有效指针。
 *
 *  @return 16位值从大端序转换为主机端序。
 */
#define net_buf_pull_be16(buf) net_buf_simple_pull_be16(&(buf)->b)

/**
 * @def net_buf_pull_le24
 * @brief 删除并转换缓冲区开头的24位。
 *
 * 与net_buf_pull（）的想法相同，但它是对24位小端数据进行操作的助手。
 *
 * @param buf 缓冲区上的有效指针。
 *
 * @return 24位值从小端序转换为主端序。
 */
#define net_buf_pull_le24(buf) net_buf_simple_pull_le24(&(buf)->b)

/**
 * @def net_buf_pull_be24
 * @brief 删除并转换缓冲区开头的24位。
 *
 * 与net_buf_pull（）的想法相同，但它是操作24位大端数据的助手。
 *
 * @param buf 缓冲区上的有效指针。
 *
 * @return 24位值从大端序转换为主机端序。
 */
#define net_buf_pull_be24(buf) net_buf_simple_pull_be24(&(buf)->b)

/**
 *  @def net_buf_pull_le32
 *  @brief 删除并转换缓冲区开头的32位。
 *
 *  与net_buf_pull（）的想法相同，但它是对32位小端数据进行操作的助手。
 *
 *  @param buf 缓冲区上的有效指针。
 *
 *  @return 32位值从little endian转换为host endian。
 */
#define net_buf_pull_le32(buf) net_buf_simple_pull_le32(&(buf)->b)

/**
 *  @def net_buf_pull_be32
 *  @brief 删除并转换缓冲区开头的32位。
 *
 *  与net_buf_pull（）的想法相同，但它是操作32位大端数据的助手。
 *
 *  @param buf 缓冲区上的有效指针
 *
 *  @return 32位值从big endian转换为host endian。
 */
#define net_buf_pull_be32(buf) net_buf_simple_pull_be32(&(buf)->b)

/**
 * @def net_buf_pull_le48
 * @brief 删除并转换缓冲区开头的48位。
 *
 * 与net_buf_pull（）的想法相同，但它是对48位小端数据进行操作的助手。
 *
 * @param buf 缓冲区上的有效指针。
 *
 * @return 48位值从小端字节转换为主机端字节。
 */
#define net_buf_pull_le48(buf) net_buf_simple_pull_le48(&(buf)->b)

/**
 * @def net_buf_pull_be48
 * @brief 删除并转换缓冲区开头的48位。
 *
 * 与net_buf_pull（）的想法相同，但它是操作48位大端数据的助手。
 *
 * @param buf 缓冲区上的有效指针
 *
 * @return 48位值从大端序转换为主机端序。
 */
#define net_buf_pull_be48(buf) net_buf_simple_pull_be48(&(buf)->b)

/**
 * @def net_buf_pull_le64
 * @brief 删除并转换缓冲区开头的64位。
 *
 * 与net_buf_pull（）的想法相同，但它是对64位小端数据进行操作的助手。
 *
 * @param buf 缓冲区上的有效指针。
 *
 * @return 64位值从小端序转换为主机端序。
 */
#define net_buf_pull_le64(buf) net_buf_simple_pull_le64(&(buf)->b)

/**
 * @def net_buf_pull_be64
 * @brief 删除并转换缓冲区开头的64位。
 *
 * 与net_buf_pull（）的想法相同，但它是对64位大端数据进行操作的助手。
 *
 * @param buf 缓冲区上的有效指针
 *
 * @return 64位值从大端序转换为主机端序。
 */
#define net_buf_pull_be64(buf) net_buf_simple_pull_be64(&(buf)->b)

/**
 *  @def net_buf_休息室
 *  @brief 检查缓冲尾室。
 *
 *  检查缓冲区末端有多少可用空间。
 *
 *  @param buf 缓冲区上的有效指针
 *
 *  @return 缓冲区末尾可用的字节数。
 */
#define net_buf_tailroom(buf) net_buf_simple_tailroom(&(buf)->b)

/**
 *  @def net_buf_headroom
 *  @brief 检查缓冲区净空。
 *
 *  检查缓冲区开头有多少可用空间。
 *
 *  buf缓冲区上的有效指针
 *
 *  @return 缓冲区开头可用的字节数。
 */
#define net_buf_headroom(buf) net_buf_simple_headroom(&(buf)->b)

/**
 * @def net_buf_tail
 * @brief 获取缓冲区的尾部指针。
 *
 * 获取指向缓冲区中数据结尾的指针。
 *
 * @param buf 缓冲器
 *
 * @return 缓冲区的尾部指针。
 */
#define net_buf_tail(buf) net_buf_simple_tail(&(buf)->b)

/**
 * @brief 在片段列表中查找最后一个片段。
 *
 * @return 指向列表中最后一个片段的指针。
 */
struct net_buf *net_buf_frag_last(struct net_buf *frags);

/**
 * @brief 将新片段插入bufs链。
 *
 * 在父级之后将新片段插入缓冲区片段列表。
 *
 * 注意：此函数获取片段引用的所有权，因此不需要调用方取消引用。
 *
 * @param parent 父缓冲区/片段。
 * @param frag 要插入的片段。
 */
void net_buf_frag_insert(struct net_buf *parent, struct net_buf *frag);

/**
 * @brief 将新片段添加到bufs链的末端。
 *
 * 将一个新片段附加到缓冲区片段列表中。
 *
 * 注意：此函数获取片段引用的所有权，因此不需要调用方取消引用。
 *
 * @param head 碎片链的头部。
 * @param frag 要添加的片段。
 *
 * @return 碎片链的新头。head（如果head为非NULL）或frag（如果head为NULL）。
 */
struct net_buf *net_buf_frag_add(struct net_buf *head, struct net_buf *frag);

/**
 * @brief 从bufs链中删除现有片段。
 *
 * @param parent 父缓冲区/片段，如果没有父缓冲区，则为NULL。
 * @param frag 要删除的片段。
 *
 * @return 指向片段后面的缓冲区的指针，如果没有其他片段，则返回NULL。
 */
#if defined(CONFIG_BLE_MESH_NET_BUF_LOG)
struct net_buf *net_buf_frag_del_debug(struct net_buf *parent,
                                       struct net_buf *frag,
                                       const char *func, int line);
#define net_buf_frag_del(_parent, _frag) \
    net_buf_frag_del_debug(_parent, _frag, __func__, __LINE__)
#else
struct net_buf *net_buf_frag_del(struct net_buf *parent, struct net_buf *frag);
#endif

/**
 * @brief 将从偏移量开始的net_buf链中的字节复制到线性缓冲区
 *
 * Copy (extract) @a 来自@asrc-net_buf链的len字节，从@a开始
 * offset in it, to a linear buffer @a 数据表。返回实际复制的字节数，如果net_buf链没有足够的数据，或者目标缓冲区太小，则可能小于请求的字节数。
 *
 * @param dst 目标缓冲区
 * @param dst_len 目标缓冲区长度
 * @param src 源net_buf链
 * @param offset 要复制的起始偏移量
 * @param len 要复制的字节数
 * @return 实际复制的字节数
 */
size_t net_buf_linearize(void *dst, size_t dst_len,
                         struct net_buf *src, size_t offset, size_t len);

/**
 * @typedef net_buf_allocater_cb
 * @brief 网络缓冲区分配器回调。
 *
 * @details 当net_buf_append_bytes需要分配新的net_buf时，将调用分配器回调。
 *
 * @param timeout 影响网络缓冲池为空时采取的操作。如果K_NO_WAIT，则立即返回。如果K_FOREVER，则根据需要等待。否则，在超时前等待指定的毫秒数。
 * @param user_data net_buf_append_bytes调用中给定的用户数据。
 * @return 指向分配的net_buf或NULL的指针。
 */
typedef struct net_buf *(*net_buf_allocator_cb)(int32_t timeout, void *user_data);

/**
 * @brief 将数据附加到net_buf列表
 *
 * @details 将数据附加到net_buf。如果net_buf中没有足够的空间，那么将添加更多的net_buf，除非没有可用的net_buf并且发生超时。
 *
 * @param buf 网络缓冲区。
 * @param len 输入数据的总长度
 * @param value 要添加的数据
 * @param timeout 超时被传递给net_buf分配器回调。
 * @param allocate_cb 当需要新的net_buf时，请使用此回调。
 * @param user_data 要提供给allocate_cb的用户数据指针。这个指针可以是mem_pool或net_pkt中的任何一个，逻辑由allocate_cb函数决定。
 *
 * @return 实际添加的数据长度。如果使用了除K_FOREVER之外的其他超时，并且池中没有可容纳所有数据的空闲片段，则这可能小于输入长度。
 */
size_t net_buf_append_bytes(struct net_buf *buf, size_t len,
                            const void *value, int32_t timeout,
                            net_buf_allocator_cb allocate_cb, void *user_data);

/**
 * @brief 跳过net_buf中的N个字节
 *
 * @details 从片段的偏移量开始跳过N个字节。如果将数据的总长度放在多个片段中，此函数将从所有片段中跳过，直到达到N个字节。将从net_buf列表中删除所有完全跳过的缓冲区。
 *
 * @param buf 网络缓冲区。
 * @param len 要跳过的数据的总长度。
 *
 * @return 指向片段的指针或NULL，成功跳过后pos为0，否则NULL，pos为0xffff。
 */
static inline struct net_buf *net_buf_skip(struct net_buf *buf, size_t len)
{
    while (buf && len--) {
        net_buf_pull_u8(buf);
        if (!buf->len) {
            buf = net_buf_frag_del(NULL, buf);
        }
    }

    return buf;
}

/**
 * @brief 计算存储在片段中的字节数。
 *
 * 计算存储在给定缓冲区及其链接的片段中的数据总量。
 *
 * @param buf 开始时使用的缓冲区。
 *
 * @return 缓冲区及其片段中的字节数。
 */
static inline size_t net_buf_frags_len(struct net_buf *buf)
{
    size_t bytes = 0;

    while (buf) {
        bytes += buf->len;
        buf = buf->frags;
    }

    return bytes;
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* _BLE_MESH_BUF_H_ */

