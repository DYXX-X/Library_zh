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
 * @brief 获取HMAC加密外围设备的锁
 *
 * 内部也锁定SHA外围设备，因为HMAC依赖于SHA外围
 */
void esp_crypto_hmac_lock_acquire(void);

/**
 * @brief 释放HMAC加密外围设备的锁
 *
 * 内部也会释放SHA外围设备，因为HMAC依赖于SHA外围
 */
void esp_crypto_hmac_lock_release(void);

/**
 * @brief 获取DS加密外围设备的锁
 *
 * 内部还锁定HMAC（锁定SHA）、AES和MPI外围设备，因为DS依赖于这些外围设备
 */
void esp_crypto_ds_lock_acquire(void);

/**
 * @brief 释放DS加密外围设备的锁
 *
 * 内部还释放HMAC（锁定SHA）、AES和MPI外围设备，因为DS依赖于这些外围设备
 */
void esp_crypto_ds_lock_release(void);

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
 * @brief 获取mpi加密外围设备的锁。
 *
 */
void esp_crypto_mpi_lock_acquire(void);

/**
 * @brief 释放mpi/rsa加密外围设备的锁。
 *
 */
void esp_crypto_mpi_lock_release(void);

#ifdef __cplusplus
}
#endif

