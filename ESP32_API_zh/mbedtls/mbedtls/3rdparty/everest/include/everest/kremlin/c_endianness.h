/* 版权所有（c）INRIA和Microsoft Corporation。保留所有权利。根据Apache 2.0许可证许可。*/

#ifndef __KREMLIN_ENDIAN_H
#define __KREMLIN_ENDIAN_H

#include <string.h>
#include <inttypes.h>

/******************************************************************************/
/* 实现C.fst（第2部分：endian-ness宏）*/
/******************************************************************************/

/* …适用于Linux*/
#if defined(__linux__) || defined(__CYGWIN__)
#  include <endian.h>

/* …对于OSX*/
#elif defined(__APPLE__)
#  include <libkern/OSByteOrder.h>
#  define htole64(x) OSSwapHostToLittleInt64(x)
#  define le64toh(x) OSSwapLittleToHostInt64(x)
#  define htobe64(x) OSSwapHostToBigInt64(x)
#  define be64toh(x) OSSwapBigToHostInt64(x)

#  define htole16(x) OSSwapHostToLittleInt16(x)
#  define le16toh(x) OSSwapLittleToHostInt16(x)
#  define htobe16(x) OSSwapHostToBigInt16(x)
#  define be16toh(x) OSSwapBigToHostInt16(x)

#  define htole32(x) OSSwapHostToLittleInt32(x)
#  define le32toh(x) OSSwapLittleToHostInt32(x)
#  define htobe32(x) OSSwapHostToBigInt32(x)
#  define be32toh(x) OSSwapBigToHostInt32(x)

/* …对于Solaris*/
#elif defined(__sun__)
#  include <sys/byteorder.h>
#  define htole64(x) LE_64(x)
#  define le64toh(x) LE_64(x)
#  define htobe64(x) BE_64(x)
#  define be64toh(x) BE_64(x)

#  define htole16(x) LE_16(x)
#  define le16toh(x) LE_16(x)
#  define htobe16(x) BE_16(x)
#  define be16toh(x) BE_16(x)

#  define htole32(x) LE_32(x)
#  define le32toh(x) LE_32(x)
#  define htobe32(x) BE_32(x)
#  define be32toh(x) BE_32(x)

/* …对于BSD*/
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__DragonFly__)
#  include <sys/endian.h>
#elif defined(__OpenBSD__)
#  include <endian.h>

/* …针对Windows（MSVC）…不针对XBOX 360！*/
#elif defined(_MSC_VER)

#  include <stdlib.h>
#  define htobe16(x) _byteswap_ushort(x)
#  define htole16(x) (x)
#  define be16toh(x) _byteswap_ushort(x)
#  define le16toh(x) (x)

#  define htobe32(x) _byteswap_ulong(x)
#  define htole32(x) (x)
#  define be32toh(x) _byteswap_ulong(x)
#  define le32toh(x) (x)

#  define htobe64(x) _byteswap_uint64(x)
#  define htole64(x) (x)
#  define be64toh(x) _byteswap_uint64(x)
#  define le64toh(x) (x)

/* …适用于Windows（类似GCC，例如鸣笛或叮当声）*/
#elif (defined(_WIN32) || defined(_WIN64)) &&                                  \
    (defined(__GNUC__) || defined(__clang__))

#  define htobe16(x) __builtin_bswap16(x)
#  define htole16(x) (x)
#  define be16toh(x) __builtin_bswap16(x)
#  define le16toh(x) (x)

#  define htobe32(x) __builtin_bswap32(x)
#  define htole32(x) (x)
#  define be32toh(x) __builtin_bswap32(x)
#  define le32toh(x) (x)

#  define htobe64(x) __builtin_bswap64(x)
#  define htole64(x) (x)
#  define be64toh(x) __builtin_bswap64(x)
#  define le64toh(x) (x)

/* …通用大端回退代码*/
#elif defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__

/* 字节交换代码的灵感来自：https://github.com/rweather/arduinolibs/blob/master/libraries/Crypto/utility/EndianUtil.h
 * */

#  define htobe32(x) (x)
#  define be32toh(x) (x)
#  define htole32(x)                                                           \
    (__extension__({                                                           \
      uint32_t _temp = (x);                                                    \
      ((_temp >> 24) & 0x000000FF) | ((_temp >> 8) & 0x0000FF00) |             \
          ((_temp << 8) & 0x00FF0000) | ((_temp << 24) & 0xFF000000);          \
    }))
#  define le32toh(x) (htole32((x)))

#  define htobe64(x) (x)
#  define be64toh(x) (x)
#  define htole64(x)                                                           \
    (__extension__({                                                           \
      uint64_t __temp = (x);                                                   \
      uint32_t __low = htobe32((uint32_t)__temp);                              \
      uint32_t __high = htobe32((uint32_t)(__temp >> 32));                     \
      (((uint64_t)__low) << 32) | __high;                                      \
    }))
#  define le64toh(x) (htole64((x)))

/* …通用小端回退代码*/
#elif defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

#  define htole32(x) (x)
#  define le32toh(x) (x)
#  define htobe32(x)                                                           \
    (__extension__({                                                           \
      uint32_t _temp = (x);                                                    \
      ((_temp >> 24) & 0x000000FF) | ((_temp >> 8) & 0x0000FF00) |             \
          ((_temp << 8) & 0x00FF0000) | ((_temp << 24) & 0xFF000000);          \
    }))
#  define be32toh(x) (htobe32((x)))

#  define htole64(x) (x)
#  define le64toh(x) (x)
#  define htobe64(x)                                                           \
    (__extension__({                                                           \
      uint64_t __temp = (x);                                                   \
      uint32_t __low = htobe32((uint32_t)__temp);                              \
      uint32_t __high = htobe32((uint32_t)(__temp >> 32));                     \
      (((uint64_t)__low) << 32) | __high;                                      \
    }))
#  define be64toh(x) (htobe64((x)))

/* …无法确定目标平台的端序*/
#else
#  error "Please define __BYTE_ORDER__!"

#endif /* 已定义（__linux__）||。。。*/

/* 加载和存储。通过memcpy，可以避免由于未对齐的内存访问而导致的未定义行为。*/

inline static uint16_t load16(uint8_t *b) {
  uint16_t x;
  memcpy(&x, b, 2);
  return x;
}

inline static uint32_t load32(uint8_t *b) {
  uint32_t x;
  memcpy(&x, b, 4);
  return x;
}

inline static uint64_t load64(uint8_t *b) {
  uint64_t x;
  memcpy(&x, b, 8);
  return x;
}

inline static void store16(uint8_t *b, uint16_t i) {
  memcpy(b, &i, 2);
}

inline static void store32(uint8_t *b, uint32_t i) {
  memcpy(b, &i, 4);
}

inline static void store64(uint8_t *b, uint64_t i) {
  memcpy(b, &i, 8);
}

#define load16_le(b) (le16toh(load16(b)))
#define store16_le(b, i) (store16(b, htole16(i)))
#define load16_be(b) (be16toh(load16(b)))
#define store16_be(b, i) (store16(b, htobe16(i)))

#define load32_le(b) (le32toh(load32(b)))
#define store32_le(b, i) (store32(b, htole32(i)))
#define load32_be(b) (be32toh(load32(b)))
#define store32_be(b, i) (store32(b, htobe32(i)))

#define load64_le(b) (le64toh(load64(b)))
#define store64_le(b, i) (store64(b, htole64(i)))
#define load64_be(b) (be64toh(load64(b)))
#define store64_be(b, i) (store64(b, htobe64(i)))

#endif
