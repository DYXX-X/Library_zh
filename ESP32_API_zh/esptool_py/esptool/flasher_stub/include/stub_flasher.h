/*
 * SPDX文件版权所有文本：2016 Cesanta Software Limited
 *
 * SPDX许可证标识符：GPL-2.0或
 *
 * SPDX文件贡献者：2016-2022 Espressif Systems（上海）有限公司
 */

#ifndef STUB_FLASHER_H_
#define STUB_FLASHER_H_

#include <stdint.h>

/* 用于各种缓冲区的最大写入块大小。*/
#define MAX_WRITE_BLOCK 0x4000

/* Flash几何常数*/
#define FLASH_SECTOR_SIZE 4096
#define FLASH_BLOCK_SIZE 65536
#define FLASH_PAGE_SIZE 256
#define FLASH_STATUS_MASK 0xFFFF
#define SECTORS_PER_BLOCK (FLASH_BLOCK_SIZE / FLASH_SECTOR_SIZE)

/* ESP32S3仅支持32位寻址*/
#if defined(ESP32S3)
#define FLASH_MAX_SIZE 64*1024*1024
#else
#define FLASH_MAX_SIZE 16*1024*1024
#endif

/* 全套协议命令*/
typedef enum {
  /* ESP8266和ESP32引导加载程序支持的命令*/
  ESP_FLASH_BEGIN = 0x02,
  ESP_FLASH_DATA = 0x03,
  ESP_FLASH_END = 0x04,
  ESP_MEM_BEGIN = 0x05,
  ESP_MEM_END = 0x06,
  ESP_MEM_DATA = 0x07,
  ESP_SYNC = 0x08,
  ESP_WRITE_REG = 0x09,
  ESP_READ_REG = 0x0a,

  /* ESP32引导加载器支持的命令*/
  ESP_SPI_SET_PARAMS = 0x0b,
  ESP_PIN_READ = 0x0c, /* ??? */
  ESP_SPI_ATTACH = 0x0d,
  ESP_SPI_READ = 0x0e,
  ESP_SET_BAUD = 0x0f,
  ESP_FLASH_DEFLATED_BEGIN = 0x10,
  ESP_FLASH_DEFLATED_DATA = 0x11,
  ESP_FLASH_DEFLATED_END = 0x12,
  ESP_FLASH_VERIFY_MD5 = 0x13,

  /* ESP32S2和更高版本引导加载程序支持的命令*/
  ESP_GET_SECURITY_INFO = 0x14,

  /* 仅存根命令*/
  ESP_ERASE_FLASH = 0xD0,
  ESP_ERASE_REGION = 0xD1,
  ESP_READ_FLASH = 0xD2,
  ESP_RUN_USER_CODE = 0xD3,

  /* Flash加密调试模式支持的命令*/
  ESP_FLASH_ENCRYPT_DATA = 0xD4,
} esp_command;

/* 命令请求标头*/
typedef struct __attribute__((packed)) {
  uint8_t zero;
  uint8_t op; /* 映射到esp_command枚举*/
  uint16_t data_len;
  int32_t checksum;
  uint8_t data_buf[32]; /* 实际可变长度，由datalen确定*/
} esp_command_req_t;

/* 命令响应标头*/
typedef struct __attribute__((packed)) {
  uint8_t resp; /* 应为“1”*/
  uint8_t op_ret; /* 应匹配“op”*/
  uint16_t len_ret; /* 结果数据的长度（可以忽略，因为SLIP框架有帮助）*/
  int32_t value; /* 某些命令使用的32位响应*/
} esp_command_response_t;


/* 命令响应后面有一些（可选）数据，然后是2个（或ESP32 ROM上的4个）字节的状态。
 */
typedef struct __attribute__((packed)) {
  uint8_t error; /* 非零=失败*/
  uint8_t status; /* 故障状态*/
} esp_command_data_status_t;

/* 错误代码*/
typedef enum {
  ESP_OK = 0,

  ESP_BAD_DATA_LEN = 0xC0,
  ESP_BAD_DATA_CHECKSUM = 0xC1,
  ESP_BAD_BLOCKSIZE = 0xC2,
  ESP_INVALID_COMMAND = 0xC3,
  ESP_FAILED_SPI_OP = 0xC4,
  ESP_FAILED_SPI_UNLOCK = 0xC5,
  ESP_NOT_IN_FLASH_MODE = 0xC6,
  ESP_INFLATE_ERROR = 0xC7,
  ESP_NOT_ENOUGH_DATA = 0xC8,
  ESP_TOO_MUCH_DATA = 0xC9,

  ESP_CMD_NOT_IMPLEMENTED = 0xFF,
} esp_command_error;

#endif /* STUB_FLASHER_H_ */

