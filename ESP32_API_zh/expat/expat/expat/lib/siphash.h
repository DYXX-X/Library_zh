/* ==========================================================================
 * 西帕什。h-SipHash-2-4在单个头文件中
 * --------------------------------------------------------------------------William Ahern从Jean-Philippe Aumasson和Daniel J.Berstein发表的参考实现[1]中导出。塞巴斯蒂安·皮平（Sebastian Pipping）和维克多·斯蒂纳（Victor Stinner）在顶部所作的最小改动，见下文。根据CC0公共域专用许可证许可。
 *
 * 1.https://www.131002.net/siphash/siphash24.c2.https://www.131002.net/siphash/
 * -------------------------------------------------------------------------- HISTORY:
 *
 * 2020-10-03（塞巴斯蒂安·皮平）
 *   -放弃对Visual Studio 9.0/2008和更早版本的支持
 *
 * 2019-08-03（塞巴斯蒂安·皮平）
 *   -将sip24_valid的一部分标记为从clang格式中排除
 *   -使用clang格式9重新格式化代码
 *
 * 2018-07-08（Anton Maklakov）
 *   -为GCC添加“失败”标记-Wimplicit失败
 *
 * 2017-11-03（塞巴斯蒂安·皮平）
 *   -除非定义了SIPHASH_tobin宏，否则隐藏sip_tobin和sip_binof
 *
 * 2017-07-25（Vadim Zeitlin）
 *   -修复SIPHASH_MAIN宏的使用
 *
 * 2017-07-05（塞巴斯蒂安·皮平）
 *   -如果编译为C，则使用_SIP_ULL宏不需要C++11编译器++
 *   -在两个位置添加常量限定符
 *   -确保<=80个字符的行长度（假设制表符宽度为4）
 *
 * 2017-06-23（Victor Stinner）
 *   -解决Win64编译警告
 *
 * 2017-06-18（塞巴斯蒂安·皮平）
 *   -澄清标题中的许可说明
 *   -解决C89问题：
 *     -停止使用内联关键字（让编译器决定）
 *     -用int替换_Bool
 *     -将宏sihash24转换为函数
 *     -通过显式转换解决无效转换（空指针）
 *   -地址缺少stdint。h for Visual Studio 2003至2008
 *   -始终暴露sip24_valid（用于自检）
 *
 * 2012-11-04-出生。（威廉·埃亨）
 * -------------------------------------------------------------------------- USAGE:
 *
 * SipHash-2-4将两个64位字作为关键字，一些消息字节作为输入，并输出一个64位的字作为消息摘要。此实现使用两种数据结构：用于表示密钥的结构sipkey和用于表示哈希状态的结构sihash。
 *
 * 要将16字节无符号字符数组转换为键，请使用宏sip_keyof或例程sip_tokey。前者实例化一个复合文本键，而后者需要一个键对象作为参数。
 *
 * 无符号字符机密[16]；arc4random_buf（secret，sizeof secret）；结构sipkey key=sip_keyof（secret）；
 *
 * 对于散列消息，可以使用便利宏siphhash24或例程sip24_init、sip24_update和sip24_final。
 *
 * 结构sihash状态；无效消息；size_t长度；uint64_t哈希；
 *
 * sip24_init（&state，key）；sip24_update（&state，msg，len）；hash=sip24_final（&state）；
 *
 * 或
 *
 * hash=siphash24（消息、长度、密钥）；
 *
 * 要将64位哈希值转换为规范的8字节小端二进制表示，请使用宏sip_binof或例程sip_tobin。前者实例化并返回复合文本数组，而后者需要数组对象作为参数。
 * -------------------------------------------------------------------------- NOTES:
 *
 * o sip_keyof、sip_binof和sihash24都不能与缺少复合文本支持的编译器一起使用。相反，您必须使用较低级别的接口，这些接口将临时状态对象作为参数。
 *
 * o大写宏可以多次评估参数。小写宏不应显示任何此类副作用==========================================================================
 */
#ifndef SIPHASH_H
#define SIPHASH_H

#include <stddef.h> /* 大小（_t）*/
#include <stdint.h> /* uint64_t uint32_t uit8_t*/

/*
 * 如果包含此代码并将其编译为C++，则不需要C++11编译器来使用ULL后缀；相关的GCC警告是：警告：使用C++11长整型常量[-Wlong-long]
 */
#define _SIP_ULL(high, low) (((uint64_t)high << 32) | low)

#define SIP_ROTL(x, b) (uint64_t)(((x) << (b)) | ((x) >> (64 - (b))))

#define SIP_U32TO8_LE(p, v)                                                    \
  (p)[0] = (uint8_t)((v) >> 0);                                                \
  (p)[1] = (uint8_t)((v) >> 8);                                                \
  (p)[2] = (uint8_t)((v) >> 16);                                               \
  (p)[3] = (uint8_t)((v) >> 24);

#define SIP_U64TO8_LE(p, v)                                                    \
  SIP_U32TO8_LE((p) + 0, (uint32_t)((v) >> 0));                                \
  SIP_U32TO8_LE((p) + 4, (uint32_t)((v) >> 32));

#define SIP_U8TO64_LE(p)                                                       \
  (((uint64_t)((p)[0]) << 0) | ((uint64_t)((p)[1]) << 8)                       \
   | ((uint64_t)((p)[2]) << 16) | ((uint64_t)((p)[3]) << 24)                   \
   | ((uint64_t)((p)[4]) << 32) | ((uint64_t)((p)[5]) << 40)                   \
   | ((uint64_t)((p)[6]) << 48) | ((uint64_t)((p)[7]) << 56))

#define SIPHASH_INITIALIZER                                                    \
  { 0, 0, 0, 0, {0}, 0, 0 }

struct siphash {
  uint64_t v0, v1, v2, v3;

  unsigned char buf[8], *p;
  uint64_t c;
}; /* 结构sihash*/

#define SIP_KEYLEN 16

struct sipkey {
  uint64_t k[2];
}; /* 结构sipkey*/

#define sip_keyof(k) sip_tokey(&(struct sipkey){{0}}, (k))

static struct sipkey *
sip_tokey(struct sipkey *key, const void *src) {
  key->k[0] = SIP_U8TO64_LE((const unsigned char *)src);
  key->k[1] = SIP_U8TO64_LE((const unsigned char *)src + 8);
  return key;
} /* sip_tokey（）*/

#ifdef SIPHASH_TOBIN

#  define sip_binof(v) sip_tobin((unsigned char[8]){0}, (v))

static void *
sip_tobin(void *dst, uint64_t u64) {
  SIP_U64TO8_LE((unsigned char *)dst, u64);
  return dst;
} /* sip_tobin（）*/

#endif /* SIPHASH_TOBIN */

static void
sip_round(struct siphash *H, const int rounds) {
  int i;

  for (i = 0; i < rounds; i++) {
    H->v0 += H->v1;
    H->v1 = SIP_ROTL(H->v1, 13);
    H->v1 ^= H->v0;
    H->v0 = SIP_ROTL(H->v0, 32);

    H->v2 += H->v3;
    H->v3 = SIP_ROTL(H->v3, 16);
    H->v3 ^= H->v2;

    H->v0 += H->v3;
    H->v3 = SIP_ROTL(H->v3, 21);
    H->v3 ^= H->v0;

    H->v2 += H->v1;
    H->v1 = SIP_ROTL(H->v1, 17);
    H->v1 ^= H->v2;
    H->v2 = SIP_ROTL(H->v2, 32);
  }
} /* sip_round（）*/

static struct siphash *
sip24_init(struct siphash *H, const struct sipkey *key) {
  H->v0 = _SIP_ULL(0x736f6d65U, 0x70736575U) ^ key->k[0];
  H->v1 = _SIP_ULL(0x646f7261U, 0x6e646f6dU) ^ key->k[1];
  H->v2 = _SIP_ULL(0x6c796765U, 0x6e657261U) ^ key->k[0];
  H->v3 = _SIP_ULL(0x74656462U, 0x79746573U) ^ key->k[1];

  H->p = H->buf;
  H->c = 0;

  return H;
} /* sip24_init（）*/

#define sip_endof(a) (&(a)[sizeof(a) / sizeof *(a)])

static struct siphash *
sip24_update(struct siphash *H, const void *src, size_t len) {
  const unsigned char *p = (const unsigned char *)src, *pe = p + len;
  uint64_t m;

  do {
    while (p < pe && H->p < sip_endof(H->buf))
      *H->p++ = *p++;

    if (H->p < sip_endof(H->buf))
      break;

    m = SIP_U8TO64_LE(H->buf);
    H->v3 ^= m;
    sip_round(H, 2);
    H->v0 ^= m;

    H->p = H->buf;
    H->c += 8;
  } while (p < pe);

  return H;
} /* sip24_update（）*/

static uint64_t
sip24_final(struct siphash *H) {
  const char left = (char)(H->p - H->buf);
  uint64_t b = (H->c + left) << 56;

  switch (left) {
  case 7:
    b |= (uint64_t)H->buf[6] << 48;
    /* 落空*/
  case 6:
    b |= (uint64_t)H->buf[5] << 40;
    /* 落空*/
  case 5:
    b |= (uint64_t)H->buf[4] << 32;
    /* 落空*/
  case 4:
    b |= (uint64_t)H->buf[3] << 24;
    /* 落空*/
  case 3:
    b |= (uint64_t)H->buf[2] << 16;
    /* 落空*/
  case 2:
    b |= (uint64_t)H->buf[1] << 8;
    /* 落空*/
  case 1:
    b |= (uint64_t)H->buf[0] << 0;
    /* 落空*/
  case 0:
    break;
  }

  H->v3 ^= b;
  sip_round(H, 2);
  H->v0 ^= b;
  H->v2 ^= 0xff;
  sip_round(H, 4);

  return H->v0 ^ H->v1 ^ H->v2 ^ H->v3;
} /* 刀槽花纹24_最终（）*/

static uint64_t
siphash24(const void *src, size_t len, const struct sipkey *key) {
  struct siphash state = SIPHASH_INITIALIZER;
  return sip24_final(sip24_update(sip24_init(&state, key), src, len));
} /* siphash24（）*/

/*
 * SipHash-2-4输出，k=00 01 02…，in=（空字符串）in=00（1字节）in=0 01（2字节）in＝00 01 02（3字节）…in=00 01 01…3e（63字节）
 */
static int
sip24_valid(void) {
  /* clang格式关闭*/
  static const unsigned char vectors[64][8] = {
    { 0x31, 0x0e, 0x0e, 0xdd, 0x47, 0xdb, 0x6f, 0x72, },
    { 0xfd, 0x67, 0xdc, 0x93, 0xc5, 0x39, 0xf8, 0x74, },
    { 0x5a, 0x4f, 0xa9, 0xd9, 0x09, 0x80, 0x6c, 0x0d, },
    { 0x2d, 0x7e, 0xfb, 0xd7, 0x96, 0x66, 0x67, 0x85, },
    { 0xb7, 0x87, 0x71, 0x27, 0xe0, 0x94, 0x27, 0xcf, },
    { 0x8d, 0xa6, 0x99, 0xcd, 0x64, 0x55, 0x76, 0x18, },
    { 0xce, 0xe3, 0xfe, 0x58, 0x6e, 0x46, 0xc9, 0xcb, },
    { 0x37, 0xd1, 0x01, 0x8b, 0xf5, 0x00, 0x02, 0xab, },
    { 0x62, 0x24, 0x93, 0x9a, 0x79, 0xf5, 0xf5, 0x93, },
    { 0xb0, 0xe4, 0xa9, 0x0b, 0xdf, 0x82, 0x00, 0x9e, },
    { 0xf3, 0xb9, 0xdd, 0x94, 0xc5, 0xbb, 0x5d, 0x7a, },
    { 0xa7, 0xad, 0x6b, 0x22, 0x46, 0x2f, 0xb3, 0xf4, },
    { 0xfb, 0xe5, 0x0e, 0x86, 0xbc, 0x8f, 0x1e, 0x75, },
    { 0x90, 0x3d, 0x84, 0xc0, 0x27, 0x56, 0xea, 0x14, },
    { 0xee, 0xf2, 0x7a, 0x8e, 0x90, 0xca, 0x23, 0xf7, },
    { 0xe5, 0x45, 0xbe, 0x49, 0x61, 0xca, 0x29, 0xa1, },
    { 0xdb, 0x9b, 0xc2, 0x57, 0x7f, 0xcc, 0x2a, 0x3f, },
    { 0x94, 0x47, 0xbe, 0x2c, 0xf5, 0xe9, 0x9a, 0x69, },
    { 0x9c, 0xd3, 0x8d, 0x96, 0xf0, 0xb3, 0xc1, 0x4b, },
    { 0xbd, 0x61, 0x79, 0xa7, 0x1d, 0xc9, 0x6d, 0xbb, },
    { 0x98, 0xee, 0xa2, 0x1a, 0xf2, 0x5c, 0xd6, 0xbe, },
    { 0xc7, 0x67, 0x3b, 0x2e, 0xb0, 0xcb, 0xf2, 0xd0, },
    { 0x88, 0x3e, 0xa3, 0xe3, 0x95, 0x67, 0x53, 0x93, },
    { 0xc8, 0xce, 0x5c, 0xcd, 0x8c, 0x03, 0x0c, 0xa8, },
    { 0x94, 0xaf, 0x49, 0xf6, 0xc6, 0x50, 0xad, 0xb8, },
    { 0xea, 0xb8, 0x85, 0x8a, 0xde, 0x92, 0xe1, 0xbc, },
    { 0xf3, 0x15, 0xbb, 0x5b, 0xb8, 0x35, 0xd8, 0x17, },
    { 0xad, 0xcf, 0x6b, 0x07, 0x63, 0x61, 0x2e, 0x2f, },
    { 0xa5, 0xc9, 0x1d, 0xa7, 0xac, 0xaa, 0x4d, 0xde, },
    { 0x71, 0x65, 0x95, 0x87, 0x66, 0x50, 0xa2, 0xa6, },
    { 0x28, 0xef, 0x49, 0x5c, 0x53, 0xa3, 0x87, 0xad, },
    { 0x42, 0xc3, 0x41, 0xd8, 0xfa, 0x92, 0xd8, 0x32, },
    { 0xce, 0x7c, 0xf2, 0x72, 0x2f, 0x51, 0x27, 0x71, },
    { 0xe3, 0x78, 0x59, 0xf9, 0x46, 0x23, 0xf3, 0xa7, },
    { 0x38, 0x12, 0x05, 0xbb, 0x1a, 0xb0, 0xe0, 0x12, },
    { 0xae, 0x97, 0xa1, 0x0f, 0xd4, 0x34, 0xe0, 0x15, },
    { 0xb4, 0xa3, 0x15, 0x08, 0xbe, 0xff, 0x4d, 0x31, },
    { 0x81, 0x39, 0x62, 0x29, 0xf0, 0x90, 0x79, 0x02, },
    { 0x4d, 0x0c, 0xf4, 0x9e, 0xe5, 0xd4, 0xdc, 0xca, },
    { 0x5c, 0x73, 0x33, 0x6a, 0x76, 0xd8, 0xbf, 0x9a, },
    { 0xd0, 0xa7, 0x04, 0x53, 0x6b, 0xa9, 0x3e, 0x0e, },
    { 0x92, 0x59, 0x58, 0xfc, 0xd6, 0x42, 0x0c, 0xad, },
    { 0xa9, 0x15, 0xc2, 0x9b, 0xc8, 0x06, 0x73, 0x18, },
    { 0x95, 0x2b, 0x79, 0xf3, 0xbc, 0x0a, 0xa6, 0xd4, },
    { 0xf2, 0x1d, 0xf2, 0xe4, 0x1d, 0x45, 0x35, 0xf9, },
    { 0x87, 0x57, 0x75, 0x19, 0x04, 0x8f, 0x53, 0xa9, },
    { 0x10, 0xa5, 0x6c, 0xf5, 0xdf, 0xcd, 0x9a, 0xdb, },
    { 0xeb, 0x75, 0x09, 0x5c, 0xcd, 0x98, 0x6c, 0xd0, },
    { 0x51, 0xa9, 0xcb, 0x9e, 0xcb, 0xa3, 0x12, 0xe6, },
    { 0x96, 0xaf, 0xad, 0xfc, 0x2c, 0xe6, 0x66, 0xc7, },
    { 0x72, 0xfe, 0x52, 0x97, 0x5a, 0x43, 0x64, 0xee, },
    { 0x5a, 0x16, 0x45, 0xb2, 0x76, 0xd5, 0x92, 0xa1, },
    { 0xb2, 0x74, 0xcb, 0x8e, 0xbf, 0x87, 0x87, 0x0a, },
    { 0x6f, 0x9b, 0xb4, 0x20, 0x3d, 0xe7, 0xb3, 0x81, },
    { 0xea, 0xec, 0xb2, 0xa3, 0x0b, 0x22, 0xa8, 0x7f, },
    { 0x99, 0x24, 0xa4, 0x3c, 0xc1, 0x31, 0x57, 0x24, },
    { 0xbd, 0x83, 0x8d, 0x3a, 0xaf, 0xbf, 0x8d, 0xb7, },
    { 0x0b, 0x1a, 0x2a, 0x32, 0x65, 0xd5, 0x1a, 0xea, },
    { 0x13, 0x50, 0x79, 0xa3, 0x23, 0x1c, 0xe6, 0x60, },
    { 0x93, 0x2b, 0x28, 0x46, 0xe4, 0xd7, 0x06, 0x66, },
    { 0xe1, 0x91, 0x5f, 0x5c, 0xb1, 0xec, 0xa4, 0x6c, },
    { 0xf3, 0x25, 0x96, 0x5c, 0xa1, 0x6d, 0x62, 0x9f, },
    { 0x57, 0x5f, 0xf2, 0x8e, 0x60, 0x38, 0x1b, 0xe5, },
    { 0x72, 0x45, 0x06, 0xeb, 0x4c, 0x32, 0x8a, 0x95, }
  };
  /* clang格式打开*/

  unsigned char in[64];
  struct sipkey k;
  size_t i;

  sip_tokey(&k, "\000\001\002\003\004\005\006\007\010\011"
                "\012\013\014\015\016\017");

  for (i = 0; i < sizeof in; ++i) {
    in[i] = (unsigned char)i;

    if (siphash24(in, i, &k) != SIP_U8TO64_LE(vectors[i]))
      return 0;
  }

  return 1;
} /* sip24_valid（）*/

#ifdef SIPHASH_MAIN

#  include <stdio.h>

int
main(void) {
  const int ok = sip24_valid();

  if (ok)
    puts("OK");
  else
    puts("FAIL");

  return ! ok;
} /* main（）*/

#endif /* SIPHASH_MAIN */

#endif /* SIPHASH_H */

