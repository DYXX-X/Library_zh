/*
 * Argon2源代码包
 *
 * Daniel Dinu和Dmitry Khovratovich撰写，2015年
 *
 * 本作品根据Creative Commons CC0 1.0许可/弃权获得许可。
 *
 * 您应该已经收到了CC0公共域专用的副本以及此软件。如果没有，请参见<http://creativecommons.org/publicdomain/zero/1.0/>.
 */
#ifndef argon2_H
#define argon2_H

#include <limits.h>
#include <stddef.h>
#include <stdint.h>

/*
 * Argon2输入参数限制
 */

/* 最小和最大车道数（平行度）*/
#define ARGON2_MIN_LANES UINT32_C(1)
#define ARGON2_MAX_LANES UINT32_C(0xFFFFFF)

/* 最小和最大线程数*/
#define ARGON2_MIN_THREADS UINT32_C(1)
#define ARGON2_MAX_THREADS UINT32_C(0xFFFFFF)

/* 每条车道之间的同步点数量*/
#define ARGON2_SYNC_POINTS UINT32_C(4)

/* 最小和最大摘要大小（字节）*/
#define ARGON2_MIN_OUTLEN UINT32_C(16)
#define ARGON2_MAX_OUTLEN UINT32_C(0xFFFFFFFF)

/* 最小和最大内存块数（每个BLOCK_SIZE字节）*/
#define ARGON2_MIN_MEMORY (2 * ARGON2_SYNC_POINTS) /* 每个切片2个块*/

#define ARGON2_MIN(a, b) ((a) < (b) ? (a) : (b))
/* 最大内存大小是寻址空间的一半，最高可达2^32个块（4 TB）
 */
#define ARGON2_MAX_MEMORY_BITS \
    ARGON2_MIN(UINT32_C(32), (sizeof(void *) * CHAR_BIT - 10 - 1))
#define ARGON2_MAX_MEMORY \
    ARGON2_MIN(UINT32_C(0xFFFFFFFF), UINT64_C(1) << ARGON2_MAX_MEMORY_BITS)

/* 最小和最大通过次数*/
#define ARGON2_MIN_TIME UINT32_C(1)
#define ARGON2_MAX_TIME UINT32_C(0xFFFFFFFF)

/* 最小和最大密码长度（字节）*/
#define ARGON2_MIN_PWD_LENGTH UINT32_C(0)
#define ARGON2_MAX_PWD_LENGTH UINT32_C(0xFFFFFFFF)

/* 最小和最大关联数据长度（字节）*/
#define ARGON2_MIN_AD_LENGTH UINT32_C(0)
#define ARGON2_MAX_AD_LENGTH UINT32_C(0xFFFFFFFF)

/* 最小和最大盐长度（字节）*/
#define ARGON2_MIN_SALT_LENGTH UINT32_C(8)
#define ARGON2_MAX_SALT_LENGTH UINT32_C(0xFFFFFFFF)

/* 最小和最大密钥长度（字节）*/
#define ARGON2_MIN_SECRET UINT32_C(0)
#define ARGON2_MAX_SECRET UINT32_C(0xFFFFFFFF)

#define ARGON2_FLAG_CLEAR_PASSWORD (UINT32_C(1) << 0)
#define ARGON2_FLAG_CLEAR_SECRET (UINT32_C(1) << 1)
#define ARGON2_FLAG_CLEAR_MEMORY (UINT32_C(1) << 2)
#define ARGON2_DEFAULT_FLAGS (UINT32_C(0))

/* 错误代码*/
typedef enum Argon2_ErrorCodes {
    ARGON2_OK = 0,

    ARGON2_OUTPUT_PTR_NULL = -1,

    ARGON2_OUTPUT_TOO_SHORT = -2,
    ARGON2_OUTPUT_TOO_LONG  = -3,

    ARGON2_PWD_TOO_SHORT = -4,
    ARGON2_PWD_TOO_LONG  = -5,

    ARGON2_SALT_TOO_SHORT = -6,
    ARGON2_SALT_TOO_LONG  = -7,

    ARGON2_AD_TOO_SHORT = -8,
    ARGON2_AD_TOO_LONG  = -9,

    ARGON2_SECRET_TOO_SHORT = -10,
    ARGON2_SECRET_TOO_LONG  = -11,

    ARGON2_TIME_TOO_SMALL = -12,
    ARGON2_TIME_TOO_LARGE = -13,

    ARGON2_MEMORY_TOO_LITTLE = -14,
    ARGON2_MEMORY_TOO_MUCH   = -15,

    ARGON2_LANES_TOO_FEW  = -16,
    ARGON2_LANES_TOO_MANY = -17,

    ARGON2_PWD_PTR_MISMATCH    = -18, /* 长度为非零的NULL指针*/
    ARGON2_SALT_PTR_MISMATCH   = -19, /* 长度为非零的NULL指针*/
    ARGON2_SECRET_PTR_MISMATCH = -20, /* 长度为非零的NULL指针*/
    ARGON2_AD_PTR_MISMATCH     = -21, /* 长度为非零的NULL指针*/

    ARGON2_MEMORY_ALLOCATION_ERROR = -22,

    ARGON2_FREE_MEMORY_CBK_NULL     = -23,
    ARGON2_ALLOCATE_MEMORY_CBK_NULL = -24,

    ARGON2_INCORRECT_PARAMETER = -25,
    ARGON2_INCORRECT_TYPE      = -26,

    ARGON2_OUT_PTR_MISMATCH = -27,

    ARGON2_THREADS_TOO_FEW  = -28,
    ARGON2_THREADS_TOO_MANY = -29,

    ARGON2_MISSING_ARGS = -30,

    ARGON2_ENCODING_FAIL = -31,

    ARGON2_DECODING_FAIL = -32,

    ARGON2_THREAD_FAIL = -33,

    ARGON2_DECODING_LENGTH_FAIL = -34,

    ARGON2_VERIFY_MISMATCH = -35
} argon2_error_codes;

/* Argon2外部数据结构*/

/*
 * 上下文：保存Argon2输入的结构：输出数组及其长度、密码及其长度、salt及其长度、secret及其长度、关联数据及其长度、传递次数、使用的内存量（以KB为单位，可以向上舍入一位）将运行的并行线程数。以上所有参数都会影响输出哈希值。此外，可以提供两个函数指针来分配和释放内存（如果为NULL，内存将在内部分配）。此外，三个标志指示是否删除密码、预散列后立即加密（因此不再需要）以及整个内存
 *****
 * 最简单的情况：您有输出数组out[8]，密码存储在pwd[32]中，salt存储在salt[16]中，您既没有密钥也没有关联数据。您需要花费1 GB的RAM，并使用4条平行车道运行5次Argon2。您想删除密码，但最后一次密码不会被删除。您希望使用默认内存分配器。然后初始化：Argon2_Context（out，8，pwd，32，salt，16，NULL，0，NULL，0,5,1<<20,4,4，NULL，NULL，true，false，false，false）。
 */
typedef struct Argon2_Context {
    uint8_t *out;    /* 输出阵列*/
    uint32_t outlen; /* 摘要长度*/

    uint8_t *pwd;    /* 密码数组*/
    uint32_t pwdlen; /* 密码长度*/

    uint8_t *salt;    /* 盐阵列*/
    uint32_t saltlen; /* 盐的长度*/

    uint8_t *secret;    /* 关键字数组*/
    uint32_t secretlen; /* 密钥长度*/

    uint8_t *ad;    /* 关联数据数组*/
    uint32_t adlen; /* 相关数据长度*/

    uint32_t t_cost;  /* 通过次数*/
    uint32_t m_cost;  /* 请求的内存量（KB）*/
    uint32_t lanes;   /* 车道数*/
    uint32_t threads; /* 最大线程数*/

    uint32_t flags; /* 布尔选项数组*/
} argon2_context;

/* Argon2原始类型*/
typedef enum Argon2_type { Argon2_i = 1, Argon2_id = 2 } argon2_type;

/*
 * 以一定的并行度执行内存硬哈希的函数
 * @param  context  指向Argon2内部结构的指针
 * @return 如果smth错误，则返回错误代码，否则返回ARGON2_OK
 */
int argon2_ctx(argon2_context *context, argon2_type type);

/**
 * 使用Argon2i哈希密码，生成编码哈希
 * @param t_cost 迭代次数
 * @param m_cost 将内存使用率设置为m_cost-kibibytes
 * @param parallelism 线程数和计算通道数
 * @param pwd 指向密码的指针
 * @param pwdlen 密码大小（字节）
 * @param salt 指向盐的指针
 * @param saltlen 盐大小（字节）
 * @param hashlen 所需的哈希长度（字节）
 * @param encoded 写入编码哈希的缓冲区
 * @param encodedlen 缓冲区大小（因此编码哈希的最大大小）
 * @pre   不同的并行度将产生不同的结果
 * @pre   如果成功，返回ARGON2_OK
 */
int argon2i_hash_encoded(const uint32_t t_cost, const uint32_t m_cost,
                         const uint32_t parallelism, const void *pwd,
                         const size_t pwdlen, const void *salt,
                         const size_t saltlen, const size_t hashlen,
                         char *encoded, const size_t encodedlen);

/**
 * 使用Argon2id散列密码，生成编码散列
 * @param t_cost 迭代次数
 * @param m_cost 将内存使用率设置为m_cost-kibibytes
 * @param parallelism 线程数和计算通道数
 * @param pwd 指向密码的指针
 * @param pwdlen 密码大小（字节）
 * @param salt 指向盐的指针
 * @param saltlen 盐大小（字节）
 * @param hashlen 所需的哈希长度（字节）
 * @param encoded 写入编码哈希的缓冲区
 * @param encodedlen 缓冲区大小（因此编码哈希的最大大小）
 * @pre   不同的并行度将产生不同的结果
 * @pre   如果成功，返回ARGON2_OK
 */
int argon2id_hash_encoded(const uint32_t t_cost, const uint32_t m_cost,
                          const uint32_t parallelism, const void *pwd,
                          const size_t pwdlen, const void *salt,
                          const size_t saltlen, const size_t hashlen,
                          char *encoded, const size_t encodedlen);

/**
 * 使用Argon2i哈希密码，生成原始哈希
 * @param t_cost 迭代次数
 * @param m_cost 将内存使用率设置为m_cost-kibibytes
 * @param parallelism 线程数和计算通道数
 * @param pwd 指向密码的指针
 * @param pwdlen 密码大小（字节）
 * @param salt 指向盐的指针
 * @param saltlen 盐大小（字节）
 * @param hash 写入原始哈希的缓冲区
 * @param hashlen 所需的哈希长度（字节）
 * @pre   不同的并行度将产生不同的结果
 * @pre   如果成功，返回ARGON2_OK
 */
int argon2i_hash_raw(const uint32_t t_cost, const uint32_t m_cost,
                     const uint32_t parallelism, const void *pwd,
                     const size_t pwdlen, const void *salt,
                     const size_t saltlen, void *hash, const size_t hashlen);

/**
 * 使用Argon2id哈希密码，生成原始哈希
 * @param t_cost 迭代次数
 * @param m_cost 将内存使用率设置为m_cost-kibibytes
 * @param parallelism 线程数和计算通道数
 * @param pwd 指向密码的指针
 * @param pwdlen 密码大小（字节）
 * @param salt 指向盐的指针
 * @param saltlen 盐大小（字节）
 * @param hash 写入原始哈希的缓冲区
 * @param hashlen 所需的哈希长度（字节）
 * @pre   不同的并行度将产生不同的结果
 * @pre   如果成功，返回ARGON2_OK
 */
int argon2id_hash_raw(const uint32_t t_cost, const uint32_t m_cost,
                      const uint32_t parallelism, const void *pwd,
                      const size_t pwdlen, const void *salt,
                      const size_t saltlen, void *hash, const size_t hashlen);

/* 上述函数的通用函数*/
int argon2_hash(const uint32_t t_cost, const uint32_t m_cost,
                const uint32_t parallelism, const void *pwd,
                const size_t pwdlen, const void *salt, const size_t saltlen,
                void *hash, const size_t hashlen, char *encoded,
                const size_t encodedlen, argon2_type type);

/**
 * 根据编码字符串验证密码编码字符串受到限制，如validate_inputs（）中所示
 * @param encoded 字符串编码参数，salt，hash
 * @param pwd 指向密码的指针
 * @pre   如果成功，返回ARGON2_OK
 */
int argon2i_verify(const char *encoded, const void *pwd, const size_t pwdlen);

/**
 * 根据编码字符串验证密码编码字符串受到限制，如validate_inputs（）中所示
 * @param encoded 字符串编码参数，salt，hash
 * @param pwd 指向密码的指针
 * @pre   如果成功，返回ARGON2_OK
 */
int argon2id_verify(const char *encoded, const void *pwd, const size_t pwdlen);

/* 上述函数的通用函数*/
int argon2_verify(const char *encoded, const void *pwd, const size_t pwdlen,
                  argon2_type type);
#endif

