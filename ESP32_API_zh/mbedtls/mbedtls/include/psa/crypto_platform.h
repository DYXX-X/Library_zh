/**
 * \psa/crypto_platform.h文件
 *
 * \PSA密码模块简介：Mbed TLS平台定义
 *
 * \注意：此文件可能不直接包含。应用程序必须包括psa/crypto.h。
 *
 * 此文件包含依赖于平台的类型定义。
 *
 * 在应用程序和加密模块之间具有隔离的实现中，实现者应注意确保向应用程序公开的定义与模块实现的内容相匹配。
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

#ifndef PSA_CRYPTO_PLATFORM_H
#define PSA_CRYPTO_PLATFORM_H

/* 包括Mbed TLS配置文件，即Mbed TLS在其每个头文件中执行的方式。*/
#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

/* 在经典MBEDTLS_xx特征符号和PSA_xx特征符号之间进行转换。*/
#include "mbedtls/config_psa.h"

/* PSA需要C99在stdint.h中提供的几种类型。*/
#include <stdint.h>

#if ( defined(__ARMCC_VERSION) || defined(_MSC_VER) ) && \
    !defined(inline) && !defined(__cplusplus)
#define inline __inline
#endif

#if defined(MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER)

/* 在PSA平台上为PSA Crypto服务构建，密钥所有者是PSA分区标识符。
 *
 * psa_crypto_storage.c中用于将密钥标识符转换为密钥存储文件名的函数psa_its_identifier_of_slot（）假定mbedtls_key_owner_id_t是32位整数。因此，如果这里不再将mbedtls_key_owner_id_t定义为32位整数，则需要修改此函数。
 */
typedef int32_t mbedtls_key_owner_id_t;

/** 比较两个密钥所有者标识符。
 *
 * \param id1第一个密钥所有者标识符。\param id2第二个密钥所有者标识符。
 *
 * \如果两个密钥所有者标识符相等，则返回非零，否则返回零。
 */
static inline int mbedtls_key_owner_id_equal( mbedtls_key_owner_id_t id1,
                                              mbedtls_key_owner_id_t id2 )
{
    return( id1 == id2 );
}

#endif /* MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER */

/*
 * 当定义MBEDTLS_PSA_CRYPTO_SPM时，正在为SPM（安全分区管理器）集成构建代码，该集成将代码分为两部分：NSPE（非安全处理环境）和SPE（安全处理环境”）。为SPE构建时，应包含一个附加的头文件。
 */
#if defined(MBEDTLS_PSA_CRYPTO_SPM)
#define PSA_CRYPTO_SECURE 1
#include "crypto_spe.h"
#endif // MBEDTLS_PSA_CRYPTO_SPM

#if defined(MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG)
/** 传递给mbedtls_psa_external_get_random（）的上下文类型。
 *
 * 在第一次调用mbedtls_psa_external_get_random（）之前，Mbed TLS将上下文初始化为所有位零。
 *
 * Mbed TLS源代码中对该类型的定义用于演示。mbedtls_psa_external_get_random（）的实现者希望用自定义定义替换它。
 */
typedef struct {
    uintptr_t opaque[2];
} mbedtls_psa_external_random_context_t;
#endif /* MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG */

#endif /* PSA_CRYPTO_PLATFORM_H */

