/**
 * @file SNMP服务器选项列表
 */

/*
 * 版权所有（c）2015 Dirk Ziegelmeier保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Dirk Ziegelmeier
 *
 */
#ifndef LWIP_HDR_SNMP_OPTS_H
#define LWIP_HDR_SNMP_OPTS_H

#include "lwip/opt.h"

/**
 * @defgroup snmp_opts选项
 * @ingroup snmp协议@{
 */

/**
 * LWIP_SNMP==1：这将启用LWIP SNMP代理。UDP必须可用于SNMP传输。如果要使用自己的SNMP代理，请将其保持禁用状态。要集成外部代理的MIB2，需要启用LWIP_MIB2_CALLBACKS和MIB2_STATS。这将为您提供使MIB2工作所需的回调和统计计数器。
 */
#if !defined LWIP_SNMP || defined __DOXYGEN__
#define LWIP_SNMP                       0
#endif

/**
 * SNMP_USE_NETCONN：使用NETCONN API而不是原始API。使SNMP代理在工作线程中运行，因此可以在MIB调用中执行阻塞操作。
 */
#if !defined SNMP_USE_NETCONN || defined __DOXYGEN__
#define SNMP_USE_NETCONN           0
#endif

/**
 * SNMP_USE_RAW：使用原始API。SNMP代理不在工作线程中运行，因此不应在MIB调用中执行阻塞操作。
 */
#if !defined SNMP_USE_RAW || defined __DOXYGEN__
#define SNMP_USE_RAW               1
#endif

#if SNMP_USE_NETCONN && SNMP_USE_RAW
#error SNMP stack can use only one of the APIs {raw, netconn}
#endif

#if LWIP_SNMP && !SNMP_USE_NETCONN && !SNMP_USE_RAW
#error SNMP stack needs a receive API and UDP {raw, netconn}
#endif

#if SNMP_USE_NETCONN
/**
 * SNMP_STACK_SIZE:SNMP netconn工作线程的堆栈大小
 */
#if !defined SNMP_STACK_SIZE || defined __DOXYGEN__
#define SNMP_STACK_SIZE            DEFAULT_THREAD_STACKSIZE
#endif

/**
 * SNMP_THREAD_PRIO：SNMP网络连接工作线程优先级
 */
#if !defined SNMP_THREAD_PRIO || defined __DOXYGEN__
#define SNMP_THREAD_PRIO           DEFAULT_THREAD_PRIO
#endif
#endif /* SNMP_USE_NETCONN */

/**
 * SNMP_TRAP_DESTINATIONS：陷阱目标数。至少需要一个陷阱目标
 */
#if !defined SNMP_TRAP_DESTINATIONS || defined __DOXYGEN__
#define SNMP_TRAP_DESTINATIONS          1
#endif

/**
 * 仅允许“安全”的SNMP写入操作（例如，禁用netifs不是安全操作，当SNMP_safe_REQUESTS=1时禁用）。默认情况下禁用不安全请求！
 */
#if !defined SNMP_SAFE_REQUESTS || defined __DOXYGEN__
#define SNMP_SAFE_REQUESTS              1
#endif

/**
 * 所用字符串的最大长度。
 */
#if !defined SNMP_MAX_OCTET_STRING_LEN || defined __DOXYGEN__
#define SNMP_MAX_OCTET_STRING_LEN       127
#endif

/**
 * 对象标识符内的子ID的最大数量。间接地，这也限制了SNMP树的最大深度。
 */
#if !defined SNMP_MAX_OBJ_ID_LEN || defined __DOXYGEN__
#define SNMP_MAX_OBJ_ID_LEN             50
#endif

#if !defined SNMP_MAX_VALUE_SIZE || defined __DOXYGEN__
/**
 * 值的最小大小。
 */
#define SNMP_MIN_VALUE_SIZE             (2 * sizeof(u32_t*)) /* 存储基本类型所需的大小（counter64为8字节）*/
/**
 * 值的最大大小。
 */
#define SNMP_MAX_VALUE_SIZE             LWIP_MAX(LWIP_MAX((SNMP_MAX_OCTET_STRING_LEN), sizeof(u32_t)*(SNMP_MAX_OBJ_ID_LEN)), SNMP_MIN_VALUE_SIZE)
#endif

/**
 * snmp读取访问社区。也用于写访问和陷阱，除非分别启用了SNMP_COMMUNITY_write或SNMP_COMMAUNITY_TRAP。
 */
#if !defined SNMP_COMMUNITY || defined __DOXYGEN__
#define SNMP_COMMUNITY                  "public"
#endif

/**
 * snmp写访问社区。将此社区设置为“”以禁止任何写入访问。
 */
#if !defined SNMP_COMMUNITY_WRITE || defined __DOXYGEN__
#define SNMP_COMMUNITY_WRITE            "private"
#endif

/**
 * 用于发送陷阱的snmp社区。
 */
#if !defined SNMP_COMMUNITY_TRAP || defined __DOXYGEN__
#define SNMP_COMMUNITY_TRAP             "public"
#endif

/**
 * 团体字符串的最大长度。如果社区名称应在运行时通过snmp_set_community（）调用进行调整，请在此处输入可能的最大长度（+1表示终止空字符）。
 */
#if !defined SNMP_MAX_COMMUNITY_STR_LEN || defined __DOXYGEN__
#define SNMP_MAX_COMMUNITY_STR_LEN LWIP_MAX(LWIP_MAX(sizeof(SNMP_COMMUNITY), sizeof(SNMP_COMMUNITY_WRITE)), sizeof(SNMP_COMMUNITY_TRAP))
#endif

/**
 * 标识设备的OID。这可能是企业OID本身或树中位于其下方的任何OID。
 */
#if !defined SNMP_DEVICE_ENTERPRISE_OID || defined __DOXYGEN__
#define SNMP_LWIP_ENTERPRISE_OID 26381
/**
 * IANA为lwIP分配的企业ID为26381
 * @see http://www.iana.org/assignments/enterprise-numbers
 *
 * @note 此企业ID分配给lwIP项目，此ID下的所有对象标识符都由lwIP维护者分配！
 * @note 不要更改此定义，请使用snmp_set_device_enterprise_oid（）
 *
 * 如果您需要创建自己的私有MIB，则需要向IANA申请自己的企业ID：http://www.iana.org/numbers.html
 */
#define SNMP_DEVICE_ENTERPRISE_OID {1, 3, 6, 1, 4, 1, SNMP_LWIP_ENTERPRISE_OID}
/**
 * SNMP_DEVICE_ENTERPRICE_OID的长度
 */
#define SNMP_DEVICE_ENTERPRISE_OID_LEN 7
#endif

/**
 * SNMP_DEBUG：启用SNMP消息的调试。
 */
#if !defined SNMP_DEBUG || defined __DOXYGEN__
#define SNMP_DEBUG                      LWIP_DBG_OFF
#endif

/**
 * SNMP_MIB_DEBUG：启用SNMP MIB的调试。
 */
#if !defined SNMP_MIB_DEBUG || defined __DOXYGEN__
#define SNMP_MIB_DEBUG                  LWIP_DBG_OFF
#endif

/**
 * 指示是否使用LWIP SNMP堆栈的MIB2实现。
 */
#if !defined SNMP_LWIP_MIB2 || defined __DOXYGEN__
#define SNMP_LWIP_MIB2                      LWIP_SNMP
#endif

/**
 * MIB2的sysDesc字段的值返回。
 */
#if !defined SNMP_LWIP_MIB2_SYSDESC || defined __DOXYGEN__
#define SNMP_LWIP_MIB2_SYSDESC              "lwIP"
#endif

/**
 * MIB2的sysName字段的值返回。要使sysName字段可设置，请调用snmp_MIB2_set_sysName（）以提供必要的缓冲区。
 */
#if !defined SNMP_LWIP_MIB2_SYSNAME || defined __DOXYGEN__
#define SNMP_LWIP_MIB2_SYSNAME              "FQDN-unk"
#endif

/**
 * MIB2的sysContact字段的值返回。要使sysContact字段可设置，请调用snmp_MIB2_set_sysContact（）以提供必要的缓冲区。
 */
#if !defined SNMP_LWIP_MIB2_SYSCONTACT || defined __DOXYGEN__
#define SNMP_LWIP_MIB2_SYSCONTACT           ""
#endif

/**
 * MIB2的sysLocation字段的值返回。要使sysLocation字段可设置，请调用snmp_MIB2_set_sysLocation（）以提供必要的缓冲区。
 */
#if !defined SNMP_LWIP_MIB2_SYSLOCATION || defined __DOXYGEN__
#define SNMP_LWIP_MIB2_SYSLOCATION          ""
#endif

/**
 * 此值用于限制GetBulk请求中处理的重复次数（值==0表示没有限制）。这可能有助于限制单个请求的负载。根据SNMP RFC 1905，如果系统负载过高，则允许不返回GetBulk请求中的所有请求变量。因此，结果是客户端将执行更多的请求来收集所有数据。对于堆栈，这在SNMP处理在TCP/IP线程中完成的情况下可能很有用。在这种情况下，多次重复的请求可能会阻塞线程更长的时间。在此处设置限制将使堆栈更具响应性。
 */
#if !defined SNMP_LWIP_GETBULK_MAX_REPETITIONS || defined __DOXYGEN__
#define SNMP_LWIP_GETBULK_MAX_REPETITIONS 0
#endif

/**
 * @}
 */

/*
   ------------------------------------
   ----------SNMPv3选项----------
   ------------------------------------
*/

/**
 * LWIP_SNMP_V3==1：这将启用实验SNMPv3支持。还必须启用LWIP_SNMP。这正在开发中，不应在产品中启用。
 */
#ifndef LWIP_SNMP_V3
#define LWIP_SNMP_V3               0
#endif

#ifndef LWIP_SNMP_V3_MBEDTLS
#define LWIP_SNMP_V3_MBEDTLS       LWIP_SNMP_V3
#endif

#ifndef LWIP_SNMP_V3_CRYPTO
#define LWIP_SNMP_V3_CRYPTO        LWIP_SNMP_V3_MBEDTLS
#endif

#ifndef LWIP_SNMP_CONFIGURE_VERSIONS
#define LWIP_SNMP_CONFIGURE_VERSIONS 0
#endif

#endif /* LWIP_HDR_SNMP_OPTS_H */

