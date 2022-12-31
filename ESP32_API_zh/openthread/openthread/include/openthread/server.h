/*
 *  版权所有（c）2016-2017，The OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThreadServer API。
 */

#ifndef OPENTHREAD_SERVER_H_
#define OPENTHREAD_SERVER_H_

#include <openthread/netdata.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api服务器
 *
 * @brief 该模块包括使用OpenThreadServer管理本地网络数据的功能。
 *
 * @{
 *
 */

/**
 * 此方法提供本地线程网络数据的完整或稳定副本。
 *
 * @param[in]     aInstance    指向OpenThread实例的指针。
 * @param[in]     aStable      复制稳定版本时为TRUE，复制完整版本时为FALSE。
 * @param[out]    aData        指向数据缓冲区的指针。
 * @param[inout]  aDataLength  输入时，@p aData指向的数据缓冲区的大小。退出时，复制的字节数。
 *
 */
otError otServerGetNetDataLocal(otInstance *aInstance, bool aStable, uint8_t *aData, uint8_t *aDataLength);

/**
 * 向本地网络数据添加服务配置。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 * @param[in]  aConfig   指向服务配置的指针。
 *
 * @retval OT_ERROR_NONE已成功将配置添加到本地网络数据。
 * @retval OT_ERROR_INVALID_ARGS一个或多个配置参数无效。
 * @retval OT_ERROR_NO_BUFS没有足够的空间将配置添加到本地网络数据。
 *
 * @sa otServerRemoveService
 * @sa otServer寄存器
 *
 */
otError otServerAddService(otInstance *aInstance, const otServiceConfig *aConfig);

/**
 * 从本地网络数据中删除服务配置。
 *
 * @param[in]  aInstance          指向OpenThread实例的指针。
 * @param[in]  aEnterpriseNumber  要删除的服务条目的企业编号。
 * @param[in]  aServiceData       删除期间要查找的服务数据的指针。
 * @param[in]  aServiceDataLength @p aServiceData的长度（以字节为单位）。
 *
 * @retval OT_ERROR_NONE已成功从本地网络数据中删除配置。
 * @retval OT_ERROR_NOT_FOUND找不到边界路由器条目。
 *
 * @sa otServer添加服务
 * @sa otServer寄存器
 *
 */
otError otServerRemoveService(otInstance *   aInstance,
                              uint32_t       aEnterpriseNumber,
                              const uint8_t *aServiceData,
                              uint8_t        aServiceDataLength);

/**
 * 此函数获取本地网络数据中的下一个服务。
 *
 * @param[in]     aInstance  指向OpenThread实例的指针。
 * @param[inout]  aIterator  指向网络数据迭代器上下文的指针。要获取第一个服务条目，应将其设置为OT_NETWORK_DATA_ITERATOR_INIT。
 * @param[out]    aConfig    指向将放置服务信息的位置的指针。
 *
 * @retval OT_ERROR_NONE已成功找到下一个服务。
 * @retval OT_ERROR_NOT_FOUND线程网络数据中不存在后续服务。
 *
 */
otError otServerGetNextService(otInstance *aInstance, otNetworkDataIterator *aIterator, otServiceConfig *aConfig);

/**
 * 立即向领导登记本地网络数据。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @retval OT_ERROR_NONE已成功将服务器数据请求消息排队等待传递。
 *
 * @sa otServer添加服务
 * @sa otServerRemoveService
 *
 */
otError otServerRegister(otInstance *aInstance);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_SERVER_H_

