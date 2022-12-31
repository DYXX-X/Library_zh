/*
  用于硬件数字签名外围设备验证的ROM功能
*/
// 版权所有2019 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#define ETS_DS_IV_LEN 16

/* 闪存中存储的参数“C”的长度*/
#define ETS_DS_C_LEN (12672 / 8)

/* 加密ETS数据。建议以这种格式存储在闪存中。
 */
typedef struct {
    /* RSA LENGTH寄存器参数（RSA密钥和操作数中的字数减1）。
     *
     * 最大值127（对于RSA 4096）。
     *
     * 此值必须与加密并存储在“c”中的长度字段匹配，否则将返回无效结果。（DS外围设备将始终使用“c”中的值，而不是此值，因此攻击者无法以这种方式更改DS外围设备结果，它只会在软件中截断或扩展消息和生成的签名。）
     */
    unsigned rsa_length;

    /* 用于加密“c”的IV值*/
    uint8_t iv[ETS_DS_IV_LEN];

    /* 加密数字签名参数。明文值的AES-CBC加密结果。包括加密邮件摘要。
    */
    uint8_t c[ETS_DS_C_LEN];
} ets_ds_data_t;

typedef enum {
    ETS_DS_OK,
    ETS_DS_INVALID_PARAM,   /* 提供的参数无效*/
    ETS_DS_INVALID_KEY,     /* HMAC外围设备无法提供密钥*/
    ETS_DS_INVALID_PADDING, /* 用无效填充解密的“c”*/
    ETS_DS_INVALID_DIGEST,  /* 用无效摘要解密的“c”*/
} ets_ds_result_t;

void ets_ds_enable(void);

void ets_ds_disable(void);


/*
 * @brief 开始使用数字签名外围设备对消息（或填充的消息摘要）进行签名
 *
 * - @param message 指向包含要签名的消息的消息（或填充摘要）的指针。应为
 *   (data->rsa_length + 1)*4 bytes long.  @param data 指向DS数据的指针。可以是指向闪存中数据的指针。
 *
 * 调用此函数之前，调用方必须已经调用了ets_ds_enable（）和ets_hmc_calculate_downstream（），并负责随后调用ets_ds_finish_sign（）和sets_hmc_validate_downflow（）。
 *
 * @return ETS_DS_OK（如果签名正在进行），ETS_DS_INVALID_PARAM（如果参数无效），EST_DS_INVALID_KEY（如果密钥或HMAC外围设备配置不正确）。
 */
ets_ds_result_t ets_ds_start_sign(const void *message, const ets_ds_data_t *data);


/*
 * @brief 如果调用ets_DS_start_sign（）后DS外设正忙，则返回true
 *
 * 结果为false表示不会阻止对ets_ds_finish_sign（）的调用。
 *
 * 仅当已调用ets_ds_enable（）时有效。
 */
bool ets_ds_is_busy(void);


/* @brief 使用数字签名外围设备完成对消息的签名
 *
 * 必须在ets_ds_start_sign（）之后调用。可以使用ets_ds_businy（）等待外围设备不再忙碌。
 *
 * - @param signature 指向包含签名的缓冲区的指针。应为（data->rsa\ulength+1）4字节长。
 * - @param data 应与传递给ets_ds_start_sign（）的“data”参数匹配
 *
 * @param ETS_DS_OK 如果签名成功，则如果参数无效，则为ETS_DS_INVALID_PARAM；如果加密的数据摘要或填充字节有问题，则为SETS_DS_INVALID_DIGEST或ETS_DS_INVALID_PADDING（如果是ETS_DS/INVALID_PADD，则无论如何都会生成摘要）
 */
ets_ds_result_t ets_ds_finish_sign(void *signature, const ets_ds_data_t *data);


/* 数字签名使用的明文参数。

   不用于与DS外设进行签名，但可以通过调用ets_DS_encrypt_params（）在设备中进行加密
*/
typedef struct {
    uint32_t Y[4096/32];
    uint32_t M[4096/32];
    uint32_t Rb[4096/32];
    uint32_t M_prime;
    uint32_t length;
} ets_ds_p_data_t;

typedef enum {
    ETS_DS_KEY_HMAC, /* HMAC密钥（存储在efuse中）*/
    ETS_DS_KEY_AES,  /* AES密钥（由HMAC外围设备在下游模式下从HMAC密钥导出）*/
} ets_ds_key_t;

/* @brief 加密DS参数，以便于存储和稍后与DS外围设备一起使用
 *
 * @param data 用于存储加密数据的输出缓冲区，适用于以后生成签名。
 * @param iv 指向16字节IV缓冲区的指针将复制到“数据”中。每次应随机生成字节。
 * @param p_data 指向输入明文密钥数据的指针。期望在完成此过程并存储“数据”后删除此数据。
 * @param key 指向32字节密钥数据的指针。由key_Type参数确定的类型。预期相应的HMAC密钥将存储到efuse，然后永久擦除。
 * @param key_type 存储在“key”中的密钥类型（AES-256 DS密钥，或使用HMAC外围设备派生AES DS密钥的HMAC DS密钥）
 *
 * @return 如果任何参数无效，则为ETS_DS_INVALID_PARAM；如果从输入参数成功生成“数据”，则为SETS_DS_OK。
 */
ets_ds_result_t ets_ds_encrypt_params(ets_ds_data_t *data, const void *iv, const ets_ds_p_data_t *p_data, const void *key, ets_ds_key_t key_type);


#ifdef __cplusplus
}
#endif

