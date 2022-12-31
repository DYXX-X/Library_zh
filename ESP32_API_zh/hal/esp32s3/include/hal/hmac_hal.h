/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/*******************************************************************************
 * 注意hal不是公共api，不要在应用程序代码中使用它。请参阅自述文件。soc/include/hal/readme.md中的md
 ******************************************************************************/

#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * HMAC外围设备可以被配置为直接将其输出传递给用户，或者直接将输出传递给另一个外围设备，例如数字签名外围设备。
 */
typedef enum {
    HMAC_OUTPUT_USER = 0,           /**<让用户提供消息并读取HMAC结果*/
    HMAC_OUTPUT_DS = 1,             /**<HMAC被提供给DS外围设备以解密DS私钥参数*/
    HMAC_OUTPUT_JTAG_ENABLE = 2,    /**<HMAC用于在软禁用JTAG后启用JTAG*/
    HMAC_OUTPUT_ALL = 3             /**<HMAC用于JTAG的DS输入或启用JTAG*/
} hmac_hal_output_t;

/**
 * @brief 准备好外围设备以供使用。
 *
 * 这将触发启用设备后所需的任何进一步步骤
 */
void hmac_hal_start(void);

/**
 * @brief 配置应使用的硬件密钥槽，并配置HMAC输出的目标。
 *
 * @note 写入超出范围的值是未定义的行为。用户必须确保参数在范围内。
 *
 * @param config HMAC的目标。可能的目标在\chmac_hal_output_t中描述。有关详细信息，请参阅ESP32S3 TRM。
 * @param key_id 要使用的硬件密钥槽的ID。
 *
 * @return 如果配置成功，则为0，否则为非零。配置不成功意味着相应密钥插槽的eFuse中的目标值与提供的\c-config值不匹配。
 */
uint32_t hmac_hal_configure(hmac_hal_output_t config, uint32_t key_id);

/**
 * @brief 向HMAC外围设备写入512位的填充单块消息。
 *
 * 消息长度不得超过一个块（512位），并且在写入之前必须由软件应用填充。填充必须能够适应消息后面的块。有关HMAC填充的更多信息，请参阅ESP32S3 TRM。
 */
void hmac_hal_write_one_block_512(const void *block);

/**
 * @brief 向HMAC外围设备写入512位的消息块。
 *
 * 此函数必须与\chmac_hal_next_block_normal（）或\chmac_hal_next_block_padding（）结合使用。第一个消息块是在没有任何先决条件的情况下编写的。所有不是最后一个消息块的消息块都需要在之前调用\chmac_hal_next_block_normal（），向硬件指示后面将出现“正常”，即无填充块。甚至对于已经开始填充但填充不合适的块（剩余消息大小>（块大小-填充大小））也是如此。在写入包含填充的最后一个块之前，需要调用\chmac_hal_next_block_padding（），以向硬件指示将写入带有填充的块。
 *
 * 有关HMAC填充的更多信息，请参阅ESP32S3 TRM。
 */
void hmac_hal_write_block_512(const void *block);

/**
 * @brief 向硬件指示将写入正常块。
 */
void hmac_hal_next_block_normal(void);

/**
 * @brief 向硬件指示将写入带有填充的块。
 */
void hmac_hal_next_block_padding(void);

/**
 * @brief 从硬件读取256位HMAC结果。
 */
void hmac_hal_read_result_256(void *result);

/**
 * @brief 清除（使）提供给其他硬件的HMAC结果无效。
 */
void hmac_hal_clean(void);

#ifdef __cplusplus
}
#endif

