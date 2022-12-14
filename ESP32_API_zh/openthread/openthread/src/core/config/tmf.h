/*
 *  版权所有（c）2019，The OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file 此文件包括线程管理框架服务的编译时配置。
 *
 */

#ifndef CONFIG_TMF_H_
#define CONFIG_TMF_H_

/**
 * @def OPENTHREAD_CONFIG_TMF_ADDRESS_CACHE_ENTRIES
 *
 * EID到RLOC缓存项的数量。
 *
 */
#ifndef OPENTHREAD_CONFIG_TMF_ADDRESS_CACHE_ENTRIES
#define OPENTHREAD_CONFIG_TMF_ADDRESS_CACHE_ENTRIES 10
#endif

/**
 * @def OPENTHREAD_CONFIG_TMF_ADDRESS_CACHE_MAX_SNOOP_ENTRIES
 *
 * 可用于“窥探优化”的EID到RLOC缓存条目的最大数量，其中通过检查接收到的消息来创建条目。
 *
 */
#ifndef OPENTHREAD_CONFIG_TMF_ADDRESS_CACHE_MAX_SNOOP_ENTRIES
#define OPENTHREAD_CONFIG_TMF_ADDRESS_CACHE_MAX_SNOOP_ENTRIES 2
#endif

/**
 * @def OPENTHREAD_CONFIG_TMF_SNOOP_CACHE_ENTRY_TIMEOUT
 *
 * 阻止通过窥探优化（即，检查接收到的消息）创建的地址缓存项被逐出的超时值（以秒为单位）。超时过期后，可以再次回收条目。此超时允许接收到的消息有更长的响应延迟，从而有更多的机会使用窥探条目（避免在响应消息发送到先前接收到消息的同一目的地时发送地址查询）。
 *
 */
#ifndef OPENTHREAD_CONFIG_TMF_SNOOP_CACHE_ENTRY_TIMEOUT
#define OPENTHREAD_CONFIG_TMF_SNOOP_CACHE_ENTRY_TIMEOUT 3
#endif

/**
 * @def OPENTHREAD_CONFIG_TMF_ADDRESS_QUERY_TIMEOUT
 *
 * 发送地址查询后等待地址通知响应的超时值（秒）。
 *
 * 默认值：3秒
 *
 */
#ifndef OPENTHREAD_CONFIG_TMF_ADDRESS_QUERY_TIMEOUT
#define OPENTHREAD_CONFIG_TMF_ADDRESS_QUERY_TIMEOUT 3
#endif

/**
 * @def OPENTHREAD_CONFIG_TMF_ADDRESS_QUERY_INITIAL_RETRY_DELAY
 *
 * 地址查询的初始重试延迟（秒）。
 *
 * 默认值：15秒
 *
 */
#ifndef OPENTHREAD_CONFIG_TMF_ADDRESS_QUERY_INITIAL_RETRY_DELAY
#define OPENTHREAD_CONFIG_TMF_ADDRESS_QUERY_INITIAL_RETRY_DELAY 15
#endif

/**
 * @def OPENTHREAD_CONFIG_TMF_ADDRESS_QUERY_MAX_RETRY_DELAY
 *
 * 地址查询的最大重试延迟（秒）。
 *
 * 默认值：120秒
 *
 */
#ifndef OPENTHREAD_CONFIG_TMF_ADDRESS_QUERY_MAX_RETRY_DELAY
#define OPENTHREAD_CONFIG_TMF_ADDRESS_QUERY_MAX_RETRY_DELAY 120
#endif

/**
 * @def OPENTHREAD_CONFIG_TMF_PENDING_DATASET_MINIMUM_DELAY
 *
 * 挂起操作数据集的最小延迟计时器值（毫秒）。
 *
 * 线程规范将此值定义为30000 ms。应仅在测试时更改指定值。
 *
 */
#ifndef OPENTHREAD_CONFIG_TMF_PENDING_DATASET_MINIMUM_DELAY
#define OPENTHREAD_CONFIG_TMF_PENDING_DATASET_MINIMUM_DELAY 30000
#endif

/**
 * @def OPENTHREAD_CONFIG_TMF_PENDING_DATASET_DEFAULT_DELAY
 *
 * 挂起操作数据集的默认延迟计时器值（毫秒）。
 *
 * 线程规范将此值定义为300000毫秒。应仅为测试更改指定值。
 *
 */
#ifndef OPENTHREAD_CONFIG_TMF_PENDING_DATASET_DEFAULT_DELAY
#define OPENTHREAD_CONFIG_TMF_PENDING_DATASET_DEFAULT_DELAY 300000
#endif

/**
 * @def OPENTHREAD_CONFIG_TMF_ENERGY_SCAN_MAX_RESULTS
 *
 * 能量列表条目的最大数量。
 *
 */
#ifndef OPENTHREAD_CONFIG_TMF_ENERGY_SCAN_MAX_RESULTS
#define OPENTHREAD_CONFIG_TMF_ENERGY_SCAN_MAX_RESULTS 64
#endif

/**
 * @def OPENTHREAD_CONFIG_TMF_NETDATA_SERVICE_ENABLE
 *
 * 定义为1以支持将服务条目注入线程网络数据。
 *
 */
#ifndef OPENTHREAD_CONFIG_TMF_NETDATA_SERVICE_ENABLE
#define OPENTHREAD_CONFIG_TMF_NETDATA_SERVICE_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_TMF_NETDATA_SERVICE_MAX_ALOCS
 *
 * 此设备支持的最大服务ALOC注册数。
 *
 */
#ifndef OPENTHREAD_CONFIG_TMF_NETDATA_SERVICE_MAX_ALOCS
#define OPENTHREAD_CONFIG_TMF_NETDATA_SERVICE_MAX_ALOCS 1
#endif

/**
 * @def OPENTHREAD_CONFIG_TMF_NETWORK_DIAG_MTD_ENABLE
 *
 * 定义为1以启用MTD上的TMF网络诊断。
 *
 */
#ifndef OPENTHREAD_CONFIG_TMF_NETWORK_DIAG_MTD_ENABLE
#define OPENTHREAD_CONFIG_TMF_NETWORK_DIAG_MTD_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_TMF_ANYCAST_LOCATOR_ENABLE
 *
 * 定义为1以启用TMF选播定位器功能。
 *
 * 此功能允许设备通过发送“TMF_anycast_LOCATE”请求来确定选播地址（如果有）的最近目的地的网格本地EID和RLOC16。
 *
 */
#ifndef OPENTHREAD_CONFIG_TMF_ANYCAST_LOCATOR_ENABLE
#define OPENTHREAD_CONFIG_TMF_ANYCAST_LOCATOR_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_TMF_ANYCAST_LOCATOR_SEND_RESPONSE
 *
 * 定义为1以要求设备侦听并响应“TMF_ANYCAST_LOCATE”请求。
 *
 * 此配置仅在启用“OPENTHREAD_config_TMF_ANYCAST_LOCATOR_ENABLE”时使用。默认情况下已启用。
 *
 */
#ifndef OPENTHREAD_CONFIG_TMF_ANYCAST_LOCATOR_SEND_RESPONSE
#define OPENTHREAD_CONFIG_TMF_ANYCAST_LOCATOR_SEND_RESPONSE 1
#endif

/**
 * @def OPENTHREAD_CONFIG_TMF_PROXY_DUA_ENABLE
 *
 * 为线程1.2 FTD设备定义为1，以注册其MTD子级的DUA，即使它本身不启用DUA功能。
 *
 */
#ifndef OPENTHREAD_CONFIG_TMF_PROXY_DUA_ENABLE
#define OPENTHREAD_CONFIG_TMF_PROXY_DUA_ENABLE (OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2)
#endif

#if OPENTHREAD_CONFIG_TMF_PROXY_DUA_ENABLE && OPENTHREAD_CONFIG_THREAD_VERSION < OT_THREAD_VERSION_1_2
#error "Thread 1.2 or higher version is required for OPENTHREAD_CONFIG_TMF_PROXY_DUA_ENABLE"
#endif

/**
 * 此设置配置线程1.2中的多播侦听器注册父代理。
 *
 */
#ifndef OPENTHREAD_CONFIG_TMF_PROXY_MLR_ENABLE
#define OPENTHREAD_CONFIG_TMF_PROXY_MLR_ENABLE (OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2)
#endif

#if OPENTHREAD_CONFIG_TMF_PROXY_MLR_ENABLE && OPENTHREAD_CONFIG_THREAD_VERSION < OT_THREAD_VERSION_1_2
#error "Thread 1.2 or higher version is required for OPENTHREAD_CONFIG_TMF_PROXY_MLR_ENABLE"
#endif

#endif // CONFIG_TMF_H_

