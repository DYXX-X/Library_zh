/* 版权所有2018 Espressif Systems（上海）私人有限公司
 *
 * 根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

//  mbc_serial_master。h Modbus控制器串行主实施头文件

#ifndef _MODBUS_SERIAL_CONTROLLER_MASTER
#define _MODBUS_SERIAL_CONTROLLER_MASTER

#include <stdint.h>                 // 用于标准int类型定义
#include <stddef.h>                 // 对于NULL和std定义
#include "soc/soc.h"                // 用于BITN定义
#include "esp_err.h"                // 对于esp_err_t
#include "esp_modbus_common.h"      // 用于公共定义

/**
 * @brief 初始化Modbus控制器和堆栈
 *
 * @param[out] handler 主数据结构的处理程序（指针）
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_NO_MEM参数错误
 */
esp_err_t mbc_serial_master_create(void** handler);

#endif // _MODBUS_SERIAL_CONTROLLER_MASTER

