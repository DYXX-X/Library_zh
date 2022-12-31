/*
 * FreeModbus库：Modbus ASCII/RTU的便携式Modbus实现。版权所有（c）2006 Christian Walter<wolti@sil.at>保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 文件：$Id:mumbtils。h、 v 1.5 2006年12月7日22:10:34 wolti Exp$
 */

#ifndef _MB_UTILS_H
#define _MB_UTILS_H

#ifdef __cplusplus
PR_BEGIN_EXTERN_C
#endif
/*! \defgroup modbus_utils实用程序
 *
 * 该模块包含一些应用程序可以使用的实用程序功能。它包括一些特殊的函数，用于处理由字符数组缓冲区支持的位字段。
 *
 */
/*! \添加组modbus_utils@{
 */
/*! \brief函数设置字节缓冲区中的位。
 *
 * 此函数允许有效使用数组来实现位字段。用于存储位的数组必须始终是两个字节的倍数。一次操作中最多可设置或清除八位。
 *
 * \param ucByteBuf存储位值的缓冲区。必须是2字节的倍数。不执行长度检查，如果usBitOffset/8大于缓冲区内存内容的大小，则会被覆盖。\param usBitOffset要设置的位的起始地址。第一位的偏移量为0。\param ucNBits要修改的位数。该值必须始终小于8。\param ucValues位的新值。从<code>usBitOffset</code>开始的第一位的值是值<code>ucValues</code>的LSB
 *
 * \代码ucBits[2]＝｛0，0｝；
 *
 * //将位4设置为1（读取：将从位偏移4开始的1位设置为值1）xMBUtilSetBits（ucBits，4，1，1）；
 *
 * //将第7位设置为1，将第8位设置为0.xMBUtilSetBits（ucBits，7，2，0x01）；
 *
 * //将位8-11设置为0x05，将位12-15设置为0x0A；xMBUtilSetBits（ucBits，8，8，0x5A）；\结束代码
 */
void            xMBUtilSetBits( UCHAR * ucByteBuf, USHORT usBitOffset,
                                UCHAR ucNBits, UCHAR ucValues );

/*! \读取字节缓冲区中的位的简短函数。
 *
 * 此函数用于从数组中提取高位值。在一个步骤中最多可以提取八位值。
 *
 * \param ucByteBuf存储位值的缓冲区。\param usBitOffset要设置的位的起始地址。第一位的偏移量为0。\param ucNBits要修改的位数。该值必须始终小于8。
 *
 * \代码UCHAR ucBits[2]＝｛0，0｝；UCHAR ucResult；
 *
 * //提取位3-10。ucResult=xMBUtilGetBits（ucBits，3，8）；\结束代码
 */
UCHAR           xMBUtilGetBits( UCHAR * ucByteBuf, USHORT usBitOffset,
                                UCHAR ucNBits );

/*! @} */

#ifdef __cplusplus
PR_END_EXTERN_C
#endif
#endif

