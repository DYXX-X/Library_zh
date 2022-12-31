/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
*
* SPDX许可证标识符：Apache-2.0
*/

#pragma once

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief ESP Memprot API错误代码定义
*/
#define ESP_ERR_MEMPROT_MEMORY_TYPE_INVALID     (ESP_ERR_MEMPROT_BASE + 1)   /**<给定上下文中的内存类型无效*/
#define ESP_ERR_MEMPROT_SPLIT_ADDR_INVALID      (ESP_ERR_MEMPROT_BASE + 2)   /**<在给定上下文中拆分地址无效*/
#define ESP_ERR_MEMPROT_SPLIT_ADDR_OUT_OF_RANGE (ESP_ERR_MEMPROT_BASE + 3)   /**<拆分地址超出范围*/
#define ESP_ERR_MEMPROT_SPLIT_ADDR_UNALIGNED    (ESP_ERR_MEMPROT_BASE + 4)   /**<拆分地址未与所需边界对齐*/
#define ESP_ERR_MEMPROT_UNIMGMT_BLOCK_INVALID   (ESP_ERR_MEMPROT_BASE + 5)   /**<所需的统一管理块无效*/
#define ESP_ERR_MEMPROT_WORLD_INVALID           (ESP_ERR_MEMPROT_BASE + 6)   /**<所需的世界标识符无效*/
#define ESP_ERR_MEMPROT_AREA_INVALID            (ESP_ERR_MEMPROT_BASE + 7)   /**<所需区域标识符无效*/

#ifdef __cplusplus
}
#endif

