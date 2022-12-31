/*
 * MD5内部定义版权所有（c）2003-2005，Jouni Malinen<j@w1.fi>
 *
 * 该程序是免费软件；您可以根据自由软件基金会发布的GNU通用公共许可证第2版的条款重新分发和/或修改它。
 *
 * 或者，此软件可以根据BSD许可证条款进行分发。
 *
 * 有关详细信息，请参阅自述和复制。
 */

#ifndef _ROM_MD5_HASH_H_
#define _ROM_MD5_HASH_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct MD5Context {
    uint32_t buf[4];
    uint32_t bits[2];
    uint8_t in[64];
};

void MD5Init(struct MD5Context *context);
void MD5Update(struct MD5Context *context, unsigned char const *buf, unsigned len);
void MD5Final(unsigned char digest[16], struct MD5Context *context);

#ifdef __cplusplus
}
#endif

#endif /* _ROM_MD5_HASH_H_ */

