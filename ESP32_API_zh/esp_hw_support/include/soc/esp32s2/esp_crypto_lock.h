/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * ESP32S2上使用SHA、AES、HMAC和DS加密硬件的所有组件都应使用此API。它们不能并行使用，因为它们使用相同的DMA或相互调用。E、 例如，HMAC使用SHA或DS使用HMAC和AES。有关详细信息，请参阅ESP32S2技术参考手册。
 *
 * 其他无关组件不得使用。
 */

/**
 * 获取AES和SHA加密外围设备的锁，它们都使用加密DMA。
 */
void esp_crypto_dma_lock_acquire(void);

/**
 * 释放AES和SHA加密外围设备的锁，它们都使用加密DMA。
 */
void esp_crypto_dma_lock_release(void);

/**
 * 获取MPI/RSA加密外围设备的锁
 */
void esp_crypto_mpi_lock_acquire(void);

/**
 * 释放MPI/RSA加密外围设备的锁
 */
void esp_crypto_mpi_lock_release(void);

#ifdef __cplusplus
}
#endif

