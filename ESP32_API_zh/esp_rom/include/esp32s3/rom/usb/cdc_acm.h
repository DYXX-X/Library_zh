/*******************************************************************************
 * 版权所有（c）20152016 Intel Corporation。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * *源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。未经事先书面许可，不得使用“英特尔公司”的名称或其贡献者的名称来支持或推广源自此软件的产品。
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/

#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void cdc_acm_device;
extern cdc_acm_device *uart_acm_dev;

#define ACM_BYTES_PER_TX  64

//ACM状态为负值，以区别于USB_DC_*状态代码
#define ACM_STATUS_LINESTATE_CHANGED -1
#define ACM_STATUS_LINECODING_CHANGED -2
#define ACM_STATUS_TX -3
#define ACM_STATUS_RX -4

typedef void(*uart_irq_callback_t)(cdc_acm_device *dev, int status);

/**
 * @brief 获取缓冲区中接收的字符数
 *
 * @returns 字符计数
 */

int cdc_acm_rx_fifo_cnt(cdc_acm_device *dev);


/*
 * @brief 轮询设备以获取输入。
 *
 * @return -ENOTSUP由于底层USB设备控制器始终使用中断，轮询模式UART API不适用于CDC ACM驱动程序导出的UART接口。应用程序应改用fifo_read API。
 */

int cdc_acm_poll_in(cdc_acm_device *dev, unsigned char *c);

/*
 * @brief 以轮询模式输出字符。
 *
 * USB UART的UART轮询方法是通过等待直到我们从USB设备控制器获得下一个BULK In调用或100ms来模拟的。
 *
 * @return 发送的相同字符
 */
unsigned char cdc_acm_poll_out(cdc_acm_device *dev, unsigned char c);

/**
 * @brief 用数据填充FIFO
 *
 * @param dev     CDC ACM设备结构。
 * @param tx_data 要传输的数据。
 * @param len     要发送的字节数。
 *
 * @return 发送的字节数。
 */
int cdc_acm_fifo_fill(cdc_acm_device *dev, const uint8_t *tx_data, int len);

/**
 * @brief 从FIFO读取数据
 *
 * @param dev     CDC ACM设备结构。
 * @param rx_data 指向数据容器的指针。
 * @param size    容器尺寸。
 *
 * @return 读取的字节数。
 */
int cdc_acm_fifo_read(cdc_acm_device *dev, uint8_t *rx_data, const int size);

/**
 * @brief 启用TX中断
 *
 * @param dev CDC ACM设备结构。
 *
 * @return N/A.
 */
void cdc_acm_irq_tx_enable(cdc_acm_device *dev);

/**
 * @brief 禁用TX中断
 *
 * @param dev CDC ACM设备结构。
 *
 * @return N/A.
 */
void cdc_acm_irq_tx_disable(cdc_acm_device *dev);

/**
 * @brief 检查Tx IRQ是否已升高
 *
 * @param dev CDC ACM设备结构。
 *
 * @return 如果Tx IRQ未决，则为1，否则为0。
 */
int cdc_acm_irq_tx_ready(cdc_acm_device *dev);

/**
 * @brief 启用RX中断
 *
 * @param dev CDC ACM设备结构。
 *
 * @return N/A
 */
void cdc_acm_irq_rx_enable(cdc_acm_device *dev);

/**
 * @brief 禁用RX中断
 *
 * @param dev CDC ACM设备结构。
 *
 * @return N/A.
 */
void cdc_acm_irq_rx_disable(cdc_acm_device *dev);

/**
 * @brief 启用线路状态中断
 *
 * @param dev CDC ACM设备结构。
 *
 * @return N/A.
 */
void cdc_acm_irq_state_enable(cdc_acm_device *dev);

/**
 * @brief 禁用线路状态中断
 *
 * @param dev CDC ACM设备结构。
 *
 * @return N/A.
 */
void cdc_acm_irq_state_disable(cdc_acm_device *dev);


/**
 * @brief 检查Rx IRQ是否已提高
 *
 * @param dev CDC ACM设备结构。
 *
 * @return 如果IRQ就绪，则为1，否则为0。
 */
int cdc_acm_irq_rx_ready(cdc_acm_device *dev);

/**
 * @brief 检查Tx或Rx IRQ是否待定
 *
 * @param dev CDC ACM设备结构。
 *
 * @return 如果Tx或Rx IRQ未决，则为1，否则为0。
 */
int cdc_acm_irq_is_pending(cdc_acm_device *dev);

/**
 * @brief 设置IRQ的回调函数指针。
 *
 * @param dev CDC ACM设备结构。
 * @param cb  回调函数指针。
 *
 * @return N/A
 */
void cdc_acm_irq_callback_set(cdc_acm_device *dev, uart_irq_callback_t cb);

/**
 * @brief 操作UART的线路控制。
 *
 * @param dev CDC ACM设备结构
 * @param ctrl 要操纵的行控件
 * @param val 设置行控件的值
 *
 * @return 如果成功，则为0，否则为失败。
 */
int cdc_acm_line_ctrl_set(cdc_acm_device *dev, uint32_t ctrl, uint32_t val);

/**
 * @brief 操作UART的线路控制。
 *
 * @param dev CDC ACM设备结构
 * @param ctrl 要操纵的行控件
 * @param val 设置行控件的值
 *
 * @return 如果成功，则为0，否则为失败。
 */
int cdc_acm_line_ctrl_get(cdc_acm_device *dev, uint32_t ctrl, uint32_t *val);


/**
 * @brief 初始化UART通道
 *
 * 调用此例程将芯片重置为静态。假设每个UART只调用一次此函数。
 *
 * @param mem_chunk 用于内部使用的内存块
 * @param mem_chunk_size 内存块的大小（字节）
 *
 * @return dev或NULL
 */
cdc_acm_device *cdc_acm_init(void *mem_chunk, int mem_chunk_size);


/**UART的公共线路控制。*/
#define LINE_CTRL_BAUD_RATE (1 << 0)
#define LINE_CTRL_RTS       (1 << 1)
#define LINE_CTRL_DTR       (1 << 2)
#define LINE_CTRL_DCD       (1 << 3)
#define LINE_CTRL_DSR       (1 << 4)

/* UART的常见通信错误。*/

/** @brief 超限错误*/
#define UART_ERROR_OVERRUN  (1 << 0)

/** @brief 奇偶校验错误*/
#define UART_ERROR_PARITY   (1 << 1)

/** @brief 成帧错误*/
#define UART_ERROR_FRAMING  (1 << 2)

/**
 * @brief 中断中断错误：
 *
 * 收到中断。当串行输入保持在逻辑“0”状态的时间超过起始时间+数据位+奇偶校验+停止位的总和时，就会发生这种情况。
 */
#define UART_ERROR_BREAK    (1 << 3)

#ifdef __cplusplus
}
#endif

