/*
 * EAP对等方法：EAP-FAST PAC文件处理版权所有（c）2004-2007，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef EAP_FAST_PAC_H
#define EAP_FAST_PAC_H

#include "eap_peer/eap_fast_common.h"

struct eap_fast_pac {
	struct eap_fast_pac *next;

	u8 pac_key[EAP_FAST_PAC_KEY_LEN];
	u8 *pac_opaque;
	size_t pac_opaque_len;
	u8 *pac_info;
	size_t pac_info_len;
	u8 *a_id;
	size_t a_id_len;
	u8 *i_id;
	size_t i_id_len;
	u8 *a_id_info;
	size_t a_id_info_len;
	u16 pac_type;
};


void eap_fast_free_pac(struct eap_fast_pac *pac);
struct eap_fast_pac * eap_fast_get_pac(struct eap_fast_pac *pac_root,
				       const u8 *a_id, size_t a_id_len,
				       u16 pac_type);
int eap_fast_add_pac(struct eap_fast_pac **pac_root,
		     struct eap_fast_pac **pac_current,
		     struct eap_fast_pac *entry);
int eap_fast_load_pac(struct eap_sm *sm, struct eap_fast_pac **pac_root,
		      const char *pac_file);
int eap_fast_save_pac(struct eap_sm *sm, struct eap_fast_pac *pac_root,
		      const char *pac_file);
size_t eap_fast_pac_list_truncate(struct eap_fast_pac *pac_root,
				  size_t max_len);
int eap_fast_load_pac_bin(struct eap_sm *sm, struct eap_fast_pac **pac_root,
			  const char *pac_file);
int eap_fast_save_pac_bin(struct eap_sm *sm, struct eap_fast_pac *pac_root,
			  const char *pac_file);

#endif /* EAP_FAST_PAC_H */

