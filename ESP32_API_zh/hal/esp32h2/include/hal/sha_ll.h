// 版权所有2020 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。
#pragma once

#include <stdbool.h>
#include "soc/hwcrypto_reg.h"
#include "hal/sha_types.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief 开始新的SHA块转换（硬件中没有初始哈希）
 *
 * @param sha_type SHA算法类型
 */
static inline void sha_ll_start_block(esp_sha_type sha_type)
{
    REG_WRITE(SHA_MODE_REG, sha_type);
    REG_WRITE(SHA_START_REG, 1);
}

/**
 * @brief 继续SHA块转换（硬件中的初始哈希）
 *
 * @param sha_type SHA算法类型
 */
static inline void sha_ll_continue_block(esp_sha_type sha_type)
{
    REG_WRITE(SHA_MODE_REG, sha_type);
    REG_WRITE(SHA_CONTINUE_REG, 1);
}

/**
 * @brief 使用DMA开始新的SHA消息转换（硬件中没有初始哈希）
 *
 * @param sha_type SHA算法类型
 */
static inline void sha_ll_start_dma(esp_sha_type sha_type)
{
    REG_WRITE(SHA_MODE_REG, sha_type);
    REG_WRITE(SHA_DMA_START_REG, 1);
}

/**
 * @brief 使用DMA（硬件中的初始哈希）继续SHA消息转换
 *
 * @param sha_type SHA算法类型
 */
static inline void sha_ll_continue_dma(esp_sha_type sha_type)
{
    REG_WRITE(SHA_MODE_REG, sha_type);
    REG_WRITE(SHA_DMA_CONTINUE_REG, 1);
}

/**
 * @brief 将当前哈希摘要加载到摘要寄存器
 *
 * @note 在ESP32S3上自动发生
 *
 * @param sha_type SHA算法类型
 */
static inline void sha_ll_load(esp_sha_type sha_type)
{
}

/**
 * @brief 设置要哈希的消息块数
 *
 * @note 仅DMA操作
 *
 * @param num_blocks 要处理的消息块数
 */
static inline void sha_ll_set_block_num(size_t num_blocks)
{
    REG_WRITE(SHA_BLOCK_NUM_REG, num_blocks);
}

/**
 * @brief 检查SHA引擎当前是否正忙于哈希块
 *
 * @return 真正的SHA引擎忙
 * @return 假SHA发动机怠速
 */
static inline bool sha_ll_busy(void)
{
    return REG_READ(SHA_BUSY_REG);
}

/**
 * @brief 将文本（消息）块写入SHA引擎
 *
 * @param input_text 要写入SHA引擎的输入缓冲区
 * @param block_word_len 块中的单词数
 */
static inline void sha_ll_fill_text_block(const void *input_text, size_t block_word_len)
{
    uint32_t *data_words = (uint32_t *)input_text;
    uint32_t *reg_addr_buf = (uint32_t *)(SHA_TEXT_BASE);

    for (int i = 0; i < block_word_len; i++) {
        REG_WRITE(&reg_addr_buf[i], data_words[i]);
    }
}

/**
 * @brief 从SHA引擎读取消息摘要
 *
 * @param sha_type SHA算法类型
 * @param digest_state 消息摘要将写入的缓冲区
 * @param digest_word_len 消息摘要的长度
 */
static inline void sha_ll_read_digest(esp_sha_type sha_type, void *digest_state, size_t digest_word_len)
{
    uint32_t *digest_state_words = (uint32_t *)digest_state;
    const size_t REG_WIDTH = sizeof(uint32_t);

    for (size_t i = 0; i < digest_word_len; i++) {
        digest_state_words[i] = REG_READ(SHA_H_BASE + (i * REG_WIDTH));
    }

}

/**
 * @brief 将消息摘要写入SHA引擎
 *
 * @param sha_type SHA算法类型
 * @param digest_state 要写入SHA引擎的消息摘要
 * @param digest_word_len 消息摘要的长度
 */
static inline void sha_ll_write_digest(esp_sha_type sha_type, void *digest_state, size_t digest_word_len)
{
    uint32_t *digest_state_words = (uint32_t *)digest_state;
    uint32_t *reg_addr_buf = (uint32_t *)(SHA_H_BASE);

    for (int i = 0; i < digest_word_len; i++) {
        REG_WRITE(&reg_addr_buf[i], digest_state_words[i]);
    }
}


#ifdef __cplusplus
}
#endif

