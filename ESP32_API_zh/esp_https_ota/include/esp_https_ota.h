// 版权所有2017-2018 Espressif Systems（上海）私人有限公司
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

#pragma once

#include <esp_http_client.h>
#include <bootloader_common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void *esp_https_ota_handle_t;
typedef esp_err_t(*http_client_init_cb_t)(esp_http_client_handle_t);

/**
 * @brief ESP HTTPS OTA配置
 */
typedef struct {
    const esp_http_client_config_t *http_config;   /*!< ESP HTTP客户端配置*/
    http_client_init_cb_t http_client_init_cb;     /*!< 初始化ESP HTTP客户端后的回调*/
    bool bulk_flash_erase;                         /*!< 初始化期间擦除整个闪存分区。默认情况下，闪存分区在写入操作期间和4K扇区大小的块中被擦除*/
    bool partial_http_download;                    /*!< 允许通过多个HTTP请求下载固件映像*/
    int max_http_request_size;                     /*!< 部分HTTP下载的最大请求大小*/
} esp_https_ota_config_t;

#define ESP_ERR_HTTPS_OTA_BASE            (0x9000)
#define ESP_ERR_HTTPS_OTA_IN_PROGRESS     (ESP_ERR_HTTPS_OTA_BASE + 1)  /* OTA操作正在进行*/

/**
 * @brief    HTTPS OTA固件升级。
 *
 * 此功能分配HTTPS OTA固件升级上下文，建立HTTPS连接，从HTTP流中读取图像数据并将其写入OTA分区，完成HTTPS OTA升级操作。此API支持URL重定向，但如果URL的CA证书不同，则应将其附加到“config”的“cert_pem”成员。
 *
 * @param[in]  config       指向esp_http_client_config_t结构的指针。
 *
 * @note     此API处理整个OTA操作，因此如果正在使用此API，则不应调用“esp_https_OTA”组件中的其他API。如果在HTTPS OTA过程中需要更多信息和控制，那么可以使用“esp_HTTPS_OTA_begin”和后续API。如果此API成功返回，则必须调用esp_restart（）从新固件映像启动。
 *
 * @return
 *    -ESP_OK:OTA数据已更新，下次重新启动将使用指定的分区。
 *    -ESP_FAIL：用于一般故障。
 *    -ESP_ERR_INVALID_ARG:参数无效
 *    -ESP_ERR_OTA_VALIDATE_FAILED:应用程序映像无效
 *    -ESP_ERR_NO_MEM:无法为OTA操作分配内存。
 *    -ESP_ERR_FLASH_OP_TIMEOUT或ESP_ERR-FLASH_OP_FAIL：闪存写入失败。
 *    -有关其他返回代码，请参阅esp-idf的app_update组件中的OTA文档。
 */
esp_err_t esp_https_ota(const esp_http_client_config_t *config);

/**
 * @brief    启动HTTPS OTA固件升级
 *
 * 此函数初始化ESP HTTPS OTA上下文并建立HTTPS连接。必须首先调用此函数。如果此函数成功返回，则应调用“esp_https_ota_perform”以继续ota过程，并且应在ota操作完成或后续操作失败时调用“esp_https_ota_finish”。此API支持URL重定向，但如果URL的CA证书不同，则应将其附加到“http_config”的“cert_pem”成员，该成员是“ota_config”的一部分。如果出现错误，此API会显式将“handle”设置为NULL。
 *
 * @param[in]   ota_config       指向esp_https_ota_config_t结构的指针
 * @param[out]  handle           指向将在此函数中初始化的“esp_https_ota_handle_t”类型的分配数据的指针
 *
 * @note     此API正在阻止，因此设置“http_config”结构的“is_async”成员将导致错误。
 *
 * @return
 *    -ESP_OK:HTTPS OTA固件升级上下文已初始化，HTTPS连接已建立
 *    -ESP_FAIL：用于一般故障。
 *    -ESP_ERR_INVALID_ARG：参数无效（缺少/不正确的配置、证书等）
 *    -有关其他返回代码，请参阅esp-idf中app_update组件和esp_http_client组件中的文档。
 */
esp_err_t esp_https_ota_begin(esp_https_ota_config_t *ota_config, esp_https_ota_handle_t *handle);

/**
 * @brief    从HTTP流读取图像数据并将其写入OTA分区
 *
 * 此函数从HTTP流中读取图像数据并将其写入OTA分区。只有当esp_https_ota_begin（）成功返回时，才能调用此函数。此函数必须在循环中调用，因为它在每次HTTP读取操作后都会返回，因此您可以灵活地中途停止OTA操作。
 *
 * @param[in]  https_ota_handle  指向esp_https_ota_handle_t结构的指针
 *
 * @return
 *    -ESP_ERR_HTTPS_OTA_IN_PROGRESS：OTA更新正在进行中，请再次调用此API以继续。
 *    -ESP_OK:OTA更新成功
 *    -ESP_FAIL:OTA更新失败
 *    -ESP_ERR_INVALID_ARG:参数无效
 *    -ESP_ERR_OTA_VALIDATE_FAILED:应用程序映像无效
 *    -ESP_ERR_NO_MEM:无法为OTA操作分配内存。
 *    -ESP_ERR_FLASH_OP_TIMEOUT或ESP_ERR-FLASH_OP_FAIL：闪存写入失败。
 *    -有关其他返回代码，请参阅esp-idf的app_update组件中的OTA文档。
 */
esp_err_t esp_https_ota_perform(esp_https_ota_handle_t https_ota_handle);

/**
 * @brief   检查是否收到完整数据
 *
 * @note    可以在esp_https_ota_finish（）之前调用此API，以验证是否确实收到了完整的图像。
 *
 * @param[in]   https_ota_handle 指向esp_https_ota_handle_t结构的指针
 *
 * @return
 *    -假的
 *    -真的
 */
bool esp_https_ota_is_complete_data_received(esp_https_ota_handle_t https_ota_handle);

/**
 * @brief    清理HTTPS OTA固件升级并关闭HTTPS连接
 *
 * 此函数关闭HTTP连接并释放ESP HTTPS OTA上下文。此功能将引导分区切换到包含新固件映像的OTA分区。
 *
 * @note     如果此API成功返回，则必须调用esp_restart（）从新固件映像启动。在调用esp_https_ota_abort后，不应调用esp_https_ota_finish
 *
 * @param[in]  https_ota_handle   指向esp_https_ota_handle_t结构的指针
 *
 * @return
 *    -ESP_OK：清理成功
 *    - ESP_ERR_INVALID_STATE
 *    -ESP_ERR_INVALID_ARG:参数无效
 *    -ESP_ERR_OTA_VALIDATE_FAILED:应用程序映像无效
 */
esp_err_t esp_https_ota_finish(esp_https_ota_handle_t https_ota_handle);


/**
 * @brief 清理HTTPS OTA固件升级并关闭HTTPS连接
 *
 * 此函数关闭HTTP连接并释放ESP HTTPS OTA上下文。
 *
 * @note     调用esp_https_ota_finish后不应调用esp_https_ota_abort
 *
 * @param[in]  https_ota_handle   指向esp_https_ota_handle_t结构的指针
 *
 * @return
 *    -ESP_OK：清理成功
 *    -ESP_ERR_INVALID_STATE:ESP HTTPS OTA状态无效
 *    -ESP_FAIL:OTA未启动
 *    -ESP_ERR_NOT_FOUND：未找到OTA句柄
 *    -ESP_ERR_INVALID_ARG:参数无效
 */
esp_err_t esp_https_ota_abort(esp_https_ota_handle_t https_ota_handle);


/**
 * @brief   从图像标题读取应用程序描述。应用程序描述提供了图像的“固件版本”等信息。
 *
 * @note    此API只能在esp_https_ota_begin（）之后和esp_https-ota_perform（）之前调用。调用此API不是强制性的。
 *
 * @param[in]   https_ota_handle   指向esp_https_ota_handle_t结构的指针
 * @param[out]  new_app_info       指向分配的esp_app_desc_t结构的指针
 *
 * @return
 *    -ESP_ERR_INVALID_ARG:参数无效
 *    -ESP_FAIL:无法读取图像描述符
 *    -ESP_OK:已成功读取图像描述符
 */
esp_err_t esp_https_ota_get_img_desc(esp_https_ota_handle_t https_ota_handle, esp_app_desc_t *new_app_info);


/**
* @brief  此函数返回到目前为止读取的OTA图像数据。
*
* @note   仅当至少调用了一次“esp_https_ota_perform（）”或之前调用过“esp_hhttps_ota_get_img_desc”时，才应调用此API。
*
* @param[in]   https_ota_handle   指向esp_https_ota_handle_t结构的指针
*
* @return
*    --1故障时
*    -到目前为止读取的总字节数
*/
int esp_https_ota_get_image_len_read(esp_https_ota_handle_t https_ota_handle);


/**
* @brief  此函数返回OTA图像的总大小。
*
* @note   应在已调用esp_https_ota_begin（）后调用此API。这可用于创建某种进度指示（与esp_https_ota_get_image_len_read（）结合使用）
*
* @param[in]   https_ota_handle   指向esp_https_ota_handle_t结构的指针
*
* @return
*    --1失败或分块编码时
*    -图像的总字节数
*/
int esp_https_ota_get_image_size(esp_https_ota_handle_t https_ota_handle);
#ifdef __cplusplus
}
#endif

