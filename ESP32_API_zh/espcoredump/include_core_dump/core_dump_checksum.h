// 版权所有2015-2020 Espressif Systems（上海）私人有限公司
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

/**
 * @file
 * @brief 核心转储校验和接口。
 *
 * 该文件包含核心转储组件计算要写入（或已写入）闪存的数据校验和所需的所有函数。目前，CRC32和SHA256都受支持，但此接口独立于实现。
 */

#ifndef CORE_DUMP_CHECKSUM_H_
#define CORE_DUMP_CHECKSUM_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 校验和的最大可能长度（无论实现方式如何）。如果一个新的实现需要更大的规模，则可以在将来对其进行修改。
 */
#define COREDUMP_CHECKSUM_MAX_LEN 32

/**
 * @brief 描述校验和上下文的类型。它是一种抽象类型，因为它是独立于实现的，它是在C源代码中定义的。
 */
typedef struct core_dump_checksum_ctx core_dump_checksum_ctx;

/**
 * @brief “esp_core_dump_checksum_finish（）”返回的类型。它将校验和描述为字节数组。也可以将其提供给“esp_core_dump_print_checksum（）”。
 */
typedef uint8_t* core_dump_checksum_bytes;


/**
 * @brief 获取ELF核心转储版本。
 *
 * @note 目前，这在核心转储标头中用于识别用于特定转储的校验和，因为版本因校验和而异。
 *
 * @return 使用的核心转储的版本。
 */
uint32_t esp_core_dump_elf_version(void);

/**
 * @brief 初始化给定上下文的校验和计算。
 *
 * @param wr_data 要填充的核心转储校验和上下文。
 */
void esp_core_dump_checksum_init(core_dump_checksum_ctx** wr_data);

/**
 * @brief 通过在上下文中集成给定数据来更新校验和计算。
 *
 * @param wr_data 核心转储校验和上下文。
 * @param data    指向要在校验和计算中集成的数据的指针。这通常是要写入（或已写入）闪存的新数据。
 */
void esp_core_dump_checksum_update(core_dump_checksum_ctx* wr_data, void* data, size_t data_len);

/**
 * @brief 终止并返回为给定上下文计算的校验和。
 *
 * @param wr_data 核心转储校验和上下文。只有当chs_ptr也为NULL时，它才能为NULL。
 * @param chs_ptr 用于返回计算的校验和的指针。它可以是NULL，在这种情况下，它将被忽略，但将返回正确大小的校验和。
 *
 * @return 校验和的大小（字节）。
 */
uint32_t esp_core_dump_checksum_finish(core_dump_checksum_ctx* wr_data, core_dump_checksum_bytes* chs_ptr);

/**
 * @brief 返回校验和的大小。
 *
 * @note 这相当于“esp_core_dump_checksum_finish（NULL，NULL）”。
 *
 * @return 校验和的大小（以字节为单位）。
 */
uint32_t esp_core_dump_checksum_size(void);

/**
 * @brief 打印一条消息，后跟作为参数给出的校验和。
 *
 * @note 校验和将以十六进制格式打印，后跟\r\n。
 *
 * @param msg      要在校验和之前打印的消息。可以为NULL。
 * @param checksum 要打印的校验和。不能为NULL。
 */
void esp_core_dump_print_checksum(const char* msg, core_dump_checksum_bytes checksum);

#ifdef __cplusplus
}
#endif

#endif

