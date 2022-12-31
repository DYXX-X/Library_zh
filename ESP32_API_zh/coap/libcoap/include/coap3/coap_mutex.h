/*
 * coap_mutex.h—互斥实用程序
 *
 * Copyright (C) 2019 Jon Shallow <supjps-libcoap@jpshallow.com> 2019奥拉夫·伯格曼<bergmann@tzi.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

/**
 * @file coap_mutex.h
 * @brief COAP互斥机制包装器
 */

#ifndef COAP_MUTEX_H_
#define COAP_MUTEX_H_

/*
 * 互斥当前仅在存在受约束的堆栈时使用，并且需要保护大型静态变量（而不是堆栈上的大型变量）。
 */
#if COAP_CONSTRAINED_STACK

#if defined(HAVE_PTHREAD_H) && defined(HAVE_PTHREAD_MUTEX_LOCK)
#include <pthread.h>

typedef pthread_mutex_t coap_mutex_t;
#define COAP_MUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER
#define coap_mutex_lock(a) pthread_mutex_lock(a)
#define coap_mutex_trylock(a) pthread_mutex_trylock(a)
#define coap_mutex_unlock(a) pthread_mutex_unlock(a)

#elif defined(RIOT_VERSION)
/* 使用RIOT的互斥API*/
#include <mutex.h>

typedef mutex_t coap_mutex_t;
#define COAP_MUTEX_INITIALIZER MUTEX_INIT
#define coap_mutex_lock(a) mutex_lock(a)
#define coap_mutex_trylock(a) mutex_trylock(a)
#define coap_mutex_unlock(a) mutex_unlock(a)

#else
/* 定义存根互斥函数*/
typedef int coap_mutex_t;
#define COAP_MUTEX_INITIALIZER 0
#define coap_mutex_lock(a) *(a) = 1
#define coap_mutex_trylock(a) *(a) = 1
#define coap_mutex_unlock(a) *(a) = 0

#endif /* !RIOT_VERSION && !HAVE_PTHREAD_H && !HAVE_PTHREAD_MUTEX_LOCK */

#endif /* COAP_CONSTRAINED_STACK */

#endif /* COAP_MUTEX_H_ */

