// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
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

typedef enum {
    WDT_RWDT = 0,   /*!< RTC看门狗定时器（RWDT）*/
    WDT_MWDT0,      /*!< 定时器组0的主系统看门狗定时器（MWDT）*/
    WDT_MWDT1,      /*!< 定时器组1的主系统看门狗定时器（MWDT）*/
} wdt_inst_t;

/**
 * @brief 看门狗计时器的阶段。WDT有4个阶段。
 */
typedef enum {
    WDT_STAGE0 = 0,     /*!< 阶段0*/
    WDT_STAGE1 = 1,     /*!< 第1阶段*/
    WDT_STAGE2 = 2,     /*!< 第2阶段*/
    WDT_STAGE3 = 3      /*!< 第3阶段*/
} wdt_stage_t;

/**
 * @brief WDT阶段超时时的行为
 *
 * @note 这些枚举值应与相应的寄存器字段值兼容。
 */
typedef enum {
    WDT_STAGE_ACTION_OFF = 0,           /*!< 残废此阶段对系统没有影响。*/
    WDT_STAGE_ACTION_INT = 1,           /*!< 阶段到期时触发中断。*/
    WDT_STAGE_ACTION_RESET_CPU = 2,     /*!< 阶段到期时重置CPU核心。*/
    WDT_STAGE_ACTION_RESET_SYSTEM = 3,  /*!< 阶段结束时重置主系统。这包括CPU和所有外围设备。RTC为异常，不会重置。*/
    WDT_STAGE_ACTION_RESET_RTC = 4,     /*!< 阶段到期时重置主系统和RTC。仅适用于RWDT*/
} wdt_stage_action_t;

/**
 * @brief CPU或系统复位信号的长度
 *
 * @note 这些枚举值应与相应的寄存器字段值兼容。
 */
typedef enum {
    WDT_RESET_SIG_LENGTH_100ns = 0,    /*!< 100纳秒*/
    WDT_RESET_SIG_LENGTH_200ns = 1,    /*!< 200纳秒*/
    WDT_RESET_SIG_LENGTH_300ns = 2,    /*!< 300纳秒*/
    WDT_RESET_SIG_LENGTH_400ns = 3,    /*!< 400纳秒*/
    WDT_RESET_SIG_LENGTH_500ns = 4,    /*!< 500纳秒*/
    WDT_RESET_SIG_LENGTH_800ns = 5,    /*!< 800纳秒*/
    WDT_RESET_SIG_LENGTH_1_6us = 6,    /*!< 1.6美元*/
    WDT_RESET_SIG_LENGTH_3_2us = 7     /*!< 3.2我们*/
} wdt_reset_sig_length_t;


#ifdef __cplusplus
}
#endif

