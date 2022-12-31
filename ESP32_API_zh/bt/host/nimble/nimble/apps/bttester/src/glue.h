/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef __GLUE_H__
#define __GLUE_H__

#include "os/endian.h"

#define u8_t    uint8_t
#define s8_t    int8_t
#define u16_t   uint16_t
#define u32_t   uint32_t
#define s32_t   int32_t

#ifndef BIT
#define BIT(n)  (1UL << (n))
#endif

#define __packed    __attribute__((__packed__))

#define sys_le16_to_cpu le16toh

struct bt_data {
    u8_t type;
    u8_t data_len;
    const u8_t *data;
};

#define BT_DATA(_type, _data, _data_len) \
    { \
        .type = (_type), \
        .data_len = (_data_len), \
        .data = (const u8_t *)(_data), \
    }

struct os_mbuf * NET_BUF_SIMPLE(uint16_t size);
void net_buf_simple_init(struct os_mbuf *buf, size_t reserve_head);
void net_buf_simple_add_le16(struct os_mbuf *om, uint16_t val);
void net_buf_simple_add_u8(struct os_mbuf *om, uint8_t val);
void *net_buf_simple_add(struct os_mbuf *om, uint8_t len);
uint8_t *net_buf_simple_push(struct os_mbuf *om, uint8_t len);

#define net_buf_simple_add_mem(a,b,c) os_mbuf_append(a,b,c)

const char *bt_hex(const void *buf, size_t len);

#endif /* __GLUE_H__ */

