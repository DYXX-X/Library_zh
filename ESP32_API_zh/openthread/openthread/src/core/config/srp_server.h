/*
 *  版权所有（c）2020，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file 此文件包括SRP（服务注册协议）服务器的编译时配置。
 *
 */

#ifndef CONFIG_SRP_SERVER_H_
#define CONFIG_SRP_SERVER_H_

/**
 * @def OPENTHREAD_CONFIG_SRP_SERVER_ENABLE
 *
 * 定义为1以启用SRP服务器支持。
 *
 */
#ifndef OPENTHREAD_CONFIG_SRP_SERVER_ENABLE
#define OPENTHREAD_CONFIG_SRP_SERVER_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_SRP_SERVER_DEFAULT_ADDDRESS_MODE
 *
 * 指定SRP服务器使用的默认地址模式。
 *
 * 地址模式指定SRP服务器如何确定地址和端口号，以及如何在线程网络数据中发布此信息。
 *
 * 此配置的值应来自“otSrpServerAddressMode”枚举。
 *
 */
#ifndef OPENTHREAD_CONFIG_SRP_SERVER_DEFAULT_ADDDRESS_MODE
#define OPENTHREAD_CONFIG_SRP_SERVER_DEFAULT_ADDDRESS_MODE OT_SRP_SERVER_ADDRESS_MODE_UNICAST
#endif

/**
 * @def OPENTHREAD_CONFIG_SRP_SERVER_UDP_PORT_MIN
 *
 * 指定为SRP服务器保留的端口范围中的最小端口号。
 *
 */
#ifndef OPENTHREAD_CONFIG_SRP_SERVER_UDP_PORT_MIN
#define OPENTHREAD_CONFIG_SRP_SERVER_UDP_PORT_MIN 53535
#endif

/**
 * @def OPENTHREAD_CONFIG_SRP_SERVER_UDP_PORT_MAX
 *
 * 指定为SRP服务器保留的端口范围中的最大端口号。
 *
 */
#ifndef OPENTHREAD_CONFIG_SRP_SERVER_UDP_PORT_MAX
#define OPENTHREAD_CONFIG_SRP_SERVER_UDP_PORT_MAX 53554
#endif

/**
 * @def OPENTHREAD_CONFIG_SRP_SERVER_PORT_SWITCH_ENABLE
 *
 * 定义为1以启用SRP服务器功能，将其自己的端口保存在非易失性设置中。
 *
 * 启用后，SRP服务器将在非易失性设置中保存其端口。在服务器重新启动时（例如，由于设备重置），它将恢复端口并更改为其他端口。由于收到SRP更新，第一个服务注册后，信息将写入设置。
 *
 */
#ifndef OPENTHREAD_CONFIG_SRP_SERVER_PORT_SWITCH_ENABLE
#define OPENTHREAD_CONFIG_SRP_SERVER_PORT_SWITCH_ENABLE 1
#endif

/**
 * @def OPENTHREAD_CONFIG_SRP_SERVER_SERVICE_UPDATE_TIMEOUT
 *
 * 指定服务更新处理程序的超时值（以毫秒为单位）。
 *
 * 默认超时值是最大总mDNS探测延迟和250毫秒的松散IPC超时之和。如果使用广告代理处理服务更新事件，建议此配置不应使用小于此处默认值的值。
 *
 */
#ifndef OPENTHREAD_CONFIG_SRP_SERVER_SERVICE_UPDATE_TIMEOUT
#define OPENTHREAD_CONFIG_SRP_SERVER_SERVICE_UPDATE_TIMEOUT ((4 * 250u) + 250u)
#endif

/**
 * @def OPENTHREAD_CONFIG_SRP_SERVER_MAX_ADDRESSES_NUM
 *
 * 指定SRP服务器可以为主机处理的最大地址数。
 *
 */
#ifndef OPENTHREAD_CONFIG_SRP_SERVER_MAX_ADDRESSES_NUM
#define OPENTHREAD_CONFIG_SRP_SERVER_MAX_ADDRESSES_NUM 2
#endif

#endif // CONFIG_SRP_SERVER_H_

