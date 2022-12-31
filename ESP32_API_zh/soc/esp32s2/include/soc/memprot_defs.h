// 版权所有2020 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。
#pragma once

#include "soc/soc.h"
#include "soc/sensitive_reg.h"

#ifdef __cplusplus
extern "C" {
#endif

//IRAM0中断状态位掩码
#define IRAM0_INTR_ST_OP_TYPE_BIT               BIT(1)      //指令：0，数据：1
#define IRAM0_INTR_ST_OP_RW_BIT                 BIT(0)      //读取：0，写入：1

#define CONF_REG_ADDRESS_SHIFT                  2

//IRAM0范围
#define IRAM0_SRAM_BASE_ADDRESS                 0x40000000
#define IRAM0_SRAM_ADDRESS_LOW                  0x40020000
#define IRAM0_SRAM_ADDRESS_HIGH                 0x4006FFFF

//IRAM0统一管理块
#define IRAM0_SRAM_TOTAL_UNI_BLOCKS             4
#define IRAM0_SRAM_UNI_BLOCK_0                  0
#define IRAM0_SRAM_UNI_BLOCK_1                  1
#define IRAM0_SRAM_UNI_BLOCK_2                  2
#define IRAM0_SRAM_UNI_BLOCK_3                  3

//统一管理地址范围（块0-3）
#define IRAM0_SRAM_UNI_BLOCK_0_LOW              0x40020000
#define IRAM0_SRAM_UNI_BLOCK_1_LOW              0x40022000
#define IRAM0_SRAM_UNI_BLOCK_2_LOW              0x40024000
#define IRAM0_SRAM_UNI_BLOCK_3_LOW              0x40026000

//拆分管理地址范围（块4-21）
#define IRAM0_SRAM_SPL_BLOCK_LOW                0x40028000 //区块4低
#define IRAM0_SRAM_SPL_BLOCK_HIGH               0x4006FFFF //第21区偏高

#define IRAM0_INTR_ST_FAULTADDR_M               0x003FFFFC  //reg中的位21:6以及真实地址
#define IRAM0_SRAM_INTR_ST_FAULTADDR_HI         0x40000000  //错误地址常数的高非重要位31:22

#define IRAM0_SRAM_ADDR_TO_CONF_REG(addr)       (((addr >> CONF_REG_ADDRESS_SHIFT) & DPORT_PMS_PRO_IRAM0_SRAM_4_SPLTADDR) << DPORT_PMS_PRO_IRAM0_SRAM_4_SPLTADDR_S)

//IRAM0 RTCFAST
#define IRAM0_RTCFAST_ADDRESS_LOW               0x40070000
#define IRAM0_RTCFAST_ADDRESS_HIGH              0x40071FFF
#define IRAM0_RTCFAST_INTR_ST_FAULTADDR_HI      0x40070000  //RTCFAST错误地址高位（31:22，常量）

#define IRAM0_RTCFAST_ADDR_TO_CONF_REG(addr)    (((addr >> CONF_REG_ADDRESS_SHIFT) & DPORT_PMS_PRO_IRAM0_RTCFAST_SPLTADDR) << DPORT_PMS_PRO_IRAM0_RTCFAST_SPLTADDR_S)

//DRAM0中断状态位掩码
#define DRAM0_INTR_ST_FAULTADDR_M               0x03FFFFC0  //（reg中的位25:6）
#define DRAM0_INTR_ST_FAULTADDR_S               0x4         //（实际地址的位21:2）
#define DRAM0_INTR_ST_OP_RW_BIT                 BIT(4)      //读取：0，写入：1
#define DRAM0_INTR_ST_OP_ATOMIC_BIT             BIT(5)      //非原子：0，原子：1

#define DRAM0_SRAM_ADDRESS_LOW                  0x3FFB0000
#define DRAM0_SRAM_ADDRESS_HIGH                 0x3FFFFFFF

#define DRAM0_SRAM_TOTAL_UNI_BLOCKS             4
#define DRAM0_SRAM_UNI_BLOCK_0                  0
#define DRAM0_SRAM_UNI_BLOCK_1                  1
#define DRAM0_SRAM_UNI_BLOCK_2                  2
#define DRAM0_SRAM_UNI_BLOCK_3                  3

//统一管理（SRAM块0-3）
#define DRAM0_SRAM_UNI_BLOCK_0_LOW              0x3FFB0000
#define DRAM0_SRAM_UNI_BLOCK_1_LOW              0x3FFB2000
#define DRAM0_SRAM_UNI_BLOCK_2_LOW              0x3FFB4000
#define DRAM0_SRAM_UNI_BLOCK_3_LOW              0x3FFB6000

//分割管理（SRAM块4-21）
#define DRAM0_SRAM_SPL_BLOCK_HIGH               0x3FFFFFFF  //第21区偏高
#define DRAM0_SRAM_INTR_ST_FAULTADDR_HI         0x3FF00000  //故障地址的SRAM高位31:22-常量

#define DRAM0_SRAM_ADDR_TO_CONF_REG(addr)       (((addr >> CONF_REG_ADDRESS_SHIFT) & DPORT_PMS_PRO_DRAM0_SRAM_4_SPLTADDR) << DPORT_PMS_PRO_DRAM0_SRAM_4_SPLTADDR_S)

//DRAM0 RTCFAST
#define DRAM0_RTCFAST_ADDRESS_LOW               0x3FF9E000
#define DRAM0_RTCFAST_ADDRESS_HIGH              0x3FF9FFFF
#define DRAM0_RTCFAST_INTR_ST_FAULTADDR_HI      0x3FF00000  //RTCFAST错误地址的高位31:22-常量
#define DRAM0_RTCFAST_ADDR_TO_CONF_REG(addr)    (((addr >> CONF_REG_ADDRESS_SHIFT) & DPORT_PMS_PRO_DRAM0_RTCFAST_SPLTADDR) << DPORT_PMS_PRO_DRAM0_RTCFAST_SPLTADDR_S)

//RTCSLOW
#define RTCSLOW_MEMORY_SIZE                     0x00002000

//PeriBus1中断状态位掩码
#define PERI1_INTR_ST_OP_TYPE_BIT               BIT(4)      //0：非原子，1：原子
#define PERI1_INTR_ST_OP_HIGH_BITS              BIT(5)      //0：高位=不变，1：高位=0x03F40000
#define PERI1_INTR_ST_FAULTADDR_M               0x03FFFFC0  //（reg中的位25:6）
#define PERI1_INTR_ST_FAULTADDR_S               0x4         //（实际地址的位21:2）

#define PERI1_RTCSLOW_ADDRESS_BASE              0x3F421000
#define PERI1_RTCSLOW_ADDRESS_LOW               PERI1_RTCSLOW_ADDRESS_BASE
#define PERI1_RTCSLOW_ADDRESS_HIGH              PERI1_RTCSLOW_ADDRESS_LOW + RTCSLOW_MEMORY_SIZE
#define PERI1_RTCSLOW_INTR_ST_FAULTADDR_HI_0    0x3F400000

#define PERI1_RTCSLOW_ADDR_TO_CONF_REG(addr)    (((addr >> CONF_REG_ADDRESS_SHIFT) & DPORT_PMS_PRO_DPORT_RTCSLOW_SPLTADDR) << DPORT_PMS_PRO_DPORT_RTCSLOW_SPLTADDR_S)

//PeriBus2中断状态位掩码
#define PERI2_INTR_ST_OP_TYPE_BIT               BIT(1)      //指令：0，数据：1
#define PERI2_INTR_ST_OP_RW_BIT                 BIT(0)      //读取：0，写入：1
#define PERI2_INTR_ST_FAULTADDR_M               0xFFFFFFFC  //（reg中的位31:2）

#define PERI2_RTCSLOW_0_ADDRESS_BASE            0x50000000
#define PERI2_RTCSLOW_0_ADDRESS_LOW             PERI2_RTCSLOW_0_ADDRESS_BASE
#define PERI2_RTCSLOW_0_ADDRESS_HIGH            PERI2_RTCSLOW_0_ADDRESS_LOW + RTCSLOW_MEMORY_SIZE

#define PERI2_RTCSLOW_0_ADDR_TO_CONF_REG(addr)  (((addr >> CONF_REG_ADDRESS_SHIFT) & DPORT_PMS_PRO_AHB_RTCSLOW_0_SPLTADDR) << DPORT_PMS_PRO_AHB_RTCSLOW_0_SPLTADDR_S)

#define PERI2_RTCSLOW_1_ADDRESS_BASE            0x60021000
#define PERI2_RTCSLOW_1_ADDRESS_LOW             PERI2_RTCSLOW_1_ADDRESS_BASE
#define PERI2_RTCSLOW_1_ADDRESS_HIGH            PERI2_RTCSLOW_1_ADDRESS_LOW + RTCSLOW_MEMORY_SIZE

#define PERI2_RTCSLOW_1_ADDR_TO_CONF_REG(addr)  (((addr >> CONF_REG_ADDRESS_SHIFT) & DPORT_PMS_PRO_AHB_RTCSLOW_1_SPLTADDR) << DPORT_PMS_PRO_AHB_RTCSLOW_1_SPLTADDR_S)

#ifdef __cplusplus
}
#endif

