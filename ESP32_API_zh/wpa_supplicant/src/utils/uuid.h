/*
 * 通用唯一标识符（UUID）版权所有（c）2008，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef UUID_H
#define UUID_H

#define UUID_LEN 16

int uuid_str2bin(const char *str, u8 *bin);
int uuid_bin2str(const u8 *bin, char *str, size_t max_len);
int is_nil_uuid(const u8 *uuid);

#endif /* UUID_H */

