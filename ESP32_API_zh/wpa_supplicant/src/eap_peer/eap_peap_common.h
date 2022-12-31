/*
 * EAP-PEAP通用例程版权所有（c）2008-2011，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef EAP_PEAP_COMMON_H
#define EAP_PEAP_COMMON_H

int peap_prfplus(int version, const u8 *key, size_t key_len,
		 const char *label, const u8 *seed, size_t seed_len,
		 u8 *buf, size_t buf_len);

#endif /* EAP_PEAP_COMMON_H */

