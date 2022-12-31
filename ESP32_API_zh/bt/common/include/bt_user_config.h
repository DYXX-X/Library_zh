// 版权所有2019 Espressif Systems（上海）私人有限公司
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

#ifndef __BT_USER_CONFIG_H__
#define __BT_USER_CONFIG_H__
#include "sdkconfig.h"

#define UC_TRACE_LEVEL_NONE                 0          /* 不生成跟踪消息*/
#define UC_TRACE_LEVEL_ERROR                1          /* 错误条件跟踪消息*/
#define UC_TRACE_LEVEL_WARNING              2          /* 警告条件跟踪消息*/
#define UC_TRACE_LEVEL_API                  3          /* API跟踪*/
#define UC_TRACE_LEVEL_EVENT                4          /* 事件的调试消息*/
#define UC_TRACE_LEVEL_DEBUG                5          /* 完整调试消息*/
#define UC_TRACE_LEVEL_VERBOSE              6          /* 详细调试消息*/

//DYNAMIC ENV ALLOCATOR
#ifdef CONFIG_BT_BLE_DYNAMIC_ENV_MEMORY
#define UC_BT_BLE_DYNAMIC_ENV_MEMORY            CONFIG_BT_BLE_DYNAMIC_ENV_MEMORY
#else
#define UC_BT_BLE_DYNAMIC_ENV_MEMORY            FALSE
#endif

#ifdef CONFIG_BT_STACK_NO_LOG
#define UC_BT_STACK_NO_LOG               CONFIG_BT_STACK_NO_LOG
#else
#define UC_BT_STACK_NO_LOG               FALSE
#endif

/**********************************************************
 * 线程/任务参考
 **********************************************************/
#ifdef CONFIG_BT_BLUEDROID_PINNED_TO_CORE
#define UC_TASK_PINNED_TO_CORE              (CONFIG_BT_BLUEDROID_PINNED_TO_CORE < portNUM_PROCESSORS ? CONFIG_BT_BLUEDROID_PINNED_TO_CORE : tskNO_AFFINITY)
#else
#define UC_TASK_PINNED_TO_CORE              (0)
#endif

#ifdef CONFIG_BT_BTC_TASK_STACK_SIZE
#define UC_BTC_TASK_STACK_SIZE              CONFIG_BT_BTC_TASK_STACK_SIZE
#else
#define UC_BTC_TASK_STACK_SIZE              4096
#endif

/**********************************************************
 * 跟踪引用
 **********************************************************/

#ifdef CONFIG_LOG_DEFAULT_LEVEL
#define UC_LOG_DEFAULT_LEVEL                CONFIG_LOG_DEFAULT_LEVEL
#else
#define UC_LOG_DEFAULT_LEVEL                3
#endif

#ifdef CONFIG_BOOTLOADER_LOG_LEVEL
#define UC_BOOTLOADER_LOG_LEVEL             CONFIG_BOOTLOADER_LOG_LEVEL
#else
#define UC_BOOTLOADER_LOG_LEVEL             3
#endif

#ifdef CONFIG_BT_LOG_BTC_TRACE_LEVEL
#define UC_BT_LOG_BTC_TRACE_LEVEL           CONFIG_BT_LOG_BTC_TRACE_LEVEL
#else
#define UC_BT_LOG_BTC_TRACE_LEVEL           UC_TRACE_LEVEL_WARNING
#endif

#ifdef CONFIG_BT_LOG_OSI_TRACE_LEVEL
#define UC_BT_LOG_OSI_TRACE_LEVEL           CONFIG_BT_LOG_OSI_TRACE_LEVEL
#else
#define UC_BT_LOG_OSI_TRACE_LEVEL           UC_TRACE_LEVEL_WARNING
#endif

#ifdef CONFIG_BT_LOG_BLUFI_TRACE_LEVEL
#define UC_BT_LOG_BLUFI_TRACE_LEVEL         CONFIG_BT_LOG_BLUFI_TRACE_LEVEL
#else
#define UC_BT_LOG_BLUFI_TRACE_LEVEL         UC_TRACE_LEVEL_WARNING
#endif

//BLUFI
#if  defined(CONFIG_BT_BLE_BLUFI_ENABLE) || defined(CONFIG_BT_NIMBLE_BLUFI_ENABLE)
#define UC_BT_BLUFI_ENABLE                  TRUE
#else
#define UC_BT_BLUFI_ENABLE                  FALSE
#endif

#endif /* __BT_USER_CONFIG_H__ */

