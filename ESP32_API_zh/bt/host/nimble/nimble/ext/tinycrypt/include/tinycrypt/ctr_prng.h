/* ctr_prng。h-到CTR-PRNG实现的TinyCrypt接口*/

/*
 * 版权所有（c）2016，Chris Morrison保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * *源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。
 *
 * *二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 与CTR-PRNG实现的接口。
 *
 *  概述：伪随机数生成器（PRNG）生成的数字序列的分布与真实随机数序列的分布接近。NIST特别出版物800-90A规定了几种生成伪随机数序列的机制，包括基于AES的CTR-PRNG机制。TinyCrypt使用AES-128实现CTR-PRNG。
 *
 *  安全性：加密安全的PRNG取决于熵源的存在，以提供真正的随机种子，以及用作构建块的原语的安全性（本例中为AES-128）。
 *
 *  需要：-AES-128
 *
 *  用法：1）调用tc_ctr_prng_init为prng上下文设置种子
 *
 *              2） 调用tc_ctrprng_reseed将额外的熵混合到prng上下文中
 *
 *              3） 调用tc_ctr_prng_generate以输出伪随机数据
 *
 *              4） 调用tc_ctr_prng_unistantiate将prng上下文清零
 */

#ifndef __TC_CTR_PRNG_H__
#define __TC_CTR_PRNG_H__

#include <tinycrypt/aes.h>

#define TC_CTR_PRNG_RESEED_REQ -1

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	/* 每次生成另一个BLOCKLEN_BYTES字节时更新*/
	uint8_t V[TC_AES_BLOCK_SIZE]; 

	/* 每当重新播种PRNG时更新*/
	struct tc_aes_key_sched_struct key;

	/* 自初始化/重新播种后的请求数*/
	uint64_t reseedCount;
} TCCtrPrng_t;


/**
 *  @brief CTR-PRNG初始化过程使用熵和个性化字符串（如果有）初始化PRNG上下文
 *  @return 返回TC_CRYPTO_SUCCESS（1）如果：ctx==NULL，熵==NULL，entropyLen<（TC_AES_KEY_SIZE+TC_AES_BLOCK_SIZE），则返回TC_CRYPTO_FAIL（0）
 *  @note       仅使用熵和个性化输入的第一个（TC_AES_KEY_SIZE+TC_AES_BLOCK_SIZE）字节-提供额外的字节无效。
 *  @param ctx IN/OUT—要初始化的PRNG上下文
 *  @param entropy IN——用于播种PRNG的熵
 *  @param entropyLen IN—熵长度（字节）
 *  @param personalization IN——用于设定PRNG种子的个性化字符串（可以为空）
 *  @param plen IN--个性化长度（字节）
 *
 */
int tc_ctr_prng_init(TCCtrPrng_t * const ctx, 
		     uint8_t const * const entropy,
		     unsigned int entropyLen, 
		     uint8_t const * const personalization,
		     unsigned int pLen);

/**
 *  @brief CTR-PRNG重置过程将熵和额外的输入混合到PRNG上下文中
 *  @return 返回TC_CRYPTO_SUCCESS（1）如果：ctx==NULL，熵==NULL，熵<（TC_AES_KEY_SIZE+TC_AES_BLOCK_SIZE），则返回TC_CRYPTO_FAIL（0）
 *  @note 最好重新设定现有的prng上下文，而不是重新初始化，这样上下文中的任何现有熵都会得到保护。这为防止熵源未检测到的故障提供了一些保护。
 *  @note 假设已为ctx调用tc_ctr_prng_init
 *  @param ctx IN/OUT——PRNG状态
 *  @param entropy IN——混合到prng中的熵
 *  @param entropylen IN——熵长度（字节）
 *  @param additional_input IN——prng的附加输入（可以为空）
 *  @param additionallen IN—附加输入长度（字节）
 */
int tc_ctr_prng_reseed(TCCtrPrng_t * const ctx, 
		       uint8_t const * const entropy,
		       unsigned int entropyLen,
		       uint8_t const * const additional_input,
		       unsigned int additionallen);

/**
 *  @brief CTR-PRNG生成过程将输出伪随机字节生成到输出缓冲区，更新PRNG
 *  @return 返回TC_CRYPTO_SUCCESS（1）如果需要重新设定种子，则返回TC_CTR_PRNG_RESEED_REQ（-1）如果：ctx==NULL，out==NULL，outlen>=2^16
 *  @note 假设已为ctx调用tc_ctr_prng_init
 *  @param ctx IN/OUT——PRNG上下文
 *  @param additional_input IN——prng的附加输入（可以为空）
 *  @param additionallen IN—附加输入长度（字节）
 *  @param out IN/OUT—接收输出的缓冲区
 *  @param outlen IN—输出缓冲区的大小（字节）
 */
int tc_ctr_prng_generate(TCCtrPrng_t * const ctx,
			 uint8_t const * const additional_input,
			 unsigned int additionallen,
			 uint8_t * const out,
			 unsigned int outlen);

/**
 *  @brief CTR-PRNG非恒定过程将提供的PRNG上下文的内部状态归零
 *  @return 没有一个
 *  @param ctx IN/OUT——PRNG上下文
 */
void tc_ctr_prng_uninstantiate(TCCtrPrng_t * const ctx);

#ifdef __cplusplus
}
#endif

#endif /* __TC_CTR_PRNG_H__ */

