/*******************************************************************************
 * 版权所有（c）2019奥拉夫·伯格曼（TZI）和其他人。保留所有权利。本程序和随附材料根据本发行版附带的Eclipse公共许可证v1.0和Eclipse发行许可证v1.1的条款提供。
 *
 * Eclipse公共许可证位于http://www.eclipse.org/legal/epl-v10.htmlEclipse发行许可证在http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * 贡献者：Jon Shallow-通用互斥支持的Initall插件
 *
 *******************************************************************************/

/**
 * @file 分分钟_分钟.h
 * @brief DTLS互斥机制包装器
 */

#ifndef _DTLS_MUTEX_H_
#define _DTLS_MUTEX_H_

#if defined(RIOT_VERSION)

#include <mutex.h>

typedef mutex_t dtls_mutex_t;
#define DTLS_MUTEX_INITIALIZER MUTEX_INIT
#define dtls_mutex_lock(a) mutex_lock(a)
#define dtls_mutex_trylock(a) mutex_trylock(a)
#define dtls_mutex_unlock(a) mutex_unlock(a)

#elif defined(WITH_CONTIKI)

/* CONTIKI不支持互斥*/

typedef int dtls_mutex_t;
#define DTLS_MUTEX_INITIALIZER 0
#define dtls_mutex_lock(a) *(a) = 1
#define dtls_mutex_trylock(a) *(a) = 1
#define dtls_mutex_unlock(a) *(a) = 0

#else /* ! RIOT_VERSION && ! WITH_CONTIKI */

#include <pthread.h>

typedef pthread_mutex_t dtls_mutex_t;
#define DTLS_MUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER
#define dtls_mutex_lock(a) pthread_mutex_lock(a)
#define dtls_mutex_trylock(a) pthread_mutex_trylock(a)
#define dtls_mutex_unlock(a) pthread_mutex_unlock(a)

#endif /* ! RIOT_VERSION && ! WITH_CONTIKI */

#endif /* _DTLS_MUTEX_H_ */

