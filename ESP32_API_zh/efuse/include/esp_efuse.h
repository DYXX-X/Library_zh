/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "esp_err.h"
#include "esp_log.h"
#include "soc/soc_caps.h"
#include "sdkconfig.h"
#include_next "esp_efuse.h"

#if CONFIG_IDF_TARGET_ESP32
#include "esp32/rom/secure_boot.h"
#elif CONFIG_IDF_TARGET_ESP32S2
#include "esp32s2/rom/secure_boot.h"
#elif CONFIG_IDF_TARGET_ESP32C3
#include "esp32c3/rom/secure_boot.h"
#elif CONFIG_IDF_TARGET_ESP32S3
#include "esp32s3/rom/secure_boot.h"
#elif CONFIG_IDF_TARGET_ESP32H2
#include "esp32h2/rom/secure_boot.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define ESP_ERR_EFUSE                              0x1600                     /*!< efuse api的基本错误代码。*/
#define ESP_OK_EFUSE_CNT                          (ESP_ERR_EFUSE + 0x01)      /*!< OK，设置所需位数。*/
#define ESP_ERR_EFUSE_CNT_IS_FULL                 (ESP_ERR_EFUSE + 0x02)      /*!< 错误字段已满。*/
#define ESP_ERR_EFUSE_REPEATED_PROG               (ESP_ERR_EFUSE + 0x03)      /*!< 严禁对编程位进行错误重复编程。*/
#define ESP_ERR_CODING                            (ESP_ERR_EFUSE + 0x04)      /*!< 编码操作时出错。*/
#define ESP_ERR_NOT_ENOUGH_UNUSED_KEY_BLOCKS      (ESP_ERR_EFUSE + 0x05)      /*!< 错误：没有足够的未使用密钥块可用*/
#define ESP_ERR_DAMAGED_READING                   (ESP_ERR_EFUSE + 0x06)      /*!< 错误在读取操作期间进行刻录或重置会导致读取数据损坏。此错误是efuse组件的内部错误，任何公共API都不会返回。*/

/**
 * @brief eFuse字段的类型定义
 */
typedef struct {
    esp_efuse_block_t   efuse_block: 8; /**<电子保险丝堵塞*/
    uint8_t             bit_start;      /**<起始位[0..255]*/
    uint16_t            bit_count;      /**<位字段长度[1..-]*/
} esp_efuse_desc_t;

/**
 * @brief ROM日志方案的类型定义
 */
typedef enum {
    ESP_EFUSE_ROM_LOG_ALWAYS_ON,    /**<始终启用ROM日志记录*/
    ESP_EFUSE_ROM_LOG_ON_GPIO_LOW,  /**<ROM日志记录在启动期间特定GPIO水平低时启用*/
    ESP_EFUSE_ROM_LOG_ON_GPIO_HIGH, /**<ROM日志记录在启动期间特定GPIO水平高时启用*/
    ESP_EFUSE_ROM_LOG_ALWAYS_OFF    /**<永久禁用ROM日志记录*/
} esp_efuse_rom_log_scheme_t;

/**
 * @brief   从EFUSE字段读取位并将其写入数组。
 *
 * 读取的位数将限制在“字段”结构或“dst_size_bits”所需大小中的位数描述中的最小值。使用“esp_efuse_get_field_size（）”函数确定字段的长度。
 *
 * @note 请注意，在批处理模式下读取不会显示未提交的更改。
 *
 * @param[in]  field          指向描述efuse字段的结构的指针。
 * @param[out] dst            指向将包含读取结果的数组的指针。
 * @param[in]  dst_size_bits  需要读取的位数。如果请求的位数大于字段，则该位数将被限制为字段大小。
 *
 * @return
 *    -ESP_OK:操作已成功完成。
 *    -ESP_ERR_INVALID_ARG：传递的参数中存在错误。
 */
esp_err_t esp_efuse_read_field_blob(const esp_efuse_desc_t* field[], void* dst, size_t dst_size_bits);


/**
 * @brief 将单个位eFuse字段读取为布尔值。
 *
 * @note 该值必须存在，并且必须是单位宽。如果提供的参数中可能存在错误，请调用esp_efuse_read_field_lob（）并检查返回的值。
 *
 * @note 如果断言已启用且参数无效，则执行将中止
 * @note 请注意，在批处理模式下读取不会显示未提交的更改。
 *
 * @param[in]  field          指向描述efuse字段的结构的指针。
 * @return
 *    -true：字段参数有效，位已设置。
 *    -false：未设置位，或者参数无效，断言被禁用。
 *
 */
bool esp_efuse_read_field_bit(const esp_efuse_desc_t *field[]);

/**
 * @brief   从EFUSE字段读取位并返回编程为“1”的位数。
 *
 * 如果未按顺序设置位，则仍将对其进行计数。
 * @note 请注意，在批处理模式下读取不会显示未提交的更改。
 *
 * @param[in]  field          指向描述efuse字段的结构的指针。
 * @param[out] out_cnt        包含编程为“1”位的指针。
 *
 * @return
 *    -ESP_OK:操作已成功完成。
 *    -ESP_ERR_INVALID_ARG：传递的参数中存在错误。
 */
esp_err_t esp_efuse_read_field_cnt(const esp_efuse_desc_t* field[], size_t* out_cnt);

/**
 * @brief   将数组写入EFUSE字段。
 *
 * 写入位的数量将限制为“字段”结构中的位描述或“src_size_bits”所需大小中的最小值。使用“esp_efuse_get_field_size（）”函数确定字段的长度。功能完成后，将清除写入寄存器。
 * @param[in]  field          指向描述efuse字段的结构的指针。
 * @param[in]  src            指向包含要写入的数据的数组的指针。
 * @param[in]  src_size_bits  写入所需的位数。
 *
 * @return
 *    -ESP_OK:操作已成功完成。
 *    -ESP_ERR_INVALID_ARG：传递的参数中存在错误。
 *    -ESP_ERR_EFUSE_REPEATED_PROG：严禁对编程位进行错误重复编程。
 *    -ESP_ERR_CODING：数据的错误范围与编码方案不匹配。
 */
esp_err_t esp_efuse_write_field_blob(const esp_efuse_desc_t* field[], const void* src, size_t src_size_bits);

/**
 * @brief   将所需的位数作为“1”写入EFUSE字段。
 *
 * 如果字段中没有可用位来将所需位数设置为“1”，则返回ESP_ERR_EFUSE_CNT_IS_FULL错误，该字段将不会被部分记录。功能完成后，将清除写入寄存器。
 * @param[in]  field          指向描述efuse字段的结构的指针。
 * @param[in]  cnt            编程为“1”位的所需数量。
 *
 * @return
 *    -ESP_OK:操作已成功完成。
 *    -ESP_ERR_INVALID_ARG：传递的参数中存在错误。
 *    -ESP_ERR_EFUSE_CNT_IS_FULL：未设置所有请求的CNT位。
 */
esp_err_t esp_efuse_write_field_cnt(const esp_efuse_desc_t* field[], size_t cnt);

/**
 * @brief 将单个位eFuse字段写入1
 *
 * 用于单个位的eFuse字段。如果尚未设置位，此函数将将其写入值1，如果已设置位，则不执行任何操作。
 *
 * 这相当于在cnt参数等于1的情况下调用esp_efuse_write_field_cnt（），但如果字段已设置为1，则返回esp_OK。
 *
 * @param[in] field 指向描述efuse字段的结构的指针。
 *
 * @return
 * -ESP_OK：操作已成功完成，或位已设置为值1。
 * -ESP_ERR_INVALID_ARG：传递的分段中出错，包括efuse字段不是1位宽。
 */
esp_err_t esp_efuse_write_field_bit(const esp_efuse_desc_t* field[]);

/**
 * @brief   为整个块设置写保护。
 *
 * 之后，就不可能写入这个块了。写入保护不适用于块0。
 * @param[in]  blk          eFuse的块号。（EFUSE_BLK1、EFUSE_BLK2和EFUSE_BLK3）
 *
 * @return
 *    -ESP_OK:操作已成功完成。
 *    -ESP_ERR_INVALID_ARG：传递的参数中存在错误。
 *    -ESP_ERR_EFUSE_CNT_IS_FULL：未设置所有请求的CNT位。
 *    -ESP_ERR_NOT_SUPPORTED：块不支持此命令。
 */
esp_err_t esp_efuse_set_write_protect(esp_efuse_block_t blk);

/**
 * @brief   为整个块设置读保护。
 *
 * 之后，就不可能从这个块中读取了。读取保护不适用于块0。
 * @param[in]  blk          eFuse的块号。（EFUSE_BLK1、EFUSE_BLK2和EFUSE_BLK3）
 *
 * @return
 *    -ESP_OK:操作已成功完成。
 *    -ESP_ERR_INVALID_ARG：传递的参数中存在错误。
 *    -ESP_ERR_EFUSE_CNT_IS_FULL：未设置所有请求的CNT位。
 *    -ESP_ERR_NOT_SUPPORTED：块不支持此命令。
 */
esp_err_t esp_efuse_set_read_protect(esp_efuse_block_t blk);

/**
 * @brief   返回字段使用的位数。
 *
 * @param[in]  field          指向描述efuse字段的结构的指针。
 *
 * @return 返回字段使用的位数。
 */
int esp_efuse_get_field_size(const esp_efuse_desc_t* field[]);

/**
 * @brief   返回efuse寄存器的值。
 *
 * 这是一个线程安全的实现。示例：EFUSE_BLK2_RDATA3_REG其中（blk=2，num_REG=3）
 * @note 请注意，在批处理模式下读取不会显示未提交的更改。
 *
 * @param[in]  blk     eFuse的块号。
 * @param[in]  num_reg 块中的寄存器号。
 *
 * @return 寄存器值
 */
uint32_t esp_efuse_read_reg(esp_efuse_block_t blk, unsigned int num_reg);

/**
 * @brief   将值写入efuse寄存器。
 *
 * 必要时应用编码方案。这是一个线程安全的实现。示例：EFUSE_BLK3_WDATA0_REG其中（blk=3，num_REG=0）
 * @param[in]  blk     eFuse的块号。
 * @param[in]  num_reg 块中的寄存器号。
 * @param[in]  val     要写入的值。
 *
 * @return
 *      -ESP_OK:操作已成功完成。
 *      -ESP_ERR_EFUSE_REPEATED_PROG：严禁对编程位进行错误重复编程。
 */
esp_err_t esp_efuse_write_reg(esp_efuse_block_t blk, unsigned int num_reg, uint32_t val);

/**
 * @brief   返回块的efuse编码方案。
 *
 * 注：编码方案仅适用于1、2和3个块。对于0块，编码方案始终为“NONE”。
 *
 * @param[in]  blk     eFuse的块号。
 * @return 返回块的efuse编码方案
 */
esp_efuse_coding_scheme_t esp_efuse_get_coding_scheme(esp_efuse_block_t blk);

/**
 * @brief   从偏移量和所需大小开始读取efuse块的键。
 *
 * @note 请注意，在批处理模式下读取不会显示未提交的更改。
 *
 * @param[in]  blk             eFuse的块号。
 * @param[in]  dst_key         指向将包含读取结果的数组的指针。
 * @param[in]  offset_in_bits  块中的起始位。
 * @param[in]  size_bits       需要读取的位数。
 *
 * @return
 *    -ESP_OK:操作已成功完成。
 *    -ESP_ERR_INVALID_ARG：传递的参数中存在错误。
 *    -ESP_ERR_CODING：数据的错误范围与编码方案不匹配。
 */
esp_err_t esp_efuse_read_block(esp_efuse_block_t blk, void* dst_key, size_t offset_in_bits, size_t size_bits);

/**
 * @brief   从偏移量和所需大小开始向efuse块写入密钥。
 *
 * @param[in]  blk             eFuse的块号。
 * @param[in]  src_key         指向数组的指针，该数组包含用于写入的键。
 * @param[in]  offset_in_bits  块中的起始位。
 * @param[in]  size_bits       写入所需的位数。
 *
 * @return
 *    -ESP_OK:操作已成功完成。
 *    -ESP_ERR_INVALID_ARG：传递的参数中存在错误。
 *    -ESP_ERR_CODING：数据的错误范围与编码方案不匹配。
 *    -ESP_ERR_EFUSE_REPEATED_PROG：编程位重复编程错误
 */
esp_err_t esp_efuse_write_block(esp_efuse_block_t blk, const void* src_key, size_t offset_in_bits, size_t size_bits);

/**
 * @brief   从efuse返回芯片版本
 *
 * @return 芯片版本
 */
uint8_t esp_efuse_get_chip_ver(void);

/**
 * @brief   从efuse返回芯片包
 *
 * @return 芯片封装
 */
uint32_t esp_efuse_get_pkg_ver(void);


/**
 *  @brief 重置efuse写入寄存器
 *
 * Efuse写入寄存器被写入零，以否定此处已暂存的任何更改。
 *
 * @note 此函数不是线程安全的，若调用代码从多个任务中更新efuse值，则这是调用者的责任。
 */
void esp_efuse_reset(void);

#ifdef CONFIG_IDF_TARGET_ESP32
/**
 *  @brief 通过efuse禁用BASIC ROM控制台
 *
 * 默认情况下，如果从闪存启动失败，ESP32将在ROM中启动BASIC控制台。
 *
 * 调用此函数（从引导加载程序或应用程序）永久禁用此芯片上的控制台。
 *
 */
void esp_efuse_disable_basic_rom_console(void);
#endif


/**
 *  @brief 通过eFuse禁用ROM下载模式
 *
 * 永久禁用ROM下载模式功能。一旦被禁用，如果SoC启动时带着设置为ROM下载模式的捆扎引脚，则会打印错误。
 *
 * @note 并非所有SoC都支持此选项。如果在硅版本低于3的ESP32上调用，将返回错误，因为这些版本不支持此选项。
 *
 * @note 如果ROM下载模式已禁用，则此函数不执行任何操作并返回成功。
 *
 * @return
 * -ESP_OK如果电子保险丝已成功熔断或已熔断。
 * -ESP_ERR_NOT_SUPPORTED（仅限ESP32）此SoC无法禁用UART下载模式
 * -ESP_ERR_INVALID_STATE（仅限ESP32）此eFuse受写保护，无法写入
 */
esp_err_t esp_efuse_disable_rom_download_mode(void);

/**
 * @brief 通过eFuse设置引导ROM日志方案
 *
 * @note 默认情况下，引导ROM将始终打印到控制台。每个芯片只能调用此API设置一次日志方案，一旦值从默认值更改，就不能再更改。
 *
 * @param log_scheme 支持的ROM日志方案
 * @return
 *      -ESP_OK如果电子保险丝已成功熔断或已熔断。
 *      -ESP_ERR_NOT_SUPPORTED（仅限ESP32）此SoC无法设置ROM日志方案
 *      -ESP_ERR_INVALID_STATE此eFuse受写保护或已被烧毁
 */
esp_err_t esp_efuse_set_rom_log_scheme(esp_efuse_rom_log_scheme_t log_scheme);

#if SOC_SUPPORTS_SECURE_DL_MODE
/**
 *  @brief 通过eFuse将ROM下载模式切换到安全下载模式
 *
 * 永久启用安全下载模式。此模式将ROM下载模式功能的使用限制为简单的闪存读取、写入和擦除操作，以及返回当前启用的安全功能摘要的命令。
 *
 * @note 如果已启用安全下载模式，则此函数不执行任何操作并返回成功。
 *
 * @note 禁用ROM下载模式也会禁用安全下载模式。
 *
 * @return
 * -ESP_OK如果电子保险丝已成功熔断或已熔断。
 * -ESP_ERR_INVALID_STATE ROM下载模式已通过eFuse禁用，因此安全下载模式不可用。
 */
esp_err_t esp_efuse_enable_rom_secure_download_mode(void);
#endif


/**
 *  @brief 从efuse字段返回secure_version。
 * @return efuse字段的安全版本
 */
uint32_t esp_efuse_read_secure_version(void);

/**
 *  @brief 从app和secure_version以及efuse字段检查secure_vversion。
 *
 * @param secure_version 应用程序的安全版本。
 * @return
 *          -True：如果应用程序的版本等于或大于efuse的secure_version。
 */
bool esp_efuse_check_secure_version(uint32_t secure_version);

/**
 *  @brief 按secure_version值写入efuse字段。
 *
 * 如果编码方案为None，则可以更新secure_version值。注意：不要在应用程序中使用此功能。此函数作为其他API的一部分调用。
 *
 * @param[in] secure_version 应用程序的安全版本。
 * @return
 *          -ESP_OK：成功。
 *          -ESP_FAIL:应用程序的安全版本不能设置为efuse字段。
 *          -ESP_ERR_NOT_SUPPORTED：3/4和重复编码方案不支持反回滚。
 */
esp_err_t esp_efuse_update_secure_version(uint32_t secure_version);

#if defined(BOOTLOADER_BUILD) && defined(CONFIG_EFUSE_VIRTUAL) && !defined(CONFIG_EFUSE_VIRTUAL_KEEP_IN_FLASH)
/**
 *  @brief 初始化eFuse API以将eFuse保存在RAM中。
 *
 * 此功能仅将所有eFuse复制到RAM。IDF eFuse API使用RAM而不是真正的eFuse执行所有运算符。（仅在引导加载程序中使用）。
 */
void esp_efuse_init_virtual_mode_in_ram(void);
#endif

#ifdef CONFIG_EFUSE_VIRTUAL_KEEP_IN_FLASH
/**
 *  @brief 初始化变量：偏移量和大小以模拟eFuse的工作。
 *
 * 注意：要模拟eFuse的工作，需要设置CONFIG_eFuse_VIRTUAL_KEEP_IN_FLASH选项并添加分区。csv文件一行“efuse_em，data，efuse，0x2000，”。
 *
 * @param[in] offset eFuse数据所在分区的起始地址。
 * @param[in] size 分区的大小。
 */
void esp_efuse_init_virtual_mode_in_flash(uint32_t offset, uint32_t size);
#endif

/**
 *  @brief 设置写入字段的批处理模式。
 *
 * 该模式允许您在需要同时刻录多个efuse时以批处理模式写入字段。要启用批处理模式，请调用begin（），然后照常执行必要的读写操作，并在结束时调用commit（）来实际刻录所有已写入的efuse。批处理模式可以嵌套使用。提交将由最后一个commit（）函数完成。begin（）函数的数量应等于commit（）函数数量。
 *
 * @note 请注意，在批处理模式下读取不会显示未提交的更改。
 *
 * 注意：如果第一个任务启用了批处理模式，此时第二个任务无法写入/读取efuse。第二个任务将等待第一个任务完成批处理操作。
 *
 * \code｛c｝//使用批处理写入模式的示例。
 *
 * //设置批写入模式esp_efuse_batch_write_begin（）；
 *
 * //照常使用任何写入函数esp_efuse_write_field_lob（esp_efuse_…）；esp_efuse_write_field_cnt（esp_efuse_…）；esp_efuse_set_write_protect（efuse_BLKx）；esp_efuse_write_reg（efuse_BLKx，…）；esp_efuse_write_block（efuse_BLKx，…）；esp_efuse_write（esp_efuse_1，3）；//ESP_EFUSE_1==1，这里我们写一个新值=3。更改将被commit（）函数烧录。esp_efuse_read_…（esp_efuse_1）；//此函数返回ESP_EFUSE_1==1，因为未提交的更改不可读，只有在提交后才可用。。。
 *
 * //esp_efuse_batch_write API可以递归调用。esp_efuse_batch_write_begin（）；esp_efuse_set_write_protect（efuse_BLKx）；esp_efuse_batch_write_commit（）；//这里将跳过烧录，它将在最后一个commit（）中完成。
 *
 * ...
 *
 * //将所有这些字段写入efuse寄存器esp_efuse_batch_Write_commit（）；esp_efuse_read_…（esp_efuse_1）；//此函数返回ESP_EFUSE_1==3。
 *
 * \结束代码
 *
 * @return
 *          -ESP_OK：成功。
 */
esp_err_t esp_efuse_batch_write_begin(void);

/**
 *  @brief 重置写入字段的批处理模式。
 *
 * 它将重置批量写入模式和任何写入更改。
 *
 * @return
 *          -ESP_OK：成功。
 *          -ESP_ERR_INVALID_STATE:未设置批处理模式。
 */
esp_err_t esp_efuse_batch_write_cancel(void);

/**
 *  @brief 写入批处理模式的所有准备数据。
 *
 * 必须调用以确保将更改写入efuse寄存器。在此之后，将重置批量写入模式。
 *
 * @return
 *          -ESP_OK：成功。
 *          -ESP_ERR_INVALID_STATE:未设置延迟写入模式。
 */
esp_err_t esp_efuse_batch_write_commit(void);

/**
 *  @brief 检查给定块是否为空。
 *
 * @return
 *          -True：块为空。
 *          -False：块不是空的或是错误的。
 */
bool esp_efuse_block_is_empty(esp_efuse_block_t block);

/**
 * @brief 返回密钥块的读取保护。
 *
 * @param[in] block EFUSE_BLK_KEY0..EFUE_BLK_key_MAX范围内的键块
 *
 * @return True：密钥块受读保护False：密钥块可读。
 */
bool esp_efuse_get_key_dis_read(esp_efuse_block_t block);

/**
 * @brief 设置密钥块的读取保护。
 *
 * @param[in] block EFUSE_BLK_KEY0..EFUE_BLK_key_MAX范围内的键块
 *
 * @return
 *    -ESP_OK：成功。
 *    -ESP_ERR_INVALID_ARG：传递的参数中存在错误。
 *    -ESP_ERR_EFUSE_REPEATED_PROG：严禁对编程位进行错误重复编程。
 *    -ESP_ERR_CODING：数据的错误范围与编码方案不匹配。
 */
esp_err_t esp_efuse_set_key_dis_read(esp_efuse_block_t block);

/**
 * @brief 返回密钥块的写保护。
 *
 * @param[in] block EFUSE_BLK_KEY0..EFUE_BLK_key_MAX范围内的键块
 *
 * @return True：密钥块受写保护False：密钥块可写。
 */
bool esp_efuse_get_key_dis_write(esp_efuse_block_t block);

/**
 * @brief 为密钥块设置写保护。
 *
 * @param[in] block EFUSE_BLK_KEY0..EFUE_BLK_key_MAX范围内的键块
 *
 * @return
 *    -ESP_OK：成功。
 *    -ESP_ERR_INVALID_ARG：传递的参数中存在错误。
 *    -ESP_ERR_EFUSE_REPEATED_PROG：严禁对编程位进行错误重复编程。
 *    -ESP_ERR_CODING：数据的错误范围与编码方案不匹配。
 */
esp_err_t esp_efuse_set_key_dis_write(esp_efuse_block_t block);

/**
 * @brief 如果密钥块未使用，则返回true，否则返回false。
 *
 * 未使用的密钥块全部为零内容，不受读写保护，用途为0（ESP_EFUSE_key_purpose_USER）
 *
 * @param block 要检查的键块。
 *
 * @return
 *         -如果密钥块未使用，则为True，
 *         -如果使用了键块或指定的块索引不是键块，则为False。
 */
bool esp_efuse_key_block_unused(esp_efuse_block_t block);

/**
 * @brief 找到具有特定目的集的关键块。
 *
 * @param[in] purpose 要搜索的目的。
 * @param[out] block EFUSE_BLK_KEY0..EFUE_BLK_KEY_MAX范围内的指针，如果找到该指针，将设置为键块。如果只需要测试密钥块存在，则可以为NULL。
 *
 * @return
 *         -True：如果找到，
 *         -False：如果未找到（块指针处的值不变）。
 */
bool esp_efuse_find_purpose(esp_efuse_purpose_t purpose, esp_efuse_block_t *block);

/**
 * @brief 返回efuse密钥块的密钥用途字段的写保护。
 *
 * @param[in] block EFUSE_BLK_KEY0..EFUE_BLK_key_MAX范围内的键块
 *
 * @note 对于ESP32：无关键用途，它始终返回True。
 *
 * @return 正确：关键目的是写保护。错误：关键目的是可写的。
 */
bool esp_efuse_get_keypurpose_dis_write(esp_efuse_block_t block);

/**
 * @brief 返回efuse键块的当前用途集。
 *
 * @param[in] block EFUSE_BLK_KEY0..EFUE_BLK_key_MAX范围内的键块
 *
 * @return
 *         -值：如果成功，则返回与给定密钥块相关的目的值。
 *         -ESP_EFUSE_KEY_PURPOSE_MAX：否则。
 */
esp_efuse_purpose_t esp_efuse_get_key_purpose(esp_efuse_block_t block);


#ifndef CONFIG_IDF_TARGET_ESP32
/**
 * @brief 返回指向efuse键块的键用途的指针。
 *
 * @param[in] block EFUSE_BLK_KEY0..EFUE_BLK_key_MAX范围内的键块
 *
 * 要获取此字段的值，请使用esp_efuse_read_field_lob（）或esp_efuse_get_key_purpose（）。
 *
 * @return 指针：如果成功，则返回指向相应efuse字段的指针，否则为NULL。
 */
const esp_efuse_desc_t **esp_efuse_get_purpose_field(esp_efuse_block_t block);

/**
 * @brief 返回指向键块的指针。
 *
 * @param[in] block EFUSE_BLK_KEY0..EFUE_BLK_key_MAX范围内的键块
 *
 * @return 指针：如果成功，则返回指向相应efuse字段的指针，否则为NULL。
 */
const esp_efuse_desc_t** esp_efuse_get_key(esp_efuse_block_t block);

/**
 * @brief 设置efuse密钥块的密钥用途。
 *
 * @param[in] block EFUSE_BLK_KEY0..EFUE_BLK_key_MAX范围内的键块
 * @param[in] purpose 关键目的。
 *
 * @return
 *    -ESP_OK：成功。
 *    -ESP_ERR_INVALID_ARG：传递的参数中存在错误。
 *    -ESP_ERR_EFUSE_REPEATED_PROG：严禁对编程位进行错误重复编程。
 *    -ESP_ERR_CODING：数据的错误范围与编码方案不匹配。
 */
esp_err_t esp_efuse_set_key_purpose(esp_efuse_block_t block, esp_efuse_purpose_t purpose);

/**
 * @brief 为efuse密钥块设置密钥用途字段的写保护。
 *
 * @param[in] block EFUSE_BLK_KEY0..EFUE_BLK_key_MAX范围内的键块
 *
 * @return
 *    -ESP_OK：成功。
 *    -ESP_ERR_INVALID_ARG：传递的参数中存在错误。
 *    -ESP_ERR_EFUSE_REPEATED_PROG：严禁对编程位进行错误重复编程。
 *    -ESP_ERR_CODING：数据的错误范围与编码方案不匹配。
 */
esp_err_t esp_efuse_set_keypurpose_dis_write(esp_efuse_block_t block);

/**
 * @brief 搜索未使用的密钥块并返回找到的第一个密钥块。
 *
 * 有关未使用密钥块的说明，请参见esp_efuse_key_block_unused。
 *
 * @return 第一个未使用的密钥块，如果没有找到未使用的键块，则为EFUSE_BLK_key_MAX。
 */
esp_efuse_block_t esp_efuse_find_unused_key_block(void);

/**
 * @brief 返回efuse_BLK_KEY0..EFUE_BLK_key_MAX范围内未使用的efuse密钥块的数量
 */
unsigned esp_efuse_count_unused_key_blocks(void);

/**
 * @brief 返回安全引导公钥摘要吊销位的状态。
 *
 * @param[in] num_digest 范围0..2中的摘要数
 *
 * @return
 *         -True：如果密钥摘要被撤销，
 *         -错误；如果密钥摘要未被撤销。
 */
bool esp_efuse_get_digest_revoke(unsigned num_digest);

/**
 * @brief 设置安全引导公钥摘要吊销位。
 *
 * @param[in] num_digest 范围0..2中的摘要数
 *
 * @return
 *    -ESP_OK：成功。
 *    -ESP_ERR_INVALID_ARG：传递的参数中存在错误。
 *    -ESP_ERR_EFUSE_REPEATED_PROG：严禁对编程位进行错误重复编程。
 *    -ESP_ERR_CODING：数据的错误范围与编码方案不匹配。
 */
esp_err_t esp_efuse_set_digest_revoke(unsigned num_digest);

/**
 * @brief 返回安全启动公钥摘要吊销位的写保护。
 *
 * @param[in] num_digest 范围0..2中的摘要数
 *
 * @return True：吊销位受写保护。False：吊销位是可写的。
 */
bool esp_efuse_get_write_protect_of_digest_revoke(unsigned num_digest);

/**
 * @brief 设置安全引导公钥摘要吊销位的写保护。
 *
 * @param[in] num_digest 范围0..2中的摘要数
 *
 * @return
 *    -ESP_OK：成功。
 *    -ESP_ERR_INVALID_ARG：传递的参数中存在错误。
 *    -ESP_ERR_EFUSE_REPEATED_PROG：严禁对编程位进行错误重复编程。
 *    -ESP_ERR_CODING：数据的错误范围与编码方案不匹配。
 */
esp_err_t esp_efuse_set_write_protect_of_digest_revoke(unsigned num_digest);

#endif // 不是CONFIG_IDF_TARGET_ESP32

/**
 * @brief 将密钥数据块编程为efuse块
 *
 * 密钥、保护位和目的的烧录在批处理模式下发生。
 *
 * @param[in] block 要读取目的的块。必须在EFUSE_BLK_KEY0到EFUSE_BLK_KEY_MAX的范围内。密钥块必须未使用（esp_efuse_Key_block_unused）。
 * @param[in] purpose 设置此密钥的目的。目的必须已设置。
 * @param[in] key 指向要写入的数据的指针。
 * @param[in] key_size_bytes 要写入的数据的字节长度。
 *
 * @return
 *    -ESP_OK：成功。
 *    -ESP_ERR_INVALID_ARG：传递的参数中存在错误。
 *    -ESP_ERR_INVALID_STATE:efuses状态错误，未找到未使用的块。
 *    -ESP_ERR_EFUSE_REPEATED_PROG：严禁对编程位进行错误重复编程。
 *    -ESP_ERR_CODING：数据的错误范围与编码方案不匹配。
 */
esp_err_t esp_efuse_write_key(esp_efuse_block_t block, esp_efuse_purpose_t purpose, const void *key, size_t key_size_bytes);

/**
 * @brief 未使用efuse块的程序键
 *
 * 密钥、保护位和目的的烧录以批处理模式进行。
 *
 * @param[in] purposes 目的数组（目的[number_of_keys]）。
 * @param[in] keys 键数组（uint8_t keys[number_of_keys][32]）。每个密钥的长度为32字节。
 * @param[in] number_of_keys 要写入的键数（最多6个键）。
 *
 * @return
 *    -ESP_OK：成功。
 *    -ESP_ERR_INVALID_ARG：传递的参数中存在错误。
 *    -ESP_ERR_INVALID_STATE:efuses状态错误，未找到未使用的块。
 *    -ESP_ERR_NOT_ENOUGH_UNUSED_KEY_BLOCKS：错误：没有足够的未使用密钥块可用
 *    -ESP_ERR_EFUSE_REPEATED_PROG：严禁对编程位进行错误重复编程。
 *    -ESP_ERR_CODING：数据的错误范围与编码方案不匹配。
 */
esp_err_t esp_efuse_write_keys(const esp_efuse_purpose_t purposes[], uint8_t keys[][32], unsigned number_of_keys);


#if CONFIG_ESP32_REV_MIN_3 || !CONFIG_IDF_TARGET_ESP32
/**
 * @brief 阅读efuse的关键摘要。任何已撤销/丢失的摘要都将标记为NULL
 *
 * @param[out] trusted_keys 范围0..2中的摘要数
 *
 * @return
 *    -ESP_OK：成功。
 *    -ESP_FAIL：如果trusted_keys为NULL或没有有效的摘要。
 */
esp_err_t esp_secure_boot_read_key_digests(ets_secure_boot_key_digests_t *trusted_keys);
#endif

#ifdef __cplusplus
}
#endif

