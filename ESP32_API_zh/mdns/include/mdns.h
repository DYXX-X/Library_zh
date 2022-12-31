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
#ifndef ESP_MDNS_H_
#define ESP_MDNS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <esp_netif.h>
#include "esp_event.h"

#define MDNS_TYPE_A                 0x0001
#define MDNS_TYPE_PTR               0x000C
#define MDNS_TYPE_TXT               0x0010
#define MDNS_TYPE_AAAA              0x001C
#define MDNS_TYPE_SRV               0x0021
#define MDNS_TYPE_OPT               0x0029
#define MDNS_TYPE_NSEC              0x002F
#define MDNS_TYPE_ANY               0x00FF

/**
 * @brief   异步查询句柄
 */
typedef struct mdns_search_once_s mdns_search_once_t;

/**
 * @brief   mDNS枚举以指定ip_procol类型
 */
typedef enum {
    MDNS_IP_PROTOCOL_V4,
    MDNS_IP_PROTOCOL_V6,
    MDNS_IP_PROTOCOL_MAX
} mdns_ip_protocol_t;

/**
 * @brief   mDNS基本文本项结构用于mDNS_service_add（）
 */
typedef struct {
    const char * key;                       /*!< 项目密钥名称*/
    const char * value;                     /*!< 项目值字符串*/
} mdns_txt_item_t;

/**
 * @brief   mDNS查询链接列表IP项
 */
typedef struct mdns_ip_addr_s {
    esp_ip_addr_t addr;                     /*!< IP地址*/
    struct mdns_ip_addr_s * next;           /*!< 下一个IP，或列表中最后一个IP为NULL*/
} mdns_ip_addr_t;

typedef enum mdns_if_internal {
    MDNS_IF_STA = 0,
    MDNS_IF_AP = 1,
    MDNS_IF_ETH = 2,
    MDNS_IF_MAX
} mdns_if_t;

/**
 * @brief   mDNS查询结果结构
 */
typedef struct mdns_result_s {
    struct mdns_result_s * next;            /*!< 下一个结果，或列表中最后一个结果为NULL*/

    mdns_if_t tcpip_if;                     /*!< 界面索引*/
    uint32_t ttl;                           /*!< 生存时间*/

    mdns_ip_protocol_t ip_protocol;         /*!< 接口的ip_协议类型（v4/v6）*/
    // PTR
    char * instance_name;                   /*!< 实例名称*/
    char * service_type;                    /*!< 服务类型*/
    char * proto;                           /*!< 设备协议*/
    // SRV
    char * hostname;                        /*!< 主机名*/
    uint16_t port;                          /*!< 服务端口*/
    // TXT
    mdns_txt_item_t * txt;                  /*!< txt记录*/
    uint8_t *txt_value_len;                 /*!< 每个记录的txt值len数组*/
    size_t txt_count;                       /*!< txt项目数*/
    // A和AAAA
    mdns_ip_addr_t * addr;                  /*!< 找到IP地址的链接列表*/
} mdns_result_t;

typedef void (*mdns_query_notify_t)(mdns_search_once_t *search);

/**
 * @brief  在给定接口上初始化mDNS
 *
 * @return
 *     -成功时ESP_OK
 *     -注册事件处理程序失败时的ESP_ERR_INVALID_STATE
 *     -ESP_ERR_NO_MEM内存错误
 *     -启动mdns任务失败时的ESP_FAIL
 */
esp_err_t mdns_init(void);

/**
 * @brief  停止并释放mDNS服务器
 *
 */
void mdns_free(void);

/**
 * @brief  如果要播发服务，请设置所需的mDNS服务器的主机名
 *
 * @param  hostname     要设置的主机名
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_ERR_NO_MEM内存错误
 */
esp_err_t mdns_hostname_set(const char * hostname);

/**
 * @brief  添加要委派的主机名和地址a/AAAA查询将被答复，主机名和服务可以添加到此主机。
 *
 * @param  hostname     要添加的主机名
 * @param  address_list 主机的IP地址列表
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE mDNS未运行
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_ERR_NO_MEM内存错误
 *
 */
esp_err_t mdns_delegate_hostname_add(const char * hostname, const mdns_ip_addr_t *address_list);

/**
 * @brief  删除委派的主机名添加到此主机的所有服务也将被删除。
 *
 * @param  hostname     要删除的主机名
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE mDNS未运行
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_ERR_NO_MEM内存错误
 *
 */
esp_err_t mdns_delegate_hostname_remove(const char * hostname);

/**
 * @brief  查询是否已添加主机名
 *
 * @param  hostname     要查询的主机名
 *
 * @return
 *     -true已添加主机名。
 *     -false尚未添加主机名。
 *
 */
bool mdns_hostname_exists(const char * hostname);

/**
 * @brief  设置mDNS服务器的默认实例名称
 *
 * @param  instance_name     要设置的实例名称
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_ERR_NO_MEM内存错误
 */
esp_err_t mdns_instance_name_set(const char * instance_name);

/**
 * @brief  向mDNS服务器添加服务
 *
 * @note txt项的值长度将由strlen自动决定
 *
 * @param  instance_name    要设置的实例名称。如果为NULL，将使用全局实例名或主机名。请注意，添加具有相同实例类型的多个实例时，需要启用MDNS_MULTIPLE_INSTANCE配置选项。
 * @param  service_type     服务类型（_http、_ftp等）
 * @param  proto            服务协议（_tcp，_udp）
 * @param  port             服务端口
 * @param  txt              TXT数据的字符串数组（例如｛｛“var”，“val”｝，｛“other”，“2”｝）
 * @param  num_items        TXT数据中的项目数
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_ERR_NO_MEM内存错误
 *     -ESP_FAIL无法添加服务
 */
esp_err_t mdns_service_add(const char * instance_name, const char * service_type, const char * proto, uint16_t port, mdns_txt_item_t txt[], size_t num_items);

/**
 * @brief  向具有委派主机名的mDNS服务器添加服务
 *
 * @note txt项的值长度将由strlen自动决定
 *
 * @param  instance_name    要设置的实例名称。如果为NULL，则将使用全局实例名或主机名。请注意，需要启用MDNS_MULTIPLE_instance配置选项以添加具有相同实例类型的多个实例。
 * @param  service_type     服务类型（_http、_ftp等）
 * @param  proto            服务协议（_tcp，_udp）
 * @param  hostname         服务主机名。如果为NULL，将使用本地主机名。
 * @param  port             服务端口
 * @param  txt              TXT数据的字符串数组（例如｛｛“var”，“val”｝，｛“other”，“2”｝）
 * @param  num_items        TXT数据中的项目数
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_ERR_NO_MEM内存错误
 *     -ESP_FAIL无法添加服务
 */
esp_err_t mdns_service_add_for_host(const char * instance_name, const char * service_type, const char * proto,
                                    const char * hostname, uint16_t port, mdns_txt_item_t txt[], size_t num_items);

/**
 * @brief  检查是否已添加服务。
 *
 * @param  service_type     服务类型（_http、_ftp等）
 * @param  proto            服务协议（_tcp，_udp）
 * @param  hostname         服务主机名。如果为NULL，则检查本地主机名。
 *
 * @return
 *     -true已添加对应服务。
 *     -找不到false服务。
 */
bool mdns_service_exists(const char * service_type, const char * proto, const char * hostname);


/**
 * @brief  检查是否已添加服务。
 *
 * @param  instance         实例名称
 * @param  service_type     服务类型（_http、_ftp等）
 * @param  proto            服务协议（_tcp，_udp）
 * @param  hostname         服务主机名。如果为NULL，则检查本地主机名。
 *
 * @return
 *     -true已添加对应服务。
 *     -找不到false服务。
 */
bool mdns_service_exists_with_instance(const char *instance, const char *service_type, const char *proto,
                                       const char *hostname);

/**
 * @brief  从mDNS服务器删除服务
 *
 * @param  service_type 服务类型（_http、_ftp等）
 * @param  proto        服务协议（_tcp，_udp）
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -未找到ESP_ERR_NOT_FOUND服务
 *     -ESP_ERR_NO_MEM内存错误
 */
esp_err_t mdns_service_remove(const char * service_type, const char * proto);

/**
 * @brief  从主机名为的mDNS服务器中删除服务
 *
 * @param  service_type 服务类型（_http、_ftp等）
 * @param  proto        服务协议（_tcp，_udp）
 * @param  hostname     服务主机名。如果为NULL，将使用本地主机名。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -未找到ESP_ERR_NOT_FOUND服务
 *     -ESP_ERR_NO_MEM内存错误
 */
esp_err_t mdns_service_remove_for_host(const char * service_type, const char * proto, const char *hostname);

/**
 * @brief  设置服务的实例名称
 *
 * @param  service_type     服务类型（_http、_ftp等）
 * @param  proto            服务协议（_tcp，_udp）
 * @param  instance_name    要设置的实例名称
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -未找到ESP_ERR_NOT_FOUND服务
 *     -ESP_ERR_NO_MEM内存错误
 */
esp_err_t mdns_service_instance_name_set(const char * service_type, const char * proto, const char * instance_name);

/**
 * @brief  使用主机名设置服务的实例名
 *
 * @param  service_type     服务类型（_http、_ftp等）
 * @param  proto            服务协议（_tcp，_udp）
 * @param  hostname         服务主机名。如果为NULL，将使用本地主机名。
 * @param  instance_name    要设置的实例名称
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -未找到ESP_ERR_NOT_FOUND服务
 *     -ESP_ERR_NO_MEM内存错误
 */
esp_err_t mdns_service_instance_name_set_for_host(const char * service_type, const char * proto, const char * hostname,
                                                  const char * instance_name);

/**
 * @brief  设置服务端口
 *
 * @param  service_type 服务类型（_http、_ftp等）
 * @param  proto        服务协议（_tcp，_udp）
 * @param  port         服务端口
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -未找到ESP_ERR_NOT_FOUND服务
 *     -ESP_ERR_NO_MEM内存错误
 */
esp_err_t mdns_service_port_set(const char * service_type, const char * proto, uint16_t port);


/**
 * @brief  使用主机名设置服务端口
 *
 * @param  service_type 服务类型（_http、_ftp等）
 * @param  proto        服务协议（_tcp，_udp）
 * @param  hostname     服务主机名。如果为NULL，将使用本地主机名。
 * @param  port         服务端口
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -未找到ESP_ERR_NOT_FOUND服务
 *     -ESP_ERR_NO_MEM内存错误
 */
esp_err_t mdns_service_port_set_for_host(const char * service_type, const char * proto, const char * hostname,
                                         uint16_t port);

/**
 * @brief  更换所有TXT项目进行维修
 *
 * @note txt项的值长度将由strlen自动决定
 *
 * @param  service_type 服务类型（_http、_ftp等）
 * @param  proto        服务协议（_tcp，_udp）
 * @param  txt          TXT数据数组（例如｛｛“var”，“val”｝，｛“other”，“2”｝｝）
 * @param  num_items    TXT数据中的项目数
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -未找到ESP_ERR_NOT_FOUND服务
 *     -ESP_ERR_NO_MEM内存错误
 */
esp_err_t mdns_service_txt_set(const char * service_type, const char * proto, mdns_txt_item_t txt[], uint8_t num_items);

/**
 * @brief  用主机名替换服务的所有TXT项
 *
 * @note txt项的值长度将由strlen自动决定
 *
 * @param  service_type 服务类型（_http、_ftp等）
 * @param  proto        服务协议（_tcp，_udp）
 * @param  hostname     服务主机名。如果为NULL，将使用本地主机名。
 * @param  txt          TXT数据数组（例如｛｛“var”，“val”｝，｛“other”，“2”｝｝）
 * @param  num_items    TXT数据中的项目数
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -未找到ESP_ERR_NOT_FOUND服务
 *     -ESP_ERR_NO_MEM内存错误
 */
esp_err_t mdns_service_txt_set_for_host(const char * service_type, const char * proto, const char * hostname,
                                        mdns_txt_item_t txt[], uint8_t num_items);

/**
 * @brief  设置/添加服务TXT记录的TXT项
 *
 * @note 值长度将由strlen自动决定
 *
 * @param  service_type 服务类型（_http、_ftp等）
 * @param  proto        服务协议（_tcp，_udp）
 * @param  key          要添加/更新的密钥
 * @param  value        密钥的新值
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -未找到ESP_ERR_NOT_FOUND服务
 *     -ESP_ERR_NO_MEM内存错误
 */
esp_err_t mdns_service_txt_item_set(const char * service_type, const char * proto, const char * key, const char * value);

/**
 * @brief  设置/添加服务TXT记录的TXT项
 *
 * @param  service_type 服务类型（_http、_ftp等）
 * @param  proto        服务协议（_tcp，_udp）
 * @param  key          要添加/更新的密钥
 * @param  value        密钥的新值
 * @param  value_len    值的长度
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -未找到ESP_ERR_NOT_FOUND服务
 *     -ESP_ERR_NO_MEM内存错误
 */
esp_err_t mdns_service_txt_item_set_with_explicit_value_len(const char *service_type, const char *proto,
                                                            const char *key, const char *value, uint8_t value_len);

/**
 * @brief  为具有主机名的服务TXT记录设置/添加TXT项
 *
 * @note 值长度将由strlen自动决定
 *
 * @param  service_type 服务类型（_http、_ftp等）
 * @param  proto        服务协议（_tcp，_udp）
 * @param  hostname     服务主机名。如果为NULL，将使用本地主机名。
 * @param  key          要添加/更新的密钥
 * @param  value        密钥的新值
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -未找到ESP_ERR_NOT_FOUND服务
 *     -ESP_ERR_NO_MEM内存错误
 */
esp_err_t mdns_service_txt_item_set_for_host(const char * service_type, const char * proto, const char * hostname,
                                             const char * key, const char * value);

/**
 * @brief  为具有主机名和TXT值长度的服务TXT记录设置/添加TXT项
 *
 * @param  service_type 服务类型（_http、_ftp等）
 * @param  proto        服务协议（_tcp，_udp）
 * @param  hostname     服务主机名。如果为NULL，将使用本地主机名。
 * @param  key          要添加/更新的密钥
 * @param  value        密钥的新值
 * @param  value_len    值的长度
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -未找到ESP_ERR_NOT_FOUND服务
 *     -ESP_ERR_NO_MEM内存错误
 */
esp_err_t mdns_service_txt_item_set_for_host_with_explicit_value_len(const char *service_type, const char *proto,
                                                                     const char *hostname, const char *key,
                                                                     const char *value, uint8_t value_len);

/**
 * @brief  删除服务TXT记录的TXT项
 *
 * @param  service_type 服务类型（_http、_ftp等）
 * @param  proto        服务协议（_tcp，_udp）
 * @param  key          要删除的密钥
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -未找到ESP_ERR_NOT_FOUND服务
 *     -ESP_ERR_NO_MEM内存错误
 */
esp_err_t mdns_service_txt_item_remove(const char * service_type, const char * proto, const char * key);

/**
 * @brief  删除带有主机名的服务TXT记录的TXT项
 *
 * @param  service_type 服务类型（_http、_ftp等）
 * @param  proto        服务协议（_tcp，_udp）
 * @param  hostname     服务主机名。如果为NULL，将使用本地主机名。
 * @param  key          要删除的密钥
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -未找到ESP_ERR_NOT_FOUND服务
 *     -ESP_ERR_NO_MEM内存错误
 */
esp_err_t mdns_service_txt_item_remove_for_host(const char * service_type, const char * proto, const char * hostname,
                                                const char * key);

/**
 * @brief  从mDNS服务器删除并释放所有服务
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mdns_service_remove_all(void);

/**
 * @brief 删除完成的查询。只有在搜索结束后才能调用此命令！
 *
 * @param search 指向搜索对象的指针
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE搜索尚未完成
 *     -指向搜索对象的ESP_ERR_INVALID_ARG指针为空
 */
esp_err_t mdns_query_async_delete(mdns_search_once_t* search);

/**
 * @brief 从搜索指针获取结果。结果可用作输出参数的指针。查询完成后，必须通过“mdns_query_async_delete”删除指向搜索对象的指针。尽管必须手动释放结果。
 *
 * @param search 指向搜索对象的指针
 * @param timeout 等待答案的时间（毫秒）
 * @param results 指向查询结果的指针
 *
 * @return 如果搜索在超时之前或之后完成，则为True如果搜索超时结束，则为False
 */
bool mdns_query_async_get_results(mdns_search_once_t* search, uint32_t timeout, mdns_result_t ** results);

/**
 * @brief  异步查询mDNS以查找主机或服务。必须测试搜索进度并手动删除！
 *
 * @param  name         服务实例或主机名（PTR查询为NULL）
 * @param  service_type 服务类型（_http、_arduino、_ftp等）（主机查询为NULL）
 * @param  proto        服务协议（_tcp、_udp等）（主机查询为NULL）
 * @param  type         查询类型（MDNS_type_*）
 * @param  timeout      mDNS查询处于活动状态的时间（毫秒）
 * @param  max_results  要收集的最大结果
 * @param  notifier     结果就绪时要调用的通知函数可以为NULL
 *
 * @return 如果查询成功启动，则mdns_search_onces指向新搜索对象的指针。否则为NULL。
 */
mdns_search_once_t *mdns_query_async_new(const char *name, const char *service_type, const char *proto, uint16_t type,
                                         uint32_t timeout, size_t max_results, mdns_query_notify_t notifier);

/**
 * @brief  查询主机或服务的mDNS以下所有查询方法都源自此方法
 *
 * @param  name         服务实例或主机名（PTR查询为NULL）
 * @param  service_type 服务类型（_http、_arduino、_ftp等）（主机查询为NULL）
 * @param  proto        服务协议（_tcp、_udp等）（主机查询为NULL）
 * @param  type         查询类型（MDNS_type_*）
 * @param  timeout      等待答案的时间（毫秒）。
 * @param  max_results  要收集的最大结果
 * @param  results      必须使用下面的mdns_query_results_free释放指向查询结果结果的指针
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE mDNS未运行
 *     -ESP_ERR_NO_MEM内存错误
 *     -未给出ESP_ERR_INVALID_ARG超时
 */
esp_err_t mdns_query(const char * name, const char * service_type, const char * proto, uint16_t type, uint32_t timeout, size_t max_results, mdns_result_t ** results);

/**
 * @brief  自由查询结果
 *
 * @param  results      要释放的结果的链接列表
 */
void mdns_query_results_free(mdns_result_t * results);

/**
 * @brief  查询mDNS以获取服务
 *
 * @param  service_type 服务类型（_http、_arduino、_ftp等）
 * @param  proto        服务协议（_tcp、_udp等）
 * @param  timeout      等待应答的时间（毫秒）。
 * @param  max_results  要收集的最大结果
 * @param  results      指向查询结果的指针
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE mDNS未运行
 *     -ESP_ERR_NO_MEM内存错误
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mdns_query_ptr(const char * service_type, const char * proto, uint32_t timeout, size_t max_results, mdns_result_t ** results);

/**
 * @brief  查询mDNS以查找SRV记录
 *
 * @param  instance_name    服务实例名称
 * @param  service_type     服务类型（_http、_arduino、_ftp等）
 * @param  proto            服务协议（_tcp、_udp等）
 * @param  timeout          等待应答的时间（毫秒）。
 * @param  result           指向查询结果的指针
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE mDNS未运行
 *     -ESP_ERR_NO_MEM内存错误
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mdns_query_srv(const char * instance_name, const char * service_type, const char * proto, uint32_t timeout, mdns_result_t ** result);

/**
 * @brief  查询mDNS以获取TXT记录
 *
 * @param  instance_name    服务实例名称
 * @param  service_type     服务类型（_http、_arduino、_ftp等）
 * @param  proto            服务协议（_tcp、_udp等）
 * @param  timeout          等待应答的时间（毫秒）。
 * @param  result           指向查询结果的指针
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE mDNS未运行
 *     -ESP_ERR_NO_MEM内存错误
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mdns_query_txt(const char * instance_name, const char * service_type, const char * proto, uint32_t timeout, mdns_result_t ** result);

/**
 * @brief  查询mDNS以查找A记录
 *
 * @param  host_name    要查找的主机名
 * @param  timeout      等待应答的时间（毫秒）。
 * @param  addr         指向生成的IP4地址的指针
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE mDNS未运行
 *     -ESP_ERR_NO_MEM内存错误
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mdns_query_a(const char * host_name, uint32_t timeout, esp_ip4_addr_t * addr);

#if CONFIG_LWIP_IPV6
/**
 * @brief  查询mDNS以查找A记录
 *
 * 请注意，主机名不能包含域名，因为mDNS使用“”。local”域。
 *
 * @param  host_name    要查找的主机名
 * @param  timeout      等待应答的时间（毫秒）。如果为0，则需要定义max_results
 * @param  addr         指向生成的IP6地址的指针
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE mDNS未运行
 *     -ESP_ERR_NO_MEM内存错误
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mdns_query_aaaa(const char * host_name, uint32_t timeout, esp_ip6_addr_t * addr);
#endif

/**
 * @brief   系统事件处理程序此方法控制所有活动接口上的服务状态，应用程序需要从系统事件处理中调用它才能正常运行mDNS服务。
 *
 * 请注意，主机名不能包含域名，因为mDNS使用“”。local”域。
 *
 * @param  ctx          系统事件上下文
 * @param  event        系统事件
 */
esp_err_t mdns_handle_system_event(void *ctx, system_event_t *event) __attribute__((deprecated));

#ifdef __cplusplus
}
#endif

#endif /* ESP_MDNS_H_ */

