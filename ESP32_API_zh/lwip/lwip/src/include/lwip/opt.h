/**
 * @file
 *
 * lwIP选项配置
 */

/*
 * 版权所有（c）2001-2004瑞典计算机科学研究所。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Adam Dunkels<adam@sics.se>
 *
 */

/*
 * 注意：||defined__DOXYGEN__是DOXYGEN bug的一个解决方法-如果没有这个，DOXYGEN将看不到实际的#define
 */

#if !defined LWIP_HDR_OPT_H
#define LWIP_HDR_OPT_H

/*
 * 首先包括用户定义的选项。这些文件中未定义的任何内容都将设置为标准值。覆盖任何你不喜欢的东西！
 */
#include "lwipopts.h"
#include "lwip/debug.h"

/**
 * @defgroup lwip_opts选项（lwipopts.h）
 * @ingroup 低密度聚乙烯
 *
 * @defgroup lwip_opts_debug调试
 * @ingroup lwip端口（_O）
 *
 * @defgroup lwip_opts_infrastructure基础设施
 * @ingroup lwip端口（_O）
 *
 * @defgroup lwip_opts_callback回调样式API
 * @ingroup lwip端口（_O）
 *
 * @defgroup lwip_opts_threadsafe_apis线程安全API
 * @ingroup lwip端口（_O）
 */

 /*
   ------------------------------------
   -------------- NO SYS --------------
   ------------------------------------
*/
/**
 * @defgroup lwip_opts_nosys NO_SYS公司
 * @ingroup lwip_opts基础设施@{
 */
/**
 * NO_SYS==1：使用lwIP时无需操作系统意识（无线程、信号量、互斥或mbox）。这意味着不能使用线程化api（socket、netconn，即“api”文件夹中的所有内容），只有回调样式的原始api可用（而且您必须小心，不能一次从多个上下文访问lwIP函数/结构！）
 */
#if !defined NO_SYS || defined __DOXYGEN__
#define NO_SYS                          0
#endif
/**
 * @}
 */

/**
 * @defgroup lwip_opts_timers计时器
 * @ingroup lwip_opts基础设施@{
 */
/**
 * LWIP_TIMERS==0:删除对sys_timeout和LWIP内部循环计时器的支持。（仍然提供lwip内部循环计时器阵列）（检查NO_SYS_NO_timers是否与旧版本兼容）
 */
#if !defined LWIP_TIMERS || defined __DOXYGEN__
#ifdef NO_SYS_NO_TIMERS
#define LWIP_TIMERS                     (!NO_SYS || (NO_SYS && !NO_SYS_NO_TIMERS))
#else
#define LWIP_TIMERS                     1
#endif
#endif

/**
 * LWIP_TIMERS_CUSTOM==1：提供自己的计时器实现。函数原型超时。h和lwip内部循环计时器阵列仍然包含在内，但实现没有。需要以下函数：sys_timeout_init（）、sys_timeout（）、sys_untimeout（）和sys_timeout_mbox_fetch（）
 */
#if !defined LWIP_TIMERS_CUSTOM || defined __DOXYGEN__
#define LWIP_TIMERS_CUSTOM              0
#endif
/**
 * @}
 */

/**
 * @defgroup lwip_opts_memcpy内存
 * @ingroup lwip_opts基础设施@{
 */
/**
 * MEMCPY：如果手头有比C库中包含的实现更快的实现，请重写此选项
 */
#if !defined MEMCPY || defined __DOXYGEN__
#define MEMCPY(dst,src,len)             memcpy(dst,src,len)
#endif

/**
 * SMEMCPY:小心忽略这个！如果长度在编译时已知并且很小，一些编译器（例如gcc）可以内联对memcpy（）的调用。
 */
#if !defined SMEMCPY || defined __DOXYGEN__
#define SMEMCPY(dst,src,len)            memcpy(dst,src,len)
#endif

/**
 * MEMMOVE：如果手头有比C库中包含的实现更快的实现，请重写此选项。lwIP当前仅在启用IPv6碎片支持时使用MEMMOVE。
 */
#if !defined MEMMOVE || defined __DOXYGEN__
#define MEMMOVE(dst,src,len)            memmove(dst,src,len)
#endif
/**
 * @}
 */

/*
   ------------------------------------
   -----------核心锁定-----------
   ------------------------------------
*/
/**
 * @defgroup lwip_opts_lock核心锁定和MPU
 * @ingroup lwip_opts基础设施@{
 */
/**
 * LWIP_MPU_COMPATIBLE：启用特殊的内存管理机制，通过不向其他线程传递堆栈指针，使LWIP能够在MPU（内存保护单元）系统上工作（这会降低性能，因为内存是从池分配的，而不是将其保留在堆栈上）
 */
#if !defined LWIP_MPU_COMPATIBLE || defined __DOXYGEN__
#define LWIP_MPU_COMPATIBLE             0
#endif

/**
 * LWIP_TCPIP_CORE_LOCKING创建TCPIP线程操作期间保持的全局互斥。可以由客户端代码锁定以执行lwIP操作，而无需使用回调更改为TCPIP线程。请参见LOCK_TCPP_CORE（）和UNLOCK_TCP_CORE（）。您的系统应该提供支持优先级反转的互斥锁来使用它。
 */
#if !defined LWIP_TCPIP_CORE_LOCKING || defined __DOXYGEN__
#define LWIP_TCPIP_CORE_LOCKING         1
#endif

/**
 * LWIP_TCPIP_CORE_LOCKING_INPUT：当启用LWIP_TCP IP_CORE-LOCKING时，这将使TCPIP_INPUT（）获取输入数据包的互斥锁，而不是分配消息并将其传递给TCPIP_thread。
 *
 * 注意：当从中断上下文调用tcpip_input（）时，这不起作用！
 */
#if !defined LWIP_TCPIP_CORE_LOCKING_INPUT || defined __DOXYGEN__
#define LWIP_TCPIP_CORE_LOCKING_INPUT   0
#endif

/**
 * SYS_LIGHTWEIGHT_PROT==1：在缓冲区分配、解除分配和内存分配和解除分配期间，为某些关键区域启用任务间保护（以及任务与中断保护）。注意：当从多个上下文中使用lwIP时，这是必需的！如果禁用此功能，则必须确保正在执行的操作！
 */
#if !defined SYS_LIGHTWEIGHT_PROT || defined __DOXYGEN__
#define SYS_LIGHTWEIGHT_PROT            1
#endif

/**
 * 宏/函数，用于检查在当前函数调用期间是否满足lwIP的线程/锁定要求。此宏通常调用在依赖于OS的sys层中实现的函数，并执行以下检查：
 * -不在ISR中（也应检查NO_SYS==1！）
 * - If @ref LWIP_TCPIP_CORE_LOCKING=1:TCPIP核心锁被保持
 * - If @ref LWIP_TCPIP_CORE_LOCKING=0：从TCPIP线程调用函数
 * @see @ref多线程
 */
#if !defined LWIP_ASSERT_CORE_LOCKED || defined __DOXYGEN__
#define LWIP_ASSERT_CORE_LOCKED()
#endif

/**
 * 在lwIP TCPIP线程中首先调用。可结合使用
 * with @ref LWIP_ASSERT_CORE_LOCKED以检查芯锁定。
 * @see @ref多线程
 */
#if !defined LWIP_MARK_TCPIP_THREAD || defined __DOXYGEN__
#define LWIP_MARK_TCPIP_THREAD()
#endif
/**
 * @}
 */

/*
   ------------------------------------
   ----------内存选项----------
   ------------------------------------
*/
/**
 * @defgroup lwip_opts_mem堆和内存池
 * @ingroup lwip_opts基础设施@{
 */
/**
 * MEM_LIBC_MALLOC==1：使用C库提供的MALLOC/free/realloc，而不是lwip内部分配器。如果您已经使用它，可以保存代码大小。
 */
#if !defined MEM_LIBC_MALLOC || defined __DOXYGEN__
#define MEM_LIBC_MALLOC                 0
#endif

/**
 * MEMP_MEM_MALLOC==1：使用MEM_MALLOC/MEM_free而不是lwip池分配器。对于MEM_LIBC_MALLOC特别有用，但要小心处理执行速度（堆分配可能比池分配慢得多）和中断使用情况（特别是如果netif驱动程序为从中断接收的帧分配PBUF_pool pbufs）！注意：目前，这将堆用于所有池（也用于私有池，不仅用于memp_std.h中定义的内部池）！
 */
#if !defined MEMP_MEM_MALLOC || defined __DOXYGEN__
#define MEMP_MEM_MALLOC                 0
#endif

/**
 * MEMP_MEM_INIT==1：强制使用memset初始化池内存。如果池在未初始化的内存段中移动，则非常有用。这将确保pcbs结构中的默认值在所有条件下都得到良好初始化。
 */
#if !defined MEMP_MEM_INIT || defined __DOXYGEN__
#define MEMP_MEM_INIT                   0
#endif

/**
 * MEM_ALIGNMENT：应设置为CPU 4字节对齐->\#define MEM_ALIGNMENT 4 2字节对齐->\#define MEM_ALIGNENT 2
 */
#if !defined MEM_ALIGNMENT || defined __DOXYGEN__
#define MEM_ALIGNMENT                   1
#endif

/**
 * MEM_SIZE：堆内存的大小。如果应用程序将发送大量需要复制的数据，则应将其设置为较高。
 */
#if !defined MEM_SIZE || defined __DOXYGEN__
#define MEM_SIZE                        1600
#endif

/**
 * MEMP_OVERFLOW_CHECK：MEMP溢出保护在每个池中的每个MEMP元素之前和之后保留一个可配置的字节数，并用一个突出的默认值填充它。MEMP_OVERFLOW_CHECK==0不检查MEMP_OVERFLOW_CHECK==1在释放每个元素时检查每个元素MEMP_OVERFLOW_CHECK>=2在每次调用MEMP_malloc（）或MEMP_free（）时检查每个池中的每个元素（有用但很慢！）
 */
#if !defined MEMP_OVERFLOW_CHECK || defined __DOXYGEN__
#define MEMP_OVERFLOW_CHECK             0
#endif

/**
 * MEMP_SANITY_CHECK==1：在每个MEMP_free（）之后运行健全性检查，以确保链接列表中没有循环。
 */
#if !defined MEMP_SANITY_CHECK || defined __DOXYGEN__
#define MEMP_SANITY_CHECK               0
#endif

/**
 * MEM_OVERFLOW_CHECK:MEM溢出保护在每个堆分配块之前和之后保留可配置的字节数，并用突出的默认值填充。MEM_OVERFLOW_CHECK==0不检查MEM_OVERFLOW_CHECK==1在释放每个元素时检查每个元素MEM_OVERFLOW_CHECK>=2每次调用MEM_malloc（）或MEM_free（）时检查所有堆元素（有用但很慢！）
 */
#if !defined MEM_OVERFLOW_CHECK || defined __DOXYGEN__
#define MEM_OVERFLOW_CHECK              0
#endif

/**
 * MEM_SANITY_CHECK==1：在每个MEM_free（）之后运行健全性检查，以确保堆元素的链接列表没有损坏。
 */
#if !defined MEM_SANITY_CHECK || defined __DOXYGEN__
#define MEM_SANITY_CHECK                0
#endif

/**
 * MEM_USE_POOLS==1：使用malloc（）的替代方法，从一组不同大小的内存池中进行分配。当调用mem_malloc时，将返回能够提供所需长度的最小池的元素。要使用此功能，还必须启用MEMP_use_CUSTOM_POOLS。
 */
#if !defined MEM_USE_POOLS || defined __DOXYGEN__
#define MEM_USE_POOLS                   0
#endif

/**
 * MEM_USE_POOLS_TRY_BIGGER_POOL==1：如果一个malloc池是空的，请尝试下一个更大的池-警告：这可能会浪费内存，但可以使系统更可靠。*/
#if !defined MEM_USE_POOLS_TRY_BIGGER_POOL || defined __DOXYGEN__
#define MEM_USE_POOLS_TRY_BIGGER_POOL   0
#endif

/**
 * MEMP_USE_CUSTOM_POOLS==1：是否包含用户文件lwippools。h定义了lwIP所需的“标准”池之外的其他池。如果将此设置为1，则必须具有lwippools。h在包含路径的某个位置。
 */
#if !defined MEMP_USE_CUSTOM_POOLS || defined __DOXYGEN__
#define MEMP_USE_CUSTOM_POOLS           0
#endif

/**
 * 如果要从中断上下文（或其他不允许等待信号量的上下文）中释放PBUF_RAM pbufs（或调用mem_free（）），请将其设置为1。如果设置为1，mem_malloc将受到信号量和SYS_ARCH_PROTECT的保护，而mem_free将仅使用SYS_ARCH-PROTECT。mem_malloc SYS_ARCH_UNPROTECT与每个循环关联，以便mem_free可以运行。
 *
 * 注意：从上面的描述中可以看到，这会导致经常中断/启用中断，这可能会很慢！此外，在内存不足的情况下，mem_malloc可能需要更长的时间。
 *
 * 如果您不想这样做，至少对于NO_SYS=0，您仍然可以使用以下函数将释放调用排入队列，然后在tcpip_thread上下文中运行：
 * -pbuf_free_callback（p）；
 * -mem_free_callback（m）；
 */
#if !defined LWIP_ALLOW_MEM_FREE_FROM_OTHER_CONTEXT || defined __DOXYGEN__
#define LWIP_ALLOW_MEM_FREE_FROM_OTHER_CONTEXT 0
#endif
/**
 * @}
 */

/*
   ------------------------------------------------
   ----------内部内存池大小----------
   ------------------------------------------------
*/
/**
 * @defgroup lwip_opts_memp内部内存池
 * @ingroup lwip_opts基础设施@{
 */
/**
 * MEMP_NUM_PBUF：MEMP结构pbufs的数量（用于PBUF_ROM和PBUF_REF）。如果应用程序从ROM（或其他静态存储器）发送大量数据，则应将其设置为高。
 */
#if !defined MEMP_NUM_PBUF || defined __DOXYGEN__
#define MEMP_NUM_PBUF                   16
#endif

/**
 * MEMP_NUM_RAW_PCB：原始连接PCB的数量（需要LWIP_RAW选项）
 */
#if !defined MEMP_NUM_RAW_PCB || defined __DOXYGEN__
#define MEMP_NUM_RAW_PCB                4
#endif

/**
 * MEMP_NUM_UDP_PCB：UDP协议控制块的数量。每个活动UDP“连接”一个。（需要LWIP_UDP选项）
 */
#if !defined MEMP_NUM_UDP_PCB || defined __DOXYGEN__
#define MEMP_NUM_UDP_PCB                4
#endif

/**
 * MEMP_NUM_TCP_PCB：同时活动的TCP连接数。（需要LWIP_TCP选项）
 */
#if !defined MEMP_NUM_TCP_PCB || defined __DOXYGEN__
#define MEMP_NUM_TCP_PCB                5
#endif

/**
 * MEMP_NUM_TCP_PCB_LISTEN：侦听TCP连接的数量。（需要LWIP_TCP选项）
 */
#if !defined MEMP_NUM_TCP_PCB_LISTEN || defined __DOXYGEN__
#define MEMP_NUM_TCP_PCB_LISTEN         8
#endif

/**
 * MEMP_NUM_TCP_SEG：同时排队的TCP段数。（需要LWIP_TCP选项）
 */
#if !defined MEMP_NUM_TCP_SEG || defined __DOXYGEN__
#define MEMP_NUM_TCP_SEG                16
#endif

/**
 * MEMP_NUM_ALTCP_PCB：同时活动的ALTCP层PCB的数量。（需要LWIP_ALTCP选项）具有多个层的连接需要多个ALTCP_pcb（例如，TCP上的TLS需要两个ALTCP_prcb，一个用于TLS，另一个用于TCP）。
 */
#if !defined MEMP_NUM_ALTCP_PCB || defined __DOXYGEN__
#define MEMP_NUM_ALTCP_PCB              MEMP_NUM_TCP_PCB
#endif

/**
 * MEMP_NUM_REASSDATA：同时排队重新组装的IP数据包的数量（整个数据包，而不是碎片！）
 */
#if !defined MEMP_NUM_REASSDATA || defined __DOXYGEN__
#define MEMP_NUM_REASSDATA              5
#endif

/**
 * MEMP_NUM_FRAG_BUF：同时发送的IP片段数（片段，而不是整个数据包！）。这仅适用于LWIP_NETIF_TX_SINGLE_BUF==0，并且仅适用于启用DMA的MAC，当NETIF->输出返回时，数据包尚未发送。
 */
#if !defined MEMP_NUM_FRAG_PBUF || defined __DOXYGEN__
#define MEMP_NUM_FRAG_PBUF              15
#endif

/**
 * MEMP_NUM_ARP_QUEUE：等待ARP请求（解析其目标地址）完成的同时排队的传出数据包（pbuf）的数量。（需要ARP_QUEUEING选项）
 */
#if !defined MEMP_NUM_ARP_QUEUE || defined __DOXYGEN__
#define MEMP_NUM_ARP_QUEUE              30
#endif

/**
 * MEMP_NUM_IGMP_GROUP：其网络接口可以同时成为成员的多播组的数量（每个netif-allsystems组一个，每个netif成员一个）。（需要LWIP_IGMP选项）
 */
#if !defined MEMP_NUM_IGMP_GROUP || defined __DOXYGEN__
#define MEMP_NUM_IGMP_GROUP             8
#endif

/**
 * 核心堆栈（而不是应用程序）使用的系统超时数此处计算所有已启用模块的默认超时数。
 */
#if ESP_LWIP
#define LWIP_NUM_SYS_TIMEOUT_INTERNAL   (LWIP_TCP + IP_REASSEMBLY + (LWIP_ARP + (ESP_GRATUITOUS_ARP ? 1 : 0)) + (2*LWIP_DHCP + (ESP_DHCPS_TIMER ? 1 : 0)) + LWIP_AUTOIP + LWIP_IGMP + LWIP_DNS + PPP_NUM_TIMEOUTS + (LWIP_IPV6 * (1 + LWIP_IPV6_REASS + LWIP_IPV6_MLD)))
#else
#define LWIP_NUM_SYS_TIMEOUT_INTERNAL   (LWIP_TCP + IP_REASSEMBLY + LWIP_ARP + (2*LWIP_DHCP) + LWIP_AUTOIP + LWIP_IGMP + LWIP_DNS + PPP_NUM_TIMEOUTS + (LWIP_IPV6 * (1 + LWIP_IPV6_REASS + LWIP_IPV6_MLD)))
#endif
/**
 * MEMP_NUM_SYS_TIMEOUT：同时活动超时的数量。此处计算所有已启用模块的默认超时数。公式要求设置为“0”或“1”。
 */
#if !defined MEMP_NUM_SYS_TIMEOUT || defined __DOXYGEN__
#define MEMP_NUM_SYS_TIMEOUT            LWIP_NUM_SYS_TIMEOUT_INTERNAL
#endif

/**
 * MEMP_NUM_NETBUF：结构netbufs的数量。（仅当使用顺序API（如API_lib.c）时才需要）
 */
#if !defined MEMP_NUM_NETBUF || defined __DOXYGEN__
#define MEMP_NUM_NETBUF                 2
#endif

/**
 * MEMP_NUM_NETCONN：结构NETCONN的数量。（仅当使用顺序API（如API_lib.c）时才需要）
 */
#if !defined MEMP_NUM_NETCONN || defined __DOXYGEN__
#define MEMP_NUM_NETCONN                4
#endif

/**
 * MEMP_NUM_SELECT_CB：结构lwip_SELECT_CB的数量。（只有当LWIP_MPU_COMPATIBLE==1并使用套接字API时才需要。在这种情况下，每个线程需要一个调用LWIP_select的API。）
 */
#if !defined MEMP_NUM_SELECT_CB || defined __DOXYGEN__
#define MEMP_NUM_SELECT_CB              4
#endif

/**
 * MEMP_NUM_TCPIP_MSG_API：用于回调/超时API通信的结构TCPIP_MSG的数量。（仅在使用tcpip.c时需要）
 */
#if !defined MEMP_NUM_TCPIP_MSG_API || defined __DOXYGEN__
#define MEMP_NUM_TCPIP_MSG_API          8
#endif

/**
 * MEMP_NUM_TCPIP_MSG_INPKT：用于传入数据包的结构TCPIP_MSG的数量。（仅在使用tcpip.c时需要）
 */
#if !defined MEMP_NUM_TCPIP_MSG_INPKT || defined __DOXYGEN__
#define MEMP_NUM_TCPIP_MSG_INPKT        8
#endif

/**
 * MEMP_NUM_NETDB：同时运行的lwip_addrinfo（）调用数（在使用lwip_freeaddrinfo（）释放相应内存之前）。
 */
#if !defined MEMP_NUM_NETDB || defined __DOXYGEN__
#define MEMP_NUM_NETDB                  1
#endif

/**
 * MEMP_NUM_LOCALHOSTLIST：如果DNS_local_HOSTLIST_IS_DYNAMIC==1，则本地主机列表中的主机条目数。
 */
#if !defined MEMP_NUM_LOCALHOSTLIST || defined __DOXYGEN__
#define MEMP_NUM_LOCALHOSTLIST          1
#endif

/**
 * PBUF_POOL_SIZE：PBUF池中的缓冲区数。
 */
#if !defined PBUF_POOL_SIZE || defined __DOXYGEN__
#define PBUF_POOL_SIZE                  16
#endif

/** MEMP_NUM_API_MSG：对各种套接字、netconn和tcpip函数的并发活动调用数
 */
#if !defined MEMP_NUM_API_MSG || defined __DOXYGEN__
#define MEMP_NUM_API_MSG                MEMP_NUM_TCPIP_MSG_API
#endif

/** MEMP_NUM_DNS_API_MSG：对netconn_gethostbyname的并发活动调用数
 */
#if !defined MEMP_NUM_DNS_API_MSG || defined __DOXYGEN__
#define MEMP_NUM_DNS_API_MSG            MEMP_NUM_TCPIP_MSG_API
#endif

/** MEMP_NUM_SOCKET_SETGETSOCKOPT_DATA:getsockoopt/setsockopt的并发活动调用数
 */
#if !defined MEMP_NUM_SOCKET_SETGETSOCKOPT_DATA || defined __DOXYGEN__
#define MEMP_NUM_SOCKET_SETGETSOCKOPT_DATA MEMP_NUM_TCPIP_MSG_API
#endif

/** MEMP_NUM_NETIFAPI_MSG：对NETIFAPI函数的并发活动调用数
 */
#if !defined MEMP_NUM_NETIFAPI_MSG || defined __DOXYGEN__
#define MEMP_NUM_NETIFAPI_MSG           MEMP_NUM_TCPIP_MSG_API
#endif
/**
 * @}
 */

/*
   ---------------------------------
   ----------ARP选项----------
   ---------------------------------
*/
/**
 * @defgroup lwip_opts_arp arp协议
 * @ingroup lwip_opts_ipv4@{
 */
/**
 * LWIP_ARP==1：启用ARP功能。
 */
#if !defined LWIP_ARP || defined __DOXYGEN__
#define LWIP_ARP                        1
#endif

/**
 * ARP_TABLE_SIZE:缓存的活动MAC-IP地址对数。
 */
#if !defined ARP_TABLE_SIZE || defined __DOXYGEN__
#define ARP_TABLE_SIZE                  10
#endif

/** ARP条目在其上次更新后保持有效的时间，对于ARP_TMR_INTERVAL=1000，这是（60 5）秒=5分钟。
 */
#if !defined ARP_MAXAGE || defined __DOXYGEN__
#define ARP_MAXAGE                      300
#endif

/**
 * ARP_QUEUEING==1：在硬件地址解析期间，多个传出数据包被排队。默认情况下，每个IP地址只排队最近的数据包。这对于大多数协议来说已经足够了，并且主要减少了TCP连接启动时间。如果您知道应用程序在一行中向不在ARP缓存中的IP地址发送了多个数据包，请将此值设置为1。
 */
#if !defined ARP_QUEUEING || defined __DOXYGEN__
#define ARP_QUEUEING                    0
#endif

/** 其他网络层可以为每个未解析地址排队的最大数据包数。默认值为3，0表示禁用。旧数据包被丢弃，新数据包被排队。
 */
#if !defined ARP_QUEUE_LEN || defined __DOXYGEN__
#define ARP_QUEUE_LEN                   3
#endif

/**
 * ETHARP_SUPPORT_VLAN==1：支持接收和发送带有VLAN报头的以太网数据包。请参阅LWIP_HOOK_VLAN_CHECK和LWIP_HOOK_VLAN_SET挂钩的说明，以检查/设置VLAN标头。此外，您可以将ETHARP_VLAN_CHECK定义为要检查的u16_t VLAN ID。如果定义了ETHARP_VLAN_CHECK，则只接受此VLAN的VLAN流量。如果未定义ETHARP_VALAN_CHECK，则接受所有流量。或者，定义一个函数/定义ETHARP_VLAN_CHECK_FN（eth_hdr，VLAN），返回1表示接受数据包，返回0表示丢弃数据包。
 */
#if !defined ETHARP_SUPPORT_VLAN || defined __DOXYGEN__
#define ETHARP_SUPPORT_VLAN             0
#endif

/** LWIP_ETHERNET==1：即使ARP可能被禁用，也启用以太网支持
 */
#if !defined LWIP_ETHERNET || defined __DOXYGEN__
#define LWIP_ETHERNET                   LWIP_ARP
#endif

/** ETH_PAD_SIZE：在以太网报头之前添加的字节数，以确保该报头之后的有效负载对齐。由于标头长度为14字节，如果没有此填充，例如IP标头中的地址将不会在32位边界上对齐，因此将其设置为2可以加快32位平台的速度。
 */
#if !defined ETH_PAD_SIZE || defined __DOXYGEN__
#define ETH_PAD_SIZE                    0
#endif

/** ETHARP_SUPPORT_STATIC_ENTRIES==1：启用代码以支持静态ARP表条目（使用ETHARP_add_STATIC_entry/ETHARP_move_STATIC_eentry）。
 */
#if !defined ETHARP_SUPPORT_STATIC_ENTRIES || defined __DOXYGEN__
#define ETHARP_SUPPORT_STATIC_ENTRIES   0
#endif

/** ETHARP_ABLE_MATCH_NETIF==1：匹配ARP表条目的NETIF。如果禁用，则不支持多个netif上的重复IP地址（但这只适用于AutoIP）。
 */
#if !defined ETHARP_TABLE_MATCH_NETIF || defined __DOXYGEN__
#define ETHARP_TABLE_MATCH_NETIF        !LWIP_SINGLE_NETIF
#endif
/**
 * @}
 */

/*
   --------------------------------
   ----------IP选项----------
   --------------------------------
*/
/**
 * @defgroup lwip_opts_ipv4 ipv4
 * @ingroup lwip端口（_O）@{
 */
/**
 * LWIP_IPV4==1:启用IPV4
 */
#if !defined LWIP_IPV4 || defined __DOXYGEN__
#define LWIP_IPV4                       1
#endif

/**
 * IP_FORWARD==1：允许跨网络接口转发IP数据包。如果要在只有一个网络接口的设备上运行lwIP，请将其定义为0。
 */
#if !defined IP_FORWARD || defined __DOXYGEN__
#define IP_FORWARD                      0
#endif

/**
 * IP_REASSEMBLY==1：重新组装传入的碎片化IP数据包。注意，此选项不影响传出数据包大小，可通过IP_FRAG控制。
 */
#if !defined IP_REASSEMBLY || defined __DOXYGEN__
#define IP_REASSEMBLY                   1
#endif

/**
 * IP_FRAG==1：如果传出IP数据包的大小超过MTU，则将其分段。请注意，此选项不影响传入数据包大小，可以通过IP_REASSEMBLY控制。
 */
#if !defined IP_FRAG || defined __DOXYGEN__
#define IP_FRAG                         1
#endif

#if !LWIP_IPV4
/* 禁用IPv4时禁用IPv4扩展*/
#undef IP_FORWARD
#define IP_FORWARD                      0
#undef IP_REASSEMBLY
#define IP_REASSEMBLY                   0
#undef IP_FRAG
#define IP_FRAG                         0
#endif /* !LWIP_IPV4 */

/**
 * IP_NAPT==1:启用IPv4网络地址和端口转换注意，需要启用IP_FORWARD，NAPT才能工作
 */
#if !defined IP_NAPT || defined __DOXYGEN__
#define IP_NAPT                      0
#endif

/**
 * IP_OPTIONS_ALLOWED：定义IP选项的行为。IP_OPTIONS_ALLOWED==0：丢弃所有具有IP选项的数据包。IP_OPTIONS_ALLOWED==1:IP选项是允许的（但不分析）。
 */
#if !defined IP_OPTIONS_ALLOWED || defined __DOXYGEN__
#define IP_OPTIONS_ALLOWED              1
#endif

/**
 * IP_REASS_MAXAGE：碎片化IP数据包等待所有碎片到达的最长时间（以IP_TMR_INTERVAL的倍数表示，通常为秒）。如果此时不是所有碎片都到达，则丢弃整个数据包。
 */
#if !defined IP_REASS_MAXAGE || defined __DOXYGEN__
#define IP_REASS_MAXAGE                 15
#endif

/**
 * IP_REASS_MAX_PBUFS：等待重新组装的pbuf的最大总数。由于接收到的PBUF已入队，请确保配置PBUF_POOL_SIZE>IP_REASS_MAX_pbufs，以便堆栈仍然能够接收数据包，即使已入队进行重组的碎片数量达到最大！启用IPv4和IPv6时，甚至会变为（PBUF_POOL_SIZE>2IP_REASS_MAX_PBUFS）！
 */
#if !defined IP_REASS_MAX_PBUFS || defined __DOXYGEN__
#define IP_REASS_MAX_PBUFS              10
#endif

/**
 * IP_DEFAULT_TTL：传输层使用的生存时间的默认值。
 */
#if !defined IP_DEFAULT_TTL || defined __DOXYGEN__
#define IP_DEFAULT_TTL                  255
#endif

/**
 * IP_SOF_BROADCAST=1：使用SOF_BROADCAS字段启用udp和原始发送操作上每个pcb的广播过滤器。要在录制操作上启用广播筛选器，还必须将IP_SOF_broadcast_recv设置为1。
 */
#if !defined IP_SOF_BROADCAST || defined __DOXYGEN__
#define IP_SOF_BROADCAST                0
#endif

/**
 * IP_SOF_BROADCAST_RECV（要求IP_SOF-BROADCAST=1）在录制操作上启用广播过滤器。
 */
#if !defined IP_SOF_BROADCAST_RECV || defined __DOXYGEN__
#define IP_SOF_BROADCAST_RECV           0
#endif

/**
 * IP_FORWARD_ALLOW_TX_ON_RX_NETIF==1：允许IP_FORWARD（）将数据包发送回接收数据包的NETIF。这只能用于无线网络。注意：当该值为1时，请确保netif驱动程序使用相应的pbuf标志正确标记传入的链路层广播/多播数据包！
 */
#if !defined IP_FORWARD_ALLOW_TX_ON_RX_NETIF || defined __DOXYGEN__
#define IP_FORWARD_ALLOW_TX_ON_RX_NETIF 0
#endif
/**
 * @}
 */

/*
   ----------------------------------
   ----------ICMP选项----------
   ----------------------------------
*/
/**
 * @defgroup lwip_opts_icmp icmp
 * @ingroup lwip_opts_ipv4@{
 */
/**
 * LWIP_ICMP==1：在IP堆栈内启用ICMP模块。小心，禁用会使您的产品不符合RFC1122
 */
#if !defined LWIP_ICMP || defined __DOXYGEN__
#define LWIP_ICMP                       1
#endif

/**
 * ICMP_TTL:ICMP数据包使用的生存时间的默认值。
 */
#if !defined ICMP_TTL || defined __DOXYGEN__
#define ICMP_TTL                        IP_DEFAULT_TTL
#endif

/**
 * LWIP_BROADCAST_PING==1：响应广播PING（默认为仅单播）
 */
#if !defined LWIP_BROADCAST_PING || defined __DOXYGEN__
#define LWIP_BROADCAST_PING             0
#endif

/**
 * LWIP_MULTICAST_PING==1：响应多播PING（默认值仅为单播）
 */
#if !defined LWIP_MULTICAST_PING || defined __DOXYGEN__
#define LWIP_MULTICAST_PING             0
#endif
/**
 * @}
 */

/*
   ---------------------------------
   ----------RAW选项----------
   ---------------------------------
*/
/**
 * @defgroup lwip_opts_raw原始
 * @ingroup lwip_opts回调@{
 */
/**
 * LWIP_RAW==1：使应用程序层能够挂接到IP层本身。
 */
#if !defined LWIP_RAW || defined __DOXYGEN__
#define LWIP_RAW                        0
#endif

/**
 * LWIP_RAW==1：使应用程序层能够挂接到IP层本身。
 */
#if !defined RAW_TTL || defined __DOXYGEN__
#define RAW_TTL                         IP_DEFAULT_TTL
#endif
/**
 * @}
 */

/*
   ----------------------------------
   ----------DHCP选项----------
   ----------------------------------
*/
/**
 * @defgroup lwip_opts_dhcp dhcp
 * @ingroup lwip_opts_ipv4@{
 */
/**
 * LWIP_DHCP==1：启用DHCP模块。
 */
#if !defined LWIP_DHCP || defined __DOXYGEN__
#define LWIP_DHCP                       0
#endif
#if !LWIP_IPV4
/* 禁用IPv4时禁用DHCP*/
#undef LWIP_DHCP
#define LWIP_DHCP                       0
#endif /* !LWIP_IPV4 */

/**
 * DHCP_DOES_ARP_CHECK==1：对提供的地址执行ARP检查。
 */
#if !defined DHCP_DOES_ARP_CHECK || defined __DOXYGEN__
#define DHCP_DOES_ARP_CHECK             (LWIP_DHCP && LWIP_ARP)
#endif

/**
 * LWIP_DHCP_BOOTP_FILE==1：存储offered_si_addr和boot_FILE_name。
 */
#if !defined LWIP_DHCP_BOOTP_FILE || defined __DOXYGEN__
#define LWIP_DHCP_BOOTP_FILE            0
#endif

/**
 * LWIP_DHCP_GETS_NTP==1：使用发现/选择请求NTP服务器。对于每个响应包，都会调用一个回调，该回调必须由端口提供：void dhcp_set_ntp_servers（u8_t num_ntp_server，ip_addr_t ntp_server_addrs）；
*/
#if !defined LWIP_DHCP_GET_NTP_SRV || defined __DOXYGEN__
#define LWIP_DHCP_GET_NTP_SRV           0
#endif

/**
 * 请求的NTP服务器的最大数量
 */
#if !defined LWIP_DHCP_MAX_NTP_SERVERS || defined __DOXYGEN__
#define LWIP_DHCP_MAX_NTP_SERVERS       1
#endif

/**
 * LWIP_DHCP_MAX_DNS_SERVERS>0：请求具有发现/选择功能的DNS服务器。响应中接收的DNS服务器通过@ref DNS_setserver（）传递给DNS（达到此处定义的最大限制）。
 */
#if !defined LWIP_DHCP_MAX_DNS_SERVERS || defined __DOXYGEN__
#define LWIP_DHCP_MAX_DNS_SERVERS       DNS_MAX_SERVERS
#endif
/**
 * @}
 */

#ifndef LWIP_DHCP_IP_ADDR_RESTORE
#define LWIP_DHCP_IP_ADDR_RESTORE()       0
#endif

#ifndef LWIP_DHCP_IP_ADDR_STORE
#define LWIP_DHCP_IP_ADDR_STORE()
#endif

#ifndef LWIP_DHCP_IP_ADDR_ERASE
#define LWIP_DHCP_IP_ADDR_ERASE(esp_netif)
#endif

/*
   ------------------------------------
   ----------AUTOIP选项----------
   ------------------------------------
*/
/**
 * @defgroup lwip_opts_autoip自动IP
 * @ingroup lwip_opts_ipv4@{
 */
/**
 * LWIP_AUTOIP==1：启用AUTOIP模块。
 */
#if !defined LWIP_AUTOIP || defined __DOXYGEN__
#define LWIP_AUTOIP                     0
#endif
#if !LWIP_IPV4
/* 禁用IPv4时禁用AUTOIP*/
#undef LWIP_AUTOIP
#define LWIP_AUTOIP                     0
#endif /* !LWIP_IPV4 */

/**
 * LWIP_DHCP_AUTOIP_COP==1：允许同时在同一接口上启用DHCP和AUTOIP。
 */
#if !defined LWIP_DHCP_AUTOIP_COOP || defined __DOXYGEN__
#define LWIP_DHCP_AUTOIP_COOP           0
#endif

/**
 * ESP_IPV6_ATOCONFIG==1：根据RFC 4862启用无状态地址自动配置。
 */
#if !defined ESP_IPV6_AUTOCONFIG
#define ESP_IPV6_AUTOCONFIG 0
#endif

/**
 * LWIP_DHCP_AUTOIP_COP_TRIES：设置为在返回AUTOIP之前应发送的DHCP DISCOVER探测数（在这种情况下，DHCP客户端保持运行）。这可以设置为低至1，以快速获得AutoIP地址，但当DHCP覆盖AutoIP时，您应该准备好处理更改的IP地址。
 */
#if !defined LWIP_DHCP_AUTOIP_COOP_TRIES || defined __DOXYGEN__
#define LWIP_DHCP_AUTOIP_COOP_TRIES     9
#endif
/**
 * @}
 */

/*
   ----------------------------------
   -----SNMP MIB2支持-----
   ----------------------------------
*/
/**
 * @defgroup lwip_opts_mib2 SNMP mib2回调
 * @ingroup lwip_opts基础设施@{
 */
/**
 * LWIP_MIB2_CALLBACKS==1：打开SNMP MIB2回调。启用此选项可获取实现MIB2所需的回调。通常也应启用MIB2_STATS。
 */
#if !defined LWIP_MIB2_CALLBACKS || defined __DOXYGEN__
#define LWIP_MIB2_CALLBACKS             0
#endif
/**
 * @}
 */

/*
   ----------------------------------
   --------多播选项-------
   ----------------------------------
*/
/**
 * @defgroup lwip_opts_multicast多播
 * @ingroup lwip_opts基础设施@{
 */
/**
 * LWIP_MULTICAST_TX_OPTIONS==1：启用多播传输支持，如套接字选项IP_MULTIACST_TTL/IP_MULTICACT_IF/IP_MULTICAST_LOOP，以及相应IPv6选项的核心支持（当前仅限）。
 */
#if !defined LWIP_MULTICAST_TX_OPTIONS || defined __DOXYGEN__
#define LWIP_MULTICAST_TX_OPTIONS       ((LWIP_IGMP || LWIP_IPV6_MLD) && (LWIP_UDP || LWIP_RAW))
#endif
/**
 * @}
 */

/*
   ----------------------------------
   ----------IGMP选项----------
   ----------------------------------
*/
/**
 * @defgroup lwip_opts_igmp igmp
 * @ingroup lwip_opts_ipv4@{
 */
/**
 * LWIP_IGMP==1：打开IGMP模块。
 */
#if !defined LWIP_IGMP || defined __DOXYGEN__
#define LWIP_IGMP                       0
#endif
#if !LWIP_IPV4
#undef LWIP_IGMP
#define LWIP_IGMP                       0
#endif
/**
 * @}
 */

/*
   ----------------------------------
   ----------DNS选项-----------
   ----------------------------------
*/
/**
 * @defgroup lwip_opts_dns dns
 * @ingroup lwip_opts回调@{
 */
/**
 * LWIP_DNS==1:打开DNS模块。UDP必须可用于DNS传输。
 */
#if !defined LWIP_DNS || defined __DOXYGEN__
#define LWIP_DNS                        0
#endif

/**DNS本地维护的最大条目数。*/
#if !defined DNS_TABLE_SIZE || defined __DOXYGEN__
#define DNS_TABLE_SIZE                  4
#endif

/**名称表中支持的DNS最大主机名长度。*/
#if !defined DNS_MAX_NAME_LENGTH || defined __DOXYGEN__
#define DNS_MAX_NAME_LENGTH             256
#endif

/** DNS服务器的最大数量第一台服务器可以通过定义DNS_server_ADDRESS（ipaddr）自动初始化，其中“ipaddr”是“ip_addr_t”
 */
#if !defined DNS_MAX_SERVERS || defined __DOXYGEN__
#define DNS_MAX_SERVERS                 2
#endif

/**在“超时”之前，请求名称时的DNS最大重试次数。*/
#if !defined DNS_MAX_RETRIES || defined __DOXYGEN__
#define DNS_MAX_RETRIES                 4
#endif

/**DNS在查询和响应之间进行名称检查。*/
#if !defined DNS_DOES_NAME_CHECK || defined __DOXYGEN__
#define DNS_DOES_NAME_CHECK             1
#endif

/**LWIP_DNS_SECURE：控制DNS实现的安全级别默认使用所有DNS安全功能。这是可重写的，但应该仅在非常小的目标或在对非标准DNS服务器使用时才需要。*/
#if !defined LWIP_DNS_SECURE || defined __DOXYGEN__
#define LWIP_DNS_SECURE (LWIP_DNS_SECURE_RAND_XID | LWIP_DNS_SECURE_NO_MULTIPLE_OUTSTANDING | LWIP_DNS_SECURE_RAND_SRC_PORT)
#endif

/* DNS安全功能列表如下*/
#define LWIP_DNS_SECURE_RAND_XID                1
#define LWIP_DNS_SECURE_NO_MULTIPLE_OUTSTANDING 2
#define LWIP_DNS_SECURE_RAND_SRC_PORT           4

/** DNS_LOCAL_HOSTLIST：实现本地主机到地址列表。如果已启用，则必须定义一个初始值设定项：\#define DNS_LOCAL_HOSTLIST_INIT｛DNS_LOCAL_HOSTLIST_ELEM（“host_ip4”，IPADDR4_INIT_BYTES（1,2,3,4）），\DNS_LOCAL-HOSTLIST_ELE（“host_id6”，IPADDR6_INIT_host（123234345456）｝
 *
 *  相反，您也可以使用外部函数：\#define DNS_LOOKUP_LOCAL_EXTERN（x）EXTERN err_t my_LOOKUP_function（const char name，ip_addr_t addr，u8_t DNS_addrtype），该函数查找ip地址，如果找到则返回err_OK（LWIP_DNS_addrtype_xxx在DNS_addrtype中传递）。
 */
#if !defined DNS_LOCAL_HOSTLIST || defined __DOXYGEN__
#define DNS_LOCAL_HOSTLIST              0
#endif /* DNS_LOCAL_HOSTLIST */

/**如果启用此选项，则可以在运行时动态更改本地主机列表。*/
#if !defined DNS_LOCAL_HOSTLIST_IS_DYNAMIC || defined __DOXYGEN__
#define DNS_LOCAL_HOSTLIST_IS_DYNAMIC   0
#endif /* DNS_LOCAL_HOSTLIST_IS_DYNAMIC */

/**将此值设置为1以启用使用一次多播DNS查询通过mDNS查询“.local”名称*/
#if !defined LWIP_DNS_SUPPORT_MDNS_QUERIES || defined __DOXYGEN__
#define LWIP_DNS_SUPPORT_MDNS_QUERIES   0
#endif
/**
 * @}
 */

/*
   ---------------------------------
   ----------UDP选项----------
   ---------------------------------
*/
/**
 * @defgroup lwip_opts_udp udp
 * @ingroup lwip_opts回调@{
 */
/**
 * LWIP_UDP==1：打开UDP。
 */
#if !defined LWIP_UDP || defined __DOXYGEN__
#define LWIP_UDP                        1
#endif

/**
 * LWIP_UDPLITE==1：打开UDP Lite。（需要LWIP_UDP）
 */
#if !defined LWIP_UDPLITE || defined __DOXYGEN__
#define LWIP_UDPLITE                    0
#endif

/**
 * UDP_TTL：默认生存时间值。
 */
#if !defined UDP_TTL || defined __DOXYGEN__
#define UDP_TTL                         IP_DEFAULT_TTL
#endif

/**
 * LWIP_NETBUF_RECINFO==1：将目标地址和端口附加到每个NETBUF。
 */
#if !defined LWIP_NETBUF_RECVINFO || defined __DOXYGEN__
#define LWIP_NETBUF_RECVINFO            0
#endif
/**
 * @}
 */

/*
   ---------------------------------
   ----------TCP选项----------
   ---------------------------------
*/
/**
 * @defgroup lwip_opts_tcp tcp
 * @ingroup lwip_opts回调@{
 */
/**
 * LWIP_TCP==1：打开TCP。
 */
#if !defined LWIP_TCP || defined __DOXYGEN__
#define LWIP_TCP                        1
#endif

/**
 * TCP_TTL：默认生存时间值。
 */
#if !defined TCP_TTL || defined __DOXYGEN__
#define TCP_TTL                         IP_DEFAULT_TTL
#endif

/**
 * TCP_WND：TCP窗口的大小。这必须至少是（2 TCP_MSS）才能正常工作。注意：使用TCP_RCV_SCALE时，TCP_WND是应用缩放的总大小。TCP标头中的最大窗口值将为TCP_WND>>TCP_RCV_SCALE
 */
#if !defined TCP_WND || defined __DOXYGEN__
#define TCP_WND                         (4 * TCP_MSS)
#endif

/**
 * TCP_MAXRTX：数据段的最大重传次数。
 */
#if !defined TCP_MAXRTX || defined __DOXYGEN__
#define TCP_MAXRTX                      12
#endif

/**
 * TCP_SYNMAXRTX：SYN段的最大重传次数。
 */
#if !defined TCP_SYNMAXRTX || defined __DOXYGEN__
#define TCP_SYNMAXRTX                   6
#endif

/**
 * TCP_QUEUE_OOSEQ==1:TCP将对无序到达的段进行排队。如果设备内存不足，则定义为0。
 */
#if !defined TCP_QUEUE_OOSEQ || defined __DOXYGEN__
#define TCP_QUEUE_OOSEQ                 LWIP_TCP
#endif

/**
 * LWIP_TCP_SACK_OUT==1:TCP将支持发送选择性确认（SACK）。
 */
#if !defined LWIP_TCP_SACK_OUT || defined __DOXYGEN__
#define LWIP_TCP_SACK_OUT               0
#endif

/**
 * LWIP_TCP_MAX_SACK_NUM:要包含在TCP段中的SACK值的最大数量。必须至少为1，但仅在启用LWIP_TCP_SACK_OUT时使用。注意：尽管我们在单个段中发送的SACK范围从未超过3或4（取决于其他选项），但将此选项设置为大于4的值并非毫无意义。这基本上是我们要跟踪的SACK范围的最大数量。随着新数据的传递，一些SACK范围可能会被删除或合并。在这种情况下，可以再次使用一些较旧的SACK范围。用于存储SACK范围的内存量为每个TCP PCB的LWIP_TCP_MAX_SACK_NUM 8字节。
 */
#if !defined LWIP_TCP_MAX_SACK_NUM || defined __DOXYGEN__
#define LWIP_TCP_MAX_SACK_NUM           4
#endif

/**
 * TCP_MSS:TCP最大段大小。（默认值为536，这是保守的默认值，您可能需要增加此值。）对于接收端，当打开连接时，此MSS会向远程端通告。对于传输大小，该MSS设置远程主机通告的MSS上限。
 */
#if !defined TCP_MSS || defined __DOXYGEN__
#define TCP_MSS                         536
#endif

/**
 * TCP_CCULATE_EFF_SEND_MSS：“TCP真正发送的段的最大大小，即‘有效发送MSS’，必须是发送MSS（反映远程主机上可用的重组缓冲区大小）和IP层允许的最大大小中的较小者”（RFC 1122）将其设置为1启用代码，该代码将TCP_MSS与用于连接的netif的MTU进行检查，并在以下情况下限制MSS否则就太大了。
 */
#if !defined TCP_CALCULATE_EFF_SEND_MSS || defined __DOXYGEN__
#define TCP_CALCULATE_EFF_SEND_MSS      1
#endif


/**
 * TCP_SND_BUF:TCP发送方缓冲区空间（字节）。为了获得良好的性能，这至少应为2 TCP_MSS。
 */
#if !defined TCP_SND_BUF || defined __DOXYGEN__
#define TCP_SND_BUF                     (2 * TCP_MSS)
#endif

/**
 * TCP_SND_QUEUELEN:TCP发送方缓冲区空间（pbufs）。这必须至少与（2 TCP_SND_BUF/TCP_MSS）一样多才能工作。
 */
#if !defined TCP_SND_QUEUELEN || defined __DOXYGEN__
#define TCP_SND_QUEUELEN                ((4 * (TCP_SND_BUF) + (TCP_MSS - 1))/(TCP_MSS))
#endif

/**
 * TCP_SNDLOWAT:TCP可写空间（字节）。这必须小于TCP_SND_BUF。这是TCP snd_buf中必须可用的空间量，以便选择返回可写（与TCP_SNDQUEUELOWAT结合）。
 */
#if !defined TCP_SNDLOWAT || defined __DOXYGEN__
#define TCP_SNDLOWAT                    LWIP_MIN(LWIP_MAX(((TCP_SND_BUF)/2), (2 * TCP_MSS) + 1), (TCP_SND_BUF) - 1)
#endif

/**
 * TCP_SNDQUEUELOWAT:TCP可写缓冲区（pbuf计数）。这必须小于TCP_SND_QUEUELEN。如果pcb上排队的pbuf数量低于此数量，请选择return writible（与TCP_SNDLOWAT组合）。
 */
#if !defined TCP_SNDQUEUELOWAT || defined __DOXYGEN__
#define TCP_SNDQUEUELOWAT               LWIP_MAX(((TCP_SND_QUEUELEN)/2), 5)
#endif

/**
 * TCP_OOSEQ_MAX_BYTES：如果未定义TCP_OOSSEQ_BYTES_LIMIT，则每个pcb上排队的默认最大字节数。默认值为0（无限制）。仅对TCP_QUEUE_OOSEQ==1有效。
 */
#if !defined TCP_OOSEQ_MAX_BYTES || defined __DOXYGEN__
#define TCP_OOSEQ_MAX_BYTES             0
#endif

/**
 * TCP_OOSEQ_BYTES_LIMIT（pcb）：返回给定pcb的每个pcb要在OOSEQ上排队的最大字节数。仅对TCP_QUEUE_OOSEQ==1和TCP_OOSEQ_MAX_BYTES==1有效。使用此选项可将TCP_OOSE_MAX_BYTES覆盖为每个pcb的动态值。
 */
#if !defined TCP_OOSEQ_BYTES_LIMIT
#if TCP_OOSEQ_MAX_BYTES
#define TCP_OOSEQ_BYTES_LIMIT(pcb)      TCP_OOSEQ_MAX_BYTES
#elif defined __DOXYGEN__
#define TCP_OOSEQ_BYTES_LIMIT(pcb)
#endif
#endif

/**
 * TCP_OOSEQ_MAX_PBUFS:如果未定义TCP_OOSSEQ_BYTES_LIMIT，则每个pcb在OOSEQ上排队的pbuf的默认最大数量。默认值为0（无限制）。仅对TCP_QUEUE_OOSEQ==1有效。
 */
#if !defined TCP_OOSEQ_MAX_PBUFS || defined __DOXYGEN__
#define TCP_OOSEQ_MAX_PBUFS             0
#endif

/**
 * TCP_OOSEQ_PBUFS_LIMIT（pcb）：返回给定pcb的每个pcb上要在OOSEQ上排队的pbuf的最大数量。仅对TCP_QUEUE_OOSEQ==1和TCP_OOSEQ_MAX_PBUFS==1有效。使用此选项可将TCP_OOSE_MAX_PBUFS覆盖为每个pcb的动态值。
 */
#if !defined TCP_OOSEQ_PBUFS_LIMIT
#if TCP_OOSEQ_MAX_PBUFS
#define TCP_OOSEQ_PBUFS_LIMIT(pcb)      TCP_OOSEQ_MAX_PBUFS
#elif defined __DOXYGEN__
#define TCP_OOSEQ_PBUFS_LIMIT(pcb)
#endif
#endif

/**
 * TCP_LISTEN_BACKLOG：为TCP侦听pcb启用BACKLOG选项。
 */
#if !defined TCP_LISTEN_BACKLOG || defined __DOXYGEN__
#define TCP_LISTEN_BACKLOG              0
#endif

/**
 * TCP侦听网络连接允许的最大积压。除非明确指定了另一个积压工作，否则将使用此积压工作。0xff是最大值（u8_t）。
 */
#if !defined TCP_DEFAULT_LISTEN_BACKLOG || defined __DOXYGEN__
#define TCP_DEFAULT_LISTEN_BACKLOG      0xff
#endif

/**
 * TCP_OVERSIZE：TCP_write可以提前分配的最大字节数，以尝试创建更短的pbuf链进行传输。有效范围为0至TCP_MSS。一些建议值如下：
 *
 * 0：禁用过大分配。每个tcp_write（）分配一个新的pbuf（旧行为）。1： 分配大小对齐的pbuf，并将多余量降至最低。如果分散收集DMA需要对齐碎片，请使用此选项。128:将pbuf/内存开销限制为20%。TCP_MSS:尝试创建未分段的TCP数据包。TCP_MSS/4：尝试为每个TCP数据包创建4个或更少的片段。
 */
#if !defined TCP_OVERSIZE || defined __DOXYGEN__
#define TCP_OVERSIZE                    TCP_MSS
#endif

/**
 * LWIP_TCP_TIMESTAMPS==1：支持TCP时间戳选项。timestamp选项当前仅用于帮助远程主机，而不是真正在本地使用。因此，只有在从远程主机接收到初始SYN数据包中的TS选项时，才启用该选项。
 */
#if !defined LWIP_TCP_TIMESTAMPS || defined __DOXYGEN__
#define LWIP_TCP_TIMESTAMPS             0
#endif

/**
 * TCP_WND_UPDATE_THRESHOLD：触发显式窗口更新的窗口差异
 */
#if !defined TCP_WND_UPDATE_THRESHOLD || defined __DOXYGEN__
#define TCP_WND_UPDATE_THRESHOLD        LWIP_MIN((TCP_WND / 4), (TCP_MSS * 4))
#endif

/**
 * LWIP_EVENT_API和LWIP_CALLBACK_API：其中只有一个应该设置为1。LWIP_EVENT_API==1：用户定义LWIP_tcp_EVENT（）以接收系统中发生的所有事件（接受、发送等）。LWIP_CALLBACK_API==1：直接为事件调用PCB回调函数。这是默认设置。
 */
#if !defined(LWIP_EVENT_API) && !defined(LWIP_CALLBACK_API) || defined __DOXYGEN__
#define LWIP_EVENT_API                  0
#define LWIP_CALLBACK_API               1
#else
#ifndef LWIP_EVENT_API
#define LWIP_EVENT_API                  0
#endif
#ifndef LWIP_CALLBACK_API
#define LWIP_CALLBACK_API               0
#endif
#endif

/**
 * LWIP_WND_SCALE和TCP_RCV_SCALE：将LWIP_WND _SCALE设置为1以启用窗口缩放。将TCP_RCV_SCALE设置为所需的缩放因子（移位计数在[0..14]范围内）。当启用LWIP_WND_SCALE但TCP_RCV_SCALE为0时，我们可以使用大的发送窗口，而只有小的接收窗口。
 */
#if !defined LWIP_WND_SCALE || defined __DOXYGEN__
#define LWIP_WND_SCALE                  0
#define TCP_RCV_SCALE                   0
#endif

/**
 * LWIP_TCP_PCB_NUM_EXT_ARGS：当该值>0时，每个TCP PCB（包括侦听PCB）都在数组中包含多个附加参数条目（请参见TCP_EXT_arg_alloc_id）
 */
#if !defined LWIP_TCP_PCB_NUM_EXT_ARGS || defined __DOXYGEN__
#define LWIP_TCP_PCB_NUM_EXT_ARGS       0
#endif

/** LWIP_ALTCP==1：启用ALTCP API。altcp是一个抽象层，它防止应用程序链接到tcp。h函数，但提供相同的功能。它用于例如向为tcp回调API编写的应用程序添加SSL/TLS或代理连接支持，而该应用程序不知道协议细节。
 *
 * 使用LWIP_ALTCP==0，针对ALTCP API编写的应用程序仍然可以编译，但直接链接到tcp.h回调API，因此不能使用分层协议。
 *
 * See @ref altcp_api
 */
#if !defined LWIP_ALTCP || defined __DOXYGEN__
#define LWIP_ALTCP                      0
#endif

/** LWIP_ALTCP_TLS==1：为ALTCP API启用TLS支持。这需要将altcp_tls.h中的函数端口连接到tls库。lwIP提供了到ARM mbedtls的端口，请参见apps/altcp_tls/目录和lwIP_altcp_tls_mbedtls选项。
 */
#if !defined LWIP_ALTCP_TLS || defined __DOXYGEN__
#define LWIP_ALTCP_TLS                  0
#endif

#if ESP_LWIP
#if !defined LWIP_TCP_RTO_TIME || defined __DOXYGEN__
#define LWIP_TCP_RTO_TIME             3000
#endif
#endif
/**
 * @}
 */

/*
   ----------------------------------
   ----------Pbuf选项----------
   ----------------------------------
*/
/**
 * @defgroup lwip_opts_pbuf pbuf
 * @ingroup lwip端口（_O）@{
 */
/**
 * PBUF_LINK_HLEN：应为链接级标头分配的字节数。默认值为14，这是以太网的标准值。
 */
#if !defined PBUF_LINK_HLEN || defined __DOXYGEN__
#if defined LWIP_HOOK_VLAN_SET && !defined __DOXYGEN__
#define PBUF_LINK_HLEN                  (18 + ETH_PAD_SIZE)
#else /* LWIP_HOOK_VLAN_SET */
#define PBUF_LINK_HLEN                  (14 + ETH_PAD_SIZE)
#endif /* LWIP_HOOK_VLAN_SET */
#endif

/**
 * PBUF_LINK_ENCAPSULATION_HLEN：应在以太网报头（例如802.11）之前为附加封装报头分配的字节数
 */
#if !defined PBUF_LINK_ENCAPSULATION_HLEN || defined __DOXYGEN__
#define PBUF_LINK_ENCAPSULATION_HLEN    0
#endif

/**
 * PBUF_POOL_BUFSIZE:PBUF池中每个PBUF的大小。默认设计为在一个pbuf中容纳单个完整大小的TCP帧，包括TCP_MSS、IP报头和链路报头。
 */
#if !defined PBUF_POOL_BUFSIZE || defined __DOXYGEN__
#define PBUF_POOL_BUFSIZE               LWIP_MEM_ALIGN_SIZE(TCP_MSS+40+PBUF_LINK_ENCAPSULATION_HLEN+PBUF_LINK_HLEN)
#endif

/**
 * LWIP_PBUF_REF_T：PBUF中的引用计数类型。如果255个引用对您来说不够，则可以增加u8_t的默认宽度。
 */
#if !defined LWIP_PBUF_REF_T || defined __DOXYGEN__
#define LWIP_PBUF_REF_T                 u8_t
#endif

/**
 * LWIP_PBUF_CUSTOM_DATA：在pbufs上存储私有数据（例如时间戳）这扩展了结构PBUF，因此用户可以在每个PBUF上存储自定义数据。
 */
#if !defined LWIP_PBUF_CUSTOM_DATA || defined __DOXYGEN__
#define LWIP_PBUF_CUSTOM_DATA
#endif
/**
 * @}
 */

/*
   ------------------------------------------------
   ----------网络接口选项----------
   ------------------------------------------------
*/
/**
 * @defgroup lwip_opts_netif网络IF
 * @ingroup lwip端口（_O）@{
 */
/**
 * LWIP_SINGLE_NETIF==1：仅使用单个NETIF。这是现实生活中小型目标的常见情况。可以省略一些代码，如路由等。
 */
#if !defined LWIP_SINGLE_NETIF || defined __DOXYGEN__
#define LWIP_SINGLE_NETIF               0
#endif

/**
 * LWIP_NETIF_HOSTNAME==1：将DHCP_OPTION_HOSTNNAME与NETIF的主机名字段一起使用。
 */
#if !defined LWIP_NETIF_HOSTNAME || defined __DOXYGEN__
#define LWIP_NETIF_HOSTNAME             0
#endif

/**
 * LWIP_NETIF_API==1：支持NETIF-API（在netifapi.c中）
 */
#if !defined LWIP_NETIF_API || defined __DOXYGEN__
#define LWIP_NETIF_API                  0
#endif

/**
 * LWIP_NETIF_STATUS_CALLBACK==1：每当接口更改其上/下状态时（即，由于DHCP IP获取），都支持回调函数
 */
#if !defined LWIP_NETIF_STATUS_CALLBACK || defined __DOXYGEN__
#define LWIP_NETIF_STATUS_CALLBACK      0
#endif

/**
 * LWIP_NETIF_EXT_STATUS_CALLBACK==1：支持支持多个订阅者的多个NETIF相关事件的扩展回调函数。
 * @see netif_ext_status_回调
 */
#if !defined LWIP_NETIF_EXT_STATUS_CALLBACK || defined __DOXYGEN__
#define LWIP_NETIF_EXT_STATUS_CALLBACK  0
#endif

/**
 * LWIP_NETIF_LINK_CALLBACK==1：每当链接更改（即链接关闭）时，都支持来自接口的回调函数
 */
#if !defined LWIP_NETIF_LINK_CALLBACK || defined __DOXYGEN__
#define LWIP_NETIF_LINK_CALLBACK        0
#endif

/**
 * LWIP_NETIF_REMOVE_CALLBACK==1：支持在删除NETIF时调用的回调函数
 */
#if !defined LWIP_NETIF_REMOVE_CALLBACK || defined __DOXYGEN__
#define LWIP_NETIF_REMOVE_CALLBACK      0
#endif

/**
 * LWIP_NETIF_WADDRHINT==1：结构NETIF中的缓存链接层地址提示（例如表索引）。TCP和UDP可以利用这一点来防止为每个发送的数据包扫描ARP表。虽然这对于大型ARP表或许多并发连接来说更快，但如果您有一个很小的ARP表或根本没有并发连接，则可能会适得其反。
 */
#if !defined LWIP_NETIF_HWADDRHINT || defined __DOXYGEN__
#define LWIP_NETIF_HWADDRHINT           0
#endif

/**
 * LWIP_NETIF_TX_SINGLE_BUF：如果设置为1，LWIP*将尝试*将所有要发送的数据放入一个PBUF中。这是为了与不支持分散聚集的启用DMA的MAC兼容。请注意，在传输之前，这可能涉及CPU内存，如果没有此标志，则不需要此内存！只有在需要时才使用此选项！
 *
 * ATTENTION: a driver should *NOT* rely on getting single pbufs but check TX pbufs for being in one piece. If not, @ref pbuf_clone可用于获取单个pbuf：if（p->next！=NULL）{structpbuf q=pbuf_cone（pbuf_RAW，pbuf_RAM，p）；if（q==NULL）{return ERR_MEM；}p=q；注意：不要释放旧的“p”，因为ref属于调用者！}
 */
#if !defined LWIP_NETIF_TX_SINGLE_PBUF || defined __DOXYGEN__
#define LWIP_NETIF_TX_SINGLE_PBUF       0
#endif /* LWIP_NETIF_TX_SINGLE_PBUF */

/**
 * LWIP_NUM_NETIF_CLIENT_DATA:可以在结构NETIF的CLIENT_DATA成员数组中存储数据的客户端数（最多256个）。
 */
#if !defined LWIP_NUM_NETIF_CLIENT_DATA || defined __DOXYGEN__
#define LWIP_NUM_NETIF_CLIENT_DATA      0
#endif
/**
 * @}
 */

/*
   ------------------------------------
   ----------LOOPIF选项----------
   ------------------------------------
*/
/**
 * @defgroup lwip_opts_loop环回接口
 * @ingroup lwip_opts_netif@{
 */
/**
 * LWIP_HAVE_LOOPIF==1：支持循环接口（127.0.0.1）。只有在没有可用的实际netif时才需要。如果至少有一个其他netif可用，环回流量将使用此netif。
 */
#if !defined LWIP_HAVE_LOOPIF || defined __DOXYGEN__
#define LWIP_HAVE_LOOPIF                (LWIP_NETIF_LOOPBACK && !LWIP_SINGLE_NETIF)
#endif

/**
 * LWIP_LOOPIF_MULTICAST==1：支持环路接口上的多播/IGMP（127.0.0.1）。
 */
#if !defined LWIP_LOOPIF_MULTICAST || defined __DOXYGEN__
#define LWIP_LOOPIF_MULTICAST           0
#endif

/**
 * LWIP_NETIF_LOPBACK==1：支持发送目标IP地址等于NETIF IP地址的数据包，并将其循环到堆栈中。
 */
#if !defined LWIP_NETIF_LOOPBACK || defined __DOXYGEN__
#define LWIP_NETIF_LOOPBACK             0
#endif

/**
 * LWIP_LOOPBACK_MAX_PBUFS：每个netif的环回发送队列中pbuf的最大数量（0=禁用）
 */
#if !defined LWIP_LOOPBACK_MAX_PBUFS || defined __DOXYGEN__
#define LWIP_LOOPBACK_MAX_PBUFS         0
#endif

/**
 * LWIP_NETIF_LOUPBACK_MULTITHREADING：指示是否在系统中启用线程，因为NETIF必须根据此设置更改其行为方式，LWIP_NOTIF_LOOPBACK选项才能工作。需要设置此项以避免重新输入不可重入的函数，如tcp_input（）。LWIP_NETIF_LOPBACK_MULTITTHREADING==1：表示用户正在使用多线程环境，如tcpip.c。在这种情况下，直接调用NETIF->input（）。LWIP_NETIF_LOPBACK_MULTITTHREADING==0：表示轮询（或NO_SYS）设置。数据包放在一个列表中，必须在主应用程序循环中调用netif_poll（）。
 */
#if !defined LWIP_NETIF_LOOPBACK_MULTITHREADING || defined __DOXYGEN__
#define LWIP_NETIF_LOOPBACK_MULTITHREADING    (!NO_SYS)
#endif
/**
 * @}
 */

/*
   ------------------------------------
   ----------线程选项----------
   ------------------------------------
*/
/**
 * @defgroup lwip_opts_thread线程
 * @ingroup lwip_opts基础设施@{
 */
/**
 * TCPIP_THREAD_NAME:分配给主TCPIP线程的名称。
 */
#if !defined TCPIP_THREAD_NAME || defined __DOXYGEN__
#define TCPIP_THREAD_NAME               "tcpip_thread"
#endif

/**
 * TCPIP_THREAD_STACKSIZE:主TCPIP线程使用的堆栈大小。堆栈大小值本身依赖于平台，但在创建线程时会传递给sys_thread_new（）。
 */
#if !defined TCPIP_THREAD_STACKSIZE || defined __DOXYGEN__
#define TCPIP_THREAD_STACKSIZE          0
#endif

/**
 * TCPIP_THREAD_PRIO：分配给主TCPIP线程的优先级。优先级值本身依赖于平台，但在创建线程时会传递给sys_thread_new（）。
 */
#if !defined TCPIP_THREAD_PRIO || defined __DOXYGEN__
#define TCPIP_THREAD_PRIO               1
#endif

/**
 * TCPIP_MBOX_SIZE:TCPIP线程消息的邮箱大小队列大小值本身取决于平台，但在调用TCPIP_init时传递给sys_MBOX_new（）。
 */
#if !defined TCPIP_MBOX_SIZE || defined __DOXYGEN__
#define TCPIP_MBOX_SIZE                 0
#endif

/**
 * 将其定义为触发看门狗的对象。这是在处理消息后从tcpip_thread调用的。
 */
#if !defined LWIP_TCPIP_THREAD_ALIVE || defined __DOXYGEN__
#define LWIP_TCPIP_THREAD_ALIVE()
#endif

/**
 * SLIPIF_TREAD_NAME：分配给SLIPIF_loop线程的名称。
 */
#if !defined SLIPIF_THREAD_NAME || defined __DOXYGEN__
#define SLIPIF_THREAD_NAME              "slipif_loop"
#endif

/**
 * SLIP_TREAD_STACKSIZE:slipif_lop线程使用的堆栈大小。堆栈大小值本身依赖于平台，但在创建线程时会传递给sys_thread_new（）。
 */
#if !defined SLIPIF_THREAD_STACKSIZE || defined __DOXYGEN__
#define SLIPIF_THREAD_STACKSIZE         0
#endif

/**
 * SLIPIF_TREAD_PRIO：分配给SLIPIF_loop线程的优先级。优先级值本身依赖于平台，但在创建线程时会传递给sys_thread_new（）。
 */
#if !defined SLIPIF_THREAD_PRIO || defined __DOXYGEN__
#define SLIPIF_THREAD_PRIO              1
#endif

/**
 * DEFAULT_THREAD_NAME:分配给任何其他lwIP线程的名称。
 */
#if !defined DEFAULT_THREAD_NAME || defined __DOXYGEN__
#define DEFAULT_THREAD_NAME             "lwIP"
#endif

/**
 * DEFAULT_THREAD_STACKSIZE：任何其他lwIP线程使用的堆栈大小。堆栈大小值本身依赖于平台，但在创建线程时会传递给sys_thread_new（）。
 */
#if !defined DEFAULT_THREAD_STACKSIZE || defined __DOXYGEN__
#define DEFAULT_THREAD_STACKSIZE        0
#endif

/**
 * DEFAULT_THREAD_PRIO：分配给任何其他lwIP线程的优先级。优先级值本身依赖于平台，但在创建线程时会传递给sys_thread_new（）。
 */
#if !defined DEFAULT_THREAD_PRIO || defined __DOXYGEN__
#define DEFAULT_THREAD_PRIO             1
#endif

/**
 * DEFAULT_RAW_RECVMBOX_SIZE:NETCONN_RAW上传入数据包的邮箱大小。队列大小值本身依赖于平台，但在创建recvmbox时会传递给sys_mbox_new（）。
 */
#if !defined DEFAULT_RAW_RECVMBOX_SIZE || defined __DOXYGEN__
#define DEFAULT_RAW_RECVMBOX_SIZE       0
#endif

/**
 * DEFAULT_UDP_RECVMBOX_SIZE:NETCONN_UDP上传入数据包的邮箱大小。队列大小值本身依赖于平台，但在创建recvmbox时会传递给sys_mbox_new（）。
 */
#if !defined DEFAULT_UDP_RECVMBOX_SIZE || defined __DOXYGEN__
#define DEFAULT_UDP_RECVMBOX_SIZE       0
#endif

/**
 * DEFAULT_TCP_RECVMBOX_SIZE:NETCONN_TCP上传入数据包的邮箱大小。队列大小值本身依赖于平台，但在创建recvmbox时会传递给sys_mbox_new（）。
 */
#if !defined DEFAULT_TCP_RECVMBOX_SIZE || defined __DOXYGEN__
#define DEFAULT_TCP_RECVMBOX_SIZE       0
#endif

/**
 * DEFAULT_ACCEPTMBOX_SIZE：传入连接的邮箱大小。队列大小值本身依赖于平台，但在创建acceptbox时传递给sys_mbox_new（）。
 */
#if !defined DEFAULT_ACCEPTMBOX_SIZE || defined __DOXYGEN__
#define DEFAULT_ACCEPTMBOX_SIZE         0
#endif
/**
 * @}
 */

/*
   ----------------------------------------------
   ----------顺序层选项----------
   ----------------------------------------------
*/
/**
 * @defgroup lwip_opts_netconn网络连接
 * @ingroup lwip_opts_threadsafe_api@{
 */
/**
 * LWIP_NETCONN==1：启用NETCONN API（需要使用API_lib.c）
 */
#if !defined LWIP_NETCONN || defined __DOXYGEN__
#define LWIP_NETCONN                    1
#endif

/** LWIP_TCPIP_TIMEOUT==1：启用TCPIP_TIMEOUT/TCPIP_untimeout以从另一个线程创建在TCPIP_thread中运行的计时器。
 */
#if !defined LWIP_TCPIP_TIMEOUT || defined __DOXYGEN__
#define LWIP_TCPIP_TIMEOUT              0
#endif

/** LWIP_NETCONN_SEM_PER_THREAD==1：调用套接字/NETCONN函数的每个线程使用一个（线程本地）信号量，而不是为每个NETCONN（以及每个select等）分配一个信号量注意：API调用需要一个线程本地信号量：
 * -LWIP_NETCONN_THREAD_SEM_GET（）返回sys_SEM_t*
 * -LWIP_NETCONN_THREAD_SEM_ALLOC（）创建信号量
 * -LWIP_NETCONN_THREAD_SEM_FREE（）释放信号量后2个可以通过调用NETCONN_THREAD_init（）/NETCONN_THREAD _cleanup（）调用。端口可以为使用sys_thread_new（）创建的线程调用这些函数。
 */
#if !defined LWIP_NETCONN_SEM_PER_THREAD || defined __DOXYGEN__
#define LWIP_NETCONN_SEM_PER_THREAD     0
#endif

/** LWIP_NETCONN_FULLDUPLEX==1：启用代码，允许同时从一个线程读取、从第二个线程写入和从第三个线程关闭。注意：这是目前真正的阿尔法！一些要求：
 * -LWIP_NETCONN_SEM_PER_THREAD==1需要同时从多个线程使用一个套接字/NETCONN
 * -sys_mbox_free（）必须取消阻止在recvmbox/acceptmbox上等待的接收任务，并防止在删除过程中/删除后在此上挂起任务
 */
#if !defined LWIP_NETCONN_FULLDUPLEX || defined __DOXYGEN__
#define LWIP_NETCONN_FULLDUPLEX         0
#endif
/**
 * @}
 */

/*
   ------------------------------------
   ----------套接字选项----------
   ------------------------------------
*/
/**
 * @defgroup lwip_opts_socket套接字
 * @ingroup lwip_opts_threadsafe_api@{
 */
/**
 * LWIP_SOCKET==1：启用套接字API（需要使用套接字.c）
 */
#if !defined LWIP_SOCKET || defined __DOXYGEN__
#define LWIP_SOCKET                     1
#endif

/**
 * LWIP_COMPAT_SOCKETS==1：通过定义启用BSD风格的套接字函数名称。LWIP_COMPAT_SOCKETS==2：与==1相同，但创建了正确命名的函数。虽然这有助于完成代码，但它可能与现有库冲突。（仅在使用套接字.c时使用）
 */
#if !defined LWIP_COMPAT_SOCKETS || defined __DOXYGEN__
#define LWIP_COMPAT_SOCKETS             1
#endif

/**
 * LWIP_POSIX_SOCKETS_IO_NAMES==1:启用POSIX样式的套接字函数名称。如果使用使用相同名称（读、写和关闭）的POSIX操作系统，请禁用此选项。（仅在使用套接字.c时使用）
 */
#if !defined LWIP_POSIX_SOCKETS_IO_NAMES || defined __DOXYGEN__
#define LWIP_POSIX_SOCKETS_IO_NAMES     1
#endif

/**
 * LWIP_SOCKET_OFFSET==n：用n增加LWIP创建的文件描述符数。当有多个API创建文件描述符时，这可能很有用。当它们都以不同的偏移量开始，并且您不会使它们重叠时，您可以重新实现read/write/close/ioctl/fnctl，以将请求的操作发送到正确的库（尽管共享选择需要更多的工作）。
 */
#if !defined LWIP_SOCKET_OFFSET || defined __DOXYGEN__
#define LWIP_SOCKET_OFFSET              0
#endif

/**
 * LWIP_TCP_KEEPALIVE==1：启用TCP_KEEPIDLE、TCP_KEPEINTVL和TCP_KEEP选项处理。请注意，TCP_KEEPIDLE和TCP_KEPEINTVL必须以秒为单位设置。（不需要套接字.c，并且会影响tcp.c）
 */
#if !defined LWIP_TCP_KEEPALIVE || defined __DOXYGEN__
#define LWIP_TCP_KEEPALIVE              0
#endif

/**
 * LWIP_SO_SNDTIMEO==1：为套接字/网络连接和SO_SNDTIMEO处理启用发送超时。
 */
#if !defined LWIP_SO_SNDTIMEO || defined __DOXYGEN__
#define LWIP_SO_SNDTIMEO                0
#endif

/**
 * LWIP_SO_RCVTIMEO==1：为套接字/网络连接和SO_RCVTIMEO处理启用接收超时。
 */
#if !defined LWIP_SO_RCVTIMEO || defined __DOXYGEN__
#define LWIP_SO_RCVTIMEO                0
#endif

/**
 * LWIP_SO_SNDRCVTIMEO_NONSDARD==1:SO_RCVTIMEO/SO_SNDTIMEO使用int（毫秒，非常类似于winsock）而不是结构timeval（默认值）。
 */
#if !defined LWIP_SO_SNDRCVTIMEO_NONSTANDARD || defined __DOXYGEN__
#define LWIP_SO_SNDRCVTIMEO_NONSTANDARD 0
#endif

/**
 * LWIP_SO_RCVBUF==1：启用SO_RCVBUF处理。
 */
#if !defined LWIP_SO_RCVBUF || defined __DOXYGEN__
#define LWIP_SO_RCVBUF                  0
#endif

/**
 * LWIP_SO_LINGER==1：启用SO_LINGER处理。
 */
#if !defined LWIP_SO_LINGER || defined __DOXYGEN__
#define LWIP_SO_LINGER                  0
#endif

/**
 * 如果使用LWIP_SO_RCVBUF，则这是recv_bufsize的默认值。
 */
#if !defined RECV_BUFSIZE_DEFAULT || defined __DOXYGEN__
#define RECV_BUFSIZE_DEFAULT            INT_MAX
#endif

/**
 * 默认情况下，TCP套接字/netconn关闭最多等待20秒以发送FIN
 */
#if !defined LWIP_TCP_CLOSE_TIMEOUT_MS_DEFAULT || defined __DOXYGEN__
#define LWIP_TCP_CLOSE_TIMEOUT_MS_DEFAULT 20000
#endif

/**
 * SO_REUSE==1：启用SO_REUSEADDR选项。
 */
#if !defined SO_REUSE || defined __DOXYGEN__
#define SO_REUSE                        0
#endif

/**
 * SO_REUSE_RXTOALL==1：如果打开了SO_REUSEADDR，则将传入广播/多播数据包的副本传递给所有本地匹配。警告：如果传递到多个pcb，则为每个数据包添加一个memcpy！
 */
#if !defined SO_REUSE_RXTOALL || defined __DOXYGEN__
#define SO_REUSE_RXTOALL                0
#endif

/**
 * LWIP_FIONREAD_LINUXMODE==0（默认值）：ioctl/FIONREAD返回网络缓冲区中挂起的数据量。这是windows的做法。这是lwIP的默认值，因为它较小。LWIP_FIONREAD_LINUXMODE==1:ioctl/FIONREAD返回下一个挂起数据报的大小（字节）。linux就是这样做的。此代码仅用于兼容性。
 */
#if !defined LWIP_FIONREAD_LINUXMODE || defined __DOXYGEN__
#define LWIP_FIONREAD_LINUXMODE         0
#endif

/**
 * LWIP_SOCKET_SELECT==1（默认）：为套接字启用SELECT（）（使用netconn回调来跟踪事件）。这节省了RAM（每个套接字的计数器）和代码（netconn事件回调），这会稍微提高性能）。
 */
#if !defined LWIP_SOCKET_SELECT || defined __DOXYGEN__
#define LWIP_SOCKET_SELECT              1
#endif

/**
 * LWIP_SOCKET_POLL==1（默认）：为套接字（包括结构pollfd、nfds_t和常量）启用POLL（）
 */
#if !defined LWIP_SOCKET_POLL || defined __DOXYGEN__
#define LWIP_SOCKET_POLL                1
#endif
/**
 * @}
 */

/*
   ----------------------------------------
   ----------统计信息选项----------
   ----------------------------------------
*/
/**
 * @defgroup lwip_opts_stats统计信息
 * @ingroup lwip_opts_debug@{
 */
/**
 * LWIP_STATS==1:在LWIP_STATS中启用统计信息收集。
 */
#if !defined LWIP_STATS || defined __DOXYGEN__
#define LWIP_STATS                      1
#endif

#if LWIP_STATS

/**
 * LWIP_STATS_DISPLAY==1：在统计输出函数中编译。
 */
#if !defined LWIP_STATS_DISPLAY || defined __DOXYGEN__
#define LWIP_STATS_DISPLAY              0
#endif

/**
 * LINK_STATS==1：启用链接状态。
 */
#if !defined LINK_STATS || defined __DOXYGEN__
#define LINK_STATS                      1
#endif

/**
 * ETHARP_STATS==1：启用ETHARP统计信息。
 */
#if !defined ETHARP_STATS || defined __DOXYGEN__
#define ETHARP_STATS                    (LWIP_ARP)
#endif

/**
 * IP_STATS==1：启用IP统计信息。
 */
#if !defined IP_STATS || defined __DOXYGEN__
#define IP_STATS                        1
#endif

/**
 * IPFRAG_STATS==1：启用IP碎片统计信息。如果使用frag或reass，则默认为启用。
 */
#if !defined IPFRAG_STATS || defined __DOXYGEN__
#define IPFRAG_STATS                    (IP_REASSEMBLY || IP_FRAG)
#endif

/**
 * ICMP_STATS==1：启用ICMP统计信息。
 */
#if !defined ICMP_STATS || defined __DOXYGEN__
#define ICMP_STATS                      1
#endif

/**
 * IGMP_STATS==1：启用IGMP统计信息。
 */
#if !defined IGMP_STATS || defined __DOXYGEN__
#define IGMP_STATS                      (LWIP_IGMP)
#endif

/**
 * UDP_STATS==1：启用UDP统计信息。如果启用UDP，则默认值为启用，否则为禁用。
 */
#if !defined UDP_STATS || defined __DOXYGEN__
#define UDP_STATS                       (LWIP_UDP)
#endif

/**
 * TCP_STATS==1：启用TCP统计信息。如果启用了TCP，则默认值为启用，否则为禁用。
 */
#if !defined TCP_STATS || defined __DOXYGEN__
#define TCP_STATS                       (LWIP_TCP)
#endif

/**
 * MEM_STATS==1：启用MEM。c统计数据。
 */
#if !defined MEM_STATS || defined __DOXYGEN__
#define MEM_STATS                       ((MEM_LIBC_MALLOC == 0) && (MEM_USE_POOLS == 0))
#endif

/**
 * MEMP_STATS==1：启用MEMP。c池统计。
 */
#if !defined MEMP_STATS || defined __DOXYGEN__
#define MEMP_STATS                      (MEMP_MEM_MALLOC == 0)
#endif

/**
 * SYS_STATS==1：启用系统统计信息（sem和mbox计数等）。
 */
#if !defined SYS_STATS || defined __DOXYGEN__
#define SYS_STATS                       (NO_SYS == 0)
#endif

/**
 * IP6_STATS==1:启用IPv6状态。
 */
#if !defined IP6_STATS || defined __DOXYGEN__
#define IP6_STATS                       (LWIP_IPV6)
#endif

/**
 * ICMP6_STATS==1:为IPv6统计信息启用ICMP。
 */
#if !defined ICMP6_STATS || defined __DOXYGEN__
#define ICMP6_STATS                     (LWIP_IPV6 && LWIP_ICMP6)
#endif

/**
 * IP6_FRAG_STATS==1：启用IPv6碎片状态。
 */
#if !defined IP6_FRAG_STATS || defined __DOXYGEN__
#define IP6_FRAG_STATS                  (LWIP_IPV6 && (LWIP_IPV6_FRAG || LWIP_IPV6_REASS))
#endif

/**
 * MLD6_STATS==1:为IPv6统计信息启用MLD。
 */
#if !defined MLD6_STATS || defined __DOXYGEN__
#define MLD6_STATS                      (LWIP_IPV6 && LWIP_IPV6_MLD)
#endif

/**
 * ND6_STATS==1：为IPv6统计信息启用邻居发现。
 */
#if !defined ND6_STATS || defined __DOXYGEN__
#define ND6_STATS                       (LWIP_IPV6)
#endif

/**
 * MIB2_STATS==1:SNMP MIB2的统计信息。
 */
#if !defined MIB2_STATS || defined __DOXYGEN__
#define MIB2_STATS                      0
#endif

#else

#define LINK_STATS                      0
#define ETHARP_STATS                    0
#define IP_STATS                        0
#define IPFRAG_STATS                    0
#define ICMP_STATS                      0
#define IGMP_STATS                      0
#define UDP_STATS                       0
#define TCP_STATS                       0
#define MEM_STATS                       0
#define MEMP_STATS                      0
#define SYS_STATS                       0
#define LWIP_STATS_DISPLAY              0
#define IP6_STATS                       0
#define ICMP6_STATS                     0
#define IP6_FRAG_STATS                  0
#define MLD6_STATS                      0
#define ND6_STATS                       0
#define MIB2_STATS                      0

#endif /* LWIP_STATS */
/**
 * @}
 */

/*
   --------------------------------------
   ----------校验和选项----------
   --------------------------------------
*/
/**
 * @defgroup lwip_opts_checksum校验和
 * @ingroup lwip_opts基础设施@{
 */
/**
 * LWIP_CHECKSUM_CTRL_PER_NETIF==1：可以根据NETIF启用/禁用校验和生成/检查。注意：如果启用，则必须启用CHECKSUM_GEN_和CHECKSUM_CHECK_定义！
 */
#if !defined LWIP_CHECKSUM_CTRL_PER_NETIF || defined __DOXYGEN__
#define LWIP_CHECKSUM_CTRL_PER_NETIF    0
#endif

/**
 * CHECKSUM_GEN_IP==1：在软件中为传出的IP数据包生成校验和。
 */
#if !defined CHECKSUM_GEN_IP || defined __DOXYGEN__
#define CHECKSUM_GEN_IP                 1
#endif

/**
 * CHECKSUM_GEN_UDP==1：在软件中为传出UDP数据包生成校验和。
 */
#if !defined CHECKSUM_GEN_UDP || defined __DOXYGEN__
#define CHECKSUM_GEN_UDP                1
#endif

/**
 * CHECKSUM_GEN_TCP==1：在软件中为传出的TCP数据包生成校验和。
 */
#if !defined CHECKSUM_GEN_TCP || defined __DOXYGEN__
#define CHECKSUM_GEN_TCP                1
#endif

/**
 * CHECKSUM_GEN_ICMP==1：在软件中为传出ICMP数据包生成校验和。
 */
#if !defined CHECKSUM_GEN_ICMP || defined __DOXYGEN__
#define CHECKSUM_GEN_ICMP               1
#endif

/**
 * CHECKSUM_GEN_ICMP6==1：在软件中为传出ICMP6数据包生成校验和。
 */
#if !defined CHECKSUM_GEN_ICMP6 || defined __DOXYGEN__
#define CHECKSUM_GEN_ICMP6              1
#endif

/**
 * CHECKSUM_CHECK_IP==1：检查软件中传入IP数据包的校验和。
 */
#if !defined CHECKSUM_CHECK_IP || defined __DOXYGEN__
#define CHECKSUM_CHECK_IP               1
#endif

/**
 * CHECKSUM_CHECK_UDP==1：检查软件中传入UDP数据包的校验和。
 */
#if !defined CHECKSUM_CHECK_UDP || defined __DOXYGEN__
#define CHECKSUM_CHECK_UDP              1
#endif

/**
 * CHECKSUM_CHECK_TCP==1：检查软件中传入TCP数据包的校验和。
 */
#if !defined CHECKSUM_CHECK_TCP || defined __DOXYGEN__
#define CHECKSUM_CHECK_TCP              1
#endif

/**
 * CHECKSUM_CHECK_ICMP==1：检查软件中传入ICMP数据包的校验和。
 */
#if !defined CHECKSUM_CHECK_ICMP || defined __DOXYGEN__
#define CHECKSUM_CHECK_ICMP             1
#endif

/**
 * CHECKSUM_CHECK_ICMP6==1：检查软件中传入ICMPv6数据包的校验和
 */
#if !defined CHECKSUM_CHECK_ICMP6 || defined __DOXYGEN__
#define CHECKSUM_CHECK_ICMP6            1
#endif

/**
 * LWIP_CHECKSUM_ON_COPY==1：将数据从应用程序缓冲区复制到pbufs时计算校验和。
 */
#if !defined LWIP_CHECKSUM_ON_COPY || defined __DOXYGEN__
#define LWIP_CHECKSUM_ON_COPY           0
#endif
/**
 * @}
 */

/*
   ---------------------------------------
   ----------IPv6选项---------------
   ---------------------------------------
*/
/**
 * @defgroup lwip_opts_ipv6 ipv6
 * @ingroup lwip端口（_O）@{
 */
/**
 * LWIP_IPV6==1:启用IPV6
 */
#if !defined LWIP_IPV6 || defined __DOXYGEN__
#define LWIP_IPV6                       0
#endif

/**
 * IPV6_REASS_MAXAGE：碎片IP数据包等待所有碎片到达的最长时间（通常为IP6_REASS_TMR_INTERVAL的倍数，通常为秒）。如果此时不是所有碎片都到达，则丢弃整个数据包。
 */
#if !defined IPV6_REASS_MAXAGE || defined __DOXYGEN__
#define IPV6_REASS_MAXAGE               60
#endif

/**
 * LWIP_IPV6_SCOPES==1：启用对IPV6地址范围的支持，确保例如链路本地地址确实被视为链路本地地址。仅对单个接口配置禁用此设置。根据默认策略具有作用域的所有地址（链路本地单播地址、接口本地和链路本地多播地址）现在都应该在传递到核心API之前在其上设置一个区域，尽管lwIP当前将在必要时尝试代表调用方选择一个区域。直接将IPv6地址分配给接口的应用程序（不建议使用）现在必须确保链接本地地址携带netif的区域。请参见新的ip6_zone。h头文件以获取更多信息和相关宏。目前，仍然可以通过新的LWIP_IPV6_COPES选项关闭范围支持。当升级直接使用核心API的实现时，强烈建议至少启用LWIP_IPV6_SCOPES_DEBUG一段时间，以确保正确的地址初始化。
 */
#if !defined LWIP_IPV6_SCOPES || defined __DOXYGEN__
#define LWIP_IPV6_SCOPES                (LWIP_IPV6 && !LWIP_SINGLE_NETIF)
#endif

/**
 * LWIP_IPV6_SCOPES_DEBUG==1：执行运行时检查，以验证地址是否正确分区（请参阅ip6_zone.h了解这意味着什么）。在从尚未了解范围的现有安装升级时，强烈建议启用此设置；否则可能太贵。
 */
#if !defined LWIP_IPV6_SCOPES_DEBUG || defined __DOXYGEN__
#define LWIP_IPV6_SCOPES_DEBUG          0
#endif

/**
 * LWIP_IPV6_NUM_ADDRESSES：每个网络的IPV6地址数。
 */
#if !defined LWIP_IPV6_NUM_ADDRESSES || defined __DOXYGEN__
#define LWIP_IPV6_NUM_ADDRESSES         3
#endif

/**
 * LWIP_IPV6_FORWARD==1：跨netifs转发IPV6数据包
 */
#if !defined LWIP_IPV6_FORWARD || defined __DOXYGEN__
#define LWIP_IPV6_FORWARD               0
#endif

/**
 * LWIP_IPV6_FRAG==1：分段太大的传出IPV6数据包。
 */
#if !defined LWIP_IPV6_FRAG || defined __DOXYGEN__
#define LWIP_IPV6_FRAG                  1
#endif

/**
 * LWIP_IPV6_REASS==1：重新组装已碎片化的传入IPV6数据包
 */
#if !defined LWIP_IPV6_REASS || defined __DOXYGEN__
#define LWIP_IPV6_REASS                 LWIP_IPV6
#endif

/**
 * LWIP_IPV6_SEND_ROUTER_SOLICIT==1：在网络启动期间发送路由器请求消息。
 */
#if !defined LWIP_IPV6_SEND_ROUTER_SOLICIT || defined __DOXYGEN__
#define LWIP_IPV6_SEND_ROUTER_SOLICIT   1
#endif

/**
 * LWIP_IPV6_AUTOCONFIG==1：根据RFC 4862启用无状态地址自动配置。
 */
#if !defined LWIP_IPV6_AUTOCONFIG || defined __DOXYGEN__
#define LWIP_IPV6_AUTOCONFIG            LWIP_IPV6
#endif

/**
 * LWIP_IPV6_ADDRESS_FETIMES==1：保持每个IPV6地址的有效和首选生存期。LWIP_IPV6_AUTOCONFIG需要。否则仍可以启用，在这种情况下，应用程序可以使用适当的宏分配地址生存期。假设没有生存期的地址是静态的。如果禁用此选项，则假定所有地址都是静态的。
 */
#if !defined LWIP_IPV6_ADDRESS_LIFETIMES || defined __DOXYGEN__
#define LWIP_IPV6_ADDRESS_LIFETIMES     LWIP_IPV6_AUTOCONFIG
#endif

/**
 * LWIP_IPV6_DUP_DETECT_ATTEMPTS=[0..7]：重复地址检测尝试次数。
 */
#if !defined LWIP_IPV6_DUP_DETECT_ATTEMPTS || defined __DOXYGEN__
#define LWIP_IPV6_DUP_DETECT_ATTEMPTS   1
#endif
/**
 * @}
 */

/**
 * @defgroup lwip_opts_icmp6 icmp6
 * @ingroup lwip_opts_ipv6@{
 */
/**
 * LWIP_ICMP6==1：启用ICMPv6（每个RFC强制）
 */
#if !defined LWIP_ICMP6 || defined __DOXYGEN__
#define LWIP_ICMP6                      LWIP_IPV6
#endif

/**
 * LWIP_ICMP6_DATASIZE：ICMPv6错误消息中要发送回的原始数据包的字节数。
 */
#if !defined LWIP_ICMP6_DATASIZE || defined __DOXYGEN__
#define LWIP_ICMP6_DATASIZE             8
#endif

/**
 * LWIP_ICMP6_HL：ICMPv6消息的默认跃点限制
 */
#if !defined LWIP_ICMP6_HL || defined __DOXYGEN__
#define LWIP_ICMP6_HL                   255
#endif
/**
 * @}
 */

/**
 * @defgroup lwip_opts_mld6多播侦听器发现
 * @ingroup lwip_opts_ipv6@{
 */
/**
 * LWIP_IPV6_MLD==1：启用多播侦听器发现协议。如果启用了LWIP_IPV6，但禁用了此设置，则MAC层必须无差别地将所有入站IPV6多播流量传递给LWIP。
 */
#if !defined LWIP_IPV6_MLD || defined __DOXYGEN__
#define LWIP_IPV6_MLD                   LWIP_IPV6
#endif

/**
 * MEMP_NUM_MLD6_GROUP：可以加入的IPv6多播组的最大数量。必须有足够的组，以便每个netif可以为其每个本地地址加入请求的节点多播组，如果适用，还可以为MDNS加入一个组，再加上UDP套接字上要加入的任意数量的组。
 */
#if !defined MEMP_NUM_MLD6_GROUP || defined __DOXYGEN__
#define MEMP_NUM_MLD6_GROUP             4
#endif
/**
 * @}
 */

/**
 * @defgroup lwip_opts_nd6邻居发现
 * @ingroup lwip_opts_ipv6@{
 */
/**
 * LWIP_ND6_QUEUEING==1：解析MAC地址时，将传出的IPv6数据包排入队列。
 */
#if !defined LWIP_ND6_QUEUEING || defined __DOXYGEN__
#define LWIP_ND6_QUEUEING               LWIP_IPV6
#endif

/**
 * ESP_ND6_QUEUEING==1：解析MAC地址时，将传出的IPv6数据包排队。
 */
#if !defined ESP_ND6_QUEUEING || defined __DOXYGEN__
#define ESP_ND6_QUEUEING               LWIP_IPV6
#endif

/**
 * MEMP_NUM_ND6_QUEUE:MAC解析期间要排队的IPv6数据包的最大数量。
 */
#if !defined MEMP_NUM_ND6_QUEUE || defined __DOXYGEN__
#define MEMP_NUM_ND6_QUEUE              20
#endif

/**
 * LWIP_ND6_NUM_NEIGHBORS:IPv6邻居缓存中的条目数
 */
#if !defined LWIP_ND6_NUM_NEIGHBORS || defined __DOXYGEN__
#define LWIP_ND6_NUM_NEIGHBORS          10
#endif

/**
 * LWIP_ND6_NUM_DESTINATIONS：IPv6目标缓存中的条目数
 */
#if !defined LWIP_ND6_NUM_DESTINATIONS || defined __DOXYGEN__
#define LWIP_ND6_NUM_DESTINATIONS       10
#endif

/**
 * LWIP_ND6_NUM_PREFIXES:IPv6链接前缀缓存中的条目数
 */
#if !defined LWIP_ND6_NUM_PREFIXES || defined __DOXYGEN__
#define LWIP_ND6_NUM_PREFIXES           5
#endif

/**
 * LWIP_ND6_NUM_ROUTERS:IPv6默认路由器缓存中的条目数
 */
#if !defined LWIP_ND6_NUM_ROUTERS || defined __DOXYGEN__
#define LWIP_ND6_NUM_ROUTERS            3
#endif

/**
 * LWIP_ND6_MAX_MULTICAST_SOLICIT:要发送的多播请求消息的最大数量（邻居请求和路由器请求）
 */
#if !defined LWIP_ND6_MAX_MULTICAST_SOLICIT || defined __DOXYGEN__
#define LWIP_ND6_MAX_MULTICAST_SOLICIT  3
#endif

/**
 * LWIP_ND6_MAX_UNICAST_SOLICIT:在邻居可达性检测期间要发送的单播邻居请求消息的最大数量。
 */
#if !defined LWIP_ND6_MAX_UNICAST_SOLICIT || defined __DOXYGEN__
#define LWIP_ND6_MAX_UNICAST_SOLICIT    3
#endif

/**
 * 未使用：请参阅ND RFC（以毫秒为单位的时间）。
 */
#if !defined LWIP_ND6_MAX_ANYCAST_DELAY_TIME || defined __DOXYGEN__
#define LWIP_ND6_MAX_ANYCAST_DELAY_TIME 1000
#endif

/**
 * 未使用：请参阅ND RFC
 */
#if !defined LWIP_ND6_MAX_NEIGHBOR_ADVERTISEMENT || defined __DOXYGEN__
#define LWIP_ND6_MAX_NEIGHBOR_ADVERTISEMENT  3
#endif

/**
 * LWIP_ND6_REACHABLE_TIME：默认邻居可达时间（毫秒）。可以通过路由器广告消息进行更新。
 */
#if !defined LWIP_ND6_REACHABLE_TIME || defined __DOXYGEN__
#define LWIP_ND6_REACHABLE_TIME         30000
#endif

/**
 * LWIP_ND6_RETRANS_TIMER：请求消息的默认重传计时器
 */
#if !defined LWIP_ND6_RETRANS_TIMER || defined __DOXYGEN__
#define LWIP_ND6_RETRANS_TIMER          1000
#endif

/**
 * LWIP_ND6_DELAY_FIRST_PROBE_TIME：在邻居可达性检测期间，发送第一个单播邻居请求消息之前的延迟。
 */
#if !defined LWIP_ND6_DELAY_FIRST_PROBE_TIME || defined __DOXYGEN__
#define LWIP_ND6_DELAY_FIRST_PROBE_TIME 5000
#endif

/**
 * LWIP_ND6_ALLOW_RA_UPDATES==1：允许路由器通告消息更新可到达时间和重传计时器以及netif MTU。
 */
#if !defined LWIP_ND6_ALLOW_RA_UPDATES || defined __DOXYGEN__
#define LWIP_ND6_ALLOW_RA_UPDATES       1
#endif

/**
 * LWIP_ND6_TCP_REACHABILITY_HINTS==1：允许TCP为邻居发现提供连接目标的可达性提示。这有助于避免发送单播邻居请求消息。
 */
#if !defined LWIP_ND6_TCP_REACHABILITY_HINTS || defined __DOXYGEN__
#define LWIP_ND6_TCP_REACHABILITY_HINTS 1
#endif

/**
 * LWIP_ND6_RDNSS_MAX_DNS_SERVERS>0:使用IPv6路由器通告递归DNS服务器选项（根据RFC 6106）将定义的最大DNS服务器数量复制到DNS模块。
 */
#if !defined LWIP_ND6_RDNSS_MAX_DNS_SERVERS || defined __DOXYGEN__
#define LWIP_ND6_RDNSS_MAX_DNS_SERVERS  0
#endif
/**
 * @}
 */

/**
 * @defgroup lwip_opts_dhcpv6 dhcpv6
 * @ingroup lwip_opts_ipv6@{
 */
/**
 * LWIP_IPV6_DHCP6==1：启用DHCPv6有状态/无状态地址自动配置。
 */
#if !defined LWIP_IPV6_DHCP6 || defined __DOXYGEN__
#define LWIP_IPV6_DHCP6                 0
#endif

/**
 * LWIP_IPV6_DHCP6_STATEFUL==1：启用DHCPv6有状态地址自动配置。（尚不支持！）
 */
#if !defined LWIP_IPV6_DHCP6_STATEFUL || defined __DOXYGEN__
#define LWIP_IPV6_DHCP6_STATEFUL        0
#endif

/**
 * LWIP_IPV6_DHCP6_STATELESS==1：启用DHCPv6无状态地址自动配置。
 */
#if !defined LWIP_IPV6_DHCP6_STATELESS || defined __DOXYGEN__
#define LWIP_IPV6_DHCP6_STATELESS       LWIP_IPV6_DHCP6
#endif

/**
 * LWIP_DHCP6_GETS_NTP==1：通过DHCPv6请求NTP服务器。对于每个响应包，都会调用一个回调，该回调必须由端口提供：void DHCP6_set_NTP_servers（u8_t num_NTP_server，ip_addr_t NTP_server_addrs）；
*/
#if !defined LWIP_DHCP6_GET_NTP_SRV || defined __DOXYGEN__
#define LWIP_DHCP6_GET_NTP_SRV          0
#endif

/**
 * 请求的NTP服务器的最大数量
 */
#if !defined LWIP_DHCP6_MAX_NTP_SERVERS || defined __DOXYGEN__
#define LWIP_DHCP6_MAX_NTP_SERVERS      1
#endif

/**
 * LWIP_DHCP6_MAX_DNS_SERVERS>0:通过DHCPv6请求DNS服务器。响应中接收的DNS服务器通过@ref DNS_setserver（）传递到DNS（达到此处定义的最大限制）。
 */
#if !defined LWIP_DHCP6_MAX_DNS_SERVERS || defined __DOXYGEN__
#define LWIP_DHCP6_MAX_DNS_SERVERS      DNS_MAX_SERVERS
#endif
/**
 * @}
 */

/*
   ---------------------------------------
   ----------挂钩选项---------------
   ---------------------------------------
*/

/**
 * @defgroup lwip_opts_hooks挂钩
 * @ingroup lwip_opts_infrastructure钩子默认未定义，如果需要，请将其定义为函数@{
 */

/**
 * LWIP_HOOK_FILENAME：要在提供挂钩的文件中包含的自定义文件名。在那里声明你的钩子函数原型，你也可以包含所有提供这个文件中需要的数据类型的头。
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_FILENAME "path/to/my/lwip_hooks.h"
#endif

/**
 * LWIP_HOOK_TCP_ISN：用于生成新TCP连接的初始序列号（ISN）的钩子。默认的lwIP ISN生成算法非常基本，可能允许TCP欺骗攻击。该钩子提供了实现RFC 6528标准化ISN生成算法（参见contrib/adons/tcp_ins）或任何其他所需算法的方法。当新的tcp连接需要ISN时，如果启用了tcp支持（@ref LWIP_tcp），则从tcp_connect（）和tcp_listen_input（）调用。\n签名：\code｛.c｝u32_t my_hook_tcp_isn（const ip_addr_t local_ip，u16_t local_port，const ip_addr_t remote_ip，u16_t remote_port）；\结束代码
 * -可能需要在函数声明中使用“struct ip_addr”（ip4_addr，ip6_addr）而不是“ip_addr_t”\n参数：
 * -local_ip：指向连接的本地ip地址的指针
 * -local_port：连接的本地端口号（主机字节顺序）
 * -remote_ip：指向连接的远程ip地址的指针
 * -remote_port：连接的远程端口号（主机字节顺序）\n返回值：
 * -用于新TCP连接的32位初始序列号。
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_TCP_ISN(local_ip, local_port, remote_ip, remote_port)
#endif

/**
 * LWIP_HOOK_TCP_INPACKET_PCB：用于在传入数据包传递到PCB之前拦截它们的钩子。这允许更新某些状态，甚至丢弃数据包。签名：\code｛.c｝err_t my_hook_tcp_inpkt（结构tcp_pcb pcb、结构tcp_hdr hdr、u16_t optlen、u16_ t opt1len、u8_t opt2、结构pbuf p）；\endcode参数：
 * -pcb:tcp_pcb选择用于此数据包的输入（注意：如果pcb->state==listen，则这可能是结构tcp_pcb_blisten）
 * -hdr：指向tcp头的指针（注意：tcp选项可能不是一个整体！）
 * -optlen:tcp选项长度
 * -opt1len:tcp选项长度第一部分
 * -opt2:如果是！=NULL，tcp选项在2个pbuf之间拆分。在这种情况下，选项从第一个“opt1len”字节的tcp头（“（u8_t）（hdr+1）”）之后开始，其余的从“opt2”开始。opt2len可以简单计算：“opt2len=optlen-optilen；”
 * -p：输入数据包，p->有效负载指向应用程序数据（这就是为什么tcp hdr和选项分别传入）返回值：
 * -ERR_OK：继续正常输入此数据包
 * - != ERR_OK：丢弃此数据包进行输入（不继续输入处理）
 *
 * 注意：不要调用任何可能通过回调更改tcp状态（pcb状态或任何pcb列表）的tcp api函数！
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_TCP_INPACKET_PCB(pcb, hdr, optlen, opt1len, opt2, p)
#endif

/**
 * LWIP_HOOK_TCP_OUT_TCPOPT_LENGTH：用于增加分配给TCP头的选项大小的钩子。与LWIP_HOOK_TCP_OUT_ADD_TCPOPTS一起，可用于向传出的TCP段添加自定义选项。签名：\code｛.c｝u8_t my_hook_tcp_out_tcpopt_length（const struct tcp_pcb pcb，u8_tinternal_option_length）；\endcode参数：
 * -pcb：传输的tcp_pcb（注意：如果pcb->状态==listen，则可能为NULL或结构tcp_pcb_intent）
 * -internal_option_length：堆栈内部使用的tcp选项长度返回值：
 * -为tcp选项分配的字节数（internal_option_length<=ret<=40）
 *
 * 注意：不要调用任何可能通过回调更改tcp状态（pcb状态或任何pcb列表）的tcp api函数！
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_TCP_OUT_TCPOPT_LENGTH(pcb, internal_len)
#endif

/**
 * LWIP_HOOK_TCP_OUT_ADD_TCPOPTS：用于向传出TCP段添加自定义选项的钩子。必须通过LWIP_HOOK_TCP_OUT_TCPOPT_LENGTH为这些自定义选项预留空间。签名：\code｛.c｝u32_t my_hook_tcp_out_add_tcppopts（struct pbuf p，struct tcp_hdr hdr，const struct tcp_pcb pcb，u32_topts）；\endcode参数：
 * -p：输出数据包，p->有效负载指向tcp报头，数据如下
 * -hdr:tcp头
 * -pcb：传输的tcp_pcb（注意：如果pcb->状态==listen，则可能为NULL或结构tcp_pcb_intent）
 * -opts:pointer添加自定义选项的位置（标头和这些选项之间可能已经有选项）返回值：
 * -指针直接指向插入的选项之后
 *
 * 注意：不要调用任何可能通过回调更改tcp状态（pcb状态或任何pcb列表）的tcp api函数！
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_TCP_OUT_ADD_TCPOPTS(p, hdr, pcb, opts)
#endif

/**
 * LWIP_HOOK_IP4_INPUT（pbuf，INPUT_netif）：从ip_INPUT（）（IPv4）调用签名：\code｛.c｝int my_HOOK（struct pbuf pbuf、struct netif INPUT_neti）；\endcode参数：
 * -pbuf：接收到传递给ip_input（）的结构pbuf
 * -input_netif：收到数据包的结构netif返回值：
 * -0:Hook未消耗数据包，数据包正常处理
 * - != 0:Hook已消耗数据包。如果钩子消耗了数据包，“pbuf”由钩子负责（即完成后释放）。
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_IP4_INPUT(pbuf, input_netif)
#endif

/**
 * LWIP_HOOK_IP4_ROUTE（dest）：从ip_ROUTE（）（IPv4）调用签名：\code｛.c｝struct netif my_HOOK（const IP4_addr_t dest）；\endcode参数：
 * -dest:目标IPv4地址返回值：
 * -目的地netif
 * -如果找不到目标netif，则为NULL。在这种情况下，ip_route（）照常继续。
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_IP4_ROUTE()
#endif

/**
 * LWIP_HOOK_IP4_ROUTE_SRC（SRC，dest）：基于IPv4的源路由-从ip_ROUTE（）（IPv4）调用签名：\code｛.c｝struct netif my_HOOK（const IP4_addr_t SRC，const IP4-addr_t dest）；\endcode参数：
 * -src：本地/源IPv4地址
 * -dest:目标IPv4地址返回值：
 * -目的地netif
 * -如果找不到目标netif，则为NULL。在这种情况下，ip_route（）照常继续。
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_IP4_ROUTE_SRC(src, dest)
#endif

/**
 * LWIP_HOOK_IP4_CANFORWARD（src，dest）：检查IPv4是否可以转发-从以下位置调用：IP4_input（）->IP4_forward（）->IP4_CANFORWARD（）（IPv4）
 * -源地址可通过ip4_current_src_addr（）获得
 * -允许在此上下文中调用输出函数（例如多播路由器）签名：\code｛.c｝int my_hook（struct pbuf p，u32_t dest_addr_hostorder）；\endcode参数：
 * -p：要转发的数据包
 * -dest:目标IPv4地址返回值：
 * -1：向前
 * -0：不转发
 * --1：没有决定。在这种情况下，ip4_canforward（）照常继续。
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_IP4_CANFORWARD(src, dest)
#endif

/**
 * LWIP_HOOK_ETHARP_GET_GW（netif，dest）：从ETHARP_out（）（IPv4）调用签名：\code｛.c｝const ip4_addr_t my_HOOK（结构netif netif，const ip4-addr_t dest）；\endcode参数：
 * -netif：用于发送的netif
 * -dest：目标IPv4地址返回值：
 * -处理指定目标IPv4地址的网关的IPv4地址
 * -NULL，在这种情况下使用netif的默认网关
 *
 * 返回的地址必须可以在指定的netif上直接访问！此函数旨在与LWIP_HOOK_IP4_ROUTE（）一起实现高级IPv4路由。实际的路由/网关表实现不是lwIP的一部分，但例如可以隐藏在netif的state参数中。
*/
#ifdef __DOXYGEN__
#define LWIP_HOOK_ETHARP_GET_GW(netif, dest)
#endif

/**
 * LWIP_HOOK_IP6_INPUT（pbuf，INPUT_netif）：从IP6_INPUT（）（IPv6）调用签名：\code｛.c｝int my_HOOK（struct pbuf pbuf、struct netif INPUT_neti）；\endcode参数：
 * -pbuf：接收到传递给ip6_input（）的结构pbuf
 * -input_netif：收到数据包的结构netif返回值：
 * -0:Hook未消耗数据包，数据包正常处理
 * - != 0:Hook已消耗数据包。如果钩子消耗了数据包，“pbuf”由钩子负责（即完成后释放）。
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_IP6_INPUT(pbuf, input_netif)
#endif

/**
 * LWIP_HOOK_IP6_ROUTE（src，dest）：从ip_ROUTE（）（IPv6）调用签名：\code｛.c｝struct netif my_HOOK（const IP6_addr_t dest，const ipp_addr_t src）；\endcode参数：
 * -src：源IPv6地址
 * -dest:目标IPv6地址返回值：
 * -目的地netif
 * -如果找不到目标netif，则为NULL。在这种情况下，ip6_route（）照常继续。
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_IP6_ROUTE(src, dest)
#endif

/**
 * LWIP_HOOK_ND6_GET_GW（netif，dest）：从ND6_GET_next_hop_entry（）（IPv6）调用签名：\code｛.c｝const ip6_addr_t my_HOOK（结构netif netif，const ip6_addr_t dest）；\endcode参数：
 * -netif：用于发送的netif
 * -dest：目标IPv6地址返回值：
 * -处理指定目标IPv6地址的下一跳的IPv6地址
 * -NULL，在这种情况下，使用NDP发现的路由器
 *
 * 返回的地址必须可以在指定的netif上直接访问！此函数旨在与LWIP_HOOK_IP6_ROUTE（）一起实现高级IPv6路由。实际的路由/网关表实现不是lwIP的一部分，但例如可以隐藏在netif的state参数中。
*/
#ifdef __DOXYGEN__
#define LWIP_HOOK_ND6_GET_GW(netif, dest)
#endif

/**
 * LWIP_HOOK_VLAN_CHECK（netif，eth_hdr，VLAN_hdr）：如果启用VLAN支持，则从ethernet_input（）调用签名：\code｛.c｝int my_HOOK（struct netif netif，struct eth_hdr eth_hdr、struct eth_VLAN_hdr VLAN_hdl）；\endcode参数：
 * -netif：接收数据包的结构netif
 * -eth_hdr：数据包的结构eth_hdr
 * -vlan_hdr：数据包的结构eth_vlan_hdr返回值：
 * -0:必须丢弃数据包。
 * - != 0:必须接受数据包。
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_VLAN_CHECK(netif, eth_hdr, vlan_hdr)
#endif

/**
 * LWIP_HOOK_VLAN_SET: Hook can be used to set prio_vid field of vlan_hdr. If you need to store data on per-netif basis to implement this callback, see @ref netif_cd。如果启用了VLAN支持（@ref ETHARP_support_VLAN），则从ethernet_output（）调用。\n签名：\code｛.c｝s32_t my_hook_vlan_set（struct netif netif，struct pbuf pbuf，const struct eth_addr src，const truct eth_add dst，u16_t eth_type）；\n\endcode参数：
 * -netif：数据包将通过的结构netif
 * -p：要发送的结构pbuf数据包
 * -src：源eth地址
 * -dst：目标eth地址
 * -eth_type：要发送的数据包的以太网类型\n
 * 
 *  返回值：
 * -&lt；0:数据包不应包含VLAN标头。
 * -0＜=返回值&lt；=0xFFFF：数据包应包含VLAN报头。返回值按主机字节顺序为prio_vid。
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_VLAN_SET(netif, p, src, dst, eth_type)
#endif

/**
 * LWIP_HOOK_MEMP_AVAILABLE（MEMP_t_type）：当MEMP池为空且项目现在可用时，从MEMP_free（）调用签名：\code｛.c｝void my_HOOK（MEMP_t类型）；\结束代码
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_MEMP_AVAILABLE(memp_t_type)
#endif

/**
 * LWIP_HOOK_UNKNOWN_ETH_PROTOCOL（pbuf，netif）：当遇到未知ETH类型时，从ethernet_input（）调用。签名：\code｛.c｝err_t my_hook（struct pbuf pbuf，struct netif netif）；\endcode参数：
 * -p:未知eth类型的rx数据包
 * -netif：接收数据包的netif返回值：
 * -如果数据包被接受，则返回ERR_OK（钩子函数现在拥有pbuf）
 * -否则任何错误代码（释放pbuf）
 *
 * 有效负载指向以太网标头！
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_UNKNOWN_ETH_PROTOCOL(pbuf, netif)
#endif

/**
 * LWIP_HOOK_DHCP_APPEND_OPTIONS（netif、DHCP、state、msg、msg_type、OPTIONS_len_ptr）：发送DHCP消息时从各种DHCP函数调用。在添加DHCP消息尾部之前调用此钩子，因此选项位于DHCP消息的末尾。签名：\code｛.c｝void my_hook（struct netif netif，struct dhcp dhcp，u8_t state，struct hcp_msg，u8_t msg_type，u16_t options_len_ptr）；\endcode参数：
 * -netif：数据包将通过的结构netif
 * -dhcp：该netif上的结构dhcp
 * -state：当前dhcp状态（dhcp_state_enum_t作为u8_t）
 * -msg:将发送的结构dhcp_msg
 * -msg_type：要发送的dhcp消息类型（u8_t）
 * -options_len_ptr：指向dhcp_msg“msg”中选项的当前长度的指针（添加选项时必须增加！）
 *
 * 选项需要这样附加：LWIP_ASSERT（“dhcp选项溢出”，Options_len_ptr+option_len+2<=dhcp_option_len）；消息->选项[（options_len_ptr）++]=&lt；选项_编号&gt；；消息->选项[（options_len_ptr）++]=&lt；option_len&gt；；消息->选项[（options_len_ptr）++]=&lt；选项字节&gt；；[...]
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_DHCP_APPEND_OPTIONS(netif, dhcp, state, msg, msg_type, options_len_ptr)
#endif

/**
 * LWIP_HOOK_DHCP_PARSE_OPTION（netif，DHCP，state，msg，msg_type，OPTION，len，pbuf，OPTION_value_offset）：接收DHCP消息时从DHCP_pare_reply调用。对接收到的消息中未在内部处理的每个选项调用此钩子。签名：\code｛.c｝void my_hook（struct netif netif，struct dhcp dhcp，u8_t state，struct hcp_msg，u8_t msg_type，u18_t option，u8 _t option_len，struct pbuf pbuf，u16_t option_value_offset）；\endcode参数：
 * -netif：数据包将通过的结构netif
 * -dhcp：该netif上的结构dhcp
 * -state：当前dhcp状态（dhcp_state_enum_t作为u8_t）
 * -msg:收到的结构dhcp_msg
 * -msg_type:收到dhcp消息类型（u8_t，注意：仅在解析消息类型选项后有效！）
 * -选项：选项值（u8_t）
 * -len：选项数据长度（u8_t）
 * -pbuf:pbuf，其中包含选项数据
 * -option_value_offset：pbuf中选项数据开始的偏移量
 *
 * 获取选项内容的一个好方法是pbuf_get_contiguous（）：u8_tbuf[32]；u8_tptr=（u8_t）pbuf_get_contiguous（p，buf，sizeof（buf），LWIP_MIN（option_len，sizeof，buf）），偏移量）；
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_DHCP_PARSE_OPTION(netif, dhcp, state, msg, msg_type, option, len, pbuf, offset)
#endif

/**
 * LWIP_HOOK_DHCP6_APPEND_OPTIONS（netif，DHCP6，state，msg，msg_type，OPTIONS_len_ptr，max_len）：发送DHCP6消息时从各种DHCP6函数调用。该钩子在DHCP6消息发送之前被调用，因此选项位于DHCP6信息的末尾。签名：\code｛.c｝void my_hook（struct netif netif，struct dhcp6 dhcp，u8_t state，struct hcp6_msg msg，u8_t msg_type，u16_t options_len_ptr）；\endcode参数：
 * -netif：数据包将通过的结构netif
 * -dhcp6：该netif上的结构dhcp6
 * -state：当前dhcp6状态（dhcp6_state_enum_t作为u8_t）
 * -msg:将发送的结构dhcp6_msg
 * -msg_type:要发送的dhcp6消息类型（u8_t）
 * -options_len_ptr：指向dhcp6_msg“msg”中选项的当前长度的指针（添加选项时必须增加！）
 *
 * 选项需要附加如下：u8_t Options=（u8_t）（msg+1）；LWIP_ASSERT（“dhcp选项溢出”，sizeof（结构dhcp6_msg）+options_len_ptr+newoptlen<=max_len）；options[（options_len_ptr）++]=&lt；option_data&gt；；[...]
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_DHCP6_APPEND_OPTIONS(netif, dhcp6, state, msg, msg_type, options_len_ptr, max_len)
#endif

/**
 * LWIP_HOOK_SOCKETS_SETSOCKOPT（s，sock，level，optname，optval，optlen，err）从套接字API调用，为LWIP未提供的选项实现SETSOCKOPT（）。调用此钩子时，将保持核心锁。签名：\code｛.c｝int my_hook（int s，struct lwip_sock sock，int level，int optname，const void optval，socklen_t optlen，int err）\endcode参数：
 * -s：套接字文件描述符
 * -sock：内部套接字描述符（请参阅lwip/priv/sockets_priv.h）
 * -级别：选项所在的协议级别
 * -optname：要设置的选项
 * -optval：要设置的值
 * -optlen:optval的大小
 * -错误：输出错误返回值：
 * -0:Hook尚未使用该选项，代码继续正常（内部选项）
 * - != 0:钩子已使用选项，返回“err”
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_SOCKETS_SETSOCKOPT(s, sock, level, optname, optval, optlen, err)
#endif

/**
 * LWIP_HOOK_SOCKETS_GETSOCKOPT（s，sock，level，optname，optval，optlen，err）从套接字API调用，为LWIP未提供的选项实现GETSOCKOPT（）。调用此钩子时，将保持核心锁。签名：\code｛.c｝int my_hook（int s，struct lwip_sock sock，int level，int optname，void optval，socklen_t optlen，int err）\endcode参数：
 * -s：套接字文件描述符
 * -sock：内部套接字描述符（请参阅lwip/priv/sockets_priv.h）
 * -级别：选项所在的协议级别
 * -optname：获取的选项
 * -optval：要获取的值
 * -optlen:optval的大小
 * -错误：输出错误返回值：
 * -0:Hook尚未使用该选项，代码继续正常（内部选项）
 * - != 0:钩子已使用选项，返回“err”
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_SOCKETS_GETSOCKOPT(s, sock, level, optname, optval, optlen, err)
#endif

/**
 * LWIP_HOOK_NETCONN_EXTERNAL_RESOLVE（name，addr，addrtype，err）从NETCONN API调用（不适用于回调应用程序），允许外部DNS解析器（使用顺序API）处理查询。签名：\code｛.c｝int my_hook（const char name，ip_addr_t addr，u8_t addrtype，err_t err）\endcode参数：
 * -name:要解析的主机名
 * -addr：输出主机地址
 * -addrtype：要查询的地址类型
 * -错误：输出错误返回值：
 * -0:钩子尚未使用主机名查询，查询继续到DNS模块
 * - != 0:钩子已消耗查询
 *
 * 还必须检查err以确定钩子是否使用了查询，但查询失败
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_NETCONN_EXTERNAL_RESOLVE(name, addr, addrtype, err)
#endif
/**
 * @}
 */

/*
   ---------------------------------------
   ----------调试选项----------
   ---------------------------------------
*/
/**
 * @defgroup lwip_opts_debugmsg调试消息
 * @ingroup lwip_opts_debug@{
 */
/**
 * LWIP_DBG_MIN_LEVEL：屏蔽后，将调试值与此值进行比较。如果它较小，则编写调试消息。
 * @see 调试级别
 */
#if !defined LWIP_DBG_MIN_LEVEL || defined __DOXYGEN__
#define LWIP_DBG_MIN_LEVEL              LWIP_DBG_LEVEL_ALL
#endif

/**
 * LWIP_DBG_TYPES_ON：可用于全局启用/禁用某些类型的调试消息的掩码。
 * @see 调试级别
 */
#if !defined LWIP_DBG_TYPES_ON || defined __DOXYGEN__
#define LWIP_DBG_TYPES_ON               LWIP_DBG_ON
#endif

/**
 * ETHARP_DEBUG：在ETHARP.c中启用调试。
 */
#if !defined ETHARP_DEBUG || defined __DOXYGEN__
#define ETHARP_DEBUG                    LWIP_DBG_OFF
#endif

/**
 * NETIF_DEBUG：启用NETIF.c中的调试。
 */
#if !defined NETIF_DEBUG || defined __DOXYGEN__
#define NETIF_DEBUG                     LWIP_DBG_OFF
#endif

/**
 * PBUF_DEBUG：在PBUF.c中启用调试。
 */
#if !defined PBUF_DEBUG || defined __DOXYGEN__
#define PBUF_DEBUG                      LWIP_DBG_OFF
#endif

/**
 * API_LIB_DEBUG：在API_LIB.c中启用调试。
 */
#if !defined API_LIB_DEBUG || defined __DOXYGEN__
#define API_LIB_DEBUG                   LWIP_DBG_OFF
#endif

/**
 * API_MSG_DEBUG：在API_MSG.c中启用调试。
 */
#if !defined API_MSG_DEBUG || defined __DOXYGEN__
#define API_MSG_DEBUG                   LWIP_DBG_OFF
#endif

/**
 * SOCKETS_DEBUG：在SOCKETS.c中启用调试。
 */
#if !defined SOCKETS_DEBUG || defined __DOXYGEN__
#define SOCKETS_DEBUG                   LWIP_DBG_OFF
#endif

/**
 * ICMP_DEBUG：在ICMP.c中启用调试。
 */
#if !defined ICMP_DEBUG || defined __DOXYGEN__
#define ICMP_DEBUG                      LWIP_DBG_OFF
#endif

/**
 * IGMP_DEBUG：在IGMP.c中启用调试。
 */
#if !defined IGMP_DEBUG || defined __DOXYGEN__
#define IGMP_DEBUG                      LWIP_DBG_OFF
#endif

/**
 * INET_DEBUG：在INET.c中启用调试。
 */
#if !defined INET_DEBUG || defined __DOXYGEN__
#define INET_DEBUG                      LWIP_DBG_OFF
#endif

/**
 * IP_DEBUG：启用IP调试。
 */
#if !defined IP_DEBUG || defined __DOXYGEN__
#define IP_DEBUG                        LWIP_DBG_OFF
#endif

/**
 * IP_REASS_DEBUG：在IP_frag中启用调试。c表示碎片和碎片。
 */
#if !defined IP_REASS_DEBUG || defined __DOXYGEN__
#define IP_REASS_DEBUG                  LWIP_DBG_OFF
#endif

/**
 * RAW_DEBUG：在RAW.c中启用调试。
 */
#if !defined RAW_DEBUG || defined __DOXYGEN__
#define RAW_DEBUG                       LWIP_DBG_OFF
#endif

/**
 * MEM_DEBUG：启用MEM.c中的调试。
 */
#if !defined MEM_DEBUG || defined __DOXYGEN__
#define MEM_DEBUG                       LWIP_DBG_OFF
#endif

/**
 * MEMP_DEBUG：在MEMP.c中启用调试。
 */
#if !defined MEMP_DEBUG || defined __DOXYGEN__
#define MEMP_DEBUG                      LWIP_DBG_OFF
#endif

/**
 * SYS_DEBUG：在SYS.c中启用调试。
 */
#if !defined SYS_DEBUG || defined __DOXYGEN__
#define SYS_DEBUG                       LWIP_DBG_OFF
#endif

/**
 * TIMERS_DEBUG：在timer.c中启用调试。
 */
#if !defined TIMERS_DEBUG || defined __DOXYGEN__
#define TIMERS_DEBUG                    LWIP_DBG_OFF
#endif

/**
 * TCP_DEBUG：启用TCP调试。
 */
#if !defined TCP_DEBUG || defined __DOXYGEN__
#define TCP_DEBUG                       LWIP_DBG_OFF
#endif

/**
 * TCP_INPUT_DEBUG：启用TCP_in中的调试。c表示传入调试。
 */
#if !defined TCP_INPUT_DEBUG || defined __DOXYGEN__
#define TCP_INPUT_DEBUG                 LWIP_DBG_OFF
#endif

/**
 * TCP_FR_DEBUG：启用TCP_in中的调试。c用于快速重传。
 */
#if !defined TCP_FR_DEBUG || defined __DOXYGEN__
#define TCP_FR_DEBUG                    LWIP_DBG_OFF
#endif

/**
 * TCP_ROT_DEBUG：启用TCP中的重新传输超时调试。
 */
#if !defined TCP_RTO_DEBUG || defined __DOXYGEN__
#define TCP_RTO_DEBUG                   LWIP_DBG_OFF
#endif

/**
 * TCP_CND_DEBUG：启用TCP拥塞窗口的调试。
 */
#if !defined TCP_CWND_DEBUG || defined __DOXYGEN__
#define TCP_CWND_DEBUG                  LWIP_DBG_OFF
#endif

/**
 * TCP_WND_DEBUG：在TCP_in中启用调试。c用于窗口更新。
 */
#if !defined TCP_WND_DEBUG || defined __DOXYGEN__
#define TCP_WND_DEBUG                   LWIP_DBG_OFF
#endif

/**
 * TCP_OUTPUT_DEBUG：在TCP_out中启用调试。c输出函数。
 */
#if !defined TCP_OUTPUT_DEBUG || defined __DOXYGEN__
#define TCP_OUTPUT_DEBUG                LWIP_DBG_OFF
#endif

/**
 * TCP_RST_DEBUG：使用RST消息启用TCP调试。
 */
#if !defined TCP_RST_DEBUG || defined __DOXYGEN__
#define TCP_RST_DEBUG                   LWIP_DBG_OFF
#endif

/**
 * TCP_QLEN_DEBUG：启用TCP队列长度的调试。
 */
#if !defined TCP_QLEN_DEBUG || defined __DOXYGEN__
#define TCP_QLEN_DEBUG                  LWIP_DBG_OFF
#endif

/**
 * UDP_DEBUG：启用UDP中的调试。
 */
#if !defined UDP_DEBUG || defined __DOXYGEN__
#define UDP_DEBUG                       LWIP_DBG_OFF
#endif

/**
 * TCPIP_DEBUG：在TCPIP.c中启用调试。
 */
#if !defined TCPIP_DEBUG || defined __DOXYGEN__
#define TCPIP_DEBUG                     LWIP_DBG_OFF
#endif

/**
 * SLIP_DEBUG：在slipif.c中启用调试。
 */
#if !defined SLIP_DEBUG || defined __DOXYGEN__
#define SLIP_DEBUG                      LWIP_DBG_OFF
#endif

/**
 * DHCP_DEBUG：在DHCP.c中启用调试。
 */
#if !defined DHCP_DEBUG || defined __DOXYGEN__
#define DHCP_DEBUG                      LWIP_DBG_OFF
#endif

/**
 * AUTOIP_DEBUG：在AUTOIP.c中启用调试。
 */
#if !defined AUTOIP_DEBUG || defined __DOXYGEN__
#define AUTOIP_DEBUG                    LWIP_DBG_OFF
#endif

/**
 * DNS_DEBUG:启用DNS调试。
 */
#if !defined DNS_DEBUG || defined __DOXYGEN__
#define DNS_DEBUG                       LWIP_DBG_OFF
#endif

/**
 * IP6_DEBUG：启用IPv6调试。
 */
#if !defined IP6_DEBUG || defined __DOXYGEN__
#define IP6_DEBUG                       LWIP_DBG_OFF
#endif

/**
 * DHCP6_DEBUG：在DHCP6.c中启用调试。
 */
#if !defined DHCP6_DEBUG || defined __DOXYGEN__
#define DHCP6_DEBUG                     LWIP_DBG_OFF
#endif
/**
 * @}
 */

/**
 * LWIP_TESTMODE：更改以使单元测试成为可能
 */
#if !defined LWIP_TESTMODE
#define LWIP_TESTMODE                   0
#endif

/**
 * NAPT_DEBUG：启用NAPT的调试。
 */
#ifndef NAPT_DEBUG
#define NAPT_DEBUG                       LWIP_DBG_OFF
#endif

/*
   --------------------------------------------------
   ----------性能跟踪选项----------
   --------------------------------------------------
*/
/**
 * @defgroup lwip_opts_perf性能
 * @ingroup lwip_opts_debug@{
 */
/**
 * LWIP_PERF：启用LWIP的性能测试（如果启用，则包括arch/PERF.h）
 */
#if !defined LWIP_PERF || defined __DOXYGEN__
#define LWIP_PERF                       0
#endif
/**
 * @}
 */

#endif /* LWIP_HDR_OPT_H */

