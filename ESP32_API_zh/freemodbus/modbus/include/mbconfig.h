/*
 * FreeModbus库：Modbus ASCII/RTU的便携式Modbus实现。版权所有（c）2006 Christian Walter<wolti@sil.at>保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 文件：$Id:mbconfig。h、 v 1.15 2010/06/06 13:54:40 wolti Exp$$Id:mbconfig。h、 v 1.60 2013/08/13 21:19:55 Armink添加主功能$
 */

#ifndef _MB_CONFIG_H
#define _MB_CONFIG_H

#include "sdkconfig.h" // 对于KConfig选项

#ifdef __cplusplus
PR_BEGIN_EXTERN_C
#endif
/* -----------------------定义------------------------------------------*/
/*! \defgroup modbus_cfg modbus配置
 *
 * 协议栈中的大多数模块都是完全可选的，可以排除。如果目标资源非常小，需要节省程序内存空间，这一点尤为重要。<br>
 *
 * 所有这些设置都可以在文件<code>mbconfig.h</code>中找到
 */
/*! \添加组modbus_cfg@{
 */
/*! \brief如果启用Modbus Master ASCII支持。*/
#define MB_MASTER_ASCII_ENABLED                 (  CONFIG_FMB_COMM_MODE_ASCII_EN )
/*! \brief如果启用Modbus主RTU支持。*/
#define MB_MASTER_RTU_ENABLED                   (  CONFIG_FMB_COMM_MODE_RTU_EN )
/*! \brief如果启用Modbus Master TCP支持。*/
#define MB_MASTER_TCP_ENABLED                   (  CONFIG_FMB_COMM_MODE_TCP_EN )
/*! \brief如果启用Modbus从站ASCII支持。*/
#define MB_SLAVE_ASCII_ENABLED                  (  CONFIG_FMB_COMM_MODE_ASCII_EN )
/*! \brief如果启用Modbus从RTU支持。*/
#define MB_SLAVE_RTU_ENABLED                    (  CONFIG_FMB_COMM_MODE_RTU_EN )
/*! \brief如果启用Modbus从TCP支持。*/
#define MB_TCP_ENABLED                          (  CONFIG_FMB_COMM_MODE_TCP_EN )

#if !CONFIG_FMB_COMM_MODE_ASCII_EN && !CONFIG_FMB_COMM_MODE_RTU_EN && !MB_MASTER_TCP_ENABLED && !MB_TCP_ENABLED
#error "None of Modbus communication mode is enabled. Please enable one of (ASCII, RTU, TCP) mode in Kconfig."
#endif

/*! \brief此选项定义每个ASCII字符的数据位数。
 *
 * 在停止位之前添加一个奇偶校验位，使实际字节大小保持在10位。
 */
#ifdef CONFIG_FMB_SERIAL_ASCII_BITS_PER_SYMB
#define MB_ASCII_BITS_PER_SYMB                  (  CONFIG_FMB_SERIAL_ASCII_BITS_PER_SYMB )
#endif

/*! \brief Modbus ASCII的字符超时值。
 *
 * Modbus ASCII的字符超时值不是固定的，因此是一个配置选项。应将其设置为网络的最大预期延迟时间。
 */
#ifdef CONFIG_FMB_SERIAL_ASCII_TIMEOUT_RESPOND_MS
#define MB_ASCII_TIMEOUT_MS                     (  CONFIG_FMB_SERIAL_ASCII_TIMEOUT_RESPOND_MS )
#endif

/*! \在启用发射器之前，在ASCII中等待的短暂超时。
 *
 * 如果已定义，则函数使用参数MB_ASCII_TIMEOUT_WAIT_BEFORE_SEND_MS调用vMBPortSerialDelay，以允许在启用串行发射器之前进行延迟。这是必需的，因为一些目标速度太快，以至于在接收和发送帧之间没有时间。如果主设备在启用其接收器时变慢，那么他将无法正确接收响应。
 */
#ifndef MB_ASCII_TIMEOUT_WAIT_BEFORE_SEND_MS
#define MB_ASCII_TIMEOUT_WAIT_BEFORE_SEND_MS    ( 0 )
#endif

/*! \brief协议栈应支持的Modbus功能代码的最大数量。
 *
 * 支持的Modbus函数的最大数量必须大于此文件中所有已启用函数和自定义函数处理程序的总和。如果设置为小，添加更多功能将失败。
 */
#define MB_FUNC_HANDLERS_MAX                    ( 16 )

/*! \brief应分配给<em>报告从属ID</em>命令的字节数。
 *
 * 此数字限制报告从属id函数中附加段的最大大小。有关如何设置此值的详细信息，请参见eMBSetSlaveID（）。仅当MB_FUNC_OTHER_REP_SLAVEID_ENABLED设置为<code>1</code>时使用。
 */
#define MB_FUNC_OTHER_REP_SLAVEID_BUF           ( 32 )

/*! \brief如果应启用<em>报告从属ID</em>功能。*/
#define MB_FUNC_OTHER_REP_SLAVEID_ENABLED       (  CONFIG_FMB_CONTROLLER_SLAVE_ID_SUPPORT )

/*! \brief如果应启用<em>读取输入寄存器</em>功能。*/
#define MB_FUNC_READ_INPUT_ENABLED              (  1 )

/*! \brief如果应启用<em>读取保持寄存器</em>功能。*/
#define MB_FUNC_READ_HOLDING_ENABLED            (  1 )

/*! \brief如果应启用<em>写入单寄存器</em>功能。*/
#define MB_FUNC_WRITE_HOLDING_ENABLED           (  1 )

/*! \brief如果应启用<em>写入多个寄存器</em>功能。*/
#define MB_FUNC_WRITE_MULTIPLE_HOLDING_ENABLED  (  1 )

/*! \brief如果应启用<em>读取线圈</em>功能。*/
#define MB_FUNC_READ_COILS_ENABLED              (  1 )

/*! \brief如果应启用<em>写入线圈</em>功能。*/
#define MB_FUNC_WRITE_COIL_ENABLED              (  1 )

/*! \brief如果应启用<em>写入多个线圈</em>功能。*/
#define MB_FUNC_WRITE_MULTIPLE_COILS_ENABLED    (  1 )

/*! \brief如果应启用<em>读取离散输入</em>功能。*/
#define MB_FUNC_READ_DISCRETE_INPUTS_ENABLED    (  1 )

/*! \brief如果应启用<em>读/写多个寄存器</em>功能。*/
#define MB_FUNC_READWRITE_HOLDING_ENABLED       (  1 )

/*! \brief选中将计时器处理程序放入IRAM的选项*/
#define MB_PORT_TIMER_ISR_IN_IRAM               (  CONFIG_FMB_TIMER_ISR_IN_IRAM )

/*! @} */
#ifdef __cplusplus
    PR_END_EXTERN_C
#endif

#if MB_MASTER_RTU_ENABLED || MB_MASTER_ASCII_ENABLED || MB_MASTER_TCP_ENABLED
/*! \如果主机发送广播帧，主机将等待转换到延迟的时间，然后主机可以发送其他帧*/
#define MB_MASTER_DELAY_MS_CONVERT              ( CONFIG_FMB_MASTER_DELAY_MS_CONVERT )
/*! \如果主设备发送了一个未广播的帧，主设备将等待一段时间等待从属设备。如果从设备在此时间内没有响应，则主设备将处理此超时错误。然后主机可以发送其他帧*/
#define MB_MASTER_TIMEOUT_MS_RESPOND            ( CONFIG_FMB_MASTER_TIMEOUT_MS_RESPOND )
/*! \简要介绍Modbus Master系统中的总从站。\注意：从属ID必须从1开始连续。*/
#define MB_MASTER_TOTAL_SLAVE_NUM               ( 247 )
#endif

#endif

