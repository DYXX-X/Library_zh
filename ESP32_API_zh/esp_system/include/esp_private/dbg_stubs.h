// 版权所有2017 Espressif Systems（上海）私人有限公司
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
#ifndef ESP_DBG_STUBS_H_
#define ESP_DBG_STUBS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_err.h"

/**
 * 调试存根条目ID
 */
typedef enum {
    ESP_DBG_STUB_MAGIC_NUM,
    ESP_DBG_STUB_TABLE_SIZE,
    ESP_DBG_STUB_CONTROL_DATA,   ///<存根描述符条目
    ESP_DBG_STUB_ENTRY_FIRST,
    ESP_DBG_STUB_ENTRY_GCOV	///<GCOV条目
        = ESP_DBG_STUB_ENTRY_FIRST,
    ESP_DBG_STUB_ENTRY_CAPABILITIES,
    ESP_DBG_STUB_ENTRY_MAX
} esp_dbg_stub_id_t;

#define ESP_DBG_STUB_MAGIC_NUM_VAL      0xFEEDBEEF
#define ESP_DBG_STUB_CAP_GCOV_TASK      (1 << 0)

/**
 * @brief  初始化调试存根。
 *
 * @note   如果启用了应用程序跟踪，则必须在esp_apptrace_init（）之后调用。
 */
void esp_dbg_stubs_init(void);

/**
 * @brief  初始化应用程序跟踪模块。
 *
 * @note   应在任何esp_apptrace_xxx调用之前调用。
 *
 * @param id 存根ID。
 * @param entry 存根条目。通常它是存根条目函数地址，但可以是对OpenOCD命令/代码有意义的任何值，如功能
 * @return 成功时ESP_OK，否则请参见ESP_err_t
 */
esp_err_t esp_dbg_stub_entry_set(esp_dbg_stub_id_t id, uint32_t entry);

/**
 * @brief   检索相应的存根条目
 *
 * @param id 存根ID。
 * @param entry 存根条目。通常它是存根条目函数地址，但可以是对OpenOCD命令/代码有意义的任何值，如功能
 *
 * @return 成功时ESP_OK，否则请参见ESP_err_t
 */
esp_err_t esp_dbg_stub_entry_get(esp_dbg_stub_id_t id, uint32_t *entry);

#ifdef __cplusplus
}
#endif

#endif //ESP_DBG_STUBS_H_

