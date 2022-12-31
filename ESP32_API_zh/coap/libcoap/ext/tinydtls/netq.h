/*******************************************************************************
 * 版权所有（c）2011、2012、2013、2014、2015奥拉夫·伯格曼（TZI）和其他人。保留所有权利。本程序和随附材料根据本发行版附带的Eclipse公共许可证v1.0和Eclipse发行许可证v1.1的条款提供。
 *
 * Eclipse公共许可证位于http://www.eclipse.org/legal/epl-v10.htmlEclipse发行许可证在http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * 贡献者：Olaf Bergmann-初始API和实现Hauke Mehrtens-内存优化、ECC集成
 *
 *******************************************************************************/

#ifndef _DTLS_NETQ_H_
#define _DTLS_NETQ_H_

#include "tinydtls.h"
#include "global.h"
#include "dtls.h"
#include "dtls_time.h"

/**
 * \defgroup netq网络分组队列netq实用程序功能实现了通过网络发送的数据分组的有序队列，还可以用于对从网络接收的分组进行排队@{
 */

#ifndef NETQ_MAXCNT
#ifdef DTLS_ECC
#define NETQ_MAXCNT 5 /**<netq结构中的最大元素数*/
#elif defined(DTLS_PSK)
#define NETQ_MAXCNT 3 /**<netq结构中的最大元素数*/
#endif
#endif

/** 
 * netq_t结构中的数据报具有固定的最大大小DTLS_MAX_BUF，以简化受约束节点上的内存管理。*/ 
typedef unsigned char netq_packet_t[DTLS_MAX_BUF];

typedef struct netq_t {
  struct netq_t *next;

  clock_time_t t;	        /**<下次发送PDU的时间*/
  unsigned int timeout;		/**<随机化超时值*/

  dtls_peer_t *peer;		/**<远程地址*/
  uint16_t epoch;
  uint8_t type;
  unsigned char retransmit_cnt;	/**<重传计数器，当为零时将被删除*/

  size_t length;		/**<数据的实际长度*/
#if !(defined (WITH_CONTIKI)) && !(defined (RIOT_VERSION))
  unsigned char data[];		/**<要发送的数据报*/
#else
  netq_packet_t data;		/**<要发送的数据报*/
#endif
} netq_t;

#if !(defined (WITH_CONTIKI)) && !(defined (RIOT_VERSION))
static inline void netq_init(void)
{ }
#else
void netq_init(void);
#endif

/** 
 * 将节点添加到给定队列中，按其时间戳t排序。
 * This function returns @c 错误时为0，如果成功添加了@p节点，则为非零。
 *
 * @param queue 指向将添加@p节点的队列头的指针。
 * @param node  要添加的新项目。
 * @return @c 0，如果添加了新项，则为非零。
 */
int netq_insert_node(netq_t **queue, netq_t *node);

/**销毁指定节点并释放为关联数据报分配的所有内存。*/
void netq_node_free(netq_t *node);

/**从给定队列中删除所有项目并释放分配的存储*/
void netq_delete_all(netq_t **queue);

/**创建适合添加到netq_t队列的新节点。*/
netq_t *netq_node_new(size_t size);

/**
 * 返回指向给定队列中第一项的指针，如果为空，则返回NULL。
 */
netq_t *netq_head(netq_t **queue);

netq_t *netq_next(netq_t *p);
void netq_remove(netq_t **queue, netq_t *p);

/**
 * 删除给定队列中的第一个项目，并返回指向已删除元素的指针。如果在调用netq_pop_first（）时队列为空，则此函数返回NULL。
 */
netq_t *netq_pop_first(netq_t **queue);

/**@}*/

#endif /* _DTLS_NETQ_H_ */

