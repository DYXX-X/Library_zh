/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _OTA_OPS_H
#define _OTA_OPS_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "esp_err.h"
#include "esp_partition.h"
#include "esp_image_format.h"
#include "esp_flash_partitions.h"
#include "soc/soc_caps.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define OTA_SIZE_UNKNOWN 0xffffffff /*!< 如果新图像大小未知，则用于esp_ota_begin（）*/
#define OTA_WITH_SEQUENTIAL_WRITES 0xfffffffe /*!< 用于esp_ota_begin（），如果新图像大小未知，并且可以以增量方式进行擦除（假设写入操作是连续的）*/

#define ESP_ERR_OTA_BASE                         0x1500                     /*!< ota_ops api的基本错误代码*/
#define ESP_ERR_OTA_PARTITION_CONFLICT           (ESP_ERR_OTA_BASE + 0x01)  /*!< 如果请求写入或擦除当前正在运行的分区，则出错*/
#define ESP_ERR_OTA_SELECT_INFO_INVALID          (ESP_ERR_OTA_BASE + 0x02)  /*!< OTA数据分区包含无效内容时出错*/
#define ESP_ERR_OTA_VALIDATE_FAILED              (ESP_ERR_OTA_BASE + 0x03)  /*!< OTA应用程序图像无效时出错*/
#define ESP_ERR_OTA_SMALL_SEC_VER                (ESP_ERR_OTA_BASE + 0x04)  /*!< 如果固件的安全版本低于正在运行的固件，则会出错。*/
#define ESP_ERR_OTA_ROLLBACK_FAILED              (ESP_ERR_OTA_BASE + 0x05)  /*!< 如果闪存在被动分区中没有有效固件，因此无法回滚，则会出错*/
#define ESP_ERR_OTA_ROLLBACK_INVALID_STATE       (ESP_ERR_OTA_BASE + 0x06)  /*!< 如果当前活动固件仍标记为待定验证状态（ESP_OTA_IMG_pending_VERIFY），则错误，基本上是升级后首次启动固件映像，因此无法进行固件升级*/


/**
 * @brief 应用程序OTA更新的不透明句柄
 *
 * esp_ota_begin（）返回一个句柄，然后用于对esp_ota_write（）和esp_ota_end（）的后续调用。
 */
typedef uint32_t esp_ota_handle_t;

/**
 * @brief   返回esp_app_desc结构。此结构包括应用程序版本。
 *
 * 返回运行应用程序的说明。
 * @return 指向esp_app_desc结构的指针。
 */
const esp_app_desc_t *esp_ota_get_app_description(void);

/**
 * @brief   用ELF文件的SHA256填充提供的缓冲区，格式为十六进制，以空结尾。如果缓冲区大小不足以容纳十六进制的整个SHA256加上一个空终止符，则将写入最大可能字节数，后跟一个空。
 * @param dst   目标缓冲区
 * @param size  缓冲区大小
 * @return      写入dst的字节数（包括空终止符）
 */
int esp_ota_get_app_elf_sha256(char* dst, size_t size);

/**
 * @brief   开始向指定分区写入OTA更新。

 * 指定的分区将被擦除到指定的图像大小。
 *
 * 如果图像大小未知，请传递OTA_size_UNKNOWN，这将导致整个分区被擦除。
 *
 * 成功后，该函数将分配剩余的内存，直到使用返回的句柄调用esp_ota_end（）。
 *
 * 注意：如果启用了回滚选项，并且正在运行的应用程序处于ESP_OTA_IMG_PENDING_VERIFY状态，则会导致ESP_ERR_OTA_rollback_INVALID_state错误。在运行新应用程序之前，请确认正在运行的应用程序。下载新应用程序时，请使用esp_ota_mark_app_valid_cancel_rollback（）函数（这应该在首次下载新应用时尽早完成）。
 *
 * @param partition 指向将接收OTA更新的分区的信息的指针。必修的。
 * @param image_size 新OTA应用程序图像的大小。将擦除分区以接收此大小的图像。如果为0或OTA_SIZE_UNKNOWN，则会擦除整个分区。
 * @param out_handle 成功时，返回一个句柄，该句柄应用于后续esp_ota_write（）和esp_ota_end（）调用。

 * @return
 *    -ESP_OK:OTA操作已成功启动。
 *    -ESP_ERR_INVALID_ARG：分区或out_handle参数为NULL，或者分区未指向OTA应用分区。
 *    -ESP_ERR_NO_MEM:无法为OTA操作分配内存。
 *    -ESP_ERR_OTA_PARTITION_CONFLICT：分区保存当前运行的固件，无法就地更新。
 *    -ESP_ERR_NOT_FOUND：分区表中找不到分区参数。
 *    -ESP_ERR_OTA_SELECT_INFO_INVALID：OTA数据分区包含无效数据。
 *    -ESP_ERR_INVALID_SIZE:分区不适合配置的闪存大小。
 *    -ESP_ERR_FLASH_OP_TIMEOUT或ESP_ERR-FLASH_OP_FAIL：闪存写入失败。
 *    -ESP_ERR_OTA_ROLLBACK_INVALID_STATE：如果正在运行的应用程序尚未确认状态。在执行更新之前，应用程序必须有效。
 */
esp_err_t esp_ota_begin(const esp_partition_t* partition, size_t image_size, esp_ota_handle_t* out_handle);

/**
 * @brief   将OTA更新数据写入分区
 *
 * 当在OTA操作期间接收到数据时，可以多次调用此函数。数据按顺序写入分区。
 *
 * @param handle  从esp_ota_begin获取的句柄
 * @param data    要写入的数据缓冲区
 * @param size    数据缓冲区的大小（字节）。
 *
 * @return
 *    -ESP_OK:数据已成功写入闪存。
 *    -ESP_ERR_INVALID_ARG:句柄无效。
 *    -ESP_ERR_OTA_VALIDATE_FAILED:图像的第一个字节包含无效的应用程序图像魔法字节。
 *    -ESP_ERR_FLASH_OP_TIMEOUT或ESP_ERR-FLASH_OP_FAIL：闪存写入失败。
 *    -ESP_ERR_OTA_SELECT_INFO_INVALID：OTA数据分区包含无效内容
 */
esp_err_t esp_ota_write(esp_ota_handle_t handle, const void* data, size_t size);

/**
 * @brief   将OTA更新数据写入分区
 *
 * 此函数可以以非连续方式写入数据。如果启用了闪存加密，则数据应为16字节对齐。
 *
 * @param handle  从esp_ota_begin获取的句柄
 * @param data    要写入的数据缓冲区
 * @param size    数据缓冲区大小（字节）
 * @param offset  闪存分区中的偏移量
 *
 * @note 在执行OTA时，如果数据包无序到达，则可以使用esp_OTA_write_with_offset（）以非连续方式写入数据。不建议将esp_ota_writewith_offset（）与esp_ota_write（）结合使用。
 *
 * @return
 *    -ESP_OK:数据已成功写入闪存。
 *    -ESP_ERR_INVALID_ARG:句柄无效。
 *    -ESP_ERR_OTA_VALIDATE_FAILED:图像的第一个字节包含无效的应用程序图像魔法字节。
 *    -ESP_ERR_FLASH_OP_TIMEOUT或ESP_ERR-FLASH_OP_FAIL：闪存写入失败。
 *    -ESP_ERR_OTA_SELECT_INFO_INVALID：OTA数据分区包含无效内容
 */
esp_err_t esp_ota_write_with_offset(esp_ota_handle_t handle, const void *data, size_t size, uint32_t offset);

/**
 * @brief 完成OTA更新并验证新编写的应用程序映像。
 *
 * @param handle  从esp_ota_begin（）获得的句柄。
 *
 * @note 调用esp_ota_end（）后，句柄不再有效，与之相关的任何内存都将被释放（无论结果如何）。
 *
 * @return
 *    -ESP_OK：新编写的OTA应用程序图像有效。
 *    -ESP_ERR_NOT_FOUND:未找到OTA句柄。
 *    -ESP_ERR_INVALID_ARG:句柄从未写入。
 *    -ESP_ERR_OTA_VALIDATE_FAILED:OTA映像无效（不是有效的应用程序映像，或者-如果启用了安全引导-签名验证失败）
 *    -ESP_ERR_INVALID_STATE：如果启用了闪存加密，则此结果表示将最终加密字节写入闪存时发生内部错误。
 */
esp_err_t esp_ota_end(esp_ota_handle_t handle);

/**
 * @brief 中止OTA更新，释放与之相关的句柄和内存。
 *
 * @param handle 从esp_ota_begin（）获得。
 *
 * @return
 *    -ESP_OK：句柄及其关联内存已成功释放。
 *    -ESP_ERR_NOT_FOUND:未找到OTA句柄。
 */
esp_err_t esp_ota_abort(esp_ota_handle_t handle);


/**
 * @brief 为新启动分区配置OTA数据
 *
 * @note 如果此函数返回ESP_OK，则调用ESP_restart（）将启动新配置的应用分区。
 *
 * @param partition 指向包含要启动的应用程序映像的分区的信息的指针。
 *
 * @return
 *    -ESP_OK:OTA数据已更新，下次重新启动将使用指定的分区。
 *    -ESP_ERR_INVALID_ARG：分区参数为NULL或未指向“app”类型的有效OTA分区。
 *    -ESP_ERR_OTA_VALIDATE_FAILED:分区包含无效的应用程序映像。如果启用了安全引导并且签名验证失败，也会返回。
 *    -ESP_ERR_NOT_FOUND：未找到OTA数据分区。
 *    -ESP_ERR_FLASH_OP_TIMEOUT或ESP_ERR-FLASH_OP_FAIL：闪存擦除或写入失败。
 */
esp_err_t esp_ota_set_boot_partition(const esp_partition_t* partition);

/**
 * @brief 获取当前配置的启动应用程序的分区信息
 *
 * 如果已调用esp_ota_set_boot_partition（），则将返回该函数设置的分区。
 *
 * 如果尚未调用esp_ota_set_boot_partition（），则结果通常与esp_ota_get_running_partition）相同。如果配置的引导分区不包含有效的应用程序（这意味着正在运行的分区将是引导加载程序通过回退选择的应用程序），则这两个结果不相等。
 *
 * 如果OTA数据分区不存在或无效，则结果是分区表中找到的第一个应用分区。按照优先级顺序，这意味着：工厂应用程序、第一个OTA应用程序插槽或测试应用程序分区。
 *
 * 注意，不能保证返回的分区是有效的应用程序。使用esp_image_verify（esp_image_verify，…）验证返回的分区是否包含可引导映像。
 *
 * @return 指向分区结构信息的指针，如果分区表无效或闪存读取操作失败，则返回NULL。任何返回的指针在应用程序的生存期内都有效。
 */
const esp_partition_t* esp_ota_get_boot_partition(void);


/**
 * @brief 获取当前运行应用的分区信息
 *
 * 此函数与esp_ota_get_boot_partition（）不同，因为它忽略了esp_ota_set_boot_partition导致的所选启动分区的任何更改。只有代码当前正在运行的应用程序才会返回其分区信息。
 *
 * 如果配置的引导分区不知何故无效，并且引导加载程序在引导时返回到不同的应用分区，则此函数返回的分区也可能与esp_ota_get_boot_partition（）不同。
 *
 * @return 指向分区结构信息的指针，如果找不到分区或闪存读取操作失败，则返回NULL。返回的指针在应用程序的生存期内有效。
 */
const esp_partition_t* esp_ota_get_running_partition(void);


/**
 * @brief 返回下一个OTA应用分区，该分区应使用新固件写入。
 *
 * 调用此函数以查找可以传递给esp_OTA_begin（）的OTA应用分区。
 *
 * 从当前运行的分区开始查找下一个分区循环。
 *
 * @param start_from 如果已设置，则将此分区信息视为描述当前正在运行的分区。可以为NULL，在这种情况下，esp_ota_get_running_partition（）用于查找当前正在运行的分区。此函数的结果永远不会与此参数相同。
 *
 * @return 指向下一步应更新的分区信息的指针。NULL结果表示OTA数据分区无效，或者未找到符合条件的OTA应用程序插槽分区。
 *
 */
const esp_partition_t* esp_ota_get_next_update_partition(const esp_partition_t *start_from);

/**
 * @brief 返回应用分区的esp_app_desc结构。此结构包括应用程序版本。
 *
 * 返回请求的应用分区的说明。
 * @param[in] partition     指向应用分区的指针。（仅应用程序分区）
 * @param[out] app_desc     有关应用程序的信息结构。
 * @return
 *  -ESP_OK成功。
 *  -找不到ESP_ERR_NOT_FOUND app_desc结构。魔术词不正确。
 *  -ESP_ERR_NOT_SUPPORTED分区不是应用程序。
 *  -ESP_ERR_INVALID_ARG参数为NULL或分区的偏移量超过分区大小。
 *  -ESP_ERR_INVALID_SIZE读取将超出分区的边界。
 *  -或来自低级闪存驱动器的错误代码之一。
 */
esp_err_t esp_ota_get_partition_description(const esp_partition_t *partition, esp_app_desc_t *app_desc);

/**
 * @brief 返回分区表中提供的ota分区数。
 *
 * @return
 *  -OTA分区数
 */
uint8_t esp_ota_get_app_partition_count(void);

/**
 * @brief 调用此函数表示正在运行的应用程序运行良好。
 *
 * @return
 *  -ESP_OK：如果成功。
 */
esp_err_t esp_ota_mark_app_valid_cancel_rollback(void);

/**
 * @brief 调用此函数以在重新启动时回滚到以前可用的应用程序。
 *
 * 如果回滚成功，则设备将重置，否则API将返回错误代码。检查在回滚时可以启动的闪存驱动器上的应用程序。如果闪存没有至少一个应用程序（运行中的应用程序除外），则无法回滚。
 * @return
 *  -ESP_FAIL：如果不成功。
 *  -ESP_ERR_OTA_ROLLBACK_FAILED：由于flash没有任何应用程序，因此无法回滚。
 */
esp_err_t esp_ota_mark_app_invalid_rollback_and_reboot(void);

/**
 * @brief 返回最后一个状态无效的分区（ESP_OTA_IMG_invalid或ESP_OTA-IMG_ABORTED）。
 *
 * @return 隔断
 */
const esp_partition_t* esp_ota_get_last_invalid_partition(void);

/**
 * @brief 返回给定分区的状态。
 *
 * @param[in] partition  指向分区的指针。
 * @param[out] ota_state 分区的状态（如果该分区在otadata中有记录）。
 * @return
 *        -ESP_OK：成功。
 *        -ESP_ERR_INVALID_ARG:分区或ota_state参数为NULL。
 *        -ESP_ERR_NOT_SUPPORTED：分区不是ota。
 *        -ESP_ERR_NOT_FOUND:分区表没有otadata，或者找不到给定分区的状态。
 */
esp_err_t esp_ota_get_state_partition(const esp_partition_t *partition, esp_ota_img_states_t *ota_state);

/**
 * @brief 擦除上一个启动应用程序分区，并为此分区选择相应的otadata。
 *
 * 当当前应用程序标记为有效时，您可以擦除以前的应用程序分区。
 * @return
 *        -ESP_OK：成功，否则为ESP_ERR。
 */
esp_err_t esp_ota_erase_last_boot_app_partition(void);

/**
 * @brief 检查在回滚时可以启动的插槽上的应用程序。
 *
 * 这些应用程序应该是有效的（在otadata中标记为非UNDEFINED、INVALID或ABORTED，并且crc良好），并且能够启动，并且app>=efuse的secure_version（如果启用了反回滚）。
 *
 * @return
 *        -True：如果插槽至少有一个应用程序（运行中的应用程序除外），则返回True。
 *        -False：无法回滚。
 */
bool esp_ota_check_rollback_is_possible(void);

#if SOC_EFUSE_SECURE_BOOT_KEY_DIGESTS > 1 && (CONFIG_SECURE_BOOT_V2_ENABLED || __DOXYGEN__)

/**
 * 安全引导V2公钥索引。
 */
typedef enum {
    SECURE_BOOT_PUBLIC_KEY_INDEX_0,     /*!< 指向安全引导v2公钥的第0个索引*/
    SECURE_BOOT_PUBLIC_KEY_INDEX_1,     /*!< 指向Secure Boot v2公钥的第一个索引*/
    SECURE_BOOT_PUBLIC_KEY_INDEX_2      /*!< 指向Secure Boot v2公钥的第二个索引*/
} esp_ota_secure_boot_public_key_index_t;

/**
 * @brief 撤消旧签名摘要。在回滚逻辑之后在应用程序中调用。
 *
 * 与ESP32-S2上的安全引导v2相关，其中最多可存储3个密钥摘要（密钥#N-1、密钥#N、密钥#N+1）。当用于签署应用程序的密钥#N-1无效时，OTA更新将与使用密钥#N-1&密钥#N签名的应用程序一起发送。成功启动后，OTA应用程序应调用此功能以撤销密钥#N-1。
 *
 * @param index -要吊销的签名块的索引
 *
 * @return
 *        -ESP_OK：如果撤销成功。
 *        -ESP_ERR_INVALID_ARG：如果要撤销的公钥的索引不正确。
 *        -ESP_FAIL：如果未启用安全引导v2。
 */
esp_err_t esp_ota_revoke_secure_boot_public_key(esp_ota_secure_boot_public_key_index_t index);
#endif /* SOC_EFUSE_SECURE_BOOT_KEY_DIGESTS > 1 */

#ifdef __cplusplus
}
#endif

#endif /* OTA_OPS_H */

