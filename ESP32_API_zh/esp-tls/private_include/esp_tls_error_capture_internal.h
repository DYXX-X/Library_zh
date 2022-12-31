/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef __ESP_TLS_ERROR_CAPTURE_INTERNAL_H__
#define __ESP_TLS_ERROR_CAPTURE_INTERNAL_H__
/**
* 注意：这是错误记录器的实现占位符。此版本是esp-tls组件的内部版本，仅保存上次发生错误的单个esp_err
*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 错误跟踪器日志宏，用于在内部或使用外部/全局实现映射跟踪错误
 */
#define ESP_INT_EVENT_TRACKER_CAPTURE(h, type, code)    esp_tls_internal_event_tracker_capture(h, type, code)

/**
 * @brief 内部跟踪器捕获错误
 *
 * 此实现保存可用类型的最新错误
 *
 * @param[in]  h        esp-tls错误句柄
 * @param[in]  err_type 特定错误类型
 * @param[int] code     要捕获的错误代码
 *
 */
void esp_tls_internal_event_tracker_capture(esp_tls_error_handle_t h, uint32_t type, int code);

/**
 * @brief 创建内部跟踪器存储
 *
 * @return 如果成功，则返回错误跟踪句柄；如果分配错误，则返回NULL
 */
esp_tls_error_handle_t esp_tls_internal_event_tracker_create(void);

/**
 * @brief 销毁内部跟踪器存储
 *
 * @param[in]  h        esp-tls错误句柄
 */
 void esp_tls_internal_event_tracker_destroy(esp_tls_error_handle_t h);

#ifdef __cplusplus
}
#endif

#endif //__ESP_TLS_ERROR_CAPTURE_INTERNAL_H__

