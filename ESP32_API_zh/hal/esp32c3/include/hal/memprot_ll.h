/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "soc/cache_memory.h"
#include "soc/memprot_defs.h"
#include "hal/memprot_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ******************************************************************************************************
 * *** COMMON ***
 * ******************************************************************************************************/
static inline void memprot_ll_set_iram0_dram0_split_line_lock(void)
{
    REG_WRITE(SENSITIVE_CORE_X_IRAM0_DRAM0_DMA_SPLIT_LINE_CONSTRAIN_0_REG, 1);
}

static inline bool memprot_ll_get_iram0_dram0_split_line_lock(void)
{
    return REG_READ(SENSITIVE_CORE_X_IRAM0_DRAM0_DMA_SPLIT_LINE_CONSTRAIN_0_REG) == 1;
}

static inline void *memprot_ll_get_split_addr_from_reg(uint32_t regval, uint32_t base)
{
    constrain_reg_fields_t reg_val;
    reg_val.val = regval;

    uint32_t off = reg_val.splitaddr << 9;

    if (reg_val.cat0 == 0x1 || reg_val.cat0 == 0x2) {
        return (void *)(base + off);
    } else if (reg_val.cat1 == 0x1 || reg_val.cat1 == 0x2) {
        return (void *)(base + I_D_SRAM_SEGMENT_SIZE + off);
    } else if (reg_val.cat2 == 0x1 || reg_val.cat2 == 0x2) {
        return (void *)(base + (2 * I_D_SRAM_SEGMENT_SIZE) + off);
    } else {
        /* 寄存器根本没有配置或配置不正确*/
        return NULL;
    }
}

/* ******************************************************************************************************
 * *** IRAM0 ***
 * ******************************************************************************************************/
static inline uint32_t memprot_ll_iram0_get_intr_source_num(void)
{
    return ETS_CORE0_IRAM0_PMS_INTR_SOURCE;
}

/* ********************************
 * IRAM0 - SPLIT LINES
 *
 * 注：1.IRAM0/DRAM0分割线必须与512B边界对齐（PMS模块限制）2.分割地址必须属于适当的IRAM0/DRAM0区域
 */
static inline memprot_ll_err_t memprot_ll_set_iram0_split_line(const void *line_addr, uint32_t sensitive_reg)
{
    uint32_t addr = (uint32_t)line_addr;

    if (addr < IRAM0_SRAM_LEVEL_1_LOW || addr > IRAM0_SRAM_LEVEL_3_HIGH) {
        return MEMP_LL_ERR_SPLIT_ADDR_OUT_OF_RANGE;
    }

    if (addr % 0x200 != 0) {
        return MEMP_LL_ERR_SPLIT_ADDR_UNALIGNED;
    }

    uint32_t category[3] = {0};
    if (addr <= IRAM0_SRAM_LEVEL_1_HIGH) {
        category[0] = 0x2;
        category[1] = category[2] = 0x3;
    } else if (addr >= IRAM0_SRAM_LEVEL_2_LOW && addr <= IRAM0_SRAM_LEVEL_2_HIGH) {
        category[1] = 0x2;
        category[2] = 0x3;
    } else {
        category[2] = 0x2;
    }

    //注：所有区域的类别和拆分行地址位相同
    uint32_t category_bits =
        (category[0] << SENSITIVE_CORE_X_IRAM0_DRAM0_DMA_SRAM_CATEGORY_0_S) |
        (category[1] << SENSITIVE_CORE_X_IRAM0_DRAM0_DMA_SRAM_CATEGORY_1_S) |
        (category[2] << SENSITIVE_CORE_X_IRAM0_DRAM0_DMA_SRAM_CATEGORY_2_S);

    uint32_t conf_addr = ((addr >> I_D_SPLIT_LINE_SHIFT) & SENSITIVE_CORE_X_IRAM0_DRAM0_DMA_SRAM_SPLITADDR_V) << SENSITIVE_CORE_X_IRAM0_DRAM0_DMA_SRAM_SPLITADDR_S;
    uint32_t reg_cfg = conf_addr | category_bits;

    REG_WRITE(sensitive_reg, reg_cfg);

    return MEMP_LL_OK;
}

/* 可以是IRAM0/DRAM0地址*/
static inline memprot_ll_err_t memprot_ll_set_iram0_split_line_main_I_D(const void *line_addr)
{
    return memprot_ll_set_iram0_split_line(line_addr, SENSITIVE_CORE_X_IRAM0_DRAM0_DMA_SPLIT_LINE_CONSTRAIN_1_REG);
}

static inline memprot_ll_err_t memprot_ll_set_iram0_split_line_I_0(const void *line_addr)
{
    return memprot_ll_set_iram0_split_line(line_addr, SENSITIVE_CORE_X_IRAM0_DRAM0_DMA_SPLIT_LINE_CONSTRAIN_2_REG);
}

static inline memprot_ll_err_t memprot_ll_set_iram0_split_line_I_1(const void *line_addr)
{
    return memprot_ll_set_iram0_split_line(line_addr, SENSITIVE_CORE_X_IRAM0_DRAM0_DMA_SPLIT_LINE_CONSTRAIN_3_REG);
}

static inline uint32_t memprot_ll_get_iram0_split_line_main_I_D_cat(void)
{
    return REG_READ(SENSITIVE_CORE_X_IRAM0_DRAM0_DMA_SPLIT_LINE_CONSTRAIN_1_REG) & 0x3F;
}

static inline uint32_t memprot_ll_get_iram0_split_line_I_0_cat(void)
{
    return REG_READ(SENSITIVE_CORE_X_IRAM0_DRAM0_DMA_SPLIT_LINE_CONSTRAIN_2_REG) & 0x3F;
}

static inline uint32_t memprot_ll_get_iram0_split_line_I_1_cat(void)
{
    return REG_READ(SENSITIVE_CORE_X_IRAM0_DRAM0_DMA_SPLIT_LINE_CONSTRAIN_3_REG) & 0x3F;
}

static inline void *memprot_ll_get_iram0_split_line_main_I_D(void)
{
    return memprot_ll_get_split_addr_from_reg(REG_READ(SENSITIVE_CORE_X_IRAM0_DRAM0_DMA_SPLIT_LINE_CONSTRAIN_1_REG), SOC_DIRAM_IRAM_LOW);
}

static inline void *memprot_ll_get_iram0_split_line_I_0(void)
{
    return memprot_ll_get_split_addr_from_reg(REG_READ(SENSITIVE_CORE_X_IRAM0_DRAM0_DMA_SPLIT_LINE_CONSTRAIN_2_REG), SOC_DIRAM_IRAM_LOW);
}

static inline void *memprot_ll_get_iram0_split_line_I_1(void)
{
    return memprot_ll_get_split_addr_from_reg(REG_READ(SENSITIVE_CORE_X_IRAM0_DRAM0_DMA_SPLIT_LINE_CONSTRAIN_3_REG), SOC_DIRAM_IRAM_LOW);
}

///////////////////////////////////
// IRAM0 - PMS CONFIGURATION

// 锁
static inline void memprot_ll_iram0_set_pms_lock(void)
{
    REG_WRITE(SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_0_REG, 1);
}

static inline bool memprot_ll_iram0_get_pms_lock(void)
{
    return REG_READ(SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_0_REG) == 1;
}

// 权限设置
static inline uint32_t memprot_ll_iram0_set_permissions(bool r, bool w, bool x)
{
    uint32_t permissions = 0;
    if (r) {
        permissions |= SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_SRAM_WORLD_X_R;
    }
    if (w) {
        permissions |= SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_SRAM_WORLD_X_W;
    }
    if (x) {
        permissions |= SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_SRAM_WORLD_X_F;
    }

    return permissions;
}

static inline void memprot_ll_iram0_set_pms_area_0(bool r, bool w, bool x)
{
    REG_SET_FIELD(SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_2_REG, SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_SRAM_WORLD_0_PMS_0, memprot_ll_iram0_set_permissions(r, w, x));
}

static inline void memprot_ll_iram0_set_pms_area_1(bool r, bool w, bool x)
{
    REG_SET_FIELD(SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_2_REG, SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_SRAM_WORLD_0_PMS_1, memprot_ll_iram0_set_permissions(r, w, x));
}

static inline void memprot_ll_iram0_set_pms_area_2(bool r, bool w, bool x)
{
    REG_SET_FIELD(SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_2_REG, SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_SRAM_WORLD_0_PMS_2, memprot_ll_iram0_set_permissions(r, w, x));
}

static inline void memprot_ll_iram0_set_pms_area_3(bool r, bool w, bool x)
{
    REG_SET_FIELD(SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_2_REG, SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_SRAM_WORLD_0_PMS_3, memprot_ll_iram0_set_permissions(r, w, x));
}

static inline void memprot_ll_iram0_get_permissions(uint32_t perms, bool *r, bool *w, bool *x)
{
    *r = perms & SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_SRAM_WORLD_X_R;
    *w = perms & SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_SRAM_WORLD_X_W;
    *x = perms & SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_SRAM_WORLD_X_F;
}

static inline void memprot_ll_iram0_get_pms_area_0(bool *r, bool *w, bool *x)
{
    uint32_t permissions = REG_GET_FIELD(SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_2_REG, SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_SRAM_WORLD_0_PMS_0);
    memprot_ll_iram0_get_permissions(permissions, r, w, x);
}

static inline void memprot_ll_iram0_get_pms_area_1(bool *r, bool *w, bool *x)
{
    uint32_t permissions = REG_GET_FIELD(SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_2_REG, SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_SRAM_WORLD_0_PMS_1);
    memprot_ll_iram0_get_permissions(permissions, r, w, x);
}

static inline void memprot_ll_iram0_get_pms_area_2(bool *r, bool *w, bool *x)
{
    uint32_t permissions = REG_GET_FIELD(SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_2_REG, SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_SRAM_WORLD_0_PMS_2);
    memprot_ll_iram0_get_permissions(permissions, r, w, x);
}

static inline void memprot_ll_iram0_get_pms_area_3(bool *r, bool *w, bool *x)
{
    uint32_t permissions = REG_GET_FIELD(SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_2_REG, SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_SRAM_WORLD_0_PMS_3);
    memprot_ll_iram0_get_permissions(permissions, r, w, x);
}


///////////////////////////////////
// IRAM0 - MONITOR

// 锁
static inline void memprot_ll_iram0_set_monitor_lock(void)
{
    REG_WRITE(SENSITIVE_CORE_0_IRAM0_PMS_MONITOR_0_REG, 1);
}

static inline bool memprot_ll_iram0_get_monitor_lock(void)
{
    return REG_READ(SENSITIVE_CORE_0_IRAM0_PMS_MONITOR_0_REG) == 1;
}

// 中断启用/清除
static inline void memprot_ll_iram0_set_monitor_en(bool enable)
{
    if (enable) {
        REG_SET_BIT(SENSITIVE_CORE_0_IRAM0_PMS_MONITOR_1_REG, SENSITIVE_CORE_0_IRAM0_PMS_MONITOR_VIOLATE_EN);
    } else {
        REG_CLR_BIT(SENSITIVE_CORE_0_IRAM0_PMS_MONITOR_1_REG, SENSITIVE_CORE_0_IRAM0_PMS_MONITOR_VIOLATE_EN);
    }
}

static inline bool memprot_ll_iram0_get_monitor_intrclr(void)
{
    return REG_GET_BIT(SENSITIVE_CORE_0_IRAM0_PMS_MONITOR_1_REG, SENSITIVE_CORE_0_IRAM0_PMS_MONITOR_VIOLATE_CLR) > 0;
}

static inline bool memprot_ll_iram0_get_monitor_en(void)
{
    return REG_GET_FIELD(SENSITIVE_CORE_0_IRAM0_PMS_MONITOR_1_REG, SENSITIVE_CORE_0_IRAM0_PMS_MONITOR_VIOLATE_EN) == 1;
}

static inline void memprot_ll_iram0_set_monitor_intrclr(void)
{
    REG_SET_BIT(SENSITIVE_CORE_0_IRAM0_PMS_MONITOR_1_REG, SENSITIVE_CORE_0_IRAM0_PMS_MONITOR_VIOLATE_CLR);
}

static inline void memprot_ll_iram0_reset_monitor_intrclr(void)
{
    REG_CLR_BIT(SENSITIVE_CORE_0_IRAM0_PMS_MONITOR_1_REG, SENSITIVE_CORE_0_IRAM0_PMS_MONITOR_VIOLATE_CLR);
}

static inline uint32_t memprot_ll_iram0_get_monitor_enable_register(void)
{
    return REG_READ(SENSITIVE_CORE_0_IRAM0_PMS_MONITOR_1_REG);
}

// 权限冲突状态
static inline uint32_t memprot_ll_iram0_get_monitor_status_intr(void)
{
    return REG_GET_FIELD(SENSITIVE_CORE_0_IRAM0_PMS_MONITOR_2_REG, SENSITIVE_CORE_0_IRAM0_PMS_MONITOR_VIOLATE_INTR);
}

static inline uint32_t memprot_ll_iram0_get_monitor_status_fault_wr(void)
{
    return REG_GET_FIELD(SENSITIVE_CORE_0_IRAM0_PMS_MONITOR_2_REG, SENSITIVE_CORE_0_IRAM0_PMS_MONITOR_VIOLATE_STATUS_WR);
}

static inline uint32_t memprot_ll_iram0_get_monitor_status_fault_loadstore(void)
{
    return REG_GET_FIELD(SENSITIVE_CORE_0_IRAM0_PMS_MONITOR_2_REG, SENSITIVE_CORE_0_IRAM0_PMS_MONITOR_VIOLATE_STATUS_LOADSTORE);
}

static inline uint32_t memprot_ll_iram0_get_monitor_status_fault_world(void)
{
    return REG_GET_FIELD(SENSITIVE_CORE_0_IRAM0_PMS_MONITOR_2_REG, SENSITIVE_CORE_0_IRAM0_PMS_MONITOR_VIOLATE_STATUS_WORLD);
}

static inline intptr_t memprot_ll_iram0_get_monitor_status_fault_addr(void)
{
    uint32_t addr = REG_GET_FIELD(SENSITIVE_CORE_0_IRAM0_PMS_MONITOR_2_REG, SENSITIVE_CORE_0_IRAM0_PMS_MONITOR_VIOLATE_STATUS_ADDR);
    return (intptr_t)(addr > 0 ? (addr << I_D_FAULT_ADDR_SHIFT) + IRAM0_ADDRESS_LOW : 0);
}

static inline uint32_t memprot_ll_iram0_get_monitor_status_register(void)
{
    return REG_READ(SENSITIVE_CORE_0_IRAM0_PMS_MONITOR_2_REG);
}


/* ******************************************************************************************************
 * *** RTC_FAST ***
 */

static inline uint32_t memprot_ll_rtcfast_get_intr_source_num(void)
{
    return ETS_CORE0_PIF_PMS_INTR_SOURCE;
}

//共享PIF PMS锁
//!!!: 在设置所有约束后使用
static inline void memprot_ll_set_pif_constraint_lock(void)
{
    REG_WRITE(SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_0_REG, 1);
}

static inline bool memprot_ll_get_pif_constraint_lock(void)
{
    return REG_READ(SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_0_REG) == 1;
}

static inline uint32_t memprot_ll_rtcfast_get_splitaddr_register(void)
{
    return REG_READ(SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_9_REG);
}

/* ********************************
 * IRAM0 RTCFAST - SPLIT LINES
 *
 * 注意：1.RTCFAST/WORLD只有一条分割线2.RTCFAST分割线必须与4B边界对齐（PMS在8kB RTCFAST区域中存储11位13位偏移量）3.RTCFAST具有奇怪的部分结构（text->dummy（！）->force->data）-.dummy节似乎有错误的映射（它不与.rctext内联）
 */
static inline memprot_ll_err_t memprot_ll_set_rtcfast_split_line(const void *line_addr, memprot_ll_world_t world)
{
    uint32_t addr = (uint32_t)line_addr;
    uint32_t mask;

    if (addr < SOC_RTC_IRAM_LOW || addr >= SOC_RTC_IRAM_HIGH) {
        return MEMP_LL_ERR_SPLIT_ADDR_OUT_OF_RANGE;
    }

    if (addr % 0x4 != 0) {
        return MEMP_LL_ERR_SPLIT_ADDR_UNALIGNED;
    }

    switch (world) {
    case MEMP_LL_WORLD_0:
        mask = SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_SPLTADDR_WORLD_0_M;
        break;
    case MEMP_LL_WORLD_1:
        mask = SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_SPLTADDR_WORLD_1_M;
        break;
    default:
        return MEMP_LL_ERR_WORLD_INVALID;
    }

    //使用SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_SPLTADDR_WORLD_0_V，要存储的两个世界的偏移位宽度相同
    CLEAR_PERI_REG_MASK(SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_9_REG, mask);
    REG_SET_BITS(SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_9_REG, mask, (addr >> 2) & SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_SPLTADDR_WORLD_0_V);

    return MEMP_LL_OK;
}

static inline memprot_ll_err_t memprot_ll_get_rtcfast_split_line(memprot_ll_world_t world, void **line_addr)
{
    uint32_t reg_addr = REG_READ(SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_9_REG);
    uint32_t mask = 0;
    uint32_t shift = 0;

    switch (world) {
    case MEMP_LL_WORLD_0:
        mask = SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_SPLTADDR_WORLD_0_M;
        shift = SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_SPLTADDR_WORLD_0_S;
        break;
    case MEMP_LL_WORLD_1:
        mask = SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_SPLTADDR_WORLD_1_M;
        shift = SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_SPLTADDR_WORLD_1_S;
        break;
    default:
        return MEMP_LL_ERR_WORLD_INVALID;
    }

    *line_addr = (void *)((((reg_addr & mask) >> shift) << 2) + SOC_RTC_IRAM_LOW);

    return MEMP_LL_OK;
}

///////////////////////////////////
// RTC_FAST - PMS CONFIGURATION

// 权限设置
static inline uint32_t memprot_ll_rtcfast_set_permissions(bool r, bool w, bool x)
{
    uint32_t permissions = 0;
    if (r) {
        permissions |= SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_WORLD_X_R;
    }
    if (w) {
        permissions |= SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_WORLD_X_W;
    }
    if (x) {
        permissions |= SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_WORLD_X_F;
    }

    return permissions;
}

static inline memprot_ll_err_t memprot_ll_rtcfast_set_pms_area(bool r, bool w, bool x, memprot_ll_world_t world, memprot_ll_area_t area)
{
    uint32_t bits = 0;
    uint32_t mask = 0;

    switch (world) {
    case MEMP_LL_WORLD_0: {
        switch (area) {
        case MEMP_LL_AREA_LOW:
            bits = memprot_ll_rtcfast_set_permissions(r, w, x) << SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_WORLD_0_L_S;
            mask = SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_WORLD_0_L_M;
            break;
        case MEMP_LL_AREA_HIGH:
            bits = memprot_ll_rtcfast_set_permissions(r, w, x) << SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_WORLD_0_H_S;
            mask = SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_WORLD_0_H_M;
            break;
        default:
            return MEMP_LL_ERR_AREA_INVALID;
        }
    } break;
    case MEMP_LL_WORLD_1: {
        switch (area) {
        case MEMP_LL_AREA_LOW:
            bits = memprot_ll_rtcfast_set_permissions(r, w, x) << SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_WORLD_1_L_S;
            mask = SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_WORLD_1_L_M;
            break;
        case MEMP_LL_AREA_HIGH:
            bits = memprot_ll_rtcfast_set_permissions(r, w, x) << SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_WORLD_1_H_S;
            mask = SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_WORLD_1_H_M;
            break;
        default:
            return MEMP_LL_ERR_AREA_INVALID;
        }
    } break;
    default:
        return MEMP_LL_ERR_WORLD_INVALID;
    }

    CLEAR_PERI_REG_MASK(SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_10_REG, mask);
    REG_SET_BITS(SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_10_REG, bits, mask);

    return MEMP_LL_OK;
}

static inline void memprot_ll_rtcfast_get_permissions(uint32_t perms, bool *r, bool *w, bool *x)
{
    *r = perms & SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_WORLD_X_R;
    *w = perms & SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_WORLD_X_W;
    *x = perms & SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_WORLD_X_F;
}

static inline memprot_ll_err_t memprot_ll_rtcfast_get_pms_area(bool *r, bool *w, bool *x, memprot_ll_world_t world, memprot_ll_area_t area)
{
    uint32_t permissions = 0;

    switch (world) {
    case MEMP_LL_WORLD_0: {
        switch (area) {
        case MEMP_LL_AREA_LOW:
            permissions = REG_GET_FIELD(SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_10_REG, SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_WORLD_0_L);
            break;
        case MEMP_LL_AREA_HIGH:
            permissions = REG_GET_FIELD(SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_10_REG, SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_WORLD_0_H);
            break;
        default:
            return MEMP_LL_ERR_AREA_INVALID;
        }
    } break;
    case MEMP_LL_WORLD_1: {
        switch (area) {
        case MEMP_LL_AREA_LOW:
            permissions = REG_GET_FIELD(SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_10_REG, SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_WORLD_1_L);
            break;
        case MEMP_LL_AREA_HIGH:
            permissions = REG_GET_FIELD(SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_10_REG, SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_WORLD_1_H);
            break;
        default:
            return MEMP_LL_ERR_AREA_INVALID;
        }
    } break;
    default:
        return MEMP_LL_ERR_WORLD_INVALID;
    }

    memprot_ll_rtcfast_get_permissions(permissions, r, w, x);

    return MEMP_LL_OK;
}

static inline uint32_t memprot_ll_rtcfast_get_permission_register(void)
{
    return REG_READ(SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_10_REG);
}

///////////////////////////////////
// RTC_FAST - MONITOR

// 锁
static inline void memprot_ll_rtcfast_set_monitor_lock(void)
{
    REG_WRITE(SENSITIVE_CORE_0_PIF_PMS_MONITOR_0_REG, 1);
}

static inline bool memprot_ll_rtcfast_get_monitor_lock(void)
{
    return REG_READ(SENSITIVE_CORE_0_PIF_PMS_MONITOR_0_REG) == 1;
}

// 中断启用/清除
static inline void memprot_ll_rtcfast_set_monitor_en(bool enable)
{
    if (enable) {
        REG_SET_BIT(SENSITIVE_CORE_0_PIF_PMS_MONITOR_1_REG, SENSITIVE_CORE_0_PIF_PMS_MONITOR_VIOLATE_EN);
    } else {
        REG_CLR_BIT(SENSITIVE_CORE_0_PIF_PMS_MONITOR_1_REG, SENSITIVE_CORE_0_PIF_PMS_MONITOR_VIOLATE_EN);
    }
}

static inline bool memprot_ll_rtcfast_get_monitor_en(void)
{
    return REG_GET_FIELD(SENSITIVE_CORE_0_PIF_PMS_MONITOR_1_REG, SENSITIVE_CORE_0_PIF_PMS_MONITOR_VIOLATE_EN) > 0;
}

static inline bool memprot_ll_rtcfast_get_monitor_intrclr(void)
{
    return REG_GET_BIT(SENSITIVE_CORE_0_PIF_PMS_MONITOR_1_REG, SENSITIVE_CORE_0_PIF_PMS_MONITOR_VIOLATE_CLR) > 0;
}

static inline void memprot_ll_rtcfast_set_monitor_intrclr(void)
{
    REG_SET_BIT(SENSITIVE_CORE_0_PIF_PMS_MONITOR_1_REG, SENSITIVE_CORE_0_PIF_PMS_MONITOR_VIOLATE_CLR);
}

static inline void memprot_ll_rtcfast_reset_monitor_intrclr(void)
{
    REG_CLR_BIT(SENSITIVE_CORE_0_PIF_PMS_MONITOR_1_REG, SENSITIVE_CORE_0_PIF_PMS_MONITOR_VIOLATE_CLR);
}

static inline uint32_t memprot_ll_rtcfast_get_monitor_register(void)
{
    return REG_READ(SENSITIVE_CORE_0_PIF_PMS_MONITOR_1_REG);
}

// 权限冲突状态
static inline uint32_t memprot_ll_rtcfast_get_monitor_status_intr(void)
{
    return REG_GET_FIELD(SENSITIVE_CORE_0_PIF_PMS_MONITOR_2_REG, SENSITIVE_CORE_0_PIF_PMS_MONITOR_VIOLATE_INTR);
}

static inline intptr_t memprot_ll_rtcfast_get_monitor_status_fault_addr(void)
{
    //完整地址SENSITIVE_CORE_0_PIF_PMS_MONITOR_VIOLATE_STATUS_HADDR
    return (intptr_t)REG_READ(SENSITIVE_CORE_0_PIF_PMS_MONITOR_3_REG);
}

static inline uint32_t memprot_ll_rtcfast_get_monitor_status_fault_world(void)
{
    return REG_GET_FIELD(SENSITIVE_CORE_0_PIF_PMS_MONITOR_2_REG, SENSITIVE_CORE_0_PIF_PMS_MONITOR_VIOLATE_STATUS_HWORLD);
}

static inline uint32_t memprot_ll_rtcfast_get_monitor_status_fault_loadstore(void)
{
    return REG_GET_FIELD(SENSITIVE_CORE_0_PIF_PMS_MONITOR_2_REG, SENSITIVE_CORE_0_PIF_PMS_MONITOR_VIOLATE_STATUS_HPORT_0);
}

static inline uint32_t memprot_ll_rtcfast_get_monitor_status_fault_wr(void)
{
    return REG_GET_FIELD(SENSITIVE_CORE_0_PIF_PMS_MONITOR_2_REG, SENSITIVE_CORE_0_PIF_PMS_MONITOR_VIOLATE_STATUS_HWRITE);
}


/* ******************************************************************************************************
 * *** DRAM0 ***
 * ******************************************************************************************************/

static inline uint32_t memprot_ll_dram0_get_intr_source_num(void)
{
    return ETS_CORE0_DRAM0_PMS_INTR_SOURCE;
}

///////////////////////////////////
// DRAM0 - SPLIT LINES

static inline memprot_ll_err_t memprot_ll_set_dram0_split_line(const void *line_addr, uint32_t sensitive_reg)
{
    uint32_t addr = (uint32_t)line_addr;

    //健全性检查：统一管理区域上方需要拆分地址&32位对齐
    if (addr < DRAM0_SRAM_LEVEL_1_LOW || addr > DRAM0_SRAM_LEVEL_3_HIGH) {
        return MEMP_LL_ERR_SPLIT_ADDR_OUT_OF_RANGE;
    }
    //分割线必须可被512整除（PMS模块限制）
    if (addr % 0x200 != 0) {
        return MEMP_LL_ERR_SPLIT_ADDR_UNALIGNED;
    }

    uint32_t category[3] = {0};
    if (addr <= DRAM0_SRAM_LEVEL_1_HIGH) {
        category[0] = 0x2;
        category[1] = category[2] = 0x3;
    } else if (addr >= DRAM0_SRAM_LEVEL_2_LOW && addr <= DRAM0_SRAM_LEVEL_2_HIGH) {
        category[1] = 0x2;
        category[2] = 0x3;
    } else {
        category[2] = 0x2;
    }

    //注：所有区域的线路地址和类别位、移位和掩码相同
    uint32_t category_bits =
        (category[0] << SENSITIVE_CORE_X_IRAM0_DRAM0_DMA_SRAM_CATEGORY_0_S) |
        (category[1] << SENSITIVE_CORE_X_IRAM0_DRAM0_DMA_SRAM_CATEGORY_1_S) |
        (category[2] << SENSITIVE_CORE_X_IRAM0_DRAM0_DMA_SRAM_CATEGORY_2_S);

    uint32_t conf_addr = ((addr >> I_D_SPLIT_LINE_SHIFT) & SENSITIVE_CORE_X_IRAM0_DRAM0_DMA_SRAM_SPLITADDR_V) << SENSITIVE_CORE_X_IRAM0_DRAM0_DMA_SRAM_SPLITADDR_S;
    uint32_t reg_cfg = conf_addr | category_bits;

    REG_WRITE(sensitive_reg, reg_cfg);

    return MEMP_LL_OK;
}

static inline memprot_ll_err_t memprot_ll_set_dram0_split_line_D_0(const void *line_addr)
{
    return memprot_ll_set_dram0_split_line(line_addr, SENSITIVE_CORE_X_IRAM0_DRAM0_DMA_SPLIT_LINE_CONSTRAIN_4_REG);
}

static inline memprot_ll_err_t memprot_ll_set_dram0_split_line_D_1(const void *line_addr)
{
    return memprot_ll_set_dram0_split_line(line_addr, SENSITIVE_CORE_X_IRAM0_DRAM0_DMA_SPLIT_LINE_CONSTRAIN_5_REG);
}

static inline void *memprot_ll_get_dram0_split_line_D_0(void)
{
    return memprot_ll_get_split_addr_from_reg(REG_READ(SENSITIVE_CORE_X_IRAM0_DRAM0_DMA_SPLIT_LINE_CONSTRAIN_4_REG), SOC_DIRAM_DRAM_LOW);
}

static inline void *memprot_ll_get_dram0_split_line_D_1(void)
{
    return memprot_ll_get_split_addr_from_reg(REG_READ(SENSITIVE_CORE_X_IRAM0_DRAM0_DMA_SPLIT_LINE_CONSTRAIN_5_REG), SOC_DIRAM_DRAM_LOW);
}

static inline uint32_t memprot_ll_get_dram0_split_line_D_0_cat(void)
{
    return REG_READ(SENSITIVE_CORE_X_IRAM0_DRAM0_DMA_SPLIT_LINE_CONSTRAIN_4_REG) & 0x3F;
}

static inline uint32_t memprot_ll_get_dram0_split_line_D_1_cat(void)
{
    return REG_READ(SENSITIVE_CORE_X_IRAM0_DRAM0_DMA_SPLIT_LINE_CONSTRAIN_5_REG) & 0x3F;
}

///////////////////////////////////
// DRAM0 - PMS CONFIGURATION

// 锁
static inline void memprot_ll_dram0_set_pms_lock(void)
{
    REG_WRITE(SENSITIVE_CORE_X_DRAM0_PMS_CONSTRAIN_0_REG, 1);
}

static inline bool memprot_ll_dram0_get_pms_lock(void)
{
    return REG_READ(SENSITIVE_CORE_X_DRAM0_PMS_CONSTRAIN_0_REG) == 1;
}

// 权限设置
static inline uint32_t memprot_ll_dram0_set_permissions(bool r, bool w)
{
    uint32_t permissions = 0;
    if (r) {
        permissions |= SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_SRAM_WORLD_X_R;
    }
    if (w) {
        permissions |= SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_SRAM_WORLD_X_W;
    }

    return permissions;
}

static inline void memprot_ll_dram0_set_pms_area_0(bool r, bool w)
{
    REG_SET_FIELD(SENSITIVE_CORE_X_DRAM0_PMS_CONSTRAIN_1_REG, SENSITIVE_CORE_X_DRAM0_PMS_CONSTRAIN_SRAM_WORLD_0_PMS_0, memprot_ll_dram0_set_permissions(r, w));
}

static inline void memprot_ll_dram0_set_pms_area_1(bool r, bool w)
{
    REG_SET_FIELD(SENSITIVE_CORE_X_DRAM0_PMS_CONSTRAIN_1_REG, SENSITIVE_CORE_X_DRAM0_PMS_CONSTRAIN_SRAM_WORLD_0_PMS_1, memprot_ll_dram0_set_permissions(r, w));
}

static inline void memprot_ll_dram0_set_pms_area_2(bool r, bool w)
{
    REG_SET_FIELD(SENSITIVE_CORE_X_DRAM0_PMS_CONSTRAIN_1_REG, SENSITIVE_CORE_X_DRAM0_PMS_CONSTRAIN_SRAM_WORLD_0_PMS_2, memprot_ll_dram0_set_permissions(r, w));
}

static inline void memprot_ll_dram0_set_pms_area_3(bool r, bool w)
{
    REG_SET_FIELD(SENSITIVE_CORE_X_DRAM0_PMS_CONSTRAIN_1_REG, SENSITIVE_CORE_X_DRAM0_PMS_CONSTRAIN_SRAM_WORLD_0_PMS_3, memprot_ll_dram0_set_permissions(r, w));
}

static inline void memprot_ll_dram0_get_permissions(uint32_t perms, bool *r, bool *w )
{
    *r = perms & SENSITIVE_CORE_X_DRAM0_PMS_CONSTRAIN_SRAM_WORLD_X_R;
    *w = perms & SENSITIVE_CORE_X_DRAM0_PMS_CONSTRAIN_SRAM_WORLD_X_W;
}

static inline void memprot_ll_dram0_get_pms_area_0(bool *r, bool *w)
{
    uint32_t permissions = REG_GET_FIELD(SENSITIVE_CORE_X_DRAM0_PMS_CONSTRAIN_1_REG, SENSITIVE_CORE_X_DRAM0_PMS_CONSTRAIN_SRAM_WORLD_0_PMS_0);
    memprot_ll_dram0_get_permissions(permissions, r, w);
}

static inline void memprot_ll_dram0_get_pms_area_1(bool *r, bool *w)
{
    uint32_t permissions = REG_GET_FIELD(SENSITIVE_CORE_X_DRAM0_PMS_CONSTRAIN_1_REG, SENSITIVE_CORE_X_DRAM0_PMS_CONSTRAIN_SRAM_WORLD_0_PMS_1);
    memprot_ll_dram0_get_permissions(permissions, r, w);
}

static inline void memprot_ll_dram0_get_pms_area_2(bool *r, bool *w)
{
    uint32_t permissions = REG_GET_FIELD(SENSITIVE_CORE_X_DRAM0_PMS_CONSTRAIN_1_REG, SENSITIVE_CORE_X_DRAM0_PMS_CONSTRAIN_SRAM_WORLD_0_PMS_2);
    memprot_ll_dram0_get_permissions(permissions, r, w);
}

static inline void memprot_ll_dram0_get_pms_area_3(bool *r, bool *w)
{
    uint32_t permissions = REG_GET_FIELD(SENSITIVE_CORE_X_DRAM0_PMS_CONSTRAIN_1_REG, SENSITIVE_CORE_X_DRAM0_PMS_CONSTRAIN_SRAM_WORLD_0_PMS_3);
    memprot_ll_dram0_get_permissions(permissions, r, w);
}

///////////////////////////////////
// DRAM0 - MONITOR

// 锁
static inline void memprot_ll_dram0_set_monitor_lock(void)
{
    REG_WRITE(SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_0_REG, 1);
}

static inline bool memprot_ll_dram0_get_monitor_lock(void)
{
    return REG_READ(SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_0_REG) == 1;
}

// 中断启用/清除
static inline void memprot_ll_dram0_set_monitor_en(bool enable)
{
    if (enable) {
        REG_SET_BIT(SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_1_REG, SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_VIOLATE_EN);
    } else {
        REG_CLR_BIT(SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_1_REG, SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_VIOLATE_EN);
    }
}

static inline bool memprot_ll_dram0_get_monitor_en(void)
{
    return REG_GET_BIT(SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_1_REG, SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_VIOLATE_EN) > 0;
}

static inline void memprot_ll_dram0_set_monitor_intrclr(void)
{
    REG_SET_BIT(SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_1_REG, SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_VIOLATE_CLR);
}

static inline void memprot_ll_dram0_reset_monitor_intrclr(void)
{
    REG_CLR_BIT(SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_1_REG, SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_VIOLATE_CLR);
}

static inline bool memprot_ll_dram0_get_monitor_intrclr(void)
{
    return REG_GET_BIT(SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_1_REG, SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_VIOLATE_CLR) > 0;
}

static inline uint32_t memprot_ll_dram0_get_monitor_enable_register(void)
{
    return REG_READ(SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_1_REG);
}

// 权限冲突状态
static inline uint32_t memprot_ll_dram0_get_monitor_status_intr(void)
{
    return REG_GET_FIELD(SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_2_REG, SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_VIOLATE_INTR);
}

static inline uint32_t memprot_ll_dram0_get_monitor_status_fault_lock(void)
{
    return REG_GET_FIELD(SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_2_REG, SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_VIOLATE_STATUS_LOCK);
}

static inline uint32_t memprot_ll_dram0_get_monitor_status_fault_world(void)
{
    return REG_GET_FIELD(SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_2_REG, SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_VIOLATE_STATUS_WORLD);
}

static inline uint32_t memprot_ll_dram0_get_monitor_status_fault_addr(void)
{
    uint32_t addr = REG_GET_FIELD(SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_2_REG, SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_VIOLATE_STATUS_ADDR);
    return addr > 0 ? (addr << I_D_FAULT_ADDR_SHIFT) + DRAM0_ADDRESS_LOW : 0;
}

static inline uint32_t memprot_ll_dram0_get_monitor_status_fault_wr(void)
{
    return REG_GET_FIELD(SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_3_REG, SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_VIOLATE_STATUS_WR);
}

static inline uint32_t memprot_ll_dram0_get_monitor_status_fault_byte_en(void)
{
    return REG_GET_FIELD(SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_2_REG, SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_VIOLATE_STATUS_BYTEEN);
}

static inline uint32_t memprot_ll_dram0_get_monitor_status_register_1(void)
{
    return REG_READ(SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_2_REG);
}

static inline uint32_t memprot_ll_dram0_get_monitor_status_register_2(void)
{
    return REG_READ(SENSITIVE_CORE_0_DRAM0_PMS_MONITOR_3_REG);
}

#ifdef __cplusplus
}
#endif

