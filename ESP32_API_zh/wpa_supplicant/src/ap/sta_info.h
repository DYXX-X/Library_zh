/*
 * hostapd/Station table版权所有（c）2002-2011，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef STA_INFO_H
#define STA_INFO_H

/* STA标志*/
#define WLAN_STA_AUTH BIT(0)
#define WLAN_STA_ASSOC BIT(1)
#define WLAN_STA_PS BIT(2)
#define WLAN_STA_TIM BIT(3)
#define WLAN_STA_PERM BIT(4)
#define WLAN_STA_AUTHORIZED BIT(5)
#define WLAN_STA_PENDING_POLL BIT(6) /* 未确认挂起的活动轮询*/
#define WLAN_STA_SHORT_PREAMBLE BIT(7)
#define WLAN_STA_PREAUTH BIT(8)
#define WLAN_STA_WMM BIT(9)
#define WLAN_STA_MFP BIT(10)
#define WLAN_STA_HT BIT(11)
#define WLAN_STA_WPS BIT(12)
#define WLAN_STA_MAYBE_WPS BIT(13)
#define WLAN_STA_WDS BIT(14)
#define WLAN_STA_ASSOC_REQ_OK BIT(15)
#define WLAN_STA_WPS2 BIT(16)
#define WLAN_STA_GAS BIT(17)
#define WLAN_STA_VHT BIT(18)
#define WLAN_STA_PENDING_DISASSOC_CB BIT(29)
#define WLAN_STA_PENDING_DEAUTH_CB BIT(30)
#define WLAN_STA_NONERP BIT(31)

/* 支持费率的最大数量（来自支持费率和扩展支持费率IE）。*/
#define WLAN_SUPP_RATES_MAX 32


struct sta_info {
	struct sta_info *next; /* sta列表中的下一个条目*/
	struct sta_info *hnext; /* 哈希表列表中的下一个条目*/
	u8 addr[6];
	u16 aid; /* STA的唯一AID（1..2007）或0（如果尚未分配）*/
	u32 flags; /* WLAN_STA_*的位字段*/
	u16 capability;
	u16 listen_interval; /* 或AP的beacon_int*/
	u8 supported_rates[WLAN_SUPP_RATES_MAX];
	int supported_rates_len;

	u16 auth_alg;

	enum {
		STA_NULLFUNC = 0, STA_DISASSOC, STA_DEAUTH, STA_REMOVE
	} timeout_next;

	struct wpa_state_machine *wpa_sm;

#ifdef CONFIG_IEEE80211W
	int sa_query_count; /* 挂起的SA查询请求数；0=未进行SA查询*/
	int sa_query_timed_out;
	u8 *sa_query_trans_id; /* WLAN_SA_QUERY_TR_ID_LEN*SA_QUERY_count未决SA查询事务标识符的八位字节缓冲区*/
	struct os_time sa_query_start;
#endif /* CONFIG_IEEE80211W */

#ifdef CONFIG_INTERWORKING
#define GAS_DIALOG_MAX 8 /* 最大并发对话框数*/
	struct gas_dialog_info *gas_dialog;
	u8 gas_dialog_next;
#endif /* CONFIG_INTERWORKING */

#ifdef CONFIG_SAE
	enum { SAE_INIT, SAE_COMMIT, SAE_CONFIRM } sae_state;
	u16 sae_send_confirm;
#endif /* CONFIG_SAE */
};


/* 最大站不活动的默认值。在AP_MAX_INACTIVITY自上一次从站接收到帧以来经过之后，向站发送空函数数据帧。如果此帧未被确认且未接收到其他帧，则在AP_DISASSOC_DELAY秒后，该站将被解除关联。类似地，在解除关联后经过AP_DEAUTH_DELAY秒后，将对站点进行身份验证。*/
#define AP_MAX_INACTIVITY (5 * 60)
#define AP_DISASSOC_DELAY (1)
#define AP_DEAUTH_DELAY (1)
/* 解除关联后，保持STA条目带有Authenticated标志的秒数。*/
#define AP_MAX_INACTIVITY_AFTER_DISASSOC (1 * 30)
/* 取消验证STA条目后保留该条目的秒数。*/
#define AP_MAX_INACTIVITY_AFTER_DEAUTH (1 * 5)


struct hostapd_data;

int ap_for_each_sta(struct hostapd_data *hapd,
		    int (*cb)(struct hostapd_data *hapd, struct sta_info *sta,
			      void *ctx),
		    void *ctx);
struct sta_info * ap_get_sta(struct hostapd_data *hapd, const u8 *sta);
void ap_sta_hash_add(struct hostapd_data *hapd, struct sta_info *sta);
void ap_free_sta(struct hostapd_data *hapd, struct sta_info *sta);
void hostapd_free_stas(struct hostapd_data *hapd);
void ap_handle_timer(void *eloop_ctx, void *timeout_ctx);
void ap_sta_session_timeout(struct hostapd_data *hapd, struct sta_info *sta,
			    u32 session_timeout);
void ap_sta_no_session_timeout(struct hostapd_data *hapd,
			       struct sta_info *sta);
struct sta_info * ap_sta_add(struct hostapd_data *hapd, const u8 *addr);
void ap_sta_disassociate(struct hostapd_data *hapd, struct sta_info *sta,
			 u16 reason);
void ap_sta_deauthenticate(struct hostapd_data *hapd, struct sta_info *sta,
			   u16 reason);
#ifdef CONFIG_WPS
int ap_sta_wps_cancel(struct hostapd_data *hapd,
		      struct sta_info *sta, void *ctx);
#endif /* CONFIG_WPS */
int ap_sta_bind_vlan(struct hostapd_data *hapd, struct sta_info *sta,
		     int old_vlanid);
void ap_sta_start_sa_query(struct hostapd_data *hapd, struct sta_info *sta);
void ap_sta_stop_sa_query(struct hostapd_data *hapd, struct sta_info *sta);
int ap_check_sa_query_timeout(struct hostapd_data *hapd, struct sta_info *sta);
void ap_sta_disconnect(struct hostapd_data *hapd, struct sta_info *sta,
		       const u8 *addr, u16 reason);

void ap_sta_set_authorized(struct hostapd_data *hapd,
			   struct sta_info *sta, int authorized);
static inline int ap_sta_is_authorized(struct sta_info *sta)
{
	return sta->flags & WLAN_STA_AUTHORIZED;
}

void ap_sta_deauth_cb(struct hostapd_data *hapd, struct sta_info *sta);
void ap_sta_disassoc_cb(struct hostapd_data *hapd, struct sta_info *sta);

#endif /* STA_INFO_H */

