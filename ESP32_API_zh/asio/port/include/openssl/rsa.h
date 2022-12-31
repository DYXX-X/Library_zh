/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _ESP_ASIO_OPENSSL_RSA_STUB_H
#define _ESP_ASIO_OPENSSL_RSA_STUB_H
// 使用esp openssl编译ASIO所需的伪标头

#if defined(ASIO_USE_WOLFSSL)
#include_next "openssl/rsa.h"
#endif // ASIO_USE_WOLFSSL

#endif // _ESP_ASIO_OPENSSL_RSA_STUB_H

