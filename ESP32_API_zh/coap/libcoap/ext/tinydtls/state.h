/*******************************************************************************
 * 版权所有（c）2011、2012、2013、2014、2015奥拉夫·伯格曼（TZI）和其他人。保留所有权利。本程序和随附材料根据本发行版附带的Eclipse公共许可证v1.0和Eclipse发行许可证v1.1的条款提供。
 *
 * Eclipse公共许可证位于http://www.eclipse.org/legal/epl-v10.htmlEclipse发行许可证在http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * 贡献者：Olaf Bergmann-初始API和实现Hauke Mehrtens-内存优化、ECC集成
 *
 *******************************************************************************/

/**
 * @file 状态.h
 * @brief DTLS FSM的状态信息
 */

#ifndef _DTLS_STATE_H_
#define _DTLS_STATE_H_

#include <sys/types.h>
#include <stdint.h>

#include "global.h"
#include "hmac.h"

typedef enum { 
  DTLS_STATE_INIT = 0, DTLS_STATE_WAIT_CLIENTHELLO, DTLS_STATE_WAIT_CLIENTCERTIFICATE,
  DTLS_STATE_WAIT_CLIENTKEYEXCHANGE, DTLS_STATE_WAIT_CERTIFICATEVERIFY,
  DTLS_STATE_WAIT_CHANGECIPHERSPEC,
  DTLS_STATE_WAIT_FINISHED, DTLS_STATE_FINISHED, 
  /* 客户端状态*/
  DTLS_STATE_CLIENTHELLO, DTLS_STATE_WAIT_SERVERCERTIFICATE, DTLS_STATE_WAIT_SERVERKEYEXCHANGE,
  DTLS_STATE_WAIT_SERVERHELLODONE,

  DTLS_STATE_CONNECTED,
  DTLS_STATE_CLOSING,
  DTLS_STATE_CLOSED
} dtls_state_t;

typedef struct {
  uint16_t mseq_s;	     /**<发送握手消息序列号计数器*/
  uint16_t mseq_r;	     /**<收到的握手消息序列号计数器*/

  /**握手期间更新的挂起配置*/
  /* 固定装置：dtls_security_parameters_t pending_config；*/

  /* 最终握手哈希的临时存储*/
  dtls_hash_ctx hs_hash;
  /* 扩展主密钥握手哈希的临时存储*/
  dtls_hash_ctx ext_hash;
} dtls_hs_state_t;
#endif /* _DTLS_STATE_H_ */

