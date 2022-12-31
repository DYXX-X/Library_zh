/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_ATT_
#define H_BLE_ATT_

/**
 * @brief 蓝牙属性协议（ATT）
 * @defgroup bt_att蓝牙属性协议（att）
 * @ingroup bt_主机@{
 */

#include "os/queue.h"
#ifdef __cplusplus
extern "C" {
#endif

struct os_mbuf;

#define BLE_ATT_UUID_PRIMARY_SERVICE        0x2800
#define BLE_ATT_UUID_SECONDARY_SERVICE      0x2801
#define BLE_ATT_UUID_INCLUDE                0x2802
#define BLE_ATT_UUID_CHARACTERISTIC         0x2803

#define BLE_ATT_ERR_INVALID_HANDLE          0x01
#define BLE_ATT_ERR_READ_NOT_PERMITTED      0x02
#define BLE_ATT_ERR_WRITE_NOT_PERMITTED     0x03
#define BLE_ATT_ERR_INVALID_PDU             0x04
#define BLE_ATT_ERR_INSUFFICIENT_AUTHEN     0x05
#define BLE_ATT_ERR_REQ_NOT_SUPPORTED       0x06
#define BLE_ATT_ERR_INVALID_OFFSET          0x07
#define BLE_ATT_ERR_INSUFFICIENT_AUTHOR     0x08
#define BLE_ATT_ERR_PREPARE_QUEUE_FULL      0x09
#define BLE_ATT_ERR_ATTR_NOT_FOUND          0x0a
#define BLE_ATT_ERR_ATTR_NOT_LONG           0x0b
#define BLE_ATT_ERR_INSUFFICIENT_KEY_SZ     0x0c
#define BLE_ATT_ERR_INVALID_ATTR_VALUE_LEN  0x0d
#define BLE_ATT_ERR_UNLIKELY                0x0e
#define BLE_ATT_ERR_INSUFFICIENT_ENC        0x0f
#define BLE_ATT_ERR_UNSUPPORTED_GROUP       0x10
#define BLE_ATT_ERR_INSUFFICIENT_RES        0x11

#define BLE_ATT_OP_ERROR_RSP                0x01
#define BLE_ATT_OP_MTU_REQ                  0x02
#define BLE_ATT_OP_MTU_RSP                  0x03
#define BLE_ATT_OP_FIND_INFO_REQ            0x04
#define BLE_ATT_OP_FIND_INFO_RSP            0x05
#define BLE_ATT_OP_FIND_TYPE_VALUE_REQ      0x06
#define BLE_ATT_OP_FIND_TYPE_VALUE_RSP      0x07
#define BLE_ATT_OP_READ_TYPE_REQ            0x08
#define BLE_ATT_OP_READ_TYPE_RSP            0x09
#define BLE_ATT_OP_READ_REQ                 0x0a
#define BLE_ATT_OP_READ_RSP                 0x0b
#define BLE_ATT_OP_READ_BLOB_REQ            0x0c
#define BLE_ATT_OP_READ_BLOB_RSP            0x0d
#define BLE_ATT_OP_READ_MULT_REQ            0x0e
#define BLE_ATT_OP_READ_MULT_RSP            0x0f
#define BLE_ATT_OP_READ_GROUP_TYPE_REQ      0x10
#define BLE_ATT_OP_READ_GROUP_TYPE_RSP      0x11
#define BLE_ATT_OP_WRITE_REQ                0x12
#define BLE_ATT_OP_WRITE_RSP                0x13
#define BLE_ATT_OP_PREP_WRITE_REQ           0x16
#define BLE_ATT_OP_PREP_WRITE_RSP           0x17
#define BLE_ATT_OP_EXEC_WRITE_REQ           0x18
#define BLE_ATT_OP_EXEC_WRITE_RSP           0x19
#define BLE_ATT_OP_NOTIFY_REQ               0x1b
#define BLE_ATT_OP_INDICATE_REQ             0x1d
#define BLE_ATT_OP_INDICATE_RSP             0x1e
#define BLE_ATT_OP_WRITE_CMD                0x52

#define BLE_ATT_ATTR_MAX_LEN                512

#define BLE_ATT_F_READ                      0x01
#define BLE_ATT_F_WRITE                     0x02
#define BLE_ATT_F_READ_ENC                  0x04
#define BLE_ATT_F_READ_AUTHEN               0x08
#define BLE_ATT_F_READ_AUTHOR               0x10
#define BLE_ATT_F_WRITE_ENC                 0x20
#define BLE_ATT_F_WRITE_AUTHEN              0x40
#define BLE_ATT_F_WRITE_AUTHOR              0x80

#define HA_FLAG_PERM_RW                     (BLE_ATT_F_READ | BLE_ATT_F_WRITE)

#define BLE_ATT_ACCESS_OP_READ              1
#define BLE_ATT_ACCESS_OP_WRITE             2

/**默认ATT MTU。也是最小值。*/
#define BLE_ATT_MTU_DFLT                    23

/**
 * 527的ATT MTU允许最大ATT命令（带符号写入）包含512字节的属性值。
 */
#define BLE_ATT_MTU_MAX                     527

/**
 * 读取本地注册的属性。如果指定的属性句柄对应于GATT特征值或描述符，则通过调用注册的GATT访问回调来执行读取。
 *
 * @param attr_handle           要读取的属性的16位句柄。
 * @param out_om                成功后，将指向新分配的mbuf，该mbuf包含读取的属性数据。
 *
 * @return                      成功时为0；如果属性访问回调报告失败，则NimBLE主机ATT返回代码；出现意外错误时，NimBLE主机核心返回代码。
 */
int ble_att_svr_read_local(uint16_t attr_handle, struct os_mbuf **out_om);

/**
 * 写入本地注册的属性。无论结果如何，此函数都会消耗所提供的mbuf。如果指定的属性句柄对应于GATT特征值或描述符，则通过调用注册的GATT访问回调来执行写入。
 *
 * @param attr_handle           要写入的属性的16位句柄。
 * @param om                    要写入属性的值。
 *
 * @return                      成功时为0；如果属性访问回调报告失败，则NimBLE主机ATT返回代码；出现意外错误时，NimBLE主机核心返回代码。
 */
int ble_att_svr_write_local(uint16_t attr_handle, struct os_mbuf *om);

/**
 * 检索指定连接的ATT MTU。如果发生了此连接的MTU交换，则MTU是两个对等方的首选值中的较低值。否则，MTU为默认值23。
 *
 * @param conn_handle           要查询的连接的句柄。
 *
 * @return                      指定连接的ATT MTU，如果没有这样的连接，则为0。
 */
uint16_t ble_att_mtu(uint16_t conn_handle);

/**
 * 检索首选ATT MTU。这是ATT MTU交换期间设备指示的值。
 *
 * @return                      首选ATT MTU。
 */
uint16_t ble_att_preferred_mtu(void);

/**
 * 设置首选ATT MTU；设备将在所有后续ATT MTU交换中指示该值。连接的ATT MTU等于两个对等方的首选MTU值中的较低值。ATT MTU是指GATT程序期间发送的任何消息的最大大小。
 *
 * 指定的MTU必须在以下范围内：[23，BLE_ATT_MTU_MAX]。23是蓝牙规范规定的最小值；BLE_ATT_MTU_MAX是NimBLE编译时设置。
 *
 * @param mtu                   首选ATT MTU。
 *
 * @return                      成功时为0；如果指定值不在允许的范围内，则返回BLE_HS_EINVAL。
 */
int ble_att_set_preferred_mtu(uint16_t mtu);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif

