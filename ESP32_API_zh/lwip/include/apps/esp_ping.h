// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
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

#ifndef ESP_PING_H_
#define ESP_PING_H_

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

// gen_esp_err_to_name。py：将其包含为“esp_ping.h”，因为“components/lwip/include/apps/”在编译器路径中
// 而不是“组件/lwip/include”

#define ESP_ERR_PING_BASE               0xa000

#define ESP_ERR_PING_INVALID_PARAMS     ESP_ERR_PING_BASE + 0x01
#define ESP_ERR_PING_NO_MEM             ESP_ERR_PING_BASE + 0x02

#define ESP_PING_CHECK_OPTLEN(optlen, opttype) do { if ((optlen) < sizeof(opttype)) { return ESP_ERR_PING_INVALID_PARAMS; }}while(0)

typedef struct _ping_found {
    uint32_t resp_time;
    uint32_t timeout_count;
    uint32_t send_count;
    uint32_t recv_count;
    uint32_t err_count;
    uint32_t bytes;
    uint32_t total_bytes;
    uint32_t total_time;
    uint32_t min_time;
    uint32_t max_time;
    int8_t  ping_err;
} esp_ping_found;

typedef enum {
    PING_TARGET_IP_ADDRESS          = 50,   /**<目标IP地址*/
    PING_TARGET_IP_ADDRESS_COUNT    = 51,   /**<目标IP地址总数计数器*/
    PING_TARGET_RCV_TIMEO           = 52,   /**<接收超时（毫秒）*/
    PING_TARGET_DELAY_TIME          = 53,   /**<延迟时间（毫秒）*/
    PING_TARGET_ID                  = 54,   /**<标识符*/
    PING_TARGET_RES_FN              = 55,   /**<ping结果回调函数*/
    PING_TARGET_RES_RESET           = 56,   /**<ping结果统计重置*/
    PING_TARGET_DATA_LEN            = 57,   /**<ping数据长度*/
    PING_TARGET_IP_TOS              = 58,    /**<ping QOS*/
    PING_TARGET_IF_INDEX            = 59    /**<ping if索引*/
} ping_target_id_t;

typedef enum {
    PING_RES_TIMEOUT = 0,
    PING_RES_OK      = 1,
    PING_RES_FINISH  = 2,
} ping_res_t;

typedef void (* esp_ping_found_fn)(ping_target_id_t found_id, esp_ping_found *found_val);

/**
 * @brief  设置PING功能选项
 *
 * @param[in]  opt_id: 选项索引，50代表IP，51代表COUNT，52代表RCV TIMEOUT，53代表DELAY TIME，54代表ID
 * @param[in]  opt_val: 选项参数
 * @param[in]  opt_len: 期权长度
 *
 * @return
 *      - ESP_OK
 *      - ESP_ERR_PING_INVALID_PARAMS
 */
esp_err_t esp_ping_set_target(ping_target_id_t opt_id, void *opt_val, uint32_t opt_len);

/**
 * @brief  获取PING功能选项
 *
 * @param[in]  opt_id: 选项索引，50代表IP，51代表COUNT，52代表RCV TIMEOUT，53代表DELAY TIME，54代表ID
 * @param[in]  opt_val: 选项参数
 * @param[in]  opt_len: 期权长度
 *
 * @return
 *      - ESP_OK
 *      - ESP_ERR_PING_INVALID_PARAMS
 */
esp_err_t esp_ping_get_target(ping_target_id_t opt_id, void *opt_val, uint32_t opt_len);

/**
 * @brief  获取PING函数结果操作
 *
 * @param[in]  res_val: ping函数操作，1表示成功，0表示失败。res_len：响应字节res_time：响应时间
 *
 * @return
 *      - ESP_OK
 *      - ESP_ERR_PING_INVALID_PARAMS
 */
esp_err_t esp_ping_result(uint8_t res_val, uint16_t res_len, uint32_t res_time);

#ifdef __cplusplus
}
#endif

#endif /* ESP_PING_H_ */

