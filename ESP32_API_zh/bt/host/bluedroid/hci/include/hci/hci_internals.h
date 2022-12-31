/******************************************************************************
 * 版权所有（C）2014谷歌公司。
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

#ifndef _HCI_INTERNALS_H_
#define _HCI_INTERNALS_H_

// 操作码为2字节，参数长度为1字节（第2卷，E部分，5.4.1）
#define HCI_COMMAND_PREAMBLE_SIZE 3
// 2字节用于句柄，2字节用于数据长度（第2卷E部分5.4.2）
#define HCI_ACL_PREAMBLE_SIZE 4
// 2字节用于句柄，1字节用于数据长度（第2卷，E部分，5.4.3）
#define HCI_SCO_PREAMBLE_SIZE 3
// 1字节用于事件代码，1字节用于参数长度（第2卷，E部分，5.4.4）
#define HCI_EVENT_PREAMBLE_SIZE 2

#endif /* _HCI_INTERNALS_H_ */
