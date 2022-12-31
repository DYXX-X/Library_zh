// 版权所有2019-2020 Espressif Systems（上海）私人有限公司
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

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// USB持久性标志。

//此位表示已启用持久性，即USB初始化例程不应
//重置USB设备，因为设备仍处于初始化状态，并且主机使用相同的cdcacm/dfu检测到该设备
//ROM使用的描述符；我们只需要重新初始化软件端，就可以了。
#define USBDC_PERSIST_ENA (1<<31)

//该位向ROM指示，由于进入DFU模式的请求，我们重新启动；ROM应
//遵守这一要求。
#define USBDC_BOOT_DFU (1<<30)


//非0表示存储“遗嘱”的内存位置，也就是应该输出的一段文本
//重新启动后。可以包含核心转储信息或其他信息。
#define USBDC_TESTAMENT_LOC_MASK 0x7FFFF //位19-0；这被添加到0x3FF80000的基地址。

//遗嘱是先进先出的。ROM将输出文本开始和文本结束之间的所有数据；如果textend低于textstart，它将
//输出从textstart到memend，然后memstart到textend的所有内容。
typedef struct {
    char *memstart; //存储区开始
    char *memend;   //存储区结束
    char *textstart; //要输出的文本的开头
    char *textend;
} usbdc_testament_t;

#ifdef __cplusplus
}
#endif

