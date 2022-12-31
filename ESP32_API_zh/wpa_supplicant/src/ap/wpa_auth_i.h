/*
 * hostapd-IEEE 802.11i-2004/WPA验证器：内部定义版权所有（c）2004-2007，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef WPA_AUTH_I_H
#define WPA_AUTH_I_H

/* 最大值（dot11RSNAConfigGroupUpdateCount，dot11RSNAConfigPairwiseUpdateCount）*/
#define RSNA_MAX_EAPOL_RETRIES 4

struct wpa_group;

struct wpa_stsl_negotiation {
	struct wpa_stsl_negotiation *next;
	u8 initiator[ETH_ALEN];
	u8 peer[ETH_ALEN];
};


struct wpa_state_machine {
	struct wpa_authenticator *wpa_auth;
	struct wpa_group *group;

	u8 addr[ETH_ALEN];

	enum {
		WPA_PTK_INITIALIZE, WPA_PTK_DISCONNECT, WPA_PTK_DISCONNECTED,
		WPA_PTK_AUTHENTICATION, WPA_PTK_AUTHENTICATION2,
		WPA_PTK_INITPMK, WPA_PTK_INITPSK, WPA_PTK_PTKSTART,
		WPA_PTK_PTKCALCNEGOTIATING, WPA_PTK_PTKCALCNEGOTIATING2,
		WPA_PTK_PTKINITNEGOTIATING, WPA_PTK_PTKINITDONE
	} wpa_ptk_state;

	enum {
		WPA_PTK_GROUP_IDLE = 0,
		WPA_PTK_GROUP_REKEYNEGOTIATING,
		WPA_PTK_GROUP_REKEYESTABLISHED,
		WPA_PTK_GROUP_KEYERROR
	} wpa_ptk_group_state;

	Boolean Init;
	Boolean DeauthenticationRequest;
	Boolean AuthenticationRequest;
	Boolean ReAuthenticationRequest;
	Boolean Disconnect;
	int TimeoutCtr;
	int GTimeoutCtr;
	Boolean TimeoutEvt;
	Boolean EAPOLKeyReceived;
	Boolean EAPOLKeyPairwise;
	Boolean EAPOLKeyRequest;
	Boolean MICVerified;
	Boolean GUpdateStationKeys;
	u8 ANonce[WPA_NONCE_LEN];
	u8 SNonce[WPA_NONCE_LEN];
	u8 PMK[PMK_LEN];
	struct wpa_ptk PTK;
	Boolean PTK_valid;
	Boolean pairwise_set;
	int keycount;
	Boolean Pair;
	struct wpa_key_replay_counter {
		u8 counter[WPA_REPLAY_COUNTER_LEN];
		Boolean valid;
	} key_replay[RSNA_MAX_EAPOL_RETRIES],
		prev_key_replay[RSNA_MAX_EAPOL_RETRIES];
	Boolean PInitAKeys; /* 仅WPA，不在IEEE 802.11i中*/
	Boolean PTKRequest; /* 不在IEEE 802.11i状态机中*/
	Boolean has_GTK;
	Boolean PtkGroupInit; /* PTK组状态机的初始化请求*/

	u8 *last_rx_eapol_key; /* 从IEEE 802.1X标头开始*/
	size_t last_rx_eapol_key_len;

	unsigned int changed:1;
	unsigned int in_step_loop:1;
	unsigned int pending_deinit:1;
	unsigned int started:1;
	unsigned int mgmt_frame_prot:1;
	unsigned int rx_eapol_key_secure:1;
	unsigned int update_snonce:1;
#ifdef CONFIG_IEEE80211R
	unsigned int ft_completed:1;
	unsigned int pmk_r1_name_valid:1;
#endif /* CONFIG_IEEE80211R */
	unsigned int is_wnmsleep:1;

	u8 req_replay_counter[WPA_REPLAY_COUNTER_LEN];
	int req_replay_counter_used;

	u8 *wpa_ie;
	size_t wpa_ie_len;

	enum {
		WPA_VERSION_NO_WPA = 0 /* 未使用WPA*/,
		WPA_VERSION_WPA = 1 /* WPA/IEEE 802.11i/D3.0*/,
		WPA_VERSION_WPA2 = 2 /* WPA2/IEEE 802.11i*/
	} wpa;
	int pairwise; /* 成对密码套件，WPA_cipher_**/
	int wpa_key_mgmt; /* 所选WPA_KEY_MGMT_**/

#ifdef CONFIG_IEEE80211R
	u8 xxkey[PMK_LEN]; /* PSK或MSK的第二个256位*/
	size_t xxkey_len;
	u8 pmk_r1_name[WPA_PMK_NAME_LEN]; /* PMKR1Name源自FT身份验证请求*/
	u8 r0kh_id[FT_R0KH_ID_MAX_LEN]; /* 来自FT身份验证请求的R0KH-ID*/
	size_t r0kh_id_len;
	u8 sup_pmk_r1_name[WPA_PMK_NAME_LEN]; /* 来自EAPOL密钥消息的PMKR1名称2/4*/
	u8 *assoc_resp_ftie;
#endif /* CONFIG_IEEE80211R */

	int pending_1_of_4_timeout;
	u32 index;
	ETSTimer resend_eapol;
	struct rsn_sppamsdu_sup spp_sup;
};


/* 每组密钥状态机数据*/
struct wpa_group {
	struct wpa_group *next;
	int vlan_id;

	Boolean GInit;
	int GKeyDoneStations;
	Boolean GTKReKey;
	int GTK_len;
	int GN, GM;
	Boolean GTKAuthenticator;
	u8 Counter[WPA_NONCE_LEN];

	enum {
		WPA_GROUP_GTK_INIT = 0,
		WPA_GROUP_SETKEYS, WPA_GROUP_SETKEYSDONE
	} wpa_group_state;

	u8 GMK[WPA_GMK_LEN];
	u8 GTK[2][WPA_GTK_MAX_LEN];
	u8 GNonce[WPA_NONCE_LEN];
	Boolean changed;
	Boolean first_sta_seen;
	Boolean reject_4way_hs_for_entropy;
#ifdef CONFIG_IEEE80211W
	u8 IGTK[2][WPA_IGTK_LEN];
	int GN_igtk, GM_igtk;
#endif /* CONFIG_IEEE80211W */
};


struct wpa_ft_pmk_cache;

/* 每个验证器数据*/
struct wpa_authenticator {
	struct wpa_group *group;

	struct wpa_auth_config conf;

	u8 *wpa_ie;
	size_t wpa_ie_len;

	u8 addr[ETH_ALEN];

};


int wpa_write_rsn_ie(struct wpa_auth_config *conf, u8 *buf, size_t len,
		     const u8 *pmkid);
void __wpa_send_eapol(struct wpa_authenticator *wpa_auth,
		      struct wpa_state_machine *sm, int key_info,
		      const u8 *key_rsc, const u8 *nonce,
		      const u8 *kde, size_t kde_len,
		      int keyidx, int encr, int force_version);
int wpa_auth_for_each_sta(struct wpa_authenticator *wpa_auth,
			  int (*cb)(struct wpa_state_machine *sm, void *ctx),
			  void *cb_ctx);
int wpa_auth_for_each_auth(struct wpa_authenticator *wpa_auth,
			   int (*cb)(struct wpa_authenticator *a, void *ctx),
			   void *cb_ctx);

#ifdef CONFIG_PEERKEY
int wpa_stsl_remove(struct wpa_authenticator *wpa_auth,
		    struct wpa_stsl_negotiation *neg);
void wpa_smk_error(struct wpa_authenticator *wpa_auth,
		   struct wpa_state_machine *sm, struct wpa_eapol_key *key);
void wpa_smk_m1(struct wpa_authenticator *wpa_auth,
		struct wpa_state_machine *sm, struct wpa_eapol_key *key);
void wpa_smk_m3(struct wpa_authenticator *wpa_auth,
		struct wpa_state_machine *sm, struct wpa_eapol_key *key);
#endif /* CONFIG_PEERKEY */

#ifdef CONFIG_IEEE80211R
int wpa_write_mdie(struct wpa_auth_config *conf, u8 *buf, size_t len);
int wpa_write_ftie(struct wpa_auth_config *conf, const u8 *r0kh_id,
		   size_t r0kh_id_len,
		   const u8 *anonce, const u8 *snonce,
		   u8 *buf, size_t len, const u8 *subelem,
		   size_t subelem_len);
int wpa_auth_derive_ptk_ft(struct wpa_state_machine *sm, const u8 *pmk,
			   struct wpa_ptk *ptk);
struct wpa_ft_pmk_cache * wpa_ft_pmk_cache_init(void);
void wpa_ft_pmk_cache_deinit(struct wpa_ft_pmk_cache *cache);
void wpa_ft_install_ptk(struct wpa_state_machine *sm);
#endif /* CONFIG_IEEE80211R */

#endif /* WPA_AUTH_I_H */

