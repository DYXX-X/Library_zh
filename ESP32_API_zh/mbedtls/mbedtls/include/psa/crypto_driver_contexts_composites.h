/*
 *  用于PSA驱动程序包装器接口的上下文结构声明。此文件包含“复合”操作的上下文结构，即需要使用原语中其他操作的操作（crypto_driver_contexts_primits.h）
 *
 *  警告：此文件将在将来自动生成。
 *
 * \注意：此文件可能不直接包含。应用程序必须包括psa/crypto.h。
 *
 * \注意：此标头及其内容不是Mbed TLS API的一部分，应用程序不能依赖它。其主要目的是定义包含在加密库中的PSA驱动程序的多部分状态对象。crypt_struct使用这些对象的定义。h定义PSA多部件状态对象的实现定义类型。
 */
/*  版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef PSA_CRYPTO_DRIVER_CONTEXTS_COMPOSITES_H
#define PSA_CRYPTO_DRIVER_CONTEXTS_COMPOSITES_H

#include "psa/crypto_driver_common.h"

/* 包括Mbed TLS软件驱动程序的上下文结构定义*/
#include "psa/crypto_builtin_composites.h"

/* 包括在自动生成过程中声明的驱动程序的上下文结构定义。*/

#if defined(MBEDTLS_TEST_LIBTESTDRIVER1)
#include <libtestdriver1/include/psa/crypto.h>
#endif

#if defined(PSA_CRYPTO_DRIVER_TEST)
#if defined(MBEDTLS_TEST_LIBTESTDRIVER1) && \
    defined(LIBTESTDRIVER1_MBEDTLS_PSA_BUILTIN_MAC)
typedef libtestdriver1_mbedtls_psa_mac_operation_t
        mbedtls_transparent_test_driver_mac_operation_t;
typedef libtestdriver1_mbedtls_psa_mac_operation_t
        mbedtls_opaque_test_driver_mac_operation_t;

#define MBEDTLS_TRANSPARENT_TEST_DRIVER_MAC_OPERATION_INIT \
        LIBTESTDRIVER1_MBEDTLS_PSA_MAC_OPERATION_INIT
#define MBEDTLS_OPAQUE_TEST_DRIVER_MAC_OPERATION_INIT \
        LIBTESTDRIVER1_MBEDTLS_PSA_MAC_OPERATION_INIT

#else
typedef mbedtls_psa_mac_operation_t
        mbedtls_transparent_test_driver_mac_operation_t;
typedef mbedtls_psa_mac_operation_t
        mbedtls_opaque_test_driver_mac_operation_t;

#define MBEDTLS_TRANSPARENT_TEST_DRIVER_MAC_OPERATION_INIT \
        MBEDTLS_PSA_MAC_OPERATION_INIT
#define MBEDTLS_OPAQUE_TEST_DRIVER_MAC_OPERATION_INIT \
        MBEDTLS_PSA_MAC_OPERATION_INIT

#endif /* MBEDTLS_TEST_LIBTESTDRIVER1 */
#endif /* PSA_CRYPTO_DRIVER_TEST */

/* 将用于通过PSA驱动程序包装层执行的操作的上下文定义为所有可能的驱动程序上下文的联合。
 *
 * 联合成员是驱动程序的上下文结构，成员名称的格式为“驱动程序名称”_ctx。这允许程序生成该文件和psa_crypto_driver_wrappers的内容。c*/

typedef union {
    unsigned dummy; /* 确保此联合始终为非空*/
    mbedtls_psa_mac_operation_t mbedtls_ctx;
#if defined(PSA_CRYPTO_DRIVER_TEST)
    mbedtls_transparent_test_driver_mac_operation_t transparent_test_driver_ctx;
    mbedtls_opaque_test_driver_mac_operation_t opaque_test_driver_ctx;
#endif
} psa_driver_mac_context_t;

#endif /* PSA_CRYPTO_DRIVER_CONTEXTS_COMPOSITES_H */
/* 自动生成文件的结尾。*/

