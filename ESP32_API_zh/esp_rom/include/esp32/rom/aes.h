/*
  用于硬件AES支持的ROM功能。

  不建议直接使用这些函数，请使用esp32/aes中的包装函数。h代替。

 */
// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef _ROM_AES_H_
#define _ROM_AES_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

//TODO，为aes api添加注释
enum AES_BITS {
    AES128,
    AES192,
    AES256
};

void ets_aes_enable(void);

void ets_aes_disable(void);

void ets_aes_set_endian(bool key_word_swap, bool key_byte_swap,
                        bool in_word_swap, bool in_byte_swap,
                        bool out_word_swap, bool out_byte_swap);

bool ets_aes_setkey_enc(const uint8_t *key, enum AES_BITS bits);

bool ets_aes_setkey_dec(const uint8_t *key, enum AES_BITS bits);

void ets_aes_crypt(const uint8_t input[16], uint8_t output[16]);

#ifdef __cplusplus
}
#endif

#endif /* _ROM_AES_H_ */

