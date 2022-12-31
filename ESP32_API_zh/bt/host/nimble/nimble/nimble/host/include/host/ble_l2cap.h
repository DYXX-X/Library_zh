/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_L2CAP_
#define H_BLE_L2CAP_

#include "nimble/nimble_opt.h"
#ifdef __cplusplus
extern "C" {
#endif

struct ble_l2cap_sig_update_req;
struct ble_hs_conn;

#define BLE_L2CAP_CID_ATT           4
#define BLE_L2CAP_CID_SIG           5
#define BLE_L2CAP_CID_SM            6

#define BLE_L2CAP_SIG_OP_REJECT                 0x01
#define BLE_L2CAP_SIG_OP_CONNECT_REQ            0x02
#define BLE_L2CAP_SIG_OP_CONNECT_RSP            0x03
#define BLE_L2CAP_SIG_OP_CONFIG_REQ             0x04
#define BLE_L2CAP_SIG_OP_CONFIG_RSP             0x05
#define BLE_L2CAP_SIG_OP_DISCONN_REQ            0x06
#define BLE_L2CAP_SIG_OP_DISCONN_RSP            0x07
#define BLE_L2CAP_SIG_OP_ECHO_REQ               0x08
#define BLE_L2CAP_SIG_OP_ECHO_RSP               0x09
#define BLE_L2CAP_SIG_OP_INFO_REQ               0x0a
#define BLE_L2CAP_SIG_OP_INFO_RSP               0x0b
#define BLE_L2CAP_SIG_OP_CREATE_CHAN_REQ        0x0c
#define BLE_L2CAP_SIG_OP_CREATE_CHAN_RSP        0x0d
#define BLE_L2CAP_SIG_OP_MOVE_CHAN_REQ          0x0e
#define BLE_L2CAP_SIG_OP_MOVE_CHAN_RSP          0x0f
#define BLE_L2CAP_SIG_OP_MOVE_CHAN_CONF_REQ     0x10
#define BLE_L2CAP_SIG_OP_MOVE_CHAN_CONF_RSP     0x11
#define BLE_L2CAP_SIG_OP_UPDATE_REQ             0x12
#define BLE_L2CAP_SIG_OP_UPDATE_RSP             0x13
#define BLE_L2CAP_SIG_OP_LE_CREDIT_CONNECT_REQ  0x14
#define BLE_L2CAP_SIG_OP_LE_CREDIT_CONNECT_RSP  0x15
#define BLE_L2CAP_SIG_OP_FLOW_CTRL_CREDIT       0x16
#define BLE_L2CAP_SIG_OP_CREDIT_CONNECT_REQ     0x17
#define BLE_L2CAP_SIG_OP_CREDIT_CONNECT_RSP     0x18
#define BLE_L2CAP_SIG_OP_CREDIT_RECONFIG_REQ    0x19
#define BLE_L2CAP_SIG_OP_CREDIT_RECONFIG_RSP    0x1A
#define BLE_L2CAP_SIG_OP_MAX                    0x1B

#define BLE_L2CAP_SIG_ERR_CMD_NOT_UNDERSTOOD    0x0000
#define BLE_L2CAP_SIG_ERR_MTU_EXCEEDED          0x0001
#define BLE_L2CAP_SIG_ERR_INVALID_CID           0x0002

#define BLE_L2CAP_COC_ERR_CONNECTION_SUCCESS        0x0000
#define BLE_L2CAP_COC_ERR_UNKNOWN_LE_PSM            0x0002
#define BLE_L2CAP_COC_ERR_NO_RESOURCES              0x0004
#define BLE_L2CAP_COC_ERR_INSUFFICIENT_AUTHEN       0x0005
#define BLE_L2CAP_COC_ERR_INSUFFICIENT_AUTHOR       0x0006
#define BLE_L2CAP_COC_ERR_INSUFFICIENT_KEY_SZ       0x0007
#define BLE_L2CAP_COC_ERR_INSUFFICIENT_ENC          0x0008
#define BLE_L2CAP_COC_ERR_INVALID_SOURCE_CID        0x0009
#define BLE_L2CAP_COC_ERR_SOURCE_CID_ALREADY_USED   0x000A
#define BLE_L2CAP_COC_ERR_UNACCEPTABLE_PARAMETERS   0x000B
#define BLE_L2CAP_COC_ERR_INVALID_PARAMETERS        0x000C

#define BLE_L2CAP_ERR_RECONFIG_SUCCEED                       0x0000
#define BLE_L2CAP_ERR_RECONFIG_REDUCTION_MTU_NOT_ALLOWED     0x0001
#define BLE_L2CAP_ERR_RECONFIG_REDUCTION_MPS_NOT_ALLOWED     0x0002
#define BLE_L2CAP_ERR_RECONFIG_INVALID_DCID                  0x0003
#define BLE_L2CAP_ERR_RECONFIG_UNACCAPTED_PARAM              0x0004

#define BLE_L2CAP_EVENT_COC_CONNECTED                 0
#define BLE_L2CAP_EVENT_COC_DISCONNECTED              1
#define BLE_L2CAP_EVENT_COC_ACCEPT                    2
#define BLE_L2CAP_EVENT_COC_DATA_RECEIVED             3
#define BLE_L2CAP_EVENT_COC_TX_UNSTALLED              4
#define BLE_L2CAP_EVENT_COC_RECONFIG_COMPLETED        5
#define BLE_L2CAP_EVENT_COC_PEER_RECONFIGURED         6

typedef void ble_l2cap_sig_update_fn(uint16_t conn_handle, int status,
                                     void *arg);

struct ble_l2cap_sig_update_params {
    uint16_t itvl_min;
    uint16_t itvl_max;
    uint16_t slave_latency;
    uint16_t timeout_multiplier;
};

int ble_l2cap_sig_update(uint16_t conn_handle,
                         struct ble_l2cap_sig_update_params *params,
                         ble_l2cap_sig_update_fn *cb, void *cb_arg);

struct ble_l2cap_chan;

/**
 * 表示L2CAP相关事件。当发生此类事件时，主机通过将此结构的实例传递给应用程序指定的回调来通知应用程序。
 */
struct ble_l2cap_event {
    /**
     * 指示发生的L2CAP事件的类型。这是BLE_L2CAP_EVENT代码之一。
     */
    uint8_t type;

    /**
     * 包含有关L2CAP事件的其他详细信息的受区别的联合。“type”字段指示联合的哪个成员有效。
     */
    union {
        /**
         * 表示连接尝试。对以下事件类型有效：o BLE_L2CAP_event_COC_CONNECTED*/
        struct {
            /**
             * 连接尝试的状态；o 0:连接已成功建立。o BLE主机错误代码：由于指定的原因，连接尝试失败。
             */
            int status;

            /**相关连接的连接手柄*/
            uint16_t conn_handle;

            /**相关L2CAP连接的L2CAP通道。*/
            struct ble_l2cap_chan *chan;
        } connect;

        /**
         * 表示终止的连接。对以下事件类型有效：o BLE_L2CAP_event_COC_DISCONNECTED
         */
        struct {
            /**相关连接的连接手柄*/
            uint16_t conn_handle;

            /**终止前有关L2CAP连接的信息。*/
            struct ble_l2cap_chan *chan;
        } disconnect;

        /**
         * 表示连接接受。对以下事件类型有效：o BLE_L2CAP_event_COC_ACCEPT
         */
        struct {
            /**相关连接的连接手柄*/
            uint16_t conn_handle;

            /**信道上对等设备支持的MTU*/
            uint16_t peer_sdu_size;

            /**相关L2CAP连接的L2CAP通道。*/
            struct ble_l2cap_chan *chan;
        } accept;

        /**
         * 表示接收的数据。对以下事件类型有效：o BLE_L2CAP_event_COC_DATA_RECEIVED
         */
        struct {
            /**相关连接的连接手柄*/
            uint16_t conn_handle;

            /**相关L2CAP连接的L2CAP通道。*/
            struct ble_l2cap_chan *chan;

            /**已接收SDU的mbuf。*/
            struct os_mbuf *sdu_rx;
        } receive;

        /**
         * 表示tx_uinstalled数据。对以下事件类型有效：o BLE_L2CAP_event_COC_TX_UNSTALLED
         */
        struct {
            /**相关连接的连接手柄*/
            uint16_t conn_handle;

            /**相关L2CAP连接的L2CAP通道。*/
            struct ble_l2cap_chan *chan;

            /**
             * 由于缺少信用而暂停的发送尝试的状态；仅当以下SDU片段的内存分配存在问题时，此值才可以为非零。在这种情况下，最后一个SDU已部分发送给对等设备，由应用程序决定如何处理它。
             */
            int status;
        } tx_unstalled;

        /**
         * 表示已完成重新配置。对以下事件类型有效：o BLE_L2CAP_event_COC_RECONFIG_COMPLETED o BLE_L2CAP_event_COC_PEER_RECONFIGURED
         */
        struct {
            /**
             * 重新配置尝试的状态；o 0:重新配置已成功完成。o BLE主机错误代码：由于指定的原因，重新配置尝试失败。
             */
            int status;

            /**相关连接的连接手柄*/
            uint16_t conn_handle;

            /**相关L2CAP连接的L2CAP通道。*/
            struct ble_l2cap_chan *chan;
        } reconfigured;
    };
};

struct ble_l2cap_chan_info {
    uint16_t scid;
    uint16_t dcid;
    uint16_t our_l2cap_mtu;
    uint16_t peer_l2cap_mtu;
    uint16_t psm;
    uint16_t our_coc_mtu;
    uint16_t peer_coc_mtu;
};

typedef int ble_l2cap_event_fn(struct ble_l2cap_event *event, void *arg);


uint16_t ble_l2cap_get_conn_handle(struct ble_l2cap_chan *chan);
int ble_l2cap_create_server(uint16_t psm, uint16_t mtu,
                            ble_l2cap_event_fn *cb, void *cb_arg);

int ble_l2cap_connect(uint16_t conn_handle, uint16_t psm, uint16_t mtu,
                      struct os_mbuf *sdu_rx,
                      ble_l2cap_event_fn *cb, void *cb_arg);
int ble_l2cap_disconnect(struct ble_l2cap_chan *chan);
int ble_l2cap_send(struct ble_l2cap_chan *chan, struct os_mbuf *sdu_tx);
int ble_l2cap_recv_ready(struct ble_l2cap_chan *chan, struct os_mbuf *sdu_rx);
int ble_l2cap_get_chan_info(struct ble_l2cap_chan *chan, struct ble_l2cap_chan_info *chan_info);

#ifdef __cplusplus
}
#endif

#endif

