/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

// DO NOT USE THESE APIS IN ANY APPLICATIONS
// GDMA驱动程序不面向最终用户，但面向ESP-IDF开发人员。

#pragma once

#include <stdbool.h>
#include "soc/gdma_channel.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief GDMA通道手柄类型
 *
 */
typedef struct gdma_channel_t *gdma_channel_handle_t;

/**
 * @brief 具有DMA功能的外围设备的枚举
 * @note 某些外围设备可能在某些芯片上不可用，请参阅“soc_caps”。h`详细信息。
 *
 */
typedef enum {
    GDMA_TRIG_PERIPH_M2M,  /*!< GDMA触发器外围设备：M2M*/
    GDMA_TRIG_PERIPH_UART, /*!< GDMA触发外设：UART*/
    GDMA_TRIG_PERIPH_SPI,  /*!< GDMA触发外设：SPI*/
    GDMA_TRIG_PERIPH_I2S,  /*!< GDMA触发外围设备：I2S*/
    GDMA_TRIG_PERIPH_AES,  /*!< GDMA触发器外围设备：AES*/
    GDMA_TRIG_PERIPH_SHA,  /*!< GDMA触发器外围设备：SHA*/
    GDMA_TRIG_PERIPH_ADC,  /*!< GDMA触发外围设备：ADC*/
    GDMA_TRIG_PERIPH_DAC,  /*!< GDMA触发外围设备：DAC*/
    GDMA_TRIG_PERIPH_LCD,  /*!< GDMA触发器外围设备：LCD*/
    GDMA_TRIG_PERIPH_CAM,  /*!< GDMA触发器外围设备：CAM*/
    GDMA_TRIG_PERIPH_RMT,  /*!< GDMA触发器外围设备：RMT*/
} gdma_trigger_peripheral_t;

/**
 * @brief GDMA信道方向的枚举
 *
 */
typedef enum {
    GDMA_CHANNEL_DIRECTION_TX, /*!< GDMA信道方向：TX*/
    GDMA_CHANNEL_DIRECTION_RX, /*!< GDMA信道方向：RX*/
} gdma_channel_direction_t;

/**
 * @brief 用于分配GDMA通道的配置项集合
 *
 */
typedef struct {
    gdma_channel_handle_t sibling_chan; /*!< DMA同级通道句柄（NULL表示不需要同级）*/
    gdma_channel_direction_t direction; /*!< DMA通道方向*/
    struct {
        int reserve_sibling: 1; /*!< 如果设置了，DMA信道分配器将倾向于在新对中分配新信道，并保留兄弟信道以供将来使用*/
    } flags;
} gdma_channel_alloc_config_t;

/**
 * @brief GDMA传输能力
 *
 * @note 此结构中的对齐设置**并不是保证gdma驱动程序会处理不对齐的情况。实际上，GDMA驱动程序不知道上层使用的DMA缓冲区（地址和大小）。因此，上层负责处理缓冲区地址和大小。
 *
 */
typedef struct {
    size_t sram_trans_align;  /*!< SRAM中内存的DMA传输对齐，以字节为单位。驱动程序根据该值启用/禁用突发模式。0表示不需要对齐*/
    size_t psram_trans_align; /*!< PSRAM中内存的DMA传输对齐（字节）。驱动程序根据对齐值设置适当的突发块大小。0表示不需要对齐*/
} gdma_transfer_ability_t;

/**
 * @brief GDMA事件数据的类型
 *
 */
typedef struct {
    union {
        intptr_t rx_eof_desc_addr; /*!< RX信道的EOF描述符地址*/
        intptr_t tx_eof_desc_addr; /*!< TX信道的EOF描述符地址*/
    };
} gdma_event_data_t;

/**
 * @brief GDMA事件回调的类型
 * @param dma_chan GDMA通道句柄，从`GDMA_new_channel创建`
 * @param event_data GDMA事件数据
 * @param user_data 来自“gdma_register_tx_event_callbacks”或“gdma_register_rx_event_cllbacks”的用户注册数据`
 *
 * @return 回调函数返回后是否需要任务切换，这通常是由于回调唤醒了一些高优先级任务。
 *
 */
typedef bool (*gdma_event_callback_t)(gdma_channel_handle_t dma_chan, gdma_event_data_t *event_data, void *user_data);

/**
 * @brief 支持的GDMA TX回调组
 * @note 回调都在ISR环境下运行
 *
 */
typedef struct {
    gdma_event_callback_t on_trans_eof; /*!< 当TX引擎满足EOF描述符时调用*/
} gdma_tx_event_callbacks_t;

/**
 * @brief 支持的GDMA RX回调组
 * @note 回调都在ISR环境下运行
 *
 */
typedef struct {
    gdma_event_callback_t on_recv_eof; /*!< 当RX引擎满足EOF描述符时调用*/
} gdma_rx_event_callbacks_t;

/**
 * @brief GDMA发动机触发器类型
 * @note 建议使用`GDMA_MAKE_TRIGGER`初始化此结构。
 *
 */
typedef struct {
    gdma_trigger_peripheral_t periph; /*!< 将触发DMA操作的目标外设*/
    int instance_id;                  /*!< 外围实例ID。支持的ID列在“soc/gdma_channel”中。h’，例如SOC_GDMA_TRIG_PERIPH_ART0*/
} gdma_trigger_t;

/**
 * @brief 帮助程序宏初始化GDMA触发器
 * @note “peri”的值必须从“gdma_trigger_peripheral_t”枚举中选择。e、 g.GDMA_MAKE_TRIGGER（GDMA_TRIG_ERIPH_UART，0）
 *
 */
#define GDMA_MAKE_TRIGGER(peri, id) \
    (gdma_trigger_t) { .periph = peri, .instance_id = SOC_##peri##id }

/**
 * @brief 每个GDMA渠道可以应用的策略项集合
 *
 */
typedef struct {
    bool owner_check;      /*!< 如果设置/清除，DMA通道启用/禁用检查所有者有效性*/
    bool auto_update_desc; /*!< 如果设置/清除，DMA信道启用/禁用硬件自动更新描述符（仅TX信道）*/
} gdma_strategy_config_t;

/**
 * @brief 创建GDMA通道
 * @note 此API不会为分配的通道安装中断服务。如果需要中断服务，用户必须通过“GDMA_register_tx_event_callbacks”或“GDMA_register_rx_event_cllbacks”注册GDMA事件回调。
 *
 * @param[in] config 指向用于分配GDMA信道的配置集合的指针
 * @param[out] ret_chan 返回通道手柄
 * @return
 *      -ESP_OK:成功创建DMA通道
 *      -ESP_ERR_INVALID_ARG:由于参数无效，创建DMA通道失败
 *      -ESP_ERR_NO_MEM:创建DMA通道失败，因为内存不足
 *      -ESP_FAIL:由于其他错误，创建DMA通道失败
 */
esp_err_t gdma_new_channel(const gdma_channel_alloc_config_t *config, gdma_channel_handle_t *ret_chan);

/**
 * @brief 将GDMA通道连接到触发外围设备
 *
 * @note 建议使用帮助宏`GDMA_MAKE_TRIGGER`构造参数`trig_periph`。e、 g.GDMA_MAKE_TRIGGER（GDMA_TRIG_PERIPH_SHA，0）
 * @note 连接到外围设备也会自动重置DMA FIFO和FSM
 *
 * @param[in] dma_chan GDMA通道句柄，由`GDMA_new_channel分配`
 * @param[in] trig_periph GDMA触发器外围设备
 * @return
 *      -ESP_OK:成功连接GDMA频道
 *      -ESP_ERR_INVALID_ARG:由于参数无效，连接GDMA通道失败
 *      -ESP_ERR_INVALID_STATE:连接GDMA通道失败，因为DMA通道正在与其他外围设备一起工作
 *      -ESP_FAIL:由于其他错误，连接GDMA通道失败
 */
esp_err_t gdma_connect(gdma_channel_handle_t dma_chan, gdma_trigger_t trig_periph);

/**
 * @brief 断开GMA通道与外围设备的连接
 *
 * @param[in] dma_chan GDMA通道句柄，由`GDMA_new_channel分配`
 * @return
 *      -ESP_OK:成功断开GDMA通道
 *      -ESP_ERR_INVALID_ARG:由于参数无效，断开GDMA通道失败
 *      -ESP_ERR_INVALID_STATE:断开GDMA通道失败，因为DMA通道未连接到任何外围设备
 *      -ESP_FAIL:由于其他错误，断开DMA通道失败
 */
esp_err_t gdma_disconnect(gdma_channel_handle_t dma_chan);

/**
 * @brief 设置DMA通道传输能力
 *
 * @param[in] dma_chan GDMA通道句柄，由`GDMA_new_channel分配`
 * @param[in] ability 传输能力，例如对齐
 * @return
 *      -ESP_OK：成功设置DMA通道传输能力
 *      -ESP_ERR_INVALID_ARG:由于参数无效，设置DMA通道传输能力失败
 *      -ESP_FAIL:由于其他错误，设置DMA通道传输能力失败
 */
esp_err_t gdma_set_transfer_ability(gdma_channel_handle_t dma_chan, const gdma_transfer_ability_t *ability);

/**
 * @brief 为GDMA渠道应用渠道策略
 *
 * @param dma_chan GDMA通道句柄，由`GDMA_new_channel分配`
 * @param config GDMA渠道策略配置
 *      -ESP_OK：成功应用渠道策略
 *      -ESP_ERR_INVALID_ARG:由于参数无效，应用频道策略失败
 *      -ESP_FAIL:由于其他错误，应用频道策略失败
 */
esp_err_t gdma_apply_strategy(gdma_channel_handle_t dma_chan, const gdma_strategy_config_t *config);

/**
 * @brief 删除GDMA通道
 * @note 如果对同一个外设多次调用“gdma_new_channel”，请确保同时调用此API。
 *
 * @param[in] dma_chan GDMA通道句柄，由`GDMA_new_channel分配`
 * @return
 *      -ESP_OK:成功删除GDMA频道
 *      -ESP_ERR_INVALID_ARG:由于参数无效，删除GDMA通道失败
 *      -ESP_FAIL:由于其他错误，删除GDMA通道失败
 */
esp_err_t gdma_del_channel(gdma_channel_handle_t dma_chan);

/**
 * @brief 获取频道ID
 *
 * @note 此API打破了GDMA通道对象的封装。使用返回的通道ID，您甚至可以绕过所有其他GDMA驱动程序API，直接访问低级API。
 *
 * @param[in] dma_chan GDMA通道句柄，由`GDMA_new_channel分配`
 * @param[out] channel_id 返回的频道ID
 * @return
 *      -ESP_OK:成功获取GDMA频道ID
 *      -ESP_ERR_INVALID_ARG:由于参数无效，获取GDMA通道ID失败
 *      -ESP_FAIL:由于其他错误，获取GDMA频道ID失败
 */
esp_err_t gdma_get_channel_id(gdma_channel_handle_t dma_chan, int *channel_id);

/**
 * @brief 为TX信道设置GDMA事件回调
 * @note 此API将在内部为通道安装GDMA中断服务
 *
 * @param[in] dma_chan GDMA通道句柄，由`GDMA_new_channel分配`
 * @param[in] cbs 回调函数组
 * @param[in] user_data 用户数据，将直接传递给回调函数
 * @return
 *      -ESP_OK：成功设置事件回调
 *      -ESP_ERR_INVALID_ARG:由于参数无效，Set事件回调失败
 *      -ESP_FAIL:由于其他错误，设置事件回调失败
 */
esp_err_t gdma_register_tx_event_callbacks(gdma_channel_handle_t dma_chan, gdma_tx_event_callbacks_t *cbs, void *user_data);

/**
 * @brief 设置RX信道的GDMA事件回调
 * @note 此API将在内部为通道安装GDMA中断服务
 *
 * @param[in] dma_chan GDMA通道句柄，由`GDMA_new_channel分配`
 * @param[in] cbs 回调函数组
 * @param[in] user_data 用户数据，将直接传递给回调函数
 * @return
 *      -ESP_OK：成功设置事件回调
 *      -ESP_ERR_INVALID_ARG:由于参数无效，Set事件回调失败
 *      -ESP_FAIL:由于其他错误，设置事件回调失败
 */
esp_err_t gdma_register_rx_event_callbacks(gdma_channel_handle_t dma_chan, gdma_rx_event_callbacks_t *cbs, void *user_data);

/**
 * @brief 设置DMA描述符地址并启动引擎
 *
 * @param[in] dma_chan GDMA通道句柄，由`GDMA_new_channel分配`
 * @param[in] desc_base_addr 描述符的基地址（通常将描述符链接到链接或环中）
 * @return
 *      -ESP_OK:成功启动DMA引擎
 *      -ESP_ERR_INVALID_ARG:由于参数无效，启动DMA引擎失败
 *      -ESP_FAIL:由于其他错误，启动DMA引擎失败
 */
esp_err_t gdma_start(gdma_channel_handle_t dma_chan, intptr_t desc_base_addr);

/**
 * @brief 停止DMA引擎
 *
 * @param[in] dma_chan GDMA通道句柄，由`GDMA_new_channel分配`
 * @return
 *      -ESP_OK:成功停止DMA引擎
 *      -ESP_ERR_INVALID_ARG:由于参数无效，停止DMA引擎失败
 *      -ESP_FAIL:由于其他错误，停止DMA引擎失败
 */
esp_err_t gdma_stop(gdma_channel_handle_t dma_chan);

/**
 * @brief 让DMA引擎知道附加的描述符
 * @note 该API还可以恢复暂停的DMA引擎，确保在调用它之前已将新的描述符附加到描述符链。
 *
 * @param[in] dma_chan GDMA通道句柄，由`GDMA_new_channel分配`
 * @return
 *      -ESP_OK:成功向DMA引擎发送追加命令
 *      -ESP_ERR_INVALID_ARG:向DMA引擎发送追加命令失败，因为参数无效
 *      -ESP_FAIL:由于其他错误，向DMA引擎发送追加命令失败
 */
esp_err_t gdma_append(gdma_channel_handle_t dma_chan);

/**
 * @brief 重置DMA通道FIFO和内部有限状态机
 * @note 重置DMA通道不会中断与目标外围设备的连接
 *
 * @param[in] dma_chan GDMA通道句柄，由`GDMA_new_channel分配`
 * @return
 *      -ESP_OK:DMA通道重置成功
 *      -ESP_ERR_INVALID_ARG:由于参数无效，DMA通道重置失败
 *      -ESP_FAIL:由于其他错误，DMA通道重置失败
 */
esp_err_t gdma_reset(gdma_channel_handle_t dma_chan);

#ifdef __cplusplus
}
#endif

