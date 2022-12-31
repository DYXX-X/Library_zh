/*
 *  版权所有（c）2019，The OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file 此文件包括MAC的编译时配置。
 *
 */

#ifndef CONFIG_MAC_H_
#define CONFIG_MAC_H_

#include "config/time_sync.h"

/**
 * @def OPENTHREAD_CONFIG_MAC_MAX_CSMA_BACKOFFS_DIRECT
 *
 * CSMA-CA算法在宣布信道接入失败之前将尝试的最大回退次数。
 *
 * 等效于IEEE 802.15.4-2006中的macMaxCSMA退避，默认值为4。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_MAX_CSMA_BACKOFFS_DIRECT
#define OPENTHREAD_CONFIG_MAC_MAX_CSMA_BACKOFFS_DIRECT 4
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_MAX_CSMA_BACKOFFS_INDIRECT
 *
 * CSMA-CA算法在宣布信道接入失败之前将尝试的最大回退次数。
 *
 * 等效于IEEE 802.15.4-2006中的macMaxCSMA退避，默认值为4。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_MAX_CSMA_BACKOFFS_INDIRECT
#define OPENTHREAD_CONFIG_MAC_MAX_CSMA_BACKOFFS_INDIRECT 4
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_DEFAULT_MAX_FRAME_RETRIES_DIRECT
 *
 * 直接传输失败后允许的默认最大重试次数。
 *
 * 等效于macMaxFrameRetries，默认值为15。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_DEFAULT_MAX_FRAME_RETRIES_DIRECT
#define OPENTHREAD_CONFIG_MAC_DEFAULT_MAX_FRAME_RETRIES_DIRECT 15
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_DEFAULT_MAX_FRAME_RETRIES_INDIRECT
 *
 * 间接传输失败后允许的默认最大重试次数。
 *
 * 等效于macMaxFrameRetries，默认值为0。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_DEFAULT_MAX_FRAME_RETRIES_INDIRECT
#define OPENTHREAD_CONFIG_MAC_DEFAULT_MAX_FRAME_RETRIES_INDIRECT 0
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_RETRY_SUCCESS_HISTOGRAM_ENABLE
 *
 * 定义为1以启用MAC重试数据包直方图分析。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_RETRY_SUCCESS_HISTOGRAM_ENABLE
#define OPENTHREAD_CONFIG_MAC_RETRY_SUCCESS_HISTOGRAM_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_RETRY_SUCCESS_HISTOGRAM_MAX_SIZE_COUNT_DIRECT
 *
 * 成功消息重试直接传输的MAC直方图阵列的默认大小。
 *
 * 默认值为（OPENTHREAD_CONFIGMAC_Default_MAX_FRAME_RETRIES_DIRECT+1）。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_RETRY_SUCCESS_HISTOGRAM_MAX_SIZE_COUNT_DIRECT
#define OPENTHREAD_CONFIG_MAC_RETRY_SUCCESS_HISTOGRAM_MAX_SIZE_COUNT_DIRECT \
    (OPENTHREAD_CONFIG_MAC_DEFAULT_MAX_FRAME_RETRIES_DIRECT + 1)
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_RETRY_SUCCESS_HISTOGRAM_MAX_SIZE_COUNT_INDIRECT
 *
 * 成功消息重试直接传输的MAC直方图阵列的默认大小。
 *
 * 默认值为（OPENTHREAD_CONFIGMAC_Default_MAX_FRAME_RETRIES_INDIRECT+1）。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_RETRY_SUCCESS_HISTOGRAM_MAX_SIZE_COUNT_INDIRECT
#define OPENTHREAD_CONFIG_MAC_RETRY_SUCCESS_HISTOGRAM_MAX_SIZE_COUNT_INDIRECT \
    (OPENTHREAD_CONFIG_MAC_DEFAULT_MAX_FRAME_RETRIES_INDIRECT + 1)
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_MAX_TX_ATTEMPTS_INDIRECT_POLLS
 *
 * 排队的间接事务的最大接收IEEE 802.15.4数据请求数。
 *
 * 间接帧保持在事务队列中，直到它被成功发送，或者直到在接收到最大数量的IEEE 802.15.4数据请求消息之后间接传输失败。
 *
 * 取代macTransactionPersistenceTime。时间段是以IEEE 802.15.4数据请求接收为单位指定的，而不是由macBeacon Order控制。
 *
 * @sa OPENTHREAD_CONFIG_MAC_DEFAULT_MAX_FRAME_RETRIES_INDIRECT
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_MAX_TX_ATTEMPTS_INDIRECT_POLLS
#define OPENTHREAD_CONFIG_MAC_MAX_TX_ATTEMPTS_INDIRECT_POLLS 4
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_CSL_REQUEST_AHEAD_US
 *
 * 定义MAC应提前多少微秒向SubMac发送CSL帧。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_CSL_REQUEST_AHEAD_US
#define OPENTHREAD_CONFIG_MAC_CSL_REQUEST_AHEAD_US 2000
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_FILTER_ENABLE
 *
 * 定义为1以启用MAC筛选器支持。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_FILTER_ENABLE
#define OPENTHREAD_CONFIG_MAC_FILTER_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_FILTER_SIZE
 *
 * MAC筛选器条目的数量。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_FILTER_SIZE
#define OPENTHREAD_CONFIG_MAC_FILTER_SIZE 32
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_TX_NUM_BCAST
 *
 * 每个IEEE 802.15.4广播帧被发送的次数。
 *
 * 最小值为1。大于1的值可以通过增加冗余来提高广播可靠性，但也可能增加拥塞。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_TX_NUM_BCAST
#define OPENTHREAD_CONFIG_MAC_TX_NUM_BCAST 1
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_STAY_AWAKE_BETWEEN_FRAGMENTS
 *
 * 定义为1，以在发送大数据包时在片段之间保持清醒，并在接收到帧挂起设置为真的数据包后保持清醒。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_STAY_AWAKE_BETWEEN_FRAGMENTS
#define OPENTHREAD_CONFIG_MAC_STAY_AWAKE_BETWEEN_FRAGMENTS 0
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_JOIN_BEACON_VERSION
 *
 * 设置信标加入标志时要使用的信标版本。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_JOIN_BEACON_VERSION
#define OPENTHREAD_CONFIG_MAC_JOIN_BEACON_VERSION OPENTHREAD_CONFIG_THREAD_VERSION
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_BEACON_RSP_WHEN_JOINABLE_ENABLE
 *
 * 定义为1以在启用加入时启用IEEE 802.15.4信标。
 *
 * @note 启用此功能后，即使设备不支持路由器且已分离，设备也会响应IEEE 802.15.4信标请求发送IEEE 802.15.4信号。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_BEACON_RSP_WHEN_JOINABLE_ENABLE
#define OPENTHREAD_CONFIG_MAC_BEACON_RSP_WHEN_JOINABLE_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_HEADER_IE_SUPPORT
 *
 * 定义为1以支持IEEE 802.15.4-2015报头IE（信息元素）生成和解析，必须将其设置为支持以下功能：1.时间同步服务功能（即，设置OPENTHREAD_COONFIG_Time_SYNC_ENABLE）。2.螺纹1.2。
 *
 * @note 若启用了它，平台必须支持中断上下文和并发访问AES。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_HEADER_IE_SUPPORT
#if OPENTHREAD_CONFIG_TIME_SYNC_ENABLE || (OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2)
#define OPENTHREAD_CONFIG_MAC_HEADER_IE_SUPPORT 1
#else
#define OPENTHREAD_CONFIG_MAC_HEADER_IE_SUPPORT 0
#endif
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_ATTACH_DATA_POLL_PERIOD
 *
 * 连接期间的数据轮询周期（毫秒）。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_ATTACH_DATA_POLL_PERIOD
#define OPENTHREAD_CONFIG_MAC_ATTACH_DATA_POLL_PERIOD 100
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_MINIMUM_POLL_PERIOD
 *
 * 此设置以毫秒为单位配置最小轮询周期。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_MINIMUM_POLL_PERIOD
#define OPENTHREAD_CONFIG_MAC_MINIMUM_POLL_PERIOD 10
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_RETX_POLL_PERIOD
 *
 * 此设置以毫秒为单位配置retx轮询周期。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_RETX_POLL_PERIOD
#define OPENTHREAD_CONFIG_MAC_RETX_POLL_PERIOD 1000
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_SOFTWARE_ACK_TIMEOUT_ENABLE
 *
 * 定义为1以启用软件ACK超时逻辑。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_SOFTWARE_ACK_TIMEOUT_ENABLE
#define OPENTHREAD_CONFIG_MAC_SOFTWARE_ACK_TIMEOUT_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_SOFTWARE_RETRANSMIT_ENABLE
 *
 * 定义为1以启用软件重传逻辑。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_SOFTWARE_RETRANSMIT_ENABLE
#define OPENTHREAD_CONFIG_MAC_SOFTWARE_RETRANSMIT_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_SOFTWARE_CSMA_BACKOFF_ENABLE
 *
 * 定义为1以启用软件CSMA-CA回退逻辑。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_SOFTWARE_CSMA_BACKOFF_ENABLE
#define OPENTHREAD_CONFIG_MAC_SOFTWARE_CSMA_BACKOFF_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_SOFTWARE_TX_SECURITY_ENABLE
 *
 * 定义为1以启用软件传输安全逻辑。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_SOFTWARE_TX_SECURITY_ENABLE
#define OPENTHREAD_CONFIG_MAC_SOFTWARE_TX_SECURITY_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_SOFTWARE_TX_TIMING_ENABLE
 *
 * 定义为1以启用软件传输目标时间逻辑。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_SOFTWARE_TX_TIMING_ENABLE
#define OPENTHREAD_CONFIG_MAC_SOFTWARE_TX_TIMING_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_SOFTWARE_RX_TIMING_ENABLE
 *
 * 定义为1以启用软件接收目标时间逻辑。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_SOFTWARE_RX_TIMING_ENABLE
#define OPENTHREAD_CONFIG_MAC_SOFTWARE_RX_TIMING_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_SOFTWARE_ENERGY_SCAN_ENABLE
 *
 * 定义为1以启用软件能量扫描逻辑。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_SOFTWARE_ENERGY_SCAN_ENABLE
#define OPENTHREAD_CONFIG_MAC_SOFTWARE_ENERGY_SCAN_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_CSL_TRANSMITTER_ENABLE
 *
 * 定义为1以启用csl变送器逻辑。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_CSL_TRANSMITTER_ENABLE
#define OPENTHREAD_CONFIG_MAC_CSL_TRANSMITTER_ENABLE (OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2)
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_CSL_RECEIVER_ENABLE
 *
 * 此设置配置线程1.2中的CSL接收器功能。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_CSL_RECEIVER_ENABLE
#define OPENTHREAD_CONFIG_MAC_CSL_RECEIVER_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_CSL_AUTO_SYNC_ENABLE
 *
 * 此设置基于线程1.2中的数据轮询机制配置CSL自动同步。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_CSL_AUTO_SYNC_ENABLE
#define OPENTHREAD_CONFIG_MAC_CSL_AUTO_SYNC_ENABLE OPENTHREAD_CONFIG_MAC_CSL_RECEIVER_ENABLE
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_CSL_MIN_PERIOD
 *
 * 此设置以毫秒为单位配置可以使用的最小CSL周期。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_CSL_MIN_PERIOD
#define OPENTHREAD_CONFIG_MAC_CSL_MIN_PERIOD 10
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_CSL_MAX_TIMEOUT
 *
 * 此设置以秒为单位配置可使用的最大CSL超时。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_CSL_MAX_TIMEOUT
#define OPENTHREAD_CONFIG_MAC_CSL_MAX_TIMEOUT 10000
#endif

/**
 * @def OPENTHREAD_CONFIG_CSL_TIMEOUT
 *
 * 默认CSL超时（秒）。
 *
 */
#ifndef OPENTHREAD_CONFIG_CSL_TIMEOUT
#define OPENTHREAD_CONFIG_CSL_TIMEOUT 100
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_CSL_DEBUG_ENABLE
 *
 * CSL接收器调试选项。启用此选项后，CSL接收器实际上不会在CSL状态下休眠，因此它仍然可以从CSL发送器接收数据包。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_CSL_DEBUG_ENABLE
#define OPENTHREAD_CONFIG_MAC_CSL_DEBUG_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_CSL_RECEIVE_TIME_AHEAD
 *
 * CSL接收机准备就绪所需的接收调度和斜升时间，单位为微秒。
 *
 */
#ifndef OPENTHREAD_CONFIG_CSL_RECEIVE_TIME_AHEAD
#define OPENTHREAD_CONFIG_CSL_RECEIVE_TIME_AHEAD 320
#endif

/**
 * @def OPENTHREAD_CONFIG_CSL_MIN_RECEIVE_ON
 *
 * 接收IEEE 802.15.4帧所需的最小CSL接收窗口（以微秒为单位）。
 * -带前导码的最大帧大小：6*2+127*2个符号
 * -AIFS:12个符号
 * -前导码的最大ACK大小：6*2+33*2个符号
 *
 */
#ifndef OPENTHREAD_CONFIG_CSL_MIN_RECEIVE_ON
#define OPENTHREAD_CONFIG_CSL_MIN_RECEIVE_ON 356 * 16
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_SCAN_DURATION
 *
 * 此设置以毫秒为单位配置默认扫描持续时间。
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_SCAN_DURATION
#define OPENTHREAD_CONFIG_MAC_SCAN_DURATION 300
#endif

#endif // CONFIG_MAC_H_

