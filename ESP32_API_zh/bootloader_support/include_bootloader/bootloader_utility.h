/*
 * SPDX文件版权文本：2018-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#include "bootloader_config.h"
#include "esp_image_format.h"
#include "bootloader_config.h"

/**
 * @brief 加载分区表。
 *
 * 分析分区表，获取有用的数据，如OTA数据分区的位置、工厂应用分区和测试应用分区。
 *
 * @param[out] bs 用于保存读取数据的Bootloader状态结构。
 * @return        如果分区表已成功加载并且MD5校验和有效，则返回true。
 */
bool bootloader_utility_load_partition_table(bootloader_state_t* bs);

/**
 * @brief 返回所选启动分区的索引。
 *
 * 这是首选的引导分区，由分区表和OTA数据中的任何OTA序列号决定。此分区只有在包含有效的应用程序映像时才会启动，否则load_boot_image（）将使用此选择作为起点搜索有效分区。
 *
 * @param[in] bs Bootloader状态结构。
 * @return       成功时返回索引，否则返回INVALID_index。
 */
int bootloader_utility_get_selected_boot_partition(const bootloader_state_t *bs);

/**
 * @brief 加载所选分区并启动应用程序。
 *
 * 从分区“Start_index”开始，如果不可启动，则返回到FACTORY_index（即按降序尝试任何OTA插槽，然后是工厂分区）。如果仍然没有，从“start_index+1”开始，直到编号最高的OTA分区。如果仍然没有，请尝试TEST_APP_INDEX。此函数调用的所有内容都必须位于iram_loader_seg段中。
 *
 * @param[in] bs Bootloader状态结构。
 * @param[in] start_index 开始搜索图像的索引。
 */
__attribute__((noreturn)) void bootloader_utility_load_boot_image(const bootloader_state_t *bs, int start_index);

#ifdef CONFIG_BOOTLOADER_SKIP_VALIDATE_IN_DEEP_SLEEP
/**
 * @brief 加载在我们进入深度睡眠之前工作的应用程序。
 *
 * 如果是深度睡眠，并且RTC内存中有有效分区，请检查重新启动原因，然后尝试加载在进入深度睡眠之前工作的应用程序。
 *
 */
void bootloader_utility_load_boot_image_from_deep_sleep(void);
#endif

/**
 * @brief 软件重置ESP32
 *
 * 如果无法继续，Bootloader代码应该调用它。
 *
 * 不建议从应用程序调用此函数（如果调用，应用程序将中止）。
 */
__attribute__((noreturn)) void bootloader_reset(void);

/**
 * @brief 在退出引导加载程序之前、启动应用程序或重置之前执行任何清理
 */
void bootloader_atexit(void);

/**
 * @brief 将数组转换为可打印字符串。
 *
 * 此函数用于打印SHA-256摘要。\code｛c｝//使用示例。image_hash将被打印#define hash_LEN 32//SHA-256摘要长度…char hash_print[hash_LEN 2+1]；hash_print[hash_LEN 2]=0；bootloader_sha256_hex_to_str（hash_print、image_hash、hash_LEN）；ESP_LOGI（标签，%s“，hash_print）；\nendcode

 * @param[out] out_str       输出字符串
 * @param[in]  in_array_hex  指向输入数组的指针
 * @param[in]  len           输入阵列的长度
 *
 * @return   ESP_OK:成功的ESP_ERR_INVALID_ARG：传递的参数中出错
 */
esp_err_t bootloader_sha256_hex_to_str(char *out_str, const uint8_t *in_array_hex, size_t len);

/**
 * @brief 将缓冲区的日志内容调试为十六进制。
 *
 * @note -仅在组件日志级别为DEBUG或更高时有效。
 *       -它将从@c缓冲区最多打印128个字节。
 *
 * @param buffer 要记录的缓冲区
 * @param length 缓冲区长度（字节）。最大长度128字节。
 * @param label 要打印在日志行开头的标签。
 */
void bootloader_debug_buffer(const void *buffer, size_t length, const char *label);

/** @brief 生成偏移量和偏移量+长度之间的数据摘要。
 *
 * 当数据大小大于3.2MB时，应使用此函数。MMU容量为3.2MB（每个50页-64KB）。考虑到MMU的容量，此函数以3.2MB的数据块形式生成SHA-256数据。
 *
 * @param[in]  flash_offset  闪存中数据的偏移量。
 * @param[in]  len           数据长度（字节）。
 * @param[out] digest        如果返回ESP_OK，则指向写入摘要的缓冲区的指针。
 *
 * @return 如果成功生成安全引导摘要，则ESP_OK。
 */
esp_err_t bootloader_sha256_flash_contents(uint32_t flash_offset, uint32_t len, uint8_t *digest);

