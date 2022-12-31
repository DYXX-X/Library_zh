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

/*******************************************************************************
 * 注意hal不是公共api，不要在应用程序代码中使用它。
 ******************************************************************************/

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "soc/hwcrypto_reg.h"
#include "soc/soc_caps.h"

#ifdef __cplusplus
extern "C" {
#endif

static inline void ds_ll_start(void)
{
    REG_WRITE(DS_SET_START_REG, 1);
}

/**
 * @brief 等待DS外围设备完成任何未完成的操作。
 */
static inline bool ds_ll_busy(void)
{
    return (REG_READ(DS_QUERY_BUSY_REG) > 0) ? true : false;
}

/**
 * @brief 忙等待硬件就绪。
 */
static inline void ds_ll_wait_busy(void)
{
    while (ds_ll_busy());
}

/**
 * @brief 如果出现键错误，请检查导致错误的原因。
 */
static inline ds_key_check_t ds_ll_key_error_source(void)
{
    uint32_t key_error = REG_READ(DS_QUERY_KEY_WRONG_REG);
    if (key_error == 0) {
        return DS_NO_KEY_INPUT;
    } else {
        return DS_OTHER_WRONG;
    }
}

/**
 * @brief 将初始化向量写入相应的寄存器字段。
 */
static inline void ds_ll_configure_iv(const uint32_t *iv)
{
    for (size_t i = 0; i < (SOC_DS_KEY_PARAM_MD_IV_LENGTH / sizeof(uint32_t)); i++) {
        REG_WRITE(DS_IV_BASE + (i * 4) , iv[i]);
    }
}

/**
 * @brief 写下应该签名的消息。
 *
 * @param msg 指向消息的指针。
 * @param size 消息长度（字节）。它是以字节为单位的RSA签名长度。
 */
static inline void ds_ll_write_message(const uint8_t *msg, size_t size)
{
    memcpy((uint8_t*) DS_X_BASE, msg, size);
    asm volatile ("fence");
}

/**
 * @brief 写入加密的私钥参数。
 */
static inline void ds_ll_write_private_key_params(const uint8_t *encrypted_key_params)
{
    /* 注意：由于内部外围设备仍然具有RSA 4096结构，但C是基于实际最大RSA长度（ETS_DS_max_BITS）加密的，因此在复制到硬件时需要将其片段化。。。

       （注意，如果ETS_DS_MAX_BITS==4096，这应与将数据->c复制到一个片段中的硬件相同）
    */
    typedef struct { uint32_t addr; size_t len; } frag_t;
    const frag_t frags[] = {
                            {DS_C_Y_BASE,  SOC_DS_SIGNATURE_MAX_BIT_LEN / 8},
                            {DS_C_M_BASE,  SOC_DS_SIGNATURE_MAX_BIT_LEN / 8},
                            {DS_C_RB_BASE, SOC_DS_SIGNATURE_MAX_BIT_LEN / 8},
                            {DS_C_BOX_BASE, DS_IV_BASE - DS_C_BOX_BASE},
    };
    const size_t NUM_FRAGS = sizeof(frags)/sizeof(frag_t);
    const uint8_t *from = encrypted_key_params;

    for (int i = 0; i < NUM_FRAGS; i++) {
        memcpy((uint8_t *)frags[i].addr, from, frags[i].len);
        asm volatile ("fence");
        from += frags[i].len;
    }
}

/**
 * @brief 开始签名过程。
 */
static inline void ds_ll_start_sign(void)
{
    REG_WRITE(DS_SET_ME_REG, 1);
}

/**
 * @brief 检查计算的签名。
 *
 * @return
 * -DS_SIGNATURE_OK（如果未检测到签名问题）。
 * -如果私钥参数的填充错误，则返回DS_SIGNATURE_PADING_FAIL。
 * -如果消息摘要检查失败，则为DS_SIGNATURE_MD_FAIL。这意味着使用私钥参数计算的消息摘要失败，即私钥参数的完整性不受保护。
 * -如果填充和消息摘要检查都失败，则DS_SIGNATURE_PADING_AND_MD_FAIL。
 */
static inline ds_signature_check_t ds_ll_check_signature(void)
{
    uint32_t result = REG_READ(DS_QUERY_CHECK_REG);
    switch(result) {
    case 0:
        return DS_SIGNATURE_OK;
    case 1:
        return DS_SIGNATURE_MD_FAIL;
    case 2:
        return DS_SIGNATURE_PADDING_FAIL;
    default:
        return DS_SIGNATURE_PADDING_AND_MD_FAIL;
    }
}

/**
 * @brief 从硬件读取签名。
 *
 * @param result 签名结果。
 * @param size 签名结果的长度（字节）。它是以字节为单位的RSA签名长度。
 */
static inline void ds_ll_read_result(uint8_t *result, size_t size)
{
    memcpy(result, (uint8_t*) DS_Z_BASE, size);
    asm volatile ("fence");
}

/**
 * @brief 退出签名操作。
 *
 * @note 这不会停用模块。必须触发相应的时钟/复位位以进行去激活。
 */
static inline void ds_ll_finish(void)
{
    REG_WRITE(DS_SET_FINISH_REG, 1);
    ds_ll_wait_busy();
}

#ifdef __cplusplus
}
#endif

