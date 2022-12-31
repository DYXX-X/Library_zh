/*
 * EAP-FAST定义（RFC 4851）版权所有（c）2004-2008，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef EAP_FAST_H
#define EAP_FAST_H

#define EAP_FAST_VERSION 1
#define EAP_FAST_KEY_LEN 64
#define EAP_FAST_SIMCK_LEN 40
#define EAP_FAST_SKS_LEN 40
#define EAP_FAST_CMK_LEN 20

#define TLS_EXT_PAC_OPAQUE 35

/*
 * RFC 5422：第4.2.1节-PAC TLV属性/类型字段的格式注意：位0x8000（强制）和位0x4000（保留）也在通用PAC TLV格式中定义（第4.2节）。
 */
#define PAC_TYPE_PAC_KEY 1
#define PAC_TYPE_PAC_OPAQUE 2
#define PAC_TYPE_CRED_LIFETIME 3
#define PAC_TYPE_A_ID 4
#define PAC_TYPE_I_ID 5
/*
 * 6以前分配给SERVER_PROTECTED_DATA，但draft-cam-winget-eap-fast-provisioning-02.txt将其更改为保留。
 */
#define PAC_TYPE_A_ID_INFO 7
#define PAC_TYPE_PAC_ACKNOWLEDGEMENT 8
#define PAC_TYPE_PAC_INFO 9
#define PAC_TYPE_PAC_TYPE 10

#ifdef _MSC_VER
#pragma pack(push, 1)
#endif /* _MSC_VER */

struct pac_tlv_hdr {
	be16 type;
	be16 len;
} STRUCT_PACKED;

#ifdef _MSC_VER
#pragma pack(pop)
#endif /* _MSC_VER */


#define EAP_FAST_PAC_KEY_LEN 32

/* RFC 5422:4.2.6 PAC类型TLV*/
#define PAC_TYPE_TUNNEL_PAC 1
/* 特定于应用程序的短期PAC（仅在易失性存储中）*/
/* 用户授权PAC*/
#define PAC_TYPE_USER_AUTHORIZATION 3
/* 特定于应用程序的长寿命PAC*/
/* 计算机身份验证PAC*/
#define PAC_TYPE_MACHINE_AUTHENTICATION 2


/*
 * RFC 5422：第3.3节-EAP-FAST配置交换中使用的密钥派生
 */
struct eap_fast_key_block_provisioning {
	/* TLS key_block后的额外密钥材料*/
	u8 session_key_seed[EAP_FAST_SKS_LEN];
	u8 server_challenge[16]; /* MSCHAPv2服务器挑战*/
	u8 client_challenge[16]; /* MSCHAPv2客户端挑战*/
};


struct wpabuf;
struct tls_connection;

struct eap_fast_tlv_parse {
	u8 *eap_payload_tlv;
	size_t eap_payload_tlv_len;
	struct eap_tlv_crypto_binding_tlv *crypto_binding;
	size_t crypto_binding_len;
	int iresult;
	int result;
	int request_action;
	u8 *pac;
	size_t pac_len;
};

void eap_fast_put_tlv_hdr(struct wpabuf *buf, u16 type, u16 len);
void eap_fast_put_tlv(struct wpabuf *buf, u16 type, const void *data,
		      u16 len);
void eap_fast_put_tlv_buf(struct wpabuf *buf, u16 type,
			  const struct wpabuf *data);
struct wpabuf * eap_fast_tlv_eap_payload(struct wpabuf *buf);
void eap_fast_derive_master_secret(const u8 *pac_key, const u8 *server_random,
				   const u8 *client_random, u8 *master_secret);
u8 * eap_fast_derive_key(void *ssl_ctx, struct tls_connection *conn,
			 size_t len);
int eap_fast_derive_eap_msk(const u8 *simck, u8 *msk);
int eap_fast_derive_eap_emsk(const u8 *simck, u8 *emsk);
int eap_fast_parse_tlv(struct eap_fast_tlv_parse *tlv,
		       int tlv_type, u8 *pos, size_t len);

#endif /* EAP_FAST_H */

