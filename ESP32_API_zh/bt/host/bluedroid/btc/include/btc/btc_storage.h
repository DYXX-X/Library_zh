// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
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

#ifndef __BTC_STORAGE_H__
#define __BTC_STORAGE_H__

#include <stdint.h>
#include "common/bt_defs.h"
#include "stack/bt_types.h"
#include "esp_gap_bt_api.h"


#define BTC_STORAGE_DEV_CLASS_STR       "DevClass"
#define BTC_STORAGE_LINK_KEY_STR        "LinkKey"    /* 与表相同*/
#define BTC_STORAGE_LINK_KEY_TYPE_STR   "LinkKeyType"
#define BTC_STORAGE_PIN_LENGTH_STR      "PinLength"
#define BTC_STORAGE_SC_SUPPORT          "SCSupport"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
** 函数btc_storage_add_bonded_device
**
** 说明BTC存储API-将新绑定的设备与链接密钥、密钥类型和Pin密钥长度一起添加到NVRAM
**
** 如果存储成功，则返回BT_STATUS_SSUCCESS，否则返回BT_STAS_FAIL
**
*******************************************************************************/
bt_status_t btc_storage_add_bonded_device(bt_bdaddr_t *remote_bd_addr,
        LINK_KEY link_key,
        uint8_t key_type,
        uint8_t pin_length,
        BOOLEAN sc_support);

/*******************************************************************************
** 函数btc_storage_remove_bonded_device
**
** 说明BTC存储API-从NVRAM中删除绑定的设备
**
** 如果删除成功，则返回BT_STATUS_SSUCCESS，否则返回BT_STAS_FAIL
**
*******************************************************************************/
bt_status_t btc_storage_remove_bonded_device(bt_bdaddr_t *remote_bd_addr);

/*******************************************************************************
** 函数btc_storage_remove_bonded_device
**
** 说明BTC存储API-从NVRAM中删除绑定的设备
**
** 如果删除成功，则返回BT_STATUS_SSUCCESS，否则返回BT_STAS_FAIL
**
*******************************************************************************/
bt_status_t btc_storage_load_bonded_devices(void);

/*******************************************************************************
** 函数btc_storage_get_num_bt_bond_devices
**
** 说明BTC存储API-从NVRAM获取绑定设备的编号
**
** 返回绑定设备的num
**
*******************************************************************************/
int btc_storage_get_num_bt_bond_devices(void);

/*******************************************************************************
** 函数btc_storage_get_bonded_bt_devices_list
**
** 说明BTC存储API-从NVRAM获取绑定设备列表
**
** 如果获取列表成功，则返回BT_STATUS_SSUCCESS，否则返回BT_STAS_FAIL
**
*******************************************************************************/
bt_status_t btc_storage_get_bonded_bt_devices_list(bt_bdaddr_t *bond_dev, int *dev_num);

#if (defined BTC_HH_INCLUDED && BTC_HH_INCLUDED == TRUE)
/*******************************************************************************
 * 函数btc_storage_add_hid_device_info
 *
 * 说明BTC存储API-将绑定的hid设备的hid信息添加到NVRAM
 *
 * 如果存储成功，则返回BT_STATUS_SSUCCESS，否则返回BT_STAS_FAIL
 *
 ******************************************************************************/

bt_status_t btc_storage_add_hid_device_info(bt_bdaddr_t *remote_bd_addr, uint16_t attr_mask, uint8_t sub_class,
                                             uint8_t app_id, uint16_t vendor_id, uint16_t product_id, uint16_t version,
                                             uint8_t ctry_code, uint16_t ssr_max_latency, uint16_t ssr_min_tout,
                                             uint16_t dl_len, uint8_t *dsc_list);

/*******************************************************************************
 * 函数btc_storage_load_bonded_hid_info
 *
 * 说明BTIF存储API-从NVRAM加载所有绑定设备的隐藏信息，并将这些设备添加到BTA_HH。
 *
 * 如果成功，则返回BT_STATUS_SSUCCESS，否则返回BT_STSTATUS_FAIL
 *
 ******************************************************************************/
bt_status_t btc_storage_load_bonded_hid_info(void);

/*******************************************************************************
 * 函数btc_storage_remove_hid_info
 *
 * 说明BTC存储API-从NVRAM中删除绑定的隐藏设备信息
 *
 * 如果删除成功，则返回BT_STATUS_SSUCCESS，否则返回BT_STAS_FAIL
 *
 ******************************************************************************/
bt_status_t btc_storage_remove_hid_info(bt_bdaddr_t *remote_bd_addr);
#endif // （定义的BTC_HH_INCLUDE&BTC_HH_inCLUDE==真）

#if (defined BTC_HD_INCLUDED && BTC_HD_INCLUDED == TRUE)
/*******************************************************************************
 * 函数btc_storage_load_hidd
 *
 * 说明加载hidd键合设备并将其“插入”hidd
 *
 * 如果成功，则返回BT_STATUS_SSUCCESS，否则返回BT_STSTATUS_FAIL
 *
 ******************************************************************************/
bt_status_t btc_storage_load_hidd(void);

/*******************************************************************************
 * 函数btc_storage_set_hidd
 *
 * 说明在nvram中存储隐藏绑定的设备信息。
 *
 * 返回BT_STATUS_SSUCCESS
 *
 ******************************************************************************/
bt_status_t btc_storage_set_hidd(bt_bdaddr_t *remote_bd_addr);

/*******************************************************************************
 * 函数btc_storage_remove_hidd
 *
 * 说明从nvram中删除隐藏的绑定设备信息
 *
 * 返回BT_STATUS_SSUCCESS
 *
 ******************************************************************************/
bt_status_t btc_storage_remove_hidd(bt_bdaddr_t *remote_bd_addr);
#endif //（定义的BTC_HD_INCLUDED&&BTC_HD_INCLUDED==TRUE）
#ifdef __cplusplus
}
#endif

#endif /* BTC_STORAGE_H */

