/**
 * \文件oid.h
 *
 * \简要对象标识符（OID）数据库
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
#ifndef MBEDTLS_OID_H
#define MBEDTLS_OID_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/asn1.h"
#include "mbedtls/pk.h"

#include <stddef.h>

#if defined(MBEDTLS_CIPHER_C)
#include "mbedtls/cipher.h"
#endif

#if defined(MBEDTLS_MD_C)
#include "mbedtls/md.h"
#endif

#define MBEDTLS_ERR_OID_NOT_FOUND                         -0x002E  /**未找到<OID。*/
#define MBEDTLS_ERR_OID_BUF_TOO_SMALL                     -0x000B  /**<输出缓冲区太小*/

/* 这是为了X.509的好处，但在这里定义是为了避免在这里使用X.509.h的“向后”包含*/
/*
 * 十、 509扩展类型（内部，位集的任意值）
 */
#define MBEDTLS_OID_X509_EXT_AUTHORITY_KEY_IDENTIFIER    (1 << 0)
#define MBEDTLS_OID_X509_EXT_SUBJECT_KEY_IDENTIFIER      (1 << 1)
#define MBEDTLS_OID_X509_EXT_KEY_USAGE                   (1 << 2)
#define MBEDTLS_OID_X509_EXT_CERTIFICATE_POLICIES        (1 << 3)
#define MBEDTLS_OID_X509_EXT_POLICY_MAPPINGS             (1 << 4)
#define MBEDTLS_OID_X509_EXT_SUBJECT_ALT_NAME            (1 << 5)
#define MBEDTLS_OID_X509_EXT_ISSUER_ALT_NAME             (1 << 6)
#define MBEDTLS_OID_X509_EXT_SUBJECT_DIRECTORY_ATTRS     (1 << 7)
#define MBEDTLS_OID_X509_EXT_BASIC_CONSTRAINTS           (1 << 8)
#define MBEDTLS_OID_X509_EXT_NAME_CONSTRAINTS            (1 << 9)
#define MBEDTLS_OID_X509_EXT_POLICY_CONSTRAINTS          (1 << 10)
#define MBEDTLS_OID_X509_EXT_EXTENDED_KEY_USAGE          (1 << 11)
#define MBEDTLS_OID_X509_EXT_CRL_DISTRIBUTION_POINTS     (1 << 12)
#define MBEDTLS_OID_X509_EXT_INIHIBIT_ANYPOLICY          (1 << 13)
#define MBEDTLS_OID_X509_EXT_FRESHEST_CRL                (1 << 14)
#define MBEDTLS_OID_X509_EXT_NS_CERT_TYPE                (1 << 16)

/*
 * 顶级OID元组
 */
#define MBEDTLS_OID_ISO_MEMBER_BODIES           "\x2a"          /* ｛iso（1）成员体（2）｝*/
#define MBEDTLS_OID_ISO_IDENTIFIED_ORG          "\x2b"          /* ｛iso（1）确定的组织（3）｝*/
#define MBEDTLS_OID_ISO_CCITT_DS                "\x55"          /* {节理iso ccitt（2）ds（5）}*/
#define MBEDTLS_OID_ISO_ITU_COUNTRY             "\x60"          /* {joint-iso-itu-t（2）国家（16）}*/

/*
 * ISO成员机构OID部分
 */
#define MBEDTLS_OID_COUNTRY_US                  "\x86\x48"      /* ｛我们（840）｝*/
#define MBEDTLS_OID_ORG_RSA_DATA_SECURITY       "\x86\xf7\x0d"  /* {rsadsi（113549）}*/
#define MBEDTLS_OID_RSA_COMPANY                 MBEDTLS_OID_ISO_MEMBER_BODIES MBEDTLS_OID_COUNTRY_US \
                                        MBEDTLS_OID_ORG_RSA_DATA_SECURITY /* {iso（1）成员机构（2）美国（840）rsadsi（113549）}*/
#define MBEDTLS_OID_ORG_ANSI_X9_62              "\xce\x3d" /* ansi-X9-62（10045）*/
#define MBEDTLS_OID_ANSI_X9_62                  MBEDTLS_OID_ISO_MEMBER_BODIES MBEDTLS_OID_COUNTRY_US \
                                        MBEDTLS_OID_ORG_ANSI_X9_62

/*
 * ISO识别的组织OID部分
 */
#define MBEDTLS_OID_ORG_DOD                     "\x06"          /* ｛多德（6）｝*/
#define MBEDTLS_OID_ORG_OIW                     "\x0e"
#define MBEDTLS_OID_OIW_SECSIG                  MBEDTLS_OID_ORG_OIW "\x03"
#define MBEDTLS_OID_OIW_SECSIG_ALG              MBEDTLS_OID_OIW_SECSIG "\x02"
#define MBEDTLS_OID_OIW_SECSIG_SHA1             MBEDTLS_OID_OIW_SECSIG_ALG "\x1a"
#define MBEDTLS_OID_ORG_CERTICOM                "\x81\x04"  /* 证书（132）*/
#define MBEDTLS_OID_CERTICOM                    MBEDTLS_OID_ISO_IDENTIFIED_ORG MBEDTLS_OID_ORG_CERTICOM
#define MBEDTLS_OID_ORG_TELETRUST               "\x24" /* 电传（36）*/
#define MBEDTLS_OID_TELETRUST                   MBEDTLS_OID_ISO_IDENTIFIED_ORG MBEDTLS_OID_ORG_TELETRUST

/*
 * ISO ITU OID部分
 */
#define MBEDTLS_OID_ORGANIZATION                "\x01"          /* ｛组织（1）｝*/
#define MBEDTLS_OID_ISO_ITU_US_ORG              MBEDTLS_OID_ISO_ITU_COUNTRY MBEDTLS_OID_COUNTRY_US MBEDTLS_OID_ORGANIZATION /* {joint-iso-itu-t（2）国家（16）美国（840）组织（1）}*/

#define MBEDTLS_OID_ORG_GOV                     "\x65"          /* ｛gov（101）｝*/
#define MBEDTLS_OID_GOV                         MBEDTLS_OID_ISO_ITU_US_ORG MBEDTLS_OID_ORG_GOV /* {joint-iso-itu-t（2）国家（16）美国（840）组织（1）gov（101）}*/

#define MBEDTLS_OID_ORG_NETSCAPE                "\x86\xF8\x42"  /* ｛netscape（113730）｝*/
#define MBEDTLS_OID_NETSCAPE                    MBEDTLS_OID_ISO_ITU_US_ORG MBEDTLS_OID_ORG_NETSCAPE /* Netscape OID｛joint-iso-itu-t（2）国家（16）美国（840）组织（1）Netscape（113730）｝*/

/* 标准证书和CRL扩展的ISO弧*/
#define MBEDTLS_OID_ID_CE                       MBEDTLS_OID_ISO_CCITT_DS "\x1D" /**<id ce对象标识符：：=｛joint iso ccitt（2）ds（5）29｝*/

#define MBEDTLS_OID_NIST_ALG                    MBEDTLS_OID_GOV "\x03\x04" /**{joint-iso-itu-t（2）国家（16）美国（840）组织（1）gov（101）csor（3）nist算法（4）*/

/**
 * 私有互联网扩展{iso（1）识别组织（3）dod（6）互联网（1）安全（5）机制（5）pkix（7）}
 */
#define MBEDTLS_OID_INTERNET                    MBEDTLS_OID_ISO_IDENTIFIED_ORG MBEDTLS_OID_ORG_DOD "\x01"
#define MBEDTLS_OID_PKIX                        MBEDTLS_OID_INTERNET "\x05\x05\x07"

/*
 * 标准命名属性的弧
 */
#define MBEDTLS_OID_AT                          MBEDTLS_OID_ISO_CCITT_DS "\x04" /**<id at OBJECT IDENTIFIER:：=｛joint iso ccitt（2）ds（5）4｝*/
#define MBEDTLS_OID_AT_CN                       MBEDTLS_OID_AT "\x03" /**<id at commonName AttributeType:=｛id at 3｝*/
#define MBEDTLS_OID_AT_SUR_NAME                 MBEDTLS_OID_AT "\x04" /**<id at surName AttributeType:=｛id at 4｝*/
#define MBEDTLS_OID_AT_SERIAL_NUMBER            MBEDTLS_OID_AT "\x05" /**<id at serialNumber AttributeType:=｛id at 5｝*/
#define MBEDTLS_OID_AT_COUNTRY                  MBEDTLS_OID_AT "\x06" /**<id at countryName AttributeType:=｛id at 6｝*/
#define MBEDTLS_OID_AT_LOCALITY                 MBEDTLS_OID_AT "\x07" /**<id at locality AttributeType:=｛id at 7｝*/
#define MBEDTLS_OID_AT_STATE                    MBEDTLS_OID_AT "\x08" /**<id at state AttributeType:=｛id at 8｝*/
#define MBEDTLS_OID_AT_ORGANIZATION             MBEDTLS_OID_AT "\x0A" /**<id at organizationName AttributeType:=｛id at 10｝*/
#define MBEDTLS_OID_AT_ORG_UNIT                 MBEDTLS_OID_AT "\x0B" /**<id at organizationUnitName AttributeType:=｛id at 11｝*/
#define MBEDTLS_OID_AT_TITLE                    MBEDTLS_OID_AT "\x0C" /**<id at title AttributeType:=｛id at 12｝*/
#define MBEDTLS_OID_AT_POSTAL_ADDRESS           MBEDTLS_OID_AT "\x10" /**<id at postalAddress AttributeType:=｛id at 16｝*/
#define MBEDTLS_OID_AT_POSTAL_CODE              MBEDTLS_OID_AT "\x11" /**<id at postalCode AttributeType:=｛id at 17｝*/
#define MBEDTLS_OID_AT_GIVEN_NAME               MBEDTLS_OID_AT "\x2A" /**<id at givenName AttributeType:=｛id at 42｝*/
#define MBEDTLS_OID_AT_INITIALS                 MBEDTLS_OID_AT "\x2B" /**<id at initials AttributeType:=｛id at 43｝*/
#define MBEDTLS_OID_AT_GENERATION_QUALIFIER     MBEDTLS_OID_AT "\x2C" /**<id at generationQualifier AttributeType:=｛id at 44｝*/
#define MBEDTLS_OID_AT_UNIQUE_IDENTIFIER        MBEDTLS_OID_AT "\x2D" /**<id at uniqueIdentifier AttributionType:=｛id at 45｝*/
#define MBEDTLS_OID_AT_DN_QUALIFIER             MBEDTLS_OID_AT "\x2E" /**<id at dnQualifier AttributeType:=｛id at 46｝*/
#define MBEDTLS_OID_AT_PSEUDONYM                MBEDTLS_OID_AT "\x41" /**<id at笔名AttributeType:=｛id at 65｝*/

#define MBEDTLS_OID_DOMAIN_COMPONENT            "\x09\x92\x26\x89\x93\xF2\x2C\x64\x01\x19" /**id domainComponent AttributeType：＝｛itu-t（0）data（9）pss（2342）ucl（19200300）pilot（100）pilot AttributeType（1）domainComponent（25）｝*/

/*
 * 标准证书扩展的OID
 */
#define MBEDTLS_OID_AUTHORITY_KEY_IDENTIFIER    MBEDTLS_OID_ID_CE "\x23" /**<id ce authorityKeyIdentifier OBJECT IDENTIFIER:：=｛id ce 35｝*/
#define MBEDTLS_OID_SUBJECT_KEY_IDENTIFIER      MBEDTLS_OID_ID_CE "\x0E" /**<id ce subjectKeyIdentifier OBJECT IDENTIFIER:：=｛id ce 14｝*/
#define MBEDTLS_OID_KEY_USAGE                   MBEDTLS_OID_ID_CE "\x0F" /**<id ce keyUsage OBJECT IDENTIFIER:：=｛id ce 15｝*/
#define MBEDTLS_OID_CERTIFICATE_POLICIES        MBEDTLS_OID_ID_CE "\x20" /**<id ce certificatePolicies OBJECT IDENTIFIER:：=｛id ce 32｝*/
#define MBEDTLS_OID_POLICY_MAPPINGS             MBEDTLS_OID_ID_CE "\x21" /**<id ce policyMappings OBJECT IDENTIFIER:：=｛id ce 33｝*/
#define MBEDTLS_OID_SUBJECT_ALT_NAME            MBEDTLS_OID_ID_CE "\x11" /**<id ce subjectAltName OBJECT IDENTIFIER:：=｛id ce 17｝*/
#define MBEDTLS_OID_ISSUER_ALT_NAME             MBEDTLS_OID_ID_CE "\x12" /**<id ce issuerAltName OBJECT IDENTIFIER:：=｛id ce 18｝*/
#define MBEDTLS_OID_SUBJECT_DIRECTORY_ATTRS     MBEDTLS_OID_ID_CE "\x09" /**<id ce subjectDirectoryAttributes OBJECT IDENTIFIER:：=｛id ce 9｝*/
#define MBEDTLS_OID_BASIC_CONSTRAINTS           MBEDTLS_OID_ID_CE "\x13" /**<id ce basicConstraints OBJECT IDENTIFIER:：=｛id ce 19｝*/
#define MBEDTLS_OID_NAME_CONSTRAINTS            MBEDTLS_OID_ID_CE "\x1E" /**<id ce nameConstraints OBJECT IDENTIFIER:：=｛id ce 30｝*/
#define MBEDTLS_OID_POLICY_CONSTRAINTS          MBEDTLS_OID_ID_CE "\x24" /**<id ce policyConstraints OBJECT IDENTIFIER:：=｛id ce 36｝*/
#define MBEDTLS_OID_EXTENDED_KEY_USAGE          MBEDTLS_OID_ID_CE "\x25" /**<id ce extKeyUsage OBJECT IDENTIFIER:：=｛id ce 37｝*/
#define MBEDTLS_OID_CRL_DISTRIBUTION_POINTS     MBEDTLS_OID_ID_CE "\x1F" /**<id ce cRLDistributionPoints对象标识符：：=｛id ce 31｝*/
#define MBEDTLS_OID_INIHIBIT_ANYPOLICY          MBEDTLS_OID_ID_CE "\x36" /**<id ce inhibitAnyPolicy OBJECT IDENTIFIER:：=｛id ce 54｝*/
#define MBEDTLS_OID_FRESHEST_CRL                MBEDTLS_OID_ID_CE "\x2E" /**<id ce freshstCRL对象标识符：：=｛id ce 46｝*/

/*
 * 证书策略
 */
#define MBEDTLS_OID_ANY_POLICY              MBEDTLS_OID_CERTIFICATE_POLICIES "\x00" /**<anyPolicy OBJECT IDENTIFIER:：=｛id ce certificatePolicies 0｝*/

/*
 * Netscape证书扩展
 */
#define MBEDTLS_OID_NS_CERT                 MBEDTLS_OID_NETSCAPE "\x01"
#define MBEDTLS_OID_NS_CERT_TYPE            MBEDTLS_OID_NS_CERT  "\x01"
#define MBEDTLS_OID_NS_BASE_URL             MBEDTLS_OID_NS_CERT  "\x02"
#define MBEDTLS_OID_NS_REVOCATION_URL       MBEDTLS_OID_NS_CERT  "\x03"
#define MBEDTLS_OID_NS_CA_REVOCATION_URL    MBEDTLS_OID_NS_CERT  "\x04"
#define MBEDTLS_OID_NS_RENEWAL_URL          MBEDTLS_OID_NS_CERT  "\x07"
#define MBEDTLS_OID_NS_CA_POLICY_URL        MBEDTLS_OID_NS_CERT  "\x08"
#define MBEDTLS_OID_NS_SSL_SERVER_NAME      MBEDTLS_OID_NS_CERT  "\x0C"
#define MBEDTLS_OID_NS_COMMENT              MBEDTLS_OID_NS_CERT  "\x0D"
#define MBEDTLS_OID_NS_DATA_TYPE            MBEDTLS_OID_NETSCAPE "\x02"
#define MBEDTLS_OID_NS_CERT_SEQUENCE        MBEDTLS_OID_NS_DATA_TYPE "\x05"

/*
 * CRL扩展的OID
 */
#define MBEDTLS_OID_PRIVATE_KEY_USAGE_PERIOD    MBEDTLS_OID_ID_CE "\x10"
#define MBEDTLS_OID_CRL_NUMBER                  MBEDTLS_OID_ID_CE "\x14" /**<id ce cRLNumber对象标识符：：=｛id ce 20｝*/

/*
 * 十、 509 v3扩展密钥使用OID
 */
#define MBEDTLS_OID_ANY_EXTENDED_KEY_USAGE      MBEDTLS_OID_EXTENDED_KEY_USAGE "\x00" /**<anyExtendedKeyUsage OBJECT IDENTIFIER:：=｛id ce extKeyUsage 0｝*/

#define MBEDTLS_OID_KP                          MBEDTLS_OID_PKIX "\x03" /**<id kp对象标识符：：=｛id pkix 3｝*/
#define MBEDTLS_OID_SERVER_AUTH                 MBEDTLS_OID_KP "\x01" /**<id kp serverAuth对象标识符：：=｛id kp 1｝*/
#define MBEDTLS_OID_CLIENT_AUTH                 MBEDTLS_OID_KP "\x02" /**<id kp clientAuth对象标识符：：=｛id kp 2｝*/
#define MBEDTLS_OID_CODE_SIGNING                MBEDTLS_OID_KP "\x03" /**<id kp codeSigning OBJECT IDENTIFIER:：=｛id kp 3｝*/
#define MBEDTLS_OID_EMAIL_PROTECTION            MBEDTLS_OID_KP "\x04" /**<id kp emailProtection OBJECT IDENTIFIER:：=｛id kp 4｝*/
#define MBEDTLS_OID_TIME_STAMPING               MBEDTLS_OID_KP "\x08" /**<id kp time标记对象标识符：：=｛id kp 8｝*/
#define MBEDTLS_OID_OCSP_SIGNING                MBEDTLS_OID_KP "\x09" /**<id kp OCSP签名对象标识符：：=｛id kp 9｝*/

/**
 * Wi-SUN联盟现场区域网络｛iso（1）确定的组织（3）dod（6）互联网（1）私人（4）企业（1）Wi-SUN（45605）现场区域网络（1）｝
 */
#define MBEDTLS_OID_WISUN_FAN                   MBEDTLS_OID_INTERNET "\x04\x01\x82\xe4\x25\x01"

#define MBEDTLS_OID_ON                          MBEDTLS_OID_PKIX "\x08" /**<id on OBJECT IDENTIFIER:：=｛id pkix 8｝*/
#define MBEDTLS_OID_ON_HW_MODULE_NAME           MBEDTLS_OID_ON "\x04" /**<id on hardwareModuleName OBJECT IDENTIFIER:：=｛id on 4｝*/

/*
 * PKCS定义OID
 */

#define MBEDTLS_OID_PKCS                MBEDTLS_OID_RSA_COMPANY "\x01" /**<pkcs OBJECT IDENTIFIER:：=｛iso（1）成员体（2）us（840）rsadsi（113549）1｝*/
#define MBEDTLS_OID_PKCS1               MBEDTLS_OID_PKCS "\x01" /**<pkcs-1对象标识符：：=｛iso（1）成员体（2）us（840）rsadsi（113549）pkcs（1）1｝*/
#define MBEDTLS_OID_PKCS5               MBEDTLS_OID_PKCS "\x05" /**<pkcs-5对象标识符：：=｛iso（1）成员体（2）us（840）rsadsi（113549）pkcs（1）5｝*/
#define MBEDTLS_OID_PKCS9               MBEDTLS_OID_PKCS "\x09" /**<pkcs-9对象标识符：：=｛iso（1）成员体（2）us（840）rsadsi（113549）pkcs（1）9｝*/
#define MBEDTLS_OID_PKCS12              MBEDTLS_OID_PKCS "\x0c" /**<pkcs-12对象标识符：：={iso（1）成员体（2）us（840）rsadsi（113549）pkcs（1）12}*/

/*
 * PKCS#1 OID
 */
#define MBEDTLS_OID_PKCS1_RSA           MBEDTLS_OID_PKCS1 "\x01" /**<rsaEncryption对象标识符：：=｛pkcs-1 1｝*/
#define MBEDTLS_OID_PKCS1_MD2           MBEDTLS_OID_PKCS1 "\x02" /**<md2WithRSA加密：：=｛pkcs-1 2｝*/
#define MBEDTLS_OID_PKCS1_MD4           MBEDTLS_OID_PKCS1 "\x03" /**<md4WithRSAEncryption:：=｛pkcs-1 3｝*/
#define MBEDTLS_OID_PKCS1_MD5           MBEDTLS_OID_PKCS1 "\x04" /**<md5WithRSA加密：：=｛pkcs-1 4｝*/
#define MBEDTLS_OID_PKCS1_SHA1          MBEDTLS_OID_PKCS1 "\x05" /**<sha1WithRSA加密：：=｛pkcs-1 5｝*/
#define MBEDTLS_OID_PKCS1_SHA224        MBEDTLS_OID_PKCS1 "\x0e" /**<sha224WithRSA加密：：=｛pkcs-1 14｝*/
#define MBEDTLS_OID_PKCS1_SHA256        MBEDTLS_OID_PKCS1 "\x0b" /**<sha256WithRSA加密：：=｛pkcs-1 11｝*/
#define MBEDTLS_OID_PKCS1_SHA384        MBEDTLS_OID_PKCS1 "\x0c" /**<sha384WithRSA加密：：=｛pkcs-1 12｝*/
#define MBEDTLS_OID_PKCS1_SHA512        MBEDTLS_OID_PKCS1 "\x0d" /**<sha512WithRSA加密：：=｛pkcs-1 13｝*/

#define MBEDTLS_OID_RSA_SHA_OBS         "\x2B\x0E\x03\x02\x1D"

#define MBEDTLS_OID_PKCS9_EMAIL         MBEDTLS_OID_PKCS9 "\x01" /**<emailAddress AttributeType:：=｛pkcs-9 1｝*/

/* RFC 4055 */
#define MBEDTLS_OID_RSASSA_PSS          MBEDTLS_OID_PKCS1 "\x0a" /**<id RSASSA PSS：：=｛pkcs-1 10｝*/
#define MBEDTLS_OID_MGF1                MBEDTLS_OID_PKCS1 "\x08" /**<id-mgf1:：=｛pkcs-1 8｝*/

/*
 * 摘要算法
 */
#define MBEDTLS_OID_DIGEST_ALG_MD2              MBEDTLS_OID_RSA_COMPANY "\x02\x02" /**<id-mbedtls_md2对象标识符：：={iso（1）成员体（2）us（840）rsadsi（113549）digitalAlgorithm（2）2}*/
#define MBEDTLS_OID_DIGEST_ALG_MD4              MBEDTLS_OID_RSA_COMPANY "\x02\x04" /**<id-mbedtls_md4对象标识符：：={iso（1）成员体（2）us（840）rsadsi（113549）digitalAlgorithm（2）4}*/
#define MBEDTLS_OID_DIGEST_ALG_MD5              MBEDTLS_OID_RSA_COMPANY "\x02\x05" /**<id-mbedtls_md5对象标识符：：={iso（1）成员体（2）us（840）rsadsi（113549）digitalAlgorithm（2）5}*/
#define MBEDTLS_OID_DIGEST_ALG_SHA1             MBEDTLS_OID_ISO_IDENTIFIED_ORG MBEDTLS_OID_OIW_SECSIG_SHA1 /**<id-mbedtls_sha1对象标识符：：={iso（1）识别的组织（3）oiw（14）secsig（3）算法（2）26}*/
#define MBEDTLS_OID_DIGEST_ALG_SHA224           MBEDTLS_OID_NIST_ALG "\x02\x04" /**<id-sha224对象标识符：：={joint-iso-itu-t（2）国家（16）美国（840）组织（1）gov（101）csor（3）nistalgorithm（4）hashalgs（2）4}*/
#define MBEDTLS_OID_DIGEST_ALG_SHA256           MBEDTLS_OID_NIST_ALG "\x02\x01" /**<id-mbedtls_sha256对象标识符：：={joint-iso-itu-t（2）国家（16）美国（840）组织（1）gov（101）csor（3）nistalgorithm（4）hashalgs（2）1}*/

#define MBEDTLS_OID_DIGEST_ALG_SHA384           MBEDTLS_OID_NIST_ALG "\x02\x02" /**<id-sha384对象标识符：：={joint-iso-itu-t（2）国家（16）美国（840）组织（1）gov（101）csor（3）nistalgorithm（4）hashalgs（2）2}*/

#define MBEDTLS_OID_DIGEST_ALG_SHA512           MBEDTLS_OID_NIST_ALG "\x02\x03" /**<id-mbedtls_sha512对象标识符：：={joint-iso-itu-t（2）国家（16）美国（840）组织（1）gov（101）csor（3）nistalgorithm（4）hashalgs（2）3}*/

#define MBEDTLS_OID_DIGEST_ALG_RIPEMD160        MBEDTLS_OID_TELETRUST "\x03\x02\x01" /**<id-ripemd160 OBJECT IDENTIFIER:：{iso（1）识别的组织（3）telestrust（36）算法（3）hashAlgorithm（2）ripemd160（1）}*/

#define MBEDTLS_OID_HMAC_SHA1                   MBEDTLS_OID_RSA_COMPANY "\x02\x07" /**<id-hmacWithSHA1对象标识符：：={iso（1）成员体（2）us（840）rsadsi（113549）digitalAlgorithm（2）7}*/

#define MBEDTLS_OID_HMAC_SHA224                 MBEDTLS_OID_RSA_COMPANY "\x02\x08" /**<id-hmacWithSHA224对象标识符：：={iso（1）成员体（2）us（840）rsadsi（113549）digitalAlgorithm（2）8}*/

#define MBEDTLS_OID_HMAC_SHA256                 MBEDTLS_OID_RSA_COMPANY "\x02\x09" /**<id-hmacWithSHA256对象标识符：：={iso（1）成员体（2）us（840）rsadsi（113549）digitalAlgorithm（2）9}*/

#define MBEDTLS_OID_HMAC_SHA384                 MBEDTLS_OID_RSA_COMPANY "\x02\x0A" /**<id-hmacWithSHA384对象标识符：：={iso（1）成员体（2）us（840）rsadsi（113549）digitalAlgorithm（2）10}*/

#define MBEDTLS_OID_HMAC_SHA512                 MBEDTLS_OID_RSA_COMPANY "\x02\x0B" /**<id-hmacWithSHA512对象标识符：：={iso（1）成员体（2）us（840）rsadsi（113549）digitalAlgorithm（2）11}*/

/*
 * 加密算法
 */
#define MBEDTLS_OID_DES_CBC                     MBEDTLS_OID_ISO_IDENTIFIED_ORG MBEDTLS_OID_OIW_SECSIG_ALG "\x07" /**<desCBC OBJECT IDENTIFIER:：={iso（1）识别的组织（3）oiw（14）secsig（3）算法（2）7}*/
#define MBEDTLS_OID_DES_EDE3_CBC                MBEDTLS_OID_RSA_COMPANY "\x03\x07" /**<des-ede3-bcc对象标识符：：={iso（1）成员体（2）--us（840）rsadsi（113549）加密算法（3）7}*/
#define MBEDTLS_OID_AES                         MBEDTLS_OID_NIST_ALG "\x01" /**aes对象标识符：：={joint-iso-itu-t（2）国家（16）美国（840）组织（1）gov（101）csor（3）nist算法（4）1}*/

/*
 * 密钥包装算法
 */
/*
 * RFC 5649
 */
#define MBEDTLS_OID_AES128_KW                   MBEDTLS_OID_AES "\x05" /**id-aes128-wrap对象标识符：：=｛aes 5｝*/
#define MBEDTLS_OID_AES128_KWP                  MBEDTLS_OID_AES "\x08" /**id-aes128-wrap-pad对象标识符：：=｛aes 8｝*/
#define MBEDTLS_OID_AES192_KW                   MBEDTLS_OID_AES "\x19" /**id-aes192-wrap对象标识符：：=｛aes 25｝*/
#define MBEDTLS_OID_AES192_KWP                  MBEDTLS_OID_AES "\x1c" /**id-aes192-wrap-pad对象标识符：：=｛aes 28｝*/
#define MBEDTLS_OID_AES256_KW                   MBEDTLS_OID_AES "\x2d" /**id-aes256-wrap对象标识符：：=｛aes 45｝*/
#define MBEDTLS_OID_AES256_KWP                  MBEDTLS_OID_AES "\x30" /**id-aes256-wrap-pad对象标识符：：=｛aes 48｝*/
/*
 * PKCS#5 OID
 */
#define MBEDTLS_OID_PKCS5_PBKDF2                MBEDTLS_OID_PKCS5 "\x0c" /**<id-PBKDF2对象标识符：：=｛pkcs-5 12｝*/
#define MBEDTLS_OID_PKCS5_PBES2                 MBEDTLS_OID_PKCS5 "\x0d" /**<id-PBES2对象标识符：：=｛pkcs-5 13｝*/
#define MBEDTLS_OID_PKCS5_PBMAC1                MBEDTLS_OID_PKCS5 "\x0e" /**<id-PBMAC1对象标识符：：=｛pkcs-5 14｝*/

/*
 * PKCS#5 PBES1算法
 */
#define MBEDTLS_OID_PKCS5_PBE_MD2_DES_CBC       MBEDTLS_OID_PKCS5 "\x01" /**<pbeWithMD2AndDES CBC对象标识符：：=｛pkcs-5 1｝*/
#define MBEDTLS_OID_PKCS5_PBE_MD2_RC2_CBC       MBEDTLS_OID_PKCS5 "\x04" /**<pbeWithMD2AndRC2 CBC对象标识符：：=｛pkcs-5 4｝*/
#define MBEDTLS_OID_PKCS5_PBE_MD5_DES_CBC       MBEDTLS_OID_PKCS5 "\x03" /**<pbeWithMD5AndDES CBC对象标识符：：=｛pkcs-5 3｝*/
#define MBEDTLS_OID_PKCS5_PBE_MD5_RC2_CBC       MBEDTLS_OID_PKCS5 "\x06" /**<pbeWithMD5AndRC2 CBC对象标识符：：=｛pkcs-5 6｝*/
#define MBEDTLS_OID_PKCS5_PBE_SHA1_DES_CBC      MBEDTLS_OID_PKCS5 "\x0a" /**<pbeWithSHA1AndDES CBC对象标识符：：=｛pkcs-5 10｝*/
#define MBEDTLS_OID_PKCS5_PBE_SHA1_RC2_CBC      MBEDTLS_OID_PKCS5 "\x0b" /**<pbeWithSHA1AndRC2 CBC对象标识符：：=｛pkcs-5 11｝*/

/*
 * PKCS#8 OID
 */
#define MBEDTLS_OID_PKCS9_CSR_EXT_REQ           MBEDTLS_OID_PKCS9 "\x0e" /**<extensionRequest OBJECT IDENTIFIER:：=｛pkcs-9 14｝*/

/*
 * PKCS#12 PBE OID
 */
#define MBEDTLS_OID_PKCS12_PBE                      MBEDTLS_OID_PKCS12 "\x01" /**<pkcs-12PbeIds对象标识符：：=｛pkcs-12 1｝*/

#define MBEDTLS_OID_PKCS12_PBE_SHA1_RC4_128         MBEDTLS_OID_PKCS12_PBE "\x01" /**<pbeWithSHAAnd128BitRC4对象标识符：：=｛pkcs-12PbeIds 1｝*/
#define MBEDTLS_OID_PKCS12_PBE_SHA1_RC4_40          MBEDTLS_OID_PKCS12_PBE "\x02" /**<pbeWithSHAAnd40BitRC4对象标识符：：=｛pkcs-12PbeIds 2｝*/
#define MBEDTLS_OID_PKCS12_PBE_SHA1_DES3_EDE_CBC    MBEDTLS_OID_PKCS12_PBE "\x03" /**<pbeWithSHAAnd3 KeyTripleDES CBC对象标识符：：=｛pkcs-12PbeIds 3｝*/
#define MBEDTLS_OID_PKCS12_PBE_SHA1_DES2_EDE_CBC    MBEDTLS_OID_PKCS12_PBE "\x04" /**<pbeWithSHAAnd2 KeyTripleDES CBC对象标识符：：=｛pkcs-12PbeIds 4｝*/
#define MBEDTLS_OID_PKCS12_PBE_SHA1_RC2_128_CBC     MBEDTLS_OID_PKCS12_PBE "\x05" /**<pbeWithSHAAnd128BitRC2 CBC对象标识符：：=｛pkcs-12PbeIds 5｝*/
#define MBEDTLS_OID_PKCS12_PBE_SHA1_RC2_40_CBC      MBEDTLS_OID_PKCS12_PBE "\x06" /**<pbeWithSHAAnd40BitRC2 CBC对象标识符：：=｛pkcs-12PbeIds 6｝*/

/*
 * RFC 5480中的EC密钥算法
 */

/* id ecPublicKey对象标识符：：=｛iso（1）成员体（2）us（840）ansi-X9-62（10045）keyType（2）1｝*/
#define MBEDTLS_OID_EC_ALG_UNRESTRICTED         MBEDTLS_OID_ANSI_X9_62 "\x02\01"

/*   id ecDH OBJECT IDENTIFIER:：＝｛iso（1）识别的组织（3）certicom（132）方案（1）ecDH（12）｝*/
#define MBEDTLS_OID_EC_ALG_ECDH                 MBEDTLS_OID_CERTICOM "\x01\x0c"

/*
 * ECParameters namedCurve标识符，来自RFC 5480、RFC 5639和SEC2
 */

/* secp192r1对象标识符：：={iso（1）成员体（2）us（840）ansi-X9-62（10045）曲线（3）素数（1）1}*/
#define MBEDTLS_OID_EC_GRP_SECP192R1        MBEDTLS_OID_ANSI_X9_62 "\x03\x01\x01"

/* secp224r1对象标识符：：=｛iso（1）识别的组织（3）certicom（132）曲线（0）33｝*/
#define MBEDTLS_OID_EC_GRP_SECP224R1        MBEDTLS_OID_CERTICOM "\x00\x21"

/* secp256r1对象标识符：：={iso（1）成员体（2）us（840）ansi-X9-62（10045）曲线（3）素数（1）7}*/
#define MBEDTLS_OID_EC_GRP_SECP256R1        MBEDTLS_OID_ANSI_X9_62 "\x03\x01\x07"

/* secp384r1对象标识符：：=｛iso（1）识别的组织（3）certicom（132）曲线（0）34｝*/
#define MBEDTLS_OID_EC_GRP_SECP384R1        MBEDTLS_OID_CERTICOM "\x00\x22"

/* secp521r1对象标识符：：={iso（1）识别的组织（3）certicom（132）曲线（0）35}*/
#define MBEDTLS_OID_EC_GRP_SECP521R1        MBEDTLS_OID_CERTICOM "\x00\x23"

/* secp192k1对象标识符：：={iso（1）识别的组织（3）certicom（132）曲线（0）31}*/
#define MBEDTLS_OID_EC_GRP_SECP192K1        MBEDTLS_OID_CERTICOM "\x00\x1f"

/* secp224k1对象标识符：：={iso（1）识别的组织（3）certicom（132）曲线（0）32}*/
#define MBEDTLS_OID_EC_GRP_SECP224K1        MBEDTLS_OID_CERTICOM "\x00\x20"

/* secp256k1对象标识符：：={iso（1）识别的组织（3）certicom（132）曲线（0）10}*/
#define MBEDTLS_OID_EC_GRP_SECP256K1        MBEDTLS_OID_CERTICOM "\x00\x0a"

/* RFC 5639 4.1 ecStdCurvesAndGeneration OBJECT IDENTIFIER:：=｛iso（1）标识的组织（3）telestrust（36）算法（3）签名-算法（2）ecSign（2）8｝椭圆曲线OBJECT IDENTIFIER::=｛ecStdCcurvesAndGeneration1｝版本一个OBJECT标识符：：={椭圆曲线1｝*/
#define MBEDTLS_OID_EC_BRAINPOOL_V1         MBEDTLS_OID_TELETRUST "\x03\x03\x02\x08\x01\x01"

/* brainpoolP256r1对象标识符：：=｛versionOne 7｝*/
#define MBEDTLS_OID_EC_GRP_BP256R1          MBEDTLS_OID_EC_BRAINPOOL_V1 "\x07"

/* brainpoolP384r1对象标识符：：=｛versionOne 11｝*/
#define MBEDTLS_OID_EC_GRP_BP384R1          MBEDTLS_OID_EC_BRAINPOOL_V1 "\x0B"

/* brainpoolP512r1对象标识符：：=｛versionOne 13｝*/
#define MBEDTLS_OID_EC_GRP_BP512R1          MBEDTLS_OID_EC_BRAINPOOL_V1 "\x0D"

/*
 * SEC1 C.1
 *
 * 素字段OBJECT IDENTIFIER:：={id fieldType 1｝id fieldType OBJECT标识符：：={ansi-X9-62 fieldType（1）}
 */
#define MBEDTLS_OID_ANSI_X9_62_FIELD_TYPE   MBEDTLS_OID_ANSI_X9_62 "\x01"
#define MBEDTLS_OID_ANSI_X9_62_PRIME_FIELD  MBEDTLS_OID_ANSI_X9_62_FIELD_TYPE "\x01"

/*
 * ECDSA签名标识符，来自RFC 5480
 */
#define MBEDTLS_OID_ANSI_X9_62_SIG          MBEDTLS_OID_ANSI_X9_62 "\x04" /* 签名（4）*/
#define MBEDTLS_OID_ANSI_X9_62_SIG_SHA2     MBEDTLS_OID_ANSI_X9_62_SIG "\x03" /* ecdsa-with-SHA2（3）*/

/* ecdsa-with-SHA1对象标识符：：={iso（1）成员体（2）us（840）ansi-X9-62（10045）签名（4）1}*/
#define MBEDTLS_OID_ECDSA_SHA1              MBEDTLS_OID_ANSI_X9_62_SIG "\x01"

/* ecdsa-with-SHA224对象标识符：：={iso（1）成员体（2）us（840）ansi-X9-62（10045）签名（4）ecdsa-with-SHA2（3）1}*/
#define MBEDTLS_OID_ECDSA_SHA224            MBEDTLS_OID_ANSI_X9_62_SIG_SHA2 "\x01"

/* ecdsa-with-SHA256对象标识符：：={iso（1）成员体（2）us（840）ansi-X9-62（10045）签名（4）ecdsa-with-SHA2（3）2}*/
#define MBEDTLS_OID_ECDSA_SHA256            MBEDTLS_OID_ANSI_X9_62_SIG_SHA2 "\x02"

/* ecdsa-with-SHA384对象标识符：：={iso（1）成员体（2）us（840）ansi-X9-62（10045）签名（4）ecdsa-with-SHA2（3）3}*/
#define MBEDTLS_OID_ECDSA_SHA384            MBEDTLS_OID_ANSI_X9_62_SIG_SHA2 "\x03"

/* ecdsa-with-SHA512对象标识符：：={iso（1）成员体（2）us（840）ansi-X9-62（10045）签名（4）ecdsa-with-SHA2（3）4}*/
#define MBEDTLS_OID_ECDSA_SHA512            MBEDTLS_OID_ANSI_X9_62_SIG_SHA2 "\x04"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \简短的基本OID描述符结构
 */
typedef struct mbedtls_oid_descriptor_t
{
    const char *asn1;               /*!< 类ASN。1个代表*/
    size_t asn1_len;                /*!< asn1长度*/
    const char *name;               /*!< 正式名称（如RFC）*/
    const char *description;        /*!< 人性化描述*/
} mbedtls_oid_descriptor_t;

/**
 * \简要翻译ASN。1 OID转换为其数字表示（例如“\x2A\x86\x48\x86\xF7\x0D”转换为“1.2.840.113549”）
 *
 * \param buf buffer，用于将表示形式放入\n缓冲区的大小\n要转换的oid oid
 *
 * \返回写入字符串的长度（不包括最后的NULL）或错误时的MBEDTLS_error_OID_BUF_TOO_SMALL
 */
int mbedtls_oid_get_numeric_string( char *buf, size_t size, const mbedtls_asn1_buf *oid );

/**
 * \brief将X.509扩展OID转换为本地值
 *
 * \param oid oid，用于使用\param ext_type位置存储扩展类型
 *
 * \如果成功，则返回0，或MBEDTLS_ERROR_OID_NOT_FOUND
 */
int mbedtls_oid_get_x509_ext_type( const mbedtls_asn1_buf *oid, int *ext_type );

/**
 * \brief将X.509属性类型OID转换为短名称（例如，X520通用名称的OID转换成“CN”）
 *
 * \param oid oid，用于使用\param short_name place存储字符串指针
 *
 * \如果成功，则返回0，或MBEDTLS_ERROR_OID_NOT_FOUND
 */
int mbedtls_oid_get_attr_short_name( const mbedtls_asn1_buf *oid, const char **short_name );

/**
 * \brief将PublicKeyAlgorithm OID转换为pk_type
 *
 * \param oid oid，用于使用\param pk_alg位置存储公钥算法
 *
 * \如果成功，则返回0，或MBEDTLS_ERROR_OID_NOT_FOUND
 */
int mbedtls_oid_get_pk_alg( const mbedtls_asn1_buf *oid, mbedtls_pk_type_t *pk_alg );

/**
 * \brief将pk_type转换为PublicKeyAlgorithm OID
 *
 * \param pk_alg要查找的公钥类型\param oid存储ASN的位置。1 OID字符串指针\n OID的长度
 *
 * \如果成功，则返回0，或MBEDTLS_ERROR_OID_NOT_FOUND
 */
int mbedtls_oid_get_oid_by_pk_alg( mbedtls_pk_type_t pk_alg,
                           const char **oid, size_t *olen );

#if defined(MBEDTLS_ECP_C)
/**
 * \brief将NamedCurve OID转换为EC组标识符
 *
 * \param oid oid用于存储组id
 *
 * \如果成功，则返回0，或MBEDTLS_ERROR_OID_NOT_FOUND
 */
int mbedtls_oid_get_ec_grp( const mbedtls_asn1_buf *oid, mbedtls_ecp_group_id *grp_id );

/**
 * \brief将EC组标识符转换为NamedCurve OID
 *
 * \param grp_id EC组标识符\param id存储ASN的位置。1 OID字符串指针\n OID的长度
 *
 * \如果成功，则返回0，或MBEDTLS_ERROR_OID_NOT_FOUND
 */
int mbedtls_oid_get_oid_by_ec_grp( mbedtls_ecp_group_id grp_id,
                           const char **oid, size_t *olen );
#endif /* MBEDTLS_ECP_C */

#if defined(MBEDTLS_MD_C)
/**
 * \简短地将SignatureAlgorithm OID转换为md_type和pk_type
 *
 * \param oid oid用于使用\param md_alg位置存储消息摘要算法\param pk_alg存储公钥算法
 *
 * \如果成功，则返回0，或MBEDTLS_ERROR_OID_NOT_FOUND
 */
int mbedtls_oid_get_sig_alg( const mbedtls_asn1_buf *oid,
                     mbedtls_md_type_t *md_alg, mbedtls_pk_type_t *pk_alg );

/**
 * \简短地将SignatureAlgorithm OID转换为描述
 *
 * \param oid oid，用于存储字符串指针
 *
 * \如果成功，则返回0，或MBEDTLS_ERROR_OID_NOT_FOUND
 */
int mbedtls_oid_get_sig_alg_desc( const mbedtls_asn1_buf *oid, const char **desc );

/**
 * \brief将md_type和pk_type转换为SignatureAlgorithm OID
 *
 * \param md_alg消息摘要算法\pram pk_alg公钥算法\param id存储ASN的位置。1 OID字符串指针\n OID的长度
 *
 * \如果成功，则返回0，或MBEDTLS_ERROR_OID_NOT_FOUND
 */
int mbedtls_oid_get_oid_by_sig_alg( mbedtls_pk_type_t pk_alg, mbedtls_md_type_t md_alg,
                            const char **oid, size_t *olen );

/**
 * \brief将哈希算法OID转换为md_type
 *
 * \param oid oid，用于使用\param md_alg位置存储消息摘要算法
 *
 * \如果成功，则返回0，或MBEDTLS_ERROR_OID_NOT_FOUND
 */
int mbedtls_oid_get_md_alg( const mbedtls_asn1_buf *oid, mbedtls_md_type_t *md_alg );

/**
 * \brief将hmac算法OID转换为md_type
 *
 * \param oid oid用于使用\param md_hmac位置存储消息hmac算法
 *
 * \如果成功，则返回0，或MBEDTLS_ERROR_OID_NOT_FOUND
 */
int mbedtls_oid_get_md_hmac( const mbedtls_asn1_buf *oid, mbedtls_md_type_t *md_hmac );
#endif /* MBEDTLS_MD_C */

/**
 * \brief将扩展密钥用法OID转换为描述
 *
 * \param oid oid，用于存储字符串指针
 *
 * \如果成功，则返回0，或MBEDTLS_ERROR_OID_NOT_FOUND
 */
int mbedtls_oid_get_extended_key_usage( const mbedtls_asn1_buf *oid, const char **desc );

/**
 * \brief将证书策略OID转换为描述
 *
 * \param oid oid，用于存储字符串指针
 *
 * \如果成功，则返回0，或MBEDTLS_ERROR_OID_NOT_FOUND
 */
int mbedtls_oid_get_certificate_policies( const mbedtls_asn1_buf *oid, const char **desc );

/**
 * \brief将md_type转换为哈希算法OID
 *
 * \param md_alg消息摘要算法\param id存储ASN的位置。1 OID字符串指针\n OID的长度
 *
 * \如果成功，则返回0，或MBEDTLS_ERROR_OID_NOT_FOUND
 */
int mbedtls_oid_get_oid_by_md( mbedtls_md_type_t md_alg, const char **oid, size_t *olen );

#if defined(MBEDTLS_CIPHER_C)
/**
 * \brief将加密算法OID转换为cipher_type
 *
 * \param oid oid，用于使用\param cipher_alg位置存储加密算法
 *
 * \如果成功，则返回0，或MBEDTLS_ERROR_OID_NOT_FOUND
 */
int mbedtls_oid_get_cipher_alg( const mbedtls_asn1_buf *oid, mbedtls_cipher_type_t *cipher_alg );
#endif /* MBEDTLS_CIPHER_C */

#if defined(MBEDTLS_PKCS12_C)
/**
 * \brief将PKCS#12 PBE算法OID转换为md_type和cipher_type
 *
 * \param oid oid用于使用\param md_alg位置存储消息摘要算法\param cipher_alg存储加密算法
 *
 * \如果成功，则返回0，或MBEDTLS_ERROR_OID_NOT_FOUND
 */
int mbedtls_oid_get_pkcs12_pbe_alg( const mbedtls_asn1_buf *oid, mbedtls_md_type_t *md_alg,
                            mbedtls_cipher_type_t *cipher_alg );
#endif /* MBEDTLS_PKCS12_C */

#ifdef __cplusplus
}
#endif

#endif /* 同上*/

