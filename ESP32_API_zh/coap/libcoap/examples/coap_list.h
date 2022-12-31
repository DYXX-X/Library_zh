/* -*-模式：C；标签宽度：2；缩进选项卡模式：nil；c-basic-offset：2*-*-*/

/* coap_list。h——CoAP列表结构
 *
 * 版权所有（C）201020112015奥拉夫·伯格曼<bergmann@tzi.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

/*
 * 示例/coap_list。[ch]已弃用。您应该将structcoap_optlist_t与libcoap的一部分的以下函数一起使用。
 *
 * coap_new_optlist（）coap_insert_optlist
 *
 * 有关详细信息，请参阅“man coap_pdu_setup”。
 *
 * 示例/coap_list。[ch]文件将在将来的版本中删除。它们保留在这里，以支持构建coap客户端旧版本的向后兼容性
 */

#ifndef COAP_LIST_H_
#define COAP_LIST_H_

#include <coap3/utlist.h>

typedef struct coap_list_t {
  struct coap_list_t *next;
  char data[];
} coap_list_t;

/**
 * 将节点添加到给定队列，按指定的顺序函数排序。插入成功时返回1，否则返回0。
 */
int coap_insert(coap_list_t **queue, coap_list_t *node);

/* 破坏指定节点*/
int coap_delete(coap_list_t *node);

/* 从给定队列中删除所有项目并释放分配的存储*/
void coap_delete_list(coap_list_t *queue);

#endif /* COAP_LIST_H_ */

