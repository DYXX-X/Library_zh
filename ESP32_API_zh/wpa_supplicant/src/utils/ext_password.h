/*
 * 外部密码后端版权所有（c）2012，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef EXT_PASSWORD_H
#define EXT_PASSWORD_H

struct ext_password_data;

#ifdef CONFIG_EXT_PASSWORD

struct ext_password_data * ext_password_init(const char *backend,
					     const char *params);
void ext_password_deinit(struct ext_password_data *data);

struct wpabuf * ext_password_get(struct ext_password_data *data,
				 const char *name);
void ext_password_free(struct wpabuf *pw);

#else /* CONFIG_EXT_PASSWORD */

#define ext_password_init(b, p)
#define ext_password_deinit(d)
#define ext_password_get(d, n) NULL
#define ext_password_free(p)

#endif /* CONFIG_EXT_PASSWORD */

#endif /* EXT_PASSWORD_H */

