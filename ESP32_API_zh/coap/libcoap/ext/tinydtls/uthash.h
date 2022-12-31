/*
版权所有（c）2003-2017，Troy D.Hansonhttp://troydhanson.github.com/uthash/All版权所有。

在满足以下条件的情况下，允许以源和二进制形式重新分发和使用，无论是否进行修改：

    * 源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "ASIS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITEDTO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR APARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNEROR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, ORPROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OFLIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDINGNEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THISSOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef UTHASH_H
#define UTHASH_H

#define UTHASH_VERSION 2.0.2

#include <string.h>   /* memcmp、memset、strlen*/
#include <stddef.h>   /* 指针diff_t*/
#include <stdlib.h>   /* 出口*/

/* 这些宏使用decltype或GNU扩展的早期__type。由于decltype仅在较新的编译器（编译c++源代码时为VS2010或gcc 4.3+）中可用，因此该代码使用所需的任何方法，或者对于VS2008（两者都不可用），使用强制转换解决方案。*/
#if !defined(DECLTYPE) && !defined(NO_DECLTYPE)
#if defined(_MSC_VER)   /* MS编译器*/
#if _MSC_VER >= 1600 && defined(__cplusplus)  /* C++模式下的VS2010或更高版本*/
#define DECLTYPE(x) (decltype(x))
#else                   /* VS2008或更高版本（或C模式下的VS2010）*/
#define NO_DECLTYPE
#endif
#elif defined(__BORLANDC__) || defined(__ICCARM__) || defined(__LCC__) || defined(__WATCOMC__)
#define NO_DECLTYPE
#else                   /* GNU、Sun和其他编译器*/
#define DECLTYPE(x) (__typeof(x))
#endif
#endif

#ifdef NO_DECLTYPE
#define DECLTYPE(x)
#define DECLTYPE_ASSIGN(dst,src)                                                 \
do {                                                                             \
  char **_da_dst = (char**)(&(dst));                                             \
  *_da_dst = (char*)(src);                                                       \
} while (0)
#else
#define DECLTYPE_ASSIGN(dst,src)                                                 \
do {                                                                             \
  (dst) = DECLTYPE(dst)(src);                                                    \
} while (0)
#endif

/* 许多哈希函数使用uint32_t，这在Pre-VS2010中没有定义*/
#if defined(_WIN32)
#if defined(_MSC_VER) && _MSC_VER >= 1600
#include <stdint.h>
#elif defined(__WATCOMC__) || defined(__MINGW32__) || defined(__CYGWIN__)
#include <stdint.h>
#else
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
#endif
#elif defined(__GNUC__) && !defined(__VXWORKS__)
#include <stdint.h>
#else
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
#endif

#ifndef uthash_malloc
#define uthash_malloc(sz) malloc(sz)      /* 马洛克fcn*/
#endif
#ifndef uthash_free
#define uthash_free(ptr,sz) free(ptr)     /* 自由fcn*/
#endif
#ifndef uthash_bzero
#define uthash_bzero(a,n) memset(a,'\0',n)
#endif
#ifndef uthash_memcmp
#define uthash_memcmp(a,b,n) memcmp(a,b,n)
#endif
#ifndef uthash_strlen
#define uthash_strlen(s) strlen(s)
#endif

#ifndef uthash_noexpand_fyi
#define uthash_noexpand_fyi(tbl)          /* 可以定义为记录noexpnd*/
#endif
#ifndef uthash_expand_fyi
#define uthash_expand_fyi(tbl)            /* 可以定义为日志扩展*/
#endif

#ifndef HASH_NONFATAL_OOM
#define HASH_NONFATAL_OOM 0
#endif

#if HASH_NONFATAL_OOM
/* malloc故障可以从*/

#ifndef uthash_nonfatal_oom
#define uthash_nonfatal_oom(obj) do {} while (0)    /* 非致命OOM错误*/
#endif

#define HASH_RECORD_OOM(oomed) do { (oomed) = 1; } while (0)
#define IF_HASH_NONFATAL_OOM(x) x

#else
/* malloc失败导致内存丢失，哈希表不可用*/

#ifndef uthash_fatal
#define uthash_fatal(msg) exit(-1)        /* 严重OOM错误*/
#endif

#define HASH_RECORD_OOM(oomed) uthash_fatal("out of memory")
#define IF_HASH_NONFATAL_OOM(x)

#endif

/* 桶的初始数量*/
#define HASH_INITIAL_NUM_BUCKETS 32U     /* 桶的初始数量*/
#define HASH_INITIAL_NUM_BUCKETS_LOG2 5U /* 初始桶数的lg2*/
#define HASH_BKT_CAPACITY_THRESH 10U     /* 当桶计数达到时展开*/

/* 计算哈希句柄地址为hhp的元素*/
#define ELMT_FROM_HH(tbl,hhp) ((void*)(((char*)(hhp)) - ((tbl)->hho)))
/* 根据元素地址elp计算哈希句柄*/
#define HH_FROM_ELMT(tbl,elp) ((UT_hash_handle *)(((char*)(elp)) + ((tbl)->hho)))

#define HASH_ROLLBACK_BKT(hh, head, itemptrhh)                                   \
do {                                                                             \
  struct UT_hash_handle *_hd_hh_item = (itemptrhh);                              \
  unsigned _hd_bkt;                                                              \
  HASH_TO_BKT(_hd_hh_item->hashv, (head)->hh.tbl->num_buckets, _hd_bkt);         \
  (head)->hh.tbl->buckets[_hd_bkt].count++;                                      \
  _hd_hh_item->hh_next = NULL;                                                   \
  _hd_hh_item->hh_prev = NULL;                                                   \
} while (0)

#define HASH_VALUE(keyptr,keylen,hashv)                                          \
do {                                                                             \
  HASH_FCN(keyptr, keylen, hashv);                                               \
} while (0)

#define HASH_FIND_BYHASHVALUE(hh,head,keyptr,keylen,hashval,out)                 \
do {                                                                             \
  (out) = NULL;                                                                  \
  if (head) {                                                                    \
    unsigned _hf_bkt;                                                            \
    HASH_TO_BKT(hashval, (head)->hh.tbl->num_buckets, _hf_bkt);                  \
    if (HASH_BLOOM_TEST((head)->hh.tbl, hashval) != 0) {                         \
      HASH_FIND_IN_BKT((head)->hh.tbl, hh, (head)->hh.tbl->buckets[ _hf_bkt ], keyptr, keylen, hashval, out); \
    }                                                                            \
  }                                                                              \
} while (0)

#define HASH_FIND(hh,head,keyptr,keylen,out)                                     \
do {                                                                             \
  unsigned _hf_hashv;                                                            \
  HASH_VALUE(keyptr, keylen, _hf_hashv);                                         \
  HASH_FIND_BYHASHVALUE(hh, head, keyptr, keylen, _hf_hashv, out);               \
} while (0)

#ifdef HASH_BLOOM
#define HASH_BLOOM_BITLEN (1UL << HASH_BLOOM)
#define HASH_BLOOM_BYTELEN (HASH_BLOOM_BITLEN/8UL) + (((HASH_BLOOM_BITLEN%8UL)!=0UL) ? 1UL : 0UL)
#define HASH_BLOOM_MAKE(tbl,oomed)                                               \
do {                                                                             \
  (tbl)->bloom_nbits = HASH_BLOOM;                                               \
  (tbl)->bloom_bv = (uint8_t*)uthash_malloc(HASH_BLOOM_BYTELEN);                 \
  if (!(tbl)->bloom_bv) {                                                        \
    HASH_RECORD_OOM(oomed);                                                      \
  } else {                                                                       \
    uthash_bzero((tbl)->bloom_bv, HASH_BLOOM_BYTELEN);                           \
    (tbl)->bloom_sig = HASH_BLOOM_SIGNATURE;                                     \
  }                                                                              \
} while (0)

#define HASH_BLOOM_FREE(tbl)                                                     \
do {                                                                             \
  uthash_free((tbl)->bloom_bv, HASH_BLOOM_BYTELEN);                              \
} while (0)

#define HASH_BLOOM_BITSET(bv,idx) (bv[(idx)/8U] |= (1U << ((idx)%8U)))
#define HASH_BLOOM_BITTEST(bv,idx) (bv[(idx)/8U] & (1U << ((idx)%8U)))

#define HASH_BLOOM_ADD(tbl,hashv)                                                \
  HASH_BLOOM_BITSET((tbl)->bloom_bv, ((hashv) & (uint32_t)((1UL << (tbl)->bloom_nbits) - 1U)))

#define HASH_BLOOM_TEST(tbl,hashv)                                               \
  HASH_BLOOM_BITTEST((tbl)->bloom_bv, ((hashv) & (uint32_t)((1UL << (tbl)->bloom_nbits) - 1U)))

#else
#define HASH_BLOOM_MAKE(tbl,oomed)
#define HASH_BLOOM_FREE(tbl)
#define HASH_BLOOM_ADD(tbl,hashv)
#define HASH_BLOOM_TEST(tbl,hashv) (1)
#define HASH_BLOOM_BYTELEN 0U
#endif

#define HASH_MAKE_TABLE(hh,head,oomed)                                           \
do {                                                                             \
  (head)->hh.tbl = (UT_hash_table*)uthash_malloc(sizeof(UT_hash_table));         \
  if (!(head)->hh.tbl) {                                                         \
    HASH_RECORD_OOM(oomed);                                                      \
  } else {                                                                       \
    uthash_bzero((head)->hh.tbl, sizeof(UT_hash_table));                         \
    (head)->hh.tbl->tail = &((head)->hh);                                        \
    (head)->hh.tbl->num_buckets = HASH_INITIAL_NUM_BUCKETS;                      \
    (head)->hh.tbl->log2_num_buckets = HASH_INITIAL_NUM_BUCKETS_LOG2;            \
    (head)->hh.tbl->hho = (char*)(&(head)->hh) - (char*)(head);                  \
    (head)->hh.tbl->buckets = (UT_hash_bucket*)uthash_malloc(                    \
        HASH_INITIAL_NUM_BUCKETS * sizeof(struct UT_hash_bucket));               \
    (head)->hh.tbl->signature = HASH_SIGNATURE;                                  \
    if (!(head)->hh.tbl->buckets) {                                              \
      HASH_RECORD_OOM(oomed);                                                    \
      uthash_free((head)->hh.tbl, sizeof(UT_hash_table));                        \
    } else {                                                                     \
      uthash_bzero((head)->hh.tbl->buckets,                                      \
          HASH_INITIAL_NUM_BUCKETS * sizeof(struct UT_hash_bucket));             \
      HASH_BLOOM_MAKE((head)->hh.tbl, oomed);                                    \
      IF_HASH_NONFATAL_OOM(                                                      \
        if (oomed) {                                                             \
          uthash_free((head)->hh.tbl->buckets,                                   \
              HASH_INITIAL_NUM_BUCKETS*sizeof(struct UT_hash_bucket));           \
          uthash_free((head)->hh.tbl, sizeof(UT_hash_table));                    \
        }                                                                        \
      )                                                                          \
    }                                                                            \
  }                                                                              \
} while (0)

#define HASH_REPLACE_BYHASHVALUE_INORDER(hh,head,fieldname,keylen_in,hashval,add,replaced,cmpfcn) \
do {                                                                             \
  (replaced) = NULL;                                                             \
  HASH_FIND_BYHASHVALUE(hh, head, &((add)->fieldname), keylen_in, hashval, replaced); \
  if (replaced) {                                                                \
    HASH_DELETE(hh, head, replaced);                                             \
  }                                                                              \
  HASH_ADD_KEYPTR_BYHASHVALUE_INORDER(hh, head, &((add)->fieldname), keylen_in, hashval, add, cmpfcn); \
} while (0)

#define HASH_REPLACE_BYHASHVALUE(hh,head,fieldname,keylen_in,hashval,add,replaced) \
do {                                                                             \
  (replaced) = NULL;                                                             \
  HASH_FIND_BYHASHVALUE(hh, head, &((add)->fieldname), keylen_in, hashval, replaced); \
  if (replaced) {                                                                \
    HASH_DELETE(hh, head, replaced);                                             \
  }                                                                              \
  HASH_ADD_KEYPTR_BYHASHVALUE(hh, head, &((add)->fieldname), keylen_in, hashval, add); \
} while (0)

#define HASH_REPLACE(hh,head,fieldname,keylen_in,add,replaced)                   \
do {                                                                             \
  unsigned _hr_hashv;                                                            \
  HASH_VALUE(&((add)->fieldname), keylen_in, _hr_hashv);                         \
  HASH_REPLACE_BYHASHVALUE(hh, head, fieldname, keylen_in, _hr_hashv, add, replaced); \
} while (0)

#define HASH_REPLACE_INORDER(hh,head,fieldname,keylen_in,add,replaced,cmpfcn)    \
do {                                                                             \
  unsigned _hr_hashv;                                                            \
  HASH_VALUE(&((add)->fieldname), keylen_in, _hr_hashv);                         \
  HASH_REPLACE_BYHASHVALUE_INORDER(hh, head, fieldname, keylen_in, _hr_hashv, add, replaced, cmpfcn); \
} while (0)

#define HASH_APPEND_LIST(hh, head, add)                                          \
do {                                                                             \
  (add)->hh.next = NULL;                                                         \
  (add)->hh.prev = ELMT_FROM_HH((head)->hh.tbl, (head)->hh.tbl->tail);           \
  (head)->hh.tbl->tail->next = (add);                                            \
  (head)->hh.tbl->tail = &((add)->hh);                                           \
} while (0)

#define HASH_AKBI_INNER_LOOP(hh,head,add,cmpfcn)                                 \
do {                                                                             \
  do {                                                                           \
    if (cmpfcn(DECLTYPE(head)(_hs_iter), add) > 0) {                             \
      break;                                                                     \
    }                                                                            \
  } while ((_hs_iter = HH_FROM_ELMT((head)->hh.tbl, _hs_iter)->next));           \
} while (0)

#ifdef NO_DECLTYPE
#undef HASH_AKBI_INNER_LOOP
#define HASH_AKBI_INNER_LOOP(hh,head,add,cmpfcn)                                 \
do {                                                                             \
  char *_hs_saved_head = (char*)(head);                                          \
  do {                                                                           \
    DECLTYPE_ASSIGN(head, _hs_iter);                                             \
    if (cmpfcn(head, add) > 0) {                                                 \
      DECLTYPE_ASSIGN(head, _hs_saved_head);                                     \
      break;                                                                     \
    }                                                                            \
    DECLTYPE_ASSIGN(head, _hs_saved_head);                                       \
  } while ((_hs_iter = HH_FROM_ELMT((head)->hh.tbl, _hs_iter)->next));           \
} while (0)
#endif

#if HASH_NONFATAL_OOM

#define HASH_ADD_TO_TABLE(hh,head,keyptr,keylen_in,hashval,add,oomed)            \
do {                                                                             \
  if (!(oomed)) {                                                                \
    unsigned _ha_bkt;                                                            \
    (head)->hh.tbl->num_items++;                                                 \
    HASH_TO_BKT(hashval, (head)->hh.tbl->num_buckets, _ha_bkt);                  \
    HASH_ADD_TO_BKT((head)->hh.tbl->buckets[_ha_bkt], hh, &(add)->hh, oomed);    \
    if (oomed) {                                                                 \
      HASH_ROLLBACK_BKT(hh, head, &(add)->hh);                                   \
      HASH_DELETE_HH(hh, head, &(add)->hh);                                      \
      (add)->hh.tbl = NULL;                                                      \
      uthash_nonfatal_oom(add);                                                  \
    } else {                                                                     \
      HASH_BLOOM_ADD((head)->hh.tbl, hashval);                                   \
      HASH_EMIT_KEY(hh, head, keyptr, keylen_in);                                \
    }                                                                            \
  } else {                                                                       \
    (add)->hh.tbl = NULL;                                                        \
    uthash_nonfatal_oom(add);                                                    \
  }                                                                              \
} while (0)

#else

#define HASH_ADD_TO_TABLE(hh,head,keyptr,keylen_in,hashval,add,oomed)            \
do {                                                                             \
  unsigned _ha_bkt;                                                              \
  (head)->hh.tbl->num_items++;                                                   \
  HASH_TO_BKT(hashval, (head)->hh.tbl->num_buckets, _ha_bkt);                    \
  HASH_ADD_TO_BKT((head)->hh.tbl->buckets[_ha_bkt], hh, &(add)->hh, oomed);      \
  HASH_BLOOM_ADD((head)->hh.tbl, hashval);                                       \
  HASH_EMIT_KEY(hh, head, keyptr, keylen_in);                                    \
} while (0)

#endif


#define HASH_ADD_KEYPTR_BYHASHVALUE_INORDER(hh,head,keyptr,keylen_in,hashval,add,cmpfcn) \
do {                                                                             \
  IF_HASH_NONFATAL_OOM( int _ha_oomed = 0; )                                     \
  (add)->hh.hashv = (hashval);                                                   \
  (add)->hh.key = (char*) (keyptr);                                              \
  (add)->hh.keylen = (unsigned) (keylen_in);                                     \
  if (!(head)) {                                                                 \
    (add)->hh.next = NULL;                                                       \
    (add)->hh.prev = NULL;                                                       \
    HASH_MAKE_TABLE(hh, add, _ha_oomed);                                         \
    IF_HASH_NONFATAL_OOM( if (!_ha_oomed) { )                                    \
      (head) = (add);                                                            \
    IF_HASH_NONFATAL_OOM( } )                                                    \
  } else {                                                                       \
    void *_hs_iter = (head);                                                     \
    (add)->hh.tbl = (head)->hh.tbl;                                              \
    HASH_AKBI_INNER_LOOP(hh, head, add, cmpfcn);                                 \
    if (_hs_iter) {                                                              \
      (add)->hh.next = _hs_iter;                                                 \
      if (((add)->hh.prev = HH_FROM_ELMT((head)->hh.tbl, _hs_iter)->prev)) {     \
        HH_FROM_ELMT((head)->hh.tbl, (add)->hh.prev)->next = (add);              \
      } else {                                                                   \
        (head) = (add);                                                          \
      }                                                                          \
      HH_FROM_ELMT((head)->hh.tbl, _hs_iter)->prev = (add);                      \
    } else {                                                                     \
      HASH_APPEND_LIST(hh, head, add);                                           \
    }                                                                            \
  }                                                                              \
  HASH_ADD_TO_TABLE(hh, head, keyptr, keylen_in, hashval, add, _ha_oomed);       \
  HASH_FSCK(hh, head, "HASH_ADD_KEYPTR_BYHASHVALUE_INORDER");                    \
} while (0)

#define HASH_ADD_KEYPTR_INORDER(hh,head,keyptr,keylen_in,add,cmpfcn)             \
do {                                                                             \
  unsigned _hs_hashv;                                                            \
  HASH_VALUE(keyptr, keylen_in, _hs_hashv);                                      \
  HASH_ADD_KEYPTR_BYHASHVALUE_INORDER(hh, head, keyptr, keylen_in, _hs_hashv, add, cmpfcn); \
} while (0)

#define HASH_ADD_BYHASHVALUE_INORDER(hh,head,fieldname,keylen_in,hashval,add,cmpfcn) \
  HASH_ADD_KEYPTR_BYHASHVALUE_INORDER(hh, head, &((add)->fieldname), keylen_in, hashval, add, cmpfcn)

#define HASH_ADD_INORDER(hh,head,fieldname,keylen_in,add,cmpfcn)                 \
  HASH_ADD_KEYPTR_INORDER(hh, head, &((add)->fieldname), keylen_in, add, cmpfcn)

#define HASH_ADD_KEYPTR_BYHASHVALUE(hh,head,keyptr,keylen_in,hashval,add)        \
do {                                                                             \
  IF_HASH_NONFATAL_OOM( int _ha_oomed = 0; )                                     \
  (add)->hh.hashv = (hashval);                                                   \
  (add)->hh.key = (char*) (keyptr);                                              \
  (add)->hh.keylen = (unsigned) (keylen_in);                                     \
  if (!(head)) {                                                                 \
    (add)->hh.next = NULL;                                                       \
    (add)->hh.prev = NULL;                                                       \
    HASH_MAKE_TABLE(hh, add, _ha_oomed);                                         \
    IF_HASH_NONFATAL_OOM( if (!_ha_oomed) { )                                    \
      (head) = (add);                                                            \
    IF_HASH_NONFATAL_OOM( } )                                                    \
  } else {                                                                       \
    (add)->hh.tbl = (head)->hh.tbl;                                              \
    HASH_APPEND_LIST(hh, head, add);                                             \
  }                                                                              \
  HASH_ADD_TO_TABLE(hh, head, keyptr, keylen_in, hashval, add, _ha_oomed);       \
  HASH_FSCK(hh, head, "HASH_ADD_KEYPTR_BYHASHVALUE");                            \
} while (0)

#define HASH_ADD_KEYPTR(hh,head,keyptr,keylen_in,add)                            \
do {                                                                             \
  unsigned _ha_hashv;                                                            \
  HASH_VALUE(keyptr, keylen_in, _ha_hashv);                                      \
  HASH_ADD_KEYPTR_BYHASHVALUE(hh, head, keyptr, keylen_in, _ha_hashv, add);      \
} while (0)

#define HASH_ADD_BYHASHVALUE(hh,head,fieldname,keylen_in,hashval,add)            \
  HASH_ADD_KEYPTR_BYHASHVALUE(hh, head, &((add)->fieldname), keylen_in, hashval, add)

#define HASH_ADD(hh,head,fieldname,keylen_in,add)                                \
  HASH_ADD_KEYPTR(hh, head, &((add)->fieldname), keylen_in, add)

#define HASH_TO_BKT(hashv,num_bkts,bkt)                                          \
do {                                                                             \
  bkt = ((hashv) & ((num_bkts) - 1U));                                           \
} while (0)

/* 从哈希表中删除“delptr”。应用程序订单双链接列表的“常规”修补过程。以下_hd_hh_del的用法值得特别说明。这些过去使用（delptr）表示，但如果有人对头部和被删除者使用相同的符号，如HASH_DELETE（hh，users，users），则会导致错误；我们希望这样做有效，但通过更改下面的标题（用户），我们失去了在修补过程中进一步引用被删除者（用户）的能力。解决方案：使用暂存空间复制被删除者指针，然后后者的引用通过该暂存指针而不是通过重新打印的（用户）符号。
 */
#define HASH_DELETE(hh,head,delptr)                                              \
    HASH_DELETE_HH(hh, head, &(delptr)->hh)

#define HASH_DELETE_HH(hh,head,delptrhh)                                         \
do {                                                                             \
  struct UT_hash_handle *_hd_hh_del = (delptrhh);                                \
  if ((_hd_hh_del->prev == NULL) && (_hd_hh_del->next == NULL)) {                \
    HASH_BLOOM_FREE((head)->hh.tbl);                                             \
    uthash_free((head)->hh.tbl->buckets,                                         \
                (head)->hh.tbl->num_buckets * sizeof(struct UT_hash_bucket));    \
    uthash_free((head)->hh.tbl, sizeof(UT_hash_table));                          \
    (head) = NULL;                                                               \
  } else {                                                                       \
    unsigned _hd_bkt;                                                            \
    if (_hd_hh_del == (head)->hh.tbl->tail) {                                    \
      (head)->hh.tbl->tail = HH_FROM_ELMT((head)->hh.tbl, _hd_hh_del->prev);     \
    }                                                                            \
    if (_hd_hh_del->prev != NULL) {                                              \
      HH_FROM_ELMT((head)->hh.tbl, _hd_hh_del->prev)->next = _hd_hh_del->next;   \
    } else {                                                                     \
      DECLTYPE_ASSIGN(head, _hd_hh_del->next);                                   \
    }                                                                            \
    if (_hd_hh_del->next != NULL) {                                              \
      HH_FROM_ELMT((head)->hh.tbl, _hd_hh_del->next)->prev = _hd_hh_del->prev;   \
    }                                                                            \
    HASH_TO_BKT(_hd_hh_del->hashv, (head)->hh.tbl->num_buckets, _hd_bkt);        \
    HASH_DEL_IN_BKT((head)->hh.tbl->buckets[_hd_bkt], _hd_hh_del);               \
    (head)->hh.tbl->num_items--;                                                 \
  }                                                                              \
  HASH_FSCK(hh, head, "HASH_DELETE_HH");                                         \
} while (0)

/* HASH_FIND/HASH_ADD/HASH_DEL的方便形式*/
#define HASH_FIND_STR(head,findstr,out)                                          \
    HASH_FIND(hh,head,findstr,(unsigned)uthash_strlen(findstr),out)
#define HASH_ADD_STR(head,strfield,add)                                          \
    HASH_ADD(hh,head,strfield[0],(unsigned)uthash_strlen(add->strfield),add)
#define HASH_REPLACE_STR(head,strfield,add,replaced)                             \
    HASH_REPLACE(hh,head,strfield[0],(unsigned)uthash_strlen(add->strfield),add,replaced)
#define HASH_FIND_INT(head,findint,out)                                          \
    HASH_FIND(hh,head,findint,sizeof(int),out)
#define HASH_ADD_INT(head,intfield,add)                                          \
    HASH_ADD(hh,head,intfield,sizeof(int),add)
#define HASH_REPLACE_INT(head,intfield,add,replaced)                             \
    HASH_REPLACE(hh,head,intfield,sizeof(int),add,replaced)
#define HASH_FIND_PTR(head,findptr,out)                                          \
    HASH_FIND(hh,head,findptr,sizeof(void *),out)
#define HASH_ADD_PTR(head,ptrfield,add)                                          \
    HASH_ADD(hh,head,ptrfield,sizeof(void *),add)
#define HASH_REPLACE_PTR(head,ptrfield,add,replaced)                             \
    HASH_REPLACE(hh,head,ptrfield,sizeof(void *),add,replaced)
#define HASH_DEL(head,delptr)                                                    \
    HASH_DELETE(hh,head,delptr)

/* 定义HASH_DEBUG时，HASH_FSCK在每次添加/删除时检查哈希完整性。这仅适用于uthash开发人员；如果未定义HASH_DEBUG，它将编译掉。
 */
#ifdef HASH_DEBUG
#define HASH_OOPS(...) do { fprintf(stderr,__VA_ARGS__); exit(-1); } while (0)
#define HASH_FSCK(hh,head,where)                                                 \
do {                                                                             \
  struct UT_hash_handle *_thh;                                                   \
  if (head) {                                                                    \
    unsigned _bkt_i;                                                             \
    unsigned _count = 0;                                                         \
    char *_prev;                                                                 \
    for (_bkt_i = 0; _bkt_i < (head)->hh.tbl->num_buckets; ++_bkt_i) {           \
      unsigned _bkt_count = 0;                                                   \
      _thh = (head)->hh.tbl->buckets[_bkt_i].hh_head;                            \
      _prev = NULL;                                                              \
      while (_thh) {                                                             \
        if (_prev != (char*)(_thh->hh_prev)) {                                   \
          HASH_OOPS("%s: invalid hh_prev %p, actual %p\n",                       \
              (where), (void*)_thh->hh_prev, (void*)_prev);                      \
        }                                                                        \
        _bkt_count++;                                                            \
        _prev = (char*)(_thh);                                                   \
        _thh = _thh->hh_next;                                                    \
      }                                                                          \
      _count += _bkt_count;                                                      \
      if ((head)->hh.tbl->buckets[_bkt_i].count !=  _bkt_count) {                \
        HASH_OOPS("%s: invalid bucket count %u, actual %u\n",                    \
            (where), (head)->hh.tbl->buckets[_bkt_i].count, _bkt_count);         \
      }                                                                          \
    }                                                                            \
    if (_count != (head)->hh.tbl->num_items) {                                   \
      HASH_OOPS("%s: invalid hh item count %u, actual %u\n",                     \
          (where), (head)->hh.tbl->num_items, _count);                           \
    }                                                                            \
    _count = 0;                                                                  \
    _prev = NULL;                                                                \
    _thh =  &(head)->hh;                                                         \
    while (_thh) {                                                               \
      _count++;                                                                  \
      if (_prev != (char*)_thh->prev) {                                          \
        HASH_OOPS("%s: invalid prev %p, actual %p\n",                            \
            (where), (void*)_thh->prev, (void*)_prev);                           \
      }                                                                          \
      _prev = (char*)ELMT_FROM_HH((head)->hh.tbl, _thh);                         \
      _thh = (_thh->next ? HH_FROM_ELMT((head)->hh.tbl, _thh->next) : NULL);     \
    }                                                                            \
    if (_count != (head)->hh.tbl->num_items) {                                   \
      HASH_OOPS("%s: invalid app item count %u, actual %u\n",                    \
          (where), (head)->hh.tbl->num_items, _count);                           \
    }                                                                            \
  }                                                                              \
} while (0)
#else
#define HASH_FSCK(hh,head,where)
#endif

/* 当使用-DHASH_EMIT_KEYS编译时，长度前缀键将被发送到定义此宏用于调整哈希函数的描述符。应用程序可以#include<unistd。h> 以获得用于编写的原型（2）。*/
#ifdef HASH_EMIT_KEYS
#define HASH_EMIT_KEY(hh,head,keyptr,fieldlen)                                   \
do {                                                                             \
  unsigned _klen = fieldlen;                                                     \
  write(HASH_EMIT_KEYS, &_klen, sizeof(_klen));                                  \
  write(HASH_EMIT_KEYS, keyptr, (unsigned long)fieldlen);                        \
} while (0)
#else
#define HASH_EMIT_KEY(hh,head,keyptr,fieldlen)
#endif

/* 除非被重写，否则默认为Jenkin的哈希，例如DHASH_FUNCTION=hash_SSAX*/
#ifdef HASH_FUNCTION
#define HASH_FCN HASH_FUNCTION
#else
#define HASH_FCN HASH_JEN
#endif

/* Bernstein哈希函数，在v5.6之前的Perl中使用。注意（x<<5+x）=x*33。*/
#define HASH_BER(key,keylen,hashv)                                               \
do {                                                                             \
  unsigned _hb_keylen = (unsigned)keylen;                                        \
  const unsigned char *_hb_key = (const unsigned char*)(key);                    \
  (hashv) = 0;                                                                   \
  while (_hb_keylen-- != 0U) {                                                   \
    (hashv) = (((hashv) << 5) + (hashv)) + *_hb_key++;                           \
  }                                                                              \
} while (0)


/* SAX/FNV/OAT/JEN哈希函数是在http://eternallyconfuzzled.com/tuts/algorithms/jsw_tut_hashing.aspx */
#define HASH_SAX(key,keylen,hashv)                                               \
do {                                                                             \
  unsigned _sx_i;                                                                \
  const unsigned char *_hs_key = (const unsigned char*)(key);                    \
  hashv = 0;                                                                     \
  for (_sx_i=0; _sx_i < keylen; _sx_i++) {                                       \
    hashv ^= (hashv << 5) + (hashv >> 2) + _hs_key[_sx_i];                       \
  }                                                                              \
} while (0)
/* FNV-1a变异*/
#define HASH_FNV(key,keylen,hashv)                                               \
do {                                                                             \
  unsigned _fn_i;                                                                \
  const unsigned char *_hf_key = (const unsigned char*)(key);                    \
  (hashv) = 2166136261U;                                                         \
  for (_fn_i=0; _fn_i < keylen; _fn_i++) {                                       \
    hashv = hashv ^ _hf_key[_fn_i];                                              \
    hashv = hashv * 16777619U;                                                   \
  }                                                                              \
} while (0)

#define HASH_OAT(key,keylen,hashv)                                               \
do {                                                                             \
  unsigned _ho_i;                                                                \
  const unsigned char *_ho_key=(const unsigned char*)(key);                      \
  hashv = 0;                                                                     \
  for(_ho_i=0; _ho_i < keylen; _ho_i++) {                                        \
      hashv += _ho_key[_ho_i];                                                   \
      hashv += (hashv << 10);                                                    \
      hashv ^= (hashv >> 6);                                                     \
  }                                                                              \
  hashv += (hashv << 3);                                                         \
  hashv ^= (hashv >> 11);                                                        \
  hashv += (hashv << 15);                                                        \
} while (0)

#define HASH_JEN_MIX(a,b,c)                                                      \
do {                                                                             \
  a -= b; a -= c; a ^= ( c >> 13 );                                              \
  b -= c; b -= a; b ^= ( a << 8 );                                               \
  c -= a; c -= b; c ^= ( b >> 13 );                                              \
  a -= b; a -= c; a ^= ( c >> 12 );                                              \
  b -= c; b -= a; b ^= ( a << 16 );                                              \
  c -= a; c -= b; c ^= ( b >> 5 );                                               \
  a -= b; a -= c; a ^= ( c >> 3 );                                               \
  b -= c; b -= a; b ^= ( a << 10 );                                              \
  c -= a; c -= b; c ^= ( b >> 15 );                                              \
} while (0)

#define HASH_JEN(key,keylen,hashv)                                               \
do {                                                                             \
  unsigned _hj_i,_hj_j,_hj_k;                                                    \
  unsigned const char *_hj_key=(unsigned const char*)(key);                      \
  hashv = 0xfeedbeefu;                                                           \
  _hj_i = _hj_j = 0x9e3779b9u;                                                   \
  _hj_k = (unsigned)(keylen);                                                    \
  while (_hj_k >= 12U) {                                                         \
    _hj_i +=    (_hj_key[0] + ( (unsigned)_hj_key[1] << 8 )                      \
        + ( (unsigned)_hj_key[2] << 16 )                                         \
        + ( (unsigned)_hj_key[3] << 24 ) );                                      \
    _hj_j +=    (_hj_key[4] + ( (unsigned)_hj_key[5] << 8 )                      \
        + ( (unsigned)_hj_key[6] << 16 )                                         \
        + ( (unsigned)_hj_key[7] << 24 ) );                                      \
    hashv += (_hj_key[8] + ( (unsigned)_hj_key[9] << 8 )                         \
        + ( (unsigned)_hj_key[10] << 16 )                                        \
        + ( (unsigned)_hj_key[11] << 24 ) );                                     \
                                                                                 \
     HASH_JEN_MIX(_hj_i, _hj_j, hashv);                                          \
                                                                                 \
     _hj_key += 12;                                                              \
     _hj_k -= 12U;                                                               \
  }                                                                              \
  hashv += (unsigned)(keylen);                                                   \
  switch ( _hj_k ) {                                                             \
    case 11: hashv += ( (unsigned)_hj_key[10] << 24 ); /* FALLTHROUGH */         \
    case 10: hashv += ( (unsigned)_hj_key[9] << 16 );  /* FALLTHROUGH */         \
    case 9:  hashv += ( (unsigned)_hj_key[8] << 8 );   /* FALLTHROUGH */         \
    case 8:  _hj_j += ( (unsigned)_hj_key[7] << 24 );  /* FALLTHROUGH */         \
    case 7:  _hj_j += ( (unsigned)_hj_key[6] << 16 );  /* FALLTHROUGH */         \
    case 6:  _hj_j += ( (unsigned)_hj_key[5] << 8 );   /* FALLTHROUGH */         \
    case 5:  _hj_j += _hj_key[4];                      /* FALLTHROUGH */         \
    case 4:  _hj_i += ( (unsigned)_hj_key[3] << 24 );  /* FALLTHROUGH */         \
    case 3:  _hj_i += ( (unsigned)_hj_key[2] << 16 );  /* FALLTHROUGH */         \
    case 2:  _hj_i += ( (unsigned)_hj_key[1] << 8 );   /* FALLTHROUGH */         \
    case 1:  _hj_i += _hj_key[0];                      /* FALLTHROUGH */         \
    default: /* 使gcc-Wswitch默认值满意*/                               \
       ;                                                                         \
  }                                                                              \
  HASH_JEN_MIX(_hj_i, _hj_j, hashv);                                             \
} while (0)

/* Paul Hsieh哈希函数*/
#undef get16bits
#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__)             \
  || defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
#define get16bits(d) (*((const uint16_t *) (d)))
#endif

#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)             \
                       +(uint32_t)(((const uint8_t *)(d))[0]) )
#endif
#define HASH_SFH(key,keylen,hashv)                                               \
do {                                                                             \
  unsigned const char *_sfh_key=(unsigned const char*)(key);                     \
  uint32_t _sfh_tmp, _sfh_len = (uint32_t)keylen;                                \
                                                                                 \
  unsigned _sfh_rem = _sfh_len & 3U;                                             \
  _sfh_len >>= 2;                                                                \
  hashv = 0xcafebabeu;                                                           \
                                                                                 \
  /* 主回路*/                                                                \
  for (;_sfh_len > 0U; _sfh_len--) {                                             \
    hashv    += get16bits (_sfh_key);                                            \
    _sfh_tmp  = ((uint32_t)(get16bits (_sfh_key+2)) << 11) ^ hashv;              \
    hashv     = (hashv << 16) ^ _sfh_tmp;                                        \
    _sfh_key += 2U*sizeof (uint16_t);                                            \
    hashv    += hashv >> 11;                                                     \
  }                                                                              \
                                                                                 \
  /* 处理端箱*/                                                         \
  switch (_sfh_rem) {                                                            \
    case 3: hashv += get16bits (_sfh_key);                                       \
            hashv ^= hashv << 16;                                                \
            hashv ^= (uint32_t)(_sfh_key[sizeof (uint16_t)]) << 18;              \
            hashv += hashv >> 11;                                                \
            break;                                                               \
    case 2: hashv += get16bits (_sfh_key);                                       \
            hashv ^= hashv << 11;                                                \
            hashv += hashv >> 17;                                                \
            break;                                                               \
    case 1: hashv += *_sfh_key;                                                  \
            hashv ^= hashv << 10;                                                \
            hashv += hashv >> 1;                                                 \
  }                                                                              \
                                                                                 \
  /* 强制“雪崩”最后127位*/                                    \
  hashv ^= hashv << 3;                                                           \
  hashv += hashv >> 5;                                                           \
  hashv ^= hashv << 4;                                                           \
  hashv += hashv >> 17;                                                          \
  hashv ^= hashv << 25;                                                          \
  hashv += hashv >> 6;                                                           \
} while (0)

#ifdef HASH_USING_NO_STRICT_ALIASING
/* MurmurHash利用一些CPU（x86，x86_64）对未对齐读取的容忍度。对于其他类型的CPU（例如Sparc），未对齐的读取会导致总线错误。MurmurHash只在我们知道安全的CPU上使用更快的方法。
 *
 * 请注意，预处理器内置的定义可以使用以下方式发出：
 *
 *   gcc-m64-dM-E-</dev/null（在gcc上）cc-#a.c（其中a.c是一个简单的测试文件）（Sun Studio）
 */
#if (defined(__i386__) || defined(__x86_64__)  || defined(_M_IX86))
#define MUR_GETBLOCK(p,i) p[i]
#else /* 非英特尔公司*/
#define MUR_PLUS0_ALIGNED(p) (((unsigned long)p & 3UL) == 0UL)
#define MUR_PLUS1_ALIGNED(p) (((unsigned long)p & 3UL) == 1UL)
#define MUR_PLUS2_ALIGNED(p) (((unsigned long)p & 3UL) == 2UL)
#define MUR_PLUS3_ALIGNED(p) (((unsigned long)p & 3UL) == 3UL)
#define WP(p) ((uint32_t*)((unsigned long)(p) & ~3UL))
#if (defined(__BIG_ENDIAN__) || defined(SPARC) || defined(__ppc__) || defined(__ppc64__))
#define MUR_THREE_ONE(p) ((((*WP(p))&0x00ffffff) << 8) | (((*(WP(p)+1))&0xff000000) >> 24))
#define MUR_TWO_TWO(p)   ((((*WP(p))&0x0000ffff) <<16) | (((*(WP(p)+1))&0xffff0000) >> 16))
#define MUR_ONE_THREE(p) ((((*WP(p))&0x000000ff) <<24) | (((*(WP(p)+1))&0xffffff00) >>  8))
#else /* 假设小端非intel*/
#define MUR_THREE_ONE(p) ((((*WP(p))&0xffffff00) >> 8) | (((*(WP(p)+1))&0x000000ff) << 24))
#define MUR_TWO_TWO(p)   ((((*WP(p))&0xffff0000) >>16) | (((*(WP(p)+1))&0x0000ffff) << 16))
#define MUR_ONE_THREE(p) ((((*WP(p))&0xff000000) >>24) | (((*(WP(p)+1))&0x00ffffff) <<  8))
#endif
#define MUR_GETBLOCK(p,i) (MUR_PLUS0_ALIGNED(p) ? ((p)[i]) :           \
                            (MUR_PLUS1_ALIGNED(p) ? MUR_THREE_ONE(p) : \
                             (MUR_PLUS2_ALIGNED(p) ? MUR_TWO_TWO(p) :  \
                                                      MUR_ONE_THREE(p))))
#endif
#define MUR_ROTL32(x,r) (((x) << (r)) | ((x) >> (32 - (r))))
#define MUR_FMIX(_h) \
do {                 \
  _h ^= _h >> 16;    \
  _h *= 0x85ebca6bu; \
  _h ^= _h >> 13;    \
  _h *= 0xc2b2ae35u; \
  _h ^= _h >> 16;    \
} while (0)

#define HASH_MUR(key,keylen,hashv)                                     \
do {                                                                   \
  const uint8_t *_mur_data = (const uint8_t*)(key);                    \
  const int _mur_nblocks = (int)(keylen) / 4;                          \
  uint32_t _mur_h1 = 0xf88D5353u;                                      \
  uint32_t _mur_c1 = 0xcc9e2d51u;                                      \
  uint32_t _mur_c2 = 0x1b873593u;                                      \
  uint32_t _mur_k1 = 0;                                                \
  const uint8_t *_mur_tail;                                            \
  const uint32_t *_mur_blocks = (const uint32_t*)(_mur_data+(_mur_nblocks*4)); \
  int _mur_i;                                                          \
  for (_mur_i = -_mur_nblocks; _mur_i != 0; _mur_i++) {                \
    _mur_k1 = MUR_GETBLOCK(_mur_blocks,_mur_i);                        \
    _mur_k1 *= _mur_c1;                                                \
    _mur_k1 = MUR_ROTL32(_mur_k1,15);                                  \
    _mur_k1 *= _mur_c2;                                                \
                                                                       \
    _mur_h1 ^= _mur_k1;                                                \
    _mur_h1 = MUR_ROTL32(_mur_h1,13);                                  \
    _mur_h1 = (_mur_h1*5U) + 0xe6546b64u;                              \
  }                                                                    \
  _mur_tail = (const uint8_t*)(_mur_data + (_mur_nblocks*4));          \
  _mur_k1=0;                                                           \
  switch ((keylen) & 3U) {                                             \
    case 0: break;                                                     \
    case 3: _mur_k1 ^= (uint32_t)_mur_tail[2] << 16; /* FALLTHROUGH */ \
    case 2: _mur_k1 ^= (uint32_t)_mur_tail[1] << 8;  /* FALLTHROUGH */ \
    case 1: _mur_k1 ^= (uint32_t)_mur_tail[0];                         \
    _mur_k1 *= _mur_c1;                                                \
    _mur_k1 = MUR_ROTL32(_mur_k1,15);                                  \
    _mur_k1 *= _mur_c2;                                                \
    _mur_h1 ^= _mur_k1;                                                \
  }                                                                    \
  _mur_h1 ^= (uint32_t)(keylen);                                       \
  MUR_FMIX(_mur_h1);                                                   \
  hashv = _mur_h1;                                                     \
} while (0)
#endif  /* HASH_USING_NO_STRICT_ALIASING */

/* 迭代已知存储桶中的项目以找到所需的项目*/
#define HASH_FIND_IN_BKT(tbl,hh,head,keyptr,keylen_in,hashval,out)               \
do {                                                                             \
  if ((head).hh_head != NULL) {                                                  \
    DECLTYPE_ASSIGN(out, ELMT_FROM_HH(tbl, (head).hh_head));                     \
  } else {                                                                       \
    (out) = NULL;                                                                \
  }                                                                              \
  while ((out) != NULL) {                                                        \
    if ((out)->hh.hashv == (hashval) && (out)->hh.keylen == (keylen_in)) {       \
      if (uthash_memcmp((out)->hh.key, keyptr, keylen_in) == 0) {                \
        break;                                                                   \
      }                                                                          \
    }                                                                            \
    if ((out)->hh.hh_next != NULL) {                                             \
      DECLTYPE_ASSIGN(out, ELMT_FROM_HH(tbl, (out)->hh.hh_next));                \
    } else {                                                                     \
      (out) = NULL;                                                              \
    }                                                                            \
  }                                                                              \
} while (0)

/* 将项目添加到存储桶*/
#define HASH_ADD_TO_BKT(head,hh,addhh,oomed)                                     \
do {                                                                             \
  UT_hash_bucket *_ha_head = &(head);                                            \
  _ha_head->count++;                                                             \
  (addhh)->hh_next = _ha_head->hh_head;                                          \
  (addhh)->hh_prev = NULL;                                                       \
  if (_ha_head->hh_head != NULL) {                                               \
    _ha_head->hh_head->hh_prev = (addhh);                                        \
  }                                                                              \
  _ha_head->hh_head = (addhh);                                                   \
  if ((_ha_head->count >= ((_ha_head->expand_mult + 1U) * HASH_BKT_CAPACITY_THRESH)) \
      && !(addhh)->tbl->noexpand) {                                              \
    HASH_EXPAND_BUCKETS(addhh,(addhh)->tbl, oomed);                              \
    IF_HASH_NONFATAL_OOM(                                                        \
      if (oomed) {                                                               \
        HASH_DEL_IN_BKT(head,addhh);                                             \
      }                                                                          \
    )                                                                            \
  }                                                                              \
} while (0)

/* 从给定存储桶中删除项目*/
#define HASH_DEL_IN_BKT(head,delhh)                                              \
do {                                                                             \
  UT_hash_bucket *_hd_head = &(head);                                            \
  _hd_head->count--;                                                             \
  if (_hd_head->hh_head == (delhh)) {                                            \
    _hd_head->hh_head = (delhh)->hh_next;                                        \
  }                                                                              \
  if ((delhh)->hh_prev) {                                                        \
    (delhh)->hh_prev->hh_next = (delhh)->hh_next;                                \
  }                                                                              \
  if ((delhh)->hh_next) {                                                        \
    (delhh)->hh_next->hh_prev = (delhh)->hh_prev;                                \
  }                                                                              \
} while (0)

/* Bucket扩展的效果是将Bucket的数量增加一倍，并将项目重新分配到新的Bucket中。理想情况下，项目将或多或少均匀地分布到新的桶中（这一点的真实程度是哈希函数应用于密钥域时的质量度量）。
 *
 * 随着项目被分配到更多的桶中，每个桶中的链长度（项目数）会减少。因此，通过扩展桶，哈希保持链长度的界限。这种有界的链长度是哈希如何提供恒定时间查找的本质。
 *
 * 下面的tbl->ideal_chain_maxlen的计算值得一些解释。首先，请记住，我们是根据新的（双倍）桶数计算理想的最大链长。在分数中，这只是n/b（n=项目数量，b=新的num桶）。由于理想链长是整数，我们希望计算ceil（n/b）。我们不依赖于哈希中的浮点运算，所以要用整数计算ceil（n/b），我们可以写
 *
 *      ceil（n/b）=（n/b）+（（n%b）？1:0)
 *
 * 事实上，这个哈希的前一个版本就做到了这一点。但现在，我们认识到b总是2的幂，这使情况有所改善。我们将它的基2日志放在手边（称为lb），因此现在我们可以使用位移位和逻辑and来编写它：
 *
 *      ceil（n/b）=（n>>lb）+（（n&（b-1））？1:0)
 *
 */
#define HASH_EXPAND_BUCKETS(hh,tbl,oomed)                                        \
do {                                                                             \
  unsigned _he_bkt;                                                              \
  unsigned _he_bkt_i;                                                            \
  struct UT_hash_handle *_he_thh, *_he_hh_nxt;                                   \
  UT_hash_bucket *_he_new_buckets, *_he_newbkt;                                  \
  _he_new_buckets = (UT_hash_bucket*)uthash_malloc(                              \
           2UL * (tbl)->num_buckets * sizeof(struct UT_hash_bucket));            \
  if (!_he_new_buckets) {                                                        \
    HASH_RECORD_OOM(oomed);                                                      \
  } else {                                                                       \
    uthash_bzero(_he_new_buckets,                                                \
        2UL * (tbl)->num_buckets * sizeof(struct UT_hash_bucket));               \
    (tbl)->ideal_chain_maxlen =                                                  \
       ((tbl)->num_items >> ((tbl)->log2_num_buckets+1U)) +                      \
       ((((tbl)->num_items & (((tbl)->num_buckets*2U)-1U)) != 0U) ? 1U : 0U);    \
    (tbl)->nonideal_items = 0;                                                   \
    for (_he_bkt_i = 0; _he_bkt_i < (tbl)->num_buckets; _he_bkt_i++) {           \
      _he_thh = (tbl)->buckets[ _he_bkt_i ].hh_head;                             \
      while (_he_thh != NULL) {                                                  \
        _he_hh_nxt = _he_thh->hh_next;                                           \
        HASH_TO_BKT(_he_thh->hashv, (tbl)->num_buckets * 2U, _he_bkt);           \
        _he_newbkt = &(_he_new_buckets[_he_bkt]);                                \
        if (++(_he_newbkt->count) > (tbl)->ideal_chain_maxlen) {                 \
          (tbl)->nonideal_items++;                                               \
          _he_newbkt->expand_mult = _he_newbkt->count / (tbl)->ideal_chain_maxlen; \
        }                                                                        \
        _he_thh->hh_prev = NULL;                                                 \
        _he_thh->hh_next = _he_newbkt->hh_head;                                  \
        if (_he_newbkt->hh_head != NULL) {                                       \
          _he_newbkt->hh_head->hh_prev = _he_thh;                                \
        }                                                                        \
        _he_newbkt->hh_head = _he_thh;                                           \
        _he_thh = _he_hh_nxt;                                                    \
      }                                                                          \
    }                                                                            \
    uthash_free((tbl)->buckets, (tbl)->num_buckets * sizeof(struct UT_hash_bucket)); \
    (tbl)->num_buckets *= 2U;                                                    \
    (tbl)->log2_num_buckets++;                                                   \
    (tbl)->buckets = _he_new_buckets;                                            \
    (tbl)->ineff_expands = ((tbl)->nonideal_items > ((tbl)->num_items >> 1)) ?   \
        ((tbl)->ineff_expands+1U) : 0U;                                          \
    if ((tbl)->ineff_expands > 1U) {                                             \
      (tbl)->noexpand = 1;                                                       \
      uthash_noexpand_fyi(tbl);                                                  \
    }                                                                            \
    uthash_expand_fyi(tbl);                                                      \
  }                                                                              \
} while (0)


/* 这是西蒙·塔塔姆的《O（n log（n））合并》的改编本*/
/* 请注意，HASH_SORT假定哈希句柄名称为hh。添加HASH_SRT以允许传入哈希句柄名称。*/
#define HASH_SORT(head,cmpfcn) HASH_SRT(hh,head,cmpfcn)
#define HASH_SRT(hh,head,cmpfcn)                                                 \
do {                                                                             \
  unsigned _hs_i;                                                                \
  unsigned _hs_looping,_hs_nmerges,_hs_insize,_hs_psize,_hs_qsize;               \
  struct UT_hash_handle *_hs_p, *_hs_q, *_hs_e, *_hs_list, *_hs_tail;            \
  if (head != NULL) {                                                            \
    _hs_insize = 1;                                                              \
    _hs_looping = 1;                                                             \
    _hs_list = &((head)->hh);                                                    \
    while (_hs_looping != 0U) {                                                  \
      _hs_p = _hs_list;                                                          \
      _hs_list = NULL;                                                           \
      _hs_tail = NULL;                                                           \
      _hs_nmerges = 0;                                                           \
      while (_hs_p != NULL) {                                                    \
        _hs_nmerges++;                                                           \
        _hs_q = _hs_p;                                                           \
        _hs_psize = 0;                                                           \
        for (_hs_i = 0; _hs_i < _hs_insize; ++_hs_i) {                           \
          _hs_psize++;                                                           \
          _hs_q = ((_hs_q->next != NULL) ?                                       \
            HH_FROM_ELMT((head)->hh.tbl, _hs_q->next) : NULL);                   \
          if (_hs_q == NULL) {                                                   \
            break;                                                               \
          }                                                                      \
        }                                                                        \
        _hs_qsize = _hs_insize;                                                  \
        while ((_hs_psize != 0U) || ((_hs_qsize != 0U) && (_hs_q != NULL))) {    \
          if (_hs_psize == 0U) {                                                 \
            _hs_e = _hs_q;                                                       \
            _hs_q = ((_hs_q->next != NULL) ?                                     \
              HH_FROM_ELMT((head)->hh.tbl, _hs_q->next) : NULL);                 \
            _hs_qsize--;                                                         \
          } else if ((_hs_qsize == 0U) || (_hs_q == NULL)) {                     \
            _hs_e = _hs_p;                                                       \
            if (_hs_p != NULL) {                                                 \
              _hs_p = ((_hs_p->next != NULL) ?                                   \
                HH_FROM_ELMT((head)->hh.tbl, _hs_p->next) : NULL);               \
            }                                                                    \
            _hs_psize--;                                                         \
          } else if ((cmpfcn(                                                    \
                DECLTYPE(head)(ELMT_FROM_HH((head)->hh.tbl, _hs_p)),             \
                DECLTYPE(head)(ELMT_FROM_HH((head)->hh.tbl, _hs_q))              \
                )) <= 0) {                                                       \
            _hs_e = _hs_p;                                                       \
            if (_hs_p != NULL) {                                                 \
              _hs_p = ((_hs_p->next != NULL) ?                                   \
                HH_FROM_ELMT((head)->hh.tbl, _hs_p->next) : NULL);               \
            }                                                                    \
            _hs_psize--;                                                         \
          } else {                                                               \
            _hs_e = _hs_q;                                                       \
            _hs_q = ((_hs_q->next != NULL) ?                                     \
              HH_FROM_ELMT((head)->hh.tbl, _hs_q->next) : NULL);                 \
            _hs_qsize--;                                                         \
          }                                                                      \
          if ( _hs_tail != NULL ) {                                              \
            _hs_tail->next = ((_hs_e != NULL) ?                                  \
              ELMT_FROM_HH((head)->hh.tbl, _hs_e) : NULL);                       \
          } else {                                                               \
            _hs_list = _hs_e;                                                    \
          }                                                                      \
          if (_hs_e != NULL) {                                                   \
            _hs_e->prev = ((_hs_tail != NULL) ?                                  \
              ELMT_FROM_HH((head)->hh.tbl, _hs_tail) : NULL);                    \
          }                                                                      \
          _hs_tail = _hs_e;                                                      \
        }                                                                        \
        _hs_p = _hs_q;                                                           \
      }                                                                          \
      if (_hs_tail != NULL) {                                                    \
        _hs_tail->next = NULL;                                                   \
      }                                                                          \
      if (_hs_nmerges <= 1U) {                                                   \
        _hs_looping = 0;                                                         \
        (head)->hh.tbl->tail = _hs_tail;                                         \
        DECLTYPE_ASSIGN(head, ELMT_FROM_HH((head)->hh.tbl, _hs_list));           \
      }                                                                          \
      _hs_insize *= 2U;                                                          \
    }                                                                            \
    HASH_FSCK(hh, head, "HASH_SRT");                                             \
  }                                                                              \
} while (0)

/* 此函数用于将项目从一个哈希选择到另一个哈希。最终结果是所选项目在两个散列中都具有双重存在。没有制作项目的副本；而是通过必须存在于结构中的二级散列散列句柄将它们添加到新散列中。*/
#define HASH_SELECT(hh_dst, dst, hh_src, src, cond)                              \
do {                                                                             \
  unsigned _src_bkt, _dst_bkt;                                                   \
  void *_last_elt = NULL, *_elt;                                                 \
  UT_hash_handle *_src_hh, *_dst_hh, *_last_elt_hh=NULL;                         \
  ptrdiff_t _dst_hho = ((char*)(&(dst)->hh_dst) - (char*)(dst));                 \
  if ((src) != NULL) {                                                           \
    for (_src_bkt=0; _src_bkt < (src)->hh_src.tbl->num_buckets; _src_bkt++) {    \
      for (_src_hh = (src)->hh_src.tbl->buckets[_src_bkt].hh_head;               \
        _src_hh != NULL;                                                         \
        _src_hh = _src_hh->hh_next) {                                            \
        _elt = ELMT_FROM_HH((src)->hh_src.tbl, _src_hh);                         \
        if (cond(_elt)) {                                                        \
          IF_HASH_NONFATAL_OOM( int _hs_oomed = 0; )                             \
          _dst_hh = (UT_hash_handle*)(((char*)_elt) + _dst_hho);                 \
          _dst_hh->key = _src_hh->key;                                           \
          _dst_hh->keylen = _src_hh->keylen;                                     \
          _dst_hh->hashv = _src_hh->hashv;                                       \
          _dst_hh->prev = _last_elt;                                             \
          _dst_hh->next = NULL;                                                  \
          if (_last_elt_hh != NULL) {                                            \
            _last_elt_hh->next = _elt;                                           \
          }                                                                      \
          if ((dst) == NULL) {                                                   \
            DECLTYPE_ASSIGN(dst, _elt);                                          \
            HASH_MAKE_TABLE(hh_dst, dst, _hs_oomed);                             \
            IF_HASH_NONFATAL_OOM(                                                \
              if (_hs_oomed) {                                                   \
                uthash_nonfatal_oom(_elt);                                       \
                (dst) = NULL;                                                    \
                continue;                                                        \
              }                                                                  \
            )                                                                    \
          } else {                                                               \
            _dst_hh->tbl = (dst)->hh_dst.tbl;                                    \
          }                                                                      \
          HASH_TO_BKT(_dst_hh->hashv, _dst_hh->tbl->num_buckets, _dst_bkt);      \
          HASH_ADD_TO_BKT(_dst_hh->tbl->buckets[_dst_bkt], hh_dst, _dst_hh, _hs_oomed); \
          (dst)->hh_dst.tbl->num_items++;                                        \
          IF_HASH_NONFATAL_OOM(                                                  \
            if (_hs_oomed) {                                                     \
              HASH_ROLLBACK_BKT(hh_dst, dst, _dst_hh);                           \
              HASH_DELETE_HH(hh_dst, dst, _dst_hh);                              \
              _dst_hh->tbl = NULL;                                               \
              uthash_nonfatal_oom(_elt);                                         \
              continue;                                                          \
            }                                                                    \
          )                                                                      \
          HASH_BLOOM_ADD(_dst_hh->tbl, _dst_hh->hashv);                          \
          _last_elt = _elt;                                                      \
          _last_elt_hh = _dst_hh;                                                \
        }                                                                        \
      }                                                                          \
    }                                                                            \
  }                                                                              \
  HASH_FSCK(hh_dst, dst, "HASH_SELECT");                                         \
} while (0)

#define HASH_CLEAR(hh,head)                                                      \
do {                                                                             \
  if ((head) != NULL) {                                                          \
    HASH_BLOOM_FREE((head)->hh.tbl);                                             \
    uthash_free((head)->hh.tbl->buckets,                                         \
                (head)->hh.tbl->num_buckets*sizeof(struct UT_hash_bucket));      \
    uthash_free((head)->hh.tbl, sizeof(UT_hash_table));                          \
    (head) = NULL;                                                               \
  }                                                                              \
} while (0)

#define HASH_OVERHEAD(hh,head)                                                   \
 (((head) != NULL) ? (                                                           \
 (size_t)(((head)->hh.tbl->num_items   * sizeof(UT_hash_handle))   +             \
          ((head)->hh.tbl->num_buckets * sizeof(UT_hash_bucket))   +             \
           sizeof(UT_hash_table)                                   +             \
           (HASH_BLOOM_BYTELEN))) : 0U)

#ifdef NO_DECLTYPE
#define HASH_ITER(hh,head,el,tmp)                                                \
for(((el)=(head)), ((*(char**)(&(tmp)))=(char*)((head!=NULL)?(head)->hh.next:NULL)); \
  (el) != NULL; ((el)=(tmp)), ((*(char**)(&(tmp)))=(char*)((tmp!=NULL)?(tmp)->hh.next:NULL)))
#else
#define HASH_ITER(hh,head,el,tmp)                                                \
for(((el)=(head)), ((tmp)=DECLTYPE(el)((head!=NULL)?(head)->hh.next:NULL));      \
  (el) != NULL; ((el)=(tmp)), ((tmp)=DECLTYPE(el)((tmp!=NULL)?(tmp)->hh.next:NULL)))
#endif

/* 获取哈希中的项目数*/
#define HASH_COUNT(head) HASH_CNT(hh,head)
#define HASH_CNT(hh,head) ((head != NULL)?((head)->hh.tbl->num_items):0U)

typedef struct UT_hash_bucket {
   struct UT_hash_handle *hh_head;
   unsigned count;

   /* expand_mult通常设置为0。在这种情况下，最大链长度阈值以其默认值HASH_BKT_CAPACITY_THRESH强制执行。（如果铲斗链超过此长度，将触发铲斗扩展）。然而，将expand_mult设置为非零值会延迟桶扩展（这将由添加到该特定桶而触发），直到其链长度达到HASH_BKT_CAPACITY_THRESH的倍数。（乘数简单地为expand_mult+1）。这个乘数的全部思想是减少桶的扩展，因为在我们知道某个特定的桶可能被过度使用的情况下，它们是昂贵的。与其过于频繁地进行O（n）桶扩展，不如让其链长增长到一个更长但仍有界的值。
    */
   unsigned expand_mult;

} UT_hash_bucket;

/* 仅用于在外部分析中查找哈希表的随机签名*/
#define HASH_SIGNATURE 0xa0111fe1u
#define HASH_BLOOM_SIGNATURE 0xb12220f2u

typedef struct UT_hash_table {
   UT_hash_bucket *buckets;
   unsigned num_buckets, log2_num_buckets;
   unsigned num_items;
   struct UT_hash_handle *tail; /* 应用程序顺序中的尾部hh，用于快速追加*/
   ptrdiff_t hho; /* 哈希句柄偏移量（元素中哈希句柄的字节位置*/

   /* 在理想情况下（所有bucket使用相同），没有一个bucket具有超过ceil（items/buckets）的项。这是理想的链条长度。*/
   unsigned ideal_chain_maxlen;

   /* nonidellitems是哈希中链位置超过理想链maxlen的项目数。这些项目为不均匀的哈希分布付出代价；在链遍历中到达它们需要>理想的步骤*/
   unsigned nonideal_items;

   /* 当执行桶加倍时，会发生无效的扩展，但之后，哈希中超过一半的项具有非理想的链位置。如果这发生在两个连续的扩展上，我们会阻止任何进一步的扩展，因为这没有帮助；当哈希函数不适合密钥域时，就会发生这种情况。当扩展被禁止时，哈希仍然可以工作，尽管不再是固定时间。*/
   unsigned ineff_expands, noexpand;

   uint32_t signature; /* 仅用于在外部分析中查找哈希表*/
#ifdef HASH_BLOOM
   uint32_t bloom_sig; /* 仅用于测试外部分析中是否存在坯料*/
   uint8_t *bloom_bv;
   uint8_t bloom_nbits;
#endif

} UT_hash_table;

typedef struct UT_hash_handle {
   struct UT_hash_table *tbl;
   void *prev;                       /* 应用程序顺序中的prev元素*/
   void *next;                       /* 应用程序顺序中的下一个元素*/
   struct UT_hash_handle *hh_prev;   /* 桶顺序中的上一个hh*/
   struct UT_hash_handle *hh_next;   /* 桶顺序中的下一个hh*/
   void *key;                        /* 封装结构键的指针*/
   unsigned keylen;                  /* 封闭结构的密钥长度*/
   unsigned hashv;                   /* 哈希fcn（key）的结果*/
} UT_hash_handle;

#endif /* UTHASH_H */

