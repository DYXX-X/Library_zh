/******************************************************************************
 * 版权所有（C）2014谷歌公司。
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

#ifndef _HCI_HAL_H_
#define _HCI_HAL_H_

#include <stdbool.h>
#include <stdint.h>

#include "stack/bt_types.h"

typedef enum {
    DATA_TYPE_COMMAND = 1,
    DATA_TYPE_ACL     = 2,
    DATA_TYPE_SCO     = 3,
    DATA_TYPE_EVENT   = 4
} serial_data_type_t;

typedef void (*packet_ready_cb)(BT_HDR *packet);

typedef struct {
    // 当HAL检测到入站数据时调用。
    // 数据|类型|可以是ACL、SCO或EVENT。
    // 在提供给|init|的线程上下文中执行。
    packet_ready_cb packet_ready;

    /*
    //当HAL检测到名为Dave的入境宇航员时调用。//在此之后，HAL将拒绝所有打开吊舱舱门的请求。dave_ready_cb dave_ready；
    */
} hci_hal_callbacks_t;

typedef struct hci_hal_t {
    // 初始化HAL，使用|upper_callbacks|和|upper_thread|在的上下文中运行。
    //bool（*init）（常量hci_hal_callback_t*upper_callbacks）；

    // 连接到底层硬件，让数据开始流动。
    bool (*open)(const hci_hal_callbacks_t *upper_callbacks,  void *task_thread);
    // 断开与底层硬件的连接，并关闭HAL。
    // “黛西，黛西…”
    void (*close)(void);

    // 将ACL、SCO或EVENT数据包的最大|max_size|字节检索到
    // |buffer|，如果|block|为true，则阻塞直到读取max_size字节。
    // 仅保证在data_ready回调上下文中正确
    // 对应类型的。
    //size_t（*read_data）（serial_data_type_t类型，uint8_t*缓冲区，size_t max_size）；
    // 上层必须调用此命令以通知HAL其已完成
    // 读取指定|类型|的数据包。基础实现
    // 对多个数据类型使用共享通道取决于此以了解何时
    // 以重新解释数据流。
    //void（*packet_finished）（serial_data_type_t类型）；
    // 传输COMMAND、ACL或SCO数据包。
    // |data|不能为NULL|长度|必须大于零。
    //
    // IMPORTANT NOTE:
    // 根据底层实现，字节右侧
    // 在此调用期间可以借用|data|的开头
    // 然后恢复到其原始值。
    // 这在蓝牙环境中是安全的，因为总是有缓冲区
    // 标题，它是您发送的数据的前缀。
    uint16_t (*transmit_data)(serial_data_type_t type, uint8_t *data, uint16_t length);
} hci_hal_t;


// 获取为编译的正确hal实现。
const hci_hal_t *hci_hal_h4_get_interface(void);

#endif /* _HCI_HAL_H */

