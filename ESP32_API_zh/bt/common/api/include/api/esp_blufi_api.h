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

#ifndef __ESP_BLUFI_API_H__
#define __ESP_BLUFI_API_H__

#include "esp_err.h"
#include "esp_wifi_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ESP_BLUFI_EVENT_INIT_FINISH = 0,                     /*<! 当BLUFI初始化完成时，会发生此事件*/
    ESP_BLUFI_EVENT_DEINIT_FINISH,                       /*<! BLUFI卸载完成后，会发生此事件*/
    ESP_BLUFI_EVENT_SET_WIFI_OPMODE,                     /*<! 当手机设置ESP32 wifi操作模式（AP/STA/AP_STA）时，会发生此事件*/
    ESP_BLUFI_EVENT_BLE_CONNECT,                         /*<! 当手机通过BLE连接到ESP32时，会发生此事件*/
    ESP_BLUFI_EVENT_BLE_DISCONNECT,                      /*<! 当手机与BLE断开连接时，会发生此事件*/
    ESP_BLUFI_EVENT_REQ_CONNECT_TO_AP,                   /*<! 当电话请求ESP32的STA连接到AP时，会发生此事件*/
    ESP_BLUFI_EVENT_REQ_DISCONNECT_FROM_AP,              /*<! 当电话请求ESP32的STA与AP断开连接时，会发生此事件*/
    ESP_BLUFI_EVENT_GET_WIFI_STATUS,                     /*<! 当手机获得ESP32 wifi状态时，会发生此事件*/
    ESP_BLUFI_EVENT_DEAUTHENTICATE_STA,                  /*<! 当手机从SOFTAP取消对sta的身份验证时，会发生此事件*/
    /* recv数据*/
    ESP_BLUFI_EVENT_RECV_STA_BSSID,                      /*<! 当手机向ESP32发送STA BSSID以进行连接时，会发生此事件*/
    ESP_BLUFI_EVENT_RECV_STA_SSID,                       /*<! 当手机向ESP32发送STA SSID以进行连接时，会发生此事件*/
    ESP_BLUFI_EVENT_RECV_STA_PASSWD,                     /*<! 当手机向ESP32发送STA密码以进行连接时，会发生此事件*/
    ESP_BLUFI_EVENT_RECV_SOFTAP_SSID,                    /*<! 当手机向ESP32发送SOFTAP SSID以启动SOFTAP时，会发生此事件*/
    ESP_BLUFI_EVENT_RECV_SOFTAP_PASSWD,                  /*<! 当手机向ESP32发送SOFTAP密码以启动SOFTAP时，会发生此事件*/
    ESP_BLUFI_EVENT_RECV_SOFTAP_MAX_CONN_NUM,            /*<! 当手机向ESP32发送SOFTAP最大连接号码以启动SOFTAP时，会发生此事件*/
    ESP_BLUFI_EVENT_RECV_SOFTAP_AUTH_MODE,               /*<! 当手机向ESP32发送SOFTAP身份验证模式以启动SOFTAP时，会发生此事件*/
    ESP_BLUFI_EVENT_RECV_SOFTAP_CHANNEL,                 /*<! 当手机向ESP32发送SOFTAP频道以启动SOFTAP时，会发生此事件*/
    ESP_BLUFI_EVENT_RECV_USERNAME,                       /*<! 当手机向ESP32发送用户名时，会发生此事件*/
    ESP_BLUFI_EVENT_RECV_CA_CERT,                        /*<! 当手机向ESP32发送CA证书时，会发生此事件*/
    ESP_BLUFI_EVENT_RECV_CLIENT_CERT,                    /*<! 当手机向ESP32发送客户端证书时，会发生此事件*/
    ESP_BLUFI_EVENT_RECV_SERVER_CERT,                    /*<! 当手机向ESP32发送服务器证书时，会发生此事件*/
    ESP_BLUFI_EVENT_RECV_CLIENT_PRIV_KEY,                /*<! 当手机向ESP32发送客户端私钥时，会发生此事件*/
    ESP_BLUFI_EVENT_RECV_SERVER_PRIV_KEY,                /*<! 当手机向ESP32发送服务器私钥时，会发生此事件*/
    ESP_BLUFI_EVENT_RECV_SLAVE_DISCONNECT_BLE,           /*<! 当手机向ESP32发送断开键时，会发生此事件*/
    ESP_BLUFI_EVENT_GET_WIFI_LIST,                       /*<! 当手机向ESP32发送获取wifi列表命令时，会发生此事件*/
    ESP_BLUFI_EVENT_REPORT_ERROR,                        /*<! 当Blufi报告错误时，会发生此事件*/
    ESP_BLUFI_EVENT_RECV_CUSTOM_DATA,                    /*<! 当手机向ESP32发送自定义数据时，会发生此事件*/
} esp_blufi_cb_event_t;

///BLUFI配置状态
typedef enum {
    ESP_BLUFI_STA_CONN_SUCCESS = 0x00,
    ESP_BLUFI_STA_CONN_FAIL    = 0x01,
} esp_blufi_sta_conn_state_t;

///BLUFI初始化状态
typedef enum {
    ESP_BLUFI_INIT_OK = 0,
    ESP_BLUFI_INIT_FAILED,
} esp_blufi_init_state_t;

///BLUFI卸载状态
typedef enum {
    ESP_BLUFI_DEINIT_OK = 0,
    ESP_BLUFI_DEINIT_FAILED,
} esp_blufi_deinit_state_t;

typedef enum {
    ESP_BLUFI_SEQUENCE_ERROR = 0,
    ESP_BLUFI_CHECKSUM_ERROR,
    ESP_BLUFI_DECRYPT_ERROR,
    ESP_BLUFI_ENCRYPT_ERROR,
    ESP_BLUFI_INIT_SECURITY_ERROR,
    ESP_BLUFI_DH_MALLOC_ERROR,
    ESP_BLUFI_DH_PARAM_ERROR,
    ESP_BLUFI_READ_PARAM_ERROR,
    ESP_BLUFI_MAKE_PUBLIC_ERROR,
    ESP_BLUFI_DATA_FORMAT_ERROR,
} esp_blufi_error_state_t;

/**
 * @brief BLUFI额外信息结构
 */
typedef struct {
    //火车站
    uint8_t sta_bssid[6];           /*!< 车站接口BSSID*/
    bool sta_bssid_set;             /*!< 是车站接口集的BSSID*/
    uint8_t *sta_ssid;              /*!< 车站接口SSID*/
    int sta_ssid_len;               /*!< 站接口SSID长度*/
    uint8_t *sta_passwd;            /*!< 车站接口密码*/
    int sta_passwd_len;             /*!< 车站接口密码长度*/
    uint8_t *softap_ssid;           /*!< 软ap接口的SSID*/
    int softap_ssid_len;            /*!< 软ap接口的SSID长度*/
    uint8_t *softap_passwd;         /*!< 车站接口密码*/
    int softap_passwd_len;          /*!< 车站接口密码长度*/
    uint8_t softap_authmode;        /*!< 软ap接口的认证模式*/
    bool softap_authmode_set;       /*!< 是否设置了软ap接口的身份验证模式*/
    uint8_t softap_max_conn_num;    /*!< 软ap接口的最大连接数*/
    bool softap_max_conn_num_set;   /*!< 是软ap接口集的最大连接数*/
    uint8_t softap_channel;         /*!< 软ap接口通道*/
    bool softap_channel_set;        /*!< 是否设置了软ap接口的通道*/
} esp_blufi_extra_info_t;

/** @brief WiFi AP说明*/
typedef struct {
    uint8_t ssid[33];                     /**<AP的SSID*/
    int8_t  rssi;                         /**<AP信号强度*/
} esp_blufi_ap_record_t;

///蓝牙地址长度
#define ESP_BD_ADDR_LEN     6
///蓝牙设备地址
typedef uint8_t esp_bd_addr_t[ESP_BD_ADDR_LEN];

/**
 * @brief BLUFI回调参数联合
 */
typedef union {
    /**
	 * @brief ESP_BLUFI_EVENT_INIT_FINISH
	 */
    struct blufi_init_finish_evt_param {
        esp_blufi_init_state_t state;				/*!< 初始状态*/
    } init_finish;									/*!< ESP_Blufi_EVENT_INIT_FINISH的Blufi回调参数*/

    /**
	 * @brief ESP_BLUFI_EVENT_DEINIT_FINISH
	 */
    struct blufi_deinit_finish_evt_param {
        esp_blufi_deinit_state_t state;				/*!< 取消初始状态*/
    } deinit_finish;								/*!< ESP_Blufi_EVENT_INIT_FINISH的Blufi回调参数*/

    /**
     * @brief ESP_BLUFI_EVENT_SET_WIFI_MODE
     */
    struct blufi_set_wifi_mode_evt_param {
        wifi_mode_t op_mode;                        /*!< Wifi操作模式*/
    } wifi_mode;									/*!< ESP_Blufi_EVENT_INIT_FINISH的Blufi回调参数*/

    /**
     * @brief ESP_BLUFI_EVENT_CONNECT
	 */
    struct blufi_connect_evt_param {
        esp_bd_addr_t remote_bda;                   /*!< Blufi远程蓝牙设备地址*/
        uint8_t    server_if;                       /*!< 服务器接口*/
        uint16_t   conn_id;                         /*!< 连接id*/
    } connect;									    /*!< ESP_Blufi_EVENT_CONNECT的Blufi回调参数*/

    /**
     * @brief ESP_BLUFI_EVENT_DISCONNECT
	 */
    struct blufi_disconnect_evt_param {
        esp_bd_addr_t remote_bda;                   /*!< Blufi远程蓝牙设备地址*/
    } disconnect;									/*!< ESP_Blufi_EVENT_DISCONNECT的Blufi回调参数*/

    /* ESP_BLUFI_EVENT_REQ_WIFI_CONNECT */          /* 无回调参数*/
    /* ESP_BLUFI_EVENT_REQ_WIFI_DISCONNECT */       /* 无回调参数*/

    /**
     * @brief ESP_BLUFI_EVENT_RECV_STA_BSSID
     */
    struct blufi_recv_sta_bssid_evt_param {
        uint8_t bssid[6];                           /*!< BSSID */
    } sta_bssid;                                    /*!< ESP_Blufi_EVENT_RECV_STA_BSSID的Blufi回调参数*/

    /**
     * @brief ESP_BLUFI_EVENT_RECV_STA_SSID
     */
    struct blufi_recv_sta_ssid_evt_param {
        uint8_t *ssid;                              /*!< SSID */
        int ssid_len;                               /*!< SSID长度*/
    } sta_ssid;                                     /*!< ESP_Blufi_EVENT_RECV_STA_SID的Blufi回调参数*/

    /**
     * @brief ESP_BLUFI_EVENT_RECV_STA_PASSWD
     */
    struct blufi_recv_sta_passwd_evt_param {
        uint8_t *passwd;                            /*!< 暗语*/
        int passwd_len;                             /*!< 密码长度*/
    } sta_passwd;                                   /*!< ESP_Blufi_EVENT_RECV_STA_PASSWD的Blufi回调参数*/

    /**
     * @brief ESP_BLUFI_EVENT_RECV_SOFTAP_SSID
     */
    struct blufi_recv_softap_ssid_evt_param {
        uint8_t *ssid;                              /*!< SSID */
        int ssid_len;                               /*!< SSID长度*/
    } softap_ssid;                                  /*!< ESP_Blufi_EVENT_RECV_SOFTAP_SSID的Blufi回调参数*/

    /**
     * @brief ESP_BLUFI_EVENT_RECV_SOFTAP_PASSWD
     */
    struct blufi_recv_softap_passwd_evt_param {
        uint8_t *passwd;                            /*!< 暗语*/
        int passwd_len;                             /*!< 密码长度*/
    } softap_passwd;                                /*!< ESP_Blufi_EVENT_RECV_SOFTAP_PASSWD的Blufi回调参数*/

    /**
     * @brief ESP_BLUFI_EVENT_RECV_SOFTAP_MAX_CONN_NUM
     */
    struct blufi_recv_softap_max_conn_num_evt_param {
        int max_conn_num;                           /*!< SSID */
    } softap_max_conn_num;                          /*!< ESP_Blufi_EVENT_RECV_SOFTAP_MAX_CONN_NUM的Blufi回调参数*/

    /**
     * @brief ESP_BLUFI_EVENT_RECV_SOFTAP_AUTH_MODE
     */
    struct blufi_recv_softap_auth_mode_evt_param {
        wifi_auth_mode_t auth_mode;                 /*!< 身份验证模式*/
    } softap_auth_mode;                             /*!< ESP_Blufi_EVENT_RECV_SOFTAP_AUTH_MODE的Blufi回调参数*/

    /**
     * @brief ESP_BLUFI_EVENT_RECV_SOFTAP_CHANNEL
     */
    struct blufi_recv_softap_channel_evt_param {
        uint8_t channel;                            /*!< 身份验证模式*/
    } softap_channel;                             /*!< ESP_Blufi_EVENT_RECV_SOFTAP_CHANNEL的Blufi回调参数*/

    /**
     * @brief ESP_BLUFI_EVENT_RECV_USERNAME
     */
    struct blufi_recv_username_evt_param {
        uint8_t *name;                              /*!< 用户名点*/
        int name_len;                               /*!< 用户名长度*/
    } username;                                     /*!< ESP_Blufi_EVENT_RECV_USERNAME的Blufi回调参数*/

    /**
     * @brief ESP_BLUFI_EVENT_RECV_CA_CERT
     */
    struct blufi_recv_ca_evt_param {
        uint8_t *cert;                              /*!< CA证书点*/
        int cert_len;                               /*!< CA证书长度*/
    } ca;                                           /*!< ESP_Blufi_EVENT_RECV_CA_CERT的Blufi回调参数*/

    /**
     * ESP_BLUFI_EVENT_RECV_CLIENT_CERT
     */
    struct blufi_recv_client_cert_evt_param {
        uint8_t *cert;                              /*!< 客户端证书点*/
        int cert_len;                               /*!< 客户端证书长度*/
    } client_cert;                                  /*!< ESP_Blufi_EVENT_RECV_CLIENT_CERT的Blufi回调参数*/

    /**
     * ESP_BLUFI_EVENT_RECV_SERVER_CERT
     */
    struct blufi_recv_server_cert_evt_param {
        uint8_t *cert;                              /*!< 客户端证书点*/
        int cert_len;                               /*!< 客户端证书长度*/
    } server_cert;                                  /*!< ESP_Blufi_EVENT_RECV_SERVER_CERT的Blufi回调参数*/

    /**
     * ESP_BLUFI_EVENT_RECV_CLIENT_PRIV_KEY
     */
    struct blufi_recv_client_pkey_evt_param {
        uint8_t *pkey;                              /*!< 客户端私钥点，如果客户端证书不包含密钥*/
        int pkey_len;                               /*!< 客户端私钥长度*/
    } client_pkey;                                  /*!< ESP_Blufi_EVENT_RECV_CLIENT_PRIV_KEY的Blufi回调参数*/
    /**
     * ESP_BLUFI_EVENT_RECV_SERVER_PRIV_KEY
     */
    struct blufi_recv_server_pkey_evt_param {
        uint8_t *pkey;                              /*!< 客户端私钥点，如果客户端证书不包含密钥*/
        int pkey_len;                               /*!< 客户端私钥长度*/
    } server_pkey;                                  /*!< ESP_Blufi_EVENT_RECV_SERVER_PRIV_KEY的Blufi回调参数*/
    /**
     * @brief ESP_BLUFI_EVENT_REPORT_ERROR
     */
    struct blufi_get_error_evt_param {
        esp_blufi_error_state_t state;              /*!< Blufi错误状态*/
    } report_error;                                 /*!< ESP_Blufi_EVENT_REPORT_ERROR的Blufi回调参数*/
    /**
     * @brief ESP_BLUFI_EVENT_RECV_CUSTOM_DATA
     */
    struct blufi_recv_custom_data_evt_param {
        uint8_t *data;                              /*!< 自定义数据*/
        uint32_t data_len;                          /*!< 自定义数据长度*/
    } custom_data;                                  /*!< ESP_Blufi_EVENT_RECV_CUSTOM_DATA的Blufi回调参数*/
} esp_blufi_cb_param_t;

/**
 * @brief BLUFI事件回调函数类型
 * @param event ：事件类型
 * @param param ：指向回调参数，当前为联合类型
 */
typedef void (* esp_blufi_event_cb_t)(esp_blufi_cb_event_t event, esp_blufi_cb_param_t *param);

/* 安全函数声明*/

/**
 * @brief BLUFI协商数据处理程序
 * @param data ：来自手机的数据
 * @param len  ：来自手机的数据长度
 * @param output_data ：要发送到手机的数据
 * @param output_len ：要发送到手机的数据长度
 * @param need_free ：输出报告是否需要释放内存*
 */
typedef void (*esp_blufi_negotiate_data_handler_t)(uint8_t *data, int len, uint8_t **output_data, int *output_len, bool *need_free);

/**
 * @brief BLUFI在协商共享密钥后加密数据
 * @param iv8  ：初始向量（8bit），通常，blufi核心将输入数据包序列号
 * @param crypt_data ：纯文本和加密数据，加密功能必须支持本地加密
 * @param crypt_len  ：纯文本长度
 * @return  非负数是加密长度，如果错误，返回负数；
 */
typedef int (* esp_blufi_encrypt_func_t)(uint8_t iv8, uint8_t *crypt_data, int crypt_len);

/**
 * @brief BLUFI在协商共享密钥后解密数据
 * @param iv8  ：初始向量（8bit），通常，blufi核心将输入数据包序列号
 * @param crypt_data ：加密数据和纯文本，加密函数必须支持本地解密
 * @param crypt_len  ：加密文本的长度
 * @return  非负数是解密长度，如果错误，返回负数；
 */
typedef int (* esp_blufi_decrypt_func_t)(uint8_t iv8, uint8_t *crypt_data, int crypt_len);

/**
 * @brief BLUFI校验和
 * @param iv8  ：初始向量（8bit），通常，blufi核心将输入数据包序列号
 * @param data ：数据需要校验和
 * @param len  ：数据长度
 */
typedef uint16_t (*esp_blufi_checksum_func_t)(uint8_t iv8, uint8_t *data, int len);

/**
 * @brief BLUFI回调函数类型
 */
typedef struct {
    esp_blufi_event_cb_t                event_cb;                   /*!< BLUFI事件回调*/
    esp_blufi_negotiate_data_handler_t  negotiate_data_handler;     /*!< 用于协商共享密钥的BLUFI协商数据功能*/
    esp_blufi_encrypt_func_t            encrypt_func;               /*!< BLUFI使用由gotiate_data_handler生成的共享密钥加密数据函数*/
    esp_blufi_decrypt_func_t            decrypt_func;               /*!< BLUFI使用协商数据处理程序生成的共享密钥解密数据函数*/
    esp_blufi_checksum_func_t           checksum_func;              /*!< BLUFI校验和功能（FCS）*/
} esp_blufi_callbacks_t;

/**
 *
 * @brief           调用此函数以接收blufi回调事件
 *
 * @param[in]       callbacks: 回调函数
 *
 * @return          ESP_OK-成功，其他-失败
 *
 */
esp_err_t esp_blufi_register_callbacks(esp_blufi_callbacks_t *callbacks);

/**
 *
 * @brief           调用此函数以初始化blufi_file
 *
 * @return          ESP_OK-成功，其他-失败
 *
 */
esp_err_t esp_blufi_profile_init(void);

/**
 *
 * @brief           调用此函数以取消初始化blufi_file
 *
 * @return          ESP_OK-成功，其他-失败
 *
 */
esp_err_t esp_blufi_profile_deinit(void);

/**
 *
 * @brief           调用此函数以发送wifi连接报告
 * @param opmode ：wifi操作模式
 * @param sta_conn_state   ：站点是否已连接
 * @param softap_conn_num  ：软ap连接编号
 * @param extra_info       ：其他信息，如sta_ssid、softap_ssid等。
 *
 * @return          ESP_OK-成功，其他-失败
 *
 */
esp_err_t esp_blufi_send_wifi_conn_report(wifi_mode_t opmode, esp_blufi_sta_conn_state_t sta_conn_state, uint8_t softap_conn_num, esp_blufi_extra_info_t *extra_info);

/**
 *
 * @brief           调用此函数发送wifi列表
 * @param apCount ：wifi列表计数
 * @param list   ：wifi列表
 *
 * @return          ESP_OK-成功，其他-失败
 *
 */
esp_err_t esp_blufi_send_wifi_list(uint16_t apCount, esp_blufi_ap_record_t *list);

/**
 *
 * @brief           获取BLUFI配置文件版本
 *
 * @return          最重要的8位是大版本，最不重要的8位数是小版本
 *
 */
uint16_t esp_blufi_get_version(void);

/**
 *
 * @brief           调用此函数以发送blufi错误信息
 * @param state ：错误状态
 *
 * @return          ESP_OK-成功，其他-失败
 *
 */
esp_err_t esp_blufi_send_error_info(esp_blufi_error_state_t state);
/**
 *
 * @brief           调用此函数以自定义数据
 * @param data ：自定义数据值
 * @param data_len ：自定义数据的长度
 *
 * @return          ESP_OK-成功，其他-失败
 *
 */
esp_err_t esp_blufi_send_custom_data(uint8_t *data, uint32_t data_len);
#ifdef __cplusplus
}
#endif

#endif /* _ESP_BLUFI_API_ */

