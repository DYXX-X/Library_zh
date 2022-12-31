/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件包括调试日志服务的平台抽象。
 */

#ifndef OPENTHREAD_PLATFORM_LOGGING_H_
#define OPENTHREAD_PLATFORM_LOGGING_H_

#include <stdarg.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup 平板测井
 *
 * @brief 该模块包括调试日志服务的平台抽象。
 *
 * @{
 *
 */

/**
 * 日志级别无。
 *
 * @note 日志级别的定义使得嵌入式实现可以在编译时通过#if/#else/#endif消除代码。
 *
 */
#define OT_LOG_LEVEL_NONE 0

/**
 * 日志级别严重。
 *
 * @note 日志级别的定义使得嵌入式实现可以在编译时通过#if/#else/#endif消除代码。
 *
 */
#define OT_LOG_LEVEL_CRIT 1

/**
 * 日志级别警告。
 *
 * @note 日志级别的定义使得嵌入式实现可以在编译时通过#if/#else/#endif消除代码。
 *
 */
#define OT_LOG_LEVEL_WARN 2

/**
 * 日志级别通知。
 *
 * @note 日志级别的定义使得嵌入式实现可以在编译时通过#if/#else/#endif消除代码。
 *
 */
#define OT_LOG_LEVEL_NOTE 3

/**
 * 日志级别信息。
 *
 * @note 日志级别的定义使得嵌入式实现可以在编译时通过#if/#else/#endif消除代码。
 *
 */
#define OT_LOG_LEVEL_INFO 4

/**
 * 日志级别调试。
 *
 * @note 日志级别的定义使得嵌入式实现可以在编译时通过#if/#else/#endif消除代码。
 *
 */
#define OT_LOG_LEVEL_DEBG 5

/**
 * 此类型表示日志级别。
 *
 */
typedef int otLogLevel;

/**
 * 此枚举表示日志区域。
 *
 */
typedef enum otLogRegion
{
    OT_LOG_REGION_API      = 1,  ///<OpenThread API
    OT_LOG_REGION_MLE      = 2,  ///< MLE
    OT_LOG_REGION_ARP      = 3,  ///<EID到RLOC映射。
    OT_LOG_REGION_NET_DATA = 4,  ///<网络数据
    OT_LOG_REGION_ICMP     = 5,  ///<ICMPv6
    OT_LOG_REGION_IP6      = 6,  ///<IPv6
    OT_LOG_REGION_TCP      = 7,  ///< TCP
    OT_LOG_REGION_MAC      = 8,  ///< IEEE 802.15.4 MAC
    OT_LOG_REGION_MEM      = 9,  ///<内存
    OT_LOG_REGION_NCP      = 10, ///< NCP
    OT_LOG_REGION_MESH_COP = 11, ///<网格调试协议
    OT_LOG_REGION_NET_DIAG = 12, ///<网络诊断
    OT_LOG_REGION_PLATFORM = 13, ///<平台
    OT_LOG_REGION_COAP     = 14, ///<CoAP
    OT_LOG_REGION_CLI      = 15, ///< CLI
    OT_LOG_REGION_CORE     = 16, ///<OpenThread核心
    OT_LOG_REGION_UTIL     = 17, ///<实用程序模块
    OT_LOG_REGION_BBR      = 18, ///<骨干路由器（从线程1.2开始可用）
    OT_LOG_REGION_MLR      = 19, ///<多播侦听器注册（从线程1.2开始可用）
    OT_LOG_REGION_DUA      = 20, ///<域单播地址（自线程1.2起可用）
    OT_LOG_REGION_BR       = 21, ///<边界路由器
    OT_LOG_REGION_SRP      = 22, ///<服务注册协议（SRP）
    OT_LOG_REGION_DNS      = 23, ///< DNS
} otLogRegion;

/**
 * 此函数输出日志。
 *
 * @param[in]  aLogLevel   日志级别。
 * @param[in]  aLogRegion  日志区域。
 * @param[in]  aFormat     指向格式字符串的指针。
 * @param[in]  ...         格式规范的参数。
 *
 */
void otPlatLog(otLogLevel aLogLevel, otLogRegion aLogRegion, const char *aFormat, ...);

/**
 * 此（可选）平台功能输出准备好的日志行。
 *
 * 当未启用“OpenThread_CONFIG_LOG_DEFINE_ASMACRO_ONLY”（在这种情况下，OT内核本身将准备一个完整的日志行）时，OpenThread内核使用此平台函数。
 *
 * 请注意，此函数是可选的，如果平台层不提供，则OpenThread核心将提供默认（弱）实现，并将其用作`otPlatLog（aLogLevel，aLogResion，“%s”，aLogLine）`。
 *
 * @param[in]  aLogLevel   日志级别。
 * @param[in]  aLogRegion  日志区域。
 * @param[in]  aLogLine    指向日志行字符串的指针。
 *
 */
void otPlatLogLine(otLogLevel aLogLevel, otLogRegion aLogRegion, const char *aLogLine);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_PLATFORM_LOGGING_H_

