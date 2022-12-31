/**
 * \文件doc_x509.h
 *
 * \简短的X.509模块文档文件。
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
 * @addtogroup x509_模块X.509模块
 *
 * X.509模块为证书的读、写和验证提供X.509支持。总而言之：
 *   -X.509证书（CRT）读取（请参阅\c mbedtls_x509_CRT_parse（）、\c mbedtls_x509_CRT_parse_der（）、\ c mbedtls-x509_CRT-parse_file（））。
 *   -X.509证书吊销列表（CRL）读取（请参阅\c mbedtls_x509_CRL_parse（）、\c mbedtls_x509_CRL_parse_der（）和\c mbedt ls_x509c_rl_parse_file（））。
 *   -X.509证书签名验证（请参见\c mbedtls_x509_crt_verify（）和\c mbedt ls_x509_crt_verify_with_profile（）。
 *   -X.509证书写入和证书请求写入（请参见\c mbedtls_x509write_csr_der（）和\c mbedt ls_x509write_csr_deer（））。
 *
 * 此模块可用于构建证书颁发机构（CA）链并验证其签名。它还用于生成证书签名请求和X.509证书，就像CA所做的那样。
 */

