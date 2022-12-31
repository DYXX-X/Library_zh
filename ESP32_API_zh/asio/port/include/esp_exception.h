
/*
 * SPDX文件版权文本：2018-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#ifndef _ESP_EXCEPTION_H_
#define _ESP_EXCEPTION_H_

//
// 只有在menuconfig中禁用异常时，才会启用此异常存根
//
#if !defined(CONFIG_COMPILER_CXX_EXCEPTIONS) && defined (ASIO_NO_EXCEPTIONS)

#include "esp_log.h"

//
// asio异常存根
//
namespace asio {
namespace detail {
template <typename Exception>
void throw_exception(const Exception& e)
{
  ESP_LOGE("esp32_asio_exception", "Caught exception: %s!", e.what());
  abort();
}
}}
#endif // CONFIG_COMPILER_XX_EXCEPTIONS==1定义（ASIO_NO_EXCEPTION）

#endif // _ESP_EXCEPTION_H_

