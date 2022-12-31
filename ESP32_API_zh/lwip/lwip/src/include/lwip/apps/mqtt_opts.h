/**
 * @file MQTT客户端选项
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
#ifndef LWIP_HDR_APPS_MQTT_OPTS_H
#define LWIP_HDR_APPS_MQTT_OPTS_H

#include "lwip/opt.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup mqtt_opts选项
 * @ingroup mqtt公司@{
 */

/**
 * 输出环形缓冲区大小，必须能够容纳最大的传出发布消息主题+有效负载
 */
#ifndef MQTT_OUTPUT_RINGBUF_SIZE
#define MQTT_OUTPUT_RINGBUF_SIZE 256
#endif

/**
 * 接收缓冲区中的字节数，必须至少为最长传入主题的大小+8如果要避免碎片化传入发布，请将长度设置为最大传入主题长度+最大有效负载长度+8
 */
#ifndef MQTT_VAR_HEADER_BUFFER_LEN
#define MQTT_VAR_HEADER_BUFFER_LEN 128
#endif

/**
 * 服务器上挂起的订阅、取消订阅和发布请求的最大数量。
 */
#ifndef MQTT_REQ_MAX_IN_FLIGHT
#define MQTT_REQ_MAX_IN_FLIGHT 4
#endif

/**
 * 每次循环计时器调用之间的秒数。
 */
#ifndef MQTT_CYCLIC_TIMER_INTERVAL
#define MQTT_CYCLIC_TIMER_INTERVAL 5
#endif

/**
 * 发布、订阅和取消订阅请求超时（秒）。
 */
#ifndef MQTT_REQ_TIMEOUT
#define MQTT_REQ_TIMEOUT 30
#endif

/**
 * 发送连接请求后MQTT连接响应超时的秒数
 */
#ifndef MQTT_CONNECT_TIMOUT
#define MQTT_CONNECT_TIMOUT 100
#endif

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_APPS_MQTT_OPTS_H */

