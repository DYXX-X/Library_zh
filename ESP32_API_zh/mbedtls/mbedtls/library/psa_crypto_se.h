/*
 *  PSA加密支持安全元素驱动程序
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

#ifndef PSA_CRYPTO_SE_H
#define PSA_CRYPTO_SE_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "psa/crypto.h"
#include "psa/crypto_se_driver.h"

/** 此实现支持的安全元素的最大位置值。
 *
 * 这不是每个PSA实现所具有的特征，而是由于存储所施加的限制而对当前实现的限制。请参阅#PSA_CRYPTO_SE_DRIVER_ITS_UID_BASE。
 *
 * 与任何PSA实现一样，安全元素的最小位置值为1（0表示透明密钥）。
 */
#define PSA_MAX_SE_LOCATION 255

/** 安全元素驱动程序持久数据的ITS文件标识符范围的基础。
 *
 * 我们使用实现保留范围0xffff0000..0xffffffff的一个切片，特别是0xfffffe00...0xffff。此范围的长度驱动#PSA_MAX_SE_LOCATION的值。实际上没有使用标识符0xfffffe00，因为它对应于没有驱动程序的#PSA_KEY_LOCATION_LOCAL_STORAGE。
 */
#define PSA_CRYPTO_SE_DRIVER_ITS_UID_BASE ( (psa_key_id_t) 0xfffffe00 )

/**已注册的安全元素驱动程序位置的最大数量。*/
#define PSA_MAX_SE_DRIVERS 4

/** 注销所有安全元素驱动程序。
 *
 * \警告库处于初始化状态时不要调用此函数。此函数仅在mbedtls_psa_crypto_free（）结尾处调用。
 */
void psa_unregister_all_se_drivers( void );

/** 初始化所有安全元件驱动程序。
 *
 * 从psa_crypto_init（）调用。
 */
psa_status_t psa_init_all_se_drivers( void );

/** 描述已注册安全元件驱动程序的结构。
 *
 * 安全元素驱动程序表条目包含一个指向驱动程序方法表以及驱动程序上下文结构的指针。
 */
typedef struct psa_se_drv_table_entry_s psa_se_drv_table_entry_t;

/** 返回生命周期值的安全元素驱动程序信息。
 *
 * \param lifetime要查询的生存期值。\param[out]p_methods在输出时，如果存在驱动程序，\c methods将指向其方法表。否则，\c方法为\c NULL。\param[out]p_drv_context在输出时，如果存在驱动程序，\c drv_cntext将指向其上下文结构。否则，\c drv_context为\c NULL。
 *
 * \retval 1\p生存期对应于注册的驱动程序。\retval 0\p生存期与注册的驱动程序不对应。
 */
int psa_get_se_driver( psa_key_lifetime_t lifetime,
                       const psa_drv_se_t **p_methods,
                       psa_drv_se_context_t **p_drv_context);

/** 返回安全元素驱动程序表项的生存期值。
 *
 * \param lifetime要查询的生存期值。
 *
 * \return \p lifetime的驱动程序表项，如果\p lifeth与注册的驱动程序不对应，则返回\p NULL。
 */
psa_se_drv_table_entry_t *psa_get_se_driver_entry(
    psa_key_lifetime_t lifetime );

/** 返回安全元素驱动程序的方法表。
 *
 * \param[in]driver要访问的驱动程序表项，或\c NULL。
 *
 * \return驱动程序的方法表。\如果驱动程序为空，则为空。
 */
const psa_drv_se_t *psa_get_se_driver_methods(
    const psa_se_drv_table_entry_t *driver );

/** 返回安全元素驱动程序的上下文。
 *
 * \param[in]driver要访问的驱动程序表项，或\c NULL。
 *
 * \return指向驱动程序上下文的指针。\如果驱动程序为空，则为空。
 */
psa_drv_se_context_t *psa_get_se_driver_context(
    psa_se_drv_table_entry_t *driver );

/** 为要创建的密钥找到一个空闲插槽。
 *
 * 此函数调用驱动程序中的相关方法，为具有给定属性的键找到合适的槽。
 *
 * \param[in]attributes有关将要创建的密钥的元数据。\param[in]driver要查询的驱动程序表项。\param[out]slot_number成功时，此安全元素中可用的插槽号。
 */
psa_status_t psa_find_se_slot_for_key(
    const psa_key_attributes_t *attributes,
    psa_key_creation_method_t method,
    psa_se_drv_table_entry_t *driver,
    psa_key_slot_number_t *slot_number );

/** 销毁安全元素中的密钥。
 *
 * 此函数调用相关的驱动程序方法来销毁密钥并更新驱动程序的持久数据。
 */
psa_status_t psa_destroy_se_key( psa_se_drv_table_entry_t *driver,
                                 psa_key_slot_number_t slot_number );

/** 加载安全元素驱动程序的持久数据。
 *
 * \paramdriver包含要从存储加载的持久数据的驱动程序表项。
 *
 * \return#PSA_SUCCESS\return#PSAS_ERROR_NOT_SUPPORTED\return#PSA_ERROR_DOES_NOT_EXIST\return#PSA _ERROR_STORAGE_FAILURE\return#PS A_ERROR_DATA_CORRUPT\return#PS A_ERROR_INVALID_ARGUMENT
 */
psa_status_t psa_load_se_persistent_data(
    const psa_se_drv_table_entry_t *driver );

/** 保存安全元素驱动程序的持久数据。
 *
 * \param[in]driver包含要保存到存储的持久数据的驱动程序表项。
 *
 * \return#PSA_SUCCESS\return#PSAS_ERROR_NOT_SUPPORTED\return#PSA_ERROR_NOT_PERMITTED\return#PSA _ERROR-NOT_SUPORTED\return#PS A_ERROR_INSUFFIED_STORAGE\return#S A_ERROR_STORAGE_FAILURE\return#P A_ERROR_INVALID_ARGUMENT
 */
psa_status_t psa_save_se_persistent_data(
    const psa_se_drv_table_entry_t *driver );

/** 销毁安全元素驱动程序的持久数据。
 *
 * 这目前仅用于测试。
 *
 * \param[in]location要擦除其持久数据的驱动程序的位置标识符。
 */
psa_status_t psa_destroy_se_persistent_data( psa_key_location_t location );


/** 密钥的存储表示，其数据位于安全元素中。
 */
typedef struct
{
    uint8_t slot_number[sizeof( psa_key_slot_number_t )];
} psa_se_key_data_storage_t;

#endif /* PSA_CRYPTO_SE_H */

