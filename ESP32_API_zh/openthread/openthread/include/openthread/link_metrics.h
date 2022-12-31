/*
 *  版权所有（c）2020，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread链接度量API。
 */

#ifndef LINK_METRICS_H_
#define LINK_METRICS_H_

#include "openthread-core-config.h"

#include <openthread/ip6.h>
#include <openthread/message.h>
#include <openthread/platform/radio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api链接度量
 *
 * @brief 该模块包括控制链路度量协议的功能。
 *
 * @{
 *
 */

/**
 * 此结构表示链接度量查询的结果（值）。
 *
 */
typedef struct otLinkMetricsValues
{
    otLinkMetrics mMetrics; ///<指定存在/包含哪些度量值。

    uint32_t mPduCountValue;   ///<Pdu计数的值。
    uint8_t  mLqiValue;        ///<LQI值。
    uint8_t  mLinkMarginValue; ///<链接边距的值。
    int8_t   mRssiValue;       ///<Rssi的值。
} otLinkMetricsValues;

/**
 * 此结构表示在前向跟踪系列中考虑哪些帧。
 *
 */
typedef struct otLinkMetricsSeriesFlags
{
    bool mLinkProbe : 1;      ///<MLE链接探针。
    bool mMacData : 1;        ///<MAC数据帧。
    bool mMacDataRequest : 1; ///<MAC数据请求。
    bool mMacAck : 1;         ///<MAC确认。
} otLinkMetricsSeriesFlags;

/**
 * 增强的ACK标志。
 *
 * 这些在增强的基于ACK的探测中用于指示是否注册或清除探测。
 *
 */
typedef enum otLinkMetricsEnhAckFlags
{
    OT_LINK_METRICS_ENH_ACK_CLEAR    = 0, ///<清除。
    OT_LINK_METRICS_ENH_ACK_REGISTER = 1, ///<注册。
} otLinkMetricsEnhAckFlags;

/**
 * 链接度量状态值。
 *
 */
typedef enum otLinkMetricsStatus
{
    OT_LINK_METRICS_STATUS_SUCCESS                     = 0,
    OT_LINK_METRICS_STATUS_CANNOT_SUPPORT_NEW_SERIES   = 1,
    OT_LINK_METRICS_STATUS_SERIESID_ALREADY_REGISTERED = 2,
    OT_LINK_METRICS_STATUS_SERIESID_NOT_RECOGNIZED     = 3,
    OT_LINK_METRICS_STATUS_NO_MATCHING_FRAMES_RECEIVED = 4,
    OT_LINK_METRICS_STATUS_OTHER_ERROR                 = 254,
} otLinkMetricsStatus;

/**
 * 当收到链接度量报告时，将调用此函数指针。
 *
 * @param[in]  aSource         指向源地址的指针。
 * @param[in]  aMetricsValues  指向链接度量值（查询结果）的指针。
 * @param[in]  aStatus         报告中的状态代码（仅当@p aMetricsValues为NULL时有用）。
 * @param[in]  aContext        指向应用程序特定上下文的指针。
 *
 */
typedef void (*otLinkMetricsReportCallback)(const otIp6Address *       aSource,
                                            const otLinkMetricsValues *aMetricsValues,
                                            uint8_t                    aStatus,
                                            void *                     aContext);
/**
 * 当收到链路度量管理响应时，调用此函数指针。
 *
 * @param[in]  aSource         指向源地址的指针。
 * @param[in]  aStatus         响应中的状态代码。
 * @param[in]  aContext        指向应用程序特定上下文的指针。
 *
 */
typedef void (*otLinkMetricsMgmtResponseCallback)(const otIp6Address *aSource, uint8_t aStatus, void *aContext);

/**
 * 当接收到Enh ACK探测IE时，调用此函数指针。
 *
 * @param[in] aShortAddress     探测主题的Mac短地址。
 * @param[in] aExtAddress       指向探测主题的Mac扩展地址的指针。
 * @param[in] aMetricsValues    指向从IE获得的链接度量值的指针。
 * @param[in] aContext          指向应用程序特定上下文的指针。
 *
 */
typedef void (*otLinkMetricsEnhAckProbingIeReportCallback)(otShortAddress             aShortAddress,
                                                           const otExtAddress *       aExtAddress,
                                                           const otLinkMetricsValues *aMetricsValues,
                                                           void *                     aContext);

/**
 * 此函数发送MLE数据请求以查询链路度量。
 *
 * 它可以是单探头或前向跟踪系列。
 *
 * @param[in]  aInstance            指向OpenThread实例的指针。
 * @param[in]  aDestination         指向目标地址的指针。
 * @param[in]  aSeriesId            要查询的系列ID，0表示Single Probe。
 * @param[in]  aLinkMetricsFlags    指向指定要查询的度量的标志的指针。
 * @param[in]  aCallback            收到链接度量报告时调用的函数的指针。
 * @param[in]  aCallbackContext     指向应用程序特定上下文的指针。
 *
 * @retval OT_ERROR_NONE已成功发送链路度量查询消息。
 * @retval OT_ERROR_NO_BUFS缓冲区不足，无法生成MLE数据请求消息。
 * @retval OT_ERROR_UNKNOWN_NEIGHBOR@p aDestination不是本地链接或未找到邻居。
 * @retval OT_ERROR_NOT_CAPABLE邻居不是线程1.2设备，不支持链路度量。
 *
 */
otError otLinkMetricsQuery(otInstance *                aInstance,
                           const otIp6Address *        aDestination,
                           uint8_t                     aSeriesId,
                           const otLinkMetrics *       aLinkMetricsFlags,
                           otLinkMetricsReportCallback aCallback,
                           void *                      aCallbackContext);

/**
 * 此功能发送MLE链路度量管理请求，以配置/清除转发跟踪系列。
 *
 * @param[in] aInstance          指向OpenThread实例的指针。
 * @param[in] aDestination       指向目标地址的指针。
 * @param[in] aSeriesId          要使用的系列ID。
 * @param[in] aSeriesFlags       指定要计算哪些帧的系列标志。
 * @param[in] aLinkMetricsFlags  指向指定要查询的度量的标志的指针。当“aSeriesFlags”为“0”时，应为“NULL”。
 * @param[in]  aCallback         收到链接度量管理响应时调用的函数的指针。
 * @param[in]  aCallbackContext  指向应用程序特定上下文的指针。
 *
 * @retval OT_ERROR_NONE已成功发送链路度量管理请求消息。
 * @retval OT_ERROR_NO_BUFS缓冲区不足，无法生成MLE链路度量管理请求消息。
 * @retval OT_ERROR_INVALID_ARGS@p aSeriesId不在有效范围内。
 * @retval OT_ERROR_UNKNOWN_NEIGHBOR@p aDestination不是本地链接或未找到邻居。
 * @retval OT_ERROR_NOT_CAPABLE邻居不是线程1.2设备，不支持链路度量。
 *
 */
otError otLinkMetricsConfigForwardTrackingSeries(otInstance *                      aInstance,
                                                 const otIp6Address *              aDestination,
                                                 uint8_t                           aSeriesId,
                                                 otLinkMetricsSeriesFlags          aSeriesFlags,
                                                 const otLinkMetrics *             aLinkMetricsFlags,
                                                 otLinkMetricsMgmtResponseCallback aCallback,
                                                 void *                            aCallbackContext);

/**
 * 此函数发送MLE链路度量管理请求，以配置/清除增强型基于ACK的探测。此功能需要启用OT_LINK_METRICS_INITIATOR功能。
 *
 * @param[in] aInstance          指向OpenThread实例的指针。
 * @param[in] aDestination       指向目标地址的指针。
 * @param[in] aEnhAckFlags       Enh ACK标志，指示是否注册或清除探测`“0”清除，“1”注册。保留其他值。
 * @param[in] aLinkMetricsFlags  指向指定要查询的度量的标志的指针。当“aEnhAckFlags”为“0”时，应为“NULL”。
 * @param[in] aCallback          当接收到具有链接度量的增强确认时调用的函数的指针。
 * @param[in] aCallbackContext   指向应用程序特定上下文的指针。
 *
 * @retval OT_ERROR_NONE已成功发送链路度量管理请求消息。
 * @retval OT_ERROR_NO_BUFS缓冲区不足，无法生成MLE链路度量管理请求消息。
 * @retval OT_ERROR_INVALID_ARGS@p aEnhAckFlags不是有效值或@p aLinkMetricsFlags不正确。
 * @retval OT_ERROR_UNKNOWN_NEIGHBOR@p aDestination不是本地链接或未找到邻居。
 * @retval OT_ERROR_NOT_CAPABLE邻居不是线程1.2设备，不支持链路度量。
 *
 */
otError otLinkMetricsConfigEnhAckProbing(otInstance *                               aInstance,
                                         const otIp6Address *                       aDestination,
                                         otLinkMetricsEnhAckFlags                   aEnhAckFlags,
                                         const otLinkMetrics *                      aLinkMetricsFlags,
                                         otLinkMetricsMgmtResponseCallback          aCallback,
                                         void *                                     aCallbackContext,
                                         otLinkMetricsEnhAckProbingIeReportCallback aEnhAckCallback,
                                         void *                                     aEnhAckCallbackContext);

/**
 * 此函数发送MLE链路探测消息。
 *
 * @param[in] aInstance       指向OpenThread实例的指针。
 * @param[in] aDestination    指向目标地址的指针。
 * @param[in] aSeriesId       探测消息所针对的系列ID[1254]。
 * @param[in] aLength         链路探测TLV中数据有效载荷的长度[0，64]（根据线程1.2规范，4.4.37）。
 *
 * @retval OT_ERROR_NONE已成功发送链路探测消息。
 * @retval OT_ERROR_NO_BUFS缓冲区不足，无法生成MLE链路探测消息。
 * @retval OT_ERROR_INVALID_ARGS@p aSeriesId或@p aLength不在有效范围内。
 * @retval OT_ERROR_UNKNOWN_NEIGHBOR@p aDestination不是本地链接或未找到邻居。
 * @retval OT_ERROR_NOT_CAPABLE邻居不是线程1.2设备，不支持链路度量。
 *
 */
otError otLinkMetricsSendLinkProbe(otInstance *        aInstance,
                                   const otIp6Address *aDestination,
                                   uint8_t             aSeriesId,
                                   uint8_t             aLength);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // LINK_METRICS_H_

