/*
版权所有（c）2007-2021，Troy D.Hansonhttp://troydhanson.github.io/uthash/All版权所有。

在满足以下条件的情况下，允许以源和二进制形式重新分发和使用，无论是否进行修改：

    * 源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "ASIS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITEDTO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR APARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNEROR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, ORPROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OFLIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDINGNEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THISSOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef UTLIST_H
#define UTLIST_H

#define UTLIST_VERSION 2.3.0

#include <assert.h>

/*
 * 此文件包含用于操作单链接列表和双链接列表的宏。
 *
 * 1.LL_宏：单链表。2.DL_宏：双链接列表。3.CDL_宏：循环双链接列表。
 *
 * 要使用单链接列表，结构必须具有“下一个”指针。要使用双链接列表，结构必须具有“prev”和“next”指针。无论哪种方式，指向列表头部的指针都必须初始化为NULL。
 *
 * ----------------.示例-------------------------结构项｛int id；结构项prev，next；｝
 *
 * 结构项*列表=空：
 *
 * int main（）｛struct item item；…分配并填充item…DL_APPEND（列表，item）；｝
 * --------------------------------------------------
 *
 * 对于双链接列表，追加和删除宏是O（1）对于单链接列表，附加和删除是O（n），但前置是O（2）对于所有类型的单/双/循环列表，排序宏都是O（nlog（n））。
 */

/* 这些宏使用decltype或GNU扩展的早期__type。由于decltype仅在较新的编译器（编译c++源代码时为VS2010或gcc 4.3+）中可用，因此该代码使用所需的任何方法，或者对于VS2008（两者都不可用），使用强制转换解决方案。*/
#if !defined(LDECLTYPE) && !defined(NO_DECLTYPE)
#if defined(_MSC_VER)   /* MS编译器*/
#if _MSC_VER >= 1600 && defined(__cplusplus)  /* C++模式下的VS2010或更高版本*/
#define LDECLTYPE(x) decltype(x)
#else                   /* VS2008或更高版本（或C模式下的VS2010）*/
#define NO_DECLTYPE
#endif
#elif defined(__BORLANDC__) || defined(__ICCARM__) || defined(__LCC__) || defined(__WATCOMC__)
#define NO_DECLTYPE
#else                   /* GNU、Sun和其他编译器*/
#define LDECLTYPE(x) __typeof(x)
#endif
#endif

/* 对于VS2008，我们使用一些变通方法来解决缺少decltype的问题，即，如果我们需要取消引用列表头的prev/next指针，并保存/恢复真正的头，我们总是将tmp变量重新分配给列表头。*/
#ifdef NO_DECLTYPE
#define IF_NO_DECLTYPE(x) x
#define LDECLTYPE(x) char*
#define UTLIST_SV(elt,list) _tmp = (char*)(list); {char **_alias = (char**)&(list); *_alias = (elt); }
#define UTLIST_NEXT(elt,list,next) ((char*)((list)->next))
#define UTLIST_NEXTASGN(elt,list,to,next) { char **_alias = (char**)&((list)->next); *_alias=(char*)(to); }
/* #定义UTLIST_PREV（elt，list，PREV）（（char*）（（list）->PREV））*/
#define UTLIST_PREVASGN(elt,list,to,prev) { char **_alias = (char**)&((list)->prev); *_alias=(char*)(to); }
#define UTLIST_RS(list) { char **_alias = (char**)&(list); *_alias=_tmp; }
#define UTLIST_CASTASGN(a,b) { char **_alias = (char**)&(a); *_alias=(char*)(b); }
#else
#define IF_NO_DECLTYPE(x)
#define UTLIST_SV(elt,list)
#define UTLIST_NEXT(elt,list,next) ((elt)->next)
#define UTLIST_NEXTASGN(elt,list,to,next) ((elt)->next)=(to)
/* #定义UTLIST_PREV（elt，list，PREV）（（elt）->PREV）*/
#define UTLIST_PREVASGN(elt,list,to,prev) ((elt)->prev)=(to)
#define UTLIST_RS(list)
#define UTLIST_CASTASGN(a,b) (a)=(b)
#endif

/******************************************************************************
 * 排序宏是Simon Tatham的O（n log（n））mergesort*的一个改编，这里使用了一些不友好的变量名称，以避免传入变量的阴影。
 *****************************************************************************/
#define LL_SORT(list, cmp)                                                                     \
    LL_SORT2(list, cmp, next)

#define LL_SORT2(list, cmp, next)                                                              \
do {                                                                                           \
  LDECLTYPE(list) _ls_p;                                                                       \
  LDECLTYPE(list) _ls_q;                                                                       \
  LDECLTYPE(list) _ls_e;                                                                       \
  LDECLTYPE(list) _ls_tail;                                                                    \
  IF_NO_DECLTYPE(LDECLTYPE(list) _tmp;)                                                        \
  int _ls_insize, _ls_nmerges, _ls_psize, _ls_qsize, _ls_i, _ls_looping;                       \
  if (list) {                                                                                  \
    _ls_insize = 1;                                                                            \
    _ls_looping = 1;                                                                           \
    while (_ls_looping) {                                                                      \
      UTLIST_CASTASGN(_ls_p,list);                                                             \
      (list) = NULL;                                                                           \
      _ls_tail = NULL;                                                                         \
      _ls_nmerges = 0;                                                                         \
      while (_ls_p) {                                                                          \
        _ls_nmerges++;                                                                         \
        _ls_q = _ls_p;                                                                         \
        _ls_psize = 0;                                                                         \
        for (_ls_i = 0; _ls_i < _ls_insize; _ls_i++) {                                         \
          _ls_psize++;                                                                         \
          UTLIST_SV(_ls_q,list); _ls_q = UTLIST_NEXT(_ls_q,list,next); UTLIST_RS(list);        \
          if (!_ls_q) break;                                                                   \
        }                                                                                      \
        _ls_qsize = _ls_insize;                                                                \
        while (_ls_psize > 0 || (_ls_qsize > 0 && _ls_q)) {                                    \
          if (_ls_psize == 0) {                                                                \
            _ls_e = _ls_q; UTLIST_SV(_ls_q,list); _ls_q =                                      \
              UTLIST_NEXT(_ls_q,list,next); UTLIST_RS(list); _ls_qsize--;                      \
          } else if (_ls_qsize == 0 || !_ls_q) {                                               \
            _ls_e = _ls_p; UTLIST_SV(_ls_p,list); _ls_p =                                      \
              UTLIST_NEXT(_ls_p,list,next); UTLIST_RS(list); _ls_psize--;                      \
          } else if (cmp(_ls_p,_ls_q) <= 0) {                                                  \
            _ls_e = _ls_p; UTLIST_SV(_ls_p,list); _ls_p =                                      \
              UTLIST_NEXT(_ls_p,list,next); UTLIST_RS(list); _ls_psize--;                      \
          } else {                                                                             \
            _ls_e = _ls_q; UTLIST_SV(_ls_q,list); _ls_q =                                      \
              UTLIST_NEXT(_ls_q,list,next); UTLIST_RS(list); _ls_qsize--;                      \
          }                                                                                    \
          if (_ls_tail) {                                                                      \
            UTLIST_SV(_ls_tail,list); UTLIST_NEXTASGN(_ls_tail,list,_ls_e,next); UTLIST_RS(list); \
          } else {                                                                             \
            UTLIST_CASTASGN(list,_ls_e);                                                       \
          }                                                                                    \
          _ls_tail = _ls_e;                                                                    \
        }                                                                                      \
        _ls_p = _ls_q;                                                                         \
      }                                                                                        \
      if (_ls_tail) {                                                                          \
        UTLIST_SV(_ls_tail,list); UTLIST_NEXTASGN(_ls_tail,list,NULL,next); UTLIST_RS(list);   \
      }                                                                                        \
      if (_ls_nmerges <= 1) {                                                                  \
        _ls_looping=0;                                                                         \
      }                                                                                        \
      _ls_insize *= 2;                                                                         \
    }                                                                                          \
  }                                                                                            \
} while (0)


#define DL_SORT(list, cmp)                                                                     \
    DL_SORT2(list, cmp, prev, next)

#define DL_SORT2(list, cmp, prev, next)                                                        \
do {                                                                                           \
  LDECLTYPE(list) _ls_p;                                                                       \
  LDECLTYPE(list) _ls_q;                                                                       \
  LDECLTYPE(list) _ls_e;                                                                       \
  LDECLTYPE(list) _ls_tail;                                                                    \
  IF_NO_DECLTYPE(LDECLTYPE(list) _tmp;)                                                        \
  int _ls_insize, _ls_nmerges, _ls_psize, _ls_qsize, _ls_i, _ls_looping;                       \
  if (list) {                                                                                  \
    _ls_insize = 1;                                                                            \
    _ls_looping = 1;                                                                           \
    while (_ls_looping) {                                                                      \
      UTLIST_CASTASGN(_ls_p,list);                                                             \
      (list) = NULL;                                                                           \
      _ls_tail = NULL;                                                                         \
      _ls_nmerges = 0;                                                                         \
      while (_ls_p) {                                                                          \
        _ls_nmerges++;                                                                         \
        _ls_q = _ls_p;                                                                         \
        _ls_psize = 0;                                                                         \
        for (_ls_i = 0; _ls_i < _ls_insize; _ls_i++) {                                         \
          _ls_psize++;                                                                         \
          UTLIST_SV(_ls_q,list); _ls_q = UTLIST_NEXT(_ls_q,list,next); UTLIST_RS(list);        \
          if (!_ls_q) break;                                                                   \
        }                                                                                      \
        _ls_qsize = _ls_insize;                                                                \
        while ((_ls_psize > 0) || ((_ls_qsize > 0) && _ls_q)) {                                \
          if (_ls_psize == 0) {                                                                \
            _ls_e = _ls_q; UTLIST_SV(_ls_q,list); _ls_q =                                      \
              UTLIST_NEXT(_ls_q,list,next); UTLIST_RS(list); _ls_qsize--;                      \
          } else if ((_ls_qsize == 0) || (!_ls_q)) {                                           \
            _ls_e = _ls_p; UTLIST_SV(_ls_p,list); _ls_p =                                      \
              UTLIST_NEXT(_ls_p,list,next); UTLIST_RS(list); _ls_psize--;                      \
          } else if (cmp(_ls_p,_ls_q) <= 0) {                                                  \
            _ls_e = _ls_p; UTLIST_SV(_ls_p,list); _ls_p =                                      \
              UTLIST_NEXT(_ls_p,list,next); UTLIST_RS(list); _ls_psize--;                      \
          } else {                                                                             \
            _ls_e = _ls_q; UTLIST_SV(_ls_q,list); _ls_q =                                      \
              UTLIST_NEXT(_ls_q,list,next); UTLIST_RS(list); _ls_qsize--;                      \
          }                                                                                    \
          if (_ls_tail) {                                                                      \
            UTLIST_SV(_ls_tail,list); UTLIST_NEXTASGN(_ls_tail,list,_ls_e,next); UTLIST_RS(list); \
          } else {                                                                             \
            UTLIST_CASTASGN(list,_ls_e);                                                       \
          }                                                                                    \
          UTLIST_SV(_ls_e,list); UTLIST_PREVASGN(_ls_e,list,_ls_tail,prev); UTLIST_RS(list);   \
          _ls_tail = _ls_e;                                                                    \
        }                                                                                      \
        _ls_p = _ls_q;                                                                         \
      }                                                                                        \
      UTLIST_CASTASGN((list)->prev, _ls_tail);                                                 \
      UTLIST_SV(_ls_tail,list); UTLIST_NEXTASGN(_ls_tail,list,NULL,next); UTLIST_RS(list);     \
      if (_ls_nmerges <= 1) {                                                                  \
        _ls_looping=0;                                                                         \
      }                                                                                        \
      _ls_insize *= 2;                                                                         \
    }                                                                                          \
  }                                                                                            \
} while (0)

#define CDL_SORT(list, cmp)                                                                    \
    CDL_SORT2(list, cmp, prev, next)

#define CDL_SORT2(list, cmp, prev, next)                                                       \
do {                                                                                           \
  LDECLTYPE(list) _ls_p;                                                                       \
  LDECLTYPE(list) _ls_q;                                                                       \
  LDECLTYPE(list) _ls_e;                                                                       \
  LDECLTYPE(list) _ls_tail;                                                                    \
  LDECLTYPE(list) _ls_oldhead;                                                                 \
  LDECLTYPE(list) _tmp;                                                                        \
  int _ls_insize, _ls_nmerges, _ls_psize, _ls_qsize, _ls_i, _ls_looping;                       \
  if (list) {                                                                                  \
    _ls_insize = 1;                                                                            \
    _ls_looping = 1;                                                                           \
    while (_ls_looping) {                                                                      \
      UTLIST_CASTASGN(_ls_p,list);                                                             \
      UTLIST_CASTASGN(_ls_oldhead,list);                                                       \
      (list) = NULL;                                                                           \
      _ls_tail = NULL;                                                                         \
      _ls_nmerges = 0;                                                                         \
      while (_ls_p) {                                                                          \
        _ls_nmerges++;                                                                         \
        _ls_q = _ls_p;                                                                         \
        _ls_psize = 0;                                                                         \
        for (_ls_i = 0; _ls_i < _ls_insize; _ls_i++) {                                         \
          _ls_psize++;                                                                         \
          UTLIST_SV(_ls_q,list);                                                               \
          if (UTLIST_NEXT(_ls_q,list,next) == _ls_oldhead) {                                   \
            _ls_q = NULL;                                                                      \
          } else {                                                                             \
            _ls_q = UTLIST_NEXT(_ls_q,list,next);                                              \
          }                                                                                    \
          UTLIST_RS(list);                                                                     \
          if (!_ls_q) break;                                                                   \
        }                                                                                      \
        _ls_qsize = _ls_insize;                                                                \
        while (_ls_psize > 0 || (_ls_qsize > 0 && _ls_q)) {                                    \
          if (_ls_psize == 0) {                                                                \
            _ls_e = _ls_q; UTLIST_SV(_ls_q,list); _ls_q =                                      \
              UTLIST_NEXT(_ls_q,list,next); UTLIST_RS(list); _ls_qsize--;                      \
            if (_ls_q == _ls_oldhead) { _ls_q = NULL; }                                        \
          } else if (_ls_qsize == 0 || !_ls_q) {                                               \
            _ls_e = _ls_p; UTLIST_SV(_ls_p,list); _ls_p =                                      \
              UTLIST_NEXT(_ls_p,list,next); UTLIST_RS(list); _ls_psize--;                      \
            if (_ls_p == _ls_oldhead) { _ls_p = NULL; }                                        \
          } else if (cmp(_ls_p,_ls_q) <= 0) {                                                  \
            _ls_e = _ls_p; UTLIST_SV(_ls_p,list); _ls_p =                                      \
              UTLIST_NEXT(_ls_p,list,next); UTLIST_RS(list); _ls_psize--;                      \
            if (_ls_p == _ls_oldhead) { _ls_p = NULL; }                                        \
          } else {                                                                             \
            _ls_e = _ls_q; UTLIST_SV(_ls_q,list); _ls_q =                                      \
              UTLIST_NEXT(_ls_q,list,next); UTLIST_RS(list); _ls_qsize--;                      \
            if (_ls_q == _ls_oldhead) { _ls_q = NULL; }                                        \
          }                                                                                    \
          if (_ls_tail) {                                                                      \
            UTLIST_SV(_ls_tail,list); UTLIST_NEXTASGN(_ls_tail,list,_ls_e,next); UTLIST_RS(list); \
          } else {                                                                             \
            UTLIST_CASTASGN(list,_ls_e);                                                       \
          }                                                                                    \
          UTLIST_SV(_ls_e,list); UTLIST_PREVASGN(_ls_e,list,_ls_tail,prev); UTLIST_RS(list);   \
          _ls_tail = _ls_e;                                                                    \
        }                                                                                      \
        _ls_p = _ls_q;                                                                         \
      }                                                                                        \
      UTLIST_CASTASGN((list)->prev,_ls_tail);                                                  \
      UTLIST_CASTASGN(_tmp,list);                                                              \
      UTLIST_SV(_ls_tail,list); UTLIST_NEXTASGN(_ls_tail,list,_tmp,next); UTLIST_RS(list);     \
      if (_ls_nmerges <= 1) {                                                                  \
        _ls_looping=0;                                                                         \
      }                                                                                        \
      _ls_insize *= 2;                                                                         \
    }                                                                                          \
  }                                                                                            \
} while (0)

/******************************************************************************
 * 单链表宏（非圆形）*
 *****************************************************************************/
#define LL_PREPEND(head,add)                                                                   \
    LL_PREPEND2(head,add,next)

#define LL_PREPEND2(head,add,next)                                                             \
do {                                                                                           \
  (add)->next = (head);                                                                        \
  (head) = (add);                                                                              \
} while (0)

#define LL_CONCAT(head1,head2)                                                                 \
    LL_CONCAT2(head1,head2,next)

#define LL_CONCAT2(head1,head2,next)                                                           \
do {                                                                                           \
  LDECLTYPE(head1) _tmp;                                                                       \
  if (head1) {                                                                                 \
    _tmp = (head1);                                                                            \
    while (_tmp->next) { _tmp = _tmp->next; }                                                  \
    _tmp->next=(head2);                                                                        \
  } else {                                                                                     \
    (head1)=(head2);                                                                           \
  }                                                                                            \
} while (0)

#define LL_APPEND(head,add)                                                                    \
    LL_APPEND2(head,add,next)

#define LL_APPEND2(head,add,next)                                                              \
do {                                                                                           \
  LDECLTYPE(head) _tmp;                                                                        \
  (add)->next=NULL;                                                                            \
  if (head) {                                                                                  \
    _tmp = (head);                                                                             \
    while (_tmp->next) { _tmp = _tmp->next; }                                                  \
    _tmp->next=(add);                                                                          \
  } else {                                                                                     \
    (head)=(add);                                                                              \
  }                                                                                            \
} while (0)

#define LL_INSERT_INORDER(head,add,cmp)                                                        \
    LL_INSERT_INORDER2(head,add,cmp,next)

#define LL_INSERT_INORDER2(head,add,cmp,next)                                                  \
do {                                                                                           \
  LDECLTYPE(head) _tmp;                                                                        \
  if (head) {                                                                                  \
    LL_LOWER_BOUND2(head, _tmp, add, cmp, next);                                               \
    LL_APPEND_ELEM2(head, _tmp, add, next);                                                    \
  } else {                                                                                     \
    (head) = (add);                                                                            \
    (head)->next = NULL;                                                                       \
  }                                                                                            \
} while (0)

#define LL_LOWER_BOUND(head,elt,like,cmp)                                                      \
    LL_LOWER_BOUND2(head,elt,like,cmp,next)

#define LL_LOWER_BOUND2(head,elt,like,cmp,next)                                                \
  do {                                                                                         \
    if ((head) == NULL || (cmp(head, like)) >= 0) {                                            \
      (elt) = NULL;                                                                            \
    } else {                                                                                   \
      for ((elt) = (head); (elt)->next != NULL; (elt) = (elt)->next) {                         \
        if (cmp((elt)->next, like) >= 0) {                                                     \
          break;                                                                               \
        }                                                                                      \
      }                                                                                        \
    }                                                                                          \
  } while (0)

#define LL_DELETE(head,del)                                                                    \
    LL_DELETE2(head,del,next)

#define LL_DELETE2(head,del,next)                                                              \
do {                                                                                           \
  LDECLTYPE(head) _tmp;                                                                        \
  if ((head) == (del)) {                                                                       \
    (head)=(head)->next;                                                                       \
  } else {                                                                                     \
    _tmp = (head);                                                                             \
    while (_tmp->next && (_tmp->next != (del))) {                                              \
      _tmp = _tmp->next;                                                                       \
    }                                                                                          \
    if (_tmp->next) {                                                                          \
      _tmp->next = (del)->next;                                                                \
    }                                                                                          \
  }                                                                                            \
} while (0)

#define LL_COUNT(head,el,counter)                                                              \
    LL_COUNT2(head,el,counter,next)                                                            \

#define LL_COUNT2(head,el,counter,next)                                                        \
do {                                                                                           \
  (counter) = 0;                                                                               \
  LL_FOREACH2(head,el,next) { ++(counter); }                                                   \
} while (0)

#define LL_FOREACH(head,el)                                                                    \
    LL_FOREACH2(head,el,next)

#define LL_FOREACH2(head,el,next)                                                              \
    for ((el) = (head); el; (el) = (el)->next)

#define LL_FOREACH_SAFE(head,el,tmp)                                                           \
    LL_FOREACH_SAFE2(head,el,tmp,next)

#define LL_FOREACH_SAFE2(head,el,tmp,next)                                                     \
  for ((el) = (head); (el) && ((tmp) = (el)->next, 1); (el) = (tmp))

#define LL_SEARCH_SCALAR(head,out,field,val)                                                   \
    LL_SEARCH_SCALAR2(head,out,field,val,next)

#define LL_SEARCH_SCALAR2(head,out,field,val,next)                                             \
do {                                                                                           \
    LL_FOREACH2(head,out,next) {                                                               \
      if ((out)->field == (val)) break;                                                        \
    }                                                                                          \
} while (0)

#define LL_SEARCH(head,out,elt,cmp)                                                            \
    LL_SEARCH2(head,out,elt,cmp,next)

#define LL_SEARCH2(head,out,elt,cmp,next)                                                      \
do {                                                                                           \
    LL_FOREACH2(head,out,next) {                                                               \
      if ((cmp(out,elt))==0) break;                                                            \
    }                                                                                          \
} while (0)

#define LL_REPLACE_ELEM2(head, el, add, next)                                                  \
do {                                                                                           \
 LDECLTYPE(head) _tmp;                                                                         \
 assert((head) != NULL);                                                                       \
 assert((el) != NULL);                                                                         \
 assert((add) != NULL);                                                                        \
 (add)->next = (el)->next;                                                                     \
 if ((head) == (el)) {                                                                         \
  (head) = (add);                                                                              \
 } else {                                                                                      \
  _tmp = (head);                                                                               \
  while (_tmp->next && (_tmp->next != (el))) {                                                 \
   _tmp = _tmp->next;                                                                          \
  }                                                                                            \
  if (_tmp->next) {                                                                            \
    _tmp->next = (add);                                                                        \
  }                                                                                            \
 }                                                                                             \
} while (0)

#define LL_REPLACE_ELEM(head, el, add)                                                         \
    LL_REPLACE_ELEM2(head, el, add, next)

#define LL_PREPEND_ELEM2(head, el, add, next)                                                  \
do {                                                                                           \
 if (el) {                                                                                     \
  LDECLTYPE(head) _tmp;                                                                        \
  assert((head) != NULL);                                                                      \
  assert((add) != NULL);                                                                       \
  (add)->next = (el);                                                                          \
  if ((head) == (el)) {                                                                        \
   (head) = (add);                                                                             \
  } else {                                                                                     \
   _tmp = (head);                                                                              \
   while (_tmp->next && (_tmp->next != (el))) {                                                \
    _tmp = _tmp->next;                                                                         \
   }                                                                                           \
   if (_tmp->next) {                                                                           \
     _tmp->next = (add);                                                                       \
   }                                                                                           \
  }                                                                                            \
 } else {                                                                                      \
  LL_APPEND2(head, add, next);                                                                 \
 }                                                                                             \
} while (0)                                                                                    \

#define LL_PREPEND_ELEM(head, el, add)                                                         \
    LL_PREPEND_ELEM2(head, el, add, next)

#define LL_APPEND_ELEM2(head, el, add, next)                                                   \
do {                                                                                           \
 if (el) {                                                                                     \
  assert((head) != NULL);                                                                      \
  assert((add) != NULL);                                                                       \
  (add)->next = (el)->next;                                                                    \
  (el)->next = (add);                                                                          \
 } else {                                                                                      \
  LL_PREPEND2(head, add, next);                                                                \
 }                                                                                             \
} while (0)                                                                                    \

#define LL_APPEND_ELEM(head, el, add)                                                          \
    LL_APPEND_ELEM2(head, el, add, next)

#ifdef NO_DECLTYPE
/* 以下是一些函数的VS2008/NO_DECLTYPE替换*/

#undef LL_CONCAT2
#define LL_CONCAT2(head1,head2,next)                                                           \
do {                                                                                           \
  char *_tmp;                                                                                  \
  if (head1) {                                                                                 \
    _tmp = (char*)(head1);                                                                     \
    while ((head1)->next) { (head1) = (head1)->next; }                                         \
    (head1)->next = (head2);                                                                   \
    UTLIST_RS(head1);                                                                          \
  } else {                                                                                     \
    (head1)=(head2);                                                                           \
  }                                                                                            \
} while (0)

#undef LL_APPEND2
#define LL_APPEND2(head,add,next)                                                              \
do {                                                                                           \
  if (head) {                                                                                  \
    (add)->next = head;     /* 使用add->next作为临时变量*/                             \
    while ((add)->next->next) { (add)->next = (add)->next->next; }                             \
    (add)->next->next=(add);                                                                   \
  } else {                                                                                     \
    (head)=(add);                                                                              \
  }                                                                                            \
  (add)->next=NULL;                                                                            \
} while (0)

#undef LL_INSERT_INORDER2
#define LL_INSERT_INORDER2(head,add,cmp,next)                                                  \
do {                                                                                           \
  if ((head) == NULL || (cmp(head, add)) >= 0) {                                               \
    (add)->next = (head);                                                                      \
    (head) = (add);                                                                            \
  } else {                                                                                     \
    char *_tmp = (char*)(head);                                                                \
    while ((head)->next != NULL && (cmp((head)->next, add)) < 0) {                             \
      (head) = (head)->next;                                                                   \
    }                                                                                          \
    (add)->next = (head)->next;                                                                \
    (head)->next = (add);                                                                      \
    UTLIST_RS(head);                                                                           \
  }                                                                                            \
} while (0)

#undef LL_DELETE2
#define LL_DELETE2(head,del,next)                                                              \
do {                                                                                           \
  if ((head) == (del)) {                                                                       \
    (head)=(head)->next;                                                                       \
  } else {                                                                                     \
    char *_tmp = (char*)(head);                                                                \
    while ((head)->next && ((head)->next != (del))) {                                          \
      (head) = (head)->next;                                                                   \
    }                                                                                          \
    if ((head)->next) {                                                                        \
      (head)->next = ((del)->next);                                                            \
    }                                                                                          \
    UTLIST_RS(head);                                                                           \
  }                                                                                            \
} while (0)

#undef LL_REPLACE_ELEM2
#define LL_REPLACE_ELEM2(head, el, add, next)                                                  \
do {                                                                                           \
  assert((head) != NULL);                                                                      \
  assert((el) != NULL);                                                                        \
  assert((add) != NULL);                                                                       \
  if ((head) == (el)) {                                                                        \
    (head) = (add);                                                                            \
  } else {                                                                                     \
    (add)->next = head;                                                                        \
    while ((add)->next->next && ((add)->next->next != (el))) {                                 \
      (add)->next = (add)->next->next;                                                         \
    }                                                                                          \
    if ((add)->next->next) {                                                                   \
      (add)->next->next = (add);                                                               \
    }                                                                                          \
  }                                                                                            \
  (add)->next = (el)->next;                                                                    \
} while (0)

#undef LL_PREPEND_ELEM2
#define LL_PREPEND_ELEM2(head, el, add, next)                                                  \
do {                                                                                           \
  if (el) {                                                                                    \
    assert((head) != NULL);                                                                    \
    assert((add) != NULL);                                                                     \
    if ((head) == (el)) {                                                                      \
      (head) = (add);                                                                          \
    } else {                                                                                   \
      (add)->next = (head);                                                                    \
      while ((add)->next->next && ((add)->next->next != (el))) {                               \
        (add)->next = (add)->next->next;                                                       \
      }                                                                                        \
      if ((add)->next->next) {                                                                 \
        (add)->next->next = (add);                                                             \
      }                                                                                        \
    }                                                                                          \
    (add)->next = (el);                                                                        \
  } else {                                                                                     \
    LL_APPEND2(head, add, next);                                                               \
  }                                                                                            \
} while (0)                                                                                    \

#endif /* NO_DECLTYPE */

/******************************************************************************
 * 双链接列表宏（非圆形）*
 *****************************************************************************/
#define DL_PREPEND(head,add)                                                                   \
    DL_PREPEND2(head,add,prev,next)

#define DL_PREPEND2(head,add,prev,next)                                                        \
do {                                                                                           \
 (add)->next = (head);                                                                         \
 if (head) {                                                                                   \
   (add)->prev = (head)->prev;                                                                 \
   (head)->prev = (add);                                                                       \
 } else {                                                                                      \
   (add)->prev = (add);                                                                        \
 }                                                                                             \
 (head) = (add);                                                                               \
} while (0)

#define DL_APPEND(head,add)                                                                    \
    DL_APPEND2(head,add,prev,next)

#define DL_APPEND2(head,add,prev,next)                                                         \
do {                                                                                           \
  if (head) {                                                                                  \
      (add)->prev = (head)->prev;                                                              \
      (head)->prev->next = (add);                                                              \
      (head)->prev = (add);                                                                    \
      (add)->next = NULL;                                                                      \
  } else {                                                                                     \
      (head)=(add);                                                                            \
      (head)->prev = (head);                                                                   \
      (head)->next = NULL;                                                                     \
  }                                                                                            \
} while (0)

#define DL_INSERT_INORDER(head,add,cmp)                                                        \
    DL_INSERT_INORDER2(head,add,cmp,prev,next)

#define DL_INSERT_INORDER2(head,add,cmp,prev,next)                                             \
do {                                                                                           \
  LDECLTYPE(head) _tmp;                                                                        \
  if (head) {                                                                                  \
    DL_LOWER_BOUND2(head, _tmp, add, cmp, next);                                               \
    DL_APPEND_ELEM2(head, _tmp, add, prev, next);                                              \
  } else {                                                                                     \
    (head) = (add);                                                                            \
    (head)->prev = (head);                                                                     \
    (head)->next = NULL;                                                                       \
  }                                                                                            \
} while (0)

#define DL_LOWER_BOUND(head,elt,like,cmp)                                                      \
    DL_LOWER_BOUND2(head,elt,like,cmp,next)

#define DL_LOWER_BOUND2(head,elt,like,cmp,next)                                                \
do {                                                                                           \
  if ((head) == NULL || (cmp(head, like)) >= 0) {                                              \
    (elt) = NULL;                                                                              \
  } else {                                                                                     \
    for ((elt) = (head); (elt)->next != NULL; (elt) = (elt)->next) {                           \
      if ((cmp((elt)->next, like)) >= 0) {                                                     \
        break;                                                                                 \
      }                                                                                        \
    }                                                                                          \
  }                                                                                            \
} while (0)

#define DL_CONCAT(head1,head2)                                                                 \
    DL_CONCAT2(head1,head2,prev,next)

#define DL_CONCAT2(head1,head2,prev,next)                                                      \
do {                                                                                           \
  LDECLTYPE(head1) _tmp;                                                                       \
  if (head2) {                                                                                 \
    if (head1) {                                                                               \
        UTLIST_CASTASGN(_tmp, (head2)->prev);                                                  \
        (head2)->prev = (head1)->prev;                                                         \
        (head1)->prev->next = (head2);                                                         \
        UTLIST_CASTASGN((head1)->prev, _tmp);                                                  \
    } else {                                                                                   \
        (head1)=(head2);                                                                       \
    }                                                                                          \
  }                                                                                            \
} while (0)

#define DL_DELETE(head,del)                                                                    \
    DL_DELETE2(head,del,prev,next)

#define DL_DELETE2(head,del,prev,next)                                                         \
do {                                                                                           \
  assert((head) != NULL);                                                                      \
  assert((del)->prev != NULL);                                                                 \
  if ((del)->prev == (del)) {                                                                  \
      (head)=NULL;                                                                             \
  } else if ((del)==(head)) {                                                                  \
      (del)->next->prev = (del)->prev;                                                         \
      (head) = (del)->next;                                                                    \
  } else {                                                                                     \
      (del)->prev->next = (del)->next;                                                         \
      if ((del)->next) {                                                                       \
          (del)->next->prev = (del)->prev;                                                     \
      } else {                                                                                 \
          (head)->prev = (del)->prev;                                                          \
      }                                                                                        \
  }                                                                                            \
} while (0)

#define DL_COUNT(head,el,counter)                                                              \
    DL_COUNT2(head,el,counter,next)                                                            \

#define DL_COUNT2(head,el,counter,next)                                                        \
do {                                                                                           \
  (counter) = 0;                                                                               \
  DL_FOREACH2(head,el,next) { ++(counter); }                                                   \
} while (0)

#define DL_FOREACH(head,el)                                                                    \
    DL_FOREACH2(head,el,next)

#define DL_FOREACH2(head,el,next)                                                              \
    for ((el) = (head); el; (el) = (el)->next)

/* 这个版本对于在迭代期间删除元素是安全的*/
#define DL_FOREACH_SAFE(head,el,tmp)                                                           \
    DL_FOREACH_SAFE2(head,el,tmp,next)

#define DL_FOREACH_SAFE2(head,el,tmp,next)                                                     \
  for ((el) = (head); (el) && ((tmp) = (el)->next, 1); (el) = (tmp))

/* 这些与它们的单链接列表相同*/
#define DL_SEARCH_SCALAR LL_SEARCH_SCALAR
#define DL_SEARCH LL_SEARCH
#define DL_SEARCH_SCALAR2 LL_SEARCH_SCALAR2
#define DL_SEARCH2 LL_SEARCH2

#define DL_REPLACE_ELEM2(head, el, add, prev, next)                                            \
do {                                                                                           \
 assert((head) != NULL);                                                                       \
 assert((el) != NULL);                                                                         \
 assert((add) != NULL);                                                                        \
 if ((head) == (el)) {                                                                         \
  (head) = (add);                                                                              \
  (add)->next = (el)->next;                                                                    \
  if ((el)->next == NULL) {                                                                    \
   (add)->prev = (add);                                                                        \
  } else {                                                                                     \
   (add)->prev = (el)->prev;                                                                   \
   (add)->next->prev = (add);                                                                  \
  }                                                                                            \
 } else {                                                                                      \
  (add)->next = (el)->next;                                                                    \
  (add)->prev = (el)->prev;                                                                    \
  (add)->prev->next = (add);                                                                   \
  if ((el)->next == NULL) {                                                                    \
   (head)->prev = (add);                                                                       \
  } else {                                                                                     \
   (add)->next->prev = (add);                                                                  \
  }                                                                                            \
 }                                                                                             \
} while (0)

#define DL_REPLACE_ELEM(head, el, add)                                                         \
    DL_REPLACE_ELEM2(head, el, add, prev, next)

#define DL_PREPEND_ELEM2(head, el, add, prev, next)                                            \
do {                                                                                           \
 if (el) {                                                                                     \
  assert((head) != NULL);                                                                      \
  assert((add) != NULL);                                                                       \
  (add)->next = (el);                                                                          \
  (add)->prev = (el)->prev;                                                                    \
  (el)->prev = (add);                                                                          \
  if ((head) == (el)) {                                                                        \
   (head) = (add);                                                                             \
  } else {                                                                                     \
   (add)->prev->next = (add);                                                                  \
  }                                                                                            \
 } else {                                                                                      \
  DL_APPEND2(head, add, prev, next);                                                           \
 }                                                                                             \
} while (0)                                                                                    \

#define DL_PREPEND_ELEM(head, el, add)                                                         \
    DL_PREPEND_ELEM2(head, el, add, prev, next)

#define DL_APPEND_ELEM2(head, el, add, prev, next)                                             \
do {                                                                                           \
 if (el) {                                                                                     \
  assert((head) != NULL);                                                                      \
  assert((add) != NULL);                                                                       \
  (add)->next = (el)->next;                                                                    \
  (add)->prev = (el);                                                                          \
  (el)->next = (add);                                                                          \
  if ((add)->next) {                                                                           \
   (add)->next->prev = (add);                                                                  \
  } else {                                                                                     \
   (head)->prev = (add);                                                                       \
  }                                                                                            \
 } else {                                                                                      \
  DL_PREPEND2(head, add, prev, next);                                                          \
 }                                                                                             \
} while (0)                                                                                    \

#define DL_APPEND_ELEM(head, el, add)                                                          \
   DL_APPEND_ELEM2(head, el, add, prev, next)

#ifdef NO_DECLTYPE
/* 以下是一些函数的VS2008/NO_DECLTYPE替换*/

#undef DL_INSERT_INORDER2
#define DL_INSERT_INORDER2(head,add,cmp,prev,next)                                             \
do {                                                                                           \
  if ((head) == NULL) {                                                                        \
    (add)->prev = (add);                                                                       \
    (add)->next = NULL;                                                                        \
    (head) = (add);                                                                            \
  } else if ((cmp(head, add)) >= 0) {                                                          \
    (add)->prev = (head)->prev;                                                                \
    (add)->next = (head);                                                                      \
    (head)->prev = (add);                                                                      \
    (head) = (add);                                                                            \
  } else {                                                                                     \
    char *_tmp = (char*)(head);                                                                \
    while ((head)->next && (cmp((head)->next, add)) < 0) {                                     \
      (head) = (head)->next;                                                                   \
    }                                                                                          \
    (add)->prev = (head);                                                                      \
    (add)->next = (head)->next;                                                                \
    (head)->next = (add);                                                                      \
    UTLIST_RS(head);                                                                           \
    if ((add)->next) {                                                                         \
      (add)->next->prev = (add);                                                               \
    } else {                                                                                   \
      (head)->prev = (add);                                                                    \
    }                                                                                          \
  }                                                                                            \
} while (0)
#endif /* NO_DECLTYPE */

/******************************************************************************
 * 循环双链接列表宏*
 *****************************************************************************/
#define CDL_APPEND(head,add)                                                                   \
    CDL_APPEND2(head,add,prev,next)

#define CDL_APPEND2(head,add,prev,next)                                                        \
do {                                                                                           \
 if (head) {                                                                                   \
   (add)->prev = (head)->prev;                                                                 \
   (add)->next = (head);                                                                       \
   (head)->prev = (add);                                                                       \
   (add)->prev->next = (add);                                                                  \
 } else {                                                                                      \
   (add)->prev = (add);                                                                        \
   (add)->next = (add);                                                                        \
   (head) = (add);                                                                             \
 }                                                                                             \
} while (0)

#define CDL_PREPEND(head,add)                                                                  \
    CDL_PREPEND2(head,add,prev,next)

#define CDL_PREPEND2(head,add,prev,next)                                                       \
do {                                                                                           \
 if (head) {                                                                                   \
   (add)->prev = (head)->prev;                                                                 \
   (add)->next = (head);                                                                       \
   (head)->prev = (add);                                                                       \
   (add)->prev->next = (add);                                                                  \
 } else {                                                                                      \
   (add)->prev = (add);                                                                        \
   (add)->next = (add);                                                                        \
 }                                                                                             \
 (head) = (add);                                                                               \
} while (0)

#define CDL_INSERT_INORDER(head,add,cmp)                                                       \
    CDL_INSERT_INORDER2(head,add,cmp,prev,next)

#define CDL_INSERT_INORDER2(head,add,cmp,prev,next)                                            \
do {                                                                                           \
  LDECLTYPE(head) _tmp;                                                                        \
  if (head) {                                                                                  \
    CDL_LOWER_BOUND2(head, _tmp, add, cmp, next);                                              \
    CDL_APPEND_ELEM2(head, _tmp, add, prev, next);                                             \
  } else {                                                                                     \
    (head) = (add);                                                                            \
    (head)->next = (head);                                                                     \
    (head)->prev = (head);                                                                     \
  }                                                                                            \
} while (0)

#define CDL_LOWER_BOUND(head,elt,like,cmp)                                                     \
    CDL_LOWER_BOUND2(head,elt,like,cmp,next)

#define CDL_LOWER_BOUND2(head,elt,like,cmp,next)                                               \
do {                                                                                           \
  if ((head) == NULL || (cmp(head, like)) >= 0) {                                              \
    (elt) = NULL;                                                                              \
  } else {                                                                                     \
    for ((elt) = (head); (elt)->next != (head); (elt) = (elt)->next) {                         \
      if ((cmp((elt)->next, like)) >= 0) {                                                     \
        break;                                                                                 \
      }                                                                                        \
    }                                                                                          \
  }                                                                                            \
} while (0)

#define CDL_DELETE(head,del)                                                                   \
    CDL_DELETE2(head,del,prev,next)

#define CDL_DELETE2(head,del,prev,next)                                                        \
do {                                                                                           \
  if (((head)==(del)) && ((head)->next == (head))) {                                           \
      (head) = NULL;                                                                           \
  } else {                                                                                     \
     (del)->next->prev = (del)->prev;                                                          \
     (del)->prev->next = (del)->next;                                                          \
     if ((del) == (head)) (head)=(del)->next;                                                  \
  }                                                                                            \
} while (0)

#define CDL_COUNT(head,el,counter)                                                             \
    CDL_COUNT2(head,el,counter,next)                                                           \

#define CDL_COUNT2(head, el, counter,next)                                                     \
do {                                                                                           \
  (counter) = 0;                                                                               \
  CDL_FOREACH2(head,el,next) { ++(counter); }                                                  \
} while (0)

#define CDL_FOREACH(head,el)                                                                   \
    CDL_FOREACH2(head,el,next)

#define CDL_FOREACH2(head,el,next)                                                             \
    for ((el)=(head);el;(el)=(((el)->next==(head)) ? NULL : (el)->next))

#define CDL_FOREACH_SAFE(head,el,tmp1,tmp2)                                                    \
    CDL_FOREACH_SAFE2(head,el,tmp1,tmp2,prev,next)

#define CDL_FOREACH_SAFE2(head,el,tmp1,tmp2,prev,next)                                         \
  for ((el) = (head), (tmp1) = (head) ? (head)->prev : NULL;                                   \
       (el) && ((tmp2) = (el)->next, 1);                                                       \
       (el) = ((el) == (tmp1) ? NULL : (tmp2)))

#define CDL_SEARCH_SCALAR(head,out,field,val)                                                  \
    CDL_SEARCH_SCALAR2(head,out,field,val,next)

#define CDL_SEARCH_SCALAR2(head,out,field,val,next)                                            \
do {                                                                                           \
    CDL_FOREACH2(head,out,next) {                                                              \
      if ((out)->field == (val)) break;                                                        \
    }                                                                                          \
} while (0)

#define CDL_SEARCH(head,out,elt,cmp)                                                           \
    CDL_SEARCH2(head,out,elt,cmp,next)

#define CDL_SEARCH2(head,out,elt,cmp,next)                                                     \
do {                                                                                           \
    CDL_FOREACH2(head,out,next) {                                                              \
      if ((cmp(out,elt))==0) break;                                                            \
    }                                                                                          \
} while (0)

#define CDL_REPLACE_ELEM2(head, el, add, prev, next)                                           \
do {                                                                                           \
 assert((head) != NULL);                                                                       \
 assert((el) != NULL);                                                                         \
 assert((add) != NULL);                                                                        \
 if ((el)->next == (el)) {                                                                     \
  (add)->next = (add);                                                                         \
  (add)->prev = (add);                                                                         \
  (head) = (add);                                                                              \
 } else {                                                                                      \
  (add)->next = (el)->next;                                                                    \
  (add)->prev = (el)->prev;                                                                    \
  (add)->next->prev = (add);                                                                   \
  (add)->prev->next = (add);                                                                   \
  if ((head) == (el)) {                                                                        \
   (head) = (add);                                                                             \
  }                                                                                            \
 }                                                                                             \
} while (0)

#define CDL_REPLACE_ELEM(head, el, add)                                                        \
    CDL_REPLACE_ELEM2(head, el, add, prev, next)

#define CDL_PREPEND_ELEM2(head, el, add, prev, next)                                           \
do {                                                                                           \
  if (el) {                                                                                    \
    assert((head) != NULL);                                                                    \
    assert((add) != NULL);                                                                     \
    (add)->next = (el);                                                                        \
    (add)->prev = (el)->prev;                                                                  \
    (el)->prev = (add);                                                                        \
    (add)->prev->next = (add);                                                                 \
    if ((head) == (el)) {                                                                      \
      (head) = (add);                                                                          \
    }                                                                                          \
  } else {                                                                                     \
    CDL_APPEND2(head, add, prev, next);                                                        \
  }                                                                                            \
} while (0)

#define CDL_PREPEND_ELEM(head, el, add)                                                        \
    CDL_PREPEND_ELEM2(head, el, add, prev, next)

#define CDL_APPEND_ELEM2(head, el, add, prev, next)                                            \
do {                                                                                           \
 if (el) {                                                                                     \
  assert((head) != NULL);                                                                      \
  assert((add) != NULL);                                                                       \
  (add)->next = (el)->next;                                                                    \
  (add)->prev = (el);                                                                          \
  (el)->next = (add);                                                                          \
  (add)->next->prev = (add);                                                                   \
 } else {                                                                                      \
  CDL_PREPEND2(head, add, prev, next);                                                         \
 }                                                                                             \
} while (0)

#define CDL_APPEND_ELEM(head, el, add)                                                         \
    CDL_APPEND_ELEM2(head, el, add, prev, next)

#ifdef NO_DECLTYPE
/* 以下是一些函数的VS2008/NO_DECLTYPE替换*/

#undef CDL_INSERT_INORDER2
#define CDL_INSERT_INORDER2(head,add,cmp,prev,next)                                            \
do {                                                                                           \
  if ((head) == NULL) {                                                                        \
    (add)->prev = (add);                                                                       \
    (add)->next = (add);                                                                       \
    (head) = (add);                                                                            \
  } else if ((cmp(head, add)) >= 0) {                                                          \
    (add)->prev = (head)->prev;                                                                \
    (add)->next = (head);                                                                      \
    (add)->prev->next = (add);                                                                 \
    (head)->prev = (add);                                                                      \
    (head) = (add);                                                                            \
  } else {                                                                                     \
    char *_tmp = (char*)(head);                                                                \
    while ((char*)(head)->next != _tmp && (cmp((head)->next, add)) < 0) {                      \
      (head) = (head)->next;                                                                   \
    }                                                                                          \
    (add)->prev = (head);                                                                      \
    (add)->next = (head)->next;                                                                \
    (add)->next->prev = (add);                                                                 \
    (head)->next = (add);                                                                      \
    UTLIST_RS(head);                                                                           \
  }                                                                                            \
} while (0)
#endif /* NO_DECLTYPE */

#endif /* UTLIST_H */

