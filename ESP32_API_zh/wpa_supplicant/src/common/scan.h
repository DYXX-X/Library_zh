/*
 * WPA供应商-扫描版权所有（c）2003-2014，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef SCAN_H
#define SCAN_H

/*
 * 当我们有信号强度测量但没有噪声本底测量时，要使用的噪声本底值。这些值是在有许多AP的办公环境中测量的。
 */
#define DEFAULT_NOISE_FLOOR_2GHZ (-89)

struct wpa_driver_scan_params;
void wpa_supplicant_req_scan(struct wpa_supplicant *wpa_s, int sec, int usec);
int wpa_supplicant_trigger_scan(struct wpa_supplicant *wpa_s,
				struct wpa_driver_scan_params *params);
const u8 * wpa_scan_get_ie(const struct wpa_scan_res *res, u8 ie);
void wpa_scan_free_params(struct wpa_driver_scan_params *params);
#endif /* SCAN_H */

