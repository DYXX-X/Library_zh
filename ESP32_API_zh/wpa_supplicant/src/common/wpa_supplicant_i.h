/*
 * wpa_supplicant-内部定义版权所有（c）2003-2014，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef WPA_SUPPLICANT_I_H
#define WPA_SUPPLICANT_I_H


#include "drivers/driver.h"
#include "common/ieee802_11_defs.h"
/*
 * struct rrm_data-用于管理rrm功能的数据
 */
struct rrm_data {
	/* rrm_used-关于当前连接的指示*/
	unsigned int rrm_used:1;

	/*
	 * notify_neighbor_rep—通知报告请求者的回调
	 */
	void (*notify_neighbor_rep)(void *ctx, const u8 *neighbor_rep, size_t len);

	/*
	 * neighbor_rep_cb_ctx-回调上下文在回调注册中接收，并作为参数发送给回调函数。
	 */
	void *neighbor_rep_cb_ctx;

	/* next_nighbor_rep_token-下一个请求的对话令牌*/
	u8 next_neighbor_rep_token;

	/* token-当前无线电测量的对话框标记*/
	u8 token;

	/* 当前无线电测量请求的目标地址*/
	u8 dst_addr[ETH_ALEN];
};

struct wpa_bss_tmp_disallowed {
	struct dl_list list;
	u8 bssid[ETH_ALEN];
#ifndef ESP_SUPPLICANT
	int rssi_threshold;
#else
	esp_timer_handle_t blacklist_timer;
#endif
};

#define SSID_MAX_LEN 32
struct beacon_rep_data {
	u8 token;
	u8 last_indication;
	struct wpa_driver_scan_params scan_params;
	u8 ssid[SSID_MAX_LEN];
	size_t ssid_len;
	u8 bssid[ETH_ALEN];
	enum beacon_report_detail report_detail;
	struct bitfield *eids;
};

enum scan_trigger_reason {
	REASON_INVALID,
	REASON_RRM_BEACON_REPORT,
	REASON_WNM_BSS_TRANS_REQ,
};

struct wpa_supplicant {
	int disable_btm;
	unsigned int disable_mbo_oce;
	/* rrm ie公司*/
	uint8_t rrm_ie[5];
	u8 extend_caps[8];

	int scanning;
	enum scan_trigger_reason scan_reason;
	u64 scan_start_tsf;
	u8 tsf_bssid[ETH_ALEN];
	struct wpa_bss *current_bss;

	struct dl_list bss; /* 结构wpa\bss:：列表*/
	struct dl_list bss_id; /* 结构wpa\bss:：list_id*/
	size_t num_bss;
	unsigned int bss_update_idx;
	unsigned int bss_next_id;

	 /*
	  * 按上次扫描结果中的顺序指向BSS条目的指针。
	  */
	struct wpa_bss **last_scan_res;
	unsigned int last_scan_res_used;
	unsigned int last_scan_res_size;
	struct os_reltime last_scan;

	struct os_reltime scan_trigger_time, scan_start_time;

	u8 next_scan_bssid[ETH_ALEN];
	/* 请求方已注册的帧的类型和子类型*/
	uint32_t type, subtype;
	u8 next_scan_chan;
#ifdef CONFIG_WNM
	u8 wnm_dialog_token;
	u8 wnm_reply;
	u8 wnm_num_neighbor_report;
	u8 wnm_mode;
	u16 wnm_dissoc_timer;
	u8 wnm_bss_termination_duration[12];
	struct neighbor_report *wnm_neighbor_report_elements;
	struct os_reltime wnm_cand_valid_until;
#ifdef CONFIG_MBO
        unsigned int wnm_mbo_trans_reason_present:1;
        u8 wnm_mbo_transition_reason;
	/* 多频带操作非首选信道*/
	struct wpa_mbo_non_pref_channel {
		enum mbo_non_pref_chan_reason reason;
		u8 oper_class;
		u8 chan;
		u8 preference;
	} *non_pref_chan;
	size_t non_pref_chan_num;
	u8 mbo_wnm_token;
	/**
	 * enable_oce-如果用户启用了oce，并且设备也支持oce，则启用oce。用户可以使用wpa_config的“OCE”参数启用OCE，如下所示-
	 *  -设置BIT（0）以在非AP STA模式下启用OCE。
	 *  -设置BIT（1）以在STA-CFON模式下启用OCE。
	 */
	u8 enable_oce;
	struct dl_list bss_tmp_disallowed;
#endif /* CONFIG_MBO */
#endif /* CONFIG_WNM */
	struct rrm_data rrm;
	struct beacon_rep_data beacon_rep_data;
	struct os_reltime beacon_rep_scan;
};

struct non_pref_chan_s;

/* MBO功能*/
int wpas_mbo_ie(struct wpa_supplicant *wpa_s, u8 *buf, size_t len,
		int add_oce_capa);
const u8 * mbo_attr_from_mbo_ie(const u8 *mbo_ie, enum mbo_attr_id attr);
const u8 * wpas_mbo_get_bss_attr(struct wpa_bss *bss, enum mbo_attr_id attr);
const u8 * mbo_get_attr_from_ies(const u8 *ies, size_t ies_len,
				 enum mbo_attr_id attr);
void wpas_mbo_scan_ie(struct wpa_supplicant *wpa_s, struct wpabuf *ie);
void wpas_mbo_ie_trans_req(struct wpa_supplicant *wpa_s, const u8 *ie,
			   size_t len);
size_t wpas_mbo_ie_bss_trans_reject(struct wpa_supplicant *wpa_s, u8 *pos,
				    size_t len,
				    enum mbo_transition_reject_reason reason);
void wpas_mbo_update_cell_capa(struct wpa_supplicant *wpa_s, u8 mbo_cell_capa);
struct wpabuf * mbo_build_anqp_buf(struct wpa_supplicant *wpa_s,
				   struct wpa_bss *bss, u32 mbo_subtypes);
void mbo_parse_rx_anqp_resp(struct wpa_supplicant *wpa_s,
			    struct wpa_bss *bss, const u8 *sa,
			    const u8 *data, size_t slen);
void wpas_update_mbo_connect_params(struct wpa_supplicant *wpa_s);

int wpas_mbo_update_non_pref_chan(struct wpa_supplicant *wpa_s,
				  struct non_pref_chan_s *non_pref_chan);

#endif /* WPA_SUPPLICANT_I_H */

