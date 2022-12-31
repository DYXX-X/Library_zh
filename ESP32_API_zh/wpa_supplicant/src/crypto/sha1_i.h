/*
 * SHA1内部定义版权所有（c）2003-2005，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef SHA1_I_H
#define SHA1_I_H

struct SHA1Context {
	u32 state[5];
	u32 count[2];
	unsigned char buffer[64];
};

void SHA1Init(struct SHA1Context *context);
void SHA1Update(struct SHA1Context *context, const void *data, u32 len);
void SHA1Final(unsigned char digest[20], struct SHA1Context *context);
void SHA1Transform(u32 state[5], const unsigned char buffer[64]);

#endif /* SHA1_I_H */

