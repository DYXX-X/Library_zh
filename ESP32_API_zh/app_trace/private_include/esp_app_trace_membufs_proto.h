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
#ifndef ESP_APP_TRACE_MEMBUFS_PROTO_H_
#define ESP_APP_TRACE_MEMBUFS_PROTO_H_

#include "esp_app_trace_util.h"

#ifdef __cplusplus
extern "C" {
#endif

/**TRAX HW传输状态*/
typedef struct {
    uint32_t                   in_block;     // 输入块ID
    // TODO:更改为uint16_t
    uint32_t                   markers[2];   // 块填充水平标记
} esp_apptrace_membufs_state_t;

/**内存块参数，应该打包，因为它是从主机读取的*/
typedef struct {
    uint8_t   *start;   // 起始地址
    uint32_t   sz;      // 大小
} esp_apptrace_mem_block_t;

typedef struct {
    esp_err_t (*swap_start)(uint32_t curr_block_id);
    esp_err_t (*swap)(uint32_t new_block_id);
    esp_err_t (*swap_end)(uint32_t new_block_id, uint32_t prev_block_len);
    bool (*host_data_pending)(void);
} esp_apptrace_membufs_proto_hw_t;

typedef struct {
    esp_apptrace_membufs_proto_hw_t *       hw;
    volatile esp_apptrace_membufs_state_t   state;       // 状态
    esp_apptrace_mem_block_t                blocks[2];   // 存储器块
#if CONFIG_APPTRACE_PENDING_DATA_SIZE_MAX > 0
    // 挂起用户块的环形缓冲区控制结构
    esp_apptrace_rb_t                   rb_pend;
    // 挂起用户块的存储
    uint8_t                             pending_data[CONFIG_APPTRACE_PENDING_DATA_SIZE_MAX + 1];
#endif
    // 主机数据的环形缓冲区控制结构（下行缓冲区）
    esp_apptrace_rb_t                       rb_down;
} esp_apptrace_membufs_proto_data_t;

esp_err_t esp_apptrace_membufs_init(esp_apptrace_membufs_proto_data_t *proto, const esp_apptrace_mem_block_t blocks_cfg[2]);
void esp_apptrace_membufs_down_buffer_config(esp_apptrace_membufs_proto_data_t *data, uint8_t *buf, uint32_t size);
uint8_t *esp_apptrace_membufs_down_buffer_get(esp_apptrace_membufs_proto_data_t *proto, uint32_t *size, esp_apptrace_tmo_t *tmo);
esp_err_t esp_apptrace_membufs_down_buffer_put(esp_apptrace_membufs_proto_data_t *proto, uint8_t *ptr, esp_apptrace_tmo_t *tmo);
uint8_t *esp_apptrace_membufs_up_buffer_get(esp_apptrace_membufs_proto_data_t *proto, uint32_t size, esp_apptrace_tmo_t *tmo);
esp_err_t esp_apptrace_membufs_up_buffer_put(esp_apptrace_membufs_proto_data_t *proto, uint8_t *ptr, esp_apptrace_tmo_t *tmo);
esp_err_t esp_apptrace_membufs_flush_nolock(esp_apptrace_membufs_proto_data_t *proto, uint32_t min_sz, esp_apptrace_tmo_t *tmo);

#ifdef __cplusplus
}
#endif

#endif

