/*
 * EAP服务器/对等端：EAP-TTLS（RFC 5281）版权所有（c）2004-2007，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef EAP_TTLS_H
#define EAP_TTLS_H

struct ttls_avp {
	be32 avp_code;
	be32 avp_length; /* 8位标志，24位长度；长度包括AVP标头*/
	/* 可选32位供应商ID*/
	/* 数据*/
};

struct ttls_avp_vendor {
	be32 avp_code;
	be32 avp_length; /* 8位标志，24位长度；长度包括AVP标头*/
	be32 vendor_id;
	/* 数据*/
};

#define AVP_FLAGS_VENDOR 0x80
#define AVP_FLAGS_MANDATORY 0x40

#define AVP_PAD(start, pos) \
do { \
	int __pad; \
	__pad = (4 - (((pos) - (start)) & 3)) & 3; \
	os_memset((pos), 0, __pad); \
	pos += __pad; \
} while (0)


/* RFC 2865 */
#define RADIUS_ATTR_USER_NAME 1
#define RADIUS_ATTR_USER_PASSWORD 2
#define RADIUS_ATTR_CHAP_PASSWORD 3
#define RADIUS_ATTR_REPLY_MESSAGE 18
#define RADIUS_ATTR_CHAP_CHALLENGE 60
#define RADIUS_ATTR_EAP_MESSAGE 79

/* RFC 2548 */
#define RADIUS_VENDOR_ID_MICROSOFT 311
#define RADIUS_ATTR_MS_CHAP_RESPONSE 1
#define RADIUS_ATTR_MS_CHAP_ERROR 2
#define RADIUS_ATTR_MS_CHAP_NT_ENC_PW 6
#define RADIUS_ATTR_MS_CHAP_CHALLENGE 11
#define RADIUS_ATTR_MS_CHAP2_RESPONSE 25
#define RADIUS_ATTR_MS_CHAP2_SUCCESS 26
#define RADIUS_ATTR_MS_CHAP2_CPW 27

#define EAP_TTLS_MSCHAPV2_CHALLENGE_LEN 16
#define EAP_TTLS_MSCHAPV2_RESPONSE_LEN 50
#define EAP_TTLS_MSCHAP_CHALLENGE_LEN 8
#define EAP_TTLS_MSCHAP_RESPONSE_LEN 50
#define EAP_TTLS_CHAP_CHALLENGE_LEN 16
#define EAP_TTLS_CHAP_PASSWORD_LEN 16

#endif /* EAP_TTLS_H */

