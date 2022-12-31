/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdint.h>
#include <stddef.h>
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "driver/sdspi_host.h"

///用于帧数据传输的控制令牌
///（见SD简化规范第7.3.3节）

///在单/多块读取和单块写入之前发送令牌
#define TOKEN_BLOCK_START                   0b11111110
///在多块写入之前发送令牌
#define TOKEN_BLOCK_START_WRITE_MULTI       0b11111100
///用于停止多块写入的令牌（对于读取，改用CMD12）
#define TOKEN_BLOCK_STOP_WRITE_MULTI        0b11111101

///数据响应令牌

///掩码（未定义数据响应令牌的高3位）
#define TOKEN_RSP_MASK        0b11111
///接受的数据
#define TOKEN_RSP_OK          0b00101
///CRC错误导致数据被拒绝
#define TOKEN_RSP_CRC_ERR     0b01011
///由于写入错误，数据被拒绝
#define TOKEN_RSP_WRITE_ERR   0b01101


///数据错误标记的格式为0b0000xyzw，其中xyzw是符号位标志。
///MASK和VAL用于检查令牌是否为错误令牌
#define TOKEN_ERR_MASK      0b11110000
#define TOKEN_ERR_VAL       0b00000000

///参数超出范围
#define TOKEN_ERR_RANGE     BIT(3)
///卡内部ECC错误
#define TOKEN_ERR_CARD_ECC  BIT(2)
///卡控制器错误
#define TOKEN_ERR_INTERNAL  BIT(1)
///卡已锁定
#define TOKEN_ERR_LOCKED    BIT(0)


///SPI模式下的传输格式。见SD简化规范第7.3.1.1节。
typedef struct {
    // 这些字段构成从主机发送到卡的命令（6字节）
    uint8_t cmd_index : 6;
    uint8_t transmission_bit : 1;
    uint8_t start_bit : 1;
    uint8_t arguments[4];
    uint8_t stop_bit : 1;
    uint8_t crc7 : 7;
    ///Ncr是命令和响应之间的停滞时间；应为0xff
    uint8_t ncr;
    ///对于读取操作，主机应将响应数据设置为0xff
    uint8_t r1;
    ///最多16个字节的响应。幸运的是，这是在4字节边界上对齐的。
    uint32_t response[4];
    ///响应超时（毫秒）
    int timeout_ms;
} sdspi_hw_cmd_t;

#define SDSPI_CMD_SIZE      6
#define SDSPI_NCR_MIN_SIZE  1
#define SDSPI_NCR_MAX_SIZE  8

//这里的大小包含6个字节的CMD、1个字节的虚设和实际响应
#define SDSPI_CMD_NORESP_SIZE   (SDSPI_CMD_SIZE+0)   //!< 没有任何响应的命令大小
#define SDSPI_CMD_R1_SIZE       (SDSPI_CMD_SIZE+SDSPI_NCR_MIN_SIZE+1)   //!< 带有R1响应的命令大小
#define SDSPI_CMD_R2_SIZE       (SDSPI_CMD_SIZE+SDSPI_NCR_MIN_SIZE+2)   //!< 具有R1b响应的命令大小
#define SDSPI_CMD_R3_SIZE       (SDSPI_CMD_SIZE+SDSPI_NCR_MIN_SIZE+5)  //!< 具有R3响应的命令大小
#define SDSPI_CMD_R4_SIZE       (SDSPI_CMD_SIZE+SDSPI_NCR_MIN_SIZE+5)  //!< 具有R4响应的命令大小
#define SDSPI_CMD_R5_SIZE       (SDSPI_CMD_SIZE+SDSPI_NCR_MIN_SIZE+2)   //!< 具有R5响应的命令的大小
#define SDSPI_CMD_R7_SIZE       (SDSPI_CMD_SIZE+SDSPI_NCR_MIN_SIZE+5)  //!< 具有R7响应的命令大小

#define SDSPI_CMD_FLAG_DATA     BIT(0)  //!< 命令具有数据传输
#define SDSPI_CMD_FLAG_WRITE    BIT(1)  //!< 数据写入卡
#define SDSPI_CMD_FLAG_RSP_R1   BIT(2)  //!< 响应格式R1（1字节）
#define SDSPI_CMD_FLAG_RSP_R2   BIT(3)  //!< 响应格式R2（2字节）
#define SDSPI_CMD_FLAG_RSP_R3   BIT(4)  //!< 响应格式R3（5字节）
#define SDSPI_CMD_FLAG_RSP_R4   BIT(5)  //!< 响应格式R4（5字节）
#define SDSPI_CMD_FLAG_RSP_R5   BIT(6)  //!< 响应格式R5（2字节）
#define SDSPI_CMD_FLAG_RSP_R7   BIT(7)  //!< 响应格式R7（5字节）
#define SDSPI_CMD_FLAG_NORSP    BIT(8)  //!< 不要期待响应（第一次发送CMD0时使用）。
#define SDSPI_CMD_FLAG_MULTI_BLK BIT(9) //!< 对于写多块命令，开始标记应该不同

#define SDSPI_MAX_DATA_LEN      512     //!< 单块传输的最大大小

void make_hw_cmd(uint32_t opcode, uint32_t arg, int timeout_ms, sdspi_hw_cmd_t *hw_cmd);

esp_err_t sdspi_host_start_command(sdspi_dev_handle_t handle, sdspi_hw_cmd_t *cmd,
                                   void *data, uint32_t data_size, int flags);

