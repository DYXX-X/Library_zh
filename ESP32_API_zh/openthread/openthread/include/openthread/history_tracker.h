/*
 *  版权所有（c）2021，The OpenThread Authors。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 */

#ifndef OPENTHREAD_HISTORY_TRACKER_H_
#define OPENTHREAD_HISTORY_TRACKER_H_

#include <openthread/instance.h>
#include <openthread/ip6.h>
#include <openthread/thread.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api历史跟踪器
 *
 * @{
 *
 */

/**
 * @brief 此标头定义历史跟踪程序的公共API。
 *
 *   历史跟踪器模块记录线程网络运行时不同事件的历史（例如RX和TX消息或网络信息更改等）。所有跟踪的条目都有时间戳。
 *
 *   当启用“OPENTHREAD_CONFIG_HISTOR_TRACKER_ENABLE”时，此模块中的功能可用。
 *
 */

/**
 * 此常数指定条目的最长期限，即49天（以毫秒为单位）。
 *
 * 早于最大年龄的条目将给出该值作为其年龄。
 *
 */
#define OT_HISTORY_TRACKER_MAX_AGE (49 * 24 * 60 * 60 * 1000u)

#define OT_HISTORY_TRACKER_ENTRY_AGE_STRING_SIZE 21 ///<条目年龄的字符串表示的推荐大小。

/**
 * 此类型表示遍历历史列表的迭代器。
 *
 * 此类型中的字段是不透明的（供OpenThread核心使用），因此调用者不应访问/使用。
 *
 * 在使用迭代器之前，必须使用“otHistoryTrackerInitIterator（）”对其进行初始化，
 *
 */
typedef struct otHistoryTrackerIterator
{
    uint32_t mData32;
    uint16_t mData16;
} otHistoryTrackerIterator;

/**
 * 此结构表示线程网络信息。
 *
 */
typedef struct otHistoryTrackerNetworkInfo
{
    otDeviceRole     mRole;        ///<设备角色。
    otLinkModeConfig mMode;        ///<设备模式。
    uint16_t         mRloc16;      ///<设备RLOC16。
    uint32_t         mPartitionId; ///<分区ID（连接时有效）。
} otHistoryTrackerNetworkInfo;

/**
 * 此枚举定义IPv6（单播或多播）地址信息的事件（即，是添加还是删除地址）。
 *
 */
typedef enum
{
    OT_HISTORY_TRACKER_ADDRESS_EVENT_ADDED   = 0, ///<添加地址。
    OT_HISTORY_TRACKER_ADDRESS_EVENT_REMOVED = 1, ///<地址已删除。
} otHistoryTrackerAddressEvent;

/**
 * 此结构表示单播IPv6地址信息。
 *
 */
typedef struct otHistoryTrackerUnicastAddressInfo
{
    otIp6Address                 mAddress;       ///<单播IPv6地址。
    uint8_t                      mPrefixLength;  ///<前缀长度（以位为单位）。
    uint8_t                      mAddressOrigin; ///<地址原点（`OT_address_origin_*`常量）。
    otHistoryTrackerAddressEvent mEvent;         ///<表示事件（添加/删除地址）。
    uint8_t                      mScope : 4;     ///<IPv6作用域。
    bool                         mPreferred : 1; ///<如果首选地址。
    bool                         mValid : 1;     ///<如果地址有效。
    bool                         mRloc : 1;      ///<如果地址是RLOC。
} otHistoryTrackerUnicastAddressInfo;

/**
 * 此结构表示IPv6多播地址信息。
 *
 */
typedef struct otHistoryTrackerMulticastAddressInfo
{
    otIp6Address                 mAddress;       ///<IPv6多播地址。
    uint8_t                      mAddressOrigin; ///<地址原点（`OT_address_origin_*`常量）。
    otHistoryTrackerAddressEvent mEvent;         ///<表示事件（添加/删除地址）。
} otHistoryTrackerMulticastAddressInfo;

/**
 * 表示`otHistoryTrackerMessageInfo`结构中使用的消息优先级的常量。
 *
 */
enum
{
    OT_HISTORY_TRACKER_MSG_PRIORITY_LOW    = OT_MESSAGE_PRIORITY_LOW,      ///<低优先级。
    OT_HISTORY_TRACKER_MSG_PRIORITY_NORMAL = OT_MESSAGE_PRIORITY_NORMAL,   ///<正常优先级。
    OT_HISTORY_TRACKER_MSG_PRIORITY_HIGH   = OT_MESSAGE_PRIORITY_HIGH,     ///<高优先级。
    OT_HISTORY_TRACKER_MSG_PRIORITY_NET    = OT_MESSAGE_PRIORITY_HIGH + 1, ///<网络控制优先级。
};

/**
 * 此结构表示RX/TX IPv6消息信息。
 *
 * 此结构中的一些字段仅适用于RX消息或TX消息，例如，“mAveRxRss”是形成接收消息的所有片段帧的平均RSS，并且仅适用于TX消息。
 *
 */
typedef struct otHistoryTrackerMessageInfo
{
    uint16_t   mPayloadLength;       ///<IPv6有效负载长度（不包括IP6报头本身）。
    uint16_t   mNeighborRloc16;      ///<发送/接收消息的邻居的RLOC16（如果没有RLOC16，则为“0xfffe”）。
    otSockAddr mSource;              ///<源IPv6地址和端口（如果是UDP/TCP）
    otSockAddr mDestination;         ///<目标IPv6地址和端口（如果是UDP/TCP）。
    uint16_t   mChecksum;            ///<消息校验和（仅对UDP/TCP/ICMP6有效）。
    uint8_t    mIpProto;             ///<IP协议编号（`OT_IP6_PROTO_*`枚举）。
    uint8_t    mIcmp6Type;           ///<ICMP6类型，如果消息为ICMP6，则为零（`OT_ICMP6_type_*`枚举）。
    int8_t     mAveRxRss;            ///<接收消息的RSS或OT_RADIO_INVALI_RSSI（如果未知）。
    bool       mLinkSecurity : 1;    ///<指示消息是否使用链接安全性。
    bool       mTxSuccess : 1;       ///<表示发送成功（例如，收到确认）。仅适用于发送消息。
    uint8_t    mPriority : 2;        ///<消息优先级（`OT_HISTORY_TRACKER_MSG_priority_*`枚举）。
    bool       mRadioIeee802154 : 1; ///<指示消息是否通过15.4无线电链路发送/接收。
    bool       mRadioTrelUdp6 : 1;   ///<指示消息是否通过TREL无线电链路发送/接收。
} otHistoryTrackerMessageInfo;

/**
 * 此枚举定义邻居信息中的事件（即，是否添加、删除或更改邻居）。
 *
 * 事件`OT_HISTORY_TRACKER_NEIGHBOR_Event_STORING`仅适用于子邻居。当设备（重新）启动后，从非易失性设置中检索到以前的子列表，并且设备尝试恢复与这些子列表的连接时，将触发该事件。
 *
 */
typedef enum
{
    OT_HISTORY_TRACKER_NEIGHBOR_EVENT_ADDED     = 0, ///<添加邻居。
    OT_HISTORY_TRACKER_NEIGHBOR_EVENT_REMOVED   = 1, ///<邻居已删除。
    OT_HISTORY_TRACKER_NEIGHBOR_EVENT_CHANGED   = 2, ///<邻居已更改（例如，设备模式标志已更改）。
    OT_HISTORY_TRACKER_NEIGHBOR_EVENT_RESTORING = 3, ///<邻居正在恢复（仅适用于儿童）。
} otHistoryTrackerNeighborEvent;

/**
 * 此结构表示邻居信息。
 *
 */
typedef struct otHistoryTrackerNeighborInfo
{
    otExtAddress mExtAddress;           ///<邻居的扩展地址。
    uint16_t     mRloc16;               ///<邻居的RLOC16。
    int8_t       mAverageRssi;          ///<记录进入时来自邻居的rx帧的平均RSSI。
    uint8_t      mEvent : 2;            ///<表示事件（`OT_HISTORY_TRACKER_NEIGHBOR_event_*`枚举）。
    bool         mRxOnWhenIdle : 1;     ///空闲时<Rx开启。
    bool         mFullThreadDevice : 1; ///<全线程设备。
    bool         mFullNetworkData : 1;  ///<完整网络数据。
    bool         mIsChild : 1;          ///<指示邻居是否是孩子。
} otHistoryTrackerNeighborInfo;

/**
 * 此函数初始化`otHistoryTrackerIterator`。
 *
 * 迭代器必须在使用之前初始化。
 *
 * 迭代器可以再次初始化，从列表的开头开始。
 *
 * 当对列表中的条目进行迭代时，为了确保条目年龄是一致的，年龄是相对于迭代器初始化的时间给出的，即，条目年龄是作为从事件（记录条目时）到迭代器的初始化时间的持续时间（以毫秒为单位）提供的。
 *
 * @param[in] aIterator  指向要初始化的迭代器的指针（不能为空）。
 *
 */
void otHistoryTrackerInitIterator(otHistoryTrackerIterator *aIterator);

/**
 * 此函数遍历网络信息历史列表中的条目。
 *
 * @param[in]    aInstance   指向OpenThread实例的指针。
 * @param[inout] aIterator   指向迭代器的指针。必须初始化或行为未定义。
 * @param[out]   aEntryAge   用于输出条目年龄的变量指针。不得为空。Age提供为从记录条目到
 *                           @p a计时器初始化时间。对于大于最大年龄的条目，将其设置为`OT_HISTORY_TRACKER_MAX_AGE`。
 *
 * @returns 指向“otHistoryTrackerNetworkInfo”条目的指针，如果列表中没有更多条目，则指向“NULL”。
 *
 */
const otHistoryTrackerNetworkInfo *otHistoryTrackerIterateNetInfoHistory(otInstance *              aInstance,
                                                                         otHistoryTrackerIterator *aIterator,
                                                                         uint32_t *                aEntryAge);

/**
 * 此函数迭代单播地址历史列表中的条目。
 *
 * @param[in]    aInstance   指向OpenThread实例的指针。
 * @param[inout] aIterator   指向迭代器的指针。必须初始化或行为未定义。
 * @param[out]   aEntryAge   用于输出条目年龄的变量指针。不得为空。Age提供为从记录条目到
 *                           @p a计时器初始化时间。对于大于最大年龄的条目，将其设置为`OT_HISTORY_TRACKER_MAX_AGE`。
 *
 * @returns 指向“otHistoryTrackerUnicastAddressInfo”条目的指针，如果列表中没有更多条目，则指向“NULL”。
 *
 */
const otHistoryTrackerUnicastAddressInfo *otHistoryTrackerIterateUnicastAddressHistory(
    otInstance *              aInstance,
    otHistoryTrackerIterator *aIterator,
    uint32_t *                aEntryAge);

/**
 * 此函数迭代多播地址历史列表中的条目。
 *
 * @param[in]    aInstance   指向OpenThread实例的指针。
 * @param[inout] aIterator   指向迭代器的指针。必须初始化或行为未定义。
 * @param[out]   aEntryAge   用于输出条目年龄的变量指针。不得为空。Age提供为从记录条目到
 *                           @p a计时器初始化时间。对于大于最大年龄的条目，将其设置为`OT_HISTORY_TRACKER_MAX_AGE`。
 *
 * @returns 指向“otHistoryTrackerMulticastAddressInfo”条目的指针，如果列表中没有更多条目，则指向“NULL”。
 *
 */
const otHistoryTrackerMulticastAddressInfo *otHistoryTrackerIterateMulticastAddressHistory(
    otInstance *              aInstance,
    otHistoryTrackerIterator *aIterator,
    uint32_t *                aEntryAge);

/**
 * 此函数迭代RX消息历史列表中的条目。
 *
 * @param[in]    aInstance   指向OpenThread实例的指针。
 * @param[inout] aIterator   指向迭代器的指针。必须初始化或行为未定义。
 * @param[out]   aEntryAge   用于输出条目年龄的变量指针。不得为空。Age提供为从记录条目到
 *                           @p a计时器初始化时间。对于大于最大年龄的条目，将其设置为`OT_HISTORY_TRACKER_MAX_AGE`。
 *
 * @returns “otHistoryTrackerMessageInfo”条目，如果列表中没有更多条目，则为“NULL”。
 *
 */
const otHistoryTrackerMessageInfo *otHistoryTrackerIterateRxHistory(otInstance *              aInstance,
                                                                    otHistoryTrackerIterator *aIterator,
                                                                    uint32_t *                aEntryAge);

/**
 * 此函数迭代TX消息历史列表中的条目。
 *
 * @param[in]    aInstance   指向OpenThread实例的指针。
 * @param[inout] aIterator   指向迭代器的指针。必须初始化或行为未定义。
 * @param[out]   aEntryAge   用于输出条目年龄的变量指针。不得为空。Age提供为从记录条目到
 *                           @p a计时器初始化时间。对于大于最大年龄的条目，将其设置为`OT_HISTORY_TRACKER_MAX_AGE`。
 *
 * @returns “otHistoryTrackerMessageInfo”条目，如果列表中没有更多条目，则为“NULL”。
 *
 */
const otHistoryTrackerMessageInfo *otHistoryTrackerIterateTxHistory(otInstance *              aInstance,
                                                                    otHistoryTrackerIterator *aIterator,
                                                                    uint32_t *                aEntryAge);

/**
 * 此函数迭代邻居历史列表中的条目。
 *
 * @param[in]    aInstance   指向OpenThread实例的指针。
 * @param[inout] aIterator   指向迭代器的指针。必须初始化或行为未定义。
 * @param[out]   aEntryAge   用于输出条目年龄的变量指针。不得为空。Age提供为从记录条目到
 *                           @p a计时器初始化时间。对于大于最大年龄的条目，将其设置为`OT_HISTORY_TRACKER_MAX_AGE`。
 *
 * @returns “otHistoryTrackerNeighborInfo”条目，如果列表中没有更多条目，则为“NULL”。
 *
 */
const otHistoryTrackerNeighborInfo *otHistoryTrackerIterateNeighborHistory(otInstance *              aInstance,
                                                                           otHistoryTrackerIterator *aIterator,
                                                                           uint32_t *                aEntryAge);

/**
 * 此函数将给定的条目年龄转换为可读字符串。
 *
 * 输入年龄字符串的格式为“<hh>：<mm>：<ss>.<mmmm>”，表示小时、分钟、秒和毫秒（如果短于一天）或“<dd>天<hh>：<mm>：<ss>.<mmmm>”（如果长于一天）。
 *
 * If the resulting string does not fit in @p aBuffer（在其@p aSize字符内），字符串将被截断，但输出的字符串始终以空结尾。
 *
 * @param[in]  aEntryAge 输入年龄（持续时间，以毫秒为单位）。
 * @param[out] aBuffer   指向字符数组以输出字符串的指针（不能为空）。
 * @param[in]  aSize     @p aBuffer的大小。建议使用`OT_HISTORY_TRACKER_ENTRY_AGE_STRING_SIZE`。
 *
 */
void otHistoryTrackerEntryAgeToString(uint32_t aEntryAge, char *aBuffer, uint16_t aSize);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_HISTORY_TRACKER_H_

