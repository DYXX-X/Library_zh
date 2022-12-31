/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/* MMU内存保护功能的内部API通用接口
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "esp_attr.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

//方便的常量，提高代码可读性
#define RD_ENA                  true
#define RD_DIS                  false
#define WR_ENA                  true
#define WR_DIS                  false
#define EX_ENA                  true
#define EX_DIS                  false
#define RD_LOW_ENA              true
#define RD_LOW_DIS              false
#define WR_LOW_ENA              true
#define WR_LOW_DIS              false
#define EX_LOW_ENA              true
#define EX_LOW_DIS              false
#define RD_HIGH_ENA             true
#define RD_HIGH_DIS             false
#define WR_HIGH_ENA             true
#define WR_HIGH_DIS             false
#define EX_HIGH_ENA             true
#define EX_HIGH_DIS             false
#define PANIC_HNDL_ON           true
#define PANIC_HNDL_OFF          false
#define MEMPROT_LOCK            true
#define MEMPROT_UNLOCK          false
#define DEF_SPLIT_LINE          NULL

#define MEMPROT_INVALID_ADDRESS -1

//内存范围类型
typedef enum {
    MEMPROT_NONE =              0x00000000,
    MEMPROT_IRAM0_SRAM =        0x00000001, //0x40020000-0x4006FFF，RWX
    MEMPROT_DRAM0_SRAM =        0x00000002, //0x3FFB00-0x3FFFFFFF，RW
    MEMPROT_IRAM0_RTCFAST =     0x00000004, //0x400700000-0x40071FFF，RWX
    MEMPROT_DRAM0_RTCFAST =     0x00000008, //0x3FF9E000-00x3FF9FFFF，RW
    MEMPROT_PERI1_RTCSLOW =     0x00000010, //0x3F42100-0x3F42300，RW
    MEMPROT_PERI2_RTCSLOW_0 =   0x00000020, //0x50001000-0x50003000，RWX
    MEMPROT_PERI2_RTCSLOW_1 =   0x00000040, //0x60002000-0x60004000，RWX
    MEMPROT_ALL =               0xFFFFFFFF
} mem_type_prot_t;


/**
 * @brief 返回所需内存区域的拆分地址
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 *
 * @return 需要拆分内存区域的地址。地址由从链接器脚本导出的特定于区域的全局符号给出，它不会从相关的配置寄存器中读出。
 */
uint32_t *IRAM_ATTR esp_memprot_get_split_addr(mem_type_prot_t mem_type);

/**
 * @brief 初始化所需内存段的非法内存访问控制。
 *
 * 所有内存访问中断共享ETS_MEMACCESS_ERR_INUM输入通道，正确检测实际intr是调用者的责任。以及在一个intr期间报告多个源的情况下可能的优先级。处理程序运行
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）\
 *
 * @return 成功时ESP_OK，失败时ESP_ERR_INVALID_ARG
 */
esp_err_t esp_memprot_intr_init(mem_type_prot_t mem_type);

/**
 * @brief 启用/禁用内存保护中断
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 * @param enable 启用/禁用
 *
 * @return 成功时ESP_OK，失败时ESP_ERR_INVALID_ARG
 */
esp_err_t esp_memprot_intr_ena(mem_type_prot_t mem_type, bool enable);

/**
 * @brief 为指定内存区域设置清除中断标志的请求（寄存器写入）
 *
 * @note 当在标志设置上没有实际中断的情况下调用时，相关中断的后续发生将被忽略。应仅在实际中断出现后使用，通常作为中断处理程序例程的最后一步。
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 *
 * @return 成功时ESP_OK，失败时ESP_ERR_INVALID_ARG
 */
esp_err_t esp_memprot_clear_intr(mem_type_prot_t mem_type);

/**
 * @brief 检测哪个内存保护中断处于活动状态
 *
 * @note 检查订单MEMPROT_IRAM0_SRAM MEMPROT_IRAM0_RTCFAST MEMPROT_DRAM0_SRAM MEMPRO T_DRAM0_RTCFAST
 *
 * @return 内存保护区类型（请参见mem_type_prot_t enum）
 */
mem_type_prot_t IRAM_ATTR esp_memprot_get_active_intr_memtype(void);

/**
 * @brief 获取指定内存区域的中断状态寄存器内容
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 * @param fault_reg_val 状态寄存器的内容
 *
 * @return 成功时ESP_OK，失败时ESP_ERR_INVALID_ARG
 */
esp_err_t esp_memprot_get_fault_reg(mem_type_prot_t mem_type, uint32_t *fault_reg_val);

/**
 * @brief 获取给定中断状态的详细信息
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 * @param faulting_address 导致中断的错误地址[out]
 * @param op_type 在错误地址[out]IRAM0处处理的操作：0-读取，1-写入DRAM0：0-读，1-写
 * @param op_subtype op_type[out]IRAM0的附加信息：0-指令段访问，1-数据段访问DRAM0:0-非原子操作，1-原子操作
 * @return 成功时ESP_OK，失败时ESP_ERR_INVALID_ARG
 */
esp_err_t IRAM_ATTR esp_memprot_get_fault_status(mem_type_prot_t mem_type, uint32_t **faulting_address, uint32_t *op_type, uint32_t *op_subtype);

/**
 * @brief 获取所需内存区域标识符的字符串表示形式
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 *
 * @return mem_type作为字符串
 */
const char *IRAM_ATTR esp_memprot_type_to_str(mem_type_prot_t mem_type);

/**
 * @brief 检测是否有任何中断锁处于激活状态（需要数字系统复位才能解锁）
 *
 * @return 真/假
 */
bool esp_memprot_is_locked_any(void);

/**
 * @brief 设置指定内存区域的锁定。
 *
 * 只有通过数字系统重置才能解锁锁
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 *
 * @return 成功时ESP_OK，失败时ESP_ERR_INVALID_ARG
 */
esp_err_t esp_memprot_set_lock(mem_type_prot_t mem_type);

/**
 * @brief 获取所需内存区域的锁定状态
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 * @param locked 设置锁定：真/假（锁定/解锁）
 *
 * @return 成功时ESP_OK，失败时ESP_ERR_INVALID_ARG
 */
esp_err_t esp_memprot_get_lock(mem_type_prot_t mem_type, bool *locked);

/**
 * @brief 获取所需内存区域的权限控制配置寄存器内容
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 * @param conf_reg_val 权限控制寄存器内容
 *
 * @return 成功时ESP_OK，失败时ESP_ERR_INVALID_ARG
 */
esp_err_t esp_memprot_get_conf_reg(mem_type_prot_t mem_type, uint32_t *conf_reg_val);

/**
 * @brief 获取统一管理块的中断权限设置
 *
 * 获取所需内存区域的中断权限设置寄存器内容，返回统一管理块的设置
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 * @param perm_reg 权限设置注册内容
 *
 * @return 成功时ESP_OK，失败时ESP_ERR_INVALID_ARG
 */
esp_err_t esp_memprot_get_perm_uni_reg(mem_type_prot_t mem_type, uint32_t *perm_reg);

/**
 * @brief 获取拆分管理块的中断权限设置
 *
 * 获取所需内存区域（统一管理块）的中断权限设置寄存器内容
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 * @return split_reg统一管理设置寄存器内容
 *
 * @return 成功时ESP_OK，失败时ESP_ERR_INVALID_ARG
 */
esp_err_t esp_memprot_get_perm_split_reg(mem_type_prot_t mem_type, uint32_t *split_reg);

/**
 * @brief 检测是否启用了任何内存保护中断
 *
 * @return 真/假
 */
bool esp_memprot_is_intr_ena_any(void);

/**
 * @brief 获取给定内存区域的中断启用标志
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 * @param enable_bit 中断启用标志
 *
 * @return 成功时ESP_OK，失败时ESP_ERR_INVALID_ARG
 */
esp_err_t esp_memprot_get_intr_ena_bit(mem_type_prot_t mem_type, uint32_t *enable_bit);

/**
 * @brief 获取给定内存区域的中断活动标志
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 * @param intr_on_bit 中断激活标志
 *
 * @成功时返回ESP_OK，失败时返回ESP_ERR_INVALID_ARG*/
esp_err_t esp_memprot_get_intr_on_bit(mem_type_prot_t mem_type, uint32_t *intr_on_bit);

/**
 * @brief 获取给定内存区域的中断清除请求标志
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 * @param clear_bit 中断清除请求标志
 *
 * @return 成功时ESP_OK，失败时ESP_ERR_INVALID_ARG
 */
esp_err_t esp_memprot_get_intr_clr_bit(mem_type_prot_t mem_type, uint32_t *clear_bit);

/**
 * @brief 获取指定块和内存区域的读取权限值
 *
 * 返回给定内存区域中所需统一管理块（0-3）的读取权限位值。适用于所有内存类型。
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 * @param block 内存块标识符（0-3）
 * @param read_bit 读取所需块的权限值
 *
 * @return 成功时ESP_OK，失败时ESP_ERR_INVALID_ARG
 */
esp_err_t esp_memprot_get_uni_block_read_bit(mem_type_prot_t mem_type, uint32_t block, uint32_t *read_bit);

/**
 * @brief 获取指定块和内存区域的写入权限值
 *
 * 返回给定内存区域中所需统一管理块（0-3）的写入权限位值。适用于所有内存类型。
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 * @param block 内存块标识符（0-3）
 * @param write_bit 所需块的写入权限值
 *
 * @return 成功时ESP_OK，失败时ESP_ERR_INVALID_ARG
 */
esp_err_t esp_memprot_get_uni_block_write_bit(mem_type_prot_t mem_type, uint32_t block, uint32_t *write_bit);

/**
 * @brief 获取指定块和内存区域的执行权限值
 *
 * 返回给定内存区域中所需统一管理块（0-3）的执行权限位值。仅适用于IRAM内存类型
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 * @param block 内存块标识符（0-3）
 * @param exec_bit 执行所需块的权限值
 *
 * @return 成功时ESP_OK，失败时ESP_ERR_INVALID_ARG
 */
esp_err_t esp_memprot_get_uni_block_exec_bit(mem_type_prot_t mem_type, uint32_t block, uint32_t *exec_bit);

/**
 * @brief 设置DRAM区域中指定块的权限
 *
 * 为给定内存区域中指定的统一管理块（0-3）设置读写权限。仅适用于DRAM内存类型
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 * @param block 内存块标识符（0-3）
 * @param write_perm 写入权限标志
 * @param read_perm 读取权限标志
 *
 * @return 成功时ESP_OK，失败时ESP_ERR_INVALID_ARG
 */
esp_err_t esp_memprot_set_uni_block_perm_dram(mem_type_prot_t mem_type, uint32_t block, bool write_perm, bool read_perm);

/**
 * @brief 设置DRAM区域中高内存段和低内存段的权限
 *
 * 设置由拆分地址给定的低内存段和高内存段的读写权限。分割地址必须等于或高于块5的开头仅适用于DRAM存储器类型
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 * @param split_addr 将内存区域拆分为较低段和较高段的地址
 * @param lw 低段写入权限标志
 * @param lr 低段读取权限标志
 * @param hw 高段写入权限标志
 * @param hr 高段读取权限标志
 *
 * @return 成功时ESP_OK，失败时ESP_ERR_INVALID_ARG
 */
esp_err_t esp_memprot_set_prot_dram(mem_type_prot_t mem_type, uint32_t *split_addr, bool lw, bool lr, bool hw, bool hr);

/**
 * @brief 设置IRAM区域中指定块的权限
 *
 * 为给定内存区域中指定的统一管理块（0-3）设置读取、写入和执行权限。仅适用于IRAM内存类型
 *
 * @param mem_type 内存保护区类型（MEMPROT_IRAM0_SRAM）
 * @param block 内存块标识符（0-3）
 * @param write_perm 写入权限标志
 * @param read_perm 读取权限标志
 * @param exec_perm 执行权限标志
 *
 * @return 成功时ESP_OK ESP_ERR_NOT_SUPPORTED对无效的mem_type ESP_ERR_invalid_ARG对错误的块编号
 */
esp_err_t esp_memprot_set_uni_block_perm_iram(mem_type_prot_t mem_type, uint32_t block, bool write_perm, bool read_perm, bool exec_perm);

/**
 * @brief 设置IRAM区域中高内存段和低内存段的权限
 *
 * 设置由拆分地址给定的低内存段和高内存段的读取、写入和执行权限。拆分地址必须等于或高于块5的开头仅适用于IRAM内存类型
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 * @param split_addr 将内存区域拆分为较低段和较高段的地址
 * @param lw 低段写入权限标志
 * @param lr 低段读取权限标志
 * @param lx 低段执行权限标志
 * @param hw 高段写入权限标志
 * @param hr 高段读取权限标志
 * @param hx 高段执行权限标志
 *
 * @return 成功时ESP_OK，失败时ESP_ERR_INVALID_ARG
 */
esp_err_t esp_memprot_set_prot_iram(mem_type_prot_t mem_type, uint32_t *split_addr, bool lw, bool lr, bool lx, bool hw, bool hr, bool hx);

/**
 * @brief 为所有受支持的内存区域类型激活内存保护
 *
 * @note 连接JTAG接口时禁用该功能
 *
 * @param invoke_panic_handler 地图内存。ETS_MEMACCESS_ERR_INUM的prot中断，因此在触发时调用紧急处理程序（'true'不适合测试）
 * @param lock_feature 设置LOCK位，请参见esp_memprot_set_LOCK（）（'true'不适合测试）
 * @param mem_type_mask 保存一组所需的内存保护类型（由mem_type_prott构建的位掩码）。NULL表示默认值（在此版本中为MEMPROT_ALL）
 *
 * @return 成功时ESP_OK，失败时ESP_ERR_INVALID_ARG
 */
esp_err_t esp_memprot_set_prot(bool invoke_panic_handler, bool lock_feature, uint32_t *mem_type_mask);

/**
 * @brief 获取IRAM0拆分管理的权限设置位。仅允许IRAM0内存类型
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 * @param lw 低段写入权限标志
 * @param lr 低段读取权限标志
 * @param lx 低段执行权限标志
 * @param hw 高段写入权限标志
 * @param hr 高段读取权限标志
 * @param hx 高段执行权限标志
 *
 * @return 成功时ESP_OK，失败时ESP_ERR_INVALID_ARG
 */
esp_err_t esp_memprot_get_perm_split_bits_iram(mem_type_prot_t mem_type, bool *lw, bool *lr, bool *lx, bool *hw, bool *hr, bool *hx);

/**
 * @brief 获取DRAM0拆分管理的权限设置位。仅允许DRAM0内存类型
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 * @param lw 低段写入权限标志
 * @param lr 低段读取权限标志
 * @param hw 高段写入权限标志
 * @param hr 高段读取权限标志
 *
 * @return 成功时ESP_OK，失败时ESP_ERR_INVALID_ARG
 */
esp_err_t esp_memprot_get_perm_split_bits_dram(mem_type_prot_t mem_type, bool *lw, bool *lr, bool *hw, bool *hr);

/**
 * @brief 设置PERIBUS1区域中高内存段和低内存段的权限
 *
 * 设置由拆分地址给定的低内存段和高内存段的读写权限。仅适用于PERIBUS1内存类型
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 * @param split_addr 将内存区域拆分为较低段和较高段的地址
 * @param lw 低段写入权限标志
 * @param lr 低段读取权限标志
 * @param hw 高段写入权限标志
 * @param hr 高段读取权限标志
 *
 * @return 成功时ESP_OK，失败时ESP_ERR_INVALID_ARG
 */
esp_err_t esp_memprot_set_prot_peri1(mem_type_prot_t mem_type, uint32_t *split_addr, bool lw, bool lr, bool hw, bool hr);

/**
 * @brief 获取PERIBUS1拆分管理的权限设置位。仅允许PERIBUS1内存类型
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 * @param lw 低段写入权限标志
 * @param lr 低段读取权限标志
 * @param hw 高段写入权限标志
 * @param hr 高段读取权限标志
 *
 * @return 成功时ESP_OK，失败时ESP_ERR_INVALID_ARG
 */
esp_err_t esp_memprot_get_perm_split_bits_peri1(mem_type_prot_t mem_type, bool *lw, bool *lr, bool *hw, bool *hr);

/**
 * @brief 获取PERIBUS2拆分管理的权限设置位。仅允许PERIBUS2内存类型
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 * @param lw 低段写入权限标志
 * @param lr 低段读取权限标志
 * @param lx 低段执行权限标志
 * @param hw 高段写入权限标志
 * @param hr 高段读取权限标志
 * @param hx 高段执行权限标志
 *
 * @return 成功时ESP_OK，失败时ESP_ERR_INVALID_ARG
 */
esp_err_t esp_memprot_get_perm_split_bits_peri2(mem_type_prot_t mem_type, bool *lw, bool *lr, bool *lx, bool *hw, bool *hr, bool *hx);

/**
 * @brief 配置PERIBUS2区域中高段和低段的内存保护
 *
 * 设置由拆分地址给定的低内存段和高内存段的读写权限。仅适用于PERIBUS2内存类型
 *
 * @param mem_type 内存保护区类型（MEMPROT_PERI2_RTCSLOW_0、MEMPROT_PERI2_RTCSLOW_1）
 * @param split_addr 将内存区域拆分为较低段和较高段的地址（32位对齐）
 * @param lw 低段写入权限标志
 * @param lr 低段读取权限标志
 * @param lx 低段执行权限标志
 * @param hw 高段写入权限标志
 * @param hr 高段读取权限标志
 * @param hx 高段执行权限标志
 *
 * @return 成功时ESP_OK ESP_ERR_NOT_SUPPORTED对无效mem_type ESP_ERR_invalid_STATE（拆分地址超出PERIBUS2范围时）ESP_ERR_invalid_SIZE（拆分地址未对齐32位）
 */
esp_err_t esp_memprot_set_prot_peri2(mem_type_prot_t mem_type, uint32_t *split_addr, bool lw, bool lr, bool lx, bool hw, bool hr, bool hx);

/**
 * @brief 获取指定内存类型的权限。忽略不相关的位
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 * @param lw 低段写入权限标志
 * @param lr 低段读取权限标志
 * @param lx 低段执行权限标志
 * @param hw 高段写入权限标志
 * @param hr 高段读取权限标志
 * @param hx 高段执行权限标志
 *
 * @return 成功时ESP_OK ESP_ERR_INVALID_ARG为空lw/lx/hw/hr/hx参数ESP_ERR_NOT_SUPPORTED为无效mem_type
 */
esp_err_t esp_memprot_get_permissions(mem_type_prot_t mem_type, bool *lw, bool *lr, bool *lx, bool *hw, bool *hr, bool *hx);

/**
 * @brief 获取给定内存类型的低区域和高区域的读取权限设置
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 * @param lr 低段读取权限标志
 * @param hr 高段读取权限标志
 *
 * @return 成功时ESP_OK ESP_ERR_INVALID_ARG为空lr/hr参数ESP_ERR_NOT_SUPPORTED为无效mem_type
 */
esp_err_t esp_memprot_get_perm_read(mem_type_prot_t mem_type, bool *lr, bool *hr);

/**
 * @brief 获取给定内存类型的低区域和高区域的写入权限设置
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 * @param lr 低段写入权限标志
 * @param hr 高段写入权限标志
 *
 * @return 成功时ESP_OK ESP_ERR_INVALID_ARG空lw/hw参数ESP_ERR_NOT_SUPPORTED无效mem_type
 */
esp_err_t esp_memprot_get_perm_write(mem_type_prot_t mem_type, bool *lw, bool *hw);

/**
 * @brief 获取给定内存类型的低区域和高区域的执行权限设置仅适用于IBUS兼容内存类型
 *
 * @param mem_type 内存保护区类型（MEMPROT_IRAM0_SRAM、MEMPROT_ILAM0_RTCFAST、MEMPROT_PERI2_RTCSLOW_0、MEMPROT-PERI2_RRCSLOW_1）
 * @param lx 低段Exec权限标志
 * @param hx 高段Exec权限标志
 *
 * @return 成功时ESP_OK ESP_ERR_INVALID_ARG为空lx/hx参数ESP_ERR_NOT_SUPPORTED为无效mem_type
 */
esp_err_t esp_memprot_get_perm_exec(mem_type_prot_t mem_type, bool *lx, bool *hx);

/**
 * @brief 返回所需内存区域中的最低地址
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 *
 * @return 无效mem_type的必需地址或MEMPROT_INVALID_address
 */
uint32_t esp_memprot_get_low_limit(mem_type_prot_t mem_type);

/**
 * @brief 返回所需内存区域中的最高地址
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 *
 * @return 无效mem_type的必需地址或MEMPROT_INVALID_address
 */
uint32_t esp_memprot_get_high_limit(mem_type_prot_t mem_type);

/**
 * @brief 设置所需内存区域的读取权限位
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 * @param lr 低段读取权限标志
 * @param hr 高段读取权限标志
 *
 * @return 成功时ESP_OK ESP_ERR_NOT_SUPPORTED的mem_type无效
 */
esp_err_t esp_memprot_set_read_perm(mem_type_prot_t mem_type, bool lr, bool hr);

/**
 * @brief 设置所需内存区域的WRITE权限位
 *
 * @param mem_type 内存保护区类型（请参见mem_type_prot_t enum）
 * @param lr 低段写入权限标志
 * @param hr 高段写入权限标志
 *
 * @return 成功时ESP_OK ESP_ERR_NOT_SUPPORTED的mem_type无效
 */
esp_err_t esp_memprot_set_write_perm(mem_type_prot_t mem_type, bool lw, bool hw);

/**
 * @brief 设置所需内存区域的EXECUTE权限位
 *
 * @param mem_type 内存保护区类型（MEMPROT_IRAM0_SRAM、MEMPROT_ILAM0_RTCFAST、MEMPROT_PERI2_RTCSLOW_0、MEMPROT-PERI2_RRCSLOW_1）
 * @param lr 低段Exec权限标志
 * @param hr 高段Exec权限标志
 *
 * @return 成功时ESP_OK ESP_ERR_NOT_SUPPORTED的mem_type无效
 */
esp_err_t esp_memprot_set_exec_perm(mem_type_prot_t mem_type, bool lx, bool hx);


#ifdef __cplusplus
}
#endif

