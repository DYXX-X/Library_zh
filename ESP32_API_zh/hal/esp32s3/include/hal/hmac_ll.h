/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/*******************************************************************************
 * 注意hal不是公共api，不要在应用程序代码中使用它。请参阅自述文件。soc/include/hal/readme.md中的md
 ******************************************************************************/

#pragma once

#include "soc/hwcrypto_reg.h"

#define SHA256_BLOCK_SZ 64
#define SHA256_DIGEST_SZ 32

#define HMAC_LL_EFUSE_KEY_PURPOSE_DOWN_JTAG 6
#define HMAC_LL_EFUSE_KEY_PURPOSE_DOWN_DIGITAL_SIGNATURE 7
#define HMAC_LL_EFUSE_KEY_PURPOSE_UP 8
#define HMAC_LL_EFUSE_KEY_PURPOSE_DOWN_ALL 5

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 启用外围设备后，使其随时可用。
 */
static inline void hmac_ll_start(void)
{
    REG_WRITE(HMAC_SET_START_REG, 1);
}

/**
 * @brief 确定HMAC输出的去向。
 *
 * HMAC外围设备可以被配置为直接将其输出传递给用户，或者直接将输出传递给另一个外围设备，例如数字签名外围设备。
 */
static inline void hmac_ll_config_output(hmac_hal_output_t config)
{
    switch(config) {
    case HMAC_OUTPUT_USER:
        REG_WRITE(HMAC_SET_PARA_PURPOSE_REG, HMAC_LL_EFUSE_KEY_PURPOSE_UP);
        break;
    case HMAC_OUTPUT_DS:
        REG_WRITE(HMAC_SET_PARA_PURPOSE_REG, HMAC_LL_EFUSE_KEY_PURPOSE_DOWN_DIGITAL_SIGNATURE);
        break;
    case HMAC_OUTPUT_JTAG_ENABLE:
        REG_WRITE(HMAC_SET_PARA_PURPOSE_REG, HMAC_LL_EFUSE_KEY_PURPOSE_DOWN_JTAG);
        break;
    case HMAC_OUTPUT_ALL:
        REG_WRITE(HMAC_SET_PARA_PURPOSE_REG, HMAC_LL_EFUSE_KEY_PURPOSE_DOWN_ALL);
        break;
    default:
        ; // 不执行任何操作，错误将由hmac_hal_config_error（）指示
    }
}

/**
 * @brief 选择应使用的硬件密钥。
 */
static inline void hmac_ll_config_hw_key_id(uint32_t key_id)
{
    REG_WRITE(HMAC_SET_PARA_KEY_REG, key_id);
}

/**
 * @brief 应用并检查配置。
 *
 * 然后，可以使用hmac_hal_config_error（）检查配置是否存在错误。
 */
static inline void hmac_ll_config_finish(void)
{
    REG_WRITE(HMAC_SET_PARA_FINISH_REG, 1);
}

/**
 *
 * @brief 配置操作后查询HMAC错误状态。
 *
 * @return
 *  -出错时为1或更大
 *  -成功时为0
 */
static inline uint32_t hmac_ll_query_config_error(void)
{
    return REG_READ(HMAC_QUERY_ERROR_REG);
}

/**
 * 等待HAL准备好进行下一次交互。
 */
static inline void hmac_ll_wait_idle(void)
{
    uint32_t query;
    do {
        query = REG_READ(HMAC_QUERY_BUSY_REG);
    } while(query != 0);
}

/**
 * @brief 向HMAC外围设备写入512位的消息块。
 */
static inline void hmac_ll_write_block_512(const uint32_t *block)
{
    const size_t REG_WIDTH = sizeof(uint32_t);
    for (size_t i = 0; i < SHA256_BLOCK_SZ / REG_WIDTH; i++) {
        REG_WRITE(HMAC_WDATA_BASE + (i * REG_WIDTH), block[i]);
    }

    REG_WRITE(HMAC_SET_MESSAGE_ONE_REG, 1);
}

/**
 * @brief 读取256位HMAC。
 */
static inline void hmac_ll_read_result_256(uint32_t *result)
{
    const size_t REG_WIDTH = sizeof(uint32_t);
    for (size_t i = 0; i < SHA256_DIGEST_SZ / REG_WIDTH; i++) {
        result[i] = REG_READ(HMAC_RDATA_BASE + (i * REG_WIDTH));
    }
}

/**
 * @brief 清理提供给其他硬件的HMAC结果。
 */
static inline void hmac_ll_clean(void)
{
    REG_WRITE(HMAC_SET_INVALIDATE_DS_REG, 1);
    REG_WRITE(HMAC_SET_INVALIDATE_JTAG_REG, 1);
}

/**
 * @brief 表示下一个块将是填充的最后一个块。
 */
static inline void hmac_ll_msg_padding(void)
{
    REG_WRITE(HMAC_SET_MESSAGE_PAD_REG, 1);
}

/**
 * @brief 硬件将自动应用所有块已写入和填充块的信号。
 *
 * 仅当消息长度为512位的倍数时适用。有关详细信息，请参阅ESP32S3 TRM HMAC章节。
 */
static inline void hmac_ll_msg_end(void)
{
    REG_WRITE(HMAC_SET_MESSAGE_END_REG, 1);
}

/**
 * @brief 包含填充的消息适合一个块，因此不需要采取进一步的操作。
 *
 * 这是在写入一个块消息后调用的。
 */
static inline void hmac_ll_msg_one_block(void)
{
    REG_WRITE(HMAC_ONE_BLOCK_REG, 1);
}

/**
 * @brief 指示将在最后一个块之后写入更多块。
 */
static inline void hmac_ll_msg_continue(void)
{
    REG_WRITE(HMAC_SET_MESSAGE_ING_REG, 1);
}

/**
 * @brief 清除HMAC结果。
 *
 * 在读取HMAC结果后，或者如果在上述任何其他步骤后中止，请使用此选项。
 */
static inline void hmac_ll_calc_finish(void)
{
    REG_WRITE(HMAC_SET_RESULT_FINISH_REG, 2);
}

#ifdef __cplusplus
}
#endif

