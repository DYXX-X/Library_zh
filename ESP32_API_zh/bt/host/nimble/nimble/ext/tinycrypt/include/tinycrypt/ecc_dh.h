/* ecc_dh。h-到EC-DH实施的TinyCrypt接口*/

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

/* 英特尔公司版权所有（C）2017，保留所有权利。
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
 * @brief --与EC-DH实施的接口。
 *
 *  概述：此软件是EC-DH的实现。该实施使用NIST p-256曲线。
 *
 *  安全性：NIST p-256曲线提供了大约128位的安全性。
 */

#ifndef __TC_ECC_DH_H__
#define __TC_ECC_DH_H__

#include <tinycrypt/ecc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 创建公钥/私钥对。
 * @return 如果成功生成密钥对，则返回TC_CRYPTO_SUCCESS（1）；如果生成密钥对时出错，则返回TCP_CRYPTO_FAIL（0）
 *
 * @param p_public_key OUT——将用公钥填充。长度必须至少为曲线大小（字节）的2倍。对于曲线secp256r1，p_public_key的长度必须为64字节。
 * @param p_private_key OUT——将用私钥填充。必须与曲线顺序一样长（对于secp256r1，p_private_key必须为32字节长）。
 *
 * @note 侧信道对策：针对定时攻击增强的算法。
 * @warning 在调用uECC_make_key（）之前，必须设置加密安全的PRNG函数（使用uECC_set_rng（））。
 */
int uECC_make_key(uint8_t *p_public_key, uint8_t *p_private_key, uECC_Curve curve);

#ifdef ENABLE_TESTS

/**
 * @brief 创建给定特定d的公钥/私钥对。
 *
 * @note 此函数只能用于测试目的。有关实际应用程序，请参阅uECC_make_key（）函数。
 */
int uECC_make_key_with_d(uint8_t *p_public_key, uint8_t *p_private_key,
    			 unsigned int *d, uECC_Curve curve);
#endif

/**
 * @brief 根据您的密钥和其他人的公钥计算共享密钥。
 * @return 如果成功计算共享密钥，则返回TC_CRYPTO_SUCCESS（1）；否则返回TC_CRYPTO_FAIL（0）
 *
 * @param p_secret OUT——将用共享的秘密值填充。必须与曲线大小相同（对于曲线secp256r1，secret必须为32字节长。
 * @param p_public_key IN——远程方的公钥。
 * @param p_private_key IN——您的私钥。
 *
 * @warning 建议使用uECC_shared_secret（）的输出作为推荐密钥派生函数的输入（参见NIST SP 800-108），以生成加密安全的对称密钥。
 */
int uECC_shared_secret(const uint8_t *p_public_key, const uint8_t *p_private_key,
		       uint8_t *p_secret, uECC_Curve curve);

#ifdef __cplusplus
}
#endif

#endif /* __TC_ECC_DH_H__ */

