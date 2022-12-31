/*
 * SPDX文件版权文本：2013-2015 Wind River Systems，Inc。
 *
 * SPDX许可证标识符：Apache-2.0
 */

/**
 * @file
 * @brief 双重链接列表实现
 *
 * 使用内联宏/函数实现双重链接列表。此API不是线程安全的，因此如果在线程之间使用列表，则必须使用同步原语保护对函数的调用。
 *
 * 列表应该被初始化，以便头指针和尾指针都指向列表本身。以这种方式初始化列表简化了向列表中添加节点和从列表中删除节点。
 */

#ifndef _BLE_MESH_DLIST_H_
#define _BLE_MESH_DLIST_H_

#include <stddef.h>
#include "mesh_util.h"

#ifdef __cplusplus
extern "C" {
#endif


struct _dnode {
    union {
        struct _dnode *head; /* 指向列表头的指针（sys_dlist_t）*/
        struct _dnode *next; /* 指向下一个节点的指针（sys_dnode_t）*/
    };
    union {
        struct _dnode *tail; /* 列表尾部指针（sys_dlist_t）*/
        struct _dnode *prev; /* 指向上一节点的指针（sys_dnode_t）*/
    };
};

typedef struct _dnode sys_dlist_t;
typedef struct _dnode sys_dnode_t;

/**
 * @brief 提供要在列表上迭代的原语注意：循环不安全，因此不应删除__dn
 *
 * 用户_MUST_添加包含自己代码的循环语句大括号：
 *
 *     SYS_DLIST_FOR_EACH_NODE（l，n）｛＜用户代码＞｝
 *
 * 此宏和其他SYS_DLIST_*（）宏不是线程安全的。
 *
 * @param __dl 要迭代的sys_dlist_t上的指针
 * @param __dn 用于查看列表中每个节点的sys_dnode_t指针
 */
#define SYS_DLIST_FOR_EACH_NODE(__dl, __dn)             \
    for (__dn = sys_dlist_peek_head(__dl); __dn;            \
         __dn = sys_dlist_peek_next(__dl, __dn))

/**
 * @brief 提供从列表中的节点对列表进行迭代的原语注意：循环不安全，因此不应删除__dn
 *
 * 用户_MUST_添加包含自己代码的循环语句大括号：
 *
 *     SYS_DLIST_ITERATE_FROM_NODE（l，n）｛＜用户代码＞｝
 *
 * 与SYS_DLIST_FOR_EACH_NODE（）类似，但__dn已经在列表中包含一个节点，可以从中开始搜索下一个条目。如果为NULL，则从头部开始。
 *
 * 此宏和其他SYS_DLIST_*（）宏不是线程安全的。
 *
 * @param __dl 要迭代的sys_dlist_t上的指针
 * @param __dn sys_dnode_t指针，用于查看列表中的每个节点；它包含起始节点，或NULL以从头开始
 */
#define SYS_DLIST_ITERATE_FROM_NODE(__dl, __dn) \
    for (__dn = __dn ? sys_dlist_peek_next_no_check(__dl, __dn) \
             : sys_dlist_peek_head(__dl); \
         __dn; \
         __dn = sys_dlist_peek_next(__dl, __dn))

/**
 * @brief 提供原语以安全地对列表进行迭代注意：__dn可以被删除，它不会中断循环。
 *
 * 用户_MUST_添加包含自己代码的循环语句大括号：
 *
 *     SYS_DLIST_FOR_EACH_NODE_SAFE（l，n，s）｛＜用户代码＞｝
 *
 * 此宏和其他SYS_DLIST_*（）宏不是线程安全的。
 *
 * @param __dl 要迭代的sys_dlist_t上的指针
 * @param __dn 用于查看列表中每个节点的sys_dnode_t指针
 * @param __dns 循环安全运行的sys_dnode_t指针
 */
#define SYS_DLIST_FOR_EACH_NODE_SAFE(__dl, __dn, __dns)         \
    for (__dn = sys_dlist_peek_head(__dl),              \
             __dns = sys_dlist_peek_next(__dl, __dn);       \
         __dn; __dn = __dns,                    \
             __dns = sys_dlist_peek_next(__dl, __dn))

/*
 * @brief 提供原语来解析列表节点的容器注意：与NULL指针节点一起使用是安全的
 *
 * @param __dn 指向sys_dnode_t以获取其容器的指针
 * @param __cn 容器结构类型指针
 * @param __n 容器结构中sys_dnode_t的字段名
 */
#define SYS_DLIST_CONTAINER(__dn, __cn, __n) \
    (__dn ? CONTAINER_OF(__dn, __typeof__(*__cn), __n) : NULL)
/*
 * @brief 为列表头的peek容器提供原语
 *
 * @param __dl 要查看的sys_dlist_t上的指针
 * @param __cn 容器结构类型指针
 * @param __n 容器结构中sys_dnode_t的字段名
 */
#define SYS_DLIST_PEEK_HEAD_CONTAINER(__dl, __cn, __n) \
    SYS_DLIST_CONTAINER(sys_dlist_peek_head(__dl), __cn, __n)

/*
 * @brief 提供原语以查看下一个容器
 *
 * @param __dl 要查看的sys_dlist_t上的指针
 * @param __cn 容器结构类型指针
 * @param __n 容器结构中sys_dnode_t的字段名
 */
#define SYS_DLIST_PEEK_NEXT_CONTAINER(__dl, __cn, __n) \
    ((__cn) ? SYS_DLIST_CONTAINER(sys_dlist_peek_next(__dl, &(__cn->__n)), \
                      __cn, __n) : NULL)

/**
 * @brief 提供在容器下的列表上迭代的原语注意：循环是不安全的，因此__cn不应分离
 *
 * 用户_MUST_添加包含自己代码的循环语句大括号：
 *
 *     SYS_DLIST_FOR_EACH_CONTAINER（l，c，n）｛＜用户代码＞｝
 *
 * @param __dl 要迭代的sys_dlist_t上的指针
 * @param __cn 查看列表中每个条目的指针
 * @param __n 容器结构中sys_dnode_t的字段名
 */
#define SYS_DLIST_FOR_EACH_CONTAINER(__dl, __cn, __n)           \
    for (__cn = SYS_DLIST_PEEK_HEAD_CONTAINER(__dl, __cn, __n); __cn; \
         __cn = SYS_DLIST_PEEK_NEXT_CONTAINER(__dl, __cn, __n))

/**
 * @brief 提供原语以安全地对容器下的列表进行迭代注意：__cn可以分离，它不会中断循环。
 *
 * 用户_MUST_添加包含自己代码的循环语句大括号：
 *
 *     SYS_DLIST_FOR_EACH_CONTAINER_SAFE（l，c，cn，n）｛＜用户代码＞｝
 *
 * @param __dl 要迭代的sys_dlist_t上的指针
 * @param __cn 查看列表中每个条目的指针
 * @param __cns 循环安全运行的指针
 * @param __n 容器结构中sys_dnode_t的字段名
 */
#define SYS_DLIST_FOR_EACH_CONTAINER_SAFE(__dl, __cn, __cns, __n)   \
    for (__cn = SYS_DLIST_PEEK_HEAD_CONTAINER(__dl, __cn, __n), \
         __cns = SYS_DLIST_PEEK_NEXT_CONTAINER(__dl, __cn, __n); __cn; \
         __cn = __cns,                      \
         __cns = SYS_DLIST_PEEK_NEXT_CONTAINER(__dl, __cn, __n))

/**
 * @brief 初始化列表
 *
 * @param list 双重链接列表
 *
 * @return N/A
 */

static inline void sys_dlist_init(sys_dlist_t *list)
{
    list->head = (sys_dnode_t *)list;
    list->tail = (sys_dnode_t *)list;
}

#define SYS_DLIST_STATIC_INIT(ptr_to_list) {{(ptr_to_list)}, {(ptr_to_list)}}

/**
 * @brief 检查节点是否是列表的头部
 *
 * @param list 要操作的双链接列表
 * @param node 要检查的节点
 *
 * @return 如果节点是头部，则为1，否则为0
 */

static inline int sys_dlist_is_head(sys_dlist_t *list, sys_dnode_t *node)
{
    return list->head == node;
}

/**
 * @brief 检查节点是否是列表的尾部
 *
 * @param list 要操作的双链接列表
 * @param node 要检查的节点
 *
 * @return 如果节点是尾部，则为1，否则为0
 */

static inline int sys_dlist_is_tail(sys_dlist_t *list, sys_dnode_t *node)
{
    return list->tail == node;
}

/**
 * @brief 检查列表是否为空
 *
 * @param list 要操作的双链接列表
 *
 * @return 如果为空，则为1，否则为0
 */

static inline int sys_dlist_is_empty(sys_dlist_t *list)
{
    return list->head == list;
}

/**
 * @brief 检查是否存在多个节点
 *
 * 此函数和其他sys_dlist_*（）函数不是线程安全的。
 *
 * @param list 要操作的双链接列表
 *
 * @return 如果有多个节点，则为1，否则为0
 */

static inline int sys_dlist_has_multiple_nodes(sys_dlist_t *list)
{
    return list->head != list->tail;
}

/**
 * @brief 获取列表中标题项的引用
 *
 * @param list 要操作的双链接列表
 *
 * @return 指向head元素的指针，如果列表为空，则为NULL
 */

static inline sys_dnode_t *sys_dlist_peek_head(sys_dlist_t *list)
{
    return sys_dlist_is_empty(list) ? NULL : list->head;
}

/**
 * @brief 获取列表中标题项的引用
 *
 * 列表必须为非空。
 *
 * @param list 要操作的双链接列表
 *
 * @return 指向head元素的指针
 */

static inline sys_dnode_t *sys_dlist_peek_head_not_empty(sys_dlist_t *list)
{
    return list->head;
}

/**
 * @brief 获取对列表中下一项的引用，节点不为NULL
 *
 * 如果节点不为NULL，则比sys_dlist_peek_next（）快。
 *
 * @param list 要操作的双链接列表
 * @param node 从中获取列表中下一个元素的节点
 *
 * @return 指向节点中下一个元素的指针，如果节点是尾部，则为NULL
 */

static inline sys_dnode_t *sys_dlist_peek_next_no_check(sys_dlist_t *list,
                                                        sys_dnode_t *node)
{
    return (node == list->tail) ? NULL : node->next;
}

/**
 * @brief 获取列表中下一项的引用
 *
 * @param list 要操作的双链接列表
 * @param node 从中获取列表中下一个元素的节点
 *
 * @return 指向节点的下一个元素的指针，如果节点是尾部，则为NULL；如果节点是读取空列表的头部，则为空。
 */

static inline sys_dnode_t *sys_dlist_peek_next(sys_dlist_t *list,
                                               sys_dnode_t *node)
{
    return node ? sys_dlist_peek_next_no_check(list, node) : NULL;
}

/**
 * @brief 获取列表中尾项的引用
 *
 * @param list 要操作的双链接列表
 *
 * @return 指向尾部元素的指针，如果列表为空，则为NULL
 */

static inline sys_dnode_t *sys_dlist_peek_tail(sys_dlist_t *list)
{
    return sys_dlist_is_empty(list) ? NULL : list->tail;
}

/**
 * @brief 将节点添加到列表尾部
 *
 * 此函数和其他sys_dlist_*（）函数不是线程安全的。
 *
 * @param list 要操作的双链接列表
 * @param node 要附加的元素
 *
 * @return N/A
 */

static inline void sys_dlist_append(sys_dlist_t *list, sys_dnode_t *node)
{
    node->next = list;
    node->prev = list->tail;

    list->tail->next = node;
    list->tail = node;
}

/**
 * @brief 将节点添加到列表头
 *
 * 此函数和其他sys_dlist_*（）函数不是线程安全的。
 *
 * @param list 要操作的双链接列表
 * @param node 要附加的元素
 *
 * @return N/A
 */

static inline void sys_dlist_prepend(sys_dlist_t *list, sys_dnode_t *node)
{
    node->next = list->head;
    node->prev = list;

    list->head->prev = node;
    list->head = node;
}

/**
 * @brief 在节点后插入节点
 *
 * 在列表中的指定节点之后插入节点。此函数和其他sys_dlist_（）函数不是线程安全的。
 *
 * @param list 要操作的双链接列表
 * @param insert_point 列表中的插入点：如果为NULL，则在开头插入
 * @param node 要附加的元素
 *
 * @return N/A
 */

static inline void sys_dlist_insert_after(sys_dlist_t *list,
                                          sys_dnode_t *insert_point,
                                          sys_dnode_t *node)
{
    if (!insert_point) {
        sys_dlist_prepend(list, node);
    } else {
        node->next = insert_point->next;
        node->prev = insert_point;
        insert_point->next->prev = node;
        insert_point->next = node;
    }
}

/**
 * @brief 在节点之前插入节点
 *
 * 在列表中的指定节点之前插入节点。此函数和其他sys_dlist_（）函数不是线程安全的。
 *
 * @param list 要操作的双链接列表
 * @param insert_point 列表中的插入点：如果为NULL，则在尾部插入
 * @param node 要插入的元素
 *
 * @return N/A
 */

static inline void sys_dlist_insert_before(sys_dlist_t *list,
                                           sys_dnode_t *insert_point,
                                           sys_dnode_t *node)
{
    if (!insert_point) {
        sys_dlist_append(list, node);
    } else {
        node->prev = insert_point->prev;
        node->next = insert_point;
        insert_point->prev->next = node;
        insert_point->prev = node;
    }
}

/**
 * @brief 在位置插入节点
 *
 * 根据外部条件在某个位置插入节点。cond（）函数用于检查节点是否要插入到当前节点之前，并对其进行检查。此函数和其他sys_dlist_（）函数不是线程安全的。
 *
 * @param list 要操作的双链接列表
 * @param node 要插入的元素
 * @param cond 确定当前节点是否为正确插入点的函数
 * @param data cond（）的参数
 *
 * @return N/A
 */

static inline void sys_dlist_insert_at(sys_dlist_t *list, sys_dnode_t *node,
                                       int (*cond)(sys_dnode_t *, void *), void *data)
{
    if (sys_dlist_is_empty(list)) {
        sys_dlist_append(list, node);
    } else {
        sys_dnode_t *pos = sys_dlist_peek_head(list);

        while (pos && !cond(pos, data)) {
            pos = sys_dlist_peek_next(list, pos);
        }
        sys_dlist_insert_before(list, pos, node);
    }
}

/**
 * @brief 从列表中删除特定节点
 *
 * 该列表在节点中是隐式的。节点必须是列表的一部分。此函数和其他sys_dlist_（）函数不是线程安全的。
 *
 * @param node 要删除的节点
 *
 * @return N/A
 */

static inline void sys_dlist_remove(sys_dnode_t *node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

/**
 * @brief 获取列表中的第一个节点
 *
 * 此函数和其他sys_dlist_*（）函数不是线程安全的。
 *
 * @param list 要操作的双链接列表
 *
 * @return 列表中的第一个节点，如果列表为空，则为NULL
 */

static inline sys_dnode_t *sys_dlist_get(sys_dlist_t *list)
{
    sys_dnode_t *node;

    if (sys_dlist_is_empty(list)) {
        return NULL;
    }

    node = list->head;
    sys_dlist_remove(node);
    return node;
}

#ifdef __cplusplus
}
#endif

#endif /* _BLE_MESH_DLIST_H_ */

