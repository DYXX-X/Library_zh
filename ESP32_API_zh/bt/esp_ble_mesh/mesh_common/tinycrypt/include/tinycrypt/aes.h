/* aes。h-到AES-128实现的TinyCrypt接口*/

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
 * @brief --AES-128实现的接口。
 *
 *  概述：AES-128是FIPS 197中规定的NIST批准的分组密码。分组密码是执行由固定长度数据集（也称为块）中的对称密钥指定的转换的确定性算法。
 *
 *  安全性：AES-128提供大约128位的安全性。
 *
 *  用法：1）调用tc_aes128_set_encrypt/decrypt_key设置密钥。
 *
 *              2） 调用tcaes_encrypt/decrypt处理数据。
 */

#ifndef __BLE_MESH_TC_AES_H__
#define __BLE_MESH_TC_AES_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define Nb (4)  /* 包含状态的列数（32位字）*/
#define Nk (4)  /* 包含密钥的32位字的数量*/
#define Nr (10) /* 轮数*/
#define TC_AES_BLOCK_SIZE (Nb*Nk)
#define TC_AES_KEY_SIZE (Nb*Nk)

typedef struct tc_aes_key_sched_struct {
    unsigned int words[Nb * (Nr + 1)];
} *TCAesKeySched_t;

/**
 *  @brief 设置AES-128加密密钥使用密钥k初始化s
 *  @return  返回TC_CRYPTO_SUCCESS（1）如果：s==NULL或k==NULL，则返回TC_CRYPTO_FAIL（0）
 *  @note       此实现跳过了大于128位的密钥所需的额外步骤，并且不得用于AES-192或AES-256密钥调度——有关详细信息，请参阅FIPS 197
 *  @param      s IN/OUT—初始化结构tc_aes_key_sched_struct
 *  @param      k IN—指向AES密钥
 */
int tc_aes128_set_encrypt_key(TCAesKeySched_t s, const uint8_t *k);

/**
 *  @brief AES-128加密程序根据密钥将缓冲区内的内容加密到缓冲区外；时间表s
 *  @note 假设s由aes_set_encrypt_key初始化；输出和输入点到16字节缓冲区
 *  @return  返回TC_CRYPTO_SUCCESS（1）如果：out==NULL或in==NULL或s==NULL，则返回TC_CRYPTO_FAIL（0）
 *  @param out IN/OUT—接收密文块的缓冲区
 *  @param in IN—要加密的明文块
 *  @param s IN—初始化的AES密钥计划
 */
int tc_aes_encrypt(uint8_t *out, const uint8_t *in,
                   const TCAesKeySched_t s);

/**
 *  @brief 设置AES-128解密密钥使用密钥k初始化s
 *  @return 返回TC_CRYPTO_SUCCESS（1）如果：s==NULL或k==NULL，则返回TC_CRYPTO_FAIL（0）
 *  @note       这是使用FIPS-197图12中记录的密码实现的直接逆密码，而不是图15中所示的等效逆密码
 *  @warning    此例程跳过大于128的密钥所需的其他步骤，并且不得用于AES-192或AES-256密钥计划——有关详细信息，请参阅FIPS 197
 *  @param s  IN/OUT—初始化结构tc_aes_key_sched_struct
 *  @param k  IN—指向AES密钥
 */
int tc_aes128_set_decrypt_key(TCAesKeySched_t s, const uint8_t *k);

/**
 *  @brief AES-128加密过程根据密钥调度将缓冲区中的解密到缓冲区中
 *  @return 返回TC_CRYPTO_SUCCESS（1）如果：out为NULL或in为NULL或s为NULL，则返回TC_CRYPTO_FAIL（0）
 *  @note   假设s由aes_set_encrypt_key out和in初始化，指向16字节缓冲区
 *  @param out IN/OUT—接收密文块的缓冲区
 *  @param in IN—要加密的明文块
 *  @param s IN—初始化的AES密钥计划
 */
int tc_aes_decrypt(uint8_t *out, const uint8_t *in,
                   const TCAesKeySched_t s);

#ifdef __cplusplus
}
#endif

#endif /* __BLE_MESH_TC_AES_H__ */

