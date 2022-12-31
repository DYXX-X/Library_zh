// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
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
#include <stdbool.h>

#include "gdbstub_target_config.h"
#include "esp_gdbstub_arch.h"
#include "sdkconfig.h"

#ifdef CONFIG_ESP_GDBSTUB_SUPPORT_TASKS
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/task_snapshot.h"
#endif // CONFIG_ESP_GDBSTUB_SUPPORT_TASKS

/* 解析传入gdb数据包的例程使用的内部错误代码*/
#define GDBSTUB_ST_ENDPACKET -1
#define GDBSTUB_ST_ERR -2
#define GDBSTUB_ST_OK -3
#define GDBSTUB_ST_CONT -4

/* 特殊任务索引值*/
#define GDBSTUB_CUR_TASK_INDEX_UNKNOWN -1

/* Cab在gdbstub_target_config中设置为较低的值。小时*/
#ifndef GDBSTUB_CMD_BUFLEN
#define GDBSTUB_CMD_BUFLEN 512
#endif

#if CONFIG_ESP_GDBSTUB_SUPPORT_TASKS
typedef enum {
    GDBSTUB_NOT_STARTED,
    GDBSTUB_STARTED,
    GDBSTUB_TASK_SUPPORT_DISABLED
} esp_gdbstub_state_t;

#define GDBSTUB_TASKS_NUM  CONFIG_ESP_GDBSTUB_MAX_TASKS

#endif // CONFIG_ESP_GDBSTUB_SUPPORT_TASKS

/* gdbsub临时运行时数据，存储在.bss中以减少堆栈使用*/
typedef struct {
    esp_gdbstub_gdb_regfile_t regfile;
    int signal;
#if CONFIG_ESP_GDBSTUB_SUPPORT_TASKS
    esp_gdbstub_state_t state;
    int task_count;
    int paniced_task_index;
    int current_task_index;
    int thread_info_index;                             //!< 传递给qsThreadInfo的最后一个任务的索引
    esp_gdbstub_frame_t paniced_frame;
    TaskSnapshot_t tasks[GDBSTUB_TASKS_NUM];           // TODO:添加API以逐个获取快照
#endif // CONFIG_ESP_GDBSTUB_SUPPORT_TASKS
} esp_gdbstub_scratch_t;


/****体系结构特定部分提供的功能****/

/**
 * @param frame 异常帧指针
 * @return 给定异常原因的适当“信号”编号
 */
int esp_gdbstub_get_signal(const esp_gdbstub_frame_t *frame);

/**
 * 将异常帧中的寄存器写入GDB寄存器文件
 * @param frame  要分析的异常帧
 * @param dst  指向GDB寄存器文件的指针
 */
void esp_gdbstub_frame_to_regfile(const esp_gdbstub_frame_t *frame, esp_gdbstub_gdb_regfile_t *dst);

#if CONFIG_ESP_GDBSTUB_SUPPORT_TASKS
/**
 * 将给定任务的保存帧中的寄存器写入GDB寄存器文件
 * @param tcb  指向任务TCB的指针
 * @param dst  指向GDB寄存器文件的指针
 */
void esp_gdbstub_tcb_to_regfile(TaskHandle_t tcb, esp_gdbstub_gdb_regfile_t *dst);
#endif // CONFIG_ESP_GDBSTUB_SUPPORT_TASKS



/****目标特定部件提供的功能****/

/**
 * 在gdbstub可以开始通信之前，执行特定于目标的初始化。例如，这可能涉及配置UART。
 */
void esp_gdbstub_target_init(void);

/**
 * 从GDB客户端接收一个字节。块，直到一个字节可用。
 * @return 接收字节
 */
int esp_gdbstub_getchar(void);

/**
 * 向GDB客户端发送一个字节
 * @param c  要发送的字节
 */
void esp_gdbstub_putchar(int c);

/**
 * 从目标内存读取一个字节
 * @param ptr  住址
 * @return  字节值，或GDBSTUB_ST_ERR（如果地址不可读）
 */
int esp_gdbstub_readmem(intptr_t addr);

/**
 * 确保使用putchar（）发送的所有字节都在主机上结束。（通常用于UART，但可用于其他信道）
 */
void esp_gdbstub_flush(void);

/**
 * 将字节写入目标内存
 * @param addr  住址
 * @param data  数据字节
 * @return 成功时为0，错误时为-1
 */
int esp_gdbstub_writemem(unsigned int addr, unsigned char data);

/**
 * 从fifo读取数据并检测开始符号
 * @return  如果检测到中断符号，则为1；如果没有，则为0
 */
int esp_gdbstub_getfifo(void);

/****GDB数据包相关功能****/

/**开始数据包*/
void esp_gdbstub_send_start(void);

/**将字符作为数据包的一部分发送*/
void esp_gdbstub_send_char(char c);

/**将字符串作为数据包的一部分发送*/
void esp_gdbstub_send_str(const char *s);

/**将十六进制值作为数据包的一部分发送*/
void esp_gdbstub_send_hex(int val, int bits);

/**完成发送数据包*/
void esp_gdbstub_send_end(void);

/**发送包含字符串作为内容的数据包*/
void esp_gdbstub_send_str_packet(const char *str);

/**从gdb数据包中获取十六进制值*/
uint32_t esp_gdbstub_gethex(const unsigned char **ptr, int bits);

/**读取、取消扫描并验证传入的GDB命令*/
int esp_gdbstub_read_command(unsigned char **out_cmd, size_t *out_size);

/**处理从gdb接收的命令*/
int esp_gdbstub_handle_command(unsigned char *cmd, int len);

