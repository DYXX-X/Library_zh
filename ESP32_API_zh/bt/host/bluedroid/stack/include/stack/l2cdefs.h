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

#ifndef L2CDEFS_H
#define L2CDEFS_H

/* L2CAP命令代码
*/
#define L2CAP_CMD_REJECT                    0x01
#define L2CAP_CMD_CONN_REQ                  0x02
#define L2CAP_CMD_CONN_RSP                  0x03
#define L2CAP_CMD_CONFIG_REQ                0x04
#define L2CAP_CMD_CONFIG_RSP                0x05
#define L2CAP_CMD_DISC_REQ                  0x06
#define L2CAP_CMD_DISC_RSP                  0x07
#define L2CAP_CMD_ECHO_REQ                  0x08
#define L2CAP_CMD_ECHO_RSP                  0x09
#define L2CAP_CMD_INFO_REQ                  0x0A
#define L2CAP_CMD_INFO_RSP                  0x0B
#define L2CAP_CMD_AMP_CONN_REQ              0x0C
#define L2CAP_CMD_AMP_CONN_RSP              0x0D
#define L2CAP_CMD_AMP_MOVE_REQ              0x0E
#define L2CAP_CMD_AMP_MOVE_RSP              0x0F
#define L2CAP_CMD_AMP_MOVE_CFM              0x10
#define L2CAP_CMD_AMP_MOVE_CFM_RSP          0x11

#define L2CAP_CMD_BLE_UPDATE_REQ            0x12
#define L2CAP_CMD_BLE_UPDATE_RSP            0x13
#define L2CAP_CMD_BLE_CREDIT_BASED_CONN_REQ 0x14
#define L2CAP_CMD_BLE_CREDIT_BASED_CONN_RES 0x15
#define L2CAP_CMD_BLE_FLOW_CTRL_CREDIT      0x16



/* 定义一些数据包和标头长度
*/
#define L2CAP_PKT_OVERHEAD      4           /* 长度和CID*/
#define L2CAP_CMD_OVERHEAD      4           /* 命令代码、Id和长度*/
#define L2CAP_CMD_REJECT_LEN    2           /* 原因（数据可选）*/
#define L2CAP_CONN_REQ_LEN      4           /* PSM和源CID*/
#define L2CAP_CONN_RSP_LEN      8           /* 目的地CID、源CID、原因、状态*/
#define L2CAP_CONFIG_REQ_LEN    4           /* Dest CID，标志（数据可选）*/
#define L2CAP_CONFIG_RSP_LEN    6           /* 目标CID、标志、结果、数据可选*/
#define L2CAP_DISC_REQ_LEN      4           /* 目标CID、源CID*/
#define L2CAP_DISC_RSP_LEN      4           /* 目标CID、源CID*/
#define L2CAP_ECHO_REQ_LEN      0           /* 数据是可选的*/
#define L2CAP_ECHO_RSP_LEN      0           /* 数据是可选的*/
#define L2CAP_INFO_REQ_LEN      2           /* 信息类型*/
#define L2CAP_INFO_RSP_LEN      4           /* 信息类型、结果（数据可选）*/
#define L2CAP_BCST_OVERHEAD     2           /* 附加广播数据包开销*/
#define L2CAP_UCD_OVERHEAD      2           /* 额外的无连接数据包开销*/

#define L2CAP_AMP_CONN_REQ_LEN  5           /* PSM、CID和遥控器ID*/
#define L2CAP_AMP_MOVE_REQ_LEN  3           /* CID和遥控器ID*/
#define L2CAP_AMP_MOVE_RSP_LEN  4           /* CID和结果*/
#define L2CAP_AMP_MOVE_CFM_LEN  4           /* CID和结果*/
#define L2CAP_AMP_MOVE_CFM_RSP_LEN  2       /* CID                                  */

#define L2CAP_CMD_BLE_UPD_REQ_LEN   8       /* 最小和最大间隔、延迟、tout*/
#define L2CAP_CMD_BLE_UPD_RSP_LEN   2       /* 后果*/

#define L2CAP_CMD_BLE_CREDIT_BASED_CONN_REQ_LEN 10 /* LE_PSM、SCID、MTU、MPS、初始信用*/
#define L2CAP_CMD_BLE_CREDIT_BASED_CONN_RES_LEN 10 /* DCID、MTU、MPS、初始信用、结果*/
#define L2CAP_CMD_BLE_FLOW_CTRL_CREDIT_LEN      4  /* CID，信贷*/



/* 定义数据包边界标志
*/
#if (L2CAP_NON_FLUSHABLE_PB_INCLUDED == TRUE)
#define L2CAP_PKT_START_FLUSHABLE       2
#define L2CAP_PKT_START_NON_FLUSHABLE   0
#endif
#define L2CAP_COMPLETE_AMP_PKT          3       /* AMP HCI上的完整L2CAP数据包*/
#define L2CAP_PKT_START                 2
#define L2CAP_PKT_CONTINUE              1
#define L2CAP_MASK_FLAG            0x0FFF
#define L2CAP_PKT_TYPE_SHIFT            12
#define L2CAP_PKT_TYPE_MASK             3


/* 定义L2CAP连接结果代码
*/
#define L2CAP_CONN_OK                0
#define L2CAP_CONN_PENDING           1
#define L2CAP_CONN_NO_PSM            2
#define L2CAP_CONN_SECURITY_BLOCK    3
#define L2CAP_CONN_NO_RESOURCES      4
#define L2CAP_CONN_BAD_CTLR_ID       5              /* AMP相关*/
#define L2CAP_CONN_TIMEOUT           0xEEEE
#define L2CAP_CONN_AMP_FAILED        254
#define L2CAP_CONN_NO_LINK           255        /* 添加一些我们自己的供内部使用*/
#define L2CAP_CONN_CANCEL            256        /* L2CAP连接已取消*/


/* 定义L2CAP移动通道响应结果代码
*/
#define L2CAP_MOVE_OK                   0
#define L2CAP_MOVE_PENDING              1
#define L2CAP_MOVE_CTRL_ID_NOT_SUPPORT  2
#define L2CAP_MOVE_SAME_CTRLR_ID        3
#define L2CAP_MOVE_CONFIG_NOT_SUPPORTED 4
#define L2CAP_MOVE_CHAN_COLLISION       5
#define L2CAP_MOVE_NOT_ALLOWED          6


/* 定义L2CAP移动通道确认结果代码
*/
#define L2CAP_MOVE_CFM_OK               0
#define L2CAP_MOVE_CFM_REFUSED          1


/* 定义L2CAP命令拒绝原因代码
*/
#define L2CAP_CMD_REJ_NOT_UNDERSTOOD    0
#define L2CAP_CMD_REJ_MTU_EXCEEDED      1
#define L2CAP_CMD_REJ_INVALID_CID       2


/* L2CAP预定义CID
*/
#define L2CAP_SIGNALLING_CID            1
#define L2CAP_CONNECTIONLESS_CID        2
#define L2CAP_AMP_CID                   3
#define L2CAP_ATT_CID                   4
#define L2CAP_BLE_SIGNALLING_CID        5
#define L2CAP_SMP_CID                   6
#define L2CAP_SMP_BR_CID                7
#define L2CAP_AMP_TEST_CID              0x003F
#define L2CAP_BASE_APPL_CID             0x0040
#define L2CAP_BLE_CONN_MAX_CID          0x007F

/* 固定通道掩码位*/

/* 支持信号通道（强制要求）*/
#define L2CAP_FIXED_CHNL_SIG_BIT     (1 << L2CAP_SIGNALLING_CID)

/* 无连接接收*/
#define L2CAP_FIXED_CHNL_CNCTLESS_BIT (1 << L2CAP_CONNECTIONLESS_CID)

/* 支持AMP Manager*/
#define L2CAP_FIXED_CHNL_AMP_BIT      (1 << L2CAP_AMP_CID)

/* 支持属性协议*/
#define L2CAP_FIXED_CHNL_ATT_BIT      (1 << L2CAP_ATT_CID)

/* 支持BLE信号*/
#define L2CAP_FIXED_CHNL_BLE_SIG_BIT  (1 << L2CAP_BLE_SIGNALLING_CID)

/* 支持BLE安全管理器*/
#define L2CAP_FIXED_CHNL_SMP_BIT      (1 << L2CAP_SMP_CID)

/* 支持BR上的安全管理器*/
#define L2CAP_FIXED_CHNL_SMP_BR_BIT   (1 << L2CAP_SMP_BR_CID)



/* 定义L2CAP配置结果代码
*/
#define L2CAP_CFG_OK                    0
#define L2CAP_CFG_UNACCEPTABLE_PARAMS   1
#define L2CAP_CFG_FAILED_NO_REASON      2
#define L2CAP_CFG_UNKNOWN_OPTIONS       3
#define L2CAP_CFG_PENDING               4
#define L2CAP_CFG_FLOW_SPEC_REJECTED    5


/* 定义L2CAP配置选项类型
*/
#define L2CAP_CFG_TYPE_MTU              0x01
#define L2CAP_CFG_TYPE_FLUSH_TOUT       0x02
#define L2CAP_CFG_TYPE_QOS              0x03
#define L2CAP_CFG_TYPE_FCR              0x04
#define L2CAP_CFG_TYPE_FCS              0x05
#define L2CAP_CFG_TYPE_EXT_FLOW         0x06
#define L2CAP_CFG_TYPE_EXT_WIN_SIZE     0x07

#define L2CAP_CFG_MTU_OPTION_LEN        2           /* MTU选件长度*/
#define L2CAP_CFG_FLUSH_OPTION_LEN      2           /* 齐平选项len*/
#define L2CAP_CFG_QOS_OPTION_LEN        22          /* QOS选项长度*/
#define L2CAP_CFG_FCR_OPTION_LEN        9           /* FCR选项长度*/
#define L2CAP_CFG_FCS_OPTION_LEN        1           /* FCR选项长度*/
#define L2CAP_CFG_EXT_FLOW_OPTION_LEN   16          /* 扩展流量规格*/
#define L2CAP_CFG_EXT_WIN_SIZE_LEN      2           /* 外部窗口大小长度*/
#define L2CAP_CFG_OPTION_OVERHEAD       2           /* 类型和长度*/

/* 配置命令/Rsp标志掩码
*/
#define L2CAP_CFG_FLAGS_MASK_CONT       0x0001      /* 标志掩码：继续*/

/* FCS检查选项值
*/
#define L2CAP_CFG_FCS_BYPASS            0       /* 在流媒体或ERTM模式下绕过FCS*/
#define L2CAP_CFG_FCS_USE               1       /* 在流媒体或ERTM模式下使用FCS[默认]*/

/* 配置的默认值
*/
#define L2CAP_NO_AUTOMATIC_FLUSH        0xFFFF
#define L2CAP_NO_RETRANSMISSION         0x0001

#define L2CAP_DEFAULT_MTU               (672)
#define L2CAP_DEFAULT_FLUSH_TO          L2CAP_NO_AUTOMATIC_FLUSH
#define L2CAP_DEFAULT_SERV_TYPE         1
#define L2CAP_DEFAULT_TOKEN_RATE        0
#define L2CAP_DEFAULT_BUCKET_SIZE       0
#define L2CAP_DEFAULT_PEAK_BANDWIDTH    0
#define L2CAP_DEFAULT_LATENCY           0xFFFFFFFF
#define L2CAP_DEFAULT_DELAY             0xFFFFFFFF
#define L2CAP_DEFAULT_FCS               L2CAP_CFG_FCS_USE


/* 定义L2CAP断开连接结果代码
*/
#define L2CAP_DISC_OK                   0
#define L2CAP_DISC_TIMEOUT              0xEEEE

/* 定义L2CAP信息和结果代码
*/
#define L2CAP_INFO_RESP_RESULT_SUCCESS          0
#define L2CAP_INFO_RESP_RESULT_NOT_SUPPORTED    1

/* 定义信息请求和响应的信息类型字段
*/
#define L2CAP_CONNLESS_MTU_INFO_TYPE      0x0001
#define L2CAP_EXTENDED_FEATURES_INFO_TYPE 0x0002    /* 用于信息请求/响应*/
#define L2CAP_FIXED_CHANNELS_INFO_TYPE    0x0003    /* 用于AMP*/

#define L2CAP_CONNLESS_MTU_INFO_SIZE           2    /* 无连接MTU大小*/
#define L2CAP_EXTENDED_FEATURES_ARRAY_SIZE     4    /* 扩展功能阵列大小*/
#define L2CAP_FIXED_CHNL_ARRAY_SIZE            8    /* 固定通道阵列大小*/

/* 扩展功能掩码位
*/
#define L2CAP_EXTFEA_RTRANS         0x00000001    /* 重新传输模式（不支持）*/
#define L2CAP_EXTFEA_FC             0x00000002    /* 流量控制模式（不支持）*/
#define L2CAP_EXTFEA_QOS            0x00000004
#define L2CAP_EXTFEA_ENH_RETRANS    0x00000008    /* 增强的重传模式*/
#define L2CAP_EXTFEA_STREAM_MODE    0x00000010    /* 流式处理模式*/
#define L2CAP_EXTFEA_NO_CRC         0x00000020    /* 可选FCS（如果设置不需要FCS）*/
#define L2CAP_EXTFEA_EXT_FLOW_SPEC  0x00000040    /* 扩展流量规格*/
#define L2CAP_EXTFEA_FIXED_CHNLS    0x00000080    /* 固定频道*/
#define L2CAP_EXTFEA_EXT_WINDOW     0x00000100    /* 扩展窗口大小*/
#define L2CAP_EXTFEA_UCD_RECEPTION  0x00000200    /* 单播无连接数据接收*/

/* 信息响应中使用的LE支持功能的掩码（默认为无）*/
#ifndef L2CAP_BLE_EXTFEA_MASK
#define L2CAP_BLE_EXTFEA_MASK 0
#endif

/* 定义一个值，告诉L2CAP使用默认HCI ACL缓冲区大小*/
#define L2CAP_INVALID_ERM_BUF_SIZE      0

/* 定义一个值，告诉L2CAP使用默认MPS*/
#define L2CAP_DEFAULT_ERM_MPS           0x0000

#define L2CAP_FCR_OVERHEAD         2   /* 控制字*/
#define L2CAP_FCS_LEN              2   /* FCS占用2个字节*/
#define L2CAP_SDU_LEN_OVERHEAD     2   /* SDU长度字段为2字节*/
#define L2CAP_SDU_LEN_OFFSET       2   /* SDU长度偏移量为2字节*/
#define L2CAP_EXT_CONTROL_OVERHEAD 4   /* 扩展控制字段*/
#define L2CAP_MAX_HEADER_FCS       (L2CAP_PKT_OVERHEAD + L2CAP_EXT_CONTROL_OVERHEAD + L2CAP_SDU_LEN_OVERHEAD + L2CAP_FCS_LEN)
/* 长度（2），信道（2）、控制（4），SDU长度（2，FCS（2）*/
/* 为了优化这一点，它必须是L2CAP PDU长度的倍数，并且与每个数据包中包含L2CAP报头的3DH5 air相匹配-为了与后者相匹配，添加了-5
 */
#define L2CAP_MAX_SDU_LENGTH     (8080 + 26 - (L2CAP_MIN_OFFSET + 6))
#define L2CAP_MAX_BUF_SIZE       (10240 + 24)

/* L2CAP_MIN_OFFSET的一部分不是L2CAP的一部分
*/
#define L2CAP_OFFSET_WO_L2HDR  (L2CAP_MIN_OFFSET-(L2CAP_PKT_OVERHEAD+L2CAP_FCR_OVERHEAD))

/* 控制字中的SAR位
*/
#define L2CAP_FCR_UNSEG_SDU    0x0000   /* 未分段PDU的控制字开头*/
#define L2CAP_FCR_START_SDU    0x4000   /* …用于启动指定SDU的PDU*/
#define L2CAP_FCR_END_SDU      0x8000   /* …用于结束分段SDU的PDU*/
#define L2CAP_FCR_CONT_SDU     0xc000   /* …用于分段SDU的延续PDU*/

/* 监控框架类型
*/
#define L2CAP_FCR_SUP_RR        0x0000   /* 监控框架-右后*/
#define L2CAP_FCR_SUP_REJ       0x0001   /* 监管框架-REJ*/
#define L2CAP_FCR_SUP_RNR       0x0002   /* 监控框架-RNR*/
#define L2CAP_FCR_SUP_SREJ      0x0003   /* 监控框架-SREJ*/

#define L2CAP_FCR_SAR_BITS           0xC000    /* 从控制字中获取SAR位的掩码*/
#define L2CAP_FCR_SAR_BITS_SHIFT     14        /* 右移位以从ctrl字中获得SAR位*/

#define L2CAP_FCR_S_FRAME_BIT         0x0001   /* 用于检查PDU是否为S帧的掩码*/
#define L2CAP_FCR_REQ_SEQ_BITS        0x3F00   /* 掩码以从控制字获取req-seq*/
#define L2CAP_FCR_REQ_SEQ_BITS_SHIFT  8        /* 右移位以从ctrl字获得req-seq*/
#define L2CAP_FCR_TX_SEQ_BITS         0x007E   /* 从控制字获取tx-seq时的掩码*/
#define L2CAP_FCR_TX_SEQ_BITS_SHIFT   1        /* 右移位以从ctrl字获取tx-seq*/

#define L2CAP_FCR_F_BIT               0x0080   /* 控制字中的F位（Sup和I帧）*/
#define L2CAP_FCR_P_BIT               0x0010   /* 控制字中的P位（仅限Sup帧）*/

#define L2CAP_FCR_F_BIT_SHIFT         7
#define L2CAP_FCR_P_BIT_SHIFT         4

#define L2CAP_FCR_SEG_BITS            0xC000   /* 掩码以从ctrl字中获取分段位*/
#define L2CAP_FCR_SUP_SHIFT           2        /* 右移位以从ctrl字中获取S位*/
#define L2CAP_FCR_SUP_BITS            0x000C   /* 掩码以从ctrl字中获取监控位*/

#define L2CAP_FCR_INIT_CRC            0   /* CRC寄存器的初始状态*/
#define L2CAP_FCR_SEQ_MODULO          0x3F     /* 序列号掩码（范围0-63）*/

#endif

