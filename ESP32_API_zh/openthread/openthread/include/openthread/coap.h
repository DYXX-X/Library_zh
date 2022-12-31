/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThreadCoAP实现的顶级函数。
 */

#ifndef OPENTHREAD_COAP_H_
#define OPENTHREAD_COAP_H_

#include <stdint.h>

#include <openthread/ip6.h>
#include <openthread/message.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup 美国石油学会
 *
 * @brief 该模块包括控制CoAP通信的功能。
 *
 *   启用CoAP API功能（`OPENTHREAD_COONFIG_CoAP_API_ENABLE`）时，此模块中的功能可用。
 *
 * @{
 *
 */

#define OT_DEFAULT_COAP_PORT 5683 ///<RFC 7252中指定的默认CoAP端口

#define OT_COAP_DEFAULT_TOKEN_LENGTH 2 ///<默认令牌长度。

#define OT_COAP_MAX_TOKEN_LENGTH 8 ///<指定的最大令牌长度（RFC 7252）。

#define OT_COAP_MAX_RETRANSMIT 20 ///<OpenThread支持的最大重传。

#define OT_COAP_MIN_ACK_TIMEOUT 1000 ///＜OpenThread支持的最小ACK超时（毫秒）。

/**
 * CoAP类型值（2位无符号整数）。
 *
 */
typedef enum otCoapType
{
    OT_COAP_TYPE_CONFIRMABLE     = 0, ///<可确认
    OT_COAP_TYPE_NON_CONFIRMABLE = 1, ///<不可确认
    OT_COAP_TYPE_ACKNOWLEDGMENT  = 2, ///<确认
    OT_COAP_TYPE_RESET           = 3, ///<重置
} otCoapType;

/**
 * 用于定义CoAP代码值的帮助程序宏。
 *
 */
#define OT_COAP_CODE(c, d) ((((c)&0x7) << 5) | ((d)&0x1f))

/**
 * CoAP代码值。
 *
 */
typedef enum otCoapCode
{
    OT_COAP_CODE_EMPTY  = OT_COAP_CODE(0, 0), ///<空消息代码
    OT_COAP_CODE_GET    = OT_COAP_CODE(0, 1), ///<获取
    OT_COAP_CODE_POST   = OT_COAP_CODE(0, 2), ///<发布
    OT_COAP_CODE_PUT    = OT_COAP_CODE(0, 3), ///<看跌期权
    OT_COAP_CODE_DELETE = OT_COAP_CODE(0, 4), ///<删除

    OT_COAP_CODE_RESPONSE_MIN = OT_COAP_CODE(2, 0),  ///< 2.00
    OT_COAP_CODE_CREATED      = OT_COAP_CODE(2, 1),  ///<已创建
    OT_COAP_CODE_DELETED      = OT_COAP_CODE(2, 2),  ///<已删除
    OT_COAP_CODE_VALID        = OT_COAP_CODE(2, 3),  ///<有效
    OT_COAP_CODE_CHANGED      = OT_COAP_CODE(2, 4),  ///<已更改
    OT_COAP_CODE_CONTENT      = OT_COAP_CODE(2, 5),  ///<内容
    OT_COAP_CODE_CONTINUE     = OT_COAP_CODE(2, 31), ///<RFC7959继续

    OT_COAP_CODE_BAD_REQUEST         = OT_COAP_CODE(4, 0),  ///<错误请求
    OT_COAP_CODE_UNAUTHORIZED        = OT_COAP_CODE(4, 1),  ///<未授权
    OT_COAP_CODE_BAD_OPTION          = OT_COAP_CODE(4, 2),  ///<坏选项
    OT_COAP_CODE_FORBIDDEN           = OT_COAP_CODE(4, 3),  ///<禁止
    OT_COAP_CODE_NOT_FOUND           = OT_COAP_CODE(4, 4),  ///<未找到
    OT_COAP_CODE_METHOD_NOT_ALLOWED  = OT_COAP_CODE(4, 5),  ///<不允许的方法
    OT_COAP_CODE_NOT_ACCEPTABLE      = OT_COAP_CODE(4, 6),  ///<不可接受
    OT_COAP_CODE_REQUEST_INCOMPLETE  = OT_COAP_CODE(4, 8),  ///<RFC7959请求实体不完整
    OT_COAP_CODE_PRECONDITION_FAILED = OT_COAP_CODE(4, 12), ///<前提条件失败
    OT_COAP_CODE_REQUEST_TOO_LARGE   = OT_COAP_CODE(4, 13), ///<请求实体太大
    OT_COAP_CODE_UNSUPPORTED_FORMAT  = OT_COAP_CODE(4, 15), ///<不支持的内容格式

    OT_COAP_CODE_INTERNAL_ERROR      = OT_COAP_CODE(5, 0), ///<内部服务器错误
    OT_COAP_CODE_NOT_IMPLEMENTED     = OT_COAP_CODE(5, 1), ///<未实施
    OT_COAP_CODE_BAD_GATEWAY         = OT_COAP_CODE(5, 2), ///<坏网关
    OT_COAP_CODE_SERVICE_UNAVAILABLE = OT_COAP_CODE(5, 3), ///<服务不可用
    OT_COAP_CODE_GATEWAY_TIMEOUT     = OT_COAP_CODE(5, 4), ///<网关超时
    OT_COAP_CODE_PROXY_NOT_SUPPORTED = OT_COAP_CODE(5, 5), ///<不支持代理
} otCoapCode;

/**
 * CoAP选项编号
 */
typedef enum otCoapOptionType
{
    OT_COAP_OPTION_IF_MATCH       = 1,  ///<如果匹配
    OT_COAP_OPTION_URI_HOST       = 3,  ///<Uri主机
    OT_COAP_OPTION_E_TAG          = 4,  ///<ETag
    OT_COAP_OPTION_IF_NONE_MATCH  = 5,  ///<如果无匹配
    OT_COAP_OPTION_OBSERVE        = 6,  ///<遵守[RFC7641]
    OT_COAP_OPTION_URI_PORT       = 7,  ///<Uri端口
    OT_COAP_OPTION_LOCATION_PATH  = 8,  ///<位置路径
    OT_COAP_OPTION_URI_PATH       = 11, ///<Uri路径
    OT_COAP_OPTION_CONTENT_FORMAT = 12, ///<内容格式
    OT_COAP_OPTION_MAX_AGE        = 14, ///<最大年龄
    OT_COAP_OPTION_URI_QUERY      = 15, ///<Uri查询
    OT_COAP_OPTION_ACCEPT         = 17, ///<接受
    OT_COAP_OPTION_LOCATION_QUERY = 20, ///<位置查询
    OT_COAP_OPTION_BLOCK2         = 23, ///<区块2（RFC7959）
    OT_COAP_OPTION_BLOCK1         = 27, ///<区块1（RFC7959）
    OT_COAP_OPTION_SIZE2          = 28, ///<尺寸2（RFC7959）
    OT_COAP_OPTION_PROXY_URI      = 35, ///<代理Uri
    OT_COAP_OPTION_PROXY_SCHEME   = 39, ///<代理方案
    OT_COAP_OPTION_SIZE1          = 60, ///<尺寸1
} otCoapOptionType;

/**
 * 此结构表示CoAP选项。
 *
 */
typedef struct otCoapOption
{
    uint16_t mNumber; ///<选项编号
    uint16_t mLength; ///<选项长度
} otCoapOption;

/**
 * 此结构充当CoAP选项的迭代器
 *
 */
typedef struct otCoapOptionIterator
{
    const otMessage *mMessage;          ///<CoAP消息
    otCoapOption     mOption;           ///<CoAP消息选项
    uint16_t         mNextOptionOffset; ///<下一选项的字节偏移
} otCoapOptionIterator;

/**
 * CoAP内容格式代码。完整列表记录在https://www.iana.org/assignments/core-parameters/core-parameters.xhtml#content-格式
 */
typedef enum otCoapOptionContentFormat
{
    /**
     * 文本/纯文本；字符集=utf-8:[RFC2046][RFC3676][RFC5147]
     */
    OT_COAP_OPTION_CONTENT_FORMAT_TEXT_PLAIN = 0,

    /**
     * 应用/cose；cose type=“cose-encrypt0”：[RFC8152]
     */
    OT_COAP_OPTION_CONTENT_FORMAT_COSE_ENCRYPT0 = 16,

    /**
     * 应用/cose；cose type=“cose-mac0”：[RFC8152]
     */
    OT_COAP_OPTION_CONTENT_FORMAT_COSE_MAC0 = 17,

    /**
     * 应用/cose；cose type=“cose-sign1”：[RFC8152]
     */
    OT_COAP_OPTION_CONTENT_FORMAT_COSE_SIGN1 = 18,

    /**
     * 应用程序/链接格式：[RFC6690]
     */
    OT_COAP_OPTION_CONTENT_FORMAT_LINK_FORMAT = 40,

    /**
     * 应用程序/xml:[RFC3023]
     */
    OT_COAP_OPTION_CONTENT_FORMAT_XML = 41,

    /**
     * 应用程序/八位字节流：[RFC2045][RFC2046]
     */
    OT_COAP_OPTION_CONTENT_FORMAT_OCTET_STREAM = 42,

    /**
     * application/exi:[“高效XML交换（exi）格式1.0（第二版）”，2014年2月]
     */
    OT_COAP_OPTION_CONTENT_FORMAT_EXI = 47,

    /**
     * 应用程序/json:[RFC7159]
     */
    OT_COAP_OPTION_CONTENT_FORMAT_JSON = 50,

    /**
     * application/json补丁+json:[RFC6902]
     */
    OT_COAP_OPTION_CONTENT_FORMAT_JSON_PATCH_JSON = 51,

    /**
     * 应用程序/合并补丁+json:[RFC7396]
     */
    OT_COAP_OPTION_CONTENT_FORMAT_MERGE_PATCH_JSON = 52,

    /**
     * 应用程序/cbor:[RFC7049]
     */
    OT_COAP_OPTION_CONTENT_FORMAT_CBOR = 60,

    /**
     * 应用程序/cwt:[RFC8392]
     */
    OT_COAP_OPTION_CONTENT_FORMAT_CWT = 61,

    /**
     * 应用/cose；cose type=“cose encrypt”：[RFC8152]
     */
    OT_COAP_OPTION_CONTENT_FORMAT_COSE_ENCRYPT = 96,

    /**
     * 应用/cose；cose type=“cose mac”：[RFC8152]
     */
    OT_COAP_OPTION_CONTENT_FORMAT_COSE_MAC = 97,

    /**
     * 应用/cose；cose type=“cose符号”：[RFC8152]
     */
    OT_COAP_OPTION_CONTENT_FORMAT_COSE_SIGN = 98,

    /**
     * 应用程序/cose密钥：[RFC8152]
     */
    OT_COAP_OPTION_CONTENT_FORMAT_COSE_KEY = 101,

    /**
     * 应用程序/陪集密钥集：[RFC8152]
     */
    OT_COAP_OPTION_CONTENT_FORMAT_COSE_KEY_SET = 102,

    /**
     * application/senml+json:[RFC8428]
     */
    OT_COAP_OPTION_CONTENT_FORMAT_SENML_JSON = 110,

    /**
     * application/sensml+json:[RFC8428]
     */
    OT_COAP_OPTION_CONTENT_FORMAT_SENSML_JSON = 111,

    /**
     * 应用程序/senml+cbor:[RFC8428]
     */
    OT_COAP_OPTION_CONTENT_FORMAT_SENML_CBOR = 112,

    /**
     * 应用程序/传感器+cbor:[RFC8428]
     */
    OT_COAP_OPTION_CONTENT_FORMAT_SENSML_CBOR = 113,

    /**
     * 应用程序/senml exi:[RFC8428]
     */
    OT_COAP_OPTION_CONTENT_FORMAT_SENML_EXI = 114,

    /**
     * 应用程序/传感器出口：[RFC8428]
     */
    OT_COAP_OPTION_CONTENT_FORMAT_SENSML_EXI = 115,

    /**
     * 应用程序/coap组+json:[RFC7390]
     */
    OT_COAP_OPTION_CONTENT_FORMAT_COAP_GROUP_JSON = 256,

    /**
     * 应用程序/senml+xml:[RFC8428]
     */
    OT_COAP_OPTION_CONTENT_FORMAT_SENML_XML = 310,

    /**
     * 应用程序/sensml+xml:[RFC8428]
     */
    OT_COAP_OPTION_CONTENT_FORMAT_SENSML_XML = 311
} otCoapOptionContentFormat;

/**
 * CoAP块大小指数
 */
typedef enum otCoapBlockSzx
{
    OT_COAP_OPTION_BLOCK_SZX_16   = 0,
    OT_COAP_OPTION_BLOCK_SZX_32   = 1,
    OT_COAP_OPTION_BLOCK_SZX_64   = 2,
    OT_COAP_OPTION_BLOCK_SZX_128  = 3,
    OT_COAP_OPTION_BLOCK_SZX_256  = 4,
    OT_COAP_OPTION_BLOCK_SZX_512  = 5,
    OT_COAP_OPTION_BLOCK_SZX_1024 = 6
} otCoapBlockSzx;

/**
 * 当接收到CoAP响应或在请求超时时调用此函数指针。
 *
 * @param[in]  aContext      指向应用程序特定上下文的指针。
 * @param[in]  aMessage      指向包含响应的消息缓冲区的指针。如果未收到响应，则为NULL。
 * @param[in]  aMessageInfo  指向@p aMessage的消息信息的指针。如果未收到响应，则为NULL。
 * @param[in]  aResult       CoAP事务的结果。
 *
 * @retval  OT_ERROR_NONE成功接收到响应。
 * @retval  OT_ERROR_ABORT对等方重置了CoAP事务。
 * @retval  OT_ERROR_RESPONSE_TIMEOUT超时期间未收到响应或确认。
 *
 */
typedef void (*otCoapResponseHandler)(void *               aContext,
                                      otMessage *          aMessage,
                                      const otMessageInfo *aMessageInfo,
                                      otError              aResult);

/**
 * 当接收到具有给定Uri路径的CoAP请求时，将调用此函数指针。
 *
 * @param[in]  aContext      指向任意上下文信息的指针。
 * @param[in]  aMessage      指向消息的指针。
 * @param[in]  aMessageInfo  指向@p aMessage的消息信息的指针。
 *
 */
typedef void (*otCoapRequestHandler)(void *aContext, otMessage *aMessage, const otMessageInfo *aMessageInfo);

/**
 * 当接收到具有逐块传输选项的CoAP消息时，调用此函数指针。
 *
 * 启用OPENTHREAD_COONFIG_COAP_BLOCKWISE_TRANFER_ENABLE配置时，此功能可用。
 *
 * @param[in]  aContext     指向应用程序特定上下文的指针。
 * @param[in]  aBlock       指向块段的指针。
 * @param[in]  aPosition    @p aBlock在字节序列中的位置。
 * @param[in]  aBlockLength 块段的长度（字节）。
 * @param[in]  aMore        如果后面有更多块段，则标记。
 * @param[in]  aTotalLength 传输信息的总长度（以字节为单位）（由Size1或Size2选项指示）。
 *
 * @retval  OT_ERROR_NONE块段已成功存储。
 * @retval  OT_ERROR_NO_BUFS没有更多内存来存储块。
 * @retval  OT_ERROR_NO_FRAME_REVICED块段缺失。
 *
 */
typedef otError (*otCoapBlockwiseReceiveHook)(void *         aContext,
                                              const uint8_t *aBlock,
                                              uint32_t       aPosition,
                                              uint16_t       aBlockLength,
                                              bool           aMore,
                                              uint32_t       aTotalLength);

/**
 * 在发送逐块传输中的下一个块之前，调用此函数指针。
 *
 * 启用OPENTHREAD_COONFIG_COAP_BLOCKWISE_TRANFER_ENABLE配置时，此功能可用。
 *
 * @param[in]       aContext     指向应用程序特定上下文的指针。
 * @param[inout]    aBlock       指向块段可以写入的位置的指针。
 * @param[in]       aPosition    序列中获取块段的位置。
 * @param[inout]    aBlockLength 输入时，以字节为单位的最大块段长度。
 * @param[out]      aMore        如果后面将有更多块段，则指向标志的指针。
 *
 * @warning 通过更改aBlockLength的值，可以重新协商整个交换的块大小。建议在收到第一个块后执行此操作，因为稍后的更改可能会导致其他CoAP实现出现问题。
 *
 * @retval  OT_ERROR_NONE未发生错误。
 * @retval  @p aPosition处的OT_ERROR_INVALID_ARGS块不存在。
 *
 */
typedef otError (*otCoapBlockwiseTransmitHook)(void *    aContext,
                                               uint8_t * aBlock,
                                               uint32_t  aPosition,
                                               uint16_t *aBlockLength,
                                               bool *    aMore);

/**
 * 此结构表示CoAP资源。
 *
 */
typedef struct otCoapResource
{
    const char *           mUriPath; ///<URI路径字符串
    otCoapRequestHandler   mHandler; ///<处理接收请求的回调
    void *                 mContext; ///<应用程序特定上下文
    struct otCoapResource *mNext;    ///<列表中的下一个CoAP资源
} otCoapResource;

/**
 * 此结构表示具有逐块传输的CoAP资源。
 *
 */
typedef struct otCoapBlockwiseResource
{
    const char *         mUriPath; ///<URI路径字符串
    otCoapRequestHandler mHandler; ///<处理接收请求的回调

    /** 用于处理传入的按块传输的回调。当启用OPENTHREAD_COONFIG_COAP_BLOCKWISE_TRANFER_ENABLE配置时，此回调可用。
     */
    otCoapBlockwiseReceiveHook mReceiveHook;

    /** 用于处理传出分块传输的回调。当启用OPENTHREAD_COONFIG_COAP_BLOCKWISE_TRANFER_ENABLE配置时，此回调可用。
     */
    otCoapBlockwiseTransmitHook     mTransmitHook;
    void *                          mContext; ///<应用程序特定上下文
    struct otCoapBlockwiseResource *mNext;    ///<列表中的下一个CoAP资源
} otCoapBlockwiseResource;

/**
 * 该结构表示CoAP传输参数。
 *
 * @note mAckTimeout*（（2**（mMaxRetransmit+1））-1）*（mAckRandomFactorNumerator/mAckRandom FactorDenominator）不得超过uint32_t（0xffffff）所表示的值。此限制允许OpenThread避免64位运算。
 *
 */
typedef struct otCoapTxParameters
{
    /**
     * 未收到ACK时第一次重传前的最小间隔，以毫秒为单位（RFC7252默认值为2000ms）。
     *
     */
    uint32_t mAckTimeout;

    /**
     * ACK_RANDOM_FACTOR的分子，用于在未接收到ACK时计算第一次重传前的最大间隔（RFC7252 ACK_RANDOM_FACTOR默认值为1.5；不得小于1）。
     *
     */
    uint8_t mAckRandomFactorNumerator;

    /**
     * ACK_RANDOM_FACTOR的分母，用于在未接收到ACK时计算第一次重传前的最大间隔（ACK_RANCOM_FACTOR默认值为1.5；不得小于1）。
     *
     */
    uint8_t mAckRandomFactorDenominator;

    /**
     * CoAP可确认消息的最大重传次数（RFC7252默认值为4）。
     *
     */
    uint8_t mMaxRetransmit;
} otCoapTxParameters;

/**
 * 此函数初始化CoAP标头。
 *
 * @param[inout] aMessage   指向要初始化的CoAP消息的指针。
 * @param[in]    aType      CoAP消息类型。
 * @param[in]    aCode      CoAP消息代码。
 *
 */
void otCoapMessageInit(otMessage *aMessage, otCoapType aType, otCoapCode aCode);

/**
 * 此函数初始化响应消息。
 *
 * @note 消息ID和令牌都是根据@p aRequest设置的。
 *
 * @param[inout] aResponse  指向CoAP响应消息的指针。
 * @param[in]    aRequest   指向CoAP请求消息的指针。
 * @param[in]    aType      CoAP消息类型。
 * @param[in]    aCode      CoAP消息代码。
 *
 * @retval OT_ERROR_NONE已成功初始化响应消息。
 * @retval OT_ERROR_NO_BUFS可用的消息缓冲区不足，无法初始化响应消息。
 *
 */
otError otCoapMessageInitResponse(otMessage *aResponse, const otMessage *aRequest, otCoapType aType, otCoapCode aCode);

/**
 * 此函数设置标头中的Token值和长度。
 *
 * @param[inout]  aMessage          指向CoAP消息的指针。
 * @param[in]     aToken            指向Token值的指针。
 * @param[in]     aTokenLength      @p aToken的长度。
 *
 * @retval OT_ERROR_NONE成功设置令牌值。
 * @retval OT_ERROR_NO_BUFS缓冲区不足，无法设置令牌值。
 *
 */
otError otCoapMessageSetToken(otMessage *aMessage, const uint8_t *aToken, uint8_t aTokenLength);

/**
 * 此函数设置令牌长度并随机化其值。
 *
 * @param[inout]  aMessage      指向CoAP消息的指针。
 * @param[in]     aTokenLength  要设置的令牌的长度。
 *
 */
void otCoapMessageGenerateToken(otMessage *aMessage, uint8_t aTokenLength);

/**
 * 此函数附加中指定的内容格式CoAP选项https://tools.ietf.org/html/rfc7252#page-92.如果要在消息中包含有效载荷，则必须在设置otCoapMessageSetPayloadMarker之前调用此函数。
 *
 * 该函数是otCoapMessageAppendUintOption的便利包装器，如果otCoapOptionContentFormat中未列出所需的格式类型代码，则应改用此基函数。
 *
 * @param[inout]  aMessage          指向CoAP消息的指针。
 * @param[in]     aContentFormat    上面otCoapOptionContentFormat中列出的内容格式之一。
 *
 * @retval OT_ERROR_NONE已成功附加选项。
 * @retval OT_ERROR_INVALID_ARGS选项类型不等于或大于上一个选项类型。
 * @retval OT_ERROR_NO_BUFS选项长度超过缓冲区大小。
 *
 */
otError otCoapMessageAppendContentFormatOption(otMessage *aMessage, otCoapOptionContentFormat aContentFormat);

/**
 * 此函数在标头中附加CoAP选项。
 *
 * @param[inout]  aMessage  指向CoAP消息的指针。
 * @param[in]     aNumber   CoAP选项编号。
 * @param[in]     aLength   CoAP选项长度。
 * @param[in]     aValue    指向CoAP值的指针。
 *
 * @retval OT_ERROR_NONE已成功附加选项。
 * @retval OT_ERROR_INVALID_ARGS选项类型不等于或大于上一个选项类型。
 * @retval OT_ERROR_NO_BUFS选项长度超过缓冲区大小。
 *
 */
otError otCoapMessageAppendOption(otMessage *aMessage, uint16_t aNumber, uint16_t aLength, const void *aValue);

/**
 * 此函数附加一个无符号整数CoAP选项，如https://tools.ietf.org/html/rfc7252#section-3.2
 *
 * @param[inout]  aMessage 指向CoAP消息的指针。
 * @param[in]     aNumber  CoAP选项编号。
 * @param[in]     aValue   CoAP选项无符号整数值。
 *
 * @retval OT_ERROR_NONE已成功附加选项。
 * @retval OT_ERROR_INVALID_ARGS选项类型不等于或大于上一个选项类型。
 * @retval OT_ERROR_NO_BUFS选项长度超过缓冲区大小。
 *
 * @see otCoapMessageGetOptionUint值
 */
otError otCoapMessageAppendUintOption(otMessage *aMessage, uint16_t aNumber, uint32_t aValue);

/**
 * 此函数附加“观察”选项。
 *
 * @param[inout]  aMessage  指向CoAP消息的指针。
 * @param[in]     aObserve  观察字段值。
 *
 * @retval OT_ERROR_NONE已成功附加选项。
 * @retval OT_ERROR_INVALID_ARGS选项类型不等于或大于上一个选项类型。
 * @retval OT_ERROR_NO_BUFS选项长度超过缓冲区大小。
 *
 */
otError otCoapMessageAppendObserveOption(otMessage *aMessage, uint32_t aObserve);

/**
 * 此函数附加Uri路径选项。
 *
 * @param[inout]  aMessage  指向CoAP消息的指针。
 * @param[in]     aUriPath  指向以NULL结尾的字符串的指针。
 *
 * @retval OT_ERROR_NONE已成功附加选项。
 * @retval OT_ERROR_INVALID_ARGS选项类型不等于或大于上一个选项类型。
 * @retval OT_ERROR_NO_BUFS选项长度超过缓冲区大小。
 *
 */
otError otCoapMessageAppendUriPathOptions(otMessage *aMessage, const char *aUriPath);

/**
 * 此函数将CoAP块选项SZX字段转换为实际块大小
 *
 * @param[in]     aSize     块大小指数。
 *
 * @returns 实际大小指数值。
 *
 */
uint16_t otCoapBlockSizeFromExponent(otCoapBlockSzx aSize);

/**
 * 此函数附加Block2选项
 *
 * @param[inout]  aMessage  指向CoAP消息的指针。
 * @param[in]     aNum      当前块号。
 * @param[in]     aMore     布尔值表示要发送更多块。
 * @param[in]     aSize     块大小指数。
 *
 * @retval OT_ERROR_NONE已成功附加选项。
 * @retval OT_ERROR_INVALID_ARGS选项类型不等于或大于上一个选项类型。
 * @retval OT_ERROR_NO_BUFS选项长度超过缓冲区大小。
 *
 */
otError otCoapMessageAppendBlock2Option(otMessage *aMessage, uint32_t aNum, bool aMore, otCoapBlockSzx aSize);

/**
 * 此函数附加Block1选项
 *
 * @param[inout]  aMessage  指向CoAP消息的指针。
 * @param[in]     aNum      当前块号。
 * @param[in]     aMore     布尔值表示要发送更多块。
 * @param[in]     aSize     块大小指数。
 *
 * @retval OT_ERROR_NONE已成功附加选项。
 * @retval OT_ERROR_INVALID_ARGS选项类型不等于或大于上一个选项类型。
 * @retval OT_ERROR_NO_BUFS选项长度超过缓冲区大小。
 *
 */
otError otCoapMessageAppendBlock1Option(otMessage *aMessage, uint32_t aNum, bool aMore, otCoapBlockSzx aSize);

/**
 * 此函数附加代理Uri选项。
 *
 * @param[inout]  aMessage  指向CoAP消息的指针。
 * @param[in]     aUriPath  指向以NULL结尾的字符串的指针。
 *
 * @retval OT_ERROR_NONE已成功附加选项。
 * @retval OT_ERROR_INVALID_ARGS选项类型不等于或大于上一个选项类型。
 * @retval OT_ERROR_NO_BUFS选项长度超过缓冲区大小。
 *
 */
otError otCoapMessageAppendProxyUriOption(otMessage *aMessage, const char *aUriPath);

/**
 * 此函数附加“最大年龄”选项。
 *
 * @param[inout]  aMessage  指向CoAP消息的指针。
 * @param[in]     aMaxAge   “最大年龄”值。
 *
 * @retval OT_ERROR_NONE已成功附加选项。
 * @retval OT_ERROR_INVALID_ARGS选项类型不等于或大于上一个选项类型。
 * @retval OT_ERROR_NO_BUFS选项长度超过缓冲区大小。
 *
 */
otError otCoapMessageAppendMaxAgeOption(otMessage *aMessage, uint32_t aMaxAge);

/**
 * 此函数附加一个Uri查询选项。
 *
 * @param[inout]  aMessage  指向CoAP消息的指针。
 * @param[in]     aUriQuery 指向以NULL结尾的字符串的指针，该字符串应包含单个key=value对。
 *
 * @retval OT_ERROR_NONE已成功附加选项。
 * @retval OT_ERROR_INVALID_ARGS选项类型不等于或大于上一个选项类型。
 * @retval OT_ERROR_NO_BUFS选项长度超过缓冲区大小。
 */
otError otCoapMessageAppendUriQueryOption(otMessage *aMessage, const char *aUriQuery);

/**
 * 此功能将指示有效载荷开始的有效载荷标记添加到CoAP报头。
 *
 * @param[inout]  aMessage  指向CoAP消息的指针。
 *
 * @retval OT_ERROR_NONE有效负载标记已成功添加。
 * @retval OT_ERROR_NO_BUFS标头有效负载标记超过缓冲区大小。
 *
 */
otError otCoapMessageSetPayloadMarker(otMessage *aMessage);

/**
 * 此函数返回Type值。
 *
 * @param[in]  aMessage  指向CoAP消息的指针。
 *
 * @returns Type值。
 *
 */
otCoapType otCoapMessageGetType(const otMessage *aMessage);

/**
 * 此函数返回Code值。
 *
 * @param[in]  aMessage  指向CoAP消息的指针。
 *
 * @returns “代码”值。
 *
 */
otCoapCode otCoapMessageGetCode(const otMessage *aMessage);

/**
 * 此方法将CoAP代码作为可读字符串返回。
 *
 * @param[in]   aMessage    指向CoAP消息的指针。
 *
 * @ 以字符串形式返回CoAP代码。
 *
 */
const char *otCoapMessageCodeToString(const otMessage *aMessage);

/**
 * 此函数返回消息ID值。
 *
 * @param[in]  aMessage  指向CoAP消息的指针。
 *
 * @returns 消息ID值。
 *
 */
uint16_t otCoapMessageGetMessageId(const otMessage *aMessage);

/**
 * 此函数返回Token长度。
 *
 * @param[in]  aMessage  指向CoAP消息的指针。
 *
 * @returns 令牌长度。
 *
 */
uint8_t otCoapMessageGetTokenLength(const otMessage *aMessage);

/**
 * 此函数返回指向Token值的指针。
 *
 * @param[in]  aMessage  指向CoAP消息的指针。
 *
 * @returns 指向Token值的指针。
 *
 */
const uint8_t *otCoapMessageGetToken(const otMessage *aMessage);

/**
 * 此函数为给定消息中的选项初始化迭代器。
 *
 * @param[inout]  aIterator 指向CoAP消息选项迭代器的指针。
 * @param[in]     aMessage  指向CoAP消息的指针。
 *
 * @retval  OT_ERROR_NONE已成功初始化。
 * @retval  OT_ERROR_PARSE消息状态不一致。
 *
 */
otError otCoapOptionIteratorInit(otCoapOptionIterator *aIterator, const otMessage *aMessage);

/**
 * 此函数返回指向与指定选项编号匹配的第一个选项的指针。
 *
 * @param[in]  aIterator 指向CoAP消息选项迭代器的指针。
 * @param[in]  aOption   寻求的选项编号。
 *
 * @returns 指向第一个匹配选项的指针。如果没有匹配的选项，则返回NULL指针。
 *
 */
const otCoapOption *otCoapOptionIteratorGetFirstOptionMatching(otCoapOptionIterator *aIterator, uint16_t aOption);

/**
 * 此函数返回指向第一个选项的指针。
 *
 * @param[inout]  aIterator 指向CoAP消息选项迭代器的指针。
 *
 * @returns 指向第一个选项的指针。如果没有选项，则返回NULL指针。
 *
 */
const otCoapOption *otCoapOptionIteratorGetFirstOption(otCoapOptionIterator *aIterator);

/**
 * 此函数返回指向与指定选项编号匹配的下一个选项的指针。
 *
 * @param[in]  aIterator 指向CoAP消息选项迭代器的指针。
 * @param[in]  aOption   寻求的选项编号。
 *
 * @returns 指向下一个匹配选项的指针。如果没有进一步的匹配选项，则返回NULL指针。
 *
 */
const otCoapOption *otCoapOptionIteratorGetNextOptionMatching(otCoapOptionIterator *aIterator, uint16_t aOption);

/**
 * 此函数返回指向下一个选项的指针。
 *
 * @param[inout]  aIterator 指向CoAP消息选项迭代器的指针。
 *
 * @returns 指向下一个选项的指针。如果没有更多选项，则返回NULL指针。
 *
 */
const otCoapOption *otCoapOptionIteratorGetNextOption(otCoapOptionIterator *aIterator);

/**
 * This function fills current option value into @p aValue，假设当前值是无符号整数，根据https://tools.ietf.org/html/rfc7252#section-3.2
 *
 * @param[inout]    aIterator   指向CoAP消息选项迭代器的指针。
 * @param[out]      aValue      指向无符号整数以接收选项值的指针。
 *
 * @retval  OT_ERROR_NONE已成功填充值。
 * @retval  OT_ERROR_NOT_FOUND无当前选项。
 * @retval  OT_ERROR_NO_BUFS值太长，无法放入uint64_t。
 *
 * @see otCoapMessageAppendUint选项
 */
otError otCoapOptionIteratorGetOptionUintValue(otCoapOptionIterator *aIterator, uint64_t *aValue);

/**
 * 此函数将当前选项值填充到@p aValue中。
 *
 * @param[inout]  aIterator 指向CoAP消息选项迭代器的指针。
 * @param[out]    aValue    指向缓冲区以接收选项值的指针。
 *
 * @retval  OT_ERROR_NONE已成功填充值。
 * @retval  OT_ERROR_NOT_FOUND无当前选项。
 *
 */
otError otCoapOptionIteratorGetOptionValue(otCoapOptionIterator *aIterator, void *aValue);

/**
 * 此函数创建新的CoAP消息。
 *
 * @note 如果@p aSettings为“NULL”，则链接层安全性启用，消息优先级默认设置为OT_message_priority_NORMAL。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aSettings  指向消息设置的指针，或NULL设置默认设置。
 *
 * @returns 指向消息缓冲区的指针，如果没有可用的消息缓冲区或参数无效，则返回NULL。
 *
 */
otMessage *otCoapNewMessage(otInstance *aInstance, const otMessageSettings *aSettings);

/**
 * 此函数发送带有自定义传输参数的CoAP请求。
 *
 * 如果期望对请求作出响应，则应提供相应的功能和上下文信息。如果不需要响应，这些参数应该是NULL指针。
 *
 * @param[in]  aInstance        指向OpenThread实例的指针。
 * @param[in]  aMessage         指向要发送的消息的指针。
 * @param[in]  aMessageInfo     指向与@p aMessage关联的消息信息的指针。
 * @param[in]  aHandler         响应接收或超时时应调用的函数指针。
 * @param[in]  aContext         指向任意上下文信息的指针。如果未使用，则可能为NULL。
 * @param[in]  aTxParameters    指向此请求的传输参数的指针。默认值使用NULL。否则，给定的参数必须满足以下条件：1.mMaxRetransmit不超过OT_COAP_MAX_RETRANSMIT。2.mAckRandomFactorNumerator/mAckRandomFactorDenominator不得低于1.0。3.计算的交换寿命不得超过uint32_t。
 *
 * @retval OT_ERROR_INVALID_ARGS@p aTxParameters无效。
 * @retval OT_ERROR_NONE已成功发送CoAP消息。
 * @retval OT_ERROR_NO_BUFS无法分配重传数据。
 *
 */
otError otCoapSendRequestWithParameters(otInstance *              aInstance,
                                        otMessage *               aMessage,
                                        const otMessageInfo *     aMessageInfo,
                                        otCoapResponseHandler     aHandler,
                                        void *                    aContext,
                                        const otCoapTxParameters *aTxParameters);

/**
 * 此函数按块发送带有自定义传输参数的CoAP请求。
 *
 * 启用OPENTHREAD_COONFIG_COAP_BLOCKWISE_TRANFER_ENABLE配置时，此功能可用。
 *
 * 如果期望对请求作出响应，则应提供相应的功能和上下文信息。如果预期响应是逐块的，则应提供相应的钩子函数。如果不需要响应，这些参数应该是NULL指针。
 *
 * @param[in]  aInstance        指向OpenThread实例的指针。
 * @param[in]  aMessage         指向要发送的消息的指针。
 * @param[in]  aMessageInfo     指向与@p aMessage关联的消息信息的指针。
 * @param[in]  aHandler         响应接收或超时时应调用的函数指针。
 * @param[in]  aContext         指向任意上下文信息的指针。如果未使用，则可能为NULL。
 * @param[in]  aTxParameters    指向此请求的传输参数的指针。默认值使用NULL。
 * @param[in]  aTransmitHook    一个指针，指向用于传出分块传输的钩子函数。
 * @param[in]  aReceiveHook     一个指针，指向传入的按块传输的钩子函数。
 *
 * @retval OT_ERROR_NONE已成功发送CoAP消息。
 * @retval OT_ERROR_NO_BUFS无法分配重传数据。
 *
 */
otError otCoapSendRequestBlockWiseWithParameters(otInstance *                aInstance,
                                                 otMessage *                 aMessage,
                                                 const otMessageInfo *       aMessageInfo,
                                                 otCoapResponseHandler       aHandler,
                                                 void *                      aContext,
                                                 const otCoapTxParameters *  aTxParameters,
                                                 otCoapBlockwiseTransmitHook aTransmitHook,
                                                 otCoapBlockwiseReceiveHook  aReceiveHook);

/**
 * 此函数按块发送CoAP请求。
 *
 * 启用OPENTHREAD_COONFIG_COAP_BLOCKWISE_TRANFER_ENABLE配置时，此功能可用。
 *
 * 如果期望对请求作出响应，则应提供相应的功能和上下文信息。如果预期响应是逐块的，则应提供相应的钩子函数。如果不需要响应，这些参数应该是NULL指针。
 *
 * @param[in]  aInstance     指向OpenThread实例的指针。
 * @param[in]  aMessage      指向要发送的消息的指针。
 * @param[in]  aMessageInfo  指向与@p aMessage关联的消息信息的指针。
 * @param[in]  aHandler      响应接收或超时时应调用的函数指针。
 * @param[in]  aContext      指向任意上下文信息的指针。如果未使用，则可能为NULL。
 * @param[in]  aTransmitHook 一个指针，指向用于传出分块传输的钩子函数。
 * @param[in]  aReceiveHook  一个指针，指向传入的按块传输的钩子函数。
 *
 * @retval OT_ERROR_NONE已成功发送CoAP消息。
 * @retval OT_ERROR_NO_BUFS无法分配重传数据。
 *
 */
static inline otError otCoapSendRequestBlockWise(otInstance *                aInstance,
                                                 otMessage *                 aMessage,
                                                 const otMessageInfo *       aMessageInfo,
                                                 otCoapResponseHandler       aHandler,
                                                 void *                      aContext,
                                                 otCoapBlockwiseTransmitHook aTransmitHook,
                                                 otCoapBlockwiseReceiveHook  aReceiveHook)
{
    // NOLINTNEXTLINE（现代化使用nullptr）
    return otCoapSendRequestBlockWiseWithParameters(aInstance, aMessage, aMessageInfo, aHandler, aContext, NULL,
                                                    aTransmitHook, aReceiveHook);
}

/**
 * 此函数发送CoAP请求。
 *
 * 如果期望对请求作出响应，则应提供相应的功能和上下文信息。如果不需要响应，这些参数应该是NULL指针。
 *
 * @param[in]  aInstance     指向OpenThread实例的指针。
 * @param[in]  aMessage      指向要发送的消息的指针。
 * @param[in]  aMessageInfo  指向与@p aMessage关联的消息信息的指针。
 * @param[in]  aHandler      响应接收或超时时应调用的函数指针。
 * @param[in]  aContext      指向任意上下文信息的指针。如果未使用，则可能为NULL。
 *
 * @retval OT_ERROR_NONE已成功发送CoAP消息。
 * @retval OT_ERROR_NO_BUFS无法分配重传数据。
 *
 */
static inline otError otCoapSendRequest(otInstance *          aInstance,
                                        otMessage *           aMessage,
                                        const otMessageInfo * aMessageInfo,
                                        otCoapResponseHandler aHandler,
                                        void *                aContext)
{
    // NOLINTNEXTLINE（现代化使用nullptr）
    return otCoapSendRequestWithParameters(aInstance, aMessage, aMessageInfo, aHandler, aContext, NULL);
}

/**
 * 此功能启动CoAP服务器。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aPort      要绑定到的本地UDP端口。
 *
 * @retval OT_ERROR_NONE已成功启动CoAP服务器。
 * @retval OT_ERROR_FAILED无法启动CoAP服务器。
 *
 */
otError otCoapStart(otInstance *aInstance, uint16_t aPort);

/**
 * 此函数用于停止CoAP服务器。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 *
 * @retval OT_ERROR_NONE已成功停止CoAP服务器。
 *
 */
otError otCoapStop(otInstance *aInstance);

/**
 * 此函数向CoAP服务器添加资源。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aResource  指向资源的指针。
 *
 */
void otCoapAddResource(otInstance *aInstance, otCoapResource *aResource);

/**
 * 此函数用于从CoAP服务器中删除资源。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aResource  指向资源的指针。
 *
 */
void otCoapRemoveResource(otInstance *aInstance, otCoapResource *aResource);

/**
 * 此函数向CoAP服务器添加逐块资源。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aResource  指向资源的指针。
 *
 */
void otCoapAddBlockWiseResource(otInstance *aInstance, otCoapBlockwiseResource *aResource);

/**
 * 此函数用于从CoAP服务器中删除逐块资源。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aResource  指向资源的指针。
 *
 */
void otCoapRemoveBlockWiseResource(otInstance *aInstance, otCoapBlockwiseResource *aResource);

/**
 * 此函数为未处理的CoAP请求设置默认处理程序。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aHandler   当未处理的请求到达时应调用的函数指针。
 * @param[in]  aContext   指向任意上下文信息的指针。如果未使用，则可能为NULL。
 *
 */
void otCoapSetDefaultHandler(otInstance *aInstance, otCoapRequestHandler aHandler, void *aContext);

/**
 * 此函数从服务器发送带有自定义传输参数的CoAP响应。
 *
 * @param[in]  aInstance        指向OpenThread实例的指针。
 * @param[in]  aMessage         指向要发送的CoAP响应的指针。
 * @param[in]  aMessageInfo     指向与@p aMessage关联的消息信息的指针。
 * @param[in]  aTxParameters    指向此响应的传输参数的指针。默认值使用NULL。
 *
 * @retval OT_ERROR_NONE已成功将CoAP响应消息排入队列。
 * @retval OT_ERROR_NO_BUFS可用缓冲区不足，无法发送CoAP响应。
 *
 */
otError otCoapSendResponseWithParameters(otInstance *              aInstance,
                                         otMessage *               aMessage,
                                         const otMessageInfo *     aMessageInfo,
                                         const otCoapTxParameters *aTxParameters);

/**
 * 此函数通过自定义传输参数从服务器逐块发送CoAP响应。
 *
 * 启用OPENTHREAD_COONFIG_COAP_BLOCKWISE_TRANFER_ENABLE配置时，此功能可用。
 *
 * @param[in]  aInstance        指向OpenThread实例的指针。
 * @param[in]  aMessage         指向要发送的CoAP响应的指针。
 * @param[in]  aMessageInfo     指向与@p aMessage关联的消息信息的指针。
 * @param[in]  aTxParameters    指向此响应的传输参数的指针。默认值使用NULL。
 * @param[in]  aContext         指向任意上下文信息的指针。如果未使用，则可能为NULL。
 * @param[in]  aTransmitHook    一个指针，指向用于传出分块传输的钩子函数。
 *
 * @retval OT_ERROR_NONE已成功将CoAP响应消息排入队列。
 * @retval OT_ERROR_NO_BUFS可用缓冲区不足，无法发送CoAP响应。
 *
 */
otError otCoapSendResponseBlockWiseWithParameters(otInstance *                aInstance,
                                                  otMessage *                 aMessage,
                                                  const otMessageInfo *       aMessageInfo,
                                                  const otCoapTxParameters *  aTxParameters,
                                                  void *                      aContext,
                                                  otCoapBlockwiseTransmitHook aTransmitHook);

/**
 * 此函数从服务器逐块发送CoAP响应。
 *
 * 启用OPENTHREAD_COONFIG_COAP_BLOCKWISE_TRANFER_ENABLE配置时，此功能可用。
 *
 * @param[in]  aInstance     指向OpenThread实例的指针。
 * @param[in]  aMessage      指向要发送的CoAP响应的指针。
 * @param[in]  aMessageInfo  指向与@p aMessage关联的消息信息的指针。
 * @param[in]  aContext      指向任意上下文信息的指针。如果未使用，则可能为NULL。
 * @param[in]  aTransmitHook 一个指针，指向用于传出分块传输的钩子函数。
 *
 * @retval OT_ERROR_NONE已成功将CoAP响应消息排入队列。
 * @retval OT_ERROR_NO_BUFS可用缓冲区不足，无法发送CoAP响应。
 *
 */
static inline otError otCoapSendResponseBlockWise(otInstance *                aInstance,
                                                  otMessage *                 aMessage,
                                                  const otMessageInfo *       aMessageInfo,
                                                  void *                      aContext,
                                                  otCoapBlockwiseTransmitHook aTransmitHook)
{
    // NOLINTNEXTLINE（现代化使用nullptr）
    return otCoapSendResponseBlockWiseWithParameters(aInstance, aMessage, aMessageInfo, NULL, aContext, aTransmitHook);
}

/**
 * 此函数从服务器发送CoAP响应。
 *
 * @param[in]  aInstance     指向OpenThread实例的指针。
 * @param[in]  aMessage      指向要发送的CoAP响应的指针。
 * @param[in]  aMessageInfo  指向与@p aMessage关联的消息信息的指针。
 *
 * @retval OT_ERROR_NONE已成功将CoAP响应消息排入队列。
 * @retval OT_ERROR_NO_BUFS可用缓冲区不足，无法发送CoAP响应。
 *
 */
static inline otError otCoapSendResponse(otInstance *aInstance, otMessage *aMessage, const otMessageInfo *aMessageInfo)
{
    // NOLINTNEXTLINE（现代化使用nullptr）
    return otCoapSendResponseWithParameters(aInstance, aMessage, aMessageInfo, NULL);
}

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif /* OPENTHREAD_COAP_H_ */

