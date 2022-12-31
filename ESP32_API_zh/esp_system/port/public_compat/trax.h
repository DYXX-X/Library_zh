// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#include "sdkconfig.h"
#include "esp_err.h"
#include "eri.h"
#include "xtensa-debug-module.h"
#include "xt_trax.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    TRAX_DOWNCOUNT_WORDS,
    TRAX_DOWNCOUNT_INSTRUCTIONS
} trax_downcount_unit_t;

typedef enum {
    TRAX_ENA_NONE = 0,
    TRAX_ENA_PRO,
    TRAX_ENA_APP,
    TRAX_ENA_PRO_APP,
    TRAX_ENA_PRO_APP_SWAP
} trax_ena_select_t;

/**
 * @brief  启用trax内存块以用作trax内存。
 *
 * @param  pro_cpu_enable ：如果需要为pro CPU启用Trax，则为true
 * @param  app_cpu_enable ：如果需要为pro CPU启用Trax，则为true
 * @param  swap_regions ：通常情况下，pro CPU写入Trax内存块0，而app CPU写入块1。将此设置为true会反转此设置。
 *
 * @return esp_err_t。如果请求为2个CPU启用Trax，但memmap只有1个空间，或者如果完全禁用Trax memmap，则ESP_ERR_NO_MEM失败。
 */
int trax_enable(trax_ena_select_t ena);

/**
 * @brief  在当前CPU上启动Trax跟踪
 *
 * @param  units_until_stop ：设置传递给trax_trigger_tracend_after_delay的延迟单位。TRAX_DOWNCOUNT_WORDS或TRAX_DOWNCOUNT_STRUCTIONS之一。
 *
 * @return esp_err_t。如果禁用Trax，则ESP_ERR_NO_MEM失败。
 */
int trax_start_trace(trax_downcount_unit_t units_until_stop);


/**
 * @brief  在指定的延迟后触发Trax跟踪停止。如果之前调用了此函数，而上一个延迟尚未结束，则将使用新值覆盖该延迟。延迟将始终在调用函数时开始。
 *
 * @param  delay ：停止跟踪的延迟，单位为trax_start_trace。注意：跟踪内存有4K字可用。
 *
 * @return 电子邮箱地址
 */
int trax_trigger_traceend_after_delay(int delay);

#ifdef __cplusplus
}
#endif

