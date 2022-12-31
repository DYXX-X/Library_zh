// 版权所有2015-2018 Espressif Systems（上海）私人有限公司
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

#ifndef _ESP_TRANSPORT_UTILS_H_
#define _ESP_TRANSPORT_UTILS_H_
#include <sys/time.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief      malloc之后用于NULL ptr检查的实用程序宏
 *
 */
#define ESP_TRANSPORT_MEM_CHECK(TAG, a, action) if (!(a)) {                                         \
        ESP_LOGE(TAG,"%s(%d): %s", __FUNCTION__, __LINE__, "Memory exhausted");                     \
        action;                                                                                     \
        }

/**
 * @brief      用于检查esp_err_t错误代码的实用宏
 */
#define ESP_TRANSPORT_ERR_OK_CHECK(TAG, err, action) \
        {                                                     \
            esp_err_t _esp_transport_err_to_check = err;      \
            if (_esp_transport_err_to_check != ESP_OK) {      \
                ESP_LOGE(TAG,"%s(%d): Expected ESP_OK; reported: %d", __FUNCTION__, __LINE__, _esp_transport_err_to_check); \
                action;                                       \
            }                                                 \
        }

/**
 * @brief      将毫秒转换为有效超时的timeval结构，否则（如果timeout_ms=-1请求“永远等待”）timeval结构不会更新，返回NULL
 *
 * @param[in]  timeout_ms  超时值（以毫秒为单位）或-1到永远等待
 * @param[out] tv          指向timeval结构的指针
 *
 * @return
 * -如果timeout_ms=-1，则为NULL（永远等待）
 * -指向更新的timeval结构（作为“tv”参数提供）的指针，并重新计算超时值
 */
struct timeval* esp_transport_utils_ms_to_timeval(int timeout_ms, struct timeval *tv);


#ifdef __cplusplus
}
#endif
#endif /* _ESP_TRANSPORT_UTILS_H_ */

