/**
 * 版权所有2020 Espressif Systems（上海）私人有限公司
 *
 * 根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef ESP_SCAN_I_H
#define ESP_SCAN_I_H
void esp_scan_init(struct wpa_supplicant *wpa_s);
void esp_scan_deinit(struct wpa_supplicant *wpa_s);
int esp_handle_beacon_probe(u8 type, u8 *frame, size_t len, u8 *sender,
			    u32 rssi, u8 channel, u64 current_tsf);

void esp_supplicant_handle_scan_done_evt(void);
#endif

