// 版权所有2015-2020 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef __RVRUNTIME_FRAMES_H__
#define __RVRUNTIME_FRAMES_H__

/* 将值对齐到最近的n字节边界，其中n是2的幂。*/
#define ALIGNUP(n, val) (((val) + (n) - 1) & -(n))

#ifdef STRUCT_BEGIN
#undef STRUCT_BEGIN
#undef STRUCT_FIELD
#undef STRUCT_AFIELD
#undef STRUCT_END
#endif

#if defined(_ASMLANGUAGE) || defined(__ASSEMBLER__)
#define STRUCT_BEGIN            .pushsection .text; .struct 0
#define STRUCT_FIELD(ctype,size,asname,name)    asname: .space  size
#define STRUCT_AFIELD(ctype,size,asname,name,n) asname: .space  (size)*(n)
#define STRUCT_END(sname)       sname##Size:; .popsection
#else
#define STRUCT_BEGIN            typedef struct {
#define STRUCT_FIELD(ctype,size,asname,name)    ctype   name;
#define STRUCT_AFIELD(ctype,size,asname,name,n) ctype   name[n];
#define STRUCT_END(sname)       } sname;
#endif

/*
------------------------------------------------------------------------------- INTERRUPT/EXCEPTION STACK FRAME FOR A EXCEPTION OR NESTED INTERRUPT
-------------------------------------------------------------------------------
*/
STRUCT_BEGIN
STRUCT_FIELD (long, 4, RV_STK_MEPC,    mepc)       /* 机器异常程序计数器*/
STRUCT_FIELD (long, 4, RV_STK_RA,      ra)         /* 返回地址*/
STRUCT_FIELD (long, 4, RV_STK_SP,      sp)         /* 堆栈指针*/
STRUCT_FIELD (long, 4, RV_STK_GP,      gp)         /* 全局指针*/
STRUCT_FIELD (long, 4, RV_STK_TP,      tp)         /* 线程指针*/
STRUCT_FIELD (long, 4, RV_STK_T0,      t0)         /* 临时/备用链接寄存器*/
STRUCT_FIELD (long, 4, RV_STK_T1,      t1)         /* t1-2：临时*/
STRUCT_FIELD (long, 4, RV_STK_T2,      t2)
STRUCT_FIELD (long, 4, RV_STK_S0,      s0)         /* 保存的寄存器/帧指针*/
STRUCT_FIELD (long, 4, RV_STK_S1,      s1)         /* 保存的寄存器*/
STRUCT_FIELD (long, 4, RV_STK_A0,      a0)         /* a0-1：函数参数/返回地址*/
STRUCT_FIELD (long, 4, RV_STK_A1,      a1)
STRUCT_FIELD (long, 4, RV_STK_A2,      a2)         /* a2-7：函数参数*/
STRUCT_FIELD (long, 4, RV_STK_A3,      a3)
STRUCT_FIELD (long, 4, RV_STK_A4,      a4)
STRUCT_FIELD (long, 4, RV_STK_A5,      a5)
STRUCT_FIELD (long, 4, RV_STK_A6,      a6)
STRUCT_FIELD (long, 4, RV_STK_A7,      a7)
STRUCT_FIELD (long, 4, RV_STK_S2,      s2)         /* s2-11：保存的寄存器*/
STRUCT_FIELD (long, 4, RV_STK_S3,      s3)
STRUCT_FIELD (long, 4, RV_STK_S4,      s4)
STRUCT_FIELD (long, 4, RV_STK_S5,      s5)
STRUCT_FIELD (long, 4, RV_STK_S6,      s6)
STRUCT_FIELD (long, 4, RV_STK_S7,      s7)
STRUCT_FIELD (long, 4, RV_STK_S8,      s8)
STRUCT_FIELD (long, 4, RV_STK_S9,      s9)
STRUCT_FIELD (long, 4, RV_STK_S10,     s10)
STRUCT_FIELD (long, 4, RV_STK_S11,     s11)
STRUCT_FIELD (long, 4, RV_STK_T3,      t3)         /* t3-6：临时*/
STRUCT_FIELD (long, 4, RV_STK_T4,      t4)
STRUCT_FIELD (long, 4, RV_STK_T5,      t5)
STRUCT_FIELD (long, 4, RV_STK_T6,      t6)
STRUCT_FIELD (long, 4, RV_STK_MSTATUS, mstatus)    /* 机器状态*/
STRUCT_FIELD (long, 4, RV_STK_MTVEC,   mtvec)      /* 机器陷阱矢量基地址*/
STRUCT_FIELD (long, 4, RV_STK_MCAUSE,  mcause)     /* 机器陷阱原因*/
STRUCT_FIELD (long, 4, RV_STK_MTVAL,   mtval)      /* 机器陷阱值*/
STRUCT_FIELD (long, 4, RV_STK_MHARTID, mhartid)    /* 机器模式下的硬件线程ID*/
STRUCT_END(RvExcFrame)

#if defined(_ASMLANGUAGE) || defined(__ASSEMBLER__)
#define RV_STK_SZ1     RvExcFrameSize
#else
#define RV_STK_SZ1     sizeof(RvExcFrame)
#endif

/*
 * 异常堆栈帧大小，最多对齐16字节边界后
 */
#define RV_STK_FRMSZ    (ALIGNUP(0x10, RV_STK_SZ1))

#endif /* #如果NDef __RVRUNTIME_FRAMES_H__*/

