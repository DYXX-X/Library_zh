/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread的无线电接口。
 *
 */

#ifndef OPENTHREAD_PLATFORM_RADIO_H_
#define OPENTHREAD_PLATFORM_RADIO_H_

#include <stdint.h>

#include <openthread/error.h>
#include <openthread/instance.h>
#include <openthread/platform/crypto.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup 平板收音机
 *
 * @brief 该模块包括无线电通信的平台抽象。
 *
 * @{
 *
 */

/**
 * @defgroup 无线电类型类型
 *
 * @brief 该模块包括无线电帧的平台抽象。
 *
 * @{
 *
 */

enum
{
    OT_RADIO_FRAME_MAX_SIZE    = 127,    ///<aMaxPHYPacketSize（IEEE 802.15.4-2006）
    OT_RADIO_FRAME_MIN_SIZE    = 3,      ///<框架最小尺寸FCS+CONTROL
    OT_RADIO_SYMBOLS_PER_OCTET = 2,      ///<2.4 GHz IEEE 802.15.4-2006
    OT_RADIO_BIT_RATE          = 250000, ///<2.4 GHz IEEE 802.15.4（比特/秒）
    OT_RADIO_BITS_PER_OCTET    = 8,      ///<每八位字节的位数

    OT_RADIO_SYMBOL_TIME   = ((OT_RADIO_BITS_PER_OCTET / OT_RADIO_SYMBOLS_PER_OCTET) * 1000000) / OT_RADIO_BIT_RATE,
    OT_RADIO_LQI_NONE      = 0,   ///<不支持LQI测量
    OT_RADIO_RSSI_INVALID  = 127, ///<无效或未知RSSI值
    OT_RADIO_POWER_INVALID = 127, ///<无效或未知的功率值
};

/**
 * 此枚举定义频道页。
 *
 */
enum
{
    OT_RADIO_CHANNEL_PAGE_0      = 0,                               ///<2.4 GHz IEEE 802.15.4-2006
    OT_RADIO_CHANNEL_PAGE_0_MASK = (1U << OT_RADIO_CHANNEL_PAGE_0), ///<2.4 GHz IEEE 802.15.4-2006
    OT_RADIO_CHANNEL_PAGE_2      = 2,                               ///<915 MHz IEEE 802.15.4-2006
    OT_RADIO_CHANNEL_PAGE_2_MASK = (1U << OT_RADIO_CHANNEL_PAGE_2), ///<915 MHz IEEE 802.15.4-2006
};

/**
 * 此枚举定义频带信道范围。
 *
 */
enum
{
    OT_RADIO_915MHZ_OQPSK_CHANNEL_MIN  = 1,                                           ///<915 MHz IEEE 802.15.4-2006
    OT_RADIO_915MHZ_OQPSK_CHANNEL_MAX  = 10,                                          ///<915 MHz IEEE 802.15.4-2006
    OT_RADIO_915MHZ_OQPSK_CHANNEL_MASK = 0x3ff << OT_RADIO_915MHZ_OQPSK_CHANNEL_MIN,  ///<915 MHz IEEE 802.15.4-2006
    OT_RADIO_2P4GHZ_OQPSK_CHANNEL_MIN  = 11,                                          ///<2.4 GHz IEEE 802.15.4-2006
    OT_RADIO_2P4GHZ_OQPSK_CHANNEL_MAX  = 26,                                          ///<2.4 GHz IEEE 802.15.4-2006
    OT_RADIO_2P4GHZ_OQPSK_CHANNEL_MASK = 0xffff << OT_RADIO_2P4GHZ_OQPSK_CHANNEL_MIN, ///<2.4 GHz IEEE 802.15.4-2006
};

/**
 * 此类型表示无线电功能。
 *
 * 该值是指示无线电支持的能力的位字段。请参见`OT_RADIO_CAPS_*`定义。
 *
 */
typedef uint8_t otRadioCaps;

/**
 * 此枚举定义用于指示不同无线电能力的常数。请参见`otRadioCaps`。
 *
 */
enum
{
    OT_RADIO_CAPS_NONE             = 0,      ///<收音机不支持任何功能。
    OT_RADIO_CAPS_ACK_TIMEOUT      = 1 << 0, ///<Radio支持AckTime事件。
    OT_RADIO_CAPS_ENERGY_SCAN      = 1 << 1, ///<无线电支持能量扫描。
    OT_RADIO_CAPS_TRANSMIT_RETRIES = 1 << 2, ///<Radio支持带有冲突避免（CSMA）的tx重试逻辑。
    OT_RADIO_CAPS_CSMA_BACKOFF     = 1 << 3, ///<无线电支持帧传输的CSMA回退（但不重试）。
    OT_RADIO_CAPS_SLEEP_TO_TX      = 1 << 4, ///<无线电支持通过CSMA从休眠到TX的直接转换。
    OT_RADIO_CAPS_TRANSMIT_SEC     = 1 << 5, ///<收音机支持tx安全。
    OT_RADIO_CAPS_TRANSMIT_TIMING  = 1 << 6, ///<收音机在特定时间支持tx。
    OT_RADIO_CAPS_RECEIVE_TIMING   = 1 << 7, ///<收音机在特定时间支持rx。
};

#define OT_PANID_BROADCAST 0xffff ///<IEEE 802.15.4广播PAN ID

/**
 * 此类型表示IEEE 802.15.4 PAN ID。
 *
 */
typedef uint16_t otPanId;

/**
 * 此类型表示IEEE 802.15.4短地址。
 *
 */
typedef uint16_t otShortAddress;

#define OT_EXT_ADDRESS_SIZE 8 ///<IEEE 802.15.4扩展地址的大小（字节）

/**
 * 此枚举定义有关ACK中标头IE大小的常量。
 *
 */
enum
{
    OT_IE_HEADER_SIZE               = 2,  ///<IE标头的大小（字节）。
    OT_CSL_IE_SIZE                  = 4,  ///<CSL IE内容的大小（字节）。
    OT_ACK_IE_MAX_SIZE              = 16, ///<ACK中标头IE的最大长度。
    OT_ENH_PROBING_IE_DATA_MAX_SIZE = 2,  ///<供应商特定IE中链接度量数据的最大长度。
};

#define CSL_IE_HEADER_BYTES_LO 0x04 ///<固定CSL IE头第一字节
#define CSL_IE_HEADER_BYTES_HI 0x0d ///<固定CSL IE头第二字节

/**
 * @struct otExt地址
 *
 * 此结构表示IEEE 802.15.4扩展地址。
 *
 */
OT_TOOL_PACKED_BEGIN
struct otExtAddress
{
    uint8_t m8[OT_EXT_ADDRESS_SIZE]; ///<IEEE 802.15.4扩展地址字节
} OT_TOOL_PACKED_END;

/**
 * 此结构表示IEEE 802.15.4扩展地址。
 *
 */
typedef struct otExtAddress otExtAddress;

#define OT_MAC_KEY_SIZE 16 ///<MAC密钥的大小（字节）。

/**
 * @struct otMacKey
 *
 * 此结构表示MAC密钥。
 *
 */
OT_TOOL_PACKED_BEGIN
struct otMacKey
{
    uint8_t m8[OT_MAC_KEY_SIZE]; ///<MAC密钥字节。
} OT_TOOL_PACKED_END;

/**
 * 此结构表示MAC密钥。
 *
 */
typedef struct otMacKey otMacKey;

/**
 * 此类型表示PSA使用的MAC密钥参考。
 *
 */
typedef otCryptoKeyRef otMacKeyRef;

/**
 * @struct otMacKey材质
 *
 * 此结构表示MAC密钥。
 *
 */
typedef struct otMacKeyMaterial
{
    union
    {
        otMacKeyRef mKeyRef; ///<对存储的密钥的引用。
        otMacKey    mKey;    ///<密钥存储为文本。
    } mKeyMaterial;
} otMacKeyMaterial;

/**
 * 此枚举定义有关键类型的常量。
 *
 */
typedef enum
{
    OT_KEY_TYPE_LITERAL_KEY = 0, ///<使用文字键。
    OT_KEY_TYPE_KEY_REF     = 1, ///<使用密钥引用。
} otRadioKeyType;

/**
 * 该结构表示无线帧的IEEE 802.15.4报头IE（信息元素）相关信息。
 */
typedef struct otRadioIeInfo
{
    int64_t mNetworkTimeOffset; ///<线程网络时间的时间偏移。
    uint8_t mTimeIeOffset;      ///<从PSDU开始的时间IE偏移。
    uint8_t mTimeSyncSeq;       ///<时间同步序列。
} otRadioIeInfo;

/**
 * 该结构表示IEEE 802.15.4无线帧。
 */
typedef struct otRadioFrame
{
    uint8_t *mPsdu; ///<PSDU。

    uint16_t mLength;  ///<PSDU的长度。
    uint8_t  mChannel; ///<用于发送/接收帧的信道。

    uint8_t mRadioType; ///<无线电链路类型-无线电驱动程序应忽略。

    /**
     * 无线电帧的发射和接收信息的联合。
     */
    union
    {
        /**
         * 表示无线帧传输信息的结构。
         */
        struct
        {
            const otMacKeyMaterial *mAesKey;  ///<用于AES-CCM框架安全的关键材料。
            otRadioIeInfo *         mIeInfo;  ///<标题IE相关信息的指针。
            uint32_t                mTxDelay; ///<此传输的延迟时间（基于“mTxDelayBaseTime”）。
            uint32_t                mTxDelayBaseTime; ///<传输延迟的基准时间。
            uint8_t mMaxCsmaBackoffs; ///<宣布CCA失败之前的最大回退尝试次数。
            uint8_t mMaxFrameRetries; ///<传输失败后允许的最大重试次数。

            /**
             * 指示帧计数器和CSL IE是否在标头中正确更新。
             *
             * 如果平台层不提供“OT_RADIO_CAPS_TRANSMIT_SEC”功能，则可以忽略此标志。
             *
             * 如果平台提供“OT_RADIO_CAPS_TRANSMIT_SEC”功能，则平台应处理tx安全处理和帧计数器分配。在这种情况下，预期会出现以下行为：
             *
             * 当设置“mIsHeaderUpdated”时，表示OpenThread内核已经在准备好的帧中设置了帧计数器和CSL IE（如果启用了安全性）。确保计数器与同一帧的先前尝试的计数器值相匹配。平台不应分配或更改帧计数器（但可能仍需要根据“mIsSecurityProcessed”标志执行安全处理）。
             *
             * 如果未设置“mIsHeaderUpdated”，则OpenThread核心未在帧中设置帧计数器和密钥CSL IE，无线电平台负责分配它们。平台必须在通过空中发送帧之前更新帧报头（分配计数器和CSL IE值），但是如果传输被中止并且帧从未通过空中发送（例如，信道接入错误），则平台可以选择不更新报头。如果平台更新了标头，则在将帧从`otPlatRadioTxDone（）`回调传递回之前，还必须设置此标志。
             *
             */
            bool mIsHeaderUpdated : 1;
            bool mIsARetx : 1;             ///<指示帧是否为重传。
            bool mCsmaCaEnabled : 1;       ///<设置为true以启用此数据包的CSMA-CA，否则为false。
            bool mCslPresent : 1;          ///<如果存在CSL标头IE，则设置为true。
            bool mIsSecurityProcessed : 1; ///＜True，如果SubMac应跳过此帧的AES处理。
        } mTxInfo;

        /**
         * 表示无线帧接收信息的结构。
         */
        struct
        {
            /**
             * 接收帧时的时间戳（以微秒为单位）。
             *
             * 该值应为启用time_SYNC或CSL时收到SFD的时间。否则，MAC帧被完全接收的时间也是可接受的。
             *
             */
            uint64_t mTimestamp;

            uint32_t mAckFrameCounter; ///<ACK安全帧计数器（设置“mAckedWithSecEnhAck”时适用）。
            uint8_t  mAckKeyId;        ///<ACK安全密钥索引（设置“mAckedWithSecEnhAck”时适用）。
            int8_t   mRssi;            ///<接收帧的接收信号强度指示符，单位为dBm。
            uint8_t  mLqi;             ///<接收帧的链路质量指示符。

            // 旗帜
            bool mAckedWithFramePending : 1; ///<这表示此帧是否已通过帧挂起设置确认。
            bool mAckedWithSecEnhAck : 1; ///<这表示该帧是否通过安全增强ACK确认。
        } mRxInfo;
    } mInfo;
} otRadioFrame;

/**
 * 此结构表示收音机的状态。最初，收音机处于禁用状态。
 */
typedef enum otRadioState
{
    OT_RADIO_STATE_DISABLED = 0,
    OT_RADIO_STATE_SLEEP    = 1,
    OT_RADIO_STATE_RECEIVE  = 2,
    OT_RADIO_STATE_TRANSMIT = 3,
    OT_RADIO_STATE_INVALID  = 255,
} otRadioState;

/**
 * 以下是有效的无线电状态转换：
 *
 *                                    （收音机打开）+--------+启用（）+--------+Receive（）+----------+发送（）+------------+|---------->||---------->| |---------->|| |---------->|1|---------->已禁用||Sleep||Receive||Transmit |||<---------||<-------||<-----------||+----------+禁用（）+---------------+休眠（）+-----+接收（）+----+（收音机关闭）或信号发送完成
 *
 * 在IEEE 802.15.4数据请求命令期间，如果平台支持OT_RADIO_CAPS_Sleep_to_TX功能，则可以将睡眠->接收->传输转换缩短为直接从睡眠转换为传输。
 */

/**
 * 此结构表示无线电共存度量。
 */
typedef struct otRadioCoexMetrics
{
    uint32_t mNumGrantGlitch;          ///<授权故障数。
    uint32_t mNumTxRequest;            ///<tx请求数。
    uint32_t mNumTxGrantImmediate;     ///<授权处于活动状态时的tx请求数。
    uint32_t mNumTxGrantWait;          ///<授权处于非活动状态时的tx请求数。
    uint32_t mNumTxGrantWaitActivated; ///<授予处于非活动状态时最终授予的tx请求数。
    uint32_t mNumTxGrantWaitTimeout;   ///<授权处于非活动状态时超时的tx请求数。
    uint32_t mNumTxGrantDeactivatedDuringRequest; ///<授权停用时正在进行的tx数。
    uint32_t mNumTxDelayedGrant;                  ///<50us内未授权的tx请求数。
    uint32_t mAvgTxRequestToGrantTime;            ///<从tx请求到授权的平均使用时间。
    uint32_t mNumRxRequest;                       ///<rx请求数。
    uint32_t mNumRxGrantImmediate;                ///<授权处于活动状态时的rx请求数。
    uint32_t mNumRxGrantWait;                     ///<授权处于非活动状态时的rx请求数。
    uint32_t mNumRxGrantWaitActivated; ///<授予处于非活动状态时最终授予的rx请求数。
    uint32_t mNumRxGrantWaitTimeout;   ///<授权处于非活动状态时超时的rx请求数。
    uint32_t mNumRxGrantDeactivatedDuringRequest; ///<授权停用时正在进行的rx数。
    uint32_t mNumRxDelayedGrant;                  ///<50us内未授权的rx请求数。
    uint32_t mAvgRxRequestToGrantTime;            ///<从rx请求到授权的平均使用时间。
    uint32_t mNumRxGrantNone;                     ///<未收到授权而完成的rx请求数。
    bool     mStopped;                            ///<Stats收集因饱和而停止。
} otRadioCoexMetrics;

/**
 * 此结构表示指定要查询的度量。
 *
 */
typedef struct otLinkMetrics
{
    bool mPduCount : 1;   ///<Pdu计数。
    bool mLqi : 1;        ///<链路质量指示器。
    bool mLinkMargin : 1; ///<链接边距。
    bool mRssi : 1;       ///<接收信号强度指示器。
    bool mReserved : 1;   ///<保留，这是参考设备。
} otLinkMetrics;

/**
 * @}
 *
 */

/**
 * @defgroup 无线电配置配置
 *
 * @brief 该模块包括无线电配置的平台抽象。
 *
 * @{
 *
 */

/**
 * 获取无线电功能。
 *
 * @param[in] aInstance  OpenThread实例结构。
 *
 * @returns 无线电能力位向量（参见“OT_radio_CAP_*”定义）。
 *
 */
otRadioCaps otPlatRadioGetCaps(otInstance *aInstance);

/**
 * 获取无线电版本字符串。
 *
 * 这是可选的无线电驾驶员平台功能。如果平台无线电驱动程序不提供，OpenThread将使用OpenThread版本（@sa-otGetVersionString（））。
 *
 * @param[in]  aInstance   OpenThread实例结构。
 *
 * @returns 指向OpenThread无线电版本的指针。
 *
 */
const char *otPlatRadioGetVersionString(otInstance *aInstance);

/**
 * 获取无线电接收灵敏度值。
 *
 * @param[in] aInstance  OpenThread实例结构。
 *
 * @returns 无线电接收灵敏度值，单位为dBm。
 *
 */
int8_t otPlatRadioGetReceiveSensitivity(otInstance *aInstance);

/**
 * 获取此接口的工厂分配IEEE EUI-64。
 *
 * @param[in]  aInstance   OpenThread实例结构。
 * @param[out] aIeeeEui64  指向工厂指定的IEEE EUI-64的指针。
 *
 */
void otPlatRadioGetIeeeEui64(otInstance *aInstance, uint8_t *aIeeeEui64);

/**
 * 设置地址筛选的PAN ID。
 *
 * @param[in] aInstance  OpenThread实例结构。
 * @param[in] aPanId     IEEE 802.15.4 PAN ID。
 *
 */
void otPlatRadioSetPanId(otInstance *aInstance, otPanId aPanId);

/**
 * 设置地址筛选的扩展地址。
 *
 * @param[in] aInstance    OpenThread实例结构。
 * @param[in] aExtAddress  指向以小端字节顺序存储的IEEE 802.15.4扩展地址的指针。
 *
 *
 */
void otPlatRadioSetExtendedAddress(otInstance *aInstance, const otExtAddress *aExtAddress);

/**
 * 设置地址筛选的短地址。
 *
 * @param[in] aInstance      OpenThread实例结构。
 * @param[in] aShortAddress  IEEE 802.15.4短地址。
 *
 */
void otPlatRadioSetShortAddress(otInstance *aInstance, otShortAddress aShortAddress);

/**
 * 以dBm为单位获取无线电发射功率。
 *
 * @note 返回的发射功率将不大于当前信道的最大功率表中指定的功率。
 *
 * @param[in] aInstance  OpenThread实例结构。
 * @param[out] aPower    发射功率（dBm）。
 *
 * @retval OT_ERROR_NONE成功检索到发射功率。
 * @retval OT_ERROR_INVALID_ARGS@p aPower为空。
 * @retval OT_ERROR_NOT_IMPLEMENTED未实现通过dBm的发射功率配置。
 *
 */
otError otPlatRadioGetTransmitPower(otInstance *aInstance, int8_t *aPower);

/**
 * 设置收音机的发射功率，单位为dBm。
 *
 * @note 实际发射功率将不大于当前信道的最大功率表中指定的功率。
 *
 * @param[in] aInstance  OpenThread实例结构。
 * @param[in] aPower     发射功率（dBm）。
 *
 * @retval OT_ERROR_NONE成功设置发射功率。
 * @retval OT_ERROR_NOT_IMPLEMENTED未实现通过dBm的发射功率配置。
 *
 */
otError otPlatRadioSetTransmitPower(otInstance *aInstance, int8_t aPower);

/**
 * 根据IEEE 802.15.4-2015第10.1.4节，获取在天线连接器处测量的无线电CCA ED阈值（dBm）。
 *
 * @param[in] aInstance    OpenThread实例结构。
 * @param[out] aThreshold  CCA ED阈值（dBm）。
 *
 * @retval OT_ERROR_NONE已成功检索CCA ED阈值。
 * @retval OT_ERROR_INVALID_ARGS@p aThreshold为空。
 * @retval 未通过dBm实现OT_ERROR_NOT_IMPLEMENTED CCA ED阈值配置。
 *
 */
otError otPlatRadioGetCcaEnergyDetectThreshold(otInstance *aInstance, int8_t *aThreshold);

/**
 * 根据IEEE 802.15.4-2015第10.1.4节，设置在天线连接器处测量的无线电CCA ED阈值（单位：dBm）。
 *
 * @param[in] aInstance   OpenThread实例结构。
 * @param[in] aThreshold  CCA ED阈值（dBm）。
 *
 * @retval OT_ERROR_NONE成功设置发射功率。
 * @retval OT_ERROR_INVALID_ARGS给定阈值超出范围。
 * @retval 未通过dBm实现OT_ERROR_NOT_IMPLEMENTED CCA ED阈值配置。
 *
 */
otError otPlatRadioSetCcaEnergyDetectThreshold(otInstance *aInstance, int8_t aThreshold);

/**
 * 获取外部FEM的Rx LNA增益（单位：dBm）。
 *
 * @param[in]  aInstance  OpenThread实例结构。
 * @param[out] aGain     外部FEM的Rx LNA增益（dBm）。
 *
 * @retval OT_ERROR_NONE成功检索到外部FEM的LNA增益。
 * @retval OT_ERROR_INVALID_ARGS@p aGain为空。
 * @retval OT_ERROR_NOT_IMPLEMENTED外部FEM的LNA设置未实现。
 *
 */
otError otPlatRadioGetFemLnaGain(otInstance *aInstance, int8_t *aGain);

/**
 * 以dBm为单位设置外部FEM的Rx LNA增益。
 *
 * @param[in] aInstance  OpenThread实例结构。
 * @param[in] aGain      外部FEM的Rx LNA增益（dBm）。
 *
 * @retval OT_ERROR_NONE成功设置外部FEM的LNA增益。
 * @retval OT_ERROR_NOT_IMPLEMENTED外部FEM的LNA增益设置未实现。
 *
 */
otError otPlatRadioSetFemLnaGain(otInstance *aInstance, int8_t aGain);

/**
 * 获取混杂模式的状态。
 *
 * @param[in] aInstance  OpenThread实例结构。
 *
 * @retval TRUE混杂模式已启用。
 * @retval FALSE混杂模式已禁用。
 *
 */
bool otPlatRadioGetPromiscuous(otInstance *aInstance);

/**
 * 启用或禁用混杂模式。
 *
 * @param[in]  aInstance OpenThread实例结构。
 * @param[in]  aEnable   TRUE表示启用，FALSE表示禁用混杂模式。
 *
 */
void otPlatRadioSetPromiscuous(otInstance *aInstance, bool aEnable);

/**
 * 更新MAC密钥和密钥索引
 *
 * 当无线电提供OT_radio_CAPS_TRANSMIT_SEC功能时，使用此功能。
 *
 * @param[in]   aInstance    指向OpenThread实例的指针。
 * @param[in]   aKeyIdMode   钥匙ID模式。
 * @param[in]   aKeyId       当前MAC密钥索引。
 * @param[in]   aPrevKey     指向上一个MAC密钥的指针。
 * @param[in]   aCurrKey     指向当前MAC密钥的指针。
 * @param[in]   aNextKey     指向下一个MAC密钥的指针。
 * @param[in]   aKeyType     使用的密钥类型。
 *
 */
void otPlatRadioSetMacKey(otInstance *            aInstance,
                          uint8_t                 aKeyIdMode,
                          uint8_t                 aKeyId,
                          const otMacKeyMaterial *aPrevKey,
                          const otMacKeyMaterial *aCurrKey,
                          const otMacKeyMaterial *aNextKey,
                          otRadioKeyType          aKeyType);

/**
 * 此方法设置当前MAC帧计数器值。
 *
 * 当收音机提供“OT_radio_CAPS_TRANSMIT_SEC”功能时，使用此功能。
 *
 * @param[in]   aInstance         指向OpenThread实例的指针。
 * @param[in]   aMacFrameCounter  MAC帧计数器值。
 *
 */
void otPlatRadioSetMacFrameCounter(otInstance *aInstance, uint32_t aMacFrameCounter);

/**
 * 获取无线电芯片的当前估计时间（64位宽度）。
 *
 * @param[in]   aInstance    指向OpenThread实例的指针。
 *
 * @returns 当前时间（以微秒为单位）。UINT64_MAX，当平台不支持或无线电时间未就绪时。
 *
 */
uint64_t otPlatRadioGetNow(otInstance *aInstance);

/**
 * 获取主机和无线电芯片之间的总线速度（以位/秒为单位）。
 *
 * @param[in]   aInstance    指向OpenThread实例的指针。
 *
 * @returns 主机和无线电芯片之间的总线速度（以位/秒为单位）。当MAC及以上层和无线层位于同一芯片上时，返回0。
 *
 */
uint32_t otPlatRadioGetBusSpeed(otInstance *aInstance);

/**
 * @}
 *
 */

/**
 * @defgroup 无线电操作操作
 *
 * @brief 该模块包括无线电操作的平台抽象。
 *
 * @{
 *
 */

/**
 * 获取收音机的当前状态。
 *
 * OpenThread不需要此函数。它可用于调试和/或应用程序特定目的。
 *
 * @note 此功能可能未实现。它不会影响OpenThread。
 *
 * @param[in] aInstance  OpenThread实例结构。
 *
 * @return  收音机的当前状态。
 *
 */
otRadioState otPlatRadioGetState(otInstance *aInstance);

/**
 * 启用收音机。
 *
 * @param[in] aInstance  OpenThread实例结构。
 *
 * @retval OT_ERROR_NONE已成功启用。
 * @retval OT_ERROR_FAILED无法启用无线电。
 *
 */
otError otPlatRadioEnable(otInstance *aInstance);

/**
 * 禁用收音机。
 *
 * @param[in] aInstance  OpenThread实例结构。
 *
 * @retval OT_ERROR_NONE已成功转换为禁用。
 * @retval OT_ERROR_INVALID_STATE收音机未处于睡眠状态。
 *
 */
otError otPlatRadioDisable(otInstance *aInstance);

/**
 * 检查收音机是否已启用。
 *
 * @param[in] aInstance  OpenThread实例结构。
 *
 * @returns 如果启用无线电，则为TRUE，否则为FALSE。
 *
 */
bool otPlatRadioIsEnabled(otInstance *aInstance);

/**
 * 将收音机从“接收”切换到“睡眠”（关闭收音机）。
 *
 * @param[in] aInstance  OpenThread实例结构。
 *
 * @retval OT_ERROR_NONE已成功转换为睡眠。
 * @retval OT_ERROR_BUSY收音机正在发射。
 * @retval OT_ERROR_INVALID_STATE无线电已禁用。
 *
 */
otError otPlatRadioSleep(otInstance *aInstance);

/**
 * 将收音机从“睡眠”切换到“接收”（打开收音机）。
 *
 * @param[in]  aInstance  OpenThread实例结构。
 * @param[in]  aChannel   用于接收的频道。
 *
 * @retval OT_ERROR_NONE已成功转换为接收。
 * @retval OT_ERROR_INVALID_STATE无线电已禁用或正在发送。
 *
 */
otError otPlatRadioReceive(otInstance *aInstance, uint8_t aChannel);

/**
 * 在特定时间和持续时间安排无线电接收窗口。
 *
 * @param[in]  aChannel   要接收的无线电信道。
 * @param[in]  aStart     接收窗口开始时间，以微秒为单位。
 * @param[in]  aDuration  接收窗口持续时间，以微秒为单位
 *
 * @retval OT_ERROR_NONE已成功计划接收窗口。
 * @retval OT_ERROR_FAILED无法计划接收窗口。
 */
otError otPlatRadioReceiveAt(otInstance *aInstance, uint8_t aChannel, uint32_t aStart, uint32_t aDuration);

/**
 * 无线电驱动程序调用此方法以通知OpenThread接收到的帧。
 *
 * @param[in]  aInstance OpenThread实例结构。
 * @param[in]  aFrame    指向接收帧的指针，如果接收操作失败，则返回NULL。
 * @param[in]  aError    OT_ERROR_NONE（当成功接收到帧时）、OT_ERROR _ABORT（当接收被中止且未接收到帧）、OT-ERROR_NO_BUFS（当由于缺少rx缓冲区空间而无法接收帧时）。
 *
 */
extern void otPlatRadioReceiveDone(otInstance *aInstance, otRadioFrame *aFrame, otError aError);

/**
 * 无线电驱动程序调用此方法以通知OpenThread诊断模块收到的帧。
 *
 * 启用诊断时使用此功能。
 *
 * @param[in]  aInstance OpenThread实例结构。
 * @param[in]  aFrame    指向接收帧的指针，如果接收操作失败，则返回NULL。
 * @param[in]  aError    OT_ERROR_NONE（当成功接收到帧时）、OT_ERROR _ABORT（当接收被中止且未接收到帧）、OT-ERROR_NO_BUFS（当由于缺少rx缓冲区空间而无法接收帧时）。
 *
 */
extern void otPlatDiagRadioReceiveDone(otInstance *aInstance, otRadioFrame *aFrame, otError aError);

/**
 * 获取无线电传输帧缓冲区。
 *
 * OpenThread在此缓冲区中形成IEEE 802.15.4帧，然后调用“otPlatRadioTransmit（）”请求传输。
 *
 * @param[in] aInstance  OpenThread实例结构。
 *
 * @returns 指向传输帧缓冲区的指针。
 *
 */
otRadioFrame *otPlatRadioGetTransmitBuffer(otInstance *aInstance);

/**
 * 在收音机上开始发射序列。
 *
 * 在请求传输之前，调用者必须在“otPlatRadioGetTransmitBuffer（）”提供的缓冲区中形成IEEE 802.15.4帧。otRadioFrame结构中还包括信道和发射功率。
 *
 * 发射序列包括：1.将无线电从以下状态之一转换为发射：
 *    -如果设备空闲或不支持OT_RADIO_CAPS_SLEEP_TO_TX时RX打开，则接收
 *    -如果设备空闲且支持OT_RADIO_CAPS_Sleep_TO_TX时RX关闭，则休眠。2.在给定信道上以给定发射功率发射psdu。
 *
 * @param[in] aInstance  OpenThread实例结构。
 * @param[in] aFrame     指向要传输的帧的指针。
 *
 * @retval OT_ERROR_NONE已成功转换为传输。
 * @retval OT_ERROR_INVALID_STATE无线电未处于接收状态。
 *
 */
otError otPlatRadioTransmit(otInstance *aInstance, otRadioFrame *aFrame);

/**
 * 无线电驱动程序调用此方法以通知OpenThread传输已开始。
 *
 * @note  该函数应由执行所有其他OpenThread代码的同一线程调用。ISR或任何其他任务都不应调用它。
 *
 * @param[in]  aInstance  指向OpenThread实例结构的指针。
 * @param[in]  aFrame     指向正在传输的帧的指针。
 *
 */
extern void otPlatRadioTxStarted(otInstance *aInstance, otRadioFrame *aFrame);

/**
 * 无线电驱动程序调用此函数以通知OpenThread发送操作已完成，同时提供发送的帧和接收的ack帧（如果适用）。
 *
 * 当无线电提供“OT_radio_CAPS_TRANSMIT_SEC”功能时，无线电平台层使用无线电维护的安全帧计数器和密钥索引值更新@p aFrame。
 *
 * @param[in]  aInstance  OpenThread实例结构。
 * @param[in]  aFrame     指向传输的帧的指针。
 * @param[in]  aAckFrame  指向ACK帧的指针，如果没有收到ACK，则为NULL。
 * @param[in]  aError     当发送帧时为OT_ERROR_NONE，当发送帧但未收到ACK时为OT-ERROR_NO_ACK，由于信道上的活动而无法进行OT_ERROR_CHANNEL_ACCESS_FAILURE tx，当传输因其他原因而中止时为OT.ERROR_ABORT。
 *
 */
extern void otPlatRadioTxDone(otInstance *aInstance, otRadioFrame *aFrame, otRadioFrame *aAckFrame, otError aError);

/**
 * 无线电驱动程序调用此方法以通知OpenThread诊断模块传输已完成。
 *
 * 启用诊断时使用此功能。
 *
 * @param[in]  aInstance      OpenThread实例结构。
 * @param[in]  aFrame         指向传输的帧的指针。
 * @param[in]  aError         传输帧时OT_ERROR_NONE，由于信道上的活动，OT_ERROR_CHANNEL_ACCESS_FAILURE tx无法发生，传输因其他原因中止时OT_EERROR_ABORT。
 *
 */
extern void otPlatDiagRadioTransmitDone(otInstance *aInstance, otRadioFrame *aFrame, otError aError);

/**
 * 获取最近的RSSI测量值。
 *
 * @param[in] aInstance  OpenThread实例结构。
 *
 * @returns 有效时的RSSI单位为dBm。当RSSI无效时为127。
 *
 */
int8_t otPlatRadioGetRssi(otInstance *aInstance);

/**
 * 开始收音机的能量扫描序列。
 *
 * 当收音机提供OT_radio_CAPS_ENERGY_SCAN功能时，使用此功能。
 *
 * @param[in] aInstance      OpenThread实例结构。
 * @param[in] aScanChannel   要执行能量扫描的通道。
 * @param[in] aScanDuration  要扫描的通道的持续时间（毫秒）。
 *
 * @retval OT_ERROR_NONE已成功开始扫描通道。
 * @retval OT_ERROR_NOT_IMPLEMENTED收音机不支持能量扫描。
 *
 */
otError otPlatRadioEnergyScan(otInstance *aInstance, uint8_t aScanChannel, uint16_t aScanDuration);

/**
 * 无线电驱动程序调用此方法以通知OpenThread能量扫描已完成。
 *
 * 当收音机提供OT_radio_CAPS_ENERGY_SCAN功能时，使用此功能。
 *
 * @param[in]  aInstance           OpenThread实例结构。
 * @param[in]  aEnergyScanMaxRssi  扫描信道上遇到的最大RSSI。
 *
 */
extern void otPlatRadioEnergyScanDone(otInstance *aInstance, int8_t aEnergyScanMaxRssi);

/**
 * 启用/禁用源地址匹配功能。
 *
 * 源地址匹配功能控制无线层如何为响应子级的数据请求命令而发送的ack确定“帧挂起”位。
 *
 * 如果禁用，则无线层必须在所有ack上设置“帧挂起”以请求数据命令。
 *
 * 如果启用，则无线层使用源地址匹配表来确定是否设置或清除数据请求命令确认中的“帧挂起”位。
 *
 * 源地址匹配表提供存在挂起帧的子级列表。可以将短地址或扩展/长地址添加到源地址匹配表中。
 *
 * @param[in]  aInstance   OpenThread实例结构。
 * @param[in]  aEnable     启用/禁用源地址匹配功能。
 *
 */
void otPlatRadioEnableSrcMatch(otInstance *aInstance, bool aEnable);

/**
 * 将短地址添加到源地址匹配表中。
 *
 * @param[in]  aInstance      OpenThread实例结构。
 * @param[in]  aShortAddress  要添加的短地址。
 *
 * @retval OT_ERROR_NONE已成功将短地址添加到源匹配表。
 * @retval OT_ERROR_NO_BUFS源匹配表中没有可用条目。
 *
 */
otError otPlatRadioAddSrcMatchShortEntry(otInstance *aInstance, otShortAddress aShortAddress);

/**
 * 将扩展地址添加到源地址匹配表中。
 *
 * @param[in]  aInstance    OpenThread实例结构。
 * @param[in]  aExtAddress  要添加的扩展地址以小端字节顺序存储。
 *
 * @retval OT_ERROR_NONE已成功将扩展地址添加到源匹配表。
 * @retval OT_ERROR_NO_BUFS源匹配表中没有可用条目。
 *
 */
otError otPlatRadioAddSrcMatchExtEntry(otInstance *aInstance, const otExtAddress *aExtAddress);

/**
 * 从源地址匹配表中删除短地址。
 *
 * @param[in]  aInstance      OpenThread实例结构。
 * @param[in]  aShortAddress  要删除的短地址。
 *
 * @retval OT_ERROR_NONE已成功从源匹配表中删除短地址。
 * @retval OT_ERROR_NO_ADDRESS短地址不在源地址匹配表中。
 *
 */
otError otPlatRadioClearSrcMatchShortEntry(otInstance *aInstance, otShortAddress aShortAddress);

/**
 * 从源地址匹配表中删除扩展地址。
 *
 * @param[in]  aInstance    OpenThread实例结构。
 * @param[in]  aExtAddress  要删除的扩展地址以小端字节顺序存储。
 *
 * @retval OT_ERROR_NONE已成功从源匹配表中删除扩展地址。
 * @retval OT_ERROR_NO_ADDRESS扩展地址不在源地址匹配表中。
 *
 */
otError otPlatRadioClearSrcMatchExtEntry(otInstance *aInstance, const otExtAddress *aExtAddress);

/**
 * 清除源地址匹配表中的所有短地址。
 *
 * @param[in]  aInstance   OpenThread实例结构。
 *
 */
void otPlatRadioClearSrcMatchShortEntries(otInstance *aInstance);

/**
 * 清除源地址匹配表中的所有扩展/长地址。
 *
 * @param[in]  aInstance   OpenThread实例结构。
 *
 */
void otPlatRadioClearSrcMatchExtEntries(otInstance *aInstance);

/**
 * 获取设备允许打开的无线电支持频道掩码。
 *
 * @param[in]  aInstance   OpenThread实例结构。
 *
 * @returns 收音机支持的频道掩码。
 *
 */
uint32_t otPlatRadioGetSupportedChannelMask(otInstance *aInstance);

/**
 * 获取设备首选的电台频道掩码。
 *
 * @param[in]  aInstance   OpenThread实例结构。
 *
 * @returns 收音机首选频道掩码。
 *
 */
uint32_t otPlatRadioGetPreferredChannelMask(otInstance *aInstance);

/**
 * 启用无线电coex。
 *
 * 启用OPENTHREAD_CONFIG_PLATFORM_RADIO_COEX_ENABLE功能时使用此功能。
 *
 * @param[in] aInstance  OpenThread实例结构。
 * @param[in] aEnabled   TRUE表示启用无线电coex，否则为FALSE。
 *
 * @retval OT_ERROR_NONE已成功启用。
 * @retval OT_ERROR_FAILED无法启用无线电coex。
 *
 */
otError otPlatRadioSetCoexEnabled(otInstance *aInstance, bool aEnabled);

/**
 * 检查无线电coex是否已启用。
 *
 * 启用OPENTHREAD_CONFIG_PLATFORM_RADIO_COEX_ENABLE功能时使用此功能。
 *
 * @param[in] aInstance  OpenThread实例结构。
 *
 * @returns 如果启用了无线电coex，则为TRUE，否则为FALSE。
 *
 */
bool otPlatRadioIsCoexEnabled(otInstance *aInstance);

/**
 * 获取无线电共存指标。
 *
 * 启用OPENTHREAD_CONFIG_PLATFORM_RADIO_COEX_ENABLE功能时使用此功能。
 *
 * @param[in]  aInstance     OpenThread实例结构。
 * @param[out] aCoexMetrics  指向共存度量结构的指针。
 *
 * @retval OT_ERROR_NONE已成功检索coex指标。
 * @retval OT_ERROR_INVALID_ARGS@p aCoexMetrics为空。
 */
otError otPlatRadioGetCoexMetrics(otInstance *aInstance, otRadioCoexMetrics *aCoexMetrics);

/**
 * 启用或禁用CSL接收器。
 *
 * @param[in]  aInstance     OpenThread实例结构。
 * @param[in]  aCslPeriod    CSL周期，0表示禁用CSL。
 * @param[in]  aShortAddr    CSL接收方对等方的短源地址。
 * @param[in]  aExtAddr      CSL接收方对等方的扩展源地址。
 *
 * @note 平台在生成增强ack时应使用CSL对等地址来包括CSL IE。
 *
 * @retval  kErrorNotImplemented Radio驱动程序不支持CSL。
 * @retval  kErrorFailed其他特定于平台的错误。
 * @retval  kErrorNone已成功启用或禁用CSL。
 *
 */
otError otPlatRadioEnableCsl(otInstance *        aInstance,
                             uint32_t            aCslPeriod,
                             otShortAddress      aShortAddr,
                             const otExtAddress *aExtAddr);

/**
 * 更新无线电驱动程序中的CSL采样时间。
 *
 * 采样时间作为副本存储在无线电驱动器中，以计算使用CSL IE发送ACK时的相位。
 *
 * @param[in]  aInstance         OpenThread实例结构。
 * @param[in]  aCslSampleTime    最新采样时间。
 *
 */
void otPlatRadioUpdateCslSampleTime(otInstance *aInstance, uint32_t aCslSampleTime);

/**
 * 获取用于调度CSL操作的时钟的当前精度，单位为±ppm。
 *
 * @note 平台可根据操作条件（即：温度）优化该值。
 *
 * @param[in]   aInstance    指向OpenThread实例的指针。
 *
 * @returns 当前CSL rx/tx调度漂移，单位为±ppm。
 *
 */
uint8_t otPlatRadioGetCslAccuracy(otInstance *aInstance);

/**
 * 获取用于调度CSL操作的时钟的当前不确定性，单位为10us。
 *
 * @param[in]   aInstance    指向OpenThread实例的指针。
 *
 * @returns 当前CSL时钟不确定性单位为10 us。
 *
 */
uint8_t otPlatRadioGetCslClockUncertainty(otInstance *aInstance);

/**
 * 设置特定信道的最大发射功率。
 *
 * @param[in]  aInstance    OpenThread实例结构。
 * @param[in]  aChannel     无线电频道。
 * @param[in]  aMaxPower    通过OT_RADIO_RSSI_INVALID的最大功率（dBm）将禁用此信道。
 *
 * @retval  OT_ERROR_NOT_IMPLEMENTED功能未实现
 * @retval  OT_ERROR_INVALID_ARGS指定的通道无效。
 * @retval  OT_ERROR_FAILED其他特定于平台的错误。
 * @retval  OT_ERROR_NONE成功设置最大发射功率。
 *
 */
otError otPlatRadioSetChannelMaxTransmitPower(otInstance *aInstance, uint8_t aChannel, int8_t aMaxPower);

/**
 * 设置地区代码。
 *
 * 无线电区域格式是ISO 3166字母-2代码的2字节ascii表示。
 *
 * @param[in]  aInstance    OpenThread实例结构。
 * @param[in]  aRegionCode  无线电区域。
 *
 * @retval  OT_ERROR_FAILED其他特定于平台的错误。
 * @retval  OT_ERROR_NONE已成功设置地区代码。
 *
 */
otError otPlatRadioSetRegion(otInstance *aInstance, uint16_t aRegionCode);

/**
 * 获取地区代码。
 *
 * 无线电区域格式是ISO 3166字母-2代码的2字节ascii表示。

 * @param[in]  aInstance    OpenThread实例结构。
 * @param[out] aRegionCode  无线电区域。
 *
 * @retval  OT_ERROR_INVALID_ARGS@p aRegionCode为nullptr。
 * @retval  OT_ERROR_FAILED其他特定于平台的错误。
 * @retval  OT_ERROR_NONE已成功获取地区代码。
 *
 */
otError otPlatRadioGetRegion(otInstance *aInstance, uint16_t *aRegionCode);

/**
 * 为特定启动器启用/禁用或更新无线电中的增强型基于ACK的探测。
 *
 * 在特定探测发起方配置基于增强ACK的探测后，发送到该节点的增强ACK应包括包含链路度量数据的供应商特定IE。该方法通知无线电启动/停止以收集链路度量数据，并包括供应商特定IE，该IE包含发送给该探测发起方的增强ACK中的数据。
 *
 * @param[in]  aInstance     OpenThread实例结构。
 * @param[in]  aLinkMetrics  此参数指定要查询的度量。根据规范4.11.3.4.4.6，最多可指定2个指标。如果@p`aLinkMetrics`按位为0，则将禁用探测。
 * @param[in]  aShortAddr    探测启动器的短地址。
 * @param[in]  aExtAddr      探测启动器的扩展源地址@p aExtAddr不能为“NULL”。
 *
 * @retval  OT_ERROR_NONE已成功配置增强型基于ACK的探测。
 * @retval  OT_ERROR_INVALID_ARGS@p aExtAddress为“NULL”。
 * @retval  OT_ERROR_NOT_FOUND尝试清除时找不到@p aShortAddress指示的启动器。
 * @retval  OT_ERROR_NO_BUFS无法支持更多启动器。
 *
 */
otError otPlatRadioConfigureEnhAckProbing(otInstance *        aInstance,
                                          otLinkMetrics       aLinkMetrics,
                                          otShortAddress      aShortAddress,
                                          const otExtAddress *aExtAddress);

/**
 * @}
 *
 */

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”结尾
#endif

#endif // OPENTHREAD_PLATFORM_RADIO_H_

