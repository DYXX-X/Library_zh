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

#ifndef _PACKET_FRAGMENTER_H_
#define _PACKET_FRAGMENTER_H_

#include "osi/allocator.h"
#include "stack/bt_types.h"
#include "hci/hci_layer.h"

typedef void (*transmit_finished_cb)(BT_HDR *packet, bool all_fragments_sent);
typedef void (*packet_reassembled_cb)(BT_HDR *packet);
typedef void (*packet_fragmented_cb)(BT_HDR *packet, bool send_transmit_finished);

typedef struct {
    // 为每个数据包片段调用。
    packet_fragmented_cb fragmented;

    // 为每个完全重新组装的数据包调用。
    packet_reassembled_cb reassembled;

    // 当碎片器完成发送所有请求的碎片时调用，
    // 但是该分组尚未被完全发送。
    transmit_finished_cb transmit_finished;
} packet_fragmenter_callbacks_t;

typedef struct packet_fragmenter_t {
    // 初始化碎片程序，指定|result_callbacks|。
    void (*init)(const packet_fragmenter_callbacks_t *result_callbacks);

    // 释放与碎片程序关联的所有资源。
    void (*cleanup)(void);

    // 检查Current fragmenter是否正在进行
    BT_HDR *(*fragment_current_packet)(void);

    // 如果需要，碎片|数据包|并将所有内容交给碎片回调。
    void (*fragment_and_dispatch)(BT_HDR *packet);
    // 如果|package|是一个完整的数据包，则转发到重新组合的回调。否则
    // 直到所有片段到达，此时调用重新组合的回调
    // 重新组合的数据。
    void (*reassemble_and_dispatch)(BT_HDR *packet);
} packet_fragmenter_t;

const packet_fragmenter_t *packet_fragmenter_get_interface(void);

#endif /* _PACKET_FRAGMENTER_H_ */

