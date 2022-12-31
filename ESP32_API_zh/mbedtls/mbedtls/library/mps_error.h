/*
 *  版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 *  此文件是mbed TLS的一部分(https://tls.mbed.org)
 */

/**
 * \文件mps_error.h
 *
 * \MPS使用的简短错误代码
 */

#ifndef MBEDTLS_MPS_ERROR_H
#define MBEDTLS_MPS_ERROR_H


/* TODO:需要重新访问错误代码分配：
 *
 * -我们是否应该公开（部分）MPS Reader错误代码？如果是这样，我们需要调整MBEDTLS_MPS_READER_MAKE_ERROR（），以在Mbed TLS公共错误空间中找到一个缺口。如果没有，我们必须确保不会在公共API级别转发这些错误——只要MPS是一个无法从公共API访问的实验组件，目前就没有风险。
 */

/**
 * \name SECTION:MPS常规错误代码
 *
 * \{
 */

#ifndef MBEDTLS_MPS_ERR_BASE
#define MBEDTLS_MPS_ERR_BASE ( 0 )
#endif

#define MBEDTLS_MPS_MAKE_ERROR(code) \
    ( -( MBEDTLS_MPS_ERR_BASE | (code) ) )

#define MBEDTLS_ERR_MPS_OPERATION_UNEXPECTED  MBEDTLS_MPS_MAKE_ERROR( 0x1 )
#define MBEDTLS_ERR_MPS_INTERNAL_ERROR        MBEDTLS_MPS_MAKE_ERROR( 0x2 )

/* \}name SECTION:MPS常规错误代码*/

/**
 * \name SECTION:MPS读取器错误代码
 *
 * \{
 */

#ifndef MBEDTLS_MPS_READER_ERR_BASE
#define MBEDTLS_MPS_READER_ERR_BASE ( 1 << 8 )
#endif

#define MBEDTLS_MPS_READER_MAKE_ERROR(code) \
    ( -( MBEDTLS_MPS_READER_ERR_BASE | (code) ) )

/*! 尝试从读取器回收数据缓冲区失败，因为用户尚未读取并提交所有数据。*/
#define MBEDTLS_ERR_MPS_READER_DATA_LEFT             MBEDTLS_MPS_READER_MAKE_ERROR( 0x1 )

/*! 传递给读取器的参数无效。*/
#define MBEDTLS_ERR_MPS_READER_INVALID_ARG           MBEDTLS_MPS_READER_MAKE_ERROR( 0x2 )

/*! 暂停后尝试通过mbedtls_mps_reader_feed（）将读取器移动到消费模式失败，因为提供的数据不足以满足导致暂停的读取请求。*/
#define MBEDTLS_ERR_MPS_READER_NEED_MORE             MBEDTLS_MPS_READER_MAKE_ERROR( 0x3 )

/*! 获取请求失败，因为读取器中没有足够的数据可用。*/
#define MBEDTLS_ERR_MPS_READER_OUT_OF_DATA           MBEDTLS_MPS_READER_MAKE_ERROR( 0x4 )

/*!< 暂停并重新激活读取器后的获取请求失败，因为该请求与暂停前的请求不一致。暂停并重新激活读取器后，用户不得更改其“策略”。*/
#define MBEDTLS_ERR_MPS_READER_INCONSISTENT_REQUESTS MBEDTLS_MPS_READER_MAKE_ERROR( 0x5 )

/*! 尝试从读卡器回收数据缓冲区失败，因为读卡器没有可用于备份未处理数据的累加器。*/
#define MBEDTLS_ERR_MPS_READER_NEED_ACCUMULATOR      MBEDTLS_MPS_READER_MAKE_ERROR( 0x6 )

/*! 试图从读取器回收数据缓冲区失败，因为传递给读取器的累加器不够大，无法容纳尚未处理的数据和上一次读取请求的多余数据。*/
#define MBEDTLS_ERR_MPS_READER_ACCUMULATOR_TOO_SMALL MBEDTLS_MPS_READER_MAKE_ERROR( 0x7 )

/* \}name SECTION:MPS读取器错误代码*/

#endif /* MBEDTLS_MPS_ERROR_H */

