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
#ifndef __HWCRYPTO_REG_H__
#define __HWCRYPTO_REG_H__

#include "soc.h"

/* 通过多精度整数运算实现RSA加速寄存器*/
#define RSA_MEM_M_BLOCK_BASE          ((DR_REG_RSA_BASE)+0x000)
/* RB&Z使用相同的内存块，具体取决于操作阶段*/
#define RSA_MEM_RB_BLOCK_BASE         ((DR_REG_RSA_BASE)+0x200)
#define RSA_MEM_Z_BLOCK_BASE          ((DR_REG_RSA_BASE)+0x200)
#define RSA_MEM_Y_BLOCK_BASE          ((DR_REG_RSA_BASE)+0x400)
#define RSA_MEM_X_BLOCK_BASE          ((DR_REG_RSA_BASE)+0x600)

#define RSA_M_DASH_REG                (DR_REG_RSA_BASE + 0x800)
#define RSA_MODEXP_MODE_REG           (DR_REG_RSA_BASE + 0x804)
#define RSA_MODEXP_START_REG          (DR_REG_RSA_BASE + 0x808)
#define RSA_MULT_MODE_REG             (DR_REG_RSA_BASE + 0x80c)
#define RSA_MULT_START_REG            (DR_REG_RSA_BASE + 0x810)

#define RSA_CLEAR_INTERRUPT_REG       (DR_REG_RSA_BASE + 0x814)
#define RSA_QUERY_INTERRUPT_REG       (DR_REG_RSA_BASE + 0x814) /* 相同的*/

#define RSA_QUERY_CLEAN_REG           (DR_REG_RSA_BASE + 0x818)

/* ESP32S2之前使用的向后兼容寄存器名称*/
#define RSA_CLEAN_REG                 (RSA_QUERY_CLEAN_REG)
#define RSA_INTERRUPT_REG             (RSA_CLEAR_INTERRUPT_REG)
#define RSA_START_MODEXP_REG          (RSA_MODEXP_START_REG)

/* SHA加速寄存器*/
#define SHA_TEXT_BASE           ((DR_REG_SHA_BASE) + 0x00)

#define SHA_1_START_REG         ((DR_REG_SHA_BASE) + 0x80)
#define SHA_1_CONTINUE_REG      ((DR_REG_SHA_BASE) + 0x84)
#define SHA_1_LOAD_REG          ((DR_REG_SHA_BASE) + 0x88)
#define SHA_1_BUSY_REG          ((DR_REG_SHA_BASE) + 0x8c)

#define SHA_256_START_REG       ((DR_REG_SHA_BASE) + 0x90)
#define SHA_256_CONTINUE_REG    ((DR_REG_SHA_BASE) + 0x94)
#define SHA_256_LOAD_REG        ((DR_REG_SHA_BASE) + 0x98)
#define SHA_256_BUSY_REG        ((DR_REG_SHA_BASE) + 0x9c)

#define SHA_384_START_REG       ((DR_REG_SHA_BASE) + 0xa0)
#define SHA_384_CONTINUE_REG    ((DR_REG_SHA_BASE) + 0xa4)
#define SHA_384_LOAD_REG        ((DR_REG_SHA_BASE) + 0xa8)
#define SHA_384_BUSY_REG        ((DR_REG_SHA_BASE) + 0xac)

#define SHA_512_START_REG       ((DR_REG_SHA_BASE) + 0xb0)
#define SHA_512_CONTINUE_REG    ((DR_REG_SHA_BASE) + 0xb4)
#define SHA_512_LOAD_REG        ((DR_REG_SHA_BASE) + 0xb8)
#define SHA_512_BUSY_REG        ((DR_REG_SHA_BASE) + 0xbc)

/* AES加速寄存器*/
#define AES_START_REG           ((DR_REG_AES_BASE) + 0x00)
#define AES_IDLE_REG            ((DR_REG_AES_BASE) + 0x04)
#define AES_MODE_REG            ((DR_REG_AES_BASE) + 0x08)
#define AES_KEY_BASE            ((DR_REG_AES_BASE) + 0x10)
#define AES_TEXT_BASE           ((DR_REG_AES_BASE) + 0x30)
#define AES_ENDIAN              ((DR_REG_AES_BASE) + 0x40)

#endif

