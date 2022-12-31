/*
 * SPDX文件版权文本：2010-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

// 内部标头，不要在用户代码中使用

#pragma once

#include <esp_intr_alloc.h>
#include "driver/spi_common.h"
#include "freertos/FreeRTOS.h"
#include "hal/spi_types.h"
#include "esp_pm.h"

#ifdef __cplusplus
extern "C"
{
#endif


#ifdef CONFIG_SPI_MASTER_ISR_IN_IRAM
#define SPI_MASTER_ISR_ATTR IRAM_ATTR
#else
#define SPI_MASTER_ISR_ATTR
#endif

#ifdef CONFIG_SPI_MASTER_IN_IRAM
#define SPI_MASTER_ATTR IRAM_ATTR
#else
#define SPI_MASTER_ATTR
#endif


#define BUS_LOCK_DEBUG  0

#if BUS_LOCK_DEBUG
#define BUS_LOCK_DEBUG_EXECUTE_CHECK(x)  assert(x)
#else
#define BUS_LOCK_DEBUG_EXECUTE_CHECK(x)
#endif


struct spi_bus_lock_t;
struct spi_bus_lock_dev_t;
///SPI总线锁的句柄
typedef struct spi_bus_lock_t* spi_bus_lock_handle_t;
///SPI总线上一个设备的锁定句柄
typedef struct spi_bus_lock_dev_t* spi_bus_lock_dev_handle_t;

///后台操作控制功能
typedef void (*bg_ctrl_func_t)(void*);

///SPI总线的属性
typedef struct {
    spi_bus_config_t bus_cfg;   ///<用于初始化总线的配置
    uint32_t flags;             ///<总线的标志（属性）
    int max_transfer_sz;        ///<可发送的最大字节长度
    bool dma_enabled;           ///<是否启用DMA
    int tx_dma_chan;            ///<TX DMA信道，在ESP32和ESP32S2上，TX_DMA_chan和rx_DMA_can相同
    int rx_dma_chan;            ///<RX DMA信道，在ESP32和ESP32S2上，tx_DMA_chan和RX_DMA_can相同
    int dma_desc_num;           ///<dmadesc_tx或dmadesc_rx的DMA描述符编号。
    lldesc_t *dmadesc_tx;       ///<TX的DMA描述符数组
    lldesc_t *dmadesc_rx;       ///<RX的DMA描述符数组
    spi_bus_lock_handle_t lock;
#ifdef CONFIG_PM_ENABLE
    esp_pm_lock_handle_t pm_lock;   ///<电源管理锁
#endif
} spi_bus_attr_t;

///总线去初始化时调用Destructor。
typedef esp_err_t (*spi_destroy_func_t)(void*);


/**
 * @brief 尝试使用SPI外围设备
 *
 * 如果您的驱动程序想要管理SPI外设，请调用此命令。
 *
 * @param host 索赔的外围设备
 * @param source 调用方标识字符串。
 *
 * @note 此公共API已弃用。
 *
 * @return 如果成功申领外围设备，则为True；如果已声明外围设备，则为false。
 */
bool spicommon_periph_claim(spi_host_device_t host, const char* source);

/**
 * @brief 检查spi外围设备是否在使用中。
 *
 * @param host 要检查的外围设备。
 *
 * @note 此公共API已弃用。
 *
 * @return 如果正在使用，则为True，否则为false。
 */
bool spicommon_periph_in_use(spi_host_device_t host);

/**
 * @brief 返回SPI外围设备，以便其他驱动程序可以使用它。
 *
 * @param host 要返回的外围设备
 *
 * @note 此公共API已弃用。
 *
 * @return 如果成功返回外围设备，则为True；如果外围设备已经可以自由声明，则为false。
 */
bool spicommon_periph_free(spi_host_device_t host);

/**
 * @brief 用于SPI的Alloc DMA
 *
 * @param host_id                      SPI主机ID
 * @param dma_chan                     要使用的DMA通道
 * @param[out] out_actual_tx_dma_chan  实际TX DMA信道（如果您选择分配一个特定的DMA信道，这将是您之前分配的信道）
 * @param[out] out_actual_rx_dma_chan  实际RX DMA信道（如果您选择分配一个特定的DMA信道，这将是您之前分配的信道）
 *
 * @return
 *        -ESP_OK：成功时
 *        -ESP_ERR_NO_MEM：内存不足
 *        -ESP_ERR_NOT_FOUND：没有可用的DMA通道
 */
esp_err_t spicommon_dma_chan_alloc(spi_host_device_t host_id, spi_dma_chan_t dma_chan, uint32_t *out_actual_tx_dma_chan, uint32_t *out_actual_rx_dma_chan);

/**
 * @brief SPI的免费DMA
 *
 * @param host_id  SPI主机ID
 *
 * @return
 *        -ESP_OK：成功时
 */
esp_err_t spicommon_dma_chan_free(spi_host_device_t host_id);

/**
 * @brief 将SPI外设连接到GPIO引脚
 *
 * 此例程用于将SPI外设连接到参数中给出的IO焊盘和DMA通道。根据所请求的IO焊盘，可以使用IO_mux或GPIO矩阵进行布线。
 *
 * @note 此公共API已弃用。请调用`spi_bus_initialize``进行主总线初始化，调用`spi_slave_initialize ``进行从总线初始化。
 *
 * @param host 要路由的SPI外围设备
 * @param bus_config 指向详细描述GPIO引脚的spi_bus_config结构的指针
 * @param flags 设置SPICOMMON_BUSFLAG_*标志的组合，以确保引脚集能够执行某些功能：
 *              -``SPICOMMON_BUSFLAG_MASTER``：在主模式下初始化I/O
 *              -``SPICOMMON_BUSFLAG_SLAVE``：在从属模式下初始化I/O
 *              -``SPICOMMON_BUSFLAG_IOMUX_PINS``：引脚集应与控制器的IOMUX引脚匹配。
 *              -``SPICOMMON_BUSFLAG_SCLK``，``SPICOMON_BUSFLAG_MISO``，` ` SPICOMMON-BUSFLAG_MOSI``：确保SCLK/MISO/MOSI设置为有效的GPIO。同时根据模式检查输出能力。
 *              -``SPICOMMON_BUSFLAG_DUAL``：确保MISO和MOSI都具有输出能力，以便DIO模式能够工作。
 *              -``SPICOMMON_BUSFLAG_WPHD``确保WP和HD设置为有效的输出GPIO。
 *              -``SPICOMMON_BUSFLAG_QUAD``：``SPICOMMON_BUSFLAG_DUAL``和``SPICOMON_BUSFLAG_WPHD``的组合。
 *              -``SPICOMMON_BUSFLAG_IO4_IO7``：确保spi data4~spi data7设置为有效的输出GPIO。
 *              -``SPICOMMON_BUSFLAG_OCTAL``：``SPICOMON_BUSFLAG_QUAL``和`` SPICOMMON-BUSFLAG_IO4_IO7``的组合。
 * @param[out] flags_o 总线能力的SPICOMMON_BUSFLAG_*标志组合将写入该地址。如果不需要，则保留为NULL。
 *              -``SPICOMMON_BUSFLAG_IOMUX_PINS``：总线连接到IOMUX引脚。
 *              -``SPICOMMON_BUSFLAG_SCLK``，``SPICOMON_BUSFLAG_MISO``，` ` SPICOMMON-BUSFLAG_MOSI``：总线已连接CLK/MISO/MOSI。
 *              -``SPICOMMON_BUSFLAG_DUAL``：总线支持DIO模式。
 *              -``SPICOMMON_BUSFLAG_WPHD``总线已连接WP和HD。
 *              -``SPICOMMON_BUSFLAG_QUAD``：``SPICOMMON_BUSFLAG_DUAL``和``SPICOMON_BUSFLAG_WPHD``的组合。
 *              -``SPICOMMON_BUSFLAG_IO4_IO7``：总线已连接spi data4~spi data7。
 *              -``SPICOMMON_BUSFLAG_OCTAL``：``SPICOMON_BUSFLAG_QUAL``和`` SPICOMMON-BUSFLAG_IO4_IO7``的组合。
 * @return
 *         -如果参数无效，则为ESP_ERR_INVALID_ARG
 *         -成功时ESP_OK
 */
esp_err_t spicommon_bus_initialize_io(spi_host_device_t host, const spi_bus_config_t *bus_config, uint32_t flags, uint32_t *flags_o);

/**
 * @brief 释放SPI外设使用的IO
 *
 * @note 此公共API已弃用。请调用“spi_bus_free”进行主总线去初始化，调用“spi_slave_free”用于从总线去初始化。
 *
 * @param bus_cfg 定义要使用哪些引脚的总线配置结构。
 *
 * @return
 *         -如果参数无效，则为ESP_ERR_INVALID_ARG
 *         -成功时ESP_OK
 */
esp_err_t spicommon_bus_free_io_cfg(const spi_bus_config_t *bus_cfg);

/**
 * @brief 初始化特定SPI外设的芯片选择引脚
 *
 * @note 此公共API已弃用。请调用相应的设备初始化函数。
 *
 * @param host SPI外围设备
 * @param cs_io_num 要布线的GPIO引脚
 * @param cs_num 要路由的CS id
 * @param force_gpio_matrix 如果为真，CS将始终通过GPIO矩阵路由。如果为false，如果GPIO编号允许，则路由将通过IO_mux进行。
 */
void spicommon_cs_initialize(spi_host_device_t host, int cs_io_num, int cs_num, int force_gpio_matrix);

/**
 * @brief 释放芯片选择线
 *
 * @param cs_gpio_num CS gpio num免费
 *
 * @note 此公共API已弃用。
 */
void spicommon_cs_free_io(int cs_gpio_num);

/**
 * @brief 检查主机使用的所有引脚是否通过IOMUX。
 *
 * @param host SPI外围设备
 *
 * @note 此公共API已弃用。
 *
 * @return 如果任何引脚通过GPIO矩阵，则为假，否则为真。
 */
bool spicommon_bus_using_iomux(spi_host_device_t host);

/**
 * @brief 获取特定SPI主机的IRQ源
 *
 * @param host SPI主机
 *
 * @note 此公共API已弃用。
 *
 * @return 主机IRQ源
 */
int spicommon_irqsource_for_host(spi_host_device_t host);

/**
 * @brief 获取特定SPI DMA的IRQ源
 *
 * @param host SPI主机
 *
 * @note 此公共API已弃用。
 *
 * @return 主机IRQ源
 */
int spicommon_irqdma_source_for_host(spi_host_device_t host);

/**
 * 回调，在DMA引擎重置完成时调用
*/
typedef void(*dmaworkaround_cb_t)(void *arg);


/**
 * @brief 请求重置某个DMA通道
 *
 * @note 在ESP32中的某些（定义明确的）情况下（至少版本v.0和v.1），SPI DMA通道会被混淆。如果发生这种情况，可以通过重置SPI DMA硬件来解决。不幸的是，用于thsi的重置旋钮将重置其他DMA通道，因此只有在两个DMA通道都空闲时才能安全地进行重置。这些功能协调了这一点。
 *
 * 本质上，当需要重置时，驱动程序可以使用spicommon_dmaworkaround_req_reset请求重置。这应该使用用户提供的函数作为参数来调用。如果两个DMA通道都空闲，则此调用将重置DMA子系统并返回true。如果另一个DMA信道仍然忙，则返回false；然而，一旦其他DMA通道完成，它将重置DMA子系统并调用回调。然后应该使用回调来继续SPI驱动程序活动。
 *
 * @param dmachan 与需要重置的SPI主机关联的DMA通道
 * @param cb 在DMA通道无法立即重置的情况下回拨呼叫
 * @param arg 回调的参数
 *
 * @note 此公共API已弃用。
 *
 * @return 如果可以立即执行DMA重置，则为True。当它不能做到的时候是错误的；在这种情况下，当逻辑可以在重置之后执行重置时，将使用指定的参数调用回调。
 */
bool spicommon_dmaworkaround_req_reset(int dmachan, dmaworkaround_cb_t cb, void *arg);


/**
 * @brief 检查是否请求了DMA重置，但尚未完成
 *
 * @note 此公共API已弃用。
 *
 * @return 当请求DMA重置但尚未完成时为True。否则为False。
 */
bool spicommon_dmaworkaround_reset_in_progress(void);


/**
 * @brief 将DMA通道标记为空闲。
 *
 * 对该函数的调用告诉解决方法逻辑，该通道不会受到全局SPI DMA重置的影响。
 *
 * @note 此公共API已弃用。
 */
void spicommon_dmaworkaround_idle(int dmachan);

/**
 * @brief 将DMA通道标记为活动。
 *
 * 对该函数的调用告诉解决方法逻辑，该通道将受到全局SPI DMA重置的影响，不应尝试类似的重置。
 *
 * @note 此公共API已弃用。
 */
void spicommon_dmaworkaround_transfer_active(int dmachan);

/*******************************************************************************
 * 总线属性
 ******************************************************************************/
/**
 * @brief 设置主总线的总线锁，由启动代码调用。
 *
 * @param lock 主SPI总线使用的锁。
 */
void spi_bus_main_set_lock(spi_bus_lock_handle_t lock);

/**
 * @brief 获取指定SPI总线的属性。
 *
 * @param host_id 要获取属性的指定主机
 * @return （Const）指向属性的指针
 */
const spi_bus_attr_t* spi_bus_get_attr(spi_host_device_t host_id);

/**
 * @brief 将函数注册到已初始化的总线，以便在取消初始化总线时调用它。
 *
 * @param host_id   用于注册析构函数的SPI总线。
 * @param f         要注册的析构函数
 * @param arg       调用析构函数的参数
 * @return 始终为ESP_OK。
 */
esp_err_t spi_bus_register_destroy_func(spi_host_device_t host_id,
                                        spi_destroy_func_t f, void *arg);

/*******************************************************************************
 * SPI总线锁，用于SPI主控器（intr，轮询）传输、SPI闪存操作和闪存/psram缓存访问之间的仲裁。
 *
 * 非公共API。不要在应用程序中直接使用它。
 *
 * 有一个与SPI总线相对应的主锁，其中有几个设备（持有子锁）连接到它。强烈建议每个设备仅用于一个任务，以避免并发问题。
 *
 * 条款：
 * -BG操作（后台操作）是指一些不会立即/明确发送到任务中的事务。它可以是一些缓存访问或中断事务。
 *
 * -操作：例如，使用总线进行SPI事务。
 *
 * -获取处理器：允许使用总线的任务或ISR。如果没有采集处理器，则不会执行任何操作。如果处理器在不存在获取处理器的情况下请求获取处理器，则它将成为获取处理器，否则它必须等待获取处理器将角色移交给它。当完成其操作时，采集处理器将并且将仅在等待列表中分配一个采集处理器（如果不是空的）。
 *
 * -获取设备：唯一允许使用总线的设备。可以在BG或任务中执行操作。当没有采集设备时，只允许ISR作为采集处理器并在总线上执行操作。
 *
 * 当设备想要执行操作时，它可以：1.获取总线，并在任务中操作（例如，SPI主设备的轮询事务和SPI闪存操作）
 *
 * 2.请求BG操作。ISR将在适当的时候启用。
 *
 *    例如，如果任务想要发送中断事务，它将在任务中准备数据，调用“spi_bus_lock_bg_request”，并在ISR中处理发送。
 *
 * 3.当设备已获取总线时，也允许BG操作。调用“spi_bus_lock_bg_request”后，再次在任务中的操作之前调用“spi_bus_lock_wait_bg_done”，等待bg操作完成。
 *
 * 任何设备都可以尝试调用ISR（通过“spi_bus_lock_bg_request”）。当总线未被其他处理器获取时，ISR将被调用并立即成为获取处理器。任何设备也可以尝试获取总线（通过“spi_bus_lock_acquire_start”）。当未获取总线且没有激活请求时，设备将立即成为获取处理器。
 *
 * 获取处理器必须意识到其获取角色，并在其他任务或ISR无事可做时，将获取处理器适当地转移到其他任务或任务。在选择新的采集处理器之前，必须首先选择一个新的采集设备，如果有其他设备，则要求成为采集设备。之后，按以下顺序选择新的采集处理器：
 *
 * 1.如果有采集设备：1.1 ISR，如果采集设备有活动的BG请求1.2设备的任务，如果没有针对设备的活动BG请求2.ISR，如果没有采集设备，但任何BG请求都是活动的3.没有人成为采集处理器
 *
 * 该API也有助于SPI cs线路的仲裁。总线用cs_num参数初始化。当使用“spi_bus_lock_register_dev”将设备连接到总线时，它将根据给定的标志分配具有不同设备ID的设备。如果ID小于总线初始化时给定的cs_num，将返回错误。
 *
 * 用法：初始化：1.调用“spi_bus_init_lock”为总线注册锁。2.调用“spi_bus_lock_set_bg_control”为锁准备bg启用/禁用功能。3.为可能使用总线的每个设备调用“spi_bus_lock_register_dev”，正确存储返回的句柄，表示这些设备。
 *
 * *获取：1.当设备想要使用总线时，调用“spi_bus_lock_acquire_start”。2.调用“spi_bus_lock_touch”将总线标记为该设备已触摸。同时检查总线是否被其他设备触摸。3.（可选）在总线上执行某些操作…4.（可选）调用“spi_bus_lock_bg_request”通知并调用bg。有关ISR操作，请参见下文ISR。5.（可选）如果完成了“spi_bus_lock_bg_request”，则必须在再次接触总线之前调用“spi_bus _lock_wait_bg_done”，或执行以下步骤。6.调用“spi_bus_lock_acquire_end”将总线释放到其他设备。
 *
 * *ISR：1.在输入ISR时调用“spi_bus_lock_bg_entry”，根据返回值运行或跳过上一个操作的闭包。2.调用“spi_bus_lock_get_acquiring_dev”获取获取设备。如果没有采集设备，请调用“spi_bus_lock_bg_check_dev_acq”检查并更新新的采集设备。3.调用“spi_bus_lock_bg_check_dev_req”检查所需设备的请求。如果未请求所需的设备，则转至步骤5.4。检查并开始所需设备的操作，然后转至步骤6；否则，如果无法执行任何操作，请调用“spi_bus_lock_bg_clear_req”清除此设备的请求。如果调用了“spi_bus_lock_bg_clear_req”，并且没有bg请求处于活动状态，则转到步骤6.5。（可选）如果设备是采集设备，则转至步骤6，否则查找另一个所需设备，然后返回步骤3.6。调用“spi_bus _lock_bg_exit”尝试退出ISR。如果失败，请返回步骤2再次查找新请求。否则，退出ISR。
 *
 * *取消初始化（可选）：1.当不再需要时，为每个设备调用“spi_bus_lock_unregister_dev”。2.调用“spi_bus_deinit_lock”释放锁占用的资源。
 *
 * 一些技术细节：
 *
 * 每个设备的子锁都有自己的二进制信号量，这允许在调用“spi_bus_lock_acquire_start”或“spi_bus _lock_wait_bg_done”时，服务于此设备的任务（任务A）无法成为获取处理器时被阻止。如果被阻止，则必须有一个采集处理器（ISR或另一个任务（任务B））在总线上进行事务处理。之后，当ISR调用“spi_bus_lock_bg_resume_acquired_dev”或任务B调用“spi_bus_lock_acquire_end”时，任务A将被解除阻止并成为获取处理器。
 *
 * 当设备想要发送ISR事务时，应在准备好数据后调用“spi_bus_lock_bg_request”。此函数设置关键资源中的请求位。在以下情况下，ISR将被调用并成为新的采集处理器：
 *
 * 1.当没有获取处理器时，任务调用“spi_bus_lock_bg_request”；2.当任务是获取处理器时，任务调用“spi_bus_lock_bg_request”。然后将采集处理器移交给ISR；3.作为采集处理器的任务通过调用“spi_bus_lock_acquire_end”释放总线，ISR恰好是下一个采集处理器。
 *
 * ISR将检查（通过“spi_bus_lock_bg_check_dev_req”），并在确认相应设备的所有请求都得到服务后清除请求位（通过“spi_bus_lack_bg_clear_req”。请求位支持递归写入，这意味着任务在调用另一个“spi_bus_lock_bg_request”之前不需要等待“spi_buse_lock_bg_clear_req”。API将正确处理并发冲突。
 *
 * “spi_bus_lock_bg_exit”（与之前调用的“spi_bus _lock_bg_entry”一起）负责确保当ISR尝试放弃其获取处理器规则时，将发生以下情况之一：
 *
 * 1.ISR退出，中断被禁用时没有任何任务被解除阻止，且BG位均未激活。2.ISR退出，有一个获取设备，并且通过解锁任务，将获取处理器传递给为获取设备服务的任务。3.ISR未能退出，必须重试。
 ******************************************************************************/

#define DEV_NUM_MAX 6     ///<此锁支持的设备数

///锁配置结构
typedef struct {
    int host_id;    ///<SPI主机id
    int cs_num;     ///<主机的物理cs编号
} spi_bus_lock_config_t;

///子锁配置结构
typedef struct {
    uint32_t flags; ///<锁定标志，“SPI_BUS_lock_DEV_*”标志的OR ed。
#define SPI_BUS_LOCK_DEV_FLAG_CS_REQUIRED   BIT(0)  ///<设备需要物理CS引脚。
} spi_bus_lock_dev_config_t;

/*************通用*********************/
/**
 * 初始化SPI总线的锁。
 *
 * @param out_lock 把手到锁的输出
 * @return
 *  -ESP_ERR_NO_MEM：如果内存耗尽
 *  -ESP_OK：如果成功
 */
esp_err_t spi_bus_init_lock(spi_bus_lock_handle_t *out_lock, const spi_bus_lock_config_t *config);

/**
 * 释放SPI总线锁使用的资源。
 *
 * @note 在调用此功能之前，所有连接的设备都应该已注销。
 *
 * @param lock 锁把手松开。
 */
void spi_bus_deinit_lock(spi_bus_lock_handle_t lock);

/**
 * @brief 根据总线id获取相应的锁。
 *
 * @param host_id 获取锁的总线id
 * @return 锁把手
 */
spi_bus_lock_handle_t spi_bus_lock_get_by_id(spi_host_device_t host_id);

/**
 * @brief 配置SPI总线锁如何启用后台操作。
 *
 * @note 锁不会尝试停止后台操作，而是等待“spi_bus_lock_bg_resume_acquired_dev”指示的后台操作完成。
 *
 * @param lock 要设置的锁把手
 * @param bg_enable 启用功能
 * @param bg_disable 禁用函数，如果不需要，则设置为NULL
 * @param arg 要传递给启用/禁用函数的参数。
 */
void spi_bus_lock_set_bg_control(spi_bus_lock_handle_t lock, bg_ctrl_func_t bg_enable,
                                 bg_ctrl_func_t bg_disable, void *arg);

/**
 * 将设备连接到SPI总线锁上。返回句柄用于对连接的设备执行以下请求。
 *
 * @param lock 要连接的SPI总线锁
 * @param out_dev_handle 设备对应的输出手柄
 * @param flags 设备要求，SPI_BUS_LOCK_FLAG_*标志的位或
 *
 * @return
 *  -ESP_ERR_NOT_SUPPORTED：如果没有新设备的硬件资源。
 *  -ESP_ERR_NO_MEM：如果内存耗尽
 *  -ESP_OK：如果成功
 */
esp_err_t spi_bus_lock_register_dev(spi_bus_lock_handle_t lock,
                                    spi_bus_lock_dev_config_t *config,
                                    spi_bus_lock_dev_handle_t *out_dev_handle);

/**
 * 将设备与其总线分离并释放所使用的资源
 *
 * @param dev_handle 设备手柄。
 */
void spi_bus_lock_unregister_dev(spi_bus_lock_dev_handle_t dev_handle);

/**
 * @brief 获取设备的父总线锁
 *
 * @param dev_handle 获取总线锁的设备句柄
 * @return 总线锁手柄
 */
spi_bus_lock_handle_t spi_bus_lock_get_parent(spi_bus_lock_dev_handle_t dev_handle);

/**
 * @brief 获取锁的设备ID。
 *
 * 呼叫者应根据此ID分配CS管脚。
 *
 * @param dev_handle 获取ID的设备句柄
 * @return 设备的ID
 */
int spi_bus_lock_get_dev_id(spi_bus_lock_dev_handle_t dev_handle);

/**
 * @brief 设备请求触摸总线寄存器。只能由采集处理器调用。
 *
 * 同时检查寄存器是否被其他设备触摸。
 *
 * @param dev_handle 操作寄存器的设备手柄
 * @return 如果有其他设备接触SPI寄存器，则为true。呼叫者可能需要进行完整配置。否则返回false。
 */
bool spi_bus_lock_touch(spi_bus_lock_dev_handle_t dev_handle);

/*************正在获取服务*********************/
/**
 * 获取专用SPI总线。还将等待BG完成此设备的所有请求，然后再返回。
 *
 * 成功返回后，调用者成为获取处理器。
 *
 * @note 对于主闪存总线，将调用“bg_disable”来禁用缓存。
 *
 * @param dev_handle 获取设备请求的句柄。
 * @param wait 等待超时或成功的时间现在必须为`portMAX_DELAY`。
 * @return
 *  -ESP_OK：成功时
 *  -ESP_ERR_INVALID_ARG:超时不是端口MAX_DELAY
 */
esp_err_t spi_bus_lock_acquire_start(spi_bus_lock_dev_handle_t dev_handle, TickType_t wait);

/**
 * 释放获取的总线。将获取处理器传递给其他被阻止的处理器（任务或ISR），并使其被解除阻止或调用。
 *
 * 如果没有设备请求获取，则获取设备也可能变为空。在这种情况下，如果有任何BG请求，可以调用BG。
 *
 * 如果新获取设备具有BG请求，则BG将在BG完成新获取设备的所有请求之后在任务恢复之前被调用。否则，将立即恢复新采集设备的任务。
 *
 * @param dev_handle 释放总线的设备的句柄。
 * @return
 *  -ESP_OK：成功时
 *  -ESP_ERR_INVALID_STATE：设备尚未获取锁
 */
esp_err_t spi_bus_lock_acquire_end(spi_bus_lock_dev_handle_t dev_handle);

/**
 * 获取获取总线的设备。
 *
 * @note 返回值不稳定，因为调用此函数时采集处理器可能会发生变化。
 *
 * @param lock 锁定SPI总线以获取采集设备。
 * @return 与获取设备对应的参数，请参见“spi_bus_lock_register_dev”。
 */
spi_bus_lock_dev_handle_t spi_bus_lock_get_acquiring_dev(spi_bus_lock_handle_t lock);

/*************BG（后台，用于ISR或缓存）服务*********************/
/**
 * 由设备调用以请求BG操作。
 *
 * 根据总线锁定状态，BG操作可通过此调用恢复，或等待直到允许BG操作。
 *
 * 由bg中的“spi_bus_lock_bg_clear_req”清除。
 *
 * @param dev_handle 请求BG操作的设备。
 * @return 始终ESP_OK
 */
esp_err_t spi_bus_lock_bg_request(spi_bus_lock_dev_handle_t dev_handle);

/**
 * 等待ISR完成采集设备的所有BG操作。如果此设备的任何“spi_bus_lock_bg_request”在“spi_bus _lock_acquire_start”之后被调用，则必须在任务中的任何操作之前调用此函数。
 *
 * @note 只能在该设备获取总线时调用。
 *
 * @param dev_handle 获取总线的设备的句柄。
 * @param wait 等待超时或成功的时间现在必须为`portMAX_DELAY`。
 * @return
 *  -ESP_OK：成功时
 *  -ESP_ERR_INVALID_STATE:设备不是采集总线。
 *  -ESP_ERR_INVALID_ARG:超时不是端口MAX_DELAY。
 */
esp_err_t spi_bus_lock_wait_bg_done(spi_bus_lock_dev_handle_t dev_handle, TickType_t wait);

/**
 * 处理上次操作的中断和关闭。当ISR充当采集处理器时，应在ISR开始时调用。
 *
 * @param lock SPI总线锁
 *
 * @return 如果ISR已经接触到硬件，则应首先关闭最后一个操作；否则，如果ISR刚刚开始在硬件上运行，则应跳过关闭。
 */
bool spi_bus_lock_bg_entry(spi_bus_lock_handle_t lock);

/**
 * 处理其他采集设备的调度，并控制硬件运行状态。
 *
 * 如果未找到BG请求，请使用“wip=false”进行调用。此函数将返回false，表示当前采集设备（如果没有采集设备，则为所有设备）存在BG请求，ISR需要重试。否则，如果存在，可以调度新的采集处理器（取消锁定任务），并返回true。
 *
 * 否则，如果在此ISR中启动BG请求，则使用“wip=true”进行调用，该函数将启用中断，以便在请求完成时再次调用ISR。
 *
 * 该函数是安全的，当ISR刚刚失去其获取处理器角色，但尚未退出时，仍应调用该函数。
 *
 * @note 此功能不会更改采集设备。ISR调用“spi_bus_lock_bg_update_acquiring”以检查新的获取设备，此时需要在其他设备之前为获取设备提供服务。
 *
 * @param lock SPI总线锁定。
 * @param wip 退出ISR时是否正在执行操作。
 * @param do_yield[out] 不需要让步时不触摸，否则设置为pdTRUE。
 * @return 如果需要重试，则为false，表示存在挂起的BG请求。否则为true，允许退出ISR。
 */
bool spi_bus_lock_bg_exit(spi_bus_lock_handle_t lock, bool wip, BaseType_t* do_yield);

/**
 * 检查是否有设备请求获取设备，并推荐下一次操作所需的设备。
 *
 * @note 当ISR充当采集处理器且没有采集设备时，必须调用。
 *
 * @param lock SPI总线锁定。
 * @param out_dev_lock 下一次操作的推荐设备。当发现新的采集设备时，它是新的，否则是具有活动BG请求的设备。
 *
 * @return 如果ISR需要退出（新的获取设备没有活动BG请求，或者当没有获取设备时，所有设备没有活动的BG请求），则为true，否则为false。
 */
bool spi_bus_lock_bg_check_dev_acq(spi_bus_lock_handle_t lock, spi_bus_lock_dev_handle_t *out_dev_lock);

/**
 * 检查设备是否有BG请求。当ISR充当采集处理器时，必须调用。
 *
 * @note 这是不稳定的，当任务请求BG操作时（通过“spi_bus_lock_BG_request”），可能再次变为真。
 *
 * @param dev_lock 要检查的设备。
 * @return 如果设备有BG请求，则为true，否则为false。
 */
bool spi_bus_lock_bg_check_dev_req(spi_bus_lock_dev_handle_t dev_lock);

/**
 * 清除服务后设备的未决BG操作请求。当ISR充当采集处理器时，必须调用。
 *
 * @note 当返回值为真时，ISR将失去获取处理器角色。然后，当ISR再次成为采集处理器时，在调用所有其他需要调用的函数之前，必须调用并检查“spi_bus_lock_bg_exit”。
 *
 * @param dev_handle 为其请求提供服务的设备。
 * @return 如果采集设备没有挂起的请求，则为True；如果没有采集设备，则为所有设备。否则为假。当返回值为真时，ISR不再是采集处理器。
 */
bool spi_bus_lock_bg_clear_req(spi_bus_lock_dev_handle_t dev_lock);

/**
 * 检查是否有任何活动的BG请求。
 *
 * @param lock SPI总线锁定。
 * @return 如果任何设备具有活动BG请求，则为true，否则为false。
 */
bool spi_bus_lock_bg_req_exist(spi_bus_lock_handle_t lock);

/*******************************************************************************
 * 操作系统初始化主芯片锁的变量和API
 ******************************************************************************/
///主母线的锁
extern const spi_bus_lock_handle_t g_main_spi_bus_lock;

/**
 * @brief 初始化芯片启动期间调用的主SPI总线。
 *
 * @return 始终ESP_OK
 */
esp_err_t spi_bus_lock_init_main_bus(void);

///主闪光灯装置的锁
extern const spi_bus_lock_dev_handle_t g_spi_lock_main_flash_dev;

/**
 * @brief 初始化芯片启动期间调用的主闪存设备。
 *
 * @return
 *      -ESP_OK：如果成功
 *      -ESP_ERR_NO_MEM：内存耗尽
 */
esp_err_t spi_bus_lock_init_main_dev(void);


#ifdef __cplusplus
}
#endif

