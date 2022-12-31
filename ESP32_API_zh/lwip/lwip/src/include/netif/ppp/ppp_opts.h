/*
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 */

#ifndef LWIP_PPP_OPTS_H
#define LWIP_PPP_OPTS_H

#include "lwip/opt.h"

/**
 * PPP_SUPPORT==1：启用PPP。
 */
#ifndef PPP_SUPPORT
#define PPP_SUPPORT                     0
#endif

/**
 * PPPOE_SUPPORT==1：通过以太网启用PPP
 */
#ifndef PPPOE_SUPPORT
#define PPPOE_SUPPORT                   0
#endif

/**
 * PPPOE_SCNAME_SUPPORT==1：启用以太网PPP服务名称和集中器名称支持
 */
#ifndef PPPOE_SCNAME_SUPPORT
#define PPPOE_SCNAME_SUPPORT            0
#endif

/**
 * PPPOL2TP_SUPPORT==1：在L2TP上启用PPP
 */
#ifndef PPPOL2TP_SUPPORT
#define PPPOL2TP_SUPPORT                0
#endif

/**
 * PPPOL2TP_AUTH_SUPPORT==1：启用PPP Over L2TP身份验证（启用MD5支持）
 */
#ifndef PPPOL2TP_AUTH_SUPPORT
#define PPPOL2TP_AUTH_SUPPORT           PPPOL2TP_SUPPORT
#endif

/**
 * PPPOS_SUPPORT==1：启用串行PPP
 */
#ifndef PPPOS_SUPPORT
#define PPPOS_SUPPORT                   PPP_SUPPORT
#endif

/**
 * LWIP_PPP_API==1：启用PPP API（在pppapi.c中）
 */
#ifndef LWIP_PPP_API
#define LWIP_PPP_API                    (PPP_SUPPORT && (NO_SYS == 0))
#endif

#if PPP_SUPPORT

/**
 * MEMP_NUM_PPP_PCB：同时活动的PPP连接数（需要PPP_SUPPORT选项）
 */
#ifndef MEMP_NUM_PPP_PCB
#define MEMP_NUM_PPP_PCB                1
#endif

/**
 * PPP_NUM_TIMEOUTS_PER_PCB：每个PPP_PCB并行运行的系统超时数。请参见ppp_impl末尾的详细说明。h关于同时计时器分析。
 */
#ifndef PPP_NUM_TIMEOUTS_PER_PCB
#define PPP_NUM_TIMEOUTS_PER_PCB        (1 + PPP_IPV4_SUPPORT + PPP_IPV6_SUPPORT + CCP_SUPPORT)
#endif

/* PPP模块所需的sys_timeout数*/
#define PPP_NUM_TIMEOUTS                (PPP_SUPPORT * PPP_NUM_TIMEOUTS_PER_PCB * MEMP_NUM_PPP_PCB)

/**
 * MEMP_NUM_PPPOS_INTERFACES：并发活动PPPOS接口的数量（仅与PPPOS_SUPPORT==1一起使用）
 */
#ifndef MEMP_NUM_PPPOS_INTERFACES
#define MEMP_NUM_PPPOS_INTERFACES       MEMP_NUM_PPP_PCB
#endif

/**
 * MEMP_NUM_PPPOE_INTERFACES：并发活动PPPOE接口的数量（仅与PPPOE_SUPPORT==1一起使用）
 */
#ifndef MEMP_NUM_PPPOE_INTERFACES
#define MEMP_NUM_PPPOE_INTERFACES       1
#endif

/**
 * MEMP_NUM_PPPOL2TP_INTERFACES：并发活动PPPOL2TP接口的数量（仅与PPPOL2TP_SUPPORT==1一起使用）
 */
#ifndef MEMP_NUM_PPPOL2TP_INTERFACES
#define MEMP_NUM_PPPOL2TP_INTERFACES       1
#endif

/**
 * MEMP_NUM_PPP_API_MSG：并发PPP API消息的数量（以pppapi.c为单位）
 */
#ifndef MEMP_NUM_PPP_API_MSG
#define MEMP_NUM_PPP_API_MSG 5
#endif

/**
 * PPP_DEBUG：启用PPP调试。
 */
#ifndef PPP_DEBUG
#define PPP_DEBUG                       LWIP_DBG_OFF
#endif

/**
 * PPP_INPROC_IRQ_SAFE==1使用tcpip_callback（）调用pppos_input（）。
 *
 * 请阅读PPP文档中有关此选项的“PPPoS输入路径”章节。
 */
#ifndef PPP_INPROC_IRQ_SAFE
#define PPP_INPROC_IRQ_SAFE             0
#endif

/**
 * PRINTPKT_SUPPORT==1：启用PPP打印数据包支持
 *
 * 调试时必须使用，它在调试跟踪中显示交换的数据包内容。
 */
#ifndef PRINTPKT_SUPPORT
#define PRINTPKT_SUPPORT                0
#endif

/**
 * PPP_IPV4_SUPPORT==1：启用PPP IPV4支持
 */
#ifndef PPP_IPV4_SUPPORT
#define PPP_IPV4_SUPPORT                (LWIP_IPV4)
#endif

/**
 * PPP_IPV6_SUPPORT==1：启用PPP IPV6支持
 */
#ifndef PPP_IPV6_SUPPORT
#define PPP_IPV6_SUPPORT                (LWIP_IPV6)
#endif

/**
 * PPP_NOTIFY_PHASE==1：支持PPP通知阶段支持
 *
 * PPP通知阶段支持允许您设置在内部PPP状态机更改时调用的回调。
 *
 * 这可以用于例如根据PPP会话的当前阶段设置LED模式。
 */
#ifndef PPP_NOTIFY_PHASE
#define PPP_NOTIFY_PHASE                0
#endif

/**
 * pbuf_type PPP用于LCP、PAP、CHAP、EAP、CCP、IPCP和IP6CP数据包。
 *
 * 分配的内存必须是单缓冲的，PPP才能工作，它需要在分配时不会被链接的pbuf。这需要将PBUF_POOL_BUFSIZE设置为至少512字节，这对于小型系统来说是非常大的。
 *
 * 将PPP_USE_PBUF_RAM设置为1会使PPP使用需要连续缓冲区的堆内存，从而允许您使用较小的PBUF_POOL_BUFSIZE。
 */
#ifndef PPP_USE_PBUF_RAM
#define PPP_USE_PBUF_RAM                0
#endif

/**
 * PPP_FCS_TABLE：保留一个256*2字节的表，以加快PPPoS的FCS计算
 */
#ifndef PPP_FCS_TABLE
#define PPP_FCS_TABLE                   1
#endif

/**
 * PAP_SUPPORT==1：支持PAP。
 */
#ifndef PAP_SUPPORT
#define PAP_SUPPORT                     0
#endif

/**
 * CHAP_SUPPORT==1：支持CHAP。
 */
#ifndef CHAP_SUPPORT
#define CHAP_SUPPORT                    0
#endif

/**
 * MSCHAP_SUPPORT==1：支持MSCHAP。
 */
#ifndef MSCHAP_SUPPORT
#define MSCHAP_SUPPORT                  0
#endif
#if MSCHAP_SUPPORT
/* MSCHAP需要CHAP支持*/
#undef CHAP_SUPPORT
#define CHAP_SUPPORT                    1
#endif /* MSCHAP_SUPPORT */

/**
 * EAP_SUPPORT==1：支持EAP。
 */
#ifndef EAP_SUPPORT
#define EAP_SUPPORT                     0
#endif

/**
 * CCP_SUPPORT==1：支持CCP。
 */
#ifndef CCP_SUPPORT
#define CCP_SUPPORT                     0
#endif

/**
 * MPPE_SUPPORT==1：支持MPPE。
 */
#ifndef MPPE_SUPPORT
#define MPPE_SUPPORT                    0
#endif
#if MPPE_SUPPORT
/* MPPE需要CCP支持*/
#undef CCP_SUPPORT
#define CCP_SUPPORT                     1
/* MPPE需要MSCHAP支持*/
#undef MSCHAP_SUPPORT
#define MSCHAP_SUPPORT                  1
/* MSCHAP需要CHAP支持*/
#undef CHAP_SUPPORT
#define CHAP_SUPPORT                    1
#endif /* MPPE_SUPPORT */

/**
 * CBCP_SUPPORT==1：支持CBCP。当前不支持！不要设置！
 */
#ifndef CBCP_SUPPORT
#define CBCP_SUPPORT                    0
#endif

/**
 * ECP_SUPPORT==1：支持ECP。当前不支持！不要设置！
 */
#ifndef ECP_SUPPORT
#define ECP_SUPPORT                     0
#endif

/**
 * DEMAND_SUPPORT==1：支持按需拨号。当前不支持！不要设置！
 */
#ifndef DEMAND_SUPPORT
#define DEMAND_SUPPORT                  0
#endif

/**
 * LQR_SUPPORT==1：支持链路质量报告。除了交换一些LCP数据包外，什么都不做。
 */
#ifndef LQR_SUPPORT
#define LQR_SUPPORT                     0
#endif

/**
 * PPP_SERVER==1：启用PPP服务器支持（等待传入的PPP会话）。
 *
 * 目前仅支持PPPoS。
 */
#ifndef PPP_SERVER
#define PPP_SERVER                      0
#endif

#if PPP_SERVER
/*
 * PPP_OUR_NAME：我们的名称用于身份验证
 */
#ifndef PPP_OUR_NAME
#define PPP_OUR_NAME                    "lwIP"
#endif
#endif /* PPP_SERVER */

/**
 * VJ_SUPPORT==1：支持VJ标头压缩。
 */
#ifndef VJ_SUPPORT
#define VJ_SUPPORT                      1
#endif
/* VJ压缩仅支持TCP over IPv4 over PPPoS。*/
#if !PPPOS_SUPPORT || !PPP_IPV4_SUPPORT || !LWIP_TCP
#undef VJ_SUPPORT
#define VJ_SUPPORT                      0
#endif /* !PPPOS_SUPPORT */

/**
 * PPP_MD5_RANDM==1：使用MD5获得更好的随机性。如果启用了CHAP、EAP或L2TP AUTH支持，则默认启用。
 */
#ifndef PPP_MD5_RANDM
#define PPP_MD5_RANDM                   (CHAP_SUPPORT || EAP_SUPPORT || PPPOL2TP_AUTH_SUPPORT)
#endif

/**
 * PolarSSL嵌入式库
 *
 * lwIP包含从PolarSSL项目的最新BSD版本（PolarSSL 0.10.1-BSD）中提取的一些文件，用于lwIP PPP支持所需的密码和加密方法。
 *
 * PolarSSL文件已清理，仅包含lwIP所需的必要结构字段和函数。
 *
 * PolarSSL API完全没有更改，因此如果您已经在使用PolarSSL，您可以选择跳过将包含的PolarSSL库编译为lwIP。
 *
 * 如果不使用嵌入式副本，则必须在arch/cc中包含外部库。h端口文件。
 *
 * 如果您不使用我们干净的PolarSSL库，请注意堆栈需求可能会大得多。
 */

/**
 * LWIP_USE_EXTERNAL_POLRSSL：使用外部POLARSSL库
 */
#ifndef LWIP_USE_EXTERNAL_POLARSSL
#define LWIP_USE_EXTERNAL_POLARSSL      0
#endif

/**
 * LWIP_USE_EXTERNAL_MBEDTLS:使用外部mbed TLS库
 */
#ifndef LWIP_USE_EXTERNAL_MBEDTLS
#define LWIP_USE_EXTERNAL_MBEDTLS       0
#endif

/*
 * PPP超时
 */

/**
 * FSM_DEFTIMEOUT：超时时间（秒）
 */
#ifndef FSM_DEFTIMEOUT
#define FSM_DEFTIMEOUT                  6
#endif

/**
 * FSM_DEFMAXTERMREQS：最大终止请求传输
 */
#ifndef FSM_DEFMAXTERMREQS
#define FSM_DEFMAXTERMREQS              2
#endif

/**
 * FSM_DEFMAXCONFREQS:最大配置请求传输
 */
#ifndef FSM_DEFMAXCONFREQS
#define FSM_DEFMAXCONFREQS              10
#endif

/**
 * FSM_DEFMAXNAKLOOPS：nak循环的最大数量
 */
#ifndef FSM_DEFMAXNAKLOOPS
#define FSM_DEFMAXNAKLOOPS              5
#endif

/**
 * UPAP_DEFTIMEOUT：重传请求超时（秒）
 */
#ifndef UPAP_DEFTIMEOUT
#define UPAP_DEFTIMEOUT                 6
#endif

/**
 * UPAP_DEFTRANSMITS:要发送的身份验证请求的最大数量
 */
#ifndef UPAP_DEFTRANSMITS
#define UPAP_DEFTRANSMITS               10
#endif

#if PPP_SERVER
/**
 * UPAP_DEFREQTIME:等待来自对等方的身份验证请求的时间
 */
#ifndef UPAP_DEFREQTIME
#define UPAP_DEFREQTIME                 30
#endif
#endif /* PPP_SERVER */

/**
 * CHAP_DEFTIMEOUT：重传请求超时（秒）
 */
#ifndef CHAP_DEFTIMEOUT
#define CHAP_DEFTIMEOUT                 6
#endif

/**
 * CHAP_DEFTRANSMISS：发送质询的最大次数
 */
#ifndef CHAP_DEFTRANSMITS
#define CHAP_DEFTRANSMITS               10
#endif

#if PPP_SERVER
/**
 * CHAP_DEFRECHALLENGETIME：如果此选项大于0，则每n秒重新调用一次对等方
 */
#ifndef CHAP_DEFRECHALLENGETIME
#define CHAP_DEFRECHALLENGETIME         0
#endif
#endif /* PPP_SERVER */

/**
 * EAP_DEFREQTIME:等待对等请求的时间
 */
#ifndef EAP_DEFREQTIME
#define EAP_DEFREQTIME                  6
#endif

/**
 * EAP_DEFALLOWREQ:接受请求的最大次数
 */
#ifndef EAP_DEFALLOWREQ
#define EAP_DEFALLOWREQ                 10
#endif

#if PPP_SERVER
/**
 * EAP_DEFTIMEOUT：rexmit超时（秒）
 */
#ifndef EAP_DEFTIMEOUT
#define EAP_DEFTIMEOUT                  6
#endif

/**
 * EAP_DEFTRANSMISS：发送的最大次数
 */
#ifndef EAP_DEFTRANSMITS
#define EAP_DEFTRANSMITS                10
#endif
#endif /* PPP_SERVER */

/**
 * LCP_DEFLOOPACKFAIL：在决定链接被环回之前，我们从对等端收到魔法数字的默认次数。
 */
#ifndef LCP_DEFLOOPBACKFAIL
#define LCP_DEFLOOPBACKFAIL             10
#endif

/**
 * LCP_ECHOINTERVAL：保活回显请求之间的间隔（秒），0表示禁用。
 */
#ifndef LCP_ECHOINTERVAL
#define LCP_ECHOINTERVAL                0
#endif

/**
 * LCP_MAXECHOFAILS：失败前未应答的回显请求数。
 */
#ifndef LCP_MAXECHOFAILS
#define LCP_MAXECHOFAILS                3
#endif

/**
 * PPP_MAXIDLEFLAG：重新发送标志字符之前的最大Xmit空闲时间（毫秒）。
 */
#ifndef PPP_MAXIDLEFLAG
#define PPP_MAXIDLEFLAG                 100
#endif

/**
 * PPP数据包大小
 */

/**
 * PPP_MRU：默认MRU
 */
#ifndef PPP_MRU
#define PPP_MRU                         1500
#endif

/**
 * PPP_DEFMRU：要尝试的默认MRU
 */
#ifndef PPP_DEFMRU
#define PPP_DEFMRU                      1500
#endif

/**
 * PPP_MAXMRU：通常将MRU限制为该值（pppd默认值=16384）
 */
#ifndef PPP_MAXMRU
#define PPP_MAXMRU                      1500
#endif

/**
 * PPP_MINMRU：以下无MRU
 */
#ifndef PPP_MINMRU
#define PPP_MINMRU                      128
#endif

/**
 * PPPOL2TP_DEFMRU：L2TP的默认MTU和MRU默认值=1500-PPPoE（6）-PPP协议（2）-IPv4报头（20）-UDP报头（8）
 * -L2TP报头（6）-HDLC报头（2）-PPP协议（2）-MPPE报头（2
 */
#if PPPOL2TP_SUPPORT
#ifndef PPPOL2TP_DEFMRU
#define PPPOL2TP_DEFMRU                 1450
#endif
#endif /* PPPOL2TP_SUPPORT */

/**
 * MAXNAMELEN:身份验证的主机名或名称的最大长度
 */
#ifndef MAXNAMELEN
#define MAXNAMELEN                      256
#endif

/**
 * MAXSECRETLEN：密码或密码的最大长度
 */
#ifndef MAXSECRETLEN
#define MAXSECRETLEN                    256
#endif

/* ------------------------------------------------------------------------- */

/*
 * 为嵌入式PolarSSL生成触发器
 */
#if !LWIP_USE_EXTERNAL_POLARSSL && !LWIP_USE_EXTERNAL_MBEDTLS

/* CHAP、EAP、L2TP AUTH和MD5 Random需要MD5支持*/
#if CHAP_SUPPORT || EAP_SUPPORT || PPPOL2TP_AUTH_SUPPORT || PPP_MD5_RANDM
#define LWIP_INCLUDED_POLARSSL_MD5      1
#endif /* CHAP_SUPPORT || EAP_SUPPORT || PPPOL2TP_AUTH_SUPPORT || PPP_MD5_RANDM */

#if MSCHAP_SUPPORT

/* MSCHAP需要MD4支持*/
#define LWIP_INCLUDED_POLARSSL_MD4      1
/* MSCHAP需要SHA1支持*/
#define LWIP_INCLUDED_POLARSSL_SHA1     1
/* MSCHAP需要DES支持*/
#define LWIP_INCLUDED_POLARSSL_DES      1

/* MPPE需要MS-CHAP支持*/
#if MPPE_SUPPORT
/* MPPE需要ARC4支持*/
#define LWIP_INCLUDED_POLARSSL_ARC4     1
#endif /* MPPE_SUPPORT */

#endif /* MSCHAP_SUPPORT */

#endif /* !LWIP_USE_EXTERNAL_POLARSSL && !LWIP_USE_EXTERNAL_MBEDTLS */

/* 默认值（如果未设置）*/
#ifndef LWIP_INCLUDED_POLARSSL_MD4
#define LWIP_INCLUDED_POLARSSL_MD4      0
#endif /* LWIP_INCLUDED_POLARSSL_MD4 */
#ifndef LWIP_INCLUDED_POLARSSL_MD5
#define LWIP_INCLUDED_POLARSSL_MD5      0
#endif /* LWIP_INCLUDED_POLARSSL_MD5 */
#ifndef LWIP_INCLUDED_POLARSSL_SHA1
#define LWIP_INCLUDED_POLARSSL_SHA1     0
#endif /* LWIP_INCLUDED_POLARSSL_SHA1 */
#ifndef LWIP_INCLUDED_POLARSSL_DES
#define LWIP_INCLUDED_POLARSSL_DES      0
#endif /* LWIP_INCLUDED_POLARSSL_DES */
#ifndef LWIP_INCLUDED_POLARSSL_ARC4
#define LWIP_INCLUDED_POLARSSL_ARC4     0
#endif /* LWIP_INCLUDED_POLARSSL_ARC4 */

#endif /* PPP_SUPPORT */

/* 默认值（如果未设置）*/
#ifndef PPP_NUM_TIMEOUTS
#define PPP_NUM_TIMEOUTS                0
#endif /* PPP_NUM_TIMEOUTS */

#endif /* LWIP_PPP_OPTS_H */

