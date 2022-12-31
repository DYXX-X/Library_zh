/**
 * @file MQTT客户端
 */

/*
 * 版权所有（c）2016 Erik Andersson保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：埃里克·安德森
 *
 */
#ifndef LWIP_HDR_APPS_MQTT_CLIENT_H
#define LWIP_HDR_APPS_MQTT_CLIENT_H

#include "lwip/apps/mqtt_opts.h"
#include "lwip/err.h"
#include "lwip/ip_addr.h"
#include "lwip/prot/iana.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mqtt_client_s mqtt_client_t;

#if LWIP_ALTCP && LWIP_ALTCP_TLS
struct altcp_tls_config;
#endif

/**@ingroup mqtt默认mqtt端口（非TLS）*/
#define MQTT_PORT     LWIP_IANA_PORT_MQTT
/**@ingroup mqtt默认mqtt TLS端口*/
#define MQTT_TLS_PORT LWIP_IANA_PORT_SECURE_MQTT

/*---------------------------------------------------------------------------------------------- */
/* 与服务器的连接*/

/**
 * @ingroup mqtt客户端信息和连接参数*/
struct mqtt_connect_client_info_t {
  /**客户端标识符，必须由调用者设置*/
  const char *client_id;
  /**用户名，如果未使用，则设置为NULL*/
  const char* client_user;
  /**密码，如果未使用，则设置为NULL*/
  const char* client_pass;
  /**保活时间（秒），0表示禁用保活功能*/
  u16_t keep_alive;
  /**将主题设置为NULL，如果不使用will，则将忽略will_msg、will_qos和will retain*/
  const char* will_topic;
  /**will_msg，参见will_topic*/
  const char* will_msg;
  /**will_qos，请参见will_topic*/
  u8_t will_qos;
  /**will_retain，参见will_topic*/
  u8_t will_retain;
#if LWIP_ALTCP && LWIP_ALTCP_TLS
  /**安全连接的TLS配置*/
  struct altcp_tls_config *tls_config;
#endif
};

/**
 * @ingroup mqtt连接状态代码*/
typedef enum
{
  /**已接受*/
  MQTT_CONNECT_ACCEPTED                 = 0,
  /**拒绝的协议版本*/
  MQTT_CONNECT_REFUSED_PROTOCOL_VERSION = 1,
  /**拒绝的标识符*/
  MQTT_CONNECT_REFUSED_IDENTIFIER       = 2,
  /**拒绝的服务器*/
  MQTT_CONNECT_REFUSED_SERVER           = 3,
  /**拒绝的用户凭据*/
  MQTT_CONNECT_REFUSED_USERNAME_PASS    = 4,
  /**拒绝未授权*/
  MQTT_CONNECT_REFUSED_NOT_AUTHORIZED_  = 5,
  /**已断开连接*/
  MQTT_CONNECT_DISCONNECTED             = 256,
  /**超时*/
  MQTT_CONNECT_TIMEOUT                  = 257
} mqtt_connection_status_t;

/**
 * @ingroup mqtt连接状态回调的mqtt函数原型。当客户端在通过调用mqtt_client_connect（）启动mqtt连接尝试后连接到服务器时调用，或者当连接被服务器关闭或出现错误时调用
 *
 * @param client MQTT客户机本身
 * @param arg 要传递给回调函数的附加参数
 * @param status 连接结果代码或断开连接通知@请参见mqtt_connection_status_t
 *
 */
typedef void (*mqtt_connection_cb_t)(mqtt_client_t *client, void *arg, mqtt_connection_status_t status);


/**
 * @ingroup mqtt数据回调标志*/
enum {
  /**当最后一段数据到达数据回调时设置的标志*/
  MQTT_DATA_FLAG_LAST = 1
};

/** 
 * @ingroup mqtt传入发布数据回调函数的mqtt函数原型。当数据到达订阅的主题时调用@see mqtt_subscribe
 *
 * @param arg 要传递给回调函数的附加参数
 * @param data 用户数据、指向对象、数据在回调返回后不能被引用，在传递所有发布数据时传递NULL
 * @param len 发布数据片段的长度
 * @param flags MQTT_DATA_FLAG_LAST集合（当此调用包含发布消息中的最后一部分数据时）
 *
 */
typedef void (*mqtt_incoming_data_cb_t)(void *arg, const u8_t *data, u16_t len, u8_t flags);


/** 
 * @ingroup mqtt传入发布函数的mqtt函数原型。当传入的发布到达订阅主题时调用@see mqtt_subscribe
 *
 * @param arg 要传递给回调函数的附加参数
 * @param topic 以零结尾的主题文本字符串，回调返回后不能引用主题
 * @param tot_len 发布数据的总长度，如果设置为0（无发布负载），则不会调用数据回调
 */
typedef void (*mqtt_incoming_publish_cb_t)(void *arg, const char *topic, u32_t tot_len);


/**
 * @ingroup mqtt请求回调的mqtt函数原型。在订阅、取消订阅或发布请求完成时调用
 * @param arg 指向调用请求时提供的用户数据的指针
 * @param err 如果在超时内未收到响应，则成功时ERR_OK ERR_TIMEOUT，如果（未）订阅被拒绝，则ERR_ABRT
 */
typedef void (*mqtt_request_cb_t)(void *arg, err_t err);


err_t mqtt_client_connect(mqtt_client_t *client, const ip_addr_t *ipaddr, u16_t port, mqtt_connection_cb_t cb, void *arg,
                   const struct mqtt_connect_client_info_t *client_info);

void mqtt_disconnect(mqtt_client_t *client);

mqtt_client_t *mqtt_client_new(void);
void mqtt_client_free(mqtt_client_t* client);

u8_t mqtt_client_is_connected(mqtt_client_t *client);

void mqtt_set_inpub_callback(mqtt_client_t *client, mqtt_incoming_publish_cb_t,
                             mqtt_incoming_data_cb_t data_cb, void *arg);

err_t mqtt_sub_unsub(mqtt_client_t *client, const char *topic, u8_t qos, mqtt_request_cb_t cb, void *arg, u8_t sub);

/**@ingroup mqtt订阅主题*/
#define mqtt_subscribe(client, topic, qos, cb, arg) mqtt_sub_unsub(client, topic, qos, cb, arg, 1)
/**@ingroup mqtt取消订阅主题*/
#define mqtt_unsubscribe(client, topic, cb, arg) mqtt_sub_unsub(client, topic, 0, cb, arg, 0)

err_t mqtt_publish(mqtt_client_t *client, const char *topic, const void *payload, u16_t payload_length, u8_t qos, u8_t retain,
                                    mqtt_request_cb_t cb, void *arg);

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_APPS_MQTT_CLIENT_H */

