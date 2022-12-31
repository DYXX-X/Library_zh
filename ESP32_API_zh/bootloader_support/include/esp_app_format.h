/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#include <inttypes.h>

/**
 * @brief ESP芯片ID
 *
 */
typedef enum {
    ESP_CHIP_ID_ESP32 = 0x0000,  /*!< 芯片ID:ESP32*/
    ESP_CHIP_ID_ESP32S2 = 0x0002,  /*!< 芯片ID:ESP32-S2*/
    ESP_CHIP_ID_ESP32C3 = 0x0005, /*!< 芯片ID:ESP32-C3*/
    ESP_CHIP_ID_ESP32S3 = 0x0009, /*!< 芯片ID:ESP32-S3*/
    ESP_CHIP_ID_ESP32H2 = 0x000A, /*!< 芯片ID:ESP32-H2*/  // ESP32H2-TODO: IDF-3475
    ESP_CHIP_ID_INVALID = 0xFFFF /*!< 无效的芯片ID（我们定义它是为了确保esp_chip_ID_t的大小为2字节）*/
} __attribute__((packed)) esp_chip_id_t;

/**@秒*/
_Static_assert(sizeof(esp_chip_id_t) == 2, "esp_chip_id_t should be 16 bit");
/**@结束秒*/

/**
 * @brief SPI闪存模式，用于esp_image_header_t
 */
typedef enum {
    ESP_IMAGE_SPI_MODE_QIO,         /*!< SPI模式QIO*/
    ESP_IMAGE_SPI_MODE_QOUT,        /*!< SPI模式QOUT*/
    ESP_IMAGE_SPI_MODE_DIO,         /*!< SPI模式DIO*/
    ESP_IMAGE_SPI_MODE_DOUT,        /*!< SPI模式DOUT*/
    ESP_IMAGE_SPI_MODE_FAST_READ,   /*!< SPI模式FAST_READ*/
    ESP_IMAGE_SPI_MODE_SLOW_READ    /*!< SPI模式SLOW_READ*/
} esp_image_spi_mode_t;

/**
 * @brief SPI闪存时钟频率
 */
typedef enum {
    ESP_IMAGE_SPI_SPEED_40M,        /*!< SPI时钟频率40 MHz*/
    ESP_IMAGE_SPI_SPEED_26M,        /*!< SPI时钟频率26 MHz*/
    ESP_IMAGE_SPI_SPEED_20M,        /*!< SPI时钟频率20 MHz*/
    ESP_IMAGE_SPI_SPEED_80M = 0xF   /*!< SPI时钟频率80 MHz*/
} esp_image_spi_freq_t;

/**
 * @brief 支持的SPI闪存大小
 */
typedef enum {
    ESP_IMAGE_FLASH_SIZE_1MB = 0,   /*!< SPI闪存大小1 MB*/
    ESP_IMAGE_FLASH_SIZE_2MB,       /*!< SPI闪存大小2 MB*/
    ESP_IMAGE_FLASH_SIZE_4MB,       /*!< SPI闪存大小4 MB*/
    ESP_IMAGE_FLASH_SIZE_8MB,       /*!< SPI闪存大小8 MB*/
    ESP_IMAGE_FLASH_SIZE_16MB,      /*!< SPI闪存大小16 MB*/
    ESP_IMAGE_FLASH_SIZE_MAX        /*!< SPI闪存大小最大*/
} esp_image_flash_size_t;

#define ESP_IMAGE_HEADER_MAGIC 0xE9 /*!< esp_image_header_t结构的神奇单词。*/

/**
 * @brief 二进制图像的主标题
 */
typedef struct {
    uint8_t magic;              /*!< 魔术词ESP_IMAGE_HEADER_Magic*/
    uint8_t segment_count;      /*!< 内存段计数*/
    uint8_t spi_mode;           /*!< 闪存读取模式（esp_image_spi_mode_t为uint8_t）*/
    uint8_t spi_speed: 4;       /*!< 闪光频率（esp_image_spi_freq_t为uint8_t）*/
    uint8_t spi_size: 4;        /*!< 闪存芯片大小（esp_image_flash_size_t为uint8_t）*/
    uint32_t entry_addr;        /*!< 入口地址*/
    uint8_t wp_pin;            /*!< 通过efuse设置SPI引脚时的WP引脚（由ROM引导加载器读取，IDF引导加载器使用软件配置WP引脚并将此字段设置为0xEE=禁用）*/
    uint8_t spi_pin_drv[3];     /*!< SPI闪存引脚的驱动器设置（由ROM引导加载程序读取）*/
    esp_chip_id_t chip_id;      /*!< 芯片识别号*/
    uint8_t min_chip_rev;       /*!< 图像支持的最小芯片修订*/
    uint8_t reserved[8];       /*!< 附加标头空间中的保留字节，当前未使用*/
    uint8_t hash_appended;      /*!< 如果为1，（整个图像的）SHA256摘要“简单哈希”将附加在校验和之后。包含在图像长度中。此摘要独立于安全引导，仅用于检测损坏。对于安全的引导签名映像，签名附加在其后（签名数据中包含简单哈希）。*/
} __attribute__((packed))  esp_image_header_t;

/**@秒*/
_Static_assert(sizeof(esp_image_header_t) == 24, "binary image header should be 24 bytes");
/**@结束秒*/


/**
 * @brief 二进制图像段的标题
 */
typedef struct {
    uint32_t load_addr;     /*!< 段的地址*/
    uint32_t data_len;      /*!< 数据长度*/
} esp_image_segment_header_t;

#define ESP_IMAGE_MAX_SEGMENTS 16           /*!< 图像中的最大分段数。*/

#define ESP_APP_DESC_MAGIC_WORD 0xABCD5432  /*!< DROM中esp_app_desc结构的神奇词汇。*/

/**
 * @brief 应用程序说明。
 */
typedef struct {
    uint32_t magic_word;        /*!< 魔术字ESP_APP_DESC_Magic_word*/
    uint32_t secure_version;    /*!< 安全版本*/
    uint32_t reserv1[2];        /*!< 保留1*/
    char version[32];           /*!< 应用程序版本*/
    char project_name[32];      /*!< 项目名称*/
    char time[16];              /*!< 编译时间*/
    char date[16];              /*!< 编制日期*/
    char idf_ver[32];           /*!< 版本IDF*/
    uint8_t app_elf_sha256[32]; /*!< elf文件的sha256*/
    uint32_t reserv2[20];       /*!< 保留2*/
} esp_app_desc_t;

/**@秒*/
_Static_assert(sizeof(esp_app_desc_t) == 256, "esp_app_desc_t should be 256 bytes");
/**@结束秒*/

