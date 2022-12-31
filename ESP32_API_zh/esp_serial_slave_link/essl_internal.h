// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
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

#pragma once
#include <esp_types.h>
#include <esp_err.h>

/** “esp_serial_slave_link”组件使用的上下文。
 */
struct essl_dev_t {
    void* args;

    esp_err_t (*init)(void* ctx, uint32_t wait_ms);

    esp_err_t (*wait_for_ready)(void *ctx, uint32_t wait_ms);
    esp_err_t (*update_tx_buffer_num)(void *ctx, uint32_t wait_ms);
    esp_err_t (*update_rx_data_size)(void *ctx, uint32_t wait_ms);
    esp_err_t (*send_packet)(void *ctx, const void* start, size_t length, uint32_t wait_ms);
    esp_err_t (*get_packet)(void *ctx, void* out_data, size_t size, uint32_t wait_ms);
    esp_err_t (*write_reg)(void *ctx, uint8_t addr, uint8_t value, uint8_t* value_o, uint32_t wait_ms);
    esp_err_t (*read_reg)(void *ctx, uint8_t add, uint8_t *value_o, uint32_t wait_ms);
    esp_err_t (*wait_int)(void *ctx, uint32_t wait_ms);
    esp_err_t (*clear_intr)(void* ctx, uint32_t intr_mask, uint32_t wait_ms);
    esp_err_t (*get_intr)(void* ctx, uint32_t* intr_raw, uint32_t *intr_st, uint32_t wait_ms);
    esp_err_t (*set_intr_ena)(void* ctx, uint32_t ena_mask, uint32_t wait_ms);
    esp_err_t (*get_intr_ena)(void* ctx, uint32_t* ena_mask_o, uint32_t wait_ms);
    esp_err_t (*send_slave_intr)(void* ctx, uint32_t intr_mask, uint32_t wait_ms);

    uint32_t (*get_tx_buffer_num)(void *ctx);
    uint32_t (*get_rx_data_size)(void *ctx);
    void (*reset_cnt)(void *ctx);
};

typedef struct essl_dev_t essl_dev_t;

