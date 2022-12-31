/*
 * SPDX文件版权文本：2016 Intel Corporation
 *
 * SPDX许可证标识符：Apache-2.0
 */

/**
 * @file
 *
 * @brief 单链表实现
 *
 * 使用内联宏/函数的单链接列表实现。此API不是线程安全的，因此如果在线程之间使用列表，则必须使用同步原语保护对函数的调用。
 */

#ifndef _BLE_MESH_SLIST_H_
#define _BLE_MESH_SLIST_H_

#include <stddef.h>
#include <stdbool.h>
#include "mesh_util.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _snode {
    struct _snode *next;
};

typedef struct _snode sys_snode_t;

struct _slist {
    sys_snode_t *head;
    sys_snode_t *tail;
};

typedef struct _slist sys_slist_t;

/**
 * @brief 提供要在列表上迭代的原语注意：循环不安全，因此不应删除__sn
 *
 * 用户_MUST_添加包含自己代码的循环语句大括号：
 *
 *     SYS_SLIST_FOR_EACH_NODE（l，n）｛＜用户代码＞｝
 *
 * 此宏和其他SYS_SLIST_*（）宏不是线程安全的。
 *
 * @param __sl 要迭代的sys_slist_t上的指针
 * @param __sn 用于查看列表中每个节点的sys_snode_t指针
 */
#define SYS_SLIST_FOR_EACH_NODE(__sl, __sn)         \
    for (__sn = sys_slist_peek_head(__sl); __sn;    \
         __sn = sys_slist_peek_next(__sn))

/**
 * @brief 提供从列表中的节点对列表进行迭代的原语注意：循环不安全，因此不应删除__sn
 *
 * 用户_MUST_添加包含自己代码的循环语句大括号：
 *
 *     SYS_SLIST_ITERATE_FROM_NODE（l，n）｛＜用户代码＞｝
 *
 * 与SYS_SLIST_FOR_EACH_NODE（）类似，但__dn已经在列表中包含一个节点，可以从中开始搜索下一个条目。如果为NULL，则从头部开始。
 *
 * 此宏和其他SYS_SLIST_*（）宏不是线程安全的。
 *
 * @param __sl 要迭代的sys_slist_t上的指针
 * @param __sn sys_snode_t指针，用于查看包含起始节点的列表中的每个节点，或NULL指针，用于从头开始
 */
#define SYS_SLIST_ITERATE_FROM_NODE(__sl, __sn)             \
    for (__sn = __sn ? sys_slist_peek_next_no_check(__sn)   \
             : sys_slist_peek_head(__sl);                   \
         __sn;                                              \
         __sn = sys_slist_peek_next(__sn))

/**
 * @brief 提供原语以安全地对列表进行迭代注意：__sn可以被删除，它不会中断循环。
 *
 * 用户_MUST_添加包含自己代码的循环语句大括号：
 *
 *     SYS_SLIST_FOR_EACH_NODE_SAFE（l，n，s）｛＜用户代码＞｝
 *
 * 此宏和其他SYS_SLIST_*（）宏不是线程安全的。
 *
 * @param __sl 要迭代的sys_slist_t上的指针
 * @param __sn 用于查看列表中每个节点的sys_snode_t指针
 * @param __sns 循环安全运行的sys_snode_t指针
 */
#define SYS_SLIST_FOR_EACH_NODE_SAFE(__sl, __sn, __sns) \
    for (__sn = sys_slist_peek_head(__sl),              \
             __sns = sys_slist_peek_next(__sn);         \
         __sn; __sn = __sns,                            \
             __sns = sys_slist_peek_next(__sn))

/*
 * @brief 提供原语来解析列表节点的容器注意：与NULL指针节点一起使用是安全的
 *
 * @param __ln sys_node_t上获取其容器的指针
 * @param __cn 容器结构类型指针
 * @param __n 容器结构中sys_node_t的字段名
 */
#define SYS_SLIST_CONTAINER(__ln, __cn, __n)    \
        ((__ln) ? CONTAINER_OF((__ln), __typeof__(*(__cn)), __n) : NULL)
/*
 * @brief 为列表头的peek容器提供原语
 *
 * @param __sl 要查看的sys_slist_t上的指针
 * @param __cn 容器结构类型指针
 * @param __n 容器结构中sys_node_t的字段名
 */
#define SYS_SLIST_PEEK_HEAD_CONTAINER(__sl, __cn, __n)  \
        SYS_SLIST_CONTAINER(sys_slist_peek_head(__sl), __cn, __n)

/*
 * @brief 为列表尾部的peek容器提供原语
 *
 * @param __sl 要查看的sys_slist_t上的指针
 * @param __cn 容器结构类型指针
 * @param __n 容器结构中sys_node_t的字段名
 */
#define SYS_SLIST_PEEK_TAIL_CONTAINER(__sl, __cn, __n)  \
        SYS_SLIST_CONTAINER(sys_slist_peek_tail(__sl), __cn, __n)

/*
 * @brief 提供原语以查看下一个容器
 *
 * @param __cn 容器结构类型指针
 * @param __n 容器结构中sys_node_t的字段名
 */

#define SYS_SLIST_PEEK_NEXT_CONTAINER(__cn, __n)                            \
        ((__cn) ? SYS_SLIST_CONTAINER(sys_slist_peek_next(&((__cn)->__n)),  \
                __cn, __n) : NULL)

/**
 * @brief 提供在容器下的列表上迭代的原语注意：循环是不安全的，因此__cn不应分离
 *
 * 用户_MUST_添加包含自己代码的循环语句大括号：
 *
 *     SYS_SLIST_FOR_EACH_CONTAINER（l，c，n）｛＜用户代码＞｝
 *
 * @param __sl 要迭代的sys_slist_t上的指针
 * @param __cn 查看列表中每个条目的指针
 * @param __n 容器结构中sys_node_t的字段名
 */
#define SYS_SLIST_FOR_EACH_CONTAINER(__sl, __cn, __n)                   \
    for (__cn = SYS_SLIST_PEEK_HEAD_CONTAINER(__sl, __cn, __n); __cn;   \
         __cn = SYS_SLIST_PEEK_NEXT_CONTAINER(__cn, __n))

/**
 * @brief 提供原语以安全地对容器下的列表进行迭代注意：__cn可以分离，它不会中断循环。
 *
 * 用户_MUST_添加包含自己代码的循环语句大括号：
 *
 *     SYS_SLIST_FOR_EACH_NODE_SAFE（l，c，cn，n）｛＜用户代码＞｝
 *
 * @param __sl 要迭代的sys_slist_t上的指针
 * @param __cn 查看列表中每个条目的指针
 * @param __cns 循环安全运行的指针
 * @param __n 容器结构中sys_node_t的字段名
 */
#define SYS_SLIST_FOR_EACH_CONTAINER_SAFE(__sl, __cn, __cns, __n)   \
    for (__cn = SYS_SLIST_PEEK_HEAD_CONTAINER(__sl, __cn, __n),     \
         __cns = SYS_SLIST_PEEK_NEXT_CONTAINER(__cn, __n); __cn;    \
         __cn = __cns, __cns = SYS_SLIST_PEEK_NEXT_CONTAINER(__cn, __n))

/**
 * @brief 初始化列表
 *
 * @param list 列表上要初始化的指针
 */
static inline void sys_slist_init(sys_slist_t *list)
{
    list->head = NULL;
    list->tail = NULL;
}

#define SYS_SLIST_STATIC_INIT(ptr_to_list) {NULL, NULL}

/**
 * @brief 测试给定列表是否为空
 *
 * @param list 要测试的列表上的指针
 *
 * @return 布尔值，如果为空则为true，否则为false
 */
static inline bool sys_slist_is_empty(sys_slist_t *list)
{
    return (!list->head);
}

/**
 * @brief 从列表中查看第一个节点
 *
 * @param list 列表上的一个点，用于查看第一个节点
 *
 * @return 列表第一个节点上的指针（如果没有，则为NULL）
 */
static inline sys_snode_t *sys_slist_peek_head(sys_slist_t *list)
{
    return list->head;
}

/**
 * @brief 从列表中查看最后一个节点
 *
 * @param list 从列表上的一个点查看最后一个节点
 *
 * @return 列表最后一个节点上的指针（如果没有，则为NULL）
 */
static inline sys_snode_t *sys_slist_peek_tail(sys_slist_t *list)
{
    return list->tail;
}

/**
 * @brief 从当前节点中查看下一个节点，节点不为NULL
 *
 * 如果节点不为NULL，则比sys_slist_peek_next（）更快。
 *
 * @param node 查看下一个节点的节点上的指针
 *
 * @return 下一个节点上的指针（如果没有，则为NULL）
 */
static inline sys_snode_t *sys_slist_peek_next_no_check(sys_snode_t *node)
{
    return node->next;
}

/**
 * @brief 从当前节点查看下一个节点
 *
 * @param node 查看下一个节点的节点上的指针
 *
 * @return 下一个节点上的指针（如果没有，则为NULL）
 */
static inline sys_snode_t *sys_slist_peek_next(sys_snode_t *node)
{
    return node ? sys_slist_peek_next_no_check(node) : NULL;
}

/**
 * @brief 将节点前置到给定列表
 *
 * 此函数和其他sys_slist_*（）函数不是线程安全的。
 *
 * @param list 要影响的列表上的指针
 * @param node 要准备的节点上的指针
 */
static inline void sys_slist_prepend(sys_slist_t *list,
                                     sys_snode_t *node)
{
    node->next = list->head;
    list->head = node;

    if (!list->tail) {
        list->tail = list->head;
    }
}

/**
 * @brief 将节点附加到给定列表
 *
 * 此函数和其他sys_slist_*（）函数不是线程安全的。
 *
 * @param list 要影响的列表上的指针
 * @param node 要追加的节点上的指针
 */
static inline void sys_slist_append(sys_slist_t *list,
                                    sys_snode_t *node)
{
    node->next = NULL;

    if (!list->tail) {
        list->tail = node;
        list->head = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
}

/**
 * @brief 将列表附加到给定列表
 *
 * 将包含指向下一个节点的指针的节点（作为节点的第一个元素）的单链接、以NULL结尾的列表附加到@a列表。此函数和其他sys_slist_（）函数不是线程安全的。
 *
 * @param list 要影响的列表上的指针
 * @param head 指向要附加的列表的第一个元素的指针
 * @param tail 指向要追加的列表的最后一个元素的指针
 */
static inline void sys_slist_append_list(sys_slist_t *list,
                                         void *head, void *tail)
{
    if (!list->tail) {
        list->head = (sys_snode_t *)head;
        list->tail = (sys_snode_t *)tail;
    } else {
        list->tail->next = (sys_snode_t *)head;
        list->tail = (sys_snode_t *)tail;
    }
}

/**
 * @brief 合并两个列表，将第二个列表附加到第一个列表
 *
 * 操作完成后，附加列表为空。此函数和其他sys_slist_（）函数不是线程安全的。
 *
 * @param list 要影响的列表上的指针
 * @param list_to_append 指向要追加的列表的指针。
 */
static inline void sys_slist_merge_slist(sys_slist_t *list,
                                         sys_slist_t *list_to_append)
{
    sys_slist_append_list(list, list_to_append->head,
                          list_to_append->tail);
    sys_slist_init(list_to_append);
}

/**
 * @brief 在给定列表中插入节点
 *
 * 此函数和其他sys_slist_*（）函数不是线程安全的。
 *
 * @param list 要影响的列表上的指针
 * @param prev 上一个节点上的指针
 * @param node 要插入的节点上的指针
 */
static inline void sys_slist_insert(sys_slist_t *list,
                                    sys_snode_t *prev,
                                    sys_snode_t *node)
{
    if (!prev) {
        sys_slist_prepend(list, node);
    } else if (!prev->next) {
        sys_slist_append(list, node);
    } else {
        node->next = prev->next;
        prev->next = node;
    }
}

/**
 * @brief 获取并删除给定列表的第一个节点
 *
 * 列表必须为非空。此函数和其他sys_slist_（）函数不是线程安全的。
 *
 * @param list 要影响的列表上的指针
 *
 * @return 指向列表第一个节点的指针
 */
static inline sys_snode_t *sys_slist_get_not_empty(sys_slist_t *list)
{
    sys_snode_t *node = list->head;

    list->head = node->next;
    if (list->tail == node) {
        list->tail = list->head;
    }

    return node;
}

/**
 * @brief 获取并删除给定列表的第一个节点
 *
 * 此函数和其他sys_slist_*（）函数不是线程安全的。
 *
 * @param list 要影响的列表上的指针
 *
 * @return 指向列表第一个节点的指针（如果为空，则为NULL）
 */
static inline sys_snode_t *sys_slist_get(sys_slist_t *list)
{
    return sys_slist_is_empty(list) ? NULL : sys_slist_get_not_empty(list);
}

/**
 * @brief 删除节点
 *
 * 此函数和其他sys_slist_*（）函数不是线程安全的。
 *
 * @param list 要影响的列表上的指针
 * @param prev_node 上一个节点上的指针（可以为NULL，这意味着该节点是列表的头部）
 * @param node 要删除的节点上的指针
 */
static inline void sys_slist_remove(sys_slist_t *list,
                                    sys_snode_t *prev_node,
                                    sys_snode_t *node)
{
    if (!prev_node) {
        list->head = node->next;

        /* 节点也是尾部吗？*/
        if (list->tail == node) {
            list->tail = list->head;
        }
    } else {
        prev_node->next = node->next;

        /* node是尾巴吗？*/
        if (list->tail == node) {
            list->tail = prev_node;
        }
    }

    node->next = NULL;
}

/**
 * @brief 从列表中查找并删除节点
 *
 * 此函数和其他sys_slist_*（）函数不是线程安全的。
 *
 * @param list 要影响的列表上的指针
 * @param node 要从列表中删除的节点上的指针
 *
 * @return 如果删除了节点，则为true
 */
static inline bool sys_slist_find_and_remove(sys_slist_t *list,
                                             sys_snode_t *node)
{
    sys_snode_t *prev = NULL;
    sys_snode_t *test;

    SYS_SLIST_FOR_EACH_NODE(list, test) {
        if (test == node) {
            sys_slist_remove(list, prev, node);
            return true;
        }

        prev = test;
    }

    return false;
}

#ifdef __cplusplus
}
#endif

#endif /* _BLE_MESH_SLIST_H_ */

