/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#include <stdbool.h>
#include <esp_err.h>
#include "esp_flash_partitions.h"
#include "esp_app_format.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ESP_ERR_IMAGE_BASE       0x2000
#define ESP_ERR_IMAGE_FLASH_FAIL (ESP_ERR_IMAGE_BASE + 1)
#define ESP_ERR_IMAGE_INVALID    (ESP_ERR_IMAGE_BASE + 2)

/* 支持app/bootloader映像解析可以作为app或bootloader代码的一部分进行编译。
*/

#define ESP_IMAGE_HASH_LEN 32 /* 所附SHA-256摘要的长度*/

/* 保存闪存图像元数据的结构*/
typedef struct {
  uint32_t start_addr;   /* 图像的起始地址*/
  esp_image_header_t image; /* 整个图像的标题*/
  esp_image_segment_header_t segments[ESP_IMAGE_MAX_SEGMENTS]; /* 每段标题数据*/
  uint32_t segment_data[ESP_IMAGE_MAX_SEGMENTS]; /* 每个段的数据偏移量*/
  uint32_t image_len; /* 闪存上的图像长度（字节）*/
  uint8_t image_digest[32]; /* 附加SHA-256摘要*/
} esp_image_metadata_t;

typedef enum {
    ESP_IMAGE_VERIFY,            /* 验证图像内容，不加载到内存，加载元数据。打印错误。*/
    ESP_IMAGE_VERIFY_SILENT,     /* 验证图像内容，不加载到内存，加载元数据。不要打印错误。*/
#ifdef BOOTLOADER_BUILD
    ESP_IMAGE_LOAD,              /* 验证图像内容，加载到内存，加载元数据。打印错误。*/
    ESP_IMAGE_LOAD_NO_VALIDATE,  /* 不验证图像内容，加载到内存，加载元数据。打印错误。*/
#endif
} esp_image_load_mode_t;

typedef struct {
    esp_partition_pos_t partition;  /*!< 之前工作的应用程序分区进入深度睡眠。*/
    uint16_t reboot_counter;        /*!< 重新启动计数器。仅在电源关闭时重置。*/
    uint16_t reserve;               /*!< 储备*/
#ifdef CONFIG_BOOTLOADER_CUSTOM_RESERVE_RTC
    uint8_t custom[CONFIG_BOOTLOADER_CUSTOM_RESERVE_RTC_SIZE]; /*!< 自定义建议保留*/
#endif
    uint32_t crc;                   /*!< 校验和crc32*/
} rtc_retain_mem_t;

#ifdef CONFIG_BOOTLOADER_CUSTOM_RESERVE_RTC
_Static_assert(CONFIG_BOOTLOADER_CUSTOM_RESERVE_RTC_SIZE % 4 == 0, "CONFIG_BOOTLOADER_CUSTOM_RESERVE_RTC_SIZE must be a multiple of 4 bytes");
#endif

#if defined(CONFIG_BOOTLOADER_SKIP_VALIDATE_IN_DEEP_SLEEP) || defined(CONFIG_BOOTLOADER_CUSTOM_RESERVE_RTC)
_Static_assert(CONFIG_BOOTLOADER_RESERVE_RTC_SIZE % 4 == 0, "CONFIG_BOOTLOADER_RESERVE_RTC_SIZE must be a multiple of 4 bytes");
#endif

#ifdef CONFIG_BOOTLOADER_CUSTOM_RESERVE_RTC
#define ESP_BOOTLOADER_RESERVE_RTC (CONFIG_BOOTLOADER_RESERVE_RTC_SIZE + CONFIG_BOOTLOADER_CUSTOM_RESERVE_RTC_SIZE)
#elif defined(CONFIG_BOOTLOADER_SKIP_VALIDATE_IN_DEEP_SLEEP)
#define ESP_BOOTLOADER_RESERVE_RTC (CONFIG_BOOTLOADER_RESERVE_RTC_SIZE)
#endif

#if defined(CONFIG_BOOTLOADER_SKIP_VALIDATE_IN_DEEP_SLEEP) || defined(CONFIG_BOOTLOADER_CUSTOM_RESERVE_RTC)
_Static_assert(sizeof(rtc_retain_mem_t) <= ESP_BOOTLOADER_RESERVE_RTC, "Reserved RTC area must exceed size of rtc_retain_mem_t");
#endif

/**
 * @brief 验证应用程序映像。
 *
 * 如果启用了加密，数据将被透明地解密。
 *
 * @param mode 操作模式（验证、静默验证或加载）。
 * @param part 从中加载应用程序的分区。
 * @param[inout] data 指向此函数填充的图像元数据结构的指针。'start_addr'成员应设置为（映像的起始地址）。其他字段都将由该函数初始化。
 *
 * 图像验证检查：
 * -神奇的字节。
 * -分区小于16MB。
 * -所有段和图像都适合分区。
 * -8位图像校验和有效。
 * -图像的SHA-256有效（如果图像附加了此项）。
 * -（签名）如果启用了签名验证。
 *
 * @return
 * -如果验证或加载成功，则ESP_OK
 * -如果发生SPI闪存错误，则ESP_ERR_IMAGE_FLASH_FAIL
 * -如果图像无效，则返回ESP_ERR_IMAGE_INVALID。
 * -如果分区或数据指针无效，则返回ESP_ERR_INVALID_ARG。
 */
esp_err_t esp_image_verify(esp_image_load_mode_t mode, const esp_partition_pos_t *part, esp_image_metadata_t *data);

/**
 * @brief 获取应用的元数据
 *
 * 如果启用了加密，数据将被透明地解密。
 *
 * @param part 从中加载应用程序的分区。
 * @param[out] metadata 指向此函数填充的图像元数据结构的指针。所有字段都将由该函数初始化。
 *
 * @return
 * -如果元数据填充成功，则ESP_OK
 */
esp_err_t esp_image_get_metadata(const esp_partition_pos_t *part, esp_image_metadata_t *metadata);

/**
 * @brief 验证并加载应用程序映像（仅在引导加载程序的空间中可用）。
 *
 * 如果启用了加密，数据将被透明地解密。
 *
 * @param part 从中加载应用程序的分区。
 * @param[inout] data 指向此函数填充的图像元数据结构的指针。'start_addr'成员应设置为（映像的起始地址）。其他字段都将由该函数初始化。
 *
 * 图像验证检查：
 * -神奇的字节。
 * -分区小于16MB。
 * -所有段和图像都适合分区。
 * -8位图像校验和有效。
 * -图像的SHA-256有效（如果图像附加了此项）。
 * -（签名）如果启用了签名验证。
 *
 * @return
 * -如果验证或加载成功，则ESP_OK
 * -如果发生SPI闪存错误，则ESP_ERR_IMAGE_FLASH_FAIL
 * -如果图像无效，则返回ESP_ERR_IMAGE_INVALID。
 * -如果分区或数据指针无效，则返回ESP_ERR_INVALID_ARG。
 */
esp_err_t bootloader_load_image(const esp_partition_pos_t *part, esp_image_metadata_t *data);

/**
 * @brief 加载应用程序映像而不进行验证（仅在引导加载程序的空间中可用）。
 *
 * 如果启用了加密，数据将被透明地解密。
 *
 * @param part 从中加载应用程序的分区。
 * @param[inout] data 指向此函数填充的图像元数据结构的指针。'start_addr'成员应设置为（映像的起始地址）。其他字段都将由该函数初始化。
 *
 * @return
 * -如果验证或加载成功，则ESP_OK
 * -如果发生SPI闪存错误，则ESP_ERR_IMAGE_FLASH_FAIL
 * -如果图像无效，则返回ESP_ERR_IMAGE_INVALID。
 * -如果分区或数据指针无效，则返回ESP_ERR_INVALID_ARG。
 */
esp_err_t bootloader_load_image_no_verify(const esp_partition_pos_t *part, esp_image_metadata_t *data);

/**
 * @brief 验证引导加载程序映像。
 *
 * @param[out] If 结果是ESP_OK，该指针为非NULL，它将设置为引导加载程序映像的长度。
 *
 * @return 根据esp_image_load_metadata（）。
 */
esp_err_t esp_image_verify_bootloader(uint32_t *length);

/**
 * @brief 验证引导加载程序映像。
 *
 * @param[out] Metadata 对于图像。仅当结果为ESP_OK时有效。
 *
 * @return 根据esp_image_load_metadata（）。
 */
esp_err_t esp_image_verify_bootloader_data(esp_image_metadata_t *data);

/**
 * @brief 获取图像的闪光大小
 *
 * @param app_flash_size 图像标头中配置的值
 * @return 实际大小（字节）。
 */
int esp_image_get_flash_size(esp_image_flash_size_t app_flash_size);


typedef struct {
    uint32_t drom_addr;
    uint32_t drom_load_addr;
    uint32_t drom_size;
    uint32_t irom_addr;
    uint32_t irom_load_addr;
    uint32_t irom_size;
} esp_image_flash_mapping_t;

#ifdef __cplusplus
}
#endif

