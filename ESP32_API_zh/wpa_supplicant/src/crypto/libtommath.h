/*
 * LibTomMath 0.41中RSA支持的最小代码http://libtom.org/ http://libtom.org/files/ltm-0.41.tar.bz2这个图书馆由汤姆·圣丹尼斯公开发行。
 *
 * 此文件中的组合可能不会使用LibTomMath中的所有优化算法，并且可能比使用默认设置的LibTomMath的速度慢得多。这里有这个版本的主要目的是使构建bignum更容易。c包装，而无需安装和构建外部库。
 *
 * 如果定义了CONFIG_INTERNAL_LIBTOMATH，则为bignum。c包括这个libtommath。c文件，而不是使用外部LibTomMath库。
 */
//#包括“c_types.h”
#include "os.h"
#include "stdarg.h"


#ifndef CHAR_BIT
#define CHAR_BIT 8
#endif

#define BN_MP_INVMOD_C
#define BN_S_MP_EXPTMOD_C /* 注意：tommath_superclass中的#undef。h；这将需要BN_MP_EXPTMOD_FAST_C*/
#define BN_S_MP_MUL_DIGS_C
#define BN_MP_INVMOD_SLOW_C
#define BN_S_MP_SQR_C
#define BN_S_MP_MUL_HIGH_DIGS_C /* 注意：tommath_superclass中的#undef。h；这将需要mp_reduce以外的*/

#ifdef LTM_FAST

/* 使用更快的div，代价约为1kB*/
#define BN_MP_MUL_D_C

/* 在代码中包含更快的exptmod（蒙哥马利），代价约为2.5 kB*/
#define BN_MP_EXPTMOD_FAST_C
#define BN_MP_MONTGOMERY_SETUP_C
#define BN_FAST_MP_MONTGOMERY_REDUCE_C
#define BN_MP_MONTGOMERY_CALC_NORMALIZATION_C
#define BN_MP_MUL_2_C

/* 在代码中包含更快的sqr，代价约为0.5 kB*/
#define BN_FAST_S_MP_SQR_C

#else /* LTM_FAST */

#define BN_MP_DIV_SMALL
#define BN_MP_INIT_MULTI_C
#define BN_MP_CLEAR_MULTI_C
#define BN_MP_ABS_C
#endif /* LTM_FAST */

/* 当前的使用不需要在exptmod中支持负指数，因此我们可以省去invmod，节省约1.5 kB。*/
#define LTM_NO_NEG_EXP

/* 来自tommath。小时*/

#ifndef MIN
   #define MIN(x,y) ((x)<(y)?(x):(y))
#endif

#ifndef MAX
   #define MAX(x,y) ((x)>(y)?(x):(y))
#endif

#define  OPT_CAST(x) (x *)

typedef unsigned long mp_digit;
typedef u64 mp_word;

#define DIGIT_BIT          28
#define MP_28BIT


#define XMALLOC  os_malloc
#define XFREE    os_free
#define XREALLOC os_realloc


#define MP_MASK          ((((mp_digit)1)<<((mp_digit)DIGIT_BIT))-((mp_digit)1))

#define MP_LT        -1   /* 少于*/
#define MP_EQ         0   /* 等于*/
#define MP_GT         1   /* 大于*/

#define MP_ZPOS       0   /* 正整数*/
#define MP_NEG        1   /* 消极的*/

#define MP_OKAY       0   /* 正常结果*/
#define MP_MEM        -2  /* 内存不足*/
#define MP_VAL        -3  /* 无效的输入*/

#define MP_YES        1   /* 是的回答*/
#define MP_NO         0   /* 无响应*/

typedef int           mp_err;

/* 定义它以使用内存使用率较低的例程（主要是导出）*/
#define MP_LOW_MEM

/* 默认精度*/
#ifndef MP_PREC
   #ifndef MP_LOW_MEM
      #define MP_PREC                 32     /* 默认精度位数*/
   #else
      #define MP_PREC                 8      /* 默认精度位数*/
   #endif
#endif

/* 组合数组的大小，应至少为2*2**（BITS_PER_WORD-BITS_PER_DIGIT*2）*/
#define MP_WARRAY               (1 << (sizeof(mp_word) * CHAR_BIT - 2 * DIGIT_BIT + 1))

/* 臭名昭著的mp_int结构*/
typedef struct  {
    int used, alloc, sign;
    mp_digit *dp;
} mp_int;


/* --->基本操作<---*/
#define mp_iszero(a) (((a)->used == 0) ? MP_YES : MP_NO)
#define mp_iseven(a) (((a)->used > 0 && (((a)->dp[0] & 1) == 0)) ? MP_YES : MP_NO)
#define mp_isodd(a)  (((a)->used > 0 && (((a)->dp[0] & 1) == 1)) ? MP_YES : MP_NO)


/* 复制函数的原型*/
#define s_mp_mul(a, b, c) s_mp_mul_digs(a, b, c, (a)->used + (b)->used + 1)
static int s_mp_exptmod(mp_int * G, mp_int * X, mp_int * P, mp_int * Y, int redmode);
static int s_mp_mul_digs (mp_int * a, mp_int * b, mp_int * c, int digs);
static int s_mp_sqr(mp_int * a, mp_int * b);
static int s_mp_mul_high_digs(mp_int * a, mp_int * b, mp_int * c, int digs);

static int fast_s_mp_mul_digs (mp_int * a, mp_int * b, mp_int * c, int digs);

#ifdef BN_MP_INIT_MULTI_C
static int mp_init_multi(mp_int *mp, ...);
#endif
#ifdef BN_MP_CLEAR_MULTI_C
static void mp_clear_multi(mp_int *mp, ...);
#endif
static int mp_lshd(mp_int * a, int b);
static void mp_set(mp_int * a, mp_digit b);
static void mp_clamp(mp_int * a);
static void mp_exch(mp_int * a, mp_int * b);
static void mp_rshd(mp_int * a, int b);
static void mp_zero(mp_int * a);
static int mp_mod_2d(mp_int * a, int b, mp_int * c);
static int mp_div_2d(mp_int * a, int b, mp_int * c, mp_int * d);
static int mp_init_copy(mp_int * a, mp_int * b);
static int mp_mul_2d(mp_int * a, int b, mp_int * c);
#ifndef LTM_NO_NEG_EXP
static int mp_div_2(mp_int * a, mp_int * b);
static int mp_invmod(mp_int * a, mp_int * b, mp_int * c);
static int mp_invmod_slow(mp_int * a, mp_int * b, mp_int * c);
#endif /* LTM_NO_NEG_EXP */
static int mp_copy(mp_int * a, mp_int * b);
static int mp_count_bits(mp_int * a);
static int mp_div(mp_int * a, mp_int * b, mp_int * c, mp_int * d);
static int mp_mod(mp_int * a, mp_int * b, mp_int * c);
static int mp_grow(mp_int * a, int size);
static int mp_cmp_mag(mp_int * a, mp_int * b);
#ifdef BN_MP_ABS_C
static int mp_abs(mp_int * a, mp_int * b);
#endif
static int mp_sqr(mp_int * a, mp_int * b);
static int mp_reduce_2k_l(mp_int *a, mp_int *n, mp_int *d);
static int mp_reduce_2k_setup_l(mp_int *a, mp_int *d);
static int mp_2expt(mp_int * a, int b);
static int mp_reduce_setup(mp_int * a, mp_int * b);
static int mp_reduce(mp_int * x, mp_int * m, mp_int * mu);
static int mp_init_size(mp_int * a, int size);
#ifdef BN_MP_EXPTMOD_FAST_C
static int mp_exptmod_fast (mp_int * G, mp_int * X, mp_int * P, mp_int * Y, int redmode);
#endif /* BN_MP_EXPTMOD_FAST_C */
#ifdef BN_FAST_S_MP_SQR_C
static int fast_s_mp_sqr (mp_int * a, mp_int * b);
#endif /* BN_FAST_S_MP_SQR_C */
#ifdef BN_MP_MUL_D_C
static int mp_mul_d (mp_int * a, mp_digit b, mp_int * c);
#endif /* BN_MP_MUL_D_C */



/* 来自bn_＜func name＞的函数。c*/


/* 反转数组，用于基数代码*/
static void
bn_reverse (unsigned char *s, int len)
{
  int     ix, iy;
  unsigned char t;

  ix = 0;
  iy = len - 1;
  while (ix < iy) {
    t     = s[ix];
    s[ix] = s[iy];
    s[iy] = t;
    ++ix;
    --iy;
  }
}


/* 基于HAC第594页算法14.7的低级加法*/
static int
s_mp_add (mp_int * a, mp_int * b, mp_int * c)
{
  mp_int *x;
  int     olduse, res, min, max;

  /* 找到大小，我们让|a|<=|b|，这意味着我们必须对它们进行排序。“x”将指向数字最多的输入
   */
  if (a->used > b->used) {
    min = b->used;
    max = a->used;
    x = a;
  } else {
    min = a->used;
    max = b->used;
    x = b;
  }

  /* 初始化结果*/
  if (c->alloc < max + 1) {
    if ((res = mp_grow (c, max + 1)) != MP_OKAY) {
      return res;
    }
  }

  /* 获取旧的数字计数并设置新的数字计数*/
  olduse = c->used;
  c->used = max + 1;

  {
    register mp_digit u, *tmpa, *tmpb, *tmpc;
    register int i;

    /* 数字指针的别名*/

    /* 第一次输入*/
    tmpa = a->dp;

    /* 第二输入*/
    tmpb = b->dp;

    /* 目的地*/
    tmpc = c->dp;

    /* 调零进位*/
    u = 0;
    for (i = 0; i < min; i++) {
      /* 计算一位数的总和，T[i]=A[i]+B[i]+U*/
      *tmpc = *tmpa++ + *tmpb++ + u;

      /* U=T[i]的进位位*/
      u = *tmpc >> ((mp_digit)DIGIT_BIT);

      /* 从T[i]中取出进位位*/
      *tmpc++ &= MP_MASK;
    }

    /* 现在复制更高的单词（如果有的话），如果A或B有更多的数字，则在A+B中
     */
    if (min != max) {
      for (; i < max; i++) {
        /* T[i]=X[i]+U*/
        *tmpc = x->dp[i] + u;

        /* U=T[i]的进位位*/
        u = *tmpc >> ((mp_digit)DIGIT_BIT);

        /* 从T[i]中取出进位位*/
        *tmpc++ &= MP_MASK;
      }
    }

    /* 加进位*/
    *tmpc++ = u;

    /* 清除旧数字以上的数字*/
    for (i = c->used; i < olduse; i++) {
      *tmpc++ = 0;
    }
  }

  mp_clamp (c);
  return MP_OKAY;
}


/* 低级减法（假设|a|>|b|），HAC第595页算法14.9*/
static int
s_mp_sub (mp_int * a, mp_int * b, mp_int * c)
{
  int     olduse, res, min, max;

  /* 查找大小*/
  min = b->used;
  max = a->used;

  /* 初始化结果*/
  if (c->alloc < max) {
    if ((res = mp_grow (c, max)) != MP_OKAY) {
      return res;
    }
  }
  olduse = c->used;
  c->used = max;

  {
    register mp_digit u, *tmpa, *tmpb, *tmpc;
    register int i;

    /* 数字指针的别名*/
    tmpa = a->dp;
    tmpb = b->dp;
    tmpc = c->dp;

    /* 将进位设置为零*/
    u = 0;
    for (i = 0; i < min; i++) {
      /* T[i]=A[i]-B[i]-U*/
      *tmpc = *tmpa++ - *tmpb++ - u;

      /* U=T[i]的进位位注意，这节省了执行AND运算，因为如果进位发生，它将一直传播到MSB。因此，一次换档就足以获得进位
       */
      u = *tmpc >> ((mp_digit)(CHAR_BIT * sizeof (mp_digit) - 1));

      /* 从T[i]清除进位*/
      *tmpc++ &= MP_MASK;
    }

    /* 现在复制更高的单词（如果有的话），例如，如果A的数字比B多*/
    for (; i < max; i++) {
      /* T[i]=A[i]-U*/
      *tmpc = *tmpa++ - u;

      /* U=T[i]的进位位*/
      u = *tmpc >> ((mp_digit)(CHAR_BIT * sizeof (mp_digit) - 1));

      /* 从T[i]清除进位*/
      *tmpc++ &= MP_MASK;
    }

    /* 以上使用的数字为整数（因为我们可能没有在上面增长结果）*/
    for (i = c->used; i < olduse; i++) {
      *tmpc++ = 0;
    }
  }

  mp_clamp (c);
  return MP_OKAY;
}


/* 初始化新的mp_int*/
static int
mp_init (mp_int * a)
{
  int i;

  /* 分配所需内存并清除*/
  a->dp = OPT_CAST(mp_digit) XMALLOC (sizeof (mp_digit) * MP_PREC);
  if (a->dp == NULL) {
    return MP_MEM;
  }

  /* 将数字设置为零*/
  for (i = 0; i < MP_PREC; i++) {
      a->dp[i] = 0;
  }

  /* 将used设置为零，将分配的数字设置为默认精度，将符号设置为正*/
  a->used  = 0;
  a->alloc = MP_PREC;
  a->sign  = MP_ZPOS;

  return MP_OKAY;
}


/* 清除一个（释放）*/
static void
mp_clear (mp_int * a)
{
  int i;

  /* 仅在a以前未被释放时执行任何操作*/
  if (a->dp != NULL) {
    /* 先将数字归零*/
    for (i = 0; i < a->used; i++) {
        a->dp[i] = 0;
    }

    /* 自由闸板*/
    XFREE(a->dp);

    /* 重置成员以使调试更容易*/
    a->dp    = NULL;
    a->alloc = a->used = 0;
    a->sign  = MP_ZPOS;
  }
}


/* 高级添加（处理标志）*/
static int
mp_add (mp_int * a, mp_int * b, mp_int * c)
{
  int     sa, sb, res;

  /* 获取两个输入的符号*/
  sa = a->sign;
  sb = b->sign;

  /* 处理两个案件，而不是四个*/
  if (sa == sb) {
    /* 正反两种*/
    /* 加上它们的大小，复制符号*/
    c->sign = sa;
    res = s_mp_add (a, b, c);
  } else {
    /* 一个阳性，另一个阴性*/
    /* 从中减去幅度较大的一个*/
    /* 大小较小的一个。结果得到*/
    /* 幅度较大者的符号。*/
    if (mp_cmp_mag (a, b) == MP_LT) {
      c->sign = sb;
      res = s_mp_sub (b, a, c);
    } else {
      c->sign = sa;
      res = s_mp_sub (a, b, c);
    }
  }
  return res;
}


/* 高级减法（处理符号）*/
static int
mp_sub (mp_int * a, mp_int * b, mp_int * c)
{
  int     sa, sb, res;

  sa = a->sign;
  sb = b->sign;

  if (sa != sb) {
    /* 从正数中减去负数，或*/
    /* 从负数中减去正数。*/
    /* 在任一情况下，*/
    /* 并使用第一个数字的符号。*/
    c->sign = sa;
    res = s_mp_add (a, b, c);
  } else {
    /* 从正数中减去正数，或*/
    /* 从负数中减去负数。*/
    /* 首先，考虑他们之间的差异*/
    /* 大小，然后。。。*/
    if (mp_cmp_mag (a, b) != MP_LT) {
      /* 复制第一个标志*/
      c->sign = sa;
      /* 第一个具有更大或相等的大小*/
      res = s_mp_sub (a, b, c);
    } else {
      /* 结果的*相反*符号来自*/
      /* 第一个数字。*/
      c->sign = (sa == MP_ZPOS) ? MP_NEG : MP_ZPOS;
      /* 第二个震级更大*/
      res = s_mp_sub (b, a, c);
    }
  }
  return res;
}


/* 高级乘法（句柄符号）*/
static int
mp_mul (mp_int * a, mp_int * b, mp_int * c)
{
  int     res, neg;
  neg = (a->sign == b->sign) ? MP_ZPOS : MP_NEG;

  /* 使用Toom Cook？*/
#ifdef BN_MP_TOOM_MUL_C
  if (MIN (a->used, b->used) >= TOOM_MUL_CUTOFF) {
    res = mp_toom_mul(a, b, c);
  } else
#endif
#ifdef BN_MP_KARATSUBA_MUL_C
  /* 使用Karatsuba？*/
  if (MIN (a->used, b->used) >= KARATSUBA_MUL_CUTOFF) {
    res = mp_karatsuba_mul (a, b, c);
  } else
#endif
  {
    /* 我们能用快速乘法器吗？
     *
     * 如果输出的位数小于MP_WARRAY，并且位数不会影响进位传播，则可以使用快速乘法器
     */
#ifdef BN_FAST_S_MP_MUL_DIGS_C
    int     digs = a->used + b->used + 1;

    if ((digs < MP_WARRAY) &&
        MIN(a->used, b->used) <=
        (1 << ((CHAR_BIT * sizeof (mp_word)) - (2 * DIGIT_BIT)))) {
      res = fast_s_mp_mul_digs (a, b, c, digs);
    } else
#endif
#ifdef BN_S_MP_MUL_DIGS_C
      res = s_mp_mul (a, b, c); /* 使用s_mp_mul_digs*/
#else
#error mp_mul could fail
      res = MP_VAL;
#endif

  }
  c->sign = (c->used > 0) ? neg : MP_ZPOS;
  return res;
}


/* d=a*b（模c）*/
static int
mp_mulmod (mp_int * a, mp_int * b, mp_int * c, mp_int * d)
{
  int     res;
  mp_int  t;

  if ((res = mp_init (&t)) != MP_OKAY) {
    return res;
  }

  if ((res = mp_mul (a, b, &t)) != MP_OKAY) {
    mp_clear (&t);
    return res;
  }
  res = mp_mod (&t, c, d);
  mp_clear (&t);
  return res;
}


/* c=模b，0<=c<b*/
static int
mp_mod (mp_int * a, mp_int * b, mp_int * c)
{
  mp_int  t;
  int     res;

  if ((res = mp_init (&t)) != MP_OKAY) {
    return res;
  }

  if ((res = mp_div (a, b, NULL, &t)) != MP_OKAY) {
    mp_clear (&t);
    return res;
  }

  if (t.sign != b->sign) {
    res = mp_add (b, &t, c);
  } else {
    res = MP_OKAY;
    mp_exch (&t, c);
  }

  mp_clear (&t);
  return res;
}


/* 这是一个调用normal或Montgomery exptmod函数的shell函数。最初，对蒙哥马利代码的调用嵌入在正常函数中，但这白白浪费了大量堆栈空间（因为99%的时间都会调用蒙哥马利代码）
 */
static int
mp_exptmod (mp_int * G, mp_int * X, mp_int * P, mp_int * Y)
{
  int dr;

  /* 模量P必须为正*/
  if (P->sign == MP_NEG) {
     return MP_VAL;
  }

  /* 如果指数X为负，我们必须递归*/
  if (X->sign == MP_NEG) {
#ifdef LTM_NO_NEG_EXP
        return MP_VAL;
#else /* LTM_NO_NEG_EXP */
#ifdef BN_MP_INVMOD_C
     mp_int tmpG, tmpX;
     int err;

     /* 首先计算1/G mod P*/
     if ((err = mp_init(&tmpG)) != MP_OKAY) {
        return err;
     }
     if ((err = mp_invmod(G, P, &tmpG)) != MP_OKAY) {
        mp_clear(&tmpG);
        return err;
     }

     /* 现在获取|X|*/
     if ((err = mp_init(&tmpX)) != MP_OKAY) {
        mp_clear(&tmpG);
        return err;
     }
     if ((err = mp_abs(X, &tmpX)) != MP_OKAY) {
        mp_clear_multi(&tmpG, &tmpX, NULL);
        return err;
     }

     /* 现在计算（1/G）**|X|而不是G**X[X<0]*/
     err = mp_exptmod(&tmpG, &tmpX, P, Y);
     mp_clear_multi(&tmpG, &tmpX, NULL);
     return err;
#else
#error mp_exptmod would always fail
     /* 无invmod*/
     return MP_VAL;
#endif
#endif /* LTM_NO_NEG_EXP */
  }

/* 修改的基数缩减*/
#if defined(BN_MP_REDUCE_IS_2K_L_C) && defined(BN_MP_REDUCE_2K_L_C) && defined(BN_S_MP_EXPTMOD_C)
  if (mp_reduce_is_2k_l(P) == MP_YES) {
     return s_mp_exptmod(G, X, P, Y, 1);
  }
#endif

#ifdef BN_MP_DR_IS_MODULUS_C
  /* 它是DR模量吗？*/
  dr = mp_dr_is_modulus(P);
#else
  /* 默认为否*/
  dr = 0;
#endif

#ifdef BN_MP_REDUCE_IS_2K_C
  /* 如果不是，是否为无限制DR模量？*/
  if (dr == 0) {
     dr = mp_reduce_is_2k(P) << 1;
  }
#endif

  /* 如果模量为奇数或dr！=0使用蒙哥马利方法*/
#ifdef BN_MP_EXPTMOD_FAST_C
  if (mp_isodd (P) == 1 || dr !=  0) {
    return mp_exptmod_fast (G, X, P, Y, dr);
  } else {
#endif
#ifdef BN_S_MP_EXPTMOD_C
    (void) dr;
    /* 否则使用通用巴雷特还原技术*/
    return s_mp_exptmod (G, X, P, Y, 0);
#else
#error mp_exptmod could fail
    /* 平摊不赔*/
    return MP_VAL;
#endif
#ifdef BN_MP_EXPTMOD_FAST_C
  }
#endif
}


/* 比较两个int（带符号）*/
static int
mp_cmp (mp_int * a, mp_int * b)
{
  /* 基于符号的比较*/
  if (a->sign != b->sign) {
     if (a->sign == MP_NEG) {
        return MP_LT;
     } else {
        return MP_GT;
     }
  }

  /* 比较数字*/
  if (a->sign == MP_NEG) {
     /* 如果为负，则比较相反方向*/
     return mp_cmp_mag(b, a);
  } else {
     return mp_cmp_mag(a, b);
  }
}


/* 比较一个数字*/
static int
mp_cmp_d(mp_int * a, mp_digit b)
{
  /* 基于符号的比较*/
  if (a->sign == MP_NEG) {
    return MP_LT;
  }

  /* 基于大小的比较*/
  if (a->used > 1) {
    return MP_GT;
  }

  /* 比较a和b的唯一数字*/
  if (a->dp[0] > b) {
    return MP_GT;
  } else if (a->dp[0] < b) {
    return MP_LT;
  } else {
    return MP_EQ;
  }
}


#ifndef LTM_NO_NEG_EXP
/* hac 14.61，第608页*/
static int
mp_invmod (mp_int * a, mp_int * b, mp_int * c)
{
  /* b不能为负*/
  if (b->sign == MP_NEG || mp_iszero(b) == 1) {
    return MP_VAL;
  }

#ifdef BN_FAST_MP_INVMOD_C
  /* 如果模是奇数，我们可以使用更快的例程*/
  if (mp_isodd (b) == 1) {
    return fast_mp_invmod (a, b, c);
  }
#endif

#ifdef BN_MP_INVMOD_SLOW_C
  return mp_invmod_slow(a, b, c);
#endif

#ifndef BN_FAST_MP_INVMOD_C
#ifndef BN_MP_INVMOD_SLOW_C
#error mp_invmod would always fail
#endif
#endif
  return MP_VAL;
}
#endif /* LTM_NO_NEG_EXP */


/* 获取无符号等效项的大小*/
static int
mp_unsigned_bin_size (mp_int * a)
{
  int     size = mp_count_bits (a);
  return (size / 8 + ((size & 7) != 0 ? 1 : 0));
}


#ifndef LTM_NO_NEG_EXP
/* hac 14.61，第608页*/
static int
mp_invmod_slow (mp_int * a, mp_int * b, mp_int * c)
{
  mp_int  x, y, u, v, A, B, C, D;
  int     res;

  /* b不能为负*/
  if (b->sign == MP_NEG || mp_iszero(b) == 1) {
    return MP_VAL;
  }

  /* 初始化时间*/
  if ((res = mp_init_multi(&x, &y, &u, &v,
                           &A, &B, &C, &D, NULL)) != MP_OKAY) {
     return res;
  }

  /* x=a，y=b*/
  if ((res = mp_mod(a, b, &x)) != MP_OKAY) {
      goto LBL_ERR;
  }
  if ((res = mp_copy (b, &y)) != MP_OKAY) {
    goto LBL_ERR;
  }

  /* 2.[修改]如果x和y都是偶数，则返回错误！*/
  if (mp_iseven (&x) == 1 && mp_iseven (&y) == 1) {
    res = MP_VAL;
    goto LBL_ERR;
  }

  /* 3.u=x，v=y，A=1，B=0，C=0，D=1*/
  if ((res = mp_copy (&x, &u)) != MP_OKAY) {
    goto LBL_ERR;
  }
  if ((res = mp_copy (&y, &v)) != MP_OKAY) {
    goto LBL_ERR;
  }
  mp_set (&A, 1);
  mp_set (&D, 1);

top:
  /* 4.当你是偶数的时候*/
  while (mp_iseven (&u) == 1) {
    /* 4.1 u=u/2*/
    if ((res = mp_div_2 (&u, &u)) != MP_OKAY) {
      goto LBL_ERR;
    }
    /* 4.2如果A或B为奇数，则*/
    if (mp_isodd (&A) == 1 || mp_isodd (&B) == 1) {
      /* A=（A+y）/2，B=（B-x）/2*/
      if ((res = mp_add (&A, &y, &A)) != MP_OKAY) {
         goto LBL_ERR;
      }
      if ((res = mp_sub (&B, &x, &B)) != MP_OKAY) {
         goto LBL_ERR;
      }
    }
    /* A = A/2, B = B/2 */
    if ((res = mp_div_2 (&A, &A)) != MP_OKAY) {
      goto LBL_ERR;
    }
    if ((res = mp_div_2 (&B, &B)) != MP_OKAY) {
      goto LBL_ERR;
    }
  }

  /* 5.当v是偶数时*/
  while (mp_iseven (&v) == 1) {
    /* 5.1 v=v/2*/
    if ((res = mp_div_2 (&v, &v)) != MP_OKAY) {
      goto LBL_ERR;
    }
    /* 5.2如果C或D为奇数，则*/
    if (mp_isodd (&C) == 1 || mp_isodd (&D) == 1) {
      /* C=（C+y）/2，D=（D-x）/2*/
      if ((res = mp_add (&C, &y, &C)) != MP_OKAY) {
         goto LBL_ERR;
      }
      if ((res = mp_sub (&D, &x, &D)) != MP_OKAY) {
         goto LBL_ERR;
      }
    }
    /* C = C/2, D = D/2 */
    if ((res = mp_div_2 (&C, &C)) != MP_OKAY) {
      goto LBL_ERR;
    }
    if ((res = mp_div_2 (&D, &D)) != MP_OKAY) {
      goto LBL_ERR;
    }
  }

  /* 6.如果u>=v，则*/
  if (mp_cmp (&u, &v) != MP_LT) {
    /* u=u-v，A=A-C，B=B-D*/
    if ((res = mp_sub (&u, &v, &u)) != MP_OKAY) {
      goto LBL_ERR;
    }

    if ((res = mp_sub (&A, &C, &A)) != MP_OKAY) {
      goto LBL_ERR;
    }

    if ((res = mp_sub (&B, &D, &B)) != MP_OKAY) {
      goto LBL_ERR;
    }
  } else {
    /* v-v-u，C=C-A，D=D-B*/
    if ((res = mp_sub (&v, &u, &v)) != MP_OKAY) {
      goto LBL_ERR;
    }

    if ((res = mp_sub (&C, &A, &C)) != MP_OKAY) {
      goto LBL_ERR;
    }

    if ((res = mp_sub (&D, &B, &D)) != MP_OKAY) {
      goto LBL_ERR;
    }
  }

  /* 如果不是零，转到步骤4*/
  if (mp_iszero (&u) == 0)
    goto top;

  /* 现在a=C，b=D，gcd==g*v*/

  /* 如果v！=1，则没有逆*/
  if (mp_cmp_d (&v, 1) != MP_EQ) {
    res = MP_VAL;
    goto LBL_ERR;
  }

  /* 如果太低*/
  while (mp_cmp_d(&C, 0) == MP_LT) {
      if ((res = mp_add(&C, b, &C)) != MP_OKAY) {
         goto LBL_ERR;
      }
  }

  /* 太大了*/
  while (mp_cmp_mag(&C, b) != MP_LT) {
      if ((res = mp_sub(&C, b, &C)) != MP_OKAY) {
         goto LBL_ERR;
      }
  }

  /* C现在是倒数*/
  mp_exch (&C, c);
  res = MP_OKAY;
LBL_ERR:mp_clear_multi (&x, &y, &u, &v, &A, &B, &C, &D, NULL);
  return res;
}
#endif /* LTM_NO_NEG_EXP */


/* 比较两个int（无符号）的大小*/
static int
mp_cmp_mag (mp_int * a, mp_int * b)
{
  int     n;
  mp_digit *tmpa, *tmpb;

  /* 根据非零位数进行比较*/
  if (a->used > b->used) {
    return MP_GT;
  }

  if (a->used < b->used) {
    return MP_LT;
  }

  /* 的别名*/
  tmpa = a->dp + (a->used - 1);

  /* b的别名*/
  tmpb = b->dp + (a->used - 1);

  /* 基于数字的比较*/
  for (n = 0; n < a->used; ++n, --tmpa, --tmpb) {
    if (*tmpa > *tmpb) {
      return MP_GT;
    }

    if (*tmpa < *tmpb) {
      return MP_LT;
    }
  }
  return MP_EQ;
}


/* 读取无符号字符数组，假设msb首先存储[big endian]*/
static int
mp_read_unsigned_bin (mp_int * a, const unsigned char *b, int c)
{
  int     res;

  /* 确保至少有两个数字*/
  if (a->alloc < 2) {
     if ((res = mp_grow(a, 2)) != MP_OKAY) {
        return res;
     }
  }

  /* 将int归零*/
  mp_zero (a);

  /* 读取中的字节*/
  while (c-- > 0) {
    if ((res = mp_mul_2d (a, 8, a)) != MP_OKAY) {
      return res;
    }

#ifndef MP_8BIT
      a->dp[0] |= *b++;
      a->used += 1;
#else
      a->dp[0] = (*b & MP_MASK);
      a->dp[1] |= ((*b++ >> 7U) & 1);
      a->used += 2;
#endif
  }
  mp_clamp (a);
  return MP_OKAY;
}


/* 以无符号[big endian]格式存储*/
static int
mp_to_unsigned_bin (mp_int * a, unsigned char *b)
{
  int     x, res;
  mp_int  t;

  if ((res = mp_init_copy (&t, a)) != MP_OKAY) {
    return res;
  }

  x = 0;
  while (mp_iszero (&t) == 0) {
#ifndef MP_8BIT
      b[x++] = (unsigned char) (t.dp[0] & 255);
#else
      b[x++] = (unsigned char) (t.dp[0] | ((t.dp[1] & 0x01) << 7));
#endif
    if ((res = mp_div_2d (&t, 8, &t, NULL)) != MP_OKAY) {
      mp_clear (&t);
      return res;
    }
  }
  bn_reverse (b, x);
  mp_clear (&t);
  return MP_OKAY;
}


/* 向右移动一定的位数（在c中存储商，在d中存储可选余数）*/
static int
mp_div_2d (mp_int * a, int b, mp_int * c, mp_int * d)
{
  mp_digit D, r, rr;
  int     x, res;
  mp_int  t;


  /* 如果班次计数<=0，那么我们不做任何工作*/
  if (b <= 0) {
    res = mp_copy (a, c);
    if (d != NULL) {
      mp_zero (d);
    }
    return res;
  }

  if ((res = mp_init (&t)) != MP_OKAY) {
    return res;
  }

  /* 得到剩余的*/
  if (d != NULL) {
    if ((res = mp_mod_2d (a, b, &t)) != MP_OKAY) {
      mp_clear (&t);
      return res;
    }
  }

  /* 复制*/
  if ((res = mp_copy (a, c)) != MP_OKAY) {
    mp_clear (&t);
    return res;
  }

  /* 移位位数*/
  if (b >= (int)DIGIT_BIT) {
    mp_rshd (c, b / DIGIT_BIT);
  }

  /* 移位任何位计数<DIGIT_bit*/
  D = (mp_digit) (b % DIGIT_BIT);
  if (D != 0) {
    register mp_digit *tmpc, mask, shift;

    /* 面具*/
    mask = (((mp_digit)1) << D) - 1;

    /* lsb的移位*/
    shift = DIGIT_BIT - D;

    /* 别名*/
    tmpc = c->dp + (c->used - 1);

    /* 拿*/
    r = 0;
    for (x = c->used - 1; x >= 0; x--) {
      /* 在temp中获取这个单词的低位*/
      rr = *tmpc & mask;

      /* 移位当前字并混合前一个字的进位位*/
      *tmpc = (*tmpc >> D) | (r << shift);
      --tmpc;

      /* 将进位设置为上面找到的当前字的进位位*/
      r = rr;
    }
  }
  mp_clamp (c);
  if (d != NULL) {
    mp_exch (&t, d);
  }
  mp_clear (&t);
  return MP_OKAY;
}


static int
mp_init_copy (mp_int * a, mp_int * b)
{
  int     res;

  if ((res = mp_init (a)) != MP_OKAY) {
    return res;
  }
  return mp_copy (b, a);
}


/* 设置为零*/
static void
mp_zero (mp_int * a)
{
  int       n;
  mp_digit *tmp;

  a->sign = MP_ZPOS;
  a->used = 0;

  tmp = a->dp;
  for (n = 0; n < a->alloc; n++) {
     *tmp++ = 0;
  }
}


/* 副本，b=a*/
static int
mp_copy (mp_int * a, mp_int * b)
{
  int     res, n;

  /* 如果dst==src不执行任何操作*/
  if (a == b) {
    return MP_OKAY;
  }

  /* 增长目标*/
  if (b->alloc < a->used) {
     if ((res = mp_grow (b, a->used)) != MP_OKAY) {
        return res;
     }
  }

  /* 将b归零并复制参数*/
  {
    register mp_digit *tmpa, *tmpb;

    /* 指针别名*/

    /* 来源*/
    tmpa = a->dp;

    /* 目的地*/
    tmpb = b->dp;

    /* 复制所有数字*/
    for (n = 0; n < a->used; n++) {
      *tmpb++ = *tmpa++;
    }

    /* 清除高位数字*/
    for (; n < b->used; n++) {
      *tmpb++ = 0;
    }
  }

  /* 复制使用的计数和签名*/
  b->used = a->used;
  b->sign = a->sign;
  return MP_OKAY;
}


/* 向右移动一定数量的数字*/
static void
mp_rshd (mp_int * a, int b)
{
  int     x;

  /* 如果b<=0，则忽略它*/
  if (b <= 0) {
    return;
  }

  /* 如果使用b>，则只需将其归零并返回*/
  if (a->used <= b) {
    mp_zero (a);
    return;
  }

  {
    register mp_digit *bottom, *top;

    /* 将数字下移*/

    /* 底部*/
    bottom = a->dp;

    /* 顶部[偏移到数字]*/
    top = a->dp + b;

    /* 这被实现为一个滑动窗口，其中窗口为b位数字长，窗口顶部的数字被复制到底部
     *
     * 例如

     b-2|b-1|b0|b1|b2|…|bb |---->/\ |---->\------------------/---->
     */
    for (x = 0; x < (a->used - b); x++) {
      *bottom++ = *top++;
    }

    /* 将顶部数字归零*/
    for (; x < a->used; x++) {
      *bottom++ = 0;
    }
  }

  /* 删除多余的数字*/
  a->used -= b;
}


/* 交换两个整数的元素，如果不能简单地交换mp_int指针
 */
static void
mp_exch (mp_int * a, mp_int * b)
{
  mp_int  t;

  t  = *a;
  *a = *b;
  *b = t;
}


/* 修剪未使用的数字
 *
 * 这用于确保前导零位是三倍的，前导“使用”的数字将是非零的。通常非常快。如果没有更多前导数字，也会修复该符号
 */
static void
mp_clamp (mp_int * a)
{
  /* 当最高有效数字为零时使用的减少。
   */
  while (a->used > 0 && a->dp[a->used - 1] == 0) {
    --(a->used);
  }

  /* 如果使用，则重置标志==0*/
  if (a->used == 0) {
    a->sign = MP_ZPOS;
  }
}


/* 根据需要增长*/
static int
mp_grow (mp_int * a, int size)
{
  int     i;
  mp_digit *tmp;

  /* 如果分配大小较小，则分配更多内存*/
  if (a->alloc < size) {
    /* 确保顶部至少有MP_PREC数字*/
    size += (MP_PREC * 2) - (size % MP_PREC);

    /* 重新分配数组a->dp
     *
     * 我们将返回存储在一个临时变量中，以防操作失败，我们不想覆盖a的dp成员。
     */
    tmp = OPT_CAST(mp_digit) XREALLOC (a->dp, sizeof (mp_digit) * size);
    if (tmp == NULL) {
      /* 重新分配失败，但“a”仍然有效[可以释放]*/
      return MP_MEM;
    }

    /* 重新分配成功，因此设置了->dp*/
    a->dp = tmp;

    /* 零多余数字*/
    i        = a->alloc;
    a->alloc = size;
    for (; i < a->alloc; i++) {
      a->dp[i] = 0;
    }
  }
  return MP_OKAY;
}


#ifdef BN_MP_ABS_C
/* b=|a|
 *
 * 简单函数复制输入并将符号固定为正
 */
static int
mp_abs (mp_int * a, mp_int * b)
{
  int     res;

  /* 将a复制到b*/
  if (a != b) {
     if ((res = mp_copy (a, b)) != MP_OKAY) {
       return res;
     }
  }

  /* 强制b的符号为正*/
  b->sign = MP_ZPOS;

  return MP_OKAY;
}
#endif


/* 设置为数字*/
static void
mp_set (mp_int * a, mp_digit b)
{
  mp_zero (a);
  a->dp[0] = b & MP_MASK;
  a->used  = (a->dp[0] != 0) ? 1 : 0;
}


#ifndef LTM_NO_NEG_EXP
/* b=a/2*/
static int
mp_div_2(mp_int * a, mp_int * b)
{
  int     x, res, oldused;

  /* 复制*/
  if (b->alloc < a->used) {
    if ((res = mp_grow (b, a->used)) != MP_OKAY) {
      return res;
    }
  }

  oldused = b->used;
  b->used = a->used;
  {
    register mp_digit r, rr, *tmpa, *tmpb;

    /* 源别名*/
    tmpa = a->dp + b->used - 1;

    /* dest别名*/
    tmpb = b->dp + b->used - 1;

    /* 拿*/
    r = 0;
    for (x = b->used - 1; x >= 0; x--) {
      /* 获得下一次迭代的进位*/
      rr = *tmpa & 1;

      /* 移动当前数字，添加进位和存储*/
      *tmpb-- = (*tmpa-- >> 1) | (r << (DIGIT_BIT - 1));

      /* 转入下一次迭代*/
      r = rr;
    }

    /* 零多余数字*/
    tmpb = b->dp + b->used;
    for (x = b->used; x < oldused; x++) {
      *tmpb++ = 0;
    }
  }
  b->sign = a->sign;
  mp_clamp (b);
  return MP_OKAY;
}
#endif /* LTM_NO_NEG_EXP */


/* 向左移动某个位数*/
static int
mp_mul_2d (mp_int * a, int b, mp_int * c)
{
  mp_digit d;
  int      res;

  /* 复制*/
  if (a != c) {
     if ((res = mp_copy (a, c)) != MP_OKAY) {
       return res;
     }
  }

  if (c->alloc < (int)(c->used + b/DIGIT_BIT + 1)) {
     if ((res = mp_grow (c, c->used + b / DIGIT_BIT + 1)) != MP_OKAY) {
       return res;
     }
  }

  /* 移位位数*/
  if (b >= (int)DIGIT_BIT) {
    if ((res = mp_lshd (c, b / DIGIT_BIT)) != MP_OKAY) {
      return res;
    }
  }

  /* 移位任何位计数<DIGIT_bit*/
  d = (mp_digit) (b % DIGIT_BIT);
  if (d != 0) {
    register mp_digit *tmpc, shift, mask, r, rr;
    register int x;

    /* 进位位掩码*/
    mask = (((mp_digit)1) << d) - 1;

    /* msbs的移位*/
    shift = DIGIT_BIT - d;

    /* 别名*/
    tmpc = c->dp;

    /* 拿*/
    r    = 0;
    for (x = 0; x < c->used; x++) {
      /* 获取当前单词的高位*/
      rr = (*tmpc >> shift) & mask;

      /* 移位当前字和进位中的“或”*/
      *tmpc = ((*tmpc << d) | r) & MP_MASK;
      ++tmpc;

      /* 将进位设置为当前字的进位位*/
      r = rr;
    }

    /* 设置最终进位*/
    if (r != 0) {
       c->dp[(c->used)++] = r;
    }
  }
  mp_clamp (c);
  return MP_OKAY;
}


#ifdef BN_MP_INIT_MULTI_C
static int
mp_init_multi(mp_int *mp, ...)
{
    mp_err res = MP_OKAY;      /* 假设没有问题，除非另有证明*/
    int n = 0;                 /* ok inits的数量*/
    mp_int* cur_arg = mp;
    va_list args;

    va_start(args, mp);        /* 将args初始化为调用者的下一个参数*/
    while (cur_arg != NULL) {
        if (mp_init(cur_arg) != MP_OKAY) {
            /* 哎呀-错误！回溯并mp_clear我们已经成功初始化的内容，然后返回错误。
            */
            va_list clean_args;

            /* 结束当前列表*/
            va_end(args);

            /* 现在开始清理*/
            cur_arg = mp;
            va_start(clean_args, mp);
            while (n--) {
                mp_clear(cur_arg);
                cur_arg = va_arg(clean_args, mp_int*);
            }
            va_end(clean_args);
            res = MP_MEM;
            break;
        }
        n++;
        cur_arg = va_arg(args, mp_int*);
    }
    va_end(args);
    return res;                /* 如果上面标记了错误，则假定为正常。*/
}
#endif


#ifdef BN_MP_CLEAR_MULTI_C
static void
mp_clear_multi(mp_int *mp, ...)
{
    mp_int* next_mp = mp;
    va_list args;
    va_start(args, mp);
    while (next_mp != NULL) {
        mp_clear(next_mp);
        next_mp = va_arg(args, mp_int*);
    }
    va_end(args);
}
#endif


/* 向左移动一定数量的数字*/
static int
mp_lshd (mp_int * a, int b)
{
  int     x, res;

  /* 如果它小于零返回*/
  if (b <= 0) {
    return MP_OKAY;
  }

  /* 增长以适应新的数字*/
  if (a->alloc < a->used + b) {
     if ((res = mp_grow (a, a->used + b)) != MP_OKAY) {
       return res;
     }
  }

  {
    register mp_digit *top, *bottom;

    /* 用移位量递增，然后向上复制*/
    a->used += b;

    /* 顶部*/
    top = a->dp + a->used - 1;

    /* 基础*/
    bottom = a->dp + a->used - 1 - b;

    /* 与mprshd非常类似，这是使用滑动窗口实现的，但窗口的方向相反。从底部复制到顶部。请参见bn_mp_rshd。c获取更多信息。
     */
    for (x = a->used - 1; x >= b; x--) {
      *top-- = *bottom--;
    }

    /* 将低位数字归零*/
    top = a->dp;
    for (x = 0; x < b; x++) {
      *top++ = 0;
    }
  }
  return MP_OKAY;
}


/* 返回int中的位数*/
static int
mp_count_bits (mp_int * a)
{
  int     r;
  mp_digit q;

  /* 捷径*/
  if (a->used == 0) {
    return 0;
  }

  /* 获取数字并将其相加*/
  r = (a->used - 1) * DIGIT_BIT;

  /* 取最后一个数字并计算其中的位数*/
  q = a->dp[a->used - 1];
  while (q > ((mp_digit) 0)) {
    ++r;
    q >>= ((mp_digit) 1);
  }
  return r;
}


/* 计算a值mod 2**b*/
static int
mp_mod_2d (mp_int * a, int b, mp_int * c)
{
  int     x, res;

  /* 如果b<=0，则将int归零*/
  if (b <= 0) {
    mp_zero (c);
    return MP_OKAY;
  }

  /* 如果模量大于返回值*/
  if (b >= (int) (a->used * DIGIT_BIT)) {
    res = mp_copy (a, c);
    return res;
  }

  /* 复制*/
  if ((res = mp_copy (a, c)) != MP_OKAY) {
    return res;
  }

  /* 模数最后一位以上的零位*/
  for (x = (b / DIGIT_BIT) + ((b % DIGIT_BIT) == 0 ? 0 : 1); x < c->used; x++) {
    c->dp[x] = 0;
  }
  /* 清除不完全在模数外/内的数字*/
  c->dp[b / DIGIT_BIT] &=
    (mp_digit) ((((mp_digit) 1) << (((mp_digit) b) % DIGIT_BIT)) - ((mp_digit) 1));
  mp_clamp (c);
  return MP_OKAY;
}


#ifdef BN_MP_DIV_SMALL

/* 较慢的位爆炸划分…也更小*/
static int
mp_div(mp_int * a, mp_int * b, mp_int * c, mp_int * d)
{
   mp_int ta, tb, tq, q;
   int    res, n, n2;

  /* 除数是零吗？*/
  if (mp_iszero (b) == 1) {
    return MP_VAL;
  }

  /* 如果a<b，则q=0，r=a*/
  if (mp_cmp_mag (a, b) == MP_LT) {
    if (d != NULL) {
      res = mp_copy (a, d);
    } else {
      res = MP_OKAY;
    }
    if (c != NULL) {
      mp_zero (c);
    }
    return res;
  }

  /* 初始化我们的temps*/
  if ((res = mp_init_multi(&ta, &tb, &tq, &q, NULL) != MP_OKAY)) {
     return res;
  }


  mp_set(&tq, 1);
  n = mp_count_bits(a) - mp_count_bits(b);
  if (((res = mp_abs(a, &ta)) != MP_OKAY) ||
      ((res = mp_abs(b, &tb)) != MP_OKAY) ||
      ((res = mp_mul_2d(&tb, n, &tb)) != MP_OKAY) ||
      ((res = mp_mul_2d(&tq, n, &tq)) != MP_OKAY)) {
      goto LBL_ERR;
  }

  while (n-- >= 0) {
     if (mp_cmp(&tb, &ta) != MP_GT) {
        if (((res = mp_sub(&ta, &tb, &ta)) != MP_OKAY) ||
            ((res = mp_add(&q, &tq, &q)) != MP_OKAY)) {
           goto LBL_ERR;
        }
     }
     if (((res = mp_div_2d(&tb, 1, &tb, NULL)) != MP_OKAY) ||
         ((res = mp_div_2d(&tq, 1, &tq, NULL)) != MP_OKAY)) {
           goto LBL_ERR;
     }
  }

  /* 现在q==商和ta==余数*/
  n  = a->sign;
  n2 = (a->sign == b->sign ? MP_ZPOS : MP_NEG);
  if (c != NULL) {
     mp_exch(c, &q);
     c->sign  = (mp_iszero(c) == MP_YES) ? MP_ZPOS : n2;
  }
  if (d != NULL) {
     mp_exch(d, &ta);
     d->sign = (mp_iszero(d) == MP_YES) ? MP_ZPOS : n;
  }
LBL_ERR:
   mp_clear_multi(&ta, &tb, &tq, &q, NULL);
   return res;
}

#else

/* 整数符号除法。cb+d==a[例如a/b，c=商，d=余数]HAC pp.598算法14.20
 *
 * 请注意，HAC中的描述非常不完整。例如，它不考虑数字从内部循环中的“x”中删除的情况。它也不考虑y小于三位数等情况。。
 *
 * HAC的整体算法描述为14.20，但固定用于处理这些情况。
*/
static int
mp_div (mp_int * a, mp_int * b, mp_int * c, mp_int * d)
{
  mp_int  q, x, y, t1, t2;
  int     res, n, t, i, norm, neg;

  /* 除数是零吗？*/
  if (mp_iszero (b) == 1) {
    return MP_VAL;
  }

  /* 如果a<b，则q=0，r=a*/
  if (mp_cmp_mag (a, b) == MP_LT) {
    if (d != NULL) {
      res = mp_copy (a, d);
    } else {
      res = MP_OKAY;
    }
    if (c != NULL) {
      mp_zero (c);
    }
    return res;
  }

  if ((res = mp_init_size (&q, a->used + 2)) != MP_OKAY) {
    return res;
  }
  q.used = a->used + 2;

  if ((res = mp_init (&t1)) != MP_OKAY) {
    goto LBL_Q;
  }

  if ((res = mp_init (&t2)) != MP_OKAY) {
    goto LBL_T1;
  }

  if ((res = mp_init_copy (&x, a)) != MP_OKAY) {
    goto LBL_T2;
  }

  if ((res = mp_init_copy (&y, b)) != MP_OKAY) {
    goto LBL_X;
  }

  /* 固定标志*/
  neg = (a->sign == b->sign) ? MP_ZPOS : MP_NEG;
  x.sign = y.sign = MP_ZPOS;

  /* 规范化x和y，确保y>=b/2，[b==2**DIGIT_BIT]*/
  norm = mp_count_bits(&y) % DIGIT_BIT;
  if (norm < (int)(DIGIT_BIT-1)) {
     norm = (DIGIT_BIT-1) - norm;
     if ((res = mp_mul_2d (&x, norm, &x)) != MP_OKAY) {
       goto LBL_Y;
     }
     if ((res = mp_mul_2d (&y, norm, &y)) != MP_OKAY) {
       goto LBL_Y;
     }
  } else {
     norm = 0;
  }

  /* 注意hac基于0，因此如果使用==5，则其0,1,2,3,4，例如使用4*/
  n = x.used - 1;
  t = y.used - 1;

  /* 而（x>=y*b**n-t）do{q[n-t]+=1；x-=y*b**{n-t}}*/
  if ((res = mp_lshd (&y, n - t)) != MP_OKAY) { /* y=y*b**{n-t}*/
    goto LBL_Y;
  }

  while (mp_cmp (&x, &y) != MP_LT) {
    ++(q.dp[n - t]);
    if ((res = mp_sub (&x, &y, &x)) != MP_OKAY) {
      goto LBL_Y;
    }
  }

  /* 通过向下移动重置y*/
  mp_rshd (&y, n - t);

  /* 步骤3.对于i，从n向下到（t+1）*/
  for (i = n; i >= (t + 1); i--) {
    if (i > x.used) {
      continue;
    }

    /* 步骤3.1如果xi==yt，则将q{i-t-1}设置为b-1，否则将q{i-t-1}s设置为（xi*b+x{i-1}）/yt*/
    if (x.dp[i] == y.dp[t]) {
      q.dp[i - t - 1] = ((((mp_digit)1) << DIGIT_BIT) - 1);
    } else {
      mp_word tmp;
      tmp = ((mp_word) x.dp[i]) << ((mp_word) DIGIT_BIT);
      tmp |= ((mp_word) x.dp[i - 1]);
      tmp /= ((mp_word) y.dp[t]);
      if (tmp > (mp_word) MP_MASK)
        tmp = MP_MASK;
      q.dp[i - t - 1] = (mp_digit) (tmp & (mp_word) (MP_MASK));
    }

    /* 而（q{i-t-1}*（yt*b+y{t-1}）>xi b2+xi-1b+xi-2

       do-{i--1}-=1；
    */
    q.dp[i - t - 1] = (q.dp[i - t - 1] + 1) & MP_MASK;
    do {
      q.dp[i - t - 1] = (q.dp[i - t - 1] - 1) & MP_MASK;

      /* 查找左手*/
      mp_zero (&t1);
      t1.dp[0] = (t - 1 < 0) ? 0 : y.dp[t - 1];
      t1.dp[1] = y.dp[t];
      t1.used = 2;
      if ((res = mp_mul_d (&t1, q.dp[i - t - 1], &t1)) != MP_OKAY) {
        goto LBL_Y;
      }

      /* 找到右手*/
      t2.dp[0] = (i - 2 < 0) ? 0 : x.dp[i - 2];
      t2.dp[1] = (i - 1 < 0) ? 0 : x.dp[i - 1];
      t2.dp[2] = x.dp[i];
      t2.used = 3;
    } while (mp_cmp_mag(&t1, &t2) == MP_GT);

    /* 步骤3.3 x=x-q｛i-t-1｝*y*b**｛i-i-1｝*/
    if ((res = mp_mul_d (&y, q.dp[i - t - 1], &t1)) != MP_OKAY) {
      goto LBL_Y;
    }

    if ((res = mp_lshd (&t1, i - t - 1)) != MP_OKAY) {
      goto LBL_Y;
    }

    if ((res = mp_sub (&x, &t1, &x)) != MP_OKAY) {
      goto LBL_Y;
    }

    /* 如果x＜0，则{x＝x+y*b**{i-i-1}；q｛i-t-1｝-=1；｝*/
    if (x.sign == MP_NEG) {
      if ((res = mp_copy (&y, &t1)) != MP_OKAY) {
        goto LBL_Y;
      }
      if ((res = mp_lshd (&t1, i - t - 1)) != MP_OKAY) {
        goto LBL_Y;
      }
      if ((res = mp_add (&x, &t1, &x)) != MP_OKAY) {
        goto LBL_Y;
      }

      q.dp[i - t - 1] = (q.dp[i - t - 1] - 1UL) & MP_MASK;
    }
  }

  /* 现在q是商，x是余数[我们必须归一化]
   */

  /* 在给c写信之前先签名*/
  x.sign = x.used == 0 ? MP_ZPOS : a->sign;

  if (c != NULL) {
    mp_clamp (&q);
    mp_exch (&q, c);
    c->sign = neg;
  }

  if (d != NULL) {
    mp_div_2d (&x, norm, &x, NULL);
    mp_exch (&x, d);
  }

  res = MP_OKAY;

LBL_Y:mp_clear (&y);
LBL_X:mp_clear (&x);
LBL_T2:mp_clear (&t2);
LBL_T1:mp_clear (&t1);
LBL_Q:mp_clear (&q);
  return res;
}

#endif


#ifdef MP_LOW_MEM
   #define TAB_SIZE 32
#else
   #define TAB_SIZE 256
#endif

static int
s_mp_exptmod (mp_int * G, mp_int * X, mp_int * P, mp_int * Y, int redmode)
{
  mp_int  M[TAB_SIZE], res, mu;
  mp_digit buf;
  int     err, bitbuf, bitcpy, bitcnt, mode, digidx, x, y, winsize;
  int (*redux)(mp_int*,mp_int*,mp_int*);

  /* 查找窗口大小*/
  x = mp_count_bits (X);
  if (x <= 7) {
    winsize = 2;
  } else if (x <= 36) {
    winsize = 3;
  } else if (x <= 140) {
    winsize = 4;
  } else if (x <= 450) {
    winsize = 5;
  } else if (x <= 1303) {
    winsize = 6;
  } else if (x <= 3529) {
    winsize = 7;
  } else {
    winsize = 8;
  }

#ifdef MP_LOW_MEM
    if (winsize > 5) {
       winsize = 5;
    }
#endif

  /* init M数组*/
  /* 初始化第一个单元格*/
  if ((err = mp_init(&M[1])) != MP_OKAY) {
     return err;
  }

  /* 现在初始化数组的后半部分*/
  for (x = 1<<(winsize-1); x < (1 << winsize); x++) {
    if ((err = mp_init(&M[x])) != MP_OKAY) {
      for (y = 1<<(winsize-1); y < x; y++) {
        mp_clear (&M[y]);
      }
      mp_clear(&M[1]);
      return err;
    }
  }

  /* 创建mu，用于巴雷特还原*/
  if ((err = mp_init (&mu)) != MP_OKAY) {
    goto LBL_M;
  }

  if (redmode == 0) {
     if ((err = mp_reduce_setup (&mu, P)) != MP_OKAY) {
        goto LBL_MU;
     }
     redux = mp_reduce;
  } else {
     if ((err = mp_reduce_2k_setup_l (P, &mu)) != MP_OKAY) {
        goto LBL_MU;
     }
     redux = mp_reduce_2k_l;
  }

  /* 创建M表
   *
   * M表包含基数的幂，例如M[x]=Gx mod P
   *
   * 虽然接受M[0]和M[1]，但未计算表的前半部分
   */
  if ((err = mp_mod (G, P, &M[1])) != MP_OKAY) {
    goto LBL_MU;
  }

  /* 通过将M[1]（winsize-1）乘以平方，计算M[1<<（winize-1）]处的值
   */
  if ((err = mp_copy (&M[1], &M[1 << (winsize - 1)])) != MP_OKAY) {
    goto LBL_MU;
  }

  for (x = 0; x < (winsize - 1); x++) {
    /* 把它弄成正方形*/
    if ((err = mp_sqr (&M[1 << (winsize - 1)],
                       &M[1 << (winsize - 1)])) != MP_OKAY) {
      goto LBL_MU;
    }

    /* 降模P*/
    if ((err = redux (&M[1 << (winsize - 1)], P, &mu)) != MP_OKAY) {
      goto LBL_MU;
    }
  }

  /* 创建上表，即M[x]=M[x-1]*M[1]（mod P），对于x=（2（winsize-1）+1）到（2winsize-1）
   */
  for (x = (1 << (winsize - 1)) + 1; x < (1 << winsize); x++) {
    if ((err = mp_mul (&M[x - 1], &M[1], &M[x])) != MP_OKAY) {
      goto LBL_MU;
    }
    if ((err = redux (&M[x], P, &mu)) != MP_OKAY) {
      goto LBL_MU;
    }
  }

  /* 设置结果*/
  if ((err = mp_init (&res)) != MP_OKAY) {
    goto LBL_MU;
  }
  mp_set (&res, 1);

  /* 设置初始模式和位cnt*/
  mode   = 0;
  bitcnt = 1;
  buf    = 0;
  digidx = X->used - 1;
  bitcpy = 0;
  bitbuf = 0;

  for (;;) {
    /* 根据需要抓取下一个数字*/
    if (--bitcnt == 0) {
      /* 如果digidx==-1，我们的位数不足*/
      if (digidx == -1) {
        break;
      }
      /* 读取下一个数字并重置位cnt*/
      buf    = X->dp[digidx--];
      bitcnt = (int) DIGIT_BIT;
    }

    /* 从指数中获取下一个msb*/
    y     = (buf >> (mp_digit)(DIGIT_BIT - 1)) & 1;
    buf <<= (mp_digit)1;

    /* 如果位为零且模式==0，则忽略它。这些表示指数中第一个1位之前的前导零位。从技术上讲，这个选项不是必需的，但它确实降低了所使用的平凡平方/缩减的数量
     */
    if (mode == 0 && y == 0) {
      continue;
    }

    /* 如果位为零且模式==1，则我们求平方*/
    if (mode == 1 && y == 0) {
      if ((err = mp_sqr (&res, &res)) != MP_OKAY) {
        goto LBL_RES;
      }
      if ((err = redux (&res, P, &mu)) != MP_OKAY) {
        goto LBL_RES;
      }
      continue;
    }

    /* 否则我们将其添加到窗口*/
    bitbuf |= (y << (winsize - ++bitcpy));
    mode    = 2;

    if (bitcpy == winsize) {
      /* ok窗口根据需要填充成正方形，然后相乘*/
      /* 正方形优先*/
      for (x = 0; x < winsize; x++) {
        if ((err = mp_sqr (&res, &res)) != MP_OKAY) {
          goto LBL_RES;
        }
        if ((err = redux (&res, P, &mu)) != MP_OKAY) {
          goto LBL_RES;
        }
      }

      /* 然后相乘*/
      if ((err = mp_mul (&res, &M[bitbuf], &res)) != MP_OKAY) {
        goto LBL_RES;
      }
      if ((err = redux (&res, P, &mu)) != MP_OKAY) {
        goto LBL_RES;
      }

      /* 清空窗口并重置*/
      bitcpy = 0;
      bitbuf = 0;
      mode   = 1;
    }
  }

  /* 如果保留位，则平方/乘法*/
  if (mode == 2 && bitcpy > 0) {
    /* 如果设置了位，则进行平方运算*/
    for (x = 0; x < bitcpy; x++) {
      if ((err = mp_sqr (&res, &res)) != MP_OKAY) {
        goto LBL_RES;
      }
      if ((err = redux (&res, P, &mu)) != MP_OKAY) {
        goto LBL_RES;
      }

      bitbuf <<= 1;
      if ((bitbuf & (1 << winsize)) != 0) {
        /* 然后相乘*/
        if ((err = mp_mul (&res, &M[1], &res)) != MP_OKAY) {
          goto LBL_RES;
        }
        if ((err = redux (&res, P, &mu)) != MP_OKAY) {
          goto LBL_RES;
        }
      }
    }
  }

  mp_exch (&res, Y);
  err = MP_OKAY;
LBL_RES:mp_clear (&res);
LBL_MU:mp_clear (&mu);
LBL_M:
  mp_clear(&M[1]);
  for (x = 1<<(winsize-1); x < (1 << winsize); x++) {
    mp_clear (&M[x]);
  }
  return err;
}


/* 计算b=a*a*/
static int
mp_sqr (mp_int * a, mp_int * b)
{
  int     res;

#ifdef BN_MP_TOOM_SQR_C
  /* 使用Toom Cook？*/
  if (a->used >= TOOM_SQR_CUTOFF) {
    res = mp_toom_sqr(a, b);
  /* 卡拉津巴？*/
  } else
#endif
#ifdef BN_MP_KARATSUBA_SQR_C
if (a->used >= KARATSUBA_SQR_CUTOFF) {
    res = mp_karatsuba_sqr (a, b);
  } else
#endif
  {
#ifdef BN_FAST_S_MP_SQR_C
    /* 我们可以使用快速组合乘数吗？*/
    if ((a->used * 2 + 1) < MP_WARRAY &&
         a->used <
         (1 << (sizeof(mp_word) * CHAR_BIT - 2*DIGIT_BIT - 1))) {
      res = fast_s_mp_sqr (a, b);
    } else
#endif
#ifdef BN_S_MP_SQR_C
      res = s_mp_sqr (a, b);
#else
#error mp_sqr could fail
      res = MP_VAL;
#endif
  }
  b->sign = MP_ZPOS;
  return res;
}


/* 这与reduce_2k不同，因为“d”可以大于一个数字。
*/
static int
mp_reduce_2k_l(mp_int *a, mp_int *n, mp_int *d)
{
   mp_int q;
   int    p, res;

   if ((res = mp_init(&q)) != MP_OKAY) {
      return res;
   }

   p = mp_count_bits(n);
top:
   /* q=a/2*p，a=a模2**p*/
   if ((res = mp_div_2d(a, p, &q, a)) != MP_OKAY) {
      goto ERR;
   }

   /* q=q*d*/
   if ((res = mp_mul(&q, d, &q)) != MP_OKAY) {
      goto ERR;
   }

   /* a=a+q*/
   if ((res = s_mp_add(a, &q, a)) != MP_OKAY) {
      goto ERR;
   }

   if (mp_cmp_mag(a, n) != MP_LT) {
      s_mp_sub(a, n, a);
      goto top;
   }

ERR:
   mp_clear(&q);
   return res;
}


/* 确定设置值*/
static int
mp_reduce_2k_setup_l(mp_int *a, mp_int *d)
{
   int    res;
   mp_int tmp;

   if ((res = mp_init(&tmp)) != MP_OKAY) {
      return res;
   }

   if ((res = mp_2expt(&tmp, mp_count_bits(a))) != MP_OKAY) {
      goto ERR;
   }

   if ((res = s_mp_sub(&tmp, a, d)) != MP_OKAY) {
      goto ERR;
   }

ERR:
   mp_clear(&tmp);
   return res;
}


/* 计算a=2**b
 *
 * 一个简单的算法，它将整数调零，然后将其增长，然后根据需要设置一位。
 */
static int
mp_2expt (mp_int * a, int b)
{
  int     res;

  /* 默认值为零*/
  mp_zero (a);

  /* 增长a以容纳单个位*/
  if ((res = mp_grow (a, b / DIGIT_BIT + 1)) != MP_OKAY) {
    return res;
  }

  /* 设置该位的使用计数*/
  a->used = b / DIGIT_BIT + 1;

  /* 把钻头放在原位*/
  a->dp[b / DIGIT_BIT] = ((mp_digit)1) << (b % DIGIT_BIT);

  return MP_OKAY;
}


/* 预先计算巴雷特折减所需的值对于给定的模量“b”，它计算“a”中所需的数值
 */
static int
mp_reduce_setup (mp_int * a, mp_int * b)
{
  int     res;

  if ((res = mp_2expt (a, b->used * 2 * DIGIT_BIT)) != MP_OKAY) {
    return res;
  }
  return mp_div (a, b, a, NULL);
}


/* 减少x mod m，假设0<x<m**2，mu通过mp_reduce_setup预先计算。摘自HAC第604页算法14.42
 */
static int
mp_reduce (mp_int * x, mp_int * m, mp_int * mu)
{
  mp_int  q;
  int     res, um = m->used;

  /* q=x*/
  if ((res = mp_init_copy (&q, x)) != MP_OKAY) {
    return res;
  }

  /* q1=x/b**（k-1）*/
  mp_rshd (&q, um - 1);

  /* 根据HAC的说法，这种优化是可以的*/
  if (((unsigned long) um) > (((mp_digit)1) << (DIGIT_BIT - 1))) {
    if ((res = mp_mul (&q, mu, &q)) != MP_OKAY) {
      goto CLEANUP;
    }
  } else {
#ifdef BN_S_MP_MUL_HIGH_DIGS_C
    if ((res = s_mp_mul_high_digs (&q, mu, &q, um)) != MP_OKAY) {
      goto CLEANUP;
    }
#elif defined(BN_FAST_S_MP_MUL_HIGH_DIGS_C)
    if ((res = fast_s_mp_mul_high_digs (&q, mu, &q, um)) != MP_OKAY) {
      goto CLEANUP;
    }
#else
    {
#error mp_reduce would always fail
      res = MP_VAL;
      goto CLEANUP;
    }
#endif
  }

  /* q3=q2/b**（k+1）*/
  mp_rshd (&q, um + 1);

  /* x=x mod b**（k+1），快速（无除法）*/
  if ((res = mp_mod_2d (x, DIGIT_BIT * (um + 1), x)) != MP_OKAY) {
    goto CLEANUP;
  }

  /* q=q*m mod b**（k+1），快速（无除法）*/
  if ((res = s_mp_mul_digs (&q, m, &q, um + 1)) != MP_OKAY) {
    goto CLEANUP;
  }

  /* x=x-q*/
  if ((res = mp_sub (x, &q, x)) != MP_OKAY) {
    goto CLEANUP;
  }

  /* 如果x<0，则将b**（k+1）添加到其中*/
  if (mp_cmp_d (x, 0) == MP_LT) {
    mp_set (&q, 1);
    if ((res = mp_lshd (&q, um + 1)) != MP_OKAY) {
      goto CLEANUP;
    }
    if ((res = mp_add (x, &q, x)) != MP_OKAY) {
      goto CLEANUP;
    }
  }

  /* 如果它太大，就退后*/
  while (mp_cmp (x, m) != MP_LT) {
    if ((res = s_mp_sub (x, m, x)) != MP_OKAY) {
      goto CLEANUP;
    }
  }

CLEANUP:
  mp_clear (&q);

  return res;
}


/* 乘以|a|*|b|，只计算结果的位数，HAC第595页，算法14.12修改，以便您可以控制创建的输出位数。
 */
static int
s_mp_mul_digs (mp_int * a, mp_int * b, mp_int * c, int digs)
{
  mp_int  t;
  int     res, pa, pb, ix, iy;
  mp_digit u;
  mp_word r;
  mp_digit tmpx, *tmpt, *tmpy;

  /* 我们能用快速乘法器吗？*/
  if (((digs) < MP_WARRAY) &&
      MIN (a->used, b->used) <
          (1 << ((CHAR_BIT * sizeof (mp_word)) - (2 * DIGIT_BIT)))) {
    return fast_s_mp_mul_digs (a, b, c, digs);
  }

  if ((res = mp_init_size (&t, digs)) != MP_OKAY) {
    return res;
  }
  t.used = digs;

  /* 直接计算乘积的位数*/
  pa = a->used;
  for (ix = 0; ix < pa; ix++) {
    /* 将进位设置为零*/
    u = 0;

    /* 限制我们自己制作数字输出*/
    pb = MIN (b->used, digs - ix);

    /* 设置一些别名*/
    /* 嵌套循环中使用的数字的副本*/
    tmpx = a->dp[ix];

    /* 目的地的别名移位了九个位置*/
    tmpt = t.dp + ix;

    /* b位数的别名*/
    tmpy = b->dp;

    /* 计算输出的列并传播进位*/
    for (iy = 0; iy < pb; iy++) {
      /* 将列计算为mp_word*/
      r       = ((mp_word)*tmpt) +
                ((mp_word)tmpx) * ((mp_word)*tmpy++) +
                ((mp_word) u);

      /* 新列是结果的下部*/
      *tmpt++ = (mp_digit) (r & ((mp_word) MP_MASK));

      /* 从结果中得到进位字*/
      u       = (mp_digit) (r >> ((mp_word) DIGIT_BIT));
    }
    /* 如果放置在挖掘下方，则设置进位*/
    if (ix + iy < digs) {
      *tmpt = u;
    }
  }

  mp_clamp (&t);
  mp_exch (&t, c);

  mp_clear (&t);
  return MP_OKAY;
}


/* 快速（组合）乘法器
 *
 * 这是快速列数组[comba]乘数。它的设计是先计算产品的列，然后再处理进位。这使得计算列的嵌套循环非常简单，并且可以在超级标量处理器上进行调度。
 *
 * 这已被修改为产生可变位数的输出，因此如果只需要一半的乘积，则无需计算上半（快速巴雷特缩减所需的特征）。
 *
 * 基于HAC第595页的算法14.12。
 *
 */
static int
fast_s_mp_mul_digs (mp_int * a, mp_int * b, mp_int * c, int digs)
{
  int     olduse, res, pa, ix, iz;
  mp_digit W[MP_WARRAY];
  register mp_word  _W;

  /* 根据需要增加目标*/
  if (c->alloc < digs) {
    if ((res = mp_grow (c, digs)) != MP_OKAY) {
      return res;
    }
  }

  /* 要生成的输出位数*/
  pa = MIN(digs, a->used + b->used);

  /* 清除进位*/
  _W = 0;
  for (ix = 0; ix < pa; ix++) {
      int      tx, ty;
      int      iy;
      mp_digit *tmpx, *tmpy;

      /* 获取两个bignum的偏移量*/
      ty = MIN(b->used-1, ix);
      tx = ix - ty;

      /* 设置临时别名*/
      tmpx = a->dp + tx;
      tmpy = b->dp + ty;

      /* 这是循环迭代的次数，本质上是在（tx++<a->used&&ty->=0）{…}
       */
      iy = MIN(a->used-tx, ty+1);

      /* 执行循环*/
      for (iz = 0; iz < iy; ++iz) {
         _W += ((mp_word)*tmpx++)*((mp_word)*tmpy--);

      }

      /* 存储期限*/
      W[ix] = ((mp_digit)_W) & MP_MASK;

      /* 进行下一次进位*/
      _W = _W >> ((mp_word)DIGIT_BIT);
 }

  /* 设置目标*/
  olduse  = c->used;
  c->used = pa;

  {
    register mp_digit *tmpc;
    tmpc = c->dp;
    for (ix = 0; ix < pa+1; ix++) {
      /* 现在提取上一个数字[进位以下]*/
      *tmpc++ = W[ix];
    }

    /* 清除未使用的数字[存在于c的旧副本中]*/
    for (; ix < olduse; ix++) {
      *tmpc++ = 0;
    }
  }
  mp_clamp (c);
  return MP_OKAY;
}


/* 为给定大小初始化mp_init*/
static int
mp_init_size (mp_int * a, int size)
{
  int x;

  /* 衬垫大小，因此总是有额外的数字*/
  size += (MP_PREC * 2) - (size % MP_PREC);

  /* 分配内存*/
  a->dp = OPT_CAST(mp_digit) XMALLOC (sizeof (mp_digit) * size);
  if (a->dp == NULL) {
    return MP_MEM;
  }

  /* 设置成员*/
  a->used  = 0;
  a->alloc = size;
  a->sign  = MP_ZPOS;

  /* 将数字归零*/
  for (x = 0; x < size; x++) {
      a->dp[x] = 0;
  }

  return MP_OKAY;
}


/* 低电平平方，b=a*a，HAC第596-597页，算法14.16*/
static int
s_mp_sqr (mp_int * a, mp_int * b)
{
  mp_int  t;
  int     res, ix, iy, pa;
  mp_word r;
  mp_digit u, tmpx, *tmpt;

  pa = a->used;
  if ((res = mp_init_size (&t, 2*pa + 1)) != MP_OKAY) {
    return res;
  }

  /* 默认使用的是最大可能大小*/
  t.used = 2*pa + 1;

  for (ix = 0; ix < pa; ix++) {
    /* 首先计算2*ix处的数字*/
    /* 计算双精度结果*/
    r = ((mp_word) t.dp[2*ix]) +
        ((mp_word)a->dp[ix])*((mp_word)a->dp[ix]);

    /* 将下部存储在结果中*/
    t.dp[ix+ix] = (mp_digit) (r & ((mp_word) MP_MASK));

    /* 得到支持*/
    u           = (mp_digit)(r >> ((mp_word) DIGIT_BIT));

    /* A[ix]*A[iy]的左侧*/
    tmpx        = a->dp[ix];

    /* 存储结果的别名*/
    tmpt        = t.dp + (2*ix + 1);

    for (iy = ix + 1; iy < pa; iy++) {
      /* 首先计算乘积*/
      r       = ((mp_word)tmpx) * ((mp_word)a->dp[iy]);

      /* 现在计算双倍精度的结果，注意我们使用加法而不是2，因为它更容易优化
       */
      r       = ((mp_word) *tmpt) + r + r + ((mp_word) u);

      /* 存储下部*/
      *tmpt++ = (mp_digit) (r & ((mp_word) MP_MASK));

      /* 获得进位*/
      u       = (mp_digit)(r >> ((mp_word) DIGIT_BIT));
    }
    /* 向上传播*/
    while (u != ((mp_digit) 0)) {
      r       = ((mp_word) *tmpt) + ((mp_word) u);
      *tmpt++ = (mp_digit) (r & ((mp_word) MP_MASK));
      u       = (mp_digit)(r >> ((mp_word) DIGIT_BIT));
    }
  }

  mp_clamp (&t);
  mp_exch (&t, b);
  mp_clear (&t);
  return MP_OKAY;
}


/* 乘以|a|*|b|，不计算低位数字[意味着得到乘积的高位]
 */
static int
s_mp_mul_high_digs (mp_int * a, mp_int * b, mp_int * c, int digs)
{
  mp_int  t;
  int     res, pa, pb, ix, iy;
  mp_digit u;
  mp_word r;
  mp_digit tmpx, *tmpt, *tmpy;

  /* 我们能用快速乘法器吗？*/
#ifdef BN_FAST_S_MP_MUL_HIGH_DIGS_C
  if (((a->used + b->used + 1) < MP_WARRAY)
      && MIN (a->used, b->used) < (1 << ((CHAR_BIT * sizeof (mp_word)) - (2 * DIGIT_BIT)))) {
    return fast_s_mp_mul_high_digs (a, b, c, digs);
  }
#endif

  if ((res = mp_init_size (&t, a->used + b->used + 1)) != MP_OKAY) {
    return res;
  }
  t.used = a->used + b->used + 1;

  pa = a->used;
  pb = b->used;
  for (ix = 0; ix < pa; ix++) {
    /* 清除进位*/
    u = 0;

    /* A[ix]*B[iy]的左侧*/
    tmpx = a->dp[ix];

    /* 存储数字的地址的别名*/
    tmpt = &(t.dp[digs]);

    /* 从何处读取右手边的别名*/
    tmpy = b->dp + (digs - ix);

    for (iy = digs - ix; iy < pb; iy++) {
      /* 计算双精度结果*/
      r       = ((mp_word)*tmpt) +
                ((mp_word)tmpx) * ((mp_word)*tmpy++) +
                ((mp_word) u);

      /* 得到下半部分*/
      *tmpt++ = (mp_digit) (r & ((mp_word) MP_MASK));

      /* 随身携带*/
      u       = (mp_digit) (r >> ((mp_word) DIGIT_BIT));
    }
    *tmpt = u;
  }
  mp_clamp (&t);
  mp_exch (&t, c);
  mp_clear (&t);
  return MP_OKAY;
}


#ifdef BN_MP_MONTGOMERY_SETUP_C
/* 设置蒙哥马利还原材料*/
static int
mp_montgomery_setup (mp_int * n, mp_digit * rho)
{
  mp_digit x, b;

/* 快速反转模2**k
 *
 * 基于以下事实
 *
 * XA=1（模2**n）=>（X（2-XA））A=1（模2**2n）=>2XA-XXAA=1=>2（1）-（1）=1
 */
  b = n->dp[0];

  if ((b & 1) == 0) {
    return MP_VAL;
  }

  x = (((b + 2) & 4) << 1) + b; /* 这里x*a==1模2**4*/
  x *= 2 - b * x;               /* 这里x*a==1模2**8*/
#if !defined(MP_8BIT)
  x *= 2 - b * x;               /* 这里x*a==1模2**16*/
#endif
#if defined(MP_64BIT) || !(defined(MP_8BIT) || defined(MP_16BIT))
  x *= 2 - b * x;               /* 这里x*a==1模2**32*/
#endif
#ifdef MP_64BIT
  x *= 2 - b * x;               /* 这里x*a==1模2**64*/
#endif

  /* ρ=-1/m模b*/
  *rho = (unsigned long)(((mp_word)1 << ((mp_word) DIGIT_BIT)) - x) & MP_MASK;

  return MP_OKAY;
}
#endif


#ifdef BN_FAST_MP_MONTGOMERY_REDUCE_C
/* 通过Montgomery Reduction计算xR**-1==x（mod N）
 *
 * 这是montgomery_reduce的优化实现，它使用comba方法快速计算缩减的列。
 *
 * 基于HAC第601页的算法14.32。
*/
int
fast_mp_montgomery_reduce (mp_int * x, mp_int * n, mp_digit rho)
{
  int     ix, res, olduse;
  mp_word W[MP_WARRAY];

  /* 获取旧的旧计数*/
  olduse = x->used;

  /* 根据需要增长*/
  if (x->alloc < n->used + 1) {
    if ((res = mp_grow (x, n->used + 1)) != MP_OKAY) {
      return res;
    }
  }

  /* 首先，我们必须将输入的数字输入到双精度字W[…]的数组中
   */
  {
    register mp_word *_W;
    register mp_digit *tmpx;

    /* W[]数组的别名*/
    _W   = W;

    /* x的数字别名*/
    tmpx = x->dp;

    /* 将a的数字复制到W[0..a->used-1]*/
    for (ix = 0; ix < x->used; ix++) {
      *_W++ = *tmpx++;
    }

    /* 将W的高位字归零[a->已使用..m->已使用*2]*/
    for (; ix < n->used * 2 + 1; ix++) {
      *_W++ = 0;
    }
  }

  /* 现在，我们从最低有效位开始向上连续零位
   */
  for (ix = 0; ix < n->used; ix++) {
    /* μ=ai*m'模b
     *
     * 我们通过将值向下转换为mp_digit来避免双精度乘法（这不是必需的）。注意，这需要W[ix-1]清除进位（请参见内部循环后的内容）
     */
    register mp_digit mu;
    mu = (mp_digit) (((W[ix] & MP_MASK) * rho) & MP_MASK);

    /* a=a+μ*m*b**i
     *
     * 这是实时计算的。通过偏移将结果添加到哪些列来处理bi的乘法。
     *
     * 注意，comba方法通常不处理内部循环中的进位。在这种情况下，我们修复了前一列的进位，因为Montgomery归约需要结果的位数（到目前为止）[见上文]。这是通过固定内循环后的一个进位来处理的。进位修正是按顺序进行的，因此在这些循环之后，W[]的前m个->使用的单词的进位是固定的
     */
    {
      register int iy;
      register mp_digit *tmpn;
      register mp_word *_W;

      /* 模数数字的别名*/
      tmpn = n->dp;

      /* 偏移ix设置的列的别名*/
      _W = W + ix;

      /* 内环*/
      for (iy = 0; iy < n->used; iy++) {
          *_W++ += ((mp_word)mu) * ((mp_word)*tmpn++);
      }
    }

    /* 现在修复下一位的进位，W[ix+1]*/
    W[ix + 1] += W[ix] >> ((mp_word) DIGIT_BIT);
  }

  /* 现在我们必须传播进位并向下移动单词[所有我们调零的最低有效数字]。
   */
  {
    register mp_digit *tmpx;
    register mp_word *_W, *_W1;

    /* nox修复剩余进位*/

    /* 当前单词的别名*/
    _W1 = W + ix;

    /* 下一个单词的别名，进位的位置*/
    _W = W + ++ix;

    for (; ix <= n->used * 2 + 1; ix++) {
      *_W++ += *_W1++ >> ((mp_word) DIGIT_BIT);
    }

    /* 复制，A=A/b**n
     *
     * 结果是A/b**n，但不是从mp_word数组转换为mp_digit，而是调用mp_rshd，我们只是按正确的顺序复制它们
     */

    /* 目标词别名*/
    tmpx = x->dp;

    /* 移位双精度结果的别名*/
    _W = W + n->used;

    for (ix = 0; ix < n->used + 1; ix++) {
      *tmpx++ = (mp_digit)(*_W++ & ((mp_word) MP_MASK));
    }

    /* 零个旧数字，如果输入a大于m->used+1，我们必须清除这些数字
     */
    for (; ix < olduse; ix++) {
      *tmpx++ = 0;
    }
  }

  /* 设置使用的最大值并夹紧*/
  x->used = n->used + 1;
  mp_clamp (x);

  /* 如果A>=m，则A=A-m*/
  if (mp_cmp_mag (x, n) != MP_LT) {
    return s_mp_sub (x, n, x);
  }
  return MP_OKAY;
}
#endif


#ifdef BN_MP_MUL_2_C
/* b=a*2*/
static int
mp_mul_2(mp_int * a, mp_int * b)
{
  int     x, res, oldused;

  /* 增长以适应结果*/
  if (b->alloc < a->used + 1) {
    if ((res = mp_grow (b, a->used + 1)) != MP_OKAY) {
      return res;
    }
  }

  oldused = b->used;
  b->used = a->used;

  {
    register mp_digit r, rr, *tmpa, *tmpb;

    /* 源的别名*/
    tmpa = a->dp;

    /* dest的别名*/
    tmpb = b->dp;

    /* 拿*/
    r = 0;
    for (x = 0; x < a->used; x++) {

      /* 从当前数字的MSB中获取下一个进位位
       */
      rr = *tmpa >> ((mp_digit)(DIGIT_BIT - 1));

      /* 现在把这个数字上移，加上进位*/
      *tmpb++ = ((*tmpa++ << ((mp_digit)1)) | r) & MP_MASK;

      /* 将源数字的进位复制到下一次迭代中
       */
      r = rr;
    }

    /* 新的前导数字？*/
    if (r != 0) {
      /* 添加MSB，此时MSB始终为1*/
      *tmpb = 1;
      ++(b->used);
    }

    /* 现在将我们没有写入的目标上的多余数字清零
     */
    tmpb = b->dp + b->used;
    for (x = b->used; x < oldused; x++) {
      *tmpb++ = 0;
    }
  }
  b->sign = a->sign;
  return MP_OKAY;
}
#endif


#ifdef BN_MP_MONTGOMERY_CALC_NORMALIZATION_C
/*
 * 当结果大于b时，用减法移位。
 *
 * 该方法稍作修改，无条件地将B移位到B的前导位之下。这节省了大量的多次精确移位。
 */
static int
mp_montgomery_calc_normalization (mp_int * a, mp_int * b)
{
  int     x, bits, res;

  /* b使用最后一位的位数*/
  bits = mp_count_bits (b) % DIGIT_BIT;

  if (b->used > 1) {
     if ((res = mp_2expt (a, (b->used - 1) * DIGIT_BIT + bits - 1)) != MP_OKAY) {
        return res;
     }
  } else {
     mp_set(a, 1);
     bits = 1;
  }


  /* 现在计算C=A*B mod B*/
  for (x = bits - 1; x < (int)DIGIT_BIT; x++) {
    if ((res = mp_mul_2 (a, a)) != MP_OKAY) {
      return res;
    }
    if (mp_cmp_mag (a, b) != MP_LT) {
      if ((res = s_mp_sub (a, b, a)) != MP_OKAY) {
        return res;
      }
    }
  }

  return MP_OKAY;
}
#endif


#ifdef BN_MP_EXPTMOD_FAST_C
/* 计算Y==G**X mod P，HAC第616页，算法14.85
 *
 * 使用从左到右的k元滑动窗口来计算模幂。k的值根据指数的大小而变化。
 *
 * 使用Montgomery或Diminished Radix reduction[视情况而定]
 */

static int
mp_exptmod_fast (mp_int * G, mp_int * X, mp_int * P, mp_int * Y, int redmode)
{
  mp_int  M[TAB_SIZE], res;
  mp_digit buf, mp;
  int     err, bitbuf, bitcpy, bitcnt, mode, digidx, x, y, winsize;

  /* 使用指向归约算法的指针。这使得我们可以使用许多简化算法中的一种，而不用到处使用if语句来修改代码的内部。
   */
  int     (*redux)(mp_int*,mp_int*,mp_digit);

  /* 查找窗口大小*/
  x = mp_count_bits (X);
  if (x <= 7) {
    winsize = 2;
  } else if (x <= 36) {
    winsize = 3;
  } else if (x <= 140) {
    winsize = 4;
  } else if (x <= 450) {
    winsize = 5;
  } else if (x <= 1303) {
    winsize = 6;
  } else if (x <= 3529) {
    winsize = 7;
  } else {
    winsize = 8;
  }

#ifdef MP_LOW_MEM
  if (winsize > 5) {
     winsize = 5;
  }
#endif

  /* init M数组*/
  /* 初始化第一个单元格*/
  if ((err = mp_init(&M[1])) != MP_OKAY) {
     return err;
  }

  /* 现在初始化数组的后半部分*/
  for (x = 1<<(winsize-1); x < (1 << winsize); x++) {
    if ((err = mp_init(&M[x])) != MP_OKAY) {
      for (y = 1<<(winsize-1); y < x; y++) {
        mp_clear (&M[y]);
      }
      mp_clear(&M[1]);
      return err;
    }
  }

  /* 确定并设置缩减代码*/
  if (redmode == 0) {
#ifdef BN_MP_MONTGOMERY_SETUP_C
     /* 现在设置蒙哥马利*/
     if ((err = mp_montgomery_setup (P, &mp)) != MP_OKAY) {
        goto LBL_M;
     }
#else
     err = MP_VAL;
     goto LBL_M;
#endif

     /* 如果可用，自动选择组合框（节省了不少通话/ifs）*/
#ifdef BN_FAST_MP_MONTGOMERY_REDUCE_C
     if (((P->used * 2 + 1) < MP_WARRAY) &&
          P->used < (1 << ((CHAR_BIT * sizeof (mp_word)) - (2 * DIGIT_BIT)))) {
        redux = fast_mp_montgomery_reduce;
     } else
#endif
     {
#ifdef BN_MP_MONTGOMERY_REDUCE_C
        /* 使用较慢的基线蒙哥马利方法*/
        redux = mp_montgomery_reduce;
#else
        err = MP_VAL;
        goto LBL_M;
#endif
     }
  } else if (redmode == 1) {
#if defined(BN_MP_DR_SETUP_C) && defined(BN_MP_DR_REDUCE_C)
     /* 为B**k-B形式的模量设置DR缩减*/
     mp_dr_setup(P, &mp);
     redux = mp_dr_reduce;
#else
     err = MP_VAL;
     goto LBL_M;
#endif
  } else {
#if defined(BN_MP_REDUCE_2K_SETUP_C) && defined(BN_MP_REDUCE_2K_C)
     /* 设置2**k-b形式模量的DR缩减*/
     if ((err = mp_reduce_2k_setup(P, &mp)) != MP_OKAY) {
        goto LBL_M;
     }
     redux = mp_reduce_2k;
#else
     err = MP_VAL;
     goto LBL_M;
#endif
  }

  /* 设置结果*/
  if ((err = mp_init (&res)) != MP_OKAY) {
    goto LBL_M;
  }

  /* 创建M表
   *

   *
   * 虽然接受M[0]和M[1]，但未计算表的前半部分
   */

  if (redmode == 0) {
#ifdef BN_MP_MONTGOMERY_CALC_NORMALIZATION_C
     /* 现在我们需要R mod m*/
     if ((err = mp_montgomery_calc_normalization (&res, P)) != MP_OKAY) {
       goto LBL_RES;
     }
#else
     err = MP_VAL;
     goto LBL_RES;
#endif

     /* 现在将M[1]设置为G*R mod M*/
     if ((err = mp_mulmod (G, &res, P, &M[1])) != MP_OKAY) {
       goto LBL_RES;
     }
  } else {
     mp_set(&res, 1);
     if ((err = mp_mod(G, P, &M[1])) != MP_OKAY) {
        goto LBL_RES;
     }
  }

  /* 通过将M[1]（winsize-1）乘以平方，计算M[1<<（winize-1）]处的值*/
  if ((err = mp_copy (&M[1], &M[1 << (winsize - 1)])) != MP_OKAY) {
    goto LBL_RES;
  }

  for (x = 0; x < (winsize - 1); x++) {
    if ((err = mp_sqr (&M[1 << (winsize - 1)], &M[1 << (winsize - 1)])) != MP_OKAY) {
      goto LBL_RES;
    }
    if ((err = redux (&M[1 << (winsize - 1)], P, mp)) != MP_OKAY) {
      goto LBL_RES;
    }
  }

  /* 创建上表*/
  for (x = (1 << (winsize - 1)) + 1; x < (1 << winsize); x++) {
    if ((err = mp_mul (&M[x - 1], &M[1], &M[x])) != MP_OKAY) {
      goto LBL_RES;
    }
    if ((err = redux (&M[x], P, mp)) != MP_OKAY) {
      goto LBL_RES;
    }
  }

  /* 设置初始模式和位cnt*/
  mode   = 0;
  bitcnt = 1;
  buf    = 0;
  digidx = X->used - 1;
  bitcpy = 0;
  bitbuf = 0;

  for (;;) {
    /* 根据需要抓取下一个数字*/
    if (--bitcnt == 0) {
      /* 如果digidx==-1，我们的位数不足，因此中断*/
      if (digidx == -1) {
        break;
      }
      /* 读取下一位并重置bitcnt*/
      buf    = X->dp[digidx--];
      bitcnt = (int)DIGIT_BIT;
    }

    /* 从指数中获取下一个msb*/
    y     = (mp_digit)(buf >> (DIGIT_BIT - 1)) & 1;
    buf <<= (mp_digit)1;

    /* 如果位为零且模式==0，则忽略它。这些表示指数中第一个1位之前的前导零位。从技术上讲，这个选项不是必需的，但它确实降低了所使用的平凡平方/缩减的数量
     */
    if (mode == 0 && y == 0) {
      continue;
    }

    /* 如果位为零且模式==1，则我们求平方*/
    if (mode == 1 && y == 0) {
      if ((err = mp_sqr (&res, &res)) != MP_OKAY) {
        goto LBL_RES;
      }
      if ((err = redux (&res, P, mp)) != MP_OKAY) {
        goto LBL_RES;
      }
      continue;
    }

    /* 否则我们将其添加到窗口*/
    bitbuf |= (y << (winsize - ++bitcpy));
    mode    = 2;

    if (bitcpy == winsize) {
      /* ok窗口根据需要填充成正方形，然后相乘*/
      /* 正方形优先*/
      for (x = 0; x < winsize; x++) {
        if ((err = mp_sqr (&res, &res)) != MP_OKAY) {
          goto LBL_RES;
        }
        if ((err = redux (&res, P, mp)) != MP_OKAY) {
          goto LBL_RES;
        }
      }

      /* 然后相乘*/
      if ((err = mp_mul (&res, &M[bitbuf], &res)) != MP_OKAY) {
        goto LBL_RES;
      }
      if ((err = redux (&res, P, mp)) != MP_OKAY) {
        goto LBL_RES;
      }

      /* 清空窗口并重置*/
      bitcpy = 0;
      bitbuf = 0;
      mode   = 1;
    }
  }

  /* 如果保留位，则平方/乘法*/
  if (mode == 2 && bitcpy > 0) {
    /* 如果设置了位，则进行平方运算*/
    for (x = 0; x < bitcpy; x++) {
      if ((err = mp_sqr (&res, &res)) != MP_OKAY) {
        goto LBL_RES;
      }
      if ((err = redux (&res, P, mp)) != MP_OKAY) {
        goto LBL_RES;
      }

      /* 获得下一个窗口*/
      bitbuf <<= 1;
      if ((bitbuf & (1 << winsize)) != 0) {
        /* 然后相乘*/
        if ((err = mp_mul (&res, &M[1], &res)) != MP_OKAY) {
          goto LBL_RES;
        }
        if ((err = redux (&res, P, mp)) != MP_OKAY) {
          goto LBL_RES;
        }
      }
    }
  }

  if (redmode == 0) {
     /* 修正结果，如果使用Montgomery归约，回想蒙哥马利系统中的任何值实际上都乘以Rmodn。
      */
     if ((err = redux(&res, P, mp)) != MP_OKAY) {
       goto LBL_RES;
     }
  }

  /* 用Y交换res*/
  mp_exch (&res, Y);
  err = MP_OKAY;
LBL_RES:mp_clear (&res);
LBL_M:
  mp_clear(&M[1]);
  for (x = 1<<(winsize-1); x < (1 << winsize); x++) {
    mp_clear (&M[x]);
  }
  return err;
}
#endif


#ifdef BN_FAST_S_MP_SQR_C
/* 平方的技巧……除了tmpx的偏移量（从接近零开始的偏移量）不能等于tmpy的偏移量之外，你确实喜欢mult。所以基本上，你先设置好iy，然后用（ty tx）最小化它，这样它就不会发生了。将所有添加到内部循环中的值加倍

在这个循环之后，你做方块并把它们加进去。
*/

static int
fast_s_mp_sqr (mp_int * a, mp_int * b)
{
  int       olduse, res, pa, ix, iz;
  mp_digit   W[MP_WARRAY], *tmpx;
  mp_word   W1;

  /* 根据需要增加目标*/
  pa = a->used + a->used;
  if (b->alloc < pa) {
    if ((res = mp_grow (b, pa)) != MP_OKAY) {
      return res;
    }
  }

  /* 要生成的输出位数*/
  W1 = 0;
  for (ix = 0; ix < pa; ix++) {
      int      tx, ty, iy;
      mp_word  _W;
      mp_digit *tmpy;

      /* 清除计数器*/
      _W = 0;

      /* 获取两个bignum的偏移量*/
      ty = MIN(a->used-1, ix);
      tx = ix - ty;

      /* 设置临时别名*/
      tmpx = a->dp + tx;
      tmpy = a->dp + ty;

      /* 这是循环迭代的次数，本质上是在（tx++<a->used&&ty->=0）{…}
       */
      iy = MIN(a->used-tx, ty+1);

      /* 现在，对于平方tx永远不能等于y，我们将距离减半，因为它们以2倍的速度接近，我们必须舍入，因为需要执行奇数情况
       */
      iy = MIN(iy, (ty-tx+1)>>1);

      /* 执行循环*/
      for (iz = 0; iz < iy; iz++) {
         _W += ((mp_word)*tmpx++)*((mp_word)*tmpy--);
      }

      /* 将内积加倍并添加进位*/
      _W = _W + _W + W1;

      /* 即使柱中也有平方项*/
      if ((ix&1) == 0) {
         _W += ((mp_word)a->dp[ix>>1])*((mp_word)a->dp[ix>>1]);
      }

      /* 存储它*/
      W[ix] = (mp_digit)(_W & MP_MASK);

      /* 进行下一次进位*/
      W1 = _W >> ((mp_word)DIGIT_BIT);
  }

  /* 设置目标*/
  olduse  = b->used;
  b->used = a->used+a->used;

  {
    mp_digit *tmpb;
    tmpb = b->dp;
    for (ix = 0; ix < pa; ix++) {
      *tmpb++ = W[ix] & MP_MASK;
    }

    /* 清除未使用的数字[存在于c的旧副本中]*/
    for (; ix < olduse; ix++) {
      *tmpb++ = 0;
    }
  }
  mp_clamp (b);
  return MP_OKAY;
}
#endif


#ifdef BN_MP_MUL_D_C
/* 乘以一个数字*/
static int
mp_mul_d (mp_int * a, mp_digit b, mp_int * c)
{
  mp_digit u, *tmpa, *tmpc;
  mp_word  r;
  int      ix, res, olduse;

  /* 确保c足够大，可以容纳a*b*/
  if (c->alloc < a->used + 1) {
    if ((res = mp_grow (c, a->used + 1)) != MP_OKAY) {
      return res;
    }
  }

  /* 获取原始目的地使用计数*/
  olduse = c->used;

  /* 设置标志*/
  c->sign = a->sign;

  /* ->dp[source]的别名*/
  tmpa = a->dp;

  /* c->dp[dest]的别名*/
  tmpc = c->dp;

  /* 零进位*/
  u = 0;

  /* 计算列*/
  for (ix = 0; ix < a->used; ix++) {
    /* 计算此项的积和进位和*/
    r       = ((mp_word) u) + ((mp_word)*tmpa++) * ((mp_word)b);

    /* 屏蔽掉高位以获得单个数字*/
    *tmpc++ = (mp_digit) (r & ((mp_word) MP_MASK));

    /* 将进位发送到下一次迭代*/
    u       = (mp_digit) (r >> ((mp_word) DIGIT_BIT));
  }

  /* 存储最终进位（如果有）和增量ix偏移*/
  *tmpc++ = u;
  ++ix;

  /* 现在顶部上方为零位*/
  while (ix++ < olduse) {
     *tmpc++ = 0;
  }

  /* 设置已用计数*/
  c->used = a->used + 1;
  mp_clamp(c);

  return MP_OKAY;
}
#endif

