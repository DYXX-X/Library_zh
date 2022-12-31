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
 * 注意：hal不是公共api，不要在应用程序代码中使用。请参阅soc/include/hal/readme.md中的自述文件
 ******************************************************************************/

#pragma once

#include <stddef.h>
#include <stdbool.h>
#include "soc/soc_caps.h"
#include "hal/aes_types.h"
#include "hal/aes_ll.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief 设置用于AES加密/解密的密钥
 *
 * @param key 指向键的指针
 * @param key_bytes 密钥中的字节数
 * @param mode 密钥模式，0：解密，1：加密
 *
 * @return uint8_t写入硬件的密钥字节数，用于故障注入检查
 */
uint8_t aes_hal_setkey(const uint8_t *key, size_t key_bytes, int mode);

/**
 * @brief 加密/解密单个块
 *
 * @param input_block 输入块，AES_block_BYTES的大小
 * @param output_block 输出块，AES_block_BYTES的大小
 */
void aes_hal_transform_block(const void *input_block, void *output_block);

#if SOC_AES_SUPPORT_DMA
/**
 * @brief 初始化AES操作模式
 *
 * @param mode 操作模式，如CTR或CBC
 */
void aes_hal_mode_init(esp_aes_mode_t mode);

/**
 * @brief 设置变换的初始化向量
 *
 * @note 不得将同一IV与同一钥匙重复使用
 *
 * @param iv 初始化向量，长度=IV_BYTES（16字节）
 */
void aes_hal_set_iv(const uint8_t *iv);

/**
 * @brief 读取初始化向量
 *
 * @param iv 从硬件读取的初始化矢量，长度=IV_BYTES（16字节）
 */
void aes_hal_read_iv(uint8_t *iv);

/**
 * @brief 忙等待AES操作完成
 *
 * @param output 指向内联描述符的指针
 */
void aes_hal_wait_done(void);

/**
 * @brief 启动已配置的AES DMA转换
 *
 * @param num_blocks 要转换的块数
 */
void aes_hal_transform_dma_start(size_t num_blocks);

/**
 * @brief 完成AES DMA转换，释放DMA
 *
 */
void aes_hal_transform_dma_finish(void);

/**
 * @brief 启用或禁用转换完成中断
 *
 * @param enable true表示启用，false表示禁用。
 */
#define aes_hal_interrupt_enable(enable) aes_ll_interrupt_enable(enable)

/**
 * @brief 清除中断
 *
 */
#define aes_hal_interrupt_clear() aes_ll_interrupt_clear()

#if SOC_AES_SUPPORT_GCM
/**
 * @brief 计算启动AES-GCM所需的哈希子密钥H0
 *
 * @param gcm_hash 哈希子密钥H0输出
 */
void aes_hal_gcm_calc_hash(uint8_t *gcm_hash);

/**
 * @brief 初始化AES-GCM的AES硬件
 *
 * @param aad_num_blocks 附加认证数据（AAD）块的数量
 * @param num_valid_bit 明文/密文中不完全块的有效位数
 */
void aes_hal_gcm_init(size_t aad_num_blocks, size_t num_valid_bit);

/**
 * @brief 启动AES-GCM转换
 *
 * @param num_blocks 要转换的块数
 */
void aes_hal_transform_dma_gcm_start(size_t num_blocks);

/**
 * @brief 设置J0值，有关更多信息，请参阅TRM中的GCM分章
 *
 * @note 仅影响AES-GCM
 *
 * @param j0 J0值
 */
#define aes_hal_gcm_set_j0(j0)  aes_ll_gcm_set_j0(j0)

/**
 * @brief AES-GCM转换后读取标签
 *
 * @param tag 指向结果存储位置的指针
 * @param tag_length 要读入标记的字节数
 */
void aes_hal_gcm_read_tag(uint8_t *tag, size_t tag_len);

#endif //SOC_AES_SUPPORT_GCM

#endif //SOC_AES_SUPPORT_DMA


#ifdef __cplusplus
}
#endif

