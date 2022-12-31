/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdio.h>
#include "esp_err.h"
#include "driver/sdmmc_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 使用给定主机探测并初始化SD/MMC卡
 *
 * @note 现在只支持SD卡（SDSC和SDHC/SDXC）。稍后将添加对MMC/eMMC卡的支持。
 *
 * @param host  指向定义主机控制器的结构的指针
 * @param out_card  指向结构的指针，该结构将在功能完成时接收有关卡的信息
 * @return
 *      -成功时ESP_OK
 *      -SDMMC主机控制器的错误代码之一
 */
esp_err_t sdmmc_card_init(const sdmmc_host_t* host,
        sdmmc_card_t* out_card);

/**
 * @brief 将有关卡的信息打印到流中
 * @param stream  使用fopen或fdopen获得的流
 * @param card  使用sdmmc_card_init初始化卡信息结构
 */
void sdmmc_card_print_info(FILE* stream, const sdmmc_card_t* card);

/**
 * 获取SD/MMC卡的状态
 *
 * @param card  指向先前使用sdmmc_card_init初始化的卡信息结构的指针
 * @return
 *      -成功时ESP_OK
 *      -SDMMC主机控制器的错误代码之一
 */
esp_err_t sdmmc_get_status(sdmmc_card_t* card);

/**
 * 将给定数量的扇区写入SD/MMC卡
 *
 * @param card  指向先前使用sdmmc_card_init初始化的卡信息结构的指针
 * @param src   指向要从中读取数据的数据缓冲区的指针；数据大小必须等于扇区计数卡->csd.sector_size
 * @param start_sector  开始写入的扇区
 * @param sector_count  要写入的扇区数
 * @return
 *      -成功时ESP_OK
 *      -SDMMC主机控制器的错误代码之一
 */
esp_err_t sdmmc_write_sectors(sdmmc_card_t* card, const void* src,
        size_t start_sector, size_t sector_count);

/**
 * 从SD/MMC卡读取给定数量的扇区
 *
 * @param card  指向先前使用sdmmc_card_init初始化的卡信息结构的指针
 * @param dst   指向要写入的数据缓冲区的指针；缓冲区大小必须至少为sector_count卡->csd.sector_size
 * @param start_sector  开始读取的扇区
 * @param sector_count  要读取的扇区数
 * @return
 *      -成功时ESP_OK
 *      -SDMMC主机控制器的错误代码之一
 */
esp_err_t sdmmc_read_sectors(sdmmc_card_t* card, void* dst,
        size_t start_sector, size_t sector_count);

/**
 * 使用IO_RW_DIRECT（CMD52）从SDIO卡读取一个字节
 *
 * @param card  指向先前使用sdmmc_card_init初始化的卡信息结构的指针
 * @param function  IO功能编号
 * @param reg  IO功能内的字节地址
 * @param[out] out_byte  输出，接收从卡读取的值
 * @return
 *      -成功时ESP_OK
 *      -SDMMC主机控制器的错误代码之一
 */
esp_err_t sdmmc_io_read_byte(sdmmc_card_t* card, uint32_t function,
        uint32_t reg, uint8_t *out_byte);

/**
 * 使用IO_RW_DIRECT（CMD52）将一个字节写入SDIO卡
 *
 * @param card  指向先前使用sdmmc_card_init初始化的卡信息结构的指针
 * @param function  IO功能编号
 * @param reg  IO功能内的字节地址
 * @param in_byte  要写入的值
 * @param[out] out_byte  如果不是NULL，则接收从卡读取的新字节值（写入后读取）。
 * @return
 *      -成功时ESP_OK
 *      -SDMMC主机控制器的错误代码之一
 */
esp_err_t sdmmc_io_write_byte(sdmmc_card_t* card, uint32_t function,
        uint32_t reg, uint8_t in_byte, uint8_t* out_byte);

/**
 * 使用IO_RW_EXTENDED（CMD53）从SDIO卡读取多个字节
 *
 * 此函数在字节模式下使用CMD53执行读取操作。有关块模式，请参见sdmmc_io_read_blocks。
 *
 * @param card  指向先前使用sdmmc_card_init初始化的卡信息结构的指针
 * @param function  IO功能编号
 * @param addr  IO函数中开始读取的字节地址
 * @param dst  接收从卡读取的数据的缓冲器
 * @param size  要读取的字节数
 * @return
 *      -成功时ESP_OK
 *      -如果大小超过512字节，则为ESP_ERR_INVALID_SIZE
 *      -SDMMC主机控制器的错误代码之一
 */
esp_err_t sdmmc_io_read_bytes(sdmmc_card_t* card, uint32_t function,
        uint32_t addr, void* dst, size_t size);

/**
 * 使用IO_RW_EXTENDED（CMD53）将多个字节写入SDIO卡
 *
 * 此函数在字节模式下使用CMD53执行写入操作。有关块模式，请参见sdmmc_io_write_blocks。
 *
 * @param card  指向先前使用sdmmc_card_init初始化的卡信息结构的指针
 * @param function  IO功能编号
 * @param addr  IO函数中开始写入的字节地址
 * @param src  要写入的数据
 * @param size  要写入的字节数
 * @return
 *      -成功时ESP_OK
 *      -如果大小超过512字节，则为ESP_ERR_INVALID_SIZE
 *      -SDMMC主机控制器的错误代码之一
 */
esp_err_t sdmmc_io_write_bytes(sdmmc_card_t* card, uint32_t function,
        uint32_t addr, const void* src, size_t size);

/**
 * 使用IO_RW_EXTENDED（CMD53）从SDIO卡读取数据块
 *
 * 此函数在块模式下使用CMD53执行读取操作。有关字节模式，请参见sdmmc_io_read_bytes。
 *
 * @param card  指向先前使用sdmmc_card_init初始化的卡信息结构的指针
 * @param function  IO功能编号
 * @param addr  IO函数中开始写入的字节地址
 * @param dst  接收从卡读取的数据的缓冲器
 * @param size  要读取的字节数必须可以被卡块大小整除。
 * @return
 *      -成功时ESP_OK
 *      -如果大小不能被512字节整除，则为ESP_ERR_INVALID_SIZE
 *      -SDMMC主机控制器的错误代码之一
 */
esp_err_t sdmmc_io_read_blocks(sdmmc_card_t* card, uint32_t function,
        uint32_t addr, void* dst, size_t size);

/**
 * 使用IO_RW_EXTENDED（CMD53）将数据块写入SDIO卡
 *
 * 此函数在块模式下使用CMD53执行写入操作。有关字节模式，请参见sdmmc_io_write_bytes。
 *
 * @param card  指向先前使用sdmmc_card_init初始化的卡信息结构的指针
 * @param function  IO功能编号
 * @param addr  IO函数中开始写入的字节地址
 * @param src  要写入的数据
 * @param size  要读取的字节数必须可以被卡块大小整除。
 * @return
 *      -成功时ESP_OK
 *      -如果大小不能被512字节整除，则为ESP_ERR_INVALID_SIZE
 *      -SDMMC主机控制器的错误代码之一
 */
esp_err_t sdmmc_io_write_blocks(sdmmc_card_t* card, uint32_t function,
        uint32_t addr, const void* src, size_t size);

/**
 * 在SDMMC主机中启用SDIO中断
 *
 * @param card  指向先前使用sdmmc_card_init初始化的卡信息结构的指针
 * @return
 *      -成功时ESP_OK
 *      -如果主机控制器不支持IO中断，则为ESP_ERR_NOT_SUPPORTED
 */
esp_err_t sdmmc_io_enable_int(sdmmc_card_t* card);

/**
 * 阻止，直到收到SDIO中断
 *
 * 从设备使用D1线向主机发送中断状态信号。此功能可用于等待中断。
 *
 * @param card  指向先前使用sdmmc_card_init初始化的卡信息结构的指针
 * @param timeout_ticks  等待中断的时间，以RTOS为单位
 * @return
 *      -ESP_OK（如果接收到中断）
 *      -如果主机控制器不支持IO中断，则为ESP_ERR_NOT_SUPPORTED
 *      -如果在TIMEOUT_ticks中未发生中断，则为ESP_ERR_TIMEOUT
 */
esp_err_t sdmmc_io_wait_int(sdmmc_card_t* card, TickType_t timeout_ticks);

/**
 * 获取SDIO卡的CIS区域数据。
 *
 * 您可能提供的缓冲区不足以存储所有CIS数据。在这种情况下，该函数将尽可能多的数据存储到缓冲区中。此外，此函数将尝试获取并返回所需的大小。
 *
 * @param card  指向先前使用sdmmc_card_init初始化的卡信息结构的指针
 * @param out_buffer CIS数据的输出缓冲区
 * @param buffer_size 缓冲区的大小。
 * @param inout_cis_size 强制，指向大小、输入和输出的指针。
 *              -输入：最大搜索范围的限制，应为0或大于buffer_size。该函数搜索CIS_CODE_END直到该范围。设置为0可无限搜索。
 *              -output：如果找到CIS_CODE_END，则存储所有CIS数据所需的大小。
 *
 * @return
 *      -ESP_OK：成功时
 *      -ESP_ERR_INVALID_RESPONSE：如果卡不（正确）支持CIS。
 *      -ESP_ERR_INVALID_SIZE:找到了CIS_CODE_END，但buffer_SIZE小于所需大小，然后存储在inout_CIS_SIZE中。
 *      -ESP_ERR_NOT_FOUND：如果未找到CIS_CODE_END。增加inout_cis_size的输入值或将其设置为0，如果您仍然想搜索结尾；在这种情况下，inoutcis_size的输出值无效。
 *      -以及从sdmmc_io_read_bytes返回的其他错误代码
 */
esp_err_t sdmmc_io_get_cis_data(sdmmc_card_t* card, uint8_t* out_buffer, size_t buffer_size, size_t* inout_cis_size);

/**
 * 分析并打印SDIO卡的CIS信息。
 *
 * @note 并非所有的CIS代码和所有类型的元组都受支持。如果看到一些未解析的代码，可以在sdmmc_io中添加这些代码的解析。c并通过Github存储库为IDF做出贡献。
 *
 *              使用sdmmc_card_init
 * @param buffer 要分析的缓冲区
 * @param buffer_size 缓冲区的大小。
 * @param fp 要打印到的文件指针，设置为NULL以打印到标准输出。
 *
 * @return
 *      -ESP_OK：成功时
 *      -ESP_ERR_NOT_SUPPORTED：如果不支持解析卡中的值。
 *      -ESP_ERR_INVALID_SIZE：如果CIS大小字段不正确。
 */
esp_err_t sdmmc_io_print_cis_info(uint8_t* buffer, size_t buffer_size, FILE* fp);


#ifdef __cplusplus
}
#endif

