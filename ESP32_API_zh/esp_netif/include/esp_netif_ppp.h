// 版权所有2019 Espressif Systems（上海）私人有限公司
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
//

#ifndef _ESP_NETIF_PPP_H_
#define _ESP_NETIF_PPP_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @brief PPP事件库*/
ESP_EVENT_DECLARE_BASE(NETIF_PPP_STATUS);

/** @brief PPP网络接口配置结构
 *
 */
typedef struct esp_netif_ppp_config {
    bool ppp_phase_event_enabled;  /**<启用来自PPP阶段变更的事件*/
    bool ppp_error_event_enabled;  /**<启用主PPP状态机产生错误的事件*/
} esp_netif_ppp_config_t;

/** @brief PHASE相关事件的事件id偏移
 *
 * 所有PPP相关事件都是从“netif_PPP_STATUS”下的esp netif生成的，此偏移量定义有助于区分错误事件和相位事件
 */
#define NETIF_PP_PHASE_OFFSET (0x100)

/** @brief 内部错误的事件id偏移量
 *
 */
#define NETIF_PPP_INTERNAL_ERR_OFFSET (0x200)

/** @brief 不同PPP相关事件的事件ID
 *
 */
typedef enum {
    NETIF_PPP_ERRORNONE        = 0,  /* 没有错误。*/
    NETIF_PPP_ERRORPARAM       = 1,  /* 无效参数。*/
    NETIF_PPP_ERROROPEN        = 2,  /* 无法打开PPP会话。*/
    NETIF_PPP_ERRORDEVICE      = 3,  /* PPP的I/O设备无效。*/
    NETIF_PPP_ERRORALLOC       = 4,  /* 无法分配资源。*/
    NETIF_PPP_ERRORUSER        = 5,  /* 用户中断。*/
    NETIF_PPP_ERRORCONNECT     = 6,  /* 连接丢失。*/
    NETIF_PPP_ERRORAUTHFAIL    = 7,  /* 身份验证质询失败。*/
    NETIF_PPP_ERRORPROTOCOL    = 8,  /* 未能满足协议。*/
    NETIF_PPP_ERRORPEERDEAD    = 9,  /* 连接超时*/
    NETIF_PPP_ERRORIDLETIMEOUT = 10, /* 空闲超时*/
    NETIF_PPP_ERRORCONNECTTIME = 11, /* 已达到最大连接时间*/
    NETIF_PPP_ERRORLOOPBACK    = 12, /* 检测到环回*/
    NETIF_PPP_PHASE_DEAD         = NETIF_PP_PHASE_OFFSET +  0,
    NETIF_PPP_PHASE_MASTER       = NETIF_PP_PHASE_OFFSET +  1,
    NETIF_PPP_PHASE_HOLDOFF      = NETIF_PP_PHASE_OFFSET +  2,
    NETIF_PPP_PHASE_INITIALIZE   = NETIF_PP_PHASE_OFFSET +  3,
    NETIF_PPP_PHASE_SERIALCONN   = NETIF_PP_PHASE_OFFSET +  4,
    NETIF_PPP_PHASE_DORMANT      = NETIF_PP_PHASE_OFFSET +  5,
    NETIF_PPP_PHASE_ESTABLISH    = NETIF_PP_PHASE_OFFSET +  6,
    NETIF_PPP_PHASE_AUTHENTICATE = NETIF_PP_PHASE_OFFSET +  7,
    NETIF_PPP_PHASE_CALLBACK     = NETIF_PP_PHASE_OFFSET +  8,
    NETIF_PPP_PHASE_NETWORK      = NETIF_PP_PHASE_OFFSET +  9,
    NETIF_PPP_PHASE_RUNNING      = NETIF_PP_PHASE_OFFSET +  10,
    NETIF_PPP_PHASE_TERMINATE    = NETIF_PP_PHASE_OFFSET +  11,
    NETIF_PPP_PHASE_DISCONNECT   = NETIF_PP_PHASE_OFFSET +  12,
    NETIF_PPP_CONNECT_FAILED     = NETIF_PPP_INTERNAL_ERR_OFFSET + 0,
} esp_netif_ppp_status_event_t;

/** @brief 不同授权类型的定义
 *
 */
typedef enum {
    NETIF_PPP_AUTHTYPE_NONE =      0x00,
    NETIF_PPP_AUTHTYPE_PAP =       0x01,
    NETIF_PPP_AUTHTYPE_CHAP =      0x02,
    NETIF_PPP_AUTHTYPE_MSCHAP =    0x04,
    NETIF_PPP_AUTHTYPE_MSCHAP_V2 = 0x08,
    NETIF_PPP_AUTHTYPE_EAP =       0x10,
} esp_netif_auth_type_t;

/** @brief 为提供的esp netif设置身份验证参数。
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param[in]  authtype 授权类型
 * @param[in]  user 用户名
 * @param[in]  passwd 暗语
 *
 * @return     成功时为ESP_OK，如果提供的NETIF不是PPP类型或NETIF为空，则为ESP_ERR_ESP_NETIF_INVALID_PARAMS
 */
esp_err_t esp_netif_ppp_set_auth(esp_netif_t *netif, esp_netif_auth_type_t authtype, const char *user, const char *passwd);

/** @brief 为提供的esp netif设置公共参数。
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param[in]  config 指向PPP netif配置结构的指针
 *
 * @return     成功时为ESP_OK，如果提供的NETIF不是PPP类型或NETIF为空，则为ESP_ERR_ESP_NETIF_INVALID_PARAMS
 */
esp_err_t esp_netif_ppp_set_params(esp_netif_t *netif, const esp_netif_ppp_config_t *config);

/** @brief 获取在提供的esp netif中配置的参数。
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param[out]  config 指向PPP netif配置结构的指针
 *
 * @return     成功时为ESP_OK，如果提供的NETIF不是PPP类型或NETIF为空，则为ESP_ERR_ESP_NETIF_INVALID_PARAMS
 */
esp_err_t esp_netif_ppp_get_params(esp_netif_t *netif, esp_netif_ppp_config_t *config);

#ifdef __cplusplus
}
#endif

#endif //_ESP_NETIF_PPP_H_

