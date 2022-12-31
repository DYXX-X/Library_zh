/*
   该文件改编自ref10/fe。h： 删除所有冗余功能。
*/

#ifndef fe_H
#define fe_H

#include <stdint.h>
#include <stdlib.h>

typedef uint64_t fe[10];

/*
fe表示场元素。此处字段为\Z/（2^255-19）。元素t，条目t[0]…t[9]，表示整数t[0]+2^26 t[1]+2^51 t[2]+2^77 t[3]+2^102 t[4]+…+2^230 t[9]。每个t[i]上的边界因上下文而异。
*/

#define fe_frombytes crypto_scalarmult_curve25519_sandy2x_fe_frombytes

extern void fe_frombytes(fe, const unsigned char *);

#endif

