/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include <stdio.h>
#include <stdlib.h>

#include "common/arg_macros.hpp"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 此宏验证给定的错误状态是否成功（与值零（0）进行比较），否则，它将发出给定的错误消息并退出程序。
 *
 * @param[in]  aStatus     要针对零（0）评估的标量错误状态。
 * @param[in]  aMessage    失败时打印的可选消息（常量C字符串）。
 *
 */
#define SuccessOrQuit(...)                                                                                      \
    do                                                                                                          \
    {                                                                                                           \
        if ((OT_FIRST_ARG(__VA_ARGS__)) != 0)                                                                   \
        {                                                                                                       \
            fprintf(stderr, "\nFAILED %s:%d - SuccessOrQuit(%s)" OT_SECOND_ARG(__VA_ARGS__) "\n", __FUNCTION__, \
                    __LINE__, _Stringize(OT_FIRST_ARG(__VA_ARGS__)));                                           \
            exit(-1);                                                                                           \
        }                                                                                                       \
    } while (false)

/**
 * 此宏验证给定的布尔条件是否为真，否则将发出给定的错误消息并退出程序。
 *
 * @param[in]  aCondition  要计算的布尔表达式。
 * @param[in]  aMessage    失败时打印的可选消息（常量C字符串）。
 *
 */
#define VerifyOrQuit(...)                                                                                       \
    do                                                                                                          \
    {                                                                                                           \
        if (!(OT_FIRST_ARG(__VA_ARGS__)))                                                                       \
        {                                                                                                       \
            fprintf(stderr, "\nFAILED %s:%d - VerifyOrQuit(%s) " OT_SECOND_ARG(__VA_ARGS__) "\n", __FUNCTION__, \
                    __LINE__, _Stringize(OT_FIRST_ARG(__VA_ARGS__)));                                           \
            exit(-1);                                                                                           \
        }                                                                                                       \
    } while (false)

// 将“aArg”转换为字符串的专用宏
#define _Stringize(aArg) _Stringize2(aArg)
#define _Stringize2(aArg) #aArg

#ifdef __cplusplus
}
#endif

#endif

