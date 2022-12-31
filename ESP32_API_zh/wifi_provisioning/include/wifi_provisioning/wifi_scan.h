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

#ifndef _PROV_WIFI_SCAN_H_
#define _PROV_WIFI_SCAN_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <esp_wifi.h>

#define WIFI_SSID_LEN  sizeof(((wifi_ap_record_t *)0)->ssid)
#define WIFI_BSSID_LEN sizeof(((wifi_ap_record_t *)0)->bssid)

/**
 * @brief   传递给“wifi_prop_scan_handlers”结构中每个get/set/apply处理程序函数集的上下文数据类型。
 *
 * 这是作为一个不透明的指针传递的，因此允许稍后根据需要在应用程序代码中定义它。
 */
typedef struct wifi_prov_scan_ctx wifi_prov_scan_ctx_t;

/**
 * @brief   扫描结果列表中的条目结构
 */
typedef struct {
    /**
     * Wi-Fi AP的SSID
     */
    char ssid[WIFI_SSID_LEN];

    /**
     * Wi-Fi AP的BSSID
     */
    char bssid[WIFI_BSSID_LEN];

    /**
     * Wi-Fi频道号
     */
    uint8_t channel;

    /**
     * 信号强度
     */
    int rssi;

    /**
     * Wi-Fi安全模式
     */
    uint8_t auth;
} wifi_prov_scan_result_t;

/**
 * @brief   用于接收和响应来自客户端的protocomm请求的内部处理程序
 *
 * 当调用“protocomm_add_endpoint（）”时，这将作为protocomm请求处理程序的priva_data（请参阅“wifi_prop_scan_handler（）”）传递。
 */
typedef struct wifi_prov_scan_handlers {
    /**
     * 收到带有各种扫描参数的扫描开始命令时调用的处理程序函数：
     *
     * blocking（input）-如果为true，则函数应仅在扫描完成时返回
     *
     * 被动（输入）-如果为真，扫描将以被动模式（这可能会慢一些）而不是主动模式启动
     *
     * group_channels（input）-指定是一次性扫描所有信道（当为零时）还是成组扫描信道，在连续组扫描之间延迟120ms，此参数的值设置每组中的信道数。当传输模式为SoftAP时，这很有用，因为一次性扫描所有信道可能不会给Wi-Fi驱动程序足够的时间发送信标，因此可能导致与任何连接的站点断开连接。当分组扫描时，管理器将在一组信道上完成扫描后等待至少120秒，从而允许驱动程序发送信标。例如，假设Wi-Fi信道的总数为14，那么将group_channels设置为4将创建5个组，每个组具有3个信道，最后一个组将具有14%3=2个信道。因此，当扫描开始时，前3个信道将被扫描，随后是120毫秒的延迟，然后是下3个信道，依此类推，直到所有14个信道都被扫描完。可能需要调整此参数，因为一组中只有几个信道可能会减慢整个扫描时间，而太多信道可能会再次导致断开连接。通常情况下，值4应该适用于大多数情况。请注意，对于任何其他传输模式，例如BLE，这可以安全地设置为0，从而实现最快的总扫描时间。
     *
     * period_ms（input）-扫描参数，指定在每个通道上等待的时间（毫秒）
     */
    esp_err_t (*scan_start)(bool blocking, bool passive,
                            uint8_t group_channels, uint32_t period_ms,
                            wifi_prov_scan_ctx_t **ctx);

    /**
     * 请求扫描状态时调用了处理程序函数。状态参数如下：
     *
     * scan_finished（输出）-扫描完成后，返回true
     *
     * result_count（输出）-这是到目前为止获得的结果总数。如果扫描仍在进行，该号码将继续更新
     */
    esp_err_t (*scan_status)(bool *scan_finished,
                             uint16_t *result_count,
                             wifi_prov_scan_ctx_t **ctx);

    /**
     * 请求扫描结果时调用了处理程序函数。参数：
     *
     * scan_result-用于获取扫描结果。即使扫描仍在进行，也可以调用此功能
     *
     * start_index（input）-从结果列表中获取条目的位置开始索引
     *
     * count（input）-从起始索引中提取的条目数
     *
     * entries（output）-返回的条目列表。每个条目由ssid、通道和rssi信息组成
     */
    esp_err_t (*scan_result)(uint16_t result_index,
                             wifi_prov_scan_result_t *result,
                             wifi_prov_scan_ctx_t **ctx);

    /**
     * 调用时要传递给以上处理程序函数的上下文指针
     */
    wifi_prov_scan_ctx_t *ctx;
} wifi_prov_scan_handlers_t;

/**
 * @brief   用于发送按需Wi-Fi扫描结果的处理程序
 *
 * 使用“protocomm_add_endpoint（）”将其注册为“prov-scan”端点处理程序（protocomm“protocomm_req_handler_t”）`
 */
esp_err_t wifi_prov_scan_handler(uint32_t session_id, const uint8_t *inbuf, ssize_t inlen,
                                 uint8_t **outbuf, ssize_t *outlen, void *priv_data);

#ifdef __cplusplus
}
#endif

#endif

