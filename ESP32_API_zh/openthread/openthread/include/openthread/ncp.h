/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 该文件定义OpenThread NCP模块的顶级函数。
 */

#ifndef OPENTHREAD_NCP_H_
#define OPENTHREAD_NCP_H_

#include <stdarg.h>

#include <openthread/platform/logging.h>
#include <openthread/platform/radio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api ncp
 *
 * @brief 该模块包括控制线程堆栈执行的函数。
 *
 * @{
 *
 */

/**
 * 调用此函数指针以发送HDLC编码的NCP数据。
 *
 * @param[in]  aBuf        指向具有输出的缓冲区的指针。
 * @param[in]  aBufLength  存储在缓冲区中的输出数据的长度。
 *
 * @returns                回调处理的字节数。
 *
 */
typedef int (*otNcpHdlcSendCallback)(const uint8_t *aBuf, uint16_t aBufLength);

/**
 * NCP发送完成后调用此函数。
 *
 */
void otNcpHdlcSendDone(void);

/**
 * 在接收HDLC编码的NCP数据后调用此函数。
 *
 * @param[in]  aBuf        指向缓冲区的指针。
 * @param[in]  aBufLength  缓冲区中存储的数据的长度。
 *
 */
void otNcpHdlcReceive(const uint8_t *aBuf, uint16_t aBufLength);

/**
 * 基于HDLC帧初始化NCP。
 *
 * @param[in]  aInstance        OpenThread实例结构。
 * @param[in]  aSendCallback    用于发送NCP数据的函数指针。
 *
 */
void otNcpHdlcInit(otInstance *aInstance, otNcpHdlcSendCallback aSendCallback);

/**
 * 基于SPI帧初始化NCP。
 *
 * @param[in]  aInstance  OpenThread实例结构。
 *
 */
void otNcpSpiInit(otInstance *aInstance);

/**
 * @brief 通过特定流向主机发送数据。
 *
 * 此函数尝试使用给定的aStreamId向主机发送给定的数据。这对于报告错误消息、实现调试/诊断控制台以及可能的其他类型的数据流非常有用。
 *
 * 该书面文件要么被全部接受，要么被拒绝。不尝试部分写入。
 *
 * @param[in]  aStreamId  要写入的流的数字标识符。如果设置为“0”，将默认为调试流。
 * @param[in]  aDataPtr   指向要在流上发送的数据的指针。如果aDataLen为非零，则此参数不得为NULL。
 * @param[in]  aDataLen   aDataPtr中要发送的数据字节数。
 *
 * @retval OT_ERROR_NONE数据已排队等待传送到主机。
 * @retval OT_ERROR_BUSY没有足够的资源来完成此请求。这通常是暂时的情况。
 * @retval OT_ERROR_INVALID_ARGS给定的aStreamId无效。
 */
otError otNcpStreamWrite(int aStreamId, const uint8_t *aDataPtr, int aDataLen);

/**
 * 使用“otNcpStreamWrite”写入OpenThread日志。
 *
 * @param[in]  aLogLevel   日志级别。
 * @param[in]  aLogRegion  日志区域。
 * @param[in]  aFormat     指向格式字符串的指针。
 * @param[in]  aArgs       va_list匹配aFormat。
 */
void otNcpPlatLogv(otLogLevel aLogLevel, otLogRegion aLogRegion, const char *aFormat, va_list aArgs);

//-----------------------------------------------------------------------------------------
// Peek/Poke内存访问控制代表

/**
 * 定义委托（函数指针）类型以控制peek/poke操作的行为。
 *
 * 调用此委托函数以决定是否允许查看或戳入特定内存区域。如果启用了对peek/poke命令的NCP支持，则使用此选项。
 *
 * @param[in] aAddress    内存区域的起始地址。
 * @param[in] aCount      要查看或戳取的字节数。
 *
 * @returns  TRUE表示允许对给定内存区域进行偷看/戳，否则为FALSE。
 *
 */
typedef bool (*otNcpDelegateAllowPeekPoke)(uint32_t aAddress, uint16_t aCount);

/**
 * 该方法向NCP模块注册peek/poke委托函数。
 *
 * NCP模块调用委托函数，以决定是否允许偷看或戳入特定内存区域。如果委托指针设置为NULL，则允许对任何地址执行peek/poke操作。
 *
 * @param[in] aAllowPeekDelegate      用于偷看操作的委托函数指针。
 * @param[in] aAllowPokeDelegate      用于poke操作的委托函数指针。
 *
 */
void otNcpRegisterPeekPokeDelagates(otNcpDelegateAllowPeekPoke aAllowPeekDelegate,
                                    otNcpDelegateAllowPeekPoke aAllowPokeDelegate);

//-----------------------------------------------------------------------------------------
// 传统网络API

#define OT_NCP_LEGACY_ULA_PREFIX_LENGTH 8 ///<传统ULA大小（字节）

/**
 * 定义用于启动旧网络的处理程序（函数指针）类型
 *
 * 调用以启动旧网络。
 *
 */
typedef void (*otNcpHandlerStartLegacy)(void);

/**
 * 定义用于停止传统网络的处理程序（函数指针）类型
 *
 * 调用以停止旧网络。
 *
 */
typedef void (*otNcpHandlerStopLegacy)(void);

/**
 * 定义用于启动联接进程的处理程序（函数指针）类型。
 *
 * @param[in] aExtAddress   指向要加入的节点的扩展地址的指针，如果希望加入任何相邻节点，则为NULL。
 *
 * 调用以启动到任何或特定节点的旧联接过程。
 *
 */
typedef void (*otNcpHandlerJoinLegacyNode)(const otExtAddress *aExtAddress);

/**
 * 定义用于设置旧ULA前缀的处理程序（函数指针）类型。
 *
 * @param[in] aUlaPrefix   指向包含旧ULA前缀的缓冲区的指针。
 *
 * 调用以设置旧版ULA前缀。
 *
 */
typedef void (*otNcpHandlerSetLegacyUlaPrefix)(const uint8_t *aUlaPrefix);

/**
 * 定义包含所有旧处理程序（函数指针）的结构。
 *
 */
typedef struct otNcpLegacyHandlers
{
    otNcpHandlerStartLegacy        mStartLegacy;        ///<开始处理程序
    otNcpHandlerStopLegacy         mStopLegacy;         ///<停止处理程序
    otNcpHandlerJoinLegacyNode     mJoinLegacyNode;     ///<联接处理程序
    otNcpHandlerSetLegacyUlaPrefix mSetLegacyUlaPrefix; ///<设置ULA处理程序
} otNcpLegacyHandlers;

/**
 * 旧堆栈调用此回调以通知新的旧节点确实加入了网络。
 *
 * @param[in]   aExtAddr    指向连接节点的扩展地址的指针。
 *
 */
void otNcpHandleLegacyNodeDidJoin(const otExtAddress *aExtAddr);

/**
 * 旧堆栈调用此回调以通知旧ULA前缀已更改。
 *
 * @param[in]    aUlaPrefix  指向接收到的ULA前缀的指针。
 *
 */
void otNcpHandleDidReceiveNewLegacyUlaPrefix(const uint8_t *aUlaPrefix);

/**
 * 该方法向NCP注册一组遗留处理程序。
 *
 * The set of handlers provided by the struct @p NCP代码使用处理器来启动/停止传统网络。
 * The @p aHandlers可以为NULL，以禁用NCP上的遗留支持。给定处理程序结构中的单个处理程序也可以为NULL。
 *
 * @param[in] aHandlers    指向处理程序结构的指针。
 *
 */
void otNcpRegisterLegacyHandlers(const otNcpLegacyHandlers *aHandlers);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_NCP_H_

