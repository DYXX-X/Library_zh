/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#include "esp_err.h"
#include "esp_types.h"
#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ESP_PARTITION_MAGIC 0x50AA
#define ESP_PARTITION_MAGIC_MD5 0xEBEB

#define PART_TYPE_APP 0x00
#define PART_SUBTYPE_FACTORY  0x00
#define PART_SUBTYPE_OTA_FLAG 0x10
#define PART_SUBTYPE_OTA_MASK 0x0f
#define PART_SUBTYPE_TEST     0x20

#define PART_TYPE_DATA 0x01
#define PART_SUBTYPE_DATA_OTA 0x00
#define PART_SUBTYPE_DATA_RF  0x01
#define PART_SUBTYPE_DATA_WIFI 0x02
#define PART_SUBTYPE_DATA_NVS_KEYS 0x04
#define PART_SUBTYPE_DATA_EFUSE_EM 0x05

#define PART_TYPE_END 0xff
#define PART_SUBTYPE_END 0xff

#define PART_FLAG_ENCRYPTED (1<<0)

/* md5sum值位于ESP_PARTITION_MAGIC_MD5偏移量之后的这么多字节处*/
#define ESP_PARTITION_MD5_OFFSET 16

/* 预分区表固定闪存偏移*/
#define ESP_BOOTLOADER_DIGEST_OFFSET 0x0
#define ESP_BOOTLOADER_OFFSET CONFIG_BOOTLOADER_OFFSET_IN_FLASH  /* 引导加载程序映像的偏移量。在引导加载器KConfig中具有匹配的值。projbuild文件。*/
#define ESP_PARTITION_TABLE_OFFSET CONFIG_PARTITION_TABLE_OFFSET /* 分区表的偏移量。向后兼容的名称。*/

#define ESP_PARTITION_TABLE_MAX_LEN 0xC00 /* 分区表数据的最大长度*/
#define ESP_PARTITION_TABLE_MAX_ENTRIES (ESP_PARTITION_TABLE_MAX_LEN / sizeof(esp_partition_info_t)) /* 分区表数据的最大长度，包括终止项*/

///OTA_DATA状态用于检查应用程序的可操作性。
typedef enum {
    ESP_OTA_IMG_NEW             = 0x0U,         /*!< 监控第一次启动。在引导加载程序中，此状态更改为ESP_OTA_IMG_PENDING_VERIFY。*/
    ESP_OTA_IMG_PENDING_VERIFY  = 0x1U,         /*!< 此应用程序的第一次启动是。如果在第二次启动时此状态为，则将更改为ABORTED（中止）。*/
    ESP_OTA_IMG_VALID           = 0x2U,         /*!< 应用程序已确认可行。应用程序可以无限制地启动和工作。*/
    ESP_OTA_IMG_INVALID         = 0x3U,         /*!< 应用程序被确认为不可用。此应用程序根本不会选择启动。*/
    ESP_OTA_IMG_ABORTED         = 0x4U,         /*!< 应用程序无法确认是否可行。在引导加载程序中，IMG_PENDING_VERIFY状态将更改为IMG_ABORTED。此应用程序根本不会选择启动。*/
    ESP_OTA_IMG_UNDEFINED       = 0xFFFFFFFFU,  /*!< 未定义。应用程序可以无限制地启动和工作。*/
} esp_ota_img_states_t;

/* OTA选择结构（OTA数据分区中有两个副本。）32字节的大小适合闪存加密*/
typedef struct {
    uint32_t ota_seq;
    uint8_t  seq_label[20];
    uint32_t ota_state;
    uint32_t crc; /* 仅限ota_seq字段的CRC32*/
} esp_ota_select_entry_t;


typedef struct {
    uint32_t offset;
    uint32_t size;
} esp_partition_pos_t;

/* 描述分区表项布局的结构。请参阅docs/partition_tables。有关单个字段的更多信息，请参见第一部分。
 */
typedef struct {
    uint16_t magic;
    uint8_t  type;
    uint8_t  subtype;
    esp_partition_pos_t pos;
    uint8_t  label[16];
    uint32_t flags;
} esp_partition_info_t;

/* @brief 验证分区表
 *
 * @param partition_table 至少指向潜在分区表数据的ESP_PARTITION_TABLE_MAX_ENTRIES的指针。（ESP_PARTITION_TABLE_MAX_LEN字节。）
 * @param log_errors 如果分区表无效，则记录错误。
 * @param num_partitions 如果结果为ESP_OK，num_partitions将更新为分区总数（不包括终止条目）。
 *
 * @return 成功时为ESP_OK，如果分区表无效，则为ESP_ERR_INVALID_STATE。
 */
esp_err_t esp_partition_table_verify(const esp_partition_info_t *partition_table, bool log_errors, int *num_partitions);


/**
 * 检查主闪存上的区域是否可以安全写入。
 *
 * @param addr 区域的起始地址
 * @param size 区域的大小
 *
 * @return 如果区域可以安全写入，则为true，否则为false。
 */
bool esp_partition_main_flash_region_safe(size_t addr, size_t size);

#ifdef __cplusplus
}
#endif

