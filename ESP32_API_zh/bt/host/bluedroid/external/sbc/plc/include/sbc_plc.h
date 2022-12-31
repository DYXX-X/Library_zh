// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
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

#ifndef _SBC_PLC_H
#define _SBC_PLC_H

#include <stdint.h>

#if defined __cplusplus
extern "C" {
#endif

/* PLC参数（16 kHZ）*/
#define SBC_FS          120                     /* SBC框架尺寸*/
#define SBC_N           256                     /* 16ms-用于图案匹配的窗口长度*/
#define SBC_M           64                      /* 4ms-匹配模板*/
#define SBC_LHIST       (SBC_N + SBC_FS - 1)    /* 所需的历史缓冲区长度*/
#define SBC_RT          36                      /* SBC再收敛时间（样本）*/
#define SBC_OLAL        16                      /* 重叠相加长度（示例）*/

/* PLC状态信息*/
typedef struct sbc_plc_state {
    int16_t hist[SBC_LHIST + SBC_FS + SBC_RT + SBC_OLAL];
    int16_t bestlag;
    int     nbf;
} sbc_plc_state_t;

/* 原型*/
/**
 * 执行存储器向量的PLC初始化。
 *
 * @param plc_state 指向PLC状态存储器的指针
 */
void sbc_plc_init(sbc_plc_state_t *plc_state);

/**
 * 执行存储器向量的PLC去初始化。
 *
 * @param plc_state 指向PLC状态存储器的指针
 */
void sbc_plc_deinit(sbc_plc_state_t *plc_state);

/**
 * 执行坏帧处理。
 *
 * @param plc_state 指向PLC状态存储器的指针
 * @param ZIRbuf    指向SBC解码器ZIR响应的指针
 * @param out       指向输出样本的指针
 */
void sbc_plc_bad_frame(sbc_plc_state_t *plc_state, int16_t *ZIRbuf, int16_t *out);

/**
 * 执行良好的帧处理。大多数时候，该函数只是更新历史缓冲区并将输入传递给输出，但在帧丢失后的第一个良好帧中，它必须隐藏接收到的信号，因为它与真实输出重新合并。
 *
 * @param plc_state 指向PLC状态存储器的指针
 * @param in        指向输入向量的指针
 * @param out       指向输出样本的指针
 */
void sbc_plc_good_frame(sbc_plc_state_t *plc_state, int16_t *in, int16_t *out);

/**
 * 获得零信号eSCO帧
 * @return  指向数据缓冲区的指针
 */
uint8_t * sbc_plc_zero_signal_frame(void);

/**
 * 获取零信号eSCO pcm帧
 * @return  指向数据缓冲区的指针
 */
int16_t * sbc_plc_zero_signal_frame_pcm(void);

#if defined __cplusplus
}
#endif

#endif /// _SBC_PLC_H

