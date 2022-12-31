// 版权所有2020 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef _OPENSSL_BIO_H
#define _OPENSSL_BIO_H

#include <stddef.h>

#ifdef __cplusplus
 extern "C" {
#endif

/* 这些是BIO的“类型”*/
#define BIO_TYPE_NONE 0
#define BIO_TYPE_MEM (1 | 0x0400)
#define BIO_TYPE_BIO (19 | 0x0400)        /* （半个）BIO对*/

/* 生物对象标志*/
#define BIO_FLAGS_READ		0x01
#define BIO_FLAGS_WRITE		0x02

#define BIO_should_read(a)		BIO_test_flags(a, BIO_FLAGS_READ)
#define BIO_should_write(a)		BIO_test_flags(a, BIO_FLAGS_WRITE)

typedef struct bio_st BIO;
typedef struct bio_method_st BIO_METHOD;

/**
 * @brief 创建BIO对象作为文件类型当前实现返回NULL，因为ESP平台上不支持文件类型
 *
 * @param filename 文件名
 * @param mode 模式
 *
 * @return BIO对象
 */
BIO *BIO_new_file(const char *filename, const char *mode);

/**
 * @brief 将BIO对象创建为membuf类型当前实现获取缓冲区的浅拷贝
 *
 * @param buf 指向缓冲区的指针
 * @param len 缓冲区长度
 *
 * @return BIO对象
 */
BIO *BIO_new_mem_buf(void *buf, int len);

/**
 * @brief 创建BIO对象
 *
 * @param method -指向BIO_METHOD的指针
 *
 * @return 指向BIO对象的指针
 */
BIO *BIO_new(BIO_METHOD * method);

/**
 * @brief 获取内存BIO方法函数
 */
void *BIO_s_mem(void);

/**
 * @brief 释放BIO对象
 *
 * @param x -指向BIO对象的指针
 */
void BIO_free(BIO *b);

/**
 * @brief 创建具有写缓冲区大小writebuf1和writebuf2的连接BIO bio1、bio2对
 *
 * @param out1    指向BIO1的指针
 * @param writebuf1    BIO1的写入大小（0表示将使用默认大小）
 * @param out2    指向BIO2的指针
 * @param writebuf2    BIO2的写入大小（0表示将使用默认大小）
 *
 * @return 结果0:失败1:OK
 */
int BIO_new_bio_pair(BIO **out1, size_t writebuf1, BIO **out2, size_t writebuf2);

/**
 * @brief 将数据写入BIO
 *
 * BIO_TYPE_BIO的行为方式与OpenSSL BIO对象相同，其他BIO类型模仿此功能以避免过度分配/复制，因此在调用函数后无法释放“数据”，在使用BIO对象之前，它应该保持有效。
 *
 * @param b    -指向BIO的指针
 * @param data -指向数据的指针
 * @param dlen -数据字节
 *
 * @return 后果
 *      -1，0:失败1:正常
 */
int BIO_write(BIO *b, const void *data, int dlen);

/**
 * @brief 从BIO读取数据
 *
 * BIO_TYPE_BIO的行为方式与OpenSSL BIO对象相同。其他类型只保留指针
 *
 * @param b    -指向BIO的指针
 * @param data -指向数据的指针
 * @param dlen -数据字节
 *
 * @return 后果
 *      -1，0:失败1:正常
 */
int BIO_read(BIO *bio, void *data, int len);

/**
 * @brief 获取BIO写入缓冲区中挂起的字符数。
 *
 * @param b 指向BIO的指针
 *
 * @return 待定数据量
 */
size_t BIO_wpending(const BIO *bio);

/**
 * @brief 获取BIO读取缓冲区中挂起的字符数。
 *
 * @param b 指向BIO的指针
 *
 * @return 待定数据量
 */
size_t BIO_ctrl_pending(const BIO *bio);

/**
 * @brief 获取当前可写入BIO的最大数据长度
 *
 * @param b 指向BIO的指针
 *
 * @return 可写数据的最大长度
 */
size_t BIO_ctrl_get_write_guarantee(BIO *bio);

/**
 * @brief 返回BIO的类型。
 *
 * @param b 指向BIO的指针
 *
 * @return BIO对象的类型
 */
int BIO_method_type(const BIO *b);

/**
 * @brief BIO的测试标志。
 *
 * @param b 指向BIO的指针
 * @param flags 旗帜
 *
 * @return BIO对象标志用提供的标志屏蔽
 */
int  BIO_test_flags(const BIO *b, int flags);

#ifdef __cplusplus
}
#endif

#endif //_OPENSSL_BIO_H

