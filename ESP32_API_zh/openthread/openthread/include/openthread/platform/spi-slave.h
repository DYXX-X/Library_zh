/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file spi从属.h
 * @brief 该文件包括SPI从属通信的平台抽象。
 */

#ifndef OPENTHREAD_PLATFORM_SPI_SLAVE_H_
#define OPENTHREAD_PLATFORM_SPI_SLAVE_H_

#include <stdbool.h>
#include <stdint.h>

#include <openthread/error.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup 平板式从动装置
 *
 * @brief 该模块包括SPI从机通信的平台抽象。
 *
 * @{
 *
 */

/**
 * 指示SPI事务已以给定长度完成。写入从属设备的数据已写入到上一次调用“otPlatSpiSlavePrepareTransaction（）”的“aInputBuf”参数所指示的指针。
 *
 * 调用此函数后，`otPlatSpiSlavePrepareTransaction（）`无效，必须再次调用才能使下一个事务有效。
 *
 * 请注意，即使尚未调用“otPlatSpiSlavePrepareTransaction（）”，也始终在事务结束时调用此函数。在这种情况下，“aOutputBufLen”和“aInputBufLen”将为零。
 *
 * 可以从ISR上下文调用此回调。此函数的返回值指示是否需要进一步处理。如果返回“TRUE”，则平台spi从属驱动程序实现必须调用事务进程回调（在“otPlatSpiSlaveEnable（）”中设置的“aProcessCallback”），与此回调不同，必须从调用任何其他OpenThreadAPI/回调的同一OS上下文调用该回调。
 *
 * @param[in] aContext           上下文指针传递到`otPlatSpiSlaveEnable（）`。
 * @param[in] aOutputBuf         上次调用`otPlatSpiSlavePrepareTransaction（）`时`aOutputBuf`的值。
 * @param[in] aOutputBufLen      上次调用`otPlatSpiSlavePrepareTransaction（）`时`aOutputBufLen`的值。
 * @param[in] aInputBuf          上次调用`otPlatSpiSlavePrepareTransaction（）`时的aInputBuf值。
 * @param[in] aInputBufLen       上次调用`otPlatSpiSlavePrepareTransaction（）时的aInputBufLen值`
 * @param[in] aTransactionLength 已完成事务的长度（字节）。
 *
 * @returns  如果此调用返回后，平台应调用进程回调“aProcessCallback”，则为TRUE；如果没有要处理的内容且无需调用进程回调，则为FALSE。
 */
typedef bool (*otPlatSpiSlaveTransactionCompleteCallback)(void *   aContext,
                                                          uint8_t *aOutputBuf,
                                                          uint16_t aOutputBufLen,
                                                          uint8_t *aInputBuf,
                                                          uint16_t aInputBufLen,
                                                          uint16_t aTransactionLength);

/**
 * 在调用事务完成回调后调用，并返回“TRUE”以执行所需的任何进一步处理。与“otPlatSpiSlaveTransactionCompleteCallback”（可以从任何OS上下文（例如ISR）调用）不同，此回调必须从与任何其他OpenThreadAPI/回调相同的OS上下文调用。
 *
 * @param[in] aContext           上下文指针传递到`otPlatSpiSlaveEnable（）`。
 *
 */
typedef void (*otPlatSpiSlaveTransactionProcessCallback)(void *aContext);

/**
 * 初始化SPI从属接口。

 * 请注意，在使用“otPlatSPISlavePrepareTransaction（）”准备事务之前，SPI从机尚未完全就绪。
 *
 * 如果在主机开始事务之前未调用`otPlatSPISlavePrepareTransaction（），则生成的SPI事务将发送所有“0xFF”字节并丢弃所有接收到的字节。
 *
 * @param[in] aCompleteCallback  指向事务完成回调的指针。
 * @param[in] aProcessCallback   指向进程回调的指针。
 * @param[in] aContext           要传递给回调的上下文指针。
 *
 * @retval OT_ERROR_NONE成功启用SPI从接口。
 * @retval OT_ERROR_ALREADY SPI从接口已启用。
 * @retval OT_ERROR_FAILED无法启用SPI从属接口。
 *
 */
otError otPlatSpiSlaveEnable(otPlatSpiSlaveTransactionCompleteCallback aCompleteCallback,
                             otPlatSpiSlaveTransactionProcessCallback  aProcessCallback,
                             void *                                    aContext);

/**
 * 关闭并禁用SPI从属接口。
 */
void otPlatSpiSlaveDisable(void);

/**
 * 为下一个SPI事务准备数据。数据指针必须保持有效，直到SPI从属驱动程序调用事务完成回调，或者直到下一次调用“otPlatSpiSlavePrepareTransaction（）”。
 *
 * 在SPI主机启动事务之前，可以多次调用此函数。对该函数的每一次*成功*调用都将导致先前调用中的先前值被丢弃。
 *
 * 在完成事务后不调用此函数与之前调用此函数时缓冲区长度均设置为零且“aRequestTransactionFlag”设置为“false”相同。
 *
 * 一旦“aOutputBuf”的“aOutoutBufLen”字节被计时，MISO引脚应设置为高电平，直到主控完成SPI事务。这在功能上等同于用“0xFF”字节将“aOutputBuf”的结尾填充到事务的长度。
 *
 * 一旦aInputBuf的“aInputBufLen”字节已从MOSI计时，则在SPI主控器完成事务之前，将忽略MOSI引脚的所有后续值。
 *
 * 请注意，即使在SPI主机完成事务之前耗尽了“aInputBufLen”或“aOutputBufLen”（或两者），仍必须跟踪事务的持续大小，才能将其传递给事务完成回调。例如，如果“aInputBufLen”等于10，“aOutputBufLen”等于20，并且SPI主时钟输出30字节，则将值30传递给事务完成回调。
 *
 * 如果“NULL”指针作为“aOutputBuf”或“aInputBuf”传入，则意味着该缓冲区指针不应改变其先前/当前值。在这种情况下，应忽略相应的长度参数。例如，`otPlatSpiSlavePrepareTransaction（NULL，0，aInputBuf，aInputLen，false）`更改输入缓冲区指针及其长度，但保持输出缓冲区指针与之前相同。
 *
 * 在事务进行过程中对该函数的任何调用都将导致忽略所有参数，返回值为“OT_ERROR_BUSY”。
 *
 * @param[in] aOutputBuf              要写入MISO引脚的数据
 * @param[in] aOutputBufLen           输出缓冲区的大小（字节）
 * @param[in] aInputBuf               从MOSI引脚读取的数据
 * @param[in] aInputBufLen            输入缓冲区的大小（字节）
 * @param[in] aRequestTransactionFlag 如果应设置主机中断，则设置为true
 *
 * @retval OT_ERROR_NONE事务已成功准备。
 * @retval OT_ERROR_BUSY事务当前正在进行中。
 * @retval 尚未调用OT_ERROR_INVALID_STATE otPlatSpiSlaveEnable（）。
 *
 */
otError otPlatSpiSlavePrepareTransaction(uint8_t *aOutputBuf,
                                         uint16_t aOutputBufLen,
                                         uint8_t *aInputBuf,
                                         uint16_t aInputBufLen,
                                         bool     aRequestTransactionFlag);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_PLATFORM_SPI_SLAVE_H_

