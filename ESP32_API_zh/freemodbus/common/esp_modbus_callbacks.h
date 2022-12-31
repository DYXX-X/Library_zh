/* 版权所有2018 Espressif Systems（上海）私人有限公司
 *
 * 根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
*/

// 堆栈回调函数原型

#ifndef _ESP_MODBUS_CALLBACKS_H_
#define _ESP_MODBUS_CALLBACKS_H_

#include "mb.h"
#include "mb_m.h"

typedef eMBErrorCode (*reg_input_cb)(UCHAR*, USHORT, USHORT);
typedef eMBErrorCode (*reg_holding_cb)(UCHAR*, USHORT, USHORT, eMBRegisterMode);
typedef eMBErrorCode (*reg_coils_cb)(UCHAR*, USHORT, USHORT, eMBRegisterMode);
typedef eMBErrorCode (*reg_discrete_cb)(UCHAR*, USHORT, USHORT);

#endif /* _ESP_MODBUS_CALLBACKS_H_ */

