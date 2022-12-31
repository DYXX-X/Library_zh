// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
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
#include "esp_types.h"

/** @brief 硬件SHA引擎的低级支持功能
 *
 * @note 如果您正在寻找要使用的SHA API，请尝试使用mbedtls组件mbedtls/shaXX.h。该API支持硬件加速。
 *
 * 此标头中的API提供了一些构建块，用于实现完整的SHA API，如mbedtls中的API，以及基本的SHA函数esp_SHA（）。
 *
 * 硬件SHA引擎的一些技术细节：
 *
 * -SHA加速器引擎按照每个SHA算法类型一次计算一个摘要。它在内部初始化并维护摘要状态。可以读取正在进行的SHA摘要状态，但无法将SHA摘要恢复到引擎中。
 *
 * -内存块SHA_TEXT_BASE在所有SHA摘要引擎之间共享，因此在修改此内存块之前，所有引擎必须处于空闲状态。
 *
 */

#ifdef __cplusplus
extern "C" {
#endif


/** @brief 使用硬件SHA引擎计算某些数据的SHA1或SHA2总和
 *
 * @note 对于更通用的SHA计算（其中不需要同时传递所有数据），请尝试mbedTLS mbedTLS/shaX.h API。硬件加速的mbedTLS实现在散列大量数据时也更快。
 *
 * @note 在调用此函数之前，无需锁定任何SHA硬件，线程安全由内部管理。
 *
 * @note 如果TLS连接打开，则此函数可能会无限期地阻止等待SHA引擎变为可用。使用mbedTLS SHA API可避免此问题。
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

/* @brief 开始执行单个SHA块操作
 *
 * @note 这是SHA算法的一部分，而不是整个SHA算法。
 *
 * @note 在调用此函数之前，请调用esp_sha_try_lock_engine（）。不要事先调用esp_sha_lock_memory_block（），这是在函数内部完成的。
 *
 * @param sha_type 要使用的SHA算法。
 *
 * @param data_block 指向数据块的指针。块大小由算法确定（SHA1/SHA2_256=64字节，SHA2_384/SHA2_512=128字节）
 *
 * @param is_first_block 如果此参数为真，则将在计算块之前初始化SHA状态（使用给定SHA算法的初始状态）。如果为false，将使用SHA引擎的现有状态。
 *
 * @return 作为性能优化，此函数在SHA块操作完成之前返回。此函数和esp_sha_read_state（）都将自动等待之前的任何操作完成后再开始。如果以另一种方式直接使用SHA寄存器，请在调用此函数之后但在访问SHA寄存器之前调用esp_SHA_wait_idle（）。
 */
void esp_sha_block(esp_sha_type sha_type, const void *data_block, bool is_first_block);

/** @brief 读取引擎中加载的SHA摘要的当前状态。
 *
 * @note 这是SHA算法的一部分，而不是整个SHA算法。
 *
 * @note 在调用此函数之前，请调用esp_sha_try_lock_engine（）。不要事先调用esp_sha_lock_memory_block（），这是在函数内部完成的。
 *
 * 如果已经执行了SHA后缀填充块，则读取的值是SHA摘要（大端格式）。否则，读取的值是临时SHA状态。
 *
 * @note 如果sha_type为SHA2_384，则只读取48字节的状态。这对于最终的SHA2_384摘要来说已经足够了，但是如果您想要临时的SHA-384状态（继续消化），那么请改用SHA2_512。
 *
 * @param sha_type 正在使用SHA算法。
 *
 * @param state 指向保存SHA状态的内存缓冲区的指针。大小为20字节（SHA1）、32字节（SHA2_256）、48字节（SHA_2384）或64字节（SHA_2 512）。
 *
 */
void esp_sha_read_digest_state(esp_sha_type sha_type, void *digest_state);

/**
 * @brief 获得对特定SHA引擎的独占访问权限
 *
 * @param sha_type 要使用的SHA引擎的类型。
 *
 * 阻塞，直到发动机可用。注意：TLS连接打开时可能会无限期阻塞，建议使用esp_sha_try_lock_engine（）并故障切换到软件sha。
 */
void esp_sha_lock_engine(esp_sha_type sha_type);

/**
 * @brief 尝试以独占方式访问特定的SHA引擎
 *
 * @param sha_type 要使用的SHA引擎的类型。
 *
 * @return 如果SHA引擎被锁定为独占使用，则返回true。完成后调用esp_sha_unlock_sha_engine（）。如果SHA引擎已在使用，则返回false，调用方应为此摘要使用软件SHA算法。
 */
bool esp_sha_try_lock_engine(esp_sha_type sha_type);

/**
 * @brief 解锁以前使用esp_sha_lock_engine（）或esp_sha_try_lock_eengine（）锁定的引擎
 *
 * @param sha_type 要释放的发动机类型。
 */
void esp_sha_unlock_engine(esp_sha_type sha_type);

/**
 * @brief 获取对SHA_TEXT_BASE处的SHA共享内存块的独占访问
 *
 * 此内存块在所有SHA算法类型中共享。
 *
 * 调用方在调用此函数之前应该已经锁定了SHA引擎。
 *
 * 请注意，即使SHA引擎正在使用内存块，也可以获得对内存块的独占访问。调用方应该使用esp_sha_wait_idle（）来确保sha引擎没有从硬件中的内存块读取数据。
 *
 * @note 此函数进入关键部分。拿着这把锁时不要卡住。
 *
 * @note 在调用esp_sha_block（）或esp_sha_read_digest_state（）之前，不需要锁定内存块，这些函数在内部处理内存块锁定。
 *
 * 完成后调用esp_sha_unlock_memory_block（）。
 */
void esp_sha_lock_memory_block(void);

/**
 * @brief 释放对SHA_TEXT_BASE处的SHA寄存器内存块的独占访问
 *
 * 调用方在调用此函数之前应该已经锁定了SHA引擎。
 *
 * 此函数释放esp_sha_lock_memory_block（）输入的关键部分。
 *
 * 调用以下esp_sha_lock_memory_block（）。
 */
void esp_sha_unlock_memory_block(void);

/** @brief 等待SHA引擎完成任何当前操作
 *
 * @note 此函数不能确保对任何SHA引擎的独占访问。调用方应根据需要使用esp_sha_try_lock_engine（）和esp_sha_lock_memory_block（）。
 *
 * @note 在此头文件中声明的函数会自动等待SHA引擎完成，因此不需要使用此API。但是，如果直接访问SHA寄存器，则如果使用esp_SHA_block（）函数，则需要在访问SHA之前调用该函数。
 *
 * @note 此函数忙等待，因此浪费CPU资源。最好等到你需要的时候再打电话。
 *
 */
void esp_sha_wait_idle(void);

#ifdef __cplusplus
}
#endif

