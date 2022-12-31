// 版权所有2019-2020 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#pragma once

#include "hal/sha_types.h"

/** @brief 使用DMA的硬件SHA引擎的低级支持功能
 *
 * @note 如果您正在寻找要使用的SHA API，请尝试使用mbedtls组件mbedtls/shaXX.h。该API支持硬件加速。
 *
 * 此标头中的API提供了一些构建块，用于实现完整的SHA API，如mbedtls中的API，以及基本的SHA函数esp_SHA（）。
 *
 * 硬件SHA引擎的一些技术细节：
 *
 * -加密DMA在SHA和AES引擎之间共享，它们不可能并行运行计算。
 *
 */

#ifdef __cplusplus
extern "C" {
#endif


/** @brief 使用硬件SHA引擎计算某些数据的SHA1或SHA2总和
 *
 * @note 对于更通用的SHA计算（其中不需要同时传递所有数据），请尝试mbedTLS mbedTLS/shaX。h API。
 *
 * @note 在调用此函数之前，无需锁定任何SHA硬件，线程安全由内部管理。
 *
 * @param sha_type 要使用的SHA算法。
 *
 * @param input 输入数据缓冲区。
 *
 * @param ilen 输入数据的长度（字节）。
 *
 * @param output 输出SHA摘要的缓冲区。对于sha_type SHA1，输出为20字节，对于sha_typeSHA2_256，输出为32字节，对于sha_typeSHA2_384，输出为48字节，对于sha_type SHA2_512，输出为64字节。
 */
void esp_sha(esp_sha_type sha_type, const unsigned char *input, size_t ilen, unsigned char *output);

/** @brief 使用DMA执行SHA块操作
 *
 * @note 这是SHA算法的一部分，而不是整个SHA算法。
 *
 * @note 在调用此函数之前，请调用esp_sha_aquire_hardware（）。
 *
 * @param sha_type 要使用的SHA算法。
 *
 * @param input 指向输入数据的指针。块大小由算法确定（SHA1/SHA2_256=64字节，SHA2_384/SHA2_512=128字节）
 *
 * @param ilen 输入数据的长度应该是块长度的倍数。
 *
 * @param buf 指向数据块的指针，这些数据块将在哈希运算之前被附加到data_block。当有两个数据源需要在单个SHA DMA操作中有效计算时，这很有用。
 *
 * @param buf_len buf数据的长度应该是块长度的倍数。不应长于单个块中的最大字节数（128字节）
 *
 * @param is_first_block 如果此参数为真，则将在计算块之前初始化SHA状态（使用给定SHA算法的初始状态）。如果为false，将使用SHA引擎的现有状态。
 *
 * @param t SHA512/t哈希函数的位数，输出截断为t位。用于计算初始哈希。t是除384之外的1和512之间的任何正整数。
 *
 * @return 如果成功，则为0
 */
int esp_sha_dma(esp_sha_type sha_type, const void *input, uint32_t ilen,
                const void *buf, uint32_t buf_len, bool is_first_block);

/**
 * @brief 读取SHA摘要的当前状态
 *
 * @note 这是SHA算法的一部分，而不是整个SHA算法。
 *
 * @note 在调用此函数之前，请调用esp_sha_aquire_hardware（）。
 *
 * 如果已经执行了SHA后缀填充块，则读取的值是SHA摘要。否则，读取的值是临时SHA状态。
 *
 * @param sha_type 正在使用SHA算法。
 * @param digest_state 指向保存SHA状态的内存缓冲区的指针。大小为20字节（SHA1）、32字节（SHA2_256）或64字节（SHA_2384、SHA2_512）。
 */
void esp_sha_read_digest_state(esp_sha_type sha_type, void *digest_state);

/**
 * @brief 设置SHA摘要的当前状态
 *
 * @note 在调用此函数之前，请调用esp_sha_aquire_hardware（）。
 *
 * 恢复时
 *
 * @param sha_type 正在使用SHA算法。
 * @param digest_state
 */
void esp_sha_write_digest_state(esp_sha_type sha_type, void *digest_state);


/**
 * @brief 启用SHA和加密DMA外围设备，并获取两者的锁。
 */
void esp_sha_acquire_hardware(void);

/**
 * @brief 禁用SHA和加密DMA外围设备并释放锁。
 */
void esp_sha_release_hardware(void);

/**
 * @brief 设置SHA512/t的初始哈希值。
 *
 * @note 根据TRM SHA加速器章节中描述的算法生成
 *
 * @note 必须锁定发动机，直到该值用于操作或读取。否则，您将面临另一个操作覆盖它的风险。
 *
 * @param t
 *
 * @return 如果成功，则为0
 */
int esp_sha_512_t_init_hash(uint16_t t);

#ifdef __cplusplus
}
#endif

