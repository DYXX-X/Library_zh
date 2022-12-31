/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_LL_HCI_
#define H_BLE_LL_HCI_

#ifdef __cplusplus
extern "C" {
#endif

#include "nimble/hci_common.h"

/* 对于支持的命令*/
#define BLE_LL_SUPP_CMD_LEN (42)
extern const uint8_t g_ble_ll_supp_cmds[BLE_LL_SUPP_CMD_LEN];

/* 控制器将发送的最大事件。*/
#define BLE_LL_MAX_EVT_LEN  MYNEWT_VAL(BLE_HCI_EVT_BUF_SIZE)

/*
 * 这决定了允许从主机到控制器的未完成命令的数量。注意：如果不修改代码的其他部分，就无法更改此选项，因为我们当前使用的命令是全局os事件；你需要分配一个这样的池。
 */
#define BLE_LL_CFG_NUM_HCI_CMD_PKTS     (1)

typedef void (*ble_ll_hci_post_cmd_complete_cb)(void);

/* 初始化LL HCI*/
void ble_ll_hci_init(void);

/* 用于确定LE事件是否已启用/禁用*/
bool ble_ll_hci_is_le_event_enabled(unsigned int subev);

/* 用于确定事件是否已启用/禁用*/
bool ble_ll_hci_is_event_enabled(unsigned int evcode);

/* 将事件从控制器发送到主机*/
int ble_ll_hci_event_send(struct ble_hci_ev *hci_ev);

/* 向主机发送包含无操作操作码的命令*/
void ble_ll_hci_send_noop(void);

/* 检查set default phy和set phy命令中的preferref phy掩码*/
int ble_ll_hci_chk_phy_masks(uint8_t all_phys, uint8_t tx_phys, uint8_t rx_phys,
                             uint8_t *txphy, uint8_t *rxphy);

/* 如果正在使用扩展广告HCI命令，则返回true*/
bool ble_ll_hci_adv_mode_ext(void);

/* 将TX功率补偿舍入为整数dB*/
int8_t ble_ll_get_tx_pwr_compensation(void);

#ifdef __cplusplus
}
#endif

#endif /* H_BLE_LL_HCI_ */

