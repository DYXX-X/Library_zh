/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#include <stdbool.h>
#include "esp_err.h"
#include "esp_lcd_types.h"
#include "soc/soc_caps.h"
#include "hal/lcd_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void *esp_lcd_spi_bus_handle_t;                       /*!< LCD SPI总线手柄类型*/
typedef void *esp_lcd_i2c_bus_handle_t;                       /*!< LCD I2C总线手柄类型*/
typedef struct esp_lcd_i80_bus_t *esp_lcd_i80_bus_handle_t;   /*!< LCD intel 8080总线手柄类型*/

/**
 * @brief 发送LCD命令和相应参数
 *
 * @note 此函数发送的命令很短，因此使用轮询事务发送。在命令传输完成之前，函数不会返回。如果调用此函数时，“esp_lcd_panel_io_tx_color（）”发送的任何排队事务仍处于挂起状态，则此函数将等待它们完成且队列为空后再发送命令。
 *
 * @param[in] io LCD面板IO句柄，由其他工厂API创建，如`esp_LCD_new_panel_IO_spi（）`
 * @param[in] lcd_cmd 特定LCD命令
 * @param[in] param 保存命令特定参数的缓冲区，如果命令不需要参数，则设置为NULL
 * @param[in] param_size 内存中“param”的大小（字节），如果命令不需要参数，则设置为零
 * @return
 *          -如果参数无效，则为ESP_ERR_INVALID_ARG
 *          -成功时ESP_OK
 */
esp_err_t esp_lcd_panel_io_tx_param(esp_lcd_panel_io_handle_t io, int lcd_cmd, const void *param, size_t param_size);

/**
 * @brief 传输LCD RGB数据
 *
 * @note 此函数将命令和RGB数据打包到事务中，并推送到队列中。实际传输在后台执行（DMA+中断）。调用者应该负责“颜色”缓冲区的生命周期。应在回调“on_color_trans_done（）”中回收颜色缓冲区。
 *
 * @param[in] io LCD面板IO句柄，由工厂API创建，如`esp_LCD_new_panel_IO_spi（）`
 * @param[in] lcd_cmd 特定LCD命令
 * @param[in] color 保存RGB颜色数据的缓冲区
 * @param[in] color_size 内存中“颜色”的大小（字节）
 * @return
 *          -如果参数无效，则为ESP_ERR_INVALID_ARG
 *          -成功时ESP_OK
 */
esp_err_t esp_lcd_panel_io_tx_color(esp_lcd_panel_io_handle_t io, int lcd_cmd, const void *color, size_t color_size);

/**
 * @brief Destory LCD面板IO句柄（取消初始化面板并释放所有相应的资源）
 *
 * @param[in] io LCD面板IO句柄，由工厂API创建，如`esp_LCD_new_panel_IO_spi（）`
 * @return
 *          -如果参数无效，则为ESP_ERR_INVALID_ARG
 *          -成功时ESP_OK
 */
esp_err_t esp_lcd_panel_io_del(esp_lcd_panel_io_handle_t io);

/**
 * @brief LCD面板IO事件数据类型
 */
typedef struct {
} esp_lcd_panel_io_event_data_t;

/**
 * @brief 声明当面板IO完成传输颜色数据时将调用的函数的原型
 *
 * @param[in] panel_io LCD面板IO句柄，由工厂API创建，如`esp_LCD_new_panel_IO_spi（）`
 * @param[in] edata 面板IO事件数据，由驱动程序提供
 * @param[in] user_ctx 用户数据，从`esp_lcd_panel_io_xxx_config_t传递`
 * @return 此函数是否唤醒了高优先级任务
 */
typedef bool (*esp_lcd_panel_io_color_trans_done_cb_t)(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx);

/**
 * @brief 面板IO配置结构，用于SPI接口
 */
typedef struct {
    int cs_gpio_num; /*!< 用于CS线路的GPIO*/
    int dc_gpio_num; /*!< GPIO用于选择D/C线，如果D/C线未通过手动拉高/低GPIO控制，则将其设置为-1*/
    int spi_mode;    /*!< 传统SPI模式（0~3）*/
    unsigned int pclk_hz;    /*!< 像素时钟频率*/
    size_t trans_queue_depth; /*!< 内部事务队列的大小*/
    esp_lcd_panel_io_color_trans_done_cb_t on_color_trans_done; /*!< 颜色数据传输完成时调用回调*/
    void *user_ctx;    /*!< 用户私有数据，直接传递到on_color_trans_done的User_ctx*/
    int lcd_cmd_bits;   /*!< LCD命令的位宽*/
    int lcd_param_bits; /*!< LCD参数的位宽*/
    struct {
        unsigned int dc_as_cmd_phase: 1; /*!< D/C行值编码到SPI事务命令阶段*/
        unsigned int dc_low_on_data: 1;  /*!< 如果该标志被启用，DC线路=0表示传输数据，DC线路=1表示传输命令；反之亦然*/
        unsigned int octal_mode: 1;      /*!< 使用八进制模式（8条数据线）传输，该模式用于模拟Intel 8080定时*/
    } flags;
} esp_lcd_panel_io_spi_config_t;

/**
 * @brief 为SPI接口创建LCD面板IO句柄
 *
 * @param[in] bus SPI总线手柄
 * @param[in] io_config SPI接口的IO配置
 * @param[out] ret_io 返回的IO句柄
 * @return
 *          -如果参数无效，则为ESP_ERR_INVALID_ARG
 *          -ESP_ERR_NO_MEM（如果内存不足）
 *          -成功时ESP_OK
 */
esp_err_t esp_lcd_new_panel_io_spi(esp_lcd_spi_bus_handle_t bus, const esp_lcd_panel_io_spi_config_t *io_config, esp_lcd_panel_io_handle_t *ret_io);

typedef struct {
    uint32_t dev_addr; /*!< I2C设备地址*/
    esp_lcd_panel_io_color_trans_done_cb_t on_color_trans_done; /*!< 颜色数据传输完成时调用回调*/
    void *user_ctx; /*!< 用户私有数据，直接传递到on_color_trans_done的User_ctx*/
    size_t control_phase_bytes; /*!< I2C LCD面板将控制信息（例如D/C选择）编码到控制阶段，以几个字节为单位*/
    unsigned int dc_bit_offset; /*!< 控制阶段D/C选择位的偏移*/
    int lcd_cmd_bits;           /*!< LCD命令的位宽*/
    int lcd_param_bits;         /*!< LCD参数的位宽*/
    struct {
        unsigned int dc_low_on_data: 1;  /*!< 如果该标志被启用，DC线路=0表示传输数据，DC线路=1表示传输命令；反之亦然*/
    } flags;
} esp_lcd_panel_io_i2c_config_t;

/**
 * @brief 为I2C接口创建LCD面板IO句柄
 *
 * @param[in] bus I2C总线手柄
 * @param[in] io_config IO配置，用于I2C接口
 * @param[out] ret_io 返回的IO句柄
 * @return
 *          -如果参数无效，则为ESP_ERR_INVALID_ARG
 *          -ESP_ERR_NO_MEM（如果内存不足）
 *          -成功时ESP_OK
 */
esp_err_t esp_lcd_new_panel_io_i2c(esp_lcd_i2c_bus_handle_t bus, const esp_lcd_panel_io_i2c_config_t *io_config, esp_lcd_panel_io_handle_t *ret_io);

#if SOC_LCD_I80_SUPPORTED
/**
 * @brief LCD Intel 8080总线配置结构
 */
typedef struct {
    int dc_gpio_num; /*!< 用于D/C线的GPIO*/
    int wr_gpio_num; /*!< 用于WR线的GPIO*/
    lcd_clock_source_t clk_src; /*!< I80 LCD外围设备的时钟源*/
    int data_gpio_nums[SOC_LCD_I80_BUS_WIDTH]; /*!< 用于数据线的GPIO*/
    size_t bus_width;          /*!< 数据线数量，8或16*/
    size_t max_transfer_bytes; /*!< 最大传输大小，这决定了内部DMA链路的长度*/
} esp_lcd_i80_bus_config_t;

/**
 * @brief 创建Intel 8080总线句柄
 *
 * @param[in] bus_config 总线配置
 * @param[out] ret_bus 返回的总线句柄
 * @return
 *          -如果参数无效，则为ESP_ERR_INVALID_ARG
 *          -ESP_ERR_NO_MEM（如果内存不足）
 *          -如果没有可用的空闲总线，则为ESP_ERR_NOT_FOUND
 *          -成功时ESP_OK
 */
esp_err_t esp_lcd_new_i80_bus(const esp_lcd_i80_bus_config_t *bus_config, esp_lcd_i80_bus_handle_t *ret_bus);

/**
 * @brief Destory Intel 8080总线句柄
 *
 * @param[in] bus Intel 8080总线句柄，由`esp_lcd_new_i80_bus（）创建`
 * @return
 *          -如果参数无效，则为ESP_ERR_INVALID_ARG
 *          -ESP_ERR_INVALID_STATE（如果仍有一些设备连接到总线）
 *          -成功时ESP_OK
 */
esp_err_t esp_lcd_del_i80_bus(esp_lcd_i80_bus_handle_t bus);

/**
 * @brief 面板IO配置结构，用于intel 8080接口
 */
typedef struct {
    int cs_gpio_num;         /*!< 用于CS线路的GPIO，设置为-1将宣布专用I80总线*/
    unsigned int pclk_hz;    /*!< 像素时钟频率*/
    size_t trans_queue_depth; /*!< 事务队列大小、更大的队列、更高的吞吐量*/
    esp_lcd_panel_io_color_trans_done_cb_t on_color_trans_done; /*!< 颜色数据传输完成时调用回调*/
    void *user_ctx;    /*!< 用户私有数据，直接传递到on_color_trans_done的User_ctx*/
    int lcd_cmd_bits;   /*!< LCD命令的位宽*/
    int lcd_param_bits; /*!< LCD参数的位宽*/
    struct {
        unsigned int dc_idle_level: 1;  /*!< 慢车阶段直流线路的电平*/
        unsigned int dc_cmd_level: 1;   /*!< CMD阶段直流线路的电平*/
        unsigned int dc_dummy_level: 1; /*!< DUMMY阶段直流线路的电平*/
        unsigned int dc_data_level: 1;  /*!< DATA阶段直流线路的电平*/
    } dc_levels; /*!< 每个i80设备可能有自己的D/C控制逻辑*/
    struct {
        unsigned int cs_active_high: 1;     /*!< 如果设置，CS线路的高电平将选择设备，否则，CS线路为低电平激活*/
        unsigned int reverse_color_bits: 1; /*!< 反转数据位，D[N:0]->D[0:N]*/
        unsigned int swap_color_bytes: 1;   /*!< 交换相邻的两个颜色字节*/
        unsigned int pclk_active_neg: 1;    /*!< 当WR信号（也称为PCLK）出现下降沿时，显示器将写入数据线*/
        unsigned int pclk_idle_low: 1;      /*!< WR信号（也称为PCLK）在IDLE阶段保持在低电平*/
    } flags;
} esp_lcd_panel_io_i80_config_t;

/**
 * @brief 为Intel 8080接口创建LCD面板IO
 *
 * @param[in] bus Intel 8080总线句柄，由`esp_lcd_new_i80_bus（）创建`
 * @param[in] io_config IO配置，用于i80接口
 * @param[out] ret_io 返回面板IO手柄
 * @return
 *          -如果参数无效，则为ESP_ERR_INVALID_ARG
 *          -ESP_ERR_NOT_SUPPORTED（如果无法满足某些配置，例如像素时钟超出范围）
 *          -ESP_ERR_NO_MEM（如果内存不足）
 *          -成功时ESP_OK
 */
esp_err_t esp_lcd_new_panel_io_i80(esp_lcd_i80_bus_handle_t bus, const esp_lcd_panel_io_i80_config_t *io_config, esp_lcd_panel_io_handle_t *ret_io);

#endif // SOC_LCD_I80_SUPPORTED

#ifdef __cplusplus
}
#endif

