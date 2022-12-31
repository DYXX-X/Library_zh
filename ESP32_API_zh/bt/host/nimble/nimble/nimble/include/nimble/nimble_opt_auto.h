/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_NIMBLE_OPT_AUTO_
#define H_NIMBLE_OPT_AUTO_

#include "syscfg/syscfg.h"

#ifdef __cplusplus
extern "C" {
#endif

/***
 * 自动选项。
 *
 * 这些设置是根据用户指定的syscfg设置自动生成的。
 */

#undef NIMBLE_BLE_ADVERTISE
#define NIMBLE_BLE_ADVERTISE                    \
    (MYNEWT_VAL(BLE_ROLE_BROADCASTER) || MYNEWT_VAL(BLE_ROLE_PERIPHERAL))

#undef NIMBLE_BLE_SCAN
#define NIMBLE_BLE_SCAN                         \
    (MYNEWT_VAL(BLE_ROLE_CENTRAL) || MYNEWT_VAL(BLE_ROLE_OBSERVER))

#undef NIMBLE_BLE_CONNECT
#define NIMBLE_BLE_CONNECT                      \
    (MYNEWT_VAL(BLE_ROLE_CENTRAL) || MYNEWT_VAL(BLE_ROLE_PERIPHERAL))


/**支持的客户端ATT命令。*/

#undef NIMBLE_BLE_ATT_CLT_FIND_INFO
#define NIMBLE_BLE_ATT_CLT_FIND_INFO            \
    (MYNEWT_VAL(BLE_GATT_DISC_ALL_DSCS))

#undef NIMBLE_BLE_ATT_CLT_FIND_TYPE
#define NIMBLE_BLE_ATT_CLT_FIND_TYPE            \
    (MYNEWT_VAL(BLE_GATT_DISC_SVC_UUID))

#undef NIMBLE_BLE_ATT_CLT_READ_TYPE
#define NIMBLE_BLE_ATT_CLT_READ_TYPE            \
    (MYNEWT_VAL(BLE_GATT_FIND_INC_SVCS) ||      \
     MYNEWT_VAL(BLE_GATT_DISC_ALL_CHRS) ||      \
     MYNEWT_VAL(BLE_GATT_DISC_CHRS_UUID) ||     \
     MYNEWT_VAL(BLE_GATT_READ_UUID))

#undef NIMBLE_BLE_ATT_CLT_READ
#define NIMBLE_BLE_ATT_CLT_READ                 \
    (MYNEWT_VAL(BLE_GATT_READ) ||               \
     MYNEWT_VAL(BLE_GATT_READ_LONG) ||          \
     MYNEWT_VAL(BLE_GATT_FIND_INC_SVCS))

#undef NIMBLE_BLE_ATT_CLT_READ_BLOB
#define NIMBLE_BLE_ATT_CLT_READ_BLOB            \
    (MYNEWT_VAL(BLE_GATT_READ_LONG))

#undef NIMBLE_BLE_ATT_CLT_READ_MULT
#define NIMBLE_BLE_ATT_CLT_READ_MULT            \
    (MYNEWT_VAL(BLE_GATT_READ_MULT))

#undef NIMBLE_BLE_ATT_CLT_READ_GROUP_TYPE
#define NIMBLE_BLE_ATT_CLT_READ_GROUP_TYPE      \
    (MYNEWT_VAL(BLE_GATT_DISC_ALL_SVCS))

#undef NIMBLE_BLE_ATT_CLT_WRITE
#define NIMBLE_BLE_ATT_CLT_WRITE                \
    (MYNEWT_VAL(BLE_GATT_WRITE))

#undef NIMBLE_BLE_ATT_CLT_WRITE_NO_RSP
#define NIMBLE_BLE_ATT_CLT_WRITE_NO_RSP         \
    (MYNEWT_VAL(BLE_GATT_WRITE_NO_RSP))

#undef NIMBLE_BLE_ATT_CLT_PREP_WRITE
#define NIMBLE_BLE_ATT_CLT_PREP_WRITE           \
    (MYNEWT_VAL(BLE_GATT_WRITE_LONG))

#undef NIMBLE_BLE_ATT_CLT_EXEC_WRITE
#define NIMBLE_BLE_ATT_CLT_EXEC_WRITE           \
    (MYNEWT_VAL(BLE_GATT_WRITE_LONG))

#undef NIMBLE_BLE_ATT_CLT_NOTIFY
#define NIMBLE_BLE_ATT_CLT_NOTIFY               \
    (MYNEWT_VAL(BLE_GATT_NOTIFY))

#undef NIMBLE_BLE_ATT_CLT_INDICATE
#define NIMBLE_BLE_ATT_CLT_INDICATE             \
    (MYNEWT_VAL(BLE_GATT_INDICATE))

/**安全管理器设置。*/

#undef NIMBLE_BLE_SM
#define NIMBLE_BLE_SM   (MYNEWT_VAL(BLE_SM_LEGACY) || MYNEWT_VAL(BLE_SM_SC))

#ifdef __cplusplus
}
#endif

#endif

