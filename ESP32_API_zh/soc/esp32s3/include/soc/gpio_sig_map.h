// 版权所有2017-2021 Espressif Systems（Shanghai）PTE LTD
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。
#ifndef _SOC_GPIO_SIG_MAP_H_
#define _SOC_GPIO_SIG_MAP_H_

#define SPIQ_IN_IDX                   0
#define SPIQ_OUT_IDX                  0
#define SPID_IN_IDX                   1
#define SPID_OUT_IDX                  1
#define SPIHD_IN_IDX                  2
#define SPIHD_OUT_IDX                 2
#define SPIWP_IN_IDX                  3
#define SPIWP_OUT_IDX                 3
#define SPICLK_OUT_IDX                4
#define SPICS0_OUT_IDX                5
#define SPICS1_OUT_IDX                6
#define SPID4_IN_IDX                  7
#define SPID4_OUT_IDX                 7
#define SPID5_IN_IDX                  8
#define SPID5_OUT_IDX                 8
#define SPID6_IN_IDX                  9
#define SPID6_OUT_IDX                 9
#define SPID7_IN_IDX                  10
#define SPID7_OUT_IDX                 10
#define SPIDQS_IN_IDX                 11
#define SPIDQS_OUT_IDX                11
#define U0RXD_IN_IDX                  12
#define U0TXD_OUT_IDX                 12
#define U0CTS_IN_IDX                  13
#define U0RTS_OUT_IDX                 13
#define U0DSR_IN_IDX                  14
#define U0DTR_OUT_IDX                 14
#define U1RXD_IN_IDX                  15
#define U1TXD_OUT_IDX                 15
#define U1CTS_IN_IDX                  16
#define U1RTS_OUT_IDX                 16
#define U1DSR_IN_IDX                  17
#define U1DTR_OUT_IDX                 17
#define U2RXD_IN_IDX                  18
#define U2TXD_OUT_IDX                 18
#define U2CTS_IN_IDX                  19
#define U2RTS_OUT_IDX                 19
#define U2DSR_IN_IDX                  20
#define U2DTR_OUT_IDX                 20
#define I2S1_MCLK_IN_IDX              21
#define I2S1_MCLK_OUT_IDX             21
#define I2S0O_BCK_IN_IDX              22
#define I2S0O_BCK_OUT_IDX             22
#define I2S0_MCLK_IN_IDX              23
#define I2S0_MCLK_OUT_IDX             23
#define I2S0O_WS_IN_IDX               24
#define I2S0O_WS_OUT_IDX              24
#define I2S0I_SD_IN_IDX               25
#define I2S0O_SD_OUT_IDX              25
#define I2S0I_BCK_IN_IDX              26
#define I2S0I_BCK_OUT_IDX             26
#define I2S0I_WS_IN_IDX               27
#define I2S0I_WS_OUT_IDX              27
#define I2S1O_BCK_IN_IDX              28
#define I2S1O_BCK_OUT_IDX             28
#define I2S1O_WS_IN_IDX               29
#define I2S1O_WS_OUT_IDX              29
#define I2S1I_SD_IN_IDX               30
#define I2S1O_SD_OUT_IDX              30
#define I2S1I_BCK_IN_IDX              31
#define I2S1I_BCK_OUT_IDX             31
#define I2S1I_WS_IN_IDX               32
#define I2S1I_WS_OUT_IDX              32
#define PCNT_SIG_CH0_IN0_IDX          33
#define GPIO_WLAN_PRIO_IDX            33
#define PCNT_SIG_CH1_IN0_IDX          34
#define GPIO_WLAN_ACTIVE_IDX          34
#define PCNT_CTRL_CH0_IN0_IDX         35
#define BB_DIAG0_IDX                  35
#define PCNT_CTRL_CH1_IN0_IDX         36
#define BB_DIAG1_IDX                  36
#define PCNT_SIG_CH0_IN1_IDX          37
#define BB_DIAG2_IDX                  37
#define PCNT_SIG_CH1_IN1_IDX          38
#define BB_DIAG3_IDX                  38
#define PCNT_CTRL_CH0_IN1_IDX         39
#define BB_DIAG4_IDX                  39
#define PCNT_CTRL_CH1_IN1_IDX         40
#define BB_DIAG5_IDX                  40
#define PCNT_SIG_CH0_IN2_IDX          41
#define BB_DIAG6_IDX                  41
#define PCNT_SIG_CH1_IN2_IDX          42
#define BB_DIAG7_IDX                  42
#define PCNT_CTRL_CH0_IN2_IDX         43
#define BB_DIAG8_IDX                  43
#define PCNT_CTRL_CH1_IN2_IDX         44
#define BB_DIAG9_IDX                  44
#define PCNT_SIG_CH0_IN3_IDX          45
#define BB_DIAG10_IDX                 45
#define PCNT_SIG_CH1_IN3_IDX          46
#define BB_DIAG11_IDX                 46
#define PCNT_CTRL_CH0_IN3_IDX         47
#define BB_DIAG12_IDX                 47
#define PCNT_CTRL_CH1_IN3_IDX         48
#define BB_DIAG13_IDX                 48
#define GPIO_BT_ACTIVE_IDX            49
#define BB_DIAG14_IDX                 49
#define GPIO_BT_PRIORITY_IDX          50
#define BB_DIAG15_IDX                 50
#define I2S0I_SD1_IN_IDX              51
#define BB_DIAG16_IDX                 51
#define I2S0I_SD2_IN_IDX              52
#define BB_DIAG17_IDX                 52
#define I2S0I_SD3_IN_IDX              53
#define BB_DIAG18_IDX                 53
#define CORE1_GPIO_IN7_IDX            54
#define CORE1_GPIO_OUT7_IDX           54
#define USB_EXTPHY_VP_IDX             55
#define USB_EXTPHY_OEN_IDX            55
#define USB_EXTPHY_VM_IDX             56
#define USB_EXTPHY_SPEED_IDX          56
#define USB_EXTPHY_RCV_IDX            57
#define USB_EXTPHY_VPO_IDX            57
#define USB_OTG_IDDIG_IN_IDX          58
#define USB_EXTPHY_VMO_IDX            58
#define USB_OTG_AVALID_IN_IDX         59
#define USB_EXTPHY_SUSPND_IDX         59
#define USB_SRP_BVALID_IN_IDX         60
#define USB_OTG_IDPULLUP_IDX          60
#define USB_OTG_VBUSVALID_IN_IDX      61
#define USB_OTG_DPPULLDOWN_IDX        61
#define USB_SRP_SESSEND_IN_IDX        62
#define USB_OTG_DMPULLDOWN_IDX        62
#define USB_OTG_DRVVBUS_IDX           63
#define USB_SRP_CHRGVBUS_IDX          64
#define USB_SRP_DISCHRGVBUS_IDX       65
#define SPI3_CLK_IN_IDX               66
#define SPI3_CLK_OUT_IDX              66
#define SPI3_Q_IN_IDX                 67
#define SPI3_Q_OUT_IDX                67
#define SPI3_D_IN_IDX                 68
#define SPI3_D_OUT_IDX                68
#define SPI3_HD_IN_IDX                69
#define SPI3_HD_OUT_IDX               69
#define SPI3_WP_IN_IDX                70
#define SPI3_WP_OUT_IDX               70
#define SPI3_CS0_IN_IDX               71
#define SPI3_CS0_OUT_IDX              71
#define SPI3_CS1_OUT_IDX              72
#define EXT_ADC_START_IDX             73
#define LEDC_LS_SIG_OUT0_IDX          73
#define LEDC_LS_SIG_OUT1_IDX          74
#define LEDC_LS_SIG_OUT2_IDX          75
#define LEDC_LS_SIG_OUT3_IDX          76
#define LEDC_LS_SIG_OUT4_IDX          77
#define LEDC_LS_SIG_OUT5_IDX          78
#define LEDC_LS_SIG_OUT6_IDX          79
#define LEDC_LS_SIG_OUT7_IDX          80
#define RMT_SIG_IN0_IDX               81
#define RMT_SIG_OUT0_IDX              81
#define RMT_SIG_IN1_IDX               82
#define RMT_SIG_OUT1_IDX              82
#define RMT_SIG_IN2_IDX               83
#define RMT_SIG_OUT2_IDX              83
#define RMT_SIG_IN3_IDX               84
#define RMT_SIG_OUT3_IDX              84
#define USB_JTAG_TCK_IDX              85
#define USB_JTAG_TMS_IDX              86
#define USB_JTAG_TDI_IDX              87
#define USB_JTAG_TDO_IDX              88
#define I2CEXT0_SCL_IN_IDX            89
#define I2CEXT0_SCL_OUT_IDX           89
#define I2CEXT0_SDA_IN_IDX            90
#define I2CEXT0_SDA_OUT_IDX           90
#define I2CEXT1_SCL_IN_IDX            91
#define I2CEXT1_SCL_OUT_IDX           91
#define I2CEXT1_SDA_IN_IDX            92
#define I2CEXT1_SDA_OUT_IDX           92
#define GPIO_SD0_OUT_IDX              93
#define GPIO_SD1_OUT_IDX              94
#define GPIO_SD2_OUT_IDX              95
#define GPIO_SD3_OUT_IDX              96
#define GPIO_SD4_OUT_IDX              97
#define GPIO_SD5_OUT_IDX              98
#define GPIO_SD6_OUT_IDX              99
#define GPIO_SD7_OUT_IDX              100
#define FSPICLK_IN_IDX                101
#define FSPICLK_OUT_IDX               101
#define FSPIQ_IN_IDX                  102
#define FSPIQ_OUT_IDX                 102
#define FSPID_IN_IDX                  103
#define FSPID_OUT_IDX                 103
#define FSPIHD_IN_IDX                 104
#define FSPIHD_OUT_IDX                104
#define FSPIWP_IN_IDX                 105
#define FSPIWP_OUT_IDX                105
#define FSPIIO4_IN_IDX                106
#define FSPIIO4_OUT_IDX               106
#define FSPIIO5_IN_IDX                107
#define FSPIIO5_OUT_IDX               107
#define FSPIIO6_IN_IDX                108
#define FSPIIO6_OUT_IDX               108
#define FSPIIO7_IN_IDX                109
#define FSPIIO7_OUT_IDX               109
#define FSPICS0_IN_IDX                110
#define FSPICS0_OUT_IDX               110
#define FSPICS1_OUT_IDX               111
#define FSPICS2_OUT_IDX               112
#define FSPICS3_OUT_IDX               113
#define FSPICS4_OUT_IDX               114
#define FSPICS5_OUT_IDX               115
#define TWAI_RX_IDX                   116
#define TWAI_TX_IDX                   116
#define TWAI_BUS_OFF_ON_IDX           117
#define TWAI_CLKOUT_IDX               118
#define SUBSPICLK_OUT_IDX             119
#define SUBSPIQ_IN_IDX                120
#define SUBSPIQ_OUT_IDX               120
#define SUBSPID_IN_IDX                121
#define SUBSPID_OUT_IDX               121
#define SUBSPIHD_IN_IDX               122
#define SUBSPIHD_OUT_IDX              122
#define SUBSPIWP_IN_IDX               123
#define SUBSPIWP_OUT_IDX              123
#define SUBSPICS0_OUT_IDX             124
#define SUBSPICS1_OUT_IDX             125
#define FSPIDQS_OUT_IDX               126
#define SPI3_CS2_OUT_IDX              127
#define I2S0O_SD1_OUT_IDX             128
#define CORE1_GPIO_IN0_IDX            129
#define CORE1_GPIO_OUT0_IDX           129
#define CORE1_GPIO_IN1_IDX            130
#define CORE1_GPIO_OUT1_IDX           130
#define CORE1_GPIO_IN2_IDX            131
#define CORE1_GPIO_OUT2_IDX           131
#define LCD_CS_IDX                    132
#define CAM_DATA_IN0_IDX              133
#define LCD_DATA_OUT0_IDX             133
#define CAM_DATA_IN1_IDX              134
#define LCD_DATA_OUT1_IDX             134
#define CAM_DATA_IN2_IDX              135
#define LCD_DATA_OUT2_IDX             135
#define CAM_DATA_IN3_IDX              136
#define LCD_DATA_OUT3_IDX             136
#define CAM_DATA_IN4_IDX              137
#define LCD_DATA_OUT4_IDX             137
#define CAM_DATA_IN5_IDX              138
#define LCD_DATA_OUT5_IDX             138
#define CAM_DATA_IN6_IDX              139
#define LCD_DATA_OUT6_IDX             139
#define CAM_DATA_IN7_IDX              140
#define LCD_DATA_OUT7_IDX             140
#define CAM_DATA_IN8_IDX              141
#define LCD_DATA_OUT8_IDX             141
#define CAM_DATA_IN9_IDX              142
#define LCD_DATA_OUT9_IDX             142
#define CAM_DATA_IN10_IDX             143
#define LCD_DATA_OUT10_IDX            143
#define CAM_DATA_IN11_IDX             144
#define LCD_DATA_OUT11_IDX            144
#define CAM_DATA_IN12_IDX             145
#define LCD_DATA_OUT12_IDX            145
#define CAM_DATA_IN13_IDX             146
#define LCD_DATA_OUT13_IDX            146
#define CAM_DATA_IN14_IDX             147
#define LCD_DATA_OUT14_IDX            147
#define CAM_DATA_IN15_IDX             148
#define LCD_DATA_OUT15_IDX            148
#define CAM_PCLK_IDX                  149
#define CAM_CLK_IDX                   149
#define CAM_H_ENABLE_IDX              150
#define LCD_H_ENABLE_IDX              150
#define CAM_H_SYNC_IDX                151
#define LCD_H_SYNC_IDX                151
#define CAM_V_SYNC_IDX                152
#define LCD_V_SYNC_IDX                152
#define LCD_DC_IDX                    153
#define LCD_PCLK_IDX                  154
#define SUBSPID4_IN_IDX               155
#define SUBSPID4_OUT_IDX              155
#define SUBSPID5_IN_IDX               156
#define SUBSPID5_OUT_IDX              156
#define SUBSPID6_IN_IDX               157
#define SUBSPID6_OUT_IDX              157
#define SUBSPID7_IN_IDX               158
#define SUBSPID7_OUT_IDX              158
#define SUBSPIDQS_IN_IDX              159
#define SUBSPIDQS_OUT_IDX             159
#define PWM0_SYNC0_IN_IDX             160
#define PWM0_OUT0A_IDX                160
#define PWM0_SYNC1_IN_IDX             161
#define PWM0_OUT0B_IDX                161
#define PWM0_SYNC2_IN_IDX             162
#define PWM0_OUT1A_IDX                162
#define PWM0_F0_IN_IDX                163
#define PWM0_OUT1B_IDX                163
#define PWM0_F1_IN_IDX                164
#define PWM0_OUT2A_IDX                164
#define PWM0_F2_IN_IDX                165
#define PWM0_OUT2B_IDX                165
#define PWM0_CAP0_IN_IDX              166
#define PWM1_OUT0A_IDX                166
#define PWM0_CAP1_IN_IDX              167
#define PWM1_OUT0B_IDX                167
#define PWM0_CAP2_IN_IDX              168
#define PWM1_OUT1A_IDX                168
#define PWM1_SYNC0_IN_IDX             169
#define PWM1_OUT1B_IDX                169
#define PWM1_SYNC1_IN_IDX             170
#define PWM1_OUT2A_IDX                170
#define PWM1_SYNC2_IN_IDX             171
#define PWM1_OUT2B_IDX                171
#define PWM1_F0_IN_IDX                172
#define SDHOST_CCLK_OUT_1_IDX         172
#define PWM1_F1_IN_IDX                173
#define SDHOST_CCLK_OUT_2_IDX         173
#define PWM1_F2_IN_IDX                174
#define SDHOST_RST_N_1_IDX            174
#define PWM1_CAP0_IN_IDX              175
#define SDHOST_RST_N_2_IDX            175
#define PWM1_CAP1_IN_IDX              176
#define SDHOST_CCMD_OD_PULLUP_EN_N_IDX176
#define PWM1_CAP2_IN_IDX              177
#define SDIO_TOHOST_INT_OUT_IDX       177
#define SDHOST_CCMD_IN_1_IDX          178
#define SDHOST_CCMD_OUT_1_IDX         178
#define SDHOST_CCMD_IN_2_IDX          179
#define SDHOST_CCMD_OUT_2_IDX         179
#define SDHOST_CDATA_IN_10_IDX        180
#define SDHOST_CDATA_OUT_10_IDX       180
#define SDHOST_CDATA_IN_11_IDX        181
#define SDHOST_CDATA_OUT_11_IDX       181
#define SDHOST_CDATA_IN_12_IDX        182
#define SDHOST_CDATA_OUT_12_IDX       182
#define SDHOST_CDATA_IN_13_IDX        183
#define SDHOST_CDATA_OUT_13_IDX       183
#define SDHOST_CDATA_IN_14_IDX        184
#define SDHOST_CDATA_OUT_14_IDX       184
#define SDHOST_CDATA_IN_15_IDX        185
#define SDHOST_CDATA_OUT_15_IDX       185
#define SDHOST_CDATA_IN_16_IDX        186
#define SDHOST_CDATA_OUT_16_IDX       186
#define SDHOST_CDATA_IN_17_IDX        187
#define SDHOST_CDATA_OUT_17_IDX       187
#define PCMFSYNC_IN_IDX               188
#define BT_AUDIO0_IRQ_IDX             188
#define PCMCLK_IN_IDX                 189
#define BT_AUDIO1_IRQ_IDX             189
#define PCMDIN_IDX                    190
#define BT_AUDIO2_IRQ_IDX             190
#define RW_WAKEUP_REQ_IDX             191
#define BLE_AUDIO0_IRQ_IDX            191
#define SDHOST_DATA_STROBE_1_IDX      192
#define BLE_AUDIO1_IRQ_IDX            192
#define SDHOST_DATA_STROBE_2_IDX      193
#define BLE_AUDIO2_IRQ_IDX            193
#define SDHOST_CARD_DETECT_N_1_IDX    194
#define PCMFSYNC_OUT_IDX              194
#define SDHOST_CARD_DETECT_N_2_IDX    195
#define PCMCLK_OUT_IDX                195
#define SDHOST_CARD_WRITE_PRT_1_IDX   196
#define PCMDOUT_IDX                   196
#define SDHOST_CARD_WRITE_PRT_2_IDX   197
#define BLE_AUDIO_SYNC0_P_IDX         197
#define SDHOST_CARD_INT_N_1_IDX       198
#define BLE_AUDIO_SYNC1_P_IDX         198
#define SDHOST_CARD_INT_N_2_IDX       199
#define BLE_AUDIO_SYNC2_P_IDX         199
#define ANT_SEL0_IDX                  200
#define ANT_SEL1_IDX                  201
#define ANT_SEL2_IDX                  202
#define ANT_SEL3_IDX                  203
#define ANT_SEL4_IDX                  204
#define ANT_SEL5_IDX                  205
#define ANT_SEL6_IDX                  206
#define ANT_SEL7_IDX                  207
#define SIG_IN_FUNC_208_IDX           208
#define SIG_IN_FUNC208_IDX            208
#define SIG_IN_FUNC_209_IDX           209
#define SIG_IN_FUNC209_IDX            209
#define SIG_IN_FUNC_210_IDX           210
#define SIG_IN_FUNC210_IDX            210
#define SIG_IN_FUNC_211_IDX           211
#define SIG_IN_FUNC211_IDX            211
#define SIG_IN_FUNC_212_IDX           212
#define SIG_IN_FUNC212_IDX            212
#define SDHOST_CDATA_IN_20_IDX        213
#define SDHOST_CDATA_OUT_20_IDX       213
#define SDHOST_CDATA_IN_21_IDX        214
#define SDHOST_CDATA_OUT_21_IDX       214
#define SDHOST_CDATA_IN_22_IDX        215
#define SDHOST_CDATA_OUT_22_IDX       215
#define SDHOST_CDATA_IN_23_IDX        216
#define SDHOST_CDATA_OUT_23_IDX       216
#define SDHOST_CDATA_IN_24_IDX        217
#define SDHOST_CDATA_OUT_24_IDX       217
#define SDHOST_CDATA_IN_25_IDX        218
#define SDHOST_CDATA_OUT_25_IDX       218
#define SDHOST_CDATA_IN_26_IDX        219
#define SDHOST_CDATA_OUT_26_IDX       219
#define SDHOST_CDATA_IN_27_IDX        220
#define SDHOST_CDATA_OUT_27_IDX       220
#define PRO_ALONEGPIO_IN0_IDX         221
#define PRO_ALONEGPIO_OUT0_IDX        221
#define PRO_ALONEGPIO_IN1_IDX         222
#define PRO_ALONEGPIO_OUT1_IDX        222
#define PRO_ALONEGPIO_IN2_IDX         223
#define PRO_ALONEGPIO_OUT2_IDX        223
#define PRO_ALONEGPIO_IN3_IDX         224
#define PRO_ALONEGPIO_OUT3_IDX        224
#define PRO_ALONEGPIO_IN4_IDX         225
#define PRO_ALONEGPIO_OUT4_IDX        225
#define PRO_ALONEGPIO_IN5_IDX         226
#define PRO_ALONEGPIO_OUT5_IDX        226
#define PRO_ALONEGPIO_IN6_IDX         227
#define PRO_ALONEGPIO_OUT6_IDX        227
#define PRO_ALONEGPIO_IN7_IDX         228
#define PRO_ALONEGPIO_OUT7_IDX        228
#define SYNCERR_IDX                   229
#define SYNCFOUND_FLAG_IDX            230
#define EVT_CNTL_IMMEDIATE_ABORT_IDX  231
#define LINKLBL_IDX                   232
#define DATA_EN_IDX                   233
#define DATA_IDX                      234
#define PKT_TX_ON_IDX                 235
#define PKT_RX_ON_IDX                 236
#define RW_TX_ON_IDX                  237
#define RW_RX_ON_IDX                  238
#define EVT_REQ_P_IDX                 239
#define EVT_STOP_P_IDX                240
#define BT_MODE_ON_IDX                241
#define GPIO_LC_DIAG0_IDX             242
#define GPIO_LC_DIAG1_IDX             243
#define GPIO_LC_DIAG2_IDX             244
#define CH_IDX_IDX                    245
#define RX_WINDOW_IDX                 246
#define UPDATE_RX_IDX                 247
#define RX_STATUS_IDX                 248
#define CLK_GPIO_IDX                  249
#define NBT_BLE_IDX                   250
#define USB_JTAG_TDO_BRIDGE_IDX       251
#define USB_JTAG_TRST_IDX             251
#define CORE1_GPIO_IN3_IDX            252
#define CORE1_GPIO_OUT3_IDX           252
#define CORE1_GPIO_IN4_IDX            253
#define CORE1_GPIO_OUT4_IDX           253
#define CORE1_GPIO_IN5_IDX            254
#define CORE1_GPIO_OUT5_IDX           254
#define CORE1_GPIO_IN6_IDX            255
#define CORE1_GPIO_OUT6_IDX           255
#define SIG_GPIO_OUT_IDX              256
#define GPIO_MAP_DATE_IDX             0x1907040
#endif  /* _SOC_GPIO_SIG_MAP_H_ */

