/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/** @brief 在引导加载程序中启用四路I/O模式（如果已配置）
 *
 * 查询附加的SPI闪存ID并发送正确的SPI闪存命令以启用QIO或QOUT模式，然后启用此模式。
 */
void bootloader_enable_qio_mode(void);

/**
 * @brief 通过发送0x9F命令读取闪存ID
 * @return 闪存原始ID mfg_ID=（ID>>16）&0xFF；flash_id=id&0xffff；
 */
uint32_t bootloader_read_flash_id(void);

#ifdef __cplusplus
}
#endif

