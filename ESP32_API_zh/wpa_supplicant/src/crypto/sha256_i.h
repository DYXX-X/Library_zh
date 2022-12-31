/*
 * SHA-256内部定义版权所有（c）2003-2011，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef SHA256_I_H
#define SHA256_I_H

#define SHA256_BLOCK_SIZE 64

struct sha256_state {
	u64 length;
	u32 state[8], curlen;
	u8 buf[SHA256_BLOCK_SIZE];
};

void sha256_init(struct sha256_state *md);
int sha256_process(struct sha256_state *md, const unsigned char *in,
		   unsigned long inlen);
int sha256_done(struct sha256_state *md, unsigned char *out);

#endif /* SHA256_I_H */

