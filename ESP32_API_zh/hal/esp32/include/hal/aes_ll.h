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

#include "soc/hwcrypto_reg.h"
#include "soc/dport_access.h"
#include "hal/aes_types.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief AES加速器的状态，忙或空闲
 *
 */
typedef enum {
    ESP_AES_STATE_BUSY = 0, /* 正在进行转换*/
    ESP_AES_STATE_IDLE,     /* AES加速器处于空闲状态*/
} esp_aes_state_t;


/**
 * @brief 将加密/解密密钥写入硬件
 *
 * @param key 要写入AES硬件的密钥
 * @param key_word_len 关键字中的单词数
 *
 * @return 写入硬件的字节数，用于故障注入检查，如果跳过写入，则此总和可能错误
 */
static inline uint8_t aes_ll_write_key(const uint8_t *key, size_t key_word_len)
{
    /* 此变量用于故障注入检查，因此标记为易失性，以避免优化*/
    volatile uint8_t key_bytes_in_hardware = 0;

    /* 避免潜在未对齐访问的备忘录*/
    uint32_t key_word;

    for (int i = 0; i < key_word_len; i++) {
        memcpy(&key_word, key + 4 * i, 4);
        DPORT_REG_WRITE(AES_KEY_BASE + i * 4, key_word);
        key_bytes_in_hardware += 4;
    }
    return key_bytes_in_hardware;
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
    DPORT_REG_WRITE(AES_MODE_REG, mode_reg_base + ((key_bytes / 8) - 2));
}

/**
 * @brief 将消息块写入AES硬件
 *
 * @param input 要写入的块
 */
static inline void aes_ll_write_block(const uint8_t *input)
{
    const uint32_t *input_words = (const uint32_t *)input;
    uint32_t i0;
    uint32_t i1;
    uint32_t i2;
    uint32_t i3;

    /* 将i0、i1、i2、i3存储在寄存器而不是阵列中有助于在-O级别进行优化*/
    i0 = input_words[0];
    DPORT_REG_WRITE(AES_TEXT_BASE, i0);

    i1 = input_words[1];
    DPORT_REG_WRITE(AES_TEXT_BASE + 4, i1);

    i2 = input_words[2];
    DPORT_REG_WRITE(AES_TEXT_BASE + 8, i2);

    i3 = input_words[3];
    DPORT_REG_WRITE(AES_TEXT_BASE + 12, i3);
}

/**
 * @brief 读取AES块
 *
 * @note 如果运行了转换，则这是输出
 *
 * @param output 变换的输出，长度=AES_BLOCK_BYTES
 */
static inline void aes_ll_read_block(void *output)
{
    uint32_t *output_words = (uint32_t *)output;
    esp_dport_access_read_buffer(output_words, AES_TEXT_BASE, AES_BLOCK_WORDS);
}


/**
 * @brief 开始块变换
 *
 */
static inline void aes_ll_start_transform(void)
{
    DPORT_REG_WRITE(AES_START_REG, 1);
}


/**
 * @brief 读取AES加速器的状态
 *
 * @return 具体日期
 */
static inline esp_aes_state_t aes_ll_get_state(void)
{
    return DPORT_REG_READ(AES_IDLE_REG);
}

#ifdef __cplusplus
}
#endif

