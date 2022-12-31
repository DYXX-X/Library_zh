/**
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_SVC_ANS_
#define H_BLE_SVC_ANS_

struct ble_hs_cfg;

/* 16位警报通知服务UUID*/
#define BLE_SVC_ANS_UUID16                                  0x1811

/* 16位警报通知服务特征UUID*/
#define BLE_SVC_ANS_CHR_UUID16_SUP_NEW_ALERT_CAT            0x2a47
#define BLE_SVC_ANS_CHR_UUID16_NEW_ALERT                    0x2a46
#define BLE_SVC_ANS_CHR_UUID16_SUP_UNR_ALERT_CAT            0x2a48
#define BLE_SVC_ANS_CHR_UUID16_UNR_ALERT_STAT               0x2a45
#define BLE_SVC_ANS_CHR_UUID16_ALERT_NOT_CTRL_PT            0x2a44

/* 警报通知服务类别ID位掩码
 *
 * TODO:添加剩余的2个可选类别*/
#define BLE_SVC_ANS_CAT_BM_NONE                             0x00
#define BLE_SVC_ANS_CAT_BM_SIMPLE_ALERT                     0x01
#define BLE_SVC_ANS_CAT_BM_EMAIL                            0x02
#define BLE_SVC_ANS_CAT_BM_NEWS                             0x04
#define BLE_SVC_ANS_CAT_BM_CALL                             0x08
#define BLE_SVC_ANS_CAT_BM_MISSED_CALL                      0x10
#define BLE_SVC_ANS_CAT_BM_SMS                              0x20
#define BLE_SVC_ANS_CAT_BM_VOICE_MAIL                       0x40
#define BLE_SVC_ANS_CAT_BM_SCHEDULE                         0x80

/* 警报通知服务类别ID
 *
 * TODO:添加剩余的2个可选类别*/
#define BLE_SVC_ANS_CAT_ID_SIMPLE_ALERT                     0
#define BLE_SVC_ANS_CAT_ID_EMAIL                            1
#define BLE_SVC_ANS_CAT_ID_NEWS                             2
#define BLE_SVC_ANS_CAT_ID_CALL                             3
#define BLE_SVC_ANS_CAT_ID_MISSED_CALL                      4
#define BLE_SVC_ANS_CAT_ID_SMS                              5
#define BLE_SVC_ANS_CAT_ID_VOICE_MAIL                       6
#define BLE_SVC_ANS_CAT_ID_SCHEDULE                         7

/* 有效ANS类别的数量
 *
 * TODO:添加剩余的2个可选类别*/
#define BLE_SVC_ANS_CAT_NUM                                 8

/* 警报通知控制点命令ID*/
#define BLE_SVC_ANS_CMD_EN_NEW_ALERT_CAT                    0
#define BLE_SVC_ANS_CMD_EN_UNR_ALERT_CAT                    1
#define BLE_SVC_ANS_CMD_DIS_NEW_ALERT_CAT                   2
#define BLE_SVC_ANS_CMD_DIS_UNR_ALERT_CAT                   3
#define BLE_SVC_ANS_CMD_NOT_NEW_ALERT_IMMEDIATE             4
#define BLE_SVC_ANS_CMD_NOT_UNR_ALERT_IMMEDIATE             5

/* 错误定义*/
#define BLE_SVC_ANS_ERR_CMD_NOT_SUPPORTED                   0xA0

void ble_svc_ans_on_gap_connect(uint16_t conn_handle);

int ble_svc_ans_new_alert_add(uint8_t cat_id,
                              const char * info_str);
int ble_svc_ans_unr_alert_add(uint8_t cat_id);

void ble_svc_ans_init(void);

#endif


