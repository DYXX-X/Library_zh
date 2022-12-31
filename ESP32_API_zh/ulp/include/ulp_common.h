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

/* 此文件包含esp32/ulp之间通用的定义。h和esp32s2/ulp.h
*/

#ifdef __cplusplus
extern "C" {
#endif

/**@{*/
#define ESP_ERR_ULP_BASE                0x1200                  /*!< ULP相关错误代码的偏移量*/
#define ESP_ERR_ULP_SIZE_TOO_BIG        (ESP_ERR_ULP_BASE + 1)  /*!< 程序不适合为ULP保留的RTC内存*/
#define ESP_ERR_ULP_INVALID_LOAD_ADDR   (ESP_ERR_ULP_BASE + 2)  /*!< 加载地址在为ULP保留的RTC内存之外*/
#define ESP_ERR_ULP_DUPLICATE_LABEL     (ESP_ERR_ULP_BASE + 3)  /*!< 定义了多个具有相同编号的标签*/
#define ESP_ERR_ULP_UNDEFINED_LABEL     (ESP_ERR_ULP_BASE + 4)  /*!< 分支指令引用未定义的标签*/
#define ESP_ERR_ULP_BRANCH_OUT_OF_RANGE (ESP_ERR_ULP_BASE + 5)  /*!< 分支目标超出B指令的范围（尝试用BX替换）*/
/**@}*/

union ulp_insn;  // 在芯片特定的ulp中声明。h集管

typedef union ulp_insn ulp_insn_t;

/**
 * @brief 解析程序中的所有宏引用并将其加载到RTC内存中
 * @param load_addr  应加载程序的地址，用32位字表示
 * @param program  ulp_insn_t数组与程序
 * @param psize  程序的大小，以32位字表示
 * @return
 *      -成功时ESP_OK
 *      -如果无法分配辅助临时结构，则为ESP_ERR_NO_MEM
 *      -如果程序无效或无法加载，请选择ESP_ERR_ULP_xxx之一
 */
esp_err_t ulp_process_macros_and_load(uint32_t load_addr, const ulp_insn_t* program, size_t* psize);

/**
 * @brief 将ULP程序二进制文件加载到RTC内存中
 *
 * ULP程序二进制文件应具有以下格式（所有值均为小端）：
 *
 * 1.MAGIC，（值0x00706c75，4字节）2.TEXT_OFFSET，从二进制开始的文本段的偏移量（2字节）3.TEXT_SIZE，文本段的大小（2个字节）4.DATA_SIZE（数据段的大小）（2个）5.BSS_SIZE、.BSS段的大小
 *
 * components/ulp/ld/esp32.ulp中的链接器脚本。ld生成与此格式相对应的ELF文件。此链接器脚本生成load_addr==0的二进制文件。
 *
 * @param load_addr 应加载程序的地址，用32位字表示
 * @param program_binary 程序二进制指针
 * @param program_size 程序二进制文件的大小
 * @return
 *      -成功时ESP_OK
 *      -如果load_addr超出范围，则ESP_ERR_INVALID_ARG
 *      -如果程序大小不匹配（TEXT_OFFSET+TEXT_SIZE+DATA_SIZE），则为ESP_ERR_INVALID_SIZE
 *      -如果幻数不正确，则返回ESP_ERR_NOT_SUPPORTED
 */
esp_err_t ulp_load_binary(uint32_t load_addr, const uint8_t* program_binary, size_t program_size);

/**
 * @brief 运行加载到RTC内存中的程序
 * @param entry_point 入口点，用32位字表示
 * @return  成功时ESP_OK
 */
esp_err_t ulp_run(uint32_t entry_point);

/**
 * @brief 设置ULP唤醒周期值之一
 *
 * 当唤醒计时器计数到给定值（称为周期）时，ULP协处理器开始运行程序。有5个周期值可编程到SENS_ULP_CP_LEEP_CYCx_REG寄存器中，对于ESP32，x=0..4；对于ESP32-S2，有一个周期值可以编程到RTC_CNTL_ULP_CP_TIMER_1_REG寄存器中。默认情况下，对于ESP 32，唤醒计时器将使用设置到SENS_UP_CP_SLEEP_CYC_REG中的周期，即周期编号0。ULP程序代码可以使用SLEEP指令来选择SENS_ULP_CP_SLEP_CYCx_REG中的哪一个应用于后续唤醒。
 *
 * 但是，请注意，在系统处于深度睡眠模式时发出的SLEEP指令（来自ULP程序）无效，并且使用睡眠周期计数0。
 *
 * 对于ESP32-s2，SLEEP指令不存在。相反，将使用WAKE指令。
 *
 * @param period_index 唤醒周期设置数（0-4）
 * @param period_us 唤醒期，我们
 * @note  ULP FSM需要两个时钟周期才能唤醒，然后才能运行程序。然后，在唤醒等待之后保留额外的16个周期，直到8M时钟稳定。在程序执行停止后，FSM还需要两个时钟周期才能进入休眠状态。可以为ULP设置的最小唤醒周期等于在上述内部任务上花费的周期总数。对于以150kHz运行的ULP的默认配置，它大约为133us。
 * @return
 *      -成功时ESP_OK
 *      -如果周期索引超出范围，则ESP_ERR_INVALID_ARG
 */
esp_err_t ulp_set_wakeup_period(size_t period_index, uint32_t period_us);

#ifdef __cplusplus
}
#endif

