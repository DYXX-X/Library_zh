/**
 * @file lwIP iPerf服务器实现
 */

/*
 * 版权所有（c）2014 Simon Goldschmidt保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Simon Goldschmidt
 *
 */
#ifndef LWIP_HDR_APPS_LWIPERF_H
#define LWIP_HDR_APPS_LWIPERF_H

#include "lwip/opt.h"
#include "lwip/ip_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LWIPERF_TCP_PORT_DEFAULT  5001

/**lwIPerf测试结果*/
enum lwiperf_report_type
{
  /**服务器端测试已完成*/
  LWIPERF_TCP_DONE_SERVER,
  /**客户端测试已完成*/
  LWIPERF_TCP_DONE_CLIENT,
  /**导致测试中止的本地错误*/
  LWIPERF_TCP_ABORTED_LOCAL,
  /**数据检查错误导致测试中止*/
  LWIPERF_TCP_ABORTED_LOCAL_DATAERROR,
  /**传输错误导致测试中止*/
  LWIPERF_TCP_ABORTED_LOCAL_TXERROR,
  /**远程侧中止测试*/
  LWIPERF_TCP_ABORTED_REMOTE
};

/**控制*/
enum lwiperf_client_type
{
  /**单向仅tx测试*/
  LWIPERF_CLIENT,
  /**同时进行双向测试*/
  LWIPERF_DUAL,
  /**单独进行双向测试*/
  LWIPERF_TRADEOFF
};

/**会话完成时调用的报表函数的原型。此报告功能可以显示测试结果@param report_type包含测试结果*/
typedef void (*lwiperf_report_fn)(void *arg, enum lwiperf_report_type report_type,
  const ip_addr_t* local_addr, u16_t local_port, const ip_addr_t* remote_addr, u16_t remote_port,
  u32_t bytes_transferred, u32_t ms_duration, u32_t bandwidth_kbitpsec);

void* lwiperf_start_tcp_server(const ip_addr_t* local_addr, u16_t local_port,
                               lwiperf_report_fn report_fn, void* report_arg);
void* lwiperf_start_tcp_server_default(lwiperf_report_fn report_fn, void* report_arg);
void* lwiperf_start_tcp_client(const ip_addr_t* remote_addr, u16_t remote_port,
                               enum lwiperf_client_type type,
                               lwiperf_report_fn report_fn, void* report_arg);
void* lwiperf_start_tcp_client_default(const ip_addr_t* remote_addr,
                               lwiperf_report_fn report_fn, void* report_arg);

void  lwiperf_abort(void* lwiperf_session);


#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_APPS_LWIPERF_H */

