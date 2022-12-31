/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_HS_STOP_
#define H_BLE_HS_STOP_

/** @typedef 故障_停止_故障
 * @brief 回调函数；报告主机停止过程的结果。
 *
 * @param status                主机停止过程的结果。HAL_RESET_[…]代码之一或实现定义的值。
 * @param arg                   启动停止过程时指定的可选参数。
 *
 */
typedef void ble_hs_stop_fn(int status, void *arg);

/**
 * @brief 用于报告停止程序的结果。
 *
 * 这应该用作不透明结构，而不是手动修改。
 */
struct ble_hs_stop_listener {
    ble_hs_stop_fn *fn;
    void *arg;
    SLIST_ENTRY(ble_hs_stop_listener) link;
};

/**
 * @brief 停止BLE主机。
 *
 * 中止所有活动的GAP程序并终止所有打开的连接。连接终止是异步执行的，因此通过提供的侦听器报告此函数的结果。
 *
 * @param listener              要填充的侦听器。此对象的初始值无关紧要，但其生存期必须延长到停止过程完成为止。
 * @param fn                    停止过程完成时要执行的回调。
 * @param arg                   要传递给回调的可选参数。
 *
 * @return                      0:停止过程已成功启动。BLE_HS_EBUSY：停止程序已在进行中；当过程完成时，将调用提供的回调。BLE_HS_EALREADY:主机已停止；未调用提供的回调。
 */
int ble_hs_stop(struct ble_hs_stop_listener *listener, 
                ble_hs_stop_fn *fn, void *arg);

#endif

