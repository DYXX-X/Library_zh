/* 版权所有2018 Espressif Systems（上海）私人有限公司
 *
 * 根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
*/

//  mbc_tcp_master。h Modbus控制器TCP主实施头文件

#ifndef _MODBUS_TCP_CONTROLLER_MASTER
#define _MODBUS_TCP_CONTROLLER_MASTER

#include <stdint.h>                 // 用于标准int类型定义
#include <stddef.h>                 // 对于NULL和std定义
#include "esp_modbus_common.h"      // 用于公共定义

/* -----------------------定义------------------------------------------*/
#define MB_INST_MIN_SIZE                    (2) // Modbus寄存器区域的最小大小（字节）
#define MB_INST_MAX_SIZE                    (CONFIG_MB_INST_MAX_SIZE) // Modbus区域的最大大小（字节）

#define MB_CONTROLLER_NOTIFY_QUEUE_SIZE     (CONFIG_MB_CONTROLLER_NOTIFY_QUEUE_SIZE) // 参数通知队列中的消息数
#define MB_CONTROLLER_NOTIFY_TIMEOUT        (pdMS_TO_TICKS(CONFIG_MB_CONTROLLER_NOTIFY_TIMEOUT)) // 通知超时

/**
 * @brief 为TCP端口创建Modbus主控制器和堆栈
 *
 * @param[out] handler 主数据结构的处理程序（指针）
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_NO_MEM参数错误
 */
esp_err_t mbc_tcp_master_create(void** handler);

#endif // _MODBUS_TCP_CONTROLLER_SLAVE

