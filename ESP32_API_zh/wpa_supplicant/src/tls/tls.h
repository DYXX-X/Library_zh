/*
 * SSL/TLS接口定义版权所有（c）2004-2013，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef TLS_H
#define TLS_H

struct tls_connection;

struct tls_random {
	const u8 *client_random;
	size_t client_random_len;
	const u8 *server_random;
	size_t server_random_len;
};

enum tls_event {
	TLS_CERT_CHAIN_SUCCESS,
	TLS_CERT_CHAIN_FAILURE,
	TLS_PEER_CERTIFICATE,
	TLS_ALERT
};

/*
 * 注意：这些值用作外部程序的标识符，因此不能更改值。
 */
enum tls_fail_reason {
	TLS_FAIL_UNSPECIFIED = 0,
	TLS_FAIL_UNTRUSTED = 1,
	TLS_FAIL_REVOKED = 2,
	TLS_FAIL_NOT_YET_VALID = 3,
	TLS_FAIL_EXPIRED = 4,
	TLS_FAIL_SUBJECT_MISMATCH = 5,
	TLS_FAIL_ALTSUBJECT_MISMATCH = 6,
	TLS_FAIL_BAD_CERTIFICATE = 7,
	TLS_FAIL_SERVER_CHAIN_PROBE = 8
};

union tls_event_data {
	struct {
		int depth;
		const char *subject;
		enum tls_fail_reason reason;
		const char *reason_txt;
		const struct wpabuf *cert;
	} cert_fail;

	struct {
		int depth;
		const char *subject;
		const struct wpabuf *cert;
		const u8 *hash;
		size_t hash_len;
	} peer_cert;

	struct {
		int is_local;
		const char *type;
		const char *description;
	} alert;
};

struct tls_config {
	const char *opensc_engine_path;
	const char *pkcs11_engine_path;
	const char *pkcs11_module_path;
	int fips_mode;
	int cert_in_cb;

	void (*event_cb)(void *ctx, enum tls_event ev,
			 union tls_event_data *data);
	void *cb_ctx;
};

#define TLS_CONN_ALLOW_SIGN_RSA_MD5 BIT(0)
#define TLS_CONN_DISABLE_TIME_CHECKS BIT(1)
#define TLS_CONN_DISABLE_SESSION_TICKET BIT(2)
#define TLS_CONN_REQUEST_OCSP BIT(3)
#define TLS_CONN_REQUIRE_OCSP BIT(4)
#define TLS_CONN_SUITEB BIT(11)
#define TLS_CONN_EAP_FAST BIT(7)

/**
 * struct tls_connection_params-tls连接的参数
 * @ca_cert: PEM或DER格式的CA X.509证书的文件或参考名称
 * @ca_cert_blob: ca_cert作为内联数据，如果未使用，则为%NULL
 * @ca_cert_blob_len: ca_cert_blob长度
 * @ca_path: CA证书的路径（特定于OpenSSL）
 * @subject_match: 要匹配对等证书主题的字符串，或%NULL以允许所有主题
 * @altsubject_match: 在对等证书的替代主题中匹配的字符串，或%NULL以允许所有替代主题
 * @client_cert: PEM或DER格式的客户端X.509证书的文件或引用名称
 * @client_cert_blob: client_cert作为内联数据，如果未使用，则为NULL
 * @client_cert_blob_len: 客户端客户端长度
 * @private_key: PEM或DER格式（传统格式（RSA private key）或PKCS#8（private EY）的客户端私钥的文件或引用名称
 * @private_key_blob: private_key作为内联数据，如果未使用则为%NULL
 * @private_key_blob_len: private_key_blob长度
 * @private_key_passwd: 解密私钥的密码短语，如果未使用密码短语，则为NULL。
 * @dh_file: PEM格式的DH/DSA数据的文件名，如果未使用，则为%NULL
 * @dh_blob: dh_file作为内联数据，如果未使用，则为%NULL
 * @dh_blob_len: dh_blob长度
 * @engine: 1=使用引擎（例如智能卡）进行私钥操作（目前这是OpenSSL特有的）
 * @engine_id: 引擎id字符串（这是目前OpenSSL特有的）
 * @ppin: 指向配置中pin变量的指针（目前这是OpenSSL特有的）
 * @key_id: 使用引擎时的私钥id（这是目前OpenSSL特有的）
 * @cert_id: 使用引擎时的证书id
 * @ca_cert_id: 使用引擎时的CA证书id
 * @flags: 参数选项（TLS_CONN_*）
 * @ocsp_stapling_response: 带有缓存OCSP装订响应的DER编码文件，如果未启用OCSP，则为%NULL
 *
 * 要使用TLS_connection_set_params（）和TLS_global_set_param（）配置TLS连接参数。
 *
 * 证书和私钥可以配置为引用名称（文件路径或对证书存储的引用），也可以通过提供与内存中数据指针相同的数据来配置。每个字段只能使用一个选项。
 */
struct tls_connection_params {
	const char *ca_cert;
	const u8 *ca_cert_blob;
	size_t ca_cert_blob_len;
	const char *ca_path;
	const char *subject_match;
	const char *altsubject_match;
	const char *client_cert;
	const u8 *client_cert_blob;
	size_t client_cert_blob_len;
	const char *private_key;
	const u8 *private_key_blob;
	size_t private_key_blob_len;
	const char *private_key_passwd;
	const char *dh_file;
	const u8 *dh_blob;
	size_t dh_blob_len;

	/* OpenSSL特定变量*/
	int engine;
	const char *engine_id;
	const char *pin;
	const char *key_id;
	const char *cert_id;
	const char *ca_cert_id;

	unsigned int flags;
	const char *ocsp_stapling_response;
};


/**
 * tls_init-初始化tls库
 * @conf: TLS库的配置数据返回：在调用其他函数时用作TLS_ctx的上下文数据，或失败时为%NULL。
 *
 * 在程序启动期间调用一次，每个RSN预认证会话调用一次。换句话说，可以有两个并发TLS上下文。如果需要全局库初始化（即，在两种身份验证类型之间共享的库），TLS库包装器应维护一个引用计数器，并仅在从0到1引用时进行全局初始化。
 */
void * tls_init(void);

/**
 * tls_deinit-取消初始化tls库
 * @tls_ctx: TLS_init（）中的TLS上下文数据
 *
 * 在程序关闭期间调用一次，每个RSN预认证会话调用一次。如果需要全局库去初始化（即，在两种身份验证类型之间共享的），TLS库包装器应维护一个引用计数器，并仅在从1个引用移动到0个引用时执行全局去初始化。
 */
void tls_deinit(void *tls_ctx);

/**
 * tls_get_errors-处理挂起的错误
 * @tls_ctx: TLS_init（）中的TLS上下文数据返回：找到的错误数，如果未检测到错误，则为0。
 *
 * 处理所有挂起的TLS错误。
 */
int tls_get_errors(void *tls_ctx);

/**
 * tls_connection_init-初始化新的tls连接
 * @tls_ctx: TLS_init（）中的TLS上下文数据返回：连接上下文数据，其他函数调用的conn
 */
struct tls_connection * tls_connection_init(void *tls_ctx);

/**
 * tls_connection_deinit-释放tls连接数据
 * @tls_ctx: TLS_init（）中的TLS上下文数据
 * @conn: tls_Connection_init（）中的连接上下文数据
 *
 * 释放为TLS连接分配的所有资源。
 */
void tls_connection_deinit(void *tls_ctx, struct tls_connection *conn);

/**
 * tls_connection_enstablished-tls连接是否已完成？
 * @tls_ctx: TLS_init（）中的TLS上下文数据
 * @conn: tls_Connection_init（）中的连接上下文数据返回：如果tls连接已完成，则返回1，否则返回0。
 */
int tls_connection_established(void *tls_ctx, struct tls_connection *conn);

/**
 * tls_connection_shutdown-关闭tls连接
 * @tls_ctx: TLS_init（）中的TLS上下文数据
 * @conn: tls_Connection_init（）中的连接上下文数据返回：成功时返回0，失败时返回-1
 *
 * 关闭当前TLS连接而不释放所有资源。可以使用相同的conn启动新连接，而无需再次调用tls_connection_init（）或设置证书等。新连接应尝试使用会话恢复。
 */
int tls_connection_shutdown(void *tls_ctx, struct tls_connection *conn);

enum {
	TLS_SET_PARAMS_ENGINE_PRV_VERIFY_FAILED = -3,
	TLS_SET_PARAMS_ENGINE_PRV_INIT_FAILED = -2
};

/**
 * tls_connection_set_params-设置tls连接参数
 * @tls_ctx: TLS_init（）中的TLS上下文数据
 * @conn: tls_Connection_init（）中的连接上下文数据
 * @params: Connection parameters返回：0表示成功，-1表示失败，TLS_SET_PARAMS_ENGINE_PRV_INIT_FAILED（-2）表示可能的PIN错误导致PKCS#11引擎失败，或TLS_SET-PARAMS_ENGINE _PRV_VERIFY_FAILED（-3）表示验证PKCS#111引擎私钥失败。
 */
int __must_check
tls_connection_set_params(void *tls_ctx, struct tls_connection *conn,
			  const struct tls_connection_params *params);

/**
 * tls_global_set_params-为所有tls连接设置tls参数
 * @tls_ctx: TLS_init（）中的TLS上下文数据
 * @params: Global TLS参数返回：成功时返回0，失败时返回-1，可能的PIN错误导致PKCS#11引擎失败时返回TLS_SET_PARAMS_ENGINE_PRV_INIT_FAILED（-2），验证PKCS#111引擎私钥失败时返回TLS_SET_PARAM S_ENGINE_VERIFY_FAILED（-3）。
 */
int __must_check tls_global_set_params(
	void *tls_ctx, const struct tls_connection_params *params);

/**
 * tls_global_set_verify-设置全局证书验证选项
 * @tls_ctx: TLS_init（）中的TLS上下文数据
 * @check_crl: 0=不验证CRL，1=验证用户证书的CRL，2=验证所有证书的CRL返回：成功时返回0，失败时返回-1
 */
int __must_check tls_global_set_verify(void *tls_ctx, int check_crl);

/**
 * tls_connection_set_verify-设置证书验证选项
 * @tls_ctx: TLS_init（）中的TLS上下文数据
 * @conn: tls_Connection_init（）中的连接上下文数据
 * @verify_peer: 1=验证对等证书
 * @flags: 连接标志（TLS_CONN_*）
 * @session_ctx: 会话缓存上下文或%NULL以使用默认值
 * @session_ctx_len: @session_ctx的长度（字节）。返回：成功时返回0，失败时返回-1
 */
int tls_connection_set_verify(void *tls_ctx,
					   struct tls_connection *conn,
					   int verify_peer,
					   unsigned int flags,
					   const u8 *session_ctx,
					   size_t session_ctx_len);

/**
 * tls_connection_get_random-从tls连接获取随机数据
 * @tls_ctx: TLS_init（）中的TLS上下文数据
 * @conn: tls_Connection_init（）中的连接上下文数据
 * @data: 客户端/服务器随机数据的结构（成功时填充）返回：成功时为0，失败时为-1
 */
int __must_check tls_connection_get_random(void *tls_ctx,
					 struct tls_connection *conn,
					 struct tls_random *data);

/**
 * tls_connection_export_key-从tls连接派生密钥材料
 * @tls_ctx: TLS_init（）中的TLS上下文数据
 * @conn: tls_Connection_init（）中的连接上下文数据
 * @label: PRF标签（例如，密钥描述）
 * @context: 可选的额外上层上下文（最大长度2^16）
 * @context_len: 上下文值的长度
 * @out: TLS-PRF输出数据缓冲区
 * @out_len: 输出缓冲区的长度：成功时返回0，失败时返回-1
 *
 * 使用RFC 5705中描述的机制导出密钥材料。如果上下文为%NULL，则不提供上下文；否则，提供上下文（包括context_len＝＝0的空上下文的情况）。
 */
int __must_check tls_connection_export_key(void *tls_ctx,
					   struct tls_connection *conn,
					   const char *label,
					   const u8 *context,
					   size_t context_len,
					   u8 *out, size_t out_len);

/**
 * tls_connection_get_eap_fast_key-导出eap-fast的密钥材料
 * @tls_ctx: TLS_init（）中的TLS上下文数据
 * @conn: tls_Connection_init（）中的连接上下文数据
 * @out: TLS-PRF输出数据缓冲区
 * @out_len: 输出缓冲区的长度：成功时返回0，失败时返回-1
 *
 * 在普通TLS密钥块之后导出密钥材料，以用于EAP-FAST。大多数调用者都希望tls_connection_export_key（），但EAP-FAST使用不同的传统机制。
 */
int __must_check tls_connection_get_eap_fast_key(void *tls_ctx,
						 struct tls_connection *conn,
						 u8 *out, size_t out_len);

/**
 * tls_connection_handshake-处理tls握手（客户端）
 * @tls_ctx: TLS_init（）中的TLS上下文数据
 * @conn: tls_Connection_init（）中的连接上下文数据
 * @in_data: 从TLS服务器输入数据
 * @appl_data: 指向应用程序数据指针的指针，如果丢失则返回%NULL返回：输出数据，失败时返回%NULL
 *
 * 调用者负责释放返回的输出数据。如果最终握手消息包含应用程序数据，则对其进行解密，并将appl_data（如果不是%NULL）设置为指向该数据。调用者负责释放appl_data。
 *
 * 此函数在TLS握手期间使用。第一次调用是用in_data==%NULL完成的，库将返回ClientHello数据包。然后将此数据包发送到服务器，并通过再次调用此函数（in_data指向来自服务器的TLS消息）向TLS库提供来自服务器的响应。
 *
 * 如果TLS握手失败，此函数可能返回%NULL。但是，如果TLS库有TLS警报要发送，则应将其作为输出数据返回。在这种情况下，tls_connection_get_failed（）必须返回失败（>0）。
 *
 * tls握手成功完成后，tls_connection_estabshed（）应返回1。
 */
struct wpabuf * tls_connection_handshake(void *tls_ctx,
					 struct tls_connection *conn,
					 const struct wpabuf *in_data,
					 struct wpabuf **appl_data);

struct wpabuf * tls_connection_handshake2(void *tls_ctx,
					  struct tls_connection *conn,
					  const struct wpabuf *in_data,
					  struct wpabuf **appl_data,
					  int *more_data_needed);

/**
 * tls_connection_server_shandshake-处理tls握手（服务器端）
 * @tls_ctx: TLS_init（）中的TLS上下文数据
 * @conn: tls_Connection_init（）中的连接上下文数据
 * @in_data: 从TLS对等端输入数据
 * @appl_data: 指向应用程序数据指针的指针，如果丢失则返回%NULL返回：输出数据，失败时返回%NULL
 *
 * 调用者负责释放返回的输出数据。
 */
struct wpabuf * tls_connection_server_handshake(void *tls_ctx,
						struct tls_connection *conn,
						const struct wpabuf *in_data,
						struct wpabuf **appl_data);

/**
 * tls_connection_encrypt-将数据加密到tls隧道
 * @tls_ctx: TLS_init（）中的TLS上下文数据
 * @conn: tls_Connection_init（）中的连接上下文数据
 * @in_data: 要加密的明文数据返回：加密的TLS数据或失败时的%NULL
 *
 * 此函数在TLS握手成功完成后使用，以在加密隧道中发送数据。调用者负责释放返回的输出数据。
 */
struct wpabuf * tls_connection_encrypt(void *tls_ctx,
				       struct tls_connection *conn,
				       const struct wpabuf *in_data);

/**
 * tls_connection_decrypt-从tls隧道解密数据
 * @tls_ctx: TLS_init（）中的TLS上下文数据
 * @conn: tls_Connection_init（）中的连接上下文数据
 * @in_data: 加密TLS数据返回：解密TLS数据或失败时为%NULL
 *
 * 此功能在TLS握手成功完成后使用，以从加密隧道接收数据。调用者负责释放返回的输出数据。
 */
struct wpabuf * tls_connection_decrypt(void *tls_ctx,
				       struct tls_connection *conn,
				       const struct wpabuf *in_data);

struct wpabuf * tls_connection_decrypt2(void *tls_ctx,
					struct tls_connection *conn,
					const struct wpabuf *in_data,
					int *more_data_needed);

/**
 * tls_connection_resumed-是否使用会话恢复
 * @tls_ctx: TLS_init（）中的TLS上下文数据
 * @conn: tls_Connection_init（）中的连接上下文数据返回：如果当前会话使用了会话恢复，则返回1；如果没有，则返回0
 */
int tls_connection_resumed(void *tls_ctx, struct tls_connection *conn);

enum {
	TLS_CIPHER_NONE,
	TLS_CIPHER_RC4_SHA /* 0x0005年*/,
	TLS_CIPHER_AES128_SHA /* 0x002f*/,
	TLS_CIPHER_RSA_DHE_AES128_SHA /* 0月31日*/,
	TLS_CIPHER_ANON_DH_AES128_SHA /* 0x0034位*/,
	TLS_CIPHER_RSA_DHE_AES256_SHA /* 0x0039位*/,
	TLS_CIPHER_AES256_SHA /* 0x0035位*/,
};

/**
 * tls_connection_set_cipher_list-配置可接受的密码套件
 * @tls_ctx: TLS_init（）中的TLS上下文数据
 * @conn: tls_Connection_init（）中的连接上下文数据
 * @ciphers: 零（TLS_CIPHER_NONE）终止的允许密码列表（TLS_CIPHER_）。返回：成功时返回0，失败时返回-1
 */
int __must_check tls_connection_set_cipher_list(void *tls_ctx,
						struct tls_connection *conn,
						u8 *ciphers);

/**
 * tls_get_cipher-获取当前密码名称
 * @tls_ctx: TLS_init（）中的TLS上下文数据
 * @conn: tls_Connection_init（）中的连接上下文数据
 * @buf: 密码名缓冲区
 * @buflen: buf size返回：成功时返回0，失败时返回-1
 *
 * 获取当前使用的密码的名称。
 */
int __must_check tls_get_cipher(void *tls_ctx, struct tls_connection *conn,
				char *buf, size_t buflen);

/**
 * tls_connection_enable_workaround-启用tls解决方案选项
 * @tls_ctx: TLS_init（）中的TLS上下文数据
 * @conn: tls_Connection_init（）中的连接上下文数据返回：成功时返回0，失败时返回-1
 *
 * 此函数用于为缓冲区SSL/TLS实现启用特定于连接的解决方案选项。
 */
int __must_check tls_connection_enable_workaround(void *tls_ctx,
						  struct tls_connection *conn);

/**
 * tls_connection_client_hello_ext-为ClientHello设置tls扩展
 * @tls_ctx: TLS_init（）中的TLS上下文数据
 * @conn: tls_Connection_init（）中的连接上下文数据
 * @ext_type: 扩展类型
 * @data: 扩展负载（%NULL以删除扩展）
 * @data_len: 扩展负载长度返回：成功时返回0，失败时返回-1
 */
int __must_check tls_connection_client_hello_ext(void *tls_ctx,
						 struct tls_connection *conn,
						 int ext_type, const u8 *data,
						 size_t data_len);

/**
 * tls_connection_get_failed-获取连接失败状态
 * @tls_ctx: TLS_init（）中的TLS上下文数据
 * @conn: tls_Connection_init（）中的连接上下文数据
 *
 * 如果连接失败，则返回>0，否则返回0。
 */
int tls_connection_get_failed(void *tls_ctx, struct tls_connection *conn);

/**
 * tls_connection_get_read_alerts-获取连接读取警报状态
 * @tls_ctx: TLS_init（）中的TLS上下文数据
 * @conn: tls_Connection_init（）中的连接上下文数据返回：在此连接期间发生致命读取（远程端报告错误）的次数。
 */
int tls_connection_get_read_alerts(void *tls_ctx, struct tls_connection *conn);

/**
 * tls_connection_get_write_alers-获取连接写入警报状态
 * @tls_ctx: TLS_init（）中的TLS上下文数据
 * @conn: tls_Connection_init（）中的连接上下文数据返回：在此连接期间发生致命写入（本地检测到错误）的次数。
 */
int tls_connection_get_write_alerts(void *tls_ctx,
				    struct tls_connection *conn);

/**
 * tls_capabilities-获取支持的tls功能
 * @tls_ctx: TLS_init（）中的TLS上下文数据返回：支持TLS功能的位字段（TLS_CAPABILITY_）
 */
unsigned int tls_capabilities(void *tls_ctx);

typedef int (*tls_session_ticket_cb)
(void *ctx, const u8 *ticket, size_t len, const u8 *client_random,
 const u8 *server_random, u8 *master_secret);

int __must_check  tls_connection_set_session_ticket_cb(
	void *tls_ctx, struct tls_connection *conn,
	tls_session_ticket_cb cb, void *ctx);

int tls_prf_sha1_md5(const u8 *secret, size_t secret_len, const char *label,
             const u8 *seed, size_t seed_len, u8 *out, size_t outlen);

#endif /* TLS_H */

