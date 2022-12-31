/**
 * @file 应用程序分层TCP/TLS连接API（从TCPIP线程使用）
 *
 * 此文件包含TLS层的mbedtls端口的选项。
 */

/*
 * 版权所有（c）2017 Simon Goldschmidt保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Simon Goldschmidt<goldsimon@gmx.de>
 *
 */
#ifndef LWIP_HDR_ALTCP_TLS_OPTS_H
#define LWIP_HDR_ALTCP_TLS_OPTS_H

#include "lwip/opt.h"

#if LWIP_ALTCP /* 如果未配置为在lwipots中使用，请不要构建。小时*/

/** LWIP_ALTCP_TLS_MBEDTLS==1：使用MBEDTLS对ALTCP API的TLS支持MBEDTLS include目录必须可通过include搜索路径访问
 */
#ifndef LWIP_ALTCP_TLS_MBEDTLS
#define LWIP_ALTCP_TLS_MBEDTLS                        0
#endif

/**配置此文件的调试级别*/
#ifndef ALTCP_MBEDTLS_DEBUG
#define ALTCP_MBEDTLS_DEBUG                           LWIP_DBG_OFF
#endif

/**配置mbedTLS库的lwIP调试级别*/
#ifndef ALTCP_MBEDTLS_LIB_DEBUG
#define ALTCP_MBEDTLS_LIB_DEBUG                       LWIP_DBG_OFF
#endif

/**配置mbedTLS库的最低内部调试级别*/
#ifndef ALTCP_MBEDTLS_LIB_DEBUG_LEVEL_MIN
#define ALTCP_MBEDTLS_LIB_DEBUG_LEVEL_MIN             0
#endif

/** 启用基本会话缓存注意：使用会话缓存可以通过重用密钥降低安全性！
 */
#ifndef ALTCP_MBEDTLS_USE_SESSION_CACHE
#define ALTCP_MBEDTLS_USE_SESSION_CACHE               0
#endif

/**基本会话缓存的最大缓存大小*/
#ifndef ALTCP_MBEDTLS_SESSION_CACHE_SIZE
#define ALTCP_MBEDTLS_SESSION_CACHE_SIZE              30
#endif

/**设置基本会话缓存的会话超时（秒）*/
#ifndef ALTCP_MBEDTLS_SESSION_CACHE_TIMEOUT_SECONDS
#define ALTCP_MBEDTLS_SESSION_CACHE_TIMEOUT_SECONDS   (60 * 60)
#endif

/** 使用会话票证加快连接设置（需要在MBEDTLS配置中启用MBEDTLS_SL_session_tickets）。注意：使用会话票证可以通过重用密钥降低安全性！
 */
#ifndef ALTCP_MBEDTLS_USE_SESSION_TICKETS
#define ALTCP_MBEDTLS_USE_SESSION_TICKETS             0
#endif

/**会话票证密码*/
#ifndef ALTCP_MBEDTLS_SESSION_TICKET_CIPHER
#define ALTCP_MBEDTLS_SESSION_TICKET_CIPHER           MBEDTLS_CIPHER_AES_256_GCM
#endif

/**会话票证的最大超时*/
#ifndef ALTCP_MBEDTLS_SESSION_TICKET_TIMEOUT_SECONDS
#define ALTCP_MBEDTLS_SESSION_TICKET_TIMEOUT_SECONDS  (60 * 60 * 24)
#endif

#endif /* LWIP_ALTCP */

#endif /* LWIP_HDR_ALTCP_TLS_OPTS_H */

