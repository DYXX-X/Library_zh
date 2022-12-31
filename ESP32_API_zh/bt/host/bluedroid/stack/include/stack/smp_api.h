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

/******************************************************************************
 * 此文件包含SMP API函数外部定义。
 *
 ******************************************************************************/
#ifndef SMP_API_H
#define SMP_API_H

#include "common/bt_target.h"

#define SMP_PIN_CODE_LEN_MAX    PIN_CODE_LEN
#define SMP_PIN_CODE_LEN_MIN    6

// #如果SMP_INCLUDED==真
/* SMP命令代码*/
#define SMP_OPCODE_PAIRING_REQ            0x01
#define SMP_OPCODE_PAIRING_RSP            0x02
#define SMP_OPCODE_CONFIRM                0x03
#define SMP_OPCODE_RAND                   0x04
#define SMP_OPCODE_PAIRING_FAILED         0x05
#define SMP_OPCODE_ENCRYPT_INFO           0x06
#define SMP_OPCODE_MASTER_ID              0x07
#define SMP_OPCODE_IDENTITY_INFO          0x08
#define SMP_OPCODE_ID_ADDR                0x09
#define SMP_OPCODE_SIGN_INFO              0x0A
#define SMP_OPCODE_SEC_REQ                0x0B
#define SMP_OPCODE_PAIR_PUBLIC_KEY        0x0C
#define SMP_OPCODE_PAIR_DHKEY_CHECK       0x0D
#define SMP_OPCODE_PAIR_KEYPR_NOTIF       0x0E
#define SMP_OPCODE_MAX                    SMP_OPCODE_PAIR_KEYPR_NOTIF
#define SMP_OPCODE_MIN                    SMP_OPCODE_PAIRING_REQ
#define SMP_OPCODE_PAIR_COMMITM           0x0F
// #结束符

/* SMP事件类型*/
#define SMP_IO_CAP_REQ_EVT      1       /* IO能力请求事件*/
#define SMP_SEC_REQUEST_EVT     2       /* SMP配对请求*/
#define SMP_PASSKEY_NOTIF_EVT   3       /* 密钥通知事件*/
#define SMP_PASSKEY_REQ_EVT     4       /* 密钥请求事件*/
#define SMP_OOB_REQ_EVT         5       /* OOB请求事件*/
#define SMP_NC_REQ_EVT          6       /* 数字比较请求事件*/
#define SMP_COMPLT_EVT          7       /* SMP完成事件*/
#define SMP_PEER_KEYPR_NOT_EVT  8       /* 收到对等按键通知事件*/
#define SMP_SC_OOB_REQ_EVT      9       /* SC OOB请求事件（本地和对等OOB数据*/
/* 可以预期为响应）*/
#define SMP_SC_LOC_OOB_DATA_UP_EVT  10  /* SC OOB本地数据集已创建*/
/* （作为SMP_CrLocScOobData（…）的结果）*/
#define SMP_BR_KEYS_REQ_EVT     12      /* SMP over BR密钥请求事件*/
typedef UINT8   tSMP_EVT;


/* 配对失败原因码*/
#define SMP_PASSKEY_ENTRY_FAIL      0x01
#define SMP_OOB_FAIL                0x02
#define SMP_PAIR_AUTH_FAIL          0x03
#define SMP_CONFIRM_VALUE_ERR       0x04
#define SMP_PAIR_NOT_SUPPORT        0x05
#define SMP_ENC_KEY_SIZE            0x06
#define SMP_INVALID_CMD             0x07
#define SMP_PAIR_FAIL_UNKNOWN       0x08
#define SMP_REPEATED_ATTEMPTS       0x09
#define SMP_INVALID_PARAMETERS      0x0A
#define SMP_DHKEY_CHK_FAIL          0x0B
#define SMP_NUMERIC_COMPAR_FAIL     0x0C
#define SMP_BR_PARING_IN_PROGR      0x0D
#define SMP_XTRANS_DERIVE_NOT_ALLOW 0x0E
#define SMP_MAX_FAIL_RSN_PER_SPEC   SMP_XTRANS_DERIVE_NOT_ALLOW

/* 自定义错误代码*/
#define SMP_PAIR_INTERNAL_ERR       (SMP_MAX_FAIL_RSN_PER_SPEC + 0x01) /* 0x0F格式*/

/* 0x0F未知IO能力，无法决定关联模型*/
#define SMP_UNKNOWN_IO_CAP          (SMP_MAX_FAIL_RSN_PER_SPEC + 0x02) /* 0x10像素*/

#define SMP_INIT_FAIL               (SMP_MAX_FAIL_RSN_PER_SPEC + 0x03) /* 0x11像素*/
#define SMP_CONFIRM_FAIL            (SMP_MAX_FAIL_RSN_PER_SPEC + 0x04) /* 0x12像素*/
#define SMP_BUSY                    (SMP_MAX_FAIL_RSN_PER_SPEC + 0x05) /* 0x13像素*/
#define SMP_ENC_FAIL                (SMP_MAX_FAIL_RSN_PER_SPEC + 0x06) /* 0x14像素*/
#define SMP_STARTED                 (SMP_MAX_FAIL_RSN_PER_SPEC + 0x07) /* 0x15像素*/
#define SMP_RSP_TIMEOUT             (SMP_MAX_FAIL_RSN_PER_SPEC + 0x08) /* 0x16像素*/
#define SMP_DIV_NOT_AVAIL           (SMP_MAX_FAIL_RSN_PER_SPEC + 0x09) /* 0x17像素*/

/* 0x17未指定失败原因*/
#define SMP_FAIL                    (SMP_MAX_FAIL_RSN_PER_SPEC + 0x0A) /* 0x18像素*/

#define SMP_CONN_TOUT               (SMP_MAX_FAIL_RSN_PER_SPEC + 0x0B) /* 0x19像素*/
#define SMP_SUCCESS                 0

typedef UINT8 tSMP_STATUS;


/* 设备IO能力*/
#define SMP_IO_CAP_OUT      BTM_IO_CAP_OUT   /* 仅显示*/
#define SMP_IO_CAP_IO       BTM_IO_CAP_IO   /* 显示是否*/
#define SMP_IO_CAP_IN       BTM_IO_CAP_IN   /* 仅键盘*/
#define SMP_IO_CAP_NONE     BTM_IO_CAP_NONE   /* 无输入无输出*/
#define SMP_IO_CAP_KBDISP   BTM_IO_CAP_KBDISP   /* 键盘显示器*/
#define SMP_IO_CAP_MAX      BTM_IO_CAP_MAX
typedef UINT8  tSMP_IO_CAP;

#ifndef SMP_DEFAULT_IO_CAPS
#define SMP_DEFAULT_IO_CAPS     SMP_IO_CAP_KBDISP
#endif

/* OOB数据是否存在*/
enum {
    SMP_OOB_NONE,
    SMP_OOB_PRESENT,
    SMP_OOB_UNKNOWN
};
typedef UINT8  tSMP_OOB_FLAG;

/* 应用程序所需的OOB数据类型*/
enum {
    SMP_OOB_INVALID_TYPE,
    SMP_OOB_PEER,
    SMP_OOB_LOCAL,
    SMP_OOB_BOTH
};
typedef UINT8   tSMP_OOB_DATA_TYPE;

#define SMP_AUTH_NO_BOND        0x00
#define SMP_AUTH_GEN_BOND       0x01 //todo sdh将GEN_BOND更改为BOND

/* SMP认证要求*/
#define SMP_AUTH_YN_BIT         (1 << 2)
#define SMP_SC_SUPPORT_BIT      (1 << 3)
#define SMP_KP_SUPPORT_BIT      (1 << 4)

#define SMP_AUTH_MASK    (SMP_AUTH_GEN_BOND|SMP_AUTH_YN_BIT|SMP_SC_SUPPORT_BIT|SMP_KP_SUPPORT_BIT)

#define SMP_AUTH_BOND           SMP_AUTH_GEN_BOND

/* 无MITM，无绑定，仅加密*/
#define SMP_AUTH_NB_ENC_ONLY    0x00 //(SMP_AUTH_MASK | BTM_AUTH_SP_NO)

/* MITM，无绑定，使用IO能力确定身份验证程序*/
#define SMP_AUTH_NB_IOCAP       (SMP_AUTH_NO_BOND | SMP_AUTH_YN_BIT)

/* 无MITM，通用绑定，仅加密*/
#define SMP_AUTH_GB_ENC_ONLY    (SMP_AUTH_GEN_BOND )

/* MITM，通用绑定，使用IO能力确定身份验证程序*/
#define SMP_AUTH_GB_IOCAP       (SMP_AUTH_GEN_BOND | SMP_AUTH_YN_BIT)

/* 安全连接，无MITM，无粘结*/
#define SMP_AUTH_SC_ENC_ONLY    (SMP_SC_SUPPORT_BIT)

/* 安全连接，无MITM，粘接*/
#define SMP_AUTH_SC_GB          (SMP_SC_SUPPORT_BIT | SMP_AUTH_GEN_BOND)

/* 安全连接，MITM，无粘结*/
#define SMP_AUTH_SC_MITM_NB     (SMP_SC_SUPPORT_BIT | SMP_AUTH_YN_BIT | SMP_AUTH_NO_BOND)

/* 安全连接、MITM、粘接*/
#define SMP_AUTH_SC_MITM_GB     (SMP_SC_SUPPORT_BIT | SMP_AUTH_YN_BIT | SMP_AUTH_GEN_BOND)

/* 所有AuthReq RFU位均设置为1-注意：未设置Bonding_Flags中的保留位*/
#define SMP_AUTH_ALL_RFU_SET    0xF8

typedef UINT8 tSMP_AUTH_REQ;

#define SMP_SEC_NONE                 0
#define SMP_SEC_UNAUTHENTICATE      (1 << 0)
#define SMP_SEC_AUTHENTICATED       (1 << 2)
typedef UINT8 tSMP_SEC_LEVEL;

/* 最大加密密钥大小范围*/
#define SMP_ENCR_KEY_SIZE_MIN       7
#define SMP_ENCR_KEY_SIZE_MAX       16

/* SMP密钥类型*/
#define SMP_SEC_KEY_TYPE_ENC                (1 << 0)    /* 加密密钥*/
#define SMP_SEC_KEY_TYPE_ID                 (1 << 1)    /* 身份密钥*/
#define SMP_SEC_KEY_TYPE_CSRK               (1 << 2)    /* 从属CSRK*/
#define SMP_SEC_KEY_TYPE_LK                 (1 << 3)    /* BR/EDR链接键*/
typedef UINT8 tSMP_KEYS;

#define SMP_BR_SEC_DEFAULT_KEY   (SMP_SEC_KEY_TYPE_ENC | SMP_SEC_KEY_TYPE_ID | \
                                  SMP_SEC_KEY_TYPE_CSRK)

/* 默认安全密钥分发值*/
#define SMP_SEC_DEFAULT_KEY      (SMP_SEC_KEY_TYPE_ENC | SMP_SEC_KEY_TYPE_ID | \
                                  SMP_SEC_KEY_TYPE_CSRK | SMP_SEC_KEY_TYPE_LK)

#define SMP_SC_KEY_STARTED      0   /* 密钥输入已启动*/
#define SMP_SC_KEY_ENTERED      1   /* 输入密钥数字*/
#define SMP_SC_KEY_ERASED       2   /* 密钥数字已擦除*/
#define SMP_SC_KEY_CLEARED      3   /* 密钥已清除*/
#define SMP_SC_KEY_COMPLT       4   /* 密钥输入已完成*/
#define SMP_SC_KEY_OUT_OF_RANGE 5   /* 超出范围*/
typedef UINT8 tSMP_SC_KEY_TYPE;

/* BTM_SP_IO_REQ_EVT的数据类型*/
typedef struct {
    tSMP_IO_CAP     io_cap;         /* 本地IO能力*/
    tSMP_OOB_FLAG   oob_data;       /* 对等设备存在OOB数据（本地）*/
    tSMP_AUTH_REQ   auth_req;       /* 需要身份验证（对于本地设备）*/
    UINT8           max_key_size;   /* 最大加密密钥大小*/
    tSMP_KEYS       init_keys;      /* 要分发的启动器密钥*/
    tSMP_KEYS       resp_keys;      /* 应答器密钥*/
} tSMP_IO_REQ;

typedef struct {
    tSMP_STATUS reason;
    tSMP_SEC_LEVEL sec_level;
    BOOLEAN is_pair_cancel;
    BOOLEAN smp_over_br;
    tSMP_AUTH_REQ auth_mode;
} tSMP_CMPL;

typedef struct {
    BT_OCTET32  x;
    BT_OCTET32  y;
} tSMP_PUBLIC_KEY;

/* 与通过OOB接口发送给对等方的信息相关联的数据*/
typedef struct {
    BOOLEAN         present;
    BT_OCTET16      randomizer;
    BT_OCTET16      commitment;

    tBLE_BD_ADDR    addr_sent_to;
    BT_OCTET32      private_key_used;   /* 用于计算：*/
    /* publ_key_used=P-256（private_key_used，curve_p256.G）-将其发送到*/
    /* 另一侧*/
    /* dhkey=P-256（private_key_used，来自另一侧的公钥rcvd）*/
    tSMP_PUBLIC_KEY publ_key_used; /* P-256（专用密钥，曲线p256.G）*/
} tSMP_LOC_OOB_DATA;

/* 与通过OOB接口从对等方接收的信息相关联的数据*/
typedef struct {
    BOOLEAN         present;
    BT_OCTET16      randomizer;
    BT_OCTET16      commitment;
    tBLE_BD_ADDR    addr_rcvd_from;
} tSMP_PEER_OOB_DATA;

typedef struct {
    tSMP_LOC_OOB_DATA   loc_oob_data;
    tSMP_PEER_OOB_DATA  peer_oob_data;
} tSMP_SC_OOB_DATA;


typedef union {
    UINT32          passkey;
    tSMP_IO_REQ     io_req;     /* IO请求*/
    tSMP_CMPL       cmplt;
    tSMP_OOB_DATA_TYPE  req_oob_type;
    tSMP_LOC_OOB_DATA   loc_oob_data;
} tSMP_EVT_DATA;


/* AES加密输出*/
typedef struct {
    UINT8   status;
    UINT8   param_len;
    UINT16  opcode;
    UINT8   param_buf[BT_OCTET16_LEN];
} tSMP_ENC;

/* 安全管理器事件-当安全管理器相关事件发生时由堆栈调用。*/
typedef UINT8 (tSMP_CALLBACK) (tSMP_EVT event, BD_ADDR bd_addr, tSMP_EVT_DATA *p_data);

/* CMAC算法的回调函数
*/
typedef void (tCMAC_CMPL_CBACK)(UINT8 *p_mac, UINT16 tlen, UINT32 sign_counter);

/*****************************************************************************
**  外部函数声明
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif
/* SMP的API*/

/*******************************************************************************
** 功能SMP_Init
**
** 说明此功能初始化SMP单元。
**
** 返回void
**
*******************************************************************************/
extern void SMP_Init(void);

/*******************************************************************************
** 功能SMP_Free
**
** 说明此功能可解除SMP单元的初始化。
**
** 返回void
**
*******************************************************************************/
extern void SMP_Free(void);


/*******************************************************************************
** 函数SMP_SetTraceLevel
**
** 说明此函数设置SMP的跟踪级别。如果使用值0xFF调用，则只返回当前跟踪级别。
**
** 返回新的或当前的跟踪级别
**
*******************************************************************************/
extern UINT8 SMP_SetTraceLevel (UINT8 new_level);

/*******************************************************************************
** 功能SMP_寄存器
**
** 说明此函数注册SMP服务回调。
**
** 返回void
**
*******************************************************************************/
extern BOOLEAN SMP_Register (tSMP_CALLBACK *p_cback);

/*******************************************************************************
** 功能SMP_Pair
**
** 说明调用此函数以启动SMP配对。
**
** 如果绑定已启动，则返回SMP_STARTED，否则返回异常。
**
*******************************************************************************/
extern tSMP_STATUS SMP_Pair (BD_ADDR bd_addr);

/*******************************************************************************
** 函数SMP_BR_PairWith
**
** 说明调用此函数以通过BR/EDR启动SMP配对。
**
** 如果配对已启动，则返回SMP_STARTED，否则返回失败原因。
**
*******************************************************************************/
extern tSMP_STATUS SMP_BR_PairWith (BD_ADDR bd_addr);

/*******************************************************************************
** 功能SMP_PairCancel
**
** 说明调用此函数以取消SMP配对。
**
** 返回TRUE-配对已取消
**
*******************************************************************************/
extern  BOOLEAN SMP_PairCancel (BD_ADDR bd_addr);

/*******************************************************************************
** 函数SMP_安全授权
**
** 说明调用此函数以授予安全进程。
**
** 参数bd_addr-对等设备bd地址。res-如果成功，则操作SMP_SUCCESS的结果。否则，SMP_REPEATED_ATTEMPTS尝试次数太多。
**
** 返回None
**
*******************************************************************************/
extern void SMP_SecurityGrant(BD_ADDR bd_addr, UINT8 res);

/*******************************************************************************
** 功能SMP_PasskeyReply
**
** 说明此函数在Security Manager向应用程序提交密钥请求后调用。
**
** 参数：bd_addr-请求PIN的设备的地址res-操作结果SMP_SUCCESS if SUCCESS passkey-BTM_MIN_passkey_VAL（0）-BTM_MAX_passkey-VAL（999999（0xF423F））范围内的数值。
**
*******************************************************************************/
extern void SMP_PasskeyReply (BD_ADDR bd_addr, UINT8 res, UINT32 passkey);

/*******************************************************************************
** 功能SMP_SetStaticPasskey
**
** 说明调用此函数以设置静态密钥
**
** 参数：add-add为TRUE时设置静态密钥add为FALSE时清除静态密钥passkey-静态密钥
**
**
*******************************************************************************/
extern void SMP_SetStaticPasskey (BOOLEAN add, UINT32 passkey);

/*******************************************************************************
** 功能SMP_ConfirmReply
**
** 说明此函数在Security Manager向应用程序提交数字比较请求后调用。
**
** 参数：bd_addr-请求数字比较的设备的地址res-比较结果SMP_SUCCESS（如果成功）
**
*******************************************************************************/
extern void SMP_ConfirmReply (BD_ADDR bd_addr, UINT8 res);

/*******************************************************************************
** 函数SMP_OobDataReply
**
** 说明调用此函数以响应SMP_OOB_REQ_EVT为SMP提供OOB数据
**
** 参数：bd_addr-对等设备的地址res-操作结果SMP_SUCCESS if SUCCESS p_data-SM Randomizer C。
**
*******************************************************************************/
extern void SMP_OobDataReply(BD_ADDR bd_addr, tSMP_STATUS res, UINT8 len,
                             UINT8 *p_data);

/*******************************************************************************
** 函数SMP_ScureConnectionOobDataReply
**
** 说明调用此函数以响应SMP_SC_OOB_REQ_EVT为SMP提供SC OOB数据
**
** 参数：p_data-指向数据的指针
**
*******************************************************************************/
extern void SMP_SecureConnectionOobDataReply(UINT8 *p_data);

/*******************************************************************************
** 功能SMP_Encrypt
**
** 说明调用此函数以使用指定密钥加密数据
**
** 参数：key-指向密钥[0]的指针表示MSB key_len-密钥长度plain_text-指向要加密的数据的指针plain_text[0]表示MSB pt_len-明文长度p_out-指向加密输出的指针
**
**  返回布尔值-TRUE：加密成功
*******************************************************************************/
extern BOOLEAN SMP_Encrypt (UINT8 *key, UINT8 key_len,
                            UINT8 *plain_text, UINT8 pt_len,
                            tSMP_ENC *p_out);

/*******************************************************************************
** 功能SMP_KeypressNotification
**
** 说明调用此函数以通知SM有关按键通知。
**
** 参数：bd_addr-要向value发送按键通知的设备的地址-按键通知参数值
**
*******************************************************************************/
extern void SMP_KeypressNotification (BD_ADDR bd_addr, UINT8 value);

/*******************************************************************************
** 函数SMP_CreateLocalSecureConnectionsObData
**
** 说明调用此函数以开始创建本地SC OOB数据集（tSMP_LOC_OOB_data）。
**
** 参数：bd_addr-要向其发送OOB数据块的设备的地址。
**
**  返回布尔值-TRUE：开始创建本地SC OOB数据集。
*******************************************************************************/
extern BOOLEAN SMP_CreateLocalSecureConnectionsOobData (
    tBLE_BD_ADDR *addr_to_send_to);

#ifdef __cplusplus
}
#endif
#endif /* SMP_API_H */

