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

#include "hal/assert.h"

#ifdef __cplusplus
extern "C" {
#endif

// 尚未为esp32s3实现
#if 0
/**
 * === IRAM0 ====
 */

#define IRAM0_TOTAL_UNI_BLOCKS          4
#define IRAM0_UNI_BLOCK_0               0
#define IRAM0_UNI_BLOCK_1               1
#define IRAM0_UNI_BLOCK_2               2
#define IRAM0_UNI_BLOCK_3               3

#define IRAM0_SPL_BLOCK_BASE            0x40000000

//统一管理（SRAM块0-3）
#define IRAM0_UNI_BLOCK_0_LOW           0x40020000
#define IRAM0_UNI_BLOCK_0_HIGH          0x40021FFF
#define IRAM0_UNI_BLOCK_1_LOW           0x40022000
#define IRAM0_UNI_BLOCK_1_HIGH          0x40023FFF
#define IRAM0_UNI_BLOCK_2_LOW           0x40024000
#define IRAM0_UNI_BLOCK_2_HIGH          0x40025FFF
#define IRAM0_UNI_BLOCK_3_LOW           0x40026000
#define IRAM0_UNI_BLOCK_3_HIGH          0x40027FFF

//分割管理（SRAM块4-21）
#define IRAM0_SPL_BLOCK_LOW             0x40028000 //区块4低
#define IRAM0_SPL_BLOCK_HIGH            0x4006FFFF //第21区偏高
#define IRAM0_SPLTADDR_MIN              0x40030000 //块6低-最小拆分地址

//IRAM0中断状态位掩码
#define IRAM0_INTR_ST_FAULTADDR_M       0x003FFFFC  //（reg中的位21:6，以及真实地址）
#define IRAM0_INTR_ST_FAULTADDR_HI      0x40000000  //（错误地址的高非重要位31:22-常量）
#define IRAM0_INTR_ST_OP_TYPE_BIT       BIT(1)      //指令：0，数据：1
#define IRAM0_INTR_ST_OP_RW_BIT         BIT(0)      //读取：0，写入：1


static inline uint32_t esp_memprot_iram0_get_intr_source_num(void)
{
    return ETS_PMS_PRO_IRAM0_ILG_INTR_SOURCE;
}

static inline void esp_memprot_iram0_intr_ena(bool enable)
{
    if ( enable ) {
        DPORT_SET_PERI_REG_MASK( DPORT_PMS_PRO_IRAM0_4_REG, DPORT_PMS_PRO_IRAM0_ILG_EN );
    } else {
        DPORT_CLEAR_PERI_REG_MASK( DPORT_PMS_PRO_IRAM0_4_REG, DPORT_PMS_PRO_IRAM0_ILG_EN );
    }
}

static inline uint32_t esp_memprot_iram0_get_ena_reg(void)
{
    return DPORT_READ_PERI_REG(DPORT_PMS_PRO_IRAM0_4_REG);
}

static inline uint32_t esp_memprot_iram0_get_fault_reg(void)
{
    return DPORT_READ_PERI_REG(DPORT_PMS_PRO_IRAM0_5_REG);
}

static inline void esp_memprot_iram0_get_fault_status(uint32_t **faulting_address, uint32_t *op_type, uint32_t *op_subtype)
{
    uint32_t status_bits = esp_memprot_iram0_get_fault_reg();

    uint32_t fault_addr = (status_bits & IRAM0_INTR_ST_FAULTADDR_M);
    *faulting_address = (uint32_t *)(fault_addr | IRAM0_INTR_ST_FAULTADDR_HI);

    *op_type = (uint32_t)status_bits & IRAM0_INTR_ST_OP_RW_BIT;
    *op_subtype = (uint32_t)status_bits & IRAM0_INTR_ST_OP_TYPE_BIT;
}

static inline bool esp_memprot_iram0_is_assoc_intr(void)
{
    return DPORT_GET_PERI_REG_MASK(DPORT_PMS_PRO_IRAM0_4_REG, DPORT_PMS_PRO_IRAM0_ILG_INTR) > 0;
}

static inline void esp_memprot_iram0_clear_intr(void)
{
    DPORT_SET_PERI_REG_MASK(DPORT_PMS_PRO_IRAM0_4_REG, DPORT_PMS_PRO_IRAM0_ILG_CLR);
}

static inline uint32_t esp_memprot_iram0_get_intr_ena_bit(void)
{
    return DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_4_REG, DPORT_PMS_PRO_IRAM0_ILG_EN);
}

static inline uint32_t esp_memprot_iram0_get_intr_on_bit(void)
{
    return DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_4_REG, DPORT_PMS_PRO_IRAM0_ILG_INTR);
}

static inline uint32_t esp_memprot_iram0_get_intr_clr_bit(void)
{
    return DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_4_REG, DPORT_PMS_PRO_IRAM0_ILG_CLR);
}

//CPU重新启动时自动重置
static inline void esp_memprot_iram0_set_lock(void)
{
    DPORT_WRITE_PERI_REG( DPORT_PMS_PRO_IRAM0_0_REG, DPORT_PMS_PRO_IRAM0_LOCK);
}

static inline uint32_t esp_memprot_iram0_get_lock_reg(void)
{
    return DPORT_READ_PERI_REG(DPORT_PMS_PRO_IRAM0_0_REG);
}

static inline uint32_t esp_memprot_iram0_get_lock_bit(void)
{
    return DPORT_REG_GET_FIELD(DPORT_PMS_PRO_IRAM0_0_REG, DPORT_PMS_PRO_IRAM0_LOCK);
}

//块0-3
static inline void esp_memprot_iram0_set_uni_block_perm(uint32_t block, bool write_perm, bool read_perm, bool exec_perm)
{
    HAL_ASSERT(block < IRAM0_TOTAL_UNI_BLOCKS);

    uint32_t write_bit, read_bit, exec_bit;
    switch ( block ) {
    case IRAM0_UNI_BLOCK_0:
        write_bit = DPORT_PMS_PRO_IRAM0_SRAM_0_W;
        read_bit = DPORT_PMS_PRO_IRAM0_SRAM_0_R;
        exec_bit = DPORT_PMS_PRO_IRAM0_SRAM_0_F;
        break;
    case IRAM0_UNI_BLOCK_1:
        write_bit = DPORT_PMS_PRO_IRAM0_SRAM_1_W;
        read_bit = DPORT_PMS_PRO_IRAM0_SRAM_1_R;
        exec_bit = DPORT_PMS_PRO_IRAM0_SRAM_1_F;
        break;
    case IRAM0_UNI_BLOCK_2:
        write_bit = DPORT_PMS_PRO_IRAM0_SRAM_2_W;
        read_bit = DPORT_PMS_PRO_IRAM0_SRAM_2_R;
        exec_bit = DPORT_PMS_PRO_IRAM0_SRAM_2_F;
        break;
    case IRAM0_UNI_BLOCK_3:
        write_bit = DPORT_PMS_PRO_IRAM0_SRAM_3_W;
        read_bit = DPORT_PMS_PRO_IRAM0_SRAM_3_R;
        exec_bit = DPORT_PMS_PRO_IRAM0_SRAM_3_F;
        break;
    default:
        abort();
    }

    if ( write_perm ) {
        DPORT_SET_PERI_REG_MASK( DPORT_PMS_PRO_IRAM0_1_REG, write_bit );
    } else {
        DPORT_CLEAR_PERI_REG_MASK( DPORT_PMS_PRO_IRAM0_1_REG, write_bit );
    }

    if ( read_perm ) {
        DPORT_SET_PERI_REG_MASK( DPORT_PMS_PRO_IRAM0_1_REG, read_bit );
    } else {
        DPORT_CLEAR_PERI_REG_MASK( DPORT_PMS_PRO_IRAM0_1_REG, read_bit );
    }

    if ( exec_perm ) {
        DPORT_SET_PERI_REG_MASK( DPORT_PMS_PRO_IRAM0_1_REG, exec_bit );
    } else {
        DPORT_CLEAR_PERI_REG_MASK( DPORT_PMS_PRO_IRAM0_1_REG, exec_bit );
    }
}

static inline uint32_t esp_memprot_iram0_get_uni_block_read_bit(uint32_t block)
{
    HAL_ASSERT(block < IRAM0_TOTAL_UNI_BLOCKS);

    switch ( block ) {
    case IRAM0_UNI_BLOCK_0:
        return DPORT_REG_GET_FIELD( DPORT_PMS_PRO_IRAM0_1_REG, DPORT_PMS_PRO_IRAM0_SRAM_0_R );
    case IRAM0_UNI_BLOCK_1:
        return DPORT_REG_GET_FIELD( DPORT_PMS_PRO_IRAM0_1_REG, DPORT_PMS_PRO_IRAM0_SRAM_1_R );
    case IRAM0_UNI_BLOCK_2:
        return DPORT_REG_GET_FIELD( DPORT_PMS_PRO_IRAM0_1_REG, DPORT_PMS_PRO_IRAM0_SRAM_2_R );
    case IRAM0_UNI_BLOCK_3:
        return DPORT_REG_GET_FIELD( DPORT_PMS_PRO_IRAM0_1_REG, DPORT_PMS_PRO_IRAM0_SRAM_3_R );
    default:
        abort();
    }
}

static inline uint32_t esp_memprot_iram0_get_uni_block_write_bit(uint32_t block)
{
    HAL_ASSERT(block < IRAM0_TOTAL_UNI_BLOCKS);

    switch ( block ) {
    case IRAM0_UNI_BLOCK_0:
        return DPORT_REG_GET_FIELD( DPORT_PMS_PRO_IRAM0_1_REG, DPORT_PMS_PRO_IRAM0_SRAM_0_W );
    case IRAM0_UNI_BLOCK_1:
        return DPORT_REG_GET_FIELD( DPORT_PMS_PRO_IRAM0_1_REG, DPORT_PMS_PRO_IRAM0_SRAM_1_W );
    case IRAM0_UNI_BLOCK_2:
        return DPORT_REG_GET_FIELD( DPORT_PMS_PRO_IRAM0_1_REG, DPORT_PMS_PRO_IRAM0_SRAM_2_W );
    case IRAM0_UNI_BLOCK_3:
        return DPORT_REG_GET_FIELD( DPORT_PMS_PRO_IRAM0_1_REG, DPORT_PMS_PRO_IRAM0_SRAM_3_W );
    default:
        abort();
    }
}

static inline uint32_t esp_memprot_iram0_get_uni_block_exec_bit(uint32_t block)
{
    HAL_ASSERT(block < IRAM0_TOTAL_UNI_BLOCKS);

    switch ( block ) {
    case IRAM0_UNI_BLOCK_0:
        return DPORT_REG_GET_FIELD( DPORT_PMS_PRO_IRAM0_1_REG, DPORT_PMS_PRO_IRAM0_SRAM_0_F );
    case IRAM0_UNI_BLOCK_1:
        return DPORT_REG_GET_FIELD( DPORT_PMS_PRO_IRAM0_1_REG, DPORT_PMS_PRO_IRAM0_SRAM_1_F );
    case IRAM0_UNI_BLOCK_2:
        return DPORT_REG_GET_FIELD( DPORT_PMS_PRO_IRAM0_1_REG, DPORT_PMS_PRO_IRAM0_SRAM_2_F );
    case IRAM0_UNI_BLOCK_3:
        return DPORT_REG_GET_FIELD( DPORT_PMS_PRO_IRAM0_1_REG, DPORT_PMS_PRO_IRAM0_SRAM_3_F );
    default:
        abort();
    }
}

static inline void esp_memprot_iram0_get_uni_block_sgnf_bits(uint32_t block, uint32_t *write_bit, uint32_t *read_bit, uint32_t *exec_bit)
{
    HAL_ASSERT(block < IRAM0_TOTAL_UNI_BLOCKS);

    switch ( block ) {
    case IRAM0_UNI_BLOCK_0:
        *write_bit = DPORT_PMS_PRO_IRAM0_SRAM_0_W;
        *read_bit = DPORT_PMS_PRO_IRAM0_SRAM_0_R;
        *exec_bit = DPORT_PMS_PRO_IRAM0_SRAM_0_F;
        break;
    case IRAM0_UNI_BLOCK_1:
        *write_bit = DPORT_PMS_PRO_IRAM0_SRAM_1_W;
        *read_bit = DPORT_PMS_PRO_IRAM0_SRAM_1_R;
        *exec_bit = DPORT_PMS_PRO_IRAM0_SRAM_1_F;
        break;
    case IRAM0_UNI_BLOCK_2:
        *write_bit = DPORT_PMS_PRO_IRAM0_SRAM_2_W;
        *read_bit = DPORT_PMS_PRO_IRAM0_SRAM_2_R;
        *exec_bit = DPORT_PMS_PRO_IRAM0_SRAM_2_F;
        break;
    case IRAM0_UNI_BLOCK_3:
        *write_bit = DPORT_PMS_PRO_IRAM0_SRAM_3_W;
        *read_bit = DPORT_PMS_PRO_IRAM0_SRAM_3_R;
        *exec_bit = DPORT_PMS_PRO_IRAM0_SRAM_3_F;
        break;
    default:
        abort();
    }
}

static inline uint32_t esp_memprot_iram0_get_perm_uni_reg(void)
{
    return DPORT_READ_PERI_REG(DPORT_PMS_PRO_IRAM0_1_REG);
}

static inline uint32_t esp_memprot_iram0_get_perm_split_reg(void)
{
    return DPORT_READ_PERI_REG(DPORT_PMS_PRO_IRAM0_2_REG);
}

static inline void esp_memprot_iram0_set_prot(uint32_t *split_addr, bool lw, bool lr, bool lx, bool hw, bool hr, bool hx)
{
    uint32_t addr = (uint32_t)split_addr;
    HAL_ASSERT(addr <= IRAM0_SPL_BLOCK_HIGH);

    //在低区域块中查找可能的拆分地址
    int uni_blocks_low = -1;
    if ( addr >= IRAM0_UNI_BLOCK_0_LOW ) {
        uni_blocks_low++;
    }
    if ( addr >= IRAM0_UNI_BLOCK_1_LOW ) {
        uni_blocks_low++;
    }
    if ( addr >= IRAM0_UNI_BLOCK_2_LOW ) {
        uni_blocks_low++;
    }
    if ( addr >= IRAM0_UNI_BLOCK_3_LOW ) {
        uni_blocks_low++;
    }

    //每个块的统一管理设置（位W/R/X:[11:9]bl3，[8:6]bl2，[5:3]bl1，[2:0]bl0）
    uint32_t write_bit, read_bit, exec_bit;
    uint32_t uni_block_perm = 0;

    for ( size_t x = 0; x < IRAM0_TOTAL_UNI_BLOCKS; x++ ) {
        esp_memprot_iram0_get_uni_block_sgnf_bits(x, &write_bit, &read_bit, &exec_bit);
        if ( x <= uni_blocks_low ) {
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

    //如果尚未设置splt.ddr，请执行所需的规范化操作，使addr可写入splt.mgmtcfg寄存器
    uint32_t reg_split_addr = 0;

    if ( addr >= IRAM0_SPL_BLOCK_LOW ) {

        //拆分地址必须与WORD对齐
        reg_split_addr = addr >> 2;
        HAL_ASSERT(addr == (reg_split_addr << 2));

        //仅使用17个符号位，因为整个部分的裁剪部分是恒定的（位[16:0]）
        reg_split_addr = (reg_split_addr << DPORT_PMS_PRO_IRAM0_SRAM_4_SPLTADDR_S) & DPORT_PMS_PRO_IRAM0_SRAM_4_SPLTADDR_M;
    }

    //准备高和低许可掩码（位：[22:20]高范围，[19:17]低范围）
    uint32_t permission_mask = 0;
    if ( lw ) {
        permission_mask |= DPORT_PMS_PRO_IRAM0_SRAM_4_L_W;
    }
    if ( lr ) {
        permission_mask |= DPORT_PMS_PRO_IRAM0_SRAM_4_L_R;
    }
    if ( lx ) {
        permission_mask |= DPORT_PMS_PRO_IRAM0_SRAM_4_L_F;
    }
    if ( hw ) {
        permission_mask |= DPORT_PMS_PRO_IRAM0_SRAM_4_H_W;
    }
    if ( hr ) {
        permission_mask |= DPORT_PMS_PRO_IRAM0_SRAM_4_H_R;
    }
    if ( hx ) {
        permission_mask |= DPORT_PMS_PRO_IRAM0_SRAM_4_H_F;
    }

    //编写两个cfg。寄存器
    DPORT_WRITE_PERI_REG( DPORT_PMS_PRO_IRAM0_1_REG, uni_block_perm );
    DPORT_WRITE_PERI_REG( DPORT_PMS_PRO_IRAM0_2_REG, reg_split_addr | permission_mask );
}

static inline void esp_memprot_iram0_get_split_sgnf_bits(bool *lw, bool *lr, bool *lx, bool *hw, bool *hr, bool *hx)
{
    *lw = DPORT_REG_GET_FIELD( DPORT_PMS_PRO_IRAM0_2_REG, DPORT_PMS_PRO_IRAM0_SRAM_4_L_W );
    *lr = DPORT_REG_GET_FIELD( DPORT_PMS_PRO_IRAM0_2_REG, DPORT_PMS_PRO_IRAM0_SRAM_4_L_R );
    *lx = DPORT_REG_GET_FIELD( DPORT_PMS_PRO_IRAM0_2_REG, DPORT_PMS_PRO_IRAM0_SRAM_4_L_F );
    *hw = DPORT_REG_GET_FIELD( DPORT_PMS_PRO_IRAM0_2_REG, DPORT_PMS_PRO_IRAM0_SRAM_4_H_W );
    *hr = DPORT_REG_GET_FIELD( DPORT_PMS_PRO_IRAM0_2_REG, DPORT_PMS_PRO_IRAM0_SRAM_4_H_R );
    *hx = DPORT_REG_GET_FIELD( DPORT_PMS_PRO_IRAM0_2_REG, DPORT_PMS_PRO_IRAM0_SRAM_4_H_F );
}

/**
 * === DRAM0 ====
 */

#define DRAM0_TOTAL_UNI_BLOCKS          4
#define DRAM0_UNI_BLOCK_0               0
#define DRAM0_UNI_BLOCK_1               1
#define DRAM0_UNI_BLOCK_2               2
#define DRAM0_UNI_BLOCK_3               3

#define DRAM0_SPL_BLOCK_BASE            0x3FFB0000

//统一管理（SRAM块0-3）
#define DRAM0_UNI_BLOCK_0_LOW           0x3FFB0000
#define DRAM0_UNI_BLOCK_0_HIGH          0x3FFB1FFF
#define DRAM0_UNI_BLOCK_1_LOW           0x3FFB2000
#define DRAM0_UNI_BLOCK_1_HIGH          0x3FFB3FFF
#define DRAM0_UNI_BLOCK_2_LOW           0x3FFB4000
#define DRAM0_UNI_BLOCK_2_HIGH          0x3FFB5FFF
#define DRAM0_UNI_BLOCK_3_LOW           0x3FFB6000
#define DRAM0_UNI_BLOCK_3_HIGH          0x3FFB7FFF

//分割管理（SRAM块4-21）
#define DRAM0_SPL_BLOCK_LOW             0x3FFB8000  //区块4低
#define DRAM0_SPL_BLOCK_HIGH            0x3FFFFFFF  //第21区偏高
#define DRAM0_SPLTADDR_MIN              0x3FFC0000  //块6低-最小拆分地址

//DRAM0中断状态位掩码
#define DRAM0_INTR_ST_FAULTADDR_M       0x03FFFFC0  //（reg中的位25:6）
#define DRAM0_INTR_ST_FAULTADDR_S       0x4         //（实际地址的位21:2）
#define DRAM0_INTR_ST_FAULTADDR_HI      0x3FF00000  //（错误地址的高非重要位31:22-常量）
#define DRAM0_INTR_ST_OP_RW_BIT         BIT(4)      //读取：0，写入：1
#define DRAM0_INTR_ST_OP_ATOMIC_BIT     BIT(5)      //非原子：0，原子：1


static inline uint32_t esp_memprot_dram0_get_intr_source_num(void)
{
    return ETS_PMS_PRO_DRAM0_ILG_INTR_SOURCE;
}

static inline void esp_memprot_dram0_intr_ena(bool enable)
{
    if ( enable ) {
        DPORT_SET_PERI_REG_MASK( DPORT_PMS_PRO_DRAM0_3_REG, DPORT_PMS_PRO_DRAM0_ILG_EN );
    } else {
        DPORT_CLEAR_PERI_REG_MASK( DPORT_PMS_PRO_DRAM0_3_REG, DPORT_PMS_PRO_DRAM0_ILG_EN );
    }
}

static inline bool esp_memprot_dram0_is_assoc_intr(void)
{
    return DPORT_GET_PERI_REG_MASK(DPORT_PMS_PRO_DRAM0_3_REG, DPORT_PMS_PRO_DRAM0_ILG_INTR) > 0;
}

static inline void esp_memprot_dram0_clear_intr(void)
{
    DPORT_SET_PERI_REG_MASK(DPORT_PMS_PRO_DRAM0_3_REG, DPORT_PMS_PRO_DRAM0_ILG_CLR);
}

static inline uint32_t esp_memprot_dram0_get_intr_ena_bit(void)
{
    return DPORT_REG_GET_FIELD(DPORT_PMS_PRO_DRAM0_3_REG, DPORT_PMS_PRO_DRAM0_ILG_EN);
}

static inline uint32_t esp_memprot_dram0_get_intr_on_bit(void)
{
    return DPORT_REG_GET_FIELD(DPORT_PMS_PRO_DRAM0_3_REG, DPORT_PMS_PRO_DRAM0_ILG_INTR);
}

static inline uint32_t esp_memprot_dram0_get_intr_clr_bit(void)
{
    return DPORT_REG_GET_FIELD(DPORT_PMS_PRO_DRAM0_3_REG, DPORT_PMS_PRO_DRAM0_ILG_CLR);
}

static inline uint32_t esp_memprot_dram0_get_lock_bit(void)
{
    return DPORT_REG_GET_FIELD(DPORT_PMS_PRO_DRAM0_0_REG, DPORT_PMS_PRO_DRAM0_LOCK);
}

static inline void esp_memprot_dram0_get_uni_block_sgnf_bits(uint32_t block, uint32_t *write_bit, uint32_t *read_bit)
{
    HAL_ASSERT(block < DRAM0_TOTAL_UNI_BLOCKS);

    switch ( block ) {
    case DRAM0_UNI_BLOCK_0:
        *write_bit = DPORT_PMS_PRO_DRAM0_SRAM_0_W;
        *read_bit = DPORT_PMS_PRO_DRAM0_SRAM_0_R;
        break;
    case DRAM0_UNI_BLOCK_1:
        *write_bit = DPORT_PMS_PRO_DRAM0_SRAM_1_W;
        *read_bit = DPORT_PMS_PRO_DRAM0_SRAM_1_R;
        break;
    case DRAM0_UNI_BLOCK_2:
        *write_bit = DPORT_PMS_PRO_DRAM0_SRAM_2_W;
        *read_bit = DPORT_PMS_PRO_DRAM0_SRAM_2_R;
        break;
    case DRAM0_UNI_BLOCK_3:
        *write_bit = DPORT_PMS_PRO_DRAM0_SRAM_3_W;
        *read_bit = DPORT_PMS_PRO_DRAM0_SRAM_3_R;
        break;
    default:
        abort();
    }
}

static inline void esp_memprot_dram0_set_uni_block_perm(uint32_t block, bool write_perm, bool read_perm)
{
    HAL_ASSERT(block < DRAM0_TOTAL_UNI_BLOCKS);

    uint32_t write_bit, read_bit;
    esp_memprot_dram0_get_uni_block_sgnf_bits(block, &write_bit, &read_bit);

    if ( write_perm ) {
        DPORT_SET_PERI_REG_MASK( DPORT_PMS_PRO_DRAM0_1_REG, write_bit );
    } else {
        DPORT_CLEAR_PERI_REG_MASK( DPORT_PMS_PRO_DRAM0_1_REG, write_bit );
    }

    if ( read_perm ) {
        DPORT_SET_PERI_REG_MASK( DPORT_PMS_PRO_DRAM0_1_REG, read_bit );
    } else {
        DPORT_CLEAR_PERI_REG_MASK( DPORT_PMS_PRO_DRAM0_1_REG, read_bit );
    }
}

static inline uint32_t esp_memprot_dram0_get_uni_block_read_bit(uint32_t block)
{
    HAL_ASSERT(block < DRAM0_TOTAL_UNI_BLOCKS);

    switch ( block ) {
    case DRAM0_UNI_BLOCK_0:
        return DPORT_REG_GET_FIELD( DPORT_PMS_PRO_DRAM0_1_REG, DPORT_PMS_PRO_DRAM0_SRAM_0_R );
    case DRAM0_UNI_BLOCK_1:
        return DPORT_REG_GET_FIELD( DPORT_PMS_PRO_DRAM0_1_REG, DPORT_PMS_PRO_DRAM0_SRAM_1_R );
    case DRAM0_UNI_BLOCK_2:
        return DPORT_REG_GET_FIELD( DPORT_PMS_PRO_DRAM0_1_REG, DPORT_PMS_PRO_DRAM0_SRAM_2_R );
    case DRAM0_UNI_BLOCK_3:
        return DPORT_REG_GET_FIELD( DPORT_PMS_PRO_DRAM0_1_REG, DPORT_PMS_PRO_DRAM0_SRAM_3_R );
    default:
        abort();
    }
}

static inline uint32_t esp_memprot_dram0_get_uni_block_write_bit(uint32_t block)
{
    HAL_ASSERT(block < DRAM0_TOTAL_UNI_BLOCKS);

    switch ( block ) {
    case DRAM0_UNI_BLOCK_0:
        return DPORT_REG_GET_FIELD( DPORT_PMS_PRO_DRAM0_1_REG, DPORT_PMS_PRO_DRAM0_SRAM_0_W );
    case DRAM0_UNI_BLOCK_1:
        return DPORT_REG_GET_FIELD( DPORT_PMS_PRO_DRAM0_1_REG, DPORT_PMS_PRO_DRAM0_SRAM_1_W );
    case DRAM0_UNI_BLOCK_2:
        return DPORT_REG_GET_FIELD( DPORT_PMS_PRO_DRAM0_1_REG, DPORT_PMS_PRO_DRAM0_SRAM_2_W );
    case DRAM0_UNI_BLOCK_3:
        return DPORT_REG_GET_FIELD( DPORT_PMS_PRO_DRAM0_1_REG, DPORT_PMS_PRO_DRAM0_SRAM_3_W );
    default:
        abort();
    }
}

static inline uint32_t esp_memprot_dram0_get_lock_reg(void)
{
    return DPORT_READ_PERI_REG(DPORT_PMS_PRO_DRAM0_0_REG);
}

//CPU重新启动时锁自动复位
static inline void esp_memprot_dram0_set_lock(void)
{
    DPORT_WRITE_PERI_REG( DPORT_PMS_PRO_DRAM0_0_REG, DPORT_PMS_PRO_DRAM0_LOCK);
}

static inline uint32_t esp_memprot_dram0_get_perm_reg(void)
{
    return DPORT_READ_PERI_REG(DPORT_PMS_PRO_DRAM0_1_REG);
}

static inline uint32_t esp_memprot_dram0_get_ena_reg(void)
{
    return DPORT_READ_PERI_REG(DPORT_PMS_PRO_DRAM0_3_REG);
}

static inline uint32_t esp_memprot_dram0_get_fault_reg(void)
{
    return DPORT_READ_PERI_REG(DPORT_PMS_PRO_DRAM0_4_REG);
}

static inline void esp_memprot_dram0_get_fault_status(uint32_t **faulting_address, uint32_t *op_type, uint32_t *op_subtype)
{
    uint32_t status_bits = esp_memprot_dram0_get_fault_reg();

    uint32_t fault_addr = (status_bits & DRAM0_INTR_ST_FAULTADDR_M) >> DRAM0_INTR_ST_FAULTADDR_S;
    *faulting_address = (uint32_t *)(fault_addr | DRAM0_INTR_ST_FAULTADDR_HI);

    *op_type = (uint32_t)status_bits & DRAM0_INTR_ST_OP_RW_BIT;
    *op_subtype = (uint32_t)status_bits & DRAM0_INTR_ST_OP_ATOMIC_BIT;
}

static inline void esp_memprot_dram0_set_prot(uint32_t *split_addr, bool lw, bool lr, bool hw, bool hr)
{
    uint32_t addr = (uint32_t)split_addr;

    //LD脚本提供的低边界检查。请参见esp_memprot_iram0_set_dot（）中的注释
    HAL_ASSERT(addr <= DRAM0_SPL_BLOCK_HIGH);

    //设置低区域
    int uni_blocks_low = -1;
    if ( addr >= DRAM0_UNI_BLOCK_0_LOW ) {
        uni_blocks_low++;
    }
    if ( addr >= DRAM0_UNI_BLOCK_1_LOW ) {
        uni_blocks_low++;
    }
    if ( addr >= DRAM0_UNI_BLOCK_2_LOW ) {
        uni_blocks_low++;
    }
    if ( addr >= DRAM0_UNI_BLOCK_3_LOW ) {
        uni_blocks_low++;
    }

    //设置统一管理区域
    uint32_t write_bit, read_bit, uni_block_perm = 0;
    for ( size_t x = 0; x < DRAM0_TOTAL_UNI_BLOCKS; x++ ) {
        esp_memprot_dram0_get_uni_block_sgnf_bits(x, &write_bit, &read_bit);
        if ( x <= uni_blocks_low ) {
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

    //检查拆分地址是否与WORD对齐
    uint32_t reg_split_addr = addr >> 2;
    HAL_ASSERT(addr == (reg_split_addr << 2));

    //将对齐的分割地址移位到适当的位偏移
    reg_split_addr = (reg_split_addr << DPORT_PMS_PRO_DRAM0_SRAM_4_SPLTADDR_S) & DPORT_PMS_PRO_DRAM0_SRAM_4_SPLTADDR_M;

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

    //将配置写入DPORT_PMS_PRO_DRAM0_1_REG
    DPORT_WRITE_PERI_REG(DPORT_PMS_PRO_DRAM0_1_REG, reg_split_addr | permission_mask | uni_block_perm);
}

static inline void esp_memprot_dram0_get_split_sgnf_bits(bool *lw, bool *lr, bool *hw, bool *hr)
{
    *lw = DPORT_REG_GET_FIELD( DPORT_PMS_PRO_DRAM0_1_REG, DPORT_PMS_PRO_DRAM0_SRAM_4_L_W );
    *lr = DPORT_REG_GET_FIELD( DPORT_PMS_PRO_DRAM0_1_REG, DPORT_PMS_PRO_DRAM0_SRAM_4_L_R );
    *hw = DPORT_REG_GET_FIELD( DPORT_PMS_PRO_DRAM0_1_REG, DPORT_PMS_PRO_DRAM0_SRAM_4_H_W );
    *hr = DPORT_REG_GET_FIELD( DPORT_PMS_PRO_DRAM0_1_REG, DPORT_PMS_PRO_DRAM0_SRAM_4_H_R );
}

#endif

#ifdef __cplusplus
}
#endif

