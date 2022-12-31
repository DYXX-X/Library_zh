/*
 * Tensilica Inc.版权所有（c）2012。保留所有权利。
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __XT_PERF_CONSTS_H__
#define __XT_PERF_CONSTS_H__

#include <xtensa/config/core.h>

/*
 * 性能监视器计数器选择器
 */

#define XTPERF_CNT_COMMITTED_INSN        0x8002  /* 提交的指令*/
#define XTPERF_CNT_BRANCH_PENALTY        0x8003  /* 分支惩罚周期*/
#define XTPERF_CNT_PIPELINE_INTERLOCKS   0x8004  /* 管道联锁循环*/
#define XTPERF_CNT_ICACHE_MISSES         0x8005  /* ICache在循环中未命中惩罚*/
#define XTPERF_CNT_DCACHE_MISSES         0x8006  /* DCache未命中惩罚（以周期为单位）*/

#define XTPERF_CNT_CYCLES         0  /* 计数周期*/
#define XTPERF_CNT_OVERFLOW       1  /* 计数器n-1溢出（假设这是计数器n）*/
#define XTPERF_CNT_INSN           2  /* 已成功完成说明*/
#define XTPERF_CNT_D_STALL        3  /* 与数据相关的GlobalStall周期*/
#define XTPERF_CNT_I_STALL        4  /* 指令相关和其他GlobalStall周期*/
#define XTPERF_CNT_EXR            5  /* 异常和管道回放*/
#define XTPERF_CNT_BUBBLES        6  /* 保持和其他泡沫周期*/
#define XTPERF_CNT_I_TLB          7  /* 指令TLB访问（每个失效指令）*/
#define XTPERF_CNT_I_MEM          8  /* 指令内存访问（每个指令退出）*/
#define XTPERF_CNT_D_TLB          9  /* 数据TLB访问*/
#define XTPERF_CNT_D_LOAD_U1      10 /* 数据存储器加载指令（加载存储第一单元）*/
#define XTPERF_CNT_D_STORE_U1     11 /* 数据存储器存储指令（加载存储第一单元）*/
#define XTPERF_CNT_D_ACCESS_U1    12 /* 数据存储器访问（加载、存储、S32C1I等；加载存储第一单元）*/
#define XTPERF_CNT_D_LOAD_U2      13 /* 数据存储器加载指令（加载存储第二单元）*/
#define XTPERF_CNT_D_STORE_U2     14 /* 数据存储器存储指令（加载存储第二单元）*/
#define XTPERF_CNT_D_ACCESS_U2    15 /* 数据存储器访问（加载、存储、S32C1I等；加载存储第二单元）*/
#define XTPERF_CNT_D_LOAD_U3      16 /* 数据存储器加载指令（加载存储第三单元）*/
#define XTPERF_CNT_D_STORE_U3     17 /* 数据存储器存储指令（加载存储第三单元）*/
#define XTPERF_CNT_D_ACCESS_U3    18 /* 数据存储器访问（加载、存储、S32C1I等；加载存储第三单元）*/
#define XTPERF_CNT_MULTIPLE_LS    22 /* 多重加载/存储*/
#define XTPERF_CNT_OUTBOUND_PIF   23 /* 出站PIF交易*/
#define XTPERF_CNT_INBOUND_PIF    24 /* 入站PIF事务*/
#define XTPERF_CNT_PREFETCH       26 /* 预取事件*/

#if XCHAL_HW_VERSION >= 270004

#define XTPERF_CNT_IDMA           27 /* iDMA计数器*/
#define XTPERF_CNT_INSN_LENGTH    28 /* 指令长度计数器*/

#endif /* 硬件版本>=270004*/

/*
 * 上面列出的每个选择器的掩码
 */

/* XTPERF_CNT_COMMITTED_INSN选择器掩码*/

#define XTPERF_MASK_COMMITTED_INSN               0x0001

/* XTPERF_CNT_BRANCH_PENABLEY选择器掩码*/

#define XTPERF_MASK_BRANCH_PENALTY               0x0001

/* XTPERF_CNT_PIPELINE_INTERLOCKS选择器掩码*/

#define XTPERF_MASK_PIPELINE_INTERLOCKS          0x0001

/* XTPERF_CNT_ICACHE_MISSES选择器掩码*/

#define XTPERF_MASK_ICACHE_MISSES                0x0001

/* XTPERF_CNT_DCACHE_MISSES选择器掩码*/

#define XTPERF_MASK_DCACHE_MISSES                0x0001

/* XTPERF_CNT_CYCLES选择器掩码*/

#define XTPERF_MASK_CYCLES                       0x0001

/* XTPERF_CNT_OVERFLOW选择器掩码*/

#define XTPERF_MASK_OVERFLOW                     0x0001

/*
 * XTPERF_CNT_INSN选择器掩码
 */

#define XTPERF_MASK_INSN_ALL                     0x8DFF

#define XTPERF_MASK_INSN_JX                      0x0001 /* JX */
#define XTPERF_MASK_INSN_CALLX                   0x0002 /* 呼叫Xn*/
#define XTPERF_MASK_INSN_RET                     0x0004 /* 调用返回，即RET、RETW*/
#define XTPERF_MASK_INSN_RF                      0x0008 /* 主管返回，即RFDE、RFE、RFI、RFWO、RFWU*/
#define XTPERF_MASK_INSN_BRANCH_TAKEN            0x0010 /* 执行条件分支，或loopgtz/loopnez跳过循环*/
#define XTPERF_MASK_INSN_J                       0x0020 /* J */
#define XTPERF_MASK_INSN_CALL                    0x0040 /* 呼叫*/
#define XTPERF_MASK_INSN_BRANCH_NOT_TAKEN        0x0080 /* 条件分支通过（又名未执行分支）*/
#define XTPERF_MASK_INSN_LOOP_TAKEN              0x0100 /* 循环指令落入循环（又称取循环）*/
#define XTPERF_MASK_INSN_LOOP_BEG                0x0400 /* 返回LBEG*/
#define XTPERF_MASK_INSN_LOOP_END                0x0800 /* 环回传递到LEND*/
#define XTPERF_MASK_INSN_NON_BRANCH              0x8000 /* 非分支指令（也称为非CTI）*/

/*
 * XTPERF_CNT_D_STALL选择器掩码
 */

#define XTPERF_MASK_D_STALL_ALL                  0x01FE

#define XTPERF_MASK_D_STALL_STORE_BUF_FULL       0x0002 /* 存储缓冲区满失速*/
#define XTPERF_MASK_D_STALL_STORE_BUF_CONFLICT   0x0004 /* 存储缓冲区冲突暂停*/
#define XTPERF_MASK_D_STALL_CACHE_MISS           0x0008 /* DCache未命中暂停*/
#define XTPERF_MASK_D_STALL_BUSY                 0x0010 /* 数据RAM/ROM/XLMI忙停*/
#define XTPERF_MASK_D_STALL_IN_PIF               0x0020 /* 数据入站PIF请求暂停（包括s32c1i）*/
#define XTPERF_MASK_D_STALL_MHT_LOOKUP           0x0040 /* MHT查找暂停*/
#define XTPERF_MASK_D_STALL_UNCACHED_LOAD        0x0080 /* 未缓存加载暂停（包括在MHT查找暂停中）*/
#define XTPERF_MASK_D_STALL_BANK_CONFLICT        0x0100 /* 银行冲突暂停*/

/*
 * XTPERF_CNT_I_STALL选择器掩码
 */

#define XTPERF_MASK_I_STALL_ALL                  0x01FF

#define XTPERF_MASK_I_STALL_CACHE_MISS           0x0001 /* ICache未命中暂停*/
#define XTPERF_MASK_I_STALL_BUSY                 0x0002 /* 指令RAM/ROM忙暂停*/
#define XTPERF_MASK_I_STALL_IN_PIF               0x0004 /* 指令RAM入站PIF请求暂停*/
#define XTPERF_MASK_I_STALL_TIE_PORT             0x0008 /* TIE端口失速*/
#define XTPERF_MASK_I_STALL_EXTERNAL_SIGNAL      0x0010 /* 外部RunStall信号状态*/
#define XTPERF_MASK_I_STALL_UNCACHED_FETCH       0x0020 /* 未缓存的提取暂停*/
#define XTPERF_MASK_I_STALL_FAST_L32R            0x0040 /* FastL32R失速*/
#define XTPERF_MASK_I_STALL_ITERATIVE_MUL        0x0080 /* 迭代乘法暂停*/
#define XTPERF_MASK_I_STALL_ITERATIVE_DIV        0x0100 /* 迭代除法暂停*/

/*
 * XTPERF_CNT_EXR选择器掩码
 */

#define XTPERF_MASK_EXR_ALL                      0x01FF

#define XTPERF_MASK_EXR_REPLAYS                  0x0001 /* 其他管道回放（即不包括$miss等）*/
#define XTPERF_MASK_EXR_LEVEL1_INT               0x0002 /* 1级中断*/
#define XTPERF_MASK_EXR_LEVELH_INT               0x0004 /* 大于1级中断*/
#define XTPERF_MASK_EXR_DEBUG                    0x0008 /* 调试异常*/
#define XTPERF_MASK_EXR_NMI                      0x0010 /* NMI */
#define XTPERF_MASK_EXR_WINDOW                   0x0020 /* 窗口异常*/
#define XTPERF_MASK_EXR_ALLOCA                   0x0040 /* Alloca例外*/
#define XTPERF_MASK_EXR_OTHER                    0x0080 /* 其他例外情况*/
#define XTPERF_MASK_EXR_MEM_ERR                  0x0100 /* 硬件纠正内存错误*/

/*
 * XTPERF_CNT_BUBBLES选择器掩码
 */

#define XTPERF_MASK_BUBBLES_ALL                   0x01FD

#define XTPERF_MASK_BUBBLES_PSO                   0x0001 /* 处理器域PSO气泡*/
#define XTPERF_MASK_BUBBLES_R_HOLD_D_CACHE_MISS   0x0004 /* DCache未命中导致R保持*/
#define XTPERF_MASK_BUBBLES_R_HOLD_STORE_RELEASE  0x0008 /* 存储释放导致的R保持*/
#define XTPERF_MASK_BUBBLES_R_HOLD_REG_DEP        0x0010 /* 寄存器依赖性导致的R保持*/
#define XTPERF_MASK_BUBBLES_R_HOLD_WAIT           0x0020 /* MEMW、EXTW或EXCW导致的R保持*/
#define XTPERF_MASK_BUBBLES_R_HOLD_HALT           0x0040 /* 停止指令导致的R保持（仅限TX）*/
#define XTPERF_MASK_BUBBLES_CTI                   0x0080 /* CTI气泡（例如分支延迟槽）*/
#define XTPERF_MASK_BUBBLES_WAITI                 0x0100 /* WAITI气泡*/

/*
 * XTPERF_CNT_I_TLB选择器掩码
 */

#define XTPERF_MASK_I_TLB_ALL                     0x000F

#define XTPERF_MASK_I_TLB_HITS                    0x0001 /* 打*/
#define XTPERF_MASK_I_TLB_REPLAYS                 0x0002 /* 由于ITLB未命中而重新播放指令*/
#define XTPERF_MASK_I_TLB_REFILLS                 0x0004 /* HW辅助TLB加注完成*/
#define XTPERF_MASK_I_TLB_MISSES                  0x0008 /* ITLB未命中异常*/

/*
 * XTPERF_CNT_I_MEM选择器掩码
 */

#define XTPERF_MASK_I_MEM_ALL                     0x000F

#define XTPERF_MASK_I_MEM_CACHE_HITS              0x0001 /* ICache命中*/
#define XTPERF_MASK_I_MEM_CACHE_MISSES            0x0002 /* ICache未命中（包括未缓存）*/
#define XTPERF_MASK_I_MEM_IRAM                    0x0004 /* InstRAM或InstROM*/
#define XTPERF_MASK_I_MEM_BYPASS                  0x0008 /* 绕过（即未缓存）提取*/

/*
 * XTPERF_CNT_D_TLB选择器掩码
 */

#define XTPERF_MASK_D_TLB_ALL                     0x000F

#define XTPERF_MASK_D_TLB_HITS                    0x0001 /* 打*/
#define XTPERF_MASK_D_TLB_REPLAYS                 0x0002 /* 由于DTLB未命中而导致指令重放*/
#define XTPERF_MASK_D_TLB_REFILLS                 0x0004 /* HW辅助TLB加注完成*/
#define XTPERF_MASK_D_TLB_MISSES                  0x0008 /* DTLB未命中异常*/

/*
 * XTPERF_CNT_D_LOAD_U*选择器掩码
 */

#define XTPERF_MASK_D_LOAD_ALL                    0x000F

#define XTPERF_MASK_D_LOAD_CACHE_HITS             0x0001 /* 缓存命中*/
#define XTPERF_MASK_D_LOAD_CACHE_MISSES           0x0002 /* 缓存未命中*/
#define XTPERF_MASK_D_LOAD_LOCAL_MEM              0x0004 /* 本地内存命中*/
#define XTPERF_MASK_D_LOAD_BYPASS                 0x0008 /* 旁路（即未缓存）负载*/

/*
 * XTPERF_CNT_D_STORE_U*选择器掩码
 */

#define XTPERF_MASK_D_STORE_ALL                    0x000F

#define XTPERF_MASK_D_STORE_CACHE_HITS             0x0001 /* DCache命中*/
#define XTPERF_MASK_D_STORE_CACHE_MISSES           0x0002 /* DCache未命中*/
#define XTPERF_MASK_D_STORE_LOCAL_MEM              0x0004 /* 本地内存命中*/
#define XTPERF_MASK_D_STORE_PIF                    0x0008 /* PIF存储*/

/*
 * XTPERF_CNT_D_ACCESS_U*选择器掩码
 */

#define XTPERF_MASK_D_ACCESS_ALL                   0x000F

#define XTPERF_MASK_D_ACCESS_CACHE_MISSES          0x0001 /* DCache未命中*/
#define XTPERF_MASK_D_ACCESS_HITS_SHARED           0x0002 /* 点击共享*/
#define XTPERF_MASK_D_ACCESS_HITS_EXCLUSIVE        0x0004 /* 点击独占*/
#define XTPERF_MASK_D_ACCESS_HITS_MODIFIED         0x0008 /* 命中已修改*/

/*
 * XTPERF_CNT_MULTIPLE_LS选择器掩码
 */

#define XTPERF_MASK_MULTIPLE_LS_ALL                0x003F

#define XTPERF_MASK_MULTIPLE_LS_0S_0L              0x0001 /* 0个存储和0个加载*/
#define XTPERF_MASK_MULTIPLE_LS_0S_1L              0x0002 /* 0个存储和1个加载*/
#define XTPERF_MASK_MULTIPLE_LS_1S_0L              0x0004 /* 1个存储区和0个加载区*/
#define XTPERF_MASK_MULTIPLE_LS_1S_1L              0x0008 /* 1个存储和1个加载*/
#define XTPERF_MASK_MULTIPLE_LS_0S_2L              0x0010 /* 0个存储和2个加载*/
#define XTPERF_MASK_MULTIPLE_LS_2S_0L              0x0020 /* 2个存储和0个加载*/

/*
 * XTPERF_CNT_OUTBOUND_PIF选择器掩码
 */

#define XTPERF_MASK_OUTBOUND_PIF_ALL               0x0003

#define XTPERF_MASK_OUTBOUND_PIF_CASTOUT           0x0001 /* 铸件*/
#define XTPERF_MASK_OUTBOUND_PIF_PREFETCH          0x0002 /* 预取*/

/*
 * XTPERF_CNT_INBOUND_PIF选择器掩码
 */

#define XTPERF_MASK_INBOUND_PIF_ALL                0x0003

#define XTPERF_MASK_INBOUND_PIF_I_DMA              0x0001 /* 指令DMA*/
#define XTPERF_MASK_INBOUND_PIF_D_DMA              0x0002 /* 数据DMA*/

/*
 * XTPERF_CNT_PREFETCH选择器掩码
 */

#define XTPERF_MASK_PREFETCH_ALL                   0x002F

#define XTPERF_MASK_PREFETCH_I_HIT                 0x0001 /* 我预取缓冲区查找命中*/
#define XTPERF_MASK_PREFETCH_D_HIT                 0x0002 /* D预取缓冲区查找命中*/
#define XTPERF_MASK_PREFETCH_I_MISS                0x0004 /* 我预取缓冲区查找未命中*/
#define XTPERF_MASK_PREFETCH_D_MISS                0x0008 /* D预取缓冲区查找未命中*/
#define XTPERF_MASK_PREFETCH_D_L1_FILL             0x0020 /* 直接填充到DCache L1*/

#if XCHAL_HW_VERSION >= 270004

/*
 * XTPERF_CNT_IDMA选择器掩码
 */

#define XTPERF_MASK_IDMA_ALL                       0x0001

#define XTPERF_MASK_IDMA_ACTIVE_CYCLES             0x0001 /* 活动周期*/

/*
 * XTPERF_CNT_INSN_LENGTH选择器掩码
 */

#define XTPERF_MASK_INSN_LENGTH_ALL                0x7FFF

#define XTPERF_MASK_INSN_LENGTH_16                 0x0001 /* 16位指令长度*/
#define XTPERF_MASK_INSN_LENGTH_24                 0x0002 /* 24位指令长度*/
#define XTPERF_MASK_INSN_LENGTH_32                 0x0004 /* 32位指令长度*/
#define XTPERF_MASK_INSN_LENGTH_40                 0x0008 /* 40位指令长度*/
#define XTPERF_MASK_INSN_LENGTH_48                 0x0010 /* 48位指令长度*/
#define XTPERF_MASK_INSN_LENGTH_56                 0x0020 /* 56位指令长度*/
#define XTPERF_MASK_INSN_LENGTH_64                 0x0040 /* 64位指令长度*/
#define XTPERF_MASK_INSN_LENGTH_72                 0x0080 /* 72位指令长度*/
#define XTPERF_MASK_INSN_LENGTH_80                 0x0100 /* 80位指令长度*/
#define XTPERF_MASK_INSN_LENGTH_88                 0x0200 /* 88位指令长度*/
#define XTPERF_MASK_INSN_LENGTH_96                 0x0400 /* 96位指令长度*/
#define XTPERF_MASK_INSN_LENGTH_104                0x0800 /* 104位指令长度*/
#define XTPERF_MASK_INSN_LENGTH_112                0x1000 /* 112位指令长度*/
#define XTPERF_MASK_INSN_LENGTH_120                0x2000 /* 120位指令长度*/
#define XTPERF_MASK_INSN_LENGTH_128                0x4000 /* 128位指令长度*/

#endif /* 硬件版本>=270004*/

#endif /* __XT_PERF_CONSTS_H__ */

