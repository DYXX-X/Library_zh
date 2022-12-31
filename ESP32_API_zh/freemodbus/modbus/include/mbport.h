/*
 * FreeModbus库：Modbus ASCII/RTU的便携式Modbus实现。版权所有（c）2006 Christian Walter<wolti@sil.at>保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 文件：$Id:mbport。h、 2010年6月19日13:54:40 wolti Exp$
 */

#ifndef _MB_PORT_H
#define _MB_PORT_H

#include "mbconfig.h"   // for选项

#ifdef __cplusplus
PR_BEGIN_EXTERN_C
#endif

#if CONFIG_UART_ISR_IN_IRAM
#define MB_PORT_SERIAL_ISR_FLAG ESP_INTR_FLAG_IRAM
#else
#define MB_PORT_SERIAL_ISR_FLAG ESP_INTR_FLAG_LOWMED
#endif

#if MB_PORT_TIMER_ISR_IN_IRAM
#define MB_PORT_ISR_ATTR IRAM_ATTR
#define MB_PORT_TIMER_ISR_FLAG ESP_INTR_FLAG_IRAM
#else
#define MB_PORT_ISR_ATTR
#define MB_PORT_TIMER_ISR_FLAG ESP_INTR_FLAG_LOWMED
#endif

/* -----------------------类型定义---------------------------------*/

typedef enum
{
    EV_READY = 0x01,                   /*!< 启动完成。*/
    EV_FRAME_RECEIVED = 0x02,          /*!< 收到帧。*/
    EV_EXECUTE = 0x04,                 /*!< 执行函数。*/
    EV_FRAME_SENT = 0x08,              /*!< 帧已发送。*/
    EV_FRAME_TRANSMIT = 0x10           /*!< 帧传输。*/
} eMBEventType;

#if MB_MASTER_RTU_ENABLED || MB_MASTER_ASCII_ENABLED || MB_MASTER_TCP_ENABLED
typedef enum {
    EV_MASTER_NO_EVENT = 0x0000,
    EV_MASTER_READY = 0x0001,                   /*!< 启动完成。*/
    EV_MASTER_FRAME_RECEIVED = 0x0002,          /*!< 收到帧。*/
    EV_MASTER_EXECUTE = 0x0004,                 /*!< 执行函数。*/
    EV_MASTER_FRAME_SENT = 0x0008,              /*!< 帧已发送。*/
    EV_MASTER_FRAME_TRANSMIT = 0x0010,          /*!< 帧传输。*/
    EV_MASTER_ERROR_PROCESS = 0x0020,           /*!< 帧错误处理。*/
    EV_MASTER_PROCESS_SUCCESS = 0x0040,         /*!< 请求进程成功。*/
    EV_MASTER_ERROR_RESPOND_TIMEOUT = 0x0080,   /*!< 请求响应超时。*/
    EV_MASTER_ERROR_RECEIVE_DATA = 0x0100,      /*!< 请求接收数据错误。*/
    EV_MASTER_ERROR_EXECUTE_FUNCTION = 0x0200   /*!< 请求执行函数错误。*/
} eMBMasterEventType;

typedef enum {
    EV_ERROR_INIT,             /*!< 无错误，初始状态。*/
    EV_ERROR_RESPOND_TIMEOUT,  /*!< 从属响应超时。*/
    EV_ERROR_RECEIVE_DATA,     /*!< 接收帧数据错误。*/
    EV_ERROR_EXECUTE_FUNCTION, /*!< 执行函数错误。*/
    EV_ERROR_OK                /*!< 无错误，处理完成。*/
} eMBMasterErrorEventType;
#endif

/*! \ingroup modbus\用于串行模式中字符的简短奇偶校验。
 *
 * 应应用于通过串行链路发送的字符的奇偶校验。请注意，这些值实际上被传递到了移植层，因此并非所有的奇偶校验模式都可用。
 */
typedef enum
{
    MB_PAR_NONE,                /*!< 无奇偶校验。*/
    MB_PAR_ODD,                 /*!< 奇数奇偶校验。*/
    MB_PAR_EVEN                 /*!< 偶数奇偶校验。*/
} eMBParity;

/* -----------------------支持功能-----------------------------*/
BOOL            xMBPortEventInit( void );

BOOL            xMBPortEventPost( eMBEventType eEvent );

BOOL            xMBPortEventGet(  /*@输出@*/ eMBEventType * eEvent );

#if MB_MASTER_RTU_ENABLED || MB_MASTER_ASCII_ENABLED || MB_MASTER_TCP_ENABLED
BOOL            xMBMasterPortEventInit( void );

BOOL            xMBMasterPortEventPost( eMBMasterEventType eEvent );

BOOL            xMBMasterPortEventGet(  /*@输出@*/ eMBMasterEventType * eEvent );

eMBMasterEventType
                xMBMasterPortFsmWaitConfirmation( eMBMasterEventType eEventMask, ULONG ulTimeout);

void            vMBMasterOsResInit( void );

BOOL            xMBMasterRunResTake( LONG time );

void            vMBMasterRunResRelease( void );
#endif // MB_MASTER_RTU_ENABLED || MB_MASTER_ASCII_ENABLED || MB_MASTER_TCP_ENABLED
/* -----------------------串行端口功能----------------------------*/

BOOL            xMBPortSerialInit( UCHAR ucPort, ULONG ulBaudRate,
                                   UCHAR ucDataBits, eMBParity eParity );

void            vMBPortClose( void );

void            xMBPortSerialClose( void );

void            vMBPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable );

BOOL            xMBPortSerialGetByte( CHAR * pucByte );

BOOL            xMBPortSerialPutByte( CHAR ucByte );

#if MB_MASTER_RTU_ENABLED || MB_MASTER_ASCII_ENABLED
BOOL            xMBMasterPortSerialInit( UCHAR ucPort, ULONG ulBaudRate,
                                   UCHAR ucDataBits, eMBParity eParity );

void            vMBMasterPortClose( void );

void            xMBMasterPortSerialClose( void );

void            vMBMasterPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable );

BOOL            xMBMasterPortSerialGetByte( CHAR * pucByte );

BOOL            xMBMasterPortSerialPutByte( CHAR ucByte );
#endif

/* -----------------------计时器功能---------------------------------*/
BOOL            xMBPortTimersInit( USHORT usTimeOut50us );

void            xMBPortTimersClose( void );

void            vMBPortTimersEnable( void );

void            vMBPortTimersDisable( void );

void            vMBPortTimersDelay( USHORT usTimeOutMS );

#if MB_MASTER_RTU_ENABLED || MB_MASTER_ASCII_ENABLED || MB_MASTER_TCP_ENABLED
BOOL            xMBMasterPortTimersInit( USHORT usTimeOut50us );

void            xMBMasterPortTimersClose( void );

void            vMBMasterPortTimersT35Enable( void );

void            vMBMasterPortTimersConvertDelayEnable( void );

void            vMBMasterPortTimersRespondTimeoutEnable( void );

void            vMBMasterPortTimersDisable( void );


/* -----------------主错误进程的回调------------------*/
void            vMBMasterErrorCBRespondTimeout( UCHAR ucDestAddress, const UCHAR* pucPDUData,
                                                USHORT ucPDULength );

void            vMBMasterErrorCBReceiveData( UCHAR ucDestAddress, const UCHAR* pucPDUData,
                                             USHORT ucPDULength );

void            vMBMasterErrorCBExecuteFunction( UCHAR ucDestAddress, const UCHAR* pucPDUData,
                                                 USHORT ucPDULength );

void            vMBMasterCBRequestSuccess( void );
#endif
/* -----------------------协议堆栈的回调------------------*/
/*!
 * \当新字节可用时，移植层的简短回调函数。
 *
 * 根据模式，RTU或ASCII传输层使用此回调函数。在任何情况下，对xMBPortSerialGetByte（）的调用都必须立即返回一个新字符。
 *
 * \如果由于接收到新字节而将事件发布到队列，则返回<code>TRUE</code>。端口实现应唤醒事件队列中当前被阻止的任务。
 */
extern          BOOL( *pxMBFrameCBByteReceived ) ( void );

extern          BOOL( *pxMBFrameCBTransmitterEmpty ) ( void );

extern          BOOL( *pxMBPortCBTimerExpired ) ( void );

#if MB_MASTER_RTU_ENABLED || MB_MASTER_ASCII_ENABLED || MB_MASTER_TCP_ENABLED
extern          BOOL( *pxMBMasterFrameCBByteReceived ) ( void );

extern          BOOL( *pxMBMasterFrameCBTransmitterEmpty ) ( void );

extern          BOOL( *pxMBMasterPortCBTimerExpired ) ( void );
#endif
/* -----------------------TCP端口功能-------------------------------*/
#if MB_TCP_ENABLED
BOOL            xMBTCPPortInit( USHORT usTCPPort );

void            vMBTCPPortClose( void );

void            vMBTCPPortEnable( void );

void            vMBTCPPortDisable( void );

BOOL            xMBTCPPortGetRequest( UCHAR **ppucMBTCPFrame, USHORT * usTCPLength );

BOOL            xMBTCPPortSendResponse( UCHAR *pucMBTCPFrame, USHORT usTCPLength );

#endif

#if MB_MASTER_TCP_ENABLED
BOOL            xMBMasterTCPPortInit( USHORT usTCPPort );

void            vMBMasterTCPPortClose( void );

void            vMBMasterTCPPortEnable( void );

void            vMBMasterTCPPortDisable( void );

BOOL            xMBMasterTCPPortGetRequest( UCHAR **ppucMBTCPFrame, USHORT * usTCPLength );

BOOL            xMBMasterTCPPortSendResponse( UCHAR *pucMBTCPFrame, USHORT usTCPLength );
#endif
#ifdef __cplusplus
PR_END_EXTERN_C
#endif
#endif

