/* cbc模式。h-到CBC模式实现的TinyCrypt接口*/

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
 * @brief CBC模式实现的接口。
 *
 *  概述：CBC（用于“密码块链接”）模式是NIST批准的操作模式，在SP 800-38a中定义。它可以与任何分组密码一起使用，以提供长度为基础分组密码block_size的倍数的字符串的机密性。TinyCrypt硬编码AES作为分组密码。
 *
 *  安全性：CBC模式提供了数据保密性，因为在单个密钥下加密的最大块数q满足q<2^63，这不是一个实际约束（当q==2^56时，替换加密被认为是一个好的做法）。CBC模式不提供数据完整性。
 *
 *            CBC模式假设输入到tc_CBC_mode_encrypt的IV值是随机生成的。TinyCrypt库提供HMAC-PRNG模块，用于生成合适的IV。其他生成IV的方法是可以接受的，前提是生成的IV的值对任何对手来说都是随机的，包括对系统设计完全了解的人。
 *
 *            CBC模式的安全性所依赖的随机性是IV的不可预测性。由于它是不可预测的，这意味着在实践中，CBC模式要求IV以某种方式与密文一起存储，以恢复明文。
 *
 *            TinyCrypt CBC加密在密文前面加上IV，因为这提供了更有效的（很少缓冲区）解密。因此，tc_cbc_mode_encrypt假设密文缓冲区总是比明文缓冲区大16字节。
 *
 *  需要：AES-128
 *
 *  用法：1）调用tc_cbc_mode_encrypt加密数据。
 *
 *            2） 调用tc_cbc_mode_decrypt来解密数据。
 *
 */

#ifndef __TC_CBC_MODE_H__
#define __TC_CBC_MODE_H__

#include <tinycrypt/aes.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @brief CBC加密程序CBC使用提供的加密密钥计划将输入缓冲区的输入字节加密到输出缓冲区中，并在iv到out之前
 *  @return 返回TC_CRYPTO_SUCCESS（1）如果：out==NULL或in==NULL或ctr==NULL或sched==NULL或inlen==0或（inlen%TC_AES_BLOCK_SIZE），则返回TC_CRYPTO_FAIL（0）！=0或（outlen%TC_AES_BLOCK_SIZE）！=0或outren！=输入+TC_AES_BLOCK_SIZE
 *  @note 假设：-sched已由aes_set_encrypt_key配置
 *              -iv包含一个16字节的随机字符串
 *              -输出缓冲区足够大，可以容纳密文+iv
 *              -out缓冲区是一个连续的缓冲区
 *              -in保存明文，是一个连续缓冲区
 *              -inlen给出in缓冲区中的字节数
 *  @param out IN/OUT—接收密文的缓冲区
 *  @param outlen IN——密文缓冲区的长度（字节）
 *  @param in IN—要加密的明文
 *  @param inlen IN—明文缓冲区的长度（字节）
 *  @param iv IN—此加密/解密的IV
 *  @param sched IN--此加密的AES密钥计划
 */
int tc_cbc_mode_encrypt(uint8_t *out, unsigned int outlen, const uint8_t *in,
			unsigned int inlen, const uint8_t *iv,
			const TCAesKeySched_t sched);

/**
 * @brief CBC解密过程CBC使用提供的加密密钥调度表将输入缓冲区的输入字节解密到输出缓冲区
 * @return 返回TC_CRYPTO_SUCCESS（1）如果：out==NULL或in==NULL或sched==NULL或inlen==0或outlen==0或（inlen%TC_AES_BLOCK_SIZE），则返回TC_CRYPTO_FAIL（0）！=0或（outlen%TC_AES_BLOCK_SIZE）！=0或outren！=输入+TC_AES_BLOCK_SIZE
 * @note 假设：-in==iv+密文，即iv和密文是连续的。这允许一种非常有效的解密算法，否则这是不可能的
 *              -sched由aes_set-decrypt_key配置
 *              -输出缓冲区足够大，可以容纳解密的明文，并且是一个连续缓冲区
 *              -inlen给出in缓冲区中的字节数
 * @param out IN/OUT—接收解密数据的缓冲区
 * @param outlen IN—明文缓冲区的长度（字节）
 * @param in IN——要解密的密文，包括IV
 * @param inlen IN——密文缓冲区的长度（字节）
 * @param iv IN—此加密/解密的IV
 * @param sched IN--此解密的AES密钥计划
 *
 */
int tc_cbc_mode_decrypt(uint8_t *out, unsigned int outlen, const uint8_t *in,
			unsigned int inlen, const uint8_t *iv,
			const TCAesKeySched_t sched);

#ifdef __cplusplus
}
#endif

#endif /* __TC_CBC_MODE_H__ */

