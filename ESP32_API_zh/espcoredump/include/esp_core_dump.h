// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
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
#ifndef ESP_CORE_DUMP_H_
#define ESP_CORE_DUMP_H_

#include "sdkconfig.h"
#include <stddef.h>
#include "esp_err.h"
#include "esp_private/panic_internal.h"
#include "esp_core_dump_summary_port.h"

#ifdef __cplusplus
extern "C" {
#endif

#define APP_ELF_SHA256_SZ (CONFIG_APP_RETRIEVE_LEN_ELF_SHA + 1)

#if CONFIG_ESP_COREDUMP_ENABLE_TO_FLASH && CONFIG_ESP_COREDUMP_DATA_FORMAT_ELF

/**
 * @brief 堆芯转储摘要，堆芯转储的最有意义的内容包含在该结构中
 */
typedef struct {
    uint32_t exc_tcb;                           /*!< 指向导致异常的任务的TCB指针*/
    char exc_task[16];                          /*!< 导致异常的任务的名称*/
    uint32_t exc_pc;                            /*!< 异常的程序计数器*/
    esp_core_dump_bt_info_t exc_bt_info;        /*!< 导致异常的任务的回溯信息*/
    uint32_t core_dump_version;                 /*!< 核心转储版本*/
    uint8_t app_elf_sha256[APP_ELF_SHA256_SZ];  /*!< 崩溃应用程序的SHA256和作为字符串*/
    esp_core_dump_summary_extra_info_t ex_info; /*!< 特定于体系结构的额外数据*/
} esp_core_dump_summary_t;

#endif /* CONFIG_ESP_COREDUMP_ENABLE_TO_FLASH && CONFIG_ESP_COREDUMP_DATA_FORMAT_ELF */

/**************************************************************************************/
/******************************** EXCEPTION MODE API **********************************/
/**************************************************************************************/

/**
 * @brief  初始化核心转储模块内部数据。
 *
 * @note  应在系统启动时调用。
 */
void esp_core_dump_init(void);

/**
 * @brief  将核心转储保存到闪存。
 *
 * 闪存中存储的数据结构如下：
 *
 * |  TOTAL_LEN |  VERSION    | TASKS_NUM   | TCB_SIZE | | TCB_ADDR_1 | STACK_TOP_1 | STACK_END_1 | TCB_1 | STACK_1 | . . . . . . . . | TCB_ADDR_N | STACK_TOP_N | STACK_END_N | TCB_N | STACK_N | | CHECKSUM |
 *
 * 闪存中的核心转储包括崩溃时系统中每个任务的标头和数据。对于闪存数据完整性，在转储数据的核心末尾使用校验和。核心转储数据的结构将在下面详细描述。1） 核心转储以头开始：1.1）TOTAL_LEN是闪存中核心转储数据的总长度，包括校验和。大小为4字节。1.2）VERSION字段保留核心转储的4字节版本。1.2）TASKS_NUM是存储数据的任务数。大小为4字节。1.3）TCB_SIZE是任务TCB结构的大小。大小为4字节。2） 核心转储标头后面是系统中每个任务的数据。任务数据以任务标题开头：2.1）TCB_ADDR是内存中TCB的地址。大小为4字节。2.2）STACK_TOP是任务堆栈的顶部（最顶层堆栈项的地址）。大小为4字节。2.2）STACK_END是任务堆栈的结尾（任务堆栈开始的地址）。大小为4字节。3） 任务头后面跟着TCB数据。大小为TCB_Size字节。4） 任务的堆栈放置在TCB数据之后。大小为（STACK_END-STACK_TOP）字节。5） 校验和位于数据末尾。
 */
void esp_core_dump_to_flash(panic_info_t *info);

/**
 * @brief  将base64编码的核心转储打印到UART。
 *
 * The structure of core dump data is the same as for data stored in flash (@see esp_core_dump_to_flash），并注意：1）打印到UART的核心转储中不存在校验和。2） 由于省略了校验和，TOTAL_LEN不包括其大小。3） 打印的base64数据周围环绕着特殊的消息，以帮助用户识别实际数据的开始和结束。
 */
void esp_core_dump_to_uart(panic_info_t *info);

/**************************************************************************************/
/*********************************** USER MODE API ************************************/
/**************************************************************************************/

/**
 * @brief  检查闪存中核心转储数据的完整性。此函数在计算校验和时读取核心转储数据。如果它与写入闪存的校验和不匹配，则表示数据已损坏，将返回错误。否则，返回ESP_OK。
 *
 * @return `ESP_OK`如果核心转储存在且有效，如果分区中没有存储核心转储，则为`ESP_ERR_NOT_FOUND`，如果核心转储已损坏，则为` ESP_ERR_INVALID_SIZE`或`ESP_ERR _INVALID_CRC`，如果无法访问闪存，则为其他错误，在这种情况下，请参阅\ see ESP_ERR_t
 */
esp_err_t esp_core_dump_image_check(void);

/**
 * @brief  检索闪存中核心转储数据的地址和大小。即使在menuconfig中禁用了核心转储，此函数也始终可用。
 *
 * @param  out_addr   将图像地址存储在闪存中的指针。
 * @param  out_size   将图像大小存储在闪存中的指针（包括校验和）。以字节为单位。
 *
 * @return 成功时ESP_OK，否则请参见ESP_err_t
 */
esp_err_t esp_core_dump_image_get(size_t* out_addr, size_t *out_size);

/**
 * @brief  擦除闪存中的核心转储数据。esp_core_dump_image_get（）将返回esp_ERR_NOT_FOUND。可以在成功传输核心转储后使用。即使在menuconfig中禁用了核心转储，此函数也始终可用。
 *
 * @return 成功时ESP_OK，否则请参见ESP_err_t
 */
esp_err_t esp_core_dump_image_erase(void);

#if CONFIG_ESP_COREDUMP_ENABLE_TO_FLASH && CONFIG_ESP_COREDUMP_DATA_FORMAT_ELF

/**
 * @brief  获取核心转储的摘要。
 *
 * @param  summary   堆芯转储汇总
 *
 * @return 成功时ESP_OK，否则请参见ESP_err_t
 *
 * @note  仅当coredump以闪存和ELF格式存储时，此函数才起作用
 *
 * 示例用法：
 * @code{c}
 *  esp_core_dump_summary_t*summary=malloc（sizeof（esp_core_dump_summary_t））；
 *  if（摘要）{
 *      如果（esp_core_dump_get_summary（summary）==esp_OK）{
 *          //做些什么
 *      }
 *  }
 *  免费（摘要）；
 * @endcode
 */
esp_err_t esp_core_dump_get_summary(esp_core_dump_summary_t *summary);

#endif /* CONFIG_ESP_COREDUMP_ENABLE_TO_FLASH && CONFIG_ESP_COREDUMP_DATA_FORMAT_ELF */

#ifdef __cplusplus
}
#endif

#endif

