// 版权所有2015-2017 Espressif Systems（上海）私人有限公司
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

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 初始化缓存无效访问中断
 *
 * 此功能启用缓存无效访问中断源，并将其连接到中断输入号。它是从启动代码调用的。
 *
 * 在ESP32上，中断输入号为ETS_MEMACCESS_ERR_INUM。在其他目标上，它是ETS_CACHEERR_INUM。参见soc/soc。h获取更多信息。
 */
void esp_cache_err_int_init(void);


/**
 * @brief 获取导致缓存无效访问中断的CPU。紧急处理中的助手功能。
 * @return
 *  -PRO_CPU_NUM，如果PRO_CPU导致缓存IA中断
 *  -APP_CPU_NUM，如果APP_CPU已导致缓存IA中断
 *  -（-1）否则
 */
int esp_cache_err_get_cpuid(void);

#ifdef __cplusplus
}
#endif

