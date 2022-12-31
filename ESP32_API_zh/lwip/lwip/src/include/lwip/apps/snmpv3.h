/**
 * @file 其他SNMPv3功能RFC3414和RFC3826。
 */

/*
 * 版权所有（c）2016 Elias Oenal。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 作者：Elias Oenal<lwip@eliasoenal.com>
 */

#ifndef LWIP_HDR_APPS_SNMP_V3_H
#define LWIP_HDR_APPS_SNMP_V3_H

#include "lwip/apps/snmp_opts.h"
#include "lwip/err.h"

#ifdef __cplusplus
extern "C" {
#endif

#if LWIP_SNMP && LWIP_SNMP_V3

typedef enum
{
  SNMP_V3_AUTH_ALGO_INVAL = 0,
  SNMP_V3_AUTH_ALGO_MD5   = 1,
  SNMP_V3_AUTH_ALGO_SHA   = 2
} snmpv3_auth_algo_t;

typedef enum
{
  SNMP_V3_PRIV_ALGO_INVAL = 0,
  SNMP_V3_PRIV_ALGO_DES   = 1,
  SNMP_V3_PRIV_ALGO_AES   = 2
} snmpv3_priv_algo_t;

typedef enum
{
  SNMP_V3_USER_STORAGETYPE_OTHER       = 1,
  SNMP_V3_USER_STORAGETYPE_VOLATILE    = 2,
  SNMP_V3_USER_STORAGETYPE_NONVOLATILE = 3,
  SNMP_V3_USER_STORAGETYPE_PERMANENT   = 4,
  SNMP_V3_USER_STORAGETYPE_READONLY    = 5
} snmpv3_user_storagetype_t;

/*
 * 应用程序必须实现以下回调函数。snmpv3_dumm.c中有一个虚拟实现。
 */

void snmpv3_get_engine_id(const char **id, u8_t *len);
err_t snmpv3_set_engine_id(const char* id, u8_t len);

u32_t snmpv3_get_engine_boots(void);
void snmpv3_set_engine_boots(u32_t boots);

u32_t snmpv3_get_engine_time(void);
void snmpv3_reset_engine_time(void);

err_t snmpv3_get_user(const char* username, snmpv3_auth_algo_t *auth_algo, u8_t *auth_key, snmpv3_priv_algo_t *priv_algo, u8_t *priv_key);
u8_t snmpv3_get_amount_of_users(void);
err_t snmpv3_get_user_storagetype(const char *username, snmpv3_user_storagetype_t *storagetype);
err_t snmpv3_get_username(char *username, u8_t index);

/* SNMPv3代理提供以下功能*/

void snmpv3_engine_id_changed(void);
s32_t snmpv3_get_engine_time_internal(void);

void snmpv3_password_to_key_md5(
    const u8_t *password,     /* IN */
    size_t      passwordlen,  /* IN */
    const u8_t *engineID,     /* IN-指向snmpEngineID的指针*/
    u8_t        engineLength, /* IN-snmpEngineID的长度*/
    u8_t       *key);         /* OUT-指向调用者16八位字节缓冲区的指针*/

void snmpv3_password_to_key_sha(
    const u8_t *password,     /* IN */
    size_t      passwordlen,  /* IN */
    const u8_t *engineID,     /* IN-指向snmpEngineID的指针*/
    u8_t        engineLength, /* IN-snmpEngineID的长度*/
    u8_t       *key);         /* OUT-指向调用者20八位字节缓冲区的指针*/

#endif

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_APPS_SNMP_V3_H */

