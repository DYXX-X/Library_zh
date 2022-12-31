/******************************************************************************
 * 版权所有（C）2002-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/
#ifndef DYN_MEM_H
#define DYN_MEM_H

#include "common/bluedroid_user_config.h"

#if UC_BT_BLE_DYNAMIC_ENV_MEMORY
#define BTU_DYNAMIC_MEMORY         TRUE
#define BTM_DYNAMIC_MEMORY         TRUE
#define L2C_DYNAMIC_MEMORY         TRUE
#define GATT_DYNAMIC_MEMORY        TRUE
#define SMP_DYNAMIC_MEMORY         TRUE
#define BTA_DYNAMIC_MEMORY         TRUE
#define SDP_DYNAMIC_MEMORY         TRUE
#define GAP_DYNAMIC_MEMORY         TRUE
#define RFC_DYNAMIC_MEMORY         TRUE
#define TCS_DYNAMIC_MEMORY         TRUE
#define BNEP_DYNAMIC_MEMORY        TRUE
#define AVDT_DYNAMIC_MEMORY        TRUE
#define AVCT_DYNAMIC_MEMORY        TRUE
#define MCA_DYNAMIC_MEMORY         TRUE
#define A2D_DYNAMIC_MEMORY         TRUE
#define VDP_DYNAMIC_MEMORY         TRUE
#define AVRC_DYNAMIC_MEMORY        TRUE
#define BIP_DYNAMIC_MEMORY         TRUE
#define BPP_DYNAMIC_MEMORY         TRUE
#define CTP_DYNAMIC_MEMORY         TRUE
#define FTP_DYNAMIC_MEMORY         TRUE
#define HCRP_DYNAMIC_MEMORY        TRUE
#define HFP_DYNAMIC_MEMORY         TRUE
#define HID_DYNAMIC_MEMORY         TRUE
#define HSP2_DYNAMIC_MEMORY        TRUE
#define ICP_DYNAMIC_MEMORY         TRUE
#define OPP_DYNAMIC_MEMORY         TRUE
#define PAN_DYNAMIC_MEMORY         TRUE
#define SPP_DYNAMIC_MEMORY         TRUE
#define SLIP_DYNAMIC_MEMORY        TRUE
#define LLCP_DYNAMIC_MEMORY        TRUE
#define BTC_SBC_DEC_DYNAMIC_MEMORY TRUE

#else  /* #如果UC_BT_BLE_DYNAMIC_ENV_MEMORY*/
#define BTU_DYNAMIC_MEMORY         FALSE
#define BTM_DYNAMIC_MEMORY         FALSE
#define L2C_DYNAMIC_MEMORY         FALSE
#define GATT_DYNAMIC_MEMORY        FALSE
#define SMP_DYNAMIC_MEMORY         FALSE
#define BTA_DYNAMIC_MEMORY         FALSE
#define SDP_DYNAMIC_MEMORY         FALSE
#define GAP_DYNAMIC_MEMORY         FALSE
#define RFC_DYNAMIC_MEMORY         FALSE
#define TCS_DYNAMIC_MEMORY         FALSE
#define BNEP_DYNAMIC_MEMORY        FALSE
#define AVDT_DYNAMIC_MEMORY        FALSE
#define AVCT_DYNAMIC_MEMORY        FALSE
#define MCA_DYNAMIC_MEMORY         FALSE
#define A2D_DYNAMIC_MEMORY         FALSE
#define VDP_DYNAMIC_MEMORY         FALSE
#define AVRC_DYNAMIC_MEMORY        FALSE
#define BIP_DYNAMIC_MEMORY         FALSE
#define BPP_DYNAMIC_MEMORY         FALSE
#define CTP_DYNAMIC_MEMORY         FALSE
#define FTP_DYNAMIC_MEMORY         FALSE
#define HCRP_DYNAMIC_MEMORY        FALSE
#define HFP_DYNAMIC_MEMORY         FALSE
#define HID_DYNAMIC_MEMORY         FALSE
#define HSP2_DYNAMIC_MEMORY        FALSE
#define ICP_DYNAMIC_MEMORY         FALSE
#define OPP_DYNAMIC_MEMORY         FALSE
#define PAN_DYNAMIC_MEMORY         FALSE
#define SPP_DYNAMIC_MEMORY         FALSE
#define SLIP_DYNAMIC_MEMORY        FALSE
#define LLCP_DYNAMIC_MEMORY        FALSE
#define BTC_SBC_DEC_DYNAMIC_MEMORY FALSE

#endif /* #如果UC_BT_BLE_DYNAMIC_ENV_MEMORY*/


/****************************************************************************
** 定义每个CORE组件的内存使用情况（如果未在bdroid_buildcfg.h中定义）每个组件的默认值是使用静态内存分配。
*/
#ifndef BTU_DYNAMIC_MEMORY
#define BTU_DYNAMIC_MEMORY  FALSE
#endif

#ifndef BTM_DYNAMIC_MEMORY
#define BTM_DYNAMIC_MEMORY  FALSE
#endif

#ifndef SDP_DYNAMIC_MEMORY
#define SDP_DYNAMIC_MEMORY  FALSE
#endif

#ifndef GAP_DYNAMIC_MEMORY
#define GAP_DYNAMIC_MEMORY  FALSE
#endif

#ifndef L2C_DYNAMIC_MEMORY
#define L2C_DYNAMIC_MEMORY  FALSE
#endif

#ifndef RFC_DYNAMIC_MEMORY
#define RFC_DYNAMIC_MEMORY  FALSE
#endif

#ifndef TCS_DYNAMIC_MEMORY
#define TCS_DYNAMIC_MEMORY  FALSE
#endif

#ifndef BNEP_DYNAMIC_MEMORY
#define BNEP_DYNAMIC_MEMORY FALSE
#endif

#ifndef AVDT_DYNAMIC_MEMORY
#define AVDT_DYNAMIC_MEMORY FALSE
#endif

#ifndef AVCT_DYNAMIC_MEMORY
#define AVCT_DYNAMIC_MEMORY FALSE
#endif

#ifndef MCA_DYNAMIC_MEMORY
#define MCA_DYNAMIC_MEMORY FALSE
#endif

#ifndef GATT_DYNAMIC_MEMORY
#define GATT_DYNAMIC_MEMORY  FALSE
#endif

#ifndef SMP_DYNAMIC_MEMORY
#define SMP_DYNAMIC_MEMORY  FALSE
#endif

/****************************************************************************
** 定义每个PROFILE组件的内存使用情况（如果未在bdroid_buildcfg.h中定义）每个组件的默认值是使用静态内存分配。
*/
#ifndef A2D_DYNAMIC_MEMORY
#define A2D_DYNAMIC_MEMORY  FALSE
#endif

#ifndef VDP_DYNAMIC_MEMORY
#define VDP_DYNAMIC_MEMORY  FALSE
#endif

#ifndef AVRC_DYNAMIC_MEMORY
#define AVRC_DYNAMIC_MEMORY FALSE
#endif

#ifndef BIP_DYNAMIC_MEMORY
#define BIP_DYNAMIC_MEMORY  FALSE
#endif

#ifndef BPP_DYNAMIC_MEMORY
#define BPP_DYNAMIC_MEMORY  FALSE
#endif

#ifndef CTP_DYNAMIC_MEMORY
#define CTP_DYNAMIC_MEMORY  FALSE
#endif

#ifndef FTP_DYNAMIC_MEMORY
#define FTP_DYNAMIC_MEMORY  FALSE
#endif

#ifndef HCRP_DYNAMIC_MEMORY
#define HCRP_DYNAMIC_MEMORY FALSE
#endif

#ifndef HFP_DYNAMIC_MEMORY
#define HFP_DYNAMIC_MEMORY  FALSE
#endif

#ifndef HID_DYNAMIC_MEMORY
#define HID_DYNAMIC_MEMORY  FALSE
#endif

#ifndef HSP2_DYNAMIC_MEMORY
#define HSP2_DYNAMIC_MEMORY FALSE
#endif

#ifndef ICP_DYNAMIC_MEMORY
#define ICP_DYNAMIC_MEMORY  FALSE
#endif

#ifndef OPP_DYNAMIC_MEMORY
#define OPP_DYNAMIC_MEMORY  FALSE
#endif

#ifndef PAN_DYNAMIC_MEMORY
#define PAN_DYNAMIC_MEMORY  FALSE
#endif

#ifndef SPP_DYNAMIC_MEMORY
#define SPP_DYNAMIC_MEMORY  FALSE
#endif

#ifndef SLIP_DYNAMIC_MEMORY
#define SLIP_DYNAMIC_MEMORY  FALSE
#endif

#ifndef LLCP_DYNAMIC_MEMORY
#define LLCP_DYNAMIC_MEMORY  FALSE
#endif

/****************************************************************************
** 定义BTA和BTC的内存使用情况（如果未在bdroid_buildcfg.h中定义）每个组件的默认值是使用静态内存分配。
*/
#ifndef BTA_DYNAMIC_MEMORY
#define BTA_DYNAMIC_MEMORY FALSE
#endif

#ifndef BTC_DYNAMIC_MEMORY
#define BTC_DYNAMIC_MEMORY FALSE
#endif

#endif  /* #如果定义DYN_MEM_H*/

