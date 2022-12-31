/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 该文件包括UART通信的平台抽象。
 */

#ifndef OPENTHREAD_PLATFORM_UART_H_
#define OPENTHREAD_PLATFORM_UART_H_

#include <stdint.h>

#include <openthread/error.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup 平板
 *
 * @brief 该模块包括UART通信的平台抽象。
 *
 * @{
 *
 */

/**
 * 启用UART。
 *
 * @retval OT_ERROR_NONE成功启用UART。
 * @retval OT_ERROR_FAILED未能启用UART。
 *
 */
otError otPlatUartEnable(void);

/**
 * 禁用UART。
 *
 * @retval OT_ERROR_NONE成功禁用UART。
 * @retval OT_ERROR_FAILED无法禁用UART。
 *
 */
otError otPlatUartDisable(void);

/**
 * 通过UART发送字节。
 *
 * @param[in] aBuf        指向数据缓冲区的指针。
 * @param[in] aBufLength  要传输的字节数。
 *
 * @retval OT_ERROR_NONE已成功启动传输。
 * @retval OT_ERROR_FAILED无法启动传输。
 *
 */
otError otPlatUartSend(const uint8_t *aBuf, uint16_t aBufLength);

/**
 * 刷新传出传输缓冲区并等待发送数据。当CLI UART接口具有完整的缓冲区但仍希望发送更多数据时，会调用此命令。
 *
 * @retval OT_ERROR_NONE刷新成功，我们可以继续向缓冲区写入更多数据。
 *
 * @retval OT_ERROR_NOT_IMPLEMENTED驱动程序不支持同步刷新。
 * @retval OT_ERROR_INVALID_STATE驱动程序没有要刷新的数据。
 */
otError otPlatUartFlush(void);

/**
 * UART驱动程序调用此方法来通知OpenThread请求的字节已发送。
 *
 */
extern void otPlatUartSendDone(void);

/**
 * UART驱动程序调用此方法来通知OpenThread已收到字节。
 *
 * @param[in]  aBuf        指向接收字节的指针。
 * @param[in]  aBufLength  接收的字节数。
 *
 */
extern void otPlatUartReceived(const uint8_t *aBuf, uint16_t aBufLength);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_PLATFORM_UART_H_

