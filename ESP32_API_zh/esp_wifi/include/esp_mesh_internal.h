// 版权所有2017-2018 Espressif Systems（上海）私人有限公司
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

#ifndef __ESP_MESH_INTERNAL_H__
#define __ESP_MESH_INTERNAL_H__

#include "esp_err.h"
#include "esp_mesh.h"
#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include "esp_private/wifi.h"
#include "esp_wifi_crypto_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************
 *                常量
 *******************************************************/

/*******************************************************
 *                结构
 *******************************************************/
typedef struct {
    int scan;          /**<成为根用户之前的最小扫描时间，默认值：10*/
    int vote;          /**<自我修复的最大投票次数，默认值：1000*/
    int fail;          /**<父级选择失败次数，如果扫描时间达到此值，设备将与关联的子级断开连接并加入自我修复。默认值：60*/
    int monitor_ie;    /**<更新自己的网络IE之前，父网络IE更改的可接受次数。默认值：3*/
} mesh_attempts_t;

typedef struct {
    int duration_ms;   /* 父级弱RSSI监测持续时间，如果RSSI在此持续时间内持续较弱，则设备将搜索新的父级。*/
    int cnx_rssi;      /* 保持与父级良好连接的RSSI阈值。如果设置的值大于-120 dBm，则将配备一个计时器，以在duration_ms的时间段内监控父RSSI。*/
    int select_rssi;   /* 父级选择的RSSI阈值。该值应大于switch_rssi。*/
    int switch_rssi;   /* 当RSSI大于此设置阈值时，解除与当前父级的关联并切换到新父级。*/
    int backoff_rssi;  /* 连接到根的RSSI阈值*/
} mesh_switch_parent_t;

typedef struct {
    int high;
    int medium;
    int low;
} mesh_rssi_threshold_t;

/**
 * @brief 网状网络IE
 */
typedef struct {
    /**<mesh网络IE头*/
    uint8_t eid;             /**<元素ID*/
    uint8_t len;             /**<元件长度*/
    uint8_t oui[3];          /**<组织标识符*/
    /**<网状网络IE内容*/
    uint8_t type;            /**ESP定义的IE类型*/
    uint8_t encrypted : 1;   /**<网状网络IE是否加密*/
    uint8_t version : 7;     /**<mesh网络IE版本*/
    /**<内容*/
    uint8_t mesh_type;       /**<网格设备类型*/
    uint8_t mesh_id[6];      /**<网格ID*/
    uint8_t layer_cap;       /**<最大层*/
    uint8_t layer;           /**<当前层*/
    uint8_t assoc_cap;       /**<网格AP的最大连接数*/
    uint8_t assoc;           /**<电流连接*/
    uint8_t leaf_cap;        /**<叶片容量*/
    uint8_t leaf_assoc;      /**<当前连接的叶数*/
    uint16_t root_cap;       /**<根容量*/
    uint16_t self_cap;       /**<自身容量*/
    uint16_t layer2_cap;     /**<第2层容量*/
    uint16_t scan_ap_num;    /**<扫描AP的数量*/
    int8_t rssi;             /**<父级RSSI*/
    int8_t router_rssi;      /**<路由器的RSSI*/
    uint8_t flag;            /**<联网标志*/
    uint8_t rc_addr[6];      /**<根地址*/
    int8_t rc_rssi;          /**<根RSSI*/
    uint8_t vote_addr[6];    /**<投票人地址*/
    int8_t vote_rssi;        /**<投票路由器RSSI*/
    uint8_t vote_ttl;        /**<投票ttl*/
    uint16_t votes;          /**<票*/
    uint16_t my_votes;       /**<我的选票*/
    uint8_t reason;          /**<原因*/
    uint8_t child[6];        /**<子地址*/
    uint8_t toDS;            /**<至DS状态*/
} __attribute__((packed)) mesh_assoc_t;

typedef struct {
    uint16_t layer_cap;
    uint16_t layer;
} mesh_chain_layer_t;

typedef struct {
    mesh_assoc_t tree;
    mesh_chain_layer_t chain;
} __attribute__((packed)) mesh_chain_assoc_t;

/**
 * @brief 网格PS职责
 */
typedef struct {
    uint8_t device;
    uint8_t parent;
    struct {
        bool used;
        uint8_t duty;
        uint8_t mac[6];
    } child[ESP_WIFI_MAX_CONN_NUM];
} esp_mesh_ps_duties_t;

/*******************************************************
 *                功能定义
 *******************************************************/
/**
 * @brief      设置网格软AP信标间隔
 *
 * @param[in]  interval  信标间隔（毫秒）（100毫秒~ 60000毫秒）
 *
 * @return
 *    - ESP_OK
 *    - ESP_FAIL
 *    - ESP_ERR_WIFI_ARG
 */
esp_err_t esp_mesh_set_beacon_interval(int interval_ms);

/**
 * @brief      获取网格软AP信标间隔
 *
 * @param[out] interval  信标间隔（毫秒）
 *
 * @return
 *    - ESP_OK
 */
esp_err_t esp_mesh_get_beacon_interval(int *interval_ms);

/**
 * @brief     设置网状自组织网络的尝试
 *
 * @param[in] attempts
 *
 * @return
 *    - ESP_OK
 *    - ESP_FAIL
 */
esp_err_t esp_mesh_set_attempts(mesh_attempts_t *attempts);

/**
 * @brief      尝试网状自组织网络
 *
 * @param[out] attempts
 *
 * @return
 *    - ESP_OK
 *    - ESP_ERR_MESH_ARGUMENT
 */
esp_err_t esp_mesh_get_attempts(mesh_attempts_t *attempts);

/**
 * @brief      设置父开关的参数
 *
 * @param[in]  paras  父开关的参数
 *
 * @return
 *    - ESP_OK
 *    - ESP_ERR_MESH_ARGUMENT
 */
esp_err_t esp_mesh_set_switch_parent_paras(mesh_switch_parent_t *paras);

/**
 * @brief      获取父交换机的参数
 *
 * @param[out] paras  父开关的参数
 *
 * @return
 *    - ESP_OK
 *    - ESP_ERR_MESH_ARGUMENT
 */
esp_err_t esp_mesh_get_switch_parent_paras(mesh_switch_parent_t *paras);

/**
 * @brief      设置RSSI阈值
 *             -默认的高RSSI阈值为-78 dBm。
 *             -默认的中等RSSI阈值为-82dBm。
 *             -默认的低RSSI阈值为-85dBm。
 *
 * @param[in]  threshold  RSSI阈值
 *
 * @return
 *    - ESP_OK
 *    - ESP_ERR_MESH_ARGUMENT
 */
esp_err_t esp_mesh_set_rssi_threshold(const mesh_rssi_threshold_t *threshold);

/**
 * @brief      获取RSSI阈值
 *
 * @param[out] threshold  RSSI阈值
 *
 * @return
 *    - ESP_OK
 *    - ESP_ERR_MESH_ARGUMENT
 */
esp_err_t esp_mesh_get_rssi_threshold(mesh_rssi_threshold_t *threshold);

/**
 * @brief      将最小速率设置为6 Mbps
 *
 * @attention  应在启动Wi-Fi之前调用此API。
 *
 * @param[in]  is_6m  是否启用
 *
 * @return
 *    - ESP_OK
 */
esp_err_t esp_mesh_set_6m_rate(bool is_6m);

/**
 * @brief      打印txQ等待的次数
 *
 * @return
 *    - ESP_OK
 *    - ESP_FAIL
 */
esp_err_t esp_mesh_print_txQ_waiting(void);

/**
 * @brief      打印rxQ等待的次数
 *
 * @return
 *    - ESP_OK
 *    - ESP_FAIL
 */
esp_err_t esp_mesh_print_rxQ_waiting(void);

/**
 * @brief      设置被动扫描时间
 *
 * @param[in]  interval_ms  被动扫描时间（毫秒）
 *
 * @return
 *    - ESP_OK
 *    - ESP_FAIL
 *    - ESP_ERR_ARGUMENT
 */
esp_err_t esp_mesh_set_passive_scan_time(int time_ms);

/**
 * @brief      获取被动扫描时间
 *
 * @return     interval_ms被动扫描时间（毫秒）
 */
int esp_mesh_get_passive_scan_time(void);

/**
 * @brief      设置通告间隔
 *             -默认的短间隔为500毫秒。
 *             -默认的长间隔为3000毫秒。
 *
 * @param[in]  short_ms  应大于默认值
 * @param[in]  long_ms  应大于默认值
 *
 * @return
 *    - ESP_OK
 */
esp_err_t esp_mesh_set_announce_interval(int short_ms, int long_ms);

/**
 * @brief      获取通告间隔
 *
 * @param[out] short_ms  短时间间隔
 * @param[out] long_ms  长时间间隔
 *
 * @return
 *    - ESP_OK
 */
esp_err_t esp_mesh_get_announce_interval(int *short_ms, int *long_ms);

/**
  * @brief      获取设备、家长和孩子的运行职责
 *
 * @return
 *    - ESP_OK
 */
esp_err_t esp_mesh_ps_get_duties(esp_mesh_ps_duties_t* ps_duties);

/**
 * @brief      启用网格打印扫描结果
 *
 * @param[in]  enable  是否启用
 *
 * @return
 *    - ESP_OK
 */
esp_err_t esp_mesh_print_scan_result(bool enable);
#ifdef __cplusplus
}
#endif
#endif /* __ESP_MESH_INTERNAL_H__ */

