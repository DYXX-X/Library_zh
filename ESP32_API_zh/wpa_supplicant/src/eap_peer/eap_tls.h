/*
 * EAP peer:EAP-TLS/PEAP/TTLS/FAST通用功能版权所有（c）2004-20092012，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef EAP_TLS_H
#define EAP_TLS_H

#include "eap_i.h"
#include "eap_common.h"
#include "eap.h"
#include "utils/wpabuf.h"

void * eap_tls_init(struct eap_sm *sm);
void eap_tls_deinit(struct eap_sm *sm, void *priv);
struct wpabuf * eap_tls_process(struct eap_sm *sm, void *priv,
                                       struct eap_method_ret *ret,
                                       const struct wpabuf *reqData);

u8 * eap_tls_getKey(struct eap_sm *sm, void *priv, size_t *len);

#endif /* EAP_TLS_H */

