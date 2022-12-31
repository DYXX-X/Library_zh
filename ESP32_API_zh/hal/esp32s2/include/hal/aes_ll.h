// 版权所有2020-2021 Espressif Systems（Shanghai）CO LTD
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
#include <string.h>
#include "soc/hwcrypto_reg.h"
#include "hal/aes_types.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief AES加速器的状态，忙、空闲或已完成
 *
 */
typedef enum {
    ESP_AES_STATE_IDLE = 0, /* AES加速器处于空闲状态*/
    ESP_AES_STATE_BUSY,     /* 正在进行转换*/
    ESP_AES_STATE_DONE,     /* 转换已完成*/
} esp_aes_state_t;


/**
 * @brief 将加密/解密密钥写入硬件
 *
 * @param key 要写入AES硬件的密钥
 * @param key_word_len 关键字中的单词数
 *
 * @return 写入硬件的字节数，用于故障注入检查
 */
static inline uint8_t aes_ll_write_key(const uint8_t *key, size_t key_word_len)
{
    /* 此变量用于故障注入检查，因此标记为易失性，以避免优化*/
    volatile uint8_t key_in_hardware = 0;
    /* 避免潜在未对齐访问的备忘录*/
    uint32_t key_word;
    for (int i = 0; i < key_word_len; i++) {
        memcpy(&key_word, key + 4 * i, 4);
        REG_WRITE(AES_KEY_BASE + i * 4,  key_word);
        key_in_hardware += 4;
    }
    return key_in_hardware;
}

/**
 * @brief 设置模式
 *
 * @param mode ESP_AES_ENCRYPT=1或ESP_AES_DECRYPT=0
 * @param key_bytes 密钥中的字节数
 */
static inline void aes_ll_set_mode(int mode, uint8_t key_bytes)
{
    const uint32_t MODE_DECRYPT_BIT = 4;
    unsigned mode_reg_base = (mode == ESP_AES_ENCRYPT) ? 0 : MODE_DECRYPT_BIT;

    /* 有关键长和模式位之间的映射，请参见TRM*/
    REG_WRITE(AES_MODE_REG, mode_reg_base + ((key_bytes / 8) - 2));
}

/**
 * @brief 将消息块写入AES硬件
 *
 * @param input 要写入的块
 */
static inline void aes_ll_write_block(const void *input)
{
    uint32_t input_word;

    for (int i = 0; i < AES_BLOCK_WORDS; i++) {
        memcpy(&input_word, (uint8_t*)input + 4 * i, 4);
        REG_WRITE(AES_TEXT_IN_BASE + i * 4, input_word);
    }
}

/**
 * @brief 读取AES块
 *
 * @param output 变换的输出，长度=AES_BLOCK_BYTES
 */
static inline void aes_ll_read_block(void *output)
{
    uint32_t output_word;
    const size_t REG_WIDTH = sizeof(uint32_t);

    for (size_t i = 0; i < AES_BLOCK_WORDS; i++) {
        output_word = REG_READ(AES_TEXT_OUT_BASE + (i * REG_WIDTH));
        /* 避免潜在未对齐访问的备忘录*/
        memcpy( (uint8_t*)output + i * 4, &output_word, sizeof(output_word));
    }
}


/**
 * @brief 开始块变换
 *
 */
static inline void aes_ll_start_transform(void)
{
    REG_WRITE(AES_TRIGGER_REG, 1);
}

/**
 * @brief 继续上一次启动的变换
 *
 * @note 仅在执行GCM时使用
 */
static inline void aes_ll_cont_transform(void)
{
    REG_WRITE(AES_CONTINUE_REG, 1);
}

/**
 * @brief 读取AES加速器的状态
 *
 * @return 具体日期
 */
static inline esp_aes_state_t aes_ll_get_state(void)
{
    return REG_READ(AES_STATE_REG);
}


/**
 * @brief 设置操作模式
 *
 * @note 仅用于DMA转换
 *
 * @param mode
 */
static inline void aes_ll_set_block_mode(esp_aes_mode_t mode)
{
    REG_WRITE(AES_BLOCK_MODE_REG, mode);
}

/**
 * @brief 将AES-CTR计数器设置为INC32
 *
 * @note 仅影响AES-CTR模式
 *
 */
static inline void aes_ll_set_inc(void)
{
    REG_WRITE(AES_INC_SEL_REG, 0);
}

/**
 * @brief 释放DMA
 *
 */
static inline void aes_ll_dma_exit(void)
{
    REG_WRITE(AES_DMA_EXIT_REG, 0);
}

/**
 * @brief 设置要转换的块数
 *
 * @note 仅用于DMA转换
 *
 * @param num_blocks 要转换的块数
 */
static inline void aes_ll_set_num_blocks(size_t num_blocks)
{
    REG_WRITE(AES_BLOCK_NUM_REG, num_blocks);
}

/*
 * 将IV写入硬件IV寄存器
 */
static inline void aes_ll_set_iv(const uint8_t *iv)
{
    uint32_t *reg_addr_buf = (uint32_t *)(AES_IV_BASE);
    uint32_t iv_word;

    for (int i = 0; i < IV_WORDS; i++ ) {
        /* 避免潜在未对齐访问的备忘录*/
        memcpy(&iv_word, iv + 4 * i, sizeof(iv_word));
        REG_WRITE(&reg_addr_buf[i], iv_word);
    }
}

/*
 * 从硬件IV寄存器读取IV
 */
static inline void aes_ll_read_iv(uint8_t *iv)
{
    uint32_t iv_word;
    const size_t REG_WIDTH = sizeof(uint32_t);

    for (size_t i = 0; i < IV_WORDS; i++) {
        iv_word = REG_READ(AES_IV_BASE + (i * REG_WIDTH));
        /* 避免潜在未对齐访问的备忘录*/
        memcpy(iv + i * 4, &iv_word, sizeof(iv_word));
    }
}

/**
 * @brief 启用或禁用DMA模式
 *
 * @param enable true表示启用，false表示禁用。
 */
static inline void aes_ll_dma_enable(bool enable)
{
    REG_WRITE(AES_DMA_ENABLE_REG, enable);
}

/**
 * @brief 启用或禁用转换完成中断
 *
 * @param enable true表示启用，false表示禁用。
 */
static inline void aes_ll_interrupt_enable(bool enable)
{
    REG_WRITE(AES_INT_ENA_REG, enable);
}

/**
 * @brief 清除中断
 *
 */
static inline void aes_ll_interrupt_clear(void)
{
    REG_WRITE(AES_INT_CLR_REG, 1);
}

/**
 * @brief 读取AES-GCM哈希子密钥H
 *
 * @param gcm_hash 散列值
 */
static inline void aes_ll_gcm_read_hash(uint8_t *gcm_hash)
{
    const size_t REG_WIDTH = sizeof(uint32_t);
    uint32_t hash_word;

    for (size_t i = 0; i < AES_BLOCK_WORDS; i++) {
        hash_word = REG_READ(AES_H_BASE + (i * REG_WIDTH));
        /* 避免潜在未对齐访问的备忘录*/
        memcpy(gcm_hash + i * 4, &hash_word, sizeof(hash_word));
    }
}

/**
 * @brief 设置附加身份验证数据（AAD）块的数量
 *
 * @note 仅影响AES-GCM
 *
 * @param aad_num_blocks 附加认证数据（AAD）块的数量
 */
static inline void aes_ll_gcm_set_aad_num_blocks(size_t aad_num_blocks)
{
    REG_WRITE(AES_AAD_BLOCK_NUM_REG, aad_num_blocks);
}

/**
 * @brief 设置J0值，有关更多信息，请参阅TRM中的GCM分章
 *
 * @note 仅影响AES-GCM
 *
 * @param j0 J0值
 */
static inline void aes_ll_gcm_set_j0(const uint8_t *j0)
{
    uint32_t *reg_addr_buf = (uint32_t *)(AES_J_BASE);
    uint32_t j0_word;

    for (int i = 0; i < AES_BLOCK_WORDS; i++ ) {
    /* 避免潜在未对齐访问的备忘录*/
        memcpy(&j0_word, j0 + 4 * i, sizeof(j0_word));
        REG_WRITE(&reg_addr_buf[i], j0_word);
    }
}

/**
 * @brief 设置明文/密文中不完整块的有效位数。
 *
 * @note 仅影响AES-GCM
 *
 * @param num_valid_bits 明文/密文中不完整块的有效位数。
 */
static inline void aes_ll_gcm_set_num_valid_bit(size_t num_valid_bits)
{
    REG_WRITE(AES_BIT_VALID_NUM_REG, num_valid_bits);
}

/**
 * @brief AES-GCM转换后读取标签
 *
 * @param tag 指向存储长度为TAG_WORDS的结果的位置的指针
 */
static inline void aes_ll_gcm_read_tag(uint8_t *tag)
{
    uint32_t tag_word;
    const size_t REG_WIDTH = sizeof(uint32_t);

    for (size_t i = 0; i < TAG_WORDS; i++) {
        tag_word = REG_READ(AES_T_BASE + (i * REG_WIDTH));
        /* 避免潜在未对齐访问的备忘录*/
        memcpy(tag + i * 4, &tag_word, sizeof(tag_word));
    }
}

#ifdef __cplusplus
}
#endif

