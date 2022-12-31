/*
 *  版权所有（c）2018，The OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 该文件定义logging_rtt.c使用的日志rtt接口和默认常量。
 */

#ifndef UTILS_LOGGING_RTT_H
#define UTILS_LOGGING_RTT_H

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

#include "openthread-core-config.h"
#include <openthread/config.h>
#include <openthread/platform/logging.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @def LOG_RTT_BUFFER_INDEX
 *
 * RTT的缓冲区索引。
 *
 */
#ifndef LOG_RTT_BUFFER_INDEX
#define LOG_RTT_BUFFER_INDEX 0
#endif

/**
 * @def LOG_RTT_BUFFER_NAME
 *
 * RTT的名字。仅当LOG_RTT_BUFFER_INDEX不为0时使用。否则，缓冲区名称固定为“终端”。
 *
 */
#ifndef LOG_RTT_BUFFER_NAME
#define LOG_RTT_BUFFER_NAME "Terminal"
#endif

/**
 * @def LOG_RTT_BUFFER_SIZE
 *
 * 记录RTT的缓冲区大小。仅在LOG_RTT_BUFFER_INDEX不为0时使用。若要配置缓冲区#0大小，请检查SEGGER_RTT_Conf.h中的BUFFER_size_UP定义
 *
 */
#ifndef LOG_RTT_BUFFER_SIZE
#define LOG_RTT_BUFFER_SIZE 256
#endif

/**
 * @def LOG_RTT_COLOR_ENABLE
 *
 * 在RTT Viewer上启用颜色。
 *
 */
#ifndef LOG_RTT_COLOR_ENABLE
#define LOG_RTT_COLOR_ENABLE 1
#endif

/**
 * @def LOG_PARSE_BUFFER_SIZE
 *
 * 用于分析打印格式的日志缓冲区。它将在堆栈上本地分配。
 *
 */
#ifndef LOG_PARSE_BUFFER_SIZE
#define LOG_PARSE_BUFFER_SIZE 128
#endif

/**
 * @def LOG_TIMESTAMP_ENABLE
 *
 * 在日志中启用时间戳。
 *
 */
#ifndef LOG_TIMESTAMP_ENABLE
#define LOG_TIMESTAMP_ENABLE 1
#endif

/**
 * 记录器驱动程序初始化。
 *
 */
void utilsLogRttInit(void);

/**
 * 注销Logger驱动程序。
 *
 */
void utilsLogRttDeinit(void);

/**
 * 此函数将日志输出到SEGGER RTT。
 *
 * @param[in]  aLogLevel   日志级别。
 * @param[in]  aLogRegion  日志区域。
 * @param[in]  aFormat     指向格式字符串的指针。
 * @param[in]  ap          aFormat的va_list匹配信息
 *
 */
void utilsLogRttOutput(otLogLevel aLogLevel, otLogRegion aLogRegion, const char *aFormat, va_list ap);

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // UTILS_LOGGING_RTT_H

