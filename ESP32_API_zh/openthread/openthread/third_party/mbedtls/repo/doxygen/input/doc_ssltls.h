/**
 * \文件doc_ssltls.h
 *
 * \简短的SSL/TLS通信模块文档文件。
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
 * @addtogroup ssltls_communication_module SSL/TLS通信模块
 *
 * SSL/TLS通信模块提供了创建SSL/TLS通讯通道的方法。
 *
 * 基本规定如下：
 * -初始化SSL/TLS上下文（请参见\c mbedtls_SSL_init（））。
 * -执行SSL/TLS握手（请参见\c mbedtls_SSL_handshake（））。
 * -读/写（请参见\c mbedtls_ssl_read（）和\c mbedt ls_ssl_write（））。
 * -通知对等方连接正在关闭（请参阅\c mbedtls_ssl_close_notify（））。
 *
 * 这种通道的许多方面都是通过参数和回调函数设置的：
 * -端点角色：客户端或服务器。
 * -认证模式。如果进行验证。
 * -主机到主机通信信道。提供了TCP/IP模块。
 * -随机数发生器（RNG）。
 * -用于加密/解密的密码。
 * -会话控制功能。
 * -证书处理和密钥交换的X.509参数。
 *
 * 此模块可用于创建SSL/TLS服务器和客户端，并提供通过SSL/TLS通信通道进行设置和通信的基本框架。\n请注意，如上所述，您需要自己提供几个方面。
 */

