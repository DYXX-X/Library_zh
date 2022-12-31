/**
 * @file lwIP netif实现IEEE 802.1D MAC桥
 */

/*
 * 版权所有（c）2017 Simon Goldschmidt。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Simon Goldschmidt<goldsimon@gmx.de>
 *
 */

#ifndef LWIP_HDR_NETIF_BRIDGEIF_OPTS_H
#define LWIP_HDR_NETIF_BRIDGEIF_OPTS_H

#include "lwip/opt.h"

/**
 * @defgroup bridgeif_opts选项
 * @ingroup 桥头堡@{
 */

/** BRIDGEIF_PORT_NETIFS_OUTPUT_DIRECT==1：将端口netif的“input”函数设置为直接调用BRIDGEIF代码，然后直接调用所选转发端口的“linkoutput”函数。这意味着bridgeif输入/输出路径受到保护，不受并发访问，但所有网桥端口netif的驱动程序都必须正确处理并发访问！==0：为每个输入数据包进入tcpip_thread（无多线程）注意：as==0依赖于tcpip。h、 默认值取决于NO_SYS设置
 */
#ifndef BRIDGEIF_PORT_NETIFS_OUTPUT_DIRECT
#define BRIDGEIF_PORT_NETIFS_OUTPUT_DIRECT  NO_SYS
#endif

/** BRIDGEIF_MAX_PORTS：这用于创建用于转发位字段的typedef：所需的位数是+1（对于内部/cpu端口）（63是最大值，导致位掩码为u64_t）注意：这仅控制实现的最大数量！每个网桥的最大端口数仍然必须通过netif_add参数传递！
 */
#ifndef BRIDGEIF_MAX_PORTS
#define BRIDGEIF_MAX_PORTS                  7
#endif

/**BRIDGEIF_DEBUG：在BRIDGEIF.c中启用通用调试。*/
#ifndef BRIDGEIF_DEBUG
#define BRIDGEIF_DEBUG                      LWIP_DBG_OFF
#endif

/**BRIDGEIF_DEBUG：在BRIDGEIF.c中启用FDB调试。*/
#ifndef BRIDGEIF_FDB_DEBUG
#define BRIDGEIF_FDB_DEBUG                  LWIP_DBG_OFF
#endif

/**BRIDGEIF_DEBUG：在BRIDGEIF.c中启用转发调试。*/
#ifndef BRIDGEIF_FW_DEBUG
#define BRIDGEIF_FW_DEBUG                   LWIP_DBG_OFF
#endif

/**
 * @}
 */

#endif /* LWIP_HDR_NETIF_BRIDGEIF_OPTS_H */

