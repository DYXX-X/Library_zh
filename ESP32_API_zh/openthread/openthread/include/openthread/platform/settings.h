/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 该文件包括设置的非易失性存储的平台抽象。
 */

#ifndef OPENTHREAD_PLATFORM_SETTINGS_H_
#define OPENTHREAD_PLATFORM_SETTINGS_H_

#include <openthread/instance.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup 平台设置
 *
 * @brief 该模块包括设置的非易失性存储的平台抽象。
 *
 * @{
 *
 */

/**
 * 此枚举定义设置的键。
 *
 * 注意：添加新的设置密钥时，如果与该密钥对应的设置包含安全敏感信息，则开发人员必须将该密钥添加到数组“kCriticalKeys”中。
 *
 */
enum
{
    OT_SETTINGS_KEY_ACTIVE_DATASET       = 0x0001, ///<活动操作数据集。
    OT_SETTINGS_KEY_PENDING_DATASET      = 0x0002, ///<待定操作数据集。
    OT_SETTINGS_KEY_NETWORK_INFO         = 0x0003, ///<线程网络信息。
    OT_SETTINGS_KEY_PARENT_INFO          = 0x0004, ///<父信息。
    OT_SETTINGS_KEY_CHILD_INFO           = 0x0005, ///<儿童信息。
    OT_SETTINGS_KEY_RESERVED             = 0x0006, ///<保留（以前自动启动）。
    OT_SETTINGS_KEY_SLAAC_IID_SECRET_KEY = 0x0007, ///<SLAAC键生成语义不透明的IID。
    OT_SETTINGS_KEY_DAD_INFO             = 0x0008, ///<重复地址检测（DAD）信息。
    OT_SETTINGS_KEY_OMR_PREFIX           = 0x0009, ///<离网可路由（OMR）前缀。
    OT_SETTINGS_KEY_ON_LINK_PREFIX       = 0x000a, ///<基础设施链接的链接前缀。
    OT_SETTINGS_KEY_SRP_ECDSA_KEY        = 0x000b, ///<SRP客户端ECDSA公钥/私钥对。
    OT_SETTINGS_KEY_SRP_CLIENT_INFO      = 0x000c, ///<SRP客户端信息（所选SRP服务器地址）。
    OT_SETTINGS_KEY_SRP_SERVER_INFO      = 0x000d, ///<SRP服务器信息（UDP端口）。
};

/**
 * 如有必要，对设置子系统执行任何初始化。
 *
 * @param[in]  aInstance OpenThread实例结构。
 *
 */
void otPlatSettingsInit(otInstance *aInstance);

/**
 * 如有必要，对设置子系统执行任何反初始化。
 *
 * @param[in]  aInstance OpenThread实例结构。
 *
 */
void otPlatSettingsDeinit(otInstance *aInstance);

/**
 * 此功能设置应存储在安全区域中的关键密钥。
 *
 * Note that the memory pointed by @p 在@p a实例被破坏之前，不得释放密钥。
 *
 * @param[in]  aInstance    OpenThread实例结构。
 * @param[in]  aKeys        指向包含关键键列表的数组的指针。
 * @param[in]  aKeysLength  @p aKeys数组中的条目数。
 *
 */
void otPlatSettingsSetCriticalKeys(otInstance *aInstance, const uint16_t *aKeys, uint16_t aKeysLength);

///获取设置的值
/** 此函数获取aKey标识的设置值，并将其写入aValue指向的内存。然后将长度写入aValueLength指向的整数。aValueLength的初始值是要写入aValue的最大字节数。
 *
 *  此函数可用于通过将aValue和aValueLength设置为NULL来检查是否存在键，而无需获取值。您还可以通过只将aValue设置为NULL来检查设置的长度而不获取设置。
 *
 *  请注意，底层存储实现不需要维护具有多个值的设置顺序。在对存储进行任何写入操作后，这些值的顺序可能会改变。
 *
 *  @param[in]     aInstance     OpenThread实例结构。
 *  @param[in]     aKey          与请求的设置关联的键。
 *  @param[in]     aIndex        要获取的特定项的索引。
 *  @param[out]    aValue        指向应写入设置值的位置的指针。如果只是测试设置的存在或长度，则可以设置为NULL。
 *  @param[inout]  aValueLength  指向值长度的指针。调用时，此指针应指向包含可写入aValue的最大值大小的整数。返回时，写入设置的实际长度。如果执行状态检查，则可以将其设置为NULL。
 *
 *  @retval OT_ERROR_NONE找到并成功获取给定设置。
 *  @retval OT_ERROR_NOT_FOUND在设置存储中找不到给定的设置。
 *  @retval OT_ERROR_NOT_IMPLEMENTED此功能未在此平台上实现。
 */
otError otPlatSettingsGet(otInstance *aInstance, uint16_t aKey, int aIndex, uint8_t *aValue, uint16_t *aValueLength);

///设置或替换设置的值
/** 此函数设置或替换由aKey标识的设置值。如果以前有多个值与aKey关联，则它们都将被删除并替换为此单个条目。
 *
 *  成功调用此函数可能会导致具有多个值的不相关设置重新排序。
 *
 *  @param[in]  aInstance     OpenThread实例结构。
 *  @param[in]  aKey          与要更改的设置关联的键。
 *  @param[in]  aValue        指向应该从中读取设置的新值的指针。如果aValueLength为非零，则不得为NULL。
 *  @param[in]  aValueLength  aValue指向的数据长度。可能为零。
 *
 *  @retval OT_ERROR_NONE给定设置已更改或暂存。
 *  @retval OT_ERROR_NOT_IMPLEMENTED此功能未在此平台上实现。
 *  @retval OT_ERROR_NO_BUFS没有剩余空间来存储给定设置。
 */
otError otPlatSettingsSet(otInstance *aInstance, uint16_t aKey, const uint8_t *aValue, uint16_t aValueLength);

///将值添加到设置
/** 此函数将值添加到由aKey标识的设置中，而不替换任何现有值。
 *
 *  请注意，底层实现不需要维护与特定键关联的项的顺序。附加值可以添加到末尾、开头，甚至中间的某个位置。任何预先存在的值的顺序也可能改变。
 *
 *  成功调用此函数可能会导致具有多个值的不相关设置重新排序。
 *
 * @param[in]  aInstance     OpenThread实例结构。
 * @param[in]  aKey          与要更改的设置关联的键。
 * @param[in]  aValue        指向应该从中读取设置的新值的指针。如果aValueLength为非零，则不得为NULL。
 * @param[in]  aValueLength  aValue指向的数据长度。可能为零。
 *
 * @retval OT_ERROR_NONE已添加或准备添加给定设置。
 * @retval OT_ERROR_NOT_IMPLEMENTED此功能未在此平台上实现。
 * @retval OT_ERROR_NO_BUFS没有剩余空间来存储给定设置。
 */
otError otPlatSettingsAdd(otInstance *aInstance, uint16_t aKey, const uint8_t *aValue, uint16_t aValueLength);

///从设置存储中删除设置
/** 此功能从设置存储中删除由aKey标识的设置中的特定值。
 *
 *  请注意，底层实现不需要维护与特定键关联的项的顺序。
 *
 *  @param[in] aInstance  OpenThread实例结构。
 *  @param[in] aKey       与请求的设置关联的键。
 *  @param[in] aIndex     要删除的值的索引。如果设置为-1，将删除此aKey的所有值。
 *
 *  @retval OT_ERROR_NONE找到并成功删除了给定的密钥和索引。
 *  @retval OT_ERROR_NOT_FOUND在设置存储中找不到给定的密钥或索引。
 *  @retval OT_ERROR_NOT_IMPLEMENTED此功能未在此平台上实现。
 */
otError otPlatSettingsDelete(otInstance *aInstance, uint16_t aKey, int aIndex);

///从设置存储中删除所有设置
/** 此功能从设置存储中删除所有设置，将其重置为初始出厂状态。
 *
 *  @param[in] aInstance  OpenThread实例结构。
 */
void otPlatSettingsWipe(otInstance *aInstance);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_PLATFORM_SETTINGS_H_

