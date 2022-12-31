/**
 * \文件des.h
 *
 *  基于XySSL：版权所有（C）2006-2008 Christophe Devine
 *
 *  版权所有（C）2009 Paul Bakker<polarssl_maintainer at polarssl-dot-org>
 *
 *  保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *  
 *    *源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。未经事先书面许可，不得使用PolarSSL或XySSL的名称或其贡献者的名称来支持或推广源自本软件的产品。
 *  
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "netif/ppp/ppp_opts.h"
#if LWIP_INCLUDED_POLARSSL_DES

#ifndef LWIP_INCLUDED_POLARSSL_DES_H
#define LWIP_INCLUDED_POLARSSL_DES_H

#define DES_ENCRYPT     1
#define DES_DECRYPT     0

/**
 * \简要DES上下文结构
 */
typedef struct
{
    int mode;                   /*!<  加密/解密*/
    unsigned long sk[32];       /*!<  DES子密钥*/
}
des_context;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \简短的DES密钥计划（56位，加密）
 *
 * \param ctx要初始化的DES上下文\param key 8字节密钥
 */
void des_setkey_enc( des_context *ctx, unsigned char key[8] );

/**
 * \简短的DES密钥调度（56位，解密）
 *
 * \param ctx要初始化的DES上下文\param key 8字节密钥
 */
void des_setkey_dec( des_context *ctx, unsigned char key[8] );

/**
 * \简要DES-ECB块加密/解密
 *
 * \param ctx DES上下文\param输入64位输入块\param输出64位输出块
 */
void des_crypt_ecb( des_context *ctx,
                    const unsigned char input[8],
                    unsigned char output[8] );

#ifdef __cplusplus
}
#endif

#endif /* LWIP_INCLUDED_POLARSSL_DES_H */

#endif /* LWIP_INCLUDED_POLARSSL_DES */

