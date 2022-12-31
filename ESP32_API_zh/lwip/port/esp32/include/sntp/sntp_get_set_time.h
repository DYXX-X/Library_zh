// 版权所有2021 Espressif Systems（Shanghai）PTE LTD
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

#ifndef __SNTP_GET_SET_TIME_H__
#define __SNTP_GET_SET_TIME_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * lwipopt中使用的函数声明。h重新定义默认sntp宏，例如：
 * - SNTP_UPDATE_DELAY()
 * - SNTP_SET_SYSTEM_TIME_US()
 * - SNTP_GET_SYSTEM_TIME()
 */

/*
 * @brief 获取SNTP操作的同步间隔esp_SNTP.c中IDF层提供了完整定义
 */
uint32_t sntp_get_sync_interval(void);

/**
 * @brief sntp模块中使用的系统时间设置器
 * @note lwip sntp使用u32_t类型作为sec和us参数
 */
void sntp_set_system_time(uint32_t sec, uint32_t us);

/**
 * @brief sntp模块中使用的系统时间getter
 * @note lwip sntp使用u32_t类型作为sec和us参数
 */
void sntp_get_system_time(uint32_t* sec, uint32_t* us);

#ifdef __cplusplus
}
#endif

#endif //__SNTP_GET_SET_TIME_H__

