/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件包含线程联接器角色的函数。
 */

#ifndef OPENTHREAD_JOINER_H_
#define OPENTHREAD_JOINER_H_

#include <openthread/platform/radio.h>
#include <openthread/platform/toolchain.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api连接程序
 *
 * @brief 此模块包括线程联接器角色的函数。
 *
 * @note 此模块中的函数需要`OPENTHREAD_CONFIG_JOINER_ENABLE=1 `。
 *
 * @{
 *
 */

/**
 * 此枚举定义Joiner状态。
 *
 */
typedef enum otJoinerState
{
    OT_JOINER_STATE_IDLE      = 0,
    OT_JOINER_STATE_DISCOVER  = 1,
    OT_JOINER_STATE_CONNECT   = 2,
    OT_JOINER_STATE_CONNECTED = 3,
    OT_JOINER_STATE_ENTRUST   = 4,
    OT_JOINER_STATE_JOINED    = 5,
} otJoinerState;

#define OT_JOINER_MAX_DISCERNER_LENGTH 64 ///<Joiner Discerner的最大长度（以位为单位）。

/**
 * 此结构表示Joiner Discerner。
 *
 */
typedef struct otJoinerDiscerner
{
    uint64_t mValue;  ///<识别器值（最低“m长度”位指定识别器）。
    uint8_t  mLength; ///<长度（位数）-必须为非零，最多为`OT_JOINER_MAX_DISCERNER_Length `。
} otJoinerDiscerner;

/**
 * 调用此函数指针以通知联接操作的完成。
 *
 * @param[in]  aError    如果加入过程成功，则返回OT_ERROR_NONE。OT_ERROR_SECURITY，如果加入过程因安全凭据而失败。如果未发现可连接网络，则为OT_ERROR_NOT_FOUND。如果响应超时，则返回OT_ERROR_RESPONSE_TIMEOUT。
 * @param[in]  aContext  指向应用程序特定上下文的指针。
 *
 */
typedef void (*otJoinerCallback)(otError aError, void *aContext);

/**
 * 此函数用于启用线程联接器角色。
 *
 * @param[in]  aInstance         指向OpenThread实例的指针。
 * @param[in]  aPskd             指向PSKd的指针。
 * @param[in]  aProvisioningUrl  指向设置URL的指针（可能为NULL）。
 * @param[in]  aVendorName       指向供应商名称的指针（可能为空）。
 * @param[in]  aVendorModel      指向供应商模型的指针（可能为空）。
 * @param[in]  aVendorSwVersion  指向供应商软件版本的指针（可能为空）。
 * @param[in]  aVendorData       指向供应商数据的指针（可能为空）。
 * @param[in]  aCallback         连接操作完成时调用的函数的指针。
 * @param[in]  aContext          指向应用程序特定上下文的指针。
 *
 * @retval OT_ERROR_NONE已成功启动加入者角色。
 * @retval OT_ERROR_BUSY上一次尝试仍在进行。
 * @retval OT_ERROR_INVALID_ARGS@p aPskd或@p aProvisioningUrl无效。
 * @retval OT_ERROR_INVALID_STATE IPv6堆栈未启用或线程堆栈已完全启用。
 *
 */
otError otJoinerStart(otInstance *     aInstance,
                      const char *     aPskd,
                      const char *     aProvisioningUrl,
                      const char *     aVendorName,
                      const char *     aVendorModel,
                      const char *     aVendorSwVersion,
                      const char *     aVendorData,
                      otJoinerCallback aCallback,
                      void *           aContext);

/**
 * 此函数用于禁用线程联接器角色。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 *
 */
void otJoinerStop(otInstance *aInstance);

/**
 * 此函数返回Joiner状态。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 *
 * @retval OT_JOINER_STATE_IDLE
 * @retval OT_JOINER_STATE_DISCOVER
 * @retval OT_JOINER_STATE_CONNECT
 * @retval OT_JOINER_STATE_CONNECTED
 * @retval OT_JOINER_STATE_ENTRUST
 * @retval OT_JOINER_STATE_JOINED
 *
 */
otJoinerState otJoinerGetState(otInstance *aInstance);

/**
 * 此方法获取Joiner ID。
 *
 * 如果未设置Joiner Discerner，则Joiner ID是通过工厂分配的IEEE EUI-64计算SHA-256结果的前64位。否则，Joiner ID根据Joiner Discrner值计算。
 *
 * 在调试过程中，Joiner ID还用作设备的IEEE 802.15.4扩展地址。
 *
 * @param[in]   aInstance  指向OpenThread实例的指针。
 *
 * @returns 指向Joiner ID的指针。
 *
 */
const otExtAddress *otJoinerGetId(otInstance *aInstance);

/**
 * 此方法设置Joiner Discerner。
 *
 * Joiner Discerner用于计算调试/连接过程中使用的Joiner ID。
 *
 * 默认情况下（当未提供识别器或将其设置为NULL时），Joiner ID作为通过工厂分配的IEEE EUI-64计算SHA-256的结果的前64位导出。请注意，这是线程规范预期的主要行为。
 *
 * @param[in]   aInstance    指向OpenThread实例的指针。
 * @param[in]   aDiscerner   指向Joiner Discerner的指针。如果为NULL，则清除任何先前设置的识别器。
 *
 * @retval OT_ERROR_NONE Joiner Discerner已成功更新。
 * @retval OT_ERROR_INVALID_ARGS@p aDiscerner无效（指定的长度不在有效范围内）。
 * @retval OT_ERROR_INVALID_STATE存在正在进行的加入过程，因此无法更改Joiner Discerner。
 *
 */
otError otJoinerSetDiscerner(otInstance *aInstance, otJoinerDiscerner *aDiscerner);

/**
 * 此方法获取Joiner Discerner。
 *
 * @param[in]   aInstance       指向OpenThread实例的指针。
 *
 * @returns 指向Joiner Discerner的指针，如果未设置，则为NULL。
 *
 */
const otJoinerDiscerner *otJoinerGetDiscerner(otInstance *aInstance);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”结尾
#endif

#endif // OPENTHREAD_JOINER_H_

