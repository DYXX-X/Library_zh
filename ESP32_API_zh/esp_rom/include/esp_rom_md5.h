// 版权所有2010-2020 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * MD5函数为任意数量的输入字节计算128位密码摘要。
 */

/**
 * @brief 为MD5上下文定义的类型
 *
 */
typedef struct MD5Context {
    uint32_t buf[4];
    uint32_t bits[2];
    uint8_t in[64];
} md5_context_t;

#define ESP_ROM_MD5_DIGEST_LEN 16

/**
 * @brief 初始化MD5上下文
 *
 * @param context 用户分配的上下文对象
 */
void esp_rom_md5_init(md5_context_t *context);

/**
 * @brief 对输入数据运行MD5算法
 *
 * @param context 已由`MD5Init初始化的MD5上下文`
 * @param buf 输入缓冲区
 * @param len 缓冲区长度（字节）
 */
void esp_rom_md5_update(md5_context_t *context, const void *buf, uint32_t len);

/**
 * @brief 提取MD5结果，并删除上下文
 *
 * @param digest 存储128位摘要值的位置
 * @param context MD5上下文
 */
void esp_rom_md5_final(uint8_t *digest, md5_context_t *context);

#ifdef __cplusplus
}
#endif

