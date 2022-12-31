/*
 *  版权所有（c）2018，The OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * 该头文件定义了NCP构建中用于“toranj”测试框架的OpenThread核心配置选项。
 *
 */

#if !defined(OPENTHREAD_CORE_TORANJ_CONFIG_SIMULATION_H_) && !defined(OPENTHREAD_CORE_TORANJ_CONFIG_POSIX_H_)
#error "This header file should only be included through the platform-specific one"
#endif

#ifndef OPENTHREAD_RADIO
#define OPENTHREAD_RADIO 0
#endif

#ifndef OPENTHREAD_RADIO
#define OPENTHREAD_RADIO_CLI 0
#endif

/**
 * @def OPENTHREAD_CONFIG_REFERENCE_DEVICE_ENABLE
 *
 * 定义为1以启用螺纹测试线束参考设备支持。
 *
 */
#define OPENTHREAD_CONFIG_REFERENCE_DEVICE_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_UPTIME_ENABLE
 *
 * 定义为1以启用跟踪OpenThread实例的正常运行时间。
 *
 */
#define OPENTHREAD_CONFIG_UPTIME_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_BORDER_ROUTER_ENABLE
 *
 * 定义为1以启用边界路由器支持。
 *
 */
#define OPENTHREAD_CONFIG_BORDER_ROUTER_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_COMMISSIONER_ENABLE
 *
 * 定义为1以启用专员支持。
 *
 */
#define OPENTHREAD_CONFIG_COMMISSIONER_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_COMMISSIONER_MAX_JOINER_ENTRIES
 *
 * 专员维护的加入者条目的最大数量。
 *
 */
#define OPENTHREAD_CONFIG_COMMISSIONER_MAX_JOINER_ENTRIES 4

/**
 * @def OPENTHREAD_CONFIG_BORDER_AGENT_ENABLE
 *
 * 定义为1以启用边界代理支持。
 *
 */
#define OPENTHREAD_CONFIG_BORDER_AGENT_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_DIAG_ENABLE
 *
 * 定义为1以启用工厂诊断支持。
 *
 */
#define OPENTHREAD_CONFIG_DIAG_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_JOINER_ENABLE
 *
 * 定义为1以启用Joiner支持。
 *
 */
#define OPENTHREAD_CONFIG_JOINER_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_TMF_NETDATA_SERVICE_ENABLE
 *
 * 定义为1以支持将服务条目注入线程网络数据。
 *
 */
#define OPENTHREAD_CONFIG_TMF_NETDATA_SERVICE_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_NETDATA_PUBLISHER_ENABLE
 *
 * 定义为1以启用网络数据发布器。
 *
 */
#define OPENTHREAD_CONFIG_NETDATA_PUBLISHER_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_TMF_ANYCAST_LOCATOR_ENABLE
 *
 * 定义为1以启用TMF选播定位器功能。
 *
 */
#define OPENTHREAD_CONFIG_TMF_ANYCAST_LOCATOR_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_LEGACY_ENABLE
 *
 * 定义为1以启用传统网络支持。
 *
 */
#define OPENTHREAD_CONFIG_LEGACY_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_ECDSA_ENABLE
 *
 * 定义为1以启用ECDSA支持。
 *
 */
#define OPENTHREAD_CONFIG_ECDSA_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_JAM_DETECTION_ENABLE
 *
 * 定义为1以启用卡纸检测服务。
 *
 */
#define OPENTHREAD_CONFIG_JAM_DETECTION_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_NUM_MESSAGE_BUFFERS
 *
 * 缓冲池中的消息缓冲区数。
 *
 */
#define OPENTHREAD_CONFIG_NUM_MESSAGE_BUFFERS 256

/**
 * @def OPENTHREAD_CONFIG_MESSAGE_USE_HEAP_ENABLE
 *
 * 是否对消息缓冲区使用堆分配器。
 *
 */
#define OPENTHREAD_CONFIG_MESSAGE_USE_HEAP_ENABLE 0

/**
 * @def OPENTHREAD_CONFIG_TMF_ADDRESS_CACHE_ENTRIES
 *
 * EID到RLOC缓存项的数量。
 *
 */
#define OPENTHREAD_CONFIG_TMF_ADDRESS_CACHE_ENTRIES 16

/**
 * @def OPENTHREAD_CONFIG_TMF_ADDRESS_QUERY_TIMEOUT
 *
 * 发送地址查询后等待地址通知响应的超时值（秒）。
 *
 * 默认值：3秒
 *
 */
#define OPENTHREAD_CONFIG_TMF_ADDRESS_QUERY_TIMEOUT 6

/**
 * @def OPENTHREAD_CONFIG_TMF_ADDRESS_QUERY_INITIAL_RETRY_DELAY
 *
 * 地址查询的初始重试延迟（秒）。
 *
 */
#define OPENTHREAD_CONFIG_TMF_ADDRESS_QUERY_INITIAL_RETRY_DELAY 4

/**
 * @def OPENTHREAD_CONFIG_TMF_ADDRESS_QUERY_MAX_RETRY_DELAY
 *
 * 地址查询的最大重试延迟（秒）。
 *
 * 默认值：28800秒（480分钟或8小时）
 *
 */
#define OPENTHREAD_CONFIG_TMF_ADDRESS_QUERY_MAX_RETRY_DELAY 120

/**
 * @def OPENTHREAD_CONFIG_TMF_ADDRESS_CACHE_MAX_SNOOP_ENTRIES
 *
 * 可用于“窥探优化”的EID到RLOC缓存条目的最大数量，其中通过检查接收到的消息来创建条目。
 *
 */
#define OPENTHREAD_CONFIG_TMF_ADDRESS_CACHE_MAX_SNOOP_ENTRIES 2

/**
 * @def OPENTHREAD_CONFIG_TMF_SNOOP_CACHE_ENTRY_TIMEOUT
 *
 * 阻止通过窥探优化（即，检查接收到的消息）创建的地址缓存项被逐出的超时值（以秒为单位）。超时过期后，可以再次回收条目。此超时允许接收到的消息有更长的响应延迟，从而有更多的机会使用窥探条目（避免在响应消息发送到先前接收到消息的同一目的地时发送地址查询）。
 *
 */
#define OPENTHREAD_CONFIG_TMF_SNOOP_CACHE_ENTRY_TIMEOUT 3

/**
 * @def OPENTHREAD_CONFIG_MLE_MAX_CHILDREN
 *
 * 最大子级数。
 *
 */
#define OPENTHREAD_CONFIG_MLE_MAX_CHILDREN 32

/**
 * @def OPENTHREAD_CONFIG_MLE_CHILD_TIMEOUT_DEFAULT
 *
 * 默认子超时值（以秒为单位）。
 *
 */
#define OPENTHREAD_CONFIG_MLE_CHILD_TIMEOUT_DEFAULT 120

/**
 * @def OPENTHREAD_CONFIG_MLE_IP_ADDRS_PER_CHILD
 *
 * 每个子级支持的IPv6地址注册的最大数量。
 *
 */
#define OPENTHREAD_CONFIG_MLE_IP_ADDRS_PER_CHILD 10

/**
 * @def OPENTHREAD_CONFIG_IP6_MAX_EXT_UCAST_ADDRS
 *
 * 允许外部添加的受支持IPv6地址的最大数量。
 *
 */
#define OPENTHREAD_CONFIG_IP6_MAX_EXT_UCAST_ADDRS 8

/**
 * @def OPENTHREAD_CONFIG_IP6_MAX_EXT_MCAST_ADDRS
 *
 * 允许外部添加的受支持IPv6多播地址的最大数量。
 *
 */
#define OPENTHREAD_CONFIG_IP6_MAX_EXT_MCAST_ADDRS 4

/**
 * @def OPENTHREAD_CONFIG_MAC_FILTER_ENABLE
 *
 * 定义为1以启用MAC筛选器支持。
 *
 */
#define OPENTHREAD_CONFIG_MAC_FILTER_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_MAC_FILTER_SIZE
 *
 * MAC筛选器条目的数量。
 *
 */
#define OPENTHREAD_CONFIG_MAC_FILTER_SIZE 80

/**
 * @def OPENTHREAD_CONFIG_LOG_LEVEL
 *
 * 日志级别（在编译时使用）。
 *
 */
#define OPENTHREAD_CONFIG_LOG_LEVEL OT_LOG_LEVEL_INFO

/**
 * @def OPENTHREAD_CONFIG_LOG_LEVEL_DYNAMIC_ENABLE
 *
 * 定义为1以启用动态日志级别控制。
 *
 */
#define OPENTHREAD_CONFIG_LOG_LEVEL_DYNAMIC_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_LOG_PREPEND_UPTIME
 *
 * 定义为1，将当前正常运行时间提前到所有日志消息。
 *
 */
#define OPENTHREAD_CONFIG_LOG_PREPEND_UPTIME 1

/**
 * @def OPENTHREAD_CONFIG_LOG_PREPEND_LEVEL
 *
 * 定义为所有日志消息添加日志级别
 *
 */
#define OPENTHREAD_CONFIG_LOG_PREPEND_LEVEL 1

/**
 * @def OPENTHREAD_CONFIG_LOG_PREPEND_REGION
 *
 * 定义在所有日志消息之前添加日志区域
 *
 */
#define OPENTHREAD_CONFIG_LOG_PREPEND_REGION 1

/**
 * @def OPENTHREAD_CONFIG_LOG_SUFFIX
 *
 * 定义要附加在日志末尾的后缀。
 *
 */
#define OPENTHREAD_CONFIG_LOG_SUFFIX ""

/**
 * @def OPENTHREAD_CONFIG_LOG_PLATFORM
 *
 * 定义以启用平台区域日志记录。
 *
 */
#define OPENTHREAD_CONFIG_LOG_PLATFORM 1

/**
 * @def OPENTHREAD_CONFIG_NCP_HDLC_ENABLE
 *
 * 定义为1以启用NCP HDLC支持。
 *
 */
#define OPENTHREAD_CONFIG_NCP_HDLC_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_NCP_TX_BUFFER_SIZE
 *
 *  NCP消息缓冲区的大小（字节）
 *
 */
#define OPENTHREAD_CONFIG_NCP_TX_BUFFER_SIZE 4096

/**
 * @def OPENTHREAD_CONFIG_MLE_STEERING_DATA_SET_OOB_ENABLE
 *
 * 启用带外转向数据设置。
 *
 */
#define OPENTHREAD_CONFIG_MLE_STEERING_DATA_SET_OOB_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_MLE_INFORM_PREVIOUS_PARENT_ON_REATTACH
 *
 * 将子级定义为1，以在其连接到新父级时通知其上一个父级。
 *
 * 如果启用了此功能，当设备连接到新的父级时，它将向上一个父级发送一条IP消息（带有空的有效负载和网格本地IP地址作为源地址）。
 *
 */
#define OPENTHREAD_CONFIG_MLE_INFORM_PREVIOUS_PARENT_ON_REATTACH 1

/**
 * @def OPENTHREAD_CONFIG_CHANNEL_MANAGER_ENABLE
 *
 * 定义为1以启用Channel Manager支持。
 *
 */
#define OPENTHREAD_CONFIG_CHANNEL_MANAGER_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_CHANNEL_MONITOR_ENABLE
 *
 * 定义为1以启用通道监视器支持。
 *
 */
#define OPENTHREAD_CONFIG_CHANNEL_MONITOR_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_CHANNEL_MANAGER_MINIMUM_DELAY
 *
 * Channel Manager模块用于执行频道更改的最小延迟（秒）。
 *
 * 最小延迟最好比线程网络内所有休眠终端设备使用的最大数据轮询间隔长。
 *
 * 仅在启用了Channel Manager功能时适用（即设置了“OPENTHREAD_CONFIG_Channel_Manager_ENABLE”）。
 *
 */
#define OPENTHREAD_CONFIG_CHANNEL_MANAGER_MINIMUM_DELAY 2

/**
 * @def OPENTHREAD_CONFIG_CHANNEL_MANAGER_THRESHOLD_TO_SKIP_FAVORED
 *
 * 此阈值指定两个频道之间的最小占用率差异，以便频道管理器选择不受欢迎的频道而不是最受欢迎的一个频道。当（自动）根据“频道监视器”功能收集的频道质量数据选择频道时，使用此选项。
 *
 * 差异基于“ChannelMonitor:：GetChannelOccupancy（）”定义，该定义提供了指示信道忙（即RSSI值高于阈值）的RSSI样本的平均百分比（在时间窗口内）。值0映射到0%，0xffff映射到100%。
 *
 * 仅在启用了Channel Manager功能时适用（即设置了“OPENTHREAD_CONFIG_Channel_Manager_ENABLE”）。
 *
 */
#define OPENTHREAD_CONFIG_CHANNEL_MANAGER_THRESHOLD_TO_SKIP_FAVORED (0xffff * 7 / 100)

/**
 * @def OPENTHREAD_CONFIG_CHANNEL_MANAGER_THRESHOLD_TO_CHANGE_CHANNEL
 *
 * 此阈值指定当前频道和频道管理器允许频道更改到新频道所需的新选择频道之间的最小占用率差异。
 *
 * 差异基于“ChannelMonitor:：GetChannelOccupancy（）”定义，该定义提供了指示信道忙（即RSSI值高于阈值）的RSSI样本的平均百分比（在时间窗口内）。值0映射到0%速率，0xffff映射到100%。
 *
 * 仅在启用了Channel Manager功能时适用（即设置了“OPENTHREAD_CONFIG_Channel_Manager_ENABLE”）。
 *
 */
#define OPENTHREAD_CONFIG_CHANNEL_MANAGER_THRESHOLD_TO_CHANGE_CHANNEL (0xffff * 10 / 100)

/**
 * @def OPENTHREAD_CONFIG_CHILD_SUPERVISION_ENABLE
 *
 * 定义为1以启用儿童监督支持。
 *
 */
#define OPENTHREAD_CONFIG_CHILD_SUPERVISION_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_TMF_PENDING_DATASET_MINIMUM_DELAY
 *
 * 挂起操作数据集的最小延迟计时器值（毫秒）。
 *
 * 线程规范将此值定义为30000。应仅在测试时更改指定值。
 *
 * 对于“toranj”测试脚本，该值将减小，以便可以更快地运行测试。
 *
 */
#define OPENTHREAD_CONFIG_TMF_PENDING_DATASET_MINIMUM_DELAY 1000

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
#define OPENTHREAD_CONFIG_NCP_ENABLE_MCU_POWER_STATE_CONTROL 1

/**
 * @def OPENTHREAD_CONFIG_IP6_SLAAC_ENABLE
 *
 * 定义为1，以支持OpenThread添加自动配置的SLAC地址。
 *
 */
#define OPENTHREAD_CONFIG_IP6_SLAAC_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_DNS_CLIENT_ENABLE
 *
 * 定义为1以启用DNS客户端支持。
 *
 */
#define OPENTHREAD_CONFIG_DNS_CLIENT_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_SRP_CLIENT_ENABLE
 *
 * 定义为1以启用SRP客户端支持。
 *
 */
#define OPENTHREAD_CONFIG_SRP_CLIENT_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_SRP_SERVER_ENABLE
 *
 * 定义为1以启用SRP服务器支持。
 *
 */
#define OPENTHREAD_CONFIG_SRP_SERVER_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_SRP_CLIENT_DOMAIN_NAME_CHANGE_ENABLE
 *
 * 为SRP客户端实现定义为1，以提供允许设置/更改域名的API。
 *
 */
#define OPENTHREAD_CONFIG_SRP_CLIENT_DOMAIN_NAME_API_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_HISTORY_TRACKER_ENABLE
 *
 * 定义为1以启用历史跟踪器模块。
 *
 */
#define OPENTHREAD_CONFIG_HISTORY_TRACKER_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_DNSSD_SERVER_ENABLE
 *
 * 定义为1以启用DNS-SD服务器支持。
 *
 */
#define OPENTHREAD_CONFIG_DNSSD_SERVER_ENABLE 1

#if OPENTHREAD_RADIO
/**
 * @def OPENTHREAD_CONFIG_MAC_SOFTWARE_ACK_TIMEOUT_ENABLE
 *
 * 如果要启用软件ACK超时逻辑，请定义为1。
 *
 */
#define OPENTHREAD_CONFIG_MAC_SOFTWARE_ACK_TIMEOUT_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_MAC_SOFTWARE_RETRANSMIT_ENABLE
 *
 * 如果要启用软件重传逻辑，请定义为1。
 *
 */
#define OPENTHREAD_CONFIG_MAC_SOFTWARE_RETRANSMIT_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_MAC_SOFTWARE_CSMA_BACKOFF_ENABLE
 *
 * 如果要启用软件CSMA-CA回退逻辑，请定义为1。
 *
 */
#define OPENTHREAD_CONFIG_MAC_SOFTWARE_CSMA_BACKOFF_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_MAC_SOFTWARE_TX_SECURITY_ENABLE
 *
 * 如果要启用软件传输安全逻辑，请定义为1。
 *
 */
#define OPENTHREAD_CONFIG_MAC_SOFTWARE_TX_SECURITY_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_MAC_SOFTWARE_TX_TIMING_ENABLE
 *
 * 定义为1以启用软件传输目标时间逻辑。
 *
 */
#define OPENTHREAD_CONFIG_MAC_SOFTWARE_TX_TIMING_ENABLE 1
#endif // OPENTHREAD_RADIO

