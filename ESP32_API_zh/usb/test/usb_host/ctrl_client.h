/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#include <stdint.h>

typedef struct {
    int num_ctrl_xfer_to_send;
    uint16_t idVendor;
    uint16_t idProduct;
} ctrl_client_test_param_t;

void ctrl_client_async_seq_task(void *arg);

