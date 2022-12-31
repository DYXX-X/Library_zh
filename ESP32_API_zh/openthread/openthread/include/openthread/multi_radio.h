/*
 *  版权所有（c）2020，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread多无线电链接API。
 */

#ifndef OPENTHREAD_MULTI_RADIO_H_
#define OPENTHREAD_MULTI_RADIO_H_

#include <openthread/platform/radio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api多无线电
 *
 * @brief 本模块包括多无线电链路的定义和功能。
 *
 * @{
 *
 */

/**
 * 此类型表示与无线电链路相关的信息。
 *
 */
typedef struct otRadioLinkInfo
{
    uint8_t mPreference; ///<无线电链路的首选级别
} otRadioLinkInfo;

/**
 * 此类型表示与邻居相关联的多无线电链路信息。
 *
 */
typedef struct otMultiRadioNeighborInfo
{
    bool            mSupportsIeee802154 : 1; ///<邻居支持IEEE 802.15.4无线链路
    bool            mSupportsTrelUdp6 : 1;   ///<邻居支持线程无线电封装链路（TREL）无线电链路。
    otRadioLinkInfo mIeee802154Info;         ///<15.4无线电链路的附加信息（支持时适用）。
    otRadioLinkInfo mTrelUdp6Info;           ///<TREL无线电链路的附加信息（支持时适用）。
} otMultiRadioNeighborInfo;

/**
 * 此函数获取与具有给定扩展地址的邻居相关联的多无线电链路信息。
 *
 * 此功能要求启用多无线电链路功能（请参阅“config/radio_link.h”）。
 *
 * @param[in]  aInstance      指向OpenThread实例的指针。
 * @param[in]  aExtAddress    邻居的扩展地址。
 * @param[out] aNeighborInfo  指向“otMultiRadioNeighborInfo”的指针以输出邻居信息（成功时）。
 *
 * @retval 找到OT_ERROR_NONE Neighbor，@p aNeighborInfo已成功更新。
 * @retval OT_ERROR_NOT_FOUND找不到具有@p aExtAddress的邻居。
 *
 */
otError otMultiRadioGetNeighborInfo(otInstance *              aInstance,
                                    const otExtAddress *      aExtAddress,
                                    otMultiRadioNeighborInfo *aNeighborInfo);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_MULTI_RADIO_H_

