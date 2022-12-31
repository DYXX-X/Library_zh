/******************************************************************************
 * @file     mpu_armv8.小时
 * @brief    用于Armv8-M和Armv8.1-M MPU的CMSIS MPU API
 * @version  V5.1.0
 * @date     2019年3月8日
 ******************************************************************************/
/*
 * 版权所有（c）2017-2019 Arm Limited。保留所有权利。
 *
 * SPDX许可证标识符：Apache-2.0
 *
 * 根据Apache许可证2.0版（许可证）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按原样分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */
 /* 版权所有（c）2019 Dialog Semiconductor修改*/

#if   defined ( __ICCARM__ )
  #pragma system_include         /* 将文件视为MISRA检查的系统包含文件*/
#elif defined (__clang__)
  #pragma clang system_header    /* 将文件视为系统包含文件*/
#endif

#ifndef ARM_MPU_ARMV8_H
#define ARM_MPU_ARMV8_H

/**\设备内存的brief属性（仅外部）*/
#define ARM_MPU_ATTR_DEVICE                           ( 0U )

/**\不可缓存的普通内存的brief属性*/
#define ARM_MPU_ATTR_NON_CACHEABLE                    ( 4U )

/** \正常内存（外部和内部）的brief属性\param NT Non-Transient：非瞬态数据设置为1。\param WB回写：设置为1以使用回写更新策略。\param RA Read Allocation：设置为1以在读取未命中时使用缓存分配。\param WA Write Allocation:设置为1，以在写入未命中时启用缓存分配。
*/
#define ARM_MPU_ATTR_MEMORY_(NT, WB, RA, WA) \
  (((NT & 1U) << 3U) | ((WB & 1U) << 2U) | ((RA & 1U) << 1U) | (WA & 1U))

/**\ brief设备内存类型非收集、非重新排序、非早期写入确认*/
#define ARM_MPU_ATTR_DEVICE_nGnRnE (0U)

/**\ brief设备内存类型非收集、非重新排序、早期写入确认*/
#define ARM_MPU_ATTR_DEVICE_nGnRE  (1U)

/**\ brief设备内存类型非收集、重新排序、早期写入确认*/
#define ARM_MPU_ATTR_DEVICE_nGRE   (2U)

/**\ brief设备内存类型收集、重新排序、早期写入确认*/
#define ARM_MPU_ATTR_DEVICE_GRE    (3U)

/** \简要内存属性\param O外部内存属性\pram I O==ARM_MPU_ATTR_DEVICE：设备内存属性，否则：内部内存属性
*/
#define ARM_MPU_ATTR(O, I) (((O & 0xFU) << 4U) | (((O & 0xFU) != 0U) ? (I & 0xFU) : ((I & 0x3U) << 2U)))

/**\brief普通内存不可共享*/
#define ARM_MPU_SH_NON   (0U)

/**\brief普通内存外部可共享*/
#define ARM_MPU_SH_OUTER (2U)

/**\brief普通内存内部可共享*/
#define ARM_MPU_SH_INNER (3U)

/** \brief Memory access permissions\param RO Read Only：只读内存设置为1。\param NP Non-Privileged：对于非特权内存，设置为1。
*/
#define ARM_MPU_AP_(RO, NP) (((RO & 1U) << 1U) | (NP & 1U))

/** \brief Region Base Address Register value \param Base内存区域的基本地址位[31:5]。该值为零扩展。有效地址对齐32字节。\param SH定义此内存区域的可共享性域。\param RO只读：只读内存区域设置为1。\param NP Non-Privileged：对于非特权内存区域，设置为1。\param XN eXecute Never：对于不可执行的内存区域，设置为1。
*/
#define ARM_MPU_RBAR(BASE, SH, RO, NP, XN) \
  ((BASE & MPU_RBAR_BASE_Msk) | \
  ((SH << MPU_RBAR_SH_Pos) & MPU_RBAR_SH_Msk) | \
  ((ARM_MPU_AP_(RO, NP) << MPU_RBAR_AP_Pos) & MPU_RBAR_AP_Msk) | \
  ((XN << MPU_RBAR_XN_Pos) & MPU_RBAR_XN_Msk))

/** \brief Region Limit Address Register value \param Limit此内存区域的限制地址位[31:5]。该值是一个扩展值。\param IDX与此内存区域关联的属性索引。
*/
#define ARM_MPU_RLAR(LIMIT, IDX) \
  ((LIMIT & MPU_RLAR_LIMIT_Msk) | \
  ((IDX << MPU_RLAR_AttrIndx_Pos) & MPU_RLAR_AttrIndx_Msk) | \
  (MPU_RLAR_EN_Msk))

#if defined(MPU_RLAR_PXN_Pos)
  
/** \brief Region Limit Address Register with PXN value \param Limit此内存区域的限制地址位[31:5]。该值是一个扩展值。\param PXN特权从不执行。定义是否可以从此特权区域执行代码。\param IDX与此内存区域关联的属性索引。
*/
#define ARM_MPU_RLAR_PXN(LIMIT, PXN, IDX) \
  ((LIMIT & MPU_RLAR_LIMIT_Msk) | \
  ((PXN << MPU_RLAR_PXN_Pos) & MPU_RLAR_PXN_Msk) | \
  ((IDX << MPU_RLAR_AttrIndx_Pos) & MPU_RLAR_AttrIndx_Msk) | \
  (MPU_RLAR_EN_Msk))
  
#endif

/**
* 单个MPU区域的结构
*/
typedef struct {
  uint32_t RBAR;                   /*!< 区域基址寄存器值*/
  uint32_t RLAR;                   /*!< 区域限制地址寄存器值*/
} ARM_MPU_Region_t;
    
/** 启用MPU。\param MPU_Control未配置区域的默认访问权限。
*/
__STATIC_INLINE void ARM_MPU_Enable(uint32_t MPU_Control)
{
  MPU->CTRL = MPU_Control | MPU_CTRL_ENABLE_Msk;
#ifdef SCB_SHCSR_MEMFAULTENA_Msk
  SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk;
#endif
  __DSB();
  __ISB();
}

/** 禁用MPU。
*/
__STATIC_INLINE void ARM_MPU_Disable(void)
{
  __DMB();
#ifdef SCB_SHCSR_MEMFAULTENA_Msk
  SCB->SHCSR &= ~SCB_SHCSR_MEMFAULTENA_Msk;
#endif
  MPU->CTRL  &= ~MPU_CTRL_ENABLE_Msk;
}

#ifdef MPU_NS
/** 启用非安全MPU。\param MPU_Control未配置区域的默认访问权限。
*/
__STATIC_INLINE void ARM_MPU_Enable_NS(uint32_t MPU_Control)
{
  MPU_NS->CTRL = MPU_Control | MPU_CTRL_ENABLE_Msk;
#ifdef SCB_SHCSR_MEMFAULTENA_Msk
  SCB_NS->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk;
#endif
  __DSB();
  __ISB();
}

/** 禁用非安全MPU。
*/
__STATIC_INLINE void ARM_MPU_Disable_NS(void)
{
  __DMB();
#ifdef SCB_SHCSR_MEMFAULTENA_Msk
  SCB_NS->SHCSR &= ~SCB_SHCSR_MEMFAULTENA_Msk;
#endif
  MPU_NS->CTRL  &= ~MPU_CTRL_ENABLE_Msk;
}
#endif

/** 将内存属性编码设置为给定的MPU。\param mpu指向要配置的mpu的指针。\param idx要设置的属性索引[0-7]\param attr要设置的特性值。
*/
__STATIC_INLINE void ARM_MPU_SetMemAttrEx(MPU_Type* mpu, uint8_t idx, uint8_t attr)
{
  const uint8_t reg = idx / 4U;
  const uint32_t pos = ((idx % 4U) * 8U);
  const uint32_t mask = 0xFFU << pos;
  
  if (reg >= (sizeof(mpu->MAIR) / sizeof(mpu->MAIR[0]))) {
    return; // 无效索引
  }
  
  mpu->MAIR[reg] = ((mpu->MAIR[reg] & ~mask) | ((attr << pos) & mask));
}

/** 设置内存属性编码。\param idx要设置的属性索引[0-7]\param attr要设置的特性值。
*/
__STATIC_INLINE void ARM_MPU_SetMemAttr(uint8_t idx, uint8_t attr)
{
  ARM_MPU_SetMemAttrEx(MPU, idx, attr);
}

#ifdef MPU_NS
/** 将内存属性编码设置为非安全MPU。\param idx要设置的属性索引[0-7]\param attr要设置的特性值。
*/
__STATIC_INLINE void ARM_MPU_SetMemAttr_NS(uint8_t idx, uint8_t attr)
{
  ARM_MPU_SetMemAttrEx(MPU_NS, idx, attr);
}
#endif

/** 清除并禁用给定MPU的给定MPU区域。\param mpu指向要使用的mpu的指针。\param rnr要清除的区域编号。
*/
__STATIC_INLINE void ARM_MPU_ClrRegionEx(MPU_Type* mpu, uint32_t rnr)
{
  mpu->RNR = rnr;
  mpu->RLAR = 0U;
}

/** 清除并禁用给定的MPU区域。\param rnr要清除的区域编号。
*/
__STATIC_INLINE void ARM_MPU_ClrRegion(uint32_t rnr)
{
  ARM_MPU_ClrRegionEx(MPU, rnr);
}

#ifdef MPU_NS
/** 清除并禁用给定的非安全MPU区域。\param rnr要清除的区域编号。
*/
__STATIC_INLINE void ARM_MPU_ClrRegion_NS(uint32_t rnr)
{  
  ARM_MPU_ClrRegionEx(MPU_NS, rnr);
}
#endif

/** 配置给定MPU的给定MPU区域。\param mpu指向要使用的mpu的指针。\param rnr要配置的区域编号。\param rbar rbar寄存器的值。\param rlar rlar寄存器的值。
*/   
__STATIC_INLINE void ARM_MPU_SetRegionEx(MPU_Type* mpu, uint32_t rnr, uint32_t rbar, uint32_t rlar)
{
  mpu->RNR = rnr;
  mpu->RBAR = rbar;
  mpu->RLAR = rlar;
}

/** 配置给定的MPU区域。\param rnr要配置的区域编号。\param rbar rbar寄存器的值。\param rlar rlar寄存器的值。
*/   
__STATIC_INLINE void ARM_MPU_SetRegion(uint32_t rnr, uint32_t rbar, uint32_t rlar)
{
  ARM_MPU_SetRegionEx(MPU, rnr, rbar, rlar);
}

#ifdef MPU_NS
/** 配置给定的非安全MPU区域。\param rnr要配置的区域编号。\param rbar rbar寄存器的值。\param rlar rlar寄存器的值。
*/   
__STATIC_INLINE void ARM_MPU_SetRegion_NS(uint32_t rnr, uint32_t rbar, uint32_t rlar)
{
  ARM_MPU_SetRegionEx(MPU_NS, rnr, rbar, rlar);  
}
#endif

/** 具有严格有序内存访问的Memcopy，例如用于寄存器目标。\param dst目标数据复制到。\param src源数据复制自。\param len要复制的数据字的数量。
*/
__STATIC_INLINE void ARM_MPU_OrderedMemcpy(volatile uint32_t* dst, const uint32_t* __RESTRICT src, uint32_t len)
{
  uint32_t i;
  for (i = 0U; i < len; ++i) 
  {
    dst[i] = src[i];
  }
}

/** 将给定数量的MPU区域从表加载到给定的MPU。\param mpu指向要使用的mpu寄存器的指针。\param rnr要配置的第一个区域编号。\param table指向MPU配置表的指针。\param cnt要配置的区域数量。
*/
__STATIC_INLINE void ARM_MPU_LoadEx(MPU_Type* mpu, uint32_t rnr, ARM_MPU_Region_t const* table, uint32_t cnt) 
{
  const uint32_t rowWordSize = sizeof(ARM_MPU_Region_t)/4U;
  if (cnt == 1U) {
    mpu->RNR = rnr;
    ARM_MPU_OrderedMemcpy(&(mpu->RBAR), &(table->RBAR), rowWordSize);
  } else {
    uint32_t rnrBase   = rnr & ~(MPU_TYPE_RALIASES-1U);
    uint32_t rnrOffset = rnr % MPU_TYPE_RALIASES;
    
    mpu->RNR = rnrBase;
    while ((rnrOffset + cnt) > MPU_TYPE_RALIASES) {
      uint32_t c = MPU_TYPE_RALIASES - rnrOffset;
      ARM_MPU_OrderedMemcpy(&(mpu->RBAR)+(rnrOffset*2U), &(table->RBAR), c*rowWordSize);
      table += c;
      cnt -= c;
      rnrOffset = 0U;
      rnrBase += MPU_TYPE_RALIASES;
      mpu->RNR = rnrBase;
    }
    
    ARM_MPU_OrderedMemcpy(&(mpu->RBAR)+(rnrOffset*2U), &(table->RBAR), cnt*rowWordSize);
  }
}

/** 从表中加载给定数量的MPU区域。\param rnr要配置的第一个区域编号。\param table指向MPU配置表的指针。\param cnt要配置的区域数量。
*/
__STATIC_INLINE void ARM_MPU_Load(uint32_t rnr, ARM_MPU_Region_t const* table, uint32_t cnt) 
{
  ARM_MPU_LoadEx(MPU, rnr, table, cnt);
}

#ifdef MPU_NS
/** 将给定数量的MPU区域从表加载到非安全MPU。\param rnr要配置的第一个区域编号。\param table指向MPU配置表的指针。\param cnt要配置的区域数量。
*/
__STATIC_INLINE void ARM_MPU_Load_NS(uint32_t rnr, ARM_MPU_Region_t const* table, uint32_t cnt) 
{
  ARM_MPU_LoadEx(MPU_NS, rnr, table, cnt);
}
#endif

#endif


