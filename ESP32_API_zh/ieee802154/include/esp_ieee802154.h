// 版权所有2021 Espressif Systems（Shanghai）PTE LTD
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

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "esp_ieee802154_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief  初始化IEEE 802.15.4子系统。
 *
 */
void esp_ieee802154_enable(void);

/**
 * @brief  取消IEEE 802.15.4子系统的初始化。
 *
 */
void esp_ieee802154_disable(void);

/**
 * @brief  获取操作通道。
 *
 * @return 频道号（11～26）。
 *
 */
uint8_t esp_ieee802154_get_channel(void);

/**
 * @brief  设置操作通道。
 *
 * @param[in]  channel  频道编号（11-26）。
 *
 */
void esp_ieee802154_set_channnel(uint8_t channel);

/**
 * @brief  获取发射功率。
 *
 * @return 发射功率（dBm）。
 *
 */
int8_t esp_ieee802154_get_txpower(void);

/**
 * @brief  设置发射功率。
 *
 * @param[in]  power  发射功率（dBm）。
 *
 */
void esp_ieee802154_set_txpower(int8_t power);

/**
 * @brief  获得混乱模式。
 *
 * @return
 *      -True已启用混杂模式。
 *      -False混杂模式已禁用。
 *
 */
bool esp_ieee802154_get_promiscuous(void);

/**
 * @brief  设置混杂模式。
 *
 * @param[in]  enable  要设置的混杂模式。
 *
 */
void esp_ieee802154_set_promiscuous(bool enable);

/**
 * @brief  获取IEEE 802.15.4无线电状态。
 *
 * @return  IEEE 802.15.4无线电状态，请参阅esp_ieee802154_state_t。
 *
 */
esp_ieee802154_state_t esp_ieee802154_get_state(void);

/**
 * @brief  将IEEE 802.15.4无线电设置为睡眠状态。
 *
 * @return
 *      -ESP_OK成功。
 *      -由于状态无效，ESP_FAIL失败。
 *
 */
esp_err_t esp_ieee802154_sleep(void);

/**
 * @brief  将IEEE 802.15.4无线电设置为接收状态。
 *
 * @return
 *      -成功时ESP_OK
 *      -由于状态无效，ESP_FAIL失败。
 *
 * 注意：收音机将继续接收，直到收到有效帧。参考esp_ieee802154_receive_done（）。
 *
 */
esp_err_t esp_ieee802154_receive(void);

/**
 * @brief  发送给定帧。
 *
 * @param[in]  frame  指向帧的指针，帧格式：|------------------------------------------------------------------------||Len|MHR|MAC有效负载|FCS ||-----------------------------------------------------------------------|
 * @param[in]  cca    如果是真的，则在传输前执行CCA，否则直接传输帧。
 *
 * @return
 *      -ESP_OK成功。
 *      -由于状态无效，ESP_FAIL失败。
 *
 * 注意：传输结果将通过esp_ieee802154_transmit_done（）或esp_ieee 802154_ttransmit_failed（）报告。
 *
 */
esp_err_t esp_ieee802154_transmit(const uint8_t *frame, bool cca);

/**
 * @brief  设置等待ack帧的时间。
 *
 * @param[in]  timeout  等待ack帧的时间，以符号为单位（16us）。默认值：0x006C，范围：0x0000-0xFFFF。
 *
 */
void esp_ieee802154_set_ack_timeout(uint32_t timeout);

/**
 * @brief  获取设备PAN ID。
 *
 * @return  设备PAN ID。
 *
 */
uint16_t esp_ieee802154_get_panid(void);

/**
 * @brief  设置设备PAN ID。
 *
 * @param[in]  panid  设备PAN ID。
 *
 */
void esp_ieee802154_set_panid(uint16_t panid);

/**
 * @brief  获取设备短地址。
 *
 * @return  设备短地址。
 *
 */
uint16_t esp_ieee802154_get_short_address(void);

/**
 * @brief  设置设备短地址。
 *
 * @param[in]  short_address  设备短地址。
 *
 */
void esp_ieee802154_set_short_address(uint16_t short_address);

/**
 * @brief  获取设备扩展地址。
 *
 * @param[out]  ext_addr  指向设备扩展地址的指针。
 *
 */
void esp_ieee802154_get_extended_address(uint8_t *ext_addr);

/**
 * @brief  设置设备扩展地址。
 *
 * @param[in]  ext_addr  指向设备扩展地址的指针。
 *
 */
void esp_ieee802154_set_extended_address(const uint8_t *ext_addr);

/**
 * @brief  获取设备协调器。
 *
 * @return
 *         -True已启用协调器。
 *         -False协调器已禁用。
 *
 */
bool esp_ieee802154_get_coordinator(void);

/**
 * @brief  设置设备协调器角色。
 *
 * @param[in]  enable  要设置的协调员角色。
 *
 */
void esp_ieee802154_set_coordinator(bool enable);

/**
 * @brief  获取自动帧挂起模式。
 *
 * @return  自动帧挂起模式，请参阅esp_ieee802154_pending_mode_t。
 *
 */
esp_ieee802154_pending_mode_t esp_ieee802154_get_pending_mode(void);

/**
 * @brief  设置自动帧挂起模式。
 *
 * @param[in]  pending_mode  自动帧挂起模式，请参阅esp_ieee802154_pending_mode_t。
 *
 */
void esp_ieee802154_set_pending_mode(esp_ieee802154_pending_mode_t pending_mode);

/**
 * @brief  将地址添加到源匹配表。
 *
 * @param[in]  addr      指向地址的指针。
 * @param[in]  is_short  短地址或扩展地址。
 *
 * @return
 *      -ESP_OK成功。
 *      -如果挂起的表已满，则返回ESP_ERR_NO_MEM。
 *
 */
esp_err_t esp_ieee802154_add_pending_addr(const uint8_t *addr, bool is_short);

/**
 * @brief  从源匹配表中删除地址。
 *
 * @param[in]  addr      指向地址的指针。
 * @param[in]  is_short  短地址或扩展地址。
 *
 * @return
 *      -ESP_OK成功。
 *      -如果未从源匹配表中找到地址，则返回ESP_ERR_NOT_FOUND。
 *
 */
esp_err_t esp_ieee802154_clear_pending_addr(const uint8_t *addr, bool is_short);

/**
 * @brief  将源匹配表清除为空。
 *
 * @param[in]  is_short  清除短地址表或扩展地址表。
 *
 */
void esp_ieee802154_reset_pending_table(bool is_short);

/**
 * @brief  获取CCA阈值。
 *
 * @return  CCA阈值（dBm）。
 *
 */
int8_t esp_ieee802154_get_cca_threshold(void);

/**
 * @brief  设置CCA阈值。
 *
 * @param[in]  cca_threshold  CCA阈值（dBm）。
 *
 */
void esp_ieee802154_set_cca_threshold(int8_t cca_threshold);

/**
 * @brief  获取CCA模式。
 *
 * @return  CCA模式，请参阅esp_ieee802154_CCA_mode_t。
 *
 */
esp_ieee802154_cca_mode_t esp_ieee802154_get_cca_mode(void);

/**
 * @brief  设置CCA模式。
 *
 * @param[in]  cca_mode  CCA模式，请参阅esp_ieee802154_CCA_mode_t。
 *
 */
void esp_ieee802154_set_cca_mode(esp_ieee802154_cca_mode_t cca_mode);

/**
 * @brief  启用rx_on_when_idle模式，收音机将在空闲时接收。
 *
 * @param[in]  enable  启用/禁用rx_on_when_idle模式。
 *
 */
void esp_ieee802154_set_rx_when_idle(bool enable);

/**
 * @brief  获取rx_on_when_idle模式。
 *
 * @return  rx_on_when_idle模式。
 *
 */
bool esp_ieee802154_get_rx_when_idle(void);

/**
 * @brief  执行能量检测。
 *
 * @param[in]  duration  能量检测的持续时间，以符号为单位（16 us）。结果将通过esp_ieee802154_energy_dedetect_done（）报告。
 *
 * @return
 *      -ESP_OK成功。
 *      -由于状态无效，ESP_FAIL失败。
 *
 */
esp_err_t esp_ieee802154_energy_detect(uint32_t duration);


/**以下是IEEE 802.15.4子系统生成的事件，这些事件在ISR上下文中**/
/**
 * @brief  收到一帧。
 *
 * @param[in]  frame  指向接收帧的点，帧格式：|------------------------------------------------------------------------||Len|MHR|MAC有效载荷（无FCS）||-----------------------------------------------------------------------|
 * @param[in]  frame_info  有关接收帧的更多信息，请参阅esp_ieee802154_frame_info_t。
 *
 */
extern void esp_ieee802154_receive_done(uint8_t *frame, esp_ieee802154_frame_info_t *frame_info);

/**
 * @brief  接收到帧的SFD字段。
 *
 */
extern void esp_ieee802154_receive_sfd_done(void);

/**
 * @brief  帧传输成功。
 *
 * @param[in]  frame           指向传输帧的指针。
 * @param[in]  ack             如果未设置发送帧的AR位，则接收到的ACK帧可能为空。
 * @param[in]  ack_frame_info  有关ACK帧的更多信息，请参阅esp_ieee802154_frame_info_t。
 *
 * 注意：请参阅esp_ieee802154_transmit（）。
 *
 */
extern void esp_ieee802154_transmit_done(const uint8_t *frame, const uint8_t *ack, esp_ieee802154_frame_info_t *ack_frame_info);

/**
 * @brief  帧传输失败。
 *
 * @param[in]  frame  指向框架的指针。
 * @param[in]  error  传输失败原因，请参阅esp_ieee802154_tx_error_t。
 *
 * 注意：请参阅esp_ieee802154_transmit（）。
 *
 */
extern void esp_ieee802154_transmit_failed(const uint8_t *frame, esp_ieee802154_tx_error_t error);

/**
 * @brief  传输帧的SFD字段。
 *
 */
extern void esp_ieee802154_transmit_sfd_done(uint8_t *frame);

/**
 * @brief  能量检测完成。
 *
 * @param[in]  power  检测到的功率电平，单位为dBm。
 *
 * 注意：请参阅esp_ieee802154_energy_dedetect（）。
 *
 */
extern void esp_ieee802154_energy_detect_done(int8_t power);

#ifdef __cplusplus
}
#endif

