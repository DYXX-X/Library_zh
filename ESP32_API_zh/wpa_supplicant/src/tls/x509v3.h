/*
 * 十、 509v3证书解析和处理版权所有（c）2006-2011，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef X509V3_H
#define X509V3_H

#include "asn1.h"

struct x509_algorithm_identifier {
	struct asn1_oid oid;
};

struct x509_name_attr {
	enum x509_name_attr_type {
		X509_NAME_ATTR_NOT_USED,
		X509_NAME_ATTR_DC,
		X509_NAME_ATTR_CN,
		X509_NAME_ATTR_C,
		X509_NAME_ATTR_L,
		X509_NAME_ATTR_ST,
		X509_NAME_ATTR_O,
		X509_NAME_ATTR_OU
	} type;
	char *value;
};

#define X509_MAX_NAME_ATTRIBUTES 20

struct x509_name {
	struct x509_name_attr attr[X509_MAX_NAME_ATTRIBUTES];
	size_t num_attr;
	char *email; /* 电子邮件地址*/

	/* 来自替代名称扩展名*/
	char *alt_email; /* rfc822名称*/
	char *dns; /* dNS名称*/
	char *uri; /* 统一资源标识符*/
	u8 *ip; /* IP地址*/
	size_t ip_len; /* IPv4:4，IPv4:16*/
	struct asn1_oid rid; /* 注册ID*/
};

struct x509_certificate {
	struct x509_certificate *next;
	enum { X509_CERT_V1 = 0, X509_CERT_V2 = 1, X509_CERT_V3 = 2 } version;
	unsigned long serial_number;
	struct x509_algorithm_identifier signature;
	struct x509_name issuer;
	struct x509_name subject;
	os_time_t not_before;
	os_time_t not_after;
	struct x509_algorithm_identifier public_key_alg;
	u8 *public_key;
	size_t public_key_len;
	struct x509_algorithm_identifier signature_alg;
	u8 *sign_value;
	size_t sign_value_len;

	/* 扩展*/
	unsigned int extensions_present;
#define X509_EXT_BASIC_CONSTRAINTS		(1 << 0)
#define X509_EXT_PATH_LEN_CONSTRAINT		(1 << 1)
#define X509_EXT_KEY_USAGE			(1 << 2)
#define X509_EXT_SUBJECT_ALT_NAME		(1 << 3)
#define X509_EXT_ISSUER_ALT_NAME		(1 << 4)

	/* 基本约束*/
	int ca; /* 环腺苷酸*/
	unsigned long path_len_constraint; /* 路径长度约束*/

	/* 密钥用法*/
	unsigned long key_usage;
#define X509_KEY_USAGE_DIGITAL_SIGNATURE	(1 << 0)
#define X509_KEY_USAGE_NON_REPUDIATION		(1 << 1)
#define X509_KEY_USAGE_KEY_ENCIPHERMENT		(1 << 2)
#define X509_KEY_USAGE_DATA_ENCIPHERMENT	(1 << 3)
#define X509_KEY_USAGE_KEY_AGREEMENT		(1 << 4)
#define X509_KEY_USAGE_KEY_CERT_SIGN		(1 << 5)
#define X509_KEY_USAGE_CRL_SIGN			(1 << 6)
#define X509_KEY_USAGE_ENCIPHER_ONLY		(1 << 7)
#define X509_KEY_USAGE_DECIPHER_ONLY		(1 << 8)

	/*
	 * DER格式证书遵循结构x509_certificate。这些指针指向该缓冲区。
	 */
	const u8 *cert_start;
	size_t cert_len;
	const u8 *tbs_cert_start;
	size_t tbs_cert_len;
};

enum {
	X509_VALIDATE_OK,
	X509_VALIDATE_BAD_CERTIFICATE,
	X509_VALIDATE_UNSUPPORTED_CERTIFICATE,
	X509_VALIDATE_CERTIFICATE_REVOKED,
	X509_VALIDATE_CERTIFICATE_EXPIRED,
	X509_VALIDATE_CERTIFICATE_UNKNOWN,
	X509_VALIDATE_UNKNOWN_CA
};

void x509_certificate_free(struct x509_certificate *cert);
struct x509_certificate * x509_certificate_parse(const u8 *buf, size_t len);
void x509_name_string(struct x509_name *name, char *buf, size_t len);
int x509_name_compare(struct x509_name *a, struct x509_name *b);
void x509_certificate_chain_free(struct x509_certificate *cert);
int x509_certificate_check_signature(struct x509_certificate *issuer,
				     struct x509_certificate *cert);
int x509_certificate_chain_validate(struct x509_certificate *trusted,
				    struct x509_certificate *chain,
				    int *reason, int disable_time_checks);
struct x509_certificate *
x509_certificate_get_subject(struct x509_certificate *chain,
			     struct x509_name *name);
int x509_certificate_self_signed(struct x509_certificate *cert);

#endif /* X509V3_H */

