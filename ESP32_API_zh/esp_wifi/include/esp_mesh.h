// 版权所有2017-2018 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

/*
 *   演示的软件堆栈：|-------------------------------------------------------------------------------------||||||应用程序|||--------------------------------------------------||||协议：||||1||||网格堆栈|HTTP、DNS、|||其他|||RTOS:|（网络、|DHCP、…|||组件|||（freeRTOS）|自我修复、|-------------|||流控制、，|网络堆栈：|||||…）|（LwIP）||||| |--------------------------------------------|||| | | | | ||| | Wi-Fi驱动程序|||--------------------------------------------| | | || | | ||||平台HAL||------------------------------------------------------------------------------|
 *
 *   系统事件交付：
 *
 *  |---------------|||默认处理程序|Wi-Fi堆栈|事件|--------------------||--------------->|||----------------|||||事件任务||-------------|事件|||------------>||| LwIP堆栈||--------------------| ||---------|||网格事件回调处理程序||-------------------------||-------->||||应用程序|||事件|任务||网格堆栈|------------>| | | | |-------------------------||---------------|
 *
 * 网格堆栈
 *
 *  网格事件定义了应用程序任务所需的几乎所有系统事件。网状事件包含站点接口上的Wi-Fi连接状态、软AP接口上的子连接状态等。应用程序需要首先通过API esp_Mesh_set_config（）注册网状事件回调处理程序。此处理程序用于接收从网格堆栈和LwIP堆栈发布的事件。应用程序可以为每个事件添加相对处理程序。示例：（1）应用程序可以使用Wi-Fi站点连接状态来决定何时将数据发送到其父节点、根节点或外部IP网络；（2） 应用程序可以使用Wi-Fi软AP状态来决定何时向其子女发送数据。
 *
 *  在当前实现中，应用程序能够直接访问网格堆栈，而不必经过LwIP堆栈。应用程序使用esp_mesh_send（）和esp_mesh_recv（）通过网状网络发送和接收消息。在网格堆栈设计中，普通设备不需要LwIP堆栈。但由于IDF还不支持未初始化LwIP堆栈的系统，应用程序仍需要进行LwIP初始化，还需要做两件事（1）默认停止软AP接口上的DHCP服务器（2）默认停止站点接口上的客户端。示例：tcpip_adapter_init（）；tcpip_adapter_dhcps_stop（tcpip_adapter_IF_AP）tcpip_adapter_dhcpc_stop（tcpip_adapter_IF_STA）
 *
 *  通过网状网络，只有根用户才能访问外部IP网络。在应用程序网格事件处理程序中，一旦设备成为根，无论是否选择DHCP，都立即启动DHCP客户端。
 */

#ifndef __ESP_MESH_H__
#define __ESP_MESH_H__

#include "esp_err.h"
#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include "esp_mesh_internal.h"
#include "lwip/ip_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************
 *                常量
 *******************************************************/
#define MESH_ROOT_LAYER                   (1)       /**<根层值*/
#define MESH_MTU                          (1500)    /**<最大传输单位（字节）*/
#define MESH_MPS                          (1472)    /**<最大有效负载大小（字节）*/
/**
 * @brief 网格错误代码定义
 */
#define ESP_ERR_MESH_WIFI_NOT_START       (ESP_ERR_MESH_BASE + 1)    /**<Wi-Fi未启动*/
#define ESP_ERR_MESH_NOT_INIT             (ESP_ERR_MESH_BASE + 2)    /**＜mesh未初始化*/
#define ESP_ERR_MESH_NOT_CONFIG           (ESP_ERR_MESH_BASE + 3)    /**<未配置网格*/
#define ESP_ERR_MESH_NOT_START            (ESP_ERR_MESH_BASE + 4)    /**<网格未启动*/
#define ESP_ERR_MESH_NOT_SUPPORT          (ESP_ERR_MESH_BASE + 5)    /**<尚不支持*/
#define ESP_ERR_MESH_NOT_ALLOWED          (ESP_ERR_MESH_BASE + 6)    /**<不允许操作*/
#define ESP_ERR_MESH_NO_MEMORY            (ESP_ERR_MESH_BASE + 7)    /**<内存不足*/
#define ESP_ERR_MESH_ARGUMENT             (ESP_ERR_MESH_BASE + 8)    /**<非法参数*/
#define ESP_ERR_MESH_EXCEED_MTU           (ESP_ERR_MESH_BASE + 9)    /**<数据包大小超过MTU*/
#define ESP_ERR_MESH_TIMEOUT              (ESP_ERR_MESH_BASE + 10)   /**<超时*/
#define ESP_ERR_MESH_DISCONNECTED         (ESP_ERR_MESH_BASE + 11)   /**<与站点接口上的父节点断开连接*/
#define ESP_ERR_MESH_QUEUE_FAIL           (ESP_ERR_MESH_BASE + 12)   /**<队列失败*/
#define ESP_ERR_MESH_QUEUE_FULL           (ESP_ERR_MESH_BASE + 13)   /**<队列已满*/
#define ESP_ERR_MESH_NO_PARENT_FOUND      (ESP_ERR_MESH_BASE + 14)   /**<未找到加入网格网络的父级*/
#define ESP_ERR_MESH_NO_ROUTE_FOUND       (ESP_ERR_MESH_BASE + 15)   /**<未找到转发数据包的路由*/
#define ESP_ERR_MESH_OPTION_NULL          (ESP_ERR_MESH_BASE + 16)   /**<未找到选项*/
#define ESP_ERR_MESH_OPTION_UNKNOWN       (ESP_ERR_MESH_BASE + 17)   /**<未知选项*/
#define ESP_ERR_MESH_XON_NO_WINDOW        (ESP_ERR_MESH_BASE + 18)   /**<上游无软件流控制窗口*/
#define ESP_ERR_MESH_INTERFACE            (ESP_ERR_MESH_BASE + 19)   /**<低级别Wi-Fi接口错误*/
#define ESP_ERR_MESH_DISCARD_DUPLICATE    (ESP_ERR_MESH_BASE + 20)   /**<由于序列号重复而丢弃数据包*/
#define ESP_ERR_MESH_DISCARD              (ESP_ERR_MESH_BASE + 21)   /**<丢弃数据包*/
#define ESP_ERR_MESH_VOTING               (ESP_ERR_MESH_BASE + 22)   /**<正在进行投票*/
#define ESP_ERR_MESH_XMIT                 (ESP_ERR_MESH_BASE + 23)   /**< XMIT */
#define ESP_ERR_MESH_QUEUE_READ           (ESP_ERR_MESH_BASE + 24)   /**<读取队列中出错*/
#define ESP_ERR_MESH_PS                   (ESP_ERR_MESH_BASE + 25)   /**<mesh PS未指定为启用或禁用*/
#define ESP_ERR_MESH_RECV_RELEASE         (ESP_ERR_MESH_BASE + 26)   /**<发布esp_mesh_recv_toDS*/

/**
 * @brief esp_mesh_send（）和esp_mesh_recv（）的标志位图
 */
#define MESH_DATA_ENC           (0x01)  /**<数据加密（未实现）*/
#define MESH_DATA_P2P           (0x02)  /**<通过网状网络的点到点交付*/
#define MESH_DATA_FROMDS        (0x04)  /**<从外部IP网络接收*/
#define MESH_DATA_TODS          (0x08)  /**<标识此数据包是外部IP网络的目标*/
#define MESH_DATA_NONBLOCK      (0x10)  /**<esp_mesh_send（）非块*/
#define MESH_DATA_DROP          (0x20)  /**<在根目录已更改的情况下，标识此数据包可以由新根目录丢弃*/
#define MESH_DATA_GROUP         (0x40)  /**<标识此数据包是组地址的目标*/

/**
 * @brief esp_mesh_send（）和esp_mesh_recv（）的选项定义
 */
#define MESH_OPT_SEND_GROUP     (7)     /**<分组数据传输；与esp_mesh_send（）一起使用，应具有有效载荷*/
#define MESH_OPT_RECV_DS_ADDR   (8)     /**<返回远程IP地址；与esp_mesh_send（）和esp_mesh_recv（）一起使用*/

/**
 * @brief 网状网络IE标志
 */
#define MESH_ASSOC_FLAG_VOTE_IN_PROGRESS    (0x02)     /**<正在进行投票*/
#define MESH_ASSOC_FLAG_NETWORK_FREE        (0x08)     /**<当前网络中没有根*/
#define MESH_ASSOC_FLAG_ROOTS_FOUND         (0x20)     /**<找到根冲突*/
#define MESH_ASSOC_FLAG_ROOT_FIXED          (0x40)     /**<固定根*/


/**
 * @brief Mesh PS（省电）占空比类型
 */
#define MESH_PS_DEVICE_DUTY_REQUEST         (0x01)    /**<请求加入网络PS而不指定设备占空比。设备加入网络后，网络将提供网络占空比*/
#define MESH_PS_DEVICE_DUTY_DEMAND          (0x04)    /**<请求加入网络PS并指定所需的设备占空比*/
#define MESH_PS_NETWORK_DUTY_MASTER         (0x80)    /**<表示设备为NWK-DUTY-MASTER（网络占空比主机）*/

/**
 * @brief 网格PS（省电）占空比应用规则
 */
#define MESH_PS_NETWORK_DUTY_APPLIED_ENTIRE         (0)    /**指定的网络负载适用于整个网络<*/
#define MESH_PS_NETWORK_DUTY_APPLIED_UPLINK         (1)    /**指定的网络负载仅应用于上行链路路径<*/

/*******************************************************
 *                枚举
 *******************************************************/
/**
 * @brief 网格事件id的枚举列表
 */
typedef enum {
    MESH_EVENT_STARTED,                 /**<网格已启动*/
    MESH_EVENT_STOPPED,                 /**<网格停止*/
    MESH_EVENT_CHANNEL_SWITCH,          /**<通道开关*/
    MESH_EVENT_CHILD_CONNECTED,         /**<softAP接口上连接了孩子*/
    MESH_EVENT_CHILD_DISCONNECTED,      /**<softAP接口上的孩子断开连接*/
    MESH_EVENT_ROUTING_TABLE_ADD,       /**<通过添加新加入的子项来更改路由表*/
    MESH_EVENT_ROUTING_TABLE_REMOVE,    /**<通过删除休假子项来更改路由表*/
    MESH_EVENT_PARENT_CONNECTED,        /**<父级在站接口上连接*/
    MESH_EVENT_PARENT_DISCONNECTED,     /**<站点接口上的父级已断开*/
    MESH_EVENT_NO_PARENT_FOUND,         /**<未找到父项*/
    MESH_EVENT_LAYER_CHANGE,            /**<网格网络上的层变化*/
    MESH_EVENT_TODS_STATE,              /**<state表示根是否能够访问外部IP网络*/
    MESH_EVENT_VOTE_STARTED,            /**<投票新根的过程由子代或根开始*/
    MESH_EVENT_VOTE_STOPPED,            /**<投票新根的过程停止*/
    MESH_EVENT_ROOT_ADDRESS,            /**<获得根地址。它由网格堆栈自动发布。*/
    MESH_EVENT_ROOT_SWITCH_REQ,         /**<从新投票的根候选发送的根切换请求*/
    MESH_EVENT_ROOT_SWITCH_ACK,         /**<根交换机确认响应从当前根发送的上述请求*/
    MESH_EVENT_ROOT_ASKED_YIELD,        /**<根被更强大的现有根要求产量。如果禁用自组织，并且用户将此设备指定为根设备，则用户应为此设备设置新的父设备。如果启用了自组织，则此设备将自行找到新的父级，用户可以忽略此事件。*/
    MESH_EVENT_ROOT_FIXED,              /**<当设备加入网络时，如果一个设备的“固定根”设置与其父设备的设置不同，则该设备将更新与其父设备相同的设置。每个设备的固定根设置是可变的，因为根的设置会发生变化。*/
    MESH_EVENT_SCAN_DONE,               /**<如果禁用了自组织网络，则用户可以调用esp_wifi_scan_start（）来触发此事件，并在此事件中添加相应的扫描完成处理程序。*/
    MESH_EVENT_NETWORK_STATE,           /**<网络状态，例如当前网格网络是否具有根。*/
    MESH_EVENT_STOP_RECONNECTION,       /**<根设备停止重新连接到路由器，而非根设备停止与其父设备的重新连接。*/
    MESH_EVENT_FIND_NETWORK,            /**<当网格配置中的通道字段设置为零时，网格堆栈将执行全通道扫描以找到可以加入的网格网络，并在找到该网络后返回通道值。*/
    MESH_EVENT_ROUTER_SWITCH,           /**<如果用户在网状配置中指定路由器的BSSID，则当根用户连接到具有相同SSID的另一个路由器时，将发布此事件并附加新的路由器信息。*/
    MESH_EVENT_PS_PARENT_DUTY,          /**<家长职责*/
    MESH_EVENT_PS_CHILD_DUTY,           /**<儿童责任*/
    MESH_EVENT_PS_DEVICE_DUTY,          /**<设备负荷*/
    MESH_EVENT_MAX,
} mesh_event_id_t;

/** @brief ESP-MESH事件基础声明*/
ESP_EVENT_DECLARE_BASE(MESH_EVENT);

/**
 * @brief 设备类型
 */
typedef enum {
    MESH_IDLE,    /**<尚未加入网状网络*/
    MESH_ROOT,    /**<网状网络的唯一汇点。能够访问外部IP网络*/
    MESH_NODE,    /**<中间装置。能够通过网状网络转发数据包*/
    MESH_LEAF,    /**<没有转发能力*/
    MESH_STA,     /**<使用标准Wi-Fi站模式连接到路由器，无网络扩展能力*/
} mesh_type_t;

/**
 * @brief 传输应用数据的协议
 */
typedef enum {
    MESH_PROTO_BIN,     /**<二进制*/
    MESH_PROTO_HTTP,    /**<HTTP协议*/
    MESH_PROTO_JSON,    /**<JSON格式*/
    MESH_PROTO_MQTT,    /**<MQTT协议*/
    MESH_PROTO_AP,      /**<节点AP接口的IP网络网状通信*/
    MESH_PROTO_STA,     /**<节点STA接口的IP网络网状通信*/
} mesh_proto_t;

/**
 * @brief 为了实现可靠的传输，mesh堆栈提供了三种类型的服务
 */
typedef enum {
    MESH_TOS_P2P,    /**<默认情况下在网格堆栈上提供P2P（点对点）重传*/
    MESH_TOS_E2E,    /**<在网格堆栈上提供E2E（端到端）重传（未实现）*/
    MESH_TOS_DEF,    /**<网格堆栈上无重传*/
} mesh_tos_t;

/**
 * @brief 投票原因
 */
typedef enum {
    MESH_VOTE_REASON_ROOT_INITIATED = 1,    /**<投票由root发起*/
    MESH_VOTE_REASON_CHILD_INITIATED,       /**<投票由儿童发起*/
} mesh_vote_reason_t;

/**
 * @brief 网格断开原因代码
 */
typedef enum {
    MESH_REASON_CYCLIC = 100,               /**<检测到循环*/
    MESH_REASON_PARENT_IDLE,                /**<父级空闲*/
    MESH_REASON_LEAF,                       /**<连接的设备更改为叶*/
    MESH_REASON_DIFF_ID,                    /**<在不同的网格ID中*/
    MESH_REASON_ROOTS,                      /**<检测到根冲突*/
    MESH_REASON_PARENT_STOPPED,             /**<parent已停止网格*/
    MESH_REASON_SCAN_FAIL,                  /**<扫描失败*/
    MESH_REASON_IE_UNKNOWN,                 /**<未知IE*/
    MESH_REASON_WAIVE_ROOT,                 /**<放弃根*/
    MESH_REASON_PARENT_WORSE,               /**<RSSI非常差的父母*/
    MESH_REASON_EMPTY_PASSWORD,             /**<使用空密码连接到加密的父级*/
    MESH_REASON_PARENT_UNENCRYPTED,         /**<连接到未加密的父/路由器*/
} mesh_disconnect_reason_t;

/**
 * @brief 网格拓扑结构
 */
typedef enum {
    MESH_TOPO_TREE,                         /**<树拓扑*/
    MESH_TOPO_CHAIN,                        /**<链拓扑*/
} esp_mesh_topology_t;

/*******************************************************
 *                结构
 *******************************************************/
/**
 * @brief IP地址和端口
 */
typedef struct {
    ip4_addr_t ip4;    /**<IP地址*/
    uint16_t port;     /**<端口*/
} __attribute__((packed)) mip_t;

/**
 * @brief 网格地址
 */
typedef union {
    uint8_t addr[6];    /**<mac地址*/
    mip_t mip;          /**<mip地址*/
} mesh_addr_t;

/**
 * @brief 通道开关信息
 */
typedef struct {
    uint8_t channel;    /**<新频道*/
} mesh_event_channel_switch_t;

/**
 * @brief 父级连接信息
 */
typedef struct {
    wifi_event_sta_connected_t connected; /**<父信息，与Wi-Fi事件SYSTEM_event_STA_CONNECTED相同*/
    uint16_t self_layer;                  /**<层*/
    uint8_t duty;                         /**<家长职责*/
} mesh_event_connected_t;

/**
 * @brief 未找到父级信息
 */
typedef struct {
    int scan_times;    /**<扫描时间*/
} mesh_event_no_parent_found_t;

/**
 * @brief 图层更改信息
 */
typedef struct {
    uint16_t new_layer; /**<新图层*/
} mesh_event_layer_change_t;

/**
 * @brief 根到DS（分布式系统）的可达性
 */
typedef enum {
    MESH_TODS_UNREACHABLE,    /**<根用户无法访问外部IP网络*/
    MESH_TODS_REACHABLE,      /**<根用户能够访问外部IP网络*/
} mesh_event_toDS_state_t;

/**
 * @brief 投票开始信息
 */
typedef struct {
    int reason;             /**＜投票原因，投票可以由孩子或根本身发起*/
    int attempts;           /**<停止前的最大投票次数*/
    mesh_addr_t rc_addr;    /**<用户通过API esp_mesh_waive_root（）指定的根地址*/
} mesh_event_vote_started_t;

/**
 * @brief 查找此设备可以加入的网状网络
 */
typedef struct {
    uint8_t channel;            /**<新找到的网络的频道号*/
    uint8_t router_bssid[6];    /**<路由器BSSID*/
} mesh_event_find_network_t;

/**
 * @brief 根地址
 */
typedef mesh_addr_t mesh_event_root_address_t;

/**
 * @brief 父级断开信息
 */
typedef wifi_event_sta_disconnected_t mesh_event_disconnected_t;

/**
 * @brief 儿童相关信息
 */
typedef wifi_event_ap_staconnected_t mesh_event_child_connected_t;

/**
 * @brief 儿童断开信息
 */
typedef wifi_event_ap_stadisconnected_t mesh_event_child_disconnected_t;

/**
 * @brief 根交换机请求信息
 */
typedef struct {
    int reason;             /**＜根开关原因，通常根开关由用户通过API esp_mesh_waive_root（）初始化*/
    mesh_addr_t rc_addr;    /**<根交换机请求者的地址*/
} mesh_event_root_switch_req_t;

/**
 * @brief 其他强大的根地址
 */
typedef struct {
    int8_t rssi;           /**<rssi带路由器*/
    uint16_t capacity;     /**<当前网络中的设备数量*/
    uint8_t addr[6];       /**<其他强大的根地址*/
} mesh_event_root_conflict_t;

/**
 * @brief 路由表更改
 */
typedef struct {
    uint16_t rt_size_new;      /**<新值*/
    uint16_t rt_size_change;   /**<更改值*/
} mesh_event_routing_table_change_t;

/**
 * @brief 根部固定
 */
typedef struct {
    bool is_fixed;     /**<状态*/
} mesh_event_root_fixed_t;

/**
 * @brief 扫描完成事件信息
 */
typedef struct {
    uint8_t  number;     /**<扫描的AP数*/
} mesh_event_scan_done_t;

/**
 * @brief 网络状态信息
 */
typedef struct {
    bool is_rootless;     /**<当前网格网络是否具有根*/
} mesh_event_network_state_t;

/**
 * @brief 新路由器信息
 */
typedef wifi_event_sta_connected_t mesh_event_router_switch_t;

/**
 * @brief PS职责信息
 */
typedef struct {
    uint8_t duty;                                 /**<父母或子女责任*/
    mesh_event_child_connected_t child_connected; /**<子信息*/
} mesh_event_ps_duty_t;

/**
 * @brief 网格事件信息
 */
typedef union {
    mesh_event_channel_switch_t channel_switch;            /**<通道开关*/
    mesh_event_child_connected_t child_connected;          /**<儿童连接*/
    mesh_event_child_disconnected_t child_disconnected;    /**<儿童断开连接*/
    mesh_event_routing_table_change_t routing_table;       /**<路由表更改*/
    mesh_event_connected_t connected;                      /**<父级已连接*/
    mesh_event_disconnected_t disconnected;                /**<父级已断开*/
    mesh_event_no_parent_found_t no_parent;                /**<未找到父项*/
    mesh_event_layer_change_t layer_change;                /**<图层更改*/
    mesh_event_toDS_state_t toDS_state;                    /**<toDS状态，设备在尝试向外部IP网络发送数据包之前，应首先检查此状态。此状态指示根当前是否能够发送数据包。如果没有，设备最好等待此状态更改为MESH_TODS_REACHABLE。*/
    mesh_event_vote_started_t vote_started;                /**<投票开始*/
    mesh_event_root_address_t root_addr;                   /**<根地址*/
    mesh_event_root_switch_req_t switch_req;               /**<根交换机请求*/
    mesh_event_root_conflict_t root_conflict;              /**<其他强大的根*/
    mesh_event_root_fixed_t root_fixed;                    /**<固定根*/
    mesh_event_scan_done_t scan_done;                      /**<扫描完成*/
    mesh_event_network_state_t network_state;              /**<网络状态，例如当前网格网络是否具有根。*/
    mesh_event_find_network_t find_network;                /**<找到可以加入的网络*/
    mesh_event_router_switch_t router_switch;              /**<新路由器信息*/
    mesh_event_ps_duty_t ps_duty;                          /**<PS职责信息*/
} mesh_event_info_t;

/**
 * @brief 网格选项
 */
typedef struct {
    uint8_t type;    /**<选项类型*/
    uint16_t len;    /**<选项长度*/
    uint8_t *val;    /**<选项值*/
} __attribute__((packed)) mesh_opt_t;

/**
 * @brief esp_Mesh_send（）和esp_Mesh_recv（）的网格数据
 */
typedef struct {
    uint8_t *data;         /**<数据*/
    uint16_t size;         /**<数据大小*/
    mesh_proto_t proto;    /**<数据协议*/
    mesh_tos_t tos;        /**<服务的数据类型*/
} mesh_data_t;

/**
 * @brief 路由器配置
 */
typedef struct {
    uint8_t ssid[32];             /**< SSID */
    uint8_t ssid_len;             /**<SSID长度*/
    uint8_t bssid[6];             /**<BSSID，如果指定了此值，则用户还应指定“allow_router_switch”。*/
    uint8_t password[64];         /**<密码*/
    bool allow_router_switch;     /**<如果指定了BSSID并且还设置了该值，则当在“fail”（mesh_attempts_t）次后找不到该指定BSSID的路由器时，允许整个网络切换到具有相同SSID的另一个路由器。新路由器也可能在不同的频道上。默认值为false。如果新的交换路由器和以前的路由器之间的密码不同，则可能会建立网状网络，但根将永远无法连接到新的交换路由。*/
} mesh_router_t;

/**
 * @brief 网状软AP配置
 */
typedef struct {
    uint8_t password[64];              /**<mesh softAP密码*/
    /**
     * 允许连接的最大站点数，默认值为6，最大值为10=max_connection+nonmesh_max_connection
     */
    uint8_t max_connection;            /**<最大网格连接数*/
    uint8_t nonmesh_max_connection;    /**<最大非网格连接数*/
} mesh_ap_cfg_t;

/**
 * @brief 网格初始化配置
 */
typedef struct {
    uint8_t channel;                            /**<通道，网格网络*/
    bool allow_channel_switch;                  /**<如果设置了该值，当达到“fail”（mesh_attempts_t）次数时，设备将更改为对可能加入的网络进行全通道扫描。默认值为false。*/
    mesh_addr_t mesh_id;                        /**<网状网络识别*/
    mesh_router_t router;                       /**<路由器配置*/
    mesh_ap_cfg_t mesh_ap;                      /**<mesh softAP配置*/
    const mesh_crypto_funcs_t *crypto_funcs;    /**<加密函数*/
} mesh_cfg_t;

/**
 * @brief 投票地址配置
 */
typedef union {
    int attempts;           /**<网格网络自动选择新根之前的最大投票次数。（最小值：15，默认值为15）*/
    mesh_addr_t rc_addr;    /**<用户为API esp_mesh_waive_root（）指定的新根地址*/
} mesh_rc_config_t;

/**
 * @brief 选票
 */
typedef struct {
    float percentage;           /**<批准成为root用户的投票百分比阈值*/
    bool is_rc_specified;       /**<如果为真，则应指定rc_addr（未实现）。如果为false，则应指定尝试值以进行网络启动根选择。*/
    mesh_rc_config_t config;    /**<投票地址配置*/
} mesh_vote_t;

/**
 * @brief 等待网格堆栈发送的队列中挂起的数据包数
 */
typedef struct {
    int to_parent;        /**<到父队列*/
    int to_parent_p2p;    /**<到父（P2P）队列*/
    int to_child;         /**<到子队列*/
    int to_child_p2p;     /**<到子（P2P）队列*/
    int mgmt;             /**<管理队列*/
    int broadcast;        /**<广播和多播队列*/
} mesh_tx_pending_t;

/**
 * @brief 队列中等待应用程序接收的可用数据包数
 */
typedef struct {
    int toDS;      /**<至外部DS*/
    int toSelf;    /**<对自己*/
} mesh_rx_pending_t;

/*******************************************************
 *                变量声明
 *******************************************************/
/* mesh IE加密回调函数*/
extern const mesh_crypto_funcs_t g_wifi_default_mesh_crypto_funcs;

#define MESH_INIT_CONFIG_DEFAULT() { \
    .crypto_funcs = &g_wifi_default_mesh_crypto_funcs, \
}

/*******************************************************
 *                功能定义
 *******************************************************/
/**
 * @brief      网格初始化
 *             -检查Wi-Fi是否已启动。
 *             -使用默认值初始化网格全局变量。
 *
 * @attention  Wi-Fi启动后应调用此API。
 *
 * @return
 *    - ESP_OK
 *    - ESP_FAIL
 */
esp_err_t esp_mesh_init(void);

/**
 * @brief      网格取消初始化
 *
 *             -释放资源并停止网格
 *
 * @return
 *    - ESP_OK
 *    - ESP_FAIL
 */
esp_err_t esp_mesh_deinit(void);

/**
 * @brief      开始网格（Start mesh）
 *             -初始化网格IE。
 *             -启动网状网络管理服务。
 *             -根据配置创建TX和RX队列。
 *             -注册网格数据包接收回调。
 *
 * @attention　　This 应在网格初始化和配置后调用API。
 *
 * @return
 *    - ESP_OK
 *    - ESP_FAIL
 *    - ESP_ERR_MESH_NOT_INIT
 *    - ESP_ERR_MESH_NOT_CONFIG
 *    - ESP_ERR_MESH_NO_MEMORY
 */
esp_err_t esp_mesh_start(void);

/**
 * @brief      停止网格
 *             -取消初始化网格IE。
 *             -与当前父级断开连接。
 *             -取消关联所有当前关联的子项。
 *             -停止网状网络管理服务。
 *             -取消注册网格数据包接收回调。
 *             -删除TX和RX队列。
 *             -释放资源。
 *             -如果启用了Wi-Fi双模式，则将Wi-Fi软AP恢复为默认设置。
 *             -将Wi-Fi节能类型设置为WIFI_PS_NONE。
 *
 * @return
 *    - ESP_OK
 *    - ESP_FAIL
 */
esp_err_t esp_mesh_stop(void);

/**
 * @brief      通过网状网络发送数据包
 *             -向网状网络中的任何设备发送数据包。
 *             -向外部IP网络发送数据包。
 *
 * @attention  此API不可重入。
 *
 * @param[in]  to  数据包的最终目的地地址
 *             -如果数据包位于根目录，请将此参数设置为NULL。
 *             -如果数据包指向外部IP网络，请将此参数设置为IPv4:PORT组合。此数据包将首先传递给根，然后根将将此数据包转发到最终的IP服务器地址。
 * @param[in]  data  指向发送网格数据包的指针
 *             -字段大小不应超过MESH_MPS。注意，一个网格数据包的大小不应超过mesh_MTU。
 *             -字段proto应设置为使用中的数据协议（二进制的默认值为MESH_proto_BIN）。
 *             -字段tos应设置为正在使用的传输tos（服务类型）（默认为MESH_tos_P2P，用于点对点可靠）。
 * @param[in]  flag  发送数据的位图
 *             -加快路线搜索
 *               -如果数据包指向根目录并且“to”参数为NULL，请将此参数设置为0。
 *               -如果数据包发送到内部设备，则应设置MESH_DATA_P2P。
 *               -如果数据包指向根（“to”参数不为NULL）或外部IP网络，则应设置MESH_DATA_TODS。
 *               -如果数据包从根到内部设备，则应设置MESH_DATA_FROADS。
 *             -指定此API是块还是非块，默认情况下为块
 *               -如果需要非阻塞，则应设置MESH_DATA_NONBLOCK。否则，可以使用esp_mesh_send_block_time（）指定阻塞时间。
 *             -在根目录更改的情况下，MESH_DATA_DROP确定此数据包可以由新根目录丢弃，以便将上游数据传输到外部IP网络。我们尽最大努力避免根目录更改导致的数据丢失，但存在新根目录内存不足的风险，因为大部分内存被esp_MESH_recv_toDS（）未及时读取的未决数据占用。
 *
 *               通常，我们建议在创建与IP网络的连接后调用esp_mesh_recv_toDS（）。因此，通过套接字输出到外部IP网络的数据只需读取esp_mesh_recv_toDS（）即可避免不必要的内存复制。
 *
 * @param[in]  opt  选项
 *             -在向某个组发送数据包的情况下，MESH_OPT_SEND_group是一个不错的选择。在此选项中，值字段应设置为该组中的目标接收器地址。
 *             -Root向内部设备发送数据包，该数据包来自外部IP网络，以防接收方设备响应该数据包，需要MESH_OPT_RECV_DS_ADDR附加目标DS地址。
 * @param[in]  opt_count  期权计数
 *             -目前，这个API只接受一个选项，因此opt_count只支持为1。
 *
 * @return
 *    - ESP_OK
 *    - ESP_FAIL
 *    - ESP_ERR_MESH_ARGUMENT
 *    - ESP_ERR_MESH_NOT_START
 *    - ESP_ERR_MESH_DISCONNECTED
 *    - ESP_ERR_MESH_OPT_UNKNOWN
 *    - ESP_ERR_MESH_EXCEED_MTU
 *    - ESP_ERR_MESH_NO_MEMORY
 *    - ESP_ERR_MESH_TIMEOUT
 *    - ESP_ERR_MESH_QUEUE_FULL
 *    - ESP_ERR_MESH_NO_ROUTE_FOUND
 *    - ESP_ERR_MESH_DISCARD
 */
esp_err_t esp_mesh_send(const mesh_addr_t *to, const mesh_data_t *data,
                        int flag, const mesh_opt_t opt[],  int opt_count);
/**
 * @brief      设置esp_mesh_send（）的阻塞时间
 *
 * @attention  应在网格启动之前调用此API。
 *
 * @param[in]  time_ms  esp_mesh_send（）的阻塞时间，单位：毫秒
 *
 * @return
 *    - ESP_OK
 */
esp_err_t esp_mesh_send_block_time(uint32_t time_ms);

/**
 * @brief      通过网状网络接收以自身为目标的数据包
 *
 * @attention  应定期检查网状RX队列，以避免内存耗尽。
 *             -使用esp_mesh_get_rx_pending（）检查队列中等待应用程序接收的可用数据包数量。
 *
 * @param[out] from  数据包原始源的地址
 * @param[out] data  指向接收到的网格数据包的指针
 *             -Field proto是使用中的数据协议。应该跟随它来解析接收到的数据。
 *             -字段tos是正在使用的传输tos（服务类型）。
 * @param[in]  timeout_ms  如果数据包不立即可用，则等待时间（0：不等待，portMAX_DELAY：永远等待）
 * @param[out] flag  接收数据的位图
 *             -MESH_DATA_FROADS表示来自外部IP网络的数据
 *             -MESH_DATA_TODS表示网格网络中向上的数据
 *
 *             标志可以是MESH_DATA_FROMDS或MESH_DATA_TODS。
 * @param[out] opt  希望接收的选项
 *             -MESH_OPT_RECV_DS_ADDR附加DS地址
 * @param[in]  opt_count  希望接收的选项计数
 *             -目前，这个API只接受一个选项，因此opt_count只支持为1。
 *
 * @return
 *    - ESP_OK
 *    - ESP_ERR_MESH_ARGUMENT
 *    - ESP_ERR_MESH_NOT_START
 *    - ESP_ERR_MESH_TIMEOUT
 *    - ESP_ERR_MESH_DISCARD
 */
esp_err_t esp_mesh_recv(mesh_addr_t *from, mesh_data_t *data, int timeout_ms,
                        int *flag, mesh_opt_t opt[], int opt_count);

/**
 * @brief      接收以外部IP网络为目标的数据包
 *             -根使用此API接收发送到外部IP网络的数据包
 *             -Root通过套接字将接收到的数据包转发到最终目的地。
 *             -如果没有套接字连接准备好发送接收到的数据包，并且应用程序尚未调用此esp_mesh_recv_toDS（），则来自整个网状网络的数据包将挂在toDS队列中。
 *
 *             使用esp_mesh_get_rx_pending（）检查队列中等待应用程序接收的可用数据包数量，以防根目录内存不足。
 *
 *             使用esp_mesh_set_xon_qsize（），用户可以配置RX队列大小，默认值为32。如果此大小太大，并且没有及时调用esp_mesh_recv_toDS（），则存在挂起数据包占用大量内存的风险。如果该尺寸太小，将影响上游的效率。如何确定该值取决于具体的应用场景。
 *
 * @attention  此API仅由根调用。
 *
 * @param[out] from  数据包原始源的地址
 * @param[out] to  该地址包含远程IP地址和端口（IPv4:port）
 * @param[out] data  指向所接收数据包的指针
 *             -包含协议，应用程序应遵循该协议来解析数据。
 * @param[in]  timeout_ms  如果数据包不立即可用，则等待时间（0：不等待，portMAX_DELAY：永远等待）
 * @param[out] flag  接收数据的位图
 *             -MESH_DATA_TODS表示到外部IP网络的接收数据目标。Root应通过与路由器的关联将此数据转发到外部IP网络。
 *
 *             标志可以是MESH_DATA_TODS。
 * @param[out] opt  希望接收的选项
 * @param[in]  opt_count  希望接收的选项计数
 *
 * @return
 *    - ESP_OK
 *    - ESP_ERR_MESH_ARGUMENT
 *    - ESP_ERR_MESH_NOT_START
 *    - ESP_ERR_MESH_TIMEOUT
 *    - ESP_ERR_MESH_DISCARD
 *    - ESP_ERR_MESH_RECV_RELEASE
 */
esp_err_t esp_mesh_recv_toDS(mesh_addr_t *from, mesh_addr_t *to,
                             mesh_data_t *data, int timeout_ms, int *flag, mesh_opt_t opt[],
                             int opt_count);

/**
 * @brief      设置网格堆栈配置
 *             -使用MESH_INIT_CONFIG_DEFAULT（）初始化默认值，默认情况下会加密网格IE。
 *             -网状网络建立在固定信道（1-14）上。
 *             -网格事件回调是必需的。
 *             -网格ID是MBS的标识符。具有相同网格ID的节点可以彼此通信。
 *             -关于路由器配置，如果路由器是隐藏的，则BSSID字段是必填的。
 *
 *             如果未设置BSSID字段，并且存在多个具有相同SSID的路由器，则可能会出现多个与不同BSSID连接的根。这意味着使用相同的网格ID建立了多个网格网络。
 *
 *             根冲突函数可以消除与相同BSSID连接的冗余根，但不能处理与不同BSSID相连的根。因为用户可能需要设置具有相同SSID的路由器以备将来更换。但在这种情况下，如果发生上述情况，请确保应用程序在根上实现转发功能，以确保不同网格网络中的设备可以相互通信。网状软AP的max_ connection受支持的Wi-Fi软AP的最大数量（最大：10）的限制。
 *
 * @attention  初始化网格后，应在网格启动之前调用该API。
 *
 * @param[in]  config  指向网格堆栈配置的指针
 *
 * @return
 *    - ESP_OK
 *    - ESP_ERR_MESH_ARGUMENT
 *    - ESP_ERR_MESH_NOT_ALLOWED
 */
esp_err_t esp_mesh_set_config(const mesh_cfg_t *config);

/**
 * @brief      获取网格堆栈配置
 *
 * @param[out] config  指向网格堆栈配置的指针
 *
 * @return
 *    - ESP_OK
 *    - ESP_ERR_MESH_ARGUMENT
 */
esp_err_t esp_mesh_get_config(mesh_cfg_t *config);

/**
 * @brief      获取路由器配置
 *
 * @attention  该API用于在配置网格后动态修改路由器配置。
 *
 * @param[in]  router  指向路由器配置的指针
 *
 * @return
 *    - ESP_OK
 *    - ESP_ERR_MESH_ARGUMENT
 */
esp_err_t esp_mesh_set_router(const mesh_router_t *router);

/**
 * @brief      获取路由器配置
 *
 * @param[out] router  指向路由器配置的指针
 *
 * @return
 *    - ESP_OK
 *    - ESP_ERR_MESH_ARGUMENT
 */
esp_err_t esp_mesh_get_router(mesh_router_t *router);

/**
 * @brief      设置网格网络ID
 *
 * @attention  此API用于动态修改网格网络ID。
 *
 * @param[in]  id  指向网格网络ID的指针
 *
 * @return
 *    - ESP_OK
 *    -ESP_ERR_MESH_ARGUMENT:参数无效
 */
esp_err_t esp_mesh_set_id(const mesh_addr_t *id);

/**
 * @brief      获取网格网络ID
 *
 * @param[out] id  指向网格网络ID的指针
 *
 * @return
 *    - ESP_OK
 *    - ESP_ERR_MESH_ARGUMENT
 */
esp_err_t esp_mesh_get_id(mesh_addr_t *id);

/**
 * @brief      通过网状网络指定设备类型
 *            -MESH_IDLE：将设备指定为网状网络的自组织节点
 *            -MESH_ROOT：指定网格网络的根节点
 *            -MESH_LEAF：将设备指定为连接到父设备的独立Wi-Fi站点
 *            -MESH_STA：将设备指定为连接到路由器的独立Wi-Fi站点
 *
 * @param[in]  type  设备类型
 *
 * @return
 *    - ESP_OK
 *    - ESP_ERR_MESH_NOT_ALLOWED
 */
esp_err_t esp_mesh_set_type(mesh_type_t type);

/**
 * @brief      通过网状网络获取设备类型
 *
 * @attention  应在收到事件MESH_event_PARTENT_CONNECTED后调用此API。
 *
 * @return     网格类型
 *
 */
mesh_type_t esp_mesh_get_type(void);

/**
 * @brief      设置网络最大层值
 *             -对于树拓扑，最大值为25。
 *             -对于链拓扑，最大值为1000。
 *             -网络最大层限制最大跳数。
 *
 * @attention  应在网格启动之前调用此API。
 *
 * @param[in]  max_layer  最大层值
 *
 * @return
 *    - ESP_OK
 *    - ESP_ERR_MESH_ARGUMENT
 *    - ESP_ERR_MESH_NOT_ALLOWED
 */
esp_err_t esp_mesh_set_max_layer(int max_layer);

/**
 * @brief      获取最大层值
 *
 * @return     最大层值
 */
int esp_mesh_get_max_layer(void);

/**
 * @brief      设置网格软AP密码
 *
 * @attention  应在网格启动之前调用此API。
 *
 * @param[in]  pwd  指向密码的指针
 * @param[in]  len  密码长度
 *
 * @return
 *    - ESP_OK
 *    - ESP_ERR_MESH_ARGUMENT
 *    - ESP_ERR_MESH_NOT_ALLOWED
 */
esp_err_t esp_mesh_set_ap_password(const uint8_t *pwd, int len);

/**
 * @brief      设置网状软AP认证模式
 *
 * @attention  应在网格启动之前调用此API。
 *
 * @param[in]  authmode  身份验证模式
 *
 * @return
 *    - ESP_OK
 *    - ESP_ERR_MESH_ARGUMENT
 *    - ESP_ERR_MESH_NOT_ALLOWED
 */
esp_err_t esp_mesh_set_ap_authmode(wifi_auth_mode_t authmode);

/**
 * @brief      获取mesh-softAP身份验证模式
 *
 * @return     身份验证模式
 */
wifi_auth_mode_t esp_mesh_get_ap_authmode(void);

/**
 * @brief      设置网格最大连接值
 *             -设置网格softAP最大连接=网格最大连接+非网格最大连接
 *
 * @attention  应在网格启动之前调用此API。
 *
 * @param[in]  connections  最大连接数
 *
 * @return
 *    - ESP_OK
 *    - ESP_ERR_MESH_ARGUMENT
 */
esp_err_t esp_mesh_set_ap_connections(int connections);

/**
 * @brief      获取网格最大连接配置
 *
 * @return     最大网格连接数
 */
int esp_mesh_get_ap_connections(void);

/**
 * @brief      获取非网格最大连接配置
 *
 * @return     非网格最大连接数
 */
int esp_mesh_get_non_mesh_connections(void);

/**
 * @brief      通过网格网络获取当前层值
 *
 * @attention  应在收到事件MESH_event_PARTENT_CONNECTED后调用此API。
 *
 * @return     层值
 *
 */
int esp_mesh_get_layer(void);

/**
 * @brief      获取父BSSID
 *
 * @attention  应在收到事件MESH_event_PARTENT_CONNECTED后调用此API。
 *
 * @param[out] bssid  指向父BSSID的指针
 *
 * @return
 *    - ESP_OK
 *    - ESP_FAIL
 */
esp_err_t esp_mesh_get_parent_bssid(mesh_addr_t *bssid);

/**
 * @brief      返回设备是否为网络的根节点
 *
 * @return     真/假
 */
bool esp_mesh_is_root(void);

/**
 * @brief      启用/禁用自组织网络
 *             -自组织网络有三个主要功能：选择根节点；找到一个首选的父母；如果检测到断开连接，则启动重新连接。
 *             -默认情况下启用自组织网络。
 *             -如果禁用了自组织，则用户应通过esp_mesh_set_parent（）为设备设置父级。
 *
 * @attention  此API用于动态修改是否启用自组织。
 *
 * @param[in]  enable  启用或禁用自组织网络
 * @param[in]  select_parent  仅在启用自组织网络时有效。
 *             -如果selectparent设置为true，则root将放弃其网格根状态，并像其他非root设备一样搜索新的父级。
 *
 * @return
 *    - ESP_OK
 *    - ESP_FAIL
 */
esp_err_t esp_mesh_set_self_organized(bool enable, bool select_parent);

/**
 * @brief      返回是否启用自组织网络
 *
 * @return     真/假
 */
bool esp_mesh_get_self_organized(void);

/**
 * @brief      使根设备放弃（放弃）其网格根状态
 *             -主要基于来自外部路由器的RSSI来选择设备的根。
 *             -如果外部路由器条件发生变化，用户可以调用此API来执行根切换。
 *             -在这个API中，用户可以指定一个所需的根地址来替换自己，或者指定一个尝试值来请求当前根发起新一轮投票。在投票过程中，预计会找到一个更好的基层候选人来取代现任候选人。
 *             -如果没有想要的根候选人，投票将尝试指定的次数（至少15次）。如果找不到更好的候选根，请保留当前根。如果找到更好的候选，新的更好的候选将向当前根发送根切换请求，当前根将以根切换确认作出响应。
 *             -之后，新的候选将连接到路由器以成为新的根，前一个根将与路由器断开连接并选择另一个父节点。
 *
 *             根交换机的完成对整个网状网络的中断最小。
 *
 * @attention  此API仅由根调用。
 *
 * @param[in]  vote  表决配置
 *             -如果此参数设置为NULL，则投票将执行默认15次。
 *
 *             -默认情况下，字段百分比阈值为0.9。
 *             -字段is_rc_specified应为false。
 *             -现场尝试应至少15次。
 * @param[in]  reason  暂时只接受MESH_VOTE_REASON_ROOT_INITIATED
 *
 * @return
 *    - ESP_OK
 *    - ESP_ERR_MESH_QUEUE_FULL
 *    - ESP_ERR_MESH_DISCARD
 *    - ESP_FAIL
 */
esp_err_t esp_mesh_waive_root(const mesh_vote_t *vote, int reason);

/**
 * @brief      设置批准成为root用户的投票百分比阈值（默认值：0.9）
 *             -在联网期间，只有获得投票百分比达到此阈值，设备可能是根。
 *
 * @attention  应在网格启动之前调用此API。
 *
 * @param[in]  percentage  投票百分比阈值
 *
 * @return
 *    - ESP_OK
 *    - ESP_FAIL
 */
esp_err_t esp_mesh_set_vote_percentage(float percentage);

/**
 * @brief      获取批准成为root用户的投票百分比阈值
 *
 * @return     百分比阈值
 */
float esp_mesh_get_vote_percentage(void);

/**
 * @brief      设置网格软AP关联过期时间（默认值：10秒）
 *             -如果mesh softAP在这段时间内没有从关联子节点接收到任何数据，mesh softAP将使该子节点处于非活动状态并解除关联。
 *             -如果网格软AP被加密，则该值应设置为更大的值，例如30秒。
 *
 * @param[in]  seconds  过期时间
 *
 * @return
 *    - ESP_OK
 *    - ESP_FAIL
 */
esp_err_t esp_mesh_set_ap_assoc_expire(int seconds);

/**
 * @brief      获取网格软AP关联过期时间
 *
 * @return     秒
 */
int esp_mesh_get_ap_assoc_expire(void);

/**
 * @brief      获取当前网络中的设备总数（包括根）
 *
 * @attention  当网络发生变化时，返回的值可能不正确。
 **
 * @return     设备总数（包括根）
 */
int esp_mesh_get_total_node_num(void);

/**
 * @brief      获取此设备子网络中的设备数（包括自身）
 *
 * @return     此设备子网络上的设备数（包括自身）
 */
int esp_mesh_get_routing_table_size(void);

/**
 * @brief      获取此设备的子网络（包括其自身）的路由表
 *
 * @param[out] mac  指向路由表的指针
 * @param[in]  len  路由表大小（字节）
 * @param[out] size  指向路由表中设备数量的指针（包括自身）
 *
 * @return
 *    - ESP_OK
 *    - ESP_ERR_MESH_ARGUMENT
 */
esp_err_t esp_mesh_get_routing_table(mesh_addr_t *mac, int len, int *size);

/**
 * @brief      将toDS状态发布到网格堆栈
 *
 * @attention  此API仅适用于根。
 *
 * @param[in]  reachable  此状态表示根是否能够访问外部IP网络
 *
 * @return
 *    - ESP_OK
 *    - ESP_FAIL
 */
esp_err_t esp_mesh_post_toDS_state(bool reachable);

/**
 * @brief      返回队列中等待网格堆栈发送的挂起数据包数
 *
 * @param[out] pending  指向TX挂起的指针
 *
 * @return
 *    - ESP_OK
 *    - ESP_FAIL
 */
esp_err_t esp_mesh_get_tx_pending(mesh_tx_pending_t *pending);

/**
 * @brief      返回队列中等待应用程序接收的可用数据包数
 *
 * @param[out] pending  指向RX挂起的指针
 *
 * @return
 *    - ESP_OK
 *    - ESP_FAIL
 */
esp_err_t esp_mesh_get_rx_pending(mesh_rx_pending_t *pending);

/**
 * @brief      返回指定地址可接受的数据包数
 *
 * @param[in]  addr  本人地址或关联子地址
 * @param[out] xseqno_in  从指定地址接收的最后一个数据包的序列号
 *
 * @return    特定地址的upQ数量
 */
int esp_mesh_available_txupQ_num(const mesh_addr_t *addr, uint32_t *xseqno_in);

/**
 * @brief      设置队列数
 *
 * @attention  应在网格启动之前调用此API。
 *
 * @param[in]  qsize  默认值：32（最小值：16）
 *
 * @return
 *    - ESP_OK
 *    - ESP_FAIL
 */
esp_err_t esp_mesh_set_xon_qsize(int qsize);

/**
 * @brief      获取队列大小
 *
 * @return     队列的数量
 */
int esp_mesh_get_xon_qsize(void);

/**
 * @brief      设置是否允许一个网络中存在多个根
 *
 * @param[in]  allowed  是否允许
 *
 * @return
 *    - ESP_OK
 *    - ESP_WIFI_ERR_NOT_INIT
 *    - ESP_WIFI_ERR_NOT_START
 */
esp_err_t esp_mesh_allow_root_conflicts(bool allowed);

/**
 * @brief      检查是否允许一个网络中存在多个根
 *
 * @return     真/假
 */
bool esp_mesh_is_root_conflicts_allowed(void);

/**
 * @brief      设置组ID地址
 *
 * @param[in]  addr  指向新组ID地址的指针
 * @param[in]  num  组ID地址的数量
 *
 * @return
 *    - ESP_OK
 *    - ESP_MESH_ERR_ARGUMENT
 */
esp_err_t esp_mesh_set_group_id(const mesh_addr_t *addr, int num);

/**
 * @brief      删除组ID地址
 *
 * @param[in]  addr  指向已删除组ID地址的指针
 * @param[in]  num  组ID地址的数量
 *
 * @return
 *    - ESP_OK
 *    - ESP_MESH_ERR_ARGUMENT
 */
esp_err_t esp_mesh_delete_group_id(const mesh_addr_t *addr, int num);

/**
 * @brief      获取组ID地址的数量
 *
 * @return     组ID地址的数量
 */
int esp_mesh_get_group_num(void);

/**
 * @brief      获取组ID地址
 *
 * @param[out] addr  指向组ID地址的指针
 * @param[in]  num  组ID地址的数量
 *
 * @return
 *    - ESP_OK
 *    - ESP_MESH_ERR_ARGUMENT
 */
esp_err_t esp_mesh_get_group_list(mesh_addr_t *addr, int num);

/**
 * @brief      检查指定的组地址是否为我的组
 *
 * @return     真/假
 */
bool esp_mesh_is_my_group(const mesh_addr_t *addr);

/**
 * @brief      设置网格网络容量（最大值：1000，默认值：300）
 *
 * @attention  应在网格启动之前调用此API。
 *
 * @param[in]  num  网状网络容量
 *
 * @return
 *    - ESP_OK
 *    - ESP_ERR_MESH_NOT_ALLOWED
 *    - ESP_MESH_ERR_ARGUMENT
 */
esp_err_t esp_mesh_set_capacity_num(int num);

/**
 * @brief      获取网状网络容量
 *
 * @return     网状网络容量
 */
int esp_mesh_get_capacity_num(void);

/**
 * @brief      设置网格IE加密函数
 *
 * @attention  网格初始化后，可以随时调用此API。
 *
 * @param[in]  crypto_funcs  mesh IE的加密函数
 *           -如果crypto_funcs设置为NULL，则网格IE不再加密。
 * @return
 *    - ESP_OK
 */
esp_err_t esp_mesh_set_ie_crypto_funcs(const mesh_crypto_funcs_t *crypto_funcs);

/**
 * @brief      设置网格IE加密密钥
 *
 * @attention  网格初始化后，可以随时调用此API。
 *
 * @param[in]  key  ASCII加密密钥
 * @param[in]  len  长度（字节），范围：8~64
 *
 * @return
 *    - ESP_OK
 *    - ESP_MESH_ERR_ARGUMENT
 */
esp_err_t esp_mesh_set_ie_crypto_key(const char *key, int len);

/**
 * @brief      获取mesh IE加密密钥
 *
 * @param[out] key  ASCII加密密钥
 * @param[in]  len  长度（字节），范围：8~64
 *
 * @return
 *    - ESP_OK
 *    - ESP_MESH_ERR_ARGUMENT
 */
esp_err_t esp_mesh_get_ie_crypto_key(char *key, int len);

/**
 * @brief      在开始根部愈合之前设置延迟时间
 *
 * @param[in]  delay_ms  延迟时间（毫秒）
 *
 * @return
 *    - ESP_OK
 */
esp_err_t esp_mesh_set_root_healing_delay(int delay_ms);

/**
 * @brief      获取网络开始根修复之前的延迟时间
 *
 * @return     延迟时间（毫秒）
 */
int esp_mesh_get_root_healing_delay(void);

/**
 * @brief      启用网络固定根设置
 *             -启用固定根将禁用通过投票自动选择根节点。
 *             -网络中的所有设备应使用相同的固定根设置（启用或禁用）。
 *             -如果启用了固定根，用户应确保为网络指定了根节点。
 *
 * @param[in]  enable  是否启用
 *
 * @return
 *    - ESP_OK
 */
esp_err_t esp_mesh_fix_root(bool enable);

/**
 * @brief      检查是否启用了网络固定根设置
 *             -通过API esp_mesh_fix_Root（）启用/禁用网络固定根设置。
 *             -网络固定根设置也会随着父网络IE中的“标志”值而改变。
 *
 * @return     真/假
 */
bool esp_mesh_is_root_fixed(void);

/**
 * @brief      为设备设置指定的父级
 *
 * @attention  配置网格后，可以随时调用此API。
 *
 * @param[in]  parent  父级配置、SSID和父级的通道是必需的。
 *             -如果设置了BSSID，请确保SSID和BSSID表示相同的父级，否则设备将永远找不到指定的父级。
 * @param[in]  parent_mesh_id  父网格ID，
 *             -如果未设置该值，则使用原始网格ID。
 * @param[in]  my_type  网格类型
 *             -不支持MESH_STA。
 *             -如果设备的父集合与网络配置中的路由器相同，则my_type应设置MESH_ROOT，my_layer应设置MESH_2ROOT_layer。
 * @param[in]  my_layer  网格层
 *             -设备的my_ layer可以在加入网络之后改变。
 *             -如果my_type设置为MESH_NODE，则my_layer应大于MESH_ROOT_layer。
 *             -如果my_type设置为MESH_LEAF，则设备将成为独立的Wi-Fi站点，不再具有扩展网络的能力。
 *
 * @return
 *    - ESP_OK
 *    - ESP_ERR_ARGUMENT
 *    - ESP_ERR_MESH_NOT_CONFIG
 */
esp_err_t esp_mesh_set_parent(const wifi_config_t *parent, const mesh_addr_t *parent_mesh_id, mesh_type_t my_type, int my_layer);

/**
 * @brief      获取一个AP的网状网络IE长度
 *
 * @param[out] len  网状网络IE长度
 *
 * @return
 *    - ESP_OK
 *    - ESP_ERR_WIFI_NOT_INIT
 *    - ESP_ERR_WIFI_ARG
 *    - ESP_ERR_WIFI_FAIL
 */
esp_err_t esp_mesh_scan_get_ap_ie_len(int *len);

/**
 * @brief      获取AP记录
 *
 * @attention  与esp_wifi_scan_get_ap_records（）不同，此API每次只扫描一个ap。参见“manual_networking”示例。
 *
 * @param[out] ap_record  指向一个AP记录的指针
 * @param[out] buffer  指向此AP的网状网络IE的指针
 *
 * @return
 *    - ESP_OK
 *    - ESP_ERR_WIFI_NOT_INIT
 *    - ESP_ERR_WIFI_ARG
 *    - ESP_ERR_WIFI_FAIL
 */
esp_err_t esp_mesh_scan_get_ap_record(wifi_ap_record_t *ap_record, void *buffer);

/**
 * @brief      刷新to_parent队列和to_parent_2p队列中挂起的上游数据包
 *
 * @return
 *    - ESP_OK
 */
esp_err_t esp_mesh_flush_upstream_packets(void);

/**
 * @brief      获取特定子网中的节点数
 *
 * @param[in]  child_mac  此设备的关联子地址
 * @param[out] nodes_num  指向特定子网中节点数的指针
 *
 * @return
 *    - ESP_OK
 *    - ESP_ERR_MESH_NOT_START
 *    - ESP_ERR_MESH_ARGUMENT
 */
esp_err_t esp_mesh_get_subnet_nodes_num(const mesh_addr_t *child_mac, int *nodes_num);

/**
 * @brief      获取特定子网中的节点
 *
 * @param[in]  child_mac  此设备的关联子地址
 * @param[out] nodes  指向特定子网中节点的指针
 * @param[in]  nodes_num  特定子网中的节点数
 *
 * @return
 *    - ESP_OK
 *    - ESP_ERR_MESH_NOT_START
 *    - ESP_ERR_MESH_ARGUMENT
 */
esp_err_t esp_mesh_get_subnet_nodes_list(const mesh_addr_t *child_mac, mesh_addr_t *nodes, int nodes_num);

/**
 * @brief      与当前父级断开连接
 *
 * @return
 *    - ESP_OK
 */
esp_err_t esp_mesh_disconnect(void);

/**
 * @brief      连接到当前父级
 *
 * @return
 *    - ESP_OK
 */
esp_err_t esp_mesh_connect(void);

/**
 * @brief      刷新扫描结果
 *
 * @return
 *    - ESP_OK
 */
esp_err_t esp_mesh_flush_scan_result(void);

/**
 * @brief      使根设备向信标添加信道切换公告元素（CSA IE）
 *             -设置新频道
 *             -设置在更改新频道之前将发送多少带有CSA IE的信标
 *             -启用通道切换功能
 *
 * @attention  此API仅由根调用。
 *
 * @param[in]  new_bssid  如果路由器发生更改，则返回新路由器BSSID
 * @param[in]  csa_newchan  整个网络移动到的新频道号
 * @param[in]  csa_count  信道切换周期（信标计数），单位基于其软AP的信标间隔，默认值为15。
 *
 * @return
 *    - ESP_OK
 */
esp_err_t esp_mesh_switch_channel(const uint8_t *new_bssid, int csa_newchan, int csa_count);

/**
 * @brief      获取路由器BSSID
 *
 * @param[out] router_bssid  指向路由器BSSID的指针
 *
 * @return
 *    - ESP_OK
 *    - ESP_ERR_WIFI_NOT_INIT
 *    - ESP_ERR_WIFI_ARG
 */
esp_err_t esp_mesh_get_router_bssid(uint8_t *router_bssid);

/**
 * @brief      获取TSF时间
 *
 * @return     TSF时间
 */
int64_t esp_mesh_get_tsf_time(void);

/**
 * @brief      设置网格拓扑。默认值为MESH_TOPO_TREE
 *             -MESH_TOPO_CHAIN支持多达1000层
 *
 * @attention  应在网格启动之前调用此API。
 *
 * @param[in]  topo  MESH_TOPO_TREE或MESH_TOPO_3链
 *
 * @return
 *    - ESP_OK
 *    - ESP_MESH_ERR_ARGUMENT
 *    - ESP_ERR_MESH_NOT_ALLOWED
 */
esp_err_t esp_mesh_set_topology(esp_mesh_topology_t topo);

/**
 * @brief      获取网格拓扑
 *
 * @return     MESH_TOPO_TREE或MESH_TOPO_3链
 */
esp_mesh_topology_t esp_mesh_get_topology(void);

/**
 * @brief      启用网格节能功能
 *
 * @attention  应在网格启动之前调用此API。
 *
 * @return
 *    - ESP_OK
 *    - ESP_ERR_WIFI_NOT_INIT
 *    - ESP_ERR_MESH_NOT_ALLOWED
 */
esp_err_t esp_mesh_enable_ps(void);

/**
 * @brief      禁用网格节能功能
 *
 * @attention  应在网格启动之前调用此API。
 *
 * @return
 *    - ESP_OK
 *    - ESP_ERR_WIFI_NOT_INIT
 *    - ESP_ERR_MESH_NOT_ALLOWED
 */
esp_err_t esp_mesh_disable_ps(void);

/**
 * @brief      检查网格节能功能是否已启用
 *
 * @return     真/假
 */
bool esp_mesh_is_ps_enabled(void);

/**
 * @brief      检查设备是否处于活动状态
 *             -如果设备未处于活动状态，则它既不会发送也不会接收帧。
 *
 * @return     真/假
 */
bool esp_mesh_is_device_active(void);

/**
 * @brief      设置设备占空比和类型
 *             -dev_duty值的范围为1到100。默认值为10。
 *             -dev_duty=100，PS将停止。
 *             -dev_duty最好不小于5。
 *             -dev_duty_type可以是MESH_PS_DEVICE_duty_REQUEST或MESH_PS_DEVICE_duty_DEMAND。
 *             -如果dev_duty_type设置为MESH_PS_DEVICE_duty_REQUEST，则设备将使用网络提供的nwk_duty。
 *             -如果dev_duty_type设置为MESH_PS_DEVICE_duty_DEMAND，则设备将使用指定的dev_duty。
 *
 * @attention  网格启动后，可以随时调用此API。
 *
 * @param[in]  dev_duty  设备占空比
 * @param[in]  dev_duty_type  设备PS占空比类型，不接受MESH_PS_NETWORK_duty_MASTER
 *
 * @return
 *    - ESP_OK
 *    - ESP_FAIL
 */
esp_err_t esp_mesh_set_active_duty_cycle(int dev_duty, int dev_duty_type);

/**
 * @brief      获取设备占空比和类型
 *
 * @param[out] dev_duty  设备占空比
 * @param[out] dev_duty_type  设备PS占空比类型
 *
 * @return
 *    - ESP_OK
 */
esp_err_t esp_mesh_get_active_duty_cycle(int* dev_duty, int* dev_duty_type);

/**
 * @brief      设置网络占空比、持续时间和规则
 *             -nwk_duty值的范围为1到100。默认值为10。
 *             -nwkduty是整个网络或上行链路路径将使用的网络占空比。成功设置nwk_duty的设备称为nwk-duty-MASTER。
 *             -duration_mins指定指定的nwkduty将使用多长时间。一旦duration_mins到期，root将接管NWK-DUTY-MASTER。如果现有NWK-DUTY-MASTER离开网络，则根将再次接管NWK-DUTY-MASTER。
 *             -duration_mins=（-1）表示将使用nwk_ duty，直到出现具有不同nwk_。
 *             -只有根可以将duration_mins设置为（-1）。
 *             -如果applied_rule设置为MESH_PS_NETWORK_DUTY_applied_ENTIRE，则整个网络将使用nwk_fduty。
 *             -如果applied_rule设置为MESH_PS_NETWORK_DUTY_applied_UPLINK，则nwk_DUTY将仅由上行链路路径节点使用。
 *             -根不接受MESH_PS_NETWORK_DUTY_APPLIED_UPLINK。
 *             -根用户设置的具有duration_mins（-1）的nwk_duty是整个网络使用的默认网络占空比。
 *
 * @attention  网格启动后，可以随时调用此API。
 *             -在自组织网络中，如果在所有设备中启动网格之前调用此API，则（1）nwk_doity应设置为所有设备的相同值；（2） duration_mins应设置为（-1）；（3） applied_rule应设置为MESH_PS_NETWORK_DUTY_applied_ENTIRE；在投票的根出现后，该根将成为NWK-DUTY-MASTER，并广播NWK-DUTY及其NWK-DUTY-MASTER的身份。
 *             -如果指定了根（FIXED-root），请在根中调用此API，为整个网络提供默认的nwk_aduty。
 *             -加入网络后，任何设备都可以调用此API来更改nwk_dduty、duration_mins或applied_rule。
 *
 * @param[in]  nwk_duty  网络占空比
 * @param[in]  duration_mins  持续时间（单位：分钟）
 * @param[in]  applied_rule  仅支持MESH_PS_NETWORK_DUTY_AppLICED_ENTIRE
 *
 * @return
 *    - ESP_OK
 *    - ESP_FAIL
 */
esp_err_t esp_mesh_set_network_duty_cycle(int nwk_duty, int duration_mins, int applied_rule);

/**
 * @brief      获取网络占空比、持续时间、类型和规则
 *
 * @param[out] nwk_duty  当前网络占空比
 * @param[out] duration_mins  当前nwkduty的持续时间
 * @param[out] dev_duty_type  如果它包括MESH_PS_DEVICE_DUTY_MASTER，则该设备是当前NWK-DUTY-MASTER。
 * @param[out] applied_rule  MESH_PS_NETWORK_DUTY_APPLIED_ENTIRE
 *
 * @return
 *    - ESP_OK
 */
esp_err_t esp_mesh_get_network_duty_cycle(int* nwk_duty, int* duration_mins, int* dev_duty_type, int* applied_rule);

/**
 * @brief      获取正在运行的有效占空比
 *          -根的运行有效占空比为100。
 *          -如果占空比类型设置为MESH_PS_DEVICE_duty_REQUEST，则运行的活动占空比为网络提供的nwk_duty。
 *          -如果占空比类型设置为MESH_PS_DEVICE_duty_DEMAND，则运行的活动占空比为用户指定的dev_duty。
 *          -在网状网络中，设备通常以一定的工作周期（发送、接收和休眠）工作，以降低功耗。运行活动占空比决定信标间隔内的唤醒时间量。在每个信标间隔开始时，所有设备都会醒来，广播信标，如果它们确实有父母或子女的未决数据包，则会发送数据包。请注意，低占空比意味着设备可能在大多数时间都不活动，数据传输的延迟可能更大。
 *
 * @return     运行有效占空比
 */
int esp_mesh_get_running_active_duty_cycle(void);

/**
 * @brief      负载信号
 *
 * @param[in]  fwd_times  转发任务信令分组的次数
 *
 * @return
 *    - ESP_OK
 */
esp_err_t esp_mesh_ps_duty_signaling(int fwd_times);
#ifdef __cplusplus
}
#endif
#endif /* __ESP_MESH_H__ */

