/*
 * SHA-384内部定义版权所有（c）2015，Pali Rohár<pali.rohar@gmail.com>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef SHA384_I_H
#define SHA384_I_H

#include "sha512_i.h"

#define SHA384_BLOCK_SIZE SHA512_BLOCK_SIZE

#define sha384_state sha512_state

void sha384_init(struct sha384_state *md);
int sha384_process(struct sha384_state *md, const unsigned char *in,
		   unsigned long inlen);
int sha384_done(struct sha384_state *md, unsigned char *out);

#endif /* SHA384_I_H */

