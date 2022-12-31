/*
 * SPDX文件版权文本：2019-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define COUNT_EFUSE_REG_PER_BLOCK 8      /* 每个块的寄存器数。*/

#define ESP_EFUSE_SECURE_VERSION_NUM_BLOCK EFUSE_BLK3

#define ESP_EFUSE_FIELD_CORRESPONDS_CODING_SCHEME(blk, max_num_bit)                                   \
	esp_efuse_coding_scheme_t scheme = esp_efuse_get_coding_scheme(blk);                              \
    if ((scheme == EFUSE_CODING_SCHEME_3_4    && max_num_bit > 192) ||                                \
        (scheme == EFUSE_CODING_SCHEME_REPEAT && max_num_bit > 128)) {                                \
    	return false;                                                                                 \
    }

/* @brief 将一组或多组6字节序列编码成适合3/4编码方案的8字节。
 *
 * 仅当3/4编码方案的CODING_SCHEME efuse设置为值1时，此函数才有用。
 *
 * @param[in] in_bytes 指向要为3/4编码方案编码的字节序列的指针。长度必须为in_bytes_len。写入硬件后，这些字节将作为小端字读回。
 * @param[out] out_words 指向适合写入efuse写寄存器的字数组的指针。对于in_bytes_len中的每6个字节，数组必须包含2个字（8个字节）。可以是efuse写寄存器的指针。
 * @param in_bytes_len. in_bytes指向的数组长度，以字节为单位。必须是6的倍数。
 *
 * @return 如果指针为空或in_bytes_len不是6的倍数，则为ESP_ERR_INVALID_ARG。否则为ESP_OK。
 */
esp_err_t esp_efuse_utility_apply_34_encoding(const uint8_t *in_bytes, uint32_t *out_words, size_t in_bytes_len);

#ifdef __cplusplus
}
#endif

