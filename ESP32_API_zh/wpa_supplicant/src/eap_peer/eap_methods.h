/*
 * EAP同行：方法注册版权所有（c）2004-2007，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef EAP_METHODS_H
#define EAP_METHODS_H

#include "eap_defs.h"
#include "eap_config.h"

const struct eap_method * eap_peer_get_eap_method(int vendor, EapType method);
const struct eap_method * eap_peer_get_methods(size_t *count);

u32 eap_get_phase2_type(const char *name, int *vendor);
struct eap_method_type * eap_get_phase2_types(struct eap_peer_config *config,
					      size_t *count);

struct eap_method * eap_peer_method_alloc(int verdor, EapType method,
					  const char *name);

void eap_peer_method_free(struct eap_method *method);
int eap_peer_method_register(struct eap_method *method);

void eap_peer_unregister_methods(void);

int eap_peer_tls_register(void);
int eap_peer_peap_register(void);
int eap_peer_ttls_register(void);
int eap_peer_fast_register(void);
int eap_peer_mschapv2_register(void);

void eap_peer_unregister_methods(void);
int eap_peer_register_methods(void);

#endif /* EAP_METHODS_H */

