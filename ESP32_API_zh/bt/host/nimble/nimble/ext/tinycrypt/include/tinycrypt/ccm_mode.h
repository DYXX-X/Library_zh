/* ccm_模式。h-CCM模式实现的TinyCrypt接口*/

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
 * @brief CCM偌阋执钴锶息。
 *
 *  概述：CCM（用于“带CBC-MAC的计数器”）模式是SP 800-38C中定义的NIST批准的操作模式。
 *
 *            TinyCrypt CCM实现接受：
 *
 *            1） 非空有效载荷和相关数据（它对有效载荷进行加密和认证，并对相关数据进行认证）；2） 非空有效载荷和空相关数据（它对有效载荷进行加密和认证）；3） 非空关联数据和空有效负载（它退化为关联数据的身份验证模式）。
 *
 *            TinyCrypt CCM实现接受0到（2^16-2^8）字节之间任何长度的关联数据。
 *
 *  安全性：mac长度参数是评估针对冲突攻击的安全性的一个重要参数（旨在查找产生相同身份验证标签的不同消息）。TinyCrypt CCM实现接受4到16之间的任何偶数，如SP 800-38C中所建议的。
 *
 *            RFC-3610也指定了CCM，提出了一些相关的安全建议，例如：建议大多数应用程序使用大于8的mac长度。此外，使用相同密钥加密的两个不同消息使用相同的随机数会破坏CCM模式的安全性。
 *
 *  需要：AES-128
 *
 *  用法：1）调用tc_ccm_config进行配置。
 *
 *            2） 调用tccmmodeencrypt加密数据并生成标记。
 *
 *            3） 调用tccmmodedecrypt来解密数据并验证标记。
 */

#ifndef __TC_CCM_MODE_H__
#define __TC_CCM_MODE_H__

#include <tinycrypt/aes.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 最大附加验证大小（字节）：2^16-2^8=65280*/
#define TC_CCM_AAD_MAX_BYTES 0xff00

/* 最大邮件大小（字节）：2^（8L）=2^16=65536*/
#define TC_CCM_PAYLOAD_MAX_BYTES 0x10000

/* 结构tc_ccm_mode_struct表示ccm计算的状态*/
typedef struct tc_ccm_mode_struct {
	TCAesKeySched_t sched; /* AES密钥计划*/
	uint8_t *nonce; /* CCM所需的nonce*/
	unsigned int mlen; /* mac长度（字节）（SP-800 38C中的参数t）*/
} *TCCcmMode_t;

/**
 * @brief CCM组态镲唔
 * @return 返回TC_CRYPTO_SUCCESS（1）如果：c==NULL或sched==NULL或nonce==NULL或mlen！={4, 6, 8, 10, 12, 16}
 * @param c --CCM状态
 * @param sched IN—AES密钥计划
 * @param nonce IN-当前
 * @param nlen --随机数长度（字节）
 * @param mlen --mac长度（字节）（SP-800 38C中的参数t）
 */
int tc_ccm_config(TCCcmMode_t c, TCAesKeySched_t sched, uint8_t *nonce,
		  unsigned int nlen, unsigned int mlen);

/**
 * @brief CCM标记生成和加密程序
 * @return 返回TC_CRYPTO_SUCCESS（1）如果：out==NULL或c==NULL（（plen>0）且（有效负载==NULL））或（alen>0，且（associated_data==NULL
 *
 * @param out OUT—加密数据
 * @param olen IN—输出长度（字节）
 * @param associated_data IN——关联数据
 * @param alen IN—相关数据长度（字节）
 * @param payload IN——有效载荷
 * @param plen IN—有效载荷长度（字节）
 * @param c IN—CCM状态
 *
 * @note: 输出缓冲区的长度应至少为（plen+c->mlen）字节。
 *
 * @note: 加密序列b的格式如下：b=[FLAGS|nonce|counter]，其中：FLAGS为1字节长，nonce为13字节长，counter为2字节长。字节FLAGS由以下8位组成：0-2位：用于表示q-1 3-7btis的值：始终为0
 *
 * @note: 用于身份验证的序列b的格式如下：b=[FLAGS|nonce|length（mac length）]，其中：FLAGS为1字节长nonce为13字节长length（mac length）为2字节长字节FLAGS由以下8位组成：0-2位：用于表示q-1的值3-5位：mac length（编码为：（mlen-2）/2）6:Adata（如果alen==0，则为0，否则为1）7:始终为0
 */
int tc_ccm_generation_encryption(uint8_t *out, unsigned int olen,
			   	 const uint8_t *associated_data,
			   	 unsigned int alen, const uint8_t *payload,
				 unsigned int plen, TCCcmMode_t c);

/**
 * @brief CCM解密和标签验证程序
 * @return 返回TC_CRYPTO_SUCCESS（1）如果：out==NULL或c==NULL（（plen>0）且（有效负载==NULL））或（alen>0，且（associated_data==NULL
 *
 * @param out OUT—解密数据
 * @param associated_data IN——关联数据
 * @param alen IN—相关数据长度（字节）
 * @param payload IN——有效载荷
 * @param plen IN—有效载荷长度（字节）
 * @param c IN—CCM状态
 *
 * @note: 输出缓冲区的长度应至少为（plen-c->mlen）字节。
 *
 * @note: 加密序列b的格式如下：b=[FLAGS|nonce|counter]，其中：FLAGS为1字节长，nonce为13字节长，counter为2字节长。字节FLAGS由以下8位组成：0-2位：用于表示q-1 3-7btis的值：始终为0
 *
 * @note: 用于身份验证的序列b的格式如下：b=[FLAGS|nonce|length（mac length）]，其中：FLAGS为1字节长nonce为13字节长length（mac length）为2字节长字节FLAGS由以下8位组成：0-2位：用于表示q-1的值3-5位：mac length（编码为：（mlen-2）/2）6:Adata（如果alen==0，则为0，否则为1）7:始终为0
 */
int tc_ccm_decryption_verification(uint8_t *out, unsigned int olen,
				   const uint8_t *associated_data,
				   unsigned int alen, const uint8_t *payload, unsigned int plen,
				   TCCcmMode_t c);

#ifdef __cplusplus
}
#endif

#endif /* __TC_CCM_MODE_H__ */

