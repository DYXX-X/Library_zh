/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define COUNT_EFUSE_REG_PER_BLOCK 8      /* 每个块的寄存器数。*/

#define ESP_EFUSE_SECURE_VERSION_NUM_BLOCK EFUSE_BLK0

#define ESP_EFUSE_FIELD_CORRESPONDS_CODING_SCHEME(scheme, max_num_bit)

#ifdef __cplusplus
}
#endif

