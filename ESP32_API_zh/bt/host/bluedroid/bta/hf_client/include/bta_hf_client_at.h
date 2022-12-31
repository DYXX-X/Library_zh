/******************************************************************************
 * 版权所有（c）2014 Android开源项目版权所有（c）2003-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/*****************************************************************************
**  数据类型
*****************************************************************************/
#include "common/bt_target.h"
#if (BTA_HF_INCLUDED == TRUE)

/* AT命令参数的ASCII字符串*/
#define BTA_HF_CLIENT_AT_MAX_LEN        512

/* AT命令表元素*/
typedef struct {
    const char  *p_cmd;         /* AT命令字符串*/
    UINT8       arg_type;       /* 允许的参数类型语法*/
    UINT8       fmt;            /* arg是int还是string*/
    UINT8       min;            /* int arg的最小值*/
    INT16       max;            /* int arg的最大值*/
} tBTA_AG_AT_CMD;

/* 解析命令时执行的回调函数*/
typedef void (tBTA_AG_AT_CMD_CBACK)(void *p_user, UINT16 cmd, UINT8 arg_type,
                                    char *p_arg, INT16 int_arg);

/* 执行回调函数以发送“ERROR”结果代码*/
typedef void (tBTA_AG_AT_ERR_CBACK)(void *p_user, BOOLEAN unknown, char *p_arg);

enum {
    BTA_HF_CLIENT_AT_NONE,
    BTA_HF_CLIENT_AT_BRSF,
    BTA_HF_CLIENT_AT_BAC,
    BTA_HF_CLIENT_AT_CIND,
    BTA_HF_CLIENT_AT_CIND_STATUS,
    BTA_HF_CLIENT_AT_CMER,
    BTA_HF_CLIENT_AT_CHLD,
    BTA_HF_CLIENT_AT_CMEE,
    BTA_HF_CLIENT_AT_BIA,
    BTA_HF_CLIENT_AT_CLIP,
    BTA_HF_CLIENT_AT_CCWA,
    BTA_HF_CLIENT_AT_COPS,
    BTA_HF_CLIENT_AT_CLCC,
    BTA_HF_CLIENT_AT_BVRA,
    BTA_HF_CLIENT_AT_VGS,
    BTA_HF_CLIENT_AT_VGM,
    BTA_HF_CLIENT_AT_ATD,
    BTA_HF_CLIENT_AT_BLDN,
    BTA_HF_CLIENT_AT_ATA,
    BTA_HF_CLIENT_AT_CHUP,
    BTA_HF_CLIENT_AT_BTRH,
    BTA_HF_CLIENT_AT_VTS,
    BTA_HF_CLIENT_AT_BCC,
    BTA_HF_CLIENT_AT_BCS,
    BTA_HF_CLIENT_AT_CNUM,
    BTA_HF_CLIENT_AT_NREC,
    BTA_HF_CLIENT_AT_BINP,
};

typedef UINT8 tBTA_HF_CLIENT_AT_CMD;

/* 接收的AT事件字符串的最大组合缓冲区*/
#define BTA_HF_CLIENT_AT_PARSER_MAX_LEN        4096

/* 此结构保存排队等待发送的准备好的AT命令*/
struct queued_at_cmd {
    tBTA_HF_CLIENT_AT_CMD cmd;
    char buf[BTA_HF_CLIENT_AT_MAX_LEN];
    UINT16 buf_len;
    struct queued_at_cmd *next;
};
typedef struct queued_at_cmd tBTA_HF_CLIENT_AT_QCMD;

/* 指示器的最大数量*/
#define BTA_HF_CLIENT_AT_INDICATOR_COUNT 20

/* AT命令解析控制块*/
typedef struct {
    char                    buf[BTA_HF_CLIENT_AT_PARSER_MAX_LEN + 1]; /* 额外的字节始终在末尾有\0*/
    unsigned int            offset;
    tBTA_HF_CLIENT_AT_CMD   current_cmd;
    tBTA_HF_CLIENT_AT_QCMD  *queued_cmd;

    TIMER_LIST_ENT          resp_timer;    /* AT响应计时器*/
    BOOLEAN                 resp_timer_on; /* 如果AT响应计时器激活，则为TRUE*/

    TIMER_LIST_ENT          hold_timer;    /* AT保持计时器*/
    BOOLEAN                 hold_timer_on; /* 如果AT保持计时器激活，则为TRUE*/

    /* CIND：查找表，用于存储传入指示符的序列及其值，因此当它们的值稍后出现时，我们知道序列中的哪个值与特定指示符匹配*/
    int                     indicator_lookup[BTA_HF_CLIENT_AT_INDICATOR_COUNT];

} tBTA_HF_CLIENT_AT_CB;

/*****************************************************************************
**  功能
*****************************************************************************/

void bta_hf_client_at_init(void);
void bta_hf_client_at_reset(void);
#endif /* #如果（BTA_HF_INCLUDE==真）*/

