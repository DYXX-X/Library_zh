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
#include "hal/sha_types.h"
#include "soc/hwcrypto_reg.h"
#include "soc/dport_access.h"
#include "hal/misc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SHA_LL_TYPE_OFFSET 0x10

/**
 * @brief 返回给定sha类型的LOAD_REG寄存器地址
 *
 * @param sha_type SHA算法类型
 * @return uint32_t LOAD_REG寄存器地址
 */
inline static uint32_t SHA_LOAD_REG(esp_sha_type sha_type)
{
    return SHA_1_LOAD_REG + sha_type * SHA_LL_TYPE_OFFSET;
}

/**
 * @brief 返回给定sha类型的BUSY寄存器地址
 *
 * @param sha_type SHA算法类型
 * @return uint32_t BUSY寄存器地址
 */
inline static uint32_t SHA_BUSY_REG(esp_sha_type sha_type)
{
    return SHA_1_BUSY_REG + sha_type * SHA_LL_TYPE_OFFSET;
}

/**
 * @brief 返回给定sha类型的START寄存器地址
 *
 * @param sha_type SHA算法类型
 * @return uint32_t START寄存器地址
 */
inline static uint32_t SHA_START_REG(esp_sha_type sha_type)
{
    return SHA_1_START_REG + sha_type * SHA_LL_TYPE_OFFSET;
}

/**
 * @brief 返回给定sha类型的CONTINUE寄存器地址
 *
 * @param sha_type SHA算法类型
 * @return uint32_t CONTINUE寄存器地址
 */
inline static uint32_t SHA_CONTINUE_REG(esp_sha_type sha_type)
{
    return SHA_1_CONTINUE_REG + sha_type * SHA_LL_TYPE_OFFSET;
}

/**
 * @brief 开始新的SHA块转换（硬件中没有初始哈希）
 *
 * @param sha_type SHA算法类型
 */
static inline void sha_ll_start_block(esp_sha_type sha_type)
{
    DPORT_REG_WRITE(SHA_START_REG(sha_type), 1);
}

/**
 * @brief 继续SHA块转换（硬件中的初始哈希）
 *
 * @param sha_type SHA算法类型
 */
static inline void sha_ll_continue_block(esp_sha_type sha_type)
{
    DPORT_REG_WRITE(SHA_CONTINUE_REG(sha_type), 1);
}

/**
 * @brief 将当前哈希摘要加载到摘要寄存器
 *
 * @param sha_type SHA算法类型
 */
static inline void sha_ll_load(esp_sha_type sha_type)
{
    DPORT_REG_WRITE(SHA_LOAD_REG(sha_type), 1);
}

/**
 * @brief 检查SHA引擎当前是否正忙于哈希块
 *
 * @return 真正的SHA引擎忙
 * @return 假SHA发动机怠速
 */
static inline bool sha_ll_busy(void)
{
    return (DPORT_REG_READ(SHA_1_BUSY_REG) || DPORT_REG_READ(SHA_256_BUSY_REG)
            || DPORT_REG_READ(SHA_384_BUSY_REG) || DPORT_REG_READ(SHA_512_BUSY_REG));
}

/**
 * @brief 将文本（消息）块写入SHA引擎
 *
 * @param input_text 要写入SHA引擎的输入缓冲区
 * @param block_word_len 块中的单词数
 */
static inline void sha_ll_fill_text_block(const void *input_text, size_t block_word_len)
{
    uint32_t *reg_addr_buf = NULL;
    uint32_t *data_words = NULL;
    reg_addr_buf = (uint32_t *)(SHA_TEXT_BASE);
    data_words = (uint32_t *)input_text;
    for (size_t i = 0; i < block_word_len; i++) {
        reg_addr_buf[i] = HAL_SWAP32(data_words[i]);
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
    uint32_t *reg_addr_buf  = (uint32_t *)(SHA_TEXT_BASE);
    if (sha_type == SHA2_384 || sha_type == SHA2_512) {
        /* 对于这些使用64位状态的密码，交换每对字*/
        DPORT_INTERRUPT_DISABLE(); // 仅在当前CPU上禁用中断。
        for (size_t i = 0; i < digest_word_len; i += 2) {
            digest_state_words[i + 1] = DPORT_SEQUENCE_REG_READ((uint32_t)&reg_addr_buf[i]);
            digest_state_words[i]   = DPORT_SEQUENCE_REG_READ((uint32_t)&reg_addr_buf[i + 1]);
        }
        DPORT_INTERRUPT_RESTORE(); // 恢复先前的中断级别
    } else {
        esp_dport_access_read_buffer(digest_state_words, (uint32_t)&reg_addr_buf[0], digest_word_len);
    }
}

#ifdef __cplusplus
}
#endif

