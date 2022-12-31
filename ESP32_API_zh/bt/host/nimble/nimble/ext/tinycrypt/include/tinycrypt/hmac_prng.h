/* hmac_ prng。h-HMAC-PRNG实现的TinyCrypt接口*/

/*
 *  英特尔公司版权所有（C）2017，保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 *    -源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。
 *
 *    -二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。
 *
 *    -未经事先书面许可，不得使用“英特尔公司”的名称或其贡献者的名称来支持或推广源自此软件的产品。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief HMAC-PRNG实现的接口。
 *
 *  概述：伪随机数生成器（PRNG）生成的数字序列的分布与真实随机数序列的分布接近。NIST特别出版物800-90A规定了几种生成伪随机数序列的机制，包括基于HMAC的HMAC-PRNG机制。TinyCrypt通过NIST SP 800-90A规范的某些修改实现HMAC-PRNG。
 *
 *  安全性：加密安全的PRNG取决于熵源的存在，以提供真正的随机种子，以及用作构建块的原语（HMAC和SHA256，TinyCrypt）的安全性。
 *
 *              NIST SP 800-90A标准允许空个性化，而TinyCrypt要求非空个性化。这是因为个性化字符串（例如，与时间戳连接的主机名）很容易计算，并且可能是防止熵源失败的最后一道防线。
 *
 *  需要：-SHA-256
 *              - HMAC
 *
 *  用法：1）调用tc_hmac_prng_init设置hmac密钥并处理个性化数据。
 *
 *              2） 调用tchmacprngreseed来处理种子和其他输入。
 *
 *              3） 调用tchmacprnggenerate输出伪随机数据。
 */

#ifndef __TC_HMAC_PRNG_H__
#define __TC_HMAC_PRNG_H__

#include <tinycrypt/sha256.h>
#include <tinycrypt/hmac.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TC_HMAC_PRNG_RESEED_REQ -1

struct tc_hmac_prng_struct {
	/* 此PRNG的HMAC实例*/
	struct tc_hmac_state_struct h;
	/* PRNG键*/
	uint8_t key[TC_SHA256_DIGEST_SIZE];
	/* PRNG状态*/
	uint8_t v[TC_SHA256_DIGEST_SIZE];
	/* 对tc_hmac_prng_generate的调用在重新播种之前保留*/
	unsigned int countdown;
};

typedef struct tc_hmac_prng_struct *TCHmacPrng_t;

/**
 *  @brief HMAC-PRNG初始化过程使用个性化初始化PRNG，禁用tc_HMAC_PRNG_generate
 *  @return 返回TC_CRYPTO_SUCCESS（1）如果：prng==NULL，个性化==NULL，plen>MAX_plen，则返回TC_CRYPTO_FAIL（0）
 *  @note 假设：个性化！=无效的。个性化是平台唯一的字符串（例如主机名），是防止熵源失败的最后一道防线
 *  @warning    NIST SP 800-90A在初始化期间指定了3项作为种子材料：熵种子、个性化和可选随机数。TinyCrypts需要一个非空的个性化设置（这很容易计算），并间接地需要一个熵种子（因为在init之后强制调用重种子函数）
 *  @param prng IN/OUT—要初始化的PRNG状态
 *  @param personalization IN--个性化字符串
 *  @param plen IN--个性化长度（字节）
 */
int tc_hmac_prng_init(TCHmacPrng_t prng,
		      const uint8_t *personalization,
		      unsigned int plen);

/**
 *  @brief HMAC-PRNG重新播种程序将种子混合到PRNG中，启用tc_HMAC_PRNG_generate
 *  @return 返回TC_CRYPTO_SUCCESS（1）如果：prng==NULL，seed==NULL、seedlen<MIN_SLEN、seendlen>MAX_SLEN，additional_input！=（常量uint8_t）0&&additionallen==0，additional_input！=（常量uint8_t）0&&附加长度>最大长度
 *  @note 假设：已为prng调用-tc_hmac_prng_init
 *              -种子具有足够的熵。
 *
 *  @param prng IN/OUT——PRNG状态
 *  @param seed IN——混合到prng中的熵
 *  @param seedlen IN—种子长度（字节）
 *  @param additional_input IN——prng的附加输入
 *  @param additionallen IN—附加输入长度（字节）
 */
int tc_hmac_prng_reseed(TCHmacPrng_t prng, const uint8_t *seed,
			unsigned int seedlen, const uint8_t *additional_input,
			unsigned int additionallen);

/**
 *  @brief HMAC-PRNG生成过程将输出伪随机字节生成到输出缓冲区，更新PRNG
 *  @return 返回TC_CRYPTO_SUCCESS（1）如果需要重新设定种子，则返回TC_HMAC_PRNG_RESEED_REQ（-1）如果：out==NULL，PRNG==NULL，outlen==0，outlen>=MAX_out
 *  @note 假设已为prng调用tc_hmac_prng_init
 *  @param out IN/OUT—接收输出的缓冲区
 *  @param outlen IN—输出缓冲区的大小（字节）
 *  @param prng IN/OUT——PRNG状态
 */
int tc_hmac_prng_generate(uint8_t *out, unsigned int outlen, TCHmacPrng_t prng);

#ifdef __cplusplus
}
#endif

#endif /* __TC_HMAC_PRNG_H__ */

