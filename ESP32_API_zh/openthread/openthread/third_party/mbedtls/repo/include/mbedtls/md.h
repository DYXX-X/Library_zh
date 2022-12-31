 /**
 * \文件md.h
 *
 * \brief此文件包含通用消息摘要包装器。
 *
 * \作者Adrian de Jong<dejong@fox-it.com>
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

#ifndef MBEDTLS_MD_H
#define MBEDTLS_MD_H

#include <stddef.h>

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#define MBEDTLS_ERR_MD_FEATURE_UNAVAILABLE                -0x5080  /**<所选功能不可用。*/
#define MBEDTLS_ERR_MD_BAD_INPUT_DATA                     -0x5100  /**<功能输入参数错误。*/
#define MBEDTLS_ERR_MD_ALLOC_FAILED                       -0x5180  /**<分配内存失败。*/
#define MBEDTLS_ERR_MD_FILE_IO_ERROR                      -0x5200  /**<打开或读取文件失败。*/

/* MBEDTLS_ERROR_MD_HW_ACCEL_FAILED已弃用，不应使用。*/
#define MBEDTLS_ERR_MD_HW_ACCEL_FAILED                    -0x5280  /**<MD硬件加速器失败。*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \简短支持的消息摘要。
 *
 * \警告MD2、MD4、MD5和SHA-1被认为是弱消息摘要，它们的使用构成了安全风险。我们建议考虑使用更强的消息摘要。
 *
 */
typedef enum {
    MBEDTLS_MD_NONE=0,    /**<无。*/
    MBEDTLS_MD_MD2,       /**<MD2消息摘要。*/
    MBEDTLS_MD_MD4,       /**<MD4消息摘要。*/
    MBEDTLS_MD_MD5,       /**<MD5消息摘要。*/
    MBEDTLS_MD_SHA1,      /**<SHA-1消息摘要。*/
    MBEDTLS_MD_SHA224,    /**<SHA-224消息摘要。*/
    MBEDTLS_MD_SHA256,    /**<SHA-256消息摘要。*/
    MBEDTLS_MD_SHA384,    /**<SHA-384消息摘要。*/
    MBEDTLS_MD_SHA512,    /**<SHA-512消息摘要。*/
    MBEDTLS_MD_RIPEMD160, /**<RIPEMD-160消息摘要。*/
} mbedtls_md_type_t;

#if defined(MBEDTLS_SHA512_C)
#define MBEDTLS_MD_MAX_SIZE         64  /* 已知最长的是SHA512*/
#else
#define MBEDTLS_MD_MAX_SIZE         32  /* 已知最长的是SHA256或更少*/
#endif

#if defined(MBEDTLS_SHA512_C)
#define MBEDTLS_MD_MAX_BLOCK_SIZE         128
#else
#define MBEDTLS_MD_MAX_BLOCK_SIZE         64
#endif

/**
 * md_internal.h中定义的不透明结构。
 */
typedef struct mbedtls_md_info_t mbedtls_md_info_t;

/**
 * 通用消息摘要上下文。
 */
typedef struct mbedtls_md_context_t
{
    /**有关关联消息摘要的信息。*/
    const mbedtls_md_info_t *md_info;

    /**摘要特定上下文。*/
    void *md_ctx;

    /**上下文的HMAC部分。*/
    void *hmac_ctx;
} mbedtls_md_context_t;

/**
 * \brief此函数返回通用摘要模块支持的摘要列表。
 *
 * \注意：列表以可用的最强哈希开头。
 *
 * \return静态分配的摘要数组。返回列表中的每个元素都是属于消息摘要枚举#mbedtls_md_type_t的整数。最后一个条目是0。
 */
const int *mbedtls_md_list( void );

/**
 * \brief此函数返回与给定摘要名称关联的消息摘要信息。
 *
 * \param md_name要搜索的摘要的名称。
 *
 * \return与\p md_name关联的消息摘要信息。\如果找不到关联的消息摘要信息，则返回NULL。
 */
const mbedtls_md_info_t *mbedtls_md_info_from_string( const char *md_name );

/**
 * \brief此函数返回与给定摘要类型相关联的消息摘要信息。
 *
 * \param md_type要搜索的摘要类型。
 *
 * \return与\p md_type关联的消息摘要信息。\如果找不到关联的消息摘要信息，则返回NULL。
 */
const mbedtls_md_info_t *mbedtls_md_info_from_type( mbedtls_md_type_t md_type );

/**
 * \brief此函数初始化消息摘要上下文，而不将其绑定到特定的消息摘要算法。
 *
 *                  应始终首先调用此函数。它为mbedtls_md_setup（）准备上下文，以便将其绑定到消息摘要算法。
 */
void mbedtls_md_init( mbedtls_md_context_t *ctx );

/**
 * \brief此函数清除\p ctx的内部结构并释放任何嵌入的内部结构，但不会释放\p ctx本身。
 *
 *                  如果在\p ctx上调用了mbedtls_md_setup（），则在不再使用上下文时必须调用mbedtls-md_free（）。如果您以前调用过mbedtls_md_init（），则调用此函数，其他任何操作都是可选的。如果尚未调用mbedtls_md_init（），则不能调用此函数。
 */
void mbedtls_md_free( mbedtls_md_context_t *ctx );

#if ! defined(MBEDTLS_DEPRECATED_REMOVED)
#if defined(MBEDTLS_DEPRECATED_WARNING)
#define MBEDTLS_DEPRECATED    __attribute__((deprecated))
#else
#define MBEDTLS_DEPRECATED
#endif
/**
 * \brief此函数选择要使用的消息摘要算法，并分配内部结构。
 *
 *                  它应该在mbedtls_md_init（）或mbedtls-md_free（）之后调用。使得以后需要调用mbedtls_md_free（）。
 *
 * \已弃用在2.0.0中被mbedtls_md_setup（）取代
 *
 * \param ctx要设置的上下文。\param md_info要使用的消息摘要算法的信息结构。
 *
 * \成功时返回\c 0。\参数验证失败时返回#MBEDTLS_ERROR_MD_BAD_INPUT_DATA。\内存分配失败时返回#MBEDTLS_ERROR_MD_ALLOC_FAILED。
 */
int mbedtls_md_init_ctx( mbedtls_md_context_t *ctx, const mbedtls_md_info_t *md_info ) MBEDTLS_DEPRECATED;
#undef MBEDTLS_DEPRECATED
#endif /* MBEDTLS_DEPRECATED_REMOVED */

/**
 * \brief此函数选择要使用的消息摘要算法，并分配内部结构。
 *
 *                  它应该在mbedtls_md_init（）或mbedtls-md_free（）之后调用。使得以后需要调用mbedtls_md_free（）。
 *
 * \param ctx要设置的上下文。\param md_info要使用的消息摘要算法的信息结构。\param hmac定义是否使用hmac。0:未使用HMAC（节省一些内存），或非零：HMAC与此上下文一起使用。
 *
 * \成功时返回\c 0。\参数验证失败时返回#MBEDTLS_ERROR_MD_BAD_INPUT_DATA。\内存分配失败时返回#MBEDTLS_ERROR_MD_ALLOC_FAILED。
 */
int mbedtls_md_setup( mbedtls_md_context_t *ctx, const mbedtls_md_info_t *md_info, int hmac );

/**
 * \brief此函数克隆消息摘要上下文的状态。
 *
 * \注意：在调用此函数之前，必须在\c dst上调用mbedtls_md_setup（）。
 *
 * \注意：这两个上下文必须具有相同的类型，例如，都是SHA-256。
 *
 * \warning此函数克隆消息摘要状态，而不是HMAC状态。
 *
 * \param dst目标上下文。\param src要克隆的上下文。
 *
 * \成功时返回\c 0。\参数验证失败时返回#MBEDTLS_ERROR_MD_BAD_INPUT_DATA。
 */
int mbedtls_md_clone( mbedtls_md_context_t *dst,
                      const mbedtls_md_context_t *src );

/**
 * \brief此函数从消息摘要信息结构中提取消息摘要大小。
 *
 * \param md_info要使用的消息摘要算法的信息结构。
 *
 * \return消息摘要输出的大小（字节）。
 */
unsigned char mbedtls_md_get_size( const mbedtls_md_info_t *md_info );

/**
 * \brief此函数从消息摘要信息结构中提取消息摘要类型。
 *
 * \param md_info要使用的消息摘要算法的信息结构。
 *
 * \return消息摘要的类型。
 */
mbedtls_md_type_t mbedtls_md_get_type( const mbedtls_md_info_t *md_info );

/**
 * \brief此函数从消息摘要信息结构中提取消息摘要名称。
 *
 * \param md_info要使用的消息摘要算法的信息结构。
 *
 * \return消息摘要的名称。
 */
const char *mbedtls_md_get_name( const mbedtls_md_info_t *md_info );

/**
 * \brief此函数启动消息摘要计算。
 *
 *                  必须在使用mbedtls_md_setup（）设置上下文之后，以及使用mbedtls _md_update（）传递数据之前调用此函数。
 *
 * \param ctx通用消息摘要上下文。
 *
 * \成功时返回\c 0。\参数验证失败时返回#MBEDTLS_ERROR_MD_BAD_INPUT_DATA。
 */
int mbedtls_md_starts( mbedtls_md_context_t *ctx );

/**
 * \brief此函数将输入缓冲区馈送到正在进行的消息摘要计算中。
 *
 *                  在调用此函数之前，必须调用mbedtls_md_starts（）。您可以多次调用此函数。然后，调用mbedtls_md_finish（）。
 *
 * \param ctx通用消息摘要上下文。\param input保存输入数据的缓冲区。\param ilen输入数据的长度。
 *
 * \成功时返回\c 0。\参数验证失败时返回#MBEDTLS_ERROR_MD_BAD_INPUT_DATA。
 */
int mbedtls_md_update( mbedtls_md_context_t *ctx, const unsigned char *input, size_t ilen );

/**
 * \brief此函数完成摘要操作，并将结果写入输出缓冲区。
 *
 *                  在调用mbedtls_md_starts（）之后调用此函数，然后调用任意次数的mbedtls-md_update（）。然后，您可以使用mbedtls_md_free（）清除上下文，或者调用mbedtls-md_starts（）以使用相同的算法将上下文重新用于另一个摘要操作。
 *
 * \param ctx通用消息摘要上下文。\param output通用消息摘要校验和结果的缓冲区。
 *
 * \成功时返回\c 0。\参数验证失败时返回#MBEDTLS_ERROR_MD_BAD_INPUT_DATA。
 */
int mbedtls_md_finish( mbedtls_md_context_t *ctx, unsigned char *output );

/**
 * \brief此函数计算缓冲区的消息摘要，相对于单个调用中的可配置消息摘要算法。
 *
 *                 结果计算为Output=message_digest（输入缓冲区）。
 *
 * \param md_info要使用的消息摘要算法的信息结构。\param input保存数据的缓冲区。\param ilen输入数据的长度。\param output通用消息摘要校验和结果。
 *
 * \成功时返回\c 0。\参数验证失败时返回#MBEDTLS_ERROR_MD_BAD_INPUT_DATA。
 */
int mbedtls_md( const mbedtls_md_info_t *md_info, const unsigned char *input, size_t ilen,
        unsigned char *output );

#if defined(MBEDTLS_FS_IO)
/**
 * \brief此函数计算所提供文件内容的消息摘要校验和结果。
 *
 *                 结果计算为Output=message_digest（文件内容）。
 *
 * \param md_info要使用的消息摘要算法的信息结构。\param path输入文件名。\param output通用消息摘要校验和结果。
 *
 * \成功时返回\c 0。\访问路径指向的文件时发生I/O错误，返回#MBEDTLS_ERROR_MD_FILE_IO_ERROR。\如果\n MD_info为NULL，则返回#MBEDTLS_ERROR_MD_BAD_INPUT_DATA。
 */
int mbedtls_md_file( const mbedtls_md_info_t *md_info, const char *path,
                     unsigned char *output );
#endif /* MBEDTLS_FS_IO */

/**
 * \brief此功能设置HMAC密钥并准备验证新消息。
 *
 *                  在mbedtls_md_setup（）之后调用此函数，将md上下文用于HMAC计算，然后调用mbedtls_md_HMAC_update（）提供输入数据，并调用mbedtls _md_HMAC_finish（）获取HMAC值。
 *
 * \param ctx包含嵌入式HMAC上下文的消息摘要上下文。\param key HMAC密钥。\param keylen HMAC密钥的长度（以字节为单位）。
 *
 * \成功时返回\c 0。\参数验证失败时返回#MBEDTLS_ERROR_MD_BAD_INPUT_DATA。
 */
int mbedtls_md_hmac_starts( mbedtls_md_context_t *ctx, const unsigned char *key,
                    size_t keylen );

/**
 * \brief此函数将输入缓冲区输入到正在进行的HMAC计算中。
 *
 *                  在调用此函数之前，请调用mbedtls_md_hmac_starts（）或mbedtls-md_hmac_reset（）。您可以多次调用此函数来分段传递输入。然后，调用mbedtls_md_hmac_finish（）。
 *
 * \param ctx包含嵌入式HMAC上下文的消息摘要上下文。\param input保存输入数据的缓冲区。\param ilen输入数据的长度。
 *
 * \成功时返回\c 0。\参数验证失败时返回#MBEDTLS_ERROR_MD_BAD_INPUT_DATA。
 */
int mbedtls_md_hmac_update( mbedtls_md_context_t *ctx, const unsigned char *input,
                    size_t ilen );

/**
 * \brief此函数完成HMAC操作，并将结果写入输出缓冲区。
 *
 *                  在mbedtls_md_hmac_starts（）和mbedtls-md_hmac_update（）之后调用此函数以获取hmac值。然后，您可以调用mbedtls_md_free（）来清除上下文，或者调用mbedtls _md_hmac_reset（）来使用相同的hmac密钥重用上下文。
 *
 * \param ctx包含嵌入式HMAC上下文的消息摘要上下文。\param output通用HMAC校验和结果。
 *
 * \成功时返回\c 0。\参数验证失败时返回#MBEDTLS_ERROR_MD_BAD_INPUT_DATA。
 */
int mbedtls_md_hmac_finish( mbedtls_md_context_t *ctx, unsigned char *output);

/**
 * \brief此功能准备使用与先前HMAC操作相同的密钥验证新消息。
 *
 *                  可以在mbedtls_md_hmac_finish（）之后调用此函数。然后调用mbedtls_md_hmac_update（）传递新输入。
 *
 * \param ctx包含嵌入式HMAC上下文的消息摘要上下文。
 *
 * \成功时返回\c 0。\参数验证失败时返回#MBEDTLS_ERROR_MD_BAD_INPUT_DATA。
 */
int mbedtls_md_hmac_reset( mbedtls_md_context_t *ctx );

/**
 * \brief此函数使用提供的键计算输入缓冲区上的完整通用HMAC。
 *
 *                 该函数分配上下文、执行计算并释放上下文。
 *
 *                 HMAC结果计算为输出=通用HMAC（HMAC键，输入缓冲区）。
 *
 * \param md_info要使用的消息摘要算法的信息结构。\param key HMAC密钥。\param keylen HMAC密钥的长度（以字节为单位）。\param input保存输入数据的缓冲区。\param ilen输入数据的长度。\param output通用HMAC结果。
 *
 * \成功时返回\c 0。\参数验证失败时返回#MBEDTLS_ERROR_MD_BAD_INPUT_DATA。
 */
int mbedtls_md_hmac( const mbedtls_md_info_t *md_info, const unsigned char *key, size_t keylen,
                const unsigned char *input, size_t ilen,
                unsigned char *output );

/* 内部使用*/
int mbedtls_md_process( mbedtls_md_context_t *ctx, const unsigned char *data );

#ifdef __cplusplus
}
#endif

#endif /* MBEDTLS_MD_H */

