/*
 * SPDX文件版权文本：2018-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once
#include "esp_flash_partitions.h"
#include "esp_image_format.h"
#include "esp_app_format.h"
// [重构todo]：我们不应该在公共API头中公开ROM头文件，在v5.0中删除它们
// 在IDF-1968中跟踪
#if CONFIG_IDF_TARGET_ESP32
#include "esp32/rom/rtc.h"
#elif CONFIG_IDF_TARGET_ESP32S2
#include "esp32s2/rom/rtc.h"
#elif CONFIG_IDF_TARGET_ESP32S3
#include "esp32s3/rom/rtc.h"
#elif CONFIG_IDF_TARGET_ESP32C3
#include "esp32c3/rom/rtc.h"
#elif CONFIG_IDF_TARGET_ESP32H2
#include "esp32h2/rom/rtc.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

///将GPIO保持在低状态的类型
typedef enum {
    GPIO_LONG_HOLD  = 1,    /*!< 长持GPIO*/
    GPIO_SHORT_HOLD = -1,   /*!< 短持GPIO*/
    GPIO_NOT_HOLD   = 0     /*!< 如果GPIO输入不低*/
} esp_comm_gpio_hold_t;

typedef enum {
    ESP_IMAGE_BOOTLOADER,
    ESP_IMAGE_APPLICATION
} esp_image_type;

/**
 * @brief 计算OTA数据选择的crc。
 *
 * @param[in] s OTA数据选择。
 * @return    返回crc值。
 */
uint32_t bootloader_common_ota_select_crc(const esp_ota_select_entry_t *s);

/**
 * @brief 验证OTA数据选择的有效性
 *
 * @param[in] s OTA数据选择。
 * @return    有效时返回true，否则返回false。
 */
bool bootloader_common_ota_select_valid(const esp_ota_select_entry_t *s);

/**
 * @brief 如果OTADATA未标记为可引导分区，则返回true。
 *
 * @param[in] s OTA数据选择。
 * @return    如果OTADATA无效，则返回true，否则返回false。
 */
bool bootloader_common_ota_select_invalid(const esp_ota_select_entry_t *s);

/**
 * @brief 检查GPIO输入是否长时间、短时间或根本没有保持在低电平。
 *
 * 此功能将指定的GPIO配置为启用内部上拉的输入。
 *
 * 如果GPIO输入在delay_sec周期内持续保持低电平，则为长时间保持。如果GPIO输入在较短时间内保持低电平，则为短保持。
 *
 * @param[in] num_pin GPIO输入的编号。
 * @param[in] delay_sec 输入必须持续降低至少如此长的时间。
 * @return esp_comm_gpio_hold_t检测到的低电平保持类型（如果有）。
 */
esp_comm_gpio_hold_t bootloader_common_check_long_hold_gpio(uint32_t num_pin, uint32_t delay_sec);

/**
 * @brief 检查GPIO输入是否在长时间、短时间或根本没有保持在低电平或高电平。
 *
 * 此功能将指定的GPIO配置为启用内部上拉的输入。
 *
 * 如果GPIO输入在delay_sec期间持续保持在“电平”，则为长时间保持。如果GPIO输入保持在“电平”的时间较短，则为短暂保持。
 *
 * @param[in] num_pin GPIO输入的编号。
 * @param[in] delay_sec 必须将输入驱动到“水平”至少持续这么长时间。
 * @param[in] level 保持时触发的输入引脚电平
 * @return esp_comm_gpio_hold_t检测到的保持类型（如果有）。
 */
esp_comm_gpio_hold_t bootloader_common_check_long_hold_gpio_level(uint32_t num_pin, uint32_t delay_sec, bool level);


/**
 * @brief 擦除传输列表中指定的分区数据。
 *
 * @param[in] list_erase 包含已清除分区列表的字符串。就像这个“女，菲”。字符串必须是空终端。
 * @param[in] ota_data_erase 如果为真，则OTA数据分区将被清除（如果分区表中有它）。
 * @return    成功时返回true，否则返回false。
 */
bool bootloader_common_erase_part_type_data(const char *list_erase, bool ota_data_erase);

/**
 * @brief 确定列表是否包含标签
 *
 * @param[in] list  由逗号或空格分隔的名称字符串。就像这个“nvs，phy，data”。字符串必须以空结尾。
 * @param[in] label 将在列表中搜索的子字符串。
 * @return    如果列表包含标签，则返回true，否则返回false。
 */
bool bootloader_common_label_search(const char *list, char *label);

/**
 * @brief 配置默认SPI引脚模式和驱动器强度
 *
 * @param drv GPIO驱动电平（由时钟频率确定）
 */
void bootloader_configure_spi_pins(int drv);

/**
 * @brief 获取闪存CS IO
 *
 * 可由eFuse值或默认值确定
 *
 * @return 闪存CS IO
 */
uint8_t bootloader_flash_get_cs_io(void);

/**
 * @brief 计算给定分区的sha-256或返回附加摘要。
 *
 * 此函数可用于返回应用程序、引导加载程序和数据分区的SHA-256摘要。对于将SHA-256附加到应用程序图像的应用程序，结果是应用程序图像内容的附加SHA-256值。返回前验证哈希，如果应用程序内容无效，则函数返回ESP_ERR_IMAGE_invalid。对于图像中未附加SHA-256的应用程序，结果是应用程序图像中所有字节的SHA-256。对于其他分区类型，结果是整个分区的SHA-256。
 *
 * @param[in]  address      分区的地址。
 * @param[in]  size         分区大小。
 * @param[in]  type         分区类型。对于应用程序，类型为0，否则类型为数据。
 * @param[out] out_sha_256  返回给定分区的SHA-256摘要。
 *
 * @return
 *          -ESP_OK：如果操作成功。
 *          -ESP_ERR_INVALID_ARG：大小为0或sha_256为NULL。
 *          -ESP_ERR_NO_MEM:无法为sha256操作分配内存。
 *          -ESP_ERR_IMAGE_INVALID:应用程序分区不包含有效的应用程序映像。
 *          -ESP_FAIL:发生分配错误。
 */
esp_err_t bootloader_common_get_sha256_of_partition(uint32_t address, uint32_t size, int type, uint8_t *out_sha_256);

/**
 * @brief 返回活动otadata的数量。
 *
 * @param[in] two_otadata 来自两个otadata结构的数组上的指针。
 *
 * @return 活动otadata的数量（0或1）。
 *        --1：如果没有活动的otadata。
 */
int bootloader_common_get_active_otadata(esp_ota_select_entry_t *two_otadata);

/**
 * @brief 返回活动otadata的数量。
 *
 * @param[in] two_otadata       来自两个otadata结构的数组上的指针。
 * @param[in] valid_two_otadata 来自两个布尔值的数组指针。True表示选择。
 * @param[in] max               True-将选择最大ota_seq数，否则选择最小值。
 *
 * @return 活动otadata的数量（0或1）。
 *        --1：如果没有活动的otadata。
 */
int bootloader_common_select_otadata(const esp_ota_select_entry_t *two_otadata, bool *valid_two_otadata, bool max);

/**
 * @brief 返回应用分区的esp_app_desc结构。此结构包括应用程序版本。
 *
 * 返回请求的应用分区的说明。
 * @param[in] partition      应用分区描述。
 * @param[out] app_desc      有关应用程序的信息结构。
 * @return
 *  -ESP_OK：成功。
 *  -ESP_ERR_INVALID_ARG:传递的参数无效。
 *  -ESP_ERR_NOT_FOUND:找不到app_desc结构。魔术词不正确。
 *  -ESP_FAIL:映射失败。
 */
esp_err_t bootloader_common_get_partition_description(const esp_partition_pos_t *partition, esp_app_desc_t *app_desc);

/**
 * @brief 获取芯片修订
 *
 * @return 芯片修订号
 */
uint8_t bootloader_common_get_chip_revision(void);

/**
 * @brief 获取芯片包
 *
 * @return 芯片封装编号
 */
uint32_t bootloader_common_get_chip_ver_pkg(void);

/**
 * @brief 查询重置原因
 *
 * @param cpu_no CPU编号
 * @return 重置原因枚举
 */
RESET_REASON bootloader_common_get_reset_reason(int cpu_no);

/**
 * @brief 检查映像（引导加载程序和应用程序）是否具有有效的芯片ID和版本
 *
 * @param[in] img_hdr: 图像标题
 * @param[in] type: 图像类型、引导加载程序或应用程序
 * @return
 *      -ESP_OK：图像和芯片匹配良好
 *      -ESP_FAIL：图像与芯片不匹配
 */
esp_err_t bootloader_common_check_chip_validity(const esp_image_header_t* img_hdr, esp_image_type type);

/**
 * @brief 配置VDDSDIO，当VDDSDIO调节器启用为1.8V模式时，调用此API将VDDSDI0升高至1.9V。
 */
void bootloader_common_vddsdio_configure(void);

#if defined( CONFIG_BOOTLOADER_SKIP_VALIDATE_IN_DEEP_SLEEP ) || defined( CONFIG_BOOTLOADER_CUSTOM_RESERVE_RTC )
/**
 * @brief 从rtc_retain_mem返回分区
 *
 * 用于获取在进入深度睡眠之前工作的应用程序分区。此分区存储在rtc_retain_mem中。注意：此功能操作RTC FAST内存，该内存仅适用于PRO_CPU。确保此功能仅用于PRO_CPU。
 *
 * @return partition：如果rtc_retain_mem有效。
 *        -NULL：如果无效。
 */
esp_partition_pos_t* bootloader_common_get_rtc_retain_mem_partition(void);

/**
 * @brief 更新rtc_retain_mem中的分区和reboot_counter。
 *
 * 此函数保存应用程序分区，以便从深度睡眠中快速启动。算法使用此分区来避免读取otadata，并且不验证图像。注意：此功能操作RTC FAST内存，该内存仅适用于PRO_CPU。确保此功能仅用于PRO_CPU。
 *
 * @param[in] partition      应用分区描述。在本例中，rtc_retain_mem可以为NULL。分区未更新。
 * @param[in] reboot_counter 如果为true，则更新reboot_counter。
 *
 */
void bootloader_common_update_rtc_retain_mem(esp_partition_pos_t* partition, bool reboot_counter);

/**
 * @brief 重置整个rtc_retain_mem。
 *
 * 注意：此功能操作RTC FAST内存，该内存仅适用于PRO_CPU。确保此功能仅用于PRO_CPU。
 */
void bootloader_common_reset_rtc_retain_mem(void);

/**
 * @brief 从rtc_retain_mem返回reboot_counter
 *
 * reboot_counter统计重新启动的次数。仅当电源关闭时重置。应用程序的第一次启动将从1开始。溢出是不可能的，它将在值UINT16_MAX处停止。注意：此功能操作RTC FAST内存，该内存仅适用于PRO_CPU。确保此功能仅用于PRO_CPU。
 *
 * @return 重新启动计数器：1..65535
 *         -0：如果rtc_retain_mem无效。
 */
uint16_t bootloader_common_get_rtc_retain_mem_reboot_counter(void);

/**
 * @brief 返回rtc_retain_mem
 *
 * 注意：此功能操作RTC FAST内存，该内存仅适用于PRO_CPU。确保此功能仅用于PRO_CPU。
 *
 * @return rtc保留内存
 */
rtc_retain_mem_t* bootloader_common_get_rtc_retain_mem(void);

#endif

#ifdef __cplusplus
}
#endif

