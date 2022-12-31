/*
 * WPA供应商-通用定义版权所有（c）2004-2015，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef DEFS_H
#define DEFS_H

#ifdef FALSE
#undef FALSE
#endif
#ifdef TRUE
#undef TRUE
#endif
typedef enum { FALSE = 0, TRUE = 1 } Boolean;

#define WPA_CIPHER_NONE                 BIT(0)
#define WPA_CIPHER_WEP40                BIT(7)
#define WPA_CIPHER_WEP104               BIT(8)
#define WPA_CIPHER_TKIP                 BIT(1)
#define WPA_CIPHER_CCMP                 BIT(3)
#define WPA_CIPHER_AES_128_CMAC         BIT(5)
#define WPA_CIPHER_SMS4                 BIT(10)
#define WPA_CIPHER_GCMP                 BIT(11)
#define WPA_CIPHER_GCMP_256             BIT(12)
#define WPA_CIPHER_BIP_GMAC_128         BIT(13)
#define WPA_CIPHER_BIP_GMAC_256         BIT(14)

#define WPA_KEY_MGMT_IEEE8021X BIT(0)
#define WPA_KEY_MGMT_PSK BIT(1)
#define WPA_KEY_MGMT_NONE BIT(2)
#define WPA_KEY_MGMT_IEEE8021X_NO_WPA BIT(3)
#define WPA_KEY_MGMT_WPA_NONE BIT(4)
#define WPA_KEY_MGMT_FT_IEEE8021X BIT(5)
#define WPA_KEY_MGMT_FT_PSK BIT(6)
#define WPA_KEY_MGMT_IEEE8021X_SHA256 BIT(7)
#define WPA_KEY_MGMT_PSK_SHA256 BIT(8)
#define WPA_KEY_MGMT_WPS BIT(9)
#define WPA_KEY_MGMT_SAE BIT(10)
#define WPA_KEY_MGMT_FT_SAE BIT(11)
#define WPA_KEY_MGMT_WAPI_PSK BIT(12)
#define WPA_KEY_MGMT_WAPI_CERT BIT(13)
#define WPA_KEY_MGMT_CCKM BIT(14)
#define WPA_KEY_MGMT_OSEN BIT(15)
#define WPA_KEY_MGMT_IEEE8021X_SUITE_B BIT(16)
#define WPA_KEY_MGMT_IEEE8021X_SUITE_B_192 BIT(17)

static inline int wpa_key_mgmt_wpa_ieee8021x(int akm)
{
	return !!(akm & (WPA_KEY_MGMT_IEEE8021X |
			 WPA_KEY_MGMT_FT_IEEE8021X |
			 WPA_KEY_MGMT_CCKM |
			 WPA_KEY_MGMT_OSEN |
			 WPA_KEY_MGMT_IEEE8021X_SHA256 |
			 WPA_KEY_MGMT_IEEE8021X_SUITE_B |
			 WPA_KEY_MGMT_IEEE8021X_SUITE_B_192));
}

static inline int wpa_key_mgmt_wpa_psk(int akm)
{
	return !!(akm & (WPA_KEY_MGMT_PSK |
			 WPA_KEY_MGMT_FT_PSK |
			 WPA_KEY_MGMT_PSK_SHA256 |
			 WPA_KEY_MGMT_SAE |
			 WPA_KEY_MGMT_FT_SAE));
}

static inline int wpa_key_mgmt_ft(int akm)
{
	return !!(akm & (WPA_KEY_MGMT_FT_PSK |
			 WPA_KEY_MGMT_FT_IEEE8021X |
			 WPA_KEY_MGMT_FT_SAE));
}

static inline int wpa_key_mgmt_sae(int akm)
{
	return !!(akm & (WPA_KEY_MGMT_SAE |
			 WPA_KEY_MGMT_FT_SAE));
}

static inline int wpa_key_mgmt_sha256(int akm)
{
	return !!(akm & (WPA_KEY_MGMT_PSK_SHA256 |
			 WPA_KEY_MGMT_IEEE8021X_SHA256 |
			 WPA_KEY_MGMT_OSEN |
			 WPA_KEY_MGMT_SAE |
			 WPA_KEY_MGMT_IEEE8021X_SUITE_B));
}

static inline int wpa_key_mgmt_sha384(int akm)
{
	return !!(akm & WPA_KEY_MGMT_IEEE8021X_SUITE_B_192);
}

static inline int wpa_key_mgmt_suite_b(int akm)
{
	return !!(akm & (WPA_KEY_MGMT_IEEE8021X_SUITE_B |
			 WPA_KEY_MGMT_IEEE8021X_SUITE_B_192));
}

static inline int wpa_key_mgmt_wpa(int akm)
{
	return wpa_key_mgmt_wpa_ieee8021x(akm) ||
		wpa_key_mgmt_wpa_psk(akm) ||
		wpa_key_mgmt_sae(akm);
}

static inline int wpa_key_mgmt_wpa_any(int akm)
{
	return wpa_key_mgmt_wpa(akm) || (akm & WPA_KEY_MGMT_WPA_NONE);
}

static inline int wpa_key_mgmt_cckm(int akm)
{
	return akm == WPA_KEY_MGMT_CCKM;
}


#define WPA_PROTO_WPA BIT(0)
#define WPA_PROTO_RSN BIT(1)
#define WPA_PROTO_WAPI BIT(2)
#define WPA_PROTO_OSEN BIT(3)

#define WPA_AUTH_ALG_OPEN BIT(0)
#define WPA_AUTH_ALG_SHARED BIT(1)
#define WPA_AUTH_ALG_LEAP BIT(2)
#define WPA_AUTH_ALG_FT BIT(3)
#define WPA_AUTH_ALG_SAE BIT(4)


enum wifi_key_alg {
	ALG_WEP,
	ALG_TKIP,
	ALG_CCMP,
	ALG_AES_CMAC,
};

/**
 * enum wpa_cipher-密码套件
 */
enum wpa_cipher {
	CIPHER_NONE,
	CIPHER_WEP40,
	CIPHER_TKIP,
	CIPHER_CCMP,
	CIPHER_WEP104,
	CIPHER_SMS4,
	CIPHER_GCMP_256,
};

/**
 * enum wpa_key_mgmt-密钥管理套件
 */
enum wpa_key_mgmt {
	KEY_MGMT_802_1X,
	KEY_MGMT_PSK,
	KEY_MGMT_NONE,
	KEY_MGMT_802_1X_NO_WPA,
	KEY_MGMT_WPA_NONE,
	KEY_MGMT_FT_802_1X,
	KEY_MGMT_FT_PSK,
	KEY_MGMT_802_1X_SHA256,
	KEY_MGMT_PSK_SHA256,
	KEY_MGMT_WPS
};

/**
 * 枚举wpa_states-wpa_supplicant状态
 *
 * 这些枚举值用于指示当前wpa_supplicant状态（wpa_s->wpa_state）。可以使用wpa_supplicant_get_state（）函数检索当前状态，并且可以通过调用wpa_ssuplicant_set_state（）来更改状态。在WPA状态机（WPA.c和preauth.c）中，应使用包装函数WPA_sm_get_state（）和WPA_m_set_state（）来访问状态变量。
 */
enum wpa_states {
	/**
	 * WPA_DISCONNECTED-已断开连接状态
	 *
	 * 此状态表示客户端未关联，但可能开始查找访问点。当连接丢失时，将进入此状态。
	 */
	WPA_DISCONNECTED,

	/**
	 * WPA_INTERFACE_DISABLED-接口已禁用
	 *
	 * 如果网络接口被禁用（例如，由于rfkill），则进入此状态。wpasupplicant拒绝使用无线电的任何新操作，直到接口被启用。
	 */
	WPA_INTERFACE_DISABLED,

	/**
	 * WPA_INACTIVE-非活动状态（WPA_supplicant已禁用）
	 *
	 * 如果配置中没有启用的网络，则进入此状态。wpasupplicant没有尝试与新网络关联，需要外部交互（例如，添加或启用网络的ctrliface调用）来启动关联。
	 */
	WPA_INACTIVE,

	/**
	 * WPA_SCANNING-扫描网络
	 *
	 * 当wpa_supplicant开始扫描网络时，将进入此状态。
	 */
	WPA_SCANNING,

	/**
	 * WPA_AUTHENTICATING-尝试使用BSS/SSID进行身份验证
	 *
	 * 当wpa_supplicant找到一个合适的BSS进行身份验证，并且驱动程序配置为尝试使用此BSS进行验证时，将进入此状态。此状态仅用于使用wpa_supplicant作为SME的驱动程序。
	 */
	WPA_AUTHENTICATING,

	/**
	 * WPA_ASSOCIATING-尝试与BSS/SSID关联
	 *
	 * 当wpa_supplicant找到要关联的合适BSS并且驱动程序配置为尝试以ap_scan=1模式与此BSS关联时，将进入此状态。当使用ap_scan=2模式时，当驱动程序配置为尝试使用配置的SSID和安全策略与网络关联时，将进入此状态。
	 */
	WPA_ASSOCIATING,

	/**
	 * WPA_ASSOCIATED-关联已完成
	 *
	 * 当驱动程序报告已成功完成与AP的关联时，将进入此状态。如果使用IEEE 802.1X（有或没有WPA/WPA2），WPA_supplicant将保持此状态，直到完成IEEE 802.1X/EAPOL认证。
	 */
	WPA_ASSOCIATED,

	/**
	 * WPA_4WAY_HANDSHAKE-正在进行WPA 4向密钥握手
	 *
	 * 当WPA/WPA2 4路握手启动时，将进入此状态。在WPA-PSK的情况下，这发生在关联后接收第一个EAPOL密钥帧时。在WPA-EAP的情况下，当IEEE 802.1X/EAPOL认证完成时，进入该状态。
	 */
	WPA_FIRST_HALF_4WAY_HANDSHAKE,

	WPA_LAST_HALF_4WAY_HANDSHAKE,

	/**
	 * WPA_GROUP_HANDSHAKE-正在进行WPA组密钥握手
	 *
	 * 当4向密钥握手完成时（即，当请求方发送消息4/4时），以及当AP开始组密钥重设密钥时（即当请求方接收消息1/2时），进入该状态。
	 */
	WPA_GROUP_HANDSHAKE,

	/**
	 * WPA_COMPLETED-所有身份验证都已完成
	 *
	 * 当完整身份验证过程完成时，将进入此状态。在WPA2的情况下，当4路握手成功完成时，就会发生这种情况。对于WPA，在组密钥握手之后进入该状态；IEEE 802.1X（非WPA）连接在接收到动态密钥之后（或者如果未使用，则在EAP认证完成之后）完成。对于静态WEP密钥和明文连接，当关联完成时，将进入此状态。
	 *
	 * 此状态表示请求方已完成关联阶段的处理，并且数据连接已完全配置。
	 */
	WPA_COMPLETED,

	WPA_MIC_FAILURE,                         // 发生第一个mic_error事件

	WPA_TKIP_COUNTERMEASURES  //在60秒内停止与ap连接的对策期间
};

#define MLME_SETPROTECTION_PROTECT_TYPE_NONE 0
#define MLME_SETPROTECTION_PROTECT_TYPE_RX 1
#define MLME_SETPROTECTION_PROTECT_TYPE_TX 2
#define MLME_SETPROTECTION_PROTECT_TYPE_RX_TX 3

#define MLME_SETPROTECTION_KEY_TYPE_GROUP 0
#define MLME_SETPROTECTION_KEY_TYPE_PAIRWISE 1

/**
 * enum mfp_options-管理帧保护（IEEE 802.11w）选项
 */
enum mfp_options {
	NO_MGMT_FRAME_PROTECTION = 0,
	MGMT_FRAME_PROTECTION_OPTIONAL = 1,
	MGMT_FRAME_PROTECTION_REQUIRED = 2,
};
#define MGMT_FRAME_PROTECTION_DEFAULT 3

/**
 * enum hostapd_hw_mode-硬件模式
 */
enum hostapd_hw_mode {
	HOSTAPD_MODE_IEEE80211B,
	HOSTAPD_MODE_IEEE80211G,
	HOSTAPD_MODE_IEEE80211A,
	HOSTAPD_MODE_IEEE80211AD,
	HOSTAPD_MODE_IEEE80211ANY,
	NUM_HOSTAPD_MODES
};

/**
 * enum wpa\ctrl_req_type-控制接口请求类型
 */
enum wpa_ctrl_req_type {
	WPA_CTRL_REQ_UNKNOWN,
	WPA_CTRL_REQ_EAP_IDENTITY,
	WPA_CTRL_REQ_EAP_PASSWORD,
	WPA_CTRL_REQ_EAP_NEW_PASSWORD,
	WPA_CTRL_REQ_EAP_PIN,
	WPA_CTRL_REQ_EAP_OTP,
	WPA_CTRL_REQ_EAP_PASSPHRASE,
	WPA_CTRL_REQ_SIM,
	WPA_CTRL_REQ_PSK_PASSPHRASE,
	NUM_WPA_CTRL_REQS
};

/* 为EAP服务器用户信息存储的EAP方法的最大数量*/
#define EAP_MAX_METHODS 8

enum mesh_plink_state {
	PLINK_LISTEN = 1,
	PLINK_OPEN_SENT,
	PLINK_OPEN_RCVD,
	PLINK_CNF_RCVD,
	PLINK_ESTAB,
	PLINK_HOLDING,
	PLINK_BLOCKED,
};

enum set_band {
	WPA_SETBAND_AUTO,
	WPA_SETBAND_5G,
	WPA_SETBAND_2G
};

#endif /* DEFS_H */

