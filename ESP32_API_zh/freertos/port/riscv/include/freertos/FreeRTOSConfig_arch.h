/*
    FreeRTOS V10-版权所有（C）2021 Real Time Engineers Ltd.保留所有权利

    访问http://www.FreeRTOS.org以确保您使用的是最新版本。

    此文件是FreeRTOS发行版的一部分。

    FreeRTOS是免费软件；您可以根据自由软件基金会发布的GNU通用公共许可证（第2版）条款重新分发和/或修改它>>！并由！修改<<FreeRTOS异常。

	*************************************************************************** >>! 注意：包括对GPL的修改，以允许您！分发一个包含FreeRTOS的组合作品，而不是！有义务提供专有组件的源代码！在FreeRTOS内核之外<<
	***************************************************************************
 FreeRTOS的发布是希望它有用，但没有任何保证；甚至没有适销性或特定用途适用性的隐含保证。完整许可文本可通过以下链接获得：http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS提供完全免费但专业开发的、*健壮、严格质量控制、受支持的跨平台软件，它不仅是市场领导者，而且是行业的实际标准。
     *                                                                       *
     *    通过购买FreeRTOS教程书、参考手册或两者，帮助您快速入门，同时帮助*支持FreeRTOS项目：http://www.FreeRTOS.org/Documentation 
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html-有问题吗？首先阅读常见问题解答页面“我的应用程序无法运行，可能有什么问题？”。您是否定义了configASSERT（）？

http://www.FreeRTOS.org/support-作为免费获得此顶级嵌入式软件的回报，我们请求您通过参加支持论坛来帮助我们的全球社区。

http://www.FreeRTOS.org/training-投资培训可以让您的团队尽早提高生产力。现在，您可以直接从实时工程师有限公司（Real Time Engineers Ltd）首席执行官理查德·巴里（Richard Barry）那里接受FreeRTOS培训，他是世界领先RTOS领域的世界权威。

    http://www.FreeRTOS.org/plus-一系列FreeRTOS生态系统产品，包括FreeRTOS+Trace（一种不可或缺的生产力工具）、DOS兼容的FAT文件系统以及我们的小型线程感知UDP/IP堆栈。

    http://www.FreeRTOS.org/labs-新的FreeRTOS产品将在哪里孵化。快来试试FreeRTOS+TCP，这是我们针对FreeRTOS的新开源TCP/IP堆栈。

    http://www.OpenRTOS.com-Real Time Engineers ltd.将FreeRTOS授权给High Integrity Systems ltd.，以OpenRTOS品牌进行销售。低成本OpenRTOS许可证提供了报价支持、赔偿和商业中间件。

    http://www.SafeRTOS.com-高完整性系统还提供安全工程和独立SIL3认证版本，用于需要可证明可靠性的安全和关键任务应用。

    1个制表符==4个空格！
*/

#ifndef FREERTOS_CONFIG_RISCV_H
#define FREERTOS_CONFIG_RISCV_H

// 此文件包含在常见的FreeRTOSConfig.h中。

#include "sdkconfig.h"

#define configUSE_PORT_OPTIMISED_TASK_SELECTION         0

#ifndef __ASSEMBLER__
#if CONFIG_IDF_TARGET_ESP32C3
#include "esp32c3/rom/ets_sys.h"
#elif CONFIG_IDF_TARGET_ESP32H2
#include "esp32h2/rom/ets_sys.h"
#endif
#endif // __ASSEMBLER__

/* FreeRTOS的最大中断优先级。org API函数。中断中只能使用以…FromISR（）结尾的API函数。*/
#define configMAX_SYSCALL_INTERRUPT_PRIORITY            0

#ifndef configISR_STACK_SIZE
#define configISR_STACK_SIZE                            (CONFIG_FREERTOS_ISR_STACKSIZE)
#endif

#ifndef __ASSEMBLER__
#if CONFIG_APPTRACE_SV_ENABLE
extern int xPortSwitchFlag;
#define os_task_switch_is_pended(_cpu_) (xPortSwitchFlag)
#else
#define os_task_switch_is_pended(_cpu_) (false)
#endif
#endif

#endif // FREERTOS_CONFIG_RISCV_H

