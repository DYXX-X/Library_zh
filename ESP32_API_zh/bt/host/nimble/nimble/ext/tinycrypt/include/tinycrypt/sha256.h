/* sha256.h-到SHA-256实现的TinyCrypt接口*/

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
 * @brief SHA-256实现的接口。
 *
 *  概述：SHA-256是FIPS 180中规定的NIST批准的加密哈希算法。哈希算法将任意大小的数据映射到固定长度的数据。
 *
 *  安全性：SHA-256针对冲突攻击提供128位安全性，针对预镜像攻击提供256位安全性。SHA-256的行为不像随机预言机，但如果正在散列的字符串在散列之前是无前缀编码的，则可以将其用作一个预言机。
 *
 *  用法：1）在哈希新字符串之前，调用tc_sha256_init初始化结构tc_sha256 _state_struct。
 *
 *              2） 调用tc_sha256_update来散列下一个字符串段；可以根据需要多次调用tc_sha256_update来散列字符串的所有段；顺序很重要。
 *
 *              3） 调用tcsha256final以输出哈希操作的摘要。
 */

#ifndef __TC_SHA256_H__
#define __TC_SHA256_H__

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TC_SHA256_BLOCK_SIZE (64)
#define TC_SHA256_DIGEST_SIZE (32)
#define TC_SHA256_STATE_BLOCKS (TC_SHA256_DIGEST_SIZE/4)

struct tc_sha256_state_struct {
	unsigned int iv[TC_SHA256_STATE_BLOCKS];
	uint64_t bits_hashed;
	uint8_t leftover[TC_SHA256_BLOCK_SIZE];
	size_t leftover_offset;
};

typedef struct tc_sha256_state_struct *TCSha256State_t;

/**
 *  @brief SHA256初始化过程初始化
 *  @return 返回TC_CRYPTO_SUCCESS（1）如果s==NULL，则返回TC_CRYPTO_FAIL（0）
 *  @param s Sha256状态结构
 */
int tc_sha256_init(TCSha256State_t s);

/**
 *  @brief SHA256更新过程将数据寻址的data_length字节哈希为状态
 *  @return 返回TC_CRYPTO_SUCCESS（1）如果：s==NULL，s->iv==NULL，data==NULL，则返回TC_CRYPTO_FAIL（0）
 *  @note 假设s已由tc_sha256_init初始化
 *  @warning 状态缓冲区“剩余”在处理后留在内存中。如果您的应用程序希望在此缓冲区中有敏感数据，请在处理完数据后提醒删除它
 *  @param s Sha256状态结构
 *  @param data 消息到哈希
 *  @param datalen 要哈希的消息长度
 */
int tc_sha256_update (TCSha256State_t s, const uint8_t *data, size_t datalen);

/**
 *  @brief SHA256最终过程将完成的哈希计算插入摘要
 *  @return 返回TC_CRYPTO_SUCCESS（1）如果：s==NULL，s->iv==NULL，摘要==NULL，则返回TC_CRYPTO_FAIL（0）
 *  @note 假设：s已由tc_sha256_init摘要初始化，至少指向tc_sha256_digest_SIZE字节
 *  @warning 状态缓冲区“剩余”在处理后留在内存中。如果您的应用程序希望在此缓冲区中有敏感数据，请在处理完数据后提醒删除它
 *  @param digest 无符号八位整数
 *  @param Sha256 状态结构
 */
int tc_sha256_final(uint8_t *digest, TCSha256State_t s);

#ifdef __cplusplus
}
#endif

#endif /* __TC_SHA256_H__ */

