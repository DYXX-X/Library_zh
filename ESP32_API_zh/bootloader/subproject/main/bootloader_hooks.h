// 版权所有2015-2021 Espressif Systems（Shanghai）PTE LTD
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

#ifndef BOOTLOADER_HOOKS_H
#define BOOTLOADER_HOOKS_H

/**
 * @file 第二阶段引导加载程序可以被应用程序覆盖或完成。这里声明的函数是弱的，因此，如果需要，可以由用户项目定义。有关此功能的详细信息，请查看`custom_bootloader`ESP-IDF示例。
 */


/**
 * @brief 在第二阶段引导加载程序初始化之前*执行的函数（如果提供）。
 */
void __attribute__((weak)) bootloader_before_init(void);

/**
 * @brief 在*第二阶段引导加载程序初始化之后*执行的函数（如果提供）。
 */
void __attribute__((weak)) bootloader_after_init(void);

#endif // BOOTLOADER_HOOKS_H

