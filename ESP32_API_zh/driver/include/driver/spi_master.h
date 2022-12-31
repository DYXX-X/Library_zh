/*
 * SPDX文件版权文本：2010-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "esp_err.h"
#include "freertos/FreeRTOS.h"
//对于spi_bus_initialization函数。向后兼容
#include "driver/spi_common.h"

/** SPI主时钟被80MHz apb时钟分频。下面的定义是示例频率，并且是准确的。可以自由指定随机频率，它将四舍五入到最接近的频率（如果高于8MHz，则为以下宏）。8兆赫
  */
#define SPI_MASTER_FREQ_8M      (APB_CLK_FREQ/10)
#define SPI_MASTER_FREQ_9M      (APB_CLK_FREQ/9)    ///<8.89MHz
#define SPI_MASTER_FREQ_10M     (APB_CLK_FREQ/8)    ///<10MHz
#define SPI_MASTER_FREQ_11M     (APB_CLK_FREQ/7)    ///<11.43MHz
#define SPI_MASTER_FREQ_13M     (APB_CLK_FREQ/6)    ///<13.33MHz
#define SPI_MASTER_FREQ_16M     (APB_CLK_FREQ/5)    ///<16MHz
#define SPI_MASTER_FREQ_20M     (APB_CLK_FREQ/4)    ///<20MHz
#define SPI_MASTER_FREQ_26M     (APB_CLK_FREQ/3)    ///<26.67兆赫
#define SPI_MASTER_FREQ_40M     (APB_CLK_FREQ/2)    ///<40MHz
#define SPI_MASTER_FREQ_80M     (APB_CLK_FREQ/1)    ///<80MHz
#ifdef __cplusplus
extern "C"
{
#endif

#define SPI_DEVICE_TXBIT_LSBFIRST          (1<<0)  ///<先发送命令/地址/数据LSB，而不是先发送默认MSB
#define SPI_DEVICE_RXBIT_LSBFIRST          (1<<1)  ///<先接收数据LSB，而不是先接收默认MSB
#define SPI_DEVICE_BIT_LSBFIRST            (SPI_DEVICE_TXBIT_LSBFIRST|SPI_DEVICE_RXBIT_LSBFIRST) ///<首先发送和接收LSB
#define SPI_DEVICE_3WIRE                   (1<<2)  ///<使用MOSI（=spid）发送和接收数据
#define SPI_DEVICE_POSITIVE_CS             (1<<3)  ///<在交易过程中使CS为正值而不是负值
#define SPI_DEVICE_HALFDUPLEX              (1<<4)  ///<在接收数据之前发送数据，而不是同时发送
#define SPI_DEVICE_CLK_AS_CS               (1<<5)  ///<CS激活时CS线路上的输出时钟
/** 在高频读取时存在定时问题（频率与是否使用iomux管脚、从设备看到时钟后的有效时间有关）。
  *     -在半双工模式下，驱动程序在读取阶段之前自动插入虚拟位，以解决定时问题。设置此标志以禁用此功能。
  *     -然而，在全双工模式下，硬件不能使用虚拟位，因此无法防止读取的数据损坏。设置此标志以确认您将只使用输出，或在没有伪位的情况下读取，风险自负。
  */
#define SPI_DEVICE_NO_DUMMY                (1<<6)
#define SPI_DEVICE_DDRCLK                  (1<<7)


typedef struct spi_transaction_t spi_transaction_t;
typedef void(*transaction_cb_t)(spi_transaction_t *trans);

/**
 * @brief 这是连接到SPI总线之一的SPI从设备的配置。
 */
typedef struct {
    uint8_t command_bits;           ///<命令阶段的默认位数（0-16），当不使用“SPI_TRANS_VARIABLE_CMD”时使用，否则忽略。
    uint8_t address_bits;           ///<地址阶段（0-64）中的默认位数，当不使用“SPI_TRANS_VARIABLE_ADDR”时使用，否则忽略。
    uint8_t dummy_bits;             ///<要在地址和数据相位之间插入的虚拟位的数量
    uint8_t mode;                   /**< SPI模式，表示一对（CPOL、CPHA）配置：
                                         - 0: (0, 0)
                                         - 1: (0, 1)
                                         - 2: (1, 0)
                                         - 3: (1, 1)
                                     */
    uint16_t duty_cycle_pos;         ///<正时钟的占空比，增量为1/256（128=50%/50%占空比）。将此值设置为0（=不设置）相当于将此值设为128。
    uint16_t cs_ena_pretrans;        ///<传输前应激活cs的SPI位周期数量（0-16）。这仅适用于半双工事务。
    uint8_t cs_ena_posttrans;       ///<传输后cs应保持活动的SPI位周期数量（0-16）
    int clock_speed_hz;             ///<时钟速度，80MHz分频器，单位Hz。请参见``SPI_MASTER_FREQ_*``。
    int input_delay_ns;             /**< 从设备的最大数据有效时间。SCLK和MISO有效之间所需的时间，包括从机到主机的可能时钟延迟。驾驶员使用该值在MISO准备就绪之前提供额外的延迟。0点离开，除非你知道你需要延迟。为了在高频（超过8MHz）下获得更好的计时性能，建议使用正确的值。
        */
    int spics_io_num;               ///<此设备的CS GPIO引脚，或-1（如果未使用）
    uint32_t flags;                 ///<SPI_DEVICE_*标志的位OR
    int queue_size;                 ///<事务队列大小。这设置了可以同时“空中传送”的事务数（使用spi_device_queue_trans排队，但尚未使用spi_device_get_trans_result完成）
    transaction_cb_t pre_cb;   /**< 在传输开始之前调用的回调。
                                 *
                                 *  该回调是在中断上下文中调用的。为了获得最佳性能，应该在IRAM中调用，请参阅SPI主文档中的“传输速度”部分以了解详细信息。如果没有，则当使用ESP_INTR_FLAG_IRAM初始化驱动程序时，回调可能会在闪存操作期间崩溃。
                                 */
    transaction_cb_t post_cb;  /**< 传输完成后调用的回调。
                                 *
                                 *  该回调是在中断上下文中调用的。为了获得最佳性能，应该在IRAM中调用，请参阅SPI主文档中的“传输速度”部分以了解详细信息。如果没有，则当使用ESP_INTR_FLAG_IRAM初始化驱动程序时，回调可能会在闪存操作期间崩溃。
                                 */
} spi_device_interface_config_t;


#define SPI_TRANS_MODE_DIO            (1<<0)  ///<以2位模式发送/接收数据
#define SPI_TRANS_MODE_QIO            (1<<1)  ///<以4位模式发送/接收数据
#define SPI_TRANS_USE_RXDATA          (1<<2)  ///<接收到spi_transaction_t的rx_data成员，而不是接收到rx_buffer的内存中。
#define SPI_TRANS_USE_TXDATA          (1<<3)  ///<传输spi_transaction_t的tx_data成员，而不是tx_buffer中的数据。使用此选项时不要设置tx_buffer。
#define SPI_TRANS_MODE_DIOQIO_ADDR    (1<<4)  ///<同时在SPI_mode_DIO/SPI_mode_QIO选择的模式下传输地址
#define SPI_TRANS_VARIABLE_CMD        (1<<5)  ///<使用`spi_transaction_ext_t``中的`command_bits ``，而不是`spi_device_interface_config_t`中的默认值。
#define SPI_TRANS_VARIABLE_ADDR       (1<<6)  ///<使用`spi_transaction_ext_t``中的`address_bits ``，而不是`spi_device_interface_config_t`中的默认值。
#define SPI_TRANS_VARIABLE_DUMMY      (1<<7)  ///<使用`spi_transaction_ext_t``中的`dummy_bits'`，而不是`spi_device_interface_config_t`中的默认值。
#define SPI_TRANS_CS_KEEP_ACTIVE      (1<<8)  ///<数据传输后保持CS活动
#define SPI_TRANS_MULTILINE_CMD       (1<<9)  ///<命令阶段使用的数据线与数据阶段相同（否则，命令阶段仅使用一条数据线）
#define SPI_TRANS_MODE_OCT            (1<<10) ///<以8位模式发送/接收数据
#define SPI_TRANS_MULTILINE_ADDR      SPI_TRANS_MODE_DIOQIO_ADDR ///<地址阶段使用的数据线与数据阶段相同（否则，地址阶段仅使用一条数据线）

/**
 * 此结构描述一个SPI事务。在事务完成之前，不应修改描述符。
 */
struct spi_transaction_t {
    uint32_t flags;                 ///<SPI_TRANS_*标志的位或
    uint16_t cmd;                   /**< 命令数据，其长度在spi_device_interface_config_t的“Command_bits”中设置。
                                      *
                                      *  <b>注：在ESP-IDF 2.1及之前版本中，此字段曾是“命令”，现在重新写入，以便在ESP-IDF3.0中以新的方式使用</b>
                                      *
                                      *  示例：写入0x0123和command_bits=12以发送命令0x12、0x_（在以前的版本中，您可能必须写入0x3_12）。
                                      */
    uint64_t addr;                  /**< 地址数据，其长度设置在spi_device_interface_config_t的“Address_bits”中。
                                      *
                                      *  <b>注：在ESP-IDF 2.1及之前版本中，此字段曾是“地址”，但在ESP-IDF3.0中重新写入，以便以新的方式使用</b>
                                      *
                                      *  示例：写入0x123400和address_bits=24以发送地址0x12、0x34、0x00（在以前的版本中，您可能必须写入0x12340000）。
                                      */
    size_t length;                  ///<总数据长度，以位为单位
    size_t rxlength;                ///<在全双工模式下，接收的总数据长度不应大于“长度”（0默认为“长度”值）。
    void *user;                     ///<用户定义变量。可用于存储例如交易ID。
    union {
        const void *tx_buffer;      ///<指向传输缓冲区的指针，或对于无MOSI阶段为NULL
        uint8_t tx_data[4];         ///<如果设置了SPI_TRANS_USE_TXDATA，则此处的数据集直接从此变量发送。
    };
    union {
        void *rx_buffer;            ///<指向接收缓冲区的指针，或NULL表示无MISO阶段。如果使用DMA，则以4字节为单位写入。
        uint8_t rx_data[4];         ///<如果设置了SPI_TRANS_USE_RXDATA，数据将直接接收到此变量
    };
} ;        //rx数据应该从32位对齐的地址开始，以避免dma问题。

/**
 * 此结构用于SPI事务，这些事务可能会更改其地址和命令长度。请将基中的标志设置为``SPI_TRANS_VARIABLE_CMD_ADR`，以使用此处的位长度。
 */
typedef struct {
    struct spi_transaction_t base;  ///＜事务数据，以便指向spi_Transaction_t的指针可以转换为spi_Transaction _ext_t
    uint8_t command_bits;           ///<此事务中的命令长度，以位为单位。
    uint8_t address_bits;           ///<此事务中的地址长度，以位为单位。
    uint8_t dummy_bits;             ///<此事务中的伪长度，以位为单位。
} spi_transaction_ext_t ;


typedef struct spi_device_t *spi_device_handle_t;  ///<SPI总线上设备的句柄
/**
 * @brief 在SPI总线上分配设备
 *
 * 这将初始化设备的内部结构，并在指定的SPI主外设上分配CS引脚，并将其路由到指定的GPIO。所有SPI主设备都有三个CS引脚，因此最多可以控制三个设备。
 *
 * @note 尽管一般情况下，专用SPI引脚上的速度高达80MHz，GPIO矩阵路由引脚上的速率高达40MHz，但GPIO矩阵上的全双工传输仅支持高达26MHz的速度。
 *
 * @param host_id 要在其上分配设备的SPI外围设备
 * @param dev_config 设备的SPI接口协议配置
 * @param handle 指向保存设备句柄的变量的指针
 * @return
 *         -如果参数无效，则为ESP_ERR_INVALID_ARG
 *         -如果主机没有任何可用的CS插槽，则为ESP_ERR_NOT_FOUND
 *         -ESP_ERR_NO_MEM（如果内存不足）
 *         -成功时ESP_OK
 */
esp_err_t spi_bus_add_device(spi_host_device_t host_id, const spi_device_interface_config_t *dev_config, spi_device_handle_t *handle);


/**
 * @brief 从SPI总线中移除设备
 *
 * @param handle 设备手柄释放
 * @return
 *         -如果参数无效，则为ESP_ERR_INVALID_ARG
 *         -如果设备已释放，则为ESP_ERR_INVALID_STATE
 *         -成功时ESP_OK
 */
esp_err_t spi_bus_remove_device(spi_device_handle_t handle);


/**
 * @brief 将SPI事务排队以执行中断事务。通过``spi_device_Get_trans_result``获取结果。
 *
 * @note 通常，设备不能同时启动（排队）轮询和中断事务。
 *
 * @param handle 使用spi_host_add_dev获得的设备句柄
 * @param trans_desc 要执行的事务的描述
 * @param ticks_to_wait 勾选等待，直到队列中有空间；使用portMAX_DELAY永不超时。
 * @return
 *         -如果参数无效，则返回ESP_ERR_INVALID_ARG。如果在未获取总线时指定了SPI_TRANS_CS_KEEP_ACTIVE标志，则会发生这种情况（应首先调用“SPI_device_acquire_bus（）”）
 *         -ESP_ERR_TIMEOUT（如果在ticks_to_wait过期之前队列中没有空间）
 *         -如果分配支持DMA的临时缓冲区失败，则为ESP_ERR_NO_MEM
 *         -如果以前的事务未完成，则返回ESP_ERR_INVALID_STATE
 *         -成功时ESP_OK
 */
esp_err_t spi_device_queue_trans(spi_device_handle_t handle, spi_transaction_t *trans_desc, TickType_t ticks_to_wait);


/**
 * @brief 获取前面通过“SPI_device_queue_trans”排队的SPI事务的结果。
 *
 * 此例程将等待到给定设备的事务成功完成。然后它将返回完成事务的描述，以便软件可以检查结果，例如释放内存或重新使用缓冲区。
 *
 * @param handle 使用spi_host_add_dev获得的设备句柄
 * @param trans_desc 指向变量的指针，该变量能够包含指向所执行事务描述的指针。在spi_device_get_trans_result返回描述符之前，不应修改描述符。
 * @param ticks_to_wait 勾选以等待返回的项目；使用portMAX_DELAY永不超时。
 * @return
 *         -如果参数无效，则为ESP_ERR_INVALID_ARG
 *         -如果在ticks_to_wait到期之前没有完成的事务，则为ESP_ERR_TIMEOUT
 *         -成功时ESP_OK
 */
esp_err_t spi_device_get_trans_result(spi_device_handle_t handle, spi_transaction_t **trans_desc, TickType_t ticks_to_wait);


/**
 * @brief 发送SPI事务，等待其完成，并返回结果
 *
 * 此函数相当于先调用spi_device_queue_trans（），然后调用spi_device_get_trans_result（）。如果仍有一个事务从spi_device_queue_trans（）或polling_start/transmit单独排队（启动），但尚未完成，请不要使用此选项。
 *
 * @note 当多个任务访问同一SPI设备时，此函数不是线程安全的。通常，设备不能同时启动（排队）轮询和中断事务。
 *
 * @param handle 使用spi_host_add_dev获得的设备句柄
 * @param trans_desc 要执行的事务的描述
 * @return
 *         -如果参数无效，则为ESP_ERR_INVALID_ARG
 *         -成功时ESP_OK
 */
esp_err_t spi_device_transmit(spi_device_handle_t handle, spi_transaction_t *trans_desc);


/**
 * @brief 立即启动轮询事务。
 *
 * @note 通常，设备不能同时启动（排队）轮询和中断事务。此外，如果另一个轮询事务未完成，则设备无法启动新的轮询事务。
 *
 * @param handle 使用spi_host_add_dev获得的设备句柄
 * @param trans_desc 要执行的事务的描述
 * @param ticks_to_wait 勾选等待，直到队列中有空间；当前仅支持portMAX_DELAY。
 *
 * @return
 *         -如果参数无效，则返回ESP_ERR_INVALID_ARG。如果在未获取总线时指定了SPI_TRANS_CS_KEEP_ACTIVE标志，则会发生这种情况（应首先调用“SPI_device_acquire_bus（）”）
 *         -ESP_ERR_TIMEOUT，如果设备在“ticks_to_wait”过期之前无法控制总线
 *         -如果分配支持DMA的临时缓冲区失败，则为ESP_ERR_NO_MEM
 *         -如果以前的事务未完成，则返回ESP_ERR_INVALID_STATE
 *         -成功时ESP_OK
 */
esp_err_t spi_device_polling_start(spi_device_handle_t handle, spi_transaction_t *trans_desc, TickType_t ticks_to_wait);


/**
 * @brief 轮询直到轮询事务结束。
 *
 * 在成功完成到给定设备的事务之前，此例程不会返回。任务未被阻止，但正忙着旋转以完成事务。
 *
 * @param handle 使用spi_host_add_dev获得的设备句柄
 * @param ticks_to_wait 勾选以等待返回的项目；使用portMAX_DELAY永不超时。
 * @return
 *         -如果参数无效，则为ESP_ERR_INVALID_ARG
 *         -如果交易在ticks_to_wait到期前无法完成，则为ESP_ERR_TIMEOUT
 *         -成功时ESP_OK
 */
esp_err_t spi_device_polling_end(spi_device_handle_t handle, TickType_t ticks_to_wait);


/**
 * @brief 发送轮询事务，等待其完成，并返回结果
 *
 * 此函数相当于先调用spi_device_polling_start（），然后调用spi_device_polling_end（）。如果仍有事务尚未完成，请不要使用此选项。
 *
 * @note 当多个任务访问同一SPI设备时，此函数不是线程安全的。通常，设备不能同时启动（排队）轮询和中断事务。
 *
 * @param handle 使用spi_host_add_dev获得的设备句柄
 * @param trans_desc 要执行的事务的描述
 * @return
 *         -如果参数无效，则为ESP_ERR_INVALID_ARG
 *         -成功时ESP_OK
 */
esp_err_t spi_device_polling_transmit(spi_device_handle_t handle, spi_transaction_t *trans_desc);


/**
 * @brief 占用SPI总线使设备进行连续事务。
 *
 * 所有其他设备的事务将被推迟，直到调用“spi_device_release_bus”。
 *
 * @note 该函数将等待所有现有事务发送完毕。
 *
 * @param device 占用总线的设备。
 * @param wait 设备占用总线之前等待的时间。当前必须设置为portMAX_DELAY。
 *
 * @return
 *      -ESP_ERR_INVALID_ARG:“等待”未设置为端口MAX_DELAY。
 *      -ESP_OK：成功。
 */
esp_err_t spi_device_acquire_bus(spi_device_handle_t device, TickType_t wait);

/**
 * @brief 释放设备占用的SPI总线。所有其他设备都可以开始发送事务。
 *
 * @param dev 释放总线的设备。
 */
void spi_device_release_bus(spi_device_handle_t dev);


/**
 * @brief 计算最接近所需频率的工作频率以及寄存器值。
 *
 * @param fapb apb时钟的频率应为“apb_CLK_FREQ”。
 * @param hz 期望的工作频率
 * @param duty_cycle spi时钟的占空比
 * @param reg_o 要在时钟寄存器中设置的值的输出，如果不需要，则为NULL。
 *
 * @deprecated 应用程序不应该关心寄存器。改为调用`spi_get_actual_clock``。
 *
 * @return 最适合的实际工作频率。
 */
int spi_cal_clock(int fapb, int hz, int duty_cycle, uint32_t *reg_o) __attribute__((deprecated));

/**
 * @brief 计算最接近所需频率的工作频率。
 *
 * @param fapb apb时钟的频率应为“apb_CLK_FREQ”。
 * @param hz 期望的工作频率
 * @param duty_cycle spi时钟的占空比
 *
 * @return 最适合的实际工作频率。
 */
int spi_get_actual_clock(int fapb, int hz, int duty_cycle);

/**
  * @brief 计算指定频率和设置的定时设置。
  *
  * @param gpio_is_used 如果使用GPIO矩阵，则为True；如果使用iomux引脚，则为False。
  * @param input_delay_ns 从SCLK启动边缘到MISO数据的输入延迟有效。
  * @param eff_clk spi_cl_clock的有效时钟频率（Hz）。
  * @param dummy_o 输出使用的伪位地址。如果不需要，则设置为NULL。
  * @param cycles_remain_o 剩余周期的地址（使用伪比特后）输出。
  *         --1如果剩余的周期太多，建议补偿半个时钟。
  *         -0如果没有剩余的周期或伪比特未被使用。
  *         -正值：周期建议补偿。
  *
  * @note 如果**dummy_o*不为零，则表示应在半双工模式下应用虚拟位，而全双工模式可能不起作用。
  */
void spi_get_timing(bool gpio_is_used, int input_delay_ns, int eff_clk, int *dummy_o, int *cycles_remain_o);

/**
  * @brief 获取当前配置的频率限制。SPI主机在该限制下工作正常，而超过该限制时，全双工模式和DMA将不工作，并且伪比特将应用于半双工模式。
  *
  * @param gpio_is_used 如果使用GPIO矩阵，则为True；如果使用本机引脚，则为False。
  * @param input_delay_ns 从SCLK启动边缘到MISO数据的输入延迟有效。
  * @return 电流配置的频率限制。
  */
int spi_get_freq_limit(bool gpio_is_used, int input_delay_ns);

#ifdef __cplusplus
}
#endif

