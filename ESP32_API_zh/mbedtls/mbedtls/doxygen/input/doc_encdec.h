/**
 * \文件doc_encdec.h
 *
 * \简短的加密/解密模块文档文件。
 */
/*
 * 版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

/**
 * @addtogroup encdec_module加密/解密模块
 *
 * 加密/解密模块提供加密/解密功能。可以区分对称算法和非对称算法；对称密钥主要用于消息保密，而非对称密钥用于密钥交换和消息完整性。一些对称算法提供不同的分组密码模式，主要是用于短（64位）消息的电子代码簿（ECB）和提供长消息所需结构的密码块链（CBC）。此外，针对特定算法实现了密码反馈模式（CFB-128）流密码模式、计数器模式（CTR）和伽罗瓦计数器模式（GCM）。
 *
 * 所有对称加密算法都可以通过通用密码层访问（请参见\c mbedtls_cipher_setup（））。
 *
 * 非对称加密算法可通过通用公钥层访问（请参见\c mbedtls_pk_init（））。
 *
 * 提供了以下算法：
 * -对称：
 *   -AES（请参见\c mbedtls_AES_crypt_ecb（）、\c mbedls_AES_crypt_cbc（）、\ c mbedtls_AES_crypt _cfb128（）和\c mbedt ls_AES_crypt _ctr（））。
 *   -ARCFOUR（请参见\c mbedtls_arc4_crypt（））。
 *   -Blowfish/BF（请参见\c mbedtls_Blowfish_crypt_ecb（）、\c mbedtls_Blowfish_crypt_cbc（）、\ c mbedtls_Blowfish_cCrypt_cfb64（）和\c mbedt ls_blowish _crypt_ctr（））
 *   -山茶花（请参见\c mbedtls_Camellia_crypt_ecb（）、\c mbedt ls_cameliaa_crypt _cbc（）、\ c mbedtls_Camellia_crypt _cfb128（）和\c mbeds ls_camelia_crypto_ctr（））。
 *   -DES/3DES（请参见\c mbedtls_DES_crypt_ecb（）、\c mbedls_DES_crypt_cbc（）、\ec mbedtls_descs3_crypt_ecb（）和\c mbedt ls_des3_crypt _cbc（（））。
 *   -GCM（AES-GCM和CAMELLIA-GCM）（请参阅\c mbedtls_GCM_init（））
 *   -XTEA（请参见\c mbedtls_XTEA_crypt_ecb（））。
 * -不对称：
 *   -Diffie Hellman Merkle（请参见\c mbedtls_dhm_read_public（）、\c mbedt ls_dhm_make_public。
 *   -RSA（请参见\c mbedtls_RSA_public（）和\c mbedt ls_RSA_private（））。
 *   -GF（p）上的椭圆曲线（请参见\c mbedtls_ecp_point_init（））。
 *   -椭圆曲线数字签名算法（ECDSA）（请参见\cmbedtls_ECDSA_init（））。
 *   -椭圆曲线Diffie-Hellman（ECDH）（请参见\cmbedtls_ECDH_init（））。
 *
 * 该模块提供可用于提供保密性的加密/解密。
 *
 * 它还提供了可用于保密性、完整性、身份验证和不可否认性的非对称密钥功能。
 */

