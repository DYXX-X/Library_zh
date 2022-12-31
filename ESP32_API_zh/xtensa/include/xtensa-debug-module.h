#ifndef XTENSA_DEBUG_MODULE_H
#define XTENSA_DEBUG_MODULE_H

/*
ERI寄存器/OCD偏移和字段定义
*/

#define ERI_DEBUG_OFFSET 0x100000

#define ERI_TRAX_OFFSET         (ERI_DEBUG_OFFSET+0)
#define ERI_PERFMON_OFFSET      (ERI_DEBUG_OFFSET+0x1000)
#define ERI_OCDREG_OFFSET       (ERI_DEBUG_OFFSET+0x2000)
#define ERI_MISCDBG_OFFSET      (ERI_DEBUG_OFFSET+0x3000)
#define ERI_CORESIGHT_OFFSET    (ERI_DEBUG_OFFSET+0x3F00)

#define ERI_TRAX_TRAXID         (ERI_TRAX_OFFSET+0x00)
#define ERI_TRAX_TRAXCTRL       (ERI_TRAX_OFFSET+0x04)
#define ERI_TRAX_TRAXSTAT       (ERI_TRAX_OFFSET+0x08)
#define ERI_TRAX_TRAXDATA       (ERI_TRAX_OFFSET+0x0C)
#define ERI_TRAX_TRAXADDR       (ERI_TRAX_OFFSET+0x10)
#define ERI_TRAX_TRIGGERPC      (ERI_TRAX_OFFSET+0x14)
#define ERI_TRAX_PCMATCHCTRL    (ERI_TRAX_OFFSET+0x18)
#define ERI_TRAX_DELAYCNT       (ERI_TRAX_OFFSET+0x1C)
#define ERI_TRAX_MEMADDRSTART   (ERI_TRAX_OFFSET+0x20)
#define ERI_TRAX_MEMADDREND     (ERI_TRAX_OFFSET+0x24)

#define TRAXCTRL_TREN           (1<<0)  //跟踪启用。跟踪开始于0->1
#define TRAXCTRL_TRSTP          (1<<1)  //跟踪停止。使1停止跟踪。
#define TRAXCTRL_PCMEN          (1<<2)  //PC匹配启用
#define TRAXCTRL_PTIEN          (1<<4)  //处理器触发器启用
#define TRAXCTRL_CTIEN          (1<<5)  //交叉触发启用
#define TRAXCTRL_TMEN           (1<<7)  //Tracemem启用。始终设置。
#define TRAXCTRL_CNTU           (1<<9)  //停止后触发倒计时装置；选择延迟计数发生的时间。
                                        //0-写入tracemem的每个32位字，1-每个cpu指令
#define TRAXCTRL_TSEN           (1<<11) //未记录/已弃用？
#define TRAXCTRL_SMPER_SHIFT    12      //每2^（9-smper）条消息发送一次同步。7=保留，0=无同步消息
#define TRAXCTRL_SMPER_MASK     0x7     //同步消息周期
#define TRAXCTRL_PTOWT          (1<<16) //当触发停止时，处理器触发输出（OCD停止）已启用
#define TRAXCTRL_PTOWS          (1<<17) //跟踪停止完成时启用处理器触发输出（OCD停止）
#define TRAXCTRL_CTOWT          (1<<20) //触发停止时启用交叉触发输出
#define TRAXCTRL_CTOWS          (1<<21) //跟踪停止完成时启用交叉触发器输出
#define TRAXCTRL_ITCTO          (1<<22) //集成模式：交叉触发输出
#define TRAXCTRL_ITCTIA         (1<<23) //集成模式：交叉触发确认
#define TRAXCTRL_ITATV          (1<<24) //在集成模式下替换ATID：ATVALID输出
#define TRAXCTRL_ATID_MASK      0x7F    //ARB源ID
#define TRAXCTRL_ATID_SHIFT     24
#define TRAXCTRL_ATEN           (1<<31) //ATB接口启用

#define TRAXSTAT_TRACT          (1<<0)  //跟踪活动标志。
#define TRAXSTAT_TRIG           (1<<1)  //跟踪停止触发器。清除趋势1->0
#define TRAXSTAT_PCMTG          (1<<2)  //PC匹配导致的停止触发。清除趋势1->0
#define TRAXSTAT_PJTR           (1<<3)  //JTAG交易结果。1=前一个jtag事务中出错。
#define TRAXSTAT_PTITG          (1<<4)  //处理器触发输入导致的停止触发。清除趋势1->0
#define TRAXSTAT_CTITG          (1<<5)  //交叉触发输入导致的停止触发。清除趋势1->0
#define TRAXSTAT_MEMSZ_SHIFT    8       //Traceram尺寸指示器。可用的跟踪内存为2^MEMSZ字节。
#define TRAXSTAT_MEMSZ_MASK     0x1F
#define TRAXSTAT_PTO            (1<<16) //处理器触发输出：当前值
#define TRAXSTAT_CTO            (1<<17) //交叉触发输出：电流值
#define TRAXSTAT_ITCTOA         (1<<22) //交叉触发输出确认：当前值
#define TRAXSTAT_ITCTI          (1<<23) //交叉触发输入：当前值
#define TRAXSTAT_ITATR          (1<<24) //ATREADY输入：电流值

#define TRAXADDR_TADDR_SHIFT    0       //Trax内存地址，以32位字表示。
#define TRAXADDR_TADDR_MASK     0x1FFFFF //实际上只有跟踪缓冲区大小max-addr那么大。
#define TRAXADDR_TWRAP_SHIFT    21      //TADDR溢出的次数
#define TRAXADDR_TWRAP_MASK     0x3FF
#define TRAXADDR_TWSAT          (1<<31) //1如果TWRAP已溢出，通过禁用tren清除。

#define PCMATCHCTRL_PCML_SHIFT  0       //pc触发寄存器中要忽略的低位数量
#define PCMATCHCTRL_PCML_MASK   0x1F
#define PCMATCHCTRL_PCMS        (1<<31) //PC匹配感知，0-当procs PC在范围内时匹配，1-当
                                        //超出范围

// 所有性能计数器的全局控制/状态
#define ERI_PERFMON_PGM             (ERI_PERFMON_OFFSET+0x0000)
//导致PerfMonInt断言的事件周期的PC
#define ERI_PERFMON_INTPC           (ERI_PERFMON_OFFSET+0x0010)

// 计数器的最大数量（取决于芯片）
#define ERI_PERFMON_MAX     XCHAL_NUM_PERF_COUNTERS

// 性能计数器值
#define ERI_PERFMON_PM0             (ERI_PERFMON_OFFSET+0x0080)
// 性能计数器控制寄存器
#define ERI_PERFMON_PMCTRL0         (ERI_PERFMON_OFFSET+0x0100)
// 性能计数器状态寄存器
#define ERI_PERFMON_PMSTAT0         (ERI_PERFMON_OFFSET+0x0180)


#define PMCTRL_INTEN                (1<<0)      // 在发生溢出时启用PerfMonInt输出的断言
#define PMCTRL_KRNLCNT              (1<<3)      // 当CINTLEVEL*>时启用计数
// TRACELEVEL（即，如果设置了此位，则此计数器
// 仅当CINTLEVEL>TRACELEVEL时计数；
// 如果清除此位，则此计数器仅在以下情况下计数
// CINTLEVEL ≤ TRACELEVEL)
#define PMCTRL_KRNLCNT_SHIFT        3
#define PMCTRL_TRACELEVEL_SHIFT     4           // 在决定是否计数时，将此值与CINTLEVEL*进行比较
#define PMCTRL_TRACELEVEL_MASK      0xf
#define PMCTRL_SELECT_SHIFT         8           // 选择计数器计数的输入
#define PMCTRL_SELECT_MASK          0x1f
#define PMCTRL_MASK_SHIFT           16          // 选择要计数的输入子集（计数器将
// 即使有多个条件，也只能增加一次
// 对应于出现掩码位）
#define PMCTRL_MASK_MASK            0xffff


#define PMSTAT_OVFL                 (1<<0)      // 计数器溢出。计数器翻转时设置粘性位
// 从0xffffffff到0x0。
#define PMSTAT_INTSTART             (1<<4)      // 此计数器的溢出导致PerfMonInt被断言。


#define PGM_PMEN                    (1<<0)      // 全面启用所有性能计数


#endif

