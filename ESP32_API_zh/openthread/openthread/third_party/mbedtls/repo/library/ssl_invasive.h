/**
 * \ssl_invasive.h文件
 *
 * \简短的SSL模块：仅用于侵入性测试的接口。
 *
 * 本文件中的接口仅用于测试目的。它们不应在库集成中可用，除非构建库进行测试。
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
#ifndef MBEDTLS_SSL_INVASIVE_H
#define MBEDTLS_SSL_INVASIVE_H

#include "common.h"
#include "mbedtls/md.h"

#if defined(MBEDTLS_TEST_HOOKS) &&              \
    defined(MBEDTLS_SSL_SOME_SUITES_USE_TLS_CBC)
/** \简要计算具有恒定流量的可变长度数据的HMAC。
 *
 * 此函数计算add_data和数据级联的HMAC，并使用不依赖于data_len_secret但仅依赖于min_data_len和max_data_ln的代码流和内存访问模式。特别是，此函数始终从数据中精确读取\p max_data_len字节。
 *
 * \param ctx HMAC上下文。它必须使用mbedtls_md_hmac_starts（）配置密钥，并使用以下哈希之一：SHA-384、SHA-256、SHA-1或md-5。计算完成后，将使用mbedtls _md_hmc_reset（）重置密钥，以准备下一次计算。\param add_data附加到\p数据的附加数据。这必须指向\p add_data_len字节的可读缓冲区。\param add_data_len add_data的长度（以字节为单位）。\param data附加到\p add_data的数据。这必须指向\p max_data_len字节的可读缓冲区。\param data_len_secret数据中要处理的数据的长度。这必须不小于\p min_data_len且不大于\p max_data_ln。\param min_data_len数据的最小长度（字节）。\param max_data_len数据的最大长度（字节）。\param output将在此处写入HMAC。这必须指向大小足以容纳HMAC值的可写缓冲区。
 *
 * \retval 0成功。\retval MBEDTLS_ERROR_PLATFORM_HW_ACCEL_FAILED硬件加速器失败。
 */
int mbedtls_ssl_cf_hmac(
        mbedtls_md_context_t *ctx,
        const unsigned char *add_data, size_t add_data_len,
        const unsigned char *data, size_t data_len_secret,
        size_t min_data_len, size_t max_data_len,
        unsigned char *output );

/** \brief从一个秘密位置以恒定的流量复制数据。
 *
 * 此函数使用代码流和内存访问模式将\p len字节从\p src_base+\p offset_secret复制到\p dst，该模式不依赖于\p offset _secret，而仅依赖于\poffset_min、\p offset_max和\p len。
 *
 * \param dst目标缓冲区。这必须指向至少为\plen字节的可写缓冲区。\param src_base源缓冲区的基。这必须指向至少为\p offset_max+\p len字节的可读缓冲区。\param offset_secret要从中复制的源缓冲区中的偏移量。该值必须不小于\p offset_min且不大于\p offset _max。\param offset_min \p offset_secret的最小值。\param offset_max \p offset_secret的最大值。\param len要复制的字节数。
 */
void mbedtls_ssl_cf_memcpy_offset( unsigned char *dst,
                                   const unsigned char *src_base,
                                   size_t offset_secret,
                                   size_t offset_min, size_t offset_max,
                                   size_t len );
#endif /* MBEDTLS_TEST_HOOKS && MBEDTLS_SSL_SOME_SUITES_USE_TLS_CBC */

#endif /* MBEDTLS_SSL_INVASIVE_H */

