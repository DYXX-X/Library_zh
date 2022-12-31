/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_HCI_TRANSPORT_
#define H_HCI_TRANSPORT_

#include <inttypes.h>
#include "os/os_mempool.h"

#ifdef __cplusplus
extern "C" {
#endif

struct os_mbuf;

#define BLE_HCI_TRANS_CMD_SZ        260

/***用于保存命令和事件的缓冲区类型。*/
/**
 * 控制器到主机事件缓冲区。事件具有两个优先级之一：o低优先级（BLE_HCI_TRANS_BUF_EVT_LO）o高优先级
 *
 * 低优先级事件缓冲区仅用于广告报告。如果没有可用的低优先级事件缓冲区，则传入的广告报告将被丢弃。
 *
 * 高优先级事件缓冲区用于除广告报告之外的所有内容。如果没有空闲的高优先级事件缓冲区，则请求分配一个缓冲区将尝试分配一个低优先级缓冲区。
 *
 * 如果您希望所有事件都得到同等对待，那么应该只分配低优先级事件。
 *
 * 事件优先级解决了由于广告报告泛滥而导致关键事件丢失的问题。这种解决方案可能是暂时的：当添加HCI流控制时，事件优先级可能会过时。
 *
 * 并非所有传输都区分低优先级事件和高优先级事件。如果传输没有低缓冲区计数和高缓冲区计数的单独设置，那么它将以相同的优先级处理所有事件。
 */
#define BLE_HCI_TRANS_BUF_EVT_LO    1
#define BLE_HCI_TRANS_BUF_EVT_HI    2

/* 主机到控制器命令。*/
#define BLE_HCI_TRANS_BUF_CMD       3

/**回调函数类型；当接收到HCI分组时执行。*/
typedef int ble_hci_trans_rx_cmd_fn(uint8_t *cmd, void *arg);
typedef int ble_hci_trans_rx_acl_fn(struct os_mbuf *om, void *arg);

/**
 * 从控制器向主机发送HCI事件。
 *
 * @param cmd                   要发送的HCI事件。必须通过ble_hci_trans_buf_alloc（）分配此缓冲区。
 *
 * @return                      成功时为0；失败时出现BLE_ERR_[…]错误代码。
 */
int ble_hci_trans_ll_evt_tx(uint8_t *hci_ev);

/**
 * 将ACL数据从控制器发送到主机。
 *
 * @param om                    要发送的ACL数据包。
 *
 * @return                      成功时为0；失败时出现BLE_ERR_[…]错误代码。
 */
int ble_hci_trans_ll_acl_tx(struct os_mbuf *om);

/**
 * 从主机向控制器发送HCI命令。
 *
 * @param cmd                   要发送的HCI命令。必须通过ble_hci_trans_buf_alloc（）分配此缓冲区。
 *
 * @return                      成功时为0；失败时出现BLE_ERR_[…]错误代码。
 */
int ble_hci_trans_hs_cmd_tx(uint8_t *cmd);

/**
 * 将ACL数据从主机发送到控制器。
 *
 * @param om                    要发送的ACL数据包。
 *
 * @return                      成功时为0；失败时出现BLE_ERR_[…]错误代码。
 */
int ble_hci_trans_hs_acl_tx(struct os_mbuf *om);

/**
 * 分配指定类型的平面缓冲区。
 *
 * @param type                  要分配的缓冲区类型；BLE_HCI_TRANS_BUF_[…]常数之一。
 *
 * @return                      成功时分配的缓冲区；缓冲区耗尽时为NULL。
 */
uint8_t *ble_hci_trans_buf_alloc(int type);

/**
 * 释放指定的平面缓冲区。缓冲区必须已通过ble_hci_trans_buf_alloc（）分配。
 *
 * @param buf                   要释放的缓冲区。
 */
void ble_hci_trans_buf_free(uint8_t *buf);

/**
 * 配置回调以在释放ACL数据包时执行。在释放发生之前立即调用该函数。
 *
 * @param cb                    要配置的回调。
 * @param arg                   要传递给回调的可选参数。
 *
 * @return                      成功时为0；如果传输不支持此操作，则返回BLE_ERR_UNSUPPORTED。
 */
int ble_hci_trans_set_acl_free_cb(os_mempool_put_fn *cb, void *arg);

/**
 * 将HCI传输配置为与控制器一起运行。传输将在从主机接收到HCI数据包时执行指定的回调。
 *
 * @param cmd_cb                接收到HCI命令时要执行的回调。
 * @param cmd_arg               传递给命令回调的可选参数。
 * @param acl_cb                接收ACL数据时要执行的回调。
 * @param acl_arg               传递给ACL回调的可选参数。
 */
void ble_hci_trans_cfg_ll(ble_hci_trans_rx_cmd_fn *cmd_cb,
                          void *cmd_arg,
                          ble_hci_trans_rx_acl_fn *acl_cb,
                          void *acl_arg);

/**
 * 将HCI传输配置为与主机一起运行。传输将在从控制器接收到HCI数据包时执行指定的回调。
 *
 * @param evt_cb                接收到HCI事件时要执行的回调。
 * @param evt_arg               传递给事件回调的可选参数。
 * @param acl_cb                接收ACL数据时要执行的回调。
 * @param acl_arg               传递给ACL回调的可选参数。
 */
void ble_hci_trans_cfg_hs(ble_hci_trans_rx_cmd_fn *evt_cb,
                          void *evt_arg,
                          ble_hci_trans_rx_acl_fn *acl_cb,
                          void *acl_arg);

/**
 * 将HCI模块重置为清洁状态。释放所有缓冲区并重新初始化基础传输。
 *
 * @return                      成功时为0；失败时出现BLE_ERR_[…]错误代码。
 */
int ble_hci_trans_reset(void);

#ifdef __cplusplus
}
#endif

#endif /* H_HCI_TRANSPORT_ */

