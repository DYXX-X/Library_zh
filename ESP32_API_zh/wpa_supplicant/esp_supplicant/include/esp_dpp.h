// 版权所有2020 Espressif Systems（上海）私人有限公司
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

#ifndef ESP_DPP_H
#define ESP_DPP_H

#include <stdbool.h>

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ESP_ERR_DPP_FAILURE         (ESP_ERR_WIFI_BASE + 151)   /*!< DPP操作期间的一般故障*/
#define ESP_ERR_DPP_TX_FAILURE      (ESP_ERR_WIFI_BASE + 152)   /*!< DPP帧Tx失败或未确认*/
#define ESP_ERR_DPP_INVALID_ATTR    (ESP_ERR_WIFI_BASE + 153)   /*!< 遇到无效的DPP属性*/

/** @brief DPP的引导方法类型。*/
typedef enum dpp_bootstrap_type {
    DPP_BOOTSTRAP_QR_CODE,  /**<二维码方法*/
    DPP_BOOTSTRAP_PKEX,     /**<知识证明方法*/
    DPP_BOOTSTRAP_NFC_URI,  /**<NFC URI记录方法*/
} esp_supp_dpp_bootstrap_t;

/** @brief 从DPP请求者收到的回调事件类型。*/
typedef enum {
    ESP_SUPP_DPP_URI_READY,     /**＜URI已通过引导准备就绪*/
    ESP_SUPP_DPP_CFG_RECVD,     /**<通过DPP身份验证接收的配置*/
    ESP_SUPP_DPP_FAIL,          /**<DPP身份验证失败*/
} esp_supp_dpp_event_t;

/**
  * @brief 用于从Supplicant接收DPP事件的回调函数。
  *
  *        将使用DPP相关信息调用回调函数。
  *
  * @param evt DPP事件ID
  * @param data 事件数据负载
  */
typedef void (*esp_supp_dpp_event_cb_t)(esp_supp_dpp_event_t evt, void *data);

/**
  * @brief 初始化DPP请求
  *
  *        启动DPP请求程序并初始化相关数据结构。
  *
  * @param evt_cb 用于接收DPP相关事件的回调函数
  *
  * 回来
  *    -ESP_OK：成功
  *    -ESP_FAIL：故障
  */
esp_err_t esp_supp_dpp_init(esp_supp_dpp_event_cb_t evt_cb);

/**
  * @brief 取消DPP请求
  *
  *        从DPP请求数据结构中释放内存。
  */
void esp_supp_dpp_deinit(void);

/**
  * @brief 作为注册人生成引导信息。
  *
  *        生成带外引导信息作为注册人，可由DPP配置器用于配置注册人。
  *
  * @param chan_list 设备可用于收听的频道列表
  * @param type Bootstrap方法类型，目前仅支持QR Code方法。
  * @param key （可选）用于生成引导公钥的私钥
  * @param info （可选）辅助设备信息，如序列号
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_FAIL：故障
  */
esp_err_t
esp_supp_dpp_bootstrap_gen(const char *chan_list, esp_supp_dpp_bootstrap_t type,
                           const char *key, const char *info);

/**
  * @brief 开始收听esp_supp_dpp_bootstrap_gen期间提供的频道。
  *
  *        在预定义的等待时间内收听频道列表中的每个频道。
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_FAIL：一般故障
  *    -ESP_ERR_INVALID_STATE:在启动WiFi之前尝试ROC
  *    -ESP_ERR_NO_MEM:发布ROC请求时内存分配失败
  */
esp_err_t esp_supp_dpp_start_listen(void);

/**
  * @brief 停止收听频道。
  *
  *        停止侦听频道并取消正在进行的侦听操作。
  */
void esp_supp_dpp_stop_listen(void);

#ifdef __cplusplus
}
#endif
#endif /* ESP_DPP_H */

