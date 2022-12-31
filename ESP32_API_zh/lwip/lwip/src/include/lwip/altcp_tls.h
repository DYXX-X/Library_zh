/**
 * @file 应用程序分层TCP/TLS连接API（从TCPIP线程使用）
 *
 * @defgroup altcp_tls tls层
 * @ingroup altcp此文件包含TLS层的函数原型。应用程序/树中提供了到ARM mbedtls的端口（LWIP_ALTCP_TLS_mbedtls选项）。
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
#ifndef LWIP_HDR_ALTCP_TLS_H
#define LWIP_HDR_ALTCP_TLS_H

#include "lwip/opt.h"

#if LWIP_ALTCP /* 如果未配置为在lwipopts.h中使用，则不要构建*/

#if LWIP_ALTCP_TLS

#include "lwip/altcp.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup altcp_tls altcp_tls配置句柄，内容取决于端口（例如mbedtls）
 */
struct altcp_tls_config;

/** @ingroup altcp_tls创建为多个证书准备的altcp_tls服务器配置句柄
 */
struct altcp_tls_config *altcp_tls_create_config_server(uint8_t cert_count);

/** @ingroup altcp_tls向altcp_tls服务器配置句柄添加证书
 */
err_t altcp_tls_config_server_add_privkey_cert(struct altcp_tls_config *config,
      const u8_t *privkey, size_t privkey_len,
      const u8_t *privkey_pass, size_t privkey_pass_len,
      const u8_t *cert, size_t cert_len);

/** @ingroup altcp_tls使用一个证书创建altcp_tls服务器配置句柄
 * (short version of calling @ref altcp_tls_create_config_server和
 * @ref altcp_tls_config_server_add_privkey_cert）
 */
struct altcp_tls_config *altcp_tls_create_config_server_privkey_cert(const u8_t *privkey, size_t privkey_len,
                            const u8_t *privkey_pass, size_t privkey_pass_len,
                            const u8_t *cert, size_t cert_len);

/** @ingroup altcp_tls创建altcp_tls客户端配置句柄
 */
struct altcp_tls_config *altcp_tls_create_config_client(const u8_t *cert, size_t cert_len);

/** @ingroup altcp_tls使用双向服务器/客户端身份验证创建altcp_tls客户端配置句柄
 */
struct altcp_tls_config *altcp_tls_create_config_client_2wayauth(const u8_t *ca, size_t ca_len, const u8_t *privkey, size_t privkey_len,
                            const u8_t *privkey_pass, size_t privkey_pass_len,
                            const u8_t *cert, size_t cert_len);

/** @ingroup altcp_tls释放altcp_tls配置句柄
 */
void altcp_tls_free_config(struct altcp_tls_config *conf);

/** @ingroup altcp_tls释放altcp_tls全局熵实例。所有ALTCP_TLS配置都链接到一个ALTCP_TLS_entropy_rng结构，该结构处理唯一的系统熵&ctr_drbg实例。此函数允许应用程序在所有引用altcp_tls_entropy_rng结构的配置被破坏时释放该结构。如果某些ALTCP_TLS配置句柄仍处于活动状态，则此函数不起作用。
 */
void altcp_tls_free_entropy(void);

/** @ingroup altcp_tls创建新的altcp_tls层，将现有pcb封装为内部连接（例如，tls over TCP）
 */
struct altcp_pcb *altcp_tls_wrap(struct altcp_tls_config *config, struct altcp_pcb *inner_pcb);

/** @ingroup altcp_tls创建新的altcp_tls pcb及其内部tcp pcb
 */
struct altcp_pcb *altcp_tls_new(struct altcp_tls_config *config, u8_t ip_type);

/** @ingroup altcp_tls创建新的altcp_tls层pcb及其内部tcp pcb。
 * Same as @ref altcp_tls_new，但此分配器函数适合
 * @ref altcp_allocater_t/@ref altcp_new。\n“arg”必须包含结构altcp_tls_config。
 */
struct altcp_pcb *altcp_tls_alloc(void *arg, u8_t ip_type);

/** @ingroup altcp_tls返回指向内部tls上下文的指针，以便应用程序可以调整它。实际类型取决于端口（例如mbedtls）
 */
void *altcp_tls_context(struct altcp_pcb *conn);

#ifdef __cplusplus
}
#endif

#endif /* LWIP_ALTCP_TLS */
#endif /* LWIP_ALTCP */
#endif /* LWIP_HDR_ALTCP_TLS_H */

