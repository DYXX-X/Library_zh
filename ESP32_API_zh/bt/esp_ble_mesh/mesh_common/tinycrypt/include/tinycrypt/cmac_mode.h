/*  cmac模式。h—CMAC实现的接口*/

/*
 *  英特尔公司版权所有（C）2017，保留所有权利
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
 * @brief CMAC实现的接口。
 *
 *  概述：CMAC是NIST在SP 800-38B中定义的，是使用分组密码计算MAC的标准算法。它可以计算任何长度的字节字符串的MAC。它在最终消息块的处理上与CBC-MAC不同；CMAC使用不同的技术来计算最终的消息块是完全大小还是仅部分大小，而CBC-MAC对这两种情况使用相同的技术。这种差异允许CMAC应用于可变长度消息，而CBC-MAC认证的所有消息必须具有相同的长度。
 *
 *  安全性：AES128-CMAC操作模式提供64位安全性以防冲突攻击。然而，请注意，外部攻击者在不知道MAC密钥的情况下无法自己生成标签。从这个意义上讲，为了攻击AES128-CMAC的冲突属性，外部攻击者需要合法用户的合作，以生成指数级高数量的标签（例如2^64），从而最终能够查找冲突并从中受益。作为额外的预防措施，当前实现允许在重新调用tc_cmac_setup（允许设置新密钥）之前最多调用2^48次tc_cmac_update函数，如SP 800-38B的附录B所示。
 *
 *  需要：AES-128
 *
 *  用法：此实现提供了一个“散点聚集”接口，以便可以在内存中分散在不同段中的消息上增量计算CMAC值。经验表明，这种类型的界面倾向于减少正确编程的负担。与所有对称密钥操作一样，它是面向会话的。
 *
 *           要开始CMAC会话，请使用tc_CMAC_setup使用加密密钥和缓冲区初始化结构tc_CMAC_struct。我们的实现总是假设AES密钥的大小与块密码块大小相同。一旦设置，该数据结构可用于许多CMAC计算。
 *
 *           使用密钥设置状态后，计算某些数据的CMAC需要三个步骤：
 *
 *           （1） 首先使用tc_cmac_init初始化新的cmac计算。（2） 接下来使用tc_CMAC_update将所有数据混合到CMAC计算状态。如果所有数据都驻留在一个数据段中，那么只需要一个tc_cmac_update调用；如果数据分散在n个数据段中的整个内存中，那么将需要n个调用。CMAC是顺序敏感的，能够检测交换字节的攻击，因此数据混入状态的顺序至关重要！（3） 混合消息的所有数据后，使用tc_cmac_final计算cmac标记值。
 *
 *           步骤（1）-（3）可以重复多次，只要您想对多条消息进行CMAC。在您必须更改密钥之前，实际限制为2^48 1K消息。
 *
 *           使用密钥计算CMAC后，最好销毁状态，以便攻击者无法恢复密钥；使用tccmacerase来实现这一点。
 */

#ifndef __BLE_MESH_TC_CMAC_MODE_H__
#define __BLE_MESH_TC_CMAC_MODE_H__

#include <tinycrypt/aes.h>

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 最后一个消息块的填充*/
#define TC_CMAC_PADDING 0x80

/* 结构tc_cmac_struct表示cmac计算的状态*/
typedef struct tc_cmac_struct {
    /* 初始化向量*/
    uint8_t iv[TC_AES_BLOCK_SIZE];
    /* 如果消息长度是block_size字节的倍数，则使用*/
    uint8_t K1[TC_AES_BLOCK_SIZE];
    /* 如果消息长度不是多个block_size字节，则使用*/
    uint8_t K2[TC_AES_BLOCK_SIZE];
    /* 放置未填充块的字节的位置*/
    uint8_t leftover[TC_AES_BLOCK_SIZE];
    /* 标识加密密钥*/
    unsigned int keyid;
    /* 下一个可用的剩余位置*/
    unsigned int leftover_offset;
    /* AES密钥计划*/
    TCAesKeySched_t sched;
    /* 在re-key之前对tc_cmac_update的调用*/
    uint64_t countdown;
} *TCCmacState_t;

/**
 * @brief 配置CMAC状态以使用给定的AES密钥
 * @return 配置CMAC状态后返回TC_CRYPTO_SUCCESS（1）如果：s==NULL或key==NULL，则返回TC_CRYPTO_FAIL（0）
 *
 * @param s IN/OUT——要设置的状态
 * @param key IN——要使用的密钥
 * @param sched IN—AES密钥计划
 */
int tc_cmac_setup(TCCmacState_t s, const uint8_t *key,
                  TCAesKeySched_t sched);

/**
 * @brief 清除CMAC状态
 * @return 配置CMAC状态后返回TC_CRYPTO_SUCCESS（1）如果：s==NULL，则返回TC_CRYPTO_FAIL（0）
 *
 * @param s IN/OUT—要擦除的状态
 */
int tc_cmac_erase(TCCmacState_t s);

/**
 * @brief 初始化新的CMAC计算
 * @return 初始化CMAC状态后返回TC_CRYPTO_SUCCESS（1）如果：s==NULL，则返回TC_CRYPTO_FAIL（0）
 *
 * @param s IN/OUT—要初始化的状态
 */
int tc_cmac_init(TCCmacState_t s);

/**
 * @brief 在下一个数据段上递增计算CMAC
 * @return 成功更新CMAC状态后，返回TC_CRYPTO_SUCCESS（1）。如果：s==NULL或如果数据==NULL（当dlen>0时），则返回TC_CRYPTO_FAIL（0）
 *
 * @param s IN/OUT——CMAC状态
 * @param data IN——MAC的下一个数据段
 * @param dlen IN—数据长度（字节）
 */
int tc_cmac_update(TCCmacState_t s, const uint8_t *data, size_t dlen);

/**
 * @brief 从CMAC状态生成标记
 * @return 成功生成标记后返回TC_CRYPTO_SUCCESS（1）如果：标记==NULL或s==NULL，则返回TC_CRYPTO_FAIL（0）
 *
 * @param tag OUT—CMAC标记
 * @param s IN——CMAC状态
 */
int tc_cmac_final(uint8_t *tag, TCCmacState_t s);

#ifdef __cplusplus
}
#endif

#endif /* __BLE_MESH_TC_CMAC_MODE_H__ */

