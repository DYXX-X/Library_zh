/*
 * FreeModbus库：Modbus ASCII/RTU的便携式Modbus实现。版权所有（c）2006 Christian Walter<wolti@sil.at>保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 文件：$Id:mbframe。h、 v 1.9 2006年12月7日22:10:34 wolti Exp$
 */

#ifndef _MB_FRAME_H
#define _MB_FRAME_H

#include "port.h"

#ifdef __cplusplus
PR_BEGIN_EXTERN_C
#endif

/*!
 * 定义modbus帧格式的常量。示例显示了Modbus RTU/ASCII帧。注意，Modbus PDU不依赖于底层传输。
 *
 * <code><----------------MODBUS串行线路PDU（1）------------------><----------------MODBUS PDU（1'）------------------>+----------------+----------------+---------------+地址|功能代码|数据|CRC/LRC |+----------------+---------------+-------------+| |（2）（3/2'）（3'）（4）
 *
 * (1)  ... MB_SER_PDU_SIZE_MAX = 256 (2) ... MB_SER_PDU_ADDR_OFF = 0 (3) ... MB_SER_PDU_PDU_OFF = 1 (4) ... MB_SER_PDU_SIZE_CRC = 2
 *
 * （1'）…MB_PDU_SIZE_MAX=253（2'）……MB_PDU _FUNC_OFF=0（3'）…MB_PDU_DATA_OFF=1</code>
 */

/* -----------------------定义------------------------------------------*/
#define MB_PDU_SIZE_MAX         253 /*!< PDU的最大大小。*/
#define MB_PDU_SIZE_MIN         1   /*!< 功能代码*/
#define MB_PDU_FUNC_OFF         0   /*!< PDU中功能代码的偏移量。*/
#define MB_PDU_DATA_OFF         1   /*!< PDU中响应数据的偏移量。*/

#define MB_SER_PDU_SIZE_MAX     MB_SERIAL_BUF_SIZE /*!< Modbus框架的最大尺寸。*/
#define MB_SER_PDU_SIZE_LRC     1   /*!< PDU中LRC字段的大小。*/
#define MB_SER_PDU_ADDR_OFF     0   /*!< Ser PDU中从属地址的偏移量。*/
#define MB_SER_PDU_PDU_OFF      1   /*!< 序列PDU中Modbus PDU的偏移。*/
#define MB_SER_PDU_SIZE_CRC     2   /*!< PDU中CRC字段的大小。*/

#define MB_TCP_TID              0
#define MB_TCP_PID              2
#define MB_TCP_LEN              4
#define MB_TCP_UID              6
#define MB_TCP_FUNC             7

#define MB_TCP_PSEUDO_ADDRESS 255

/* -----------------------原型0-------------------------------------*/
typedef void    ( *pvMBFrameStart ) ( void );

typedef void    ( *pvMBFrameStop ) ( void );

typedef eMBErrorCode( *peMBFrameReceive ) ( UCHAR * pucRcvAddress,
                                            UCHAR ** pucFrame,
                                            USHORT * pusLength );

typedef eMBErrorCode( *peMBFrameSend ) ( UCHAR slaveAddress,
                                         const UCHAR * pucFrame,
                                         USHORT usLength );

typedef void( *pvMBFrameClose ) ( void );

#ifdef __cplusplus
PR_END_EXTERN_C
#endif
#endif

