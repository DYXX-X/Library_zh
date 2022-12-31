#ifndef argon2_encoding_H
#define argon2_encoding_H

#include "argon2.h"

/*
 * 将Argon2哈希字符串编码到提供的缓冲区中。'“dst_len”包含“dst”缓冲区的大小（以字符为单位）；如果“dstlen”小于所需的字符数（包括终止的0），则此函数返回0。
 *
 * 如果ctx->outren为0，则哈希字符串将是salt字符串（无输出）。如果ctx->saltlen也为0，那么该字符串将是一个仅参数的字符串（没有salt和输出）。
 *
 * 成功后，返回ARGON2_OK。
 *
 * 未检查其他参数
 */
int encode_string(char *dst, size_t dst_len, argon2_context *ctx,
                  argon2_type type);

/*
 * 将Argon2哈希字符串解码为提供的结构“ctx”。字段ctx.saltlen、ctx.adlen、ctx.outlen设置允许的最大salt、ad、out长度值；无效的输入字符串导致错误
 *
 * 成功时返回的值为ARGON2_OK。
 */
int decode_string(argon2_context *ctx, const char *str, argon2_type type);

#endif

