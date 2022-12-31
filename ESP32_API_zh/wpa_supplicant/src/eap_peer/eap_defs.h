/*
 * EAP服务器/对等端：共享EAP定义版权所有（c）2004-2007，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef EAP_DEFS_H
#define EAP_DEFS_H

/* RFC 3748-可扩展身份验证协议（EAP）*/

#ifdef _MSC_VER
#pragma pack(push, 1)
#endif /* _MSC_VER */

struct eap_hdr {
	u8 code;
	u8 identifier;
	be16 length; /* 包括代码和标识符；网络字节顺序*/
	/* 后跟长度为4个八位字节的数据*/
} STRUCT_PACKED;


#ifdef _MSC_VER
#pragma pack(pop)
#endif /* _MSC_VER */

enum { EAP_CODE_REQUEST = 1, EAP_CODE_RESPONSE = 2, EAP_CODE_SUCCESS = 3,
       EAP_CODE_FAILURE = 4 };

/* EAP请求和响应数据以一个八位字节类型开头。成功和失败没有其他数据。*/

/*
 * IANA分配的EAP方法类型：http://www.iana.org/assignments/eap-numbers
 */
typedef enum {
	EAP_TYPE_NONE = 0,
	EAP_TYPE_IDENTITY = 1 /* RFC 3748 */,
	EAP_TYPE_NOTIFICATION = 2 /* RFC 3748 */,
	EAP_TYPE_NAK = 3 /* 仅响应，RFC 3748*/,
	EAP_TYPE_MD5 = 4, /* RFC 3748 */
	EAP_TYPE_OTP = 5 /* RFC 3748 */,
	EAP_TYPE_GTC = 6, /* RFC 3748 */
	EAP_TYPE_TLS = 13 /* RFC 2716 */,
	EAP_TYPE_LEAP = 17 /* Cisco专有*/,
	EAP_TYPE_SIM = 18 /* RFC 4186 */,
	EAP_TYPE_TTLS = 21 /* RFC 5281 */,
	EAP_TYPE_AKA = 23 /* RFC 4187 */,
	EAP_TYPE_PEAP = 25 /* draft-josefsson-pppext-eap-tls-eap-06.txt*/,
	EAP_TYPE_MSCHAPV2 = 26 /* 草稿-kamath-pppex-eap-mschapv2-00.txt*/,
	EAP_TYPE_TLV = 33 /* draft-josefsson-pppext-eap-tls-eap-07.txt*/,
	EAP_TYPE_TNC = 38 /* TNC IF-T v1.0-r3；注：暂定任务；类型38以前已分配给EAP-HTTP摘要（funk.com）*/,
	EAP_TYPE_FAST = 43 /* RFC 4851 */,
	EAP_TYPE_PAX = 46 /* RFC 4746 */,
	EAP_TYPE_PSK = 47 /* RFC 4764 */,
	EAP_TYPE_SAKE = 48 /* RFC 4763 */,
	EAP_TYPE_IKEV2 = 49 /* RFC 5106 */,
	EAP_TYPE_AKA_PRIME = 50 /* RFC 5448 */,
	EAP_TYPE_GPSK = 51 /* RFC 5433 */,
	EAP_TYPE_PWD = 52 /* RFC 5931 */,
	EAP_TYPE_EKE = 53 /* RFC 6124 */,
	EAP_TYPE_EXPANDED = 254 /* RFC 3748 */
} EapType;


/* 供应商特定类型的SMI网络管理专用企业代码*/
enum {
	EAP_VENDOR_IETF = 0,
	EAP_VENDOR_MICROSOFT = 0x000137 /* 微软*/,
	EAP_VENDOR_WFA = 0x00372A /* Wi-Fi联盟*/,
	EAP_VENDOR_HOSTAP = 39068 /* hostapd/wpa_supplicant项目*/
};

struct eap_expand {
    u8 vendor_id[3];
    be32 vendor_type;
    u8 opcode;
} STRUCT_PACKED;

#define EAP_VENDOR_UNAUTH_TLS EAP_VENDOR_HOSTAP
#define EAP_VENDOR_TYPE_UNAUTH_TLS 1

#define EAP_MSK_LEN 64
#define EAP_EMSK_LEN 64

#endif /* EAP_DEFS_H */

