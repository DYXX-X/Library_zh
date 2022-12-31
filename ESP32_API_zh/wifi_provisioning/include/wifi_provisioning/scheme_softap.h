// 版权所有2019 Espressif Systems（上海）私人有限公司
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

#include <protocomm.h>
#include <protocomm_httpd.h>

#include "wifi_provisioning/manager.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   管理器可用于通过SoftAP传输与HTTP服务器进行资源调配的方案
 */
extern const wifi_prov_scheme_t wifi_prov_scheme_softap;

/**
 *
 * @brief 外部提供HTTPD服务器句柄。
 *
 * 在应用程序需要Web服务器来执行某些不同的操作，并且不希望wifi供应组件启动/停止新实例的情况下非常有用。
 *
 * @note 应在wifi_prov_mgr_start_provision（）之前调用此API
 *
 * @param[in] handle HTTPD服务器实例的句柄
 */
void wifi_prov_scheme_softap_set_httpd_handle(void *handle);
#ifdef __cplusplus
}
#endif

