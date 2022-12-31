/*
 * EAP peer:EAP-TLS/PEAP/TTLS/FAST通用功能版权所有（c）2004-20092012，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef EAP_TLS_COMMON_H
#define EAP_TLS_COMMON_H

/**
 * struct eap_sl_data-eap方法的TLS数据
 */
struct eap_ssl_data {
	/**
	 * conn-TLS_connection_init（）中的TLS连接上下文数据
	 */
	struct tls_connection *conn;

	/**
	 * tls_out-要以碎片形式发送的tls消息
	 */
	struct wpabuf *tls_out;

	/**
	 * tls_out_pos-传出tls消息中的当前位置
	 */
	size_t tls_out_pos;

	/**
	 * tls_out_limit-传出tls消息的最大片段大小
	 */
	size_t tls_out_limit;

	/**
	 * tls_in-已接收tls消息缓冲区以进行重新组装
	 */
	struct wpabuf *tls_in;

	/**
	 * tls_in_left-传入tls消息中剩余的字节数
	 */
	size_t tls_in_left;

	/**
	 * tls_in_total-传入tls消息中的总字节数
	 */
	size_t tls_in_total;

	/**
	 * 阶段2-此TLS连接是否用于EAP阶段2（隧道）
	 */
	int phase2;

	/**
	 * include_tls_length—即使tls数据未分段，是否包含tls长度字段
	 */
	int include_tls_length;

	/**
	 * eap-分配有eap_peer_sm_init（）的eap状态机
	 */
	struct eap_sm *eap;

	/**
	 * ssl_ctx-用于连接的TLS库上下文
	 */
	void *ssl_ctx;

	/**
	 * eap_type-阶段1中使用的eap方法（eap_type_TLS/PEAP/TTLS/FAST）
	 */
	u8 eap_type;
};


/* EAP TLS标志*/
#define EAP_TLS_FLAGS_LENGTH_INCLUDED 0x80
#define EAP_TLS_FLAGS_MORE_FRAGMENTS 0x40
#define EAP_TLS_FLAGS_START 0x20
#define EAP_TLS_VERSION_MASK 0x07

 /* 最多可为128个字节，但仅使用前64个字节*/
#define EAP_TLS_KEY_LEN 64

/* 用作UNAUTH-TLS标志的伪类型*/
#define EAP_UNAUTH_TLS_TYPE 255


int eap_peer_tls_ssl_init(struct eap_sm *sm, struct eap_ssl_data *data,
			  struct eap_peer_config *config, u8 eap_type);
void eap_peer_tls_ssl_deinit(struct eap_sm *sm, struct eap_ssl_data *data);
u8 * eap_peer_tls_derive_key(struct eap_sm *sm, struct eap_ssl_data *data,
			     const char *label, size_t len);
u8 * eap_peer_tls_derive_session_id(struct eap_sm *sm,
				    struct eap_ssl_data *data, u8 eap_type,
				    size_t *len);
int eap_peer_tls_process_helper(struct eap_sm *sm, struct eap_ssl_data *data,
				EapType eap_type, int peap_version,
				u8 id, const u8 *in_data, size_t in_len,
				struct wpabuf **out_data);
struct wpabuf * eap_peer_tls_build_ack(u8 id, EapType eap_type,
				       int peap_version);
int eap_peer_tls_reauth_init(struct eap_sm *sm, struct eap_ssl_data *data);
int eap_peer_tls_status(struct eap_sm *sm, struct eap_ssl_data *data,
			char *buf, size_t buflen, int verbose);
const u8 * eap_peer_tls_process_init(struct eap_sm *sm,
				     struct eap_ssl_data *data,
				     EapType eap_type,
				     struct eap_method_ret *ret,
				     const struct wpabuf *reqData,
				     size_t *len, u8 *flags);
void eap_peer_tls_reset_input(struct eap_ssl_data *data);
void eap_peer_tls_reset_output(struct eap_ssl_data *data);
int eap_peer_tls_decrypt(struct eap_sm *sm, struct eap_ssl_data *data,
			 const struct wpabuf *in_data,
			 struct wpabuf **in_decrypted);
int eap_peer_tls_encrypt(struct eap_sm *sm, struct eap_ssl_data *data,
			 EapType eap_type, int peap_version, u8 id,
			 const struct wpabuf *in_data,
			 struct wpabuf **out_data);
int eap_peer_select_phase2_methods(struct eap_peer_config *config,
				   const char *prefix,
				   struct eap_method_type **types,
				   size_t *num_types);
int eap_peer_tls_phase2_nak(struct eap_method_type *types, size_t num_types,
			    struct eap_hdr *hdr, struct wpabuf **resp);

#endif /* EAP_TLS_COMMON_H */

