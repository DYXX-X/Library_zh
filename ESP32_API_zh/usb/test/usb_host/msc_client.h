/*
 * SPDX文件版权所有文本：2015-2022 Espressif Systems（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#include <stdint.h>

#define MSC_ASYNC_CLIENT_MAX_EVENT_MSGS       5

typedef struct {
    int num_sectors_to_read;
    int num_sectors_per_xfer;
    uint32_t msc_scsi_xfer_tag;
    uint16_t idVendor;
    uint16_t idProduct;
} msc_client_test_param_t;

void msc_client_async_seq_task(void *arg);

void msc_client_async_dconn_task(void *arg);

void msc_client_async_enum_task(void *arg);

