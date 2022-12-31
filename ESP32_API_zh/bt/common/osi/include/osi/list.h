#ifndef _LIST_H_
#define _LIST_H_

#include <stdbool.h>
#include <stddef.h>
struct list_node_t;
typedef struct list_node_t list_node_t;

struct list_t;
typedef struct list_t list_t;

typedef void (*list_free_cb)(void *data);
typedef bool (*list_iter_cb)(void *data, void *context);

// 返回一个新的空列表。如果无法分配足够的内存，则返回NULL
// 用于列表结构。必须使用|list_free |释放返回的列表。这个
// |callback |指定删除列表元素时要调用的函数
// 从列表中删除。它可以用于释放列表元素所持有的资源，例如。
// 内存或文件描述符|如果不需要清理，则callback |可以为NULL
// 元件移除。
list_t *list_new(list_free_cb callback);


list_node_t *list_free_node(list_t *list, list_node_t *node);

// 与list_free_node类似，此函数不会释放节点数据
list_node_t *list_delete_node(list_t *list, list_node_t *node);

// 释放列表。此函数接受NULL作为参数，在这种情况下
// 表现得像个傻瓜。
void list_free(list_t *list);

// 如果|list|为空（没有元素），则返回true，否则返回false。
// |列表|不能为NULL。
bool list_is_empty(const list_t *list);

// 如果列表包含|data|，则返回true，否则返回false。
// |列表|不能为NULL。
bool list_contains(const list_t *list, const void *data);

// 返回包含|data|的list_node，否则返回NULL。
// |列表|不能为NULL。
list_node_t *list_get_node(const list_t *list, const void *data);

// 返回|list|的长度|列表|不能为NULL。
size_t list_length(const list_t *list);

// 返回列表中的第一个元素而不删除它|列表|不能
// 为NULL或空。
void *list_front(const list_t *list);

// 返回列表中的最后一个元素，而不删除它|列表|不能
// 为NULL或空。
void *list_back(const list_t *list);
list_node_t *list_back_node(const list_t *list);

// 在|list|中的|prev_node|之后插入|data||data|、|list|和|prev_node|
// 不能为NULL。此函数不会复制|data|，因此指针
// 必须至少保持有效，直到元素从列表或
// 列表被释放。如果无法插入|data|，则返回true，否则返回false
// （例如内存不足）。
bool list_insert_after(list_t *list, list_node_t *prev_node, void *data);

// 在|list|的开头插入|data|。|data|或|list|都不能为NULL。
// 此函数不会复制|data|，因此指针必须保持有效
// 至少直到元素从列表中移除或列表被释放。
// 如果可以插入|data|，则返回true，否则返回false（例如内存不足）。
bool list_prepend(list_t *list, void *data);

// 在|list|末尾插入|data|。|data|或|list|都不能为NULL。
// 此函数不会复制|data|，因此指针必须保持有效
// 至少直到元素从列表中移除或列表被释放。
// 如果可以插入|data|，则返回true，否则返回false（例如内存不足）。
bool list_append(list_t *list, void *data);

// 从列表中删除|data|。|list|或|data|都不能为NULL。如果|数据|
// 在列表中多次插入，此函数将仅删除第一个
// 例子如果在|list_new|中指定了自由函数，则将调用该函数
// 带有|data|。如果在列表中找到并删除了|data|，则此函数返回true，
// 否则为false。
//list_node_t list_remove_node（list_t*列表，list_node_t*前一节点，list_node _t*节点）；
//list_node_t list_insert_node（list_t*列表，list_node_t*前一节点，list_node*节点）；

bool list_remove(list_t *list, void *data);

// 类似于list_remove，但不释放节点数据
bool list_delete(list_t *list, void *data);

// 删除列表中的所有元素。调用此函数会将列表返回到
// 与|list_new|之后的状态相同|列表|不能为NULL。
void list_clear(list_t *list);

// 遍历整个|list|并为每个数据元素调用|callback |。
// 如果列表为空，则永远不会调用|callback |。变异
// 列表。如果在被访问的节点之前添加了元素，
// 将不会对新插入的节点进行回调。既不是|list|也不是
// |callback |可能为NULL。
list_node_t *list_foreach(const list_t *list, list_iter_cb callback, void *context);

// 返回|list|中第一个元素的迭代器|列表|不能为NULL。
// 返回的迭代器只要不等于返回的值就有效
// 按|list_end|。
list_node_t *list_begin(const list_t *list);

// 返回指向列表末尾的迭代器。换句话说，
// 此函数返回给定列表的无效迭代器的值。
// 当迭代器的值与此函数返回的值相同时
// 不能再使用迭代器调用|list_next ||列表|不能为NULL。
list_node_t *list_end(const list_t *list);

// 给定有效的迭代器|node|，此函数将返回
// 迭代器。如果返回的值等于|list_end|返回的值
// 迭代器已到达列表末尾，可能不再用于任何
// 意图
list_node_t *list_next(const list_node_t *node);

// 返回存储在迭代器|节点|指向的位置的值。
// |node|不能等于|list_end|返回的值。
void *list_node(const list_node_t *node);

#endif /* _LIST_H_ */

