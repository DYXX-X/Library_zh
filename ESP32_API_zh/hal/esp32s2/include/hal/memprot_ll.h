// 版权所有2020 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#pragma once

#include <stdbool.h>
#include "soc/memprot_defs.h"
#include "hal/memprot_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * ===========================================================================IRAM0公共========================================================================================
 */
static inline void memprot_ll_iram0_clear_intr(void)
{
    DPORT_SET_PERI_REG_MASK(DPORT_PMS_PRO_IRAM0_4_REG, DPORT_PMS_PRO_IRAM0_ILG_CLR);
    DPORT_CLEAR_PERI_REG_MASK(DPORT_PMS_PRO_IRAM0_4_REG, DPORT_PMS_PRO_IRAM0_ILG_CLR);
}

static inline uint32_t memprot_ll_iram0_get_intr_source_num(void)
{
    return ETS_PMS_PRO_IRAM0_ILG_INTR_SOURCE;
}

static inline void memprot_ll_iram0_intr_ena(bool enable)
{
    if (enable) {
        DPORT_SET_PERI_REG_MASK(DPORT_PMS_PRO_IRAM0_4_REG, DPORT_PMS_PRO_IRAM0_ILG_EN);
    } else {
        DPORT_CLEAR_PERI_REG_MASK(DPORT_PMS_PRO_IRAM0_4_REG, DPORT_PMS_PRO_IRAM0_ILG_EN);
    }
}

static inline uint32_t memprot_ll_iram0_get_conf_reg(void)
{
    return DPORT_READ_PERI_REG(DPORT_PMS_PRO_IRAM0_4_REG);
}

static inline uint32_t memprot_ll_iram0_get_fault_reg(void)
{
    return DPORT_READ_PERI_REG(DPORT_PMS_PRO_IRAM0_5_REG);
}

static inline void memprot_ll_iram0_get_fault_op_type(uint32_t *op_type, uint32_t *op_subtype)
{
    uint32_t status_bits = memprot_ll_iram0_get_fault_reg();
    *op_type = (uint32_t)status_bits & IRAM0_INTR_ST_OP_RW_BIT;
    *op_subtype = (uint32_t)status_bits & IRAM0_INTR_ST_OP_TYPE_BIT;
}

static inline bool memprot_ll_iram0_is_assoc_intr(void)
{
    return DPORT_GET_PERI_REG_MASK(DPORT_PMS_PRO_IRAM0_4_REG, DPORT_PMS_PRO_IRAM0_ILG_INTR) > 0;
}

static inline uint32_t memprot_ll_iram0_get_intr_ena_bit(void)
{
    return DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_4_REG, DPORT_PMS_PRO_IRAM0_ILG_EN);
}

static inline uint32_t memprot_ll_iram0_get_intr_on_bit(void)
{
    return DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_4_REG, DPORT_PMS_PRO_IRAM0_ILG_INTR);
}

static inline uint32_t memprot_ll_iram0_get_intr_clr_bit(void)
{
    return DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_4_REG, DPORT_PMS_PRO_IRAM0_ILG_CLR);
}

//CPU重新启动时自动重置
static inline void memprot_ll_iram0_set_lock(void)
{
    DPORT_WRITE_PERI_REG( DPORT_PMS_PRO_IRAM0_0_REG, DPORT_PMS_PRO_IRAM0_LOCK);
}

static inline uint32_t memprot_ll_iram0_get_lock_reg(void)
{
    return DPORT_READ_PERI_REG(DPORT_PMS_PRO_IRAM0_0_REG);
}

static inline uint32_t memprot_ll_iram0_get_lock_bit(void)
{
    return DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_0_REG, DPORT_PMS_PRO_IRAM0_LOCK);
}

/**
 * ======================================================================================== === IRAM0 SRAM ========================================================================================
 */
static inline intptr_t memprot_ll_iram0_sram_get_fault_address(void)
{
    uint32_t status_bits = memprot_ll_iram0_get_fault_reg();
    return (intptr_t)((status_bits & IRAM0_INTR_ST_FAULTADDR_M) | IRAM0_SRAM_INTR_ST_FAULTADDR_HI);
}

static inline bool memprot_ll_iram0_sram_is_intr_mine(void)
{
    if (memprot_ll_iram0_is_assoc_intr()) {
        uint32_t faulting_address = (uint32_t)memprot_ll_iram0_sram_get_fault_address();
        return faulting_address >= IRAM0_SRAM_ADDRESS_LOW && faulting_address <= IRAM0_SRAM_ADDRESS_HIGH;
    }
    return false;
}

//块0-3
static inline bool memprot_ll_iram0_sram_set_uni_block_perm(uint32_t block, bool write_perm, bool read_perm, bool exec_perm)
{
    uint32_t write_bit, read_bit, exec_bit;

    switch (block) {
    case IRAM0_SRAM_UNI_BLOCK_0:
        write_bit = DPORT_PMS_PRO_IRAM0_SRAM_0_W;
        read_bit = DPORT_PMS_PRO_IRAM0_SRAM_0_R;
        exec_bit = DPORT_PMS_PRO_IRAM0_SRAM_0_F;
        break;
    case IRAM0_SRAM_UNI_BLOCK_1:
        write_bit = DPORT_PMS_PRO_IRAM0_SRAM_1_W;
        read_bit = DPORT_PMS_PRO_IRAM0_SRAM_1_R;
        exec_bit = DPORT_PMS_PRO_IRAM0_SRAM_1_F;
        break;
    case IRAM0_SRAM_UNI_BLOCK_2:
        write_bit = DPORT_PMS_PRO_IRAM0_SRAM_2_W;
        read_bit = DPORT_PMS_PRO_IRAM0_SRAM_2_R;
        exec_bit = DPORT_PMS_PRO_IRAM0_SRAM_2_F;
        break;
    case IRAM0_SRAM_UNI_BLOCK_3:
        write_bit = DPORT_PMS_PRO_IRAM0_SRAM_3_W;
        read_bit = DPORT_PMS_PRO_IRAM0_SRAM_3_R;
        exec_bit = DPORT_PMS_PRO_IRAM0_SRAM_3_F;
        break;
    default:
        return false;
    }

    if (write_perm) {
        DPORT_SET_PERI_REG_MASK(DPORT_PMS_PRO_IRAM0_1_REG, write_bit);
    } else {
        DPORT_CLEAR_PERI_REG_MASK(DPORT_PMS_PRO_IRAM0_1_REG, write_bit);
    }

    if (read_perm) {
        DPORT_SET_PERI_REG_MASK(DPORT_PMS_PRO_IRAM0_1_REG, read_bit);
    } else {
        DPORT_CLEAR_PERI_REG_MASK(DPORT_PMS_PRO_IRAM0_1_REG, read_bit);
    }

    if (exec_perm) {
        DPORT_SET_PERI_REG_MASK(DPORT_PMS_PRO_IRAM0_1_REG, exec_bit);
    } else {
        DPORT_CLEAR_PERI_REG_MASK(DPORT_PMS_PRO_IRAM0_1_REG, exec_bit);
    }

    return true;
}

static inline bool memprot_ll_iram0_sram_get_uni_block_read_bit(uint32_t block, uint32_t *read_bit)
{
    switch (block) {
    case IRAM0_SRAM_UNI_BLOCK_0:
        *read_bit = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_1_REG, DPORT_PMS_PRO_IRAM0_SRAM_0_R);
        break;
    case IRAM0_SRAM_UNI_BLOCK_1:
        *read_bit = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_1_REG, DPORT_PMS_PRO_IRAM0_SRAM_1_R);
        break;
    case IRAM0_SRAM_UNI_BLOCK_2:
        *read_bit = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_1_REG, DPORT_PMS_PRO_IRAM0_SRAM_2_R);
        break;
    case IRAM0_SRAM_UNI_BLOCK_3:
        *read_bit = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_1_REG, DPORT_PMS_PRO_IRAM0_SRAM_3_R);
        break;
    default:
        return false;
    }

    return true;
}

static inline bool memprot_ll_iram0_sram_get_uni_block_write_bit(uint32_t block, uint32_t *write_bit)
{
    switch (block) {
    case IRAM0_SRAM_UNI_BLOCK_0:
        *write_bit = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_1_REG, DPORT_PMS_PRO_IRAM0_SRAM_0_W);
        break;
    case IRAM0_SRAM_UNI_BLOCK_1:
        *write_bit = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_1_REG, DPORT_PMS_PRO_IRAM0_SRAM_1_W);
        break;
    case IRAM0_SRAM_UNI_BLOCK_2:
        *write_bit = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_1_REG, DPORT_PMS_PRO_IRAM0_SRAM_2_W);
        break;
    case IRAM0_SRAM_UNI_BLOCK_3:
        *write_bit = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_1_REG, DPORT_PMS_PRO_IRAM0_SRAM_3_W);
        break;
    default:
        return false;
    }

    return true;
}

static inline bool memprot_ll_iram0_sram_get_uni_block_exec_bit(uint32_t block, uint32_t *exec_bit)
{
    switch (block) {
    case IRAM0_SRAM_UNI_BLOCK_0:
        *exec_bit = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_1_REG, DPORT_PMS_PRO_IRAM0_SRAM_0_F);
        break;
    case IRAM0_SRAM_UNI_BLOCK_1:
        *exec_bit = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_1_REG, DPORT_PMS_PRO_IRAM0_SRAM_1_F);
        break;
    case IRAM0_SRAM_UNI_BLOCK_2:
        *exec_bit = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_1_REG, DPORT_PMS_PRO_IRAM0_SRAM_2_F);
        break;
    case IRAM0_SRAM_UNI_BLOCK_3:
        *exec_bit = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_1_REG, DPORT_PMS_PRO_IRAM0_SRAM_3_F);
        break;
    default:
        return false;
    }

    return true;
}

static inline bool memprot_ll_iram0_sram_get_uni_block_sgnf_bits(uint32_t block, uint32_t *write_bit, uint32_t *read_bit, uint32_t *exec_bit)
{
    switch (block) {
    case IRAM0_SRAM_UNI_BLOCK_0:
        *write_bit = DPORT_PMS_PRO_IRAM0_SRAM_0_W;
        *read_bit = DPORT_PMS_PRO_IRAM0_SRAM_0_R;
        *exec_bit = DPORT_PMS_PRO_IRAM0_SRAM_0_F;
        break;
    case IRAM0_SRAM_UNI_BLOCK_1:
        *write_bit = DPORT_PMS_PRO_IRAM0_SRAM_1_W;
        *read_bit = DPORT_PMS_PRO_IRAM0_SRAM_1_R;
        *exec_bit = DPORT_PMS_PRO_IRAM0_SRAM_1_F;
        break;
    case IRAM0_SRAM_UNI_BLOCK_2:
        *write_bit = DPORT_PMS_PRO_IRAM0_SRAM_2_W;
        *read_bit = DPORT_PMS_PRO_IRAM0_SRAM_2_R;
        *exec_bit = DPORT_PMS_PRO_IRAM0_SRAM_2_F;
        break;
    case IRAM0_SRAM_UNI_BLOCK_3:
        *write_bit = DPORT_PMS_PRO_IRAM0_SRAM_3_W;
        *read_bit = DPORT_PMS_PRO_IRAM0_SRAM_3_R;
        *exec_bit = DPORT_PMS_PRO_IRAM0_SRAM_3_F;
        break;
    default:
        return false;
    }

    return true;
}

static inline uint32_t memprot_ll_iram0_sram_get_perm_uni_reg(void)
{
    return DPORT_READ_PERI_REG(DPORT_PMS_PRO_IRAM0_1_REG);
}

static inline uint32_t memprot_ll_iram0_sram_get_perm_split_reg(void)
{
    return DPORT_READ_PERI_REG(DPORT_PMS_PRO_IRAM0_2_REG);
}

static inline memprot_ll_err_t memprot_ll_iram0_sram_set_prot(uint32_t *split_addr, bool lw, bool lr, bool lx, bool hw, bool hr, bool hx)
{
    uint32_t addr = (uint32_t)split_addr;

    //健全性检查：统一管理区域上方需要拆分地址&32位对齐
    if (addr > IRAM0_SRAM_SPL_BLOCK_HIGH) {
        return MEMP_LL_ERR_SPLIT_ADDR_INVALID;
    }
    if (addr % 0x4 != 0) {
        return MEMP_LL_ERR_SPLIT_ADDR_UNALIGNED;
    }

    //查找可能的拆分。低区域块中的地址
    int uni_blocks_low = -1;
    if (addr >= IRAM0_SRAM_UNI_BLOCK_0_LOW) {
        uni_blocks_low++;
    }
    if (addr >= IRAM0_SRAM_UNI_BLOCK_1_LOW) {
        uni_blocks_low++;
    }
    if (addr >= IRAM0_SRAM_UNI_BLOCK_2_LOW) {
        uni_blocks_low++;
    }
    if (addr >= IRAM0_SRAM_UNI_BLOCK_3_LOW) {
        uni_blocks_low++;
    }

    //每个块的统一管理设置（位W/R/X:[11:9]bl3，[8:6]bl2，[5:3]bl1，[2:0]bl0）
    uint32_t write_bit, read_bit, exec_bit;
    uint32_t uni_block_perm = 0;

    for (int x = 0; x < IRAM0_SRAM_TOTAL_UNI_BLOCKS; x++) {
        if (!memprot_ll_iram0_sram_get_uni_block_sgnf_bits(x, &write_bit, &read_bit, &exec_bit)) {
            return MEMP_LL_ERR_UNI_BLOCK_INVALID;
        }
        if (x <= uni_blocks_low) {
            if (lw) {
                uni_block_perm |= write_bit;
            }
            if (lr) {
                uni_block_perm |= read_bit;
            }
            if (lx) {
                uni_block_perm |= exec_bit;
            }
        } else {
            if (hw) {
                uni_block_perm |= write_bit;
            }
            if (hr) {
                uni_block_perm |= read_bit;
            }
            if (hx) {
                uni_block_perm |= exec_bit;
            }
        }
    }

    //如果splt。ddr尚未设置，请执行所需的规范化，使addr可写入splt。mgmt cfg寄存器
    uint32_t reg_split_addr = 0;

    if (addr >= IRAM0_SRAM_SPL_BLOCK_LOW) {
        reg_split_addr = IRAM0_SRAM_ADDR_TO_CONF_REG(addr); //cfg寄存器-[16:0]
    }

    //准备高和低许可掩码（位：[22:20]高范围，[19:17]低范围）
    uint32_t permission_mask = 0;
    if (lw) {
        permission_mask |= DPORT_PMS_PRO_IRAM0_SRAM_4_L_W;
    }
    if (lr) {
        permission_mask |= DPORT_PMS_PRO_IRAM0_SRAM_4_L_R;
    }
    if (lx) {
        permission_mask |= DPORT_PMS_PRO_IRAM0_SRAM_4_L_F;
    }
    if (hw) {
        permission_mask |= DPORT_PMS_PRO_IRAM0_SRAM_4_H_W;
    }
    if (hr) {
        permission_mask |= DPORT_PMS_PRO_IRAM0_SRAM_4_H_R;
    }
    if (hx) {
        permission_mask |= DPORT_PMS_PRO_IRAM0_SRAM_4_H_F;
    }

    //写入IRAM SRAM uni&splt cfg。寄存器
    DPORT_WRITE_PERI_REG(DPORT_PMS_PRO_IRAM0_1_REG, uni_block_perm);
    DPORT_WRITE_PERI_REG(DPORT_PMS_PRO_IRAM0_2_REG, (uint32_t)(reg_split_addr | permission_mask));

    return MEMP_LL_OK;
}

static inline void memprot_ll_iram0_sram_get_split_sgnf_bits(bool *lw, bool *lr, bool *lx, bool *hw, bool *hr, bool *hx)
{
    *lw = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_2_REG, DPORT_PMS_PRO_IRAM0_SRAM_4_L_W);
    *lr = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_2_REG, DPORT_PMS_PRO_IRAM0_SRAM_4_L_R);
    *lx = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_2_REG, DPORT_PMS_PRO_IRAM0_SRAM_4_L_F);
    *hw = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_2_REG, DPORT_PMS_PRO_IRAM0_SRAM_4_H_W);
    *hr = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_2_REG, DPORT_PMS_PRO_IRAM0_SRAM_4_H_R);
    *hx = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_2_REG, DPORT_PMS_PRO_IRAM0_SRAM_4_H_F);
}

static inline void memprot_ll_iram0_sram_set_read_perm(bool lr, bool hr)
{
    DPORT_REG_SET_FIELD(DPORT_PMS_PRO_IRAM0_2_REG, DPORT_PMS_PRO_IRAM0_SRAM_4_L_R, lr ? 1 : 0);
    DPORT_REG_SET_FIELD(DPORT_PMS_PRO_IRAM0_2_REG, DPORT_PMS_PRO_IRAM0_SRAM_4_H_R, hr ? 1 : 0);
}

static inline void memprot_ll_iram0_sram_set_write_perm(bool lw, bool hw)
{
    DPORT_REG_SET_FIELD(DPORT_PMS_PRO_IRAM0_2_REG, DPORT_PMS_PRO_IRAM0_SRAM_4_L_W, lw ? 1 : 0);
    DPORT_REG_SET_FIELD(DPORT_PMS_PRO_IRAM0_2_REG, DPORT_PMS_PRO_IRAM0_SRAM_4_H_W, hw ? 1 : 0);
}

static inline void memprot_ll_iram0_sram_set_exec_perm(bool lx, bool hx)
{
    DPORT_REG_SET_FIELD(DPORT_PMS_PRO_IRAM0_2_REG, DPORT_PMS_PRO_IRAM0_SRAM_4_L_F, lx ? 1 : 0);
    DPORT_REG_SET_FIELD(DPORT_PMS_PRO_IRAM0_2_REG, DPORT_PMS_PRO_IRAM0_SRAM_4_H_F, hx ? 1 : 0);
}


/**
 * ======================================================================================== === IRAM0 RTC FAST ========================================================================================
 */
static inline intptr_t memprot_ll_iram0_rtcfast_get_fault_address(void)
{
    uint32_t status_bits = memprot_ll_iram0_get_fault_reg();
    return (intptr_t)((status_bits & IRAM0_INTR_ST_FAULTADDR_M) | IRAM0_RTCFAST_INTR_ST_FAULTADDR_HI);
}

static inline bool memprot_ll_iram0_rtcfast_is_intr_mine(void)
{
    if (memprot_ll_iram0_is_assoc_intr()) {
        uint32_t faulting_address = (uint32_t)memprot_ll_iram0_rtcfast_get_fault_address();
        return faulting_address >= IRAM0_RTCFAST_ADDRESS_LOW && faulting_address <= IRAM0_RTCFAST_ADDRESS_HIGH;
    }
    return false;
}

static inline uint32_t memprot_ll_iram0_rtcfast_get_perm_split_reg(void)
{
    return DPORT_READ_PERI_REG(DPORT_PMS_PRO_IRAM0_3_REG);
}

static inline memprot_ll_err_t memprot_ll_iram0_rtcfast_set_prot(uint32_t *split_addr, bool lw, bool lr, bool lx, bool hw, bool hr, bool hx)
{
    uint32_t addr = (uint32_t)split_addr;

    //32位对齐
    if (addr < IRAM0_RTCFAST_ADDRESS_LOW || addr > IRAM0_RTCFAST_ADDRESS_HIGH) {
        return MEMP_LL_ERR_SPLIT_ADDR_INVALID;
    }
    if (addr % 0x4 != 0) {
        return MEMP_LL_ERR_SPLIT_ADDR_UNALIGNED;
    }

    //conf注册[10:0]
    uint32_t reg_split_addr = IRAM0_RTCFAST_ADDR_TO_CONF_REG(addr);

    //准备高和低许可掩码（位：[16:14]高范围，[13:11]低范围）
    uint32_t permission_mask = 0;
    if (lw) {
        permission_mask |= DPORT_PMS_PRO_IRAM0_RTCFAST_L_W;
    }
    if (lr) {
        permission_mask |= DPORT_PMS_PRO_IRAM0_RTCFAST_L_R;
    }
    if (lx) {
        permission_mask |= DPORT_PMS_PRO_IRAM0_RTCFAST_L_F;
    }
    if (hw) {
        permission_mask |= DPORT_PMS_PRO_IRAM0_RTCFAST_H_W;
    }
    if (hr) {
        permission_mask |= DPORT_PMS_PRO_IRAM0_RTCFAST_H_R;
    }
    if (hx) {
        permission_mask |= DPORT_PMS_PRO_IRAM0_RTCFAST_H_F;
    }

    //写入IRAM0 RTCFAST cfg寄存器
    DPORT_WRITE_PERI_REG(DPORT_PMS_PRO_IRAM0_3_REG, reg_split_addr | permission_mask);

    return MEMP_LL_OK;
}

static inline void memprot_ll_iram0_rtcfast_get_split_sgnf_bits(bool *lw, bool *lr, bool *lx, bool *hw, bool *hr, bool *hx)
{
    *lw = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_3_REG, DPORT_PMS_PRO_IRAM0_RTCFAST_L_W);
    *lr = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_3_REG, DPORT_PMS_PRO_IRAM0_RTCFAST_L_R);
    *lx = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_3_REG, DPORT_PMS_PRO_IRAM0_RTCFAST_L_F);
    *hw = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_3_REG, DPORT_PMS_PRO_IRAM0_RTCFAST_H_W);
    *hr = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_3_REG, DPORT_PMS_PRO_IRAM0_RTCFAST_H_R);
    *hx = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_3_REG, DPORT_PMS_PRO_IRAM0_RTCFAST_H_F);
}

static inline void memprot_ll_iram0_rtcfast_set_read_perm(bool lr, bool hr)
{
    DPORT_REG_SET_FIELD(DPORT_PMS_PRO_IRAM0_3_REG, DPORT_PMS_PRO_IRAM0_RTCFAST_L_R, lr ? 1 : 0);
    DPORT_REG_SET_FIELD(DPORT_PMS_PRO_IRAM0_3_REG, DPORT_PMS_PRO_IRAM0_RTCFAST_H_R, hr ? 1 : 0);
}

static inline void memprot_ll_iram0_rtcfast_set_write_perm(bool lw, bool hw)
{
    DPORT_REG_SET_FIELD(DPORT_PMS_PRO_IRAM0_3_REG, DPORT_PMS_PRO_IRAM0_RTCFAST_L_W, lw ? 1 : 0);
    DPORT_REG_SET_FIELD(DPORT_PMS_PRO_IRAM0_3_REG, DPORT_PMS_PRO_IRAM0_RTCFAST_H_W, hw ? 1 : 0);
}

static inline void memprot_ll_iram0_rtcfast_set_exec_perm(bool lx, bool hx)
{
    DPORT_REG_SET_FIELD(DPORT_PMS_PRO_IRAM0_3_REG, DPORT_PMS_PRO_IRAM0_RTCFAST_L_F, lx ? 1 : 0);
    DPORT_REG_SET_FIELD(DPORT_PMS_PRO_IRAM0_3_REG, DPORT_PMS_PRO_IRAM0_RTCFAST_H_F, hx ? 1 : 0);
}


/**
 * ===========================================================================DRAM0公用========================================================================================
 */
static inline uint32_t memprot_ll_dram0_get_intr_source_num(void)
{
    return ETS_PMS_PRO_DRAM0_ILG_INTR_SOURCE;
}

static inline void memprot_ll_dram0_intr_ena(bool enable)
{
    if (enable) {
        DPORT_SET_PERI_REG_MASK(DPORT_PMS_PRO_DRAM0_3_REG, DPORT_PMS_PRO_DRAM0_ILG_EN);
    } else {
        DPORT_CLEAR_PERI_REG_MASK(DPORT_PMS_PRO_DRAM0_3_REG, DPORT_PMS_PRO_DRAM0_ILG_EN);
    }
}

static inline bool memprot_ll_dram0_is_assoc_intr(void)
{
    return DPORT_GET_PERI_REG_MASK(DPORT_PMS_PRO_DRAM0_3_REG, DPORT_PMS_PRO_DRAM0_ILG_INTR) > 0;
}

static inline void memprot_ll_dram0_clear_intr(void)
{
    DPORT_SET_PERI_REG_MASK(DPORT_PMS_PRO_DRAM0_3_REG, DPORT_PMS_PRO_DRAM0_ILG_CLR);
    DPORT_CLEAR_PERI_REG_MASK(DPORT_PMS_PRO_DRAM0_3_REG, DPORT_PMS_PRO_DRAM0_ILG_CLR);
}

static inline uint32_t memprot_ll_dram0_get_intr_ena_bit(void)
{
    return DPORT_REG_GET_FIELD(DPORT_PMS_PRO_DRAM0_3_REG, DPORT_PMS_PRO_DRAM0_ILG_EN);
}

static inline uint32_t memprot_ll_dram0_get_intr_on_bit(void)
{
    return DPORT_REG_GET_FIELD(DPORT_PMS_PRO_DRAM0_3_REG, DPORT_PMS_PRO_DRAM0_ILG_INTR);
}

static inline uint32_t memprot_ll_dram0_get_intr_clr_bit(void)
{
    return DPORT_REG_GET_FIELD(DPORT_PMS_PRO_DRAM0_3_REG, DPORT_PMS_PRO_DRAM0_ILG_CLR);
}

//CPU重新启动时锁自动复位
static inline void memprot_ll_dram0_set_lock(void)
{
    DPORT_WRITE_PERI_REG(DPORT_PMS_PRO_DRAM0_0_REG, DPORT_PMS_PRO_DRAM0_LOCK);
}

static inline uint32_t memprot_ll_dram0_get_lock_reg(void)
{
    return DPORT_READ_PERI_REG(DPORT_PMS_PRO_DRAM0_0_REG);
}

static inline uint32_t memprot_ll_dram0_get_lock_bit(void)
{
    return DPORT_REG_GET_FIELD(DPORT_PMS_PRO_DRAM0_0_REG, DPORT_PMS_PRO_DRAM0_LOCK);
}

static inline uint32_t memprot_ll_dram0_get_conf_reg(void)
{
    return DPORT_READ_PERI_REG(DPORT_PMS_PRO_DRAM0_3_REG);
}

static inline uint32_t memprot_ll_dram0_get_fault_reg(void)
{
    return DPORT_READ_PERI_REG(DPORT_PMS_PRO_DRAM0_4_REG);
}

static inline void memprot_ll_dram0_get_fault_op_type(uint32_t *op_type, uint32_t *op_subtype)
{
    uint32_t status_bits = memprot_ll_dram0_get_fault_reg();
    *op_type = status_bits & DRAM0_INTR_ST_OP_RW_BIT;
    *op_subtype = status_bits & DRAM0_INTR_ST_OP_ATOMIC_BIT;
}

/**
 * ======================================================================================== === DRAM0 SRAM ========================================================================================
 */
static inline intptr_t memprot_ll_dram0_sram_get_fault_address(void)
{
    uint32_t status_bits = memprot_ll_dram0_get_fault_reg();
    return (intptr_t)(((status_bits & DRAM0_INTR_ST_FAULTADDR_M) >> DRAM0_INTR_ST_FAULTADDR_S) | DRAM0_SRAM_INTR_ST_FAULTADDR_HI);
}

static inline bool memprot_ll_dram0_sram_is_intr_mine(void)
{
    if (memprot_ll_dram0_is_assoc_intr()) {
        uint32_t faulting_address = (uint32_t)memprot_ll_dram0_sram_get_fault_address();
        return faulting_address >= DRAM0_SRAM_ADDRESS_LOW && faulting_address <= DRAM0_SRAM_ADDRESS_HIGH;
    }
    return false;
}

static inline bool memprot_ll_dram0_sram_get_uni_block_sgnf_bits(uint32_t block, uint32_t *write_bit, uint32_t *read_bit)
{
    switch (block) {
    case DRAM0_SRAM_UNI_BLOCK_0:
        *write_bit = DPORT_PMS_PRO_DRAM0_SRAM_0_W;
        *read_bit = DPORT_PMS_PRO_DRAM0_SRAM_0_R;
        break;
    case DRAM0_SRAM_UNI_BLOCK_1:
        *write_bit = DPORT_PMS_PRO_DRAM0_SRAM_1_W;
        *read_bit = DPORT_PMS_PRO_DRAM0_SRAM_1_R;
        break;
    case DRAM0_SRAM_UNI_BLOCK_2:
        *write_bit = DPORT_PMS_PRO_DRAM0_SRAM_2_W;
        *read_bit = DPORT_PMS_PRO_DRAM0_SRAM_2_R;
        break;
    case DRAM0_SRAM_UNI_BLOCK_3:
        *write_bit = DPORT_PMS_PRO_DRAM0_SRAM_3_W;
        *read_bit = DPORT_PMS_PRO_DRAM0_SRAM_3_R;
        break;
    default:
        return false;
    }

    return true;
}

static inline memprot_ll_err_t memprot_ll_dram0_sram_set_uni_block_perm(uint32_t block, bool write_perm, bool read_perm)
{
    //获取conf.register中特定于块的WR标志偏移量
    uint32_t write_bit_offset, read_bit_offset;
    if (!memprot_ll_dram0_sram_get_uni_block_sgnf_bits(block, &write_bit_offset, &read_bit_offset)) {
        return MEMP_LL_ERR_UNI_BLOCK_INVALID;
    }

    //设置/重置所需标志
    if (write_perm) {
        DPORT_SET_PERI_REG_MASK(DPORT_PMS_PRO_DRAM0_1_REG, write_bit_offset);
    } else {
        DPORT_CLEAR_PERI_REG_MASK(DPORT_PMS_PRO_DRAM0_1_REG, write_bit_offset);
    }

    if (read_perm) {
        DPORT_SET_PERI_REG_MASK(DPORT_PMS_PRO_DRAM0_1_REG, read_bit_offset);
    } else {
        DPORT_CLEAR_PERI_REG_MASK(DPORT_PMS_PRO_DRAM0_1_REG, read_bit_offset);
    }

    return MEMP_LL_OK;
}

static inline bool memprot_ll_dram0_sram_get_uni_block_read_bit(uint32_t block, uint32_t *read_bit)
{
    switch (block) {
    case DRAM0_SRAM_UNI_BLOCK_0:
        *read_bit = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_DRAM0_1_REG, DPORT_PMS_PRO_DRAM0_SRAM_0_R);
        break;
    case DRAM0_SRAM_UNI_BLOCK_1:
        *read_bit = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_DRAM0_1_REG, DPORT_PMS_PRO_DRAM0_SRAM_1_R);
        break;
    case DRAM0_SRAM_UNI_BLOCK_2:
        *read_bit = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_DRAM0_1_REG, DPORT_PMS_PRO_DRAM0_SRAM_2_R);
        break;
    case DRAM0_SRAM_UNI_BLOCK_3:
        *read_bit = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_DRAM0_1_REG, DPORT_PMS_PRO_DRAM0_SRAM_3_R);
        break;
    default:
        return false;
    }

    return true;
}

static inline bool memprot_ll_dram0_sram_get_uni_block_write_bit(uint32_t block, uint32_t *write_bit)
{
    switch (block) {
    case DRAM0_SRAM_UNI_BLOCK_0:
        *write_bit = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_DRAM0_1_REG, DPORT_PMS_PRO_DRAM0_SRAM_0_W);
        break;
    case DRAM0_SRAM_UNI_BLOCK_1:
        *write_bit = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_DRAM0_1_REG, DPORT_PMS_PRO_DRAM0_SRAM_1_W);
        break;
    case DRAM0_SRAM_UNI_BLOCK_2:
        *write_bit = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_DRAM0_1_REG, DPORT_PMS_PRO_DRAM0_SRAM_2_W);
        break;
    case DRAM0_SRAM_UNI_BLOCK_3:
        *write_bit = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_DRAM0_1_REG, DPORT_PMS_PRO_DRAM0_SRAM_3_W);
        break;
    default:
        return false;
    }

    return true;
}

//DRAM0具有在1个寄存器中配置的统一块和分割地址
static inline uint32_t memprot_ll_dram0_sram_get_perm_reg(void)
{
    return DPORT_READ_PERI_REG(DPORT_PMS_PRO_DRAM0_1_REG);
}

static inline memprot_ll_err_t memprot_ll_dram0_sram_set_prot(uint32_t *split_addr, bool lw, bool lr, bool hw, bool hr)
{
    uint32_t addr = (uint32_t)split_addr;

    //LD脚本提供的低边界检查。请参见memprot_l_iram0_sram_set_prot（）中的注释
    if (addr > DRAM0_SRAM_SPL_BLOCK_HIGH) {
        return MEMP_LL_ERR_SPLIT_ADDR_INVALID;
    }
    if (addr % 0x4 != 0) {
        return MEMP_LL_ERR_SPLIT_ADDR_UNALIGNED;
    }

    //设置低区域
    int uni_blocks_low = -1;
    if (addr >= DRAM0_SRAM_UNI_BLOCK_0_LOW) {
        uni_blocks_low++;
    }
    if (addr >= DRAM0_SRAM_UNI_BLOCK_1_LOW) {
        uni_blocks_low++;
    }
    if (addr >= DRAM0_SRAM_UNI_BLOCK_2_LOW) {
        uni_blocks_low++;
    }
    if (addr >= DRAM0_SRAM_UNI_BLOCK_3_LOW) {
        uni_blocks_low++;
    }

    //设置统一管理区域
    uint32_t write_bit, read_bit, uni_block_perm = 0;
    for (int x = 0; x < DRAM0_SRAM_TOTAL_UNI_BLOCKS; x++) {
        if (!memprot_ll_dram0_sram_get_uni_block_sgnf_bits(x, &write_bit, &read_bit)) {
            return MEMP_LL_ERR_UNI_BLOCK_INVALID;
        }
        if (x <= uni_blocks_low) {
            if (lw) {
                uni_block_perm |= write_bit;
            }
            if (lr) {
                uni_block_perm |= read_bit;
            }
        } else {
            if (hw) {
                uni_block_perm |= write_bit;
            }
            if (hr) {
                uni_block_perm |= read_bit;
            }
        }
    }

    //配置文件[24:8]
    uint32_t reg_split_addr = DRAM0_SRAM_ADDR_TO_CONF_REG(addr);

    //准备高权限和低权限掩码
    uint32_t permission_mask = 0;
    if (lw) {
        permission_mask |= DPORT_PMS_PRO_DRAM0_SRAM_4_L_W;
    }
    if (lr) {
        permission_mask |= DPORT_PMS_PRO_DRAM0_SRAM_4_L_R;
    }
    if (hw) {
        permission_mask |= DPORT_PMS_PRO_DRAM0_SRAM_4_H_W;
    }
    if (hr) {
        permission_mask |= DPORT_PMS_PRO_DRAM0_SRAM_4_H_R;
    }

    //写DRAM0 SRAM cfg寄存器
    DPORT_WRITE_PERI_REG(DPORT_PMS_PRO_DRAM0_1_REG, reg_split_addr | permission_mask | uni_block_perm);

    return MEMP_LL_OK;
}

static inline void memprot_ll_dram0_sram_get_split_sgnf_bits(bool *lw, bool *lr, bool *hw, bool *hr)
{
    *lw = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_DRAM0_1_REG, DPORT_PMS_PRO_DRAM0_SRAM_4_L_W);
    *lr = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_DRAM0_1_REG, DPORT_PMS_PRO_DRAM0_SRAM_4_L_R);
    *hw = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_DRAM0_1_REG, DPORT_PMS_PRO_DRAM0_SRAM_4_H_W);
    *hr = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_DRAM0_1_REG, DPORT_PMS_PRO_DRAM0_SRAM_4_H_R);
}

static inline void memprot_ll_dram0_sram_set_read_perm(bool lr, bool hr)
{
    DPORT_REG_SET_FIELD(DPORT_PMS_PRO_DRAM0_1_REG, DPORT_PMS_PRO_DRAM0_SRAM_4_L_R, lr ? 1 : 0);
    DPORT_REG_SET_FIELD(DPORT_PMS_PRO_DRAM0_1_REG, DPORT_PMS_PRO_DRAM0_SRAM_4_H_R, hr ? 1 : 0);
}

static inline void memprot_ll_dram0_sram_set_write_perm(bool lw, bool hw)
{
    DPORT_REG_SET_FIELD(DPORT_PMS_PRO_DRAM0_1_REG, DPORT_PMS_PRO_DRAM0_SRAM_4_L_W, lw ? 1 : 0);
    DPORT_REG_SET_FIELD(DPORT_PMS_PRO_DRAM0_1_REG, DPORT_PMS_PRO_DRAM0_SRAM_4_H_W, hw ? 1 : 0);
}


/**
 * ======================================================================================== === DRAM0 RTC FAST ========================================================================================
 */
static inline intptr_t memprot_ll_dram0_rtcfast_get_fault_address(void)
{
    uint32_t status_bits = memprot_ll_dram0_get_fault_reg();
    return (intptr_t)(((status_bits & DRAM0_INTR_ST_FAULTADDR_M) >> DRAM0_INTR_ST_FAULTADDR_S) | DRAM0_RTCFAST_INTR_ST_FAULTADDR_HI);
}

static inline bool memprot_ll_dram0_rtcfast_is_intr_mine(void)
{
    if (memprot_ll_dram0_is_assoc_intr()) {
        uint32_t faulting_address = (uint32_t)memprot_ll_dram0_rtcfast_get_fault_address();
        return faulting_address >= DRAM0_RTCFAST_ADDRESS_LOW && faulting_address <= DRAM0_RTCFAST_ADDRESS_HIGH;
    }
    return false;
}

static inline memprot_ll_err_t memprot_ll_dram0_rtcfast_set_prot(uint32_t *split_addr, bool lw, bool lr, bool hw, bool hr)
{
    uint32_t addr = (uint32_t)split_addr;

    //地址：32位对齐，在相应范围内
    if (addr < DRAM0_RTCFAST_ADDRESS_LOW || addr > DRAM0_RTCFAST_ADDRESS_HIGH) {
        return MEMP_LL_ERR_SPLIT_ADDR_INVALID;
    }
    if (addr % 0x4 != 0) {
        return MEMP_LL_ERR_SPLIT_ADDR_UNALIGNED;
    }

    //conf注册[10:0]
    uint32_t reg_split_addr = DRAM0_RTCFAST_ADDR_TO_CONF_REG(addr);

    //准备高权限和低权限掩码
    uint32_t permission_mask = 0;
    if (lw) {
        permission_mask |= DPORT_PMS_PRO_DRAM0_RTCFAST_L_W;
    }
    if (lr) {
        permission_mask |= DPORT_PMS_PRO_DRAM0_RTCFAST_L_R;
    }
    if (hw) {
        permission_mask |= DPORT_PMS_PRO_DRAM0_RTCFAST_H_W;
    }
    if (hr) {
        permission_mask |= DPORT_PMS_PRO_DRAM0_RTCFAST_H_R;
    }

    //写入DRAM0 RTC FAST cfg寄存器
    DPORT_WRITE_PERI_REG(DPORT_PMS_PRO_DRAM0_2_REG, reg_split_addr | permission_mask);

    return MEMP_LL_OK;
}

static inline void memprot_ll_dram0_rtcfast_get_split_sgnf_bits(bool *lw, bool *lr, bool *hw, bool *hr)
{
    *lw = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_DRAM0_2_REG, DPORT_PMS_PRO_DRAM0_RTCFAST_L_W);
    *lr = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_DRAM0_2_REG, DPORT_PMS_PRO_DRAM0_RTCFAST_L_R);
    *hw = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_DRAM0_2_REG, DPORT_PMS_PRO_DRAM0_RTCFAST_H_W);
    *hr = DPORT_REG_GET_FIELD(DPORT_PMS_PRO_DRAM0_2_REG, DPORT_PMS_PRO_DRAM0_RTCFAST_H_R);
}

static inline uint32_t memprot_ll_dram0_rtcfast_get_perm_split_reg(void)
{
    return DPORT_READ_PERI_REG(DPORT_PMS_PRO_DRAM0_2_REG);
}

static inline void memprot_ll_dram0_rtcfast_set_read_perm(bool lr, bool hr)
{
    DPORT_REG_SET_FIELD(DPORT_PMS_PRO_DRAM0_2_REG, DPORT_PMS_PRO_DRAM0_RTCFAST_L_R, lr ? 1 : 0);
    DPORT_REG_SET_FIELD(DPORT_PMS_PRO_DRAM0_2_REG, DPORT_PMS_PRO_DRAM0_RTCFAST_H_R, hr ? 1 : 0);
}

static inline void memprot_ll_dram0_rtcfast_set_write_perm(bool lw, bool hw)
{
    DPORT_REG_SET_FIELD(DPORT_PMS_PRO_DRAM0_2_REG, DPORT_PMS_PRO_DRAM0_RTCFAST_L_W, lw ? 1 : 0);
    DPORT_REG_SET_FIELD(DPORT_PMS_PRO_DRAM0_2_REG, DPORT_PMS_PRO_DRAM0_RTCFAST_H_W, hw ? 1 : 0);
}

#ifdef __cplusplus
}
#endif

