/*
 * 版权所有2020 Espressif Systems（上海）私人有限公司
 *
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_HS_PVCY_
#define H_BLE_HS_PVCY_

#include "host/ble_hs.h"

#ifdef __cplusplus
extern "C" {
#endif

#if MYNEWT_VAL(BLE_HOST_BASED_PRIVACY)

#define NIMBLE_HOST_DISABLE_PRIVACY            0x00
#define NIMBLE_HOST_ENABLE_RPA                 0x01
#define NIMBLE_HOST_ENABLE_NRPA                0x02

/* 调用以在使用基于主机的隐私时配置本地（自己的）隐私（RPA/NRPA）。在基于主机的隐私中，由于控制器不知道RPA/NRPA地址正在使用中，我们通过“BLE_ADDR_RANDOM（0x01）”ADDR_type路由执行此操作。这是必要的，以便在控制器中将专用地址设置为随机地址。记住在我们的密钥发行版中配置`BLE_SM_PAIR_KEY_DIST_ID`以使用RPA。对于NRPA隐私的一部分，不需要在主机中配置密钥分发，因为无论如何，NRPA是不可解析的。当我们使用主机控制器HCI命令设置专用（RPA/NRPA）地址时，一旦主机控制器同步，请调用此API。
 *
 * 要提供有关如何使用此功能的简要信息，请在使用RPA功能时参考以下步骤：
 *
 * 1.包括“host/ble_hs_pvcy.h”。2.将own_addr_type设置为`BLE_own_addr_RANDOM`。3.将`BLE_SM_PAIR_KEY_DIST_ID`添加到`BLE_hs_cfg中的密钥分布。sm_our_key_dist`&`ble_hs_cfg.sm_ther_key_dist`。4.在主机控制器同步回调中调用`ble_hs_pvcy_rpa_config（1）`。
 *
 * 对于NRPA，步骤1、2和调用ble_hs_pvcy_rpa_config（2）就足够了。
 *
 * @param                enable 当参数=1（NIMBLE_HOST_ENABLE_RPA）时，RPA在参数=2（NIMBL_HOST_ENABLE_NRPA）时启用NRPA，当参数=0（NIMBE_HOST_disable_privacy）时禁用隐私
 *
 * @return               成功时返回0。否则返回相应的错误代码
 */
int ble_hs_pvcy_rpa_config(uint8_t enable);
#endif

#ifdef __cplusplus
}
#endif

#endif

