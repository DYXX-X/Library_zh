/*
 * EAP对等配置数据版权所有（c）2003-2013，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef EAP_CONFIG_H
#define EAP_CONFIG_H

/**
 * struct eap_peer_config-eap对等配置/凭据
 */
struct eap_peer_config {
	/**
	 * identity-EAP身份
	 *
	 * 此字段用于设置真实用户标识或NAI（对于EAP-PSK/PAX/SAKE/GPSK）。
	 */
	u8 *identity;

	/**
	 * identity_len-EAP标识长度
	 */
	size_t identity_len;

	/**
	 * anonymous_identity-匿名EAP身份
	 *
	 * 该字段用于支持不同隧道身份的EAP类型（例如EAP-TTLS）的未加密使用，以便仅向认证服务器显示真实身份（身份字段）。
	 *
	 * 如果未设置，则标识字段将用于未加密字段和受保护字段。
	 *
	 * 该字段也可以与EAP-SIM/AKA/AKA'一起使用，以存储假名标识。
	 */
	u8 *anonymous_identity;

	/**
	 * anonymous_identity_len-anonymous-identity的长度
	 */
	size_t anonymous_identity_len;

	/**
	 * password-EAP的密码字符串
	 *
	 * 如果标志字段的EAP_CONFIG_flags_password_NTHASH位设置为1，则该字段可以包括明文密码（默认选项）或NtPasswordHash（密码的unicode表示的16字节MD4哈希）。NtPasswordHash只能与使用此哈希作为操作起点的身份验证机制一起使用：MSCHAP和MSCHAPv2（EAP-MSCHAPv3、EAP-TTLS/MSCHAPv2、EAP-TTP/MSCHAP、LEAP）。
	 *
	 * 此外，此字段用于配置EAP-PSK/PAX/SAKE/GPSK的预共享密钥。EAP-PSK和EAP-PAX的PSK长度必须为16，EAP-SAKE的PSK必须为32。EAP-GPSK可以使用可变长度的PSK。
	 */
	u8 *password;

	/**
	 * password_len—密码字段的长度
	 */
	size_t password_len;

	/**
	 * ca_cert-ca证书文件的文件路径（PEM/DER）
	 *
	 * 此文件可以有一个或多个受信任的CA证书。如果不包括ca_cert和ca_path，则不会验证服务器证书。这是不安全的，使用EAP-TLS/TTLS/PEAP时应始终配置可信CA证书。应使用文件的完整路径，因为当wpa_supplicant在后台运行时，工作目录可能会更改。
	 *
	 * 或者，可以通过将其设置为blob://blob_name.
	 *
	 * 或者，这可以用于仅执行服务器证书的匹配（DER编码的X.509证书的SHA-256哈希）。在这种情况下，将忽略服务器证书链中可能的CA证书，只验证服务器证书。这是用以下格式配置的：hash:：//server/sha256/cert_hash_in_hex例如：“hash://server/sha256/“
	 *
	 * 在Windows上，通过将此设置为cert，可以从系统证书存储中加载受信任的CA证书_store://name例如，ca_cert=“cert_store://CA“或ca_cert=”证书_store://ROOT请注意，当将wpa_supplicant作为应用程序运行时，将使用用户证书存储（我的用户帐户），而当将wpasvc作为服务运行时，则使用计算机存储（计算机帐户）。
	 */
	u8 *ca_cert;

	/**
	 * ca_path-ca证书文件（PEM）的目录路径
	 *
	 * 此路径可能包含多个OpenSSL格式的CA证书。这通常用于指向系统可信CA列表，该列表通常安装在/etc/ssl/certs等目录中。如果已配置，这些证书将添加到受信任CA的列表中。在这种情况下也可以包括cacert，但这不是必需的。
	 */
	u8 *ca_path;

	/**
	 * client_cert-客户端证书文件的文件路径（PEM/DER）
	 *
	 * 此字段与使用TLS身份验证的EAP方法一起使用。通常，这只为EAP-TLS配置，尽管理论上这也可以用于EAP-TTLS和EAP-PEAP。应使用文件的完整路径，因为当wpa_supplicant在后台运行时，工作目录可能会更改。
	 *
	 * 或者，可以通过将其设置为blob://blob_name.
	 */
	u8 *client_cert;

	/**
	 * private_key-客户端私钥文件的文件路径（PEM/DER/PFX）
	 *
	 * 当使用PKCS#12/PFX文件（.p12/.PFX）时，应注释掉client_cert。在这种情况下，将从PKCS#12文件中读取私钥和证书。应使用文件的完整路径，因为当wpa_supplicant在后台运行时，工作目录可能会更改。
	 *
	 * 可以使用Windows证书存储，方法是不使用client_cert，并以以下格式之一配置private_key：
	 *
	 * cert://substring_to_match
	 *
	 * hash://certificate_thumbprint_in_hex
	 *
	 * 例如：private_key=“hash://63093aa9c47f56ae88334c7b65a4"
	 *
	 * 请注意，当将wpa_supplicant作为应用程序运行时，将使用用户证书存储（我的用户帐户），而当将wpasvc作为服务运行时，则使用计算机存储（计算机帐户）。
	 *
	 * 或者，可以通过将其设置为blob://blob_name.
	 */
	u8 *private_key;

	/**
	 * private_key_passwd-私钥文件的密码
	 *
	 * 如果省略，将通过控制界面询问。
	 */
	const u8 *private_key_passwd;

	/**
	 * 第2阶段
	 */
	u8 *ca_cert2;

	/**
	 * ca_path2-ca证书文件（PEM）的目录路径（阶段2）
	 *
	 * 此路径可能包含多个OpenSSL格式的CA证书。这通常用于指向系统可信CA列表，该列表通常安装在/etc/ssl/certs等目录中。如果已配置，这些证书将添加到受信任CA的列表中。在这种情况下也可以包括cacert，但这不是必需的。
	 *
	 * 该字段类似于ca_path，但用于第2阶段（EAP-TTLS/PEAP/FAST隧道内）身份验证。
	 */
	u8 *ca_path2;

	/**
	 * client_cert2-客户端证书文件的文件路径
	 *
	 * 该字段类似于client_cert，但用于第2阶段（EAP-TTLS/PEAP/FAST隧道内）身份验证。应使用文件的完整路径，因为当wpa_supplicant在后台运行时，工作目录可能会更改。
	 *
	 * 或者，可以通过将其设置为blob://blob_name.
	 */
	u8 *client_cert2;

	/**
	 * private_key2-客户端私钥文件的文件路径
	 *
	 * 该字段类似于private_key，但用于第2阶段（EAP-TTLS/PEAP/FAST隧道内）身份验证。应使用文件的完整路径，因为当wpa_supplicant在后台运行时，工作目录可能会更改。
	 *
	 * 或者，可以通过将其设置为blob://blob_name.
	 */
	u8 *private_key2;

	u8 *private_key2_password;

	/**
	 * eap_methods-允许的eap方法
	 *
	 * （vendor=EAP_vendor_IETF，method=EAP_TYPE_NONE）终止了允许的EAP方法列表，如果所有方法都被接受，则返回%NULL。
	 */
	struct eap_method_type *eap_methods;


	char *phase1;

	/**
	 * phase2-phase2（使用TLS隧道的内部身份验证）参数
	 *
	 * 带字段值对的字符串，例如，EAP-PEAP为“auth=MSCHAPV2”，EAP-TTLS为“authap=MSCHAPV2 authap=MD5”。“mschapv2_retry=0”可用于在身份验证失败的情况下禁用mschapv2密码重试。
	 */
	char *phase2;

	/**
	 * pcsc-USIM和GSM SIM的PC/SC智能卡接口参数
	 *
	 * 此字段用于配置PC/SC智能卡接口。目前，唯一的配置是该字段是%NULL（不使用PC/SC）还是非NULL（例如“”）以启用PC/SC。
	 *
	 * 此字段用于EAP-SIM和EAP-AKA。
	 */
	char *pcsc;

	/**
	 * pin-USIM、GSM SIM卡和智能卡的pin
	 *
	 * 此字段用于为EAP-SIM和EAP-AKA配置SIM卡和智能卡的PIN。此外，如果智能卡用于私钥操作，这将与EAP-TLS一起使用。
	 *
	 * 如果省略，将通过控制界面询问。
	 */
	char *pin;

	/**
	 * pending_req_identity-是否存在挂起的身份请求
	 *
	 * 此字段不应在配置步骤中设置。仅当控制接口用于请求所需信息时才在内部使用。
	 */
	int pending_req_identity;

	/**
	 * pending_req_password-是否存在挂起的密码请求
	 *
	 * 此字段不应在配置步骤中设置。仅当控制接口用于请求所需信息时才在内部使用。
	 */
	int pending_req_password;

	/**
	 * pending_req_pin-是否存在挂起的pin请求
	 *
	 * 此字段不应在配置步骤中设置。仅当控制接口用于请求所需信息时才在内部使用。
	 */
	int pending_req_pin;

	/**
	 * pending_req_new_password-待定的密码更新请求
	 *
	 * 此字段不应在配置步骤中设置。仅当控制接口用于请求所需信息时才在内部使用。
	 */
	int pending_req_new_password;

	/**
	 * pending_req_passphrase-挂起的密码请求
	 *
	 * 此字段不应在配置步骤中设置。仅当控制接口用于请求所需信息时才在内部使用。
	 */
	int pending_req_passphrase;

	/**
	 * pending_req_sim-挂起sim卡请求
	 *
	 * 此字段不应在配置步骤中设置。仅当控制接口用于请求所需信息时才在内部使用。
	 */
	int pending_req_sim;

	/**
	 * pending_req_otp-是否存在挂起的otp请求
	 *
	 * 此字段不应在配置步骤中设置。仅当控制接口用于请求所需信息时才在内部使用。
	 */
	char *pending_req_otp;

	/**
	 * pac_file—pac条目的文件路径或blob名称（EAP-FAST）
	 *
	 * wpa_supplicant需要能够创建此文件，并在PAC被配置或刷新时向其写入更新。应使用文件的完整路径，因为当wpa_supplicant在后台运行时，工作目录可能会更改。或者，可以通过将其设置为blob://blob_name.
	 */
	char *pac_file;

	/**
	 * mschapv2_retry-mschapv2正在重试
	 *
	 * 此字段由EAP-MSCHAPv2内部使用，不应作为配置的一部分设置。
	 */
	int mschapv2_retry;

	/**
	 * new_password-密码更新的新密码
	 *
	 * 此字段在MSCHAPv2密码更新期间使用。这通常是用户通过控制界面请求的，而不是从配置中设置的。
	 */
	u8 *new_password;

	/**
	 * new_password_len—new_password字段的长度
	 */
	size_t new_password_len;

	/**
	 * fragment_size-最大EAP片段大小（字节）（默认值1398）
	 *
	 * 该值限制支持分段的EAP方法（例如EAP-TLS和EAP-PEAP）的分段大小。该值应设置得足够小，以使EAP消息适合用于EAPOL的网络接口的MTU。默认值适用于大多数情况。
	 */
	int fragment_size;

#define EAP_CONFIG_FLAGS_PASSWORD_NTHASH BIT(0)
#define EAP_CONFIG_FLAGS_EXT_PASSWORD BIT(1)
	/**
	 * flags-网络配置标志（位字段）
	 *
	 * 此变量用于内部标志，以描述网络参数的进一步详细信息。位0=密码表示为16字节NtPasswordHash值，而不是明文密码位1=密码存储在外部存储器中；密码字段中的值是该外部条目的名称
	 */
	u32 flags;

	/**
	 * ocsp-是否使用/要求ocsp检查服务器证书
	 *
	 * 0=不使用OCSP装订（TLS证书状态扩展）1=尝试使用OCSP缝合，但不需要响应2=需要有效的OCSP装订响应
	 */
	int ocsp;

	/**
	 * erp-是否启用EAP重新身份验证协议（erp）
	 */
	int erp;

	/**
	 * pending_ext_cert_check-外部服务器证书检查状态
	 *
	 * 此字段不应在配置步骤中设置。仅当控制接口用于请求服务器证书链的外部验证时，才在内部使用。
	 */
	enum {
		NO_CHECK = 0,
		PENDING_CHECK,
		EXT_CERT_CHECK_GOOD,
		EXT_CERT_CHECK_BAD,
	} pending_ext_cert_check;

};


/**
 * 结构wpa_config_blob-命名配置blob
 *
 * 此数据结构用于为二进制对象提供存储，以存储与配置数据内联的抽象信息，如证书和私钥。
 */
struct wpa_config_blob {
	/**
	 * name-Blob名称
	 */
	char *name;

	/**
	 * data-指向二进制数据的指针
	 */
	const u8 *data;

	/**
	 * len—二进制数据的长度
	 */
	size_t len;

	/**
	 * next-指向配置中下一个blob的指针
	 */
	struct wpa_config_blob *next;
};

#endif /* EAP_CONFIG_H */

