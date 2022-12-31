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

#ifndef __BTC_TASK_H__
#define __BTC_TASK_H__

#include <stdint.h>
#include "bt_common.h"
#include "osi/thread.h"

#if CONFIG_BT_BLUEDROID_ENABLED
#include "common/bt_target.h"
#endif

typedef struct btc_msg {
    uint8_t sig;    //事件信号
    uint8_t aid;    //应用程序id
    uint8_t pid;    //配置文件id
    uint8_t act;    //配置文件操作，在seprerate头文件中定义
    void   *arg;    //btc函数的param或函数param
} btc_msg_t;

typedef struct btc_adv_packet {
    uint8_t addr[6];
    uint8_t addr_type;
} btc_adv_packet_t;

typedef enum {
    BTC_SIG_API_CALL = 0,   // APP TO STACK
    BTC_SIG_API_CB,         // STACK TO APP
    BTC_SIG_NUM,
} btc_sig_t; //btc消息类型

typedef enum {
    BTC_PID_MAIN_INIT = 0,
    BTC_PID_DEV,
    BTC_PID_GATTS,
#if (GATTC_INCLUDED == TRUE)
    BTC_PID_GATTC,
#endif  ///GATTC_INCLUDED == TRUE
    BTC_PID_GATT_COMMON,
    BTC_PID_GAP_BLE,
    BTC_PID_BLE_HID,
    BTC_PID_SPPLIKE,
#if (BLUFI_INCLUDED == TRUE)
    BTC_PID_BLUFI,
#endif  ///BLUFI_INCLUDED == TRUE
    BTC_PID_DM_SEC,
    BTC_PID_ALARM,
#if (CLASSIC_BT_INCLUDED == TRUE)
    BTC_PID_GAP_BT,
    BTC_PID_PRF_QUE,
    BTC_PID_A2DP,
    BTC_PID_AVRC_CT,
    BTC_PID_AVRC_TG,
    BTC_PID_SPP,
    BTC_PID_HD,
    BTC_PID_HH,
#if (BTC_HF_INCLUDED == TRUE)
    BTC_PID_HF,
#endif /* BTC_HF_INCLUDED */
#if (BTC_HF_CLIENT_INCLUDED == TRUE)
    BTC_PID_HF_CLIENT,
#endif /* BTC_HF_CLIENT_INCLUDED */
#endif  /* CLASSIC_BT_INCLUDED */
#if CONFIG_BLE_MESH
    BTC_PID_PROV,
    BTC_PID_MODEL,
    BTC_PID_HEALTH_CLIENT,
    BTC_PID_HEALTH_SERVER,
    BTC_PID_CONFIG_CLIENT,
    BTC_PID_CONFIG_SERVER,
    BTC_PID_GENERIC_CLIENT,
    BTC_PID_LIGHTING_CLIENT,
    BTC_PID_SENSOR_CLIENT,
    BTC_PID_TIME_SCENE_CLIENT,
    BTC_PID_GENERIC_SERVER,
    BTC_PID_LIGHTING_SERVER,
    BTC_PID_SENSOR_SERVER,
    BTC_PID_TIME_SCENE_SERVER,
    BTC_PID_BLE_MESH_BLE_COEX,
#endif /* CONFIG_BLE_MESH */
    BTC_PID_NUM,
} btc_pid_t; //btc配置文件id

typedef struct {
    void (* btc_call)(btc_msg_t *msg);
    void (* btc_cb)(btc_msg_t *msg);
} btc_func_t;

typedef void (* btc_arg_deep_copy_t)(btc_msg_t *msg, void *dst, void *src);

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 将消息传输到不同任务中的另一个模块。
 * @param  msg       消息
 * @param  arg       参数
 * @param  arg_len   参数长度
 * @param  copy_func 深度复制函数
 * @return           BT_STATUS_SSUCCESS：成功其他：失败
 */
bt_status_t btc_transfer_context(btc_msg_t *msg, void *arg, int arg_len, btc_arg_deep_copy_t copy_func);

/**
 * 将消息传送到同一任务中的另一个模块。
 * @param  msg       消息
 * @param  arg       参数
 * @return           BT_STATUS_SSUCCESS：成功其他：失败
 */
bt_status_t btc_inter_profile_call(btc_msg_t *msg, void *arg);

bt_status_t btc_init(void);
void btc_deinit(void);
bool btc_check_queue_is_congest(void);
int get_btc_work_queue_size(void);

#ifdef __cplusplus
}
#endif

#endif /* __BTC_TASK_H__ */

