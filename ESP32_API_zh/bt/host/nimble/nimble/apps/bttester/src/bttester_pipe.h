/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef __BTTESTER_PIPE_H__
#define __BTTESTER_PIPE_H__

#include <stdlib.h>
#include "bttester.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef u8_t *(*bttester_pipe_recv_cb)(u8_t *buf, size_t *off);
void bttester_pipe_register(u8_t *buf, size_t len, bttester_pipe_recv_cb cb);
int bttester_pipe_send(const u8_t *data, int len);
int bttester_pipe_send_buf(struct os_mbuf *buf);
int bttester_pipe_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __BTTESTER_PIPE_H__ */

