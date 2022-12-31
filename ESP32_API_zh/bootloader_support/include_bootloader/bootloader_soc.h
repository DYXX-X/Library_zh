/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

/**
 * @brief 配置模拟超级WDT重置
 *
 * @param enable 布尔值以启用或禁用超级WDT重置
 */
void bootloader_ana_super_wdt_reset_config(bool enable);

/**
 * @brief 配置模拟断电复位
 *
 * @param enable 布尔值可启用或禁用断电重置
 */
void bootloader_ana_bod_reset_config(bool enable);

/**
 * @brief 配置模拟时钟故障复位
 *
 * @param enable 布尔值可启用或禁用时钟故障重置
 */
void bootloader_ana_clock_glitch_reset_config(bool enable);

