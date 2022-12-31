/* ecc_dh。h-到EC-DSA实施的TinyCrypt接口*/

/*
 * 版权所有（c）2014，Kenneth MacKay保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * *源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。
 *
 * *二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * 英特尔公司版权所有（C）2017，保留所有权利。
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
 * @brief --与EC-DSA实施的接口。
 *
 *  概述：此软件是EC-DSA的实现。该实施使用NIST p-256曲线。
 *
 *  安全性：NIST p-256曲线提供了大约128位的安全性。
 *
 *  用法：-要签名：计算要签名的数据的哈希（建议使用SHA-2），并将其与私钥和随机数一起传递给ecdsa\usign函数。必须使用新的不可预测随机数来生成每个新签名。
 *          -验证签名：使用与签名者相同的哈希计算签名数据的哈希，并将其与签名者的公钥和签名值（r和s）一起传递给此函数。
 */

#ifndef __TC_ECC_DSA_H__
#define __TC_ECC_DSA_H__

#include <tinycrypt/ecc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 为给定哈希值生成ECDSA签名。
 * @return 如果生成的签名成功，则返回TC_CRYPTO_SUCCESS（1）。
 *
 * @param p_private_key IN——您的私钥。
 * @param p_message_hash IN——要签名的消息的哈希。
 * @param p_hash_size IN——p_message_hash的大小（字节）。
 * @param p_signature OUT——将用签名值填充。曲线长度必须至少为2个（对于secp256r1，签名长度必须为64字节）。
 *
 * @warning 在调用uECC_sign（）之前，必须设置加密安全的PRNG函数（使用uECC_set_rng（））。
 * @note 用法：计算要签名的数据的哈希（建议使用SHA-2），并将其与私钥一起传递给此函数。
 * @note 侧信道对策：针对定时攻击增强的算法。
 */
int uECC_sign(const uint8_t *p_private_key, const uint8_t *p_message_hash,
	      unsigned p_hash_size, uint8_t *p_signature, uECC_Curve curve);

#ifdef ENABLE_TESTS
/*
 * 此函数应仅用于测试目的。有关实际应用程序，请参阅uECC_sign（）函数。
 */
int uECC_sign_with_k(const uint8_t *private_key, const uint8_t *message_hash,
		     unsigned int hash_size, uECC_word_t *k, uint8_t *signature,
		     uECC_Curve curve);
#endif

/**
 * @brief 验证ECDSA签名。
 * @return 如果签名有效，返回TC_SUCCESS（1）；如果签名无效，返回TC_FAIL（0）。
 *
 * @param p_public_key IN——签名者的公钥。
 * @param p_message_hash IN——签名数据的哈希。
 * @param p_hash_size IN——p_message_hash的大小（字节）。
 * @param p_signature IN——签名值。
 *
 * @note 用法：使用与签名者相同的哈希计算签名数据的哈希，并将其与签名者的公钥和签名值（hash_size和signature）一起传递给此函数。
 */
int uECC_verify(const uint8_t *p_public_key, const uint8_t *p_message_hash,
		unsigned int p_hash_size, const uint8_t *p_signature, uECC_Curve curve);

#ifdef __cplusplus
}
#endif

#endif /* __TC_ECC_DSA_H__ */

