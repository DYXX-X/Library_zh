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

#ifndef __ESP_NOW_H__
#define __ESP_NOW_H__

#include <stdbool.h>
#include "esp_err.h"
#include "esp_wifi_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup WiFi_APIs WiFi相关API
  * @brief WiFi API
  */

/** @addtogroup WiFi_API@{
  */

/** \解组ESPNOW_APIs ESPNOW API
  * @brief ESP32 ESPNOW API
  *
  */

/** @addtogroup ESPNOW_API@{
  */

#define ESP_ERR_ESPNOW_BASE         (ESP_ERR_WIFI_BASE + 100) /*!< ESPNOW错误编号基数。*/
#define ESP_ERR_ESPNOW_NOT_INIT     (ESP_ERR_ESPNOW_BASE + 1) /*!< ESPNOW未初始化。*/
#define ESP_ERR_ESPNOW_ARG          (ESP_ERR_ESPNOW_BASE + 2) /*!< 参数无效*/
#define ESP_ERR_ESPNOW_NO_MEM       (ESP_ERR_ESPNOW_BASE + 3) /*!< 内存不足*/
#define ESP_ERR_ESPNOW_FULL         (ESP_ERR_ESPNOW_BASE + 4) /*!< ESPNOW同行列表已满*/
#define ESP_ERR_ESPNOW_NOT_FOUND    (ESP_ERR_ESPNOW_BASE + 5) /*!< 找不到ESPNOW对等方*/
#define ESP_ERR_ESPNOW_INTERNAL     (ESP_ERR_ESPNOW_BASE + 6) /*!< 内部错误*/
#define ESP_ERR_ESPNOW_EXIST        (ESP_ERR_ESPNOW_BASE + 7) /*!< ESPNOW同行已存在*/
#define ESP_ERR_ESPNOW_IF           (ESP_ERR_ESPNOW_BASE + 8) /*!< 接口错误*/

#define ESP_NOW_ETH_ALEN             6         /*!< ESPNOW对等MAC地址的长度*/
#define ESP_NOW_KEY_LEN              16        /*!< ESPNOW对等本地主密钥的长度*/

#define ESP_NOW_MAX_TOTAL_PEER_NUM   20        /*!< ESPNOW总对等体的最大数量*/
#define ESP_NOW_MAX_ENCRYPT_PEER_NUM 6         /*!< ESPNOW加密对等体的最大数量*/

#define ESP_NOW_MAX_DATA_LEN         250       /*!< 每次发送的ESPNOW数据的最大长度*/

/**
 * @brief 发送ESPNOW数据的状态。
 */
typedef enum {
    ESP_NOW_SEND_SUCCESS = 0,       /**<成功发送ESPNOW数据*/
    ESP_NOW_SEND_FAIL,              /**<发送ESPNOW数据失败*/
} esp_now_send_status_t;

/**
 * @brief ESPNOW对等信息参数。
 */
typedef struct esp_now_peer_info {
    uint8_t peer_addr[ESP_NOW_ETH_ALEN];    /**<ESPNOW对等MAC地址，也是站点或软ap的MAC地址*/
    uint8_t lmk[ESP_NOW_KEY_LEN];           /**<ESPNOW用于加密数据的对等本地主密钥*/
    uint8_t channel;                        /**<对等方用于发送/接收ESPNOW数据的Wi-Fi信道。如果值为0，则使用当前站或软ap所在的信道。否则，必须将其设置为站或软AP所在的信道。*/
    wifi_interface_t ifidx;                 /**<对等方用于发送/接收ESPNOW数据的Wi-Fi接口*/
    bool encrypt;                           /**<此对等方发送/接收的ESPNOW数据是否加密*/
    void *priv;                             /**<ESPNOW同行私人数据*/
} esp_now_peer_info_t;

/**
 * @brief 当前存在的ESPNOW对等体数。
 */
typedef struct esp_now_peer_num {
    int total_num;                           /**<ESPNOW对等体总数，最大值为ESP_NOW_MAX_Total_PEER_NUM*/
    int encrypt_num;                         /**<加密的ESPNOW对等体数量，最大值为ESP_NOW_MAX_ENCRYPT_PEER_NUM*/
} esp_now_peer_num_t;

/**
  * @brief     接收ESPNOW数据的回调功能
  * @param     mac_addr 对等MAC地址
  * @param     data 接收的数据
  * @param     data_len 接收数据长度
  */
typedef void (*esp_now_recv_cb_t)(const uint8_t *mac_addr, const uint8_t *data, int data_len);

/**
  * @brief     发送ESPNOW数据的回调功能
  * @param     mac_addr 对等MAC地址
  * @param     status 发送ESPNOW数据的状态（成功或失败）
  */
typedef void (*esp_now_send_cb_t)(const uint8_t *mac_addr, esp_now_send_status_t status);

/**
  * @brief     初始化ESPNOW函数
  *
  * @return
  *          -ESP_OK：成功
  *          -ESP_ERR_ESPNOW_INTERNAL：内部错误
  */
esp_err_t esp_now_init(void);

/**
  * @brief     取消初始化ESPNOW函数
  *
  * @return
  *          -ESP_OK：成功
  */
esp_err_t esp_now_deinit(void);

/**
  * @brief     获取ESPNOW版本
  *
  * @param     version  ESPNOW版本
  *
  * @return
  *          -ESP_OK：成功
  *          -ESP_ERR_ESPNOW_ARG：参数无效
  */
esp_err_t esp_now_get_version(uint32_t *version);

/**
  * @brief     注册接收ESPNOW数据的回调函数
  *
  * @param     cb  接收ESPNOW数据的回调函数
  *
  * @return
  *          -ESP_OK：成功
  *          -ESP_ERR_ESPNOW_NOT_INIT:ESPNOW未初始化
  *          -ESP_ERR_ESPNOW_INTERNAL：内部错误
  */
esp_err_t esp_now_register_recv_cb(esp_now_recv_cb_t cb);

/**
  * @brief     取消注册接收ESPNOW数据的回调函数
  *
  * @return
  *          -ESP_OK：成功
  *          -ESP_ERR_ESPNOW_NOT_INIT:ESPNOW未初始化
  */
esp_err_t esp_now_unregister_recv_cb(void);

/**
  * @brief     注册发送ESPNOW数据的回调函数
  *
  * @param     cb  发送ESPNOW数据的回调函数
  *
  * @return
  *          -ESP_OK：成功
  *          -ESP_ERR_ESPNOW_NOT_INIT:ESPNOW未初始化
  *          -ESP_ERR_ESPNOW_INTERNAL：内部错误
  */
esp_err_t esp_now_register_send_cb(esp_now_send_cb_t cb);

/**
  * @brief     取消注册发送ESPNOW数据的回调函数
  *
  * @return
  *          -ESP_OK：成功
  *          -ESP_ERR_ESPNOW_NOT_INIT:ESPNOW未初始化
  */
esp_err_t esp_now_unregister_send_cb(void);

/**
  * @brief     发送ESPNOW数据
  *
  * @attention 1.如果peer_addr不为NULL，则将数据发送到MAC地址与peer_ddr匹配的对等端
  * @attention 2.如果peer_addr为NULL，则向添加到对等列表中的所有对等方发送数据
  * @attention 3.数据的最大长度必须小于ESP_NOW_MAX_data_LEN
  * @attention 4.返回esp_now_send后，data参数指向的缓冲区不需要有效
  *
  * @param     peer_addr  对等MAC地址
  * @param     data  要发送的数据
  * @param     len  数据长度
  *
  * @return
  *          -ESP_OK：成功
  *          -ESP_ERR_ESPNOW_NOT_INIT:ESPNOW未初始化
  *          -ESP_ERR_ESPNOW_ARG：参数无效
  *          -ESP_ERR_ESPNOW_INTERNAL：内部错误
  *          -ESP_ERR_ESPNOW_NO_MEM：内存不足
  *          -ESP_ERR_ESPNOW_NOT_FOUND:找不到对等方
  *          -ESP_ERR_ESPNOW_IF：当前WiFi接口与对等端不匹配
  */
esp_err_t esp_now_send(const uint8_t *peer_addr, const uint8_t *data, size_t len);

/**
  * @brief     添加对等列表
  *
  * @param     peer  对等信息
  *
  * @return
  *          -ESP_OK：成功
  *          -ESP_ERR_ESPNOW_NOT_INIT:ESPNOW未初始化
  *          -ESP_ERR_ESPNOW_ARG：参数无效
  *          -ESP_ERR_ESPNOW_FULL:对等列表已满
  *          -ESP_ERR_ESPNOW_NO_MEM：内存不足
  *          -ESP_ERR_ESPNOW_EXIST:对等方已存在
  */
esp_err_t esp_now_add_peer(const esp_now_peer_info_t *peer);

/**
  * @brief     从对等方列表中删除对等方
  *
  * @param     peer_addr  对等MAC地址
  *
  * @return
  *          -ESP_OK：成功
  *          -ESP_ERR_ESPNOW_NOT_INIT:ESPNOW未初始化
  *          -ESP_ERR_ESPNOW_ARG：参数无效
  *          -ESP_ERR_ESPNOW_NOT_FOUND:找不到对等方
  */
esp_err_t esp_now_del_peer(const uint8_t *peer_addr);

/**
  * @brief     修改对等方
  *
  * @param     peer  对等信息
  *
  * @return
  *          -ESP_OK：成功
  *          -ESP_ERR_ESPNOW_NOT_INIT:ESPNOW未初始化
  *          -ESP_ERR_ESPNOW_ARG：参数无效
  *          -ESP_ERR_ESPNOW_FULL:对等列表已满
  */
esp_err_t esp_now_mod_peer(const esp_now_peer_info_t *peer);

/**
  * @brief     从对等方列表中获取MAC地址与peer_addr匹配的对等方
  *
  * @param     peer_addr  对等MAC地址
  * @param     peer  对等信息
  *
  * @return
  *          -ESP_OK：成功
  *          -ESP_ERR_ESPNOW_NOT_INIT:ESPNOW未初始化
  *          -ESP_ERR_ESPNOW_ARG：参数无效
  *          -ESP_ERR_ESPNOW_NOT_FOUND:找不到对等方
  */
esp_err_t esp_now_get_peer(const uint8_t *peer_addr, esp_now_peer_info_t *peer);

/**
  * @brief     从对等体列表中获取对等体。仅返回地址为单播的对等方，对于多播/广播地址，函数将忽略并尝试在对等方列表中查找下一个。
  *
  * @param     from_head  是否从列表头获取
  * @param     peer  对等信息
  *
  * @return
  *          -ESP_OK：成功
  *          -ESP_ERR_ESPNOW_NOT_INIT:ESPNOW未初始化
  *          -ESP_ERR_ESPNOW_ARG：参数无效
  *          -ESP_ERR_ESPNOW_NOT_FOUND:找不到对等方
  */
esp_err_t esp_now_fetch_peer(bool from_head, esp_now_peer_info_t *peer);

/**
  * @brief     对等体是否存在
  *
  * @param     peer_addr  对等MAC地址
  *
  * @return
  *          -true：对等体存在
  *          -false：对等方不存在
  */
bool esp_now_is_peer_exist(const uint8_t *peer_addr);

/**
  * @brief     获取对等方的数量
  *
  * @param     num  对等方数量
  *
  * @return
  *          -ESP_OK：成功
  *          -ESP_ERR_ESPNOW_NOT_INIT:ESPNOW未初始化
  *          -ESP_ERR_ESPNOW_ARG：参数无效
  */
esp_err_t esp_now_get_peer_num(esp_now_peer_num_t *num);

/**
  * @brief     设置主密钥
  *
  * @param     pmk  主主密钥
  *
  * @attention 1.主密钥用于加密本地主密钥
  *
  * @return
  *          -ESP_OK：成功
  *          -ESP_ERR_ESPNOW_NOT_INIT:ESPNOW未初始化
  *          -ESP_ERR_ESPNOW_ARG：参数无效
  */
esp_err_t esp_now_set_pmk(const uint8_t *pmk);

/**
  * @brief     为sta_disconnected电源管理设置esp_now唤醒窗口
  *
  * @param     window  芯片每间隔唤醒多少微秒，从0到65535不等
  *
  * @attention 1.仅当启用ESP_WIFI_STA_DISCONNECTED_PM_ENABLE时，此配置才能工作
  * @attention 2.此配置仅适用于站模式和断开状态
  * @attention 3.如果不止一个模块配置了其唤醒窗口，芯片将选择最大的模块保持唤醒
  * @attention 4.如果间隔和窗口之间的间隔小于5ms，芯片将一直保持唤醒
  * @attention 5.如果从未配置wake_window，则芯片在使用esp_now后将在断开连接时保持唤醒
  *
  * @return
  *          -ESP_OK：成功
  *          -ESP_ERR_ESPNOW_NOT_INIT:ESPNOW未初始化
  */
esp_err_t esp_now_set_wake_window(uint16_t window);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __ESP_NOW_H__ */

