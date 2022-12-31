// 版权所有2020 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。
#ifndef ESP_APP_TRACE_PORT_H_
#define ESP_APP_TRACE_PORT_H_

#include "esp_app_trace_util.h"

#ifdef __cplusplus
extern "C" {
#endif

/**Apptrace硬件接口。*/
typedef struct {
    esp_err_t (*init)(void *hw_data);
    uint8_t *(*get_up_buffer)(void *hw_data, uint32_t, esp_apptrace_tmo_t *);
    esp_err_t (*put_up_buffer)(void *hw_data, uint8_t *, esp_apptrace_tmo_t *);
    esp_err_t (*flush_up_buffer_nolock)(void *hw_data, uint32_t, esp_apptrace_tmo_t *);
    esp_err_t (*flush_up_buffer)(void *hw_data, esp_apptrace_tmo_t *);
    void (*down_buffer_config)(void *hw_data, uint8_t *buf, uint32_t size);
    uint8_t *(*get_down_buffer)(void *hw_data, uint32_t *, esp_apptrace_tmo_t *);
    esp_err_t (*put_down_buffer)(void *hw_data, uint8_t *, esp_apptrace_tmo_t *);
    bool (*host_is_connected)(void *hw_data);
} esp_apptrace_hw_t;

esp_apptrace_hw_t *esp_apptrace_jtag_hw_get(void **data);
esp_apptrace_hw_t *esp_apptrace_uart_hw_get(int num, void **data);

#ifdef __cplusplus
}
#endif

#endif

