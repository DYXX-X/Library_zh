/*
 * EAP对等状态机内部结构（RFC 4137）版权所有（c）2004-2007，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef EAP_I_H
#define EAP_I_H

#include "utils/wpabuf.h"
#include "eap.h"
#include "eap_common.h"
#include "eap_config.h"
#include "esp_wpa2.h"

/* RFC 4137-EAP对等状态机*/

typedef enum {
	DECISION_FAIL, DECISION_COND_SUCC, DECISION_UNCOND_SUCC
} EapDecision;

typedef enum {
	METHOD_NONE, METHOD_INIT, METHOD_CONT, METHOD_MAY_CONT, METHOD_DONE
} EapMethodState;

/**
 * struct eap_method_ret-结构eap_method:：process（）的eap返回值
 *
 * 这些结构包含对等状态机和方法之间接口的OUT变量（RFC 4137，第4.2节）。eapRespData将作为结构eap_method:：process（）的返回值返回，因此它不包含在此结构中。
 */
struct eap_method_ret {
	/**
	 * 忽略-方法是否决定删除当前打包的（OUT）
	 */
	Boolean ignore;

	/**
	 * methodState-方法特定状态（IN/OUT）
	 */
	EapMethodState methodState;

	/**
	 * decision—身份验证决策（OUT）
	 */
	EapDecision decision;

	/**
	 * allowNotifications-方法是否允许通知（OUT）
	 */
	Boolean allowNotifications;
};

struct eap_sm;

/**
 * struct eap_method-eap方法接口此结构定义eap方法接口。每个方法都需要注册自己的EAP类型、EAP名称和方法特定操作的函数指针集。该接口基于RFC 4137的4.4节。
 */
struct eap_method {
	/**
	 * vendor-EAP供应商ID（EAP_vendor_*）（0=IETF）
	 */
	int vendor;

	/**
	 * method-EAP类型号（EAP_type_*）
	 */
	EapType method;

	/**
	 * name—方法的名称（例如，“TLS”）
	 */
	const char *name;

	/**
	 * init-初始化EAP方法
	 * @sm: 指向用EAP_peer_sm_init（）分配的EAP状态机的指针返回：指向分配的私有数据的指针，或失败时为%NULL
	 *
	 * 此函数用于显式初始化EAP方法，而不是使用RFC 4137中特定的method_INIT状态。该方法应初始化其特定于方法的状态，并返回一个指针，该指针将用作其他调用的priv参数。
	 */
	void * (*init)(struct eap_sm *sm);

	/**
	 * deinit-取消初始化EAP方法
	 * @sm: 指向使用EAP_peer_sm_init（）分配的EAP状态机的指针
	 * @priv: 指向EAP_method:：init（）中私有EAP方法数据的指针
	 *
	 * 取消初始化EAP方法并释放所有分配的私有数据。
	 */
	void (*deinit)(struct eap_sm *sm, void *priv);

	/**
	 * process-处理EAP请求
	 * @sm: 指向使用EAP_peer_sm_init（）分配的EAP状态机的指针
	 * @priv: 指向EAP_method:：init（）中私有EAP方法数据的指针
	 * @ret: EAP请求验证和处理的返回值
	 * @reqData: 要处理的EAP请求（eapReqData）返回：指向分配的EAP响应包（eapRespData）的指针
	 *
	 * 该函数是RFC 4137第4.4节中定义的m.check（）、m.process（）和m.buildResp（）过程的组合。换句话说，该函数验证传入的请求，处理它，并构建响应包。m、 check（）和m.process（）返回值通过结构eap_method_ret ret变量返回。调用者负责释放返回的EAP响应包。
	 */
	struct wpabuf * (*process)(struct eap_sm *sm, void *priv,
				   struct eap_method_ret *ret,
				   const struct wpabuf *reqData);
	bool (*isKeyAvailable)(struct eap_sm *sm, void *priv);
	u8 * (*getKey)(struct eap_sm *sm, void *priv, size_t *len);

	/**
	 * get_status-获取EAP方法状态
	 * @sm: 指向使用EAP_peer_sm_init（）分配的EAP状态机的指针
	 * @priv: 指向EAP_method:：init（）中私有EAP方法数据的指针
	 * @buf: 状态信息缓冲区
	 * @buflen: 最大缓冲区长度
	 * @verbose: 是否包含详细状态信息返回：写入buf的字节数
	 *
	 * 查询EAP方法以获取状态信息。此函数使用EAP方法的当前状态信息填充文本区域。如果缓冲区（buf）不够大，状态信息将被截断以适合缓冲区。
	 */
	int (*get_status)(struct eap_sm *sm, void *priv, char *buf,
			  size_t buflen, int verbose);

	/**
	 * has_reauth_data—方法是否准备好进行快速重新验证
	 * @sm: 指向使用EAP_peer_sm_init（）分配的EAP状态机的指针
	 * @priv: EAP_method:：init（）中指向私有EAP方法数据的指针返回：%TRUE或%FALSE，取决于是否可以快速重新身份验证
	 *
	 * 此函数是一个可选的处理程序，只有支持快速重新身份验证的EAP方法才需要实现。
	 */
	bool (*has_reauth_data)(struct eap_sm *sm, void *priv);

	/**
	 * deinit_for_reauth-释放快速重新身份验证不需要的数据
	 * @sm: 指向使用EAP_peer_sm_init（）分配的EAP状态机的指针
	 * @priv: 指向EAP_method:：init（）中私有EAP方法数据的指针
	 *
	 * 此函数是一个可选的处理程序，只有支持快速重新身份验证的EAP方法才需要实现。当身份验证完成并且EAP状态机请求维护足够的状态信息以进行快速重新身份验证时，将调用此命令
	 */
	void (*deinit_for_reauth)(struct eap_sm *sm, void *priv);

	/**
	 * init_for_reauth-准备开始快速重新身份验证
	 * @sm: 指向使用EAP_peer_sm_init（）分配的EAP状态机的指针
	 * @priv: 指向EAP_method:：init（）中私有EAP方法数据的指针
	 *
	 * 此函数是一个可选的处理程序，只有支持快速重新身份验证的EAP方法才需要实现。当EAP身份验证启动并且EAP状态机请求使用快速重新身份验证时，将调用此选项。
	 */
	void * (*init_for_reauth)(struct eap_sm *sm, void *priv);

	/**
	 * get_identity-获取用于重新身份验证的方法特定标识
	 * @sm: 指向使用EAP_peer_sm_init（）分配的EAP状态机的指针
	 * @priv: 指向EAP_method:：init（）中私有EAP方法数据的指针
	 * @len: 返回标识的长度返回：指向方法特定标识的指针，如果要使用默认标识，则返回%NULL
	 *
	 * 此函数是一个可选的处理程序，只有使用方法特定标识的EAP方法才需要实现。
	 */
	const u8 * (*get_identity)(struct eap_sm *sm, void *priv, size_t *len);

	/**
	 * free-免费EAP方法数据
	 * @method: 指向用eap_peer_method_register（）注册的方法数据的指针。
	 *
	 * 注销EAP方法时将调用此函数。如果EAP方法在注册期间分配了资源（例如，分配的结构EAP_method），则应在此函数中释放这些资源。此调用之后不会调用其他方法函数。如果未定义此函数（即，函数指针为%NULL），则使用默认处理程序释放具有free（方法）的方法数据。这适用于大多数情况。
	 */
	void (*free)(struct eap_method *method);

#define EAP_PEER_METHOD_INTERFACE_VERSION 1
	/**
	 * version-EAP对等方法接口的版本
	 *
	 * EAP对等方法实现应将此变量设置为EAP_peer_method_INTERFACE_VERSION。这用于在使用动态可加载EAP方法时验证EAP方法是否使用受支持的API版本。
	 */
	int version;

	/**
	 * next-指向下一个EAP方法的指针
	 *
	 * 此变量在EAP方法注册代码中内部使用，以创建已注册EAP方法的链接列表。
	 */
	struct eap_method *next;

#ifdef CONFIG_DYNAMIC_EAP_METHODS
	/**
	 * dl_handle-动态库的句柄
	 *
	 * 该变量在EAP方法注册代码中内部使用，以存储动态库的句柄。如果该方法是静态链接的，则为%NULL。
	 */
	void *dl_handle;
#endif /* CONFIG_DYNAMIC_EAP_METHODS */

	/**
	 * get_emsk-获取EAP方法特定的密钥扩展材料（emsk）
	 * @sm: 指向使用EAP_peer_sm_init（）分配的EAP状态机的指针
	 * @priv: 指向EAP_method:：init（）中私有EAP方法数据的指针
	 * @len: 指向存储EMSK长度的变量的指针返回：EMSK或%NULL（如果不可用）
	 *
	 * 此函数可用于从EAP方法获得扩展密钥材料。密钥可能已经存储在特定于方法的私有数据中，或者该函数可以导出密钥。
	 */
	u8 * (*get_emsk)(struct eap_sm *sm, void *priv, size_t *len);

	/**
	 * getSessionId-获取EAP方法特定的会话Id
	 * @sm: 指向使用EAP_peer_sm_init（）分配的EAP状态机的指针
	 * @priv: 指向EAP_method:：init（）中私有EAP方法数据的指针
	 * @len: 指向存储会话Id长度的变量的指针返回：会话Id或%NULL（如果不可用）
	 *
	 * 此函数可用于从EAP方法获取会话Id。会话Id可能已经存储在特定于方法的私有数据中，或者此函数可以派生会话Id。
	 */
	u8 * (*getSessionId)(struct eap_sm *sm, void *priv, size_t *len);
};

#define CLIENT_CERT_NAME	"CLC"
#define CA_CERT_NAME		"CAC"
#define PRIVATE_KEY_NAME	"PVK"
#define PAC_FILE_NAME		"PAC"
#define BLOB_NAME_LEN		3
#define BLOB_NUM		4

enum SIG_WPA2 {
    SIG_WPA2_START = 0,
    SIG_WPA2_RX,
    SIG_WPA2_TASK_DEL,
    SIG_WPA2_MAX,
};

/**
 * struct eap_sm-eap状态机数据
 */
struct eap_sm {
	/* RFC 4137中未定义*/
	Boolean changed;
	void *eap_method_priv;
	int init_phase2;

	void *msg_ctx;
	void *ssl_ctx;

	unsigned int workaround;
/////////////////////////////////////////////////
        struct pbuf *outbuf;
	struct wpa_config_blob blob[BLOB_NUM];
	struct eap_peer_config config;
	u8 current_identifier;
	u8 ownaddr[ETH_ALEN];
#ifdef USE_WPA2_TASK
    	u8 wpa2_sig_cnt[SIG_WPA2_MAX];
#endif
	u8 finish_state;

	/* 阶段1中产生的可选挑战（EAP-FAST）*/
	u8 *peer_challenge, *auth_challenge;

	unsigned int expected_failure:1;
	unsigned int ext_cert_check:1;
	unsigned int waiting_ext_cert_check:1;
	bool peap_done;

	u8 *eapKeyData;
	size_t eapKeyDataLen;
	struct wpabuf *lastRespData;
	const struct eap_method *m;
};

typedef enum {
    WPA2_STATE_ENABLED = 0,
    WPA2_STATE_DISABLED,
} wpa2_state_t;

const u8 * eap_get_config_identity(struct eap_sm *sm, size_t *len);
const u8 * eap_get_config_password(struct eap_sm *sm, size_t *len);
const u8 * eap_get_config_password2(struct eap_sm *sm, size_t *len, int *hash);
const u8 * eap_get_config_new_password(struct eap_sm *sm, size_t *len);
const u8 * eap_get_config_otp(struct eap_sm *sm, size_t *len);
void eap_clear_config_otp(struct eap_sm *sm);
const char * eap_get_config_phase1(struct eap_sm *sm);
const char * eap_get_config_phase2(struct eap_sm *sm);
int eap_get_config_fragment_size(struct eap_sm *sm);
struct eap_peer_config * eap_get_config(struct eap_sm *sm);
void eap_set_config_blob(struct eap_sm *sm, struct wpa_config_blob *blob);
const struct wpa_config_blob * eap_get_config_blob(struct eap_sm *sm, const char *name);
bool wifi_sta_get_enterprise_disable_time_check(void);

struct wpabuf * eap_sm_build_identity_resp(struct eap_sm *sm, u8 id, int encrypted);

#endif /* EAP_I_H */

