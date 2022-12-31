// 版权所有2015-2020 Espressif Systems（上海）私人有限公司
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

#pragma once

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief 将主CPU从睡眠或深度睡眠中唤醒。
 *
 * 如果主CPU被配置为ULP作为唤醒源，调用此函数将使主CPU退出休眠或深度休眠，这将引发软件中断信号。
 */
void ulp_riscv_wakeup_main_processor(void);

/**
 * @brief 将cpu从监视器模式中恢复
 *
 * 此函数取消ULP-RISC-V的低功耗模式，应在协处理器每次启动时调用。
 *
 * @note 为了方便起见，在启动代码中自动调用此函数。
 */
void ulp_riscv_rescue_from_monitor(void);

/**
 * @brief 完成ULP程序并关闭ULP，直到下次唤醒。
 *
 * @note 此函数不返回。调用后，它将完全重置ULP。
 *
 * @note 从ULP程序中的main（）返回将导致调用此函数。
 *
 * 该函数应在ULP程序完成处理后调用，它将触发下一次唤醒的计时器，将ULP置于监控模式并触发重置。
 *
 */
void __attribute__((noreturn)) ulp_riscv_shutdown(void);

#define ULP_RISCV_GET_CCOUNT()	({ int __ccount; \
				asm volatile("rdcycle %0;" : "=r"(__ccount)); \
				__ccount; })


/* 这些只是近似的默认数字，在默认DCAP设置下，8M振荡器的默认频率为8.5MHz+/-5%
*/
#define ULP_RISCV_CYCLES_PER_US 8.5
#define ULP_RISCV_CYCLES_PER_MS ULP_RISCV_CYCLES_PER_US*1000

/**
 * @brief 使协处理器忙碌等待一定数量的周期
 *
 * @param cycles 忙碌等待的周期数
 */
void ulp_riscv_delay_cycles(uint32_t cycles);

#ifdef __cplusplus
}
#endif

