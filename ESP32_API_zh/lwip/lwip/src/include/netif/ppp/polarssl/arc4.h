/**
 * \文件arc4.h
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
#if LWIP_INCLUDED_POLARSSL_ARC4

#ifndef LWIP_INCLUDED_POLARSSL_ARC4_H
#define LWIP_INCLUDED_POLARSSL_ARC4_H

/**
 * \ARC4上下文结构简介
 */
typedef struct
{
    int x;                      /*!< 排列指数*/
    int y;                      /*!< 排列指数*/
    unsigned char m[256];       /*!< 排列表*/
}
arc4_context;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ARC4关键计划简介
 *
 * \param ctx ARC4上下文要初始化\param key密钥\param keylen密钥长度
 */
void arc4_setup( arc4_context *ctx, unsigned char *key, int keylen );

/**
 * \简短的ARC4密码函数
 *
 * \param ctx ARC4上下文\param要处理的缓冲区\param缓冲区中的数据量
 */
void arc4_crypt( arc4_context *ctx, unsigned char *buf, int buflen );

#ifdef __cplusplus
}
#endif

#endif /* LWIP_INCLUDED_POLARSSL_ARC4_H */

#endif /* LWIP_INCLUDED_POLARSSL_ARC4 */

