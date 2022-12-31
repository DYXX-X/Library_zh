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

/* 注意：1.将所有任务优先级和堆栈大小定义放在此文件中2.如果任务优先级小于10，请使用ESP_task_PRIO_MIN+X样式，否则使用ESP_TATK_PRIO_MAX-X样式3.如果这是一个守护程序任务，则宏前缀为ESP_TASKD_，否则为ESP_task_4。如果修改了configMAX_PRIORITIES，请将所有优先级设置为大于0 5。确保ESP_task。h在wifi lib和idf 6之间是一致的。如果更改系统任务优先级，请检查/api guides/performance/speed中记录的值。rst是最新的
 */

#ifndef _ESP_TASK_H_
#define _ESP_TASK_H_

#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSConfig.h"

#define ESP_TASK_PRIO_MAX (configMAX_PRIORITIES)
#define ESP_TASK_PRIO_MIN (0)

/* Bt控制器任务*/
/* 控制器*/
#define ESP_TASK_BT_CONTROLLER_PRIO   (ESP_TASK_PRIO_MAX - 2)
#ifdef CONFIG_NEWLIB_NANO_FORMAT
#define TASK_EXTRA_STACK_SIZE      (0)
#else
#define TASK_EXTRA_STACK_SIZE      (512)
#endif

#define BT_TASK_EXTRA_STACK_SIZE      TASK_EXTRA_STACK_SIZE
#define ESP_TASK_BT_CONTROLLER_STACK  (3584 + TASK_EXTRA_STACK_SIZE)


/* idf任务*/
#define ESP_TASK_TIMER_PRIO           (ESP_TASK_PRIO_MAX - 3)
#define ESP_TASK_TIMER_STACK          (CONFIG_ESP_TIMER_TASK_STACK_SIZE +  TASK_EXTRA_STACK_SIZE)
#define ESP_TASKD_EVENT_PRIO          (ESP_TASK_PRIO_MAX - 5)
#if CONFIG_LWIP_TCPIP_CORE_LOCKING
#define ESP_TASKD_EVENT_STACK         (CONFIG_ESP_SYSTEM_EVENT_TASK_STACK_SIZE + TASK_EXTRA_STACK_SIZE + 2048)
#else
#define ESP_TASKD_EVENT_STACK         (CONFIG_ESP_SYSTEM_EVENT_TASK_STACK_SIZE + TASK_EXTRA_STACK_SIZE)
#endif /* CONFIG_LWIP_TCPIP_CORE_LOCKING */
#define ESP_TASK_TCPIP_PRIO           (ESP_TASK_PRIO_MAX - 7)
#define ESP_TASK_TCPIP_STACK          (CONFIG_LWIP_TCPIP_TASK_STACK_SIZE + TASK_EXTRA_STACK_SIZE)
#define ESP_TASK_MAIN_PRIO            (ESP_TASK_PRIO_MIN + 1)
#define ESP_TASK_MAIN_STACK           (CONFIG_ESP_MAIN_TASK_STACK_SIZE + TASK_EXTRA_STACK_SIZE)
#define ESP_TASK_MAIN_CORE            CONFIG_ESP_MAIN_TASK_AFFINITY

#endif

