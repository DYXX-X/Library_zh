/*******************************************************************************
//版权所有（c）2003-2015 Cadence Design Systems，Inc.////特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权限，包括//但不限于使用、复制、修改、合并、发布、//分发、再许可和/或销售软件副本的权利，和//允许向其提供软件的人员这样做，但须遵守以下conditions:////上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。////软件按“原样”提供，无任何明示或暗示的保证，包括但不限于适销性、适用于特定用途和非侵权性的保证。//在任何情况下，作者或版权持有人均不对因软件或软件的使用或其他交易而产生的任何索赔、损害或其他责任负责，无论是在合同诉讼、侵权诉讼或其他诉讼中。
--------------------------------------------------------------------------------
*/

/*
 * 该实用程序有助于对中断延迟和上下文开关进行基准测试。为了启用它，请在FreeRTOSConfig.h中将configBENCHMARK设置为1。您还需要下载包含portbenchmark的FreeRTOS_trace补丁。c和portbenchmark.h的完整版本
 */

#ifndef PORTBENCHMARK_H
#define PORTBENCHMARK_H

#if configBENCHMARK
    #error "You need to download the FreeRTOS_trace patch that overwrites this file"
#endif

#define portbenchmarkINTERRUPT_DISABLE()
#define portbenchmarkINTERRUPT_RESTORE(newstate)
#define portbenchmarkIntLatency()
#define portbenchmarkIntWait()
#define portbenchmarkReset()
#define portbenchmarkPrint()

#endif /* PORTBENCHMARK */

