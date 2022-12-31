/*
 * 版权所有（c）2016，飞思卡尔半导体公司版权所有2016-2017 NXP保留所有权利。
 *
 * SPDX许可证标识符：BSD-3-条款
 */

#ifndef __EVKBIMXRT1050_FLEXSPI_NOR_CONFIG__
#define __EVKBIMXRT1050_FLEXSPI_NOR_CONFIG__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_common.h"

/*! @名称驱动程序版本*/
/*@{*/
/*! @brief XIP_BOARD驱动程序2.0.0版。*/
#define FSL_XIP_BOARD_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

/* FLEXSPI内存配置块相关定义*/
#define FLEXSPI_CFG_BLK_TAG (0x42464346UL)     // ascii“FCFB”Big Endian
#define FLEXSPI_CFG_BLK_VERSION (0x56010400UL) // V1.4.0
#define FLEXSPI_CFG_BLK_SIZE (512)

/* FLEXSPI功能相关定义*/
#define FLEXSPI_FEATURE_HAS_PARALLEL_MODE 1

/* 查找表相关定义*/
#define CMD_INDEX_READ 0
#define CMD_INDEX_READSTATUS 1
#define CMD_INDEX_WRITEENABLE 2
#define CMD_INDEX_WRITE 4

#define CMD_LUT_SEQ_IDX_READ 0
#define CMD_LUT_SEQ_IDX_READSTATUS 1
#define CMD_LUT_SEQ_IDX_WRITEENABLE 3
#define CMD_LUT_SEQ_IDX_WRITE 9

#define CMD_SDR 0x01
#define CMD_DDR 0x21
#define RADDR_SDR 0x02
#define RADDR_DDR 0x22
#define CADDR_SDR 0x03
#define CADDR_DDR 0x23
#define MODE1_SDR 0x04
#define MODE1_DDR 0x24
#define MODE2_SDR 0x05
#define MODE2_DDR 0x25
#define MODE4_SDR 0x06
#define MODE4_DDR 0x26
#define MODE8_SDR 0x07
#define MODE8_DDR 0x27
#define WRITE_SDR 0x08
#define WRITE_DDR 0x28
#define READ_SDR 0x09
#define READ_DDR 0x29
#define LEARN_SDR 0x0A
#define LEARN_DDR 0x2A
#define DATSZ_SDR 0x0B
#define DATSZ_DDR 0x2B
#define DUMMY_SDR 0x0C
#define DUMMY_DDR 0x2C
#define DUMMY_RWDS_SDR 0x0D
#define DUMMY_RWDS_DDR 0x2D
#define JMP_ON_CS 0x1F
#define STOP 0

#define FLEXSPI_1PAD 0
#define FLEXSPI_2PAD 1
#define FLEXSPI_4PAD 2
#define FLEXSPI_8PAD 3

#define FLEXSPI_LUT_SEQ(cmd0, pad0, op0, cmd1, pad1, op1)                                                              \
    (FLEXSPI_LUT_OPERAND0(op0) | FLEXSPI_LUT_NUM_PADS0(pad0) | FLEXSPI_LUT_OPCODE0(cmd0) | FLEXSPI_LUT_OPERAND1(op1) | \
     FLEXSPI_LUT_NUM_PADS1(pad1) | FLEXSPI_LUT_OPCODE1(cmd1))

//!@FlexSPI串行时钟频率的简要定义
typedef enum _FlexSpiSerialClockFreq
{
    kFlexSpiSerialClk_30MHz  = 1,
    kFlexSpiSerialClk_50MHz  = 2,
    kFlexSpiSerialClk_60MHz  = 3,
    kFlexSpiSerialClk_75MHz  = 4,
    kFlexSpiSerialClk_80MHz  = 5,
    kFlexSpiSerialClk_100MHz = 6,
    kFlexSpiSerialClk_133MHz = 7,
    kFlexSpiSerialClk_166MHz = 8,
    kFlexSpiSerialClk_200MHz = 9,
} flexspi_serial_clk_freq_t;

//!@简要FlexSPI时钟配置类型
enum
{
    kFlexSpiClk_SDR, //!< SDR模式的时钟配置
    kFlexSpiClk_DDR, //!< DDR模式的时钟配置
};

//!@简要FlexSPI读取示例时钟源定义
typedef enum _FlashReadSampleClkSource
{
    kFlexSPIReadSampleClk_LoopbackInternally      = 0,
    kFlexSPIReadSampleClk_LoopbackFromDqsPad      = 1,
    kFlexSPIReadSampleClk_LoopbackFromSckPad      = 2,
    kFlexSPIReadSampleClk_ExternalInputFromDqsPad = 3,
} flexspi_read_sample_clk_t;

//!@简要其他特征位定义
enum
{
    kFlexSpiMiscOffset_DiffClkEnable            = 0, //!< 差分时钟启用位
    kFlexSpiMiscOffset_Ck2Enable                = 1, //!< CK2启用位
    kFlexSpiMiscOffset_ParallelEnable           = 2, //!< 并行模式启用位
    kFlexSpiMiscOffset_WordAddressableEnable    = 3, //!< 字寻址启用位
    kFlexSpiMiscOffset_SafeConfigFreqEnable     = 4, //!< 安全配置频率启用位
    kFlexSpiMiscOffset_PadSettingOverrideEnable = 5, //!< 极板设置超控启用位
    kFlexSpiMiscOffset_DdrModeEnable            = 6, //!< DDR时钟确认指示位。
};

//!@简要闪存类型定义
enum
{
    kFlexSpiDeviceType_SerialNOR    = 1,    //!< 闪存设备为串行NOR
    kFlexSpiDeviceType_SerialNAND   = 2,    //!< 闪存设备是串行NAND
    kFlexSpiDeviceType_SerialRAM    = 3,    //!< 闪存设备是串行RAM/HyperFLASH
    kFlexSpiDeviceType_MCP_NOR_NAND = 0x12, //!< 闪存设备是MCP设备，A1是串行NOR，A2是串行NAND
    kFlexSpiDeviceType_MCP_NOR_RAM  = 0x13, //!< 闪存设备是MCP设备，A1是串行NOR，A2是串行RAM
};

//!@Flash Pad的简要定义
enum
{
    kSerialFlash_1Pad  = 1,
    kSerialFlash_2Pads = 2,
    kSerialFlash_4Pads = 4,
    kSerialFlash_8Pads = 8,
};

//!@简要FlexSPI LUT序列结构
typedef struct _lut_sequence
{
    uint8_t seqNum; //!< 序列号，有效编号：1-16
    uint8_t seqId;  //!< 序列索引，有效编号：0-15
    uint16_t reserved;
} flexspi_lut_seq_t;

//!@简要闪存配置命令类型
enum
{
    kDeviceConfigCmdType_Generic,    //!< 通用命令，例如：配置虚拟循环、驱动强度等
    kDeviceConfigCmdType_QuadEnable, //!< 四元启用命令
    kDeviceConfigCmdType_Spi2Xpi,    //!< 从SPI切换到DPI/QPI/OPI模式
    kDeviceConfigCmdType_Xpi2Spi,    //!< 从DPI/QPI/OPI切换到SPI模式
    kDeviceConfigCmdType_Spi2NoCmd,  //!< 切换到0-4-4/0-8-8模式
    kDeviceConfigCmdType_Reset,      //!< 重置设备命令
};

//!@简要FlexSPI内存配置块
typedef struct _FlexSPIConfig
{
    uint32_t tag;               //!< [0x00-0x003]标签，固定值0x42464346UL
    uint32_t version;           //!< [0x04-0x007]版本，[31:24]-“V”，[23:16]-主要，[15:8]-次要，[7:0]-错误修复
    uint32_t reserved0;         //!< [0x08-0x00b]保留以备将来使用
    uint8_t readSampleClkSrc;   //!< [0x000c-0x00c]读取样本时钟源，有效值：0/1/3
    uint8_t csHoldTime;         //!< [0x00d-0x00d]CS保持时间，默认值：3
    uint8_t csSetupTime;        //!< [0x00e-0x00e]CS设置时间，默认值：3
    uint8_t columnAddressWidth; //!< [0x00f-0x00f]列地址，对于HyperBus协议，它固定为3，对于
    //! 串行NAND，需要参考数据表
    uint8_t deviceModeCfgEnable; //!< [0x010-0x010]设备模式配置启用标志，1-启用，0-禁用
    uint8_t deviceModeType; //!< [0x011-0x011]指定配置命令类型：Quad Enable、DPI/QPI/OPI开关、，
    //! 通用配置等。
    uint16_t waitTimeCfgCommands; //!< [0x012-0x013]所有配置命令的等待时间，单位：100us，用于
    //! DPI/QPI/OPI开关或重置命令
    flexspi_lut_seq_t deviceModeSeq; //!< [0x014-0x017]设备模式序列信息，[7:0]-LUT序列id，[15:8]-LUT
    //! 序列号，[31:16]保留
    uint32_t deviceModeArg;    //!< [0x018-0x01b]设备配置的参数/参数
    uint8_t configCmdEnable;   //!< [0x01c-0x01c]配置命令启用标志，1-启用，0-禁用
    uint8_t configModeType[3]; //!< [0x01d-0x01f]配置模式类型，类似于deviceModeTpe
    flexspi_lut_seq_t
        configCmdSeqs[3]; //!< [0x020-0x02b]设备配置命令的序列信息，类似于deviceModeSeq
    uint32_t reserved1;   //!< [0x02c-0x02f]保留供将来使用
    uint32_t configCmdArgs[3];     //!< [0x030-0x03b]设备配置命令的参数/参数
    uint32_t reserved2;            //!< [0x03c-0x03f]保留供将来使用
    uint32_t controllerMiscOption; //!< [0x040-0x043]控制器其他选项，有关详细信息，请参阅其他功能位定义
    //! 细节
    uint8_t deviceType;    //!< [0x044-0x044]设备类型：有关详细信息，请参阅闪存类型定义
    uint8_t sflashPadType; //!< [0x045-0x045]串行闪存板类型：1-单，2-双，4-四，8-八进制
    uint8_t serialClkFreq; //!< [0x046-0x046]串行闪存频率，设备特定定义，请参阅系统引导
    //! 第章了解更多详细信息
    uint8_t lutCustomSeqEnable; //!< [0x047-0x047]LUT自定义启用，如果程序/擦除无法
    //! 使用1个LUT序列完成，目前，仅适用于HyperFLASH
    uint32_t reserved3[2];           //!< [0x048-0x04f]保留供将来使用
    uint32_t sflashA1Size;           //!< [0x050-0x053]连接到A1的闪存大小
    uint32_t sflashA2Size;           //!< [0x054-0x057]连接到A2的闪存大小
    uint32_t sflashB1Size;           //!< [0x058-0x05b]连接到B1的闪存大小
    uint32_t sflashB2Size;           //!< [0x05c-0x05f]连接到B2的闪存大小
    uint32_t csPadSettingOverride;   //!< [0x060-0x063]CS极板设置超控值
    uint32_t sclkPadSettingOverride; //!< [0x064-0x067]SCK极板设置超控值
    uint32_t dataPadSettingOverride; //!< [0x068-0x06b]数据焊盘设置覆盖值
    uint32_t dqsPadSettingOverride;  //!< [0x06c-0x06f]DQS焊盘设置覆盖值
    uint32_t timeoutInMs;            //!< [0x070-0x073]读取状态命令的超时阈值
    uint32_t commandInterval;        //!< [0x074-0x077]CS取消选择两个命令之间的间隔
    uint16_t dataValidTime[2]; //!< [0x078-0x07b]端口A和端口B的CLK边缘到数据有效时间，以0.1ns为单位
    uint16_t busyOffset;       //!< [0x07c-0x07d]忙偏移量，有效值：0-31
    uint16_t busyBitPolarity;  //!< [0x07e-0x07f]忙标志极性，0-闪存设备忙时忙标志为1，1-
    //! 当闪存设备忙时，忙标志为0
    uint32_t lookupTable[64];           //!< [0x080-0x17f]查找表包含Flash命令序列
    flexspi_lut_seq_t lutCustomSeq[12]; //!< [0x180-0x1af]可定制LUT序列
    uint32_t reserved4[4];              //!< [0x1b0-0x1bf]保留供将来使用
} flexspi_mem_config_t;

/*  */
#define NOR_CMD_INDEX_READ CMD_INDEX_READ               //!< 0
#define NOR_CMD_INDEX_READSTATUS CMD_INDEX_READSTATUS   //!< 1
#define NOR_CMD_INDEX_WRITEENABLE CMD_INDEX_WRITEENABLE //!< 2
#define NOR_CMD_INDEX_ERASESECTOR 3                     //!< 3
#define NOR_CMD_INDEX_PAGEPROGRAM CMD_INDEX_WRITE       //!< 4
#define NOR_CMD_INDEX_CHIPERASE 5                       //!< 5
#define NOR_CMD_INDEX_DUMMY 6                           //!< 6
#define NOR_CMD_INDEX_ERASEBLOCK 7                      //!< 7

#define NOR_CMD_LUT_SEQ_IDX_READ CMD_LUT_SEQ_IDX_READ //!< 0读取配置块中存储的查找表中的LUT序列id
#define NOR_CMD_LUT_SEQ_IDX_READSTATUS \
    CMD_LUT_SEQ_IDX_READSTATUS //!< 1读取配置块中存储的查找表中的状态LUT序列id
#define NOR_CMD_LUT_SEQ_IDX_READSTATUS_XPI \
    2 //!< 2读取配置块中存储的查找表中的状态DPI/QPI/OPI序列id
#define NOR_CMD_LUT_SEQ_IDX_WRITEENABLE \
    CMD_LUT_SEQ_IDX_WRITEENABLE //!< 3在配置块中存储的查找表中写入启用序列id
#define NOR_CMD_LUT_SEQ_IDX_WRITEENABLE_XPI \
    4 //!< 4在配置块中存储的查找表中写入启用DPI/QPI/OPI序列id
#define NOR_CMD_LUT_SEQ_IDX_ERASESECTOR 5 //!< 5擦除配置块中存储的查找表中的扇区序列id
#define NOR_CMD_LUT_SEQ_IDX_ERASEBLOCK 8  //!< 8擦除配置块中存储的查找表中的块序列id
#define NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM \
    CMD_LUT_SEQ_IDX_WRITE                //!< 9配置块中存储的查找表中的程序序列id
#define NOR_CMD_LUT_SEQ_IDX_CHIPERASE 11 //!< 11配置块中存储的查找表id中的芯片擦除序列
#define NOR_CMD_LUT_SEQ_IDX_READ_SFDP 13 //!< 13读取配置块中存储的查找表id中的SFDP序列
#define NOR_CMD_LUT_SEQ_IDX_RESTORE_NOCMD \
    14 //!< 14恢复配置块中存储的查找表中的0-4-4/0-8-8模式序列id
#define NOR_CMD_LUT_SEQ_IDX_EXIT_NOCMD \
    15 //!< 15退出配置blobk中存储的查找表中的0-4-4/0-8-8模式序列id

/*
 *  串行NOR配置块
 */
typedef struct _flexspi_nor_config
{
    flexspi_mem_config_t memConfig; //!< 通过FlexSPI的通用内存配置信息
    uint32_t pageSize;              //!< 串行NOR的页面大小
    uint32_t sectorSize;            //!< 串行NOR的扇区大小
    uint8_t ipcmdSerialClkFreq;     //!< IP命令的时钟频率
    uint8_t isUniformBlockSize;     //!< 扇区/块大小相同
    uint8_t reserved0[2];           //!< 保留供将来使用
    uint8_t serialNorType;          //!< 串行NOR闪存类型：0/1/2/3
    uint8_t needExitNoCmdMode;      //!< 需要在其他IP命令之前退出NoCmd模式
    uint8_t halfClkForNonReadCmd;   //!< 非读取命令的串行时钟的一半：真/假
    uint8_t needRestoreNoCmdMode;   //!< 执行IP命令后需要恢复NoCmd模式
    uint32_t blockSize;             //!< 数据块大小
    uint32_t reserve2[11];          //!< 保留供将来使用
} flexspi_nor_config_t;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif
#endif /* __EVKBIMXRT1050_FLEXSPI_NOR_CONFIG__ */

