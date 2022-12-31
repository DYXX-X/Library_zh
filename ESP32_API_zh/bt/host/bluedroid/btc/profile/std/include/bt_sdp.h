/*
 * 版权所有（C）2015 Android开源项目
 *
 * 根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef __BT_SDP_H__
#define __BT_SDP_H__

#include <stdint.h>
// #包括“bluetooth.h”
#include "common/bt_defs.h"

#define SDP_OPP_SUPPORTED_FORMATS_MAX_LENGTH 15

/**
 * 这些事件由状态机处理
 */
typedef enum {
    SDP_TYPE_RAW,        // 用于携带未知UUID的原始SDP搜索数据
    SDP_TYPE_MAP_MAS,    // 邮件访问配置文件-服务器
    SDP_TYPE_MAP_MNS,    // 消息访问配置文件-客户端（通知服务器）
    SDP_TYPE_PBAP_PSE,   // 电话簿配置文件-服务器
    SDP_TYPE_PBAP_PCE,   // 电话簿配置文件-客户端
    SDP_TYPE_OPP_SERVER, // 对象推送配置文件
    SDP_TYPE_SAP_SERVER  // SIM卡接入模式
} bluetooth_sdp_types;

typedef struct _bluetooth_sdp_hdr {
    bluetooth_sdp_types type;
    bt_uuid_t   uuid;
    uint32_t    service_name_length;
    char       *service_name;
    int32_t     rfcomm_channel_number;
    int32_t     l2cap_psm;
    int32_t     profile_version;
} bluetooth_sdp_hdr;

/**
 * 有些信号需要额外的指针，因此我们引入了一种处理这些指针的通用方法。
 */
typedef struct _bluetooth_sdp_hdr_overlay {
    bluetooth_sdp_types type;
    bt_uuid_t   uuid;
    uint32_t    service_name_length;
    char       *service_name;
    int32_t     rfcomm_channel_number;
    int32_t     l2cap_psm;
    int32_t     profile_version;

    // 用户指针，仅用于某些信号-请参见bluetooth_sdp_ops_record
    int         user1_ptr_len;
    uint8_t    *user1_ptr;
    int         user2_ptr_len;
    uint8_t    *user2_ptr;
} bluetooth_sdp_hdr_overlay;

typedef struct _bluetooth_sdp_mas_record {
    bluetooth_sdp_hdr_overlay hdr;
    uint32_t    mas_instance_id;
    uint32_t    supported_features;
    uint32_t    supported_message_types;
} bluetooth_sdp_mas_record;

typedef struct _bluetooth_sdp_mns_record {
    bluetooth_sdp_hdr_overlay hdr;
    uint32_t    supported_features;
} bluetooth_sdp_mns_record;

typedef struct _bluetooth_sdp_pse_record {
    bluetooth_sdp_hdr_overlay hdr;
    uint32_t    supported_features;
    uint32_t    supported_repositories;
} bluetooth_sdp_pse_record;

typedef struct _bluetooth_sdp_pce_record {
    bluetooth_sdp_hdr_overlay hdr;
} bluetooth_sdp_pce_record;

typedef struct _bluetooth_sdp_ops_record {
    bluetooth_sdp_hdr_overlay hdr;
    int         supported_formats_list_len;
    uint8_t     supported_formats_list[SDP_OPP_SUPPORTED_FORMATS_MAX_LENGTH];
} bluetooth_sdp_ops_record;

typedef struct _bluetooth_sdp_sap_record {
    bluetooth_sdp_hdr_overlay hdr;
} bluetooth_sdp_sap_record;

typedef union {
    bluetooth_sdp_hdr_overlay   hdr;
    bluetooth_sdp_mas_record    mas;
    bluetooth_sdp_mns_record    mns;
    bluetooth_sdp_pse_record    pse;
    bluetooth_sdp_pce_record    pce;
    bluetooth_sdp_ops_record    ops;
    bluetooth_sdp_sap_record    sap;
} bluetooth_sdp_record;

#endif /* __BT_SDP_H__ */

