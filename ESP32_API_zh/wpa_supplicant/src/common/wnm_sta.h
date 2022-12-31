/*
 * IEEE 802.11v WNM相关功能和结构版权所有（c）2011-2012，高通Atheros，Inc。
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef WNM_STA_H
#define WNM_STA_H

struct measurement_pilot {
	u8 measurement_pilot;
	u8 subelem_len;
	u8 subelems[255];
};

struct multiple_bssid {
	u8 max_bssid_indicator;
	u8 subelem_len;
	u8 subelems[255];
};

struct neighbor_report {
	u8 bssid[ETH_ALEN];
	u32 bssid_info;
	u8 regulatory_class;
	u8 channel_number;
	u8 phy_type;
	u8 preference; /* 如果preference_represent=1，则有效*/
	u16 tsf_offset; /* 如果tsf_represent=1，则有效*/
	u16 beacon_int; /* 如果tsf_represent=1，则有效*/
	char country[2]; /* 如果country_present=1，则有效*/
	u8 rm_capab[5]; /* 如果rm_capab_present=1，则有效*/
	u16 bearing; /* 如果bearing_present=1，则有效*/
	u16 rel_height; /* 如果bearing_present=1，则有效*/
	u32 distance; /* 如果bearing_present=1，则有效*/
	u64 bss_term_tsf; /* 如果bss_term_present=1，则有效*/
	u16 bss_term_dur; /* 如果bss_term_present=1，则有效*/
	unsigned int preference_present:1;
	unsigned int tsf_present:1;
	unsigned int country_present:1;
	unsigned int rm_capab_present:1;
	unsigned int bearing_present:1;
	unsigned int bss_term_present:1;
	unsigned int acceptable:1;
#ifdef CONFIG_MBO
	unsigned int is_first:1;
#endif /* CONFIG_MBO */
	struct measurement_pilot *meas_pilot;
	struct multiple_bssid *mul_bssid;
	int freq;
};


int ieee802_11_send_wnmsleep_req(struct wpa_supplicant *wpa_s,
				 u8 action, u16 intval, struct wpabuf *tfs_req);

void ieee802_11_rx_wnm_action(struct wpa_supplicant *wpa_s,
			      u8 *sender, u8 *payload, size_t len);

void wpas_mbo_ie_trans_req(struct wpa_supplicant *wpa_s, const u8 *ie,
			   size_t len);

size_t wpas_mbo_ie_bss_trans_reject(struct wpa_supplicant *wpa_s, u8 *pos,
				    size_t len,
				    enum mbo_transition_reject_reason reason);

int wnm_send_bss_transition_mgmt_query(struct wpa_supplicant *wpa_s,
				       u8 query_reason,
				       const char *btm_candidates,
				       int cand_list);

void wnm_deallocate_memory(struct wpa_supplicant *wpa_s);
int wnm_scan_process(struct wpa_supplicant *wpa_s, int reply_on_fail);
void wnm_bss_tm_connect(struct wpa_supplicant *wpa_s,
			struct wpa_bss *bss, char *ssid,
			int after_new_scan);
int wpa_is_bss_tmp_disallowed(struct wpa_supplicant *wpa_s,
			      struct wpa_bss *bss);

#endif /* WNM_STA_H */

