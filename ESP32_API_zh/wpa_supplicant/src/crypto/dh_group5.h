/*
 * Diffie Hellman group 5运营版权所有（c）2009，2012，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef DH_GROUP5_H
#define DH_GROUP5_H

void * dh5_init(struct wpabuf **priv, struct wpabuf **publ);
void * dh5_init_fixed(const struct wpabuf *priv, const struct wpabuf *publ);
struct wpabuf * dh5_derive_shared(void *ctx, const struct wpabuf *peer_public,
				  const struct wpabuf *own_private);
void dh5_free(void *ctx);

#endif /* DH_GROUP5_H */

