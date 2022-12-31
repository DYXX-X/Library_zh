/*
 * 版权所有（c）19911993加州大学校长。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。4.未经事先书面许可，不得使用大学的名称或其贡献者的名称来支持或推广源自本软件的产品。
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *	@(#)queue.h	8.5 （伯克利）8/20/94$FreeBSD:src/sys/sys/queue。h、 v 1.32.2.7 2002/04/17 14:21:02出口$
 */

#ifndef _QUEUE_H_
#define	_QUEUE_H_

/* 这里已经为ESP-IDF定义了常见的BSD链接列表队列宏*/
#include <sys/queue.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * 此文件定义循环队列。其他类型的数据结构：单链表、单链尾队列、列表和尾队列是从sys/queue.h中使用的
 *
 * 一个单链接列表由一个前向指针指向。这些元素被单独链接以获得最小的空间和指针操作开销，代价是任意元素的O（n）移除。可以将新元素添加到列表中现有元素之后或列表的开头。从列表开头删除的元素应为此使用显式宏，以获得最佳效率。单个链接列表只能向前遍历。单链接列表非常适合具有大型数据集和很少或没有删除的应用程序，或者用于实现LIFO队列。
 *
 * 单个链接的尾部队列由一对指针组成，一对指针指向列表的头部，另一对指针则指向列表的尾部。这些元素被单独链接以获得最小的空间和指针操作开销，代价是任意元素的O（n）移除。可以在现有元素之后、列表的开头或列表的末尾将新元素添加到列表中。从尾部队列的头部删除的元素应为此使用显式宏，以获得最佳效率。单个链接的尾部队列只能在正向上遍历。单一链接的尾部队列非常适合具有大型数据集和很少或没有删除的应用程序，或者用于实现FIFO队列。
 *
 * 列表由单个前向指针（或哈希表头的前向指针数组）开头。元素是双重链接的，因此可以删除任意元素，而无需遍历列表。可以在现有元素之前或之后或在列表的开头将新元素添加到列表中。列表只能向前遍历。
 *
 * 尾部队列由一对指针组成，一对指针指向列表的头部，另一对指针则指向列表的尾部。元素是双重链接的，因此可以删除任意元素，而无需遍历列表。新元素可以在现有元素之前或之后、列表的开头或列表的末尾添加到列表中。尾部队列可以沿任一方向遍历。
 *
 * 循环队列由一对指针组成，一对指针指向列表的头部，另一对指针则指向列表的尾部。元素是双重链接的，因此可以删除任意元素，而无需遍历列表。新元素可以在现有元素之前或之后、列表的开头或列表的末尾添加到列表中。圆形队列可以沿任一方向遍历，但具有更复杂的列表结尾检测。
 *
 * 有关使用这些宏的详细信息，请参阅队列（3）手册页。
 *
 * SLIST LIST STAILQ TAILQ CIRCLEQ _HEAD + + + + + _HEAD_INITIALIZER + + + + + _ENTRY + + + + + _INIT + + + + + _EMPTY + + + + + _FIRST + + + + + _NEXT + + + + + _PREV - - - + + _LAST - - + + + _FOREACH + + + + + _FOREACH_REVERSE - - - + + _INSERT_HEAD + + + + + _INSERT_BEFORE - + - + + _INSERT_AFTER + + + + + _INSERT_TAIL - - + + + _REMOVE_HEAD + - + - - _REMOVE + + + + +
 *
 */


/*
 * 循环队列声明。
 */
#define	CIRCLEQ_HEAD(name, type)					\
struct name {								\
	struct type *cqh_first;		/* 第一个元素*/		\
	struct type *cqh_last;		/* 最后一个元素*/		\
}

#define	CIRCLEQ_HEAD_INITIALIZER(head)					\
	{ (void *)&(head), (void *)&(head) }

#define	CIRCLEQ_ENTRY(type)						\
struct {								\
	struct type *cqe_next;		/* 下一个元素*/		\
	struct type *cqe_prev;		/* 上一个元素*/		\
}

/*
 * 循环队列函数。
 */
#define	CIRCLEQ_EMPTY(head)	((head)->cqh_first == (void *)(head))

#define	CIRCLEQ_FIRST(head)	((head)->cqh_first)

#define	CIRCLEQ_FOREACH(var, head, field)				\
	for ((var) = CIRCLEQ_FIRST((head));				\
	    (var) != (void *)(head) || ((var) = NULL);			\
	    (var) = CIRCLEQ_NEXT((var), field))

#define	CIRCLEQ_FOREACH_REVERSE(var, head, field)			\
	for ((var) = CIRCLEQ_LAST((head));				\
	    (var) != (void *)(head) || ((var) = NULL);			\
	    (var) = CIRCLEQ_PREV((var), field))

#define	CIRCLEQ_INIT(head) do {						\
	CIRCLEQ_FIRST((head)) = (void *)(head);				\
	CIRCLEQ_LAST((head)) = (void *)(head);				\
} while (0)

#define	CIRCLEQ_INSERT_AFTER(head, listelm, elm, field) do {		\
	CIRCLEQ_NEXT((elm), field) = CIRCLEQ_NEXT((listelm), field);	\
	CIRCLEQ_PREV((elm), field) = (listelm);				\
	if (CIRCLEQ_NEXT((listelm), field) == (void *)(head))		\
		CIRCLEQ_LAST((head)) = (elm);				\
	else								\
		CIRCLEQ_PREV(CIRCLEQ_NEXT((listelm), field), field) = (elm);\
	CIRCLEQ_NEXT((listelm), field) = (elm);				\
} while (0)

#define	CIRCLEQ_INSERT_BEFORE(head, listelm, elm, field) do {		\
	CIRCLEQ_NEXT((elm), field) = (listelm);				\
	CIRCLEQ_PREV((elm), field) = CIRCLEQ_PREV((listelm), field);	\
	if (CIRCLEQ_PREV((listelm), field) == (void *)(head))		\
		CIRCLEQ_FIRST((head)) = (elm);				\
	else								\
		CIRCLEQ_NEXT(CIRCLEQ_PREV((listelm), field), field) = (elm);\
	CIRCLEQ_PREV((listelm), field) = (elm);				\
} while (0)

#define	CIRCLEQ_INSERT_HEAD(head, elm, field) do {			\
	CIRCLEQ_NEXT((elm), field) = CIRCLEQ_FIRST((head));		\
	CIRCLEQ_PREV((elm), field) = (void *)(head);			\
	if (CIRCLEQ_LAST((head)) == (void *)(head))			\
		CIRCLEQ_LAST((head)) = (elm);				\
	else								\
		CIRCLEQ_PREV(CIRCLEQ_FIRST((head)), field) = (elm);	\
	CIRCLEQ_FIRST((head)) = (elm);					\
} while (0)

#define	CIRCLEQ_INSERT_TAIL(head, elm, field) do {			\
	CIRCLEQ_NEXT((elm), field) = (void *)(head);			\
	CIRCLEQ_PREV((elm), field) = CIRCLEQ_LAST((head));		\
	if (CIRCLEQ_FIRST((head)) == (void *)(head))			\
		CIRCLEQ_FIRST((head)) = (elm);				\
	else								\
		CIRCLEQ_NEXT(CIRCLEQ_LAST((head)), field) = (elm);	\
	CIRCLEQ_LAST((head)) = (elm);					\
} while (0)

#define	CIRCLEQ_LAST(head)	((head)->cqh_last)

#define	CIRCLEQ_NEXT(elm,field)	((elm)->field.cqe_next)

#define	CIRCLEQ_PREV(elm,field)	((elm)->field.cqe_prev)

#define	CIRCLEQ_REMOVE(head, elm, field) do {				\
	if (CIRCLEQ_NEXT((elm), field) == (void *)(head))		\
		CIRCLEQ_LAST((head)) = CIRCLEQ_PREV((elm), field);	\
	else								\
		CIRCLEQ_PREV(CIRCLEQ_NEXT((elm), field), field) =	\
		    CIRCLEQ_PREV((elm), field);				\
	if (CIRCLEQ_PREV((elm), field) == (void *)(head))		\
		CIRCLEQ_FIRST((head)) = CIRCLEQ_NEXT((elm), field);	\
	else								\
		CIRCLEQ_NEXT(CIRCLEQ_PREV((elm), field), field) =	\
		    CIRCLEQ_NEXT((elm), field);				\
} while (0)

#ifdef __cplusplus
}
#endif

#endif /* !_QUEUE_H_ */

