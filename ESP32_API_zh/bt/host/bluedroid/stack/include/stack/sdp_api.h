/******************************************************************************
 * 版权所有（C）1999-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/
#ifndef SDP_API_H
#define SDP_API_H

#include "common/bt_target.h"
#include "stack/sdpdefs.h"
#if (SDP_INCLUDED == TRUE)
/*****************************************************************************
**  常量
*****************************************************************************/

/* 成功代码和错误代码*/
#define  SDP_SUCCESS                        0x0000
#define  SDP_INVALID_VERSION                0x0001
#define  SDP_INVALID_SERV_REC_HDL           0x0002
#define  SDP_INVALID_REQ_SYNTAX             0x0003
#define  SDP_INVALID_PDU_SIZE               0x0004
#define  SDP_INVALID_CONT_STATE             0x0005
#define  SDP_NO_RESOURCES                   0x0006
#define  SDP_DI_REG_FAILED                  0x0007
#define  SDP_DI_DISC_FAILED                 0x0008
#define  SDP_NO_DI_RECORD_FOUND             0x0009
#define  SDP_ERR_ATTR_NOT_PRESENT           0x000A
#define  SDP_ILLEGAL_PARAMETER              0x000B

#define  SDP_NO_RECS_MATCH                  0xFFF0
#define  SDP_CONN_FAILED                    0xFFF1
#define  SDP_CFG_FAILED                     0xFFF2
#define  SDP_GENERIC_ERROR                  0xFFF3
#define  SDP_DB_FULL                        0xFFF4
#define  SDP_INVALID_PDU                    0xFFF5
#define  SDP_SECURITY_ERR                   0xFFF6
#define  SDP_CONN_REJECTED                  0xFFF7
#define  SDP_CANCEL                         0xFFF8

/* 定义SDP使用的PSM*/
#define SDP_PSM     0x0001

/* Legacy#定义以避免代码更改-SDP UUID与BT UUID相同*/
#define tSDP_UUID   tBT_UUID

/* tSDP_DISC_attr的属性值字段掩码*/
#define SDP_DISC_ATTR_LEN_MASK          0x0FFF
#define SDP_DISC_ATTR_TYPE(len_type)    (len_type >> 12)
#define SDP_DISC_ATTR_LEN(len_type)     (len_type & SDP_DISC_ATTR_LEN_MASK)

/* 协议列表项的最大数量（tSDP_protocol_elem中的list_elem）*/
#define SDP_MAX_LIST_ELEMS      3


/*****************************************************************************
**  类型定义
*****************************************************************************/

/* 定义发现完成时的回调函数。*/
typedef void (tSDP_DISC_CMPL_CB) (UINT16 result);
typedef void (tSDP_DISC_CMPL_CB2) (UINT16 result, void *user_data);

typedef struct {
    BD_ADDR         peer_addr;
    UINT16          peer_mtu;
} tSDP_DR_OPEN;

typedef struct {
    UINT8           *p_data;
    UINT16          data_len;
} tSDP_DR_DATA;

typedef union {
    tSDP_DR_OPEN    open;
    tSDP_DR_DATA    data;
} tSDP_DATA;

/* 定义接收发现结果时的回调函数。*/
typedef void (tSDP_DISC_RES_CB) (UINT16 event, tSDP_DATA *p_data);

/* 定义一个结构来保存发现的服务信息。*/
typedef struct {
    union {
        UINT8       u8;                         /* 8位整数*/
        UINT16      u16;                        /* 16位整数*/
        UINT32      u32;                        /* 32位整数*/
        UINT8       array[4];                   /* 可变长度字段*/
        struct t_sdp_disc_attr *p_sub_attr;     /* 第一个子属性的地址（列表）*/
    } v;

} tSDP_DISC_ATVAL;

typedef struct t_sdp_disc_attr {
    struct t_sdp_disc_attr *p_next_attr;        /* 下一个链接属性的地址*/
    UINT16                  attr_id;            /* 属性ID*/
    UINT16                  attr_len_type;      /* 长度和类型字段*/
    tSDP_DISC_ATVAL         attr_value;         /* 可变长度条目数据*/
} tSDP_DISC_ATTR;

typedef struct t_sdp_disc_rec {
    tSDP_DISC_ATTR          *p_first_attr;      /* 记录的第一个属性*/
    struct t_sdp_disc_rec   *p_next_rec;        /* 下一条链接记录的地址*/
    UINT32                  time_read;          /* 读取记录的时间*/
    BD_ADDR                 remote_bd_addr;     /* 远程BD地址*/
} tSDP_DISC_REC;

typedef struct {
    UINT32          mem_size;                   /* 数据库的内存大小*/
    UINT32          mem_free;                   /* 内存仍然可用*/
    tSDP_DISC_REC   *p_first_rec;               /* 数据库中第一条记录的地址*/
    UINT16          num_uuid_filters;           /* 要筛选的UUID数*/
    tSDP_UUID       uuid_filters[SDP_MAX_UUID_FILTERS]; /* 要筛选的UUID*/
    UINT16          num_attr_filters;           /* 属性筛选器的数量*/
    UINT16          attr_filters[SDP_MAX_ATTR_FILTERS]; /* 要筛选的属性*/
    UINT8           *p_free_mem;                /* 指向可用内存的指针*/
#if (SDP_RAW_DATA_INCLUDED == TRUE)
    UINT8           *raw_data;                  /* 从服务器接收到记录。由客户分配/发布*/
    UINT32          raw_size;                   /* raw_data的大小*/
    UINT32          raw_used;                   /* 所用raw_data的长度*/
#endif
} tSDP_DISCOVERY_DB;

/* 此结构用于添加协议列表和查找协议元素*/
typedef struct {
    UINT16      protocol_uuid;
    UINT16      num_params;
    UINT16      params[SDP_MAX_PROTOCOL_PARAMS];
} tSDP_PROTOCOL_ELEM;

typedef struct {
    UINT16              num_elems;
    tSDP_PROTOCOL_ELEM  list_elem[SDP_MAX_LIST_ELEMS];
} tSDP_PROTO_LIST_ELEM;

/* 设备标识（DI）数据结构
*/
/* 用于设置DI记录*/
typedef struct t_sdp_di_record {
    UINT16       vendor;
    UINT16       vendor_id_source;
    UINT16       product;
    UINT16       version;
    BOOLEAN      primary_record;
    char         client_executable_url[SDP_MAX_ATTR_LEN];   /* 可选择的*/
    char         service_description[SDP_MAX_ATTR_LEN];     /* 可选择的*/
    char         documentation_url[SDP_MAX_ATTR_LEN];       /* 可选择的*/
} tSDP_DI_RECORD;

/* 用于获取DI记录*/
typedef struct t_sdp_di_get_record {
    UINT16          spec_id;
    tSDP_DI_RECORD  rec;
} tSDP_DI_GET_RECORD;


/*****************************************************************************
**  外部函数声明
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/* 用于服务发现的SDP层的API。*/

/*******************************************************************************
** 函数SDP_IitDiscoveryDb
**
** 说明调用此函数以初始化发现数据库。
**
** 如果成功，则返回TRUE；如果一个或多个参数不正确，则返回FALSE
**
*******************************************************************************/
extern BOOLEAN SDP_InitDiscoveryDb (tSDP_DISCOVERY_DB *p_db, UINT32 len,
                                    UINT16 num_uuid,
                                    tSDP_UUID *p_uuid_list,
                                    UINT16 num_attr,
                                    UINT16 *p_attr_list);

/*******************************************************************************
** 函数SDP_CancelServiceSearch
**
** 说明此功能取消对SDP服务器的活动查询。
**
** 如果发现已取消，则返回TRUE；如果未找到匹配的活动，则返回FALSE。
**
*******************************************************************************/
extern BOOLEAN SDP_CancelServiceSearch (tSDP_DISCOVERY_DB *p_db);

/*******************************************************************************
** 函数SDP_ServiceSearchRequest
**
** 说明此函数向SDP服务器查询信息。
**
** 如果发现开始，则返回TRUE；如果失败，则返回FALSE。
**
*******************************************************************************/
extern BOOLEAN SDP_ServiceSearchRequest (UINT8 *p_bd_addr,
        tSDP_DISCOVERY_DB *p_db,
        tSDP_DISC_CMPL_CB *p_cb);


/*******************************************************************************
** 函数SDP_ServiceSearchAttributeRequest
**
** 说明此函数向SDP服务器查询信息。
**
**                  此API函数与函数SDP_ServiceSearchRequest2之间的区别在于，此函数执行组合的ServiceSearchAttributeRequest SDP函数。
**
** 如果发现开始，则返回TRUE；如果失败，则返回FALSE。
**
*******************************************************************************/
extern BOOLEAN SDP_ServiceSearchAttributeRequest (UINT8 *p_bd_addr,
        tSDP_DISCOVERY_DB *p_db,
        tSDP_DISC_CMPL_CB *p_cb);

/*******************************************************************************
** 函数SDP_ServiceSearchAttributeRequest2
**
** 说明此函数向SDP服务器查询信息。
**
**                  此API函数与SDP_ServiceSearchRequest函数之间的区别在于，此函数将ServiceSearchAttributeRequest SDP函数与用户数据一起执行
**
** 如果发现开始，则返回TRUE；如果失败，则返回FALSE。
**
*******************************************************************************/
extern BOOLEAN SDP_ServiceSearchAttributeRequest2 (UINT8 *p_bd_addr,
        tSDP_DISCOVERY_DB *p_db,
        tSDP_DISC_CMPL_CB2 *p_cb, void *user_data);

/* 在本地发现数据库中查找数据的实用程序API*/

/*******************************************************************************
** 函数SDP_FindAttributeInDb
**
** 说明此函数查询SDP数据库中的特定属性。如果p_start_rec指针为NULL，则从数据库的开头开始查找，否则从p_start_red之后的下一条记录继续查找。
**
** 返回指向匹配记录的指针，或NULL
**
*******************************************************************************/
extern tSDP_DISC_REC *SDP_FindAttributeInDb (tSDP_DISCOVERY_DB *p_db,
        UINT16 attr_id,
        tSDP_DISC_REC *p_start_rec);


/*******************************************************************************
** 函数SDP_FindAttributeInRec
**
** 说明此函数用于搜索SDP发现记录中的特定属性。
**
** 返回指向匹配属性项的指针，或NULL
**
*******************************************************************************/
extern tSDP_DISC_ATTR *SDP_FindAttributeInRec (tSDP_DISC_REC *p_rec,
        UINT16 attr_id);


/*******************************************************************************
** 函数SDP_FindServiceInDb
**
** 说明此函数用于查询SDP数据库中的特定服务。如果p_start_rec指针为NULL，则从数据库的开头开始查找，否则从p_start_red之后的下一条记录继续查找。
**
** 返回指向包含服务类或NULL的记录的指针
**
*******************************************************************************/
extern tSDP_DISC_REC *SDP_FindServiceInDb (tSDP_DISCOVERY_DB *p_db,
        UINT16 service_uuid,
        tSDP_DISC_REC *p_start_rec);


/*******************************************************************************
** 函数SDP_FindServiceUUIDInDb
**
** 说明此函数用于查询SDP数据库中的特定服务。如果p_start_rec指针为NULL，则从数据库的开头开始查找，否则从p_start_red之后的下一条记录继续查找。
**
** 注意：此函数与上一个函数“SDP_FindServiceInDb（）”之间的唯一区别是此函数接受tBT_UUID输入。
**
** 返回指向包含服务类或NULL的记录的指针
**
*******************************************************************************/
extern tSDP_DISC_REC *SDP_FindServiceUUIDInDb (tSDP_DISCOVERY_DB *p_db,
        tBT_UUID *p_uuid,
        tSDP_DISC_REC *p_start_rec);

/*******************************************************************************
** 函数SDP_FindServiceUUIDInRec_128bit
**
** 说明调用此函数以读取记录中的128位服务UUID（如果有）。
**
** 参数：p_rec-指向SDP记录的指针。p_uuid-用于保存找到的uuid的输出参数。
**
** 如果找到，则返回TRUE，否则返回FALSE。
**
*******************************************************************************/
extern BOOLEAN SDP_FindServiceUUIDInRec_128bit(tSDP_DISC_REC *p_rec, tBT_UUID *p_uuid);

/*******************************************************************************
** 函数SDP_FindServiceInDb_128bit
**
** 说明此函数用于查询SDP数据库中的特定服务。如果p_start_rec指针为NULL，则从数据库的开头开始查找，否则从p_start_red之后的下一条记录继续查找。
**
** 返回指向包含服务类或NULL的记录的指针
**
*******************************************************************************/
extern tSDP_DISC_REC *SDP_FindServiceInDb_128bit(tSDP_DISCOVERY_DB *p_db,
        tSDP_DISC_REC *p_start_rec);

/*******************************************************************************
** 函数SDP_FindProtocolListElemInRec
**
** 说明此函数查看协议列表元素的特定发现记录。
**
** 如果找到，则返回TRUE；如果没有，则返回FALSE。如果找到，将填充传递的协议列表元素。
**
*******************************************************************************/
extern BOOLEAN SDP_FindProtocolListElemInRec (tSDP_DISC_REC *p_rec,
        UINT16 layer_uuid,
        tSDP_PROTOCOL_ELEM *p_elem);


/*******************************************************************************
** 函数SDP_FindAddProtoListsLemInRec
**
** 说明此函数查看协议列表元素的特定发现记录。
**
** 如果找到，则返回TRUE；如果没有，则返回FALSE。如果找到，将填充传递的协议列表元素。
**
*******************************************************************************/
extern BOOLEAN SDP_FindAddProtoListsElemInRec (tSDP_DISC_REC *p_rec,
        UINT16 layer_uuid,
        tSDP_PROTOCOL_ELEM *p_elem);


/*******************************************************************************
** 函数SDP_FindProfileVersionInRec
**
** 说明此函数查看配置文件列表描述符的特定发现记录，并提取版本号。版本号由8位主要版本和8位次要版本组成。
**
** 如果找到，则返回TRUE；如果没有，则返回FALSE。如果找到，将填充传入的主要版本号和次要版本号。
**
*******************************************************************************/
extern BOOLEAN SDP_FindProfileVersionInRec (tSDP_DISC_REC *p_rec,
        UINT16 profile_uuid,
        UINT16 *p_version);


/* 用于本地服务数据库更新的SDP API*/

/*******************************************************************************
** 函数SDP_CreateRecord
**
** 说明调用此函数在数据库中创建记录。这将通过SDP数据库维护API实现。记录创建为空，应用程序应调用“add_attribute”添加记录的属性。
**
** 如果确定，则返回记录句柄，否则返回0。
**
*******************************************************************************/
extern UINT32 SDP_CreateRecord (void);


/*******************************************************************************
** 函数SDP_DeleteRecord
**
** 说明调用此函数以从数据库中添加记录（或所有记录）。这将通过SDP数据库维护API实现。
**
**                  如果传递了记录句柄0，则删除所有记录。
**
** 如果成功，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
extern BOOLEAN SDP_DeleteRecord (UINT32 handle);


/*******************************************************************************
** 功能SDP_ReadRecord
**
** 描述调用此函数以从数据库中获取具有给定句柄的记录的原始数据。
**
** 如果未找到记录，则返回-1。否则，p_data中数据开始的偏移量（0或1）。
**
**                  复制到p_data中的数据大小以*p_data_len为单位。
**
*******************************************************************************/
extern INT32 SDP_ReadRecord(UINT32 handle, UINT8 *p_data, INT32 *p_data_len);

/*******************************************************************************
** 函数SDP_AddAttribute
**
** 说明调用此函数将属性添加到记录。这将通过SDP数据库维护API实现。如果记录中已存在该属性，则将用新值替换该属性。
**
** 注意：属性值必须作为Big Endian流传递。
**
** 如果添加了OK，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
extern BOOLEAN SDP_AddAttribute (UINT32 handle, UINT16 attr_id,
                                 UINT8 attr_type, UINT32 attr_len,
                                 UINT8 *p_val);


/*******************************************************************************
** 函数SDP_AddSequence
**
** 说明调用此函数将序列添加到记录中。这将通过SDP数据库维护API实现。如果该序列已存在于记录中，则将用新序列替换。
**
** 注：元素值必须作为Big Endian流传递。
**
** 如果添加了OK，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
extern BOOLEAN SDP_AddSequence (UINT32 handle,  UINT16 attr_id,
                                UINT16 num_elem, UINT8 type[],
                                UINT8 len[], UINT8 *p_val[]);


/*******************************************************************************
** 函数SDP_AddUuidSequence
**
** 描述调用此函数将UUID序列添加到记录中。这将通过SDP数据库维护API实现。如果该序列已存在于记录中，则将用新序列替换。
**
** 如果添加了OK，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
extern BOOLEAN SDP_AddUuidSequence (UINT32 handle,  UINT16 attr_id,
                                    UINT16 num_uuids, UINT16 *p_uuids);


/*******************************************************************************
** 函数SDP_AddProtocolList
**
** 描述调用此函数将协议描述符列表添加到记录中。这将通过SDP数据库维护API实现。如果记录中已存在协议列表，则将用新列表替换。
**
** 如果添加了OK，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
extern BOOLEAN SDP_AddProtocolList (UINT32 handle, UINT16 num_elem,
                                    tSDP_PROTOCOL_ELEM *p_elem_list);


/*******************************************************************************
** 函数SDP_AddAdditionProtoList
**
** 描述调用此函数将协议描述符列表添加到记录中。这将通过SDP数据库维护API实现。如果记录中已存在协议列表，则将用新列表替换。
**
** 如果添加了OK，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
extern BOOLEAN SDP_AddAdditionProtoLists (UINT32 handle, UINT16 num_elem,
        tSDP_PROTO_LIST_ELEM *p_proto_list);


/*******************************************************************************
** 函数SDP_AddProfileDescriptorList
**
** 描述调用此函数将配置文件描述符列表添加到记录中。这将通过SDP数据库维护API实现。如果记录中已存在该版本，则将用新版本替换。
**
** 如果添加了OK，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
extern BOOLEAN SDP_AddProfileDescriptorList (UINT32 handle,
        UINT16 profile_uuid,
        UINT16 version);


/*******************************************************************************
** 函数SDP_AddLanguageBaseAttrIDList
**
** 描述调用此函数将语言基础属性列表添加到记录中。这将通过SDP数据库维护API实现。如果记录中已存在该版本，则将用新版本替换。
**
** 如果添加了OK，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
extern BOOLEAN SDP_AddLanguageBaseAttrIDList (UINT32 handle,
        UINT16 lang, UINT16 char_enc,
        UINT16 base_id);


/*******************************************************************************
** 函数SDP_AddServiceClassIdList
**
** 说明调用此函数将服务列表添加到记录中。这将通过SDP数据库维护API实现。如果记录中已存在服务列表，则将用新列表替换。
**
** 如果添加了OK，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
extern BOOLEAN SDP_AddServiceClassIdList (UINT32 handle,
        UINT16 num_services,
        UINT16 *p_service_uuids);


/*******************************************************************************
** 函数SDP_DeleteAttribute
**
** 说明此函数用于从记录中删除属性。这将通过SDP数据库维护API实现。
**
** 如果删除OK，则返回TRUE；如果未找到，则返回FALSE
**
*******************************************************************************/
extern BOOLEAN SDP_DeleteAttribute (UINT32 handle, UINT16 attr_id);


/* 设备标识API*/

/*******************************************************************************
** 函数SDP_SetLocalDiRecord
**
** 说明此功能将DI记录添加到本地SDP数据库。
**
** 如果成功添加记录，则返回SDP_SUCCESS，否则返回错误
**
*******************************************************************************/
extern UINT16 SDP_SetLocalDiRecord (tSDP_DI_RECORD *device_info,
                                    UINT32 *p_handle);

/*******************************************************************************
** 函数SDP_DiDiscover
**
** 说明此函数向远程设备查询DI信息。
**
** 如果查询成功启动，则返回SDP_SUCCESS，否则返回error
**
*******************************************************************************/
extern UINT16 SDP_DiDiscover (BD_ADDR remote_device,
                              tSDP_DISCOVERY_DB *p_db, UINT32 len,
                              tSDP_DISC_CMPL_CB *p_cb);


/*******************************************************************************
** 函数SDP_GetNumDiRecords
**
** 说明在指定数据库中搜索DI记录
**
** 返回找到的DI记录数
**
*******************************************************************************/
extern UINT8  SDP_GetNumDiRecords (tSDP_DISCOVERY_DB *p_db);


/*******************************************************************************
** 函数SDP_GetDiRecord
**
** 说明此函数从指定数据库检索远程设备的DI记录。
**
** 如果检索到记录，则返回SDP_SUCCESS，否则返回错误
**
*******************************************************************************/
extern UINT16 SDP_GetDiRecord (UINT8 getRecordIndex,
                               tSDP_DI_GET_RECORD *device_info,
                               tSDP_DISCOVERY_DB *p_db);


/*******************************************************************************
** 函数SDP_SetTraceLevel
**
** 说明此函数设置SDP的跟踪级别。如果用0xFF值调用，它只读取当前跟踪级别。
**
** 返回新的（当前）跟踪级别
**
*******************************************************************************/
extern UINT8 SDP_SetTraceLevel (UINT8 new_level);

/*******************************************************************************
** 函数SDP_ConnOpen
**
** 说明此功能创建到给定设备上SDP服务器的连接。
**
** 如果无法启动连接，则返回0。否则，手柄。
**
*******************************************************************************/
UINT32 SDP_ConnOpen (UINT8 *p_bd_addr, tSDP_DISC_RES_CB *p_rcb,
                     tSDP_DISC_CMPL_CB *p_cb);

/*******************************************************************************
** 函数SDP_WriteData
**
** 说明此功能将数据发送到连接的SDP服务器。
**
** 如果发送数据，则返回TRUE；如果失败，则返回FALSE。
**
*******************************************************************************/
BOOLEAN SDP_WriteData (UINT32 handle, BT_HDR  *p_msg);

/*******************************************************************************
** 函数SDP_ConnClose
**
** 说明调用此函数以关闭SDP连接。
**
** 参数：handle-SDP_ConnOpen返回的连接句柄
**
** 如果连接关闭，则返回TRUE；如果找不到句柄，则返回FALSE。
**
*******************************************************************************/
BOOLEAN SDP_ConnClose (UINT32 handle);

/*******************************************************************************
** 函数SDP_FindServiceUUIDInRec
**
** 描述调用此函数以读取记录中的服务UUID（如果有）。
**
** 参数：p_rec-指向SDP记录的指针。
**
** 如果找到，则返回TRUE，否则返回FALSE。
**
*******************************************************************************/
BOOLEAN SDP_FindServiceUUIDInRec(tSDP_DISC_REC *p_rec, tBT_UUID *p_uuid);

#ifdef __cplusplus
}
#endif

#endif  ///SDP_INCLUDED == TRUE

#endif  /* SDP_API_H */

