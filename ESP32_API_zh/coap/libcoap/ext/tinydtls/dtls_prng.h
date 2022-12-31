/*******************************************************************************
 * 版权所有（c）2011-2019 Olaf Bergmann（TZI）和其他人。保留所有权利。本程序和随附材料根据本发行版附带的Eclipse公共许可证v1.0和Eclipse发行许可证v1.1的条款提供。
 *
 * Eclipse公共许可证位于http://www.eclipse.org/legal/epl-v10.htmlEclipse发行许可证在http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * 贡献者：Olaf Bergmann-初始API和实现Hauke Mehrtens-内存优化、ECC集成Jon Shallow-依赖于平台的prng支持
 *
 *******************************************************************************/

/** 
 * @file 每小时
 * @brief 伪随机数
 */

#ifndef _DTLS_PRNG_H_
#define _DTLS_PRNG_H_

#include "tinydtls.h"
#include <stdlib.h>

/** 
 * @defgroup 伪随机数@{
 */

/**
 * 用长度随机字节填充缓冲区。这是prng（）的默认实现。您可能需要更改prng（）以在特定平台上使用更好的prng。
 *
 * @buf 要填充的缓冲区
 * @len 要填充的缓冲区的长度
 *
 * @return 1个缓冲区已填充
 */
int dtls_prng(unsigned char *buf, size_t len);

/**
 * 为函数dtls_prng（）使用的随机数生成器种子
 *
 * @seed 给随机数生成器加质数的种子
 */
void dtls_prng_init(unsigned seed);

/** @} */

#endif /* _DTLS_PRNG_H_ */

