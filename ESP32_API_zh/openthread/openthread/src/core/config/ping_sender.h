/*
 *  版权所有（c）2021，The OpenThread Authors。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file 此文件包括ping发送器模块的编译时配置。
 *
 */

#ifndef CONFIG_PING_SENDER_H_
#define CONFIG_PING_SENDER_H_

/**
 * @def OPENTHREAD_CONFIG_PING_SENDER_ENABLE
 *
 * 定义为1以启用ping发送器模块。
 *
 * Ping发送方模块实现发送ICMPv6回显请求消息和处理ICMPv6回复消息。
 *
 */
#ifndef OPENTHREAD_CONFIG_PING_SENDER_ENABLE
#define OPENTHREAD_CONFIG_PING_SENDER_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_PING_SENDER_DEFAULT_INTEVRAL
 *
 * 指定默认ping间隔（发送回显请求之间的时间）（以毫秒为单位）。
 *
 */
#ifndef OPENTHREAD_CONFIG_PING_SENDER_DEFAULT_INTEVRAL
#define OPENTHREAD_CONFIG_PING_SENDER_DEFAULT_INTEVRAL 1000
#endif

/**
 * @def OPENTHREAD_CONFIG_PING_SENDER_DEFAULT_DEADLINE
 *
 * 指定默认ping超时（毫秒）。超时是每个ping请求与其回复之间的最大可接受时间间隔。
 *
 */
#ifndef OPENTHREAD_CONFIG_PING_SENDER_DEFAULT_TIMEOUT
#define OPENTHREAD_CONFIG_PING_SENDER_DEFAULT_TIMEOUT 3000
#endif

/**
 * @def OPENTHREAD_CONFIG_PING_SENDER_DEFAULT_SIZE
 *
 * 指定默认ping数据大小（字节）。数据大小指定回音请求数据有效载荷，其中不包括IPv6和ICMPv6标头。
 *
 */
#ifndef OPENTHREAD_CONFIG_PING_SENDER_DEFAULT_SIZE
#define OPENTHREAD_CONFIG_PING_SENDER_DEFAULT_SIZE 8
#endif

/**
 * @def OPENTHREAD_CONFIG_PING_SENDER_DEFAULT_COUNT
 *
 * 指定默认ping计数（要发送的ping消息数）。
 *
 */
#ifndef OPENTHREAD_CONFIG_PING_SENDER_DEFAULT_COUNT
#define OPENTHREAD_CONFIG_PING_SENDER_DEFAULT_COUNT 1
#endif

#endif // CONFIG_PING_SENDER_H_

