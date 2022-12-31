/*
 *  版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef PSA_CRYPTO_SERVICE_INTEGRATION_H
#define PSA_CRYPTO_SERVICE_INTEGRATION_H

/*
 * 当定义MBEDTLS_PSA_CRYPTO_SPM时，正在为SPM（安全分区管理器）集成构建代码，该集成将代码分为两部分：NSPE（非安全处理环境）和SPE（安全处理环境”）。为SPE构建时，应包含一个附加的头文件。
 */
#if defined(MBEDTLS_PSA_CRYPTO_SPM)
/*
 * PSA_CRYPTO_SECURE表示包含此文件的文件正在为SPE编译。文件crypt_structs。h和crypto_ type。h对于NSPE和SPE有不同的实现，并根据此标志进行编译。
 */
#define PSA_CRYPTO_SECURE 1
#include "crypto_spe.h"
#endif // MBEDTLS_PSA_CRYPTO_SPM

#endif // PSA_CRYPTO_SERVICE_INTEGRATION_H

