/**
 *
 * @file tftp_opts.h文件
 *
 * @author   洛根·冈索普<logang@deltatee.com>
 *
 * @brief    普通文件传输协议（RFC 1350）实现选项
 *
 * 版权所有（c）Deltatee Enterprises Ltd.2013保留所有权利。
 *
 */

/* 
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 作者：Logan Gunthrope<logang@deltatee.com>
 *
 */

#ifndef LWIP_HDR_APPS_TFTP_OPTS_H
#define LWIP_HDR_APPS_TFTP_OPTS_H

#include "lwip/opt.h"
#include "lwip/prot/iana.h"

/**
 * @defgroup tftp_opts选项
 * @ingroup tftp公司@{
 */

/**
 * 启用TFTP调试消息
 */
#if !defined TFTP_DEBUG || defined __DOXYGEN__
#define TFTP_DEBUG            LWIP_DBG_OFF
#endif

/**
 * TFTP服务器端口
 */
#if !defined TFTP_PORT || defined __DOXYGEN__
#define TFTP_PORT             LWIP_IANA_PORT_TFTP
#endif

/**
 * TFTP超时
 */
#if !defined TFTP_TIMEOUT_MSECS || defined __DOXYGEN__
#define TFTP_TIMEOUT_MSECS    10000
#endif

/**
 * 从服务器读取文件时的最大重试次数
 */
#if !defined TFTP_MAX_RETRIES || defined __DOXYGEN__
#define TFTP_MAX_RETRIES      5
#endif

/**
 * TFTP计时器循环间隔
 */
#if !defined TFTP_TIMER_MSECS || defined __DOXYGEN__
#define TFTP_TIMER_MSECS      (TFTP_TIMEOUT_MSECS / 10)
#endif

/**
 * TFTP文件名的最大长度
 */
#if !defined TFTP_MAX_FILENAME_LEN || defined __DOXYGEN__
#define TFTP_MAX_FILENAME_LEN 20
#endif

/**
 * TFTP模式的最大长度
 */
#if !defined TFTP_MAX_MODE_LEN || defined __DOXYGEN__
#define TFTP_MAX_MODE_LEN     7
#endif

/**
 * @}
 */

#endif /* LWIP_HDR_APPS_TFTP_OPTS_H */

