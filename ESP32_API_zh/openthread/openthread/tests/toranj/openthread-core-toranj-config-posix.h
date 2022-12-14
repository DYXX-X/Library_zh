/*
 *  版权所有（c）2020，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef OPENTHREAD_CORE_TORANJ_CONFIG_POSIX_H_
#define OPENTHREAD_CORE_TORANJ_CONFIG_POSIX_H_

/**
 * 此头文件定义了POSIX平台上toranj的OpenThread核心配置选项。
 *
 */

// 包括所有平台的通用配置。
#include "openthread-core-toranj-config.h"

/**
 * @def OPENTHREAD_CONFIG_PLATFORM_INFO
 *
 * 要插入OpenThread版本字符串的平台特定字符串。
 *
 */
#define OPENTHREAD_CONFIG_PLATFORM_INFO "POSIX-toranj"

/**
 * @def OPENTHREAD_CONFIG_LOG_OUTPUT
 *
 * 选择日志输出是否以及输出到何处。
 *
 */
#define OPENTHREAD_CONFIG_LOG_OUTPUT OPENTHREAD_CONFIG_LOG_OUTPUT_PLATFORM_DEFINED

/**
 * @def OPENTHREAD_CONFIG_BORDER_ROUTER_ENABLE
 *
 * 定义为1以启用边界路由器支持。
 *
 */
#define OPENTHREAD_CONFIG_BORDER_ROUTER_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_POSIX_APP_TREL_INTERFACE_NAME
 *
 * 定义TREL UDP6平台使用的默认接口名称。空字符串禁用TREL平台。
 *
 */
#define OPENTHREAD_CONFIG_POSIX_APP_TREL_INTERFACE_NAME "trel"

/**
 * @def OPENTHREAD_CONFIG_POSIX_TREL_USE_NETLINK_SOCKET
 *
 * 定义TREL UDP6平台是否使用netlink套接字在TREL netif或“ioctl（）”命令上添加/删除地址。
 *
 * 使用netlink时，在netif上添加新地址时，将禁用重复地址检测（DAD）。
 *
 */
#ifdef __linux__
#define OPENTHREAD_CONFIG_POSIX_TREL_USE_NETLINK_SOCKET 1
#else
#define OPENTHREAD_CONFIG_POSIX_TREL_USE_NETLINK_SOCKET 0
#endif

/**
 * @def OPENTHREAD_POSIX_CONFIG_RCP_PTY_ENABLE
 *
 * 定义为1以在POSIX应用程序中启用PTY设备支持。
 *
 */
#define OPENTHREAD_POSIX_CONFIG_RCP_PTY_ENABLE 1

#define OPENTHREAD_POSIX_CONFIG_RCP_BUS OT_POSIX_RCP_BUS_UART

#endif /* OPENTHREAD_CORE_TORANJ_CONFIG_POSIX_H_ */

