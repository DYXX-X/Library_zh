// 版权所有2020 Espressif Systems（上海）私人有限公司
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

#include "sdkconfig.h"

/* 使用rom中的枚举实现向后兼容性*/
#if CONFIG_IDF_TARGET_ESP32
#include "esp32/rom/sha.h"
#elif CONFIG_IDF_TARGET_ESP32S2
#include "esp32s2/rom/sha.h"
#elif CONFIG_IDF_TARGET_ESP32S3
#include "esp32s3/rom/sha.h"
#elif CONFIG_IDF_TARGET_ESP32C3
#include "esp32c3/rom/sha.h"
#elif CONFIG_IDF_TARGET_ESP32H2
#include "esp32h2/rom/sha.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* 使用rom中的枚举实现向后兼容性*/
#if CONFIG_IDF_TARGET_ESP32
typedef enum SHA_TYPE esp_sha_type;
#else
typedef SHA_TYPE esp_sha_type;
#endif

#ifdef __cplusplus
}
#endif

