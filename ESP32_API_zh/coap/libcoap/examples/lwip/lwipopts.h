/*
 * 我的iPod。h——LwIP示例
 *
 * Copyright (C) 2013-2016 Christian Amsüss <chrysn@fsfe.org> 版权所有（C）2018 John Shallow<supjps-libcoap@jpshallow.com>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

typedef unsigned int sys_prot_t;

#define NO_SYS                     1
#define LWIP_SOCKET                (NO_SYS==0)
#define LWIP_NETCONN               (NO_SYS==0)
#define LWIP_NETIF_API             (NO_SYS==0)

#define LWIP_IPV6                       1
#define LWIP_IPV6_REASS                 0

#ifndef LWIP_RAND
#define LWIP_RAND() ((u32_t)rand())
#endif

#ifndef netif_get_index
#define netif_get_index(netif)      ((u8_t)((netif)->num + 1))
#endif

#if NO_SYS
#include <pthread.h>
extern pthread_mutex_t lwprot_mutex;
extern pthread_t lwprot_thread;
extern int lwprot_count;
#endif
#define MEMP_USE_CUSTOM_POOLS 1

