/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread中使用的错误。
 */

#ifndef OPENTHREAD_ERROR_H_
#define OPENTHREAD_ERROR_H_

#include <openthread/platform/toolchain.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api错误
 *
 * @brief 此模块包括OpenThread中使用的错误定义。
 *
 * @{
 *
 */

/**
 * 此枚举表示整个OpenThread中使用的错误代码。
 *
 */
typedef enum OT_MUST_USE_RESULT otError
{
    /**
     * 没有错误。
     */
    OT_ERROR_NONE = 0,

    /**
     * 操作失败。
     */
    OT_ERROR_FAILED = 1,

    /**
     * 消息已删除。
     */
    OT_ERROR_DROP = 2,

    /**
     * 缓冲区不足。
     */
    OT_ERROR_NO_BUFS = 3,

    /**
     * 无可用路线。
     */
    OT_ERROR_NO_ROUTE = 4,

    /**
     * 服务正忙，无法为操作提供服务。
     */
    OT_ERROR_BUSY = 5,

    /**
     * 无法分析消息。
     */
    OT_ERROR_PARSE = 6,

    /**
     * 输入参数无效。
     */
    OT_ERROR_INVALID_ARGS = 7,

    /**
     * 安全检查失败。
     */
    OT_ERROR_SECURITY = 8,

    /**
     * 地址解析需要地址查询操作。
     */
    OT_ERROR_ADDRESS_QUERY = 9,

    /**
     * 地址不在源匹配表中。
     */
    OT_ERROR_NO_ADDRESS = 10,

    /**
     * 操作已中止。
     */
    OT_ERROR_ABORT = 11,

    /**
     * 未实现函数或方法。
     */
    OT_ERROR_NOT_IMPLEMENTED = 12,

    /**
     * 由于状态无效，无法完成。
     */
    OT_ERROR_INVALID_STATE = 13,

    /**
     * macMaxFrameRetries（IEEE 802.15.4-2006）之后未收到确认。
     */
    OT_ERROR_NO_ACK = 14,

    /**
     * 由于信道上的活动，即CSMA-CA机制已失败，因此无法进行传输（IEEE 802.15.4-2006）。
     */
    OT_ERROR_CHANNEL_ACCESS_FAILURE = 15,

    /**
     * 当前未连接到线程分区。
     */
    OT_ERROR_DETACHED = 16,

    /**
     * 接收时FCS检查失败。
     */
    OT_ERROR_FCS = 17,

    /**
     * 未接收到帧。
     */
    OT_ERROR_NO_FRAME_RECEIVED = 18,

    /**
     * 收到来自未知邻居的帧。
     */
    OT_ERROR_UNKNOWN_NEIGHBOR = 19,

    /**
     * 收到来自无效源地址的帧。
     */
    OT_ERROR_INVALID_SOURCE_ADDRESS = 20,

    /**
     * 接收到由地址筛选器（allowlisted或denyllisted）筛选的帧。
     */
    OT_ERROR_ADDRESS_FILTERED = 21,

    /**
     * 接收到目标地址检查过滤的帧。
     */
    OT_ERROR_DESTINATION_ADDRESS_FILTERED = 22,

    /**
     * 找不到请求的项目。
     */
    OT_ERROR_NOT_FOUND = 23,

    /**
     * 操作已在进行中。
     */
    OT_ERROR_ALREADY = 24,

    /**
     * 创建IPv6地址失败。
     */
    OT_ERROR_IP6_ADDRESS_CREATION_FAILURE = 26,

    /**
     * 模式标志阻止操作
     */
    OT_ERROR_NOT_CAPABLE = 27,

    /**
     * 未收到Coap响应或确认或DNS、SNTP响应。
     */
    OT_ERROR_RESPONSE_TIMEOUT = 28,

    /**
     * 收到重复的帧。
     */
    OT_ERROR_DUPLICATED = 29,

    /**
     * 由于超时，正在从重新组装列表中删除消息。
     */
    OT_ERROR_REASSEMBLY_TIMEOUT = 30,

    /**
     * 消息不是TMF消息。
     */
    OT_ERROR_NOT_TMF = 31,

    /**
     * 接收到非低泛数据帧。
     */
    OT_ERROR_NOT_LOWPAN_DATA_FRAME = 32,

    /**
     * 链接边距太低。
     */
    OT_ERROR_LINK_MARGIN_LOW = 34,

    /**
     * 输入（CLI）命令无效。
     */
    OT_ERROR_INVALID_COMMAND = 35,

    /**
     * 用于指示成功/错误状态的特殊错误代码处于待定状态且尚未得知。
     *
     */
    OT_ERROR_PENDING = 36,

    /**
     * 请求被拒绝。
     */
    OT_ERROR_REJECTED = 37,

    /**
     * 定义的错误数。
     */
    OT_NUM_ERRORS,

    /**
     * 一般错误（不应使用）。
     */
    OT_ERROR_GENERIC = 255,
} otError;

/**
 * 此函数将otError枚举转换为字符串。
 *
 * @param[in]  aError     otError枚举。
 *
 * @returns  otError的字符串表示形式。
 *
 */
const char *otThreadErrorToString(otError aError);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_ERROR_H_

