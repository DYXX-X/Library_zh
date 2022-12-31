/*
 *  版权所有（c）2019，The OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file 此文件包括IP6服务的编译时配置。
 *
 */

#ifndef CONFIG_IP6_H_
#define CONFIG_IP6_H_

/**
 * @def OPENTHREAD_CONFIG_IP6_MAX_EXT_UCAST_ADDRS
 *
 * 允许外部添加的受支持IPv6地址的最大数量。
 *
 */
#ifndef OPENTHREAD_CONFIG_IP6_MAX_EXT_UCAST_ADDRS
#define OPENTHREAD_CONFIG_IP6_MAX_EXT_UCAST_ADDRS 4
#endif

/**
 * @def OPENTHREAD_CONFIG_IP6_MAX_EXT_MCAST_ADDRS
 *
 * 允许外部添加的受支持IPv6多播地址的最大数量。
 *
 */
#ifndef OPENTHREAD_CONFIG_IP6_MAX_EXT_MCAST_ADDRS
#define OPENTHREAD_CONFIG_IP6_MAX_EXT_MCAST_ADDRS 2
#endif

/**
 * @def OPENTHREAD_CONFIG_IP6_HOP_LIMIT_DEFAULT
 *
 * 此设置配置IPv6的默认跃点限制。
 *
 */
#ifndef OPENTHREAD_CONFIG_IP6_HOP_LIMIT_DEFAULT
#define OPENTHREAD_CONFIG_IP6_HOP_LIMIT_DEFAULT 64
#endif

/**
 * @def OPENTHREAD_CONFIG_IP6_MAX_DATAGRAM_LENGTH
 *
 * 此设置配置IPv6的最大数据报长度。
 *
 */
#ifndef OPENTHREAD_CONFIG_IP6_MAX_DATAGRAM_LENGTH
#define OPENTHREAD_CONFIG_IP6_MAX_DATAGRAM_LENGTH 1280
#endif

/**
 * @def OPENTHREAD_CONFIG_ENABLE_IP6_FRAGMENTATION
 *
 * 定义为1以启用IPv6碎片化支持。
 *
 */
#ifndef OPENTHREAD_CONFIG_IP6_FRAGMENTATION_ENABLE
#define OPENTHREAD_CONFIG_IP6_FRAGMENTATION_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_IP6_MAX_ASSEMBLED_DATAGRAM
 *
 * 此设置配置未分段IPv6数据包的最大数据报长度。
 *
 */
#ifndef OPENTHREAD_CONFIG_IP6_MAX_ASSEMBLED_DATAGRAM
#define OPENTHREAD_CONFIG_IP6_MAX_ASSEMBLED_DATAGRAM 2000
#endif

/**
 * @def OPENTHREAD_CONFIG_IP6_REASSEMBLY_TIMEOUT
 *
 * 此设置以秒为单位配置IPv6的重新组装超时。
 *
 * RFC 2460\>60秒
 *
 */
#ifndef OPENTHREAD_CONFIG_IP6_REASSEMBLY_TIMEOUT
#define OPENTHREAD_CONFIG_IP6_REASSEMBLY_TIMEOUT 60
#endif

/**
 * @def OPENTHREAD_CONFIG_IP6_SLAAC_ENABLE
 *
 * 定义为1，以支持OpenThread添加自动配置的SLAC地址。
 *
 */
#ifndef OPENTHREAD_CONFIG_IP6_SLAAC_ENABLE
#define OPENTHREAD_CONFIG_IP6_SLAAC_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_IP6_SLAAC_NUM_ADDRESSES
 *
 * 自动配置的SLAAC地址的数量。仅当启用OPENTHREAD_CONFIG_IP6_SLAAC_ENABLE时适用。
 *
 */
#ifndef OPENTHREAD_CONFIG_IP6_SLAAC_NUM_ADDRESSES
#define OPENTHREAD_CONFIG_IP6_SLAAC_NUM_ADDRESSES 4
#endif

/**
 * @def OPENTHREAD_CONFIG_MPL_SEED_SET_ENTRIES
 *
 * 用于重复检测的MPL种子集条目数。
 *
 */
#ifndef OPENTHREAD_CONFIG_MPL_SEED_SET_ENTRIES
#define OPENTHREAD_CONFIG_MPL_SEED_SET_ENTRIES 32
#endif

/**
 * @def OPENTHREAD_CONFIG_MPL_SEED_SET_ENTRY_LIFETIME
 *
 * MPL种子集条目生存期（秒）。
 *
 */
#ifndef OPENTHREAD_CONFIG_MPL_SEED_SET_ENTRY_LIFETIME
#define OPENTHREAD_CONFIG_MPL_SEED_SET_ENTRY_LIFETIME 5
#endif

/**
 * @def OPENTHREAD_CONFIG_MPL_DYNAMIC_INTERVAL_ENABLE
 *
 * 定义为1以启用动态MPL间隔功能。
 *
 * 如果启用此功能，MPL转发间隔将根据网络规模动态调整，这有助于减少多播延迟。
 *
 */
#ifndef OPENTHREAD_CONFIG_MPL_DYNAMIC_INTERVAL_ENABLE
#define OPENTHREAD_CONFIG_MPL_DYNAMIC_INTERVAL_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_UNSECURE_TRAFFIC_MANAGED_BY_STACK_ENABLE
 *
 * 定义为1以启用动态不安全端口管理
 *
 * 如果启用此功能，OpenThread将自动禁用使用不安全源端口发送的数据包的链接级安全性。一旦我们收到发送到不安全端口的安全数据包，该端口将从不安全端口列表中删除。
 *
 * 仅当您了解其行为时才启用。
 *
 */
#ifndef OPENTHREAD_CONFIG_UNSECURE_TRAFFIC_MANAGED_BY_STACK_ENABLE
#define OPENTHREAD_CONFIG_UNSECURE_TRAFFIC_MANAGED_BY_STACK_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_TCP_ENABLE
 *
 * 定义为1以启用TCP。
 *
 */
#ifndef OPENTHREAD_CONFIG_TCP_ENABLE
#define OPENTHREAD_CONFIG_TCP_ENABLE 1
#endif

#endif // CONFIG_IP6_H_
