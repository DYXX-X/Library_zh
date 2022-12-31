// 版权所有2010-2017 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef SMARTCONFIG_ACK_H
#define SMARTCONFIG_ACK_H

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  向手机发送smartconfig ACK。
  *
  * @attention API只能在接收SC_EVENT_GOT_SID_PSWD事件时使用。
  *
  * @param  type: smartconfig类型（ESPTouch或AirKiss）；token：来自手机的token；cellphone_ip：手机的ip地址；
  *
  * @return ESP_OK：成功他人：失败
  */
esp_err_t sc_send_ack_start(smartconfig_type_t type, uint8_t token, uint8_t *cellphone_ip);

/**
  * @brief  停止向手机发送smartconfig ACK。
  */
void sc_send_ack_stop(void);

#ifdef __cplusplus
}
#endif
#endif

