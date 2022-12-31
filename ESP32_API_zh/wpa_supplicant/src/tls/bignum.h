/*
 * 大数数学版权所有（c）2006，Jouni Malinen<j@w1.fi>
 *
 * 该程序是免费软件；您可以根据自由软件基金会发布的GNU通用公共许可证第2版的条款重新分发和/或修改它。
 *
 * 或者，此软件可以根据BSD许可证条款进行分发。
 *
 * 有关详细信息，请参阅自述和复制。
 */

#ifndef BIGNUM_H
#define BIGNUM_H

struct bignum;

struct bignum * bignum_init(void);
void bignum_deinit(struct bignum *n);
size_t bignum_get_unsigned_bin_len(struct bignum *n);
int bignum_get_unsigned_bin(const struct bignum *n, u8 *buf, size_t *len);
int bignum_set_unsigned_bin(struct bignum *n, const u8 *buf, size_t len);
int bignum_cmp(const struct bignum *a, const struct bignum *b);
int bignum_cmp_d(const struct bignum *a, unsigned long b);
int bignum_add(const struct bignum *a, const struct bignum *b,
	       struct bignum *c);
int bignum_sub(const struct bignum *a, const struct bignum *b,
	       struct bignum *c);
int bignum_mul(const struct bignum *a, const struct bignum *b,
	       struct bignum *c);
int bignum_mulmod(const struct bignum *a, const struct bignum *b,
		  const struct bignum *c, struct bignum *d);
int bignum_exptmod(const struct bignum *a, const struct bignum *b,
		   const struct bignum *c, struct bignum *d);

#endif /* BIGNUM_H */

