/**
 * \文件doc_mainpage.h
 *
 * \简要主页文档文件。
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
 * @mainpage mbed TLS v2.25.0源代码文档
 *
 * 本文档描述了mbed TLS的内部结构。它是使用Doxygen从mbed-TLS源代码中特殊格式化的注释块自动生成的。（参见http://www.stack.nl/~ dimitri/doxygen/了解更多关于doxygen的信息）
 *
 * mbed-TLS有一个简单的设置：它为SSL/TLS实现提供了要素。这些成分在\ref mainpage_modules“模块部分”中作为模块列出。本“模块部分”介绍了本文档中使用的高级模块概念。\n mbed TLS用法的一些示例可以在\ref mainpage_examples“examples section”中找到。
 *
 * @section mainpage_modules模块
 *
 * mbed TLS通过提供以下功能支持SSLv3至TLSv1.2通信：
 * -TCP/IP通信功能：监听、连接、接受、读/写。
 * -SSL/TLS通信功能：初始化、握手、读/写。
 * -X.509功能：CRT、CRL和密钥处理
 * -随机数生成
 * -哈希
 * -加密/解密
 *
 * 上述功能被整齐地划分为逻辑接口。它们可以单独用于提供任何上述功能，或混合和匹配到使用X.509 PKI的SSL服务器/客户端解决方案中。源代码中充分提供了此类实现的示例。
 *
 * 注意，mbed TLS不提供控制通道或（多个）会话处理，而无需开发人员的额外工作。
 *
 * @section mainpage_examples示例
 *
 * 服务器设置示例：
 *
 * \b前提条件：
 * -X.509证书和私钥
 * -会话处理功能
 *
 * \b设置：
 * -加载证书和专用RSA密钥（X.509接口）
 * -设置侦听TCP套接字（TCP/IP接口）
 * -接受传入客户端连接（TCP/IP接口）
 * -初始化为SSL服务器（SSL/TLS接口）
 *   -设置参数，例如身份验证、密码、CA链、密钥交换
 *   -设置回调函数RNG、IO、会话处理
 * -执行SSL握手（SSL/TLS接口）
 * -读/写数据（SSL/TLS接口）
 * -关闭和清理（所有接口）
 *
 * 客户端设置示例：
 *
 * \b前提条件：
 * -X.509证书和私钥
 * -X.509受信任的CA证书
 *
 * \b设置：
 * -加载受信任的CA证书（X.509接口）
 * -加载证书和专用RSA密钥（X.509接口）
 * -设置TCP/IP连接（TCP/IP接口）
 * -初始化为SSL客户端（SSL/TLS接口）
 *   -设置参数，例如身份验证模式、密码、CA链、会话
 *   -设置回调函数RNG、IO
 * -执行SSL握手（SSL/TLS接口）
 * -验证服务器证书（SSL/TLS接口）
 * -写入/读取数据（SSL/TLS接口）
 * -关闭和清理（所有接口）
 */

