/*
 *  版权所有（c）2021，The OpenThread Authors。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread SRP（服务注册协议）客户端缓冲区和服务池。
 */

#ifndef OPENTHREAD_SRP_CLIENT_BUFFERS_H_
#define OPENTHREAD_SRP_CLIENT_BUFFERS_H_

#include <openthread/dns.h>
#include <openthread/srp_client.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api srp
 *
 * @brief 该模块包括SRP客户端缓冲区和服务池的功能。
 *
 * @{
 *
 * 此模块中的功能仅在启用OPENTHREAD_CONFIG_SRP_CLIENT_BUFFERS_ENABLE功能时可用。
 *
 */

/**
 * 此结构表示SRP客户端服务池条目。
 *
 */
typedef struct otSrpClientBuffersServiceEntry
{
    otSrpClientService mService;  ///<SRP客户端服务结构。
    otDnsTxtEntry      mTxtEntry; ///<SRP客户端TXT条目。
} otSrpClientBuffersServiceEntry;

/**
 * 此函数获取用于SRP客户端主机名的字符串缓冲区。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[out] aSize      指向变量的指针，用于返回字符串缓冲区的大小（字节数）（不得为NULL）。
 *
 * @returns 用于SRP客户端主机名的字符缓冲区指针。
 *
 */
char *otSrpClientBuffersGetHostNameString(otInstance *aInstance, uint16_t *aSize);

/**
 * 此函数获取要用作SRP客户端主机地址列表的IPv6地址项数组。
 *
 * @param[in]  aInstance     指向OpenThread实例的指针。
 * @param[out] aArrayLength  指向一个变量的指针，用于返回数组长度，即数组中IPv6地址项的数量（不得为空）。
 *
 * @returns 指向“otIp6Address”条目数组的指针（条目数以@p aArrayLength返回）。
 *
 */
otIp6Address *otSrpClientBuffersGetHostAddressesArray(otInstance *aInstance, uint8_t *aArrayLength);

/**
 * 此函数从池中分配新的服务条目。
 *
 * 返回的服务条目实例将按如下方式初始化：
 *
 *  -“mService。mName”将指向已分配的字符串缓冲区，该缓冲区可以使用函数“otSrpClientBuffersGetServiceEntryServiceNameString（）”检索。
 *  -“mService。mInstanceName”将指向已分配的字符串缓冲区，该缓冲区可以使用函数“otSrpClientBuffersGetServiceEntryInstanceNameString（）”检索。
 *  -“mService。mSubTypeLabels`指向从`otSrpClientBuffersGetSubTypeLabelsArray（）`返回的数组。
 *  -“mService。mTxtEntries”将指向“mTxtEntry”。
 *  -“mService。mNumTxtEntries`将设置为1。
 *  -其他“mService”字段（端口、优先级、权重）设置为零。
 *  -`mTxt条目。mKey`设置为NULL（值被视为已编码）。
 *  -`mTxt条目。mValue”将指向可使用函数“otSrpClientBuffersGetServiceEntryTxtBuffer（）”检索的已分配缓冲区。
 *  -`mTxt条目。mValueLength`设置为零。
 *  -所有相关的数据/字符串缓冲区和数组都清零。
 *
 * @param[in] aInstance   指向OpenThread实例的指针。
 *
 * @returns 指向新分配的服务项的指针，如果池中没有更多可用项，则为NULL。
 *
 */
otSrpClientBuffersServiceEntry *otSrpClientBuffersAllocateService(otInstance *aInstance);

/**
 * 此函数释放以前分配的服务条目。
 *
 * The @p aService之前必须使用“otSrpClientBuffersAllocateService（）”分配，但尚未释放。否则，此函数的行为未定义。
 *
 * @param[in] aInstance   指向OpenThread实例的指针。
 * @param[in] aService    指向要释放的服务项的指针（不能为空）。
 *
 */
void otSrpClientBuffersFreeService(otInstance *aInstance, otSrpClientBuffersServiceEntry *aService);

/**
 * 此函数释放所有以前分配的服务条目。
 *
 * @param[in] aInstance   指向OpenThread实例的指针。
 *
 */
void otSrpClientBuffersFreeAllServices(otInstance *aInstance);

/**
 * 此函数从服务条目中获取服务名称的字符串缓冲区。
 *
 * @param[in]  aEntry   指向先前分配的服务项的指针（不能为空）。
 * @param[out] aSize    指向变量的指针，用于返回字符串缓冲区的大小（字节数）（不得为NULL）。
 *
 * @returns 指向字符串缓冲区的指针。
 *
 */
char *otSrpClientBuffersGetServiceEntryServiceNameString(otSrpClientBuffersServiceEntry *aEntry, uint16_t *aSize);

/**
 * 此函数从服务条目获取服务实例名称的字符串缓冲区。
 *
 * @param[in]  aEntry   指向先前分配的服务项的指针（不能为空）。
 * @param[out] aSize    指向变量的指针，用于返回字符串缓冲区的大小（字节数）（不得为NULL）。
 *
 * @returns 指向字符串缓冲区的指针。
 *
 */
char *otSrpClientBuffersGetServiceEntryInstanceNameString(otSrpClientBuffersServiceEntry *aEntry, uint16_t *aSize);

/**
 * 此函数从服务条目获取TXT记录的缓冲区。
 *
 * @param[in]  aEntry   指向先前分配的服务项的指针（不能为空）。
 * @param[out] aSize    指向变量的指针，用于返回缓冲区的大小（字节数）（不得为空）。
 *
 * @returns 指向缓冲区的指针。
 *
 */
uint8_t *otSrpClientBuffersGetServiceEntryTxtBuffer(otSrpClientBuffersServiceEntry *aEntry, uint16_t *aSize);

/**
 * 此函数从服务条目获取服务子类型标签的数组。
 *
 * @param[in]  aEntry          指向先前分配的服务项的指针（不能为空）。
 * @param[out] aArrayLength    返回数组长度的变量指针（不能为NULL）。
 *
 * @returns 指向数组的指针。
 *
 */
const char **otSrpClientBuffersGetSubTypeLabelsArray(otSrpClientBuffersServiceEntry *aEntry, uint16_t *aArrayLength);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_SRP_CLIENT_BUFFERS_H_

