/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_HS_
#define H_BLE_HS_

/**
 * @brief 蓝牙主机
 * @defgroup bt_host蓝牙主机@{
 */

#include <inttypes.h>
#include "nimble/hci_common.h"
#include "host/ble_att.h"
#include "host/ble_eddystone.h"
#include "host/ble_gap.h"
#include "host/ble_gatt.h"
#include "host/ble_hs_adv.h"
#include "host/ble_hs_id.h"
#include "host/ble_hs_hci.h"
#include "host/ble_hs_log.h"
#include "host/ble_hs_mbuf.h"
#include "host/ble_hs_stop.h"
#include "host/ble_ibeacon.h"
#include "host/ble_l2cap.h"
#include "host/ble_sm.h"
#include "host/ble_store.h"
#include "host/ble_uuid.h"
#include "nimble/nimble_npl.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BLE_HS_FOREVER              INT32_MAX

/**连接句柄不存在*/
#define BLE_HS_CONN_HANDLE_NONE     0xffff

/**
 * @brief 蓝牙主机错误代码
 * @defgroup bt_host_err蓝牙主机错误代码
 *
 * 定义蓝牙主机返回的错误代码。如果错误来自特定组件（如L2CAP或安全管理器），则会根据允许识别组件的基数进行移位@{
 */

#define BLE_HS_EAGAIN               1
#define BLE_HS_EALREADY             2
#define BLE_HS_EINVAL               3
#define BLE_HS_EMSGSIZE             4
#define BLE_HS_ENOENT               5
#define BLE_HS_ENOMEM               6
#define BLE_HS_ENOTCONN             7
#define BLE_HS_ENOTSUP              8
#define BLE_HS_EAPP                 9
#define BLE_HS_EBADDATA             10
#define BLE_HS_EOS                  11
#define BLE_HS_ECONTROLLER          12
#define BLE_HS_ETIMEOUT             13
#define BLE_HS_EDONE                14
#define BLE_HS_EBUSY                15
#define BLE_HS_EREJECT              16
#define BLE_HS_EUNKNOWN             17
#define BLE_HS_EROLE                18
#define BLE_HS_ETIMEOUT_HCI         19
#define BLE_HS_ENOMEM_EVT           20
#define BLE_HS_ENOADDR              21
#define BLE_HS_ENOTSYNCED           22
#define BLE_HS_EAUTHEN              23
#define BLE_HS_EAUTHOR              24
#define BLE_HS_EENCRYPT             25
#define BLE_HS_EENCRYPT_KEY_SZ      26
#define BLE_HS_ESTORE_CAP           27
#define BLE_HS_ESTORE_FAIL          28
#define BLE_HS_EPREEMPTED           29
#define BLE_HS_EDISABLED            30
#define BLE_HS_ESTALLED             31

/**ATT错误的错误基础*/
#define BLE_HS_ERR_ATT_BASE         0x100

/**将误差转换为ATT基值*/
#define BLE_HS_ATT_ERR(x)           ((x) ? BLE_HS_ERR_ATT_BASE + (x) : 0)

/**HCI错误的错误基础*/
#define BLE_HS_ERR_HCI_BASE         0x200

/**将错误转换为HCI基*/
#define BLE_HS_HCI_ERR(x)           ((x) ? BLE_HS_ERR_HCI_BASE + (x) : 0)

/**L2CAP错误的错误基础*/
#define BLE_HS_ERR_L2C_BASE         0x300

/**将错误转换为L2CAP基*/
#define BLE_HS_L2C_ERR(x)           ((x) ? BLE_HS_ERR_L2C_BASE + (x) : 0)

/**本地Security Manager错误的错误库*/
#define BLE_HS_ERR_SM_US_BASE       0x400

/**将错误转换为本地Security Manager基*/
#define BLE_HS_SM_US_ERR(x)         ((x) ? BLE_HS_ERR_SM_US_BASE + (x) : 0)

/**远程（对等）安全管理器错误的错误基础*/
#define BLE_HS_ERR_SM_PEER_BASE     0x500

/**将错误转换为远程（对等）安全管理器基*/
#define BLE_HS_SM_PEER_ERR(x)       ((x) ? BLE_HS_ERR_SM_PEER_BASE + (x) : 0)

/**硬件错误的错误基础*/
#define BLE_HS_ERR_HW_BASE          0x600

/**将错误转换为硬件错误基*/
#define BLE_HS_HW_ERR(x)            (BLE_HS_ERR_HW_BASE + (x))

/**
 * @}
 */

/**
 * @brief 蓝牙主机配置
 * @defgroup bt_host_conf蓝牙主机配置
 *
 * @{
 */

/**
 * @brief 设备的本地输入输出功能
 * @defgroup bt_host_io_local设备的本地输入输出功能
 *
 * @{
 */

/**仅显示IO功能*/
#define BLE_HS_IO_DISPLAY_ONLY              0x00

/**显示是无IO功能*/
#define BLE_HS_IO_DISPLAY_YESNO             0x01

/**仅键盘IO功能*/
#define BLE_HS_IO_KEYBOARD_ONLY             0x02

/**无输入无输出IO功能*/
#define BLE_HS_IO_NO_INPUT_OUTPUT           0x03

/**键盘仅显示IO功能*/
#define BLE_HS_IO_KEYBOARD_DISPLAY          0x04

/**
 * @}
 */

/** @brief 堆栈重置回调
 *
 * @param reason 重置原因代码
 */
typedef void ble_hs_reset_fn(int reason);


/** @brief 堆栈同步回调*/
typedef void ble_hs_sync_fn(void);

/** @brief 蓝牙主机主配置结构
 *
 * 应用程序可以使用它们来配置堆栈。
 *
 * 安全管理器（sm_members）在运行时可配置的唯一原因是简化安全测试。通过在应用程序的syscfg中选择适当的选项来配置这些选项的默认值。
 */
struct ble_hs_cfg {
    /**
     * 在注册每个GATT资源（服务、特征或描述符）时执行的可选回调。
     */
    ble_gatt_register_fn *gatts_register_cb;

    /**
     * 传递给GATT注册回调的可选参数。
     */
    void *gatts_register_arg;

    /**Security Manager本地输入输出功能*/
    uint8_t sm_io_cap;

    /** @brief 安全管理器OOB标志
     *
     * 如果设置了正确的配对请求/响应标志，则将设置。
     */
    unsigned sm_oob_data_flag:1;

    /** @brief 安全管理器债券标志
     *
     * 如果设置了正确的配对请求/响应标志，则将设置。这将导致在绑定期间存储密钥。
     */
    unsigned sm_bonding:1;

    /** @brief 安全管理器MITM标志
     *
     * 如果设置了正确的配对请求/响应标志，则将设置。这导致配对时需要中间人保护。
     */
    unsigned sm_mitm:1;

    /** @brief Security Manager安全连接标志
     *
     * 如果设置了正确的配对请求/响应标志，则将设置。如果远程设备也支持，这将导致使用LE安全连接进行配对。如果远程不支持，则回退到传统配对。
     */
    unsigned sm_sc:1;

    /** @brief Security Manager按键通知标志
     *
     * 当前不受支持，不应设置。
     */
    unsigned sm_keypress:1;

    /** @brief 安全管理器本地密钥分发掩码*/
    uint8_t sm_our_key_dist;

    /** @brief 安全管理器远程密钥分发掩码*/
    uint8_t sm_their_key_dist;

    /** @brief 堆栈重置回调
     *
     * 当主机由于严重错误而重置自身和控制器时，将执行此回调。
     */
    ble_hs_reset_fn *reset_cb;

    /** @brief 堆栈同步回调
     *
     * 此回调在主机和控制器同步时执行。这在启动时和重置后发生。
     */
    ble_hs_sync_fn *sync_cb;

    /* 三十： 这些需要消失。相反，灵活的主机包应该需要主机存储API（尚未实现）。。
     */
    /**存储读取回调处理安全材料的读取*/
    ble_store_read_fn *store_read_cb;

    /**存储写入回调处理安全材料的写入*/
    ble_store_write_fn *store_write_cb;

    /**存储删除回调处理安全材料的删除*/
    ble_store_delete_fn *store_delete_cb;

    /** @brief 存储状态回调。
     *
     * 当无法执行持久性操作或即将发生持久性失败时，将执行此回调。例如，如果存储容量不足，无法持久化记录，则调用此函数以给应用程序留出空间。
     */
    ble_store_status_fn *store_status_cb;

    /**传递给存储状态回调的可选参数。*/
    void *store_status_arg;
};

extern struct ble_hs_cfg ble_hs_cfg;

/**
 * @}
 */

/**
 * @brief 指示主机是否已启用。如果主机正在启动或完全启动，则会启用该主机。如果停止或停止，则禁用。
 *
 * @return 如果主机已启用，则为1；如果主机已禁用，则为0。
 */
int ble_hs_is_enabled(void);

/**
 * 指示主机是否已与控制器同步。必须在执行任何主机过程之前进行同步。
 *
 * @return 如果主机和控制器同步，则为1；如果主机和控制器不同步，则为0。
 */
int ble_hs_synced(void);

/**
 * 通过发送一系列HCI命令使主机与控制器同步。必须在使用任何其他主机功能之前调用此函数，但必须在主机和控制器初始化之后调用此函数。通常，宿主父任务在其任务例程的顶部调用此函数。此函数只能在宿主父任务中调用。从任何任务启动堆栈的安全替代方法是调用“ble_hs_sched_start（）”。
 *
 * 如果主机无法与控制器同步（例如，如果控制器未完全启动），主机将尝试每100毫秒重新同步一次。因此，错误返回代码不一定是致命的。
 *
 * @return 成功时为0；错误时为非零。
 */
int ble_hs_start(void);

/**
 * 将主机启动事件排入默认事件队列。实际的主机启动是在主机父任务中执行的，但在这里使用默认队列可以确保在系统初始化期间调用main（）时，事件不会运行到main（）结束。这允许应用程序同时配置主机包。
 *
 * 如果禁用自动启动，应用程序应使用此函数启动BLE堆栈。只要主机停止，就可以随时调用此函数。当主机成功启动时，将通过ble_hs_cfg通知应用程序。sync_cb回调。
 */
void ble_hs_sched_start(void);

/**
 * 使主机尽快重置NimBLE堆栈。当通过主机重置回调发生重置时，会通知应用程序。
 *
 * @param reason 传递给重置回调的主机错误代码。
 */
void ble_hs_sched_reset(int reason);

/**
 * 为NimBLE主机工作指定指定的事件队列。默认情况下，主机使用默认事件队列并在主任务中运行。如果希望主机在不同的任务中运行，则此函数非常有用。
 *
 * @param evq 用于主机工作的事件队列。
 */
void ble_hs_evq_set(struct ble_npl_eventq *evq);

/**
 * 初始化NimBLE主机。必须在启动操作系统之前调用此函数。NimBLE堆栈需要应用程序任务才能运行。特别是一个应用程序任务被指定为“主机父任务”。除了特定于应用程序的工作外，主机父任务还通过处理主机生成的事件来为NimBLE工作。
 */
void ble_hs_init(void);

/**
 * 取消初始化NimBLE主机。必须在NimBLE主机停止过程完成后调用此函数。
 */
void ble_hs_deinit(void);

/**
 * @brief 在系统关闭时调用。停止BLE主机。
 *
 * @param reason                停机的原因。HAL_RESET_[…]代码之一或实现定义的值。
 *
 * @return                      SYSDOWN_IN_PROGRESS. 
 */
int ble_hs_shutdown(int reason);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif

