/*
 *  版权所有（c）2017，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef OPENTHREAD_PLATFORM_DEBUG_UART_H_
#define OPENTHREAD_PLATFORM_DEBUG_UART_H_

#include <openthread/error.h>
#include <openthread/platform/logging.h>

/**
 * @file
 *
 * 注意：这不是一个公共线程API，并且这个头文件不是作为OpenThread的一部分安装的，这是开发人员在开发过程中可以使用的伪内部调试功能。
 *
 * 这实现了一个非常基本的调试uart，当主uart已经启动（例如NCP）并且封装日志不实用时，该调试uart可用于记录消息。
 *
 * 实施说明：
 *
 * 平台只需要实现3个功能。请在下面的评论中查看/搜索单词MUST。
 *
 * 其他函数（注释中没有MUST）是弱符号，可以由平台或应用程序选择性地覆盖。
 *
 * 许多其他功能只是在开发人员的正常工作过程中帮助他们的方便功能，不打算出现在生产系统中，也不打算用于生产系统中。
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup 内部调试api
 *
 * @{
 */

/**
 * 标准printf（）到调试uart，没有日志修饰。
 *
 * @param[in]   fmt   printf格式化程序文本
 *
 * 这是一个调试方便函数，开发人员不打算在除“调试场景”之外的任何情况下使用它。
 *
 * lf->cr/lf映射通过otPlatDebugUart_putchar（）自动处理
 *
 * @sa otPlatDebugUart_vprintf（）获取限制
 *
 * 这是一个弱符号，可以根据需要轻松覆盖。
 */
void otPlatDebugUart_printf(const char *fmt, ...);

/**
 * 调试uart的标准vprintf（），没有日志修饰。
 *
 * @param[in]   fmt   printf格式化程序文本
 * @param[in]   ap    打印参数的va_list值。
 *
 * 实现限制：这会将文本格式化为堆栈上特意较小的文本缓冲区，因此长消息可能会被截断。
 *
 * 这是一个弱符号，可以根据需要轻松覆盖。
 *
 * 例如，某些平台可能会通过非WEAK符号来覆盖这一点，因为该平台提供了一个类似UART_vprintf（）的函数，可以处理任意长度的输出。
 */
void otPlatDebugUart_vprintf(const char *fmt, va_list ap);

/**
 * 特定于平台的单个字节写入调试Uart这不应执行CR/LF映射。
 *
 * 该功能必须由平台实现
 *
 * @param[in] c   要传输的内容
 */
void otPlatDebugUart_putchar_raw(int c);

/**
 * 如果按下键，轮询/测试调试uart。这对于返回0的存根函数是常见的。
 *
 * 该功能必须由平台实现
 *
 * @retval 零-没有准备好
 * @retval 非零-otPlatDebugUart_getc（）将成功。
 */
int otPlatDebugUart_kbhit(void);

/**
 * 轮询/从调试uart读取一个字节
 *
 * 该功能必须由平台实现
 *
 * @retval （否定）没有可用数据，请参见otPlatDebugUart_kbhit（）
 * @retval （0x00..0x0ff）数据字节值
 *
 */
int otPlatDebugUart_getc(void);

/**
 * 将字节写入uart，根据需要展开cr/lf。
 *
 * 提供了一个WEAK默认实现，可以根据需要进行重写。
 *
 * @param[in] c   要传输的字节
 */
void otPlatDebugUart_putchar(int c);

/**
 * 与“man 3 put”相同-以lf结尾，然后根据需要映射到cr/lf
 *
 * 提供了一个WEAK默认实现，可以根据需要进行重写。
 *
 * @param[in]   s   要在末尾用lf打印的字符串
 */
void otPlatDebugUart_puts(const char *s);

/**
 * 向UART写入N个字节，映射cr/lf
 *
 * @param[in]  pBytes   指向要传输的字节的指针。
 * @param[in]  nBytes   要传输多少字节。
 */
void otPlatDebugUart_write_bytes(const uint8_t *pBytes, int nBytes);

/**
 * puts（）没有终端换行符。参见：“man 3 put”，没有添加终端lf
 *
 * @param[in]  s       要打印的字符串结尾没有lf
 *
 * 注意，终端“lf”通过函数otPlatDebugUart_putchar（）映射到cr/lf
 */
void otPlatDebugUart_puts_no_nl(const char *s);

/**
 * 某些平台（模拟）可以登录到文件。
 *
 * @returns OT_ERROR_NONE
 * @returns OT_ERROR_FAILED
 *
 * 希望这样做的平台必须提供实施。
 *
 */
otError otPlatDebugUart_logfile(const char *filename);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_PLATFORM_DEBUG_UART_H_

