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
 * ESP32S3上使用SHA、AES、HMAC和DS加密硬件的所有组件都应使用此API。并非所有组件都可以并行使用，因为它们使用相同的底层模块。E、 例如，HMAC使用SHA或DS使用HMAC和AES。有关详细信息，请参阅ESP32S3技术参考手册。
 *
 * 其他无关组件不得使用。
 */

/**
 * @brief 获取数字签名（DS）加密外围设备的锁
 *
 * 内部也采用HMAC锁，因为DS依赖于HMAC外围设备
 */
void esp_crypto_ds_lock_acquire(void);

/**
 * @brief 释放数字签名（DS）加密外围设备的锁
 *
 * 内部也会释放HMAC锁，因为DS依赖于HMAC外围设备
 */
void esp_crypto_ds_lock_release(void);

/**
 * @brief 获取HMAC加密外围设备的锁
 *
 * 内部也采用SHA和AES锁，因为HMAC依赖于SHA外围设备
 */
void esp_crypto_hmac_lock_acquire(void);

/**
 * @brief 释放HMAC加密外围设备的锁
 *
 * 内部也会释放SHA和AES锁，因为HMAC依赖于SHA外围设备
 */
void esp_crypto_hmac_lock_release(void);

/**
 * @brief 获取SHA和AES加密外围设备的锁。
 *
 */
void esp_crypto_sha_aes_lock_acquire(void);

/**
 * @brief 释放SHA和AES加密外围设备的锁。
 *
 */
void esp_crypto_sha_aes_lock_release(void);

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

