/*
 *  版权所有（c）2019，The OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file 此文件包括边界路由器服务的编译时配置。
 *
 */

#ifndef CONFIG_BORDER_ROUTER_H_
#define CONFIG_BORDER_ROUTER_H_

/**
 * @def OPENTHREAD_CONFIG_BORDER_AGENT_ENABLE
 *
 * 定义为1以启用边界代理支持。
 *
 */
#ifndef OPENTHREAD_CONFIG_BORDER_AGENT_ENABLE
#define OPENTHREAD_CONFIG_BORDER_AGENT_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_BORDER_ROUTER_ENABLE
 *
 * 定义为1以启用边界路由器支持。
 *
 */
#ifndef OPENTHREAD_CONFIG_BORDER_ROUTER_ENABLE
#define OPENTHREAD_CONFIG_BORDER_ROUTER_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_BORDER_ROUTING_ENABLE
 *
 * 定义为1以启用边界路由支持。
 *
 */
#ifndef OPENTHREAD_CONFIG_BORDER_ROUTING_ENABLE
#define OPENTHREAD_CONFIG_BORDER_ROUTING_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_BORDER_AGENT_UDP_PORT
 *
 * 指定边界代理UDP端口，并将0用于临时端口。
 *
 */
#ifndef OPENTHREAD_CONFIG_BORDER_AGENT_UDP_PORT
#define OPENTHREAD_CONFIG_BORDER_AGENT_UDP_PORT 0
#endif

#endif // CONFIG_BORDER_ROUTER_H_

