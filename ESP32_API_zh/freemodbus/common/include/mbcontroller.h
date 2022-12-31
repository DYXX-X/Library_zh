/* 版权所有2018 Espressif Systems（上海）私人有限公司
 *
 * 根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
*/
//  mbcontroller.h
//  mbcontroller-通用Modbus控制器头文件

#ifndef _MODBUS_CONTROLLER_COMMON
#define _MODBUS_CONTROLLER_COMMON

#include <stdint.h>                 // 用于标准int类型定义
#include <stddef.h>                 // 对于NULL和std定义
#include "string.h"                 // 用于strerr（）
#include "errno.h"                  // 用于errno
#include "esp_err.h"                // 用于错误处理
#include "driver/uart.h"            // 用于uart端口号定义
#include "sdkconfig.h"              // 对于KConfig选项

#include "esp_modbus_master.h"
#include "esp_modbus_slave.h"

#endif

