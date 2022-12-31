/**
 * \文件ssl_ciphersuites.h
 *
 * \用于mbed TLS的简短SSL密码套件
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
#ifndef MBEDTLS_SSL_CIPHERSUITES_H
#define MBEDTLS_SSL_CIPHERSUITES_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/pk.h"
#include "mbedtls/cipher.h"
#include "mbedtls/md.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * 支持的密码套件（IANA官方名称）
 */
#define MBEDTLS_TLS_RSA_WITH_NULL_MD5                    0x01   /**<弱！*/
#define MBEDTLS_TLS_RSA_WITH_NULL_SHA                    0x02   /**<弱！*/

#define MBEDTLS_TLS_RSA_WITH_RC4_128_MD5                 0x04
#define MBEDTLS_TLS_RSA_WITH_RC4_128_SHA                 0x05
#define MBEDTLS_TLS_RSA_WITH_DES_CBC_SHA                 0x09   /**<弱！不在TLS 1.2中*/

#define MBEDTLS_TLS_RSA_WITH_3DES_EDE_CBC_SHA            0x0A

#define MBEDTLS_TLS_DHE_RSA_WITH_DES_CBC_SHA             0x15   /**<弱！不在TLS 1.2中*/
#define MBEDTLS_TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA        0x16

#define MBEDTLS_TLS_PSK_WITH_NULL_SHA                    0x2C   /**<弱！*/
#define MBEDTLS_TLS_DHE_PSK_WITH_NULL_SHA                0x2D   /**<弱！*/
#define MBEDTLS_TLS_RSA_PSK_WITH_NULL_SHA                0x2E   /**<弱！*/
#define MBEDTLS_TLS_RSA_WITH_AES_128_CBC_SHA             0x2F

#define MBEDTLS_TLS_DHE_RSA_WITH_AES_128_CBC_SHA         0x33
#define MBEDTLS_TLS_RSA_WITH_AES_256_CBC_SHA             0x35
#define MBEDTLS_TLS_DHE_RSA_WITH_AES_256_CBC_SHA         0x39

#define MBEDTLS_TLS_RSA_WITH_NULL_SHA256                 0x3B   /**<弱！*/
#define MBEDTLS_TLS_RSA_WITH_AES_128_CBC_SHA256          0x3C   /**< TLS 1.2 */
#define MBEDTLS_TLS_RSA_WITH_AES_256_CBC_SHA256          0x3D   /**< TLS 1.2 */

#define MBEDTLS_TLS_RSA_WITH_CAMELLIA_128_CBC_SHA        0x41
#define MBEDTLS_TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA    0x45

#define MBEDTLS_TLS_DHE_RSA_WITH_AES_128_CBC_SHA256      0x67   /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_RSA_WITH_AES_256_CBC_SHA256      0x6B   /**< TLS 1.2 */

#define MBEDTLS_TLS_RSA_WITH_CAMELLIA_256_CBC_SHA        0x84
#define MBEDTLS_TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA    0x88

#define MBEDTLS_TLS_PSK_WITH_RC4_128_SHA                 0x8A
#define MBEDTLS_TLS_PSK_WITH_3DES_EDE_CBC_SHA            0x8B
#define MBEDTLS_TLS_PSK_WITH_AES_128_CBC_SHA             0x8C
#define MBEDTLS_TLS_PSK_WITH_AES_256_CBC_SHA             0x8D

#define MBEDTLS_TLS_DHE_PSK_WITH_RC4_128_SHA             0x8E
#define MBEDTLS_TLS_DHE_PSK_WITH_3DES_EDE_CBC_SHA        0x8F
#define MBEDTLS_TLS_DHE_PSK_WITH_AES_128_CBC_SHA         0x90
#define MBEDTLS_TLS_DHE_PSK_WITH_AES_256_CBC_SHA         0x91

#define MBEDTLS_TLS_RSA_PSK_WITH_RC4_128_SHA             0x92
#define MBEDTLS_TLS_RSA_PSK_WITH_3DES_EDE_CBC_SHA        0x93
#define MBEDTLS_TLS_RSA_PSK_WITH_AES_128_CBC_SHA         0x94
#define MBEDTLS_TLS_RSA_PSK_WITH_AES_256_CBC_SHA         0x95

#define MBEDTLS_TLS_RSA_WITH_AES_128_GCM_SHA256          0x9C   /**< TLS 1.2 */
#define MBEDTLS_TLS_RSA_WITH_AES_256_GCM_SHA384          0x9D   /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_RSA_WITH_AES_128_GCM_SHA256      0x9E   /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_RSA_WITH_AES_256_GCM_SHA384      0x9F   /**< TLS 1.2 */

#define MBEDTLS_TLS_PSK_WITH_AES_128_GCM_SHA256          0xA8   /**< TLS 1.2 */
#define MBEDTLS_TLS_PSK_WITH_AES_256_GCM_SHA384          0xA9   /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_PSK_WITH_AES_128_GCM_SHA256      0xAA   /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_PSK_WITH_AES_256_GCM_SHA384      0xAB   /**< TLS 1.2 */
#define MBEDTLS_TLS_RSA_PSK_WITH_AES_128_GCM_SHA256      0xAC   /**< TLS 1.2 */
#define MBEDTLS_TLS_RSA_PSK_WITH_AES_256_GCM_SHA384      0xAD   /**< TLS 1.2 */

#define MBEDTLS_TLS_PSK_WITH_AES_128_CBC_SHA256          0xAE
#define MBEDTLS_TLS_PSK_WITH_AES_256_CBC_SHA384          0xAF
#define MBEDTLS_TLS_PSK_WITH_NULL_SHA256                 0xB0   /**<弱！*/
#define MBEDTLS_TLS_PSK_WITH_NULL_SHA384                 0xB1   /**<弱！*/

#define MBEDTLS_TLS_DHE_PSK_WITH_AES_128_CBC_SHA256      0xB2
#define MBEDTLS_TLS_DHE_PSK_WITH_AES_256_CBC_SHA384      0xB3
#define MBEDTLS_TLS_DHE_PSK_WITH_NULL_SHA256             0xB4   /**<弱！*/
#define MBEDTLS_TLS_DHE_PSK_WITH_NULL_SHA384             0xB5   /**<弱！*/

#define MBEDTLS_TLS_RSA_PSK_WITH_AES_128_CBC_SHA256      0xB6
#define MBEDTLS_TLS_RSA_PSK_WITH_AES_256_CBC_SHA384      0xB7
#define MBEDTLS_TLS_RSA_PSK_WITH_NULL_SHA256             0xB8   /**<弱！*/
#define MBEDTLS_TLS_RSA_PSK_WITH_NULL_SHA384             0xB9   /**<弱！*/

#define MBEDTLS_TLS_RSA_WITH_CAMELLIA_128_CBC_SHA256     0xBA   /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA256 0xBE   /**< TLS 1.2 */

#define MBEDTLS_TLS_RSA_WITH_CAMELLIA_256_CBC_SHA256     0xC0   /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA256 0xC4   /**< TLS 1.2 */

#define MBEDTLS_TLS_ECDH_ECDSA_WITH_NULL_SHA             0xC001 /**<弱！*/
#define MBEDTLS_TLS_ECDH_ECDSA_WITH_RC4_128_SHA          0xC002 /**<不在SSL3中！*/
#define MBEDTLS_TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA     0xC003 /**<不在SSL3中！*/
#define MBEDTLS_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA      0xC004 /**<不在SSL3中！*/
#define MBEDTLS_TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA      0xC005 /**<不在SSL3中！*/

#define MBEDTLS_TLS_ECDHE_ECDSA_WITH_NULL_SHA            0xC006 /**<弱！*/
#define MBEDTLS_TLS_ECDHE_ECDSA_WITH_RC4_128_SHA         0xC007 /**<不在SSL3中！*/
#define MBEDTLS_TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA    0xC008 /**<不在SSL3中！*/
#define MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA     0xC009 /**<不在SSL3中！*/
#define MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA     0xC00A /**<不在SSL3中！*/

#define MBEDTLS_TLS_ECDH_RSA_WITH_NULL_SHA               0xC00B /**<弱！*/
#define MBEDTLS_TLS_ECDH_RSA_WITH_RC4_128_SHA            0xC00C /**<不在SSL3中！*/
#define MBEDTLS_TLS_ECDH_RSA_WITH_3DES_EDE_CBC_SHA       0xC00D /**<不在SSL3中！*/
#define MBEDTLS_TLS_ECDH_RSA_WITH_AES_128_CBC_SHA        0xC00E /**<不在SSL3中！*/
#define MBEDTLS_TLS_ECDH_RSA_WITH_AES_256_CBC_SHA        0xC00F /**<不在SSL3中！*/

#define MBEDTLS_TLS_ECDHE_RSA_WITH_NULL_SHA              0xC010 /**<弱！*/
#define MBEDTLS_TLS_ECDHE_RSA_WITH_RC4_128_SHA           0xC011 /**<不在SSL3中！*/
#define MBEDTLS_TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA      0xC012 /**<不在SSL3中！*/
#define MBEDTLS_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA       0xC013 /**<不在SSL3中！*/
#define MBEDTLS_TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA       0xC014 /**<不在SSL3中！*/

#define MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256  0xC023 /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384  0xC024 /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256   0xC025 /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384   0xC026 /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256    0xC027 /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384    0xC028 /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256     0xC029 /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384     0xC02A /**< TLS 1.2 */

#define MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256  0xC02B /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384  0xC02C /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256   0xC02D /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384   0xC02E /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256    0xC02F /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384    0xC030 /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256     0xC031 /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384     0xC032 /**< TLS 1.2 */

#define MBEDTLS_TLS_ECDHE_PSK_WITH_RC4_128_SHA           0xC033 /**<不在SSL3中！*/
#define MBEDTLS_TLS_ECDHE_PSK_WITH_3DES_EDE_CBC_SHA      0xC034 /**<不在SSL3中！*/
#define MBEDTLS_TLS_ECDHE_PSK_WITH_AES_128_CBC_SHA       0xC035 /**<不在SSL3中！*/
#define MBEDTLS_TLS_ECDHE_PSK_WITH_AES_256_CBC_SHA       0xC036 /**<不在SSL3中！*/
#define MBEDTLS_TLS_ECDHE_PSK_WITH_AES_128_CBC_SHA256    0xC037 /**<不在SSL3中！*/
#define MBEDTLS_TLS_ECDHE_PSK_WITH_AES_256_CBC_SHA384    0xC038 /**<不在SSL3中！*/
#define MBEDTLS_TLS_ECDHE_PSK_WITH_NULL_SHA              0xC039 /**<弱！没有SSL3！*/
#define MBEDTLS_TLS_ECDHE_PSK_WITH_NULL_SHA256           0xC03A /**<弱！没有SSL3！*/
#define MBEDTLS_TLS_ECDHE_PSK_WITH_NULL_SHA384           0xC03B /**<弱！没有SSL3！*/

#define MBEDTLS_TLS_RSA_WITH_ARIA_128_CBC_SHA256         0xC03C /**< TLS 1.2 */
#define MBEDTLS_TLS_RSA_WITH_ARIA_256_CBC_SHA384         0xC03D /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_RSA_WITH_ARIA_128_CBC_SHA256     0xC044 /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_RSA_WITH_ARIA_256_CBC_SHA384     0xC045 /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDHE_ECDSA_WITH_ARIA_128_CBC_SHA256 0xC048 /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDHE_ECDSA_WITH_ARIA_256_CBC_SHA384 0xC049 /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDH_ECDSA_WITH_ARIA_128_CBC_SHA256  0xC04A /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDH_ECDSA_WITH_ARIA_256_CBC_SHA384  0xC04B /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDHE_RSA_WITH_ARIA_128_CBC_SHA256   0xC04C /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDHE_RSA_WITH_ARIA_256_CBC_SHA384   0xC04D /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDH_RSA_WITH_ARIA_128_CBC_SHA256    0xC04E /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDH_RSA_WITH_ARIA_256_CBC_SHA384    0xC04F /**< TLS 1.2 */
#define MBEDTLS_TLS_RSA_WITH_ARIA_128_GCM_SHA256         0xC050 /**< TLS 1.2 */
#define MBEDTLS_TLS_RSA_WITH_ARIA_256_GCM_SHA384         0xC051 /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_RSA_WITH_ARIA_128_GCM_SHA256     0xC052 /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_RSA_WITH_ARIA_256_GCM_SHA384     0xC053 /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDHE_ECDSA_WITH_ARIA_128_GCM_SHA256 0xC05C /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDHE_ECDSA_WITH_ARIA_256_GCM_SHA384 0xC05D /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDH_ECDSA_WITH_ARIA_128_GCM_SHA256  0xC05E /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDH_ECDSA_WITH_ARIA_256_GCM_SHA384  0xC05F /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDHE_RSA_WITH_ARIA_128_GCM_SHA256   0xC060 /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDHE_RSA_WITH_ARIA_256_GCM_SHA384   0xC061 /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDH_RSA_WITH_ARIA_128_GCM_SHA256    0xC062 /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDH_RSA_WITH_ARIA_256_GCM_SHA384    0xC063 /**< TLS 1.2 */
#define MBEDTLS_TLS_PSK_WITH_ARIA_128_CBC_SHA256         0xC064 /**< TLS 1.2 */
#define MBEDTLS_TLS_PSK_WITH_ARIA_256_CBC_SHA384         0xC065 /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_PSK_WITH_ARIA_128_CBC_SHA256     0xC066 /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_PSK_WITH_ARIA_256_CBC_SHA384     0xC067 /**< TLS 1.2 */
#define MBEDTLS_TLS_RSA_PSK_WITH_ARIA_128_CBC_SHA256     0xC068 /**< TLS 1.2 */
#define MBEDTLS_TLS_RSA_PSK_WITH_ARIA_256_CBC_SHA384     0xC069 /**< TLS 1.2 */
#define MBEDTLS_TLS_PSK_WITH_ARIA_128_GCM_SHA256         0xC06A /**< TLS 1.2 */
#define MBEDTLS_TLS_PSK_WITH_ARIA_256_GCM_SHA384         0xC06B /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_PSK_WITH_ARIA_128_GCM_SHA256     0xC06C /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_PSK_WITH_ARIA_256_GCM_SHA384     0xC06D /**< TLS 1.2 */
#define MBEDTLS_TLS_RSA_PSK_WITH_ARIA_128_GCM_SHA256     0xC06E /**< TLS 1.2 */
#define MBEDTLS_TLS_RSA_PSK_WITH_ARIA_256_GCM_SHA384     0xC06F /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDHE_PSK_WITH_ARIA_128_CBC_SHA256   0xC070 /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDHE_PSK_WITH_ARIA_256_CBC_SHA384   0xC071 /**< TLS 1.2 */

#define MBEDTLS_TLS_ECDHE_ECDSA_WITH_CAMELLIA_128_CBC_SHA256 0xC072 /**<不在SSL3中！*/
#define MBEDTLS_TLS_ECDHE_ECDSA_WITH_CAMELLIA_256_CBC_SHA384 0xC073 /**<不在SSL3中！*/
#define MBEDTLS_TLS_ECDH_ECDSA_WITH_CAMELLIA_128_CBC_SHA256  0xC074 /**<不在SSL3中！*/
#define MBEDTLS_TLS_ECDH_ECDSA_WITH_CAMELLIA_256_CBC_SHA384  0xC075 /**<不在SSL3中！*/
#define MBEDTLS_TLS_ECDHE_RSA_WITH_CAMELLIA_128_CBC_SHA256   0xC076 /**<不在SSL3中！*/
#define MBEDTLS_TLS_ECDHE_RSA_WITH_CAMELLIA_256_CBC_SHA384   0xC077 /**<不在SSL3中！*/
#define MBEDTLS_TLS_ECDH_RSA_WITH_CAMELLIA_128_CBC_SHA256    0xC078 /**<不在SSL3中！*/
#define MBEDTLS_TLS_ECDH_RSA_WITH_CAMELLIA_256_CBC_SHA384    0xC079 /**<不在SSL3中！*/

#define MBEDTLS_TLS_RSA_WITH_CAMELLIA_128_GCM_SHA256         0xC07A /**< TLS 1.2 */
#define MBEDTLS_TLS_RSA_WITH_CAMELLIA_256_GCM_SHA384         0xC07B /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_RSA_WITH_CAMELLIA_128_GCM_SHA256     0xC07C /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_RSA_WITH_CAMELLIA_256_GCM_SHA384     0xC07D /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDHE_ECDSA_WITH_CAMELLIA_128_GCM_SHA256 0xC086 /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDHE_ECDSA_WITH_CAMELLIA_256_GCM_SHA384 0xC087 /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDH_ECDSA_WITH_CAMELLIA_128_GCM_SHA256  0xC088 /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDH_ECDSA_WITH_CAMELLIA_256_GCM_SHA384  0xC089 /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDHE_RSA_WITH_CAMELLIA_128_GCM_SHA256   0xC08A /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDHE_RSA_WITH_CAMELLIA_256_GCM_SHA384   0xC08B /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDH_RSA_WITH_CAMELLIA_128_GCM_SHA256    0xC08C /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDH_RSA_WITH_CAMELLIA_256_GCM_SHA384    0xC08D /**< TLS 1.2 */

#define MBEDTLS_TLS_PSK_WITH_CAMELLIA_128_GCM_SHA256       0xC08E /**< TLS 1.2 */
#define MBEDTLS_TLS_PSK_WITH_CAMELLIA_256_GCM_SHA384       0xC08F /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_PSK_WITH_CAMELLIA_128_GCM_SHA256   0xC090 /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_PSK_WITH_CAMELLIA_256_GCM_SHA384   0xC091 /**< TLS 1.2 */
#define MBEDTLS_TLS_RSA_PSK_WITH_CAMELLIA_128_GCM_SHA256   0xC092 /**< TLS 1.2 */
#define MBEDTLS_TLS_RSA_PSK_WITH_CAMELLIA_256_GCM_SHA384   0xC093 /**< TLS 1.2 */

#define MBEDTLS_TLS_PSK_WITH_CAMELLIA_128_CBC_SHA256       0xC094
#define MBEDTLS_TLS_PSK_WITH_CAMELLIA_256_CBC_SHA384       0xC095
#define MBEDTLS_TLS_DHE_PSK_WITH_CAMELLIA_128_CBC_SHA256   0xC096
#define MBEDTLS_TLS_DHE_PSK_WITH_CAMELLIA_256_CBC_SHA384   0xC097
#define MBEDTLS_TLS_RSA_PSK_WITH_CAMELLIA_128_CBC_SHA256   0xC098
#define MBEDTLS_TLS_RSA_PSK_WITH_CAMELLIA_256_CBC_SHA384   0xC099
#define MBEDTLS_TLS_ECDHE_PSK_WITH_CAMELLIA_128_CBC_SHA256 0xC09A /**<不在SSL3中！*/
#define MBEDTLS_TLS_ECDHE_PSK_WITH_CAMELLIA_256_CBC_SHA384 0xC09B /**<不在SSL3中！*/

#define MBEDTLS_TLS_RSA_WITH_AES_128_CCM                0xC09C  /**< TLS 1.2 */
#define MBEDTLS_TLS_RSA_WITH_AES_256_CCM                0xC09D  /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_RSA_WITH_AES_128_CCM            0xC09E  /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_RSA_WITH_AES_256_CCM            0xC09F  /**< TLS 1.2 */
#define MBEDTLS_TLS_RSA_WITH_AES_128_CCM_8              0xC0A0  /**< TLS 1.2 */
#define MBEDTLS_TLS_RSA_WITH_AES_256_CCM_8              0xC0A1  /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_RSA_WITH_AES_128_CCM_8          0xC0A2  /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_RSA_WITH_AES_256_CCM_8          0xC0A3  /**< TLS 1.2 */
#define MBEDTLS_TLS_PSK_WITH_AES_128_CCM                0xC0A4  /**< TLS 1.2 */
#define MBEDTLS_TLS_PSK_WITH_AES_256_CCM                0xC0A5  /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_PSK_WITH_AES_128_CCM            0xC0A6  /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_PSK_WITH_AES_256_CCM            0xC0A7  /**< TLS 1.2 */
#define MBEDTLS_TLS_PSK_WITH_AES_128_CCM_8              0xC0A8  /**< TLS 1.2 */
#define MBEDTLS_TLS_PSK_WITH_AES_256_CCM_8              0xC0A9  /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_PSK_WITH_AES_128_CCM_8          0xC0AA  /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_PSK_WITH_AES_256_CCM_8          0xC0AB  /**< TLS 1.2 */
/* 最后两个在RFC中用PSK_DHE命名，看起来像是拼写错误*/

#define MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_128_CCM        0xC0AC  /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_256_CCM        0xC0AD  /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_128_CCM_8      0xC0AE  /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_256_CCM_8      0xC0AF  /**< TLS 1.2 */

#define MBEDTLS_TLS_ECJPAKE_WITH_AES_128_CCM_8          0xC0FF  /**<实验性*/

/* RFC 7905 */
#define MBEDTLS_TLS_ECDHE_RSA_WITH_CHACHA20_POLY1305_SHA256   0xCCA8 /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDHE_ECDSA_WITH_CHACHA20_POLY1305_SHA256 0xCCA9 /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_RSA_WITH_CHACHA20_POLY1305_SHA256     0xCCAA /**< TLS 1.2 */
#define MBEDTLS_TLS_PSK_WITH_CHACHA20_POLY1305_SHA256         0xCCAB /**< TLS 1.2 */
#define MBEDTLS_TLS_ECDHE_PSK_WITH_CHACHA20_POLY1305_SHA256   0xCCAC /**< TLS 1.2 */
#define MBEDTLS_TLS_DHE_PSK_WITH_CHACHA20_POLY1305_SHA256     0xCCAD /**< TLS 1.2 */
#define MBEDTLS_TLS_RSA_PSK_WITH_CHACHA20_POLY1305_SHA256     0xCCAE /**< TLS 1.2 */

/* 提醒：添加新密钥交换时更新mbedtls_ssl_premaster_secret。提醒：更新下面的MBEDTLS_KEY_EXCHANGE__xxx
 */
typedef enum {
    MBEDTLS_KEY_EXCHANGE_NONE = 0,
    MBEDTLS_KEY_EXCHANGE_RSA,
    MBEDTLS_KEY_EXCHANGE_DHE_RSA,
    MBEDTLS_KEY_EXCHANGE_ECDHE_RSA,
    MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA,
    MBEDTLS_KEY_EXCHANGE_PSK,
    MBEDTLS_KEY_EXCHANGE_DHE_PSK,
    MBEDTLS_KEY_EXCHANGE_RSA_PSK,
    MBEDTLS_KEY_EXCHANGE_ECDHE_PSK,
    MBEDTLS_KEY_EXCHANGE_ECDH_RSA,
    MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA,
    MBEDTLS_KEY_EXCHANGE_ECJPAKE,
} mbedtls_key_exchange_type_t;

/* 使用证书进行密钥交换*/
#if defined(MBEDTLS_KEY_EXCHANGE_RSA_ENABLED)           || \
    defined(MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED)       || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED)     || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED)   || \
    defined(MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED)       || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED)      || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED)
#define MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED
#endif

/* 允许客户端证书请求的密钥交换*/
#if defined(MBEDTLS_KEY_EXCHANGE_RSA_ENABLED)           ||       \
    defined(MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED)       ||       \
    defined(MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED)      ||       \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED)     ||       \
    defined(MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED)    ||       \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED)
#define MBEDTLS_KEY_EXCHANGE_CERT_REQ_ALLOWED_ENABLED
#endif

/* ServerKeyExchange中涉及服务器签名的密钥交换*/
#if defined(MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED)       || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED)     || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED)
#define MBEDTLS_KEY_EXCHANGE_WITH_SERVER_SIGNATURE_ENABLED
#endif

/* 使用ECDH的密钥交换*/
#if defined(MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED)      || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED)
#define MBEDTLS_KEY_EXCHANGE_SOME_ECDH_ENABLED
#endif

/* 不涉及临时密钥的密钥交换*/
#if defined(MBEDTLS_KEY_EXCHANGE_RSA_ENABLED)           || \
    defined(MBEDTLS_KEY_EXCHANGE_PSK_ENABLED)           || \
    defined(MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED)       || \
    defined(MBEDTLS_KEY_EXCHANGE_SOME_ECDH_ENABLED)
#define MBEDTLS_KEY_EXCHANGE_SOME_NON_PFS_ENABLED
#endif

/* 涉及临时密钥的密钥交换*/
#if defined(MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED)       || \
    defined(MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED)       || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED)     || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED)     || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED)   || \
    defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
#define MBEDTLS_KEY_EXCHANGE_SOME_PFS_ENABLED
#endif

/* 使用PSK进行密钥交换*/
#if defined(MBEDTLS_KEY_EXCHANGE_PSK_ENABLED)           || \
    defined(MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED)       || \
    defined(MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED)       || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED)
#define MBEDTLS_KEY_EXCHANGE_SOME_PSK_ENABLED
#endif

/* 使用DHE进行密钥交换*/
#if defined(MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED)       || \
    defined(MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED)
#define MBEDTLS_KEY_EXCHANGE_SOME_DHE_ENABLED
#endif

/* 使用ECDHE进行密钥交换*/
#if defined(MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED)     || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED)   || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED)
#define MBEDTLS_KEY_EXCHANGE_SOME_ECDHE_ENABLED
#endif

typedef struct mbedtls_ssl_ciphersuite_t mbedtls_ssl_ciphersuite_t;

#define MBEDTLS_CIPHERSUITE_WEAK       0x01    /**<弱密码套件标志*/
#define MBEDTLS_CIPHERSUITE_SHORT_TAG  0x02    /**<短认证标签，例如CCM_8*/
#define MBEDTLS_CIPHERSUITE_NODTLS     0x04    /**<不能与DTLS一起使用*/

/**
 * \brief此结构用于存储密码组信息
 */
struct mbedtls_ssl_ciphersuite_t
{
    int id;
    const char * name;

    mbedtls_cipher_type_t cipher;
    mbedtls_md_type_t mac;
    mbedtls_key_exchange_type_t key_exchange;

    int min_major_ver;
    int min_minor_ver;
    int max_major_ver;
    int max_minor_ver;

    unsigned char flags;
};

const int *mbedtls_ssl_list_ciphersuites( void );

const mbedtls_ssl_ciphersuite_t *mbedtls_ssl_ciphersuite_from_string( const char *ciphersuite_name );
const mbedtls_ssl_ciphersuite_t *mbedtls_ssl_ciphersuite_from_id( int ciphersuite_id );

#if defined(MBEDTLS_PK_C)
mbedtls_pk_type_t mbedtls_ssl_get_ciphersuite_sig_pk_alg( const mbedtls_ssl_ciphersuite_t *info );
mbedtls_pk_type_t mbedtls_ssl_get_ciphersuite_sig_alg( const mbedtls_ssl_ciphersuite_t *info );
#endif

int mbedtls_ssl_ciphersuite_uses_ec( const mbedtls_ssl_ciphersuite_t *info );
int mbedtls_ssl_ciphersuite_uses_psk( const mbedtls_ssl_ciphersuite_t *info );

#if defined(MBEDTLS_KEY_EXCHANGE_SOME_PFS_ENABLED)
static inline int mbedtls_ssl_ciphersuite_has_pfs( const mbedtls_ssl_ciphersuite_t *info )
{
    switch( info->key_exchange )
    {
        case MBEDTLS_KEY_EXCHANGE_DHE_RSA:
        case MBEDTLS_KEY_EXCHANGE_DHE_PSK:
        case MBEDTLS_KEY_EXCHANGE_ECDHE_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDHE_PSK:
        case MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA:
        case MBEDTLS_KEY_EXCHANGE_ECJPAKE:
            return( 1 );

        default:
            return( 0 );
    }
}
#endif /* MBEDTLS_KEY_EXCHANGE_SOME_PFS_ENABLED */

#if defined(MBEDTLS_KEY_EXCHANGE_SOME_NON_PFS_ENABLED)
static inline int mbedtls_ssl_ciphersuite_no_pfs( const mbedtls_ssl_ciphersuite_t *info )
{
    switch( info->key_exchange )
    {
        case MBEDTLS_KEY_EXCHANGE_ECDH_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA:
        case MBEDTLS_KEY_EXCHANGE_RSA:
        case MBEDTLS_KEY_EXCHANGE_PSK:
        case MBEDTLS_KEY_EXCHANGE_RSA_PSK:
            return( 1 );

        default:
            return( 0 );
    }
}
#endif /* MBEDTLS_KEY_EXCHANGE_SOME_NON_PFS_ENABLED */

#if defined(MBEDTLS_KEY_EXCHANGE_SOME_ECDH_ENABLED)
static inline int mbedtls_ssl_ciphersuite_uses_ecdh( const mbedtls_ssl_ciphersuite_t *info )
{
    switch( info->key_exchange )
    {
        case MBEDTLS_KEY_EXCHANGE_ECDH_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA:
            return( 1 );

        default:
            return( 0 );
    }
}
#endif /* MBEDTLS_KEY_EXCHANGE_SOME_ECDH_ENABLED */

static inline int mbedtls_ssl_ciphersuite_cert_req_allowed( const mbedtls_ssl_ciphersuite_t *info )
{
    switch( info->key_exchange )
    {
        case MBEDTLS_KEY_EXCHANGE_RSA:
        case MBEDTLS_KEY_EXCHANGE_DHE_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDH_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDHE_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA:
        case MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA:
            return( 1 );

        default:
            return( 0 );
    }
}

static inline int mbedtls_ssl_ciphersuite_uses_srv_cert( const mbedtls_ssl_ciphersuite_t *info )
{
    switch( info->key_exchange )
    {
        case MBEDTLS_KEY_EXCHANGE_RSA:
        case MBEDTLS_KEY_EXCHANGE_RSA_PSK:
        case MBEDTLS_KEY_EXCHANGE_DHE_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDH_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDHE_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA:
        case MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA:
            return( 1 );

        default:
            return( 0 );
    }
}

#if defined(MBEDTLS_KEY_EXCHANGE_SOME_DHE_ENABLED)
static inline int mbedtls_ssl_ciphersuite_uses_dhe( const mbedtls_ssl_ciphersuite_t *info )
{
    switch( info->key_exchange )
    {
        case MBEDTLS_KEY_EXCHANGE_DHE_RSA:
        case MBEDTLS_KEY_EXCHANGE_DHE_PSK:
            return( 1 );

        default:
            return( 0 );
    }
}
#endif /* MBEDTLS_KEY_EXCHANGE_SOME_DHE_ENABLED) */

#if defined(MBEDTLS_KEY_EXCHANGE_SOME_ECDHE_ENABLED)
static inline int mbedtls_ssl_ciphersuite_uses_ecdhe( const mbedtls_ssl_ciphersuite_t *info )
{
    switch( info->key_exchange )
    {
        case MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA:
        case MBEDTLS_KEY_EXCHANGE_ECDHE_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDHE_PSK:
            return( 1 );

        default:
            return( 0 );
    }
}
#endif /* MBEDTLS_KEY_EXCHANGE_SOME_ECDHE_ENABLED) */

#if defined(MBEDTLS_KEY_EXCHANGE_WITH_SERVER_SIGNATURE_ENABLED)
static inline int mbedtls_ssl_ciphersuite_uses_server_signature( const mbedtls_ssl_ciphersuite_t *info )
{
    switch( info->key_exchange )
    {
        case MBEDTLS_KEY_EXCHANGE_DHE_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDHE_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA:
            return( 1 );

        default:
            return( 0 );
    }
}
#endif /* MBEDTLS_KEY_EXCHANGE_WITH_SERVER_SIGNATURE_ENABLED */

#ifdef __cplusplus
}
#endif

#endif /* ssl_密码套件.h*/

