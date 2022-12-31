/*
 * SPDX文件版权文本：2015-2016 Intel Corporation。
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _BLE_MESH_BYTEORDER_H_
#define _BLE_MESH_BYTEORDER_H_

#include "mesh_types.h"
#include "mesh_trace.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 内部助手仅由下面的sys_*API使用*/
#ifndef __bswap_16
#define __bswap_16(x) ((uint16_t) ((((x) >> 8) & 0xff) | (((x) & 0xff) << 8)))
#endif

#ifndef __bswap_24
#define __bswap_24(x) ((uint32_t) ((((x) >> 16) & 0xff) | \
                                   (((x)) & 0xff00) | \
                                   (((x) & 0xff) << 16)))
#endif

#ifndef __bswap_32
#define __bswap_32(x) ((uint32_t) ((((x) >> 24) & 0xff) | \
                                   (((x) >> 8) & 0xff00) | \
                                   (((x) & 0xff00) << 8) | \
                                   (((x) & 0xff) << 24)))
#endif

#ifndef __bswap_48
#define __bswap_48(x) ((uint64_t) ((((x) >> 40) & 0xff) | \
                                   (((x) >> 24) & 0xff00) | \
                                   (((x) >> 8) & 0xff0000) | \
                                   (((x) & 0xff0000) << 8) | \
                                   (((x) & 0xff00) << 24) | \
                                   (((x) & 0xff) << 40)))
#endif

#ifndef __bswap_64
#define __bswap_64(x) ((uint64_t) ((((x) >> 56) & 0xff) | \
                                   (((x) >> 40) & 0xff00) | \
                                   (((x) >> 24) & 0xff0000) | \
                                   (((x) >> 8) & 0xff000000) | \
                                   (((x) & 0xff000000) << 8) | \
                                   (((x) & 0xff0000) << 24) | \
                                   (((x) & 0xff00) << 40) | \
                                   (((x) & 0xff) << 56)))
#endif

/** @def 系统16_to_cpu
 *  @brief 将16位整数从小端序转换为主机端序。
 *
 *  @param val 以小端字节格式表示的16位整数。
 *
 *  @return 主机端序中的16位整数。
 */

/** @def sys_cpu_to_le16系统
 *  @brief 将16位整数从主机端序转换为小端序。
 *
 *  @param val 主机端序中的16位整数。
 *
 *  @return 以小端字节格式表示的16位整数。
 */

/** @def sys_le24_to_cpu系统
 *  @brief 将24位整数从小端序转换为主机端序。
 *
 *  @param val 24位小端格式的整数。
 *
 *  @return 主机端序中的24位整数。
 */

/** @def sys_cpu_to_le24系统
 *  @brief 将24位整数从主机端序转换为小端序。
 *
 *  @param val 主机端序中的24位整数。
 *
 *  @return 24位小端格式的整数。
 */

/** @def 系统_le32_to_cpu
 *  @brief 将32位整数从小端序转换为主机端序。
 *
 *  @param val 小端字节格式的32位整数。
 *
 *  @return 主机端序中的32位整数。
 */

/** @def sys_cpu_to_le32系统
 *  @brief 将32位整数从主机端序转换为小端序。
 *
 *  @param val 主机端序中的32位整数。
 *
 *  @return 小端字节格式的32位整数。
 */

/** @def sys_le48_to_cpu系统
 *  @brief 将48位整数从小端序转换为主机端序。
 *
 *  @param val 小端字节格式的48位整数。
 *
 *  @return 主机端序中的48位整数。
 */

/** @def sys_cpu_to_le48系统
 *  @brief 将48位整数从主机端序转换为小端序。
 *
 *  @param val 主机端序中的48位整数。
 *
 *  @return 小端字节格式的48位整数。
 */

/** @def sys_be16_to_cpu系统
 *  @brief 将16位整数从大端序转换为主机端序。
 *
 *  @param val 16位整数，大端格式。
 *
 *  @return 主机端序中的16位整数。
 */

/** @def 系统_cpu_to_be16
 *  @brief 将16位整数从主机端序转换为大端序。
 *
 *  @param val 主机端序中的16位整数。
 *
 *  @return 16位整数，大端格式。
 */

/** @def sys_be24_to_cpu系统
 *  @brief 将24位整数从大端序转换为主机端序。
 *
 *  @param val 24位整数，大端格式。
 *
 *  @return 主机端序中的24位整数。
 */

/** @def sys_cpu_to_be24系统
 *  @brief 将24位整数从主机端序转换为大端序。
 *
 *  @param val 主机端序中的24位整数。
 *
 *  @return 24位整数，大端格式。
 */

/** @def 系统_be32_to_cpu
 *  @brief 将32位整数从大端序转换为主机端序。
 *
 *  @param val 32位整数，大端格式。
 *
 *  @return 主机端序中的32位整数。
 */

/** @def 系统_cpu_to_be32
 *  @brief 将32位整数从主机端序转换为大端序。
 *
 *  @param val 主机端序中的32位整数。
 *
 *  @return 32位整数，大端格式。
 */

/** @def 系统be48_to_cpu
 *  @brief 将48位整数从大端序转换为主机端序。
 *
 *  @param val 采用大端数格式的48位整数。
 *
 *  @return 主机端序中的48位整数。
 */

/** @def 系统_cpu_to_be48
 *  @brief 将48位整数从主机端序转换为大端序。
 *
 *  @param val 主机端序中的48位整数。
 *
 *  @return 采用大端数格式的48位整数。
 */

#ifndef sys_le16_to_cpu
#define sys_le16_to_cpu(val) (val)
#endif
#ifndef sys_cpu_to_le16
#define sys_cpu_to_le16(val) (val)
#endif
#ifndef sys_le24_to_cpu
#define sys_le24_to_cpu(val) (val)
#endif
#ifndef sys_cpu_to_le24
#define sys_cpu_to_le24(val) (val)
#endif
#ifndef sys_le32_to_cpu
#define sys_le32_to_cpu(val) (val)
#endif
#ifndef sys_cpu_to_le32
#define sys_cpu_to_le32(val) (val)
#endif
#ifndef sys_le48_to_cpu
#define sys_le48_to_cpu(val) (val)
#endif
#ifndef sys_cpu_to_le48
#define sys_cpu_to_le48(val) (val)
#endif
#ifndef sys_le64_to_cpu
#define sys_le64_to_cpu(val) (val)
#endif
#ifndef sys_cpu_to_le64
#define sys_cpu_to_le64(val) (val)
#endif
#ifndef sys_be16_to_cpu
#define sys_be16_to_cpu(val) __bswap_16(val)
#endif
#ifndef sys_cpu_to_be16
#define sys_cpu_to_be16(val) __bswap_16(val)
#endif
#ifndef sys_be24_to_cpu
#define sys_be24_to_cpu(val) __bswap_24(val)
#endif
#ifndef sys_cpu_to_be24
#define sys_cpu_to_be24(val) __bswap_24(val)
#endif
#ifndef sys_be32_to_cpu
#define sys_be32_to_cpu(val) __bswap_32(val)
#endif
#ifndef sys_cpu_to_be32
#define sys_cpu_to_be32(val) __bswap_32(val)
#endif
#ifndef sys_be48_to_cpu
#define sys_be48_to_cpu(val) __bswap_48(val)
#endif
#ifndef sys_cpu_to_be48
#define sys_cpu_to_be48(val) __bswap_48(val)
#endif
#ifndef sys_be64_to_cpu
#define sys_be64_to_cpu(val) __bswap_64(val)
#endif
#ifndef sys_cpu_to_be64
#define sys_cpu_to_be64(val) __bswap_64(val)
#endif

/**
 *  @brief 将一个16位整数作为大尾数放入任意位置。
 *
 *  将一个16位整数（最初为主机端序）以大端序格式放入一个可能未对齐的内存位置。
 *
 *  @param val 主机端序中的16位整数。
 *  @param dst 存储结果的目标内存地址。
 */
static inline void sys_put_be16(uint16_t val, uint8_t dst[2])
{
    dst[0] = val >> 8;
    dst[1] = val;
}

/**
 *  @brief 将一个24位整数作为大尾数放入任意位置。
 *
 *  将一个24位整数（最初为主机端序）以大端序格式放入一个可能未对齐的内存位置。
 *
 *  @param val 主机端序中的24位整数。
 *  @param dst 存储结果的目标内存地址。
 */
static inline void sys_put_be24(uint32_t val, uint8_t dst[3])
{
    dst[0] = val >> 16;
    sys_put_be16(val, &dst[1]);
}

/**
 *  @brief 将一个32位整数作为大尾数放在任意位置。
 *
 *  将一个32位整数（最初为主机端序）以大端序格式放入一个可能未对齐的内存位置。
 *
 *  @param val 主机端序中的32位整数。
 *  @param dst 存储结果的目标内存地址。
 */
static inline void sys_put_be32(uint32_t val, uint8_t dst[4])
{
    sys_put_be16(val >> 16, dst);
    sys_put_be16(val, &dst[2]);
}

/**
 *  @brief 将一个48位整数作为大尾数放入任意位置。
 *
 *  将一个48位整数（最初为主机端序）以大端序格式放入一个可能未对齐的内存位置。
 *
 *  @param val 主机端序中的48位整数。
 *  @param dst 存储结果的目标内存地址。
 */
static inline void sys_put_be48(uint64_t val, uint8_t dst[6])
{
    sys_put_be16(val >> 32, dst);
    sys_put_be32(val, &dst[2]);
}

/**
 *  @brief 将一个64位整数作为大端数放在任意位置。
 *
 *  将64位整数（最初为主机端序）以大端序格式放置到可能未对齐的内存位置。
 *
 *  @param val 主机端序中的64位整数。
 *  @param dst 存储结果的目标内存地址。
 */
static inline void sys_put_be64(uint64_t val, uint8_t dst[8])
{
    sys_put_be32(val >> 32, dst);
    sys_put_be32(val, &dst[4]);
}

/**
 *  @brief 将一个16位整数作为小尾数放入任意位置。
 *
 *  将一个16位整数（最初为主机端序）以小端序格式放入一个可能未对齐的内存位置。
 *
 *  @param val 主机端序中的16位整数。
 *  @param dst 存储结果的目标内存地址。
 */
static inline void sys_put_le16(uint16_t val, uint8_t dst[2])
{
    dst[0] = val;
    dst[1] = val >> 8;
}

/**
 *  @brief 将一个24位整数作为小尾数放入任意位置。
 *
 *  以littel-endian格式将一个24位整数（最初为主机端序）放入一个可能未对齐的内存位置。
 *
 *  @param val 主机端序中的24位整数。
 *  @param dst 存储结果的目标内存地址。
 */
static inline void sys_put_le24(uint32_t val, uint8_t dst[3])
{
    sys_put_le16(val, dst);
    dst[2] = val >> 16;
}

/**
 *  @brief 将一个32位整数作为小尾数放入任意位置。
 *
 *  将一个32位整数（最初为主机端序）以小端序格式放入一个可能未对齐的内存位置。
 *
 *  @param val 主机端序中的32位整数。
 *  @param dst 存储结果的目标内存地址。
 */
static inline void sys_put_le32(uint32_t val, uint8_t dst[4])
{
    sys_put_le16(val, dst);
    sys_put_le16(val >> 16, &dst[2]);
}

/**
 *  @brief 将一个48位整数作为小尾数放入任意位置。
 *
 *  将一个48位整数（最初为主机端序）以小端序格式放入一个可能未对齐的内存位置。
 *
 *  @param val 主机端序中的48位整数。
 *  @param dst 存储结果的目标内存地址。
 */
static inline void sys_put_le48(uint64_t val, uint8_t dst[6])
{
    sys_put_le32(val, dst);
    sys_put_le16(val >> 32, &dst[4]);
}

/**
 *  @brief 将一个64位整数作为小尾数放入任意位置。
 *
 *  将一个64位整数（最初为主机端序）以小端序格式放入一个可能未对齐的内存位置。
 *
 *  @param val 主机端序中的64位整数。
 *  @param dst 存储结果的目标内存地址。
 */
static inline void sys_put_le64(uint64_t val, uint8_t dst[8])
{
    sys_put_le32(val, dst);
    sys_put_le32(val >> 32, &dst[4]);
}

/**
 *  @brief 获取以大端序格式存储的16位整数。
 *
 *  获取一个16位整数，以大端序格式存储在可能未对齐的内存位置，并将其转换为主机端序。
 *
 *  @param src 要获取的大端16位整数的位置。
 *
 *  @return 主机端序中的16位整数。
 */
static inline uint16_t sys_get_be16(const uint8_t src[2])
{
    return ((uint16_t)src[0] << 8) | src[1];
}

/**
 *  @brief 获取以大端序格式存储的24位整数。
 *
 *  获取一个24位整数，以大端序格式存储在可能未对齐的内存位置，并将其转换为主机端序。
 *
 *  @param src 要获取的大端24位整数的位置。
 *
 *  @return 主机端序中的24位整数。
 */
static inline uint32_t sys_get_be24(const uint8_t src[3])
{
    return ((uint32_t)src[0] << 16) | sys_get_be16(&src[1]);
}

/**
 *  @brief 获取以大端序格式存储的32位整数。
 *
 *  获取一个32位整数，以大端序格式存储在可能未对齐的内存位置，并将其转换为主机端序。
 *
 *  @param src 要获取的大端32位整数的位置。
 *
 *  @return 主机端序中的32位整数。
 */
static inline uint32_t sys_get_be32(const uint8_t src[4])
{
    return ((uint32_t)sys_get_be16(&src[0]) << 16) | sys_get_be16(&src[2]);
}

/**
 *  @brief 获取以大端序格式存储的48位整数。
 *
 *  获取一个48位整数，以大端序格式存储在可能未对齐的内存位置，并将其转换为主机端序。
 *
 *  @param src 要获取的大端48位整数的位置。
 *
 *  @return 主机端序中的48位整数。
 */
static inline uint64_t sys_get_be48(const uint8_t src[6])
{
    return ((uint64_t)sys_get_be32(&src[0]) << 32) | sys_get_be16(&src[4]);
}

/**
 *  @brief 获取以大端序格式存储的64位整数。
 *
 *  获取一个64位整数，以大端序格式存储在可能未对齐的内存位置，并将其转换为主机端序。
 *
 *  @param src 要获取的大端64位整数的位置。
 *
 *  @return 主机端序中的64位整数。
 */
static inline uint64_t sys_get_be64(const uint8_t src[8])
{
    return ((uint64_t)sys_get_be32(&src[0]) << 32) | sys_get_be32(&src[4]);
}

/**
 *  @brief 获取以小端字节格式存储的16位整数。
 *
 *  获取一个16位整数，以小端格式存储在可能未对齐的内存位置，并将其转换为主机端序。
 *
 *  @param src 要获取的小端16位整数的位置。
 *
 *  @return 主机端序中的16位整数。
 */
static inline uint16_t sys_get_le16(const uint8_t src[2])
{
    return ((uint16_t)src[1] << 8) | src[0];
}

/**
 *  @brief 获取一个以大端序格式存储的24位整数。
 *
 *  获取一个24位整数，以大端序格式存储在可能未对齐的内存位置，并将其转换为主机端序。
 *
 *  @param src 要获取的大端24位整数的位置。
 *
 *  @return 主机端序中的24位整数。
 */
static inline uint32_t sys_get_le24(const uint8_t src[3])
{
    return ((uint32_t)src[2] << 16) | sys_get_le16(&src[0]);
}

/**
 *  @brief 获取以小端字节格式存储的32位整数。
 *
 *  获取一个32位整数，以小端序格式存储在可能未对齐的内存位置，并将其转换为主机端序。
 *
 *  @param src 要获取的小端32位整数的位置。
 *
 *  @return 主机端序中的32位整数。
 */
static inline uint32_t sys_get_le32(const uint8_t src[4])
{
    return ((uint32_t)sys_get_le16(&src[2]) << 16) | sys_get_le16(&src[0]);
}

/**
 *  @brief 获取以小端字节格式存储的48位整数。
 *
 *  获取一个48位整数，以小端格式存储在可能未对齐的内存位置，并将其转换为主机端序。
 *
 *  @param src 要获取的小端48位整数的位置。
 *
 *  @return 主机端序中的48位整数。
 */
static inline uint64_t sys_get_le48(const uint8_t src[6])
{
    return ((uint64_t)sys_get_le32(&src[2]) << 32) | sys_get_le16(&src[0]);
}

/**
 *  @brief 获取以小端字节格式存储的64位整数。
 *
 *  获取一个64位整数，以小端序格式存储在可能未对齐的内存位置，并将其转换为主机端序。
 *
 *  @param src 要获取的小端64位整数的位置。
 *
 *  @return 主机端序中的64位整数。
 */
static inline uint64_t sys_get_le64(const uint8_t src[8])
{
    return ((uint64_t)sys_get_le32(&src[4]) << 32) | sys_get_le32(&src[0]);
}

/**
 * @brief 将一个缓冲区内容交换到另一缓冲区内容
 *
 * 将src缓冲区的内容按相反的顺序复制到dst缓冲区中，即：src[n]将放在dst[end-n]中，其中n是索引，“end”是两个数组中的最后一个索引。2个内存指针必须指向不同的区域，并且具有给定长度的最小大小。
 *
 * @param dst 内存区域上复制数据的有效指针
 * @param src 从中复制数据的内存区域上的有效指针
 * @param length dst和src内存区域的大小
 */
static inline void sys_memcpy_swap(void *dst, const void *src, size_t length)
{
    uint8_t *pdst = (uint8_t *)dst;
    const uint8_t *psrc = (const uint8_t *)src;

    __ASSERT(((psrc < pdst && (psrc + length) <= pdst) ||
            (psrc > pdst && (pdst + length) <= psrc)),
            "Source and destination buffers must not overlap");

    psrc += length - 1;

    for (; length > 0; length--) {
        *pdst++ = *psrc--;
    }
}

/**
 * @brief 交换缓冲区内容
 *
 * 就地内存交换，最终内容将被反转。一、 e.：buf[n]将放在buf[end-n]中，其中n是索引，“end”是buf的最后一个索引。
 *
 * @param buf 要交换的内存区域上的有效指针
 * @param length 缓冲存储器区域的大小
 */
static inline void sys_mem_swap(void *buf, size_t length)
{
    size_t i;

    for (i = 0; i < (length / 2); i++) {
        uint8_t tmp = ((uint8_t *)buf)[i];

        ((uint8_t *)buf)[i] = ((uint8_t *)buf)[length - 1 - i];
        ((uint8_t *)buf)[length - 1 - i] = tmp;
    }
}

#ifdef __cplusplus
}
#endif

#endif /* _BLE_MESH_BYTEORDER_H_ */

