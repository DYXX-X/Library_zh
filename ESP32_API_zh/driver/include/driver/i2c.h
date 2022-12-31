/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _DRIVER_I2C_H_
#define _DRIVER_I2C_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <esp_types.h>
#include "esp_err.h"
#include "esp_intr_alloc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/ringbuf.h"
#include "driver/gpio.h"
#include "soc/soc_caps.h"
#include "hal/i2c_types.h"

#define I2C_APB_CLK_FREQ  APB_CLK_FREQ /*!< I2C源时钟为APB时钟，80MHz*/

#define I2C_NUM_MAX            (SOC_I2C_NUM) /*!< I2C端口最大值*/
#define I2C_NUM_0              (0) /*!< I2C端口0*/
#if SOC_I2C_NUM >= 2
#define I2C_NUM_1              (1) /*!< I2C端口1*/
#endif

// I2C clk标志供用户使用，将来可以扩展。
#define I2C_SCLK_SRC_FLAG_FOR_NOMAL       (0)         /*!< 可以选择可用于指定频率的任何一个时钟源*/
#define I2C_SCLK_SRC_FLAG_AWARE_DFS       (1 << 0)    /*!< 对于REF时钟，它不会随APB而改变。*/
#define I2C_SCLK_SRC_FLAG_LIGHT_SLEEP     (1 << 1)    /*!< 对于浅睡眠模式。*/

/**
 * @brief 用于描述I2C命令链接的内部私有结构的最小大小（字节）。
 */
#define I2C_INTERNAL_STRUCT_SIZE (24)

/**
 * @brief 以下宏用于确定要传递给“i2c_cmd_link_create_static（）”函数的缓冲区的建议大小。它需要一个参数“TRANSACTIONS”，描述要在I2C端口上执行的事务数。例如，如果要对I2C设备寄存器执行读取，“TRANSACTION”必须至少为2，因为所需的命令如下：
 *  -写入设备寄存器
 *  -读取寄存器内容
 *
 * “（重复）启动”、“停止”、“nack”、“ack”等信号不应计算在内。
 */
#define I2C_LINK_RECOMMENDED_SIZE(TRANSACTIONS)     (2 * I2C_INTERNAL_STRUCT_SIZE + I2C_INTERNAL_STRUCT_SIZE * \
                                                        (5 * TRANSACTIONS)) /* 假设用户的每个事务都被“开始”、设备地址和“nack/ack”信号包围。在终点为“停止”信号分配一个额外的空间。为标头再分配2个内部结构大小。
                                                                             */

/**
 * @brief I2C初始化参数
 */
typedef struct{
    i2c_mode_t mode;     /*!< I2C模式*/
    int sda_io_num;      /*!< I2C sda信号的GPIO编号*/
    int scl_io_num;      /*!< I2C scl信号的GPIO编号*/
    bool sda_pullup_en;  /*!< I2C sda信号的内部GPIO拉模式*/
    bool scl_pullup_en;  /*!< I2C scl信号的内部GPIO拉动模式*/

    union {
        struct {
            uint32_t clk_speed;      /*!< 主模式的I2C时钟频率（目前不高于1MHz）*/
        } master;                    /*!< I2C主配置*/
        struct {
            uint8_t addr_10bit_en;   /*!< I2C 10位地址模式启用从模式*/
            uint16_t slave_addr;     /*!< 从属模式的I2C地址*/
            uint32_t maximum_speed;  /*!< 来自SCL的I2C预期时钟速度。*/
        } slave;                     /*!< I2C从属配置*/
    };
    uint32_t clk_flags;              /*!< 用于clk源选择的``I2C_SCLK_SRC_FLAG_**FOR_DFS**``按位*/
} i2c_config_t;


typedef void *i2c_cmd_handle_t;    /*!< I2C命令句柄*/

/**
 * @brief 安装I2C驱动程序
 *
 * @param i2c_num I2C端口号
 * @param mode I2C模式（主或从）
 * @param slv_rx_buf_len 接收缓冲区大小。只有从属模式才会使用此值，在主模式中会忽略此值。
 * @param slv_tx_buf_len 发送缓冲区大小。只有从属模式才会使用此值，在主模式中会忽略此值。
 * @param intr_alloc_flags 用于分配中断的标志。一个或多个（ORred）ESP_INTR_FLAG_*值。请参见esp_intr_alloc。h了解更多信息@注意：在主模式下，如果缓存可能被禁用（如写闪存），并且从缓存对时间敏感，建议使用“ESP_INTR_FLAG_IRAM”。在这种情况下，请使用i2c读写功能中从内部RAM分配的内存，因为在禁用缓存时，我们无法访问中断处理功能中的psram（如果启用了psram）。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_FAIL驱动程序安装错误
 */
esp_err_t i2c_driver_install(i2c_port_t i2c_num, i2c_mode_t mode, size_t slv_rx_buf_len, size_t slv_tx_buf_len, int intr_alloc_flags);

/**
 * @brief 删除I2C驱动程序
 *
 * @note 此功能不能保证线程安全。请确保在调用delete函数之前，没有线程会持续保持信号量。
 *
 * @param i2c_num 要删除的I2C端口
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2c_driver_delete(i2c_port_t i2c_num);

/**
 * @brief 使用给定配置配置I2C总线。
 *
 * @param i2c_num 要配置的I2C端口
 * @param i2c_conf 指向I2C配置的指针
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2c_param_config(i2c_port_t i2c_num, const i2c_config_t *i2c_conf);

/**
 * @brief 重置I2C tx硬件fifo
 *
 * @param i2c_num I2C端口号
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2c_reset_tx_fifo(i2c_port_t i2c_num);

/**
 * @brief 重置I2C rx fifo
 *
 * @param i2c_num I2C端口号
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2c_reset_rx_fifo(i2c_port_t i2c_num);

/**
 * @brief 注册I2C ISR处理程序。
 *
 * @param i2c_num 要连接处理程序的I2C端口号
 * @param fn ISR处理程序函数
 * @param arg ISR处理程序的参数
 * @param intr_alloc_flags 用于分配中断的标志。一个或多个（ORred）ESP_INTR_FLAG_值。请参见esp_intr_alloc。h了解更多信息。
 * @param handle 处理esp_intr_alloc的返回。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2c_isr_register(i2c_port_t i2c_num, void (*fn)(void *), void *arg, int intr_alloc_flags, intr_handle_t *handle);

/**
 * @brief 删除并释放I2C ISR句柄。
 *
 * @param handle 要删除的isr的句柄。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2c_isr_free(intr_handle_t handle);

/**
 * @brief 为I2C SCK和SDA信号配置GPIO引脚。
 *
 * @param i2c_num I2C端口号
 * @param sda_io_num I2C SDA信号的GPIO编号
 * @param scl_io_num I2C SCL信号的GPIO编号
 * @param sda_pullup_en 启用SDA引脚的内部上拉
 * @param scl_pullup_en 启用SCL引脚的内部上拉
 * @param mode I2C模式
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2c_set_pin(i2c_port_t i2c_num, int sda_io_num, int scl_io_num,
                      bool sda_pullup_en, bool scl_pullup_en, i2c_mode_t mode);

/**
 * @brief 对连接到特定I2C端口的设备执行写入。此函数是“I2C_master_start（）”、“I2C_master _write（）”和“I2C_master_read（）”等的包装器。只能在I2C主模式下调用。
 *
 * @param i2c_num 要在其上执行传输的I2C端口号
 * @param device_address I2C设备的7位地址
 * @param write_buffer 要在总线上发送的字节
 * @param write_size 写入缓冲区的大小（字节）
 * @param ticks_to_wait 发出超时前等待的最大滴答数。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_FAIL发送命令错误，从属设备未确认传输。
 *     -ESP_ERR_INVALID_STATE I2C驱动程序未安装或未处于主模式。
 *     -ESP_ERR_TIMEOUT操作超时，因为总线繁忙。
 */
esp_err_t i2c_master_write_to_device(i2c_port_t i2c_num, uint8_t device_address,
                                     const uint8_t* write_buffer, size_t write_size,
                                     TickType_t ticks_to_wait);

/**
 * @brief 对连接到特定I2C端口的设备执行读取。此函数是“I2C_master_start（）”、“I2C_master _write（）”和“I2C_master_read（）”等的包装器。只能在I2C主模式下调用。
 *
 * @param i2c_num 要在其上执行传输的I2C端口号
 * @param device_address I2C设备的7位地址
 * @param read_buffer 用于存储总线上接收的字节的缓冲区
 * @param read_size 读取缓冲区的大小（字节）
 * @param ticks_to_wait 发出超时前等待的最大滴答数。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_FAIL发送命令错误，从属设备未确认传输。
 *     -ESP_ERR_INVALID_STATE I2C驱动程序未安装或未处于主模式。
 *     -ESP_ERR_TIMEOUT操作超时，因为总线繁忙。
 */
esp_err_t i2c_master_read_from_device(i2c_port_t i2c_num, uint8_t device_address,
                                      uint8_t* read_buffer, size_t read_size,
                                      TickType_t ticks_to_wait);

/**
 * @brief 对I2C总线上的设备执行写操作，然后执行读操作。在“写”和“读”之间使用重复的启动信号，因此，直到两个事务完成，总线才被释放。此函数是“i2c_master_start（）”、“i2c_master_write（）”和“i2c_master _read（）”等的包装器。它只能在i2c主模式下调用。
 *
 * @param i2c_num 要在其上执行传输的I2C端口号
 * @param device_address I2C设备的7位地址
 * @param write_buffer 要在总线上发送的字节
 * @param write_size 写入缓冲区的大小（字节）
 * @param read_buffer 用于存储总线上接收的字节的缓冲区
 * @param read_size 读取缓冲区的大小（字节）
 * @param ticks_to_wait 发出超时前等待的最大滴答数。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_FAIL发送命令错误，从属设备未确认传输。
 *     -ESP_ERR_INVALID_STATE I2C驱动程序未安装或未处于主模式。
 *     -ESP_ERR_TIMEOUT操作超时，因为总线繁忙。
 */
esp_err_t i2c_master_write_read_device(i2c_port_t i2c_num, uint8_t device_address,
                                       const uint8_t* write_buffer, size_t write_size,
                                       uint8_t* read_buffer, size_t read_size,
                                       TickType_t ticks_to_wait);


/**
 * @brief 使用给定的缓冲区创建并初始化I2C命令列表。数据或信号的所有分配（START、STOP、ACK…）将在该缓冲区内执行。此缓冲区在整个事务期间必须有效。完成I2C事务后，需要调用“I2C_cmd_link_delete_static（）”。
 *
 * @note 强烈建议不要在堆栈上分配此缓冲区。下面使用的数据的大小将来可能会增加，这可能导致堆栈溢出，因为宏“I2C_LINK_RECOMMENDED_size”也会返回更大的值。更好的选择是使用静态或动态分配的缓冲区（使用“malloc”）。
 *
 * @param buffer 用于命令分配的缓冲区
 * @param size 缓冲区的字节大小
 *
 * @return I2C命令链接的句柄或NULL（如果提供的缓冲区太小），请使用`I2C_link_RECOMMENDED_SIZE`宏获取缓冲区的建议大小。
 */
i2c_cmd_handle_t i2c_cmd_link_create_static(uint8_t* buffer, uint32_t size);

/**
 * @brief 使用给定的缓冲区创建并初始化I2C命令列表。完成I2C事务后，需要调用“I2C_cmd_link_delete（）”来释放并返回资源。将动态分配所需的字节。
 *
 * @return I2C命令链接的句柄
 */
i2c_cmd_handle_t i2c_cmd_link_create(void);

/**
 * @brief 释放使用“I2C_cmd_link_create_static”静态分配的I2C命令列表。
 *
 * @param cmd_handle I2C命令列表静态分配。应使用“i2c_cmd_link_create_static（）”函数创建此句柄
 */
void i2c_cmd_link_delete_static(i2c_cmd_handle_t cmd_handle);

/**
 * @brief 释放I2C命令列表
 *
 * @param cmd_handle I2C命令列表。应使用“i2c_cmd_link_create（）”函数创建此句柄
 */
void i2c_cmd_link_delete(i2c_cmd_handle_t cmd_handle);

/**
 * @brief 将“START信号”排入给定命令列表。该功能只能在I2C主模式下调用。调用“i2c_master_cmd_begin（）”发送所有排队的命令。
 *
 * @param cmd_handle I2C命令列表
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_ERR_NO_MEM用于创建“cmd_handler”的静态缓冲区太小
 *     -ESP_FAIL堆上没有剩余内存
 */
esp_err_t i2c_master_start(i2c_cmd_handle_t cmd_handle);

/**
 * @brief 将“write-byte”命令排入命令列表。单个字节将在I2C端口上发送。此功能只能在I2C主模式下调用。调用`i2c_master_cmd_begin（）`发送所有排队的命令
 *
 * @param cmd_handle I2C命令列表
 * @param data 要在端口上发送的字节
 * @param ack_en 启用ACK信号
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_ERR_NO_MEM用于创建“cmd_handler”的静态缓冲区太小
 *     -ESP_FAIL堆上没有剩余内存
 */
esp_err_t i2c_master_write_byte(i2c_cmd_handle_t cmd_handle, uint8_t data, bool ack_en);

/**
 * @brief 将“写入（多个）字节”命令排入命令列表。该功能只能在I2C主模式下调用。调用`i2c_master_cmd_begin（）`发送所有排队的命令
 *
 * @param cmd_handle I2C命令列表
 * @param data 要发送的字节数。在事务完成之前，此缓冲区应保持**有效**。如果PSRAM已启用且“intr_flag”设置为“ESP_intr_flag_IRAM”，则应从内部RAM分配“数据”。
 * @param data_len 数据缓冲区的长度（字节）
 * @param ack_en 启用ACK信号
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_ERR_NO_MEM用于创建“cmd_handler”的静态缓冲区太小
 *     -ESP_FAIL堆上没有剩余内存
 */
esp_err_t i2c_master_write(i2c_cmd_handle_t cmd_handle, const uint8_t *data, size_t data_len, bool ack_en);

/**
 * @brief 将“read-byte”命令排入命令列表。将在I2C总线上读取单个字节。该功能只能在I2C主模式下调用。调用`i2c_master_cmd_begin（）`发送所有排队的命令
 *
 * @param cmd_handle I2C命令列表
 * @param data 存储接收字节的指针。在事务完成之前，此缓冲区应保持**有效**。
 * @param ack ACK信号
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_ERR_NO_MEM用于创建“cmd_handler”的静态缓冲区太小
 *     -ESP_FAIL堆上没有剩余内存
 */
esp_err_t i2c_master_read_byte(i2c_cmd_handle_t cmd_handle, uint8_t *data, i2c_ack_type_t ack);

/**
 * @brief 将“读取（多个）字节”命令排入命令列表。将在I2C总线上读取多个字节。该功能只能在I2C主模式下调用。调用`i2c_master_cmd_begin（）`发送所有排队的命令
 *
 * @param cmd_handle I2C命令列表
 * @param data 存储接收字节的指针。在事务完成之前，此缓冲区应保持**有效**。
 * @param data_len “数据”缓冲区的大小（字节）
 * @param ack ACK信号
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_ERR_NO_MEM用于创建“cmd_handler”的静态缓冲区太小
 *     -ESP_FAIL堆上没有剩余内存
 */
esp_err_t i2c_master_read(i2c_cmd_handle_t cmd_handle, uint8_t *data, size_t data_len, i2c_ack_type_t ack);

/**
 * @brief 将“STOP信号”排入给定命令列表。该功能只能在I2C主模式下调用。调用“i2c_master_cmd_begin（）”发送所有排队的命令。
 *
 * @param cmd_handle I2C命令列表
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_ERR_NO_MEM用于创建“cmd_handler”的静态缓冲区太小
 *     -ESP_FAIL堆上没有剩余内存
 */
esp_err_t i2c_master_stop(i2c_cmd_handle_t cmd_handle);

/**
 * @brief 以主模式在I2C总线上发送所有排队命令。在发出所有命令之前，任务将被阻止。I2C API不是线程安全的，如果您想在不同的任务中使用一个I2C端口，则需要考虑多线程问题。该功能只能在I2C主模式下调用。
 *
 * @param i2c_num I2C端口号
 * @param cmd_handle I2C命令列表
 * @param ticks_to_wait 发出超时前等待的最大滴答数。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_FAIL发送命令错误，从属设备未确认传输。
 *     -ESP_ERR_INVALID_STATE I2C驱动程序未安装或未处于主模式。
 *     -ESP_ERR_TIMEOUT操作超时，因为总线繁忙。
 */
esp_err_t i2c_master_cmd_begin(i2c_port_t i2c_num, i2c_cmd_handle_t cmd_handle, TickType_t ticks_to_wait);

/**
 * @brief 将字节写入I2C从属数据的内部环形缓冲区。当TX fifo为空时，ISR将用内部环形缓冲区的数据填充硬件fifo。
 *        @note 该功能只能在I2C从属模式下调用。
 *
 * @param i2c_num I2C端口号
 * @param data 要写入内部缓冲区的字节数
 * @param size “数据”缓冲区的大小（字节）
 * @param ticks_to_wait 等待的最大刻度。
 *
 * @return
 *     -ESP_FAIL（-1）参数错误
 *     -其他（>=0）推送到I2C从属缓冲区的数据字节数。
 */
int i2c_slave_write_buffer(i2c_port_t i2c_num, const uint8_t *data, int size, TickType_t ticks_to_wait);

/**
 * @brief 从I2C内部缓冲区读取字节。当I2C总线接收数据时，ISR会将数据从硬件RX FIFO复制到内部环形缓冲区。然后调用此函数会将字节从内部环形缓冲区复制到“数据”用户缓冲区。
 *        @note 该功能只能在I2C从属模式下调用。
 *
 * @param i2c_num I2C端口号
 * @param data 要填充环形缓冲区字节的缓冲区
 * @param max_size 要读取的最大字节数
 * @param ticks_to_wait 最大等待时间
 *
 * @return
 *     -ESP_FAIL（-1）参数错误
 *     -其他（>=0）从I2C从属缓冲区读取的数据字节数。
 */
int i2c_slave_read_buffer(i2c_port_t i2c_num, uint8_t *data, size_t max_size, TickType_t ticks_to_wait);

/**
 * @brief 设置I2C主时钟周期
 *
 * @param i2c_num I2C端口号
 * @param high_period SCL期间的时钟周期数为高电平，high_period为14位值
 * @param low_period SCL期间的时钟周期数为低电平，low_period为14位值
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2c_set_period(i2c_port_t i2c_num, int high_period, int low_period);

/**
 * @brief 获取I2C主时钟周期
 *
 * @param i2c_num I2C端口号
 * @param high_period SCL期间获取时钟周期数的指针为高电平，将获得14位值
 * @param low_period SCL期间获取时钟周期数的指针为低电平，将获得14位值
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2c_get_period(i2c_port_t i2c_num, int *high_period, int *low_period);

/**
 * @brief 启用I2C总线上的硬件滤波器有时I2C总线受到高频噪声（约20ns）的干扰，或者SCL时钟的上升沿非常慢，这些可能会导致主状态机中断。启用硬件滤波器可以滤除高频干扰，使主机更稳定。
 *        @note 启用筛选器将减慢SCL时钟。
 *
 * @param i2c_num 至过滤器的I2C端口号
 * @param cyc_num APB周期需要被过滤（0＜＝cyc_num＜＝7）。当脉冲周期小于cyc_num APB_cycle时，I2C控制器将忽略该脉冲。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2c_filter_enable(i2c_port_t i2c_num, uint8_t cyc_num);

/**
 * @brief 禁用I2C总线上的过滤器
 *
 * @param i2c_num I2C端口号
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2c_filter_disable(i2c_port_t i2c_num);

/**
 * @brief 设置I2C主启动信号定时
 *
 * @param i2c_num I2C端口号
 * @param setup_time 开始标记的SDA下降沿和SCL上升沿之间的时钟数，为10位值。
 * @param hold_time 开始标记的SDA下降沿和SCL下降沿之间的时钟num，为10位值。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2c_set_start_timing(i2c_port_t i2c_num, int setup_time, int hold_time);

/**
 * @brief 获取I2C主启动信号定时
 *
 * @param i2c_num I2C端口号
 * @param setup_time 获取设置时间的指针
 * @param hold_time 获取保持时间的指针
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2c_get_start_timing(i2c_port_t i2c_num, int *setup_time, int *hold_time);

/**
 * @brief 设置I2C主停止信号定时
 *
 * @param i2c_num I2C端口号
 * @param setup_time SCL的上升沿和SDA的上升沿之间的时钟num，它是一个10位的值。
 * @param hold_time STOP位上升沿之后的时钟编号，它是一个14位的值。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2c_set_stop_timing(i2c_port_t i2c_num, int setup_time, int hold_time);

/**
 * @brief 获取I2C主停止信号定时
 *
 * @param i2c_num I2C端口号
 * @param setup_time 获取设置时间的指针。
 * @param hold_time 获取保持时间的指针。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2c_get_stop_timing(i2c_port_t i2c_num, int *setup_time, int *hold_time);

/**
 * @brief 设置I2C数据信号定时
 *
 * @param i2c_num I2C端口号
 * @param sample_time 时钟编号I2C用于在SCL上升沿之后对SDA上的数据进行采样，它是一个10位的值
 * @param hold_time 用于在SCL下降沿之后保存数据的时钟编号I2C，它是一个10位的值
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2c_set_data_timing(i2c_port_t i2c_num, int sample_time, int hold_time);

/**
 * @brief 获取I2C数据信号定时
 *
 * @param i2c_num I2C端口号
 * @param sample_time 获取采样时间的指针
 * @param hold_time 获取保持时间的指针
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2c_get_data_timing(i2c_port_t i2c_num, int *sample_time, int *hold_time);

/**
 * @brief 设置I2C超时值
 * @param i2c_num I2C端口号
 * @param timeout I2C总线的超时值（单位：APB 80Mhz时钟周期）
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2c_set_timeout(i2c_port_t i2c_num, int timeout);

/**
 * @brief 获取I2C超时值
 * @param i2c_num I2C端口号
 * @param timeout 获取超时值的指针
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2c_get_timeout(i2c_port_t i2c_num, int *timeout);

/**
 * @brief 设置I2C数据传输模式
 *
 * @param i2c_num I2C端口号
 * @param tx_trans_mode I2C发送数据模式
 * @param rx_trans_mode I2C接收数据模式
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2c_set_data_mode(i2c_port_t i2c_num, i2c_trans_mode_t tx_trans_mode, i2c_trans_mode_t rx_trans_mode);

/**
 * @brief 获取I2C数据传输模式
 *
 * @param i2c_num I2C端口号
 * @param tx_trans_mode 获取I2C发送数据模式的指针
 * @param rx_trans_mode 获取I2C接收数据模式的指针
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2c_get_data_mode(i2c_port_t i2c_num, i2c_trans_mode_t *tx_trans_mode, i2c_trans_mode_t *rx_trans_mode);

#ifdef __cplusplus
}
#endif

#endif /*_DRIVER_I2C_H_*/

