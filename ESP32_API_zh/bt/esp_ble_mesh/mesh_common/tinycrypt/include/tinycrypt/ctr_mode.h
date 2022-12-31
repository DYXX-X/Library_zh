/* ctr_mode。h-TinyCrypt接口至CTR模式*/

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
 * @brief CTR模式接口。
 *
 *  概述：CTR（发音为“计数器”）模式是SP 800-38a中定义的NIST批准的操作模式。它可以与任何分组密码一起使用，以提供任何长度的字符串的机密性。TinyCrypt硬编码AES128作为分组密码。
 *
 *  安全性：CTR模式只有在计数器值从未使用同一加密密钥时才能实现保密性。如果反反复复，那么对手可能会击败该计划。
 *
 *             确保不同计数器值的常用方法是将计数器初始化为给定值（例如，0），并在每次加密新块时增加计数器值。这自然会对可以使用相同密钥加密的块的数量q产生限制：q<2^（计数器大小）。
 *
 *             TinyCrypt使用32位计数器。这意味着在2^32块加密之后，计数器将被重新使用（从而失去CBC安全性）。对于大多数以受限设备为目标的应用程序，2^32块加密应该足够了。用于加密更多块的应用程序必须在2^32块加密后替换密钥。
 *
 *             CTR模式不提供数据完整性。
 *
 *  需要：AES-128
 *
 *  用法：1）调用tc_ctr_mode处理要加密/解密的数据。
 *
 */

#ifndef __BLE_MESH_TC_CTR_MODE_H__
#define __BLE_MESH_TC_CTR_MODE_H__

#include <tinycrypt/aes.h>
#include <tinycrypt/constants.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @brief CTR模式加密/解密程序。CTR模式将输入字节从缓冲区加密（或解密）到输出缓冲区
 *  @return 返回TC_CRYPTO_SUCCESS（1）如果：out==NULL或in==NULL或ctr==NULL或sched==NULL或inlen==0或outren==0或inlen！=在外面的
 *  @note 假设：-ctr中的当前值未与sched一起使用
 *              -out指向inlen字节
 *              -in点到inlen字节
 *              -ctr是littleEndian格式的整数计数器
 *              -sched由aes_set_encrypt_key初始化
 * @param out OUT——生成的密文（明文）
 * @param outlen IN——密文缓冲区的长度（字节）
 * @param in IN—要加密（或解密）的数据
 * @param inlen IN—输入数据的长度（字节）
 * @param ctr IN/OUT——当前计数器值
 * @param sched IN—初始化的AES密钥计划
 */
int tc_ctr_mode(uint8_t *out, unsigned int outlen, const uint8_t *in,
                unsigned int inlen, uint8_t *ctr, const TCAesKeySched_t sched);

#ifdef __cplusplus
}
#endif

#endif /* __BLE_MESH_TC_CTR_MODE_H__ */

