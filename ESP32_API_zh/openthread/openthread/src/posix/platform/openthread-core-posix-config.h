/*
 *  版权所有（c）2017，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file 此文件包含OpenThread核心的posix应用程序编译时配置常量。
 */

#ifndef OPENTHREAD_CORE_POSIX_CONFIG_H_
#define OPENTHREAD_CORE_POSIX_CONFIG_H_

/**
 * @def OPENTHREAD_CONFIG_NUM_MESSAGE_BUFFERS
 *
 * 缓冲池中的消息缓冲区数。
 *
 */
#ifndef OPENTHREAD_CONFIG_NUM_MESSAGE_BUFFERS
#define OPENTHREAD_CONFIG_NUM_MESSAGE_BUFFERS 256
#endif

/**
 * @def OPENTHREAD_CONFIG_LOG_PLATFORM
 *
 * 定义以启用平台区域日志记录。
 *
 */
#ifndef OPENTHREAD_CONFIG_LOG_PLATFORM
#define OPENTHREAD_CONFIG_LOG_PLATFORM 1
#endif

/**
 * @def OPENTHREAD_CONFIG_LOG_OUTPUT
 *
 * 选择日志输出。
 *
 */
#ifndef OPENTHREAD_CONFIG_LOG_OUTPUT
#define OPENTHREAD_CONFIG_LOG_OUTPUT OPENTHREAD_CONFIG_LOG_OUTPUT_PLATFORM_DEFINED
#endif

/**
 * @def OPENTHREAD_CONFIG_LOG_LEVEL
 *
 * 定义编译时日志级别，该级别是可以在运行时通过“otLoggingSetLevel”设置的最低日志级别。
 *
 */
#ifndef OPENTHREAD_CONFIG_LOG_LEVEL
#define OPENTHREAD_CONFIG_LOG_LEVEL OT_LOG_LEVEL_DEBG
#endif

/**
 * @def OPENTHREAD_CONFIG_LOG_LEVEL_INIT
 *
 * 初始化OpenThread时使用的初始日志级别。请参见`OPENTHREAD_CONFIG_LOG_LEVEL_DYNAMIC_ENABLE`。
 */
#ifndef OPENTHREAD_CONFIG_LOG_LEVEL_INIT
#define OPENTHREAD_CONFIG_LOG_LEVEL_INIT OT_LOG_LEVEL_CRIT
#endif

/**
 * @def OPENTHREAD_CONFIG_LOG_LEVEL_DYNAMIC_ENABLE
 *
 * 定义为1以启用动态日志级别控制。
 *
 * 请注意，OPENTHREAD_CONFIG_LOG_LEVEL决定编译时的日志级别。动态日志级别控件（如果启用）仅允许从编译时值降低日志级别。
 *
 */
#ifndef OPENTHREAD_CONFIG_LOG_LEVEL_DYNAMIC_ENABLE
#define OPENTHREAD_CONFIG_LOG_LEVEL_DYNAMIC_ENABLE 1
#endif

/**
 * @def OPENTHREAD_CONFIG_PLATFORM_INFO
 *
 * 要插入OpenThread版本字符串的平台特定字符串。
 *
 */
#define OPENTHREAD_CONFIG_PLATFORM_INFO "POSIX"

/**
 * @def OPENTHREAD_CONFIG_IP6_SLAAC_ENABLE
 *
 * 定义为1，以支持OpenThread添加自动配置的SLAC地址。
 *
 */
#ifndef OPENTHREAD_CONFIG_IP6_SLAAC_ENABLE /* 允许命令行覆盖*/
#define OPENTHREAD_CONFIG_IP6_SLAAC_ENABLE 1
#endif

/**
 * @def OPENTHREAD_CONFIG_NCP_HDLC_ENABLE
 *
 * 定义为1以启用NCP HDLC支持。
 *
 */
#define OPENTHREAD_CONFIG_NCP_HDLC_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_PLATFORM_RADIO_COEX_ENABLE
 *
 * 如果要启用平台中实现的无线电共存，请定义为1。
 *
 */
#ifndef OPENTHREAD_CONFIG_PLATFORM_RADIO_COEX_ENABLE
#define OPENTHREAD_CONFIG_PLATFORM_RADIO_COEX_ENABLE 1
#endif

#if OPENTHREAD_POSIX_CONFIG_DAEMON_ENABLE

#ifndef OPENTHREAD_CONFIG_PLATFORM_NETIF_ENABLE
#define OPENTHREAD_CONFIG_PLATFORM_NETIF_ENABLE 1
#endif

#ifndef OPENTHREAD_CONFIG_PLATFORM_UDP_ENABLE
#define OPENTHREAD_CONFIG_PLATFORM_UDP_ENABLE 1
#endif

#endif

/**
 * @def OPENTHREAD_CONFIG_LOG_MAX_SIZE
 *
 * 最大日志字符串大小（字符数）。
 *
 */
#ifndef OPENTHREAD_CONFIG_LOG_MAX_SIZE
#define OPENTHREAD_CONFIG_LOG_MAX_SIZE 1024
#endif

/**
 * @def OPENTHREAD_CONFIG_COMMISSIONER_MAX_JOINER_ENTRIES
 *
 * 专员维护的加入者条目的最大数量。
 *
 */
#ifndef OPENTHREAD_CONFIG_COMMISSIONER_MAX_JOINER_ENTRIES
#define OPENTHREAD_CONFIG_COMMISSIONER_MAX_JOINER_ENTRIES 4
#endif

/**
 * @def OPENTHREAD_CONFIG_TMF_ADDRESS_CACHE_ENTRIES
 *
 * EID到RLOC缓存项的数量。
 *
 */
#ifndef OPENTHREAD_CONFIG_TMF_ADDRESS_CACHE_ENTRIES
#define OPENTHREAD_CONFIG_TMF_ADDRESS_CACHE_ENTRIES 128
#endif

/**
 * @def OPENTHREAD_CONFIG_MLE_MAX_CHILDREN
 *
 * 最大子级数。
 *
 */
#ifndef OPENTHREAD_CONFIG_MLE_MAX_CHILDREN
#define OPENTHREAD_CONFIG_MLE_MAX_CHILDREN 64
#endif

/**
 * @def OPENTHREAD_CONFIG_MLE_IP_ADDRS_PER_CHILD
 *
 * 每个子级支持的IPv6地址注册的最大数量。
 *
 */
#ifndef OPENTHREAD_CONFIG_MLE_IP_ADDRS_PER_CHILD
#define OPENTHREAD_CONFIG_MLE_IP_ADDRS_PER_CHILD 16
#endif

/**
 * @def OPENTHREAD_CONFIG_IP6_MAX_EXT_UCAST_ADDRS
 *
 * 允许外部添加的受支持IPv6地址的最大数量。
 *
 */
#ifndef OPENTHREAD_CONFIG_IP6_MAX_EXT_UCAST_ADDRS
#define OPENTHREAD_CONFIG_IP6_MAX_EXT_UCAST_ADDRS 8
#endif

/**
 * @def OPENTHREAD_CONFIG_IP6_MAX_EXT_MCAST_ADDRS
 *
 * 允许外部添加的受支持IPv6多播地址的最大数量。
 *
 */
#ifndef OPENTHREAD_CONFIG_IP6_MAX_EXT_MCAST_ADDRS
#define OPENTHREAD_CONFIG_IP6_MAX_EXT_MCAST_ADDRS 8
#endif

/**
 * @def OPENTHREAD_CONFIG_HISTORY_TRACKER_ENABLE
 *
 * 定义为1以启用历史跟踪器模块。
 *
 */
#ifndef OPENTHREAD_CONFIG_HISTORY_TRACKER_ENABLE
#define OPENTHREAD_CONFIG_HISTORY_TRACKER_ENABLE 1
#endif

/**
 * @def OPENTHREAD_CONFIG_HEAP_INTERNAL_SIZE
 *
 * 启用DTLS时堆缓冲区的大小。
 *
 */
#ifndef OPENTHREAD_CONFIG_HEAP_INTERNAL_SIZE
#define OPENTHREAD_CONFIG_HEAP_INTERNAL_SIZE (63 * 1024)
#endif

/**
 * @def OPENTHREAD_CONFIG_HEAP_INTERNAL_SIZE_NO_DTLS
 *
 * 禁用DTLS时堆缓冲区的大小。
 *
 */
#ifndef OPENTHREAD_CONFIG_HEAP_INTERNAL_SIZE_NO_DTLS
#define OPENTHREAD_CONFIG_HEAP_INTERNAL_SIZE_NO_DTLS (63 * 1024)
#endif

/**
 * @def OPENTHREAD_CONFIG_CLI_MAX_LINE_LENGTH
 *
 * CLI行的最大大小（字节）。
 *
 */
#ifndef OPENTHREAD_CONFIG_CLI_MAX_LINE_LENGTH
#define OPENTHREAD_CONFIG_CLI_MAX_LINE_LENGTH 640
#endif

/**
 * @def OPENTHREAD_CONFIG_CLI_UART_RX_BUFFER_SIZE
 *
 * CLI UART RX缓冲区的大小（字节）。
 *
 */
#ifndef OPENTHREAD_CONFIG_CLI_UART_RX_BUFFER_SIZE
#define OPENTHREAD_CONFIG_CLI_UART_RX_BUFFER_SIZE 640
#endif

#endif // OPENTHREAD_CORE_POSIX_CONFIG_H_
