// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef _ROM_CACHE_H_
#define _ROM_CACHE_H_

#include "soc/dport_access.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup uart_api、uart配置和通信相关api
  * @brief uart api
  */

/** @addtogroup uart_api@{
  */

/**
  * @brief 初始化缓存mmu，将所有条目标记为无效。请不要在SDK应用程序中调用此函数。
  *
  * @param  int cpu_no:0表示PRO cpu，1表示APP cpu。
  *
  * @return 没有一个
  */
void mmu_init(int cpu_no);

/**
  * @brief 设置闪存缓存mmu映射。请不要在SDK应用程序中调用此函数。
  *
  * @param  int cpu_no:cpu编号，0表示PRO cpu，1表示APP cpu。
  *
  * @param  int pod：进程标识符。范围0~7。
  *
  * @param  unsigned int vaddr：CPU地址空间中的虚拟地址。可以是IRam0、IRam1、IRom0和DRom0内存地址。应按psize对齐。
  *
  * @param  unsigned int paddr：Flash中的物理地址。应按psize对齐。
  *
  * @param  int psize：闪存的页面大小，以KB为单位。这里应该是64。
  *
  * @param  int num：要设置的页面。
  *
  * @return unsigned int：错误状态0：mmu设置成功1：vaddr或paddr未对齐2：pid错误3：psize错误4：要写入的mmu表超出范围5：vadr超出范围
  */
static inline unsigned int IRAM_ATTR cache_flash_mmu_set(int cpu_no, int pid, unsigned int vaddr, unsigned int paddr,  int psize, int num)
{
    extern unsigned int cache_flash_mmu_set_rom(int cpu_no, int pid, unsigned int vaddr, unsigned int paddr,  int psize, int num);

    unsigned int ret;

    DPORT_STALL_OTHER_CPU_START();
    ret = cache_flash_mmu_set_rom(cpu_no, pid, vaddr, paddr, psize, num);
    DPORT_STALL_OTHER_CPU_END();

    return ret;
}

/**
  * @brief 设置Ext SRAM缓存mmu映射。请不要在SDK应用程序中调用此函数。
  *
  * 请注意，此代码存在于IRAM中，并具有与此函数的ROM版本相关的错误修复（错误地拒绝了vaddr>2MiB
  *
  * @param  int cpu_no:cpu编号，0表示PRO cpu，1表示APP cpu。
  *
  * @param  int pod：进程标识符。范围0~7。
  *
  * @param  unsigned int vaddr：CPU地址空间中的虚拟地址。可以是IRam0、IRam1、IRom0和DRom0内存地址。应按psize对齐。
  *
  * @param  unsigned int paddr：Ext SRAM中的物理地址。应按psize对齐。
  *
  * @param  int psize：闪存的页面大小，以KB为单位。这里应该是32岁。
  *
  * @param  int num：要设置的页面。
  *
  * @return unsigned int：错误状态0：mmu设置成功1：vaddr或paddr未对齐2：pid错误3：psize错误4：要写入的mmu表超出范围5：vadr超出范围
  */
unsigned int IRAM_ATTR cache_sram_mmu_set(int cpu_no, int pid, unsigned int vaddr, unsigned int paddr, int psize, int num);

/**
  * @brief 初始化cpu的缓存访问。请不要在SDK应用程序中调用此函数。
  *
  * @param  int cpu_no:0表示PRO cpu，1表示APP cpu。
  *
  * @return 没有一个
  */
static inline void IRAM_ATTR Cache_Read_Init(int cpu_no)
{
    extern void Cache_Read_Init_rom(int cpu_no);
    DPORT_STALL_OTHER_CPU_START();
    Cache_Read_Init_rom(cpu_no);
    DPORT_STALL_OTHER_CPU_END();
}

/**
  * @brief 刷新cpu的缓存值。请不要在SDK应用程序中调用此函数。
  *
  * @param  int cpu_no:0表示PRO cpu，1表示APP cpu。
  *
  * @return 没有一个
  */
static inline void IRAM_ATTR Cache_Flush(int cpu_no)
{
    extern void Cache_Flush_rom(int cpu_no);
    DPORT_STALL_OTHER_CPU_START();
    Cache_Flush_rom(cpu_no);
    DPORT_STALL_OTHER_CPU_END();
}

/**
  * @brief 禁用cpu的缓存访问。请不要在SDK应用程序中调用此函数。
  *
  * @param  int cpu_no:0表示PRO cpu，1表示APP cpu。
  *
  * @return 没有一个
  */
static inline void IRAM_ATTR Cache_Read_Disable(int cpu_no)
{
    extern void Cache_Read_Disable_rom(int cpu_no);
    DPORT_STALL_OTHER_CPU_START();
    Cache_Read_Disable_rom(cpu_no);
    DPORT_STALL_OTHER_CPU_END();
}

/**
  * @brief 为cpu启用缓存访问。请不要在SDK应用程序中调用此函数。
  *
  * @param  int cpu_no:0表示PRO cpu，1表示APP cpu。
  *
  * @return 没有一个
  */
static inline void IRAM_ATTR Cache_Read_Enable(int cpu_no)
{
    extern void Cache_Read_Enable_rom(int cpu_no);
    DPORT_STALL_OTHER_CPU_START();
    Cache_Read_Enable_rom(cpu_no);
    DPORT_STALL_OTHER_CPU_END();
}

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* _ROM_CACHE_H_ */

