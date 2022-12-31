// 版权所有2021 Espressif Systems（Shanghai）PTE LTD
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

#include "soc/lldesc.h"
#include "esp_private/gdma.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 在共享加密DMA通道上启动GDMA传输
 *
 * @note 如果尚未分配GDMA信道，将为AES和SHA分配GDMA通道
 *
 * @param input 输入链接列表描述符
 * @param output 输出链接列表描述符
 * @param peripheral 将DMA连接到的加密外围设备，GDMA_TRIG_PERIPH_ARES或GDMA_TLIG_PERIPH_SHA
 * @return esp_err_t esp_FAIL（如果没有可用的GDMA信道）
 */
esp_err_t esp_crypto_shared_gdma_start(const lldesc_t *input, const lldesc_t *output, gdma_trigger_peripheral_t peripheral);


/**
 * @brief 释放任何共享的加密DMA信道，如果在此之后调用esp_crypto_shared_gdma_start，将分配新的gdma信道。
 *
 * @note 函数是从用户代码中调用的，因此使用AES/SHA锁。这意味着不应该从已经使用这些锁的代码中调用该函数，即在AES/SHA代码中。
 *
 *       如果您持续使用AES/SHA（例如，由于wifi连接），则不建议使用此API。释放通道主要用于您完成加密外围设备并需要DMA通道用于其他外围设备的使用情况。例如，在断开WiFi后进行一些处理
 */
void esp_crypto_shared_gdma_free(void);

#ifdef __cplusplus
}
#endif

