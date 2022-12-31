/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

# include "export.h"
# include "randombytes.h"

SODIUM_EXPORT
extern const struct randombytes_implementation randombytes_esp32_implementation;

/* 在这里定义RANDOMBYTES_DEFAULT_IMPLEMENTATION允许我们以ESP32硬件实现作为默认编译。无需调用randombytes_set_implementation（）。

   在头中这样做比通过-D参数传递给gcc更容易。
*/
#undef RANDOMBYTES_DEFAULT_IMPLEMENTATION
#define RANDOMBYTES_DEFAULT_IMPLEMENTATION &randombytes_esp32_implementation

