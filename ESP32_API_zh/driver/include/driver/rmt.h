/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include "esp_err.h"
#include "soc/soc_caps.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/ringbuf.h"
#include "soc/rmt_struct.h"
#include "hal/rmt_types.h"

#define RMT_CHANNEL_FLAGS_AWARE_DFS (1 << 0) /*!< 信道可以在APB时钟缩放期间工作*/
#define RMT_CHANNEL_FLAGS_INVERT_SIG (1 << 1) /*!< 反相RMT信号*/

/**@秒*/
#define RMT_CHANNEL_FLAGS_ALWAYS_ON RMT_CHANNEL_FLAGS_AWARE_DFS  /*!< 不推荐的名称，此处为兼容性定义*/
/**@结束秒*/

/**
 * @brief 定义每个RMT通道的内存空间（大写=4字节）
 *
 */
#define RMT_MEM_ITEM_NUM SOC_RMT_MEM_WORDS_PER_CHANNEL

/**
* @brief RMT TX配置参数的数据结构
*/
typedef struct {
    uint32_t carrier_freq_hz;          /*!< RMT载波频率*/
    rmt_carrier_level_t carrier_level; /*!< 应用载波时RMT输出的电平*/
    rmt_idle_level_t idle_level;       /*!< RMT闲置水平*/
    uint8_t carrier_duty_percent;      /*!< RMT承运人责任（%）*/
#if SOC_RMT_SUPPORT_TX_LOOP_COUNT
    uint32_t loop_count;               /*!< 最大循环计数*/
#endif
    bool carrier_en;                   /*!< RMT载波启用*/
    bool loop_en;                      /*!< 启用在循环中发送RMT项目*/
    bool idle_output_en;               /*!< RMT空闲电平输出启用*/
} rmt_tx_config_t;

/**
* @brief RMT RX配置参数的数据结构
*/
typedef struct {
    uint16_t idle_threshold;     /*!< RMT RX空闲阈值*/
    uint8_t filter_ticks_thresh; /*!< RMT过滤器勾号*/
    bool filter_en;              /*!< RMT接收机滤波器启用*/
#if SOC_RMT_SUPPORT_RX_DEMODULATION
    bool rm_carrier;                   /*!< RMT接收器移除载波启用*/
    uint32_t carrier_freq_hz;          /*!< RMT载波频率*/
    uint8_t carrier_duty_percent;      /*!< RMT承运人责任（%）*/
    rmt_carrier_level_t carrier_level; /*!< 拆下托架的级别*/
#endif
} rmt_rx_config_t;

/**
* @brief RMT配置参数的数据结构
*/
typedef struct {
    rmt_mode_t rmt_mode;   /*!< RMT模式：发射器或接收器*/
    rmt_channel_t channel; /*!< RMT通道*/
    gpio_num_t gpio_num;   /*!< RMT GPIO编号*/
    uint8_t clk_div;       /*!< RMT信道计数器除法器*/
    uint8_t mem_block_num; /*!< RMT内存块编号*/
    uint32_t flags;        /*!< RMT信道额外配置，或与RMT_channel_FLAGS_[*]*/
    union {
        rmt_tx_config_t tx_config; /*!< RMT TX参数*/
        rmt_rx_config_t rx_config; /*!< RMT RX参数*/
    };
} rmt_config_t;

/**
 * @brief Tx信道的默认配置
 *
 */
#define RMT_DEFAULT_CONFIG_TX(gpio, channel_id)      \
    {                                                \
        .rmt_mode = RMT_MODE_TX,                     \
        .channel = channel_id,                       \
        .gpio_num = gpio,                            \
        .clk_div = 80,                               \
        .mem_block_num = 1,                          \
        .flags = 0,                                  \
        .tx_config = {                               \
            .carrier_freq_hz = 38000,                \
            .carrier_level = RMT_CARRIER_LEVEL_HIGH, \
            .idle_level = RMT_IDLE_LEVEL_LOW,        \
            .carrier_duty_percent = 33,              \
            .carrier_en = false,                     \
            .loop_en = false,                        \
            .idle_output_en = true,                  \
        }                                            \
    }

/**
 * @brief RX信道的默认配置
 *
 */
#define RMT_DEFAULT_CONFIG_RX(gpio, channel_id) \
    {                                           \
        .rmt_mode = RMT_MODE_RX,                \
        .channel = channel_id,                  \
        .gpio_num = gpio,                       \
        .clk_div = 80,                          \
        .mem_block_num = 1,                     \
        .flags = 0,                             \
        .rx_config = {                          \
            .idle_threshold = 12000,            \
            .filter_ticks_thresh = 100,         \
            .filter_en = true,                  \
        }                                       \
    }

/**
* @brief RMT中断句柄
*
*/
typedef intr_handle_t rmt_isr_handle_t;

/**
* @brief RMT Tx End回调函数的类型
*
*/
typedef void (*rmt_tx_end_fn_t)(rmt_channel_t channel, void *arg);

/**
* @brief 封装RMT TX结束回调的结构
*/
typedef struct {
    rmt_tx_end_fn_t function; /*!< 在RMT TX端调用的函数*/
    void *arg;                /*!< 传递给函数的可选参数*/
} rmt_tx_end_callback_t;

/**
* @brief 用户回调函数，用于将uint8_t类型数据转换为rmt格式（rmt_item32_t）。
*
*        该函数可以从ISR调用，因此代码应该简短高效。
*
* @param  src 指向存储需要转换为rmt格式的原始数据的缓冲区的指针。
* @param[out] dest 指向存储rmt格式数据的缓冲区的指针。
* @param  src_size 原始数据大小。
* @param  wanted_num 要获取的rmt格式数据的数量。
* @param[out] translated_size 已转换为rmt格式的原始数据的大小，如果在用户回调中未转换数据，则应返回0。
* @param[out] item_num 实际转换为的rmt格式数据的数量，如果没有足够的原始数据，可以小于wanted_num，但不能超过wanted_nm。如果未转换任何数据，则应返回0。
*
* @note 事实上，item_num应该是translated_size的倍数，例如：当我们将uint8_t类型数据的每个字节转换为rmt格式数据时，item_nm和translated_size之间的关系应该是“item_num=translated_size8”。
*/
typedef void (*sample_to_rmt_t)(const void *src, rmt_item32_t *dest, size_t src_size, size_t wanted_num, size_t *translated_size, size_t *item_num);

/**
* @brief 设置RMT时钟分频器，信道时钟与源时钟分频。
*
* @param channel RMT通道
* @param div_cnt RMT计数器时钟分频器
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_set_clk_div(rmt_channel_t channel, uint8_t div_cnt);

/**
* @brief 获取RMT时钟分频器，信道时钟从源时钟分频。
*
* @param channel RMT通道
* @param div_cnt 接受RMT计数器除法器的指针
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_get_clk_div(rmt_channel_t channel, uint8_t *div_cnt);

/**
* @brief 设置RMT RX空闲阈值
*
*        在接收模式下，当在输入信号上检测不到超过idle_thres信道时钟周期的边沿时，接收过程结束。
*
* @param channel RMT通道
* @param thresh RMT RX空闲阈值
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_set_rx_idle_thresh(rmt_channel_t channel, uint16_t thresh);

/**
* @brief 获取RMT空闲阈值。
*
*        在接收模式下，当在输入信号上检测不到超过idle_thres信道时钟周期的边沿时，接收过程结束。
*
* @param channel RMT通道
* @param thresh 接受RMT RX空闲阈值的指针
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_get_rx_idle_thresh(rmt_channel_t channel, uint16_t *thresh);

/**
* @brief 设置RMT通道的RMT内存块编号
*
*        此功能用于配置分配给信道n的内存块的数量。8个信道共享一个512x32位RAM块，处理器内核可以通过APB总线读取和写入，也可以由发射机读取和由接收机写入。
*
*        通道n的RAM地址范围为start_addr_CHn到end_addr_CCHn，其定义如下：内存块起始地址为RMT_channel_MEM（n）（以soc/RMT_reg.h为单位），即start_addr_CHn=RMT基地址+0x800+64∗ 4.∗ n、 而end_addr_chn=RMT基地址+0x800+64∗ 4.∗ n+64∗ 4.∗ RMT_MEM_SIZE_CHn模式512∗ 4.
*
*        @note 如果一个通道的内存块号设置为大于1的值，则该通道将占用下一个通道中的内存块。通道0最多可以使用8个内存块，因此通道7只能使用一个内存块。
*
* @param channel RMT通道
* @param rmt_mem_num RMT RX内存块编号，一个块具有64*32位。
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_set_mem_block_num(rmt_channel_t channel, uint8_t rmt_mem_num);

/**
* @brief 获取RMT内存块编号
*
* @param channel RMT通道
* @param rmt_mem_num 接受RMT RX内存块编号的指针
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_get_mem_block_num(rmt_channel_t channel, uint8_t *rmt_mem_num);

/**
* @brief 为TX信号配置RMT载波。
*
*        为carrier_high和carrier_low设置不同的值，以设置不同的载波频率。载波高/低的单位是源时钟节拍，而不是分频信道计数器时钟。
*
* @param channel RMT通道
* @param carrier_en 是否启用输出载波。
* @param high_level 载波高电平持续时间
* @param low_level 载波的低电平持续时间。
* @param carrier_level 配置信道的载波调制方式。
*     -1’b1：低输出电平传输
*     -1’b0：高输出电平传输
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_set_tx_carrier(rmt_channel_t channel, bool carrier_en, uint16_t high_level, uint16_t low_level, rmt_carrier_level_t carrier_level);

/**
* @brief 将RMT内存设置为低功耗模式。
*
*        减少内存消耗的功率。1： 存储器处于低功率状态。
*
* @param channel RMT通道
* @param pd_en RMT内存低功耗启用。
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_set_mem_pd(rmt_channel_t channel, bool pd_en);

/**
* @brief 获取RMT内存低功耗模式。
*
* @param channel RMT通道
* @param pd_en 用于接受RMT内存低功耗模式的指针。
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_get_mem_pd(rmt_channel_t channel, bool *pd_en);

/**
* @brief 设置RMT开始从内存发送数据。
*
* @param channel RMT通道
* @param tx_idx_rst 设置为true以重置TX的内存索引。否则，发射器将从内存中的最后一个索引继续发送。
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_tx_start(rmt_channel_t channel, bool tx_idx_rst);

/**
* @brief 设置RMT停止发送。
*
* @param channel RMT通道
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_tx_stop(rmt_channel_t channel);

/**
* @brief 设置RMT开始接收数据。
*
* @param channel RMT通道
* @param rx_idx_rst 设置为true以重置接收器的内存索引。否则，接收器将继续接收数据到存储器中的最后一个索引。
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_rx_start(rmt_channel_t channel, bool rx_idx_rst);

/**
* @brief 设置RMT停止接收数据。
*
* @param channel RMT通道
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_rx_stop(rmt_channel_t channel);

/**
* @brief 重置RMT TX存储器
*
* @param channel RMT通道
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_tx_memory_reset(rmt_channel_t channel);

/**
* @brief 重置RMT RX存储器
*
* @param channel RMT通道
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_rx_memory_reset(rmt_channel_t channel);

/**
* @brief 设置RMT内存所有者。
* @note 设置memroy仅对RX信道有效。
*
* @param channel RMT通道
* @param owner 设置发射机或接收机何时可以处理信道存储器。
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_set_memory_owner(rmt_channel_t channel, rmt_mem_owner_t owner);

/**
* @brief 获取RMT内存所有者。
*
* @param channel RMT通道
* @param owner 获取内存所有者的指针。
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_get_memory_owner(rmt_channel_t channel, rmt_mem_owner_t *owner);

/**
* @brief 设置RMT tx循环模式。
*
* @param channel RMT通道
* @param loop_en 启用RMT发射机环路发送模式。如果设置为真，发射机将在一个循环中一次又一次地从信道中的第一个数据发送到最后一个数据。
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_set_tx_loop_mode(rmt_channel_t channel, bool loop_en);

/**
* @brief 获取RMT tx循环模式。
*
* @param channel RMT通道
* @param loop_en 用于接受RMT发射机环路发送模式的指针。
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_get_tx_loop_mode(rmt_channel_t channel, bool *loop_en);

/**
* @brief 设置RMT RX滤波器。
*
*        在接收模式下，当脉冲宽度小于阈值时，信道将忽略输入脉冲。在源时钟中计数，而不是分频计数器时钟。
*
* @param channel RMT通道
* @param rx_filter_en 启用RMT接收器过滤器。
* @param thresh 接收器的脉冲宽度阈值。
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_set_rx_filter(rmt_channel_t channel, bool rx_filter_en, uint8_t thresh);

/**
* @brief 设置RMT源时钟
*
*        RMT模块有两个时钟源：1.APB时钟，80Mhz；2.REF时钟，1Mhz（此版本不支持）。
*
* @param channel RMT通道
* @param base_clk 为RMT模块选择源时钟。
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_set_source_clk(rmt_channel_t channel, rmt_source_clk_t base_clk);

/**
* @brief 获取RMT源时钟
*
*        RMT模块有两个时钟源：1.APB时钟，80Mhz；2.REF时钟，1Mhz（此版本不支持）。
*
* @param channel RMT通道
* @param src_clk 用于接受RMT模块源时钟的指针。
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_get_source_clk(rmt_channel_t channel, rmt_source_clk_t *src_clk);

/**
* @brief 设置变送器的RMT空闲输出电平
*
* @param channel RMT通道
* @param idle_out_en 启用空闲电平输出。
* @param level 为处于空闲状态的信道设置输出信号电平。
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_set_idle_level(rmt_channel_t channel, bool idle_out_en, rmt_idle_level_t level);

/**
* @brief 获取变送器的RMT空闲输出电平
*
* @param channel RMT通道
* @param idle_out_en 用于接受启用空闲值的指针。
* @param level 指针，用于接受指定信道空闲状态下输出信号电平的值。
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_get_idle_level(rmt_channel_t channel, bool *idle_out_en, rmt_idle_level_t *level);

/**
* @brief 获取RMT状态
*
* @param channel RMT通道
* @param status 用于接受通道状态的指针。请参阅`RMT_REG中的RMT_CHnSTATUS_REG（n=0~7）。h’以获取每个字段的更多详细信息。
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_get_status(rmt_channel_t channel, uint32_t *status);

/**
* @brief 设置RMT RX中断启用
*
* @param channel RMT通道
* @param en 启用或禁用RX中断。
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_set_rx_intr_en(rmt_channel_t channel, bool en);

/**
* @brief 设置RMT RX错误中断启用
*
* @param channel RMT通道
* @param en 启用或禁用RX错误中断。
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_set_err_intr_en(rmt_channel_t channel, bool en);

/**
* @brief 设置RMT TX中断启用
*
* @param channel RMT通道
* @param en 启用或禁用TX中断。
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_set_tx_intr_en(rmt_channel_t channel, bool en);

/**
* @brief 设置RMT TX阈值事件中断启用
*
* 当传输的项目数达到阈值时，将触发中断
*
* @param channel RMT通道
* @param en 启用或禁用TX事件中断。
* @param evt_thresh RMT事件中断阈值
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_set_tx_thr_intr_en(rmt_channel_t channel, bool en, uint16_t evt_thresh);

/**
* @brief 配置RMT通道使用的GPIO
*
* @param channel RMT通道
* @param mode RMT模式，RMT_mode_TX或RMT_mode_RX
* @param gpio_num GPIO编号，与特定RMT信号连接
* @param invert_signal 通过GPIO矩阵物理反转RMT信号
*
* @return
*     -由于参数错误，ESP_ERR_INVALID_ARG配置RMT GPIO失败
*     -ESP_OK成功配置RMT GPIO
*/
esp_err_t rmt_set_gpio(rmt_channel_t channel, rmt_mode_t mode, gpio_num_t gpio_num, bool invert_signal);

/**
* @brief 配置RMT参数
*
* @param rmt_param RMT参数结构
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_config(const rmt_config_t *rmt_param);

/**
* @brief 注册RMT中断处理程序，该处理程序是ISR。
*
*        处理程序将连接到运行此函数的同一CPU内核。
*
* @note  如果您已经调用rmt_driver_install以使用系统rmt驱动程序，请不要再次注册ISR处理程序。
*
* @param fn 中断处理程序函数。
* @param arg 处理程序函数的参数
* @param intr_alloc_flags 用于分配中断的标志。一个或多个（ORred）ESP_INTR_FLAG_值。请参见esp_intr_alloc。h了解更多信息。
* @param handle 如果非零，则在此处存储稍后清理ISR的句柄。
*
* @return
*     -ESP_OK成功
*     -ESP_ERR_INVALID_ARG函数指针错误。
*     -已安装ESP_FAIL系统驱动程序，无法为RMT注册ISR处理程序
*/
esp_err_t rmt_isr_register(void (*fn)(void *), void *arg, int intr_alloc_flags, rmt_isr_handle_t *handle);

/**
* @brief   取消注册以前注册的RMT中断处理程序
*
* @param handle 从rmt_isr_register获取的句柄
*
* @return
*     -ESP_OK成功
*     -ESP_ERR_INVALID_ARG句柄无效
*/
esp_err_t rmt_isr_deregister(rmt_isr_handle_t handle);

/**
* @brief 用给定的RMT项填充通道的内存数据。
*
* @param channel RMT通道
* @param item 项目指针。
* @param item_num RMT发送项目编号。
* @param mem_offset 内存的索引偏移量。
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_fill_tx_items(rmt_channel_t channel, const rmt_item32_t *item, uint16_t item_num, uint16_t mem_offset);

/**
* @brief 初始化RMT驱动程序
*
* @param channel RMT通道
* @param rx_buf_size RMT RX环形缓冲区的大小。如果未使用RX环形缓冲区，则可以为0。
* @param intr_alloc_flags RMT驱动程序中断处理程序的标志。传递0作为默认标志。请参见esp_intr_alloc。h了解详细信息。如果使用了ESP_INTR_FLAG_IRAM，请不要在调用rmt_write_items时使用从psram分配的内存。
*
* @return
*     -ESP_ERR_INVALID_STATE驱动程序已安装，请先调用rmt_Driver_unistall。
*     -ESP_ERR_NO_MEM内存分配失败
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_driver_install(rmt_channel_t channel, size_t rx_buf_size, int intr_alloc_flags);

/**
* @brief 卸载RMT驱动程序。
*
* @param channel RMT通道
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_driver_uninstall(rmt_channel_t channel);

/**
* @brief 获取八个通道的当前状态。
*
* @note 如果可能同时调用“rmt_driver_unistall”，请不要调用此函数。
*
* @param[out] channel_status 存储每个通道的当前状态
*
* @return
*     -ESP_ERR_INVALID_ARG参数为NULL
*     -ESP_OK成功
*/
esp_err_t rmt_get_channel_status(rmt_channel_status_result_t *channel_status);

/**
* @brief 获取通道内部计数器时钟的速度。
*
* @param channel RMT通道
* @param[out] clock_hz 计数器时钟速度，单位：hz
*
* @return
*     -ESP_ERR_INVALID_ARG参数为NULL
*     -ESP_OK成功
*/
esp_err_t rmt_get_counter_clock(rmt_channel_t channel, uint32_t *clock_hz);

/**
* @brief RMT从RMT_item数组发送波形。
*
*        该API允许用户发送任意长度的波形。
*
* @param channel RMT通道
* @param rmt_item RMT项目数组的起始点。如果使用了ESP_INTR_FLAG_IRAM，请不要在调用rmt_write_items时使用从psram分配的内存。
* @param item_num RMT数据项编号。
* @param wait_tx_done
*        -如果设置为1，它将阻止任务并等待发送完成。
*        -如果设置为0，则不会立即等待并返回。
*
*         @note 此功能不会复制数据，而是指向原始项，并发送波形项。如果wait_tx_done设置为true，则该函数将被阻止，并且在所有项目发出之前不会返回。如果wait_tx_done设置为false，该函数将立即返回，驱动程序中断将继续发送项目。当驱动程序仍在驱动程序中断中发送项目时，我们必须确保项目数据不会损坏。
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_write_items(rmt_channel_t channel, const rmt_item32_t *rmt_item, int item_num, bool wait_tx_done);

/**
* @brief 等待RMT TX完成。
*
* @param channel RMT通道
* @param wait_time 等待传输完成的最长时间（单位：滴答）。如果设置为0，如果TX忙（轮询），则立即返回ESP_ERR_TIMEOUT。
*
* @return
*     -ESP_OK RMT Tx成功完成
*     -ESP_ERR_TIMEOUT超过了给定的'wait_time'
*     -ESP_ERR_INVALID_ARG参数错误
*     -未安装ESP_FAIL驱动程序
*/
esp_err_t rmt_wait_tx_done(rmt_channel_t channel, TickType_t wait_time);

/**
* @brief 从RMT获取环形缓冲区。
*
*        用户可以获得RMT RX环形缓冲区句柄，并处理RX数据。
*
* @param channel RMT通道
* @param buf_handle 指向缓冲区句柄以接受RX环形缓冲区句柄的指针。
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_get_ringbuf_handle(rmt_channel_t channel, RingbufHandle_t *buf_handle);

/**
* @brief 初始化rmt转换器并注册用户回调。回调将把需要发送的原始数据转换为rmt格式。如果通道被多次初始化，则用户回调将被后面的替换。
*
* @param channel RMT通道。
* @param fn 指向数据转换函数。
*
* @return
*     -ESP_FAIL初始化失败。
*     -ESP_OK初始化成功。
*/
esp_err_t rmt_translator_init(rmt_channel_t channel, sample_to_rmt_t fn);

/**
* @brief 为特定频道的翻译器设置用户上下文
*
* @param channel RMT通道编号
* @param context 用户上下文
*
* @return
*     -ESP_FAIL设置上下文失败
*     -ESP_OK设置上下文成功
*/
esp_err_t rmt_translator_set_context(rmt_channel_t channel, void *context);

/**
* @brief 获取由“rmt_translator_set_context”设置的用户上下文
*
* @note 必须在RMT转换器回调函数中调用此API，并且第一个参数必须是在该回调函数中获得的实际参数“item_num”。
*
* @param item_num 包含翻译项目数的内存地址（来自驱动程序的内部内存）
* @param context 返回的用户上下文
*
* @return
*     -ESP_FAIL获取上下文失败
*     -ESP_OK获取上下文成功
*/
esp_err_t rmt_translator_get_context(const size_t *item_num, void **context);

/**
* @brief 将uint8_t类型的数据转换为rmt格式并发送出去。需要rmt_translator_init首先初始化转换器。
*
* @param channel RMT通道。
* @param src 指向原始数据的指针。
* @param src_size 原始数据的大小。
* @param wait_tx_done 设置为true以等待所有数据发送完成。
*
* @return
*     -ESP_FAIL发送失败
*     -ESP_OK发送成功
*/
esp_err_t rmt_write_sample(rmt_channel_t channel, const uint8_t *src, size_t src_size, bool wait_tx_done);

/**
* @brief 注册将在传输结束时调用的回调。
*
*        由中断上下文中的rmt_driver_isr_fault调用。
*
* @note 需要rmt_driver_install安装默认ISR处理程序。
*
* @param function 要从默认中断处理程序调用的函数或NULL。
* @param arg 调用回调时将提供给回调的参数。
*
* @return 以前的回调设置（如果没有，成员将设置为NULL）
*/
rmt_tx_end_callback_t rmt_register_tx_end_callback(rmt_tx_end_fn_t function, void *arg);

#if SOC_RMT_SUPPORT_RX_PINGPONG
/**
* @brief 设置RMT RX阈值事件中断启用
*
* 当接收的项目数达到阈值时，将触发中断
*
* @param channel RMT通道
* @param en 启用或禁用RX事件中断。
* @param evt_thresh RMT事件中断阈值
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_set_rx_thr_intr_en(rmt_channel_t channel, bool en, uint16_t evt_thresh);
#endif

#if SOC_RMT_SUPPORT_TX_SYNCHRO
/**
* @brief 将通道添加到同步组中（同一组中的通道可以同时启动事务）
*
* @param channel RMT通道
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_add_channel_to_group(rmt_channel_t channel);

/**
* @brief 从组中删除频道
*
* @param channel RMT通道
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_remove_channel_from_group(rmt_channel_t channel);
#endif

#if SOC_RMT_SUPPORT_TX_LOOP_COUNT
/**
 * @brief 设置RMT TX信道的循环计数阈值
 *
 * 当tx循环计数达到该值时，ISR回调将通知用户
 *
 * @param channel RMT通道
 * @param count 循环计数，1~1023
 * @return
 *      -ESP_ERR_INVALID_ARG参数错误
 *      -ESP_OK成功
 */
esp_err_t rmt_set_tx_loop_count(rmt_channel_t channel, uint32_t count);

/**
 * @brief 启用或禁用当循环计数达到阈值时，RMT将停止发送的功能。
 *
 * -当环路自动停止功能启用时，环路计数达到一定阈值后，将停止RMT传输
 * -禁用后，RMT传输将无限期地继续，直到用户停止
 *
 * @note 自动停止功能在特定目标（即定义了SOC_RMT_SUPPORT_TX_LOOP_AUTOSTOP的目标）的硬件中实现。否则，自动停止功能通过中断在软件中实现。
 *
 * @param channel RMT通道
 * @param en 启用位
 * @return
 *      -ESP_ERR_INVALID_ARG参数错误
 *      -ESP_OK成功
 */
esp_err_t rmt_enable_tx_loop_autostop(rmt_channel_t channel, bool en);
#endif // SOC_RMT_SUPPORT_TX_LOOP_COUNT

/**
* @brief 重置RMT TX/RX内存索引。
*
* @param channel RMT通道
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_memory_rw_rst(rmt_channel_t channel)
__attribute__((deprecated("use rmt_tx_memory_reset or rmt_rx_memory_reset instead")));

/**
* @brief 将掩码值设置为RMT中断启用寄存器。
*
* @param mask 要设置到寄存器的位掩码
*
*/
void rmt_set_intr_enable_mask(uint32_t mask)
__attribute__((deprecated("interrupt should be handled by driver")));

/**
* @brief 清除RMT中断启用寄存器的掩码值。
*
* @param mask 清除寄存器的位掩码
*
*/
void rmt_clr_intr_enable_mask(uint32_t mask)
__attribute__((deprecated("interrupt should be handled by driver")));

/**
* @brief 设置RMT引脚
*
* @param channel RMT通道
* @param mode RMT的TX或RX模式
* @param gpio_num 发送或接收信号的GPIO编号。
*
* @return
*     -ESP_ERR_INVALID_ARG参数错误
*     -ESP_OK成功
*/
esp_err_t rmt_set_pin(rmt_channel_t channel, rmt_mode_t mode, gpio_num_t gpio_num)
__attribute__((deprecated("use rmt_set_gpio instead")));

#ifdef __cplusplus
}
#endif

