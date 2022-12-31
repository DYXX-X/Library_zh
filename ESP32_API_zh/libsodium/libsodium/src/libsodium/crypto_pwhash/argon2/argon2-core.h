/*
 * Argon2源代码包
 *
 * Daniel Dinu和Dmitry Khovratovich撰写，2015年
 *
 * 本作品根据Creative Commons CC0 1.0许可/弃权获得许可。
 *
 * 您应该已经收到了CC0公共域专用的副本以及此软件。如果没有，请参见<http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#ifndef argon2_core_H
#define argon2_core_H

#include <string.h>

#include "argon2.h"

/*************************Argon2内部常数**************************************************/

enum argon2_ctx_constants {
    /* 算法版本*/
    ARGON2_VERSION_NUMBER = 0x13,

    /* 内存块大小（字节）*/
    ARGON2_BLOCK_SIZE      = 1024,
    ARGON2_QWORDS_IN_BLOCK = ARGON2_BLOCK_SIZE / 8,
    ARGON2_OWORDS_IN_BLOCK = ARGON2_BLOCK_SIZE / 16,
    ARGON2_HWORDS_IN_BLOCK = ARGON2_BLOCK_SIZE / 32,
    ARGON2_512BIT_WORDS_IN_BLOCK = ARGON2_BLOCK_SIZE / 64,

    /* 通过调用Argon2i中的Blake生成参考块位置的伪随机值的数量*/
    ARGON2_ADDRESSES_IN_BLOCK = 128,

    /* 预哈希摘要长度及其扩展*/
    ARGON2_PREHASH_DIGEST_LENGTH = 64,
    ARGON2_PREHASH_SEED_LENGTH   = 72
};

/*************************Argon2内部数据类型**************************************************/

/*
 * 实现为128个64位字的（1KB）存储块的结构。内存块可以被复制、异或。内部单词可以通过[]访问（无边界检查）。
 */
typedef struct block_ {
    uint64_t v[ARGON2_QWORDS_IN_BLOCK];
} block;

typedef struct block_region_ {
    void * base;
    block *memory;
    size_t size;
} block_region;

/*****************与块一起工作的函数******************/

/* 用@in初始化块的每个字节*/
static inline void
init_block_value(block *b, uint8_t in)
{
    memset(b->v, in, sizeof(b->v));
}

/* 将block@src复制到block@dst*/
static inline void
copy_block(block *dst, const block *src)
{
    memcpy(dst->v, src->v, sizeof(uint64_t) * ARGON2_QWORDS_IN_BLOCK);
}

/* 将@src按字节XOR到@dst*/
static inline void
xor_block(block *dst, const block *src)
{
    int i;
    for (i = 0; i < ARGON2_QWORDS_IN_BLOCK; ++i) {
        dst->v[i] ^= src->v[i];
    }
}

/*
 * Argon2实例：内存指针、传递次数、内存量、类型和派生值。用于评估每个线程中要构建的块的数量和位置
 */
typedef struct Argon2_instance_t {
    block_region *region;        /* 内存区域指针*/
    uint64_t     *pseudo_rands;
    uint32_t      passes;        /* 通过次数*/
    uint32_t      current_pass;
    uint32_t      memory_blocks; /* 内存中的块数*/
    uint32_t      segment_length;
    uint32_t      lane_length;
    uint32_t      lanes;
    uint32_t      threads;
    argon2_type   type;
    int           print_internals; /* 是否打印内存块*/
} argon2_instance_t;

/*
 * Argon2位置：我们现在建造区块的位置。用于在线程之间分配工作。
 */
typedef struct Argon2_position_t {
    uint32_t pass;
    uint32_t lane;
    uint8_t  slice;
    uint32_t index;
} argon2_position_t;

/*保存线程处理FillSegment的输入的结构*/
typedef struct Argon2_thread_data {
    argon2_instance_t *instance_ptr;
    argon2_position_t  pos;
} argon2_thread_data;

/*************************Argon2核心功能**************************************************/

/*
 * 使用伪随机值作为输入，按照倾斜分布计算车道中参考块的绝对位置
 * @param instance 指向当前实例的指针
 * @param position 指向当前位置的指针
 * @param pseudo_rand 用于确定位置的32位伪随机值
 * @param same_lane 指示是否将从当前车道获取块。如果是，我们可以引用当前段
 * @pre 所有指针都必须有效
 */
static uint32_t index_alpha(const argon2_instance_t *instance,
                            const argon2_position_t *position, uint32_t pseudo_rand,
                            int same_lane)
{
    /*
     * 通道0：此通道：此段中所有已完成的段加上已构建的块其他通道：所有已完成段通道1+：此通道（SYNC_POINTS-1）此段中最后一段加上已经构建的块
     */
    uint32_t reference_area_size;
    uint64_t relative_position;
    uint32_t start_position, absolute_position;

    if (position->pass == 0) {
        /* 第一次通过*/
        if (position->slice == 0) {
            /* 第一个切片*/
            reference_area_size =
                position->index - 1; /* 除了上一个*/
        } else {
            if (same_lane) {
                /* 同一车道=>添加当前路段*/
                reference_area_size =
                    position->slice * instance->segment_length +
                    position->index - 1;
            } else {
                reference_area_size =
                    position->slice * instance->segment_length +
                    ((position->index == 0) ? (-1) : 0);
            }
        }
    } else {
        /* 第二遍*/
        if (same_lane) {
            reference_area_size = instance->lane_length -
                                  instance->segment_length + position->index -
                                  1;
        } else {
            reference_area_size = instance->lane_length -
                                  instance->segment_length +
                                  ((position->index == 0) ? (-1) : 0);
        }
    }

    /* 1.2.4.将伪区域映射到0..<reference_area_size-1>并生成相对位置*/
    relative_position = pseudo_rand;
    relative_position = relative_position * relative_position >> 32;
    relative_position = reference_area_size - 1 -
                        (reference_area_size * relative_position >> 32);

    /* 1.2.5计算起始位置*/
    start_position = 0;

    if (position->pass != 0) {
        start_position = (position->slice == ARGON2_SYNC_POINTS - 1)
                             ? 0
                             : (position->slice + 1) * instance->segment_length;
    }

    /* 1.2.6.计算绝对位置*/
    absolute_position = (start_position + relative_position) %
                        instance->lane_length; /* 绝对位置，绝对位置*/
    return absolute_position;
}

/*
 * 根据预定义的限制验证所有输入并返回错误代码的函数
 * @param context 指向当前Argon2上下文的指针
 * @return ARGON2_OK（如果一切正常），否则为一个错误代码（都在<ARGON2.h>中定义）
 */
int validate_inputs(const argon2_context *context);

/*
 * Hashes all the inputs into @a blockhash[PREHASH_DIGEST_LENGTH]，如果需要，清除密码和密码
 * @param  context  指向Argon2内部结构的指针，包含内存指针以及时间和空间要求的参数。
 * @param  blockhash 用于预哈希摘要的缓冲区
 * @param  type Argon2型
 * @pre    @blockhash必须至少分配@个PREHASH_DIGEST_LENGTH字节
 */
void initial_hash(uint8_t *blockhash, argon2_context *context,
                  argon2_type type);

/*
 * 函数为每条车道创建前2个块
 * @param instance 指向当前实例的指针
 * @param blockhash 指向预哈希摘要的指针
 * @pre blockhash必须指向@a PREHASH_SEND_LENGTH分配的值
 */
void fill_first_blocks(uint8_t *blockhash, const argon2_instance_t *instance);

/*
 * 函数分配内存，用Blake散列输入，并创建前两个块。返回每个通道初始化2个块的主内存指针
 * @param  context  指向Argon2内部结构的指针，包含内存指针以及时间和空间要求的参数。
 * @param  instance 当前Argon2实例
 * @return 如果成功，则为零；如果内存分配失败，则为-1@如果成功，context->state将被修改。
 */
int initialize(argon2_instance_t *instance, argon2_context *context);

/*
 * 取消分配内存。用于错误路径。
 */
void free_instance(argon2_instance_t *instance, int flags);

/*
 * 对每条通道的最后一个块进行异或运算，对其进行哈希运算，生成标记。取消分配内存。
 * @param context 指向当前Argon2上下文的指针（仅使用其中的out参数）
 * @param instance 指向Argon2当前实例的指针
 * @pre 实例->状态必须指向所需的内存量
 * @pre context->out必须指向内存的outlet字节
 * @pre 如果context->free_cbk不为NULL，它应该指向释放内存的函数
 */
void finalize(const argon2_context *context, argon2_instance_t *instance);

/*
 * 函数，该函数使用其他线程中的先前段填充段
 * @param instance 指向当前实例的指针
 * @param position 当前位置
 * @pre 所有块指针都必须有效
 */
typedef void (*fill_segment_fn)(const argon2_instance_t *instance,
                                argon2_position_t        position);
int argon2_pick_best_implementation(void);
void fill_segment_avx512f(const argon2_instance_t *instance,
                          argon2_position_t        position);
void fill_segment_avx2(const argon2_instance_t *instance,
                       argon2_position_t        position);
void fill_segment_ssse3(const argon2_instance_t *instance,
                        argon2_position_t        position);
void fill_segment_ref(const argon2_instance_t *instance,
                      argon2_position_t        position);

/*
 * 基于每个通道中的前两个块填充整个内存t_cost时间的函数
 * @param instance 指向当前实例的指针
 * @return 如果成功，则为零；如果内存分配失败，则为-1
 */
void fill_memory_blocks(argon2_instance_t *instance, uint32_t pass);

#endif

