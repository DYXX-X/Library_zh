/*******************************************************************************
 * 版权所有（c）2011、2012、2013、2014、2015奥拉夫·伯格曼（TZI）和其他人。保留所有权利。本程序和随附材料根据本发行版附带的Eclipse公共许可证v1.0和Eclipse发行许可证v1.1的条款提供。
 *
 * Eclipse公共许可证位于http://www.eclipse.org/legal/epl-v10.htmlEclipse发行许可证在http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * 贡献者：Olaf Bergmann-初始API和实现Hauke Mehrtens-内存优化、ECC集成
 *
 *******************************************************************************/

/**
 * @file 对等体.h
 * @brief DTLS会话中的对等方信息
 */

#ifndef _DTLS_PEER_H_
#define _DTLS_PEER_H_

#include <sys/types.h>

#include "tinydtls.h"
#include "global.h"
#include "session.h"

#include "state.h"
#include "crypto.h"

#ifndef DTLS_PEERS_NOHASH
#include "uthash.h"
#endif /* DTLS_PEERS_NOHASH */

typedef enum { DTLS_CLIENT=0, DTLS_SERVER } dtls_peer_type;

/** 
 * 保存每个对等方的安全参数、本地状态和传输地址。*/
typedef struct dtls_peer_t {
#ifdef DTLS_PEERS_NOHASH
  struct dtls_peer_t *next;
#else /* DTLS_PEERS_NOHASH */
  UT_hash_handle hh;
#endif /* DTLS_PEERS_NOHASH */

  session_t session;	     /**<对等地址和本地接口*/

  dtls_peer_type role;       /**<表示此主机是DTLS_CLIENT还是DTLS_SERVER*/
  dtls_state_t state;        /**<DTLS发动机状态*/

  dtls_security_parameters_t *security_params[2];
  dtls_handshake_parameters_t *handshake_params;
} dtls_peer_t;

static inline dtls_security_parameters_t *dtls_security_params_epoch(dtls_peer_t *peer, uint16_t epoch)
{
  if (peer->security_params[0] && peer->security_params[0]->epoch == epoch) {
    return peer->security_params[0];
  } else if (peer->security_params[1] && peer->security_params[1]->epoch == epoch) {
    return peer->security_params[1];
  } else {
    return NULL;
  }
}

static inline dtls_security_parameters_t *dtls_security_params(dtls_peer_t *peer)
{
  return peer->security_params[0];
}

static inline dtls_security_parameters_t *dtls_security_params_next(dtls_peer_t *peer)
{
  if (peer->security_params[1])
    dtls_security_free(peer->security_params[1]);

  peer->security_params[1] = dtls_security_new();
  if (!peer->security_params[1]) {
    return NULL;
  }
  peer->security_params[1]->epoch = peer->security_params[0]->epoch + 1;
  return peer->security_params[1];
}

static inline void dtls_security_params_free_other(dtls_peer_t *peer)
{
  dtls_security_parameters_t * security0 = peer->security_params[0];
  dtls_security_parameters_t * security1 = peer->security_params[1];

  if (!security0 || !security1 || security0->epoch < security1->epoch)
    return;

  dtls_security_free(security1);
  peer->security_params[1] = NULL;
}

static inline void dtls_security_params_switch(dtls_peer_t *peer)
{
  dtls_security_parameters_t * security = peer->security_params[1];

  peer->security_params[1] = peer->security_params[0];
  peer->security_params[0] = security;
}

void peer_init(void);

/**
 * Creates a new peer for given @p 一场当前配置使用密码套件TLS_NULL_with_NULL_NULL初始化（即完全没有安全性）。此函数返回指向新对等体的指针或出错时返回NULL。调用方负责使用dtls_free_peer（）释放为此对等方分配的存储。
 *
 * @param session  远程对等方的地址和本地接口索引。
 * @return 指向新创建和初始化的对等对象的指针，或出错时为NULL。
 */
dtls_peer_t *dtls_new_peer(const session_t *session);

/**释放分配给@p peer的存储。*/
void dtls_free_peer(dtls_peer_t *peer);

/**返回@p peer的当前状态。*/
static inline dtls_state_t dtls_peer_state(const dtls_peer_t *peer) {
  return peer->state;
}

/**
 * Checks if given @p 对等体已连接。此函数返回
 * @c 如果已连接，则为1，否则为@c 0。
 */
static inline int dtls_peer_is_connected(const dtls_peer_t *peer) {
  return peer->state == DTLS_STATE_CONNECTED;
}

#endif /* _DTLS_PEER_H_ */

