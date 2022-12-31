/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _ESP_ASIO_OPENSSL_CONF_H
#define _ESP_ASIO_OPENSSL_CONF_H
#include "esp_asio_config.h"
#include "openssl/esp_asio_openssl_stubs.h"

#if defined(ASIO_USE_WOLFSSL)
// 当前wolfSSL库中不存在SSLv3方法
#define OPENSSL_NO_SSL3
#include_next "openssl/conf.h"
#endif // ASIO_USE_WOLFSSL

#endif // _ESP_ASIO_OPENSSL_CONF_H

