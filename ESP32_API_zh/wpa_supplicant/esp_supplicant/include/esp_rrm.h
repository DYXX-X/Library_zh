/**
 * 版权所有2020 Espressif Systems（上海）私人有限公司
 *
 * 根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef _ESP_RRM_H
#define _ESP_RRM_H

#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  获取邻居报告的回调函数类型
  *
  * @param  ctx: 邻居报告上下文
  * @param  report: 邻居报告
  * @param  report_len: 邻居报告长度
  *
  * @return
  *    -无效
  */
typedef void (*neighbor_rep_request_cb)(void *ctx, const uint8_t *report, size_t report_len);

/**
  * @brief  向连接的AP发送无线电测量邻居报告请求
  *
  * @param  cb: 邻居报告的回调函数
  * @param  cb_ctx: 回调上下文
  *
  * @return
  *    -0:成功，否则失败
  */
int esp_rrm_send_neighbor_rep_request(neighbor_rep_request_cb cb,
				      void *cb_ctx);

#ifdef __cplusplus
}
#endif
#endif

