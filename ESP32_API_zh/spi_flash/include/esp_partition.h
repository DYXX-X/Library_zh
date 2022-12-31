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

#ifndef __ESP_PARTITION_H__
#define __ESP_PARTITION_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "esp_err.h"
#include "esp_flash.h"
#include "esp_spi_flash.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file esp_partition.h
 * @brief 分区API
 */


/**
 * @brief 分区类型
 *
 * @note 整数值为0x00-0x3F的分区类型保留给ESP-IDF定义的分区类型。任何其他整数值0x40-0xFE都可以由各个应用程序使用，不受限制。
 *
 * @internal 保持此枚举与PartitionDefinition类gen_esp32part同步。py@内部
 *
 */
typedef enum {
    ESP_PARTITION_TYPE_APP = 0x00,       //!< 应用程序分区类型
    ESP_PARTITION_TYPE_DATA = 0x01,      //!< 数据分区类型

    ESP_PARTITION_TYPE_ANY = 0xff,       //!< 用于搜索任何类型的分区
} esp_partition_type_t;

/**
 * @brief 分区子类型
 *
 * @note 这些ESP IDF定义的分区子类型适用于ESP_partition_type_APP和ESP_PARTTION_type_DATA类型的分区。
 *
 * 应用程序定义的分区类型（0x40-0xFE）可以设置任何数字子类型值。
 *
 * @internal 保持此枚举与PartitionDefinition类gen_esp32part同步。py@内部
 */
typedef enum {
    ESP_PARTITION_SUBTYPE_APP_FACTORY = 0x00,                                 //!< 工厂应用程序分区
    ESP_PARTITION_SUBTYPE_APP_OTA_MIN = 0x10,                                 //!< OTA分区子类型的基础
    ESP_PARTITION_SUBTYPE_APP_OTA_0 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 0,  //!< OTA分区0
    ESP_PARTITION_SUBTYPE_APP_OTA_1 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 1,  //!< OTA分区1
    ESP_PARTITION_SUBTYPE_APP_OTA_2 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 2,  //!< OTA分区2
    ESP_PARTITION_SUBTYPE_APP_OTA_3 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 3,  //!< OTA分区3
    ESP_PARTITION_SUBTYPE_APP_OTA_4 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 4,  //!< OTA分区4
    ESP_PARTITION_SUBTYPE_APP_OTA_5 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 5,  //!< OTA分区5
    ESP_PARTITION_SUBTYPE_APP_OTA_6 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 6,  //!< OTA分区6
    ESP_PARTITION_SUBTYPE_APP_OTA_7 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 7,  //!< OTA分区7
    ESP_PARTITION_SUBTYPE_APP_OTA_8 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 8,  //!< OTA分区8
    ESP_PARTITION_SUBTYPE_APP_OTA_9 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 9,  //!< OTA分区9
    ESP_PARTITION_SUBTYPE_APP_OTA_10 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 10,//!< OTA分区10
    ESP_PARTITION_SUBTYPE_APP_OTA_11 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 11,//!< OTA分区11
    ESP_PARTITION_SUBTYPE_APP_OTA_12 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 12,//!< OTA分区12
    ESP_PARTITION_SUBTYPE_APP_OTA_13 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 13,//!< OTA分区13
    ESP_PARTITION_SUBTYPE_APP_OTA_14 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 14,//!< OTA分区14
    ESP_PARTITION_SUBTYPE_APP_OTA_15 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 15,//!< OTA分区15
    ESP_PARTITION_SUBTYPE_APP_OTA_MAX = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 16,//!< OTA分区的最大子类型
    ESP_PARTITION_SUBTYPE_APP_TEST = 0x20,                                    //!< 测试应用程序分区

    ESP_PARTITION_SUBTYPE_DATA_OTA = 0x00,                                    //!< OTA选择分区
    ESP_PARTITION_SUBTYPE_DATA_PHY = 0x01,                                    //!< PHY初始化数据分区
    ESP_PARTITION_SUBTYPE_DATA_NVS = 0x02,                                    //!< NVS分区
    ESP_PARTITION_SUBTYPE_DATA_COREDUMP = 0x03,                               //!< COREDUMP分区
    ESP_PARTITION_SUBTYPE_DATA_NVS_KEYS = 0x04,                               //!< NVS密钥分区
    ESP_PARTITION_SUBTYPE_DATA_EFUSE_EM = 0x05,                               //!< 模拟eFuse位的分区
    ESP_PARTITION_SUBTYPE_DATA_UNDEFINED = 0x06,                              //!< 未定义（或未指定）的数据分区

    ESP_PARTITION_SUBTYPE_DATA_ESPHTTPD = 0x80,                               //!< ESPHTTPD分区
    ESP_PARTITION_SUBTYPE_DATA_FAT = 0x81,                                    //!< FAT分区
    ESP_PARTITION_SUBTYPE_DATA_SPIFFS = 0x82,                                 //!< SPIFFS分区

    ESP_PARTITION_SUBTYPE_ANY = 0xff,                                         //!< 用于搜索具有任何子类型的分区
} esp_partition_subtype_t;

/**
 * @brief 方便宏获取第i个OTA分区的esp_partition_subtype_t值
 */
#define ESP_PARTITION_SUBTYPE_OTA(i) ((esp_partition_subtype_t)(ESP_PARTITION_SUBTYPE_APP_OTA_MIN + ((i) & 0xf)))

/**
 * @brief 不透明分区迭代器类型
 */
typedef struct esp_partition_iterator_opaque_* esp_partition_iterator_t;

/**
 * @brief 分区信息结构
 *
 * 这不是flash中的格式，而是esp_partition_info_t。
 *
 * 然而，这是此API使用的格式。
 */
typedef struct {
    esp_flash_t* flash_chip;            /*!< 分区所在的SPI闪存芯片*/
    esp_partition_type_t type;          /*!< 分区类型（app/data）*/
    esp_partition_subtype_t subtype;    /*!< 分区子类型*/
    uint32_t address;                   /*!< 闪存中分区的起始地址*/
    uint32_t size;                      /*!< 分区大小，以字节为单位*/
    char label[17];                     /*!< 分区标签，以零结尾的ASCII字符串*/
    bool encrypted;                     /*!< 如果分区已加密，则标志设置为true*/
} esp_partition_t;

/**
 * @brief 基于一个或多个参数查找分区
 *
 * @param type 分区类型，esp_Partition_type_t值之一或8位无符号整数。要查找所有分区，无论其类型如何，请使用ESP_PARTITION_type_ANY，并将子类型参数设置为ESP_PARTATION_subtype_ANY。
 * @param subtype 分区子类型，esp_Partition_subtype_t值之一或8位无符号整数。要查找给定类型的所有分区，请使用ESP_PARTITION_SUBTYPE_ANY。
 * @param label （可选）分区标签。如果查找具有特定名称的分区，请设置此值。否则传递NULL。
 *
 * @return 迭代器，可用于枚举找到的所有分区，如果没有找到分区，则返回NULL。当不再使用时，必须使用esp_partition_interator_release释放通过该函数获得的迭代器。
 */
esp_partition_iterator_t esp_partition_find(esp_partition_type_t type, esp_partition_subtype_t subtype, const char* label);

/**
 * @brief 根据一个或多个参数查找第一个分区
 *
 * @param type 分区类型，esp_Partition_type_t值之一或8位无符号整数。要查找所有分区，无论其类型如何，请使用ESP_PARTITION_type_ANY，并将子类型参数设置为ESP_PARTATION_subtype_ANY。
 * @param subtype 分区子类型，esp_Partition_subtype_t值之一或8位无符号整数要查找给定类型的所有分区，请使用esp_Partition_subtype_ANY。
 * @param label （可选）分区标签。如果查找具有特定名称的分区，请设置此值。否则传递NULL。
 *
 * @return 指向esp_partition_t结构的指针，如果找不到分区，则返回NULL。此指针在应用程序的生存期内有效。
 */
const esp_partition_t* esp_partition_find_first(esp_partition_type_t type, esp_partition_subtype_t subtype, const char* label);

/**
 * @brief 获取给定分区的esp_partition_t结构
 *
 * @param iterator  使用esp_partition_find获得的迭代器。必须为非NULL。
 *
 * @return 指向esp_partition_t结构的指针。此指针在应用程序的生存期内有效。
 */
const esp_partition_t* esp_partition_get(esp_partition_iterator_t iterator);

/**
 * @brief 将分区迭代器移动到找到的下一个分区
 *
 * 在此调用之后，迭代器的任何副本都将无效。
 *
 * @param iterator 使用esp_partition_find获得的迭代器。必须为非NULL。
 *
 * @return 如果找不到分区，则为NULL，否则为有效的esp_partition_initerator_t。
 */
esp_partition_iterator_t esp_partition_next(esp_partition_iterator_t iterator);

/**
 * @brief 释放分区迭代器
 *
 * @param iterator 使用esp_partition_find获得的迭代器。迭代器允许为NULL，因此在调用此函数之前不必检查其值。
 *
 */
void esp_partition_iterator_release(esp_partition_iterator_t iterator);

/**
 * @brief 验证分区数据
 *
 * 给定指向分区数据的指针，验证分区表中是否存在此分区（所有字段都匹配）
 *
 * 该函数还可用于获取RAM缓冲区中的分区数据，并将其转换为指向闪存中存储的永久分区数据的指针。
 *
 * 从该函数返回的指针可以直接与从esp_partition_get（）返回的任何指针的地址进行比较，作为相等性的测试。
 *
 * @param partition 指向要验证的分区数据的指针。必须为非NULL。此结构的所有字段必须与flash中的分区表条目匹配，此函数才能返回成功匹配。
 *
 * @return
 * -如果找不到分区，则返回NULL。
 * -如果找到，则返回一个指向flash中esp_partition_t结构的指针。此指针在应用程序的生存期内始终有效。
 */
const esp_partition_t *esp_partition_verify(const esp_partition_t *partition);

/**
 * @brief 从分区读取数据
 *
 * 标记有加密标志的分区将通过缓存映射自动读取和解密。
 *
 * @param partition 指向使用esp_partition_find_first或esp_partition _get获得的分区结构的指针。必须为非NULL。
 * @param dst 指向应存储数据的缓冲区的指针。指针必须为非NULL，缓冲区长度必须至少为“size”字节。
 * @param src_offset 要读取的数据的地址，相对于分区的开头。
 * @param size 要读取的数据大小（字节）。
 *
 * @return ESP_OK，如果数据读取成功；如果src_offset超过分区大小，则返回ESP_ERR_INVALID_ARG；ESP_ERR_INVALID_SIZE，如果读取将超出分区的边界；或来自低级闪存驱动器的错误代码之一。
 */
esp_err_t esp_partition_read(const esp_partition_t* partition,
                             size_t src_offset, void* dst, size_t size);

/**
 * @brief 将数据写入分区
 *
 * 在将数据写入闪存之前，需要擦除闪存的相应区域。这可以使用esp_partition_ease_range函数完成。
 *
 * 标有加密标志的分区将通过spi_flash_write_encrypted（）函数自动写入。如果写入加密分区，所有写入偏移量和长度必须是16字节的倍数。有关详细信息，请参见spi_flash_write_encrypted（）函数。未加密分区没有此限制。
 *
 * @param partition 指向使用esp_partition_find_first或esp_partition _get获得的分区结构的指针。必须为非NULL。
 * @param dst_offset 应写入数据的地址，相对于分区的开头。
 * @param src 指向源缓冲区的指针。指针必须为非NULL，缓冲区长度必须至少为“size”字节。
 * @param size 要写入的数据大小（字节）。
 *
 * @note 在写入闪存之前，请确保已通过esp_partition_ease_range调用将其擦除。
 *
 * @return ESP_OK，如果数据写入成功；如果dst_offset超过分区大小，则返回ESP_ERR_INVALID_ARG；ESP_ERR_INVALID_SIZE，如果写入将超出分区边界；或来自低级闪存驱动器的错误代码之一。
 */
esp_err_t esp_partition_write(const esp_partition_t* partition,
                              size_t dst_offset, const void* src, size_t size);

/**
 * @brief 从分区读取数据，无需任何转换/解密。
 *
 * @note 此函数与上面的\c esp_partition_read（）基本相同。它只是从不解密数据，而是按原样返回数据。
 *
 * @param partition 指向使用esp_partition_find_first或esp_partition _get获得的分区结构的指针。必须为非NULL。
 * @param dst 指向应存储数据的缓冲区的指针。指针必须为非NULL，缓冲区长度必须至少为“size”字节。
 * @param src_offset 要读取的数据的地址，相对于分区的开头。
 * @param size 要读取的数据大小（字节）。
 *
 * @return ESP_OK，如果数据读取成功；如果src_offset超过分区大小，则返回ESP_ERR_INVALID_ARG；ESP_ERR_INVALID_SIZE，如果读取将超出分区边界；或来自低级闪存驱动器的错误代码之一。
 */
esp_err_t esp_partition_read_raw(const esp_partition_t* partition,
                                 size_t src_offset, void* dst, size_t size);

/**
 * @brief 将数据写入分区而不进行任何转换/加密。
 *
 * @note 此函数与上面的\c esp_partition_write（）基本相同。它只是从不加密数据，而是按原样写入数据。
 *
 * 在将数据写入闪存之前，需要擦除闪存的相应区域。这可以使用esp_partition_ease_range函数完成。
 *
 * @param partition 指向使用esp_partition_find_first或esp_partition _get获得的分区结构的指针。必须为非NULL。
 * @param dst_offset 应写入数据的地址，相对于分区的开头。
 * @param src 指向源缓冲区的指针。指针必须为非NULL，缓冲区长度必须至少为“size”字节。
 * @param size 要写入的数据大小（字节）。
 *
 * @note 在写入闪存之前，请确保已使用esp_partition_ease_range调用将其擦除。
 *
 * @return ESP_OK，如果数据写入成功；如果dst_offset超过分区大小，则返回ESP_ERR_INVALID_ARG；ESP_ERR_INVALID_SIZE，如果写入将超出分区边界；或来自低级闪存驱动器的错误代码之一。
 */
esp_err_t esp_partition_write_raw(const esp_partition_t* partition,
                                  size_t dst_offset, const void* src, size_t size);

/**
 * @brief 擦除部分分区
 *
 * @param partition 指向使用esp_partition_find_first或esp_partition _get获得的分区结构的指针。必须为非NULL。
 * @param offset 从应该开始擦除操作的分区开始的偏移量。必须对齐到4 KB。
 * @param size 应擦除的范围大小（以字节为单位）。必须可被4 KB整除。
 *
 * @return ESP_OK，如果成功擦除范围；如果迭代器或dst为空，则返回ESP_ERR_INVALID_ARG；如果擦除将超出分区边界，则返回ESP_ERR_INVALID_SIZE；或来自低级闪存驱动器的错误代码之一。
 */
esp_err_t esp_partition_erase_range(const esp_partition_t* partition,
                                    size_t offset, size_t size);

/**
 * @brief 配置MMU以将分区映射到数据存储器
 *
 * 与spi_flash_map函数（需要64kB对齐的基地址）不同，该函数没有强制要求。如果偏移导致闪存地址未与64kB边界对齐，则地址将舍入到64kB下边界，以便映射区域包括请求的范围。通过out_ptr参数返回的指针将被调整为指向请求的偏移量（不一定指向mmap ed区域的开头）。
 *
 * 要释放映射内存，请将通过out_handle参数返回的句柄传递给spi_flash_munmap函数。
 *
 * @param partition 指向使用esp_partition_find_first或esp_partition _get获得的分区结构的指针。必须为非NULL。
 * @param offset 从映射开始的分区开始的偏移量。
 * @param size 要映射的区域的大小。
 * @param memory  应映射区域的内存空间
 * @param out_ptr  输出，指向映射内存区域的指针
 * @param out_handle  输出，应用于spi_flash_munmap调用的句柄
 *
 * @return ESP_OK（如果成功）
 */
esp_err_t esp_partition_mmap(const esp_partition_t* partition, size_t offset, size_t size,
                             spi_flash_mmap_memory_t memory,
                             const void** out_ptr, spi_flash_mmap_handle_t* out_handle);

/**
 * @brief 获取所需分区的SHA-256摘要。
 *
 * 对于将SHA-256附加到应用程序图像的应用程序，结果是应用程序图像内容的附加SHA-256值。返回前验证哈希，如果应用程序内容无效，则函数返回ESP_ERR_IMAGE_invalid。对于图像中未附加SHA-256的应用程序，结果是应用程序图像中所有字节的SHA-256。对于其他分区类型，结果是整个分区的SHA-256。
 *
 * @param[in]  partition    指向包含应用程序或数据的分区的信息的指针。（必填字段：地址、大小和类型）。
 * @param[out] sha_256      返回给定分区的SHA-256摘要。
 *
 * @return
 *          -ESP_OK：如果操作成功。
 *          -ESP_ERR_INVALID_ARG：大小为0或sha_256为NULL。
 *          -ESP_ERR_NO_MEM:无法为sha256操作分配内存。
 *          -ESP_ERR_IMAGE_INVALID:应用程序分区不包含有效的应用程序映像。
 *          -ESP_FAIL:发生分配错误。
 */
esp_err_t esp_partition_get_sha256(const esp_partition_t *partition, uint8_t *sha_256);

/**
 * @brief 通过SHA-256摘要检查两个分区的标识。
 *
 * @param[in] partition_1 指向包含应用程序或数据的分区1的信息的指针。（必填字段：地址、大小和类型）。
 * @param[in] partition_2 指向包含应用程序或数据的分区2的信息的指针。（必填字段：地址、大小和类型）。
 *
 * @return
 *         -正确：在两个固件相等的情况下。
 *         -False：否则
 */
bool esp_partition_check_identity(const esp_partition_t *partition_1, const esp_partition_t *partition_2);

/**
 * @brief 在外部闪存芯片上注册分区
 *
 * 此API允许将外部闪存芯片的某些区域（由esp_flash_t结构标识）指定为分区。这允许将它们与通过esp_partitionAPI访问SPI闪存的组件一起使用。
 *
 * @param flash_chip  指向标识闪存芯片的结构的指针
 * @param offset  分区开始的地址（字节）
 * @param size  分区大小（字节）
 * @param label  分区名称
 * @param type  分区类型之一（ESP_partition_TYPE_*）或整数。请注意，应用程序无法从外部闪存芯片启动，因此不支持使用ESP_PARTITION_TYPE_APP。
 * @param subtype  分区子类型之一（ESP_partition_SUBTYPE_*）或整数。
 * @param[out] out_partition  如果输出为非NULL，则接收指向结果esp_partition_t结构的指针
 * @return
 *      -成功时ESP_OK
 *      -如果启用了CONFIG_CONFIG_SPI_FLASH_USE_LEGACY_IMPL，则为ESP_ERR_NOT_SUPPORTED
 *      -如果内存分配失败，则为ESP_ERR_NO_MEM
 *      -如果新分区与同一闪存芯片上的另一个分区重叠，则为ESP_ERR_INVALID_ARG
 *      -ESP_ERR_INVALID_SIZE（如果分区不适合闪存芯片大小）
 */
esp_err_t esp_partition_register_external(esp_flash_t* flash_chip, size_t offset, size_t size,
                                     const char* label, esp_partition_type_t type, esp_partition_subtype_t subtype,
                                     const esp_partition_t** out_partition);

/**
 * @brief 取消注册以前使用esp_partition_register_external注册的分区
 * @param partition  指向从esp_partition_register_external获得的分区结构的指针，
 * @return
 *      -成功时ESP_OK
 *      -如果找不到分区指针，则返回ESP_ERR_NOT_FOUND
 *      -如果分区来自分区表，则为ESP_ERR_INVALID_ARG
 *      -如果分区未使用ESP_partition_register_external函数注册，则返回ESP_ERR_INVALID_ARG。
 */
esp_err_t esp_partition_deregister_external(const esp_partition_t* partition);

#ifdef __cplusplus
}
#endif


#endif /* __ESP_PARTITION_H__ */

