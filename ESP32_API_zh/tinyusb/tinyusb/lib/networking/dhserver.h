/*
 * MIT许可证（MIT）
 *
 * Sergey Fetisov版权所有（c）2015<fsenok@gmail.com>
 * 
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 * 
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * 版本：1.0演示（2015年2月7日）简介：使用lwip（pcb）的微型dhcp ipv4服务器参考：https://lists.gnu.org/archive/html/lwip-users/2012-12/msg00016.html
 */

#ifndef DHSERVER_H
#define DHSERVER_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "lwip/err.h"
#include "lwip/udp.h"
#include "netif/etharp.h"

typedef struct dhcp_entry
{
	uint8_t  mac[6];
	ip_addr_t addr;
	uint32_t lease;
} dhcp_entry_t;

typedef struct dhcp_config
{
	ip_addr_t     router;
	uint16_t      port;
	ip_addr_t     dns;
	const char   *domain;
	int           num_entry;
	dhcp_entry_t *entries;
} dhcp_config_t;

err_t dhserv_init(const dhcp_config_t *config);
void dhserv_free(void);

#endif /* DHSERVER_H */

