/*
 * Copyright (c) 2006 Uwe Stuehler <uwe@openbsd.org> 适应ESP-IDF版权所有（c）2016-2018 Espressif Systems（上海）PTE LTD
 *
 * 特此授予出于任何目的使用、复制、修改和分发本软件的许可，无论是否收取费用，前提是上述版权声明和本许可声明出现在所有副本中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#pragma once

#include <string.h>
#include "esp_log.h"
#include "esp_heap_caps.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/sdmmc_defs.h"
#include "driver/sdmmc_types.h"
#include "sdmmc_cmd.h"
#include "sys/param.h"
#include "soc/soc_memory_layout.h"

#define SDMMC_GO_IDLE_DELAY_MS              20
#define SDMMC_IO_SEND_OP_COND_DELAY_MS      10

/* 这些延迟值在未使用CD引脚且卡已移除的情况下非常有用。在这种情况下，SDMMC外围设备在发出错误信号后可能不总是返回CMD_DONE/DATA_DONE中断。在这种情况下，这些超时起到了安全网的作用。
 */
#define SDMMC_DEFAULT_CMD_TIMEOUT_MS  1000   // 普通命令的最大超时
#define SDMMC_WRITE_CMD_TIMEOUT_MS    5000   // 写入命令的最大超时

/* SEND_OP_COND（CMD1）的最大重试/错误计数。这些值有些武断，源于OpenBSD驱动程序。
 */
#define SDMMC_SEND_OP_COND_MAX_RETRIES  100
#define SDMMC_SEND_OP_COND_MAX_ERRORS   3

/* 发送单个命令的功能*/
esp_err_t sdmmc_send_cmd(sdmmc_card_t* card, sdmmc_command_t* cmd);
esp_err_t sdmmc_send_app_cmd(sdmmc_card_t* card, sdmmc_command_t* cmd);
esp_err_t sdmmc_send_cmd_go_idle_state(sdmmc_card_t* card);
esp_err_t sdmmc_send_cmd_send_if_cond(sdmmc_card_t* card, uint32_t ocr);
esp_err_t sdmmc_send_cmd_send_op_cond(sdmmc_card_t* card, uint32_t ocr, uint32_t *ocrp);
esp_err_t sdmmc_send_cmd_read_ocr(sdmmc_card_t *card, uint32_t *ocrp);
esp_err_t sdmmc_send_cmd_send_cid(sdmmc_card_t *card, sdmmc_cid_t *out_cid);
esp_err_t sdmmc_send_cmd_all_send_cid(sdmmc_card_t* card, sdmmc_response_t* out_raw_cid);
esp_err_t sdmmc_send_cmd_set_relative_addr(sdmmc_card_t* card, uint16_t* out_rca);
esp_err_t sdmmc_send_cmd_set_blocklen(sdmmc_card_t* card, sdmmc_csd_t* csd);
esp_err_t sdmmc_send_cmd_switch_func(sdmmc_card_t* card,
        uint32_t mode, uint32_t group, uint32_t function,
        sdmmc_switch_func_rsp_t* resp);
esp_err_t sdmmc_send_cmd_send_csd(sdmmc_card_t* card, sdmmc_csd_t* out_csd);
esp_err_t sdmmc_send_cmd_select_card(sdmmc_card_t* card, uint32_t rca);
esp_err_t sdmmc_send_cmd_send_scr(sdmmc_card_t* card, sdmmc_scr_t *out_scr);
esp_err_t sdmmc_send_cmd_set_bus_width(sdmmc_card_t* card, int width);
esp_err_t sdmmc_send_cmd_send_status(sdmmc_card_t* card, uint32_t* out_status);
esp_err_t sdmmc_send_cmd_crc_on_off(sdmmc_card_t* card, bool crc_enable);

/* 更高级别的功能*/
esp_err_t sdmmc_enable_hs_mode(sdmmc_card_t* card);
esp_err_t sdmmc_enable_hs_mode_and_check(sdmmc_card_t* card);
esp_err_t sdmmc_write_sectors_dma(sdmmc_card_t* card, const void* src,
        size_t start_block, size_t block_count);
esp_err_t sdmmc_read_sectors_dma(sdmmc_card_t* card, void* dst,
        size_t start_block, size_t block_count);

/* SD特定*/
esp_err_t sdmmc_check_scr(sdmmc_card_t* card);
esp_err_t sdmmc_decode_cid(sdmmc_response_t resp, sdmmc_cid_t* out_cid);
esp_err_t sdmmc_decode_csd(sdmmc_response_t response, sdmmc_csd_t* out_csd);
esp_err_t sdmmc_decode_scr(uint32_t *raw_scr, sdmmc_scr_t* out_scr);

/* SDIO特定*/
esp_err_t sdmmc_io_reset(sdmmc_card_t* card);
esp_err_t sdmmc_io_enable_hs_mode(sdmmc_card_t* card);
esp_err_t sdmmc_io_send_op_cond(sdmmc_card_t* card, uint32_t ocr, uint32_t *ocrp);
esp_err_t sdmmc_io_rw_direct(sdmmc_card_t* card, int function,
        uint32_t reg, uint32_t arg, uint8_t *byte);
esp_err_t sdmmc_io_rw_extended(sdmmc_card_t* card, int function,
        uint32_t reg, int arg, void *data, size_t size);


/* MMC特定*/
esp_err_t sdmmc_mmc_send_ext_csd_data(sdmmc_card_t* card, void *out_data, size_t datalen);
esp_err_t sdmmc_mmc_switch(sdmmc_card_t* card, uint8_t set, uint8_t index, uint8_t value);
esp_err_t sdmmc_mmc_decode_cid(int mmc_ver, sdmmc_response_t resp, sdmmc_cid_t* out_cid);
esp_err_t sdmmc_mmc_decode_csd(sdmmc_response_t response, sdmmc_csd_t* out_csd);
esp_err_t sdmmc_mmc_enable_hs_mode(sdmmc_card_t* card);

/* 卡初始化流程的部分*/
esp_err_t sdmmc_init_sd_if_cond(sdmmc_card_t* card);
esp_err_t sdmmc_init_select_card(sdmmc_card_t* card);
esp_err_t sdmmc_init_csd(sdmmc_card_t* card);
esp_err_t sdmmc_init_cid(sdmmc_card_t* card);
esp_err_t sdmmc_init_rca(sdmmc_card_t* card);
esp_err_t sdmmc_init_mmc_decode_cid(sdmmc_card_t* card);
esp_err_t sdmmc_init_ocr(sdmmc_card_t* card);
esp_err_t sdmmc_init_spi_crc(sdmmc_card_t* card);
esp_err_t sdmmc_init_io(sdmmc_card_t* card);
esp_err_t sdmmc_init_sd_blocklen(sdmmc_card_t* card);
esp_err_t sdmmc_init_sd_scr(sdmmc_card_t* card);
esp_err_t sdmmc_init_sd_wait_data_ready(sdmmc_card_t* card);
esp_err_t sdmmc_init_mmc_read_ext_csd(sdmmc_card_t* card);
esp_err_t sdmmc_init_mmc_read_cid(sdmmc_card_t* card);
esp_err_t sdmmc_init_host_bus_width(sdmmc_card_t* card);
esp_err_t sdmmc_init_sd_bus_width(sdmmc_card_t* card);
esp_err_t sdmmc_init_io_bus_width(sdmmc_card_t* card);
esp_err_t sdmmc_init_mmc_bus_width(sdmmc_card_t* card);
esp_err_t sdmmc_init_card_hs_mode(sdmmc_card_t* card);
esp_err_t sdmmc_init_host_frequency(sdmmc_card_t* card);
esp_err_t sdmmc_init_mmc_check_csd(sdmmc_card_t* card);

/* 各种助手功能*/
static inline bool host_is_spi(const sdmmc_card_t* card)
{
    return (card->host.flags & SDMMC_HOST_FLAG_SPI) != 0;
}

static inline uint32_t get_host_ocr(float voltage)
{
    // TODO:向卡报告准确的电压
    // 现在告诉主机的电压范围为2.8-3.6V
    (void) voltage;
    return SD_OCR_VOL_MASK;
}

void sdmmc_flip_byte_order(uint32_t* response, size_t size);

esp_err_t sdmmc_fix_host_flags(sdmmc_card_t* card);

