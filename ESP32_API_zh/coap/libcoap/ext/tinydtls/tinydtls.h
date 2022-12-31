/* tinydtls.h.通过configure从tinydtls.h.in生成。*/
/*******************************************************************************
 * 版权所有（c）2011、2012、2013、2014、2015奥拉夫·伯格曼（TZI）和其他人。保留所有权利。本程序和随附材料根据本发行版附带的Eclipse公共许可证v1.0和Eclipse发行许可证v1.1的条款提供。
 *
 * Eclipse公共许可证位于http://www.eclipse.org/legal/epl-v10.htmlEclipse发行许可证在http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * 贡献者：Olaf Bergmann-初始API和实现Hauke Mehrtens-内存优化、ECC集成
 *
 *******************************************************************************/

/**
 * @file tinydtls.小时
 * @brief 公共tinydtls API
 */

#ifndef _DTLS_TINYDTLS_H_
#define _DTLS_TINYDTLS_H_

#ifdef RIOT_VERSION
#include "platform-specific/riot_boards.h"
#endif /* RIOT_VERSION */

#ifdef CONTIKI
#include "platform-specific/platform.h"
#endif /* CONTIKI */

#ifndef CONTIKI
#ifndef RIOT_VERSION
#ifndef WITH_POSIX
/* TODO:将来删除*/
#define WITH_POSIX 1
#endif /* WITH_POSIX */
#include "dtls_config.h"
#endif /* RIOT_VERSION */
#endif /* CONTIKI */

#ifndef DTLS_ECC
#ifndef DTLS_PSK
#error "TinyDTLS requires at least one Cipher suite!"
#endif /* DTLS_PSK */
#endif /* DTLS_ECC */

#endif /* _DTLS_TINYDTLS_H_ */

