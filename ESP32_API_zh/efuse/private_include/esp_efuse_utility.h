/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include "esp_types.h"
#include "esp_err.h"
#include "esp_efuse.h"
#include "sdkconfig.h"
#include_next "esp_efuse_utility.h"

#define ESP_EFUSE_CHK(ret)       \
    do                           \
    {                            \
        if( ( err = (ret) ) != ESP_OK ) \
            goto err_exit;        \
    } while( 0 )


/**
 * @brief 按块划分的结构范围地址
 */
typedef struct {
    uint32_t start;
    uint32_t end;
} esp_efuse_range_addr_t;

/**
 * @brief 这是处理efuse字段寄存器的函数类型。
 *
 * @param[in] num_reg          块中的寄存器号。
 * @param[in] efuse_block      区块编号。
 * @param[in] bit_start        寄存器中的起始位。
 * @param[in] bit_count        寄存器中使用的位数。
 * @param[in/out] arr          指向数组或变量的指针。
 * @param[in/out] bits_counter 计数器位。
 *
 * @return
 *      -ESP_OK:操作已成功完成。
 *      -其他efuse组件错误。
 */
typedef esp_err_t (*efuse_func_proc_t) (unsigned int num_reg, esp_efuse_block_t efuse_block, int starting_bit_num_in_reg, int num_bits_used_in_reg, void* arr, int* bits_counter);

/**
 * @brief 此函数通过调用传递的函数来处理字段。
 *
 * 此函数选择字段，检查长度，并调用寄存器处理函数。
 * @param[in] field           指向描述efuse字段的结构的指针。
 * @param[in/out] ptr         指向数组的指针，用于从efuse字段读取/写入efuse字段。
 * @param[in] ptr_size_bits   efuse字段的数据大小（以位为单位）。如果＝0，则读取所有字段位。
 * @param[in] func_proc       这是将处理efuse字段的函数。
 *
 * @return
 *      -ESP_OK:操作已成功完成。
 *      -其他efuse组件错误。
 */
esp_err_t esp_efuse_utility_process(const esp_efuse_desc_t* field[], void* ptr, size_t ptr_size_bits, efuse_func_proc_t func_proc);

/**
 * @brief 用所需数量的“1”位写入寄存器。
 * @param[in/out] cnt      需要在字段中设置的位数。
 */
esp_err_t esp_efuse_utility_write_cnt(unsigned int num_reg, esp_efuse_block_t efuse_block, int bit_start, int bit_count, void* cnt, int* bits_counter);

/**
 * @brief 从数组中填充寄存器以进行写入。
 * @param[in] arr_in       指向写入数据所在数组的指针。
 */
esp_err_t esp_efuse_utility_write_blob(unsigned int num_reg, esp_efuse_block_t efuse_block, int bit_start, int bit_count, void* arr_in, int* bits_counter);

/**
 * @brief 对寄存器中的一组位进行计数。
 * @param[in/out] out_cnt  指向size_t变量的指针，该变量将包含“1”位数。
 */
esp_err_t esp_efuse_utility_count_once(unsigned int num_reg, esp_efuse_block_t efuse_block, int bit_start, int bit_count, void* out_cnt, int* bits_counter);

/**
 * @brief 读取efuse寄存器并将该值写入数组。
 * @param[out] arr_out     指向将包含读取结果的数组的指针。
 */
esp_err_t esp_efuse_utility_fill_buff(unsigned int num_reg, esp_efuse_block_t efuse_block, int bit_start, int bit_count, void* arr_out, int* bits_counter);

/**
 * @brief 刻录写入efuse写入寄存器的值。
 *
 * 如果设置了CONFIG_EFUSE_VIRTUAL，则不会执行写入。功能完成后，将清除写入寄存器。
 */
void esp_efuse_utility_burn_efuses(void);

/**
 * @brief 执行写入efuse写入寄存器的值烧录的芯片特定操作。
 *
 * @note 使用esp_efuse_utility_burn_efuses（）燃烧efuses。
 *
 * 如果设置了CONFIG_EFUSE_VIRTUAL，则不会执行写入。功能完成后，将清除写入寄存器。
 */
void esp_efuse_utility_burn_chip(void);

/**
 * @brief 返回将这些“位”放置在数组中的数组元素数，每个元素的长度等于“size_of_base”。
 */
int esp_efuse_utility_get_number_of_items(int bits, int size_of_base);

/**
 * @brief 正在读取efuse寄存器。
 */
uint32_t esp_efuse_utility_read_reg(esp_efuse_block_t blk, unsigned int num_reg);

/**
 * @brief 写入efuse寄存器，检查编程位的重复编程。
 */
esp_err_t esp_efuse_utility_write_reg(unsigned int num_reg, esp_efuse_block_t efuse_block, uint32_t reg_to_write);

/* @brief 重置efuse写入寄存器
 *
 * Efuse写入寄存器被写入零，以否定此处已暂存的任何更改。
 */
void esp_efuse_utility_reset(void);

/**
 * @brief   用efuse_Rdata中的值填充virt_blocks数组。
 */
void esp_efuse_utility_update_virt_blocks(void);

/**
 * @brief   打印所有寄存器的efuse值。
 */
void esp_efuse_utility_debug_dump_blocks(void);

/**
 * @brief   擦除virt_blocks阵列。
 */
void esp_efuse_utility_erase_virt_blocks(void);

/**
 * @brief   应用coding_scheme写入寄存器。
 *
 * @return
 *         -ESP_OK:操作已成功完成。
 *         -ESP_ERR_CODING：数据的错误范围与编码方案不匹配。
 */
esp_err_t esp_efuse_utility_apply_new_coding_scheme(void);

/**
 * @brief   Efuse读取操作：将数据从物理Efuse复制到Efuse读取寄存器。
 */
void esp_efuse_utility_clear_program_registers(void);

#ifdef CONFIG_EFUSE_VIRTUAL_KEEP_IN_FLASH
/**
 * @brief   将efuse写入efuse闪存分区。
 *
 * 仅当设置了CONFIG_EFUSE_VIRTUAL_KEEP_IN_FLASH时使用。
 */
void esp_efuse_utility_write_efuses_to_flash(void);

/**
 * @brief   从efuse闪存分区加载efuse。
 *
 * 仅当设置了CONFIG_EFUSE_VIRTUAL_KEEP_IN_FLASH时使用。
 */
bool esp_efuse_utility_load_efuses_from_flash(void);

/**
 * @brief   擦除efuse闪存分区。
 *
 * 仅当设置了CONFIG_EFUSE_VIRTUAL_KEEP_IN_FLASH时使用。
 */
void esp_efuse_utility_erase_efuses_in_flash(void);
#endif

/**
 * @brief 返回特定efuse块的第一个读取寄存器的地址
 *
 * @param[in] block 要查找的efuse块索引
 *
 * @return 块中第一个字的数字读寄存器地址。
 */
uint32_t esp_efuse_utility_get_read_register_address(esp_efuse_block_t block);

#ifdef __cplusplus
}
#endif

