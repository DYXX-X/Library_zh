/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define TRACEMEM_MUX_BLK0_NUM                   19
#define TRACEMEM_MUX_BLK1_NUM                   20
#define TRACEMEM_BLK_NUM2ADDR(_n_)              (0x3FFB8000UL + 0x4000UL*((_n_)-4))

#define TRACEMEM_BLK0_ADDR                      TRACEMEM_BLK_NUM2ADDR(TRACEMEM_MUX_BLK0_NUM)
#define TRACEMEM_BLK1_ADDR                      TRACEMEM_BLK_NUM2ADDR(TRACEMEM_MUX_BLK1_NUM)

#ifdef __cplusplus
}
#endif

