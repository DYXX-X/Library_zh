/*
 * Base64编码/解码（RFC1341）版权所有（c）2005，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef BASE64_H
#define BASE64_H

char * base64_encode(const void *src, size_t len, size_t *out_len);
unsigned char * base64_decode(const char *src, size_t len, size_t *out_len);
char * base64_url_encode(const void *src, size_t len, size_t *out_len);
unsigned char * base64_url_decode(const char *src, size_t len, size_t *out_len);

#endif /* BASE64_H */

