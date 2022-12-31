/*
 * SPDX文件版权所有文本：2016 Cesanta Software Limited
 *
 * SPDX许可证标识符：GPL-2.0或
 *
 * SPDX文件贡献者：2016-2022 Espressif Systems（上海）有限公司
 */

#ifndef SLIP_H_
#define SLIP_H_

#include <stdint.h>

/* 发送SLIP帧开始/结束分隔符。*/
void SLIP_send_frame_delimiter(void);

/* 发送SLIP帧数据的单个字符，按照SLIP转义进行转义。*/
void SLIP_send_frame_data(char ch);

/* 发送一些SLIP帧数据，按照SLIP转义进行转义。*/
void SLIP_send_frame_data_buf(const void *buf, uint32_t size);

/* 发送包含指定内容的完整SLIP帧。*/
void SLIP_send(const void *pkt, uint32_t size);

typedef enum {
  SLIP_NO_FRAME,
  SLIP_FRAME,
  SLIP_FRAME_ESCAPING
} slip_state_t;

int16_t SLIP_recv_byte(char byte, slip_state_t *state);

#define SLIP_FINISHED_FRAME -2
#define SLIP_NO_BYTE -1

/* 接收包含指定内容的SLIP帧。*/
uint32_t SLIP_recv(void *pkt, uint32_t max_len);

#endif /* SLIP_H_ */

