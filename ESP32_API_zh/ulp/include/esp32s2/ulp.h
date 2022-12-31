// 版权所有2016-2018 Espressif Systems（上海）私人有限公司
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

#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "esp_err.h"
#include "soc/soc.h"
#include "ulp_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ULP_FSM_PREPARE_SLEEP_CYCLES 2    /*!< FSM为睡眠准备ULP所花费的周期*/
#define ULP_FSM_WAKEUP_SLEEP_CYCLES  2    /*!< FSM从睡眠中唤醒ULP所花费的周期*/

/**
 * @defgroup ulp_registers ulp协处理器寄存器@{
 */


#define R0 0    /*!< 通用寄存器0*/
#define R1 1    /*!< 通用寄存器1*/
#define R2 2    /*!< 通用寄存器2*/
#define R3 3    /*!< 通用寄存器3*/
/**@}*/

/** @defgroup ulp_opcodes ulp协处理器操作码、子操作码和各种修饰符/标志
 *
 * 这些定义不打算直接使用。它们在以后的指令定义中使用。
 *
 * @{
 */

#define OPCODE_WR_REG 1         /*!< 指令：写入外围寄存器（RTC_CNTL/RTC_IO/SARADC）（尚未实现）*/

#define OPCODE_RD_REG 2         /*!< 指令：读取外围寄存器（RTC_CNTL/RTC_IO/SARADC）（尚未实现）*/

#define RD_REG_PERIPH_RTC_CNTL 0    /*!< RD_REG和WR_REG指令的RTC_CNTL外围设备标识符*/
#define RD_REG_PERIPH_RTC_IO   1    /*!< RD_REG和WR_REG指令的RTC_IO外围设备标识符*/
#define RD_REG_PERIPH_SENS     2    /*!< RD_REG和WR_REG指令的SARADC外围设备标识符*/
#define RD_REG_PERIPH_RTC_I2C  3    /*!< RD_REG和WR_REG指令的RTC_I2C外围设备标识符*/

#define OPCODE_I2C 3            /*!< 指令：读/写I2C（尚未实现）*/

#define OPCODE_DELAY 4          /*!< 指令：给定周期数的延迟（nop）*/

#define OPCODE_ADC 5            /*!< 说明：SAR ADC测量（尚未实施）*/

#define OPCODE_ST 6             /*!< 指令：间接存储到RTC内存*/
#define SUB_OPCODE_ST 4         /*!< 存储32位，16个MSB包含PC，16个LSB包含源寄存器的值*/

#define OPCODE_ALU 7            /*!< 算术指令*/
#define SUB_OPCODE_ALU_REG 0    /*!< 算术指令，两个源值都在寄存器中*/
#define SUB_OPCODE_ALU_IMM 1    /*!< 算术指令，一个源值是立即数*/
#define SUB_OPCODE_ALU_CNT 2    /*!< 计数器寄存器和立即数之间的算术指令（尚未实现）*/
#define ALU_SEL_ADD 0           /*!< 附加*/
#define ALU_SEL_SUB 1           /*!< 扣除*/
#define ALU_SEL_AND 2           /*!< 逻辑AND*/
#define ALU_SEL_OR  3           /*!< 逻辑或*/
#define ALU_SEL_MOV 4           /*!< 复制值（直接到目标寄存器或源寄存器到目标寄存器*/
#define ALU_SEL_LSH 5           /*!< 按给定位数向左移动*/
#define ALU_SEL_RSH 6           /*!< 按给定位数右移*/

#define OPCODE_BRANCH 8         /*!< 分支机构指令*/
#define SUB_OPCODE_BX  0        /*!< 分支到绝对PC（直接或登记）*/
#define BX_JUMP_TYPE_DIRECT 0   /*!< 无条件跳转*/
#define BX_JUMP_TYPE_ZERO 1     /*!< 如果最后一个ALU结果为零，则分支*/
#define BX_JUMP_TYPE_OVF 2      /*!< 如果最后一个ALU操作导致溢出，则进行分支*/
#define SUB_OPCODE_B  1         /*!< 分支到相对偏移*/
#define B_CMP_L 0               /*!< 如果R0小于立即数，则分支*/
#define B_CMP_GE 1              /*!< 如果R0大于或等于立即数，则分支*/

#define OPCODE_END 9            /*!< 停止执行程序*/
#define SUB_OPCODE_END 0        /*!< 停止执行程序并可选地唤醒芯片*/
#define SUB_OPCODE_SLEEP 1      /*!< 停止执行程序并在选定的间隔后再次运行*/

#define OPCODE_TSENS 10         /*!< 说明：温度传感器测量（尚未实施）*/

#define OPCODE_HALT 11          /*!< 停止协处理器*/

#define OPCODE_LD 13            /*!< 从RTC内存间接加载低16位*/

#define OPCODE_MACRO 15         /*!< 不是真正的操作码。用于标识程序中的标签和分支*/
#define SUB_OPCODE_MACRO_LABEL 0    /*!< 标签宏*/
#define SUB_OPCODE_MACRO_BRANCH 1   /*!< 分支宏*/
/**@}*/

/**
 * @brief 指令格式结构
 *
 * 所有ULP指令均为32位长。此联合包含所有受支持指令使用的字段布局。这种联合还包括一个特殊的“宏”指令布局。这不是可由CPU执行的实际指令。它充当通过ulp_process_macros_and_load函数从程序中删除的令牌。
 *
 * 这些结构不打算直接使用。下面提供的预处理器定义用正确的参数填充这些结构的字段。
 */
union ulp_insn {

    struct {
        uint32_t cycles : 16;       /*!< 睡眠周期数*/
        uint32_t unused : 12;       /*!< 未使用的*/
        uint32_t opcode : 4;        /*!< 操作码（Opcode_DELAY）*/
    } delay;                        /*!< DELAY指令格式*/

    struct {
        uint32_t dreg : 2;          /*!< 包含要存储的数据的寄存器*/
        uint32_t sreg : 2;          /*!< 包含RTC内存中地址的寄存器（以字表示）*/
        uint32_t unused1 : 6;       /*!< 未使用的*/
        uint32_t offset : 11;       /*!< 要添加到sreg的偏移量*/
        uint32_t unused2 : 4;       /*!< 未使用的*/
        uint32_t sub_opcode : 3;    /*!< 子操作码（Sub_opcode_ST）*/
        uint32_t opcode : 4;        /*!< 操作码（Opcode_ST）*/
    } st;                           /*!< ST指令格式*/

    struct {
        uint32_t dreg : 2;          /*!< 注册数据应加载到的位置*/
        uint32_t sreg : 2;          /*!< 包含RTC内存中地址的寄存器（以字表示）*/
        uint32_t unused1 : 6;       /*!< 未使用的*/
        uint32_t offset : 11;       /*!< 要添加到sreg的偏移量*/
        uint32_t unused2 : 7;       /*!< 未使用的*/
        uint32_t opcode : 4;        /*!< 操作码（Opcode_LD）*/
    } ld;                           /*!< LD指令格式*/

    struct {
        uint32_t unused : 28;       /*!< 未使用的*/
        uint32_t opcode : 4;        /*!< 操作码（Opcode_HALT）*/
    } halt;                         /*!< HALT指令格式*/

    struct {
        uint32_t dreg : 2;          /*!< 包含目标PC的寄存器，以字表示（如果.reg==1则使用）*/
        uint32_t addr : 11;         /*!< 目标PC，以文字表示（如果.reg==0则使用）*/
        uint32_t unused : 8;        /*!< 未使用的*/
        uint32_t reg : 1;           /*!< 寄存器（1）或立即数（0）中的目标PC*/
        uint32_t type : 3;          /*!< 跳转条件（BX_Jump_TYPE_xxx）*/
        uint32_t sub_opcode : 3;    /*!< 子操作码（Sub_opcode_BX）*/
        uint32_t opcode : 4;        /*!< 操作码（Opcode_BRANCH）*/
    } bx;                           /*!< BRANCH指令的格式（绝对地址）*/

    struct {
        uint32_t imm : 16;          /*!< 要比较的即时值*/
        uint32_t cmp : 1;           /*!< 要执行的比较：B_CMP_L或B_CMP_GE*/
        uint32_t offset : 7;        /*!< 相对于当前PC的目标PC偏移的绝对值，用文字表示*/
        uint32_t sign : 1;          /*!< 目标PC偏移量的符号：0：正，1：负*/
        uint32_t sub_opcode : 3;    /*!< 子操作码（Sub_opcode_B）*/
        uint32_t opcode : 4;        /*!< 操作码（Opcode_BRANCH）*/
    } b;                            /*!< BRANCH指令的格式（相对地址）*/

    struct {
        uint32_t dreg : 2;          /*!< 目标寄存器*/
        uint32_t sreg : 2;          /*!< 使用操作数A注册*/
        uint32_t treg : 2;          /*!< 使用操作数B注册*/
        uint32_t unused : 15;       /*!< 未使用的*/
        uint32_t sel : 4;           /*!< 要执行的操作，ALU_SEL_xxx之一*/
        uint32_t sub_opcode : 3;    /*!< 子操作码（Sub_opcode_ALU_REG）*/
        uint32_t opcode : 4;        /*!< 操作码（Opcode_ALU）*/
    } alu_reg;                      /*!< ALU指令的格式（两个源都是寄存器）*/

    struct {
        uint32_t dreg : 2;          /*!< 目标寄存器*/
        uint32_t sreg : 2;          /*!< 使用操作数A注册*/
        uint32_t imm : 16;          /*!< 操作数B的立即数*/
        uint32_t unused : 1;        /*!< 未使用的*/
        uint32_t sel : 4;           /*!< 要执行的操作，ALU_SEL_xxx之一*/
        uint32_t sub_opcode : 3;    /*!< 子操作码（Sub_opcode_ALU_IMM）*/
        uint32_t opcode : 4;        /*!< 操作码（Opcode_ALU）*/
    } alu_imm;                      /*!< ALU指令的格式（一个源是立即数）*/

    struct {
        uint32_t addr : 8;          /*!< RTC_CNTL、RTC_IO或SARADC内的地址*/
        uint32_t periph_sel : 2;    /*!< 选择外围设备：RTC_CNTL（0）、RTC_IO（1）、SARADC（2）*/
        uint32_t data : 8;          /*!< 要写入的8位数据*/
        uint32_t low : 5;           /*!< 低位*/
        uint32_t high : 5;          /*!< 高位*/
        uint32_t opcode : 4;        /*!< 操作码（Opcode_WR_REG）*/
    } wr_reg;                       /*!< WR_REG指令格式*/

    struct {
        uint32_t addr : 8;          /*!< RTC_CNTL、RTC_IO或SARADC内的地址*/
        uint32_t periph_sel : 2;    /*!< 选择外围设备：RTC_CNTL（0）、RTC_IO（1）、SARADC（2）*/
        uint32_t unused : 8;        /*!< 未使用的*/
        uint32_t low : 5;           /*!< 低位*/
        uint32_t high : 5;          /*!< 高位*/
        uint32_t opcode : 4;        /*!< 操作码（Opcode_RD_REG）*/
    } rd_reg;                       /*!< RD_REG指令的格式*/

    struct {
        uint32_t dreg : 2;          /*!< 注册ADC结果的存储位置*/
        uint32_t mux : 4;           /*!< 选择SARADC焊盘（多路复用器+1）*/
        uint32_t sar_sel : 1;       /*!< 选择SARADC0（0）或SARADC1（1）*/
        uint32_t unused1 : 1;       /*!< 未使用的*/
        uint32_t cycles : 16;       /*!< TBD，用于测量的周期*/
        uint32_t unused2 : 4;       /*!< 未使用的*/
        uint32_t opcode: 4;         /*!< 操作码（Opcode_ADC）*/
    } adc;                          /*!< ADC指令格式*/

    struct {
        uint32_t dreg : 2;          /*!< 登记存储温度测量结果的位置*/
        uint32_t wait_delay: 14;    /*!< 测量完成后等待的周期*/
        uint32_t reserved: 12;      /*!< 保留，设置为0*/
        uint32_t opcode: 4;         /*!< 操作码（Opcode_TSENS）*/
    } tsens;                        /*!< TSENS指令格式*/

    struct {
        uint32_t i2c_addr : 8;      /*!< I2C从属地址*/
        uint32_t data : 8;          /*!< 要读取或写入的数据*/
        uint32_t low_bits : 3;      /*!< TBD */
        uint32_t high_bits : 3;     /*!< TBD */
        uint32_t i2c_sel : 4;       /*!< 待定，选择reg_i2c_slave_address[7:0]*/
        uint32_t unused : 1;        /*!< 未使用的*/
        uint32_t rw : 1;            /*!< 写入（1）或读取（0）*/
        uint32_t opcode : 4;        /*!< 操作码（Opcode_I2C）*/
    } i2c;                          /*!< I2C指令格式*/

    struct {
        uint32_t wakeup : 1;        /*!< 设置为1以唤醒芯片*/
        uint32_t unused : 24;       /*!< 未使用的*/
        uint32_t sub_opcode : 3;    /*!< 子操作码（Sub_opcode_WAKEUP）*/
        uint32_t opcode : 4;        /*!< 操作码（Opcode_END）*/
    } end;                          /*!< 带唤醒的END指令格式*/

    struct {
        uint32_t cycle_sel : 4;     /*!< 选择SARADC_ULP_CP_SLEEP_CYCx_REG中的哪一个来获取睡眠持续时间*/
        uint32_t unused : 21;       /*!< 未使用的*/
        uint32_t sub_opcode : 3;    /*!< 子操作码（Sub_opcode_SLEEP）*/
        uint32_t opcode : 4;        /*!< 操作码（Opcode_END）*/
    } sleep;                        /*!< 带休眠的END指令格式*/

    struct {
        uint32_t label : 16;        /*!< 标签编号*/
        uint32_t unused : 8;        /*!< 未使用的*/
        uint32_t sub_opcode : 4;    /*!< SUB_OPCODE_MRO_LABEL或SUB_OPCODE _MRO_BRANCH*/
        uint32_t opcode: 4;         /*!< 操作码（OPCODEMACRO）*/
    } macro;                        /*!< LABEL和BRANCH宏使用的标记格式*/

};

typedef union ulp_insn ulp_insn_t;

_Static_assert(sizeof(ulp_insn_t) == 4, "ULP coprocessor instruction size should be 4 bytes");

/**
 * 给定周期数的延迟（nop）
 */
#define I_DELAY(cycles_) { .delay = {\
    .cycles = cycles_, \
    .unused = 0, \
    .opcode = OPCODE_DELAY } }

/**
 * 停止协处理器。
 *
 * 此指令停止协处理器，但使ULP计时器保持活动状态。因此，ULP程序将由计时器重新启动。要停止程序并防止计时器重新启动程序，请使用I_END（0）指令。
 */
#define I_HALT() { .halt = {\
    .unused = 0, \
    .opcode = OPCODE_HALT } }

/**
 * 将SoC外围寄存器映射到RD_REG和WR_REG指令的peripher_sel字段。
 *
 * @param reg RTC_CNTL_、RTC_IO_、SENS_和RTC_I2C外设中的外设寄存器。
 * @return 此寄存器所属外围设备的peripher_sel值。
 */
static inline uint32_t SOC_REG_TO_ULP_PERIPH_SEL(uint32_t reg) {
    uint32_t ret = 3;
    if (reg < DR_REG_RTCCNTL_BASE) {
        assert(0 && "invalid register base");
    } else if (reg < DR_REG_RTCIO_BASE) {
        ret = RD_REG_PERIPH_RTC_CNTL;
    } else if (reg < DR_REG_SENS_BASE) {
        ret = RD_REG_PERIPH_RTC_IO;
    } else if (reg < DR_REG_RTC_I2C_BASE){
        ret = RD_REG_PERIPH_SENS;
    } else if (reg < DR_REG_IO_MUX_BASE){
        ret = RD_REG_PERIPH_RTC_I2C;
    } else {
        assert(0 && "invalid register base");
    }
    return ret;
}

/**
 * 将文字值写入外围寄存器
 *
 * reg[high_bit:low_bit]=val此指令可以访问RTC_CNTL_、RTC_IO_、SENS_和RTC_I2C外围寄存器。
 */
#define I_WR_REG(reg, low_bit, high_bit, val) {.wr_reg = {\
    .addr = (reg & 0xff) / sizeof(uint32_t), \
    .periph_sel = SOC_REG_TO_ULP_PERIPH_SEL(reg), \
    .data = val, \
    .low = low_bit, \
    .high = high_bit, \
    .opcode = OPCODE_WR_REG } }

/**
 * 从外围寄存器读取R0
 *
 * R0=reg[high_bit:low_bit]此指令可以访问RTC_CNTL_、RTC_IO_、SENS_和RTC_I2C外围寄存器。
 */
#define I_RD_REG(reg, low_bit, high_bit) {.rd_reg = {\
    .addr = (reg & 0xff) / sizeof(uint32_t), \
    .periph_sel = SOC_REG_TO_ULP_PERIPH_SEL(reg), \
    .unused = 0, \
    .low = low_bit, \
    .high = high_bit, \
    .opcode = OPCODE_RD_REG } }

/**
 * 设置或清除外围寄存器中的一位。
 *
 * 将寄存器reg的位（1<<shift）设置为值val。此指令可以访问RTC_CNTL_、RTC_IO_、SENS_和RTC_I2C外围寄存器。
 */
#define I_WR_REG_BIT(reg, shift, val) I_WR_REG(reg, shift, shift, val)

/**
 * 将SoC从沉睡中唤醒。
 *
 * 此指令启动从深度睡眠中醒来。在进入深度睡眠之前，使用esp_deep_sleep_enable_ulp_wakeup启用由ulp触发的深度睡眠唤醒。请注意，ULP程序仍将继续运行，直到I_HALT指令发出，并且即使SoC被唤醒，它仍将定期由计时器重新启动。
 *
 * 要停止ULP程序，请使用I_HALT指令。
 *
 * 要禁用启动ULP程序的计时器，请使用I_END（）指令。I_END指令清除控制ULP计时器的RTC_CNTL_STATE0_REG寄存器的RTC_CNTL_ULP_CP_SLP_TIMER_EN_S位。
 */
#define I_WAKE() { .end = { \
        .wakeup = 1, \
        .unused = 0, \
        .sub_opcode = SUB_OPCODE_END, \
        .opcode = OPCODE_END } }

/**
 * 停止ULP程序计时器。
 *
 * 这是一个禁用ULP程序计时器的方便宏。使用此指令后，在调用ULP_run函数之前，ULP程序将不再重新启动。
 *
 * ULP程序将在此指令之后继续运行。要停止当前运行的程序，请使用I_HALT（）。
 */
#define I_END() \
    I_WR_REG_BIT(RTC_CNTL_STATE0_REG, RTC_CNTL_ULP_CP_SLP_TIMER_EN_S, 0)
/**
 * 选择用于运行ULP程序的时间间隔。
 *
 * 此指令选择ULP程序计时器使用的SENS_SLEEP_CYCLES_Sx寄存器值。当ULP程序在I_HALT指令处停止时，ULP程序计时器开始计数。当计数器达到所选SENS_SLEEP_CYCLES_Sx寄存器的值时，ULP程序从开始地址（传递给ULP_run函数）再次开始运行。有5个SENS_SLEEP_CYCLES_Sx寄存器，因此0<=timer_idx<5。
 *
 * 默认情况下，ULP程序计时器使用SENS_SLEEP_CYCLES_S0寄存器。
 */
#define I_SLEEP_CYCLE_SEL(timer_idx) { .sleep = { \
        .cycle_sel = timer_idx, \
        .unused = 0, \
        .sub_opcode = SUB_OPCODE_SLEEP, \
        .opcode = OPCODE_END } }

/**
 * 执行温度传感器测量并将其存储到reg_dest中。
 *
 * 延迟可以设置在1和（（1<<14）-1）之间。值越高，测量分辨率越高。
 */
#define I_TSENS(reg_dest, delay) { .tsens = { \
        .dreg = reg_dest, \
        .wait_delay = delay, \
        .reserved = 0, \
        .opcode = OPCODE_TSENS } }

/**
 * 执行ADC测量并将结果存储在reg_dest中。
 *
 * adc_idx选择adc（0或1）。pad_idx选择ADC焊盘（0-7）。
 */
#define I_ADC(reg_dest, adc_idx, pad_idx) { .adc = {\
        .dreg = reg_dest, \
        .mux = pad_idx + 1, \
        .sar_sel = adc_idx, \
        .unused1 = 0, \
        .cycles = 0, \
        .unused2 = 0, \
        .opcode = OPCODE_ADC } }

/**
 * 将寄存器reg_val中的值存储到RTC内存中。
 *
 * 该值被写入通过将reg_addr寄存器和offset_字段的值相加而计算的偏移量（该偏移量以32位字表示）。写入RTC存储器的32位构建如下：
 * -位[31:21]保存当前指令的PC，用32位字表示
 * -位[20:18]=3'b0
 * -位[17:16]reg_addr（0..3）
 * -位[15:0]分配reg_val的内容
 *
 * RTC_SLOW_MEM[addr+offset_]=｛insn_PC[10:0]，3'b0，reg_addr，reg_val[15:0]｝
 */
#define I_ST(reg_val, reg_addr, offset_) { .st = { \
    .dreg = reg_val, \
    .sreg = reg_addr, \
    .unused1 = 0, \
    .offset = offset_, \
    .unused2 = 0, \
    .sub_opcode = SUB_OPCODE_ST, \
    .opcode = OPCODE_ST } }


/**
 * 将值从RTC内存加载到reg_dest寄存器。
 *
 * 从RTC内存字中加载16个LSB，由reg_addr中的值和offset_的值之和给出。
 */
#define I_LD(reg_dest, reg_addr, offset_) { .ld = { \
    .dreg = reg_dest, \
    .sreg = reg_addr, \
    .unused1 = 0, \
    .offset = offset_, \
    .unused2 = 0, \
    .opcode = OPCODE_LD } }


/**
 *  如果R0小于立即数，则分支相对。
 *
 *  pc_offset以字表示，可以从-127到127 imm_value是一个16位值，用于比较R0与
 */
#define I_BL(pc_offset, imm_value) { .b = { \
    .imm = imm_value, \
    .cmp = B_CMP_L, \
    .offset = abs(pc_offset), \
    .sign = (pc_offset >= 0) ? 0 : 1, \
    .sub_opcode = SUB_OPCODE_B, \
    .opcode = OPCODE_BRANCH } }

/**
 *  如果R0大于或等于立即数，则分支相对。
 *
 *  pc_offset以字表示，可以从-127到127 imm_value是一个16位值，用于比较R0与
 */
#define I_BGE(pc_offset, imm_value) { .b = { \
    .imm = imm_value, \
    .cmp = B_CMP_GE, \
    .offset = abs(pc_offset), \
    .sign = (pc_offset >= 0) ? 0 : 1, \
    .sub_opcode = SUB_OPCODE_B, \
    .opcode = OPCODE_BRANCH } }

/**
 * 绝对PC的无条件分支，寄存器中的地址。
 *
 * reg_pc是包含要跳转到的地址的寄存器。地址用32位字表示。
 */
#define I_BXR(reg_pc) { .bx = { \
    .dreg = reg_pc, \
    .addr = 0, \
    .unused = 0, \
    .reg = 1, \
    .type = BX_JUMP_TYPE_DIRECT, \
    .sub_opcode = SUB_OPCODE_BX, \
    .opcode = OPCODE_BRANCH } }

/**
 *  无条件分支到绝对PC，直接地址。
 *
 *  地址imm_pc用32位字表示。
 */
#define I_BXI(imm_pc) { .bx = { \
    .dreg = 0, \
    .addr = imm_pc, \
    .unused = 0, \
    .reg = 0, \
    .type = BX_JUMP_TYPE_DIRECT, \
    .sub_opcode = SUB_OPCODE_BX, \
    .opcode = OPCODE_BRANCH } }

/**
 * 如果ALU结果为零，则分支到绝对PC，地址在寄存器中。
 *
 * reg_pc是包含要跳转到的地址的寄存器。地址用32位字表示。
 */
#define I_BXZR(reg_pc) { .bx = { \
    .dreg = reg_pc, \
    .addr = 0, \
    .unused = 0, \
    .reg = 1, \
    .type = BX_JUMP_TYPE_ZERO, \
    .sub_opcode = SUB_OPCODE_BX, \
    .opcode = OPCODE_BRANCH } }

/**
 * 如果ALU结果为零，则分支到绝对PC，立即地址。
 *
 * 地址imm_pc用32位字表示。
 */
#define I_BXZI(imm_pc) { .bx = { \
    .dreg = 0, \
    .addr = imm_pc, \
    .unused = 0, \
    .reg = 0, \
    .type = BX_JUMP_TYPE_ZERO, \
    .sub_opcode = SUB_OPCODE_BX, \
    .opcode = OPCODE_BRANCH } }

/**
 * 如果ALU溢出，则分支到绝对PC，地址在寄存器中
 *
 * reg_pc是包含要跳转到的地址的寄存器。地址用32位字表示。
 */
#define I_BXFR(reg_pc) { .bx = { \
    .dreg = reg_pc, \
    .addr = 0, \
    .unused = 0, \
    .reg = 1, \
    .type = BX_JUMP_TYPE_OVF, \
    .sub_opcode = SUB_OPCODE_BX, \
    .opcode = OPCODE_BRANCH } }

/**
 * 如果ALU溢出，立即地址转移到绝对PC
 *
 * 地址imm_pc用32位字表示。
 */
#define I_BXFI(imm_pc) { .bx = { \
    .dreg = 0, \
    .addr = imm_pc, \
    .unused = 0, \
    .reg = 0, \
    .type = BX_JUMP_TYPE_OVF, \
    .sub_opcode = SUB_OPCODE_BX, \
    .opcode = OPCODE_BRANCH } }


/**
 * 附加：dest=src1+src2
 */
#define I_ADDR(reg_dest, reg_src1, reg_src2) { .alu_reg = { \
    .dreg = reg_dest, \
    .sreg = reg_src1, \
    .treg = reg_src2, \
    .unused = 0, \
    .sel = ALU_SEL_ADD, \
    .sub_opcode = SUB_OPCODE_ALU_REG, \
    .opcode = OPCODE_ALU } }

/**
 * 减法：dest=src1-src2
 */
#define I_SUBR(reg_dest, reg_src1, reg_src2) { .alu_reg = { \
    .dreg = reg_dest, \
    .sreg = reg_src1, \
    .treg = reg_src2, \
    .unused = 0, \
    .sel = ALU_SEL_SUB, \
    .sub_opcode = SUB_OPCODE_ALU_REG, \
    .opcode = OPCODE_ALU } }

/**
 * 逻辑与：dest=src1和src2
 */
#define I_ANDR(reg_dest, reg_src1, reg_src2) { .alu_reg = { \
    .dreg = reg_dest, \
    .sreg = reg_src1, \
    .treg = reg_src2, \
    .unused = 0, \
    .sel = ALU_SEL_AND, \
    .sub_opcode = SUB_OPCODE_ALU_REG, \
    .opcode = OPCODE_ALU } }

/**
 * 逻辑或：dest=src1|src2
 */
#define I_ORR(reg_dest, reg_src1, reg_src2)  { .alu_reg = { \
    .dreg = reg_dest, \
    .sreg = reg_src1, \
    .treg = reg_src2, \
    .unused = 0, \
    .sel = ALU_SEL_OR, \
    .sub_opcode = SUB_OPCODE_ALU_REG, \
    .opcode = OPCODE_ALU } }

/**
 * 复制：dest=src
 */
#define I_MOVR(reg_dest, reg_src) { .alu_reg = { \
    .dreg = reg_dest, \
    .sreg = reg_src, \
    .treg = 0, \
    .unused = 0, \
    .sel = ALU_SEL_MOV, \
    .sub_opcode = SUB_OPCODE_ALU_REG, \
    .opcode = OPCODE_ALU } }

/**
 * 逻辑左移：dest=src<<shift
 */
#define I_LSHR(reg_dest, reg_src, reg_shift)  { .alu_reg = { \
    .dreg = reg_dest, \
    .sreg = reg_src, \
    .treg = reg_shift, \
    .unused = 0, \
    .sel = ALU_SEL_LSH, \
    .sub_opcode = SUB_OPCODE_ALU_REG, \
    .opcode = OPCODE_ALU } }


/**
 * 逻辑右移：dest=src>>shift
 */
#define I_RSHR(reg_dest, reg_src, reg_shift)  { .alu_reg = { \
    .dreg = reg_dest, \
    .sreg = reg_src, \
    .treg = reg_shift, \
    .unused = 0, \
    .sel = ALU_SEL_RSH, \
    .sub_opcode = SUB_OPCODE_ALU_REG, \
    .opcode = OPCODE_ALU } }

/**
 * 将寄存器和立即数相加：dest=src1+imm
 */
#define I_ADDI(reg_dest, reg_src, imm_) { .alu_imm = { \
    .dreg = reg_dest, \
    .sreg = reg_src, \
    .imm = imm_, \
    .unused = 0, \
    .sel = ALU_SEL_ADD, \
    .sub_opcode = SUB_OPCODE_ALU_IMM, \
    .opcode = OPCODE_ALU } }


/**
 *  减去寄存器和立即数：dest=src-imm
 */
#define I_SUBI(reg_dest, reg_src, imm_) { .alu_imm = { \
    .dreg = reg_dest, \
    .sreg = reg_src, \
    .imm = imm_, \
    .unused = 0, \
    .sel = ALU_SEL_SUB, \
    .sub_opcode = SUB_OPCODE_ALU_IMM, \
    .opcode = OPCODE_ALU } }

/**
 * 逻辑AND寄存器和立即数：dest=src&imm
 */
#define I_ANDI(reg_dest, reg_src, imm_) { .alu_imm = { \
    .dreg = reg_dest, \
    .sreg = reg_src, \
    .imm = imm_, \
    .unused = 0, \
    .sel = ALU_SEL_AND, \
    .sub_opcode = SUB_OPCODE_ALU_IMM, \
    .opcode = OPCODE_ALU } }

/**
 * 逻辑或寄存器和立即数：dest=src|imm
 */
#define I_ORI(reg_dest, reg_src, imm_) { .alu_imm = { \
    .dreg = reg_dest, \
    .sreg = reg_src, \
    .imm = imm_, \
    .unused = 0, \
    .sel = ALU_SEL_OR, \
    .sub_opcode = SUB_OPCODE_ALU_IMM, \
    .opcode = OPCODE_ALU } }

/**
 * 将立即数复制到寄存器：dest=imm
 */
#define I_MOVI(reg_dest, imm_) { .alu_imm = { \
    .dreg = reg_dest, \
    .sreg = 0, \
    .imm = imm_, \
    .unused = 0, \
    .sel = ALU_SEL_MOV, \
    .sub_opcode = SUB_OPCODE_ALU_IMM, \
    .opcode = OPCODE_ALU } }

/**
 * 按立即数逻辑左移寄存器值：dest=src<<imm
 */
#define I_LSHI(reg_dest, reg_src, imm_) { .alu_imm = { \
    .dreg = reg_dest, \
    .sreg = reg_src, \
    .imm = imm_, \
    .unused = 0, \
    .sel = ALU_SEL_LSH, \
    .sub_opcode = SUB_OPCODE_ALU_IMM, \
    .opcode = OPCODE_ALU } }


/**
 * 按立即数逻辑右移寄存器值：dest=val>>imm
 */
#define I_RSHI(reg_dest, reg_src, imm_) { .alu_imm = { \
    .dreg = reg_dest, \
    .sreg = reg_src, \
    .imm = imm_, \
    .unused = 0, \
    .sel = ALU_SEL_RSH, \
    .sub_opcode = SUB_OPCODE_ALU_IMM, \
    .opcode = OPCODE_ALU } }

/**
 * 使用数字label_num定义标签。
 *
 * 这是一个不会生成实际指令的宏。此宏生成的令牌由ulp_process_macros_and_load函数删除。使用此宏定义的标签可以在下面定义的分支宏中使用。
 */
#define M_LABEL(label_num) { .macro = { \
    .label = label_num, \
    .unused = 0, \
    .sub_opcode = SUB_OPCODE_MACRO_LABEL, \
    .opcode = OPCODE_MACRO } }

/**
 * M_B和M_BX宏使用的令牌宏。不得直接使用。
 */
#define M_BRANCH(label_num) { .macro = { \
    .label = label_num, \
    .unused = 0, \
    .sub_opcode = SUB_OPCODE_MACRO_BRANCH, \
    .opcode = OPCODE_MACRO } }

/**
 * 宏：如果R0小于立即数，则分支到标签label_num。
 *
 * 此宏生成两个由逗号分隔的ulp_insn_t值，在定义ulp_inst_t数组的内容时应使用此宏。第一个值不是真正的指令；它是一个由ulp_process_macros_and_load函数删除的令牌。
 */
#define M_BL(label_num, imm_value) \
    M_BRANCH(label_num), \
    I_BL(0, imm_value)

/**
 * 宏：如果R0大于或等于立即数，则分支到标签label_num
 *
 * 此宏生成两个由逗号分隔的ulp_insn_t值，在定义ulp_inst_t数组的内容时应使用此宏。第一个值不是真正的指令；它是一个由ulp_process_macros_and_load函数删除的令牌。
 */
#define M_BGE(label_num, imm_value) \
    M_BRANCH(label_num), \
    I_BGE(0, imm_value)

/**
 * 宏：无条件分支到标签
 *
 * 此宏生成两个由逗号分隔的ulp_insn_t值，在定义ulp_inst_t数组的内容时应使用此宏。第一个值不是真正的指令；它是一个由ulp_process_macros_and_load函数删除的令牌。
 */
#define M_BX(label_num) \
    M_BRANCH(label_num), \
    I_BXI(0)

/**
 * 宏：如果ALU结果为零，则分支到标签
 *
 * 此宏生成两个由逗号分隔的ulp_insn_t值，在定义ulp_inst_t数组的内容时应使用此宏。第一个值不是真正的指令；它是一个由ulp_process_macros_and_load函数删除的令牌。
 */
#define M_BXZ(label_num) \
    M_BRANCH(label_num), \
    I_BXZI(0)

/**
 * 宏：如果ALU溢出，则分支到标签
 *
 * 此宏生成两个由逗号分隔的ulp_insn_t值，在定义ulp_inst_t数组的内容时应使用此宏。第一个值不是真正的指令；它是一个由ulp_process_macros_and_load函数删除的令牌。
 */
#define M_BXF(label_num) \
    M_BRANCH(label_num), \
    I_BXFI(0)



#define RTC_SLOW_MEM ((uint32_t*) 0x50000000)       /*!< RTC慢内存，8k大小*/

#ifdef __cplusplus
}
#endif

