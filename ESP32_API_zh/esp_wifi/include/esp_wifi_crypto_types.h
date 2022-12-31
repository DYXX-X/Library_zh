/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */


#ifndef __ESP_WIFI_CRYPTO_TYPES_H__
#define __ESP_WIFI_CRYPTO_TYPES_H__

/* 这是用于配置用于WiFi加密操作的实现的内部API头。

   在正常操作期间，您不需要在此标头中使用任何这些类型或函数。请参见esp_wifi。&esp_wifi_types。h代替。
*/

#ifdef __cplusplus
extern "C" {
#endif

#define ESP_WIFI_CRYPTO_VERSION 0x00000001

/*
 * 哈希操作的枚举。当WPA2正在连接时，此枚举用于通过crypto_hash_xxx函数请求哈希算法。
 */
typedef enum {
    ESP_CRYPTO_HASH_ALG_MD5, ESP_CRYPTO_HASH_ALG_SHA1,
    ESP_CRYPTO_HASH_ALG_HMAC_MD5, ESP_CRYPTO_HASH_ALG_HMAC_SHA1,
    ESP_CRYPTO_HASH_ALG_SHA256, ESP_CRYPTO_HASH_ALG_HMAC_SHA256
}esp_crypto_hash_alg_t;

/*
 * 分组密码操作的枚举。当WPA2正在连接时，此枚举用于通过crypto_cipher_xxx函数请求分组密码算法。
 */
typedef enum {
    ESP_CRYPTO_CIPHER_NULL, ESP_CRYPTO_CIPHER_ALG_AES, ESP_CRYPTO_CIPHER_ALG_3DES,
    ESP_CRYPTO_CIPHER_ALG_DES, ESP_CRYPTO_CIPHER_ALG_RC2, ESP_CRYPTO_CIPHER_ALG_RC4
} esp_crypto_cipher_alg_t;

/*
 * 此结构与执行crypt_hash操作时的算法有关，详细信息请参考crypt_ash结构。
 */
typedef struct crypto_hash esp_crypto_hash_t;

/*
 * 该结构是关于crypto_cipher操作时的算法，详细信息请参考crypto_cipher结构。
 */
typedef struct crypto_cipher esp_crypto_cipher_t;

/**
  * @brief WPS连接时的AES回调函数。
  *
  * @param key  加密密钥。
  * @param iv  CBC模式的加密IV（16字节）。
  * @param data  要就地加密的数据。
  * @param data_len  数据长度（以字节为单位）（必须可被16整除）
  */
typedef int (*esp_aes_128_encrypt_t)(const unsigned char *key, const unsigned char *iv, unsigned char *data, int data_len);

/**
  * @brief WPS连接时的AES回调函数。
  *
  * @param key  解密密钥。
  * @param iv  CBC模式的解密IV（16字节）。
  * @param data  要就地解密的数据。
  * @param data_len  数据长度（以字节为单位）（必须可被16整除）
  *
  */
typedef int (*esp_aes_128_decrypt_t)(const unsigned char *key, const unsigned char *iv, unsigned char *data, int data_len);

/**
  * @brief STA连接时的AES回调函数。
  *
  * @param kek  16位字节密钥加密密钥（KEK）。
  * @param n  明文密钥的长度，以64位为单位；
  * @param plain  要包装的明文密钥，n*64位
  * @param cipher  包装密钥，（n+1）*64位
  *
  */
typedef int (*esp_aes_wrap_t)(const unsigned char *kek, int n, const unsigned char *plain, unsigned char *cipher);

/**
  * @brief STA连接时的AES回调函数。
  *
  * @param kek  16八位字节密钥解密密钥（KEK）。
  * @param n  明文密钥的长度，以64位为单位；
  * @param cipher  要展开的包装密钥，（n+1）*64位
  * @param plain  明文密钥，n*64位
  *
  */
typedef int (*esp_aes_unwrap_t)(const unsigned char *kek, int n, const unsigned char *cipher, unsigned char *plain);

/**
  * @brief WPS连接时的SHA256回调函数。
  *
  * @param key  HMAC操作键。
  * @param key_len  密钥的长度（字节）。
  * @param num_elem  数据向量中的元素数。
  * @param addr  指向数据区域的指针。
  * @param len  数据块的长度。
  * @param mac  哈希的缓冲区（32字节）。
  *
  */
typedef int (*esp_hmac_sha256_vector_t)(const unsigned char *key, int key_len, int num_elem,
			                   const unsigned char *addr[], const int *len, unsigned char *mac);

/**
  * @brief STA连接时的AES回调函数。
  *
  * @param key  PRF键。
  * @param key_len  密钥的长度（字节）。
  * @param label  PRF各用途的唯一标签。
  * @param data  要绑定到密钥的额外数据。
  * @param data_len  数据的长度。
  * @param buf  生成的伪随机密钥的缓冲区。
  * @param buf_len  要生成的密钥的字节数。
  *
  */
typedef int (*esp_sha256_prf_t)(const unsigned char *key, int key_len, const char *label,
	                           const unsigned char *data, int data_len, unsigned char *buf, int buf_len);

/**
 * @brief 数据缓冲区上的HMAC-MD5（RFC 2104）'
 *
 * @key: HMAC操作密钥
 * @key_len: 密钥长度（字节）
 * @data: 指向数据区域的指针
 * @data_len: 数据区域的长度
 * @mac: 哈希缓冲区（16字节）返回：成功时为0，失败时为-1
 */
typedef int (*esp_hmac_md5_t)(const unsigned char *key, unsigned int key_len, const unsigned char *data,
                              unsigned int data_len, unsigned char *mac);

/**
 * @brief 数据向量上的HMAC-MD5（RFC 2104）
 *
 * @key: HMAC操作密钥
 * @key_len: 密钥长度（字节）
 * @num_elem: 数据向量中的元素数
 * @addr: 指向数据区域的指针
 * @len: 数据块的长度
 * @mac: 哈希缓冲区（16字节）返回：成功时为0，失败时为-1
 */
typedef int (*esp_hmac_md5_vector_t)(const unsigned char *key, unsigned int key_len, unsigned int num_elem,
                              const unsigned char *addr[], const unsigned int *len, unsigned char *mac);

/**
 * @brief 数据缓冲区上的HMAC-SHA1（RFC 2104）
 *
 * @key: HMAC操作密钥
 * @key_len: 密钥长度（字节）
 * @data: 指向数据区域的指针
 * @data_len: 数据区域的长度
 * @mac: 哈希缓冲区（20字节）返回：成功时为0，失败时为-1
 */
typedef int (*esp_hmac_sha1_t)(const unsigned char *key, unsigned int key_len, const unsigned char *data,
                              unsigned int data_len, unsigned char *mac);

/**
 * @brief 数据矢量上的HMAC-SHA1（RFC 2104）
 *
 * @key: HMAC操作密钥
 * @key_len: 密钥长度（字节）
 * @num_elem: 数据向量中的元素数
 * @addr: 指向数据区域的指针
 * @len: 数据块的长度
 * @mac: 哈希缓冲区（20字节）返回：成功时为0，失败时为-1
 */
typedef int (*esp_hmac_sha1_vector_t)(const unsigned char *key, unsigned int key_len, unsigned int num_elem,
                              const unsigned char *addr[], const unsigned int *len, unsigned char *mac);

/**
 * @brief 基于SHA1的伪随机函数（PRF）（IEEE 802.11i，8.5.1.1）
 *
 * @key: PRF键
 * @key_len: 密钥长度（字节）
 * @label: PRF各用途的唯一标签
 * @data: 要绑定到密钥的额外数据
 * @data_len: 数据的长度
 * @buf: 生成的伪随机密钥的缓冲区
 * @buf_len: 要生成的密钥的字节数返回：成功时为0，失败时为-1
 *
 * 此函数用于从给定密钥（例如，IEEE 802.11i中的PMK）导出新的、加密分离的密钥。
 */
typedef int (*esp_sha1_prf_t)(const unsigned char *key, unsigned int key_len, const char *label,
                              const unsigned char *data, unsigned int data_len, unsigned char *buf, unsigned int buf_len);

/**
 * @brief 数据向量的SHA-1哈希
 *
 * @num_elem: 数据向量中的元素数
 * @addr: 指向数据区域的指针
 * @len: 数据块的长度
 * @mac: 哈希返回的缓冲区：成功时为0，失败时为-1
 */
typedef int (*esp_sha1_vector_t)(unsigned int num_elem, const unsigned char *addr[], const unsigned int *len,
                              unsigned char *mac);

/**
 * @brief IEEE 802.11i中基于SHA1的密钥导出函数（PBKDF2）
 *
 * @passphrase: ASCII密码
 * @ssid: SSID
 * @ssid_len: SSID长度（字节）
 * @iterations: 要运行的迭代次数
 * @buf: 生成密钥的缓冲区
 * @buflen: 缓冲区长度（字节）：成功时返回0，失败时返回-1
 *
 * 此函数用于导出WPA-PSK的PSK。对于该协议，迭代次数设置为4096，buflen设置为32。IEEE Std 802.11-2004第H.4条中描述了该功能。主要结构来自PKCS#5 v2.0。
 */
typedef int (*esp_pbkdf2_sha1_t)(const char *passphrase, const char *ssid, unsigned int ssid_len,
                              int iterations, unsigned char *buf, unsigned int buflen);

/**
 * @brief 用跳过流开始将RC4流与给定数据进行异或
 *
 * @key: RC4键
 * @keylen: RC4密钥长度
 * @skip: 从RC4流开始跳过的字节数
 * @data: 要与RC4流进行异或的数据
 * @data_len: buf长度返回：成功时返回0，失败时返回-1
 *
 * 为给定密钥生成RC4伪随机流，跳过流的开头，并将最终结果与数据缓冲区进行XOR，以执行RC4加密/解密。
 */
typedef int (*esp_rc4_skip_t)(const unsigned char *key, unsigned int keylen, unsigned int skip,
                              unsigned char *data, unsigned int data_len);

/**
 * @brief 数据向量的MD5哈希
 *
 * @num_elem: 数据向量中的元素数
 * @addr: 指向数据区域的指针
 * @len: 数据块的长度
 * @mac: 哈希返回的缓冲区：成功时为0，失败时为-1
 */
typedef int (*esp_md5_vector_t)(unsigned int num_elem, const unsigned char *addr[], const unsigned int *len,
                              unsigned char *mac);

/**
 * @brief 加密一个AES块
 *
 * @ctx: aes_encrypt_init（）中的上下文指针
 * @plain: 要加密的明文数据（16字节）
 * @crypt: 加密数据缓冲区（16字节）
 */
typedef void (*esp_aes_encrypt_t)(void *ctx, const unsigned char *plain, unsigned char *crypt);

/**
 * @brief 初始化AES进行加密
 *
 * @key: 加密密钥
 * @len: 以字节为单位的密钥长度（通常为16，即128位）返回：指向上下文数据的指针或失败时的%NULL
 */
typedef void * (*esp_aes_encrypt_init_t)(const unsigned char *key,  unsigned int len);

/**
 * @brief 取消初始化AES加密
 *
 * @ctx: aes_encrypt_init（）中的上下文指针
 */
typedef void (*esp_aes_encrypt_deinit_t)(void *ctx);

/**
 * @brief 解密一个AES块
 *
 * @ctx: aes_encrypt_init（）中的上下文指针
 * @crypt: 加密数据（16字节）
 * @plain: 解密数据的缓冲区（16字节）
 */
typedef void (*esp_aes_decrypt_t)(void *ctx, const unsigned char *crypt, unsigned char *plain);

/**
 * @brief 初始化AES以进行解密
 *
 * @key: 解密钥匙
 * @len: 以字节为单位的密钥长度（通常为16，即128位）返回：指向上下文数据的指针或失败时的%NULL
 */
typedef void * (*esp_aes_decrypt_init_t)(const unsigned char *key, unsigned int len);

/**
 * @brief 取消初始化AES解密
 *
 * @ctx: aes_encrypt_init（）中的上下文指针
 */
typedef void (*esp_aes_decrypt_deinit_t)(void *ctx);

/**
 * @brief 用于MIC计算的带有AES-128的一键CBC MAC（OMAC1）散列
 *
 * @key: 哈希操作的128位密钥
 * @data: 计算MIC的数据缓冲区
 * @data_len: 数据缓冲区长度（字节）
 * @mic: MIC缓冲区（128位，即16字节）返回：成功时为0，失败时为-1
 */
typedef int (*esp_omac1_aes_128_t)(const uint8_t *key, const uint8_t *data, size_t data_len,
                                   uint8_t *mic);

/**
 * @brief 使用IEEE 802.11i RSN标准中使用的CCMP（计数器模式CBC-MAC协议或计数器模式密码块链接消息认证码协议）对数据进行解密。
 * @tk: 在4次握手期间获得的128位临时密钥
 * @hdr: 指向AAD所需的IEEE802.11帧头的指针
 * @data: 指向加密数据缓冲区的指针
 * @data_len: 加密数据长度（字节）
 * @decrypted_len: 解密数据的长度
 * @espnow_pkt: 指示是否为ESPNOW数据包返回：成功时指向解密数据的指针，失败时返回NULL
 */
typedef uint8_t * (*esp_ccmp_decrypt_t)(const uint8_t *tk, const uint8_t *ieee80211_hdr,
                                        const uint8_t *data, size_t data_len,
                                        size_t *decrypted_len, bool espnow_pkt);

/**
 * @brief 使用IEEE 802.11i RSN标准中使用的CCMP（计数器模式CBC-MAC协议或计数器模式密码块链接消息认证码协议）加密数据。
 * @tk: 在4次握手期间获得的128位临时密钥
 * @frame: 指向IEEE802.11帧（包括报头）的指针
 * @len: 框架长度（包括收割台）
 * @hdrlen: 收割台长度
 * @pn: 数据包编号计数器
 * @keyid: CCMP矢量中提及的密钥ID
 * @encrypted_len: 包含标头的加密帧的长度
 */
typedef uint8_t * (*esp_ccmp_encrypt_t)(const uint8_t *tk, uint8_t *frame, size_t len, size_t hdrlen,
                                        uint8_t *pn, int keyid, size_t *encrypted_len);

/**
 * @brief 用于MIC计算的带有AES的一键GMAC哈希
 *
 * @key: 哈希操作的键
 * @keylen: 密钥长度
 * @iv: 初始化向量
 * @iv_len: 初始化向量长度
 * @aad: 阿拉伯联合酋长国
 * @aad_len: aad长度
 * @mic: MIC缓冲区（128位，即16字节）返回：成功时为0，失败时为-1
 */
typedef int (*esp_aes_gmac_t)(const uint8_t *key, size_t keylen, const uint8_t *iv, size_t iv_len,
                              const uint8_t *aad, size_t aad_len, uint8_t *mic);

/**
  * @brief 站点安全连接时使用的加密回调函数结构。该结构可以设置为软件密码或由ESP32硬件优化的密码。
  */
typedef struct {
    uint32_t size;
    uint32_t version;
    esp_aes_wrap_t aes_wrap;                         /**<发送EAPOL帧时使用的站点连接功能*/
    esp_aes_unwrap_t aes_unwrap;                     /**<解密密钥数据时使用的站点连接功能*/
    esp_hmac_sha256_vector_t hmac_sha256_vector;     /**<检查MIC时使用的站连接功能*/
    esp_sha256_prf_t sha256_prf;                     /**<检查MIC时使用的站连接功能*/
    esp_hmac_md5_t hmac_md5;
    esp_hmac_md5_vector_t hamc_md5_vector;
    esp_hmac_sha1_t hmac_sha1;
    esp_hmac_sha1_vector_t hmac_sha1_vector;
    esp_sha1_prf_t sha1_prf;
    esp_sha1_vector_t sha1_vector;
    esp_pbkdf2_sha1_t pbkdf2_sha1;
    esp_rc4_skip_t rc4_skip;
    esp_md5_vector_t md5_vector;
    esp_aes_encrypt_t aes_encrypt;
    esp_aes_encrypt_init_t aes_encrypt_init;
    esp_aes_encrypt_deinit_t aes_encrypt_deinit;
    esp_aes_decrypt_t aes_decrypt;
    esp_aes_decrypt_init_t aes_decrypt_init;
    esp_aes_decrypt_deinit_t aes_decrypt_deinit;
    esp_aes_128_encrypt_t aes_128_encrypt;
    esp_aes_128_decrypt_t aes_128_decrypt;
    esp_omac1_aes_128_t omac1_aes_128;
    esp_ccmp_decrypt_t ccmp_decrypt;
    esp_ccmp_encrypt_t ccmp_encrypt;
    esp_aes_gmac_t aes_gmac;
}wpa_crypto_funcs_t;

/**
  * @brief 网格供应商IE加密中使用的加密回调函数结构。该结构可以设置为软件密码或由ESP32硬件优化的密码。
  */
typedef struct{
    esp_aes_128_encrypt_t aes_128_encrypt;          /**<网格供应商IE加密中使用的函数*/
    esp_aes_128_decrypt_t aes_128_decrypt;          /**<网格供应商IE解密中使用的函数*/
} mesh_crypto_funcs_t;

#ifdef __cplusplus
}
#endif
#endif

