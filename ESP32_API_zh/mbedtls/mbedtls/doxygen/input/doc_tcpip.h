/**
 * \文件doc_tcpip.h
 *
 * \简短的TCP/IP通信模块文档文件。
 */
/*
 * 版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

/**
 * @addtogroup tcpip_communication_module TCP/IP通信模块
 *
 * TCP/IP通信模块为\link ssltls_communication_module SSL/TLS通信模块\endlink提供了一个通信通道。在TCP/IP模型中，它提供了到传输（或主机到主机）层的通信。SSL/TLS位于应用层之上，并利用其基本规定：
 * -侦听端口（请参见\c mbedtls_net_bind（））。
 * -接受连接（通过\c mbedtls_net_accept（））。
 * -读/写（通过\c mbedtls_net_recv（）/\c mbedtls_net_send（））。
 * -关闭连接（通过\c mbedtls_net_close（））。
 *
 * 这样，您就可以实现并使用UDP或IPSec通信解决方案作为基础。
 *
 * 该模块可用于服务器端和客户端，以提供通过互联网进行通信的基本方式。
 */

