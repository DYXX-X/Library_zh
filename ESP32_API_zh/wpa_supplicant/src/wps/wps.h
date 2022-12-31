/*
 * Wi-Fi保护设置版权所有（c）2007-2012，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef WPS_H
#define WPS_H

#if CONFIG_IDF_TARGET_ESP32
#include "esp32/rom/ets_sys.h" // 将在idf v5.0中删除
#elif CONFIG_IDF_TARGET_ESP32S2
#include "esp32s2/rom/ets_sys.h"
#endif
#include "wps_defs.h"
#include "esp_wifi_types.h"

/**
 * enum wsc_op_code-EAP-wsc op代码值
 */
enum wsc_op_code {
	WSC_UPnP = 0 /* UPnP传输中没有OP代码*/,
	WSC_Start = 0x01,
	WSC_ACK = 0x02,
	WSC_NACK = 0x03,
	WSC_MSG = 0x04,
	WSC_Done = 0x05,
	WSC_FRAG_ACK = 0x06
};

struct wps_registrar;
struct wps_er;
struct wps_parse_attr;

/**
 * 结构wps_credential-wps凭据
 * @ssid: SSID
 * @ssid_len: SSID长度
 * @auth_type: 身份验证类型（WPS_WIFI_AUTH_OPEN，..标志）
 * @encr_type: 加密类型（WPS_ENCR_NONE，..标志）
 * @key_idx: 关键索引
 * @key: 钥匙
 * @key_len: 密钥长度（八位字节）
 * @mac_addr: 凭证接收器的MAC地址
 * @cred_attr: 未分析的凭据属性数据（仅在cred_cb（）中使用）；如果未使用，则可能为%NULL
 * @cred_attr_len: cred_attr的长度（八位字节）
 * @ap_channel: AP通道
 */
struct wps_credential {
	u8 ssid[32];
	size_t ssid_len;
	u16 auth_type;
	u16 encr_type;
	u8 key_idx;
	u8 key[64];
	size_t key_len;
	u8 mac_addr[ETH_ALEN];
	const u8 *cred_attr;
	size_t cred_attr_len;
	u16 ap_channel;
};

#define WPS_DEV_TYPE_LEN 8
#define WPS_DEV_TYPE_BUFSIZE 21
#define WPS_SEC_DEV_TYPE_MAX_LEN 128
/* 通告WPS供应商扩展属性的最大数量*/
#define MAX_WPS_VENDOR_EXTENSIONS 10
/* WPS供应商扩展属性的最大大小*/
#define WPS_MAX_VENDOR_EXT_LEN 1024
/* 已解析WPS供应商扩展属性的最大数量*/
#define MAX_WPS_PARSE_VENDOR_EXT 10

/**
 * 结构wps_device_data-wps设备数据
 * @mac_addr: 设备MAC地址
 * @device_name: 设备名称（0..32个八位字节，以UTF-8编码）
 * @manufacturer: 制造商（0..64个八位字节，以UTF-8编码）
 * @model_name: 型号名称（0..32个八位字节，以UTF-8编码）
 * @model_number: 型号（0..32个八位字节，以UTF-8编码）
 * @serial_number: 序列号（0..32个八位字节，以UTF-8编码）
 * @pri_dev_type: 主要设备类型
 * @sec_dev_type: 辅助设备类型阵列
 * @num_sec_dev_type: 辅助设备类型的数量
 * @os_version: 操作系统版本
 * @rf_bands: RF频段（WPS_RF_24GHZ、WPS_RF_50GHZ标志）
 * @p2p: 设备是否为P2P设备
 */
struct wps_device_data {
	u8 mac_addr[ETH_ALEN];
	char *device_name;
	char *manufacturer;
	char *model_name;
	char *model_number;
	char *serial_number;
	u8 pri_dev_type[WPS_DEV_TYPE_LEN];
#define WPS_SEC_DEVICE_TYPES 5
	u8 sec_dev_type[WPS_SEC_DEVICE_TYPES][WPS_DEV_TYPE_LEN];
	u8 num_sec_dev_types;
	u32 os_version;
	u8 rf_bands;
	u16 config_methods;
	struct wpabuf *vendor_ext_m1;
	struct wpabuf *vendor_ext[MAX_WPS_VENDOR_EXTENSIONS];

	int p2p;
};

/**
 * structwps_config-单个注册协议运行的wps配置
 */
struct wps_config {
	/**
	 * wps-指向长期wps上下文的指针
	 */
	struct wps_context *wps;

	/**
	 * 注册官-这一端是否是注册官
	 */
	int registrar;

	/**
	 * pin-注册人设备密码（对于注册器或PBC为%NULL）
	 */
	const u8 *pin;

	/**
	 * pin_len-管脚长度（八位字节）
	 */
	size_t pin_len;

	/**
	 * pbc-是否使用pbc运行协议
	 */
	int pbc;

	/**
	 * assoc_wps_ie：（Re）AssocReq wps ie（在AP中；如果不是AP，则为%NULL）
	 */
	const struct wpabuf *assoc_wps_ie;

	/**
	 * new_ap_settings-新ap设置（如果未使用，则为NULL）
	 *
	 * 当使用无线站作为注册器配置AP时，此参数提供新的AP设置。%NULL表示AP将不会被重新配置，即，站点将仅通过使用AP PIN来学习当前AP设置。
	 */
	const struct wps_credential *new_ap_settings;

	/**
	 * peer_addr:AP中对等端的MAC地址；%如果不是AP，则为NULL
	 */
	const u8 *peer_addr;

	/**
	 * use_psk_key-在凭据中使用psk格式密钥
	 *
	 * 在为注册人生成凭据时，强制使用PSK格式而不是ASCII密码。PSK值在结构wpa_ctext:：PSK中设置。
	 */
	int use_psk_key;

	/**
	 * dev_pw_id-使用PIN时注册人的设备密码id
	 */
	u16 dev_pw_id;

	/**
	 * p2p_dev_addr-来自（重新）关联请求的p2p设备地址
	 *
	 * 在AP/GO上，如果P2P IE被包括在（重新）关联请求帧中并且P2P设备地址被包括，则这被设置为关联P2P客户端的P2P设备地址。否则，该值设置为%NULL，以指示站点没有P2P设备地址。
	 */
	const u8 *p2p_dev_addr;

	/**
	 * pbc_in_m1-不删除m1（AP）中的PushButton配置方法
	 *
	 * 这可用于启用一种变通方法，允许Windows 7将PBC与AP一起使用。
	 */
	int pbc_in_m1;
};

/* 由于未选择注册表或其他原因而丢弃的丢弃AP的Bsid*/
struct discard_ap_list_t{
	u8 bssid[6];
};

struct wps_data * wps_init(void);

void wps_deinit(void);

/**
 * enum wps_process_res-wps消息处理结果
 */
enum wps_process_res {
	/**
	 * WPS_DONE-处理完成
	 */
	WPS_DONE,

	/**
	 * WPS_CONTINUE-处理继续
	 */
	WPS_CONTINUE,

	/**
	 * WPS_FAILURE-处理失败
	 */
	WPS_FAILURE,

	/**
	 * WPS_PENDING-处理继续，但等待外部事件（例如，来自外部注册器的UPnP消息）
	 */
	WPS_PENDING,
	WPS_IGNORE,     /* snake，忽略重新包装*/

	WPS_FRAGMENT    /* Tim，发送wsc片段ack*/
};
enum wps_process_res wps_process_msg(struct wps_data *wps,
				     enum wsc_op_code op_code,
				     const struct wpabuf *msg);

struct wpabuf * wps_get_msg(struct wps_data *wps, enum wsc_op_code *op_code);

int wps_is_selected_pbc_registrar(const struct wpabuf *msg);
int wps_is_selected_pin_registrar(const struct wpabuf *msg);
int wps_ap_priority_compar(const struct wpabuf *wps_a,
			   const struct wpabuf *wps_b);
int wps_is_addr_authorized(const struct wpabuf *msg, const u8 *addr,
			   int ver1_compat);
const u8 * wps_get_uuid_e(const struct wpabuf *msg);
int wps_is_20(const struct wpabuf *msg);

struct wpabuf * wps_build_assoc_req_ie(enum wps_request_type req_type);
struct wpabuf * wps_build_assoc_resp_ie(void);
struct wpabuf * wps_build_probe_req_ie(u16 pw_id, struct wps_device_data *dev,
				       const u8 *uuid,
				       enum wps_request_type req_type,
				       unsigned int num_req_dev_types,
				       const u8 *req_dev_types);


/**
 * 结构wps_registrar_config-wps注册器配置
 */
struct wps_registrar_config {
	/**
	 * new_psk_cb-新psk的回调
	 * @ctx: 更高层上下文数据（cb_ctx）
	 * @mac_addr: 注册人的MAC地址
	 * @psk: 新PSK
	 * @psk_len: psk的长度（以八位字节为单位）：成功时返回0，失败时返回-1
	 *
	 * 当配置新的每设备PSK时，调用此回调。
	 */
	int (*new_psk_cb)(void *ctx, const u8 *mac_addr, const u8 *psk,
			  size_t psk_len);

	/**
	 * set_ie_cb-WPS ie更改的回调
	 * @ctx: 更高层上下文数据（cb_ctx）
	 * @beacon_ie: 信标WPS IE
	 * @probe_resp_ie: WPS IE探测响应返回：成功时返回0，失败时返回-1
	 *
	 * 每当需要更改信标或探测响应帧中的WPS IE时（仅限AP），就会调用此回调。被调用者负责释放缓冲区。
	 */
	int (*set_ie_cb)(void *ctx, struct wpabuf *beacon_ie,
			 struct wpabuf *probe_resp_ie);

	/**
	 * pin_needed_cb-请求pin的回调
	 * @ctx: 更高层上下文数据（cb_ctx）
	 * @uuid_e: 未知注册人的UUID-E
	 * @dev: 未知注册人的设备数据
	 *
	 * 每当未知注册人请求使用PIN方法，并且在注册器数据中找不到匹配的PIN（设备密码）时，就会调用此回调。
	 */
	void (*pin_needed_cb)(void *ctx, const u8 *uuid_e,
			      const struct wps_device_data *dev);

	/**
	 * reg_success_cb-报告成功注册的回调
	 * @ctx: 更高层上下文数据（cb_ctx）
	 * @mac_addr: 注册人的MAC地址
	 * @uuid_e: 受试者UUID-E
	 * @dev_pw: 注册期间使用的设备密码（PIN）
	 * @dev_pw_len: dev_pw的长度（八位字节）
	 *
	 * 每当注册人成功完成注册时，就会调用此回调。
	 */
	void (*reg_success_cb)(void *ctx, const u8 *mac_addr,
			       const u8 *uuid_e, const u8 *dev_pw,
			       size_t dev_pw_len);

	/**
	 * set_sel_reg_cb-报告所选注册器更改的回调
	 * @ctx: 更高层上下文数据（cb_ctx）
	 * @sel_reg: 是否选择注册官
	 * @dev_passwd_id: 设备密码ID，用于指示注册器打算使用的方法或特定密码
	 * @sel_reg_config_methods: 活动配置方法的位字段
	 *
	 * 每当选定注册器状态发生变化时（例如，新PIN可用或PBC被调用），就会调用此回调。此回调仅由外部注册器实现使用；set_ie_cb（）在类似情况下由AP实现使用，但它提供完整的WPS ie数据，而不仅仅是最小的注册器状态信息。
	 */
	void (*set_sel_reg_cb)(void *ctx, int sel_reg, u16 dev_passwd_id,
			       u16 sel_reg_config_methods);

	/**
	 * enrollee_seen_cb-基于ProbeReq报告enrollee的回调
	 * @ctx: 更高层上下文数据（cb_ctx）
	 * @addr: 注册人的MAC地址
	 * @uuid_e: 受试者UUID
	 * @pri_dev_type: 主要设备类型
	 * @config_methods: 配置方法
	 * @dev_password_id: 设备密码ID
	 * @request_type: 请求类型
	 * @dev_name: 设备名称（如果可用）
	 */
	void (*enrollee_seen_cb)(void *ctx, const u8 *addr, const u8 *uuid_e,
				 const u8 *pri_dev_type, u16 config_methods,
				 u16 dev_password_id, u8 request_type,
				 const char *dev_name);

	/**
	 * cb_ctx:注册器回调的更高层上下文数据
	 */
	void *cb_ctx;

	/**
	 * skip_cred_build:不生成凭据
	 *
	 * 此选项可用于禁用基于当前网络配置和Enrollee功能将Credential属性构建到M8中的内部代码。然后，外部数据将用作凭据。
	 */
	int skip_cred_build;

	/**
	 * extra_cred：其他凭据属性
	 *
	 * 此可选数据（设置为%NULL以禁用）可用于将其他网络的凭据属性添加到M8中。如果设置了skip_cred_build，这也将覆盖自动生成的凭据属性。
	 */
	const u8 *extra_cred;

	/**
	 * extra_cred_len：extra_cred的长度（以八位字节为单位）
	 */
	size_t extra_cred_len;

	/**
	 * disable_auto_conf-在首次注册时禁用自动配置
	 *
	 * 默认情况下，在未配置状态下启动的AP将生成随机PSK，并在第一次注册协议运行成功完成时移动到已配置状态。此选项可用于禁用此功能，并由外部程序负责配置。这需要使用合适的凭据和skip_cred_build设置extra_cred。
	 */
	int disable_auto_conf;

	/**
	 * static_wep_only-BSS是否仅支持静态wep
	 */
	int static_wep_only;

	/**
	 * dualband-是否为并发dualband AP
	 */
	int dualband;
};


/**
 * 枚举wps_event-wps事件类型
 */
enum wps_event {
	/**
	 * WPS_EV_M2D-收到M2D（注册官不认识我们）
	 */
	WPS_EV_M2D,

	/**
	 * WPS_EV_FAIL-注册失败
	 */
	WPS_EV_FAIL,

	/**
	 * WPS_EV_SUCCESS-注册成功
	 */
	WPS_EV_SUCCESS,

	/**
	 * WPS_EV_PWD_AUTH_FAIL-密码验证失败
	 */
	WPS_EV_PWD_AUTH_FAIL,

	/**
	 * WPS_EV_PBC_OVERLAP-检测到PBC会话重叠
	 */
	WPS_EV_PBC_OVERLAP,

	/**
	 * WPS_EV_PBC_TIMEOUT-协议运行开始前PBC步行时间已过期
	 */
	WPS_EV_PBC_TIMEOUT,

	/**
	 * WPS_EV_ER_AP_ADD-ER:AP已添加
	 */
	WPS_EV_ER_AP_ADD,

	/**
	 * WPS_EV_ER_AP_REMOVE-ER:AP已删除
	 */
	WPS_EV_ER_AP_REMOVE,

	/**
	 * WPS_EV_ER_ENROLLEE_ADD-ER:已添加注册人
	 */
	WPS_EV_ER_ENROLLEE_ADD,

	/**
	 * WPS_EV_ER_ENROLLEE_REMOVE-ER:已删除注册人
	 */
	WPS_EV_ER_ENROLLEE_REMOVE,

	/**
	 * WPS_EV_ER_AP_SETTINGS-ER:AP设置已学习
	 */
	WPS_EV_ER_AP_SETTINGS,

	/**
	 * WPS_EV_ER_SET_SELECTED_REGISTRAR-ER:SetSelectedRegistor事件
	 */
	WPS_EV_ER_SET_SELECTED_REGISTRAR,

	/**
	 * WPS_EV_AP_PIN_SUCCESS-外部注册器使用了正确的AP PIN
	 */
	WPS_EV_AP_PIN_SUCCESS
};

/**
 * 联合wps_event_data-wps事件数据
 */
union wps_event_data {
	/**
	 * 结构wps_event_m2d-m2d事件数据
	 */
	struct wps_event_m2d {
		u16 config_methods;
		const u8 *manufacturer;
		size_t manufacturer_len;
		const u8 *model_name;
		size_t model_name_len;
		const u8 *model_number;
		size_t model_number_len;
		const u8 *serial_number;
		size_t serial_number_len;
		const u8 *dev_name;
		size_t dev_name_len;
		const u8 *primary_dev_type; /* 8个八位字节*/
		u16 config_error;
		u16 dev_password_id;
	} m2d;

	/**
	 * 结构wps_event_fail-注册失败信息
	 * @msg: 枚举wps_msg_type
	 */
	struct wps_event_fail {
		int msg;
		u16 config_error;
		u16 error_indication;
	} fail;

	struct wps_event_pwd_auth_fail {
		int enrollee;
		int part;
	} pwd_auth_fail;

	struct wps_event_er_ap {
		const u8 *uuid;
		const u8 *mac_addr;
		const char *friendly_name;
		const char *manufacturer;
		const char *manufacturer_url;
		const char *model_description;
		const char *model_name;
		const char *model_number;
		const char *model_url;
		const char *serial_number;
		const char *upc;
		const u8 *pri_dev_type;
		u8 wps_state;
	} ap;

	struct wps_event_er_enrollee {
		const u8 *uuid;
		const u8 *mac_addr;
		int m1_received;
		u16 config_methods;
		u16 dev_passwd_id;
		const u8 *pri_dev_type;
		const char *dev_name;
		const char *manufacturer;
		const char *model_name;
		const char *model_number;
		const char *serial_number;
	} enrollee;

	struct wps_event_er_ap_settings {
		const u8 *uuid;
		const struct wps_credential *cred;
	} ap_settings;

	struct wps_event_er_set_selected_registrar {
		const u8 *uuid;
		int sel_reg;
		u16 dev_passwd_id;
		u16 sel_reg_config_methods;
		enum {
			WPS_ER_SET_SEL_REG_START,
			WPS_ER_SET_SEL_REG_DONE,
			WPS_ER_SET_SEL_REG_FAILED
		} state;
	} set_sel_reg;
};
#ifdef CONFIG_WPS_UPNP
/**
 * 结构upnp_pending_message-挂起的PutWLANResponse消息
 * @next: 指向下一个挂起消息的指针或%NULL
 * @addr: 新WLAN事件MAC
 * @msg: 新建消息
 * @type: 消息类型
 */
struct upnp_pending_message {
	struct upnp_pending_message *next;
	u8 addr[ETH_ALEN];
	struct wpabuf *msg;
	enum wps_msg_type type;
};
void wps_free_pending_msgs(struct upnp_pending_message *msgs);
#endif
/**
 * 结构wps_context-长期wps上下文数据
 *
 * 该数据存储在更高层的Authenticator或Supplicant数据结构中，并通过多次注册协议运行进行维护。
 */
struct wps_context {
	/**
	 * ap-本地端是否为接入点
	 */
	int ap;

	/**
	 * register-指向WPS_registrar_init（）中WPS注册器数据的指针
	 */
	struct wps_registrar *registrar;

	/**
	 * wps_state-当前wps状态
	 */
	enum wps_state wps_state;

	/**
	 * ap_setup_locked—ap设置是否已锁定（仅在ap处使用）
	 */
	int ap_setup_locked;

	/**
	 * uuid-自己的uuid
	 */
	u8 uuid[16];

	/**
	 * ssid-ssid
	 *
	 * 注册官使用此SSID填写凭据信息。此外，AP在作为注册者时使用它来通知注册者当前配置。
	 */
	u8 ssid[32];

	/**
	 * ssid_len—ssid的长度（以八位字节为单位）
	 */
	size_t ssid_len;

	/**
	 * dev-自己的WPS设备数据
	 */
	struct wps_device_data dev;

	/**
	 * dh_ctx-Diffie-Hellman操作的上下文数据
	 */
	void *dh_ctx;

	/**
	 * dh_privkey-Diffie Hellman私钥
	 */
	struct wpabuf *dh_privkey;

	/**
	 * dh_pubkey_oob-Diffie Hellman公钥
	 */
	struct wpabuf *dh_pubkey;

	/**
	 * config_methods-启用的配置方法
	 *
	 * WPS_CONFIG的位字段_*
	 */
	u16 config_methods;

	/**
	 * encr_types-启用的加密类型（WPS_encr_*的位字段）
	 */
	u16 encr_types;

	/**
	 * auth_types-身份验证类型（WPS_auth_*的位字段）
	 */
	u16 auth_types;

	/**
	 * network_key-当前网络密钥（PSK）或%NULL以生成新的
	 *
	 * 如果为NULL，注册器将生成每个设备的PSK。此外，AP在作为注册人通知注册官当前配置时使用此选项。
	 *
	 * 使用WPA/WPA2 Person时，此密钥可以是ASCII密码（8..63个字符）或32个八位字节PSK（64个十六进制字符）。当设置为ASCII密码时，可以在PSK缓冲区中提供PSK，并为每个注册者使用PSK来控制凭证中包含的密钥类型（例如，通过提供PSK同时仍允许其他设备获取密码，减少低功耗设备上的计算需求）。
	 */
	u8 *network_key;

	/**
	 * network_key_len-以八位字节为单位的network_key长度
	 */
	size_t network_key_len;

	/**
	 * psk-当前网络psk
	 *
	 * 如果network_key设置为ASCII密码，则此可选值可用于提供当前PSK。
	 */
	u8 psk[32];

	/**
	 * psk_set—是否设置psk值
	 */
	int psk_set;

	/**
	 * ap_settings-M7的ap设置覆盖（仅用于ap）
	 *
	 * 如果为NULL，将根据当前网络配置生成AP设置属性。
	 */
	u8 *ap_settings;

	/**
	 * ap_settings_len-以八位字节为单位的ap_setting长度
	 */
	size_t ap_settings_len;

	/**
	 * friendly_name-友好名称（UPnP需要）
	 */
	char *friendly_name;

	/**
	 * manufacturer_url-制造商url（UPnP可选）
	 */
	char *manufacturer_url;

	/**
	 * model_description-型号描述（建议用于UPnP）
	 */
	char *model_description;

	/**
	 * model_url-型号url（UPnP可选）
	 */
	char *model_url;

	/**
	 * upc-通用产品代码（UPnP可选）
	 */
	char *upc;

	/**
	 * cred_cb-回调以通知已收到新凭据
	 * @ctx: 更高层上下文数据（cb_ctx）
	 * @cred: 收到的凭据返回：成功时为0，失败时为-1
	 */
	int (*cred_cb)(void *ctx, const struct wps_credential *cred);

	/**
	 * event_cb-事件回调（有关进度的状态信息）
	 * @ctx: 更高层上下文数据（cb_ctx）
	 * @event: 事件类型
	 * @data: 事件数据
	 */
	void (*event_cb)(void *ctx, enum wps_event event,
			 union wps_event_data *data);

	/**
	 * cb_ctx：回调的更高层上下文数据
	 */
	void *cb_ctx;

	/* 来自UPnP PutWLANResponse的挂起消息*/
#ifdef CONFIG_WPS_NFC

	u16 ap_nfc_dev_pw_id;
	struct wpabuf *ap_nfc_dh_pubkey;
	struct wpabuf *ap_nfc_dh_privkey;
	struct wpabuf *ap_nfc_dev_pw;
#endif
};

struct wps_registrar *
wps_registrar_init(struct wps_context *wps,
		   const struct wps_registrar_config *cfg);
void wps_registrar_deinit(struct wps_registrar *reg);
#ifdef CONFIG_WPS_PIN

int wps_registrar_add_pin(struct wps_registrar *reg, const u8 *addr,
			  const u8 *uuid, const u8 *pin, size_t pin_len,
			  int timeout);
int wps_registrar_invalidate_pin(struct wps_registrar *reg, const u8 *uuid);
int wps_registrar_unlock_pin(struct wps_registrar *reg, const u8 *uuid);
#endif
int wps_registrar_wps_cancel(struct wps_registrar *reg);

int wps_registrar_button_pushed(struct wps_registrar *reg,
				const u8 *p2p_dev_addr);
void wps_registrar_complete(struct wps_registrar *registrar, const u8 *uuid_e,
			    const u8 *dev_pw, size_t dev_pw_len);
void wps_registrar_probe_req_rx(struct wps_registrar *reg, const u8 *addr,
				const struct wpabuf *wps_data,
				int p2p_wildcard);
int wps_registrar_update_ie(struct wps_registrar *reg);
int wps_registrar_get_info(struct wps_registrar *reg, const u8 *addr,
			   char *buf, size_t buflen);
int wps_registrar_config_ap(struct wps_registrar *reg,
			    struct wps_credential *cred);
#ifdef CONFIG_WPS_NFC

int wps_registrar_add_nfc_pw_token(struct wps_registrar *reg,
				   const u8 *pubkey_hash, u16 pw_id,
				   const u8 *dev_pw, size_t dev_pw_len);
int wps_registrar_add_nfc_password_token(struct wps_registrar *reg,
					 const u8 *oob_dev_pw,
					 size_t oob_dev_pw_len);
#endif
int wps_build_credential_wrap(struct wpabuf *msg,
			      const struct wps_credential *cred);
#ifdef CONFIG_WPS_PIN
unsigned int wps_pin_checksum(unsigned int pin);
unsigned int wps_pin_valid(unsigned int pin);
int wps_pin_str_valid(const char *pin);
#endif

unsigned int wps_generate_pin(void);

#ifdef CONFIG_WPS_OOB

struct wpabuf * wps_get_oob_cred(struct wps_context *wps);
int wps_oob_use_cred(struct wps_context *wps, struct wps_parse_attr *attr);
#endif
int wps_attr_text(struct wpabuf *data, char *buf, char *end);

struct wps_er * wps_er_init(struct wps_context *wps, const char *ifname,
			    const char *filter);
void wps_er_refresh(struct wps_er *er);
void wps_er_deinit(struct wps_er *er, void (*cb)(void *ctx), void *ctx);
void wps_er_set_sel_reg(struct wps_er *er, int sel_reg, u16 dev_passwd_id,
			u16 sel_reg_config_methods);
int wps_er_pbc(struct wps_er *er, const u8 *uuid);
int wps_er_learn(struct wps_er *er, const u8 *uuid, const u8 *pin,
		 size_t pin_len);
int wps_er_set_config(struct wps_er *er, const u8 *uuid,
		      const struct wps_credential *cred);
int wps_er_config(struct wps_er *er, const u8 *uuid, const u8 *pin,
		  size_t pin_len, const struct wps_credential *cred);
#ifdef CONFIG_WPS_NFC

struct wpabuf * wps_er_nfc_config_token(struct wps_er *er, const u8 *uuid);

#endif

int wps_dev_type_str2bin(const char *str, u8 dev_type[WPS_DEV_TYPE_LEN]);
char * wps_dev_type_bin2str(const u8 dev_type[WPS_DEV_TYPE_LEN], char *buf,
			    size_t buf_len);
void uuid_gen_mac_addr(const u8 *mac_addr, u8 *uuid);
u16 wps_config_methods_str2bin(const char *str);

#ifdef CONFIG_WPS_NFC

struct wpabuf * wps_build_nfc_pw_token(u16 dev_pw_id,
				       const struct wpabuf *pubkey,
				       const struct wpabuf *dev_pw);
struct wpabuf * wps_nfc_token_gen(int ndef, int *id, struct wpabuf **pubkey,
				  struct wpabuf **privkey,
				  struct wpabuf **dev_pw);
#endif

/* 索引c*/
struct wpabuf * ndef_parse_wifi(const struct wpabuf *buf);
struct wpabuf * ndef_build_wifi(const struct wpabuf *buf);
struct wpabuf * ndef_build_wifi_hr(void);

#ifdef CONFIG_WPS_STRICT
int wps_validate_beacon(const struct wpabuf *wps_ie);
int wps_validate_beacon_probe_resp(const struct wpabuf *wps_ie, int probe,
				   const u8 *addr);
int wps_validate_probe_req(const struct wpabuf *wps_ie, const u8 *addr);
int wps_validate_assoc_req(const struct wpabuf *wps_ie);
int wps_validate_assoc_resp(const struct wpabuf *wps_ie);
int wps_validate_m1(const struct wpabuf *tlvs);
int wps_validate_m2(const struct wpabuf *tlvs);
int wps_validate_m2d(const struct wpabuf *tlvs);
int wps_validate_m3(const struct wpabuf *tlvs);
int wps_validate_m4(const struct wpabuf *tlvs);
int wps_validate_m4_encr(const struct wpabuf *tlvs, int wps2);
int wps_validate_m5(const struct wpabuf *tlvs);
int wps_validate_m5_encr(const struct wpabuf *tlvs, int wps2);
int wps_validate_m6(const struct wpabuf *tlvs);
int wps_validate_m6_encr(const struct wpabuf *tlvs, int wps2);
int wps_validate_m7(const struct wpabuf *tlvs);
int wps_validate_m7_encr(const struct wpabuf *tlvs, int ap, int wps2);
int wps_validate_m8(const struct wpabuf *tlvs);
int wps_validate_m8_encr(const struct wpabuf *tlvs, int ap, int wps2);
int wps_validate_wsc_ack(const struct wpabuf *tlvs);
int wps_validate_wsc_nack(const struct wpabuf *tlvs);
int wps_validate_wsc_done(const struct wpabuf *tlvs);
int wps_validate_upnp_set_selected_registrar(const struct wpabuf *tlvs);
#else /* CONFIG_WPS_STRICT */
static inline int wps_validate_beacon(const struct wpabuf *wps_ie){
	return 0;
}

static inline int wps_validate_beacon_probe_resp(const struct wpabuf *wps_ie,
						 int probe, const u8 *addr)
{
	return 0;
}

static inline int wps_validate_probe_req(const struct wpabuf *wps_ie,
					 const u8 *addr)
{
	return 0;
}

static inline int wps_validate_assoc_req(const struct wpabuf *wps_ie)
{
	return 0;
}

static inline int wps_validate_assoc_resp(const struct wpabuf *wps_ie)
{
	return 0;
}

static inline int wps_validate_m1(const struct wpabuf *tlvs)
{
	return 0;
}

static inline int wps_validate_m2(const struct wpabuf *tlvs)
{
	return 0;
}

static inline int wps_validate_m2d(const struct wpabuf *tlvs)
{
	return 0;
}

static inline int wps_validate_m3(const struct wpabuf *tlvs)
{
	return 0;
}

static inline int wps_validate_m4(const struct wpabuf *tlvs)
{
	return 0;
}

static inline int wps_validate_m4_encr(const struct wpabuf *tlvs, int wps2)
{
	return 0;
}

static inline int wps_validate_m5(const struct wpabuf *tlvs)
{
	return 0;
}

static inline int wps_validate_m5_encr(const struct wpabuf *tlvs, int wps2)
{
	return 0;
}

static inline int wps_validate_m6(const struct wpabuf *tlvs)
{
	return 0;
}

static inline int wps_validate_m6_encr(const struct wpabuf *tlvs, int wps2)
{
	return 0;
}

static inline int wps_validate_m7(const struct wpabuf *tlvs)
{
	return 0;
}

static inline int wps_validate_m7_encr(const struct wpabuf *tlvs, int ap,
				       int wps2)
{
	return 0;
}

static inline int wps_validate_m8(const struct wpabuf *tlvs)
{
	return 0;
}

static inline int wps_validate_m8_encr(const struct wpabuf *tlvs, int ap,
				       int wps2)
{
	return 0;
}

static inline int wps_validate_wsc_ack(const struct wpabuf *tlvs)
{
	return 0;
}

static inline int wps_validate_wsc_nack(const struct wpabuf *tlvs)
{
	return 0;
}

static inline int wps_validate_wsc_done(const struct wpabuf *tlvs)
{
	return 0;
}

static inline int wps_validate_upnp_set_selected_registrar(
	const struct wpabuf *tlvs)
{
	return 0;
}
#endif /* CONFIG_WPS_STRICT */

enum wps_cb_status {
	WPS_CB_ST_SUCCESS = 0,
	WPS_CB_ST_FAILED,
	WPS_CB_ST_TIMEOUT,
	WPS_CB_ST_WEP,
	WPS_CB_ST_SCAN_ERR,
};

typedef void (*wps_st_cb_t)(int status);

#ifdef USE_WPS_TASK
enum wps_sig_type {
    SIG_WPS_ENABLE = 1,         //1
    SIG_WPS_DISABLE,            //2
    SIG_WPS_START,              //3
    SIG_WPS_RX,                 //4
    SIG_WPS_TIMER_TIMEOUT,      //5
    SIG_WPS_TIMER_MSG_TIMEOUT,  //6
    SIG_WPS_TIMER_SUCCESS_CB,   //7
    SIG_WPS_TIMER_SCAN,         //8
    SIG_WPS_TIMER_EAPOL_START,  //9
    SIG_WPS_NUM,                //10
};
#endif

#define WPS_EAP_EXT_VENDOR_TYPE "WFA-SimpleConfig-Enrollee-1-0"
#define WPS_OUTBUF_SIZE 500
struct wps_sm {
    struct wps_config *wps_cfg;
    struct wps_context *wps_ctx;
    struct wps_data *wps;
    char identity[32];
    u8 identity_len;
    u8 ownaddr[ETH_ALEN];
    u8 bssid[ETH_ALEN];
    u8 ssid[MAX_WPS_AP_CRED][MAX_SSID_LEN];
    u8 ssid_len[MAX_WPS_AP_CRED];
    char key[MAX_WPS_AP_CRED][MAX_PASSPHRASE_LEN];
    u8 key_len[MAX_WPS_AP_CRED];
    u8 ap_cred_cnt;
    struct wps_device_data *dev;
    u8 uuid[16];
    u8 eapol_version;
    ETSTimer wps_timeout_timer;
    ETSTimer wps_msg_timeout_timer;
    ETSTimer wps_scan_timer;
    ETSTimer wps_success_cb_timer;
    ETSTimer wps_eapol_start_timer;
    wps_st_cb_t st_cb;
    u8 current_identifier;
    bool is_wps_scan;
    u8 channel;
    u8 scan_cnt;
#ifdef USE_WPS_TASK
    u8 wps_sig_cnt[SIG_WPS_NUM];
#endif
    u8 discover_ssid_cnt;
    bool ignore_sel_reg;
    bool wps_pin_war;
    struct discard_ap_list_t dis_ap_list[WPS_MAX_DIS_AP_NUM];
    u8 discard_ap_cnt;
    wifi_sta_config_t config;
};

#define    WIFI_CAPINFO_PRIVACY        0x0010

struct wps_sm *wps_sm_get(void);
int wps_ssid_save(u8 *ssid, u8 ssid_len, u8 idx);
int wps_key_save(char *key, u8 key_len, u8 idx);
int wps_station_wps_register_cb(wps_st_cb_t cb);
int wps_station_wps_unregister_cb(void);
int wps_start_pending(void);
int wps_sm_rx_eapol(u8 *src_addr, u8 *buf, u32 len);

int wps_dev_deinit(struct wps_device_data *dev);
#endif /* WPS_H */

