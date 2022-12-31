// 版权所有2018-2019 Espressif Systems（Shanghai）PTE LTD
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


#ifndef _PERF_MON_ACCESS_H_
#define _PERF_MON_ACCESS_H_

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "esp_log.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**@{*/
/**
 * @brief      初始化性能监视器
 *
 * 使用定义值初始化性能监视器寄存器
 *
 * @param[in] id: 性能计数器编号
 * @param[in] select: 从PMCTRLx寄存器中选择值
 * @param[in] mask: PMCTRLx寄存器的掩码值
 * @param[in] kernelcnt: PMCTRLx寄存器的kernelcnt值
 * @param[in] tracelevel: PMCTRLx寄存器的跟踪级别值
 *
 * @return
 *      -成功时ESP_OK
 *      -如果其中一个参数不正确，则返回ESP_ERR_INVALID_ARG
 */
esp_err_t xtensa_perfmon_init(int id, uint16_t select, uint16_t mask, int kernelcnt, int tracelevel);
/**@}*/

/**@{*/
/**
 * @brief      重置PM计数器
 *
 * 重置PM计数器。将0写入PMx寄存器。
 *
 * @param[in] id: 性能计数器编号
 *
 * @return
 *      -成功时ESP_OK
 *      -如果id超出范围，则为ESP_ERR_INVALID_ARG
 */
esp_err_t xtensa_perfmon_reset(int id);
/**@}*/

/**@{*/
/**
 * @brief      启动PM计数器
 *
 * 同步启动所有PM计数器。将1写入PGM寄存器
 */
void xtensa_perfmon_start(void);
/**@}*/

/**@{*/
/**
 * @brief      停止PM计数器
 *
 * 同步停止所有PM计数器。将0写入PGM寄存器
 */
void xtensa_perfmon_stop(void);
/**@}*/

/**@{*/
/**
 * @brief      读取PM计数器
 *
 * 读取已定义PM计数器的值。
 *
 * @param[in] id: 性能计数器编号
 *
 * @return
 *      -性能计数器值
 */
uint32_t xtensa_perfmon_value(int id);
/**@}*/

/**@{*/
/**
 * @brief      读取PM溢出状态
 *
 * 读取已定义PM计数器的溢出值。
 *
 * @param[in] id: 性能计数器编号
 *
 * @return
 *      -如果没有溢出（溢出=0），则ESP_OK
 *      -如果发生溢出（溢出=1），则返回ESP_FAIL
 */
esp_err_t xtensa_perfmon_overflow(int id);
/**@}*/

/**@{*/
/**
 * @brief      转储PM值
 *
 * 将所有PM寄存器转储到控制台。
 *
 */
void xtensa_perfmon_dump(void);
/**@}*/


#ifdef __cplusplus
}
#endif

#endif // _PERF_MON_ACCESS_H_

