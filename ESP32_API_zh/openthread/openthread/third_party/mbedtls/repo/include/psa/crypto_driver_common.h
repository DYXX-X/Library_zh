/**
 * \psa/crypto_driver_common文件。所有PSA加密驱动程序的简要定义
 *
 * 此文件包含所有PSA加密驱动程序共享的通用定义。不要直接包含它：相反，要包含正在实现的驱动程序类型的头文件。例如，如果您正在为一个芯片编写驱动程序，该芯片同时为一些加密算法提供硬件随机生成器和加速器，请包括“psa/crypto_entropy_driver”。h”和“psa/crypto_accel_driver.h”。
 *
 * 该文件是PSA Crypto驱动程序模型的一部分，包含驱动程序开发人员要实现的功能，以使PSA Cryptographic API实现能够以标准化的方式调用硬件。驱动程序作者实现的包含驱动程序模型的函数不打算由应用程序开发人员调用。
 */

/*
 *  版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */
#ifndef PSA_CRYPTO_DRIVER_COMMON_H
#define PSA_CRYPTO_DRIVER_COMMON_H

#include <stddef.h>
#include <stdint.h>

/* 包括类型定义（psa_status_t、psa_algorithm_t、psa_key_type_t等）和宏，以构建和分析这些类型的值。*/
#include "crypto_types.h"
#include "crypto_values.h"

/**对于加密-解密函数，操作是加密还是解密。*/
typedef enum {
    PSA_CRYPTO_DRIVER_DECRYPT,
    PSA_CRYPTO_DRIVER_ENCRYPT
} psa_encrypt_or_decrypt_t;

#endif /* PSA_CRYPTO_DRIVER_COMMON_H */

