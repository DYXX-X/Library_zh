/*
 * TLS v1.0/v.1/v1.2服务器（RFC 2246、RFC 4346、RFC 5246）版权所有（c）2006-2011，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef TLSV1_SERVER_H
#define TLSV1_SERVER_H

#include "tlsv1_cred.h"

struct tlsv1_server;

int tlsv1_server_global_init(void);
void tlsv1_server_global_deinit(void);
struct tlsv1_server * tlsv1_server_init(struct tlsv1_credentials *cred);
void tlsv1_server_deinit(struct tlsv1_server *conn);
int tlsv1_server_established(struct tlsv1_server *conn);
int tlsv1_server_prf(struct tlsv1_server *conn, const char *label,
		     int server_random_first, u8 *out, size_t out_len);
u8 * tlsv1_server_handshake(struct tlsv1_server *conn,
			    const u8 *in_data, size_t in_len, size_t *out_len);
int tlsv1_server_encrypt(struct tlsv1_server *conn,
			 const u8 *in_data, size_t in_len,
			 u8 *out_data, size_t out_len);
int tlsv1_server_decrypt(struct tlsv1_server *conn,
			 const u8 *in_data, size_t in_len,
			 u8 *out_data, size_t out_len);
int tlsv1_server_get_cipher(struct tlsv1_server *conn, char *buf,
			    size_t buflen);
int tlsv1_server_shutdown(struct tlsv1_server *conn);
int tlsv1_server_resumed(struct tlsv1_server *conn);
int tlsv1_server_get_random(struct tlsv1_server *conn, struct tls_random *data);
int tlsv1_server_get_keyblock_size(struct tlsv1_server *conn);
int tlsv1_server_set_cipher_list(struct tlsv1_server *conn, u8 *ciphers);
int tlsv1_server_set_verify(struct tlsv1_server *conn, int verify_peer);

typedef int (*tlsv1_server_session_ticket_cb)
(void *ctx, const u8 *ticket, size_t len, const u8 *client_random,
 const u8 *server_random, u8 *master_secret);

void tlsv1_server_set_session_ticket_cb(struct tlsv1_server *conn,
					tlsv1_server_session_ticket_cb cb,
					void *ctx);

#endif /* TLSV1_SERVER_H */

