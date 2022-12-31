/*******************************************************************************
 * 版权所有（c）2011、2012、2013、2014、2015奥拉夫·伯格曼（TZI）和其他人。保留所有权利。本程序和随附材料根据本发行版附带的Eclipse公共许可证v1.0和Eclipse发行许可证v1.1的条款提供。
 *
 * Eclipse公共许可证位于http://www.eclipse.org/legal/epl-v10.htmlEclipse发行许可证在http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * 贡献者：Olaf Bergmann-初始API和实现Hauke Mehrtens-内存优化、ECC集成
 *
 *******************************************************************************/

#ifndef _DTLS_CCM_H_
#define _DTLS_CCM_H_

#include "aes/rijndael.h"

/* 计数器模式CBC-MAC的实现，RFC 3610*/

#define DTLS_CCM_BLOCKSIZE  16	/**<hmac块的大小*/
#define DTLS_CCM_MAX        16	/**<摘要中的最大字节数*/
#define DTLS_CCM_NONCE_SIZE 12	/**<随机数的大小*/

/** 
 * 在CCM模式下使用AES对消息进行身份验证和加密。有关\p M、\p L、\p lm和\p la的含义，请参见RFC 3610。
 * 
 * \param ctx用于AES操作的初始化rijndael_ctx对象。\param M身份验证八位字节的数量。\param L用于编码消息长度的字节数。\param N要使用的随机数值。您必须提供\c DTLS_CCM_BLOCKSIZE随机数八位字节，尽管只使用前\c 16-\p L-1。\param msg要加密的消息。前一个八位字节是明文形式的附加身份验证数据。请注意，加密操作会修改\p msg的内容，并添加\p M字节MAC。因此，缓冲区大小必须至少为\p lm+\p M字节。\param lm \p消息的实际长度。\param aad指向附加身份验证数据的指针（如果\p la为零，则可以为空）。\param la附加身份验证八位字节的数量（可以为零）。\返回FIXME
 */
long int
dtls_ccm_encrypt_message(rijndael_ctx *ctx, size_t M, size_t L, 
			 const unsigned char nonce[DTLS_CCM_BLOCKSIZE],
			 unsigned char *msg, size_t lm, 
			 const unsigned char *aad, size_t la);

long int
dtls_ccm_decrypt_message(rijndael_ctx *ctx, size_t M, size_t L, 
			 const unsigned char nonce[DTLS_CCM_BLOCKSIZE],
			 unsigned char *msg, size_t lm, 
			 const unsigned char *aad, size_t la);

#endif /* _DTLS_CCM_H_ */

