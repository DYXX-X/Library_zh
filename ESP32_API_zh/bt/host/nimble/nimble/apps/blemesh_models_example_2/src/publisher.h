/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

/* 蓝牙：Mesh Generic OnOff、Generic Level、照明和供应商型号
 *
 * 版权所有（c）2018 Vikrant More
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _PUBLISHER_H
#define _PUBLISHER_H

/* 其他*/
#define LEVEL_S0   -32768
#define LEVEL_S25  -16384
#define LEVEL_S50  0
#define LEVEL_S75  16384
#define LEVEL_S100 32767

#define LEVEL_U0   0
#define LEVEL_U25  16384
#define LEVEL_U50  32768
#define LEVEL_U75  49152
#define LEVEL_U100 65535

void randomize_publishers_TID(void);
void publish(struct os_event *work);

#endif

