/*
 * SPDX文件版权文本：2010-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _ESP_DPORT_ACCESS_H_
#define _ESP_DPORT_ACCESS_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 将DPORT寄存器序列读取到缓冲区。
 *
 * @param[out] buff_out  包含读取的数据。
 * @param[in]  address   读取寄存器的初始地址。
 * @param[in]  num_words 单词的数量。
 */
void esp_dport_access_read_buffer(uint32_t *buff_out, uint32_t address, uint32_t num_words);

#define DPORT_STALL_OTHER_CPU_START()
#define DPORT_STALL_OTHER_CPU_END()
#define DPORT_INTERRUPT_DISABLE()
#define DPORT_INTERRUPT_RESTORE()

#ifdef __cplusplus
}
#endif

#endif /* _ESP_DPORT_ACCESS_H_ */

