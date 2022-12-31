/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#ifndef _TEST_COMMON_SPI_H_
#define _TEST_COMMON_SPI_H_

#include <esp_types.h>
#include "driver/spi_master.h"
#include "freertos/FreeRTOS.h"
#include "freertos/ringbuf.h"
#include "freertos/task.h"
#include "unity.h"
#include "test_utils.h"
#include <string.h>
#include "param_test.h"
#include "soc/io_mux_reg.h"
#include "sdkconfig.h"
#include "soc/spi_periph.h"

// 使用标头的所有测试都应尽可能使用此定义，
// 从而在将来可以容易地更换工作主机。
#if CONFIG_IDF_TARGET_ESP32
#define TEST_SPI_HOST           SPI2_HOST
#define TEST_SLAVE_HOST         SPI3_HOST

#define PIN_NUM_MISO            SPI2_IOMUX_PIN_NUM_MISO
#define PIN_NUM_MOSI            SPI2_IOMUX_PIN_NUM_MOSI
#define PIN_NUM_CLK             SPI2_IOMUX_PIN_NUM_CLK
#define PIN_NUM_CS              SPI2_IOMUX_PIN_NUM_CS
#define PIN_NUM_WP              SPI2_IOMUX_PIN_NUM_WP
#define PIN_NUM_HD              SPI2_IOMUX_PIN_NUM_HD

#define MASTER_IOMUX_PIN_MISO   SPI2_IOMUX_PIN_NUM_MISO
#define MASTER_IOMUX_PIN_MOSI   SPI2_IOMUX_PIN_NUM_MOSI
#define MASTER_IOMUX_PIN_SCLK   SPI2_IOMUX_PIN_NUM_CLK
#define MASTER_IOMUX_PIN_CS     SPI2_IOMUX_PIN_NUM_CS
#define MASTER_IOMUX_PIN_WP     SPI2_IOMUX_PIN_NUM_WP
#define MASTER_IOMUX_PIN_HD     SPI2_IOMUX_PIN_NUM_HD

#define SLAVE_IOMUX_PIN_MISO    SPI3_IOMUX_PIN_NUM_MISO
#define SLAVE_IOMUX_PIN_MOSI    SPI3_IOMUX_PIN_NUM_MOSI
#define SLAVE_IOMUX_PIN_SCLK    SPI3_IOMUX_PIN_NUM_CLK
#define SLAVE_IOMUX_PIN_CS      SPI3_IOMUX_PIN_NUM_CS
#define SLAVE_IOMUX_PIN_WP      SPI3_IOMUX_PIN_NUM_WP
#define SLAVE_IOMUX_PIN_HD      SPI3_IOMUX_PIN_NUM_HD

#define UNCONNECTED_PIN         27
#define INPUT_ONLY_PIN          34
#define GPIO_DELAY              (12.5*2)
#define ESP_SPI_SLAVE_TV        (12.5*3.5)
#define WIRE_DELAY              12.5

#elif CONFIG_IDF_TARGET_ESP32S2 || CONFIG_IDF_TARGET_ESP32S3
#define TEST_SPI_HOST           SPI2_HOST
#define TEST_SLAVE_HOST         SPI3_HOST

#define PIN_NUM_MISO            SPI2_IOMUX_PIN_NUM_MISO
#define PIN_NUM_MOSI            SPI2_IOMUX_PIN_NUM_MOSI
#define PIN_NUM_CLK             SPI2_IOMUX_PIN_NUM_CLK
#define PIN_NUM_CS              SPI2_IOMUX_PIN_NUM_CS
#define PIN_NUM_WP              SPI2_IOMUX_PIN_NUM_WP
#define PIN_NUM_HD              SPI2_IOMUX_PIN_NUM_HD

#define MASTER_IOMUX_PIN_MISO   SPI2_IOMUX_PIN_NUM_MISO
#define MASTER_IOMUX_PIN_MOSI   SPI2_IOMUX_PIN_NUM_MOSI
#define MASTER_IOMUX_PIN_SCLK   SPI2_IOMUX_PIN_NUM_CLK
#define MASTER_IOMUX_PIN_CS     SPI2_IOMUX_PIN_NUM_CS
#define MASTER_IOMUX_PIN_WP     SPI2_IOMUX_PIN_NUM_WP
#define MASTER_IOMUX_PIN_HD     SPI2_IOMUX_PIN_NUM_HD

#define SLAVE_IOMUX_PIN_MISO    -1
#define SLAVE_IOMUX_PIN_MOSI    -1
#define SLAVE_IOMUX_PIN_SCLK    -1
#define SLAVE_IOMUX_PIN_CS      -1
#define SLAVE_IOMUX_PIN_NUM_WP  -1
#define SLAVE_IOMUX_PIN_NUM_HD  -1

#define UNCONNECTED_PIN         41
#define INPUT_ONLY_PIN          46
#define GPIO_DELAY              0
#define ESP_SPI_SLAVE_TV        0
#define WIRE_DELAY              12.5

#elif CONFIG_IDF_TARGET_ESP32C3
//注：在esp32c3上，只有1个GPSPI控制器，因此应禁用单板上的主从测试
#define TEST_SPI_HOST           SPI2_HOST
#define TEST_SLAVE_HOST         SPI2_HOST

#define PIN_NUM_MISO            SPI2_IOMUX_PIN_NUM_MISO
#define PIN_NUM_MOSI            SPI2_IOMUX_PIN_NUM_MOSI
#define PIN_NUM_CLK             SPI2_IOMUX_PIN_NUM_CLK
#define PIN_NUM_CS              SPI2_IOMUX_PIN_NUM_CS
#define PIN_NUM_WP              SPI2_IOMUX_PIN_NUM_WP
#define PIN_NUM_HD              SPI2_IOMUX_PIN_NUM_HD

#define SLAVE_IOMUX_PIN_MISO    SPI2_IOMUX_PIN_NUM_MISO
#define SLAVE_IOMUX_PIN_MOSI    SPI2_IOMUX_PIN_NUM_MOSI
#define SLAVE_IOMUX_PIN_SCLK    SPI2_IOMUX_PIN_NUM_CLK
#define SLAVE_IOMUX_PIN_CS      SPI2_IOMUX_PIN_NUM_CS

#define MASTER_IOMUX_PIN_MISO   SPI2_IOMUX_PIN_NUM_MISO
#define MASTER_IOMUX_PIN_MOSI   SPI2_IOMUX_PIN_NUM_MOSI
#define MASTER_IOMUX_PIN_SCLK   SPI2_IOMUX_PIN_NUM_CLK
#define MASTER_IOMUX_PIN_CS     SPI2_IOMUX_PIN_NUM_CS

#define GPIO_DELAY              0
#define ESP_SPI_SLAVE_TV        0
#define WIRE_DELAY              12.5
#endif

#define GET_DMA_CHAN(HOST)      (HOST)

#define TEST_DMA_CHAN_MASTER    GET_DMA_CHAN(TEST_SPI_HOST)
#define TEST_DMA_CHAN_SLAVE     GET_DMA_CHAN(TEST_SLAVE_HOST)


#define FUNC_SPI    1
#define FUNC_GPIO   PIN_FUNC_GPIO

//延迟信息
#define TV_INT_CONNECT_GPIO     (ESP_SPI_SLAVE_TV+GPIO_DELAY)
#define TV_INT_CONNECT          (ESP_SPI_SLAVE_TV)
//当连接到另一个板时，延迟通常增加12.5ns
#define TV_WITH_ESP_SLAVE_GPIO  (TV_INT_CONNECT_GPIO+WIRE_DELAY)
#define TV_WITH_ESP_SLAVE       (TV_INT_CONNECT+WIRE_DELAY)

//目前，ESP32从机仅支持20MHz，但在同一板上支持40MHz
#define ESP_SPI_SLAVE_MAX_FREQ      SPI_MASTER_FREQ_20M
#define ESP_SPI_SLAVE_MAX_FREQ_SYNC SPI_MASTER_FREQ_40M

#define MAX_TEST_SIZE   16  ///<在本测试中，我们运行多个事务，这是可以运行的最大事务
#define PSET_NAME_LEN   30  ///<每个参数集名称的长度

//测试低频、高频，直到最坏情况下的频率极限（两个GPIO）
#define TEST_FREQ_DEFAULT(){    \
        1*1000*1000,            \
        SPI_MASTER_FREQ_8M ,    \
        SPI_MASTER_FREQ_9M ,    \
        SPI_MASTER_FREQ_10M,    \
        SPI_MASTER_FREQ_11M,    \
        SPI_MASTER_FREQ_13M,    \
        SPI_MASTER_FREQ_16M,    \
        SPI_MASTER_FREQ_20M,    \
        SPI_MASTER_FREQ_26M,    \
        SPI_MASTER_FREQ_40M,    \
        SPI_MASTER_FREQ_80M,    \
        0,\
    }

//测试的默认总线配置
#define SPI_BUS_TEST_DEFAULT_CONFIG() {\
        .miso_io_num=PIN_NUM_MISO, \
        .mosi_io_num=PIN_NUM_MOSI,\
        .sclk_io_num=PIN_NUM_CLK,\
        .quadwp_io_num=-1,\
        .quadhd_io_num=-1\
    }

//主设备的默认设备配置
#define SPI_DEVICE_TEST_DEFAULT_CONFIG()    {\
        .clock_speed_hz=10*1000*1000,\
        .mode=0,\
        .spics_io_num=PIN_NUM_CS,\
        .queue_size=16,\
        .pre_cb=NULL,  \
        .cs_ena_pretrans = 0,\
        .cs_ena_posttrans = 0,\
        .input_delay_ns = 62.5,\
    }

//从属设备的默认设备配置
#define SPI_SLAVE_TEST_DEFAULT_CONFIG() {\
        .mode=0,\
        .spics_io_num=PIN_NUM_CS,\
        .queue_size=3,\
        .flags=0,\
    }

typedef enum {
    FULL_DUPLEX = 0,
    HALF_DUPLEX_MISO = 1,
    HALF_DUPLEX_MOSI = 2,
} spi_dup_t;

/*--------从属任务相关的内容-----------*/
typedef struct {
    uint32_t len;
    uint8_t* tx_start;
    uint8_t data[1];
} slave_rxdata_t;

typedef struct {
    uint32_t len;
    const uint8_t *start;
} slave_txdata_t;

typedef struct {
    spi_host_device_t spi;
    RingbufHandle_t data_received;
    QueueHandle_t data_to_send;
} spi_slave_task_context_t;

// 主设备和从设备的测试数据
extern uint8_t spitest_master_send[];
extern uint8_t spitest_slave_send[];

//主应用程序和从应用程序的标签
extern const char MASTER_TAG[];
extern const char SLAVE_TAG[];

//参数集定义
typedef struct {
    const char pset_name[PSET_NAME_LEN];
    /*The 测试工作直到频率低于，将频率设置为更高，并删除驱动器中的检查，以了解系统的运行速度。
     */
    const int *freq_list;     // 测试频率列表，以0结尾
    int freq_limit;     //freq大于（不等于）此值将被忽略
    spi_dup_t dup;
    int mode;
    bool length_aligned;
    int test_size;

    int master_limit;   // 主设备禁用伪位并丢弃此频率上的读数
    bool master_iomux;
    int master_dma_chan;

    bool slave_iomux;
    int slave_dma_chan;
    int slave_tv_ns;
    bool slave_unaligned_addr;
} spitest_param_set_t;

//参数化测试的上下文定义
typedef struct {
    uint8_t master_rxbuf[480];
    spi_transaction_t master_trans[MAX_TEST_SIZE];
    TaskHandle_t handle_slave;
    spi_slave_task_context_t slave_context;
    slave_txdata_t slave_trans[MAX_TEST_SIZE];
} spitest_context_t;

// 填充spitest_param_set_t的默认值
void spitest_def_param(void* arg);

// 从属任务的函数
esp_err_t init_slave_context(spi_slave_task_context_t *context);
void deinit_slave_context(spi_slave_task_context_t *context);
void spitest_slave_task(void* arg);

//从设备调用，拉起从设备使用的所有引脚
void slave_pull_up(const spi_bus_config_t* cfg, int spics_io_num);

// 以访问预定义事务的数据。
void spitest_init_transactions(const spitest_param_set_t *cfg, spitest_context_t* context);

// 打印事务中的数据
void spitest_master_print_data(spi_transaction_t *t, int rxlength);
void spitest_slave_print_data(slave_rxdata_t *t, bool print_rxdata);
// 检查主从数据是否匹配
esp_err_t spitest_check_data(int len, spi_transaction_t *master_t, slave_rxdata_t *slave_t, bool check_master_data, bool check_slave_len, bool check_slave_data);

#define spitest_cmp_or_dump(expected, actual, len) ({\
    int r = memcmp(expected, actual, len);\
    if (r != 0) {\
        ESP_LOG_BUFFER_HEXDUMP("expected", expected, len, ESP_LOG_INFO);\
        ESP_LOG_BUFFER_HEXDUMP("actual", actual, len, ESP_LOG_WARN);\
        TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, actual, len);\
    }\
    r;\
})

static inline int get_trans_len(spi_dup_t dup, spi_transaction_t *master_t)
{
    if (dup!=HALF_DUPLEX_MISO) {
        return master_t->length;
    } else {
        return master_t->rxlength;
    }
}
//从总线上移除设备并释放总线
void master_free_device_bus(spi_device_handle_t spi);

//当将多个函数分配给同一管脚时，使用此函数修复输出源
void spitest_gpio_output_sel(uint32_t gpio_num, int func, uint32_t signal_idx);

//当将多个函数分配给同一管脚时，使用此函数修复输入源
void spitest_gpio_input_sel(uint32_t gpio_num, int func, uint32_t signal_idx);

//注意此cs_num是所连接设备的ID，
//则第一和第二设备的cs_num分别为0和1。
void same_pin_func_sel(spi_bus_config_t bus, spi_device_interface_config_t dev, uint8_t cs_num);

/**
 * 此函数用于获取双板测试中使用的tx_buffer
 */
void get_tx_buffer(uint32_t seed, uint8_t *master_send_buf, uint8_t *slave_send_buf, int send_buf_size);
#endif  //_TEST_COMMON_SPI_H_

