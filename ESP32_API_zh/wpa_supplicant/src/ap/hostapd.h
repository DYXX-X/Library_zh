/*
 * hostapd/初始化和配置版权所有（c）2002-2009，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef HOSTAPD_H
#define HOSTAPD_H

#include "common/defs.h"
#include "ap/ap_config.h"

struct wpa_driver_ops;
struct wpa_ctrl_dst;
struct radius_server_data;
struct upnp_wps_device_sm;
struct hostapd_data;
struct sta_info;
struct hostap_sta_driver_data;
struct ieee80211_ht_capabilities;
struct full_dynamic_vlan;
enum wps_event;
union wps_event_data;

struct hostapd_iface;

struct hapd_interfaces {
	int (*reload_config)(struct hostapd_iface *iface);
	struct hostapd_config * (*config_read_cb)(const char *config_fname);
	int (*ctrl_iface_init)(struct hostapd_data *hapd);
	void (*ctrl_iface_deinit)(struct hostapd_data *hapd);
	int (*for_each_interface)(struct hapd_interfaces *interfaces,
				  int (*cb)(struct hostapd_iface *iface,
					    void *ctx), void *ctx);
	int (*driver_init)(struct hostapd_iface *iface);

	size_t count;
	int global_ctrl_sock;
	char *global_iface_path;
	char *global_iface_name;
	struct hostapd_iface **iface;
};


struct hostapd_probereq_cb {
	int (*cb)(void *ctx, const u8 *sa, const u8 *da, const u8 *bssid,
		  const u8 *ie, size_t ie_len, int ssi_signal);
	void *ctx;
};

#define HOSTAPD_RATE_BASIC 0x00000001

struct hostapd_rate_data {
	int rate; /* 速率为100 kbps*/
	int flags; /* HOSTAPD_RATE_标志*/
};

struct hostapd_frame_info {
	u32 channel;
	u32 datarate;
	int ssi_signal; /* 分贝（dBm）*/
};


/**
 * struct hostapd_data-每个BSS数据结构的hostapd
 */
struct hostapd_data {
	struct hostapd_config *iconf;
	struct hostapd_bss_config *conf;
	int interface_added; /* 为此BSS添加的虚拟接口*/

	u8 own_addr[ETH_ALEN];

	int num_sta; /* sta_list中的条目数*/

	struct wpa_authenticator *wpa_auth;

#ifdef CONFIG_FULL_DYNAMIC_VLAN
	struct full_dynamic_vlan *full_dynamic_vlan;
#endif /* CONFIG_FULL_DYNAMIC_VLAN */

#ifdef CONFIG_WPS
	unsigned int ap_pin_failures;
	unsigned int ap_pin_failures_consecutive;
	struct upnp_wps_device_sm *wps_upnp;
	unsigned int ap_pin_lockout_time;
#endif /* CONFIG_WPS */

#ifdef CONFIG_P2P
	struct p2p_data *p2p;
	struct p2p_group *p2p_group;
	struct wpabuf *p2p_beacon_ie;
	struct wpabuf *p2p_probe_resp_ie;

	/* 非P2P关联站点数量*/
	int num_sta_no_p2p;

	/* 周期性NoA（仅在组中没有非P2P客户端时使用）*/
	int noa_enabled;
	int noa_start;
	int noa_duration;
#endif /* CONFIG_P2P */
#ifdef CONFIG_INTERWORKING
	size_t gas_frag_limit;
#endif /* CONFIG_INTERWORKING */

#ifdef CONFIG_SQLITE
	struct hostapd_eap_user tmp_eap_user;
#endif /* CONFIG_SQLITE */
};

#endif /* HOSTAPD_H */

