/*
 * 版权所有（c）2017-2019，Nordic Semiconductor ASA保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。
 *
 * 2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。
 *
 * 3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef NRFX_LOG_H__
#define NRFX_LOG_H__

// THIS IS A TEMPLATE FILE.
// 应将其复制到主机环境中的适当位置
// 其中nrfx是集成的，并且应提供以下宏
// 适当的实现。
// 应该从自定义文件中删除此注释。

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup 编号fx_log编号fx_log.h@{
 * @ingroup 国家外汇基金
 *
 * @brief 此文件包含宏，这些宏应根据集成了@em nrfx的主机环境的需要来实现。
 */

/**
 * @brief 用于记录严重级别为ERROR的消息的宏。
 *
 * @param format printf样式的格式字符串，可选地后跟要格式化并插入到结果字符串中的参数。
 */
#define NRFX_LOG_ERROR(format, ...)

/**
 * @brief 用于记录严重级别为“警告”的消息的宏。
 *
 * @param format printf样式的格式字符串，可选地后跟要格式化并插入到结果字符串中的参数。
 */
#define NRFX_LOG_WARNING(format, ...)

/**
 * @brief 用于记录严重级别为INFO的消息的宏。
 *
 * @param format printf样式的格式字符串，可选地后跟要格式化并插入到结果字符串中的参数。
 */
#define NRFX_LOG_INFO(format, ...)

/**
 * @brief 用于记录严重级别为DEBUG的消息的宏。
 *
 * @param format printf样式的格式字符串，可选地后跟要格式化并插入到结果字符串中的参数。
 */
#define NRFX_LOG_DEBUG(format, ...)


/**
 * @brief 用于记录严重级别为ERROR的内存转储的宏。
 *
 * @param[in] p_memory 指向要转储的内存区域的指针。
 * @param[in] length   内存区域的长度（字节）。
 */
#define NRFX_LOG_HEXDUMP_ERROR(p_memory, length)

/**
 * @brief 用于记录严重级别为“警告”的内存转储的宏。
 *
 * @param[in] p_memory 指向要转储的内存区域的指针。
 * @param[in] length   内存区域的长度（字节）。
 */
#define NRFX_LOG_HEXDUMP_WARNING(p_memory, length)

/**
 * @brief 用于记录严重级别为INFO的内存转储的宏。
 *
 * @param[in] p_memory 指向要转储的内存区域的指针。
 * @param[in] length   内存区域的长度（字节）。
 */
#define NRFX_LOG_HEXDUMP_INFO(p_memory, length)

/**
 * @brief 用于记录严重级别为DEBUG的内存转储的宏。
 *
 * @param[in] p_memory 指向要转储的内存区域的指针。
 * @param[in] length   内存区域的长度（字节）。
 */
#define NRFX_LOG_HEXDUMP_DEBUG(p_memory, length)


/**
 * @brief 用于获取给定错误代码的文本表示的宏。
 *
 * @param[in] error_code 错误代码。
 *
 * @return 包含错误代码文本表示的字符串。
 */
#define NRFX_LOG_ERROR_STRING_GET(error_code)

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NRFX_LOG_H__

