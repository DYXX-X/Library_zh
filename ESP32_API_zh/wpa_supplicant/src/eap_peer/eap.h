/*
 * EAP对等状态机功能（RFC 4137）版权所有（c）2004-2012，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef EAP_H
#define EAP_H

#include "common/defs.h"
#include "eap_peer/eap_defs.h"

struct eap_sm;

struct eap_method_type {
	int vendor;
	EapType method;
};

u8 *g_wpa_anonymous_identity;
int g_wpa_anonymous_identity_len;
u8 *g_wpa_username;
int g_wpa_username_len;
const u8 *g_wpa_client_cert;
int g_wpa_client_cert_len;
const u8 *g_wpa_private_key;
int g_wpa_private_key_len;
const u8 *g_wpa_private_key_passwd;
int g_wpa_private_key_passwd_len;

const u8 *g_wpa_ca_cert;
int g_wpa_ca_cert_len;

u8 *g_wpa_password;
int g_wpa_password_len;

u8 *g_wpa_new_password;
int g_wpa_new_password_len;

char *g_wpa_ttls_phase2_type;
char *g_wpa_phase1_options;

u8 *g_wpa_pac_file;
int g_wpa_pac_file_len;

bool g_wpa_suiteb_certification;

const u8 * eap_get_eapKeyData(struct eap_sm *sm, size_t *len);
void eap_deinit_prev_method(struct eap_sm *sm, const char *txt);
struct wpabuf * eap_sm_build_nak(struct eap_sm *sm, EapType type, u8 id);
struct wpabuf * eap_sm_buildIdentity(struct eap_sm *sm, int id, int encrypted);
int eap_peer_blob_init(struct eap_sm *sm);
void eap_peer_blob_deinit(struct eap_sm *sm);
int eap_peer_config_init(
	struct eap_sm *sm, const u8 *private_key_passwd,
	int private_key_passwd_len);
void eap_peer_config_deinit(struct eap_sm *sm);
void eap_sm_abort(struct eap_sm *sm);
int eap_peer_register_methods(void);
void eap_sm_request_identity(struct eap_sm *sm);
void eap_sm_request_password(struct eap_sm *sm);
void eap_sm_request_new_password(struct eap_sm *sm);

#endif /* EAP_H */

