/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_HS_ID_
#define H_BLE_HS_ID_

/**
 * @brief 蓝牙主机标识
 * @defgroup bt_host_id蓝牙主机标识
 * @ingroup bt_主机@{
 */

#include <inttypes.h>
#include "nimble/ble.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 生成新的随机地址。此功能不使用新地址配置设备；调用者可以在后续操作中使用该地址。
 *
 * @param nrpa                  要生成的随机地址类型：0：静态1：不可解析的专用
 * @param out_addr              成功后，生成的地址将写入此处。
 *
 * @return                      成功时为0；失败时为非零。
 */
int ble_hs_id_gen_rnd(int nrpa, ble_addr_t *out_addr);

/**
 * 设置设备的随机地址。地址类型（静态与不可解析的私有）是从地址的最高有效字节推断出来的。地址以主机字节顺序（小端！）指定。
 *
 * @param rnd_addr              要设置的随机地址。
 *
 * @return                      成功时为0；如果指定的地址不是有效的静态随机或不可解析的专用地址，则返回BLE_HS_EINVAL。其他非零错误。
 */
int ble_hs_id_set_rnd(const uint8_t *rnd_addr);

/**
 * 检索设备的标识地址之一。该设备可以有两个身份地址：一个公共地址和一个随机地址。id_addr_type参数指定要检索这两个地址中的哪一个。
 *
 * @param id_addr_type          要检索的标识地址的类型。有效值为：o BLE_ADDR_PUBLIC o BLE_ADR_RANDOM
 * @param out_id_addr           成功后，将请求的标识地址复制到此缓冲区。缓冲区的大小必须至少为六个字节。如果不需要此信息，请传递NULL。
 * @param out_is_nrpa           成功时，指向的值指示检索到的地址是否是不可解析的私有地址。如果不需要此信息，请传递NULL。
 *
 * @return                      成功时为0；如果指定了无效的地址类型，则返回BLE_HS_EINVAL；如果设备没有所请求类型的标识地址，则返回BLE_HS_ENOADDR；其他BLE主机核心代码出错。
 */
int ble_hs_id_copy_addr(uint8_t id_addr_type, uint8_t *out_id_addr,
                        int *out_is_nrpa);

/**
 * 确定用于自动地址类型解析的最佳地址类型。最佳地址类型的计算如下：
 *
 * 如果需要隐私：如果我们有一个随机静态地址：
 *          -->具有静态随机ID的RPA else
 *          -->如果我们有一个随机静态地址，则使用公共ID结束RPA：
 *          -->随机静态地址else
 *          -->公共广播终端
 *
 * @param privacy               （0/1）是否使用专用地址。
 * @param out_addr_type         成功后，这里将编写“自己的地址类型”代码。
 *
 * @return                      如果成功推断出地址类型，则为0。如果设备没有合适的地址，则返回BLE_HS_ENOADDR。其他BLE主机核心代码出错。
 */
int ble_hs_id_infer_auto(int privacy, uint8_t *out_addr_type);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif

