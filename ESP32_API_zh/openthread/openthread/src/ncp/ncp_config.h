/*
 *  版权所有（c）2019，The OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file 该文件包括NCP的编译时配置。
 *
 */

#ifndef CONFIG_NCP_H_
#define CONFIG_NCP_H_

#ifndef OPENTHREAD_RADIO
#define OPENTHREAD_RADIO 0
#endif

/**
 * @def OPENTHREAD_CONFIG_NCP_SPI_ENABLE
 *
 * 定义为1以启用NCP SPI支持。
 *
 */
#ifndef OPENTHREAD_CONFIG_NCP_SPI_ENABLE
#define OPENTHREAD_CONFIG_NCP_SPI_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_NCP_HDLC_ENABLE
 *
 * 定义为1以启用NCP HDLC支持。
 *
 */
#ifndef OPENTHREAD_CONFIG_NCP_HDLC_ENABLE
#define OPENTHREAD_CONFIG_NCP_HDLC_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_NCP_TX_BUFFER_SIZE
 *
 * NCP消息缓冲区的大小（字节）。
 *
 */
#ifndef OPENTHREAD_CONFIG_NCP_TX_BUFFER_SIZE
#define OPENTHREAD_CONFIG_NCP_TX_BUFFER_SIZE 2048
#endif

/**
 * @def OPENTHREAD_CONFIG_NCP_HDLC_TX_CHUNK_SIZE
 *
 * NCP HDLC TX块的大小（字节）。
 *
 */
#ifndef OPENTHREAD_CONFIG_NCP_HDLC_TX_CHUNK_SIZE
#define OPENTHREAD_CONFIG_NCP_HDLC_TX_CHUNK_SIZE 2048
#endif

/**
 * @def OPENTHREAD_CONFIG_NCP_HDLC_RX_BUFFER_SIZE
 *
 * NCP HDLC RX缓冲区的大小（字节）。
 *
 */
#ifndef OPENTHREAD_CONFIG_NCP_HDLC_RX_BUFFER_SIZE
#if OPENTHREAD_RADIO
#define OPENTHREAD_CONFIG_NCP_HDLC_RX_BUFFER_SIZE 512
#else
#define OPENTHREAD_CONFIG_NCP_HDLC_RX_BUFFER_SIZE 1300
#endif
#endif // OPENTHREAD_CONFIG_NCP_HDLC_RX_BUFFER_SIZE

/**
 * @def OPENTHREAD_CONFIG_NCP_SPI_BUFFER_SIZE
 *
 * NCP SPI（RX/TX）缓冲区的大小（字节）。
 *
 */
#ifndef OPENTHREAD_CONFIG_NCP_SPI_BUFFER_SIZE
#if OPENTHREAD_RADIO
#define OPENTHREAD_CONFIG_NCP_SPI_BUFFER_SIZE 512
#else
#define OPENTHREAD_CONFIG_NCP_SPI_BUFFER_SIZE 1300
#endif
#endif // OPENTHREAD_CONFIG_NCP_SPI_BUFFER_SIZE

/**
 * @def OPENTHREAD_CONFIG_NCP_SPINEL_ENCRYPTER_EXTRA_DATA_SIZE
 *
 * NCP Spinel Encrypter需要的UART缓冲区中分配的额外数据的大小。
 *
 */
#ifndef OPENTHREAD_CONFIG_NCP_SPINEL_ENCRYPTER_EXTRA_DATA_SIZE
#define OPENTHREAD_CONFIG_NCP_SPINEL_ENCRYPTER_EXTRA_DATA_SIZE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_NCP_SPINEL_LOG_MAX_SIZE
 *
 * NCP使用Spinel“StreamWrite”支持的最大OpenThread日志字符串大小（字符数）。
 *
 */
#ifndef OPENTHREAD_CONFIG_NCP_SPINEL_LOG_MAX_SIZE
#define OPENTHREAD_CONFIG_NCP_SPINEL_LOG_MAX_SIZE 150
#endif

/**
 * @def OPENTHREAD_CONFIG_NCP_ENABLE_PEEK_POKE
 *
 * 定义为1以启用NCP上的偷看/戳功能。
 *
 * Peek/Poke允许主机读取/写入NCP上的内存地址。这是用于调试的。
 *
 */
#ifndef OPENTHREAD_CONFIG_NCP_ENABLE_PEEK_POKE
#define OPENTHREAD_CONFIG_NCP_ENABLE_PEEK_POKE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_NCP_SPINEL_RESPONSE_QUEUE_SIZE
 *
 * NCP Spinel命令响应队列的大小。
 *
 * NCP保证它可以同时响应“OPENTHREAD_CONFIG_NCP_SPINEL_RESPONSE_QUEUE_SIZE”尖晶石命令。尖晶石协议将事务ID（TID）定义为尖晶石命令帧的一部分（TID可以是值0-15，其中TID 0用于不需要响应的帧）。Spinel协议最多支持15个同时命令。
 *
 * 主机驱动程序实现可以进一步限制同时出现的Spine命令帧的数量（例如，wpantend将其限制为两个）。此配置选项可用于减少响应队列大小。
 *
 */
#ifndef OPENTHREAD_CONFIG_NCP_SPINEL_RESPONSE_QUEUE_SIZE
#define OPENTHREAD_CONFIG_NCP_SPINEL_RESPONSE_QUEUE_SIZE 15
#endif

/**
 * @def OPENTHREAD_CONFIG_NCP_ENABLE_MCU_POWER_STATE_CONTROL
 *
 * 定义为1，以支持控制NCP微控制器的所需功率状态。
 *
 * 当底层平台的操作系统进入空闲模式（即，处理所有活动任务/事件，MCU可能进入节能电源状态）时，电源状态指定NCP的微控制器（MCU）的期望电源状态。
 *
 * 电源状态主要决定主机应如何与NCP交互，以及主机是否需要外部触发器（“poke”）才能与NCP通信。
 *
 * 启用后，平台应提供“otPlatSetMcuPowerState（）”和“otPlatGetMcuPowerState（）”函数（请参见“openthread/platform/misc.h”）。然后主机可以使用“SPINEL_PROP_MCU_power_state”控制电源状态。
 *
 */
#ifndef OPENTHREAD_CONFIG_NCP_ENABLE_MCU_POWER_STATE_CONTROL
#define OPENTHREAD_CONFIG_NCP_ENABLE_MCU_POWER_STATE_CONTROL 0
#endif

/**
 * @def OPENTHREAD_ENABLE_NCP_VENDOR_HOOK
 *
 * TODO:完成。
 *
 */
#ifndef OPENTHREAD_ENABLE_NCP_VENDOR_HOOK
#define OPENTHREAD_ENABLE_NCP_VENDOR_HOOK 0
#endif

#endif // CONFIG_NCP_H_

