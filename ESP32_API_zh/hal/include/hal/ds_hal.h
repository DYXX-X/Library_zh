// 版权所有2020 Espressif Systems（上海）私人有限公司
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

/*******************************************************************************
 * 注意hal不是公共api，不要在应用程序代码中使用它。请参阅自述文件。soc/include/hal/readme.md中的md
 ******************************************************************************/

#pragma once

#if CONFIG_IDF_TARGET_ESP32
#error "ESP32 doesn't have a DS peripheral"
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 检查用于解密RSA参数的密钥是否准备就绪时的结果。
 */
typedef enum {
    DS_KEY_INPUT_OK = 0, /**<解密密钥已准备好。*/
    DS_NO_KEY_INPUT,     /**<从属外围设备提供键尚未激活。*/
    DS_OTHER_WRONG,      /**<从属外围设备正在运行，但接收密钥时出现问题。*/
} ds_key_check_t;

typedef enum {
    DS_SIGNATURE_OK = 0,                    /**<签名有效，可以读取。*/
    DS_SIGNATURE_PADDING_FAIL = 1,          /**<填充无效，如果用户需要，可以读取签名。*/
    DS_SIGNATURE_MD_FAIL = 2,               /**<消息摘要检查失败，签名无效。*/
    DS_SIGNATURE_PADDING_AND_MD_FAIL = 3,   /**<填充和MD检查都失败。*/
} ds_signature_check_t;

/**
 * @brief 输入密钥就绪后，开始整个签名过程。
 *
 * 在使用以下任何函数之前调用此函数。此时输入键已准备就绪。
 */
void ds_hal_start(void);

/**
 * @brief 完成整个签名过程。在读取签名后或在出现错误时调用此函数。
 */
void ds_hal_finish(void);

/**
 * @brief 写入初始化向量。
 */
void ds_hal_configure_iv(const uint32_t *iv);

/**
 * @brief 写下应该签名的消息。
 *
 * @param msg 指向消息的指针。
 * @param size 签名结果的长度（字节）。它是以字节为单位的RSA签名长度。
 */
void ds_hal_write_message(const uint8_t *msg, size_t size);

/**
 * @brief 写入加密的私钥参数。
 */
void ds_hal_write_private_key_params(const uint8_t *block);

/**
 * @brief 开始签名过程。
 */
void ds_hal_start_sign(void);

/**
 * @brief 检查硬件是否正忙于某项操作。
 *
 * @return 如果硬件已完成签名过程，则为True，否则为false。
 */
bool ds_hal_busy(void);

/**
 * @brief 检查并读取硬件的签名。
 *
 * @return
 * -DS_SIGNATURE_OK（如果未检测到签名问题）。
 * -如果私钥参数的填充错误，则返回DS_SIGNATURE_PADING_FAIL。
 * -如果消息摘要检查失败，则为DS_SIGNATURE_MD_FAIL。这意味着使用私钥参数计算的消息摘要失败，即私钥参数的完整性不受保护。
 * -如果填充和消息摘要检查都失败，则DS_SIGNATURE_PADING_AND_MD_FAIL。
 */
ds_signature_check_t ds_hal_read_result(uint8_t *result, size_t size);

#ifdef __cplusplus
}
#endif

