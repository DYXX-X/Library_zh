/**
 * @file IEEE分配的编号
 *
 * @defgroup ieee ieee分配的编号
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

#ifndef LWIP_HDR_PROT_IEEE_H
#define LWIP_HDR_PROT_IEEE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @ingroup ieee经常使用ethtype的列表（尽管lwIP不使用所有类型）。
 */
enum lwip_ieee_eth_type {
  /**Internet协议v4*/
  ETHTYPE_IP        = 0x0800U,
  /**地址解析协议*/
  ETHTYPE_ARP       = 0x0806U, 
  /**唤醒局域网*/
  ETHTYPE_WOL       = 0x0842U,
  /** RARP */
  ETHTYPE_RARP      = 0x8035U,
  /**虚拟局域网*/
  ETHTYPE_VLAN      = 0x8100U,
  /**Internet协议v6*/
  ETHTYPE_IPV6      = 0x86DDU,
  /**以太网PPP发现阶段*/
  ETHTYPE_PPPOEDISC = 0x8863U,
  /**以太网PPP会话阶段*/
  ETHTYPE_PPPOE     = 0x8864U,
  /**巨型框架*/
  ETHTYPE_JUMBO     = 0x8870U,
  /**工艺现场网络*/
  ETHTYPE_PROFINET  = 0x8892U,
  /**以太网用于控制自动化技术*/
  ETHTYPE_ETHERCAT  = 0x88A4U,
  /**链路层发现协议*/
  ETHTYPE_LLDP      = 0x88CCU,
  /**串行实时通信系统*/
  ETHTYPE_SERCOS    = 0x88CDU,
  /**媒体冗余协议*/
  ETHTYPE_MRP       = 0x88E3U,
  /**精确时间协议*/
  ETHTYPE_PTP       = 0x88F7U,
  /**Q中Q，802.1ad*/
  ETHTYPE_QINQ      = 0x9100U
};

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_PROT_IEEE_H */

