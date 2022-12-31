/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

/* 为bootloader_support代码提供SHA256 API，可从bootloader或应用程序代码中使用。

   此标头仅可用于bootloader和bootloader_support组件中的源代码。使用mbedTLS API或包含esp32/sha。h来计算IDF应用程序中的SHA256。
*/

#include <stdint.h>
#include <stdlib.h>
#include "esp_err.h"

typedef void *bootloader_sha256_handle_t;

bootloader_sha256_handle_t bootloader_sha256_start(void);

void bootloader_sha256_data(bootloader_sha256_handle_t handle, const void *data, size_t data_len);

void bootloader_sha256_finish(bootloader_sha256_handle_t handle, uint8_t *digest);

