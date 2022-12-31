// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* ----------------------------寄存器布局------------------------------*/

/* TWAI外设的寄存器为8位，但是ESP32-S2只能每32位访问一次外设寄存器。因此，每个TWAI寄存器被映射到每32位的最低有效字节。
 */

typedef volatile struct twai_dev_s {
    //配置和控制寄存器
    union {
        struct {
            uint32_t rm: 1;                     /* MOD.0重置模式*/
            uint32_t lom: 1;                    /* MOD.1仅监听模式*/
            uint32_t stm: 1;                    /* MOD.2自检模式*/
            uint32_t afm: 1;                    /* MOD.3验收过滤器模式*/
            uint32_t reserved4: 28;             /* 内部保留。MOD.4睡眠模式不受支持*/
        };
        uint32_t val;
    } mode_reg;                                 /* 地址0x0000*/
    union {
        struct {
            uint32_t tr: 1;                     /* CMR.0传输请求*/
            uint32_t at: 1;                     /* CMR.1中止传输*/
            uint32_t rrb: 1;                    /* CMR.2释放接收缓冲区*/
            uint32_t cdo: 1;                    /* CMR.3清除数据超限*/
            uint32_t srr: 1;                    /* CMR.4自我接收请求*/
            uint32_t reserved5: 27;             /* 内部保留*/
        };
        uint32_t val;
    } command_reg;                              /* 地址0x0004*/
    union {
        struct {
            uint32_t rbs: 1;                    /* SR.0接收缓冲区状态*/
            uint32_t dos: 1;                    /* 数据超限状态*/
            uint32_t tbs: 1;                    /* SR.2传输缓冲区状态*/
            uint32_t tcs: 1;                    /* SR.3传输完成状态*/
            uint32_t rs: 1;                     /* SR.4接收状态*/
            uint32_t ts: 1;                     /* SR.5传输状态*/
            uint32_t es: 1;                     /* SR.6错误状态*/
            uint32_t bs: 1;                     /* SR.7总线状态*/
            uint32_t ms: 1;                     /* SR.8未命中状态*/
            uint32_t reserved9: 23;             /* 内部保留*/
        };
        uint32_t val;
    } status_reg;                               /* 地址0x0008*/
    union {
        struct {
            uint32_t ri: 1;                     /* IR.0接收中断*/
            uint32_t ti: 1;                     /* IR.1传输中断*/
            uint32_t ei: 1;                     /* IR.2错误中断*/
            uint32_t doi: 1;                    /* IR.3数据溢出中断*/
            uint32_t reserved4: 1;              /* 内部保留（不支持唤醒）*/
            uint32_t epi: 1;                    /* IR.5错误被动中断*/
            uint32_t ali: 1;                    /* IR.6仲裁丢失中断*/
            uint32_t bei: 1;                    /* IR.7总线错误中断*/
            uint32_t reserved8: 24;             /* 内部保留*/
        };
        uint32_t val;
    } interrupt_reg;                           /* 地址0x000C*/
    union {
        struct {
            uint32_t rie: 1;                    /* IER.0接收中断启用*/
            uint32_t tie: 1;                    /* IER.1传输中断启用*/
            uint32_t eie: 1;                    /* IER.2错误中断启用*/
            uint32_t doie: 1;                   /* IER.3数据溢出中断启用*/
            uint32_t reserved4: 1;              /* 内部保留（不支持唤醒）*/
            uint32_t epie: 1;                   /* IER.5错误被动中断启用*/
            uint32_t alie: 1;                   /* IER.6仲裁丢失中断启用*/
            uint32_t beie: 1;                   /* IER.7总线错误中断启用*/
            uint32_t reserved8: 24;             /* 内部保留*/
        };
        uint32_t val;
    } interrupt_enable_reg;                     /* 地址0x0010*/
    uint32_t reserved_14;
    union {
        struct {
            uint32_t brp: 14;                   /* BTR0[13:0]波特率预分频器*/
            uint32_t sjw: 2;                    /* BTR0[15:14]同步跳转宽度*/
            uint32_t reserved16: 16;            /* 内部保留*/
        };
        uint32_t val;
    } bus_timing_0_reg;                         /* 地址0x0018*/
    union {
        struct {
            uint32_t tseg1: 4;                  /* BTR1[3:0]定时段1*/
            uint32_t tseg2: 3;                  /* BTR1[6:4]定时段2*/
            uint32_t sam: 1;                    /* BTR1.7取样*/
            uint32_t reserved8: 24;             /* 内部保留*/
        };
        uint32_t val;
    } bus_timing_1_reg;                         /* 地址0x001C*/
    uint32_t reserved_20;                       /* 地址0x0020（不支持输出控制）*/
    uint32_t reserved_24;                       /* 地址0x0024（不支持测试寄存器）*/
    uint32_t reserved_28;                       /* 地址0x0028*/

    //捕获和计数器寄存器
    union {
        struct {
            uint32_t alc: 5;                    /* ALC[4:0]仲裁丢失捕获*/
            uint32_t reserved5: 27;             /* 内部保留*/
        };
        uint32_t val;
    } arbitration_lost_captue_reg;              /* 地址0x002C*/
    union {
        struct {
            uint32_t seg: 5;                    /* ECC[4:0]错误代码段0至5*/
            uint32_t dir: 1;                    /* ECC.5错误方向（TX/RX）*/
            uint32_t errc: 2;                   /* ECC[7:6]错误代码*/
            uint32_t reserved8: 24;             /* 内部保留*/
        };
        uint32_t val;
    } error_code_capture_reg;                   /* 地址0x0030*/
    union {
        struct {
            uint32_t ewl: 8;                    /* EWL[7:0]错误警告限制*/
            uint32_t reserved8: 24;             /* 内部保留*/
        };
        uint32_t val;
    } error_warning_limit_reg;                  /* 地址0x0034*/
    union {
        struct {
            uint32_t rxerr: 8;                  /* RXERR[7:0]接收错误计数器*/
            uint32_t reserved8: 24;             /* 内部保留*/
        };
        uint32_t val;
    } rx_error_counter_reg;                     /* 地址0x0038*/
    union {
        struct {
            uint32_t txerr: 8;                  /* TXERR[7:0]接收错误计数器*/
            uint32_t reserved8: 24;             /* 内部保留*/
        };
        uint32_t val;
    } tx_error_counter_reg;                     /* 地址0x003C*/

    //共享寄存器（TX缓冲/RX缓冲/Acc滤波器）
    union {
        struct {
            union {
                struct {
                    uint32_t byte: 8;           /* ACRx[7:0]验收规范*/
                    uint32_t reserved8: 24;     /* 内部保留*/
                };
                uint32_t val;
            } acr[4];
            union {
                struct {
                    uint32_t byte: 8;           /* AMRx[7:0]接受掩码*/
                    uint32_t reserved8: 24;     /* 内部保留*/
                };
                uint32_t val;
            } amr[4];
            uint32_t reserved_60;
            uint32_t reserved_64;
            uint32_t reserved_68;
            uint32_t reserved_6c;
            uint32_t reserved_70;
        } acceptance_filter;
        union {
            struct {
                uint32_t byte: 8;               /* TX/RX字节X[7:0]*/
                uint32_t reserved24: 24;        /* 内部保留*/
            };
            uint32_t val;
        } tx_rx_buffer[13];
    };                                          /* 地址0x0040-0x0070*/

    //杂项寄存器
    union {
        struct {
            uint32_t rmc: 7;                    /* RMC[6:0]RX消息计数器*/
            uint32_t reserved7: 25;             /* 内部保留*/
        };
        uint32_t val;
    } rx_message_counter_reg;                   /* 地址0x0074*/
    uint32_t reserved_78;                       /* 地址0x0078（不支持RX缓冲区起始地址）*/
    union {
        struct {
            uint32_t cd: 8;                     /* 基于fOSC的CDR[7:0]CLKOUT频率选择器*/
            uint32_t co: 1;                     /* CDR.8 CLKOUT启用/禁用*/
            uint32_t reserved9: 23;             /* 内部保留*/
        };
        uint32_t val;
    } clock_divider_reg;                        /* 地址0x007C*/
} twai_dev_t;

_Static_assert(sizeof(twai_dev_t) == 128, "TWAI registers should be 32 * 4 bytes");

extern twai_dev_t TWAI;

#ifdef __cplusplus
}
#endif

