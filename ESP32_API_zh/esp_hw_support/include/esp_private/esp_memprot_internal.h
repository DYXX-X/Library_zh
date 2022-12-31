/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "sdkconfig.h"
#if CONFIG_ESP_SYSTEM_MEMPROT_FEATURE || CONFIG_ESP_SYSTEM_MEMPROT_TEST

#include <stdbool.h>
#include <stdint.h>
#include "esp_err.h"
#include "esp_memprot_err.h"
#include "hal/memprot_types.h"
#include "soc_memprot_types.h"
#include "esp_memprot_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief 将Memprot低级错误转换为esp_err_t
*/
esp_err_t esp_mprot_ll_err_to_esp_err(const memprot_ll_err_t err);

/**
 * @brief 将Memprot低级PMS World ID转换为esp_mprot_PMS_World_t
 */
esp_mprot_pms_world_t esp_mprot_ll_world_to_hl_world(const memprot_ll_world_t world);

/**
 * @brief 将操作类型转换为字符串，不允许操作组合
 *
 * @param oper_type PMS操作类型
 */
const char *esp_mprot_oper_type_to_str(const uint32_t oper_type);

/**
 * @brief 将PMS World类型转换为字符串
 *
 * @param area_type PMS世界型
 */
const char *esp_mprot_pms_world_to_str(const esp_mprot_pms_world_t world_type);

/**
 * @brief 设置目标内存类型中给定行类型的拆分地址
 *
 * @param mem_type 存储器类型
 * @param line_type 分割地址类型
 * @param line_addr 与给定line_addr相关的内存范围中的目标地址
 *
 * @return 成功时ESP_OK ESP_ERR_MEMPROT_MEMORY_TYPE_INVALID无效mem_TYPE ESP_ERR-MEMPROT_PLIT_ADDR_INVALID线类型无效ESP_ERR_MEMPROT_SPLIT_ADDR_OUT_OF_RANGE拆分线超出给定内存类型范围ESP_ERR_LEMPROT_SPLIT_ADDT_UNALIGNED拆分线未与PMS所需边界对齐
 */
esp_err_t esp_mprot_set_split_addr(const esp_mprot_mem_t mem_type, const esp_mprot_split_addr_t line_type, const void *line_addr);

/**
 * @brief 获取给定split_addr类型的PMS拆分地址
 *
 * 从PMS配置寄存器中读取该值
 *
 * @param mem_type 存储器类型
 * @param line_type 拆分线型（请参见esp_mprot_Split_addr_t enum）
 * @param[out] line_addr 从配置寄存器分割行地址
 *
 * @return 成功时的ESP_OK line_addr上的ESP_ERR_INVALID_ARG是无效mem_TYPE上的指针ESP_ERR_MEMPROT_MEMORY_TYPE_INVALID
 */
esp_err_t esp_mprot_get_split_addr(const esp_mprot_mem_t mem_type, const esp_mprot_split_addr_t line_type, void **line_addr);

/**
 * @brief 返回给定内存类型的默认主I/O拆分地址
 *
 * @param mem_type 存储器类型
 * @param[out] def_split_addr 所需mem_type的主I/O拆分地址
 *
 * @return 成功时ESP_OK无效的def_split_addr指针ESP_ERR_MEMPROT_MEMORY_TYPE_INVALID无效的mem_TYPE上的ESP_ERR_INVALID_ARG
 */
esp_err_t esp_mprot_get_default_main_split_addr(const esp_mprot_mem_t mem_type, void **def_split_addr);

/**
 * @brief 为主IRAM/DRAM分割地址设置锁。只有通过数字系统重置才能解锁锁
 *
 * @param mem_type 存储器类型
 *
 * @return 成功时ESP_OK ESP_ERR_MEMPROT_MEMORY_TYPE_INVALID无效mem_TYPE
 */
esp_err_t esp_mprot_set_split_addr_lock(const esp_mprot_mem_t mem_type);

/**
 * @brief 获取给定内存类型的拆分地址配置的锁定状态
 *
 * @param mem_type 存储器类型
 * @param[out] locked mem_type相关的锁定状态
 *
 * @return 成功时ESP_OK ESP_ERR_INVALID_ARGUMENT对无效的锁定指针ESP_ERR_MEMPROT_MEMORY_TYPE_INVALID对无效的mem_TYPE
 */
esp_err_t esp_mprot_get_split_addr_lock(const esp_mprot_mem_t mem_type, bool *locked);

/**
 * @brief 为所需内存类型的PMS区域设置设置锁。只有通过数字系统重置才能解锁锁
 *
 * @param mem_type 存储器类型
 *
 * @return 成功时ESP_OK ESP_ERR_MEMPROT_MEMORY_TYPE_INVALID无效mem_TYPE
 */
esp_err_t esp_mprot_set_pms_lock(const esp_mprot_mem_t mem_type);

/**
 * @brief 获取所需内存类型的PMS区域设置的锁定状态
 *
 * @param mem_type 存储器类型
 * @param[out] locked mem_type相关的锁定状态
 *
 * @return 成功时ESP_OK：无效mem_TYPE上的ESP_ERR_MEMPROT_MEMORY_TYPE_INVALID：无效锁定指针上的ESP-ERR_INVALID_ARGUMENT
 */
esp_err_t esp_mprot_get_pms_lock(const esp_mprot_mem_t mem_type, bool *locked);

/**
 * @brief 设置给定PMS区域的权限
 *
 * @param area_type PMS区域类型
 * @param flags MEMPROT_OP_*的组合定义
 *
 * @return 成功时ESP_OK ESP_ERR_MEMPROT_MEMORY_TYPE_INVALID无效mem_TYPE
 */
esp_err_t esp_mprot_set_pms_area(const esp_mprot_pms_area_t area_type, const uint32_t flags);

/**
 * @brief 获取给定PMS区域的当前权限
 *
 * @param area_type PMS区域类型
 * @param[out] flags MEMPROT_OP_*的组合定义
 *
 * @return 成功时ESP_OK ESP_ERR_MEMPROT_MEMORY_TYPE_INVALID无效mem_TYPE ESP_ERR_INVALID_ARG无效标志指针
 */
esp_err_t esp_mprot_get_pms_area(const esp_mprot_pms_area_t area_type, uint32_t *flags);

/**
 * @brief 为所需内存类型的PMS中断监视器设置设置锁
 *
 * 只有通过数字系统重置才能解锁锁
 *
 * @param mem_type 内存类型（请参阅esp_mprot_mem_t enum）
 *
 * @return 成功时ESP_OK ESP_ERR_MEMPROT_MEMORY_TYPE_INVALID无效mem_TYPE
 */
esp_err_t esp_mprot_set_monitor_lock(const esp_mprot_mem_t mem_type);

/**
 * @brief 获取所需内存类型的PMS中断监视器设置的锁定状态
 *
 * @param mem_type 存储器类型
 * @param[out] locked mem_type相关的锁定状态
 *
 * @return 成功时ESP_OK ESP_ERR_MEMPROT_MEMORY_TYPE_INVALID无效mem_TYPE ESP_ERR_INVALID_ARG无效锁定指针
 */
esp_err_t esp_mprot_get_monitor_lock(const esp_mprot_mem_t mem_type, bool *locked);

/**
 * @brief 启用所需内存类型的PMS违规中断监控
 *
 * @param mem_type 存储器类型
 * @param enable 启用/禁用违规中断监视
 *
 * @return 成功时ESP_OK ESP_ERR_MEMPROT_MEMORY_TYPE_INVALID无效mem_TYPE
 */
esp_err_t esp_mprot_set_monitor_en(const esp_mprot_mem_t mem_type, const bool enable);

#ifdef __cplusplus
}
#endif

#endif //CONFIG_ESP_SYSTEM_MEMPROT_FEATURE || CONFIG_ESP_SYSTEM_MEMPROT_TEST

