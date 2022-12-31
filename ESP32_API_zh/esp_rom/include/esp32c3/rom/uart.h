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

#ifndef _ROM_UART_H_
#define _ROM_UART_H_

#include "esp_types.h"
#include "esp_attr.h"
#include "ets_sys.h"
#include "soc/soc.h"
#include "soc/uart_reg.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup uart_api、uart配置和通信相关api
  * @brief uart api
  */

/** @addtogroup uart_api@{
  */

#define RX_BUFF_SIZE                     0x400
#define TX_BUFF_SIZE                     100

//uart int enalbe寄存器ctrl位
#define UART_RCV_INTEN                   BIT0
#define UART_TRX_INTEN                   BIT1
#define UART_LINE_STATUS_INTEN           BIT2

//uart int标识ctrl位
#define UART_INT_FLAG_MASK               0x0E

//uart fifo ctrl位
#define UART_CLR_RCV_FIFO                BIT1
#define UART_CLR_TRX_FIFO                BIT2
#define UART_RCVFIFO_TRG_LVL_BITS        BIT6

//uart行控制位
#define  UART_DIV_LATCH_ACCESS_BIT       BIT7

//uart行状态位
#define  UART_RCV_DATA_RDY_FLAG          BIT0
#define  UART_RCV_OVER_FLOW_FLAG         BIT1
#define  UART_RCV_PARITY_ERR_FLAG        BIT2
#define  UART_RCV_FRAME_ERR_FLAG         BIT3
#define  UART_BRK_INT_FLAG               BIT4
#define  UART_TRX_FIFO_EMPTY_FLAG        BIT5
#define  UART_TRX_ALL_EMPTY_FLAG         BIT6   // 包括fifo和shift reg
#define  UART_RCV_ERR_FLAG               BIT7

//发送和接收消息帧头
#define FRAME_FLAG                       0x7E

typedef enum {
    UART_LINE_STATUS_INT_FLAG  = 0x06,
    UART_RCV_FIFO_INT_FLAG     = 0x04,
    UART_RCV_TMOUT_INT_FLAG    = 0x0C,
    UART_TXBUFF_EMPTY_INT_FLAG = 0x02
} UartIntType;   //考虑int_flag的bit0

typedef enum {
    RCV_ONE_BYTE      = 0x0,
    RCV_FOUR_BYTE     = 0x1,
    RCV_EIGHT_BYTE    = 0x2,
    RCV_FOURTEEN_BYTE = 0x3
} UartRcvFifoTrgLvl;

typedef enum {
    FIVE_BITS  = 0x0,
    SIX_BITS   = 0x1,
    SEVEN_BITS = 0x2,
    EIGHT_BITS = 0x3
} UartBitsNum4Char;

typedef enum {
    ONE_STOP_BIT      = 1,
    ONE_HALF_STOP_BIT = 2,
    TWO_STOP_BIT      = 3
} UartStopBitsNum;

typedef enum {
    NONE_BITS = 0,
    ODD_BITS  = 2,
    EVEN_BITS = 3

} UartParityMode;

typedef enum {
    STICK_PARITY_DIS = 0,
    STICK_PARITY_EN  = 2
} UartExistParity;

typedef enum {
    BIT_RATE_9600   = 9600,
    BIT_RATE_19200  = 19200,
    BIT_RATE_38400  = 38400,
    BIT_RATE_57600  = 57600,
    BIT_RATE_115200 = 115200,
    BIT_RATE_230400 = 230400,
    BIT_RATE_460800 = 460800,
    BIT_RATE_921600 = 921600
} UartBautRate;

typedef enum {
    NONE_CTRL,
    HARDWARE_CTRL,
    XON_XOFF_CTRL
} UartFlowCtrl;

typedef enum {
    EMPTY,
    UNDER_WRITE,
    WRITE_OVER
} RcvMsgBuffState;

typedef struct {
    uint8_t *pRcvMsgBuff;
    uint8_t *pWritePos;
    uint8_t *pReadPos;
    uint8_t  TrigLvl;
    RcvMsgBuffState BuffState;
} RcvMsgBuff;

typedef struct {
    uint32_t  TrxBuffSize;
    uint8_t  *pTrxBuff;
} TrxMsgBuff;

typedef enum {
    BAUD_RATE_DET,
    WAIT_SYNC_FRM,
    SRCH_MSG_HEAD,
    RCV_MSG_BODY,
    RCV_ESC_CHAR,
} RcvMsgState;

typedef struct {
    UartBautRate     baut_rate;
    UartBitsNum4Char data_bits;
    UartExistParity  exist_parity;
    UartParityMode   parity;    // 芯片大小（字节）
    UartStopBitsNum  stop_bits;
    UartFlowCtrl     flow_ctrl;
    uint8_t          buff_uart_no;  //指示哪个uart使用tx/rx缓冲区
    RcvMsgBuff       rcv_buff;
//    TrxMsgBuff trx_buff；
    RcvMsgState      rcv_state;
    int              received;
} UartDevice;

/**
  * @brief 初始化uart设备结构值并重置uart0/uart1 rx。请不要在SDK中调用此函数。
  *
  * @param  rxBuffer, 必须是指向RX_BUFF_SIZE字节或NULL的指针
  *
  * @return 没有一个
  */
void uartAttach(void *rxBuffer);

/**
  * @brief 对于UART下载引导模式，初始化uart0或uart1。请不要在SDK中调用此函数。
  *
  * @param  uint8_t uart_no:0表示UART0，否则表示UART1。
  *
  * @param  uint32_t 时钟：uart模块用来调整波特率的时钟。
  *
  * @return 没有一个
  */
void Uart_Init(uint8_t uart_no, uint32_t clock);

/**
  * @brief 修改uart baudrate。此功能将重置uart的RX/TX fifo。
  *
  * @param  uint8_t uart_no:0表示UART0，1表示UART1。
  *
  * @param  uint32_t DivLatchValue：（时钟<<4）/波特率。
  *
  * @return 没有一个
  */
void uart_div_modify(uint8_t uart_no, uint32_t DivLatchValue);

/**
  * @brief 对于UART下载引导模式，初始化uart0或uart1。请不要在SDK中调用此函数。
  *
  * @param  uint8_t uart_no:0表示UART0，1表示UART1。
  *
  * @param  uint8_t is_sync:0，只有一个UART模块，易于检测，等待检测；1，两个UART模块，难以检测、检测和返回。
  *
  * @return 没有一个
  */
int uart_baudrate_detect(uint8_t uart_no, uint8_t is_sync);

/**
  * @brief 切换uart_tx_one_char的printf通道。打印时请不要调用此函数。
  *
  * @param  uint8_t uart_no:0表示UART0，1表示UART1。
  *
  * @return 没有一个
  */
void uart_tx_switch(uint8_t uart_no);

/**
  * @brief 切换UART下载引导的消息交换通道。请不要在SDK中调用此函数。
  *
  * @param  uint8_t uart_no:0表示UART0，1表示UART1。
  *
  * @return 没有一个
  */
void uart_buff_switch(uint8_t uart_no);

/**
  * @brief 将字符输出到printf通道，等待fifo未满。
  *
  * @param  None
  *
  * @return OK.
  */
STATUS uart_tx_one_char(uint8_t TxChar);

/**
  * @brief 将字符输出到消息交换通道，等待fifo未满。请不要在SDK中调用此函数。
  *
  * @param  None
  *
  * @return OK.
  */
STATUS uart_tx_one_char2(uint8_t TxChar);

/**
  * @brief 等待uart tx完全清空。
  *
  * @param  uint8_t uart_no:0表示UART0，1表示UART1。
  *
  * @return 没有一个
  */
void uart_tx_flush(uint8_t uart_no);

/**
  * @brief 等待uart tx为空，最后一个字符发送成功。
  *
  * @param  uart_no ：0代表UART0，1代表UART1
  *
  * ROM代码中定义的函数有一个错误，因此我们在这里定义了正确的版本以实现兼容性。
  */
void uart_tx_wait_idle(uint8_t uart_no);

/**
  * @brief 从消息通道获取输入字符。请不要在SDK中调用此函数。
  *
  * @param  uint8_t *pRxChar：存储字符的指针。
  *
  * @return 确定成功。失败的失败。
  */
STATUS uart_rx_one_char(uint8_t *pRxChar);

/**
  * @brief 从消息通道获取输入字符，等待成功。请不要在SDK中调用此函数。
  *
  * @param  None
  *
  * @return char：输入字符值。
  */
char uart_rx_one_char_block(void);

/**
  * @brief 从消息通道获取输入字符串行。请不要在SDK中调用此函数。
  *
  * @param  uint8_t *pString：存储字符串的指针。
  *
  * @param  uint8_t MaxStrlen:最大字符串长度，包括“\0”。
  *
  * @return OK.
  */
STATUS UartRxString(uint8_t *pString, uint8_t MaxStrlen);

/**
  * @brief 在中断处理程序中处理接收到的信息。请不要在SDK中调用此函数。
  *
  * @param  void *para：消息接收缓冲区。
  *
  * @return 没有一个
  */
void uart_rx_intr_handler(void *para);

/**
  * @brief 从接收缓冲区获取一个字符。请不要在SDK中调用此函数。
  *
  * @param  RcvMsgBuff *pRxBuff：指向包含接收缓冲区的结构的指针。
  *
  * @param  uint8_t *pRxByte：存储字符的指针。
  *
  * @return 确定成功。失败的失败。
  */
STATUS uart_rx_readbuff( RcvMsgBuff *pRxBuff, uint8_t *pRxByte);

/**
  * @brief 从接收缓冲区获取所有字符。请不要在SDK中调用此函数。
  *
  * @param  uint8_t *pCmdLn：存储字符串的指针。
  *
  * @return 确定成功。失败的失败。
  */
STATUS UartGetCmdLn(uint8_t *pCmdLn);

/**
  * @brief 获取uart配置结构。请不要在SDK中调用此函数。
  *
  * @param  None
  *
  * @return UartDevice*：uart配置结构指针。
  */
UartDevice *GetUartDevice(void);

/**
  * @brief 发送一个数据包到下载工具，SLIP转义。请不要在SDK中调用此函数。
  *
  * @param  uint8_t *p：输出字符串的指针。
  *
  * @param  int len：字符串长度。
  *
  * @return 没有一个
  */
void send_packet(uint8_t *p, int len);

/**
  * @brief 接收来自下载工具的数据包，SLIP转义。请不要在SDK中调用此函数。
  *
  * @param  uint8_t *p：输入字符串的指针。
  *
  * @param  int len：如果字符串长度大于len，则字符串将被截断。
  *
  * @param  uint8_t is_sync:0，只有一个UART模块；1，两个UART模块。
  *
  * @return int：字符串的长度。
  */
int recv_packet(uint8_t *p, int len, uint8_t is_sync);

/**
  * @brief 发送一个数据包到下载工具，SLIP转义。请不要在SDK中调用此函数。
  *
  * @param  uint8_t *pData：指向输入字符串的指针。
  *
  * @param  uint16_t DataLen：字符串长度。
  *
  * @return 确定成功。失败的失败。
  */
STATUS SendMsg(uint8_t *pData, uint16_t DataLen);

/**
  * @brief 接收来自下载工具的数据包，SLIP转义。请不要在SDK中调用此函数。
  *
  * @param  uint8_t *pData：指向输入字符串的指针。
  *
  * @param  uint16_t MaxDataLen:如果字符串长度大于MaxDataLen，则字符串将被截断。
  *
  * @param  uint8_t is_sync:0，只有一个UART模块；1，两个UART模块。
  *
  * @return 确定成功。失败的失败。
  */
STATUS RcvMsg(uint8_t *pData, uint16_t MaxDataLen, uint8_t is_sync);

/**
  * @brief 检查此UART是否处于下载连接。请不要在SDK中调用此函数。
  *
  * @param  uint8_t uart_no:0表示UART0，1表示UART1。
  *
  * @return ETS_NO_BOOT=0表示否SEL_UART_BOOT=BIT（1）表示是。
  */
uint8_t UartConnCheck(uint8_t uart_no);

/**
  * @brief 初始化USB ACM UART需要提供至少128字节的缓冲区，以及您可能需要的任何rx缓冲区。
  *
  * @param cdc_acm_work_mem 指向CDC-ACM代码工作内存的指针
  * @param cdc_acm_work_mem_len 工作长度mem
  */
void Uart_Init_USB(void *cdc_acm_work_mem, int cdc_acm_work_mem_len);


/**
  * @brief 安装处理器以在CDC-ACM“UART”上检测到RTS更改时重置芯片。
  */
void uart_usb_enable_reset_on_rts(void);


extern UartDevice UartDev;

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* _ROM_UART_H_ */

