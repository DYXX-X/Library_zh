// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
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
 * 注意：hal不是公共api，不要在应用程序代码中使用。请参阅自述文件。soc/include/hal/readme.md中的md
 ******************************************************************************/

#pragma once

#include <stddef.h>
#include <stdbool.h>
#include "soc/soc_caps.h"
#include "soc/lldesc.h"
#include "hal/sha_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 散列单个消息块
 *
 * @param sha_type          要哈希的SHA算法
 * @param data_block        要散列的输入消息
 * @param block_word_len    输入消息的长度
 * @param first_block       这是消息中的第一个块还是继续？
 */
void sha_hal_hash_block(esp_sha_type sha_type, const void *data_block, size_t block_word_len, bool first_block);

/**
 * @brief 轮询并等待，直到SHA引擎空闲
 *
 */
void sha_hal_wait_idle(void);

/**
 * @brief 从SHA引擎读取当前消息摘要
 *
 * @param sha_type 使用的SHA算法
 * @param digest_state 要将消息摘要读取到的输出缓冲区
 */
void sha_hal_read_digest(esp_sha_type sha_type, void *digest_state);

#if SOC_SHA_SUPPORT_RESUME
/**
 * @brief 将消息摘要写入SHA引擎
 *
 * @param sha_type SHA算法类型
 * @param digest_state 要写入SHA引擎的消息摘要
 */
void sha_hal_write_digest(esp_sha_type sha_type, void *digest_state);
#endif

#if SOC_SHA_SUPPORT_DMA
/**
 * @brief 使用DMA对多个消息块进行哈希
 *
 * @param sha_type      要哈希的SHA算法
 * @param num_blocks    要哈希的块数
 * @param first_block   这是消息中的第一个块还是继续？
 */
void sha_hal_hash_dma(esp_sha_type sha_type, size_t num_blocks, bool first_block);
#endif

#if SOC_SHA_SUPPORT_SHA512_T
/**
 * @brief 计算并设置SHA512_t的初始数字
 *
 * @param t_string
 * @param t_len
 */
void sha_hal_sha512_init_hash(uint32_t t_string, uint8_t t_len);
#endif

#ifdef __cplusplus
}
#endif

