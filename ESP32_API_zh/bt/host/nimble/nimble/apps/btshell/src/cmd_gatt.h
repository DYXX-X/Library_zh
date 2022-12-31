/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef CMD_GATT_H
#define CMD_GATT_H

#include "cmd.h"

int cmd_gatt_discover_characteristic(int argc, char **argv);
int cmd_gatt_discover_descriptor(int argc, char **argv);
int cmd_gatt_discover_service(int argc, char **argv);
int cmd_gatt_discover_full(int argc, char **argv);
int cmd_gatt_find_included_services(int argc, char **argv);
int cmd_gatt_exchange_mtu(int argc, char **argv);
int cmd_gatt_notify(int argc, char **argv);
int cmd_gatt_read(int argc, char **argv);
int cmd_gatt_service_changed(int argc, char **argv);
int cmd_gatt_service_visibility(int argc, char **argv);
int cmd_gatt_show(int argc, char **argv);
int cmd_gatt_show_local(int argc, char **argv);
int cmd_gatt_write(int argc, char **argv);

#endif

