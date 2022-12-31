/*
 *  版权所有（c）2017，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread库的顶级DNS函数。
 */

#ifndef OPENTHREAD_DNS_H_
#define OPENTHREAD_DNS_H_

#include <stdint.h>

#include <openthread/error.h>
#include <openthread/instance.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api dns
 *
 * @brief 此模块包括控制DNS通信的功能。
 *
 * @{
 *
 */

#define OT_DNS_MAX_NAME_SIZE 255 ///<最大名称字符串大小（包括字符串末尾的空字符）。

#define OT_DNS_MAX_LABEL_SIZE 64 ///<最大标签字符串大小（包括字符串末尾的空字符）。

#define OT_DNS_TXT_KEY_MIN_LENGTH 1 ///<TXT记录密钥串的最小长度（RFC 6763-第6.4节）。

#define OT_DNS_TXT_KEY_MAX_LENGTH 9 ///<TXT记录密钥串的建议最大长度（RFC 6763-第6.4节）。

/**
 * 该结构表示表示密钥/值对的TXT记录条目（RFC 6763-第6.3节）。
 *
 * “mKey”和“mValue”指向的字符串缓冲区必须保持不变，并且在将此类结构的实例传递给OpenThread（作为“otSrpClientService”实例的一部分）后保持不变。
 *
 * 在“otSrpClientService”中使用一个“otDnsTxtEntry”条目数组来指定完整的TXT记录（条目列表）。
 *
 */
typedef struct otDnsTxtEntry
{
    /**
     * TXT记录密钥字符串。
     *
     * 如果“mKey”不为NULL，则它必须是以空结尾的C字符串。该条目被视为键/值对，“mValue”缓冲区提供值。
     *   -条目编码如下：
     *        -一个字符串长度字节，后跟“key=value”格式（不带引号）。
              -在这种情况下，总编码长度必须小于或等于255字节。
     *   -如果`mValue`为NULL，则key被视为布尔属性，并编码为“key”（没有`=`）。
     *   -如果`mValue`不为NULL，但`mValueLength`为零，则将其视为空值并编码为“key=”。
     *
     * 如果“mKey”为NULL，则“mValue”缓冲区被视为已编码的TXT-DATA，并按DNS消息中的原样附加。
     *
     */
    const char *   mKey;
    const uint8_t *mValue;       ///<TXT记录值或已编码的TXT-DATA（取决于“mKey”）。
    uint16_t       mValueLength; ///<“mValue”缓冲区中的字节数。
} otDnsTxtEntry;

/**
 * 此结构表示TXT记录整数（键/值对）的迭代器。
 *
 * 此结构中的数据字段供OpenThread核心使用，调用者不应读取或更改它们。
 *
 */
typedef struct otDnsTxtEntryIterator
{
    const void *mPtr;
    uint16_t    mData[2];
    char        mChar[OT_DNS_TXT_KEY_MAX_LENGTH + 1];
} otDnsTxtEntryIterator;

/**
 * 此函数初始化TXT记录迭代器。
 *
 * The buffer pointer @p aTxtData及其内容在使用@p aIterator对象时必须保持不变。
 *
 * @param[in] aIterator       指向要初始化的迭代器的指针（不能为空）。
 * @param[in] aTxtData        指向包含编码TXT数据的缓冲区的指针。
 * @param[in] aTxtDataLength  @p aTxtData的长度（字节数）。
 *
 */
void otDnsInitTxtEntryIterator(otDnsTxtEntryIterator *aIterator, const uint8_t *aTxtData, uint16_t aTxtDataLength);

/**
 * 此函数解析迭代器中的TXT数据，并获取下一个TXT记录条目（键/值对）。
 *
 * The @p 在调用此函数之前，必须使用“otDnsInitTxtEntry迭代器（）”初始化迭代器，用于初始化迭代程序的TXT数据缓冲区必须保持不变。否则，此函数的行为未定义。
 *
 * 如果解析的密钥字符串长度小于或等于`OT_DNS_TXT_key_MAX_length`（建议的最大密钥长度）
 * the key string is returned in `mKey` in @p a进入。但如果密钥较长，则“mKey”设置为NULL，并且整个编码的TXT条目字符串以“mValue”和“mValueLength”返回。
 *
 * @param[in]  aIterator   迭代器的指针（不能为空）。
 * @param[out] aEntry      指向`otDnsTxtEntry`结构的指针，用于输出已解析/读取的条目（不得为NULL）。
 *
 * @retval OT_ERROR_NONE已成功解析下一个条目@p aEntry已更新。
 * @retval OT_ERROR_NOT_FOUND TXT数据中没有更多条目。
 * @retval OT_ERROR_PARSE@p aIterator的TXT数据格式不正确。
 *
 */
otError otDnsGetNextTxtEntry(otDnsTxtEntryIterator *aIterator, otDnsTxtEntry *aEntry);

/**
 * 此功能启用/禁用“DNS名称压缩”模式。
 *
 * 默认情况下，DNS名称压缩已启用。禁用时，DNS名称将作为完整名称附加，并且从不压缩。这适用于OpenThread的DNS和SRP客户端/服务器模块。
 *
 * 这仅用于测试，并且在启用“OPENTHREAD_COONFIG_REFERENCE_DEVICE_ENABLE”配置时可用。
 *
 * 注意，在使用“OPENTHREAD_CONFIG_MULTIPLE_INSTANCE_ENABLE”的情况下，此模式适用于所有OPENTHREAD实例（即，调用此函数启用/禁用所有OPENTHREAD实例上的压缩模式）。
 *
 * @param[in] aEnabled   TRUE表示启用“DNS名称压缩”模式，FALSE表示禁用。
 *
 */
void otDnsSetNameCompressionEnabled(bool aEnabled);

/**
 * 此函数指示是否启用“DNS名称压缩”模式。
 *
 * 这仅用于测试，并且在启用“OPENTHREAD_COONFIG_REFERENCE_DEVICE_ENABLE”配置时可用。
 *
 * @returns 如果启用了“DNS名称压缩”模式，则为TRUE，否则为FALSE。
 *
 */
bool otDnsIsNameCompressionEnabled(void);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_DNS_H_

