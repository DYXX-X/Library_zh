/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread网络数据API。
 */

#ifndef OPENTHREAD_NETDATA_H_
#define OPENTHREAD_NETDATA_H_

#include <openthread/ip6.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api线程常规
 *
 * @{
 *
 */

#define OT_NETWORK_DATA_ITERATOR_INIT 0 ///<初始化“otNetworkDataIterator”的值。

typedef uint32_t otNetworkDataIterator; ///<用于遍历网络数据信息。

/**
 * 此结构表示边界路由器配置。
 */
typedef struct otBorderRouterConfig
{
    otIp6Prefix mPrefix;           ///<IPv6前缀。
    signed int  mPreference : 2;   ///<2位带符号整数首选项（`OT_ROUTE_preference_*`值）。
    bool        mPreferred : 1;    ///<是否首选前缀。
    bool        mSlaac : 1;        ///<前缀是否可用于地址自动配置（SLAAC）。
    bool        mDhcp : 1;         ///<边界路由器是否为DHCPv6代理。
    bool        mConfigure : 1;    ///<DHCPv6代理是否提供其他配置数据。
    bool        mDefaultRoute : 1; ///<边界路由器是否是前缀的默认路由器。
    bool        mOnMesh : 1;       ///<是否在网格上考虑此前缀。
    bool        mStable : 1;       ///<此配置是否被视为稳定网络数据。
    bool        mNdDns : 1;        ///<此边界路由器是否可以通过ND提供DNS信息。
    bool        mDp : 1;           ///<前缀是否为线程域前缀（从线程1.2开始添加）。
    uint16_t    mRloc16;           ///<边界路由器的RLOC16（配置添加时忽略值）。
} otBorderRouterConfig;

/**
 * 此结构表示外部路由配置。
 *
 */
typedef struct otExternalRouteConfig
{
    otIp6Prefix mPrefix;                  ///<IPv6前缀。
    uint16_t    mRloc16;                  ///<边界路由器的RLOC16（配置添加时忽略值）。
    signed int  mPreference : 2;          ///<2位带符号整数首选项（`OT_ROUTE_preference_*`值）。
    bool        mNat64 : 1;               ///<是否为NAT64前缀。
    bool        mStable : 1;              ///<此配置是否被视为稳定网络数据。
    bool        mNextHopIsThisDevice : 1; ///<下一跳是否为该设备（配置添加时忽略该值）。
} otExternalRouteConfig;

/**
 * 在“otExternalRouteConfig”和“otBorderRouteConfig”中定义“mPreference”的有效值。
 *
 */
typedef enum otRoutePreference
{
    OT_ROUTE_PREFERENCE_LOW  = -1, ///<低路线偏好。
    OT_ROUTE_PREFERENCE_MED  = 0,  ///<中等路线偏好。
    OT_ROUTE_PREFERENCE_HIGH = 1,  ///<高路线偏好。
} otRoutePreference;

#define OT_SERVICE_DATA_MAX_SIZE 252 ///<服务数据的最大大小（字节）。
#define OT_SERVER_DATA_MAX_SIZE 248  ///<服务器数据的最大大小（字节）。理论极限，实际上要低得多。

/**
 * 此结构表示服务器配置。
 *
 */
typedef struct otServerConfig
{
    bool     mStable : 1;                          ///<此配置是否被视为稳定网络数据。
    uint8_t  mServerDataLength;                    ///<服务器数据长度。
    uint8_t  mServerData[OT_SERVER_DATA_MAX_SIZE]; ///<服务器数据字节。
    uint16_t mRloc16;                              ///<服务器RLOC16。
} otServerConfig;

/**
 * 此结构表示服务配置。
 *
 */
typedef struct otServiceConfig
{
    uint8_t        mServiceId;                             ///<服务ID（在网络数据上迭代时）。
    uint32_t       mEnterpriseNumber;                      ///<IANA企业编号。
    uint8_t        mServiceDataLength;                     ///<服务数据长度。
    uint8_t        mServiceData[OT_SERVICE_DATA_MAX_SIZE]; ///<服务数据字节。
    otServerConfig mServerConfig;                          ///<服务器配置。
} otServiceConfig;

/**
 * 此方法提供分区的线程网络数据的完整或稳定副本。
 *
 * @param[in]     aInstance    指向OpenThread实例的指针。
 * @param[in]     aStable      复制稳定版本时为TRUE，复制完整版本时为FALSE。
 * @param[out]    aData        指向数据缓冲区的指针。
 * @param[inout]  aDataLength  输入时，@p aData指向的数据缓冲区的大小。退出时，复制的字节数。
 *
 */
otError otNetDataGet(otInstance *aInstance, bool aStable, uint8_t *aData, uint8_t *aDataLength);

/**
 * 此函数获取分区的网络数据中的下一个网格上前缀。
 *
 * @param[in]     aInstance  指向OpenThread实例的指针。
 * @param[inout]  aIterator  指向网络数据迭代器上下文的指针。要获取网格上的第一个条目，应将其设置为OT_NETWORK_DATA_ITERATOR_INIT。
 * @param[out]    aConfig    指向将放置“网格上前缀”信息的位置的指针。
 *
 * @retval OT_ERROR_NONE已成功找到下一个网格上前缀。
 * @retval OT_ERROR_NOT_FOUND线程网络数据中不存在后续的网格上前缀。
 *
 */
otError otNetDataGetNextOnMeshPrefix(otInstance *           aInstance,
                                     otNetworkDataIterator *aIterator,
                                     otBorderRouterConfig * aConfig);

/**
 * 此函数获取分区的网络数据中的下一个外部路由。
 *
 * @param[in]     aInstance  指向OpenThread实例的指针。
 * @param[inout]  aIterator  指向网络数据迭代器上下文的指针。要获取第一个外部路由条目，应将其设置为OT_NETWORK_DATA_ITERATOR_INIT。
 * @param[out]    aConfig    指向将放置外部路由信息的位置的指针。
 *
 * @retval OT_ERROR_NONE已成功找到下一个外部路由。
 * @retval OT_ERROR_NOT_FOUND线程网络数据中不存在后续的外部路由条目。
 *
 */
otError otNetDataGetNextRoute(otInstance *aInstance, otNetworkDataIterator *aIterator, otExternalRouteConfig *aConfig);

/**
 * 此函数获取分区的网络数据中的下一个服务。
 *
 * @param[in]     aInstance  指向OpenThread实例的指针。
 * @param[inout]  aIterator  指向网络数据迭代器上下文的指针。要获取第一个服务条目，应将其设置为OT_NETWORK_DATA_ITERATOR_INIT。
 * @param[out]    aConfig    指向将放置服务信息的位置的指针。
 *
 * @retval OT_ERROR_NONE已成功找到下一个服务。
 * @retval OT_ERROR_NOT_FOUND分区的网络数据中不存在后续服务。
 *
 */
otError otNetDataGetNextService(otInstance *aInstance, otNetworkDataIterator *aIterator, otServiceConfig *aConfig);

/**
 * 获取网络数据版本。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 网络数据版本。
 *
 */
uint8_t otNetDataGetVersion(otInstance *aInstance);

/**
 * 获取稳定的网络数据版本。
 *
 * @param[in]  aInstance 指向OpenThread实例的指针。
 *
 * @returns 稳定的网络数据版本。
 *
 */
uint8_t otNetDataGetStableVersion(otInstance *aInstance);

/**
 * 检查转向数据是否包含Joiner。
 *
 * @param[in]  aInstance          指向OpenThread实例的指针。
 * @param[in]  aEui64             指向Joiner的IEEE EUI-64的指针。
 *
 * @retval OT_ERROR_NONE@p aEui64包含在转向数据中。
 * @retval OT_ERROR_INVALID_STATE不存在转向数据。
 * @retval OT_ERROR_NOT_FOUND@p aEui64不包含在转向数据中。
 *
 */
otError otNetDataSteeringDataCheckJoiner(otInstance *aInstance, const otExtAddress *aEui64);

// 转发声明
struct otJoinerDiscerner;

/**
 * 检查转向数据是否包含具有给定识别值的Joiner。
 *
 * @param[in]  aInstance          指向OpenThread实例的指针。
 * @param[in]  aDiscerner         指向Joiner Discerner的指针。
 *
 * @retval OT_ERROR_NONE@p aDiscerner包含在转向数据中。
 * @retval OT_ERROR_INVALID_STATE不存在转向数据。
 * @retval OT_ERROR_NOT_FOUND@p aDiscerner不包含在转向数据中。
 *
 */
otError otNetDataSteeringDataCheckJoinerWithDiscerner(otInstance *                    aInstance,
                                                      const struct otJoinerDiscerner *aDiscerner);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_NETDATA_H_

