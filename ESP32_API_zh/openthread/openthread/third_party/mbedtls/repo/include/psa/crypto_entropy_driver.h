/**
 * \psa/crypto_entropy_driver文件。简要PSA熵源驱动模块
 *
 * 此标头声明了熵源的类型和函数签名。
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
#ifndef PSA_CRYPTO_ENTROPY_DRIVER_H
#define PSA_CRYPTO_ENTROPY_DRIVER_H

#include "crypto_driver_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup driver_ng熵生成
 */
/**@{*/

/** \brief初始化熵驱动程序
 *
 * \param[in，out]p_context包含实现的任何上下文信息的硬件特定结构
 *
 * \retval#PSA_SUCCESS
 */
typedef psa_status_t (*psa_drv_entropy_init_t)(void *p_context);

/** \brief从熵源中获取指定数量的比特
 *
 * 它从熵源检索“buffer_size”字节的数据。熵源将始终将所提供的缓冲区填充到其全部大小，然而，大多数熵源具有偏差，并且缓冲区中包含的实际熵量将小于字节数。驱动程序将以“p_received_entropy_bytes”的形式返回放置在缓冲区中的实际熵字节数。PSA Crypto API实现可能会将此函数的输出馈送到数字随机位生成器（DRBG）中，并且通常具有所需的最小熵量。为了实现这一点，PSA Crypto实现应该设计为多次调用该函数，直到它从熵源接收到所需的熵量。
 *
 * \param[in，out]p_context包含实现的任何上下文信息的硬件特定结构\param[in]p_buffer调用方分配的缓冲区，用于将检索到的熵放入\param[iin]buffer_size“p_buffer”的分配大小\param[out]p_received_entropy_bits“p_buff”中实际提供的熵量（以位为单位）`
 *
 * \retval#PSA_SUCCESS
 */
typedef psa_status_t (*psa_drv_entropy_get_bits_t)(void *p_context,
                                                   uint8_t *p_buffer,
                                                   uint32_t buffer_size,
                                                   uint32_t *p_received_entropy_bits);

/**
 * \brief包含与熵源接口所需的所有函数指针的结构
 *
 * PSA Crypto API实现应在启动时适当填充表的实例。
 *
 * 如果其中一个函数未实现，则应将其设置为NULL。
 */
typedef struct {
    /**熵上下文的驱动程序特定大小*/
    const size_t                context_size;
    /**为熵源执行初始化的函数*/
    psa_drv_entropy_init_t      p_init;
    /**为熵源执行get_bits操作的函数*/
    psa_drv_entropy_get_bits_t  p_get_bits;
} psa_drv_entropy_t;
/**@}*/

#ifdef __cplusplus
}
#endif

#endif /* PSA_CRYPTO_ENTROPY_DRIVER_H */

