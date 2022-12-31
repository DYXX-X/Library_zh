/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/////////////////////////////////////////////////////////////////////////////////////////
// ESP内存保护API（PMS）
// -允许PMS模块操作的配置和违规中断处理
// -不打算供公众使用。

#pragma once

#include "sdkconfig.h"
#if CONFIG_ESP_SYSTEM_MEMPROT_FEATURE || CONFIG_ESP_SYSTEM_MEMPROT_TEST

#include <stdbool.h>
#include <stdint.h>
#include "esp_err.h"
#include "esp_memprot_err.h"
#include "soc_memprot_types.h"
#include "esp_memprot_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ESP_MEMPROT_ERR_CHECK(retval, fnc) if ((retval=fnc) != ESP_OK) { return retval; }

/**
* @brief 基本PMS中断源信息
*/
typedef struct {
    esp_mprot_mem_t mem_type;   /*!< 包含错误地址的内存类型*/
    int core;                   /*!< 运行错误指令的CPU/核心ID*/
} esp_memp_intr_source_t;

/**
 * @brief 清除给定内存类型和CPU/核心ID的当前中断ON标志
 *
 * 对于PMS模块设计的某些芯片，此操作是非原子的。在这种情况下，中断清除分两步进行：1.设置中断CLR标志（清除中断ON状态并禁止链接的中断处理）2.重置中断CLR标志
 *
 * @param mem_type 内存类型（请参见esp_mprot_mem_t enum）
 * @param core 目标CPU/核心ID（请参阅soc.h中的*_CPU_NUM defs）。在1-CPU系统上可以为NULL
 *
 * @return 成功传递无效指针ESP_ERR_MEMPROT_MEMORY_TYPE_INVALID时的ESP_ERR_INVALID_ARG为ESP_OK
 */
esp_err_t esp_mprot_monitor_clear_intr(const esp_mprot_mem_t mem_type, int const *const core);

/**
 * @brief 检查PMS设置是否锁定
 *
 * @param[out] locked 有锁吗？（真/假）
 *
 * @return 成功时ESP_OK ESP_ERR_INVALID_ARG无效锁定ptr其他失败：任何失败的ESP_mprot_get__lock（）例程的错误代码（内部调用）
 */
esp_err_t esp_mprot_is_conf_locked_any(bool *locked);

/**
 * @brief 检查是否启用任何PMS违规中断监控
 *
 * @param[out] locked 启用任何PMS违规中断监视器（真/假）
 *
 * @return 成功时ESP_OK ESP_ERR_INVALID_ARG无效启用ptr其他失败：ESP_mprot_get_monitor_en（）例程的错误代码（对所有内存类型进行内部调用）
 */
esp_err_t esp_mprot_is_intr_ena_any(bool *enabled);

/**
 * @brief 返回活动PMS违规中断内存类型（如果有）（未检测到时为MEMPROT_type_NONE）和运行错误代码的CPU/CoreID（无中断时为-1）
 *
 * 如果上指示了更多中断（不应该发生），则优先顺序由“esp_mprot_mem_t”枚举定义（低->高）给出
 *
 * @param[out] mem_type 错误地址给出的内存类型的输出指针（请参阅esp_mprot_mem_t enum）
 * @param[out] core CPU/核心ID的输出指针（请参阅soc.h中的*_CPU_NUM defs）
 *
 * @return 成功传递无效指针时的ESP_OK ESP_ERR_INVALID_ARG
 */
esp_err_t esp_mprot_get_active_intr(esp_memp_intr_source_t *active_memp_intr);

/**
 * @brief 返回导致给定内存类型和CPU/核心ID冲突中断的地址。在基本解析（当前）中断参数（即对应的内存类型和CPU ID，请参阅esp_mprot_get_active_intr（））后调用此函数。这是为了最小化实际异常的处理时间，因为此API通常用于紧急处理代码中。如果所需的内存类型/CPU ID没有可用的活动中断，fault_addr将设置为NULL。
 *
 * @param mem_type 存储器类型
 * @param[out] fault_addr 导致PMS违规中断的操作地址
 * @param core 错误指令CPU/核心ID（请参阅soc.h中的*_CPU_NUM defs）。在1-CPU系统上可以为NULL
 *
 * @return 成功时ESP_OK ESP_ERR_MEMPROT_MEMORY_TYPE_INVALID无效mem_TYPE ESP_ERR_INVALID_ARG无效fault_addr指针
 */
esp_err_t esp_mprot_get_violate_addr(const esp_mprot_mem_t mem_type, void **fault_addr, int const *const core);

/**
 * @brief 返回导致冲突中断的代码的PMS World标识符
 *
 * 该值从适当的PMS违规状态寄存器中读取，因此如果中断当前未激活，则该值可能为0。
 *
 * @param mem_type 内存类型
 * @param[out] world PMS世界型（见esp_mprot_PMS_World_t）
 * @param core 错误指令CPU/核心ID（请参阅soc.h中的*_CPU_NUM defs）。在1-CPU系统上可以为NULL
 *
 * @return 成功时的ESP_OK ESP_ERR_MEMPROT_MEMORY_TYPE_INVALID（针对无效的mem_TYPE）
 */
esp_err_t esp_mprot_get_violate_world(const esp_mprot_mem_t mem_type, esp_mprot_pms_world_t *world, int const *const core);

/**
 * @brief 返回导致冲突中断的操作类型
 *
 * 根据给定的内存类型参数，在各种PMS状态寄存器标志上处理操作解析。如果中断不是活动的，则返回的结果是不相关的（可能评估为MEMPROT_OP_READ）。
 *
 * @param mem_type 内存类型
 * @param[out] oper 操作类型（参见MEMPROT_OP_*定义）
 * @param core 错误指令CPU/核心ID（请参阅soc.h中的*_CPU_NUM defs）。在1-CPU系统上可以为NULL
 *
 * @return 成功时ESP_OK ESP_ERR_MEMPROT_MEMORY_TYPE_INVALID无效mem_TYPE ESP_ERR_INVALID_ARG无效操作指针
 */
esp_err_t esp_mprot_get_violate_operation(const esp_mprot_mem_t mem_type, uint32_t *oper, int const *const core);

/**
 * @brief 检查给定内存类型是否支持字节启用信息
 *
 * 字节启用状态仅适用于DMA/DRAM操作
  *
 * @param mem_type 存储器类型
 *
 * @return byte启用可用信息真/假
 */
bool esp_mprot_has_byte_enables(const esp_mprot_mem_t mem_type);

/**
 * @brief 返回导致冲突中断的地址的字节启用
 *
 * 根据给定的内存类型，该值取自适当的PMS违规状态寄存器
 *
 * @param mem_type 内存类型（MEMPROT_type_DRAM0_SRAM）
 * @param[out] byte_en 字节启用位
 * @param core 错误指令CPU/核心ID（请参阅soc.h中的*_CPU_NUM defs）。在1-CPU系统上可以为NULL
 *
 * @return 成功时ESP_OK：无效mem_TYPE上的ESP_ERR_MEMPROT_MEMORY_TYPE_INVALID：无效byte_en指针上的ESP-ERR_INVALID_ARGUMENT
 */
esp_err_t esp_mprot_get_violate_byte_enables(const esp_mprot_mem_t mem_type, uint32_t *byte_en, int const *const core);

/**
 * @brief 设置PMS默认值的便捷程序
 *
 * 在系统启动时调用，具体取决于ESP_system_MEMPROT_FEATURE Kconfig值
 *
 * @param memp_config 指向Memprot配置结构（esp_memp_config_t）的指针。特定于芯片的结构，有关详细信息和默认值，请参阅相应的[目标芯片]/soc_memprot_types.h
 *
 * @return 成功时ESP_OK其他失败：内部调用的失败例程的错误代码。在这种情况下，由于大量的嵌入式调用，没有提供特定的错误处理（即没有提供全局唯一错误表，因此一个错误代码可能具有不同的含义，这取决于发出错误的例程）
 */
esp_err_t esp_mprot_set_prot(const esp_memp_config_t *memp_config);

/**
 * @brief 生成实际设备的PMS配置字符串（诊断）
 *
 * 这些函数从实际设备的PMS（或类似）模块的当前配置、控制和状态寄存器生成字符串。使用HAL LL调用获取值，以帮助查找Memprot API实现中可能的错误
 *
 * @param[out] dump_info_string 配置字符串缓冲区指针。字符串由被调用者分配，必须由调用者释放。
 *
 * @return 成功时的ESP_OK缓冲区分配失败时的ESP_ERR_NO_MEM ESP_ERR_INVALID_ARGUMENT无效的dump_info_string指针
 */
esp_err_t esp_mprot_dump_configuration(char **dump_info_string);

#ifdef __cplusplus
}
#endif

#endif //CONFIG_ESP_SYSTEM_MEMPROT_FEATURE || CONFIG_ESP_SYSTEM_MEMPROT_TEST

