/*
 *  版权所有（c）2016-2018，The OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件包含OpenThread日志记录相关定义。
 */

#ifndef OPENTHREAD_LOGGING_H_
#define OPENTHREAD_LOGGING_H_

#include <openthread/error.h>
#include <openthread/platform/logging.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api日志记录
 *
 * @brief 本模块包括OpenThread日志记录相关定义。
 *
 * @{
 *
 */

/**
 * 此函数返回当前日志级别。
 *
 * 如果启用了动态日志级别功能`OPENTHREAD_CONFIG_log_level_dynamic_ENABLE`，则此函数将返回当前设置的动态日志级别。否则，此函数将返回构建时配置的日志级别。
 *
 * @returns 日志级别。
 *
 */
otLogLevel otLoggingGetLevel(void);

/**
 * 此函数用于设置日志级别。
 *
 * @note 此函数要求`OPENTHREAD_CONFIG_LOG_LEVEL_DYNAMIC_ENABLE=1'。
 *
 * @param[in]  aLogLevel               日志级别。
 *
 * @retval OT_ERROR_NONE已成功更新日志级别。
 * @retval OT_ERROR_INVALID_ARGS日志级别值无效。
 *
 */
otError otLoggingSetLevel(otLogLevel aLogLevel);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_LOGGING_H_

