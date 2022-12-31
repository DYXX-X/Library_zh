/**
 * \文件psa_crypto_storage.h
 *
 * \简短的PSA加密模块：Mbed TLS密钥存储
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

#ifndef PSA_CRYPTO_STORAGE_H
#define PSA_CRYPTO_STORAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "psa/crypto.h"
#include "psa/crypto_se_driver.h"

#include <stdint.h>
#include <string.h>

/* 限制存储中的最大密钥大小。这应该没有任何影响，因为密钥大小在内存中受到限制。*/
#define PSA_CRYPTO_MAX_STORAGE_SIZE ( PSA_BITS_TO_BYTES( PSA_MAX_KEY_BITS ) )
/* 健康检查：文件大小必须符合32位。允许64kB的元数据。*/
#if PSA_CRYPTO_MAX_STORAGE_SIZE > 0xffff0000
#error PSA_CRYPTO_MAX_STORAGE_SIZE > 0xffff0000
#endif

/** 允许的最大永久插槽数。
 *
 * 在Mbed Crypto 0.1.0b中：
 * -使用文件后端，除0外，所有密钥ID都正常。
 * -使用ITS后端，除0xFFFFFF52（#PSA_CRYPTO_ITS_RANDOM_SEED_UID）外，所有密钥ID都正常，文件中包含设备的随机种子（如果启用了此功能）。
 * -实际上只使用从1到#MBEDTLS_PSA_key_SLOT_COUNT的密钥ID。
 *
 * 因为我们需要保留随机种子，所以避免使用该密钥槽。预留一整套钥匙槽，以防出现其他问题。
 *
 * 当我们为密钥存储实现客户端分离时，这个限制可能会变得毫无意义。
 */
#define PSA_MAX_PERSISTENT_KEY_IDENTIFIER PSA_KEY_ID_VENDOR_MAX

/**
 * \brief检查是否为给定的钥匙槽编号存储了持久性数据
 *
 * 此函数检查持久存储中的密钥槽是否存在任何密钥数据或元数据。
 *
 * \param键要检查的持久标识符。
 *
 * \retval 0插槽号不存在持久数据\retval 1插槽号存在持久数据
 */
int psa_is_key_present_in_storage( const mbedtls_svc_key_id_t key );

/**
 * \brief格式化密钥数据和元数据，并保存到给定密钥槽的位置。
 *
 * 此函数格式化关键数据和元数据，并将其保存到持久存储后端。与钥匙槽对应的存储位置必须为空，否则此功能将失败。应在将密钥加载到内部插槽后调用此函数，以确保持久密钥不会保存到与已占用的非持久密钥相对应的存储位置，并确保密钥数据得到验证。
 *
 * 注意：此函数仅对非空的密钥缓冲区成功。如果传递了NULL指针或零长度，则函数将失败，并显示#PSA_ERROR_INVALID_ARGUMENT。
 *
 * \param[in]attr要保存的密钥的属性。属性中的密钥标识符字段确定密钥的位置。\param[in]data包含密钥数据的缓冲区。\param data_length构成密钥数据的字节数。
 *
 * \retval#PSA_SUCCESS\retval#PSTA_ERROR_INVALID_ARGUMENT\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#1PSA_ERROR_inSUFFIE_STORAGE\retval#8PSA_ERROR_STORAGE_FAILURE\retval#3PSA_ERROR_ALREADY_EXISTS\retval#2PSA_ERROR_DATA_INVALID\retval#5PSA_ERROR-DATA_CORRUPT
 */
psa_status_t psa_save_persistent_key( const psa_core_key_attributes_t *attr,
                                      const uint8_t *data,
                                      const size_t data_length );

/**
 * \brief分析密钥数据和元数据，并为给定的密钥槽编号加载持久密钥。
 *
 * 此函数从存储后端读取数据，解析关键数据和元数据，并将其写入适当的输出参数。
 *
 * 注意：此函数分配缓冲区，并通过数据参数返回指向它的指针。成功返回时，指针保证有效，缓冲区至少包含一个字节的数据。之后必须在数据缓冲区上调用psa_free_persistent_key_data（），以将该缓冲区清零并释放。
 *
 * \param[in，out]attr在输入时，密钥标识符字段标识要加载的密钥。其他字段将被忽略。成功后，属性结构包含从存储加载的密钥元数据。\param[out]data返回时指向已分配密钥数据缓冲区的指针。\param[out]data_length构成密钥数据的字节数。
 *
 * \retval#PSA_SUCCESS\retval#PSTA_ERROR_INSUFFIE_MEMORY\retval#PSA_ERROR_DATA_INVALID\retval#1 PSA_ERROR-DATA_CORRUPT\retval#2 PSA_ERROR_SOES_NOT_EXIST
 */
psa_status_t psa_load_persistent_key( psa_core_key_attributes_t *attr,
                                      uint8_t **data,
                                      size_t *data_length );

/**
 * \brief删除给定密钥槽编号的持久数据。
 *
 * \param key要从持久存储中删除的密钥的持久标识符。
 *
 * \retval#PSA_SUCCESS密钥已成功删除，或者密钥不存在。\retval#PSA_ERROR_DATA_INVALID
 */
psa_status_t psa_destroy_persistent_key( const mbedtls_svc_key_id_t key );

/**
 * \brief释放psa_oload_persistent_key（）分配的临时缓冲区。
 *
 * 必须在psa_oload_persistent_key（）之后的某个时间点调用该函数，以将分配给该函数中缓冲区的内存清零并释放。
 *
 * \param key_data键数据的缓冲区。\param key_data_length密钥数据缓冲区的大小。
 *
 */
void psa_free_persistent_key_data( uint8_t *key_data, size_t key_data_length );

/**
 * \brief格式化持久存储的关键数据和元数据
 *
 * \param[in]data包含密钥数据的缓冲区。\param data_length密钥数据缓冲区的长度。\param[in]attr键的核心属性。\param[out]storage_data格式化数据的输出缓冲区。
 *
 */
void psa_format_key_data_for_storage( const uint8_t *data,
                                      const size_t data_length,
                                      const psa_core_key_attributes_t *attr,
                                      uint8_t *storage_data );

/**
 * \brief将持久存储数据解析为关键数据和元数据
 *
 * \param[in]storage_data存储数据的缓冲区。\param storage_data_length存储数据缓冲区的长度\param[out]key_data在输出时，指向包含密钥数据的新分配缓冲区的指针。必须使用psa_free_persistent_key_data（）\param[out]key_data_length密钥数据缓冲区的长度\param[out]attr释放。成功后，属性结构将填充加载的密钥元数据。
 *
 * \retval#PSA_SUCCESS\retval#PSA错误_充分_记忆\retval#PSA_ERROR_DATA_INVALID
 */
psa_status_t psa_parse_key_data_from_storage( const uint8_t *storage_data,
                                              size_t storage_data_length,
                                              uint8_t **key_data,
                                              size_t *key_data_length,
                                              psa_core_key_attributes_t *attr );

#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
/**如果需要事务支持，则定义此符号。*/
#define PSA_CRYPTO_STORAGE_HAS_TRANSACTIONS
#endif

#if defined(PSA_CRYPTO_STORAGE_HAS_TRANSACTIONS)

/** 正在进行的事务类型。
 */
/* 这是一个整数类型而不是枚举，原因有两个：加载事务文件时支持未知值，以及确保类型具有已知大小。
 */
typedef uint16_t psa_crypto_transaction_type_t;

/** 没有正在进行的事务。
 *
 * 它的值为0，因此零初始化将事务的类型设置为该值。
 */
#define PSA_CRYPTO_TRANSACTION_NONE             ( (psa_crypto_transaction_type_t) 0x0000 )

/** 密钥创建事务。
 *
 * 这仅用于外部密码处理器（安全元件）中的密钥。RAM或内部存储器中的键是在存储器中原子地创建的（简单的文件创建），因此它们不需要事务机制。
 */
#define PSA_CRYPTO_TRANSACTION_CREATE_KEY       ( (psa_crypto_transaction_type_t) 0x0001 )

/** 密钥销毁交易。
 *
 * 这仅用于外部密码处理器（安全元件）中的密钥。RAM或内部存储中的密钥在存储中被原子销毁（简单的文件删除），因此它们不需要事务机制。
 */
#define PSA_CRYPTO_TRANSACTION_DESTROY_KEY      ( (psa_crypto_transaction_type_t) 0x0002 )

/** 交易数据。
 *
 * 此类型被设计为通过在同一设备上写入内存表示并将其读回来序列化。
 *
 * \注意：事务机制是为一次一个活动事务而设计的。事务对象是#psa_crypto_transaction。
 *
 * \注意：如果API调用启动了一个事务，则必须在返回到应用程序之前完成该事务。
 *
 * 事务的生存期如下（请注意，一次只能激活一个事务）：
 *
 * -#调用psa_crypto_prepare_transaction（）初始化内存中的事务对象，并声明正在启动的事务类型。
 * -#填写#psa_crypto_transaction的类型特定字段。
 * -#调用psa_crypto_save_transaction（）启动事务。这会将事务数据保存到内部存储。
 * -#通过修改文件、联系外部实体或任何需要做的事情来执行事务的工作。请注意，事务可能会因电源故障而中断，因此您需要有一种从中断中恢复的方法，既可以取消目前已完成的操作，也可以从中断处恢复。
 * -#如果事务中存在中间阶段，请更新#psa_crypto_transaction的字段，并在到达每个阶段时再次调用psa_cCrypto_save_transaction（）。
 * -#事务结束后，调用psa_crypto_stop_transaction（）删除存储和内存中的事务数据。
 *
 * 如果在事务进行过程中系统崩溃，psa_crypto_init（）将调用psa_cCrypto_load_transaction（）并负责完成或倒回事务。这是在psa_crypto.c中的psa_ccrypto_recover_transaction（）中完成的。如果您添加了新类型的事务，请确保在psa\yccrypto_recover_transaction（）中为其添加代码。
 */
typedef union
{
    /* 此联合的每个元素必须具有以下属性以便于序列化和反序列化：
     *
     * -元素是一个结构。
     * -结构的第一个字段是“psa_crypto_transaction_type_type”。
     * -结构元素的排列方式没有填充。
     */
    struct psa_crypto_transaction_unknown_s
    {
        psa_crypto_transaction_type_t type;
        uint16_t unused1;
        uint32_t unused2;
        uint64_t unused3;
        uint64_t unused4;
    } unknown;
    /* ：：类型为#PSA_CRYPTO_TRANSACTION_CREATE_KEY或#PSA_RYPTO_TRANSSACTION_STROY_KEY。*/
    struct psa_crypto_transaction_key_s
    {
        psa_crypto_transaction_type_t type;
        uint16_t unused1;
        psa_key_lifetime_t lifetime;
        psa_key_slot_number_t slot;
        mbedtls_svc_key_id_t id;
    } key;
} psa_crypto_transaction_t;

/** 单个活动事务。
 */
extern psa_crypto_transaction_t psa_crypto_transaction;

/** 准备交易。
 *
 * 不得有正在进行的交易。
 *
 * \param type要启动的事务类型。
 */
static inline void psa_crypto_prepare_transaction(
    psa_crypto_transaction_type_t type )
{
    psa_crypto_transaction.unknown.type = type;
}

/** 将事务数据保存到存储器。
 *
 * 您可以在事务期间多次调用此函数，以自动更新事务状态。
 *
 * \retval#PSA_SUCCESS\retval#PSTA_ERROR_DATA_CORRUPT\retval#PSA_ERROR_INSUFFIE_STORAGE\retval#PSA_ERROR_STORAGE_FAILURE
 */
psa_status_t psa_crypto_save_transaction( void );

/** 从存储中加载事务数据（如果有的话）。
 *
 * 该函数旨在从psa_crypto_init（）调用，以在系统崩溃中断事务时进行恢复。
 *
 * \retval#PSA_SUCCESS有关正在进行的事务的数据已加载到#PSA_crypto_transaction。\retval#PSA_ERROR_DOES_NOT_EXIST没有正在进行的事务。\retval#PSA_ERROR_STORAGE_FAILURE\retval#PSA_ERROR_DATA_INVALID\retval#PSA_ERROR_DATA_CORRUPT
 */
psa_status_t psa_crypto_load_transaction( void );

/** 指示当前事务已完成。
 *
 * 在事务处理结束时调用此函数。此函数不“提交”或“中止”事务：存储子系统没有“提交”和“中止”的概念，只是保存和删除存储中的事务信息。
 *
 * 此功能清除存储器中的事务数据（如果有）并重置存储器中的数据。
 *
 * \retval#PSA_SUCCESS存储中存在事务数据。\retval#PSA_ERROR_DOES_NOT_EXIST存储中没有事务数据。\retval#PSA_ERROR_STORAGE_FAILURE无法确定存储中是否存在事务数据，或者无法擦除事务数据。
 */
psa_status_t psa_crypto_stop_transaction( void );

/** 交易数据的ITS文件标识符。
 *
 * 0xffffffNN=特殊文件；0x74=事务的“t”。
 */
#define PSA_CRYPTO_ITS_TRANSACTION_UID ( (psa_key_id_t) 0xffffff74 )

#endif /* PSA_CRYPTO_STORAGE_HAS_TRANSACTIONS */

#if defined(MBEDTLS_PSA_INJECT_ENTROPY)
/** mbedtls_psa_inject_entropy（）的后端。
 *
 * 此函数将提供的数据存储到熵种子文件中。
 *
 * \retval#PSA_SUCCESS SUCCESS\retval#PSA错误_STORAGE_FAILURE\retval#PSA_ERROR_INSUFFIE_STORAGE\retval#PSA_ERROR_NOT_PERMITTED熵种子文件已存在。
 */
psa_status_t mbedtls_psa_storage_inject_entropy( const unsigned char *seed,
                                                 size_t seed_size );
#endif /* MBEDTLS_PSA_INJECT_ENTROPY */

#ifdef __cplusplus
}
#endif

#endif /* PSA_CRYPTO_STORAGE_H */

