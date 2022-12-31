/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread CLI服务器的顶级功能。
 */

#ifndef OPENTHREAD_CLI_H_
#define OPENTHREAD_CLI_H_

#include <stdarg.h>
#include <stdint.h>

#include <openthread/instance.h>
#include <openthread/platform/logging.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 此结构表示CLI命令。
 *
 */
typedef struct otCliCommand
{
    const char *mName; ///<指向命令字符串的指针。
    void (*mCommand)(void *  aContext,
                     uint8_t aArgsLength,
                     char *  aArgs[]); ///<处理命令的函数指针。
} otCliCommand;

/**
 * @addtogroup api客户端
 *
 * @brief 该模块包括控制线程堆栈执行的函数。
 *
 * @{
 *
 */

/**
 * 调用此函数指针以通知Console输出。
 *
 * @param[in]  aBuf        指向具有输出的缓冲区的指针。
 * @param[in]  aBufLength  存储在缓冲区中的输出数据的长度。
 * @param[out] aContext    用户上下文指针。
 *
 * @returns                回调写入的字节数。
 *
 */
typedef int (*otCliOutputCallback)(void *aContext, const char *aFormat, va_list aArguments);

/**
 * 初始化CLI模块。
 *
 * @param[in]  aInstance   OpenThread实例结构。
 * @param[in]  aCallback   调用回调方法以处理CLI输出。
 * @param[in]  aContext    用户上下文指针。
 *
 */
void otCliInit(otInstance *aInstance, otCliOutputCallback aCallback, void *aContext);

/**
 * 调用此方法以输入控制台输入行。
 *
 * @param[in]  aBuf        指向以空结尾的字符串的指针。
 *
 */
void otCliInputLine(char *aBuf);

/**
 * 设置用户命令表。
 *
 * @param[in]  aUserCommands  指向带有用户命令的数组的指针。
 * @param[in]  aLength        @p aUserCommands长度。
 * @param[in]  aContext       @p传递给处理程序的上下文。
 *
 */
void otCliSetUserCommands(const otCliCommand *aUserCommands, uint8_t aLength, void *aContext);

/**
 * 将多个字节作为十六进制字符串写入CLI控制台。
 *
 * @param[in]  aBytes   指向应该打印的数据的指针。
 * @param[in]  aLength  @p aBytes长度。
 *
 */
void otCliOutputBytes(const uint8_t *aBytes, uint8_t aLength);

/**
 * 将格式化的字符串写入CLI控制台
 *
 * @param[in]  aFmt   指向格式字符串的指针。
 * @param[in]  ...    参数的匹配列表。
 *
 */
void otCliOutputFormat(const char *aFmt, ...);

/**
 * 将错误代码写入CLI控制台
 *
 * If the @p aError为“OT_ERROR_PENDING”，不会输出任何内容。
 *
 * @param[in]  aError 错误代码值。
 *
 */
void otCliAppendResult(otError aError);

/**
 * 回调以将OpenThread日志写入CLI控制台
 *
 * @param[in]  aLogLevel   日志级别。
 * @param[in]  aLogRegion  日志区域。
 * @param[in]  aFormat     指向格式字符串的指针。
 * @param[in]  aArgs       va_list匹配aFormat。
 *
 */
void otCliPlatLogv(otLogLevel aLogLevel, otLogRegion aLogRegion, const char *aFormat, va_list aArgs);

/**
 * 函数将OpenThread日志写入CLI控制台。
 *
 * @param[in]  aLogLevel   日志级别。
 * @param[in]  aLogRegion  日志区域。
 * @param[in]  aLogLine    指向日志行字符串的指针。
 *
 */
void otCliPlatLogLine(otLogLevel aLogLevel, otLogRegion aLogRegion, const char *aLogLine);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_CLI_H_

