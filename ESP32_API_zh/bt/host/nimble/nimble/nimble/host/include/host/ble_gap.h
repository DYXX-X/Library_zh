/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_GAP_
#define H_BLE_GAP_

/**
 * @brief 蓝牙主机通用接入模式（GAP）
 * @defgroup bt_host_gap蓝牙主机通用访问配置文件（gap）
 * @ingroup bt_主机@{
 */

#include <inttypes.h>
#include "host/ble_hs.h"
#include "host/ble_hs_adv.h"
#include "syscfg/syscfg.h"

#ifdef __cplusplus
extern "C" {
#endif

struct hci_le_conn_complete;
struct hci_conn_update;

/**30毫秒。*/
#define BLE_GAP_ADV_FAST_INTERVAL1_MIN      (30 * 1000 / BLE_HCI_ADV_ITVL)

/**60毫秒。*/
#define BLE_GAP_ADV_FAST_INTERVAL1_MAX      (60 * 1000 / BLE_HCI_ADV_ITVL)

/**100毫秒。*/
#define BLE_GAP_ADV_FAST_INTERVAL2_MIN      (100 * 1000 / BLE_HCI_ADV_ITVL)

/**150毫秒。*/
#define BLE_GAP_ADV_FAST_INTERVAL2_MAX      (150 * 1000 / BLE_HCI_ADV_ITVL)

/**30毫秒；主动扫描。*/
#define BLE_GAP_SCAN_FAST_INTERVAL_MIN      (30 * 1000 / BLE_HCI_ADV_ITVL)

/**60毫秒；主动扫描。*/
#define BLE_GAP_SCAN_FAST_INTERVAL_MAX      (60 * 1000 / BLE_HCI_ADV_ITVL)

/**11.25毫秒；有限的发现间隔。*/
#define BLE_GAP_LIM_DISC_SCAN_INT           (11.25 * 1000 / BLE_HCI_SCAN_ITVL)

/**11.25毫秒；有限的发现窗口（不是来自规范）。*/
#define BLE_GAP_LIM_DISC_SCAN_WINDOW        (11.25 * 1000 / BLE_HCI_SCAN_ITVL)

/**30毫秒；主动扫描。*/
#define BLE_GAP_SCAN_FAST_WINDOW            (30 * 1000 / BLE_HCI_SCAN_ITVL)

/* 30.72秒；主动扫描。*/
#define BLE_GAP_SCAN_FAST_PERIOD            (30.72 * 1000)

/**1.28秒；背景扫描。*/
#define BLE_GAP_SCAN_SLOW_INTERVAL1         (1280 * 1000 / BLE_HCI_SCAN_ITVL)

/**11.25毫秒；背景扫描。*/
#define BLE_GAP_SCAN_SLOW_WINDOW1           (11.25 * 1000 / BLE_HCI_SCAN_ITVL)

/**10.24秒。*/
#define BLE_GAP_DISC_DUR_DFLT               (10.24 * 1000)

/**30秒（不符合规范）。*/
#define BLE_GAP_CONN_DUR_DFLT               (30 * 1000)

/**1秒。*/
#define BLE_GAP_CONN_PAUSE_CENTRAL          (1 * 1000)

/**5秒。*/
#define BLE_GAP_CONN_PAUSE_PERIPHERAL       (5 * 1000)

/* 30毫秒。*/
#define BLE_GAP_INITIAL_CONN_ITVL_MIN       (30 * 1000 / BLE_HCI_CONN_ITVL)

/* 50毫秒。*/
#define BLE_GAP_INITIAL_CONN_ITVL_MAX       (50 * 1000 / BLE_HCI_CONN_ITVL)

/**默认通道掩码：使用所有三个通道。*/
#define BLE_GAP_ADV_DFLT_CHANNEL_MAP        0x07

#define BLE_GAP_INITIAL_CONN_LATENCY        0
#define BLE_GAP_INITIAL_SUPERVISION_TIMEOUT 0x0100
#define BLE_GAP_INITIAL_CONN_MIN_CE_LEN     0x0000
#define BLE_GAP_INITIAL_CONN_MAX_CE_LEN     0x0000

#define BLE_GAP_ROLE_MASTER                 0
#define BLE_GAP_ROLE_SLAVE                  1

#define BLE_GAP_EVENT_CONNECT               0
#define BLE_GAP_EVENT_DISCONNECT            1
/* 保留2*/
#define BLE_GAP_EVENT_CONN_UPDATE           3
#define BLE_GAP_EVENT_CONN_UPDATE_REQ       4
#define BLE_GAP_EVENT_L2CAP_UPDATE_REQ      5
#define BLE_GAP_EVENT_TERM_FAILURE          6
#define BLE_GAP_EVENT_DISC                  7
#define BLE_GAP_EVENT_DISC_COMPLETE         8
#define BLE_GAP_EVENT_ADV_COMPLETE          9
#define BLE_GAP_EVENT_ENC_CHANGE            10
#define BLE_GAP_EVENT_PASSKEY_ACTION        11
#define BLE_GAP_EVENT_NOTIFY_RX             12
#define BLE_GAP_EVENT_NOTIFY_TX             13
#define BLE_GAP_EVENT_SUBSCRIBE             14
#define BLE_GAP_EVENT_MTU                   15
#define BLE_GAP_EVENT_IDENTITY_RESOLVED     16
#define BLE_GAP_EVENT_REPEAT_PAIRING        17
#define BLE_GAP_EVENT_PHY_UPDATE_COMPLETE   18
#define BLE_GAP_EVENT_EXT_DISC              19
#define BLE_GAP_EVENT_PERIODIC_SYNC         20
#define BLE_GAP_EVENT_PERIODIC_REPORT       21
#define BLE_GAP_EVENT_PERIODIC_SYNC_LOST    22
#define BLE_GAP_EVENT_SCAN_REQ_RCVD         23
#define BLE_GAP_EVENT_PERIODIC_TRANSFER     24

/***订阅GAP事件的原因代码。*/

/**对等方的CCCD订阅状态因描述符写入而更改。*/
#define BLE_GAP_SUBSCRIBE_REASON_WRITE      1

/**由于连接终止，对等方的CCCD订阅状态已清除。*/
#define BLE_GAP_SUBSCRIBE_REASON_TERM       2

/**
 * 由于从持久性恢复（绑定已恢复），对等方的CCCD订阅状态已更改。
 */
#define BLE_GAP_SUBSCRIBE_REASON_RESTORE    3

#define BLE_GAP_REPEAT_PAIRING_RETRY        1
#define BLE_GAP_REPEAT_PAIRING_IGNORE       2

/**连接安全状态*/
struct ble_gap_sec_state {
    /**如果连接已加密*/
    unsigned encrypted:1;

    /**如果连接已验证*/
    unsigned authenticated:1;

    /**如果连接已绑定（存储安全信息）*/
    unsigned bonded:1;

    /**用于加密的密钥大小*/
    unsigned key_size:5;
};

/**广告参数*/
struct ble_gap_adv_params {
    /** 广告模式。可以是以下常量之一：
     *  -BLE_GAP_CONN_MODE_NON（不可连接；3.C.9.3.2）。
     *  -BLE_GAP_CONN_MODE_DIR（可直接连接；3.C.9.3.3）。
     *  -BLE_GAP_CONN_MODE_UND（无方向可连接；3.C.9.3.4）。
     */
    uint8_t conn_mode;
    /** 可发现模式。可以是以下常量之一：
     *  -BLE_GAP_DISC_MODE_NON（不可发现；3.C.9.2.2）。
     *  -BLE_GAP_DISC_MODE_LTD（有限可发现；3.C.9.2.3）。
     *  -BLE_GAP_DISC_MODE_GEN（一般可发现；3.C.9.2.4）。
     */
    uint8_t disc_mode;

    /**最小广告间隔，如果0堆栈使用正常默认值*/
    uint16_t itvl_min;
    /**最大广告间隔，如果0堆栈使用正常默认值*/
    uint16_t itvl_max;
    /**广告频道图，如果0堆栈使用正常默认值*/
    uint8_t channel_map;

    /**广告筛选策略*/
    uint8_t filter_policy;

    /**如果做定向广告的高占空比*/
    uint8_t high_duty_cycle:1;
};

/** @brief 连接描述符*/
struct ble_gap_conn_desc {
    /**连接安全状态*/
    struct ble_gap_sec_state sec_state;

    /**本地身份地址*/
    ble_addr_t our_id_addr;

    /**对等身份地址*/
    ble_addr_t peer_id_addr;

    /**本地无线地址*/
    ble_addr_t our_ota_addr;

    /**对等无线地址*/
    ble_addr_t peer_ota_addr;

    /**连接手柄*/
    uint16_t conn_handle;

    /**连接间隔*/
    uint16_t conn_itvl;

    /**连接延迟*/
    uint16_t conn_latency;

    /**连接监控超时*/
    uint16_t supervision_timeout;

    /** 连接角色可能值BLE_GAP_Role_SLAVE或BLE_GAP-Role_MASTER
     */
    uint8_t role;

    /**主时钟精度*/
    uint8_t master_clock_accuracy;
};

/** @brief 连接参数*/
struct ble_gap_conn_params {
    /**扫描间隔（单位：0.625ms）*/
    uint16_t scan_itvl;

    /**以0.625ms为单位扫描窗口*/
    uint16_t scan_window;

    /**以1.25ms为单位的连接间隔最小值*/
    uint16_t itvl_min;

    /**以1.25ms为单位的连接间隔最大值*/
    uint16_t itvl_max;

    /**连接延迟*/
    uint16_t latency;

    /**以10ms为单位的监控超时*/
    uint16_t supervision_timeout;

    /**连接事件的最小长度（单位：0.625ms）*/
    uint16_t min_ce_len;

    /**连接事件的最大长度（单位：0.625ms）*/
    uint16_t max_ce_len;
};

/** @brief 扩展发现参数*/
struct ble_gap_ext_disc_params {
    /**扫描间隔（单位：0.625ms）*/
    uint16_t itvl;

    /**以0.625ms为单位扫描窗口*/
    uint16_t window;

    /**如果应使用被动扫描*/
    uint8_t passive:1;
};

/** @brief 发现参数*/
struct ble_gap_disc_params {
    /**扫描间隔（单位：0.625ms）*/
    uint16_t itvl;

    /**以0.625ms为单位扫描窗口*/
    uint16_t window;

    /**扫描筛选器策略*/
    uint8_t filter_policy;

    /**如果应使用有限的发现过程*/
    uint8_t limited:1;

    /**如果应使用被动扫描*/
    uint8_t passive:1;

    /**如果启用重复筛选*/
    uint8_t filter_duplicates:1;
};

/** @brief 连接参数更新参数*/
struct ble_gap_upd_params {
    /**以1.25ms为单位的连接间隔最小值*/
    uint16_t itvl_min;

    /**以1.25ms为单位的连接间隔最大值*/
    uint16_t itvl_max;

    /**连接延迟*/
    uint16_t latency;

    /**以10ms为单位的监控超时*/
    uint16_t supervision_timeout;

    /**连接事件的最小长度（单位：0.625ms）*/
    uint16_t min_ce_len;

    /**连接事件的最大长度（单位：0.625ms）*/
    uint16_t max_ce_len;
};

/** @brief Passkey查询*/
struct ble_gap_passkey_params {
    /** Passkey操作，可以是以下常量之一：
     *  - BLE_SM_IOACT_NONE
     *  - BLE_SM_IOACT_OOB
     *  - BLE_SM_IOACT_INPUT
     *  - BLE_SM_IOACT_DISP
     *  - BLE_SM_IOACT_NUMCMP
     */
    uint8_t action;

    /**要比较的密钥，对BLE_SM_IOACT_NUMCMP操作有效*/
    uint32_t numcmp;
};

#if MYNEWT_VAL(BLE_EXT_ADV)

#define BLE_GAP_EXT_ADV_DATA_STATUS_COMPLETE   0x00
#define BLE_GAP_EXT_ADV_DATA_STATUS_INCOMPLETE 0x01
#define BLE_GAP_EXT_ADV_DATA_STATUS_TRUNCATED  0x02

/** @brief 扩展广告报告*/
struct ble_gap_ext_disc_desc {
    /** 报告属性位掩码
     *  - BLE_HCI_ADV_CONN_MASK
     *  - BLE_HCI_ADV_SCAN_MASK
     *  - BLE_HCI_ADV_DIRECT_MASK
     *  - BLE_HCI_ADV_SCAN_RSP_MASK
     *  - BLE_HCI_ADV_LEGACY_MASK
     *  */
    uint8_t props;

    /** 广告数据状态，可以是以下常量之一：
     *  - BLE_GAP_EXT_ADV_DATA_STATUS_COMPLETE
     *  - BLE_GAP_EXT_ADV_DATA_STATUS_INCOMPLETE
     *  - BLE_GAP_EXT_ADV_DATA_STATUS_TRUNCATED
     */
    uint8_t data_status;

    /** 传统广告PDU类型。如果设置了BLE_HCI_ADV_LEGACY_MASK道具，则有效。可以是以下常量之一：
     *  - BLE_HCI_ADV_RPT_EVTYPE_ADV_IND
     *  - BLE_HCI_ADV_RPT_EVTYPE_DIR_IND
     *  - BLE_HCI_ADV_RPT_EVTYPE_SCAN_IND
     *  - BLE_HCI_ADV_RPT_EVTYPE_NONCONN_IND
     *  - BLE_HCI_ADV_RPT_EVTYPE_SCAN_RSP
     */
    uint8_t legacy_event_type;

    /**广告客户地址*/
    ble_addr_t addr;

    /**接收信号强度指示（单位：dBm）（127，如果不可用）*/
    int8_t rssi;

    /**广告商发射功率（dBm）（127，如果不可用）*/
    int8_t tx_power;

    /**广告集ID*/
    uint8_t sid;

    /** 主要广告PHY可以是以下常量之一：
     *  - BLE_HCI_LE_PHY_1M
     *  - BLE_HCI_LE_PHY_CODED
     */
    uint8_t prim_phy;

    /** 二级广告PHY可以是以下常量之一：
     *  - BLE_HCI_LE_PHY_1M
     *  - LE_HCI_LE_PHY_2M
     *  - BLE_HCI_LE_PHY_CODED
     */
    uint8_t sec_phy;

    /**定期广告间隔。如果没有定期广告，则为0。*/
    uint16_t periodic_adv_itvl;

    /**广告数据长度*/
    uint8_t length_data;

    /**广告数据*/
    const uint8_t *data;

    /** 定向广告地址。如果设置了BLE_HCI_ADV_DIRECT_MASK道具（否则为BLE_ADDR_ANY），则有效。
     */
    ble_addr_t direct_addr;
};
#endif

/** @brief 广告报道*/
struct ble_gap_disc_desc {
    /** 广告PDU类型。可以是以下常量之一：
     *  - BLE_HCI_ADV_RPT_EVTYPE_ADV_IND
     *  - BLE_HCI_ADV_RPT_EVTYPE_DIR_IND
     *  - BLE_HCI_ADV_RPT_EVTYPE_SCAN_IND
     *  - BLE_HCI_ADV_RPT_EVTYPE_NONCONN_IND
     *  - BLE_HCI_ADV_RPT_EVTYPE_SCAN_RSP
     */
    uint8_t event_type;

    /**广告数据长度*/
    uint8_t length_data;

    /**广告客户地址*/
    ble_addr_t addr;

    /**接收信号强度指示（单位：dBm）（127，如果不可用）*/
    int8_t rssi;

    /**广告数据*/
    const uint8_t *data;

    /** 定向广告地址。对于BLE_HCI_ADV_RPT_EVTYPE_DIR_IND事件类型有效（否则为BLE_ADDR_ANY）。
     */
    ble_addr_t direct_addr;
};

struct ble_gap_repeat_pairing {
    /**相关连接的句柄。*/
    uint16_t conn_handle;

    /**现有债券的性质。*/
    uint8_t cur_key_size;
    uint8_t cur_authenticated:1;
    uint8_t cur_sc:1;

    /**
     * 如果允许继续配对过程，则即将到来的安全链接的属性。
     */
    uint8_t new_key_size;
    uint8_t new_authenticated:1;
    uint8_t new_sc:1;
    uint8_t new_bonding:1;
};

/**
 * 表示GAP相关事件。当发生此类事件时，主机通过将此结构的实例传递给应用程序指定的回调来通知应用程序。
 */
struct ble_gap_event {
    /**
     * 指示发生的GAP事件的类型。这是BLE_GAP_EVENT代码之一。
     */
    uint8_t type;

    /**
     * 一个受歧视的工会，包含有关GAP事件的其他细节。“type”字段指示联合的哪个成员有效。
     */
    union {
        /**
         * 表示连接尝试。对以下事件类型有效：o BLE_GAP_event_CONNECT
         */
        struct {
            /**
             * 连接尝试的状态；o 0:连接已成功建立。o BLE主机错误代码：由于指定的原因，连接尝试失败。
             */
            int status;

            /**相关连接的句柄。*/
            uint16_t conn_handle;
        } connect;

        /**
         * 表示终止的连接。对以下事件类型有效：o BLE_GAP_event_DISCONNECT
         */
        struct {
            /**
             * BLE主机返回代码，指示断开连接的原因。
             */
            int reason;

            /**终止前有关连接的信息。*/
            struct ble_gap_conn_desc conn;
        } disconnect;

        /**
         * 表示在发现过程中收到的播发报告。对以下事件类型有效：o BLE_GAP_event_DISC
         */
        struct ble_gap_disc_desc disc;

#if MYNEWT_VAL(BLE_EXT_ADV)
        /**
         * 表示在发现过程中接收的扩展广告报告。对以下事件类型有效：o BLE_GAP_event_EXT_DISC
         */
        struct ble_gap_ext_disc_desc ext_disc;
#endif

        /**
         * 表示已完成的发现过程。对以下事件类型有效：o BLE_GAP_event_DISC_COMPLETE
         */
        struct {
            /**
             * 发现过程停止的原因。典型原因代码为：o 0：持续时间已过期。o BLE_HS_EPREEMPTED：主机中止了配置对等方身份的过程。
             */
            int reason;
        } disc_complete;

        /**
         * 表示已完成的播发过程。对以下事件类型有效：o BLE_GAP_event_ADV_COMPLETE
         */
        struct {
            /**
             * 播发过程停止的原因。典型原因代码为：o 0：因连接而终止。o BLE_HS_ETIMEOUT：持续时间已过期。o BLE_HS_EPREEMPTED：主机中止了配置对等方身份的过程。
             */
            int reason;

#if MYNEWT_VAL(BLE_EXT_ADV)
            /**广告实例*/
            uint8_t instance;
            /**相关连接的句柄-如果原因=0则有效*/
            uint16_t conn_handle;
            /**
             * 已完成的扩展广告事件数
             *
             * 仅当将非零max_events传递给ble_gap_ext_adv_start（）并且由于持续时间超时或传输的最大事件而完成广告时，此字段才有效。
             * */
            uint8_t num_ext_adv_events;
#endif
        } adv_complete;

        /**
         * 表示尝试更新连接的参数。如果尝试成功，则连接的描述符将反映更新的参数。
         *
         * 对以下事件类型有效：o BLE_GAP_event_CONN_UPDATE
         */
        struct {
            /**
             * 连接更新尝试的结果；o 0:连接已成功更新。o BLE主机错误代码：由于指定的原因，连接更新尝试失败。
             */
            int status;

            /**相关连接的句柄。*/
            uint16_t conn_handle;
        } conn_update;

        /**
         * 表示对等方更新连接参数的请求。当对等方执行以下任一过程时，会生成此事件：o L2CAP连接参数更新过程o链路层连接参数请求过程
         *
         * 要拒绝请求，请返回非零HCI错误代码。返回的值是给控制器的拒绝原因。
         *
         * 对以下事件类型有效：o BLE_GAP_event_L2CAP_UPDATE_REQ o BLE_GAP-event_CONN_UPDATE_REQ
         */
        struct {
            /**
             * 指示对等方要使用的连接参数。
             */
            const struct ble_gap_upd_params *peer_params;

            /**
             * 指示本地设备要使用的连接参数。应用程序回调应填写此内容。默认情况下，此结构包含请求的参数（即，它是“peer_params”的副本）。
             */
            struct ble_gap_upd_params *self_params;

            /**相关连接的句柄。*/
            uint16_t conn_handle;
        } conn_update_req;

        /**
         * 表示尝试终止已建立的连接失败。对以下事件类型有效：o BLE_GAP_event_TERM_FAILURE
         */
        struct {
            /**
             * BLE主机返回代码，指示失败原因。
             */
            int status;

            /**相关连接的句柄。*/
            uint16_t conn_handle;
        } term_failure;

        /**
         * 表示尝试更改连接的加密状态。如果尝试成功，则连接描述符将反映更新的加密状态。
         *
         * 对以下事件类型有效：o BLE_GAP_event_ENC_CHANGE
         */
        struct {
            /**
             * 指示加密状态更改尝试的结果；o 0：已成功更新加密状态；o BLE主机错误代码：由于指定的原因，加密状态更改尝试失败。
             */
            int status;

            /**相关连接的句柄。*/
            uint16_t conn_handle;
        } enc_change;

        /**
         * 表示完成配对过程所需的密钥查询。
         *
         * 对以下事件类型有效：o BLE_GAP_event_PASSKEY_ACTION
         */
        struct {
            /**包含有关密钥查询的详细信息。*/
            struct ble_gap_passkey_params params;

            /**相关连接的句柄。*/
            uint16_t conn_handle;
        } passkey;

        /**
         * 表示收到的ATT通知或指示。
         *
         * 对以下事件类型有效：o BLE_GAP_event_NOTIFY_RX
         */
        struct {
            /**
             * 通知或指示的内容。如果应用程序希望保留此mbuf供以后使用，则必须将此指针设置为NULL，以防止堆栈释放它。
             */
            struct os_mbuf *om;

            /**相关ATT属性的句柄。*/
            uint16_t attr_handle;

            /**相关连接的句柄。*/
            uint16_t conn_handle;

            /**
             * 所接收的命令是通知还是指示；o 0：通知；o 1：指示。
             */
            uint8_t indication:1;
        } notify_rx;

        /**
         * 表示传输的ATT通知或指示，或完成的指示事务。
         *
         * 对以下事件类型有效：o BLE_GAP_event_NOTIFY_TX
         */
        struct {
            /**
             * 通知或指示交易的状态；o 0：命令发送成功；o BLE_HS_EDONE：收到确认（指示ack）；o BLE_HS_ETIMEOUT：从未收到确认（指示ack）；o其他返回代码：错误。
             */
            int status;

            /**相关连接的句柄。*/
            uint16_t conn_handle;

            /**相关特征值的句柄。*/
            uint16_t attr_handle;

            /**
             * 所发送的命令是通知还是指示；o 0：通知；o 1：指示。
             */
            uint8_t indication:1;
        } notify_tx;

        /**
         * 表示对等方订阅状态的状态更改。在本评论中，术语“更新”用于指通知或指示。此事件由以下任何情况触发：o对等方通过CCCD写入启用或禁用更新。o连接即将终止，对等方已订阅更新。o对等体现在在其状态从持久性恢复后订阅更新。当粘结恢复时会发生这种情况。
         *
         * 对以下事件类型有效：o BLE_GAP_event_SUBSCRIBE
         */
        struct {
            /**相关连接的句柄。*/
            uint16_t conn_handle;

            /**相关特性的值句柄。*/
            uint16_t attr_handle;

            /**BLE_GAP_SUBSCRIBE_REASON代码之一。*/
            uint8_t reason;

            /**对等方以前是否订阅了通知。*/
            uint8_t prev_notify:1;

            /**对等方当前是否订阅了通知。*/
            uint8_t cur_notify:1;

            /**对等方先前是否订阅了指示。*/
            uint8_t prev_indicate:1;

            /**对等方当前是否订阅了指示。*/
            uint8_t cur_indicate:1;
        } subscribe;

        /**
         * 表示L2CAP通道MTU的更改。
         *
         * 对以下事件类型有效：o BLE_GAP_event_TU
         */
        struct {
            /**相关连接的句柄。*/
            uint16_t conn_handle;

            /**
             * 表示MTU已更新的信道；BLE_L2CAP_CID_ATT或面向连接的信道的ID。
             */
            uint16_t channel_id;

            /* 该频道的新MTU。*/
            uint16_t value;
        } mtu;

        /**
         * 表示对等身份的更改。这是在成功配对后收到身份地址信息后发出的。
         *
         * 对以下事件类型有效：o BLE_GAP_event_IDENTITY_RESOLVED
         */
        struct {
            /**相关连接的句柄。*/
            uint16_t conn_handle;
        } identity_resolved;

        /**
         * 表示对等方尝试配对，尽管已存在绑定。应用程序有两个选项来处理此事件类型：o重试：删除冲突绑定后返回BLE_GAP_REPEAT_PAIRING_Retry。堆栈将验证键是否已删除，并继续配对程序。如果债券仍然存在，将再次报告该事件。o忽略：返回BLE_GAP_REPEAT_PAIRING_Ignore。堆栈将自动忽略配对请求。
         *
         * 对以下事件类型有效：o BLE_GAP_event_REPET_PAIRING
         */
        struct ble_gap_repeat_pairing repeat_pairing;

        /**
         * 表示PHY的更改。这是PHY成功更改后的问题。
         */
        struct {
            int status;
            uint16_t conn_handle;

            /**
             * 表示已启用TX/RX PHY。可能的值：o BLE_GAP_LE_PHY_1M o BLE_GAP-LE_PHY_2M o BLE_GAP _LE_PHY_CODED
             */
            uint8_t tx_phy;
            uint8_t rx_phy;
        } phy_updated;
#if MYNEWT_VAL(BLE_PERIODIC_ADV)
        /**
         * 表示在发现过程中建立的定期播发同步。对以下事件类型有效：o BLE_GAP_event_PERIODIC_SYNC
         */
        struct {
            /** 成功时为BLE_ERR_SUCCESS，失败时为错误代码。其他字段仅对成功有效
             */
            uint8_t status;
            /**定期同步句柄*/
            uint16_t sync_handle;

            /**广告集ID*/
            uint8_t sid;

            /**广告客户地址*/
            ble_addr_t adv_addr;

            /** 广告PHY可以是以下常量之一：
             *  - BLE_HCI_LE_PHY_1M
             *  - LE_HCI_LE_PHY_2M
             *  - BLE_HCI_LE_PHY_CODED
            */
            uint8_t adv_phy;

            /**定期广告间隔*/
            uint16_t per_adv_ival;

            /**广告商时钟精度*/
            uint8_t adv_clk_accuracy;
        } periodic_sync;

        /**
         * 表示在建立同步时收到的定期广告报告。对以下事件类型有效：o BLE_GAP_event_PERIODIC_REPORT
         */
        struct {
            /**定期同步句柄*/
            uint16_t sync_handle;

            /**广告商发射功率（dBm）（127，如果不可用）*/
            int8_t tx_power;

            /**接收信号强度指示（单位：dBm）（127，如果不可用）*/
            int8_t rssi;

            /** 广告数据状态，可以是以下常量之一：
             *  - BLE_HCI_PERIODIC_DATA_STATUS_COMPLETE
             *  - BLE_HCI_PERIODIC_DATA_STATUS_INCOMPLETE
             *  - BLE_HCI_PERIODIC_DATA_STATUS_TRUNCATED
             */
            uint8_t data_status;

            /**广告数据长度*/
            uint8_t data_length;

            /**广告数据*/
            const uint8_t *data;
        } periodic_report;

        /**
         * 表示已建立同步的定期广告同步丢失。同步丢失原因可能是BLE_HS_ETIMEOUT（同步超时）或BLE_HS_EDONE（本地终止同步）。对以下事件类型有效：o BLE_GAP_event_PERIODIC_SYNC_LOST
         */
        struct {
            /**定期同步句柄*/
            uint16_t sync_handle;

            /** 同步丢失的原因，可以是BLE_HS_ETIMEOUT表示超时，BLE_HS_EDONE表示本地终止的同步
             */
            int reason;
        } periodic_sync_lost;
#endif

#if MYNEWT_VAL(BLE_EXT_ADV)
        /**
         * 表示已启用扫描请求通知的扩展广告实例的扫描请求。对以下事件类型有效：o BLE_GAP_event_SCAN_REQ_RCVD
         */
        struct {
            /**扩展广告实例*/
            uint8_t instance;
            /**扫描仪地址*/
            ble_addr_t scan_addr;
        } scan_req_rcvd;
#endif
#if MYNEWT_VAL(BLE_PERIODIC_ADV_SYNC_TRANSFER)
        /**
         * 表示收到的定期播发同步传输。对以下事件类型有效：o BLE_GAP_event_PERIODIC_TRANSFER
         */
        struct {
            /** 成功时为BLE_ERR_SUCCESS，失败时为错误代码。同步句柄仅对成功有效。
             */
            uint8_t status;

            /**定期同步句柄*/
            uint16_t sync_handle;

            /**连接手柄*/
            uint16_t conn_handle;

            /**服务数据*/
            uint16_t service_data;

            /**广告集ID*/
            uint8_t sid;

            /**广告客户地址*/
            ble_addr_t adv_addr;

            /** 广告PHY可以是以下常量之一：
             *  - BLE_HCI_LE_PHY_1M
             *  - LE_HCI_LE_PHY_2M
             *  - BLE_HCI_LE_PHY_CODED
            */
            uint8_t adv_phy;

            /**定期广告间隔*/
            uint16_t per_adv_itvl;

            /**广告商时钟精度*/
            uint8_t adv_clk_accuracy;
        } periodic_transfer;
#endif
    };
};

typedef int ble_gap_event_fn(struct ble_gap_event *event, void *arg);

#define BLE_GAP_CONN_MODE_NON               0
#define BLE_GAP_CONN_MODE_DIR               1
#define BLE_GAP_CONN_MODE_UND               2

#define BLE_GAP_DISC_MODE_NON               0
#define BLE_GAP_DISC_MODE_LTD               1
#define BLE_GAP_DISC_MODE_GEN               2

/**
 * 搜索具有指定句柄的连接。如果找到匹配的连接，则相应地填充所提供的连接描述符。
 *
 * @param handle    要搜索的连接句柄。
 * @param out_desc  成功后，将填充与匹配连接相关的信息。如果不需要此信息，请传递NULL。
 *
 * @return          成功时为0，如果找不到匹配的连接，则为BLE_HS_ENOTCONN。
 */
int ble_gap_conn_find(uint16_t handle, struct ble_gap_conn_desc *out_desc);

/**
 * 搜索与具有指定地址的对等方的连接。如果找到匹配的连接，则相应地填充所提供的连接描述符。
 *
 * @param addr      要搜索的已连接对等设备的表地址。
 * @param out_desc  成功后，将填充与匹配连接相关的信息。如果不需要此信息，请传递NULL。
 *
 * @return          成功时为0，如果找不到匹配的连接，则为BLE_HS_ENOTCONN。
 */
int ble_gap_conn_find_by_addr(const ble_addr_t *addr,
                              struct ble_gap_conn_desc *out_desc);

/**
 * 配置连接以使用指定的GAP事件回调。连接的GAP事件回调是在创建连接时首先指定的，无论是通过广告还是启动。此函数替换上次配置的回调。
 *
 * @param conn_handle   要配置的连接的句柄。
 * @param cb            要与连接关联的回调。
 * @param cb_arg        回调接收的可选参数。
 *
 * @return              成功时为0，如果没有与指定句柄的连接，则为BLE_HS_ENOTCONN。
 */
int ble_gap_set_event_cb(uint16_t conn_handle,
                         ble_gap_event_fn *cb, void *cb_arg);

/** @brief 开始广告宣传
 *
 * 此功能配置并启动广告过程。
 *
 * @param own_addr_type 堆栈应用于自身的地址类型。有效值为：
 *                         - BLE_OWN_ADDR_PUBLIC
 *                         - BLE_OWN_ADDR_RANDOM
 *                         - BLE_OWN_ADDR_RPA_PUBLIC_DEFAULT
 *                         - BLE_OWN_ADDR_RPA_RANDOM_DEFAULT
 * @param direct_addr   定向广告的同行地址。如果正在使用定向广告，则此参数应为非NULL。
 * @param duration_ms   广告过程的持续时间。到期时，过程结束，并报告BLE_GAP_EVENT_ADV_COMPLETE事件。单位为毫秒。指定BLE_HS_FOREVER不过期。
 * @param adv_params    指定广告程序细节的附加参数。
 * @param cb            与此广告过程关联的回调。如果广告结束，则通过此回调报告事件。如果广告导致连接，则连接将继承此回调作为其事件报告机制。
 * @param cb_arg        要传递给回调函数的可选参数。
 *
 * @return              成功时为0，失败时为错误代码。
 */
int ble_gap_adv_start(uint8_t own_addr_type, const ble_addr_t *direct_addr,
                      int32_t duration_ms,
                      const struct ble_gap_adv_params *adv_params,
                      ble_gap_event_fn *cb, void *cb_arg);

/**
 * 停止当前活动的广告过程。成功返回代码表示广告已完全中止，可以立即启动新的广告过程。
 *
 * 注意：如果呼叫者运行的任务与NimBLE主机相同，或者它运行的任务优先级高于主机，则在重新启动广告时必须小心。在这些情况下，以下方法不是重新启动广告的可靠方法：ble_gap_adv_stop（）ble_gap_adv_start（）
 *
 * 相反，必须在单独的事件上下文中调用“ble_gap_adv_start（）”。也就是说，“ble_gap_adv_start（）”必须通过将事件排入当前任务的事件队列来异步调用。看见https://github.com/apache/mynewt-nimble/pull/211了解更多信息。
 *
 * @return  成功时为0，如果没有活动的广告过程，则为BLE_HS_EALREADY，失败时为其他错误代码。
 */
int ble_gap_adv_stop(void);

/**
 * 指示当前是否正在进行播发过程。
 *
 * @return 如果没有正在进行的广告过程，则为0，否则为1。
 */
int ble_gap_adv_active(void);

/**
 * 配置要包含在后续播发中的数据。
 *
 * @param data      包含广告数据的缓冲区。
 * @param data_len  广告数据的大小，以字节为单位。
 *
 * @return          成功时为0，如果广告正在进行，则为BLE_HS_EBUSY，失败时为其他错误代码。
 */
int ble_gap_adv_set_data(const uint8_t *data, int data_len);

/**
 * 配置要包含在后续扫描响应中的数据。
 *
 * @param data      包含扫描响应数据的缓冲区。
 * @param data_len  响应数据的大小，以字节为单位。
 *
 * @return          成功时为0，如果广告正在进行，则为BLE_HS_EBUSY，失败时为其他错误代码。
 */
int ble_gap_adv_rsp_set_data(const uint8_t *data, int data_len);

/**
 * 配置要包含在后续播发中的字段。这是ble_gap_adv_set_data（）的便利包装。
 *
 * @param adv_fields    指定广告数据。
 *
 * @return              成功时为0，如果正在进行广告，则为BLE_HS_EBUSY，如果指定的数据太大，无法放入广告，则返回BLE_HS_EMSGSIZE，失败时返回其他错误代码。
 */
int ble_gap_adv_set_fields(const struct ble_hs_adv_fields *rsp_fields);

/**
 * 配置要包含在后续扫描响应中的字段。这是ble_gap_adv_rsp_set_data（）的便利包装。
 *
 * @param adv_fields   指定扫描响应数据。
 *
 * @return              成功时为0，如果正在进行广告，则为BLE_HS_EBUSY，如果指定的数据太大，无法容纳扫描响应，则为ABL_HS_EMSGSIZE，失败时为其他错误代码。
 */
int ble_gap_adv_rsp_set_fields(const struct ble_hs_adv_fields *rsp_fields);

/**
 * 在控制器中配置LE数据长度（OGF=0x08，OCF=0x0022）。
 *
 * @param conn_handle      连接手柄。
 * @param tx_octets        控制器应用于新连接的有效负载八位字节的首选值（范围0x001B-0x00FB）。
 * @param tx_time          本地控制器应用于传输单链路层数据包的首选最大微秒数（范围0x0148-0x4290）。
 *
 * @return              成功时为0，失败时为其他错误代码。
 */
int ble_hs_hci_util_set_data_len(uint16_t conn_handle, uint16_t tx_octets,
                                 uint16_t tx_time);

#if MYNEWT_VAL(BLE_EXT_ADV)
/** @brief 扩展的广告参数*/
struct ble_gap_ext_adv_params {
    /**如果执行可连接广告*/
    unsigned int connectable:1;

    /**如果执行可扫描广告*/
    unsigned int scannable:1;

    /**如果执行定向广告*/
    unsigned int directed:1;

    /**如果执行高责任定向广告*/
    unsigned int high_duty_directed:1;

    /**如果使用传统PDU进行广告*/
    unsigned int legacy_pdu:1;

    /**如果执行匿名广告*/
    unsigned int anonymous:1;

    /**如果在广告PDU中包含TX功率*/
    unsigned int include_tx_power:1;

    /**如果启用扫描请求通知*/
    unsigned int scan_req_notif:1;

    /** 最小广告间隔（单位：0.625ms），如果0堆栈使用正常默认值
     */
    uint32_t itvl_min;

    /** 最大广告间隔（单位：0.625ms），如果0堆栈使用正常默认值
     */
    uint32_t itvl_max;

    /**广告频道图，如果0堆栈使用正常默认值*/
    uint8_t channel_map;

    /**广告实例使用的自己的地址类型*/
    uint8_t own_addr_type;

    /**定向广告的对等地址，仅当设置了定向时有效*/
    ble_addr_t peer;

    /**广告筛选策略*/
    uint8_t filter_policy;

    /** 要使用的主要广告PHY可以是以下常量之一：
     *  - BLE_HCI_LE_PHY_1M
     *  - BLE_HCI_LE_PHY_CODED
     */
    uint8_t primary_phy;

    /** 要使用的次要广告PHY可以是以下常量之一：
     *  - BLE_HCI_LE_PHY_1M
     *  - LE_HCI_LE_PHY_2M
     *  - BLE_HCI_LE_PHY_CODED
     */
    uint8_t secondary_phy;

    /**首选广告客户传输功率*/
    int8_t tx_power;

    /**广告集ID*/
    uint8_t sid;
};

/**
 * 配置扩展广告实例
 *
 * @param instance            实例ID
 * @param params              指定广告详情的附加参数。
 * @param selected_tx_power   如果非空，则选定的广告发射功率将存储在该参数中。
 * @param cb                  与此广告过程关联的回调。通过此回调报告广告完成事件
 * @param cb_arg              要传递给回调函数的可选参数。
 *
 * @return                      成功时为0；失败时为非零。
 */
int ble_gap_ext_adv_configure(uint8_t instance,
                              const struct ble_gap_ext_adv_params *params,
                              int8_t *selected_tx_power,
                              ble_gap_event_fn *cb, void *cb_arg);

/**
 * 为配置的广告实例设置随机地址。
 *
 * @param instance            实例ID
 * @param addr                要设置的随机地址
 *
 * @return                      成功时为0；失败时为非零。
 */
int ble_gap_ext_adv_set_addr(uint8_t instance, const ble_addr_t *addr);

/**
 * 启动广告实例。
 *
 * @param instance            实例ID
 * @param duration            广告过程的持续时间。到期时，过程结束，并报告BLE_GAP_EVENT_ADV_COMPLETE事件。单位为10毫秒。指定0表示无过期。
 * @params max_events         在广告结束并报告BLE_GAP_EVENT_ADV_COMPLETE事件之前应发送的广告事件数。指定0表示无限制。
 *
 * @return              成功时为0，失败时为错误代码。
 */
int ble_gap_ext_adv_start(uint8_t instance, int duration, int max_events);

/**
 * 停止指定实例的播发过程。
 *
 * @param instance            实例ID
 *
 * @return  成功时为0，如果没有活动的广告过程，则为BLE_HS_EALREADY，失败时为其他错误代码。
 */
int ble_gap_ext_adv_stop(uint8_t instance);

/**
 * 配置要包含在指定播发实例的播发数据包中的数据。
 *
 * @param instance            实例ID
 * @param data                包含广告数据的链。
 *
 * @return          成功时为0，失败时为错误代码。
 */
int ble_gap_ext_adv_set_data(uint8_t instance, struct os_mbuf *data);

/**
 * 配置数据以包括在指定广告实例的后续扫描响应中。
 *
 * @param instance            实例ID
 * @param data                包含扫描响应数据的链。
 *
 * @return          成功时为0，失败时为错误代码。
 */

int ble_gap_ext_adv_rsp_set_data(uint8_t instance, struct os_mbuf *data);

/**
 * 删除现有广告实例。
 *
 * @param instance            实例ID
 *
 * @return              成功时为0，如果广告正在进行，则为BLE_HS_EBUSY，失败时为其他错误代码。
 */
int ble_gap_ext_adv_remove(uint8_t instance);

/**
 * 清除所有现有广告实例
 * @return              成功时为0，如果广告正在进行，则为BLE_HS_EBUSY，失败时为其他错误代码。
 */
int ble_gap_ext_adv_clear(void);
#endif

/* 定期广告*/
#if MYNEWT_VAL(BLE_PERIODIC_ADV)

/** @brief 定期广告参数*/
struct ble_gap_periodic_adv_params {
    /**如果在广告PDU中包含TX功率*/
    unsigned int include_tx_power:1;

    /** 最小广告间隔（单位：0.625ms），如果0堆栈使用正常默认值
     */
    uint16_t itvl_min;

    /** 最大广告间隔（单位：0.625ms），如果0堆栈使用正常默认值
     */
    uint16_t itvl_max;
};

/** @brief 周期同步参数*/
struct ble_gap_periodic_sync_params {
    /** 成功接收后控制器可以跳过的周期性广告事件的最大数量。
     * */
    uint16_t skip;

    /** 以10ms为单位的定期广告列车的同步超时
     */
    uint16_t sync_timeout;

    /**如果创建同步时最初应禁用报告*/
    unsigned int reports_disabled:1;
};

/**
 * 为指定的播发实例配置定期播发
 *
 * 这仅适用于配置为不可注释、不可连接和不可扫描的实例。
 *
 * @param instance            实例ID
 * @param params              指定定期广告详情的附加参数。
 *
 * @return                    成功时为0；失败时为非零。
 */
int ble_gap_periodic_adv_configure(uint8_t instance,
                                   const struct ble_gap_periodic_adv_params *params);

/**
 * 为指定的播发实例启动定期播发。
 *
 * @param instance            实例ID
 *
 * @return              成功时为0，失败时为错误代码。
 */
int ble_gap_periodic_adv_start(uint8_t instance);

/**
 * 停止指定广告实例的定期广告。
 *
 * @param instance            实例ID
 *
 * @return              成功时为0，失败时为错误代码。
 */
int ble_gap_periodic_adv_stop(uint8_t instance);

/**
 * 配置数据以包括在指定播发实例的定期播发中。
 *
 * @param instance            实例ID
 * @param data                包含定期广告数据的链。
 *
 * @return          成功时为0，失败时为错误代码。
 */
int ble_gap_periodic_adv_set_data(uint8_t instance, struct os_mbuf *data);

/**
 * 与定期广告客户执行同步过程。
 *
 * @param addr               要同步的对等地址。如果为NULL，则使用周期列表中的对等项。
 * @param adv_sid            广告客户集ID
 * @param params             指定同步过程细节的其他参数。
 * @param cb                 与此同步过程关联的回调。BLE_GAP_EVENT_PERIODIC_REPORT事件仅由此回调报告。
 * @param cb_arg             要传递给回调函数的可选参数。
 *
 * @return                   成功时为0；失败时为非零。
 */
int ble_gap_periodic_adv_sync_create(const ble_addr_t *addr, uint8_t adv_sid,
                                     const struct ble_gap_periodic_sync_params *params,
                                     ble_gap_event_fn *cb, void *cb_arg);

/**
 * 取消挂起的同步过程。
 *
 * @return                   成功时为0；失败时为非零。
 */
int ble_gap_periodic_adv_sync_create_cancel(void);

/**
 * 终止同步过程。
 *
 * @param sync_handle        标识要终止的同步的句柄。
 *
 * @return                   成功时为0；失败时为非零。
 */
int ble_gap_periodic_adv_sync_terminate(uint16_t sync_handle);

#if MYNEWT_VAL(BLE_PERIODIC_ADV_SYNC_TRANSFER)
/**
 * 禁用或启用指定同步的定期报告。
 *
 * @param sync_handle        标识同步的句柄。
 * @param enable             如果应启用报告。
 *
 * @return                   成功时为0；失败时为非零。
 */
int ble_gap_periodic_adv_sync_reporting(uint16_t sync_handle, bool enable);

/**
 * 初始化指定句柄的同步传输过程。
 *
 * 这允许将定期同步传输到已同步的主机。
 *
 * @param sync_handle        标识同步的句柄。
 * @param conn_handle        标识连接的句柄。
 * @param service_data       同步传输服务数据
 *
 * @return                   成功时为0；失败时为非零。
 */
int ble_gap_periodic_adv_sync_transfer(uint16_t sync_handle,
                                       uint16_t conn_handle,
                                       uint16_t service_data);

/**
 * 初始化指定句柄的集合信息传输过程。
 *
 * 这允许传输主机通告的周期性同步。
 *
 * @param instance           启用了定期广告的广告实例。
 * @param conn_handle        标识连接的句柄。
 * @param service_data       同步传输服务数据
 *
 * @return                   成功时为0；失败时为非零。
 */
int ble_gap_periodic_adv_sync_set_info(uint8_t instance,
                                       uint16_t conn_handle,
                                       uint16_t service_data);

/**
 * 启用或禁用指定连接上的同步传输接收。当同步传输到达时，BLE_GAP_EVENT_PERIODIC_transfer将发送给用户。之后，该连接上的同步传输接收被终止，用户需要在期望接收下一个同步传输时再次调用此API。
 *
 * 注意：如果ACL连接在同步传输到达之前断开，则用户将不会收到BLE_GAP_EVENT_PERIODIC_transfer。相反，同步传输接收由主机自动终止。
 *
 * @param conn_handle        标识连接的句柄。
 * @param params             启用同步传输接收的参数。指定NULL以禁用接收。
 * @param cb                 与此同步过程关联的回调。BLE_GAP_EVENT_PERIODIC_REPORT事件仅由此回调报告。
 * @param cb_arg             要传递给回调函数的可选参数。
 *
 * @return                   成功时为0；失败时为非零。
 */
int ble_gap_periodic_adv_sync_receive(uint16_t conn_handle,
                                      const struct ble_gap_periodic_sync_params *params,
                                      ble_gap_event_fn *cb, void *cb_arg);
#endif

/**
 * 将对等设备添加到定期同步列表。
 *
 * @param addr               要添加到列表的对等地址。
 * @param adv_sid            广告客户集ID
 *
 * @return                   成功时为0；失败时为非零。
 */
int ble_gap_add_dev_to_periodic_adv_list(const ble_addr_t *peer_addr,
                                         uint8_t adv_sid);

/**
 * 从定期同步列表中删除对等设备。
 *
 * @param addr               要从列表中删除的对等地址。
 * @param adv_sid            广告客户集ID
 *
 * @return                   成功时为0；失败时为非零。
 */
int ble_gap_rem_dev_from_periodic_adv_list(const ble_addr_t *peer_addr,
                                           uint8_t adv_sid);

/**
 * 清除定期同步列表。
 *
 * @return                   成功时为0；失败时为非零。
 */
int ble_gap_clear_periodic_adv_list(void);

/**
 * 获取定期同步列表大小。
 *
 * @param per_adv_list_size  成功列表大小存储在此处。
 *
 * @return                   成功时为0；失败时为非零。
 */
int ble_gap_read_periodic_adv_list_size(uint8_t *per_adv_list_size);
#endif


/**
 * 执行有限或一般发现程序。
 *
 * @param own_addr_type         发送扫描请求时堆栈应为其自身使用的地址类型。有效值为：
 *                                      - BLE_ADDR_TYPE_PUBLIC
 *                                      - BLE_ADDR_TYPE_RANDOM
 *                                      - BLE_ADDR_TYPE_RPA_PUB_DEFAULT
 *                                      -BLE_ADDR_TYPE_RPA_RND_DEFAULT除非正在使用活动扫描，否则将忽略此参数。
 * @param duration_ms           发现过程的持续时间。到期时，过程结束，并报告BLE_GAP_EVENT_DISC_COMPLETE事件。单位为毫秒。指定BLE_HS_FOREVER不过期。指定0以使用堆栈默认值。
 * @param disc_params           指定发现过程详细信息的其他参数。
 * @param cb                    与此发现过程关联的回调。广告报告和发现终止事件通过此回调进行报告。
 * @param cb_arg                要传递给回调函数的可选参数。
 *
 * @return                      成功时为0；失败时为非零。
 */
int ble_gap_disc(uint8_t own_addr_type, int32_t duration_ms,
                 const struct ble_gap_disc_params *disc_params,
                 ble_gap_event_fn *cb, void *cb_arg);

/**
 * 执行有限或一般扩展发现程序。
 *
 * @param own_addr_type         发送扫描请求时堆栈应为其自身使用的地址类型。有效值为：
 *                                      - BLE_ADDR_TYPE_PUBLIC
 *                                      - BLE_ADDR_TYPE_RANDOM
 *                                      - BLE_ADDR_TYPE_RPA_PUB_DEFAULT
 *                                      -BLE_ADDR_TYPE_RPA_RND_DEFAULT除非正在使用活动扫描，否则将忽略此参数。
 * @param duration              发现过程的持续时间。到期时，如果period设置为0，则过程结束，并报告BLE_GAP_EVENT_DISC_COMPLETE事件。单位为10毫秒。指定0表示无过期。
 * @param period                从控制器开始上次扫描持续时间到开始后续扫描持续时间的时间间隔。指定0以连续扫描。单位为1.28秒。
 * @param limited               如果有限，应使用发现程序。
 * @param uncoded_params        指定未编码PHY的发现过程细节的附加参数。如果提供NULL，则不对该PHY执行扫描。
  * @param coded_params         指定编码PHY的发现过程细节的附加参数。如果提供NULL，则不对该PHY执行扫描。
 * @param cb                    与此发现过程关联的回调。广告报告和发现终止事件通过此回调进行报告。
 * @param cb_arg                要传递给回调函数的可选参数。
 *
 * @return                      成功时为0；失败时为非零。
 */
int ble_gap_ext_disc(uint8_t own_addr_type, uint16_t duration, uint16_t period,
                     uint8_t filter_duplicates, uint8_t filter_policy,
                     uint8_t limited,
                     const struct ble_gap_ext_disc_params *uncoded_params,
                     const struct ble_gap_ext_disc_params *coded_params,
                     ble_gap_event_fn *cb, void *cb_arg);

/**
 * 取消当前正在进行的查找过程。成功返回代码表示扫描已完全中止；可以立即启动新的发现或连接过程。
 *
 * @return                      成功时为0；BLE_HS_EALREADY，如果没有要取消的发现过程；意外错误时的其他非零。
 */
int ble_gap_disc_cancel(void);

/**
 * 指示发现过程当前是否正在进行。
 *
 * @return                      0：没有正在进行的发现过程；1： 发现过程正在进行中。
 */
int ble_gap_disc_active(void);

/**
 * 启动连接过程。
 *
 * @param own_addr_type         在连接建立期间堆栈应该为自己使用的地址类型。
 *                                      - BLE_OWN_ADDR_PUBLIC
 *                                      - BLE_OWN_ADDR_RANDOM
 *                                      - BLE_OWN_ADDR_RPA_PUBLIC_DEFAULT
 *                                      - BLE_OWN_ADDR_RPA_RANDOM_DEFAULT
 * @param peer_addr             要连接到的对等方的地址。如果此参数为NULL，则使用白名单。
 * @param duration_ms           发现过程的持续时间。到期时，过程结束，并报告BLE_GAP_EVENT_DISC_COMPLETE事件。单位为毫秒。
 * @param conn_params           指定连接过程细节的其他参数。为默认值指定null。
 * @param cb                    与此连接过程关联的回调。当连接过程完成时，将通过此回调报告结果。如果连接过程成功，则连接将继承此回调作为其事件报告机制。
 * @param cb_arg                要传递给回调函数的可选参数。
 *
 * @return                      成功时为0；BLE_HS_EALREADY（如果连接尝试已在进行中）；BLE_HS_EBUSY，如果由于扫描正在进行而无法启动连接；BLE_HS_EDONE（如果指定的对等体已连接）；其他非零错误。
 */
int ble_gap_connect(uint8_t own_addr_type, const ble_addr_t *peer_addr,
                    int32_t duration_ms,
                    const struct ble_gap_conn_params *params,
                    ble_gap_event_fn *cb, void *cb_arg);

/**
 * 启动扩展连接过程。
 *
 * @param own_addr_type         在连接建立期间堆栈应该为自己使用的地址类型。
 *                                      - BLE_OWN_ADDR_PUBLIC
 *                                      - BLE_OWN_ADDR_RANDOM
 *                                      - BLE_OWN_ADDR_RPA_PUBLIC_DEFAULT
 *                                      - BLE_OWN_ADDR_RPA_RANDOM_DEFAULT
 * @param peer_addr             要连接到的对等方的地址。如果此参数为NULL，则使用白名单。
 * @param duration_ms           发现过程的持续时间。到期时，过程结束，并报告BLE_GAP_EVENT_DISC_COMPLETE事件。单位为毫秒。
 * @param phy_mask              定义应在哪些PHY上进行连接尝试
 * @param phy_1m_conn_params     指定连接过程细节的其他参数。当在PHY_MASK中设置BLE_GAP_LE_PHY_1M_MASK时，该参数可以指定为空作为默认值。
 * @param phy_2m_conn_params     指定连接过程细节的其他参数。当在PHY_MASK中设置BLE_GAP_LE_PHY_2M_MASK时，该参数可以指定为空作为默认值。
 * @param phy_coded_conn_params  指定连接过程细节的其他参数。当在PHY_MASK中设置了BLE_GAP_LE_PHY_CODED_MASK时，该参数可以指定为空作为默认值。
 * @param cb                    与此连接过程关联的回调。当连接过程完成时，将通过此回调报告结果。如果连接过程成功，则连接将继承此回调作为其事件报告机制。
 * @param cb_arg                要传递给回调函数的可选参数。
 *
 * @return                      成功时为0；BLE_HS_EALREADY（如果连接尝试已在进行中）；BLE_HS_EBUSY，如果由于扫描正在进行而无法启动连接；BLE_HS_EDONE（如果指定的对等体已连接）；其他非零错误。
 */
int ble_gap_ext_connect(uint8_t own_addr_type, const ble_addr_t *peer_addr,
                        int32_t duration_ms, uint8_t phy_mask,
                        const struct ble_gap_conn_params *phy_1m_conn_params,
                        const struct ble_gap_conn_params *phy_2m_conn_params,
                        const struct ble_gap_conn_params *phy_coded_conn_params,
                        ble_gap_event_fn *cb, void *cb_arg);

/**
 * 中止正在进行的连接过程。
 *
 * @return                      成功时为0；BLE_HS_EALREADY（如果没有激活的连接过程）。其他非零错误。
 */
int ble_gap_conn_cancel(void);

/**
 * 指示当前是否正在进行连接过程。
 *
 * @return                      0：没有正在进行的连接过程；1： 正在进行连接过程。
 */
int ble_gap_conn_active(void);

/**
 * 终止已建立的连接。
 *
 * @param conn_handle           与要终止的连接相对应的句柄。
 * @param hci_reason            要指示终止原因的HCI错误代码。
 *
 * @return                      成功时为0；BLE_HS_ENOTCONN，如果没有与指定句柄的连接；其他非零故障。
 */
int ble_gap_terminate(uint16_t conn_handle, uint8_t hci_reason);

/**
 * 用指定的内容覆盖控制器的白名单。
 *
 * @param addrs                 要写入白名单的条目。
 * @param white_list_count      白名单中的条目数。
 *
 * @return                      成功时为0；失败时为非零。
 */
int ble_gap_wl_set(const ble_addr_t *addrs, uint8_t white_list_count);

/**
 * 从控制器的白名单中删除地址。
 *
 * @param addrs                 要从白名单中删除的条目。
 *
 * @return                      成功时为0；失败时为非零。
 */
int ble_gap_wl_tx_rmv(const ble_addr_t *addrs);

/**
 * 启动连接参数更新过程。
 *
 * @param conn_handle           与要更新的连接对应的句柄。
 * @param params                要尝试更新到的连接参数。
 *
 * @return                      成功时为0；BLE_HS_ENOTCONN，如果没有与指定句柄的连接；BLE_HS_EALREADY，如果此连接的连接更新过程已在进行中；如果请求的参数无效，则返回BLE_HS_EINVAL；其他非零错误。
 */
int ble_gap_update_params(uint16_t conn_handle,
                          const struct ble_gap_upd_params *params);

/**
 * 在控制器中配置LE数据长度（OGF=0x08，OCF=0x0022）。
 *
 * @param conn_handle      连接手柄。
 * @param tx_octets        控制器应用于新连接的有效负载八位字节的首选值（范围0x001B-0x00FB）。
 * @param tx_time          本地控制器应用于传输单链路层数据包的首选最大微秒数（范围0x0148-0x4290）。
 *
 * @return                 成功时为0，失败时为其他错误代码。
 */
int ble_gap_set_data_len(uint16_t conn_handle, uint16_t tx_octets, uint16_t tx_time);

/**
 * 启动GAP安全程序。
 *
 * 根据连接角色和存储的安全信息，此功能将启动适当的安全程序（配对或加密）。
 *
 * @param conn_handle           与要固定的连接相对应的手柄。
 *
 * @return                      成功时为0；BLE_HS_ENOTCONN，如果没有与指定句柄的连接；BLE_HS_EALREADY，如果此连接的安全过程已在进行中；其他非零错误。
 */
int ble_gap_security_initiate(uint16_t conn_handle);

/**
 * 作为主机启动GAP配对程序。这仅用于测试，不应由应用程序使用。请改用ble_gap_security_initite（）。
 *
 * @param conn_handle           与要开始配对的连接相对应的句柄。
 *
 * @return                      成功时为0；BLE_HS_ENOTCONN，如果没有与指定句柄的连接；BLE_HS_EALREADY，如果此连接的配对过程已在进行中；其他非零错误。
 */
int ble_gap_pair_initiate(uint16_t conn_handle);

/**
 * 作为主机启动GAP加密过程。这仅用于测试，不应由应用程序使用。请改用ble_gap_security_initite（）。
 *
 * @param conn_handle           与要开始加密的连接相对应的句柄。
 * @param key_size              加密密钥大小
 * @param ltk                   用于加密的长期密钥。
 * @param udiv                  用于LTK的加密多样化器
 * @param rand_val              EDIV和LTK的随机值
 * @param auth                  如果提供的LTK经过认证。
 *
 * @return                      成功时为0；BLE_HS_ENOTCONN，如果没有与指定句柄的连接；BLE_HS_EALREADY，如果此连接的加密过程已在进行中；其他非零错误。
 */
int ble_gap_encryption_initiate(uint16_t conn_handle, uint8_t key_size,
                                const uint8_t *ltk, uint16_t ediv,
                                uint64_t rand_val, int auth);

/**
 * 检索指定连接的最近测量的RSSI。每当接收到数据信道PDU时，就更新连接的RSSI。
 *
 * @param conn_handle           指定要查询的连接。
 * @param out_rssi              成功后，此处将写入检索到的RSSI。
 *
 * @return                      成功时为0；如果控制器拒绝请求，BLE主机HCI返回代码；BLE主机核心在出现意外错误时返回代码。
 */
int ble_gap_conn_rssi(uint16_t conn_handle, int8_t *out_rssi);

/**
 * 用指定的地址取消设备的付款。与该对等设备相关的密钥将从存储器中删除，对等地址将从控制器的解析列表中删除。如果对等体已连接，则连接将终止。
 *
 * @param peer_addr             要取消配对的设备的地址
 *
 * @return                      成功时为0；如果控制器拒绝请求，BLE主机HCI返回代码；BLE主机核心在出现意外错误时返回代码。
 */
int ble_gap_unpair(const ble_addr_t *peer_addr);

/**
 * 取消最旧的绑定对等设备的支付。与该对等设备相关的密钥将从存储器中删除，对等地址将从控制器的解析列表中删除。如果对等体已连接，则连接将终止。
 *
 * @return                      成功时为0；如果控制器拒绝请求，BLE主机HCI返回代码；BLE主机核心在出现意外错误时返回代码。
 */
int ble_gap_unpair_oldest_peer(void);

/**
 * 类似于`ble_gap_unpair_oldest_peer（）`，不同的是它确保输入参数中接收的对等体不会被删除。
 *
 * @param peer_addr             对等方地址（不删除）
 *
 * @return                      成功时为0；如果控制器拒绝请求，BLE主机HCI返回代码；BLE主机核心在出现意外错误时返回代码。
 */
int ble_gap_unpair_oldest_except(const ble_addr_t *peer_addr);

#define BLE_GAP_PRIVATE_MODE_NETWORK        0
#define BLE_GAP_PRIVATE_MODE_DEVICE         1

/**
 * 为指定的对等设备设置隐私模式
 *
 * @param peer_addr          对等设备地址
 * @param priv_mode          要使用的隐私模式。可以是以下常量之一：
 *                             - BLE_GAP_PRIVATE_MODE_NETWORK
 *                             - BLE_GAP_PRIVATE_MODE_DEVICE
 *
 * @return                   成功时为0；失败时为非零。
 */
int ble_gap_set_priv_mode(const ble_addr_t *peer_addr, uint8_t priv_mode);

#define BLE_GAP_LE_PHY_1M                   1
#define BLE_GAP_LE_PHY_2M                   2
#define BLE_GAP_LE_PHY_CODED                3
/**
 * 读取用于指定连接的PHY。
 *
 * 成功时，输出参数填充有有关所用PHY类型的信息。
 *
 * @param conn_handle       连接手柄
 * @param tx_phy            已使用TX PHY。可以是以下常量之一：
 *                            - BLE_GAP_LE_PHY_1M
 *                            - BLE_GAP_LE_PHY_2M
 *                            - BLE_GAP_LE_PHY_CODED
 * @param rx_phy            使用RX PHY。可以是以下常量之一：
 *                            - BLE_GAP_LE_PHY_1M
 *                            - BLE_GAP_LE_PHY_2M
 *                            - BLE_GAP_LE_PHY_CODED
 *
 * @return                   成功时为0；失败时为非零。
 */
int ble_gap_read_le_phy(uint16_t conn_handle, uint8_t *tx_phy, uint8_t *rx_phy);

#define BLE_GAP_LE_PHY_1M_MASK              0x01
#define BLE_GAP_LE_PHY_2M_MASK              0x02
#define BLE_GAP_LE_PHY_CODED_MASK           0x04
#define BLE_GAP_LE_PHY_ANY_MASK             0x0F
/**
 * 设置用于连接的首选默认PHY。
 *
 * @params tx_phys_mask     首选TX PHY。可以是以下常量的掩码：
 *                          - BLE_GAP_LE_PHY_1M_MASK
 *                          - BLE_GAP_LE_PHY_2M_MASK
 *                          - BLE_GAP_LE_PHY_CODED_MASK
 *                          - BLE_GAP_LE_PHY_ANY_MASK
 * @params rx_phys_mask     首选RX PHY。可以是以下常量的掩码：
 *                          - BLE_GAP_LE_PHY_1M_MASK
 *                          - BLE_GAP_LE_PHY_2M_MASK
 *                          - BLE_GAP_LE_PHY_CODED_MASK
 *                          - BLE_GAP_LE_PHY_ANY_MASK

 * @return                   成功时为0；失败时为非零。
 */
int ble_gap_set_prefered_default_le_phy(uint8_t tx_phys_mask,
                                        uint8_t rx_phys_mask);

#define BLE_GAP_LE_PHY_CODED_ANY            0
#define BLE_GAP_LE_PHY_CODED_S2             1
#define BLE_GAP_LE_PHY_CODED_S8             2
/**
 * 设置用于连接的首选PHY。
 *
 * @param conn_handle       连接手柄
 * @params tx_phys_mask     首选TX PHY。可以是以下常量的掩码：
 *                          - BLE_GAP_LE_PHY_1M_MASK
 *                          - BLE_GAP_LE_PHY_2M_MASK
 *                          - BLE_GAP_LE_PHY_CODED_MASK
 *                          - BLE_GAP_LE_PHY_ANY_MASK
 * @params rx_phys_mask     首选RX PHY。可以是以下常量的掩码：
 *                          - BLE_GAP_LE_PHY_1M_MASK
 *                          - BLE_GAP_LE_PHY_2M_MASK
 *                          - BLE_GAP_LE_PHY_CODED_MASK
 *                          - BLE_GAP_LE_PHY_ANY_MASK
 * @param phy_opts          其他PHY选项。有效值为：
 *                          - BLE_GAP_LE_PHY_CODED_ANY
 *                          - BLE_GAP_LE_PHY_CODED_S2
 *                          - BLE_GAP_LE_PHY_CODED_S8
 *
 * @return                   成功时为0；失败时为非零。
 */
int ble_gap_set_prefered_le_phy(uint16_t conn_handle, uint8_t tx_phys_mask,
                                uint8_t rx_phys_mask, uint16_t phy_opts);

/**
 * 事件侦听器结构
 *
 * 这应该用作不透明结构，而不是手动修改。
 */
struct ble_gap_event_listener {
    ble_gap_event_fn *fn;
    void *arg;
    SLIST_ENTRY(ble_gap_event_listener) link;
};

/**
 * 为GAP事件注册侦听器
 *
 * 成功时，侦听器结构将自动初始化，在调用此函数之前不需要初始化。要更改回调和/或参数，请先注销侦听器，然后再次注册它。
 *
 * @param listener      侦听器结构
 * @param fn            回调函数
 * @param arg           回调参数
 *
 * @return              如果已注册侦听器，则成功时BLE_HS_EINVAL为0（如果未指定回调）BLE_HS_EALREADY
 */
int ble_gap_event_listener_register(struct ble_gap_event_listener *listener,
                                    ble_gap_event_fn *fn, void *arg);

/**
 * 注销GAP事件的侦听器
 *
 * @param listener      侦听器结构
 *
 * @return              如果未注册侦听器，则成功时BLE_HS_ENOENT为0
 */
int ble_gap_event_listener_unregister(struct ble_gap_event_listener *listener);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif

