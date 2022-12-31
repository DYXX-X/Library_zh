/*
 * SHA-512内部定义版权所有（c）2015，Pali Rohár<pali.rohar@gmail.com>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef SHA512_I_H
#define SHA512_I_H

#define SHA512_BLOCK_SIZE 128

struct sha512_state {
	u64 length, state[8];
	u32 curlen;
	u8 buf[SHA512_BLOCK_SIZE];
};

void sha512_init(struct sha512_state *md);
int sha512_process(struct sha512_state *md, const unsigned char *in,
		   unsigned long inlen);
int sha512_done(struct sha512_state *md, unsigned char *out);

#endif /* SHA512_I_H */

