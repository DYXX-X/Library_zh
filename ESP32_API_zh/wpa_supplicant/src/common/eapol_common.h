/*
 * hostapd和wpa_supplicant共享EAPOL定义版权所有（c）2002-2007，Jouni Malinen<j@w1.fi>
 *
 * 该程序是免费软件；您可以根据自由软件基金会发布的GNU通用公共许可证第2版的条款重新分发和/或修改它。
 *
 * 或者，此软件可以根据BSD许可证条款进行分发。
 *
 * 有关详细信息，请参阅自述和复制。
 */

#ifndef EAPOL_COMMON_H
#define EAPOL_COMMON_H

/* IEEE标准802.1X-2004*/

struct ieee802_1x_hdr {
	u8 version;
	u8 type;
	be16 length;
	/* 后跟数据的长度八位字节*/
} STRUCT_PACKED;


#define EAPOL_VERSION 2
#define SPP_AMSDU_CAP_ENABLE   1
#define SPP_AMSDU_REQ_ENABLE   1
#define SPP_AMSDU_CAP_DISABLE  0
#define SPP_AMSDU_REQ_DISABLE  0

enum { IEEE802_1X_TYPE_EAP_PACKET = 0,
       IEEE802_1X_TYPE_EAPOL_START = 1,
       IEEE802_1X_TYPE_EAPOL_LOGOFF = 2,
       IEEE802_1X_TYPE_EAPOL_KEY = 3,
       IEEE802_1X_TYPE_EAPOL_ENCAPSULATED_ASF_ALERT = 4
};

enum { EAPOL_KEY_TYPE_RC4 = 1, EAPOL_KEY_TYPE_RSN = 2,
       EAPOL_KEY_TYPE_WPA = 254 };

#define IEEE8021X_REPLAY_COUNTER_LEN 8
#define IEEE8021X_KEY_SIGN_LEN 16
#define IEEE8021X_KEY_IV_LEN 16

#define IEEE8021X_KEY_INDEX_FLAG 0x80
#define IEEE8021X_KEY_INDEX_MASK 0x03

struct ieee802_1x_eapol_key {
	u8 type;
	/* 注意：key_length未对齐*/
	u8 key_length[2];
	/* 在用于加密密钥字段的密钥材料的生命周期内不重复；此处可以使用64位NTP时间戳*/
	u8 replay_counter[IEEE8021X_REPLAY_COUNTER_LEN];
	u8 key_iv[IEEE8021X_KEY_IV_LEN]; /* 密码随机数*/
	u8 key_index; /* 最高有效位中的密钥标志：0=广播（默认密钥），1=单播（密钥映射密钥）；密钥索引在7个最低有效位中*/
	/* 以MS MPPE发送密钥作为密钥计算的HMAC-MD5消息完整性检查*/
	u8 key_signature[IEEE8021X_KEY_SIGN_LEN];

	/* 后跟密钥：如果包体长度=44+密钥长度，则密钥字段（key_length字节）包含加密形式的密钥；如果包体长度＝44，则密钥字段不存在，并且key_length表示要用作密钥材料的来自MS MPPE发送密钥属性的最低有效八位字节的数量；加密中使用的RC4密钥=密钥IV+MS MPPE Recv密钥*/
} STRUCT_PACKED;

#endif /* EAPOL_COMMON_H */

