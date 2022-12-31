// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
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
#ifndef ESP_CORE_DUMP_ELF_H_
#define ESP_CORE_DUMP_ELF_H_

#include "esp_core_dump_types.h"

/**
 * @brief 启动ELF核心转储生成。
 *
 * @param info      发生死机时生成的异常帧信息。
 * @param write_cfg 包含将被调用以写入生成的核心转储数据的回调的结构。
 *
 * @return 成功时ESP_OK，否则请参见ESP_err_t。
 */
esp_err_t esp_core_dump_write_elf(core_dump_write_config_t *write_cfg);

#endif

