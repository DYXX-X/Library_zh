/*
   BLAKE2参考源代码包-优化的C实现

   塞缪尔·内维斯于2012年撰写<sneves@dei.uc.pt>

   在法律允许的范围内，作者已将本软件的所有版权和相关权利以及邻近权利授予全球公共领域。本软件的分发无任何担保。

   您应该已经收到了CC0公共域专用的副本以及此软件。如果没有，请参见<http://creativecommons.org/publicdomain/zero/1.0/>.
*/

#ifndef blake2b_load_sse41_H
#define blake2b_load_sse41_H

#define LOAD_MSG_0_1(b0, b1)             \
    do {                                 \
        b0 = _mm_unpacklo_epi64(m0, m1); \
        b1 = _mm_unpacklo_epi64(m2, m3); \
    } while (0)

#define LOAD_MSG_0_2(b0, b1)             \
    do {                                 \
        b0 = _mm_unpackhi_epi64(m0, m1); \
        b1 = _mm_unpackhi_epi64(m2, m3); \
    } while (0)

#define LOAD_MSG_0_3(b0, b1)             \
    do {                                 \
        b0 = _mm_unpacklo_epi64(m4, m5); \
        b1 = _mm_unpacklo_epi64(m6, m7); \
    } while (0)

#define LOAD_MSG_0_4(b0, b1)             \
    do {                                 \
        b0 = _mm_unpackhi_epi64(m4, m5); \
        b1 = _mm_unpackhi_epi64(m6, m7); \
    } while (0)

#define LOAD_MSG_1_1(b0, b1)             \
    do {                                 \
        b0 = _mm_unpacklo_epi64(m7, m2); \
        b1 = _mm_unpackhi_epi64(m4, m6); \
    } while (0)

#define LOAD_MSG_1_2(b0, b1)             \
    do {                                 \
        b0 = _mm_unpacklo_epi64(m5, m4); \
        b1 = _mm_alignr_epi8(m3, m7, 8); \
    } while (0)

#define LOAD_MSG_1_3(b0, b1)                                 \
    do {                                                     \
        b0 = _mm_shuffle_epi32(m0, _MM_SHUFFLE(1, 0, 3, 2)); \
        b1 = _mm_unpackhi_epi64(m5, m2);                     \
    } while (0)

#define LOAD_MSG_1_4(b0, b1)             \
    do {                                 \
        b0 = _mm_unpacklo_epi64(m6, m1); \
        b1 = _mm_unpackhi_epi64(m3, m1); \
    } while (0)

#define LOAD_MSG_2_1(b0, b1)             \
    do {                                 \
        b0 = _mm_alignr_epi8(m6, m5, 8); \
        b1 = _mm_unpackhi_epi64(m2, m7); \
    } while (0)

#define LOAD_MSG_2_2(b0, b1)                \
    do {                                    \
        b0 = _mm_unpacklo_epi64(m4, m0);    \
        b1 = _mm_blend_epi16(m1, m6, 0xF0); \
    } while (0)

#define LOAD_MSG_2_3(b0, b1)                \
    do {                                    \
        b0 = _mm_blend_epi16(m5, m1, 0xF0); \
        b1 = _mm_unpackhi_epi64(m3, m4);    \
    } while (0)

#define LOAD_MSG_2_4(b0, b1)             \
    do {                                 \
        b0 = _mm_unpacklo_epi64(m7, m3); \
        b1 = _mm_alignr_epi8(m2, m0, 8); \
    } while (0)

#define LOAD_MSG_3_1(b0, b1)             \
    do {                                 \
        b0 = _mm_unpackhi_epi64(m3, m1); \
        b1 = _mm_unpackhi_epi64(m6, m5); \
    } while (0)

#define LOAD_MSG_3_2(b0, b1)             \
    do {                                 \
        b0 = _mm_unpackhi_epi64(m4, m0); \
        b1 = _mm_unpacklo_epi64(m6, m7); \
    } while (0)

#define LOAD_MSG_3_3(b0, b1)                \
    do {                                    \
        b0 = _mm_blend_epi16(m1, m2, 0xF0); \
        b1 = _mm_blend_epi16(m2, m7, 0xF0); \
    } while (0)

#define LOAD_MSG_3_4(b0, b1)             \
    do {                                 \
        b0 = _mm_unpacklo_epi64(m3, m5); \
        b1 = _mm_unpacklo_epi64(m0, m4); \
    } while (0)

#define LOAD_MSG_4_1(b0, b1)             \
    do {                                 \
        b0 = _mm_unpackhi_epi64(m4, m2); \
        b1 = _mm_unpacklo_epi64(m1, m5); \
    } while (0)

#define LOAD_MSG_4_2(b0, b1)                \
    do {                                    \
        b0 = _mm_blend_epi16(m0, m3, 0xF0); \
        b1 = _mm_blend_epi16(m2, m7, 0xF0); \
    } while (0)

#define LOAD_MSG_4_3(b0, b1)                \
    do {                                    \
        b0 = _mm_blend_epi16(m7, m5, 0xF0); \
        b1 = _mm_blend_epi16(m3, m1, 0xF0); \
    } while (0)

#define LOAD_MSG_4_4(b0, b1)                \
    do {                                    \
        b0 = _mm_alignr_epi8(m6, m0, 8);    \
        b1 = _mm_blend_epi16(m4, m6, 0xF0); \
    } while (0)

#define LOAD_MSG_5_1(b0, b1)             \
    do {                                 \
        b0 = _mm_unpacklo_epi64(m1, m3); \
        b1 = _mm_unpacklo_epi64(m0, m4); \
    } while (0)

#define LOAD_MSG_5_2(b0, b1)             \
    do {                                 \
        b0 = _mm_unpacklo_epi64(m6, m5); \
        b1 = _mm_unpackhi_epi64(m5, m1); \
    } while (0)

#define LOAD_MSG_5_3(b0, b1)                \
    do {                                    \
        b0 = _mm_blend_epi16(m2, m3, 0xF0); \
        b1 = _mm_unpackhi_epi64(m7, m0);    \
    } while (0)

#define LOAD_MSG_5_4(b0, b1)                \
    do {                                    \
        b0 = _mm_unpackhi_epi64(m6, m2);    \
        b1 = _mm_blend_epi16(m7, m4, 0xF0); \
    } while (0)

#define LOAD_MSG_6_1(b0, b1)                \
    do {                                    \
        b0 = _mm_blend_epi16(m6, m0, 0xF0); \
        b1 = _mm_unpacklo_epi64(m7, m2);    \
    } while (0)

#define LOAD_MSG_6_2(b0, b1)             \
    do {                                 \
        b0 = _mm_unpackhi_epi64(m2, m7); \
        b1 = _mm_alignr_epi8(m5, m6, 8); \
    } while (0)

#define LOAD_MSG_6_3(b0, b1)                                 \
    do {                                                     \
        b0 = _mm_unpacklo_epi64(m0, m3);                     \
        b1 = _mm_shuffle_epi32(m4, _MM_SHUFFLE(1, 0, 3, 2)); \
    } while (0)

#define LOAD_MSG_6_4(b0, b1)                \
    do {                                    \
        b0 = _mm_unpackhi_epi64(m3, m1);    \
        b1 = _mm_blend_epi16(m1, m5, 0xF0); \
    } while (0)

#define LOAD_MSG_7_1(b0, b1)                \
    do {                                    \
        b0 = _mm_unpackhi_epi64(m6, m3);    \
        b1 = _mm_blend_epi16(m6, m1, 0xF0); \
    } while (0)

#define LOAD_MSG_7_2(b0, b1)             \
    do {                                 \
        b0 = _mm_alignr_epi8(m7, m5, 8); \
        b1 = _mm_unpackhi_epi64(m0, m4); \
    } while (0)

#define LOAD_MSG_7_3(b0, b1)             \
    do {                                 \
        b0 = _mm_unpackhi_epi64(m2, m7); \
        b1 = _mm_unpacklo_epi64(m4, m1); \
    } while (0)

#define LOAD_MSG_7_4(b0, b1)             \
    do {                                 \
        b0 = _mm_unpacklo_epi64(m0, m2); \
        b1 = _mm_unpacklo_epi64(m3, m5); \
    } while (0)

#define LOAD_MSG_8_1(b0, b1)             \
    do {                                 \
        b0 = _mm_unpacklo_epi64(m3, m7); \
        b1 = _mm_alignr_epi8(m0, m5, 8); \
    } while (0)

#define LOAD_MSG_8_2(b0, b1)             \
    do {                                 \
        b0 = _mm_unpackhi_epi64(m7, m4); \
        b1 = _mm_alignr_epi8(m4, m1, 8); \
    } while (0)

#define LOAD_MSG_8_3(b0, b1)             \
    do {                                 \
        b0 = m6;                         \
        b1 = _mm_alignr_epi8(m5, m0, 8); \
    } while (0)

#define LOAD_MSG_8_4(b0, b1)                \
    do {                                    \
        b0 = _mm_blend_epi16(m1, m3, 0xF0); \
        b1 = m2;                            \
    } while (0)

#define LOAD_MSG_9_1(b0, b1)             \
    do {                                 \
        b0 = _mm_unpacklo_epi64(m5, m4); \
        b1 = _mm_unpackhi_epi64(m3, m0); \
    } while (0)

#define LOAD_MSG_9_2(b0, b1)                \
    do {                                    \
        b0 = _mm_unpacklo_epi64(m1, m2);    \
        b1 = _mm_blend_epi16(m3, m2, 0xF0); \
    } while (0)

#define LOAD_MSG_9_3(b0, b1)             \
    do {                                 \
        b0 = _mm_unpackhi_epi64(m7, m4); \
        b1 = _mm_unpackhi_epi64(m1, m6); \
    } while (0)

#define LOAD_MSG_9_4(b0, b1)             \
    do {                                 \
        b0 = _mm_alignr_epi8(m7, m5, 8); \
        b1 = _mm_unpacklo_epi64(m6, m0); \
    } while (0)

#define LOAD_MSG_10_1(b0, b1)            \
    do {                                 \
        b0 = _mm_unpacklo_epi64(m0, m1); \
        b1 = _mm_unpacklo_epi64(m2, m3); \
    } while (0)

#define LOAD_MSG_10_2(b0, b1)            \
    do {                                 \
        b0 = _mm_unpackhi_epi64(m0, m1); \
        b1 = _mm_unpackhi_epi64(m2, m3); \
    } while (0)

#define LOAD_MSG_10_3(b0, b1)            \
    do {                                 \
        b0 = _mm_unpacklo_epi64(m4, m5); \
        b1 = _mm_unpacklo_epi64(m6, m7); \
    } while (0)

#define LOAD_MSG_10_4(b0, b1)            \
    do {                                 \
        b0 = _mm_unpackhi_epi64(m4, m5); \
        b1 = _mm_unpackhi_epi64(m6, m7); \
    } while (0)

#define LOAD_MSG_11_1(b0, b1)            \
    do {                                 \
        b0 = _mm_unpacklo_epi64(m7, m2); \
        b1 = _mm_unpackhi_epi64(m4, m6); \
    } while (0)

#define LOAD_MSG_11_2(b0, b1)            \
    do {                                 \
        b0 = _mm_unpacklo_epi64(m5, m4); \
        b1 = _mm_alignr_epi8(m3, m7, 8); \
    } while (0)

#define LOAD_MSG_11_3(b0, b1)                                \
    do {                                                     \
        b0 = _mm_shuffle_epi32(m0, _MM_SHUFFLE(1, 0, 3, 2)); \
        b1 = _mm_unpackhi_epi64(m5, m2);                     \
    } while (0)

#define LOAD_MSG_11_4(b0, b1)            \
    do {                                 \
        b0 = _mm_unpacklo_epi64(m6, m1); \
        b1 = _mm_unpackhi_epi64(m3, m1); \
    } while (0)

#endif

