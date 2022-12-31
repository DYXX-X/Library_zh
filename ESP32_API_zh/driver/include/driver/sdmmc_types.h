/*
 * SPDX文件版权文本：2006 Uwe Stuehler<uwe@openbsd.org>
 *
 * SPDX许可证标识符：ISC
 *
 * SPDX文件撰稿人：2016-2021 Espressif Systems（Shanghai）CO LTD
 */
/*
 * 版权所有（c）2006 Uwe Stuehler<uwe@openbsd.org>
 *
 * 特此授予出于任何目的使用、复制、修改和分发本软件的许可，无论是否收取费用，前提是上述版权声明和本许可声明出现在所有副本中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _SDMMC_TYPES_H_
#define _SDMMC_TYPES_H_

#include <stdint.h>
#include <stddef.h>
#include "esp_err.h"
#include "freertos/FreeRTOS.h"

/**
 * SD卡特定数据寄存器中的解码值
 */
typedef struct {
    int csd_ver;                /*!< CSD结构格式*/
    int mmc_ver;                /*!< MMC版本（CID格式）*/
    int capacity;               /*!< 扇区总数*/
    int sector_size;            /*!< 扇区大小（字节）*/
    int read_block_len;         /*!< 读取的块长度*/
    int card_command_class;     /*!< SD卡命令类*/
    int tr_speed;               /*!< 最大传输速度*/
} sdmmc_csd_t;

/**
 * SD卡ID识别寄存器中的解码值
 */
typedef struct {
    int mfg_id;     /*!< 制造商识别号*/
    int oem_id;     /*!< OEM/产品识别号*/
    char name[8];   /*!< 产品名称（MMC v1最长）*/
    int revision;   /*!< 产品修订版*/
    int serial;     /*!< 产品序列号*/
    int date;       /*!< 制造日期*/
} sdmmc_cid_t;

/**
 * SD配置寄存器中的解码值
 */
typedef struct {
    int sd_spec;    /*!< SD物理层规范版本，由卡报告*/
    int bus_width;  /*!< 板卡支持的总线宽度：BIT（0）-1位总线，BIT（2）-4位总线*/
} sdmmc_scr_t;

/**
 * 扩展卡特定数据的解码值
 */
typedef struct {
    uint8_t power_class;    /*!< 卡使用的功率等级*/
} sdmmc_ext_csd_t;

/**
 * SD/MMC命令响应缓冲区
 */
typedef uint32_t sdmmc_response_t[4];

/**
 * SD SWITCH_UNC响应缓冲区
 */
typedef struct {
    uint32_t data[512 / 8 / sizeof(uint32_t)];  /*!< 响应数据*/
} sdmmc_switch_func_rsp_t;

/**
 * SD/MMC命令信息
 */
typedef struct {
        uint32_t opcode;            /*!< SD或MMC命令索引*/
        uint32_t arg;               /*!< SD/MMC命令参数*/
        sdmmc_response_t response;  /*!< 响应缓冲器*/
        void* data;                 /*!< 要发送或读入的缓冲区*/
        size_t datalen;             /*!< 数据缓冲区长度*/
        size_t blklen;              /*!< 块体长度*/
        int flags;                  /*!< 见下文*/
/**@秒*/
#define SCF_ITSDONE      0x0001     /*!< 命令已完成*/
#define SCF_CMD(flags)   ((flags) & 0x00f0)
#define SCF_CMD_AC       0x0000
#define SCF_CMD_ADTC     0x0010
#define SCF_CMD_BC       0x0020
#define SCF_CMD_BCR      0x0030
#define SCF_CMD_READ     0x0040     /*!< read命令（需要数据）*/
#define SCF_RSP_BSY      0x0100
#define SCF_RSP_136      0x0200
#define SCF_RSP_CRC      0x0400
#define SCF_RSP_IDX      0x0800
#define SCF_RSP_PRESENT  0x1000
/* 响应类型*/
#define SCF_RSP_R0       0 /*!< 没有一个*/
#define SCF_RSP_R1       (SCF_RSP_PRESENT|SCF_RSP_CRC|SCF_RSP_IDX)
#define SCF_RSP_R1B      (SCF_RSP_PRESENT|SCF_RSP_CRC|SCF_RSP_IDX|SCF_RSP_BSY)
#define SCF_RSP_R2       (SCF_RSP_PRESENT|SCF_RSP_CRC|SCF_RSP_136)
#define SCF_RSP_R3       (SCF_RSP_PRESENT)
#define SCF_RSP_R4       (SCF_RSP_PRESENT)
#define SCF_RSP_R5       (SCF_RSP_PRESENT|SCF_RSP_CRC|SCF_RSP_IDX)
#define SCF_RSP_R5B      (SCF_RSP_PRESENT|SCF_RSP_CRC|SCF_RSP_IDX|SCF_RSP_BSY)
#define SCF_RSP_R6       (SCF_RSP_PRESENT|SCF_RSP_CRC|SCF_RSP_IDX)
#define SCF_RSP_R7       (SCF_RSP_PRESENT|SCF_RSP_CRC|SCF_RSP_IDX)
/* 特殊标志*/
#define SCF_WAIT_BUSY    0x2000     /*!< 返回前等待卡忙信号完成*/
/**@结束秒*/
        esp_err_t error;            /*!< 传输返回错误*/
        int timeout_ms;             /*!< 响应超时（毫秒）*/
} sdmmc_command_t;

/**
 * SD/MMC主机描述
 *
 * 该结构定义了SD/MMC主机的属性和上层可以使用的SD/MMC的功能。
 */
typedef struct {
    uint32_t flags;             /*!< 定义主机属性的标志*/
#define SDMMC_HOST_FLAG_1BIT    BIT(0)      /*!< 主机支持单线SD和MMC协议*/
#define SDMMC_HOST_FLAG_4BIT    BIT(1)      /*!< 主机支持4线SD和MMC协议*/
#define SDMMC_HOST_FLAG_8BIT    BIT(2)      /*!< 主机支持8线MMC协议*/
#define SDMMC_HOST_FLAG_SPI     BIT(3)      /*!< 主机支持SPI协议*/
#define SDMMC_HOST_FLAG_DDR     BIT(4)      /*!< 主机支持SD/MMC的DDR模式*/
#define SDMMC_HOST_FLAG_DEINIT_ARG BIT(5)      /*!< 使用slot参数调用host“deinit”函数*/
    int slot;                   /*!< 插槽号，要传递给主机函数*/
    int max_freq_khz;           /*!< 主机支持的最大频率*/
#define SDMMC_FREQ_DEFAULT      20000       /*!< SD/MMC默认速度（受时钟分频器限制）*/
#define SDMMC_FREQ_HIGHSPEED    40000       /*!< SD高速（受时钟分频器限制）*/
#define SDMMC_FREQ_PROBING      400         /*!< SD/MMC探测速度*/
#define SDMMC_FREQ_52M          52000       /*!< MMC 52MHz速度*/
#define SDMMC_FREQ_26M          26000       /*!< MMC 26MHz速度*/
    float io_voltage;           /*!< 控制器使用的I/O电压（不支持电压切换）*/
    esp_err_t (*init)(void);    /*!< 初始化驱动程序的主机功能*/
    esp_err_t (*set_bus_width)(int slot, size_t width);    /*!< 设置总线宽度的主机功能*/
    size_t (*get_bus_width)(int slot); /*!< 获取总线宽度的主机函数*/
    esp_err_t (*set_bus_ddr_mode)(int slot, bool ddr_enable); /*!< 设置DDR模式的主机功能*/
    esp_err_t (*set_card_clk)(int slot, uint32_t freq_khz); /*!< 设置板卡时钟频率的主机功能*/
    esp_err_t (*do_transaction)(int slot, sdmmc_command_t* cmdinfo);    /*!< 执行事务的主机函数*/
    union {
        esp_err_t (*deinit)(void);  /*!< 主机函数来取消初始化驱动程序*/
        esp_err_t (*deinit_p)(int slot);  /*!< 用“slot”调用的主机函数去初始化驱动程序*/
    };
    esp_err_t (*io_int_enable)(int slot); /*!< 启用SDIO中断线的主机功能*/
    esp_err_t (*io_int_wait)(int slot, TickType_t timeout_ticks); /*!< 等待SDIO中断线激活的主机功能*/
    int command_timeout_ms;     /*!< 单个命令的超时（毫秒）。设置为0以使用默认值。*/
} sdmmc_host_t;

/**
 * SD/MMC卡信息结构
 */
typedef struct {
    sdmmc_host_t host;          /*!< 与卡关联的主机*/
    uint32_t ocr;               /*!< OCR（操作条件寄存器）值*/
    union {
        sdmmc_cid_t cid;            /*!< 解码的CID（卡标识）寄存器值*/
        sdmmc_response_t raw_cid;   /*!< 在数据传输模式下获取CSD后，要解码的MMC卡的原始CID*/
    };
    sdmmc_csd_t csd;            /*!< 解码CSD（卡特定数据）寄存器值*/
    sdmmc_scr_t scr;            /*!< 解码的SCR（SD卡配置寄存器）值*/
    sdmmc_ext_csd_t ext_csd;    /*!< 解码EXT_CSD（扩展卡特定数据）寄存器值*/
    uint16_t rca;               /*!< RCA（相对卡地址）*/
    uint16_t max_freq_khz;      /*!< 卡支持的最大频率（kHz）*/
    uint32_t is_mem : 1;        /*!< 位指示卡是否为存储卡*/
    uint32_t is_sdio : 1;       /*!< 位指示卡是否为IO卡*/
    uint32_t is_mmc : 1;        /*!< 位指示卡是否为MMC*/
    uint32_t num_io_functions : 3;  /*!< 如果is_sdio为1，则包含卡上IO功能的数量*/
    uint32_t log_bus_width : 2; /*!< log2（卡支持的总线宽度）*/
    uint32_t is_ddr : 1;        /*!< 卡支持DDR模式*/
    uint32_t reserved : 23;     /*!< 保留用于未来扩展*/
} sdmmc_card_t;


#endif // _SDMMC_TYPES_H_

