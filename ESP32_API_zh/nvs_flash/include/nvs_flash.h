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
#ifndef nvs_flash_h
#define nvs_flash_h

#ifdef __cplusplus
extern "C" {
#endif

#include "nvs.h"
#include "esp_partition.h"


#define NVS_KEY_SIZE 32 // AES-256

/**
 * @brief 加密和解密密钥
 */
typedef struct {
    uint8_t eky[NVS_KEY_SIZE]; /*!<  XTS加密和解密密钥*/
    uint8_t tky[NVS_KEY_SIZE]; /*!<  XTS调整键*/
} nvs_sec_cfg_t;

/**
 * @brief 初始化默认NVS分区。
 *
 * 此API初始化默认NVS分区。默认NVS分区是分区表中标记为“NVS”的分区。
 *
 * 当在menuconfig中启用“NVS_ENCRYPTION”时，此API为默认NVS分区启用NVS加密，如下所示1.从分区表中列出的第一个NVS密钥分区读取安全配置。（NVS密钥分区是子类型值设置为“NVS_keys”的任何“数据”类型分区）2.如果在上一步骤中获得的NVS密钥部分为空，则在该NVS密钥中生成并存储新密钥。3.使用前面步骤中获得/生成的安全配置在内部调用“nvs_flash_secure_init（）”。
 *
 * 初始化后NVS读/写API保持不变，与NVS加密无关。
 *
 * @return
 *      -如果存储已成功初始化，则返回ESP_OK。
 *      -如果NVS存储不包含空页（如果NVS分区被截断，则可能发生这种情况），则为ESP_ERR_NVS_NO_FREE_PAGES
 *      -如果分区表中未找到标签为“nvs”的分区，则为ESP_ERR_NOT_FOUND
 *      -ESP_ERR_NO_MEM，以防无法为内部结构分配内存
 *      -来自底层闪存驱动程序的错误代码之一
 *      -nvs_flash_read_security_cfg API中的错误代码（启用“nvs_ENCRYPTION”时）。
 *      -nvs_flash_generate_keys API中的错误代码（启用“nvs_ENCRYPTION”时）。
 *      -nvs_flash_secure_init_partition API中的错误代码（启用“nvs_ENCRYPTION”时）。
 */
esp_err_t nvs_flash_init(void);

/**
 * @brief 初始化指定分区的NVS闪存。
 *
 * @param[in]  partition_label   分区的标签。不能超过16个字符。
 *
 * @return
 *      -如果存储已成功初始化，则返回ESP_OK。
 *      -如果NVS存储不包含空页（如果NVS分区被截断，则可能发生这种情况），则为ESP_ERR_NVS_NO_FREE_PAGES
 *      -如果在分区表中找不到指定的分区，则为ESP_ERR_NOT_FOUND
 *      -ESP_ERR_NO_MEM，以防无法为内部结构分配内存
 *      -来自底层闪存驱动程序的错误代码之一
 */
esp_err_t nvs_flash_init_partition(const char *partition_label);

/**
 * @brief 为分区指针指定的分区初始化NVS闪存。
 *
 * @param[in] partition 指向ESP分区API获得的分区的指针。
 *
 * @return
 *      -ESP_OK（如果存储已成功初始化）
 *      -如果NVS存储不包含空页（如果NVS分区被截断，则可能发生这种情况），则为ESP_ERR_NVS_NO_FREE_PAGES
 *      -分区为空时的ESP_ERR_INVALID_ARG
 *      -ESP_ERR_NO_MEM，以防无法为内部结构分配内存
 *      -来自底层闪存驱动程序的错误代码之一
 */
esp_err_t nvs_flash_init_partition_ptr(const esp_partition_t *partition);

/**
 * @brief 取消初始化默认NVS分区的NVS存储
 *
 * 默认NVS分区是分区表中带有“NVS”标签的分区。
 *
 * @return
 *      -成功时ESP_OK（存储已取消初始化）
 *      -如果在调用之前未初始化存储，则为ESP_ERR_NVS_NOT_INITIALIZED
 */
esp_err_t nvs_flash_deinit(void);

/**
 * @brief 取消初始化给定NVS分区的NVS存储
 *
 * @param[in]  partition_label   分区的标签
 *
 * @return
 *      -成功时ESP_OK
 *      -如果在此调用之前未初始化给定分区的存储，则为ESP_ERR_NVS_NOT_INITIALIZED
 */
esp_err_t nvs_flash_deinit_partition(const char* partition_label);

/**
 * @brief 擦除默认NVS分区
 *
 * 擦除默认NVS分区的所有内容（标签为“NVS”的分区）。
 *
 * @note 如果分区已初始化，则此函数首先对其进行反初始化。之后，必须再次初始化分区才能使用。
 *
 * @return
 *      -成功时ESP_OK
 *      -如果分区表中没有标记为“NVS”的NVS分区，则为ESP_ERR_NOT_FOUND
 *      -在反初始化失败的情况下出现不同的错误（不应该发生）
 */
esp_err_t nvs_flash_erase(void);

/**
 * @brief 擦除指定的NVS分区
 *
 * 擦除指定NVS分区的所有内容
 *
 * @note 如果分区已初始化，则此函数首先对其进行反初始化。之后，必须再次初始化分区才能使用。
 *
 * @param[in]  part_name    应该擦除的分区的名称（标签）
 *
 * @return
 *      -成功时ESP_OK
 *      -如果分区表中没有具有指定名称的NVS分区，则为ESP_ERR_NOT_FOUND
 *      -在反初始化失败的情况下出现不同的错误（不应该发生）
 */
esp_err_t nvs_flash_erase_partition(const char *part_name);

/**
 * @brief 擦除自定义分区。
 *
 * 清除指定自定义分区的所有内容。
 *
 * @note 如果分区已初始化，则此函数首先对其进行反初始化。之后，必须再次初始化分区才能使用。
 *
 * @param[in] partition 指向ESP分区API获得的分区的指针。
 *
 * @return
 *      -成功时ESP_OK
 *      -如果分区表中没有具有指定参数的分区，则为ESP_ERR_NOT_FOUND
 *      -分区为空时的ESP_ERR_INVALID_ARG
 *      -来自底层闪存驱动程序的错误代码之一
 */
esp_err_t nvs_flash_erase_partition_ptr(const esp_partition_t *partition);

/**
 * @brief 初始化默认NVS分区。
 *
 * 此API初始化默认NVS分区。默认NVS分区是分区表中标记为“NVS”的分区。
 *
 * @param[in]  cfg 用于NVS加密/解密的安全配置（密钥）。如果cfg为NULL，则不使用加密。
 *
 * @return
 *      -如果存储已成功初始化，则返回ESP_OK。
 *      -如果NVS存储不包含空页（如果NVS分区被截断，则可能发生这种情况），则为ESP_ERR_NVS_NO_FREE_PAGES
 *      -如果分区表中未找到标签为“nvs”的分区，则为ESP_ERR_NOT_FOUND
 *      -ESP_ERR_NO_MEM，以防无法为内部结构分配内存
 *      -来自底层闪存驱动程序的错误代码之一
 */
esp_err_t nvs_flash_secure_init(nvs_sec_cfg_t* cfg);

/**
 * @brief 初始化指定分区的NVS闪存。
 *
 * @param[in]  partition_label   分区的标签。请注意，在内部，保留对传递值的引用，并且应可供将来操作使用
 *
 * @param[in]  cfg 用于NVS加密/解密的安全配置（密钥）。如果cfg为空，则不使用加密/解密。
 * @return
 *      -如果存储已成功初始化，则返回ESP_OK。
 *      -如果NVS存储不包含空页（如果NVS分区被截断，则可能发生这种情况），则为ESP_ERR_NVS_NO_FREE_PAGES
 *      -如果在分区表中找不到指定的分区，则为ESP_ERR_NOT_FOUND
 *      -ESP_ERR_NO_MEM，以防无法为内部结构分配内存
 *      -来自底层闪存驱动程序的错误代码之一
 */
esp_err_t nvs_flash_secure_init_partition(const char *partition_label, nvs_sec_cfg_t* cfg);

/**
 * @brief 在提供的esp分区中生成并存储NVS密钥
 *
 * @param[in]  partition 指向使用esp_partition_find_first或esp_partition _get获得的分区结构的指针。必须为非NULL。
 * @param[out] cfg       指向nvs安全配置结构的指针。指针必须为非NULL。生成的密钥将填充到此结构中。
 *
 *
 * @return
 *      -ESP_OK，如果cfg读取成功；
 *      -ESP_INVALID_ARG，如果是分区或cfg；
 *      -或来自esp_partition_write/eerase API的错误代码。
 */

esp_err_t nvs_flash_generate_keys(const esp_partition_t* partition, nvs_sec_cfg_t* cfg);


/**
 * @brief 从分区读取NVS安全配置。
 *
 * @param[in]  partition 指向使用esp_partition_find_first或esp_partition _get获得的分区结构的指针。必须为非NULL。
 * @param[out] cfg       指向nvs安全配置结构的指针。指针必须为非NULL。
 *
 * @note  假设提供的分区标记为“加密”。
 *
 * @return
 *      -ESP_OK，如果cfg读取成功；
 *      -ESP_INVALID_ARG，如果是分区或cfg；
 *      -如果分区尚未用键写入，则为ESP_ERR_NVS_KEYS_NOT_INITIALIZED。
 *      -如果发现包含密钥的分区已损坏，则返回ESP_ERR_NVS_CORRUPT_KEY_PART
 *      -或esp_partition_read API中的错误代码。
 */

esp_err_t nvs_flash_read_security_cfg(const esp_partition_t* partition, nvs_sec_cfg_t* cfg);

#ifdef __cplusplus
}
#endif


#endif /* nvs_flash_h*/

