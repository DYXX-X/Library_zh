/** \文件psa_crypto_its。h \ brief加密所基于的可信存储的接口。
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

#ifndef PSA_CRYPTO_ITS_H
#define PSA_CRYPTO_ITS_H

#include <stddef.h>
#include <stdint.h>

#include <psa/crypto_types.h>
#include <psa/crypto_values.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \创建数据项时使用的简短标志
 */
typedef uint32_t psa_storage_create_flags_t;

/** \brief用于识别数据的UID的类型
 */
typedef uint64_t psa_storage_uid_t;

#define PSA_STORAGE_FLAG_NONE        0         /**<没有要传递的标志*/
#define PSA_STORAGE_FLAG_WRITE_ONCE (1 << 0) /**<与uid关联的数据将无法修改或删除。用于设置“psa_storage_create_flags_t”中的位`*/

/**
 * \brief与特定uid关联的元数据的容器
 */
struct psa_storage_info_t
{
    uint32_t size;                  /**<与uid关联的数据的大小**/
    psa_storage_create_flags_t flags;    /**<创建uid时设置的标志**/
};

/**表示支持\ref psa_storage_create和\ref pses_storage_set_extended的标志*/
#define PSA_STORAGE_SUPPORT_SET_EXTENDED (1 << 0)

/** \PSA存储特定的简短错误代码
 */
#define PSA_ERROR_INVALID_SIGNATURE     ((psa_status_t)-149)
#define PSA_ERROR_DATA_CORRUPT          ((psa_status_t)-152)

#define PSA_ITS_API_VERSION_MAJOR  1  /**<PSA ITS API的主要版本号。在重大更新（可能包括中断更改）时，它将递增*/
#define PSA_ITS_API_VERSION_MINOR  1  /**<PSA ITS API的次要版本号。它将在不太可能包含中断更改的小更新中递增*/

/**
 * \简要创建新的或修改现有的uid/值对
 *
 * \param[in]uid数据的标识符\param[in]data_length“p_data”中数据的字节大小\param[iin]p_data包含数据的缓冲区\param[in]create_flags数据将使用的标志
 *
 * \return指示操作成功/失败的状态
 *
 * \retval#PSA_SUCCESS操作已成功完成\retval#PSA_ERROR_NOT_PERMITTED操作失败，因为提供的“uid”值已使用PSA_STORAGE_WRITE_ONCE_FLAG\retval#PSA _ERROR_NOT_SUPPORTED创建。操作失败，原因是“create_flags”中提供的一个或多个标志不受支持或无效\retval#PSA_ERROR_INSUFFIE_STORAGE操作失败，因为存储介质上的空间不足\retval#PSA_ERROR_STORAGE_FAILURE操作失败，原因是物理存储失败（致命错误）\retval#PSA_ERROR_INVALID_ARGUMENT操作失败，例如为“NULL”或引用调用方无法访问的内存
 */
psa_status_t psa_its_set(psa_storage_uid_t uid,
                         uint32_t data_length,
                         const void *p_data,
                         psa_storage_create_flags_t create_flags);

/**
 * \brief检索与提供的uid关联的值
 *
 * \param[in]uid uid值\param[in]data_offset请求数据的起始偏移量\param[iin]data_length请求的数据量（以及“p_data”缓冲区的最小分配大小）\param[out]p_data成功完成后将放置数据的缓冲区\param[out]p_data_lengthp_data缓冲区中返回的数据量
 *
 * \return指示操作成功/失败的状态
 *
 * \retval#PSA_SUCCESS操作成功完成\retval#PSA _ERROR_DOES_NOT_EXIST操作失败，因为在存储中找不到提供的“uid”值\retval#PSA_ERROR_storage_FAILURE操作失败，原因是物理存储失败（致命错误）\retval#1PSA_ERROR_DATA_CORRUPT操作失败，是因为存储的数据已损坏\retval#PSA_ERROR_INVALID_ARGUMENT由于提供的指针之一（“p_data”、“p_data_length”）无效，操作失败。例如，“NULL”或引用调用方无法访问的内存。此外，如果提供了无效的偏移量，也可能发生这种情况。
 */
psa_status_t psa_its_get(psa_storage_uid_t uid,
                         uint32_t data_offset,
                         uint32_t data_length,
                         void *p_data,
                         size_t *p_data_length );

/**
 * \brief检索有关所提供uid的元数据
 *
 * \param[in]uid uid值\param[out]p_info指向将用元数据填充的“psa_stage_info_t”结构的指针
 *
 * \return指示操作成功/失败的状态
 *
 * \retval#PSA_SUCCESS操作成功完成\retval#PSTA_ERROR_DOES_NOT_EXIST操作失败，因为在存储中找不到提供的uid值\retval#PSA_ERROR_DATA_CORRUPT操作失败，原因是存储的数据已损坏\retval#1PSA_ERROR_INVALID_ARGUMENT操作失败无效，例如为“NULL”或引用调用方无法访问的内存
 */
psa_status_t psa_its_get_info(psa_storage_uid_t uid,
                              struct psa_storage_info_t *p_info);

/**
 * \brief从存储中删除提供的密钥及其相关数据
 *
 * \param[in]uid uid值
 *
 * \return指示操作成功/失败的状态
 *
 * \retval#PSA_SUCCESS操作成功完成\retval#PSA _ERROR_DOES_NOT_EXIST操作失败，因为在存储中找不到提供的键值\retval#PSA_ERROR_NOT_PERMITTED操作失败，原因是提供的键值是使用PSA_storage_WRITE_ONCE_FLAG\retval#PSA_ERROR_storage_FAILURE创建的物理存储失败（严重错误）
 */
psa_status_t psa_its_remove(psa_storage_uid_t uid);

#ifdef __cplusplus
}
#endif

#endif /* PSA_CRYPTO_ITS_H */

