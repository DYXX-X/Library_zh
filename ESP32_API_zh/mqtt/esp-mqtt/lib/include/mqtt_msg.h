#ifndef MQTT_MSG_H
#define MQTT_MSG_H
#include <stdint.h>
#include <stdbool.h>

#include "mqtt_config.h"
#include "mqtt_client.h"
#ifdef  __cplusplus
extern "C" {
#endif

/*
* 版权所有（c）2014，Stephen Robinson保留所有权利。
*
* 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
*
* 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/
/* 7      6     5     4     3     2     1     0 */
/*|---消息类型----|DUP标志| QoS级别|保留|*/
/*                    剩余长度*/


enum mqtt_message_type {
    MQTT_MSG_TYPE_CONNECT = 1,
    MQTT_MSG_TYPE_CONNACK = 2,
    MQTT_MSG_TYPE_PUBLISH = 3,
    MQTT_MSG_TYPE_PUBACK = 4,
    MQTT_MSG_TYPE_PUBREC = 5,
    MQTT_MSG_TYPE_PUBREL = 6,
    MQTT_MSG_TYPE_PUBCOMP = 7,
    MQTT_MSG_TYPE_SUBSCRIBE = 8,
    MQTT_MSG_TYPE_SUBACK = 9,
    MQTT_MSG_TYPE_UNSUBSCRIBE = 10,
    MQTT_MSG_TYPE_UNSUBACK = 11,
    MQTT_MSG_TYPE_PINGREQ = 12,
    MQTT_MSG_TYPE_PINGRESP = 13,
    MQTT_MSG_TYPE_DISCONNECT = 14
};

typedef struct mqtt_message {
    uint8_t *data;
    size_t length;
    size_t fragmented_msg_total_length;       /*!< 碎片消息的总长度（所有其他消息为零）*/
    size_t fragmented_msg_data_offset;        /*!< 碎片消息的数据偏移量（所有其他消息为零）*/
} mqtt_message_t;

typedef struct mqtt_connection {
    mqtt_message_t message;
#if MQTT_MSG_ID_INCREMENTAL
    uint16_t last_message_id;   /*!< 如果配置了增量消息id，则最后使用的id*/
#endif
    uint8_t *buffer;
    size_t buffer_length;

} mqtt_connection_t;

typedef struct mqtt_connect_info {
    char *client_id;
    char *username;
    char *password;
    char *will_topic;
    char *will_message;
    int keepalive;          /*!< keepalive=0->keepalive已禁用*/
    int will_length;
    int will_qos;
    int will_retain;
    int clean_session;
    esp_mqtt_protocol_ver_t protocol_ver;

} mqtt_connect_info_t;


static inline int mqtt_get_type(const uint8_t *buffer)
{
    return (buffer[0] & 0xf0) >> 4;
}
static inline int mqtt_get_connect_session_present(const uint8_t *buffer)
{
    return buffer[2] & 0x01;
}
static inline int mqtt_get_connect_return_code(const uint8_t *buffer)
{
    return buffer[3];
}
static inline int mqtt_get_dup(const uint8_t *buffer)
{
    return (buffer[0] & 0x08) >> 3;
}
static inline void mqtt_set_dup(uint8_t *buffer)
{
    buffer[0] |= 0x08;
}
static inline int mqtt_get_qos(const uint8_t *buffer)
{
    return (buffer[0] & 0x06) >> 1;
}
static inline int mqtt_get_retain(const uint8_t *buffer)
{
    return (buffer[0] & 0x01);
}

void mqtt_msg_init(mqtt_connection_t *connection, uint8_t *buffer, size_t buffer_length);
bool mqtt_header_complete(uint8_t *buffer, size_t buffer_length);
size_t mqtt_get_total_length(const uint8_t *buffer, size_t length, int *fixed_size_len);
char *mqtt_get_publish_topic(uint8_t *buffer, size_t *length);
char *mqtt_get_publish_data(uint8_t *buffer, size_t *length);
uint16_t mqtt_get_id(uint8_t *buffer, size_t length);
int mqtt_has_valid_msg_hdr(uint8_t *buffer, size_t length);

mqtt_message_t *mqtt_msg_connect(mqtt_connection_t *connection, mqtt_connect_info_t *info);
mqtt_message_t *mqtt_msg_publish(mqtt_connection_t *connection, const char *topic, const char *data, int data_length, int qos, int retain, uint16_t *message_id);
mqtt_message_t *mqtt_msg_puback(mqtt_connection_t *connection, uint16_t message_id);
mqtt_message_t *mqtt_msg_pubrec(mqtt_connection_t *connection, uint16_t message_id);
mqtt_message_t *mqtt_msg_pubrel(mqtt_connection_t *connection, uint16_t message_id);
mqtt_message_t *mqtt_msg_pubcomp(mqtt_connection_t *connection, uint16_t message_id);
mqtt_message_t *mqtt_msg_subscribe(mqtt_connection_t *connection, const char *topic, int qos, uint16_t *message_id);
mqtt_message_t *mqtt_msg_unsubscribe(mqtt_connection_t *connection, const char *topic, uint16_t *message_id);
mqtt_message_t *mqtt_msg_pingreq(mqtt_connection_t *connection);
mqtt_message_t *mqtt_msg_pingresp(mqtt_connection_t *connection);
mqtt_message_t *mqtt_msg_disconnect(mqtt_connection_t *connection);


#ifdef  __cplusplus
}
#endif

#endif  /* MQTT_MSG_H */


