// 版权所有2015-2018 Espressif Systems（上海）私人有限公司
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

#ifndef __ESP_INT_WDT_H
#define __ESP_INT_WDT_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup 看门狗_API@{
  */

/*
此例程使看门狗能够捕获进程禁用中断时间过长或中断处理程序中的代码耗时过长的实例。它通过设置一个看门狗来实现这一点，该看门狗从FreeRTOStack开关中断得到反馈。当这个看门狗超时时，最初它将调用一个高级中断例程，使FreeRTOS死机，以便对两个CPU的状态进行法医检查。当未调用此中断处理程序且看门狗再次超时时，它将重置SoC。

这使用TIMERG1 WDT。
*/


/**
  * @brief  初始化中断监视器的非CPU特定部分。如果在menuconfig中启用了中断看门狗，则在初始化代码中调用该命令。
  *
  */
void esp_int_wdt_init(void);

/**
  * @brief  启用当前CPU上的中断监视器。如果在menuconfig中启用了中断监视器，则这两个CPU都会在初始化代码中调用。
  *
  */
void esp_int_wdt_cpu_init(void);



/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif

