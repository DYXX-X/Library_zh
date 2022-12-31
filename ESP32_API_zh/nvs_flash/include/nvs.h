/*
 * SPDX文件版权所有文本：2015-2022 Espressif Systems（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#ifndef ESP_NVS_H
#define ESP_NVS_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "esp_attr.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 表示非易失性存储句柄的不透明指针类型
 */
typedef uint32_t nvs_handle_t;

/*
 * IDF V4.0之前的版本使用nvs_handle，因此为了兼容性，这里保留了原始的typedef。
 */
typedef nvs_handle_t nvs_handle IDF_DEPRECATED("Replace with nvs_handle_t");

#define ESP_ERR_NVS_BASE                    0x1100                     /*!< 起始错误代码数*/
#define ESP_ERR_NVS_NOT_INITIALIZED         (ESP_ERR_NVS_BASE + 0x01)  /*!< 存储驱动程序未初始化*/
#define ESP_ERR_NVS_NOT_FOUND               (ESP_ERR_NVS_BASE + 0x02)  /*!< Id命名空间尚不存在，模式为NVS_READONLY*/
#define ESP_ERR_NVS_TYPE_MISMATCH           (ESP_ERR_NVS_BASE + 0x03)  /*!< 设置或获取操作的类型与NVS中存储的值类型不匹配*/
#define ESP_ERR_NVS_READ_ONLY               (ESP_ERR_NVS_BASE + 0x04)  /*!< 存储句柄以只读方式打开*/
#define ESP_ERR_NVS_NOT_ENOUGH_SPACE        (ESP_ERR_NVS_BASE + 0x05)  /*!< 基础存储空间不足，无法保存值*/
#define ESP_ERR_NVS_INVALID_NAME            (ESP_ERR_NVS_BASE + 0x06)  /*!< 命名空间名称不满足约束*/
#define ESP_ERR_NVS_INVALID_HANDLE          (ESP_ERR_NVS_BASE + 0x07)  /*!< 句柄已关闭或为空*/
#define ESP_ERR_NVS_REMOVE_FAILED           (ESP_ERR_NVS_BASE + 0x08)  /*!< 由于闪存写入操作失败，该值未更新。然而，该值已写入，如果闪存操作不会再次失败，则在重新初始化nv后将完成更新。*/
#define ESP_ERR_NVS_KEY_TOO_LONG            (ESP_ERR_NVS_BASE + 0x09)  /*!< 密钥名称太长*/
#define ESP_ERR_NVS_PAGE_FULL               (ESP_ERR_NVS_BASE + 0x0a)  /*!< 内部错误；nvs API函数从未返回*/
#define ESP_ERR_NVS_INVALID_STATE           (ESP_ERR_NVS_BASE + 0x0b)  /*!< 由于先前的错误，NVS处于不一致状态。再次调用nvs_flash_init和nvs_open，然后重试。*/
#define ESP_ERR_NVS_INVALID_LENGTH          (ESP_ERR_NVS_BASE + 0x0c)  /*!< 字符串或blob长度不足以存储数据*/
#define ESP_ERR_NVS_NO_FREE_PAGES           (ESP_ERR_NVS_BASE + 0x0d)  /*!< NVS分区不包含任何空页。如果NVS分区被截断，可能会发生这种情况。擦除整个分区并再次调用nvs_flash_init。*/
#define ESP_ERR_NVS_VALUE_TOO_LONG          (ESP_ERR_NVS_BASE + 0x0e)  /*!< 字符串或blob长度大于实现支持的长度*/
#define ESP_ERR_NVS_PART_NOT_FOUND          (ESP_ERR_NVS_BASE + 0x0f)  /*!< 分区表中找不到具有指定名称的分区*/

#define ESP_ERR_NVS_NEW_VERSION_FOUND       (ESP_ERR_NVS_BASE + 0x10)  /*!< NVS分区包含新格式的数据，此版本的代码无法识别*/
#define ESP_ERR_NVS_XTS_ENCR_FAILED         (ESP_ERR_NVS_BASE + 0x11)  /*!< 写入NVS条目时XTS加密失败*/
#define ESP_ERR_NVS_XTS_DECR_FAILED         (ESP_ERR_NVS_BASE + 0x12)  /*!< 读取NVS条目时XTS解密失败*/
#define ESP_ERR_NVS_XTS_CFG_FAILED          (ESP_ERR_NVS_BASE + 0x13)  /*!< XTS配置设置失败*/
#define ESP_ERR_NVS_XTS_CFG_NOT_FOUND       (ESP_ERR_NVS_BASE + 0x14)  /*!< 未找到XTS配置*/
#define ESP_ERR_NVS_ENCR_NOT_SUPPORTED      (ESP_ERR_NVS_BASE + 0x15)  /*!< 此版本不支持NVS加密*/
#define ESP_ERR_NVS_KEYS_NOT_INITIALIZED    (ESP_ERR_NVS_BASE + 0x16)  /*!< NVS密钥分区未初始化*/
#define ESP_ERR_NVS_CORRUPT_KEY_PART        (ESP_ERR_NVS_BASE + 0x17)  /*!< NVS密钥分区已损坏*/
#define ESP_ERR_NVS_WRONG_ENCRYPTION        (ESP_ERR_NVS_BASE + 0x19)  /*!< NVS分区标记为使用通用闪存加密进行加密。这是禁止的，因为NVS加密工作方式不同。*/

#define ESP_ERR_NVS_CONTENT_DIFFERS         (ESP_ERR_NVS_BASE + 0x18)  /*!< 内部错误；nvs API函数从未返回。相比之下，NVS密钥不同*/

#define NVS_DEFAULT_PART_NAME               "nvs"   /*!< 分区表中NVS分区的默认分区名称*/

#define NVS_PART_NAME_MAX_SIZE              16   /*!< 分区名称的最大长度（不包括空终止符）*/
#define NVS_KEY_NAME_MAX_SIZE               16   /*!< NVS密钥名称的最大长度（包括空终止符）*/

/**
 * @brief 打开非易失性存储器的模式
 */
typedef enum {
	NVS_READONLY,  /*!< 只读*/
	NVS_READWRITE  /*!< 读写*/
} nvs_open_mode_t;

/*
 * IDF V4.0之前的版本使用nvs_open_mode，因此为了兼容性，此处保留原始typedef。
 */
typedef nvs_open_mode_t nvs_open_mode IDF_DEPRECATED("Replace with nvs_open_mode_t");


/**
 * @brief 变量类型
 *
 */
typedef enum {
    NVS_TYPE_U8    = 0x01,  /*!< 键入uint8_t*/
    NVS_TYPE_I8    = 0x11,  /*!< 类型int8_t*/
    NVS_TYPE_U16   = 0x02,  /*!< 类型uint16_t*/
    NVS_TYPE_I16   = 0x12,  /*!< 类型int16_t*/
    NVS_TYPE_U32   = 0x04,  /*!< 类型uint32_t*/
    NVS_TYPE_I32   = 0x14,  /*!< 类型int32_t*/
    NVS_TYPE_U64   = 0x08,  /*!< 键入uint64_t*/
    NVS_TYPE_I64   = 0x18,  /*!< 类型int64_t*/
    NVS_TYPE_STR   = 0x21,  /*!< 类型字符串*/
    NVS_TYPE_BLOB  = 0x42,  /*!< 类型blob*/
    NVS_TYPE_ANY   = 0xff   /*!< 必须是最后一个*/
} nvs_type_t;

/**
 * @brief 从nvs_entryinfo函数获得的条目信息
 */
typedef struct {
    char namespace_name[16];    /*!< 键值所属的命名空间*/
    char key[NVS_KEY_NAME_MAX_SIZE];               /*!< 存储的键值对的键*/
    nvs_type_t type;            /*!< 存储的键值对的类型*/
} nvs_entry_info_t;

/**
 * 表示nvs项迭代器的不透明指针类型
 */
typedef struct nvs_opaque_iterator_t *nvs_iterator_t;

/**
 * @brief      从默认NVS分区打开具有给定命名空间的非易失性存储
 *
 * 多个内部ESP-IDF和第三方应用程序模块可以将其键值对存储在NVS模块中。为了减少可能的密钥名称冲突，每个模块都可以使用自己的命名空间。默认NVS分区是分区表中标记为“NVS”的分区。
 *
 * @param[in]  name        命名空间名称。最大长度为（NVS_KEY_NAME_MAX_SIZE-1）个字符。不应该是空的。
 * @param[in]  open_mode   NVS_READWRITE或NVS_READONLY。如果NVS_READONLY，将打开只读句柄。此句柄的所有写入请求都将被拒绝。
 * @param[out] out_handle  如果成功（返回代码为零），将在此参数中返回句柄。
 *
 * @return
 *             -ESP_OK（如果存储句柄已成功打开）
 *             -如果存储驱动程序未初始化，则为ESP_ERR_NVS_NOT_INITIALIZED
 *             -如果找不到标签为“NVS”的分区，则为ESP_ERR_NVS_PART_NOT_FOUND
 *             -ESP_ERR_NVS_NOT_FOUND id命名空间尚不存在，模式为NVS_READONLY
 *             -如果命名空间名称不满足约束，则为ESP_ERR_NVS_INVALID_NAME
 *             -ESP_ERR_NO_MEM，以防无法为内部结构分配内存
 *             -基础存储驱动程序中的其他错误代码
 */
esp_err_t nvs_open(const char* name, nvs_open_mode_t open_mode, nvs_handle_t *out_handle);

/**
 * @brief      从指定分区打开具有给定命名空间的非易失性存储
 *
 * 行为与nvs_open（）API相同。但是，此API可以在指定的NVS分区上运行，而不是在默认NVS分区。注意，必须使用NVS_flash_init_partition（）API向NVS注册指定的分区。
 *
 * @param[in]  part_name   对象读/写/擦除感兴趣分区的标签（名称）
 * @param[in]  name        命名空间名称。最大长度为（NVS_KEY_NAME_MAX_SIZE-1）个字符。不应该是空的。
 * @param[in]  open_mode   NVS_READWRITE或NVS_READONLY。如果NVS_READONLY，将打开只读句柄。此句柄的所有写入请求都将被拒绝。
 * @param[out] out_handle  如果成功（返回代码为零），将在此参数中返回句柄。
 *
 * @return
 *             -ESP_OK（如果存储句柄已成功打开）
 *             -如果存储驱动程序未初始化，则为ESP_ERR_NVS_NOT_INITIALIZED
 *             -如果找不到具有指定名称的分区，则返回ESP_ERR_NVS_PART_NOT_FOUND
 *             -ESP_ERR_NVS_NOT_FOUND id命名空间尚不存在，模式为NVS_READONLY
 *             -如果命名空间名称不满足约束，则为ESP_ERR_NVS_INVALID_NAME
 *             -ESP_ERR_NO_MEM，以防无法为内部结构分配内存
 *             -基础存储驱动程序中的其他错误代码
 */
esp_err_t nvs_open_from_partition(const char *part_name, const char* name, nvs_open_mode_t open_mode, nvs_handle_t *out_handle);

/**@{*/
/**
 * @brief      为给定键设置int8_t值
 *
 * 根据键的名称设置键的值。请注意，在调用\cnvs_commit之前，不会更新实际存储。
 *
 * @param[in]  handle  从nvs_open函数获得的句柄。无法使用以只读方式打开的句柄。
 * @param[in]  key     密钥名称。最大长度为（NVS_KEY_NAME_MAX_SIZE-1）个字符。不应该是空的。
 * @param[in]  value   要设置的值。
 *
 * @return
 *             -如果值设置成功，则ESP_OK
 *             -如果句柄已关闭或为空，则为ESP_ERR_NVS_INVALID_HANDLE
 *             -如果存储句柄以只读方式打开，则为ESP_ERR_NVS_READ_ONLY
 *             -如果密钥名称不满足约束，则为ESP_ERR_NVS_INVALID_NAME
 *             -ESP_ERR_NVS_NOT_ENOUGH_SPACE（如果基础存储中没有足够的空间来保存值）
 *             -如果由于闪存写入操作失败而未更新值，则返回ESP_ERR_NVS_REMOVE_FAILED。然而，该值已写入，如果闪存操作不会再次失败，则在重新初始化nv后将完成更新。
 */
esp_err_t nvs_set_i8 (nvs_handle_t handle, const char* key, int8_t value);

/**
 * @brief      为给定键设置uint8_t值
 *
 * 除数据类型外，此函数与\c nvs_set_i8相同。
 */
esp_err_t nvs_set_u8 (nvs_handle_t handle, const char* key, uint8_t value);

/**
 * @brief      为给定键设置int16_t值
 *
 * 除数据类型外，此函数与\c nvs_set_i8相同。
 */
esp_err_t nvs_set_i16 (nvs_handle_t handle, const char* key, int16_t value);

/**
 * @brief      为给定密钥设置uint16_t值
 *
 * 除数据类型外，此函数与\c nvs_set_i8相同。
 */
esp_err_t nvs_set_u16 (nvs_handle_t handle, const char* key, uint16_t value);

/**
 * @brief      设置给定键的int32_t值
 *
 * 除数据类型外，此函数与\c nvs_set_i8相同。
 */
esp_err_t nvs_set_i32 (nvs_handle_t handle, const char* key, int32_t value);

/**
 * @brief      为给定密钥设置uint32_t值
 *
 * 除数据类型外，此函数与\c nvs_set_i8相同。
 */
esp_err_t nvs_set_u32 (nvs_handle_t handle, const char* key, uint32_t value);

/**
 * @brief      为给定键设置int64_t值
 *
 * 除数据类型外，此函数与\c nvs_set_i8相同。
 */
esp_err_t nvs_set_i64 (nvs_handle_t handle, const char* key, int64_t value);

/**
 * @brief      为给定键设置uint64_t值
 *
 * 除数据类型外，此函数与\c nvs_set_i8相同。
 */
esp_err_t nvs_set_u64 (nvs_handle_t handle, const char* key, uint64_t value);

/**
 * @brief      为给定键设置字符串
 *
 * 根据键的名称设置键的值。请注意，在调用\cnvs_commit之前，不会更新实际存储。
 *
 * @param[in]  handle  从nvs_open函数获得的句柄。无法使用以只读方式打开的句柄。
 * @param[in]  key     密钥名称。最大长度为（NVS_KEY_NAME_MAX_SIZE-1）个字符。不应该是空的。
 * @param[in]  value   要设置的值。对于字符串，如果有一个完整的页面可供写入，则最大长度（包括空字符）为4000字节。但是，如果空闲空间被分割，则这会减少。
 *
 * @return
 *             -如果值设置成功，则ESP_OK
 *             -如果句柄已关闭或为空，则为ESP_ERR_NVS_INVALID_HANDLE
 *             -如果存储句柄以只读方式打开，则为ESP_ERR_NVS_READ_ONLY
 *             -如果密钥名称不满足约束，则为ESP_ERR_NVS_INVALID_NAME
 *             -ESP_ERR_NVS_NOT_ENOUGH_SPACE（如果基础存储中没有足够的空间来保存值）
 *             -如果由于闪存写入操作失败而未更新值，则返回ESP_ERR_NVS_REMOVE_FAILED。然而，该值已写入，如果闪存操作不会再次失败，则在重新初始化nv后将完成更新。
 *             -如果字符串值过长，则为ESP_ERR_NVS_VALUE_TOO_LONG
 */
esp_err_t nvs_set_str (nvs_handle_t handle, const char* key, const char* value);
/**@}*/

/**
 * @brief       为给定密钥设置可变长度二进制值
 *
 * 这一系列函数为给定名称的键设置值。请注意，在调用nvs_commit函数之前，不会更新实际存储。
 *
 * @param[in]  handle  从nvs_open函数获得的句柄。无法使用以只读方式打开的句柄。
 * @param[in]  key     密钥名称。最大长度为（NVS_KEY_NAME_MAX_SIZE-1）个字符。不应该是空的。
 * @param[in]  value   要设置的值。
 * @param[in]  length  要设置的二进制值的长度，以字节为单位；最大长度为508000字节或（分区大小的97.6%-4000）字节，以较低者为准。
 *
 * @return
 *             -如果值设置成功，则ESP_OK
 *             -如果句柄已关闭或为空，则为ESP_ERR_NVS_INVALID_HANDLE
 *             -如果存储句柄以只读方式打开，则为ESP_ERR_NVS_READ_ONLY
 *             -如果密钥名称不满足约束，则为ESP_ERR_NVS_INVALID_NAME
 *             -ESP_ERR_NVS_NOT_ENOUGH_SPACE（如果基础存储中没有足够的空间来保存值）
 *             -如果由于闪存写入操作失败而未更新值，则返回ESP_ERR_NVS_REMOVE_FAILED。然而，该值已写入，如果闪存操作不会再次失败，则在重新初始化nv后将完成更新。
 *             -如果值太长，则为ESP_ERR_NVS_VALUE_TOO_LONG
 */
esp_err_t nvs_set_blob(nvs_handle_t handle, const char* key, const void* value, size_t length);

/**@{*/
/**
 * @brief      获取给定键的int8_t值
 *
 * 这些函数检索给定名称的键的值。如果\c键不存在，或者请求的变量类型与设置值时使用的类型不匹配，则返回错误。
 *
 * 如果出现任何错误，则不会修改out_value。
 *
 * \c out_value必须是指向给定类型的已分配变量的指针。
 *
 * \code｛c｝//使用nvs_get_i32的示例：int32_t max_buffer_size=4096；//默认值esp_err_t err=nvs_get_i32（my_handle，“max_buffer_size”，&max_buffer _size）；断言（err==ESP_OK | | err==ESP_err_NVS_NOT_FOUND）；//如果返回了ESP_ERR_NVS_NOT_FOUND，max_buffer_size仍然//具有其默认值。
 *
 * \结束代码
 *
 * @param[in]     handle     从nvs_open函数获得的句柄。
 * @param[in]     key        密钥名称。最大长度为（NVS_KEY_NAME_MAX_SIZE-1）个字符。不应该是空的。
 * @param         out_value  指向输出值的指针。nvs_get_str和nvs_get_blob可能为NULL，在这种情况下，所需的长度将在长度参数中返回。
 *
 * @return
 *             -ESP_OK（如果成功检索到值）
 *             -如果请求的密钥不存在，则为ESP_ERR_NVS_NOT_FOUND
 *             -如果句柄已关闭或为空，则为ESP_ERR_NVS_INVALID_HANDLE
 *             -如果密钥名称不满足约束，则为ESP_ERR_NVS_INVALID_NAME
 *             -如果长度不足以存储数据，则为ESP_ERR_NVS_INVALID_LENGTH
 */
esp_err_t nvs_get_i8 (nvs_handle_t handle, const char* key, int8_t* out_value);

/**
 * @brief      获取给定键的uint8_t值
 *
 * 除数据类型外，此函数与\c nvs_get_i8相同。
 */
esp_err_t nvs_get_u8 (nvs_handle_t handle, const char* key, uint8_t* out_value);

/**
 * @brief      获取给定键的int16_t值
 *
 * 除数据类型外，此函数与\c nvs_get_i8相同。
 */
esp_err_t nvs_get_i16 (nvs_handle_t handle, const char* key, int16_t* out_value);

/**
 * @brief      获取给定键的uint16_t值
 *
 * 除数据类型外，此函数与\c nvs_get_i8相同。
 */
esp_err_t nvs_get_u16 (nvs_handle_t handle, const char* key, uint16_t* out_value);

/**
 * @brief      获取给定键的int32_t值
 *
 * 除数据类型外，此函数与\c nvs_get_i8相同。
 */
esp_err_t nvs_get_i32 (nvs_handle_t handle, const char* key, int32_t* out_value);

/**
 * @brief      获取给定密钥的uint32_t值
 *
 * 除数据类型外，此函数与\c nvs_get_i8相同。
 */
esp_err_t nvs_get_u32 (nvs_handle_t handle, const char* key, uint32_t* out_value);

/**
 * @brief      获取给定键的int64_t值
 *
 * 除数据类型外，此函数与\c nvs_get_i8相同。
 */
esp_err_t nvs_get_i64 (nvs_handle_t handle, const char* key, int64_t* out_value);

/**
 * @brief      获取给定键的uint64_t值
 *
 * 除数据类型外，此函数与\c nvs_get_i8相同。
 */
esp_err_t nvs_get_u64 (nvs_handle_t handle, const char* key, uint64_t* out_value);
/**@}*/

/**@{*/
/**
 * @brief      获取给定键的字符串值
 *
 * 这些函数检索给定密钥的条目的数据。如果键不存在，或者请求的变量类型与设置值时使用的类型不匹配，则返回错误。
 *
 * 如果出现任何错误，则不会修改out_value。
 *
 * 所有函数都希望out_value是指向给定类型的已分配变量的指针。
 *
 * nvs_get_str和nvs_get_blob函数支持WinAPI风格的长度查询。要获取存储值所需的大小，请使用零out_value和非零长度指针调用nvs_get_str或nvs_get_blob。长度参数指向的变量将设置为所需的长度。对于nvs_get_str，此长度包括零终止符。当使用非零out_value调用nvs_get_str和nvs_get_blob时，长度必须为非零，并且必须指向out_value中可用的长度。建议将nvs_get/set_str用于以零结尾的C字符串，将nvs_get/set_blob用于任意数据结构。
 *
 * \code｛c｝//使用nvs_get_str将字符串获取到动态数组中的示例（无错误检查）：size_t required_size；nvs_get_str（my_handle，“服务器名”，NULL，&required_size）；char服务器名称=malloc（required_size）；nvs_get_str（my_handle，“服务器名”，服务器名，&required_size）；
 *
 * //使用nvs_get_blob将二进制数据获取到静态数组中的示例（无错误检查）：uint8_t mac_addr[6]；size_t size=sizeof（mac_addr）；nvs_get_blob（my_handle，“dst_mac_addr”，mac_addr，&size）；\结束代码
 *
 * @param[in]     handle     从nvs_open函数获得的句柄。
 * @param[in]     key        密钥名称。最大长度为（NVS_KEY_NAME_MAX_SIZE-1）个字符。不应该是空的。
 * @param[out]    out_value  指向输出值的指针。nvs_get_str和nvs_get_blob可能为NULL，在这种情况下，所需的长度将在长度参数中返回。
 * @param[inout]  length     指向保存out_value长度的变量的非零指针。如果out_value为零，则将设置为保持该值所需的长度。如果out_value不为零，将设置为写入值的实际长度。对于nvs_get_str，这包括零终止符。
 *
 * @return
 *             -ESP_OK（如果成功检索到值）
 *             -如果请求的密钥不存在，则为ESP_ERR_NVS_NOT_FOUND
 *             -如果句柄已关闭或为空，则为ESP_ERR_NVS_INVALID_HANDLE
 *             -如果密钥名称不满足约束，则为ESP_ERR_NVS_INVALID_NAME
 *             -如果长度不足以存储数据，则为ESP_ERR_NVS_INVALID_LENGTH
 */
esp_err_t nvs_get_str (nvs_handle_t handle, const char* key, char* out_value, size_t* length);

/**
 * @brief      获取给定密钥的blob值
 *
 * 除数据类型外，此函数的行为与\cnvs_get_str相同。
 */
esp_err_t nvs_get_blob(nvs_handle_t handle, const char* key, void* out_value, size_t* length);
/**@}*/

/**
 * @brief      使用给定密钥名称擦除密钥值对。
 *
 * 请注意，在调用nvs_commit函数之前，可能不会更新实际存储。
 *
 * @param[in]  handle  使用nvs_open获取的存储句柄。无法使用以只读方式打开的句柄。
 *
 * @param[in]  key     密钥名称。最大长度为（NVS_KEY_NAME_MAX_SIZE-1）个字符。不应该是空的。
 *
 * @return
 *              -如果擦除操作成功，则ESP_OK
 *              -如果句柄已关闭或为空，则为ESP_ERR_NVS_INVALID_HANDLE
 *              -如果句柄以只读方式打开，则为ESP_ERR_NVS_READ_ONLY
 *              -如果请求的密钥不存在，则为ESP_ERR_NVS_NOT_FOUND
 *              -基础存储驱动程序中的其他错误代码
 */
esp_err_t nvs_erase_key(nvs_handle_t handle, const char* key);

/**
 * @brief      擦除命名空间中的所有键值对
 *
 * 请注意，在调用nvs_commit函数之前，可能不会更新实际存储。
 *
 * @param[in]  handle  使用nvs_open获取的存储句柄。无法使用以只读方式打开的句柄。
 *
 * @return
 *              -如果擦除操作成功，则ESP_OK
 *              -如果句柄已关闭或为空，则为ESP_ERR_NVS_INVALID_HANDLE
 *              -如果句柄以只读方式打开，则为ESP_ERR_NVS_READ_ONLY
 *              -基础存储驱动程序中的其他错误代码
 */
esp_err_t nvs_erase_all(nvs_handle_t handle);

/**
 * @brief      将任何挂起的更改写入非易失性存储
 *
 * 设置任何值后，必须调用nvs_commit（）以确保将更改写入非易失性存储。个别实现可能会在其他时间写入存储，但这并不能保证。
 *
 * @param[in]  handle  使用nvs_open获取的存储句柄。无法使用以只读方式打开的句柄。
 *
 * @return
 *             -ESP_OK（如果已成功写入更改）
 *             -如果句柄已关闭或为空，则为ESP_ERR_NVS_INVALID_HANDLE
 *             -基础存储驱动程序中的其他错误代码
 */
esp_err_t nvs_commit(nvs_handle_t handle);

/**
 * @brief      关闭存储句柄并释放所有分配的资源
 *
 * 一旦不再使用nvs_open打开的每个句柄，都应调用该函数。关闭句柄可能不会自动将更改写入非易失性存储。这必须使用nvs_commit函数显式完成。一旦在句柄上调用了此函数，就不应再使用该句柄。
 *
 * @param[in]  handle  要关闭的存储手柄
 */
void nvs_close(nvs_handle_t handle);

/**
 * @note 有关存储空间NVS的信息。
 */
typedef struct {
    size_t used_entries;      /**<已使用条目的数量。*/
    size_t free_entries;      /**<自由条目的数量。*/
    size_t total_entries;     /**<所有可用条目的金额。*/
    size_t namespace_count;   /**<数量名称空间。*/
} nvs_stats_t;

/**
 * @brief      填充结构nvs_stats_t。它提供有关分区中已用内存的信息。
 *
 * 此函数计算分区中已使用的条目数、可用条目数、总条目数和数量命名空间。
 *
 * \code｛c｝//nvs_get_stats（）的示例，用于获取已使用条目和空闲条目的数量：nvs_stats_t nvs_stats；nvs_get_stats（NULL，&nvs_stats）；printf（“计数：UsedEntries=（%d），FreeEntries=（%d），AllEntries=“%d）\n”，nvs_stats。used_entries、nvs_stats。free_entries、nvs_stats。total_entries）；\结束代码
 *
 * @param[in]   part_name   分区表中的分区名称NVS。如果传递NULL，则将使用NVS_DEFAULT_PART_NAME（“NVS”）。
 *
 * @param[out]  nvs_stats   返回填充结构nvs_states_t。它提供有关分区中已用内存的信息。
 *
 *
 * @return
 *             -如果已成功写入更改，则ESP_OK。将填充返回参数nvs_stats。
 *             -如果找不到标签为“name”的分区，则返回ESP_ERR_NVS_PART_NOT_FOUND。返回参数nvs_stats将填充为0。
 *             -如果存储驱动程序未初始化，则为ESP_ERR_NVS_NOT_INITIALIZED。返回参数nvs_stats将填充0。
 *             -如果nvs_stats等于NULL，则为ESP_ERR_INVALID_ARG。
 *             -如果存在状态为“无效”的页面，则返回ESP_ERR_INVALID_STATE。返回参数nvs_stats将不会填充正确的值，因为不会对所有页面进行计数。计数将在第一个无效页面中断。
 */
esp_err_t nvs_get_stats(const char *part_name, nvs_stats_t *nvs_stats);

/**
 * @brief      计算命名空间中的所有条目。
 *
 * 条目表示NVS中最小的存储单元。字符串和Blob可能占用多个条目。请注意，要找出命名空间占用的条目总数，请在返回值used_entries上加一（如果err等于ESP_OK）。因为名称空间条目需要一个条目。
 *
 * \code｛c｝//nvs_get_used_entry_count（）的示例，用于获取一个命名空间中所有键值对的数量：nvs_handle_t handle；nvs_open（“namespace1”，nvs_READWRITE，&handle）。。。使用的条目大小；size_t total_entries_namespace；如果（nvs_get_used_entry_count（handle，&used_entries）==ESP_OK）{//命名空间total_entries_namespace=used_entries+1所占用的条目总数；}\结束代码
 *
 * @param[in]   handle              从nvs_open函数获得的句柄。
 *
 * @param[out]  used_entries        返回命名空间中已使用条目的数量。
 *
 *
 * @return
 *             -如果已成功写入更改，则ESP_OK。返回参数used_entries将为有效值。
 *             -如果存储驱动程序未初始化，则为ESP_ERR_NVS_NOT_INITIALIZED。返回参数used_entries将填充为0。
 *             -如果句柄已关闭或为NULL，则返回ESP_ERR_NVS_INVALID_HANDLE。返回参数used_entries将填充为0。
 *             -如果used_entries等于NULL，则为ESP_ERR_INVALID_ARG。
 *             -来自基础存储驱动程序的其他错误代码。返回参数used_entries将填充为0。
 */
esp_err_t nvs_get_used_entry_count(nvs_handle_t handle, size_t* used_entries);

/**
 * @brief       创建迭代器以基于一个或多个参数枚举NVS条目
 *
 * \code｛c｝//列出指定分区和命名空间nvs_iterator_t it=nvs_entry_find（分区、命名空间、nvs_type_any）下任何类型的所有键值对的示例；while（it！=NULL）｛nvs_entry_info_t info；nvs_entr_info（it，&I）；it=nvs_entry-next（it）；printf（“键'%s'，类型'%d'\n”，info.key，info.type）；｝；//注意：当//nvs_entry_find或nvs_entry-next函数返回NULL时，不需要释放从nvs_entre_find函数获得的迭代器，这表示找不到指定条件的其他//元素。｝\结束代码
 *
 * @param[in]   part_name       分区名称
 *
 * @param[in]   namespace_name  如果查找具有特定命名空间的条目，请设置此值。否则传递NULL。
 *
 * @param[in]   type            nvs_type_t值之一。
 *
 * @return 用于枚举找到的所有条目的迭代器，如果没有找到满足条件的条目，则为NULL。通过此函数获得的迭代器在不再使用时必须使用nvs_release_initerator释放。
 */
nvs_iterator_t nvs_entry_find(const char *part_name, const char *namespace_name, nvs_type_t type);

/**
 * @brief       返回与迭代器条件匹配的下一项，如果不存在此类项，则返回NULL。
 *
 * 请注意，在此调用之后，迭代器的任何副本都将无效。
 *
 * @param[in]   iterator     从nvs_entry_find函数获得的迭代器。必须为非NULL。
 *
 * @return 如果未找到条目，则为NULL，否则为有效的nvs_iterator_t。
 */
nvs_iterator_t nvs_entry_next(nvs_iterator_t iterator);

/**
 * @brief       用迭代器指向的条目信息填充nvs_entry_info_t结构。
 *
 * @param[in]   iterator     从nvs_entry_find或nvs_entry_next函数获得的迭代器。必须为非NULL。
 *
 * @param[out]  out_info     条目信息复制到的结构。
 */
void nvs_entry_info(nvs_iterator_t iterator, nvs_entry_info_t *out_info);

/**
 * @brief       释放迭代器
 *
 * @param[in]   iterator    释放从nvs_entry_find函数获得的迭代器。允许NULL参数。
 *
 */
void nvs_release_iterator(nvs_iterator_t iterator);


#ifdef __cplusplus
} // 外部“C”
#endif

#endif //ESP_NVS_H

