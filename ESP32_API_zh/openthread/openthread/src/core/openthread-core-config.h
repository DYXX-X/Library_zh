/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file 此文件包含OpenThread的编译时配置常量。
 */

#ifndef OPENTHREAD_CORE_CONFIG_H_
#define OPENTHREAD_CORE_CONFIG_H_

#include <openthread/config.h>

#define OT_THREAD_VERSION_INVALID 0
#define OT_THREAD_VERSION_1_1 2
#define OT_THREAD_VERSION_1_2 3

#define OPENTHREAD_CORE_CONFIG_H_IN

#ifdef OPENTHREAD_PROJECT_CORE_CONFIG_FILE
#include OPENTHREAD_PROJECT_CORE_CONFIG_FILE
#elif defined(OPENTHREAD_CONFIG_CORE_USER_CONFIG_HEADER_ENABLE)
// 用户应在以下情况下提供此配置头文件：
// OPENTHREAD_COONFIG_CORE_USER_CONFIG_HEADER_ENABLE定义为1。
#include "openthread-core-user-config.h"
#endif

#ifndef OPENTHREAD_CONFIG_THREAD_VERSION
#define OPENTHREAD_CONFIG_THREAD_VERSION OT_THREAD_VERSION_1_2
#endif

#include "config/openthread-core-default-config.h"

#include "config/announce_sender.h"
#include "config/backbone_router.h"
#include "config/border_router.h"
#include "config/channel_manager.h"
#include "config/channel_monitor.h"
#include "config/child_supervision.h"
#include "config/coap.h"
#include "config/commissioner.h"
#include "config/crypto.h"
#include "config/dataset_updater.h"
#include "config/dhcp6_client.h"
#include "config/dhcp6_server.h"
#include "config/diag.h"
#include "config/dns_client.h"
#include "config/dnssd_server.h"
#include "config/dtls.h"
#include "config/history_tracker.h"
#include "config/ip6.h"
#include "config/joiner.h"
#include "config/link_quality.h"
#include "config/link_raw.h"
#include "config/logging.h"
#include "config/mac.h"
#include "config/mle.h"
#include "config/netdata_publisher.h"
#include "config/parent_search.h"
#include "config/ping_sender.h"
#include "config/platform.h"
#include "config/radio_link.h"
#include "config/sntp_client.h"
#include "config/srp_client.h"
#include "config/srp_server.h"
#include "config/time_sync.h"
#include "config/tmf.h"

#undef OPENTHREAD_CORE_CONFIG_H_IN

#include "config/openthread-core-config-check.h"

#ifdef OPENTHREAD_CORE_CONFIG_PLATFORM_CHECK_FILE
#include OPENTHREAD_CORE_CONFIG_PLATFORM_CHECK_FILE
#endif

#endif // OPENTHREAD_CORE_CONFIG_H_

