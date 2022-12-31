/**
 * @defgroup lwip lwip
 *
 * @defgroup 基础设施基础设施
 * 
 * @defgroup api api lwIP为用于与TCP/IP代码通信的程序提供了三个应用程序接口（api）：
 * -低级“核心”/“回调”或@ref callbackstyle_api。
 * - higher-level @ref sequential_api。
 * -BSD样式@ref套接字。
 * 
 * 原始TCP/IP接口允许应用程序更好地与TCP/IP代码集成。通过在TCP/IP代码中调用回调函数，程序执行是基于事件的。TCP/IP代码和应用程序都在同一线程中运行。顺序API的开销要高得多，而且不太适合小型系统，因为它强制应用程序采用多线程模式。
 * 
 * 原始TCP/IP接口不仅在代码执行时间方面更快，而且内存占用更少。缺点是程序开发有些困难，为原始TCP/IP接口编写的应用程序更难理解。尽管如此，这是编写代码大小和内存使用量应该较小的应用程序的首选方式。
 * 
 * 不同的应用程序可以同时使用所有API。事实上，顺序API是使用原始TCP/IP接口作为应用程序实现的。
 * 
 * 不要将lwIP原始API与原始以太网或IP套接字混淆。前者是连接lwIP网络堆栈（包括TCP和UDP）的一种方式，后者指的是处理原始以太网或IP数据，而不是TCP连接或UDP数据包。
 * 
 * 原始API应用程序可能永远不会阻塞，因为所有数据包处理（输入和输出）以及定时器处理（主要是TCP）都在单个执行上下文中完成。
 *
 * @defgroup callbackstyle_api“原始”api
 * @ingroup api非线程安全api，回调样式可实现最大性能和最小内存占用。程序执行由回调函数驱动，当与该应用程序相关的活动发生时，lwIP核心会调用回调函数。特定应用程序可以注册以通过回调函数通知事件，例如可用的传入数据、发送的传出数据、错误通知、轮询计时器过期、连接关闭等。应用程序可以提供回调函数来对任何或所有这些事件执行处理。每个回调都是从TCP/IP代码中调用的普通C函数。每个回调函数都作为参数传递当前TCP或UDP连接状态。此外，为了能够保持程序特定的状态，回调函数使用独立于TCP/IP状态的程序指定参数调用。原始API（有时称为本机API）是一种事件驱动API，旨在在没有实现零拷贝发送和接收的操作系统的情况下使用。该API也被核心堆栈用于各种协议之间的交互。它是在没有操作系统的情况下运行lwIP时唯一可用的API。
 * 
 * @defgroup sequential_api顺序样式api
 * @ingroup api顺序式api，阻塞函数。开销更大，但可以从TCPIP线程以外的任何线程调用。顺序API为普通的顺序程序提供了一种使用lwIP堆栈的方法。它与BSD套接字API非常相似。执行模型基于阻塞-打开-读取-写入-关闭模式。由于TCP/IP堆栈本质上是基于事件的，因此TCP/IP代码和应用程序必须驻留在不同的执行上下文（线程）中。
 * 
 * @defgroup 套接字套接字API
 * @ingroup api BSD风格的套接字api。\n线程安全，仅从非TCPIP线程调用。\n可以通过将@ref LWIP_SOCKET定义为1来激活。\n标头位于posix/sys/SOCKET中。h\n套接字API是现有应用程序的兼容性API，目前它构建在顺序API之上。它旨在提供运行在其他平台（例如unix/windows等）上运行的套接字API应用程序所需的所有功能。然而，由于此API规范的限制，可能存在需要对现有程序进行少量修改的不兼容性。
 * 
 * @defgroup netifs NETIF
 * 
 * @defgroup 应用程序应用程序
 */

/**
 * @mainpage 概述
 * @verbinclude "README"
 */

/**
 * @page 升级升级
 * @verbinclude "UPGRADING"
 */

/**
 * @page 变更日志变更日志
 *
 * 2.1.0
 * -----
 * * Support TLS via new @ref altcp_api连接api（https、smtps、mqtt over TLS）切换到cmake作为主构建系统（Makefile文件列表目前仍在维护）改进IPv6支持：支持地址范围，支持无状态DHCPv6，错误修复添加调试助手断言以确保满足线程/锁定要求添加sys_mbox_trypost_fromisr（）和tcpip_callbackmsg_trycallback_fromis（）（主要用于FreeRTOS）套接字API：支持poll（）、sendmsg（）和recvmsg（）；在关闭时修复问题
 * 
 * 详细变更日志
 * ------------------
 * @verbinclude "CHANGELOG"
 */

/**
 * @page contrib如何为lwIP做出贡献
 * @verbinclude “contrib.txt”
 */

/**
 * @page 陷阱常见陷阱
 *
 * lwIP代码中的多个执行上下文========================================
 *
 * lwIP问题的最常见来源是lwIP代码中有多个执行上下文。
 * 
 * lwIP可以在两种基本模式下使用：@ref lwIP_nosys（无OS/RTOS
 * running on target system) or @ref lwip_os（目标系统上有一个操作系统正在运行）。
 * 
 * See also: @ref 多线程（尤其是关于@ref LWIP_ASSERT_CORE_LOCKED（）的部分！）
 *
 * 主回路模式
 * -------------
 * In mainloop mode, only @ref 可以使用callbackstyleapi。用户有两种可能确保lwIP中一次只有一个执行上下文：
 *
 * 1） 通过在中断中直接调用netif->input，将中断上下文中的RX以太网数据包直接传递到lwIP。这意味着所有lwIP回调函数都是在IRQ上下文中调用的，这可能会在应用程序代码中造成进一步的问题：IRQ被长时间阻塞，应用程序代码有多个执行上下文等。当应用程序想要调用lwIP时，只需在调用期间禁用中断。如果涉及定时器，则需要更多的锁定代码来锁定定时器IRQ和以太网IRQ，假设它们可能是嵌套的。
 *
 * 2) Run lwIP in a mainloop. There is example code here: @ref lwip_nosys。lwIP是从这里的主循环调用堆栈调用的_ONLY_。以太网IRQ必须将接收到的电报放入主环路中轮询的队列中。确保lwIP是从中断调用的，例如某些SPI IRQ想要将数据转发到udp_send（）或tcp_write（）！
 *
 * 操作系统模式
 * -------
 * In OS mode, @ref 可以使用callbackstyle_api AND@ref sequential_api。
 * @ref sequential_api被设计为从TCPIP线程以外的线程调用，因此这里没有什么需要考虑的。
 * But @ref callbackstyle_api函数必须从TCPIP线程调用_ONLY_。从其他线程或IRQ上下文调用这些是一个常见错误。​以太网RX需要通过向TCPIP线程发送消息以正确的方式传递传入的数据包，这在TCPIP_input（）中实现。​​ 同样，确保lwIP是从中断调用的_NEVER_，例如某些SPI IRQ想要将数据转发到udp_send（）或tcp_write（）！
 * 
 * 1） tcpip_callback（）可以用于从tcpip线程回调，
 *    it is safe to call any @ref 从那里调用backstyleapi。
 *
 * 2) Use @ref LWIP_TCPIP_CORE_LOCKING。当获取lwIP核心锁时，可以调用所有@ref callbackstyle_api函数，请参见
 *    @ref LOCK_TCPP_CORE（）和@ref UNLOCK_TCP_CORE（）。这些宏不能在中断上下文中使用！注意，操作系统必须正确处理优先级反转。
 *
 * 缓存/DMA问题==================
 *
 * 支持DMA的以太网硬件和零拷贝RX
 * ----------------------------------------------
 * 
 * lwIP更改TCP代码路径中RECEIVE pbufs的内容。这意味着RX pbuf的一个或多个缓存行变脏，需要在将内存移交给DMA以太网硬件以接收下一个报文之前进行刷新。看见http://lists.nongnu.org/archive/html/lwip-devel/2017-12/msg00070.html以获得更详细的解释。还要记住，用户应用程序也可能写入pbufs，因此在将缓冲区交给DMA硬件之前不刷新数据缓存通常是一个错误。
 *
 * 支持DMA的以太网硬件和缓存线对齐
 * -----------------------------------------------------关于支持DMA的硬件和缓冲区处理的详细描述：http://www.pebblebay.com/a-guide-to-using-direct-memory-access-in-embedded-systems-part-two/特别阅读“缓存一致性”和“缓冲区对齐”部分。
 */

/**
 * @page mem_err调试内存池大小如果lwIP存在问题，并且正在使用内存池，请检查池的大小是否正确。\n要调试池大小，请将LWIP_STATS和MEMP_STATS定义为1。检查全局变量LWIP_STATS。memp[]使用调试器。如果池的“err”成员大于0，则该池对于您的应用程序来说可能太小，您需要增加其大小。
 */

/**
 * @page bug报告bug请在萨凡纳的lwIP bug跟踪器中报告bug。\n提交前，请检查是否已报告错误！\n个https://savannah.nongnu.org/bugs/?group=lwip
 */

/**
 * @page zerocopyrx零拷贝RX以下代码是零拷贝RX以太网驱动程序的示例：
 * @include 零拷贝Rx.c
 */

/**
 * @defgroup lwip_nosys主回路模式（“NO_SYS”）
 * @ingroup lwip如果您没有在系统上运行操作系统，请使用此模式\#将NO_SYS定义为1。从主循环（而不是中断上下文）向netif->input（pbuf，netif）函数馈送传入数据包。您可以在中断上下文中分配一个@ref pbuf，并将它们放入从主循环处理的队列中。\n在主循环中定期调用sys_check_timeouts（）。\n移植：实现@ref sys_time、@ref sys_prot和
 * @ref compiler_abstraction。\n
 * You can only use @ref 在此模式下调用backstyleapi。\n示例代码：\n
 * @include NO_SYS_样本代码.c
 */

/**
 * @defgroup lwip_os os模式（TCPIP线程）
 * @ingroup lwip如果在系统上运行操作系统，请使用此模式。建议使用正确处理优先级反转和
 * to use @ref LWIP_TCPIP_CORE_LOCKING。\n移植：在@ref sys_layer中实现所有函数。\n
 * You can use @ref callbackstyle_api与@ref tcpip_callback一起，
 * and all @ref sequential_api。
 */

/**
 * @page sys_init系统初始化无法给出用于初始化lwIP堆栈的真正完整的通用序列，因为它取决于运行时环境的其他初始化（例如计时器）。

我们可以给你一些关于如何使用原始API的想法。我们假设使用单个以太网网络、UDP和TCP传输层、IPv4和DHCP客户端的配置。

按外观顺序调用这些函数：

-lwip_init（）：初始化lwip堆栈及其所有子系统。

- netif_add(struct netif *netif, …）：将网络接口添加到netif_list。分配一个结构netif，并将指针作为第一个参数传递给该结构。当使用DHCP时，为已清除的ip_addr结构提供指针，否则用正确的数字填充。状态指针可能为NULL。

  init函数指针必须指向以太网netif接口的初始化函数。下面的代码说明了它的用法。
  
@代码｛.c｝
  err_t netif_init（结构netif*netif）
  {
    u8_ti；
    
    对于（i=0；i<ETHARP_WADDR_LEN；i++）{
      netif->hwaddr[i]=some_eth_addr[i]；
    }
    init_my_eth_device（）；
    返回ERR_OK；
  }
@结束代码
  
  对于以太网驱动程序，输入函数指针必须指向“netif/etharp.h”中声明的lwIP函数Ethernet_input（）。其他驱动程序必须使用“lwip/ip.h”中声明的ip_input（）。
  
- netif_set_default(struct netif *netif) 注册默认网络接口。

- netif_set_link_up(struct netif *netif) 这是硬件链路状态；e、 g.有线以太网接口的电缆是否插入。即使您不知道当前状态，也必须调用此函数。具有链接启动和链接关闭事件是可选的，但DHCP和IPv6发现从这些事件中受益匪浅。

- netif_set_up(struct netif *netif) 这是netif的管理（=软件）状态，当netif完全配置时，必须调用此函数。

- dhcp_start(struct netif *netif) 在第一次调用时为此接口创建新的DHCP客户端。您可以在netif->dhcp结构中查看实际的dhcp状态。

-sys_check_timeouts（）当系统运行时，您必须周期性地调用sys_check_Timeout（），它将处理堆栈中所有协议的所有计时器；将其添加到主循环或等效循环中。
 */

/**
 * @page 多线程多线程lwIP开始针对单线程环境。在添加多线程支持时，选择了另一种方法，而不是使核心线程安全：有一个主线程运行lwIP核心（也称为“tcpip_thread”）。在多线程环境中运行时，原始API函数只能从核心线程调用，因为原始API函数不受并发访问的保护（除了pbuf和内存管理函数）。使用顺序或套接字API的应用程序线程通过消息传递与该主线程通信。
 * 
 * 因此，可以从其他线程或ISR调用的函数列表非常有限！只有来自这些API头文件的函数是线程安全的：
 * -api.h语言
 * -网布.h
 * -网络数据库.h
 * -netifapi.h
 * -pppapi.小时
 * -套接字.h
 * -系统.h
 * 
 * 此外，可以从多个线程（而不是ISR！）调用内存（去）分配函数NO_SYS=0
 * since they are protected by @ref SYS_LIGHTWEIGHT_PROT和/或信号量。
 * 
 * Netconn或Socket API函数对核心线程是线程安全的，但在控制块粒度级别上不可重入。也就是说，在没有适当锁定的情况下，UDP或TCP控制块不能在多个线程之间共享。
 * 
 * If @ref SYS_LIGHTWEIGHT_PROT设置为1
 * @ref LWIP_ALLOW_MEM_FREE_FROM_THER_CONTEXT设置为1，pbuf_FREE（）也可以从另一个线程或ISR调用（因为只有这样，MEM_FREE-对于pbuf_RAM-才能从ISR调用：否则，HEAP仅受信号量保护）。
 * 
 * 如何正确完成线程
 * -------------------------------
 * 
 * 强烈建议在使用多线程的应用程序中实现LWIP_ASSERT_CORE_LOCKED（）宏。lwIP代码有几个地方可以实现对正确线程上下文的检查，这极大地帮助用户正确完成线程。请参见示例sys_arch。c文件和contrib存储库中的Win32端口。
 * 
 * 简而言之：将函数sys_mark_tcpip_thread（）和sys_check_core_locking（）复制到您的端口，并对它们进行修改，使其与您的操作系统一起使用。
 * Then let @ref LWIP_ASSERT_CORE_LOCKED（）和@ref LWIP_MARK_TCPIP_THREAD（）指向这些函数。
 * 
 * If you use @ref LWIP_TCPIP_CORE_LOCKING，还需要复制和调整函数sys_lock_TCPIP_CORE（）和sys_unlock_TCPIP _CORE（（）。
 * Let @ref LOCK_TCPP_CORE（）和@ref UNLOCK_TCP_CORE（）指向这些函数。
 */

/**
 * @page 优化优化提示首先要优化src/core/inet.c中的lwip_standard_checksum（）例程。您可以使用\#define lwip_CHKSUM your_checksum_routine（）重写此标准函数。

inet中给出了C个示例。或者您可能想为此编写一个汇编函数。RFC1071是对这个主题的一个很好的介绍。

如果您使用的是little endian体系结构，则可以通过为htons（）和hton（）提供汇编或内联替换来实现其他显著的改进\#define lwip_htons（x）your_htons。

如果网络接口驱动程序读取的速度高于最大线速度，请检查它。如果硬件没有得到频繁的服务，并且缓冲区溢出速度很快，则可能发生。

E、 g.使用cs8900驱动程序时，请尽可能频繁地调用cs8900if_service（ethif）。使用RTOS时，让cs8900中断唤醒一个高优先级任务，该任务使用二进制信号或事件标志为驱动程序提供服务。某些驱动程序可能允许额外的调整以匹配您的应用程序和网络。

对于生产版本，建议将LWIP_STATS设置为0。请注意，简单地为内存选项设置高值不会对速度性能产生太大影响。
 */

