/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_ATT_CMD_
#define H_BLE_ATT_CMD_

#include <inttypes.h>
#include <stddef.h>
#include "os/os_mbuf.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ble_att_hdr {
    uint8_t opcode;
    uint8_t data[0];
} __attribute__((packed));

/**
 * |参数|大小（八位字节）|+-------------------------------+-------------------+|属性操作码|1 | |请求操作码出错|1 | |属性句柄出错|2 | |错误代码|1|
 */
#define BLE_ATT_ERROR_RSP_SZ             5
struct ble_att_error_rsp {
    uint8_t baep_req_op;
    uint16_t baep_handle;
    uint8_t baep_error_code;
} __attribute__((packed));

/**
 * |参数|大小（八位字节）|+-------------------------------+-------------------+|属性操作码|1 | |服务器Rx MTU |2|
 */
#define BLE_ATT_MTU_CMD_SZ               3
struct ble_att_mtu_cmd {
    uint16_t bamc_mtu;
} __attribute__((packed));

/**
 * |参数|大小（八位字节）|+-------------------------------+-------------------+|属性操作码|1 | |起始句柄|2 | |结束句柄|2|
 */
#define BLE_ATT_FIND_INFO_REQ_SZ         5
struct ble_att_find_info_req {
    uint16_t bafq_start_handle;
    uint16_t bafq_end_handle;
} __attribute__((packed));

/**
 * |参数|大小（八位字节）|+-------------------------------+-------------------+|属性操作码|1 | |格式|1 | |信息数据|4到（ATT_MTU-2）|
 */
#define BLE_ATT_FIND_INFO_RSP_BASE_SZ       2
struct ble_att_find_info_rsp {
    uint8_t bafp_format;
    /* 其次是信息数据。*/
} __attribute__((packed));

#define BLE_ATT_FIND_INFO_RSP_FORMAT_16BIT   1
#define BLE_ATT_FIND_INFO_RSP_FORMAT_128BIT  2

#define BLE_ATT_FIND_INFO_IDATA_16_SZ           4
#define BLE_ATT_FIND_INFO_IDATA_128_SZ          18

/**
 * |参数|大小（八位字节）|+-------------------------------+-------------------+|属性操作码|1 | |起始句柄|2 | |结束句柄|2 |属性类型|2 | |属性值|0到（ATT_MTU-7）|
 */
#define BLE_ATT_FIND_TYPE_VALUE_REQ_BASE_SZ   7
struct ble_att_find_type_value_req {
    uint16_t bavq_start_handle;
    uint16_t bavq_end_handle;
    uint16_t bavq_attr_type;
    uint16_t bavq_value[0];
} __attribute__((packed));

/**
 * |参数|大小（八位字节）|+-------------------------------+-------------------+|属性操作码|1 | |信息数据|4到（ATT_MTU-1）|
 */
#define BLE_ATT_FIND_TYPE_VALUE_RSP_BASE_SZ     1
#define BLE_ATT_FIND_TYPE_VALUE_HINFO_BASE_SZ   4

struct ble_att_handle_group {
        uint16_t attr_handle;
        uint16_t group_end_handle;
} __attribute__((packed));

struct ble_att_find_type_value_rsp {
    struct ble_att_handle_group list[0];
} __attribute__((packed));

/**
 * |参数|大小（八位字节）|+-------------------------------+-------------------+|属性操作码|1 | |起始句柄|2 | |结束句柄|2 |属性类型|2或16|
 */
#define BLE_ATT_READ_TYPE_REQ_BASE_SZ   5
#define BLE_ATT_READ_TYPE_REQ_SZ_16     7
#define BLE_ATT_READ_TYPE_REQ_SZ_128    21
struct ble_att_read_type_req {
    uint16_t batq_start_handle;
    uint16_t batq_end_handle;
    uint8_t uuid[0];
} __attribute__((packed));

/**
 * |参数|大小（八位字节）|+-------------------------------+-------------------+|属性操作码|1 | |长度|1 | |属性数据列表|2到（ATT_MTU-2）|
 */
#define BLE_ATT_READ_TYPE_RSP_BASE_SZ       2

struct ble_att_attr_data_list {
    uint16_t handle;
    uint8_t value[0];
} __attribute__((packed));

struct ble_att_read_type_rsp {
    uint8_t batp_length;
    struct ble_att_attr_data_list batp_list[0];
} __attribute__((packed));

#define BLE_ATT_READ_TYPE_ADATA_BASE_SZ     2
#define BLE_ATT_READ_TYPE_ADATA_SZ_16       6
#define BLE_ATT_READ_TYPE_ADATA_SZ_128      20

/**
 * |参数|大小（八位字节）|+-------------------------------+-------------------+|属性操作码|1 | |属性句柄|2|
 */
#define BLE_ATT_READ_REQ_SZ              3
struct ble_att_read_req {
    uint16_t barq_handle;
} __attribute__((packed));

/**
 * |参数|大小（八位字节）|+-------------------------------+-------------------+|属性操作码|1 | |属性值|0到（ATT_MTU-1）|
 */
#define BLE_ATT_READ_RSP_BASE_SZ        1

/**
 * |参数|大小（八位字节）|+-------------------------------+-------------------+|属性操作码|1 | |属性句柄|2 | |值偏移量|2|
 */
#define BLE_ATT_READ_BLOB_REQ_SZ        5
struct ble_att_read_blob_req {
    uint16_t babq_handle;
    uint16_t babq_offset;
} __attribute__((packed));

/**
 * |参数|大小（八位字节）|+-------------------------------+-------------------+|属性操作码|1 | |属性值|0到（ATT_MTU-1）|
 */
#define BLE_ATT_READ_BLOB_RSP_BASE_SZ   1

/**
 * |参数|大小（八位字节）|+-------------------------------+-------------------+|属性操作码|1 | |句柄集|4到（ATT_MTU-1）|
 */
#define BLE_ATT_READ_MULT_REQ_BASE_SZ   1
struct ble_att_read_mult_req {
        uint16_t handles[0];
} __attribute__((packed));

/**
 * |参数|大小（八位字节）|+-------------------------------+-------------------+|属性操作码|1 | |值集|4到（ATT_MTU-1）|
 */
#define BLE_ATT_READ_MULT_RSP_BASE_SZ   1

/**
 * |参数|大小（八位字节）|+-------------------------------+-------------------+|属性操作码|1 | |起始句柄|2 | |结束句柄|2 |属性组类型|2或16|
 */
#define BLE_ATT_READ_GROUP_TYPE_REQ_BASE_SZ  5
#define BLE_ATT_READ_GROUP_TYPE_REQ_SZ_16    7
#define BLE_ATT_READ_GROUP_TYPE_REQ_SZ_128   21
struct ble_att_read_group_type_req {
    uint16_t bagq_start_handle;
    uint16_t bagq_end_handle;
    uint8_t uuid[0];
} __attribute__((packed));

/**
 * |参数|大小（八位字节）|+-------------------------------+-------------------+|属性操作码|1 | |长度|1 | |属性数据列表|2到（ATT_MTU-2）|
 */
#define BLE_ATT_READ_GROUP_TYPE_RSP_BASE_SZ  2
struct ble_att_read_group_type_rsp {
    uint8_t bagp_length;
} __attribute__((packed));

#define BLE_ATT_READ_GROUP_TYPE_ADATA_BASE_SZ   4
#define BLE_ATT_READ_GROUP_TYPE_ADATA_SZ_16     6
#define BLE_ATT_READ_GROUP_TYPE_ADATA_SZ_128    20

/**
 * |参数|大小（八位字节）|+-------------------------------+-------------------+|属性操作码|1 | |属性句柄|2 | |属性值|0到（ATT_MTU-3）|
 */
#define BLE_ATT_WRITE_REQ_BASE_SZ       3
struct ble_att_write_req {
    uint16_t bawq_handle;
    uint8_t value[0];
} __attribute__((packed));

#define BLE_ATT_WRITE_RSP_SZ            1

/**
 * |参数|大小（八位字节）|+-------------------------------+-------------------+|属性操作码|1 | |属性句柄|2 | |值偏移量|2 | |部分属性值|0到（ATT_MTU-5）|
 */
#define BLE_ATT_PREP_WRITE_CMD_BASE_SZ  5
struct ble_att_prep_write_cmd {
    uint16_t bapc_handle;
    uint16_t bapc_offset;
    uint16_t bapc_value[0];
} __attribute__((packed));

/**
 * |参数|大小（八位字节）|+-------------------------------+-------------------+|属性操作码|1 | |标志|1|
 */
#define BLE_ATT_EXEC_WRITE_REQ_SZ       2
struct ble_att_exec_write_req {
    uint8_t baeq_flags;
} __attribute__((packed));

#define BLE_ATT_EXEC_WRITE_F_CANCEL     0x00
#define BLE_ATT_EXEC_WRITE_F_EXECUTE    0x01

/**
 * |参数|大小（八位字节）|+-------------------------------+-------------------+|属性操作码|1|
 */
#define BLE_ATT_EXEC_WRITE_RSP_SZ       1

/**
 * |参数|大小（八位字节）|+-------------------------------+-------------------+|属性操作码|1 | |属性句柄|2 | |属性值|0到（ATT_MTU-3）|
 */
#define BLE_ATT_NOTIFY_REQ_BASE_SZ      3
struct ble_att_notify_req {
    uint16_t banq_handle;
} __attribute__((packed));

/**
 * |参数|大小（八位字节）|+-------------------------------+-------------------+|属性操作码|1 | |属性句柄|2 | |属性值|0到（ATT_MTU-3）|
 */
#define BLE_ATT_INDICATE_REQ_BASE_SZ    3
struct ble_att_indicate_req {
    uint16_t baiq_handle;
} __attribute__((packed));

/**
 * |参数|大小（八位字节）|+-------------------------------+-------------------+|属性操作码|1|
 */
#define BLE_ATT_INDICATE_RSP_SZ         1

/**
 * |参数|大小（八位字节）|+-------------------------------+-------------------+|属性操作码|1 | |属性句柄|2 | |属性值|0到（ATT_MTU-3）|
 */
#define BLE_ATT_WRITE_CMD_BASE_SZ       3
struct ble_att_write_cmd {
    uint16_t handle;
    uint8_t value[0];
} __attribute__((packed));

void ble_att_error_rsp_parse(const void *payload, int len,
                             struct ble_att_error_rsp *rsp);
void ble_att_error_rsp_write(void *payload, int len,
                             const struct ble_att_error_rsp *rsp);
void ble_att_mtu_req_parse(const void *payload, int len,
                           struct ble_att_mtu_cmd *cmd);
void ble_att_mtu_req_write(void *payload, int len,
                           const struct ble_att_mtu_cmd *cmd);
void ble_att_mtu_rsp_parse(const void *payload, int len,
                           struct ble_att_mtu_cmd *cmd);
void ble_att_mtu_rsp_write(void *payload, int len,
                           const struct ble_att_mtu_cmd *cmd);
void ble_att_find_info_req_parse(const void *payload, int len,
                                 struct ble_att_find_info_req *req);
void ble_att_find_info_req_write(void *payload, int len,
                                 const struct ble_att_find_info_req *req);
void ble_att_find_info_rsp_parse(const void *payload, int len,
                                 struct ble_att_find_info_rsp *rsp);
void ble_att_find_info_rsp_write(void *payload, int len,
                                 const struct ble_att_find_info_rsp *rsp);
void ble_att_find_type_value_req_parse(
    const void *payload, int len, struct ble_att_find_type_value_req *req);
void ble_att_find_type_value_req_write(
    void *payload, int len, const struct ble_att_find_type_value_req *req);
void ble_att_read_type_req_parse(const void *payload, int len,
                                 struct ble_att_read_type_req *req);
void ble_att_read_type_req_write(void *payload, int len,
                                 const struct ble_att_read_type_req *req);
void ble_att_read_type_rsp_parse(const void *payload, int len,
                                 struct ble_att_read_type_rsp *rsp);
void ble_att_read_type_rsp_write(void *payload, int len,
                                 const struct ble_att_read_type_rsp *rsp);
void ble_att_read_req_parse(const void *payload, int len,
                            struct ble_att_read_req *req);
void ble_att_read_req_write(void *payload, int len,
                            const struct ble_att_read_req *req);
void ble_att_read_blob_req_parse(const void *payload, int len,
                                 struct ble_att_read_blob_req *req);
void ble_att_read_blob_req_write(void *payload, int len,
                                 const struct ble_att_read_blob_req *req);
void ble_att_read_mult_req_parse(const void *payload, int len);
void ble_att_read_mult_req_write(void *payload, int len);
void ble_att_read_mult_rsp_parse(const void *payload, int len);
void ble_att_read_mult_rsp_write(void *payload, int len);
void ble_att_read_group_type_req_parse(
    const void *payload, int len, struct ble_att_read_group_type_req *req);
void ble_att_read_group_type_req_write(
    void *payload, int len, const struct ble_att_read_group_type_req *req);
void ble_att_read_group_type_rsp_parse(
    const void *payload, int len, struct ble_att_read_group_type_rsp *rsp);
void ble_att_read_group_type_rsp_write(
    void *payload, int len, const struct ble_att_read_group_type_rsp *rsp);
void ble_att_write_req_parse(const void *payload, int len,
                             struct ble_att_write_req *req);
void ble_att_write_req_write(void *payload, int len,
                             const struct ble_att_write_req *req);
void ble_att_write_cmd_parse(const void *payload, int len,
                             struct ble_att_write_req *req);
void ble_att_write_cmd_write(void *payload, int len,
                             const struct ble_att_write_req *req);
void ble_att_prep_write_req_parse(const void *payload, int len,
                                  struct ble_att_prep_write_cmd *cmd);
void ble_att_prep_write_req_write(void *payload, int len,
                                  const struct ble_att_prep_write_cmd *cmd);
void ble_att_prep_write_rsp_parse(const void *payload, int len,
                                  struct ble_att_prep_write_cmd *cmd);
void ble_att_prep_write_rsp_write(void *payload, int len,
                                  const struct ble_att_prep_write_cmd *cmd);
void ble_att_exec_write_req_parse(const void *payload, int len,
                                  struct ble_att_exec_write_req *req);
void ble_att_exec_write_req_write(void *payload, int len,
                                  const struct ble_att_exec_write_req *req);
void ble_att_exec_write_rsp_parse(const void *payload, int len);
void ble_att_exec_write_rsp_write(void *payload, int len);
void ble_att_notify_req_parse(const void *payload, int len,
                              struct ble_att_notify_req *req);
void ble_att_notify_req_write(void *payload, int len,
                              const struct ble_att_notify_req *req);
void ble_att_indicate_req_parse(const void *payload, int len,
                                struct ble_att_indicate_req *req);
void ble_att_indicate_req_write(void *payload, int len,
                                const struct ble_att_indicate_req *req);
void ble_att_indicate_rsp_parse(const void *payload, int len);
void ble_att_indicate_rsp_write(void *payload, int len);

void *ble_att_cmd_prepare(uint8_t opcode, size_t len, struct os_mbuf *txom);
void *ble_att_cmd_get(uint8_t opcode, size_t len, struct os_mbuf **txom);
int ble_att_tx(uint16_t conn_handle, struct os_mbuf *txom);

#ifdef __cplusplus
}
#endif

#endif

