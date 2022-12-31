/**
 * @file MQTT客户端（专用接口）
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
#ifndef LWIP_HDR_APPS_MQTT_PRIV_H
#define LWIP_HDR_APPS_MQTT_PRIV_H

#include "lwip/apps/mqtt.h"
#include "lwip/altcp.h"

#ifdef __cplusplus
extern "C" {
#endif

/**挂起请求项，将应用程序回调绑定到挂起的服务器请求*/
struct mqtt_request_t
{
  /**列表中的下一项，NULL表示这是链中的最后一项，下一项指向自身表示请求未分配*/
  struct mqtt_request_t *next;
  /**回调到上层*/
  mqtt_request_cb_t cb;
  void *arg;
  /**MQTT数据包标识符*/
  u16_t pkt_id;
  /**相对于在此之前的元素的过期时间*/
  u16_t timeout_diff;
};

/**环形缓冲区*/
struct mqtt_ringbuf_t {
  u16_t put;
  u16_t get;
  u8_t buf[MQTT_OUTPUT_RINGBUF_SIZE];
};

/**MQTT客户端*/
struct mqtt_client_s
{
  /**计时器和超时*/
  u16_t cyclic_tick;
  u16_t keep_alive;
  u16_t server_watchdog;
  /**数据包标识符生成器*/
  u16_t pkt_id_seq;
  /**挂起的传入发布的数据包标识符*/
  u16_t inpub_pkt_id;
  /**连接状态*/
  u8_t conn_state;
  struct altcp_pcb *conn;
  /**连接回调*/
  void *connect_arg;
  mqtt_connection_cb_t connect_cb;
  /**对服务器的挂起请求*/
  struct mqtt_request_t *pend_req_queue;
  struct mqtt_request_t req_list[MQTT_REQ_MAX_IN_FLIGHT];
  void *inpub_arg;
  /**传入数据回调*/
  mqtt_incoming_data_cb_t data_cb;
  mqtt_incoming_publish_cb_t pub_cb;
  /**输入*/
  u32_t msg_idx;
  u8_t rx_buffer[MQTT_VAR_HEADER_BUFFER_LEN];
  /**输出环形缓冲区*/
  struct mqtt_ringbuf_t output;
};

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_APPS_MQTT_PRIV_H */

