// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
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
#ifndef _SOC_SDMMC_STRUCT_H_
#define _SOC_SDMMC_STRUCT_H_

#include <stdint.h>

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sdmmc_desc_s {
    struct {
        uint32_t reserved1: 1;
        uint32_t disable_int_on_completion: 1;
        uint32_t last_descriptor: 1;
        uint32_t first_descriptor: 1;
        uint32_t second_address_chained: 1;
        uint32_t end_of_ring: 1;
        uint32_t reserved2: 24;
        uint32_t card_error_summary: 1;
        uint32_t owned_by_idmac: 1;
    };
    struct {
        uint32_t buffer1_size: 13;
        uint32_t buffer2_size: 13;
        uint32_t reserved3: 6;
    };
    void* buffer1_ptr;
    union {
        void* buffer2_ptr;
        void* next_desc_ptr;
    };
} sdmmc_desc_t;

#define SDMMC_DMA_MAX_BUF_LEN 4096

_Static_assert(sizeof(sdmmc_desc_t) == 16, "invalid size of sdmmc_desc_t structure");


typedef struct sdmmc_hw_cmd_s {
    uint32_t cmd_index: 6;          ///<命令索引
    uint32_t response_expect: 1;    ///<如果预期响应，则设置
    uint32_t response_long: 1;      ///<0:应为短响应，1:应为长响应
    uint32_t check_response_crc: 1; ///<设置控制器是否应检查响应CRC
    uint32_t data_expected: 1;      ///<0:不需要数据，1:需要数据
    uint32_t rw: 1;                 ///<0：从卡读取，1：写入卡（不关心是否需要数据）
    uint32_t stream_mode: 1;        ///<0：块传输，1：流传输（不关心是否需要数据）
    uint32_t send_auto_stop: 1;     ///<设置为在传输结束时发送停止
    uint32_t wait_complete: 1;      ///<0:立即发送命令，1:等待上一个命令完成
    uint32_t stop_abort_cmd: 1;     ///<set，如果这是用于停止电流传输的停止或中止命令
    uint32_t send_init: 1;          ///<设置为发送初始化序列（80个时钟，共1个）
    uint32_t card_num: 5;           ///<卡号
    uint32_t update_clk_reg: 1;     ///＜0：正常命令，1：不发送命令，只更新时钟寄存器
    uint32_t read_ceata: 1;         ///<从CE-ATA设备读取时设置
    uint32_t ccs_expected: 1;       ///<如果预计来自CE-ATA设备的CCS，则设置
    uint32_t enable_boot: 1;        ///<设置为强制启动模式
    uint32_t expect_boot_ack: 1;    ///<当与enable_boot一起设置时，控制器期望启动ack模式
    uint32_t disable_boot: 1;       ///<设置为终止启动操作（不要与enable_boot一起设置）
    uint32_t boot_mode: 1;          ///＜0：强制启动操作，1：备用启动操作
    uint32_t volt_switch: 1;        ///<设置为启用电压切换（仅适用于CMD11）
    uint32_t use_hold_reg: 1;       ///<清除以绕过HOLD寄存器
    uint32_t reserved: 1;
    uint32_t start_command: 1;      ///<开始命令；一旦命令被发送到卡，位被清除。
} sdmmc_hw_cmd_t;  ///<cmd寄存器中使用的命令格式；定义此结构是为了更容易地构建命令值

_Static_assert(sizeof(sdmmc_hw_cmd_t) == 4, "invalid size of sdmmc_cmd_t structure");


typedef volatile struct sdmmc_dev_s {
    union {
        struct {
            uint32_t controller_reset: 1;
            uint32_t fifo_reset: 1;
            uint32_t dma_reset: 1;
            uint32_t reserved1: 1;
            uint32_t int_enable: 1;
            uint32_t dma_enable: 1;
            uint32_t read_wait: 1;
            uint32_t send_irq_response: 1;
            uint32_t abort_read_data: 1;
            uint32_t send_ccsd: 1;
            uint32_t send_auto_stop_ccsd: 1;
            uint32_t ceata_device_interrupt_status: 1;
            uint32_t reserved2: 4;
            uint32_t card_voltage_a: 4;
            uint32_t card_voltage_b: 4;
            uint32_t enable_od_pullup: 1;
            uint32_t use_internal_dma: 1;
            uint32_t reserved3: 6;
        };
        uint32_t val;
    } ctrl;

    uint32_t pwren;             ///<1：启用卡电源，0：禁用卡电源

    union {
        struct {
            uint32_t div0: 8;   ///<0：旁路，1-255：时钟除以（2*div0）。
            uint32_t div1: 8;   ///<0：旁路，1-255：时钟除以（2*div0）。
            uint32_t div2: 8;   ///<0：旁路，1-255：时钟除以（2*div0）。
            uint32_t div3: 8;   ///<0：旁路，1-255：时钟除以（2*div0）。
        };
        uint32_t val;
    } clkdiv;

    union {
        struct {
            uint32_t card0: 2;            ///<0-3：在div0-div3中为卡0选择时钟分频器
            uint32_t card1: 2;            ///<0-3：在div0-div3中为卡1选择时钟分频器
            uint32_t reserved: 28;
        };
        uint32_t val;
    } clksrc;

    union {
        struct {
            uint32_t cclk_enable: 16;       ///<1：启用时钟到卡，0：禁用时钟
            uint32_t cclk_low_power: 16;    ///<1：卡空闲时启用时钟门控，0：禁用时钟门控
        };
        uint32_t val;
    } clkena;

    union {
        struct {
            uint32_t response: 8;       ///<响应超时，卡输出时钟周期
            uint32_t data: 24;          ///<数据读取超时，以卡输出时钟周期为单位
        };
        uint32_t val;
    } tmout;

    union {
        struct {
            uint32_t card_width: 16;    ///<每张卡一位：0：1位模式，1：4位模式
            uint32_t card_width_8: 16;  ///<每个卡一位：0：非8位模式（使用相应的卡宽度位），1：8位模式
        };
        uint32_t val;
    } ctype;

    struct {
        uint32_t blksiz: 16;        ///<块大小，默认值0x200
        uint32_t reserved: 16;
    };

    uint32_t bytcnt;            ///<要传输的字节数

    union {
        struct {
            uint32_t cd: 1;             ///<卡检测中断启用
            uint32_t re: 1;             ///<响应错误中断启用
            uint32_t cmd_done: 1;       ///<命令完成中断启用
            uint32_t dto: 1;            ///<通过中断启用数据传输
            uint32_t txdr: 1;           ///<传输FIFO数据请求中断启用
            uint32_t rxdr: 1;           ///<接收FIFO数据请求中断启用
            uint32_t rcrc: 1;           ///<响应CRC错误中断启用
            uint32_t dcrc: 1;           ///<数据CRC错误中断启用
            uint32_t rto: 1;            ///<响应超时中断启用
            uint32_t drto: 1;           ///<数据读取超时中断启用
            uint32_t hto: 1;            ///<通过主机超时中断启用数据饥饿
            uint32_t frun: 1;           ///<FIFO欠载/超限错误中断启用
            uint32_t hle: 1;            ///<硬件锁定写入错误中断启用
            uint32_t sbi_bci: 1;        ///<启动位错误/忙清除中断启用
            uint32_t acd: 1;            ///<自动命令完成中断启用
            uint32_t ebe: 1;            ///<结束位错误/写入无CRC中断启用
            uint32_t sdio: 16;          ///<SDIO中断启用
        };
        uint32_t val;
    } intmask;

    uint32_t cmdarg;        ///<要传递给卡的命令参数

    sdmmc_hw_cmd_t cmd;

    uint32_t resp[4];           ///<来自卡的响应

    union {
        struct {
            uint32_t cd: 1;             ///<卡检测中断屏蔽状态
            uint32_t re: 1;             ///<响应错误中断屏蔽状态
            uint32_t cmd_done: 1;       ///<命令完成中断屏蔽状态
            uint32_t dto: 1;            ///<数据传输中断屏蔽状态
            uint32_t txdr: 1;           ///<传输FIFO数据请求中断屏蔽状态
            uint32_t rxdr: 1;           ///<接收FIFO数据请求中断屏蔽状态
            uint32_t rcrc: 1;           ///<响应CRC错误中断屏蔽状态
            uint32_t dcrc: 1;           ///<数据CRC错误中断屏蔽状态
            uint32_t rto: 1;            ///<响应超时中断屏蔽状态
            uint32_t drto: 1;           ///<数据读取超时中断屏蔽状态
            uint32_t hto: 1;            ///<主机超时中断屏蔽状态导致的数据饥饿
            uint32_t frun: 1;           ///<FIFO欠载/超限错误中断屏蔽状态
            uint32_t hle: 1;            ///<硬件锁定写入错误中断屏蔽状态
            uint32_t sbi_bci: 1;        ///<开始位错误/忙清除中断屏蔽状态
            uint32_t acd: 1;            ///<自动命令完成中断屏蔽状态
            uint32_t ebe: 1;            ///<结束位错误/写入无CRC中断屏蔽状态
            uint32_t sdio: 16;          ///<SDIO中断屏蔽状态
        };
        uint32_t val;
    } mintsts;

    union {
        struct {
            uint32_t cd: 1;             ///<板卡检测原始中断状态
            uint32_t re: 1;             ///<响应错误原始中断状态
            uint32_t cmd_done: 1;       ///<命令完成原始中断状态
            uint32_t dto: 1;            ///<原始中断状态上的数据传输
            uint32_t txdr: 1;           ///<传输FIFO数据请求原始中断状态
            uint32_t rxdr: 1;           ///<接收FIFO数据请求原始中断状态
            uint32_t rcrc: 1;           ///<响应CRC错误原始中断状态
            uint32_t dcrc: 1;           ///<数据CRC错误原始中断状态
            uint32_t rto: 1;            ///<响应超时原始中断状态
            uint32_t drto: 1;           ///<数据读取超时原始中断状态
            uint32_t hto: 1;            ///<主机超时原始中断状态导致的数据饥饿
            uint32_t frun: 1;           ///<FIFO欠载/超限错误原始中断状态
            uint32_t hle: 1;            ///<硬件锁定写入错误原始中断状态
            uint32_t sbi_bci: 1;        ///<起始位错误/忙清除原始中断状态
            uint32_t acd: 1;            ///<自动命令完成原始中断状态
            uint32_t ebe: 1;            ///<结束位错误/写入无CRC原始中断状态
            uint32_t sdio: 16;          ///<SDIO原始中断状态
        };
        uint32_t val;
    } rintsts;                          ///<可以通过写入此寄存器来清除中断

    union {
        struct {
            uint32_t fifo_rx_watermark: 1;  ///<FIFO达到接收水印级别
            uint32_t fifo_tx_watermark: 1;  ///<FIFO达到传输水印级别
            uint32_t fifo_empty: 1;         ///<FIFO为空
            uint32_t fifo_full: 1;          ///<FIFO已满
            uint32_t cmd_fsm_state: 4;      ///<命令FSM状态
            uint32_t data3_status: 1;       ///<如果存在卡，则该位读取1
            uint32_t data_busy: 1;          ///<如果卡忙，则此位读取1
            uint32_t data_fsm_busy: 1;      ///<如果发送/接收FSM忙，则此位读取1
            uint32_t response_index: 6;     ///<先前响应的索引
            uint32_t fifo_count: 13;        ///<FIFO中填充位置的数量
            uint32_t dma_ack: 1;            ///<DMA确认信号
            uint32_t dma_req: 1;            ///<DMA请求信号
        };
        uint32_t val;
    } status;

    union {
        struct {
            uint32_t tx_watermark: 12;      ///<FIFO TX水印级别
            uint32_t reserved1: 4;
            uint32_t rx_watermark: 12;      ///<FIFO RX水印级别
            uint32_t dw_dma_mts: 3;
            uint32_t reserved2: 1;
        };
        uint32_t val;
    } fifoth;

    union {
        struct {
            uint32_t cards: 2;              ///如果存在卡N，<位N读取0
            uint32_t reserved: 30;
        };
        uint32_t val;
    } cdetect;

    union {
        struct {
            uint32_t cards: 2;              ///如果卡N受写保护，则<位N读取1
            uint32_t reserved: 30;
        };
        uint32_t val;
    } wrtprt;

    uint32_t gpio;      ///<未使用
    uint32_t tcbcnt;    ///<传输（到卡）字节计数
    uint32_t tbbcnt;    ///<从主机传输到FIFO字节计数

    union {
        struct {
            uint32_t debounce_count: 24;    ///<去抖动滤波器使用的主机周期数，典型时间应为5-25ms
            uint32_t reserved: 8;
        };
    } debnce;

    uint32_t usrid;     ///<用户ID
    uint32_t verid;     ///<IP块版本
    uint32_t hcon;      ///<编译时IP配置
    union {
        struct {
            uint32_t voltage: 16;           ///<插槽电压控制；ESP32上没有操作。
            uint32_t ddr: 16;                ///<bit N为卡N启用DDR模式
        };
    } uhs;              ///<UHS相关设置

    union {
        struct {
            uint32_t cards: 2;          ///<位N重置卡N，激活低
            uint32_t reserved: 30;
        };
    } rst_n;

    uint32_t reserved_7c;

    union {
        struct {
            uint32_t sw_reset: 1;       ///<设置为重置DMA控制器
            uint32_t fb: 1;             ///<set，如果AHB主机执行固定突发传输
            uint32_t dsl: 5;            ///＜descriptor skip length：在两个非约束描述符之间跳过的单词数
            uint32_t enable: 1;         ///<设置为启用IDMAC
            uint32_t pbl: 3;            ///<可编程突发长度
            uint32_t reserved: 21;
        };
        uint32_t val;
    } bmod;

    uint32_t pldmnd;                    ///<设置任何位以从挂起状态恢复IDMAC FSM
    sdmmc_desc_t* dbaddr;        ///<描述符列表基

    union {
        struct {
            uint32_t ti: 1;         ///<传输中断状态
            uint32_t ri: 1;         ///<接收中断状态
            uint32_t fbe: 1;        ///<致命总线错误
            uint32_t reserved1: 1;
            uint32_t du: 1;         ///<描述符不可用
            uint32_t ces: 1;        ///<卡片错误摘要
            uint32_t reserved2: 2;
            uint32_t nis: 1;        ///<正常中断摘要
            uint32_t ais: 1;        ///<异常中断摘要
            uint32_t fbe_code: 3;   ///<致命总线错误代码
            uint32_t fsm: 4;        ///<DMAC FSM状态
            uint32_t reserved3: 15;
        };
        uint32_t val;
    } idsts;

    union {
        struct {
            uint32_t ti: 1;         ///<传输中断启用
            uint32_t ri: 1;         ///<接收中断启用
            uint32_t fbe: 1;        ///<致命总线错误中断启用
            uint32_t reserved1: 1;
            uint32_t du: 1;         ///<描述符不可用中断启用
            uint32_t ces: 1;        ///<卡错误中断启用
            uint32_t reserved2: 2;
            uint32_t ni: 1;         ///<正常中断中断启用
            uint32_t ai: 1;         ///<异常中断启用
            uint32_t reserved3: 22;
        };
        uint32_t val;
    } idinten;

    uint32_t dscaddr;       ///<当前主机描述符地址
    uint32_t dscaddrl;      ///<未使用
    uint32_t dscaddru;      ///<未使用
    uint32_t bufaddrl;      ///<未使用
    uint32_t bufaddru;      ///<未使用
    uint32_t reserved_a8[22];
    union {
        struct {
            uint32_t read_thr_en : 1;       ///<仅当FIFO的空间大于读取阈值时才启动传输
            uint32_t busy_clr_int_en : 1;   ///<启用繁忙清除中断的生成
            uint32_t write_thr_en : 1;      ///<相当于read_thr_en的写入
            uint32_t reserved1 : 13;
            uint32_t card_threshold : 12;   ///<读取/写入阈值（字节）
            uint32_t reserved28: 4;
        };
        uint32_t val;
    } cardthrctl;
    uint32_t back_end_power;
    uint32_t uhs_reg_ext;
    uint32_t emmc_ddr_reg;
    uint32_t enable_shift;
    uint32_t reserved_114[443];
    union {
        struct {
            uint32_t phase_dout: 3;         ///<数据输出时钟相位（0x0:0，0x1:90，0x4:180，0x6:270）
            uint32_t phase_din: 3;          ///<数据输入时钟相位
            uint32_t phase_core: 3;         ///<SDMMC外围设备的时钟相位
            uint32_t div_factor_p: 4;       ///<控制时钟周期；它将是（div_factor_p+1）/160MHz
            uint32_t div_factor_h: 4;       ///<控制高脉冲长度；它将是（div_factor_h+1）/160MHz
            uint32_t div_factor_m: 4;       ///<应等于div_factor_p
            uint32_t reserved21: 11;
        };
        uint32_t val;
    } clock;
} sdmmc_dev_t;
extern sdmmc_dev_t SDMMC;

_Static_assert(sizeof(sdmmc_dev_t) == 0x804, "invalid size of sdmmc_dev_t structure");

#ifdef __cplusplus
}
#endif

#endif //_SOC_SDMMC_STRUCT_H_

