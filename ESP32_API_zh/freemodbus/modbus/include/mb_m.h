/*
 * FreeModbus库：Modbus ASCII/RTU的便携式Modbus实现。版权所有（C）2013 Armink<armink.ztl@gmail.com>保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 文件：$Id:mb_m.h，v 1.60 2013/09/03 10:20:05 Armink添加主功能$
 */

#ifndef _MB_M_H
#define _MB_M_H

#include "mbconfig.h"
#include "port.h"
#include "mb.h"

#ifdef __cplusplus
PR_BEGIN_EXTERN_C
#endif

#include "mbport.h"
#include "mbproto.h"
/*! \defgroup modbus modbus\code#包含“mb.h”\endcode
 *
 * 此模块定义应用程序的接口。它包含使用Modbus主协议栈所需的基本功能和类型。典型的应用程序需要首先调用eMBMasterInit（）。如果设备准备好响应网络请求，则必须调用eMBEnable（）来激活协议堆栈。在主循环中，必须定期调用函数eMBMasterPoll（）。池之间的时间间隔取决于配置的Modbus超时。如果RTOS可用，则应创建单独的任务，并且该任务应始终调用函数eMBMasterPoll（）。
 *
 * \code//在RTU模式下初始化主eBMasterInit（MB_RTU，38400，MB_PAR_EVEN）的协议栈；//启用Modbus协议堆栈。eMBMasterEnable（）；for（；；）｛//调用Modbus主协议栈的主轮询循环。eMBMasterPoll（）；…｝\endcode
 */

/* -----------------------定义------------------------------------------*/

/*! \ingroup modbus\sbrief使用默认modbus主TCP端口（502）
 */
#define MB_MASTER_TCP_PORT_USE_DEFAULT 0

/*! \ingroup modbus\主请求中所有函数使用的简要错误代码。
 */
typedef enum
{
    MB_MRE_NO_ERR,                  /*!< 没有错误。*/
    MB_MRE_NO_REG,                  /*!< 非法注册地址。*/
    MB_MRE_ILL_ARG,                 /*!< 非法参数。*/
    MB_MRE_REV_DATA,                /*!< 接收数据错误。*/
    MB_MRE_TIMEDOUT,                /*!< 发生超时错误。*/
    MB_MRE_MASTER_BUSY,             /*!< 主人现在很忙。*/
    MB_MRE_EXE_FUN                  /*!< 执行函数错误。*/
} eMBMasterReqErrCode;

/*! \ingroup modbus\brief TimerMode是主3种定时器模式。
 */
typedef enum
{
	MB_TMODE_T35,                   /*!< 主接收帧T3.5超时。*/
	MB_TMODE_RESPOND_TIMEOUT,       /*!< 主机等待响应从机。*/
	MB_TMODE_CONVERT_DELAY          /*!< Master发送了广播，然后延迟了一段时间。*/
}eMBMasterTimerMode;

/* -----------------------功能原型------------------------------*/
/*! \ingroup modbus\sbrief初始化modbus主协议栈。
 *
 * 该函数初始化ASCII或RTU模块，并调用移植层的init函数来准备硬件。请注意，接收器仍处于禁用状态，在调用eMBMasterEnable（）之前，不会处理任何Modbus帧。
 *
 * \param eMode如果应使用ASCII或RTU模式。\param ucPort要使用的端口。E、 g.1个用于窗口上的COM1。此值取决于平台，某些端口只选择忽略它。\param ulBaudRate波特率。E、 g.19200.支持的波特率取决于端口层。\param用于串行传输的eParity Parity。
 *
 * \return如果没有发生错误，函数将返回eMBErrorCode:：MB_ENOERR。然后，该协议处于禁用状态，可以通过调用eMBMasterEnable（）来激活。否则将返回以下错误代码之一：
 *    -eMBErrorCode:：MB_EPORTERR如果移植层返回错误。
 */
eMBErrorCode    eMBMasterSerialInit( eMBMode eMode, UCHAR ucPort,
		                 ULONG ulBaudRate, eMBParity eParity );

/*! \ingroup modbus\sbrief初始化modbus TCP的modbus主协议栈。
 *
 * 此功能初始化Modbus TCP模块。请注意，在调用eMBEnable（）之前，帧处理仍被禁用。
 *
 * \param usTCPPort要侦听的TCP端口。\return如果协议堆栈已正确初始化，则函数返回eMBErrorCode:：MB_ENOERR。否则将返回以下错误代码之一：
 *    -eMBErrorCode:：MB_EINVAL如果从属地址无效。有效的从属地址范围为1-247。
 *    -eMBErrorCode:：MB_EPORTERR如果移植层返回错误。
 */
eMBErrorCode    eMBMasterTCPInit( USHORT usTCPPort );

/*! \ingroup modbus\brief释放协议栈使用的资源。
 *
 * 此功能禁用Modbus主协议栈并释放所有硬件资源。只有在禁用协议堆栈时才能调用它。
 *
 * \注意：所有端口都实现此功能。想要获取回调的端口必须将宏MB_port_HAS_CLOSE定义为1。
 *
 * \return如果释放的资源返回eMBErrorCode:：MB_ENOERR。如果协议堆栈未处于禁用状态，则返回eMBErrorCode:：MB_EILLSTATE。
 */
eMBErrorCode    eMBMasterClose( void );

/*! \ingroup modbus\sbrief启用modbus主协议栈。
 *
 * 该功能可处理Modbus主帧。只有当协议堆栈处于禁用状态时，才能启用协议堆栈。
 *
 * \return如果协议栈现在处于启用状态，则返回eMBErrorCode:：MB_ENOERR。如果未处于禁用状态，则返回eMBErrorCode:：MB_EILLSTATE。
 */
eMBErrorCode    eMBMasterEnable( void );

/*! \ingroup modbus\sbrief禁用modbus主协议栈。
 *
 * 此功能禁用Modbus帧的处理。
 *
 * \return如果协议堆栈已禁用，则返回eMBErrorCode:：MB_ENOERR。如果未处于启用状态，则返回eMBErrorCode:：MB_EILLSTATE。
 */
eMBErrorCode    eMBMasterDisable( void );

/*! \ingroup modbus\brief modbus主协议栈的主池环路。
 *
 * 必须定期调用此函数。所需的计时器间隔由依赖于应用程序的Modbus从站超时给出。在内部，该函数调用xMBMasterPortEventGet（）并等待来自接收器或发射器状态机的事件。
 *
 * \return如果协议堆栈未处于启用状态，则函数返回eMBErrorCode:：MB_EILLSTATE。否则返回eMBErrorCode:：MB_ENOERR。
 */
eMBErrorCode    eMBMasterPoll( void );

/*! \ingroup modbus\brief为给定函数代码注册回调处理程序。
 *
 * 此函数为给定的函数代码注册新的回调处理程序。提供的回调处理程序负责解释Modbus PDU并创建适当的响应。如果出现错误，它应该返回一个可能的Modbus异常，这会导致协议栈发送Modbus异常帧。
 *
 * \param ucFunctionCode此处理程序应注册的Modbus功能代码。有效的函数代码在1到127的范围内。\param pxHandler在收到此类帧时应调用的函数处理程序。如果\c为NULL，则删除此函数代码以前注册的函数处理程序。
 *
 * \如果已安装处理程序，则返回eMBErrorCode:：MB_ENOERR。如果没有更多资源可用，则返回eMBErrorCode:：MB_ENORES。在本例中，mbconfig。h应进行调整。如果参数无效，则返回eMBErrorCode:：MB_EINVAL。
 */
eMBErrorCode    eMBMasterRegisterCB( UCHAR ucFunctionCode,
                               pxMBFunctionHandler pxHandler );

/* -----------------------回调-----------------------------------------*/

/*! \defgroup modbus_master registers modbus registers\code#include“mb_m.h”\endcode协议栈不在内部为寄存器分配任何内存。这使得协议栈非常小，也可用于低端目标。此外，这些值不必存储在存储器中，例如可以存储在闪存中<br>每当协议栈需要一个值时，它就会调用一个回调函数，将寄存器地址和要读取的寄存器数作为参数。然后，应用程序应读取实际寄存器值（例如ADC电压），并将结果存储在提供的缓冲器中<br>如果协议栈因为接收到写寄存器函数而想要更新寄存器值，则会将带有新寄存器值的缓冲区传递给回调函数。然后，函数应使用这些值更新应用程序寄存器值。
 */

/*! \ingroup modbus_registers \如果协议栈需要＜em＞输入寄存器＜/em＞的值，则使用简短回调函数。起始寄存器地址由\c usAddress给出，最后一个寄存器由<tt>usAddress+usNRegs-1</tt>给出。
 *
 * \param pucRegBuffer回调函数应将modbus寄存器的当前值写入的缓冲区。\param usAddress寄存器的起始地址。输入寄存器的范围为1-65535。\param usNRegs回调函数必须提供的寄存器数。
 *
 * \return函数必须返回以下错误代码之一：
 *   -eMBErrorCode:：MB_ENOERR如果没有发生错误。在这种情况下，发送正常的Modbus响应。
 *   -eMBErrorCode:：MB_ENOREG如果应用程序未在请求的地址范围内映射线圈。在这种情况下，<b>非法数据地址</b>作为响应发送。
 */
eMBErrorCode eMBMasterRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress,
		USHORT usNRegs );

/*! \ingroup modbus_registers \如果协议栈读取或写入<em>保持寄存器</em>值，则使用简短回调函数。起始寄存器地址由\c usAddress给出，最后一个寄存器由<tt>usAddress+usNRegs-1</tt>给出。
 *
 * \param pucRegBuffer如果应更新应用程序寄存器值，则缓冲区指向新的寄存器值。如果协议栈现在需要当前值，回调函数应将其写入此缓冲区。\param usAddress寄存器的起始地址。\param usNRegs要读取或写入的寄存器数。\param eMode如果eMBRegisterMode:：MB_REG_WRITE，应用程序寄存器值应根据缓冲区中的值进行更新。例如，当Modbus主机发出＜b＞WRITE SINGLE REGISTER（写入单寄存器）＜/b＞命令时，就是这种情况。如果值eMBRegisterMode:：MB_REG_READ，应用程序应将当前值复制到缓冲区中。
 *
 * \return函数必须返回以下错误代码之一：
 *   -eMBErrorCode:：MB_ENOERR如果没有发生错误。在这种情况下，发送正常的Modbus响应。
 *   -eMBErrorCode:：MB_ENOREG如果应用程序未在请求的地址范围内映射线圈。在这种情况下，<b>非法数据地址</b>作为响应发送。
 */
eMBErrorCode eMBMasterRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress,
		USHORT usNRegs, eMBRegisterMode eMode );

/*! \ingroup modbus_registers \如果协议栈读取或写入<em>线圈寄存器</em>值，则使用简短回调函数。如果要使用此函数，可以使用函数xMBUtilSetBits（）和xMBUtilGetBits（。
 *
 * \param pucRegBuffer位以字节为单位，其中从地址\cusAddress开始的第一个线圈存储在缓冲区中第一个字节的LSB中。如果缓冲区应由回调函数写入，则未使用的线圈值（即，如果未使用八个线圈的倍数）应设置为零。\param usAddress第一个线圈编号。\param usNCoils请求的线圈值数量。\param eMode如果eMBRegisterMode:：MB_REG_WRITE，应用程序值应根据缓冲区pucRegBuffer中提供的值进行更新。如果eMBRegisterMode:：MB_REG_READ，应用程序应将当前值存储在缓冲区中。
 *
 * \return函数必须返回以下错误代码之一：
 *   -eMBErrorCode:：MB_ENOERR如果没有发生错误。在这种情况下，发送正常的Modbus响应。
 *   -eMBErrorCode:：MB_ENOREG如果应用程序未在请求的地址范围内映射线圈。在这种情况下，<b>非法数据地址</b>作为响应发送。
 */
eMBErrorCode eMBMasterRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress,
		USHORT usNCoils, eMBRegisterMode eMode );

/*! \ingroup modbus_registers \当协议栈读取＜em＞输入离散寄存器＜/em＞值时使用的简短回调函数。
 *
 * 如果要使用他的函数，可以使用函数xMBUtilSetBits（）和xMBUtilGetBits（。
 *
 * \param pucRegBuffer应使用当前线圈值更新缓冲区。从\c usAddress开始的第一个离散输入必须存储在缓冲区中第一个字节的LSB中。如果请求的数字不是8的倍数，则剩余的位应设置为零。\param usAddress第一个离散输入的起始地址。\param usNDiscrete离散输入值的数量。\return函数必须返回以下错误代码之一：
 *   -eMBErrorCode:：MB_ENOERR如果没有发生错误。在这种情况下，发送正常的Modbus响应。
 *   -eMBErrorCode:：MB_ENOREG如果应用程序未在请求的地址范围内映射线圈。在这种情况下，<b>非法数据地址</b>作为响应发送。
 */
eMBErrorCode eMBMasterRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress,
		USHORT usNDiscrete );

/*! \当modbus在主模式下运行时，用户会调用这些modbus功能。
 */
eMBMasterReqErrCode
eMBMasterReqReadInputRegister( UCHAR ucSndAddr, USHORT usRegAddr, USHORT usNRegs, LONG lTimeOut );
eMBMasterReqErrCode
eMBMasterReqWriteHoldingRegister( UCHAR ucSndAddr, USHORT usRegAddr, USHORT usRegData, LONG lTimeOut );
eMBMasterReqErrCode
eMBMasterReqWriteMultipleHoldingRegister( UCHAR ucSndAddr, USHORT usRegAddr,
		USHORT usNRegs, USHORT * pusDataBuffer, LONG lTimeOut );
eMBMasterReqErrCode
eMBMasterReqReadHoldingRegister( UCHAR ucSndAddr, USHORT usRegAddr, USHORT usNRegs, LONG lTimeOut );
eMBMasterReqErrCode
eMBMasterReqReadWriteMultipleHoldingRegister( UCHAR ucSndAddr,
		USHORT usReadRegAddr, USHORT usNReadRegs, USHORT * pusDataBuffer,
		USHORT usWriteRegAddr, USHORT usNWriteRegs, LONG lTimeOut );
eMBMasterReqErrCode
eMBMasterReqReadCoils( UCHAR ucSndAddr, USHORT usCoilAddr, USHORT usNCoils, LONG lTimeOut );
eMBMasterReqErrCode
eMBMasterReqWriteCoil( UCHAR ucSndAddr, USHORT usCoilAddr, USHORT usCoilData, LONG lTimeOut );
eMBMasterReqErrCode
eMBMasterReqWriteMultipleCoils( UCHAR ucSndAddr,
		USHORT usCoilAddr, USHORT usNCoils, UCHAR * pucDataBuffer, LONG lTimeOut );
eMBMasterReqErrCode
eMBMasterReqReadDiscreteInputs( UCHAR ucSndAddr, USHORT usDiscreteAddr, USHORT usNDiscreteIn, LONG lTimeOut );

eMBException
eMBMasterFuncReportSlaveID( UCHAR * pucFrame, USHORT * usLen );
eMBException
eMBMasterFuncReadInputRegister( UCHAR * pucFrame, USHORT * usLen );
eMBException
eMBMasterFuncReadHoldingRegister( UCHAR * pucFrame, USHORT * usLen );
eMBException
eMBMasterFuncWriteHoldingRegister( UCHAR * pucFrame, USHORT * usLen );
eMBException
eMBMasterFuncWriteMultipleHoldingRegister( UCHAR * pucFrame, USHORT * usLen );
eMBException
eMBMasterFuncReadCoils( UCHAR * pucFrame, USHORT * usLen );
eMBException
eMBMasterFuncWriteCoil( UCHAR * pucFrame, USHORT * usLen );
eMBException
eMBMasterFuncWriteMultipleCoils( UCHAR * pucFrame, USHORT * usLen );
eMBException
eMBMasterFuncReadDiscreteInputs( UCHAR * pucFrame, USHORT * usLen );
eMBException
eMBMasterFuncReadWriteMultipleHoldingRegister( UCHAR * pucFrame, USHORT * usLen );

/* \ingroup modbus\b简要这些功能是modbus Master的接口
 */
void vMBMasterGetPDUSndBuf( UCHAR ** pucFrame );
UCHAR ucMBMasterGetDestAddress( void );
void vMBMasterSetDestAddress( UCHAR Address );
BOOL xMBMasterGetCBRunInMasterMode( void );
void vMBMasterSetCBRunInMasterMode( BOOL IsMasterMode );
USHORT usMBMasterGetPDUSndLength( void );
void vMBMasterSetPDUSndLength( USHORT SendPDULength );
void vMBMasterSetCurTimerMode( eMBMasterTimerMode eMBTimerMode );
void vMBMasterRequestSetType( BOOL xIsBroadcast );
eMBMasterTimerMode xMBMasterGetCurTimerMode( void );
BOOL xMBMasterRequestIsBroadcast( void );
eMBMasterErrorEventType eMBMasterGetErrorType( void );
void vMBMasterSetErrorType( eMBMasterErrorEventType errorType );
eMBMasterReqErrCode eMBMasterWaitRequestFinish( void );

/* -----------------------回调-----------------------------------------*/

#ifdef __cplusplus
PR_END_EXTERN_C
#endif
#endif

