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

#pragma once
#include "soc/soc.h"
#include "soc/periph_defs.h"
#include "soc/i2s_struct.h"
#include "soc/i2s_reg.h"
#include "soc/soc_caps.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 存储一堆per-I2S-外围数据。
*/
typedef struct {
    const uint8_t mck_out_sig;

    const uint8_t m_tx_bck_sig;
    const uint8_t m_rx_bck_sig;
    const uint8_t m_tx_ws_sig;
    const uint8_t m_rx_ws_sig;

    const uint8_t s_tx_bck_sig;
    const uint8_t s_rx_bck_sig;
    const uint8_t s_tx_ws_sig;
    const uint8_t s_rx_ws_sig;

    const uint8_t data_out_sig;
    const uint8_t data_in_sig;

    const uint8_t irq;
    const periph_module_t module;
} i2s_signal_conn_t;

extern const i2s_signal_conn_t i2s_periph_signal[SOC_I2S_NUM];

#ifdef __cplusplus
}
#endif

