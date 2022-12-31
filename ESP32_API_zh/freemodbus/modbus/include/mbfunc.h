/*
 * FreeModbus库：Modbus ASCII/RTU的便携式Modbus实现。版权所有（c）2006 Christian Walter<wolti@sil.at>保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 文件：$Id:mbfunc。h、 v 2006年12月12日星期四22:10:34 wolti Exp$
 */

#ifndef _MB_FUNC_H
#define _MB_FUNC_H

#ifdef __cplusplus
PR_BEGIN_EXTERN_C
#endif
#if MB_FUNC_OTHER_REP_SLAVEID_BUF > 0
    eMBException eMBFuncReportSlaveID( UCHAR * pucFrame, USHORT * usLen );
#endif

#if MB_FUNC_READ_INPUT_ENABLED > 0
eMBException    eMBFuncReadInputRegister( UCHAR * pucFrame, USHORT * usLen );
#endif

#if MB_FUNC_READ_HOLDING_ENABLED > 0
eMBException    eMBFuncReadHoldingRegister( UCHAR * pucFrame, USHORT * usLen );
#endif

#if MB_FUNC_WRITE_HOLDING_ENABLED > 0
eMBException    eMBFuncWriteHoldingRegister( UCHAR * pucFrame, USHORT * usLen );
#endif

#if MB_FUNC_WRITE_MULTIPLE_HOLDING_ENABLED > 0
eMBException    eMBFuncWriteMultipleHoldingRegister( UCHAR * pucFrame, USHORT * usLen );
#endif

#if MB_FUNC_READ_COILS_ENABLED > 0
eMBException    eMBFuncReadCoils( UCHAR * pucFrame, USHORT * usLen );
#endif

#if MB_FUNC_WRITE_COIL_ENABLED > 0
eMBException    eMBFuncWriteCoil( UCHAR * pucFrame, USHORT * usLen );
#endif

#if MB_FUNC_WRITE_MULTIPLE_COILS_ENABLED > 0
eMBException    eMBFuncWriteMultipleCoils( UCHAR * pucFrame, USHORT * usLen );
#endif

#if MB_FUNC_READ_DISCRETE_INPUTS_ENABLED > 0
eMBException    eMBFuncReadDiscreteInputs( UCHAR * pucFrame, USHORT * usLen );
#endif

#if MB_FUNC_READWRITE_HOLDING_ENABLED > 0
eMBException    eMBFuncReadWriteMultipleHoldingRegister( UCHAR * pucFrame, USHORT * usLen );
#endif

#ifdef __cplusplus
PR_END_EXTERN_C
#endif
#endif

