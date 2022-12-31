/* hmac。h-HMAC实现的TinyCrypt接口*/

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
 * @brief HMAC实现的接口。
 *
 *  概述：HMAC是一种基于哈希函数的消息认证代码。TinyCrypt硬编码SHA-256作为哈希函数。基于哈希函数的消息认证代码也被称为密钥加密哈希函数，因为它执行由任意长度数据集中的密钥指定的转换为固定长度数据集（也称为标记）。
 *
 *  安全性：HMAC的安全性取决于密钥的长度和哈希函数的安全性。注意，HMAC原语比其对应的哈希函数受冲突攻击的影响小得多。
 *
 *  需要：SHA-256
 *
 *  用法：1）调用tc_hmac_set_key设置hmac密钥。
 *
 *              2） 在处理数据之前，调用tchmacinit初始化结构hashstate。
 *
 *              3） 调用tc_hmac_update处理下一个输入段；可以根据需要多次调用tc_hmac_update来处理输入的所有段；顺序很重要。
 *
 *              4） 调用tc_hmac_final输出标记。
 */

#ifndef __TC_HMAC_H__
#define __TC_HMAC_H__

#include <tinycrypt/sha256.h>

#ifdef __cplusplus
extern "C" {
#endif

struct tc_hmac_state_struct {
	/* h所需的内部状态*/
	struct tc_sha256_state_struct hash_state;
	/* HMAC密钥计划*/
	uint8_t key[2*TC_SHA256_BLOCK_SIZE];
};
typedef struct tc_hmac_state_struct *TCHmacState_t;

/**
 *  @brief HMAC设置密钥过程配置ctx以使用密钥
 *  @return 返回TC_CRYPTO_SUCCESS（1）如果ctx==NULL或key==NULL或key_size==0，则返回TC_CRYPTO_FAIL（0）
 * @param ctx IN/OUT—结构tc_hmac_state_struct到initial
 * @param key IN——要配置的HMAC密钥
 * @param key_size IN——HMAC密钥大小
 */
int tc_hmac_set_key(TCHmacState_t ctx, const uint8_t *key,
		    unsigned int key_size);

/**
 * @brief HMAC初始化过程初始化ctx以开始下一个HMAC操作
 * @return 返回TC_CRYPTO_SUCCESS（1）如果：ctx==NULL或key==NULL，则返回TC_CRYPTO_FAIL（0）
 * @param ctx IN/OUT--结构tc_hmac_state_struct缓冲区到init
 */
int tc_hmac_init(TCHmacState_t ctx);

/**
 *  @brief HMAC更新过程将数据寻址的data_length字节混合到状态
 *  @return 返回TC_CRYPTO_SUCCESS（1）如果：ctx==NULL或key==NULL，则返回TC_CRYPTO_FAIL（0）
 *  @note 假设状态已由tc_hmac_init初始化
 *  @param ctx IN/OUT——迄今为止HMAC计算的状态
 *  @param data IN——要合并到状态中的数据
 *  @param data_length IN—数据大小（字节）
 */
int tc_hmac_update(TCHmacState_t ctx, const void *data,
		   unsigned int data_length);

/**
 *  @brief HMAC最终过程将HMAC标记写入标记缓冲区
 *  @return 返回TC_CRYPTO_SUCCESS（1）如果：标记==NULL或ctx==NULL或键==NULL或taglen！=TC_SHA256_DIGEST_SIZE
 *  @note ctx在退出之前被擦除。不得更改/删除。
 *  @note 假设标记bufer至少为sizeof（hmac_tag_size（state））字节，状态已由tc_hmac_init初始化
 *  @param tag IN/OUT—接收计算的HMAC标记的缓冲区
 *  @param taglen IN—标记的大小（字节）
 *  @param ctx IN/OUT——计算标签的HMAC状态
 */
int tc_hmac_final(uint8_t *tag, unsigned int taglen, TCHmacState_t ctx);

#ifdef __cplusplus
}
#endif

#endif /*__TC_HMAC_H__*/

