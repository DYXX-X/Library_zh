/**
 * @file SNTP客户端选项列表
 */

/*
 * 版权所有（c）2007-2009 Frédéric Bernon，Simon Goldschmidt保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Frédéric Bernon，Simon Goldschmidt
 *
 */
#ifndef LWIP_HDR_APPS_SNTP_OPTS_H
#define LWIP_HDR_APPS_SNTP_OPTS_H

#include "lwip/opt.h"
#include "lwip/prot/iana.h"

/**
 * @defgroup sntp_opts选项
 * @ingroup sntp公司@{
 */

/** SNTP宏以秒为单位更改系统时间定义SNTP_SET_system_time_US（sec，US）以微秒为单位设置时间，而不是在需要额外精度时设置此时间。或者，定义SNTP_SET_SYSTEM_TIME_NTP（sec，frac），以便使用本机NTP时间戳。
 */
#if !defined SNTP_SET_SYSTEM_TIME || defined __DOXYGEN__
#define SNTP_SET_SYSTEM_TIME(sec)   LWIP_UNUSED_ARG(sec)
#endif

/**可设置的最大SNTP服务器数*/
#if !defined SNTP_MAX_SERVERS || defined __DOXYGEN__
#define SNTP_MAX_SERVERS           LWIP_DHCP_MAX_NTP_SERVERS
#endif

/**将此值设置为1，以在收到NTP服务器时实现dhcp调用的回调函数。*/
#if !defined SNTP_GET_SERVERS_FROM_DHCP || defined __DOXYGEN__
#define SNTP_GET_SERVERS_FROM_DHCP LWIP_DHCP_GET_NTP_SRV
#endif

/**将此值设置为1，以在收到NTP服务器时实现dhcpv6调用的回调函数。*/
#if !defined SNTP_GET_SERVERS_FROM_DHCPV6 || defined __DOXYGEN__
#define SNTP_GET_SERVERS_FROM_DHCPV6 LWIP_DHCP6_GET_NTP_SRV
#endif

/** 将此值设置为1以支持DNS名称（或IP地址字符串）以设置sntp服务器如果sntp_server_DNS==1:\#define sntp_server_address“pool.ntp.org”，则可以将一个服务器地址/名称定义为默认值
 */
#if !defined SNTP_SERVER_DNS || defined __DOXYGEN__
#define SNTP_SERVER_DNS            0
#endif

/**
 * SNTP_DEBUG：启用SNTP调试。
 */
#if !defined SNTP_DEBUG || defined __DOXYGEN__
#define SNTP_DEBUG                  LWIP_DBG_OFF
#endif

/**SNTP服务器端口*/
#if !defined SNTP_PORT || defined __DOXYGEN__
#define SNTP_PORT                   LWIP_IANA_PORT_SNTP
#endif

/** 健康检查：将其定义为
 * -0关闭健全性检查（默认值；较小的代码）
 * ->=1以检查响应包的地址和端口，以确保响应来自发送请求的服务器。
 * ->=2以检查返回的原始时间戳与发送到服务器的传输时间戳（以确保对旧请求的响应）。
 * - >= 3 @todo: 如果VN、Stratum或Transmit Timestamp字段中的任何一个为0或Mode字段不是4（单播）或5（广播），则放弃应答。
 * - >= 4 @todo: 检查“根延迟”和“根色散”字段是否均大于或等于0且小于无穷大，其中无穷大当前是一个舒适的数字，例如一秒。此检查可避免使用同步源已过期很长时间的服务器。
 */
#if !defined SNTP_CHECK_RESPONSE || defined __DOXYGEN__
#define SNTP_CHECK_RESPONSE         0
#endif

/** 启用往返延迟补偿。根据RFC，通过计算源、接收、发送和目标时间戳的时钟偏移来补偿往返延迟。
 *
 * 计算要求编译器支持64位整数。此外，必须实现SNTP_SET_SYSTEM_TIME_US或SNTP_SET_SYSTEM_TIME_NTP，以设置具有亚秒精度的系统时钟。同样，SNTP_GET_SYSTEM_TIME或SNTP_GET_SYSTEM_MIME_NTP需要以亚秒精度实现。
 *
 * 虽然不是严格要求，但将此选项与SNTP_CHECK_RESPONSE>=2结合起来，对接收到的时间戳进行健全性检查是有意义的。此外，为了使往返计算工作，本地时钟和NTP服务器时钟之间的差异不得大于约34年。如果超过该限制，则实现将返回到设置时钟而不进行补偿。为了确保本地时钟始终在允许的补偿范围内，即使是首次尝试，也可能需要在非易失性存储器中至少存储当前年份。
 */
#if !defined SNTP_COMP_ROUNDTRIP || defined __DOXYGEN__
#define SNTP_COMP_ROUNDTRIP         0
#endif

/** 根据RFC，这应该是1到5分钟（以毫秒为单位）之间的随机延迟，以防止负载峰值。这可以定义为一个随机生成函数，它必须以毫秒为单位将延迟返回为u32_t。默认情况下禁用。
 */
#if !defined SNTP_STARTUP_DELAY || defined __DOXYGEN__
#ifdef LWIP_RAND
#define SNTP_STARTUP_DELAY          1
#else
#define SNTP_STARTUP_DELAY          0
#endif
#endif

/** 如果希望启动延迟为函数，请将其定义为函数（包括括号），并将SNTP_startup_delay定义为1。
 */
#if !defined SNTP_STARTUP_DELAY_FUNC || defined __DOXYGEN__
#define SNTP_STARTUP_DELAY_FUNC     (LWIP_RAND() % 5000)
#endif

/** SNTP接收超时-以毫秒为单位也用作重试超时-这不应该太低。默认值为15秒。规格不得超过15秒（即15000）
 */
#if !defined SNTP_RECV_TIMEOUT || defined __DOXYGEN__
#define SNTP_RECV_TIMEOUT           15000
#endif

/** SNTP更新延迟-以毫秒为单位默认值为1小时。规格不得超过60秒（即60000）
 */
#if !defined SNTP_UPDATE_DELAY || defined __DOXYGEN__
#define SNTP_UPDATE_DELAY           3600000
#endif

/** SNTP宏用于获取系统时间，与SNTP_CHECK_RESPONSE>=2一起用于发送请求和比较响应。如果SNTP_COMP_ROUNDTRIP！=0。或者，定义SNTP_GET_SYSTEM_TIME_NTP（sec，frac），以便使用本机NTP时间戳。
 */
#if !defined SNTP_GET_SYSTEM_TIME || defined __DOXYGEN__
#define SNTP_GET_SYSTEM_TIME(sec, us)     do { (sec) = 0; (us) = 0; } while(0)
#endif

/** 如果收到的响应无效，则默认重试超时（以毫秒为单位）。每次重试时，此值加倍，直到达到SNTP_retry_TIMEOUT_MAX。
 */
#if !defined SNTP_RETRY_TIMEOUT || defined __DOXYGEN__
#define SNTP_RETRY_TIMEOUT          SNTP_RECV_TIMEOUT
#endif

/**最大重试超时（毫秒）。*/
#if !defined SNTP_RETRY_TIMEOUT_MAX || defined __DOXYGEN__
#define SNTP_RETRY_TIMEOUT_MAX      (SNTP_RETRY_TIMEOUT * 10)
#endif

/** 每次发送重试时，增加重试超时。默认值为启用以符合RFC。
 */
#if !defined SNTP_RETRY_TIMEOUT_EXP || defined __DOXYGEN__
#define SNTP_RETRY_TIMEOUT_EXP      1
#endif

/** 为每台服务器保留一个可达性移位寄存器。默认设置为启用以符合RFC。
 */
#if !defined SNTP_MONITOR_SERVER_REACHABILITY || defined __DOXYGEN__
#define SNTP_MONITOR_SERVER_REACHABILITY 1
#endif

/**
 * @}
 */

#endif /* LWIP_HDR_APPS_SNTP_OPTS_H */

