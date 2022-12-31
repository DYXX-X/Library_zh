/**
 * @file IANA分配的编号（RFC 1700及后续版本）
 *
 * @defgroup iana iana分配的号码
 * @ingroup 基础设施
 */

/*
 * 版权所有（c）2017 Dirk Ziegelmeier。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Dirk Ziegelmeier<dziegel@gmx.de>
 *
 */

#ifndef LWIP_HDR_PROT_IANA_H
#define LWIP_HDR_PROT_IANA_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @ingroup iana硬件类型
 */
enum lwip_iana_hwtype {
  /**以太网*/
  LWIP_IANA_HWTYPE_ETHERNET = 1
};

/**
 * @ingroup iana港口编号https://www.iana.org/assignments/service-names-port-numbers/service-names-port-numbers.txt
 */
enum lwip_iana_port_number {
  /** SMTP */
  LWIP_IANA_PORT_SMTP        = 25,
  /**DHCP服务器*/
  LWIP_IANA_PORT_DHCP_SERVER = 67,
  /**DHCP客户端*/
  LWIP_IANA_PORT_DHCP_CLIENT = 68,
  /** TFTP */
  LWIP_IANA_PORT_TFTP        = 69,
  /** HTTP */
  LWIP_IANA_PORT_HTTP        = 80,
  /** SNTP */
  LWIP_IANA_PORT_SNTP        = 123,
  /** NETBIOS */
  LWIP_IANA_PORT_NETBIOS     = 137,
  /** SNMP */
  LWIP_IANA_PORT_SNMP        = 161,
  /**SNMP陷阱*/
  LWIP_IANA_PORT_SNMP_TRAP   = 162,
  /** HTTPS */
  LWIP_IANA_PORT_HTTPS       = 443,
  /** SMTPS */
  LWIP_IANA_PORT_SMTPS       = 465,
  /** MQTT */
  LWIP_IANA_PORT_MQTT        = 1883,
  /** MDNS */
  LWIP_IANA_PORT_MDNS        = 5353,
  /**安全MQTT*/
  LWIP_IANA_PORT_SECURE_MQTT = 8883
};

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_PROT_IANA_H */

