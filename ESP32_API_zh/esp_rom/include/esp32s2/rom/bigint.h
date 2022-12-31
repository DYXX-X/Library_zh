/*
  用于硬件bigint支持的ROM函数。

  不建议直接使用这些函数，请使用hwcrypto/mpi中的包装函数。h代替。

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

#ifndef _ROM_BIGINT_H_
#define _ROM_BIGINT_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void ets_bigint_enable(void);

void ets_bigint_disable(void);

int ets_bigint_multiply(const uint32_t *x, const uint32_t *y, uint32_t len_words);

int ets_bigint_modmult(const uint32_t *x, const uint32_t *y, const uint32_t *m, uint32_t m_dash, const uint32_t *rb, uint32_t len_words);

int ets_bigint_modexp(const uint32_t *x, const uint32_t *y, const uint32_t *m, uint32_t m_dash, const uint32_t *rb, bool constant_time, uint32_t len_words);

void ets_bigint_wait_finish(void);

int ets_bigint_getz(uint32_t *z, uint32_t len_words);

#ifdef __cplusplus
}
#endif

#endif /* _ROM_BIGINT_H_ */

