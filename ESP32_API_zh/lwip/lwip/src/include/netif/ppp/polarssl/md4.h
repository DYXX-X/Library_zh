/**
 * \文件md4.h
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
#if LWIP_INCLUDED_POLARSSL_MD4

#ifndef LWIP_INCLUDED_POLARSSL_MD4_H
#define LWIP_INCLUDED_POLARSSL_MD4_H

/**
 * \简要的MD4上下文结构
 */
typedef struct
{
    unsigned long total[2];     /*!< 处理的字节数*/
    unsigned long state[4];     /*!< 中间消化状态*/
    unsigned char buffer[64];   /*!< 正在处理的数据块*/
}
md4_context;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \简短的MD4上下文设置
 *
 * \要初始化的param ctx上下文
 */
void md4_starts( md4_context *ctx );

/**
 * \简短的MD4进程缓冲区
 *
 * \param ctx MD4上下文\param保存数据的输入缓冲区\param输入数据的长度
 */
void md4_update( md4_context *ctx, const unsigned char *input, int ilen );

/**
 * \简要MD4最终摘要
 *
 * \param ctx MD4上下文\param输出MD4校验和结果
 */
void md4_finish( md4_context *ctx, unsigned char output[16] );

/**
 * \简要输出=MD4（输入缓冲区）
 *
 * \param保存数据的输入缓冲区\param输入数据的长度\param输出MD4校验和结果
 */
void md4( unsigned char *input, int ilen, unsigned char output[16] );


#ifdef __cplusplus
}
#endif

#endif /* LWIP_INCLUDED_POLARSSL_MD4_H */

#endif /* LWIP_INCLUDED_POLARSSL_MD4 */

