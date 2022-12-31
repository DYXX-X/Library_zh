/*
 *  版权所有（c）2020，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file 此文件包含退出代码实用程序的标头。
 */

#ifndef PLATFORM_EXIT_CODE_H_
#define PLATFORM_EXIT_CODE_H_

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 此枚举表示OpenThread退出时使用的退出代码。
 *
 */
enum
{
    /**
     * 成功
     */
    OT_EXIT_SUCCESS = 0,

    /**
     * 一般故障。
     */
    OT_EXIT_FAILURE = 1,

    /**
     * 参数无效。
     */
    OT_EXIT_INVALID_ARGUMENTS = 2,

    /**
     * 不相容的放射性尖晶石。
     */
    OT_EXIT_RADIO_SPINEL_INCOMPATIBLE = 3,

    /**
     * 意外的无线电尖晶石重置。
     */
    OT_EXIT_RADIO_SPINEL_RESET = 4,

    /**
     * 系统调用或库函数错误。
     */
    OT_EXIT_ERROR_ERRNO = 5,

    /**
     * 无线电尖晶石无响应。
     */
    OT_EXIT_RADIO_SPINEL_NO_RESPONSE = 6,
};

/**
 * 此函数将退出代码转换为字符串。
 *
 * @param[in]  aExitCode  退出代码。
 *
 * @returns  退出代码的字符串表示。
 *
 */
const char *otExitCodeToString(uint8_t aExitCode);

/**
 * 此宏检查指定的条件（通常为真），如果条件为假，则记录退出状态并终止程序。
 *
 * @param[in]   aCondition  要验证的条件
 * @param[in]   aExitCode   退出代码。
 *
 */
#define VerifyOrDie(aCondition, aExitCode)                                                                   \
    do                                                                                                       \
    {                                                                                                        \
        if (!(aCondition))                                                                                   \
        {                                                                                                    \
            otLogCritPlat("%s() at %s:%d: %s", __func__, __FILE__, __LINE__, otExitCodeToString(aExitCode)); \
            exit(aExitCode);                                                                                 \
        }                                                                                                    \
    } while (false)

/**
 * 此宏检查指定的错误代码（通常预期会成功），并记录退出状态，如果错误代码不成功，则终止程序。
 *
 * @param[in]  aError  要根据OT_error_NONE评估的错误代码。
 *
 */
#define SuccessOrDie(aError)             \
    VerifyOrDie(aError == OT_ERROR_NONE, \
                (aError == OT_ERROR_INVALID_ARGS ? OT_EXIT_INVALID_ARGUMENTS : OT_EXIT_FAILURE))

/**
 * 此宏无条件地记录退出状态并终止程序。
 *
 * @param[in]   aExitCode   退出代码。
 *
 */
#define DieNow(aExitCode) VerifyOrDie(false, aExitCode)

/**
 * 此宏无条件地记录退出状态和退出消息，并终止程序。
 *
 * @param[in]   aMessage    退出消息。
 * @param[in]   aExitCode   退出代码。
 *
 */
#define DieNowWithMessage(aMessage, aExitCode)                                                 \
    do                                                                                         \
    {                                                                                          \
        otLogCritPlat("exit(%d): %s line %d, %s, %s", aExitCode, __func__, __LINE__, aMessage, \
                      otExitCodeToString(aExitCode));                                          \
        exit(aExitCode);                                                                       \
    } while (false)

#ifdef __cplusplus
}
#endif

#endif // PLATFORM_EXIT_CODE_H_

