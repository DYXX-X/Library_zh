/*
 * Bitfield版权所有（c）2013，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef BITFIELD_H
#define BITFIELD_H

struct bitfield;

struct bitfield * bitfield_alloc(size_t max_bits);
void bitfield_free(struct bitfield *bf);
void bitfield_set(struct bitfield *bf, size_t bit);
void bitfield_clear(struct bitfield *bf, size_t bit);
int bitfield_is_set(struct bitfield *bf, size_t bit);
int bitfield_get_first_zero(struct bitfield *bf);

#endif /* BITFIELD_H */

