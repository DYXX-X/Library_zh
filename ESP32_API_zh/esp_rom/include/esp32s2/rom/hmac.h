// 版权所有2018 Espressif Systems（上海）私人有限公司
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

#ifndef _ROM_HMAC_H_
#define _ROM_HMAC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include "efuse.h"

void ets_hmac_enable(void);

void ets_hmac_disable(void);

/* 使用“上游”HMAC键（ETS_EFUSE_key_PURPOSE_HMAC_UP）来消化消息。
*/
int ets_hmac_calculate_message(ets_efuse_block_t key_block, const void *message, size_t message_len, uint8_t *hmac);

/* 计算下游HMAC消息以临时启用JTAG，或生成数字签名数据解密密钥。

   -目的必须是ETS_EFUSE_KEY_purpose_HMAC_DOWN_DIGITAL_SIGNATURE或ETS_EFUSE_KEY_purpose_HMAC _DOWN_JTAG

   -key_block必须在ETS_EFUSE_block_KEY0到ETS_EFUSE_block_KEY6的范围内。此EFUSE块必须在“用途”或ETS_EFUSE_key_purpose_HMAC_DOWN_ALL中设置相应的用途。

   HMAC计算结果仅在“下游”提供给相应的硬件模块，软件无法访问。
*/
int ets_hmac_calculate_downstream(ets_efuse_block_t key_block, ets_efuse_purpose_t purpose);

/* 使之前由ets_mac_calculate_downstream（）计算的下游HMAC值无效。
 *
 * -目的必须与之前对ets_mac_calculate_downstream（）的调用相匹配。
 *
 * 调用此函数后，相应的内部操作（JTAG或DS）将不再能够访问生成的密钥。
 */
int ets_hmac_invalidate_downstream(ets_efuse_purpose_t purpose);

#ifdef __cplusplus
}
#endif

#endif // _ROM_HMAC_H_

