/*
 * SPDX文件版权文本：2006 Christian Walter
 *
 * SPDX许可证标识符：BSD-3-条款
 *
 * SPDX文件撰稿人：2016-2021 Espressif Systems（Shanghai）CO LTD
 */
/*
 * FreeModbus库：ESP32 TCP端口版权所有（C）2006 Christian Walter<wolti@sil.at>crt0.S的部分版权所有（c）1995、1996、1998 Cygnus支持
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES IF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 文件：$Id:port.h，v 1.2 2006/09/04 14:39:20 wolti Exp$
 */

#ifndef _PORT_TCP_SLAVE_H
#define _PORT_TCP_SLAVE_H

/* -----------------------平台包括--------------------------------*/
#include "esp_log.h"

#include "lwip/sys.h"
#include "freertos/event_groups.h"
#include "port.h"

/* -----------------------定义------------------------------------------*/

#ifndef TRUE
#define TRUE                    1
#endif

#ifndef FALSE
#define FALSE                   0
#endif

#ifdef __cplusplus
PR_BEGIN_EXTERN_C
#endif

/* -----------------------类型定义---------------------------------*/

typedef struct {
    int xIndex;                 /*!< 从属信息索引*/
    int xSockId;                /*!< 从机的套接字ID*/
    int xError;                 /*!< 套接字错误*/
    int xRcvErr;                /*!< 套接字接收错误*/
    const char* pcIpAddr;       /*!< TCP/UDP IP地址*/
    UCHAR ucSlaveAddr;          /*!< 从属短地址*/
    UCHAR* pucRcvBuf;           /*!< 接收缓冲区指针*/
    USHORT usRcvPos;            /*!< 接收缓冲器位置*/
    int pcPort;                 /*!< TCP/UDP端口号*/
    eMBPortProto xMbProto;      /*!< 协议类型*/
    int64_t xSendTimeStamp;     /*!< 发送请求时间戳*/
    int64_t xRecvTimeStamp;     /*!< 接收响应时间戳*/
    uint16_t usTidCnt;          /*!< 从属服务器的事务标识符（TID）*/
} MbSlaveInfo_t;

typedef struct {
    TaskHandle_t  xMbTcpTaskHandle;     /*!< 主TCP/UDP处理任务句柄*/
    QueueHandle_t xConnectQueue;        /*!< 主连接队列*/
    USHORT usPort;                      /*!< 主TCP/UDP端口号*/
    USHORT usMbSlaveInfoCount;          /*!< 已连接从属设备的主计数*/
    USHORT ucCurSlaveIndex;             /*!< 主电流处理从索引*/
    eMBPortIpVer eMbIpVer;              /*!< 主IP版本*/
    eMBPortProto eMbProto;              /*!< 主协议类型*/
    void* pvNetIface;                   /*!< 主netif接口指针*/
    MbSlaveInfo_t** pxMbSlaveInfo;      /*!< 每个连接从属设备的主信息结构*/
    MbSlaveInfo_t* pxMbSlaveCurrInfo;   /*!< 主电流从信息*/
} MbPortConfig_t;

typedef struct {
    USHORT usIndex;                     /*!< 地址信息索引*/
    const char* pcIPAddr;               /*!< 表示从属设备的IP地址*/
    UCHAR ucSlaveAddr;                  /*!< MBAP帧的从属单元ID（UID）字段*/
} MbSlaveAddrInfo_t;

/* -----------------------功能原型------------------------------*/

// Modbus控制器接口使用以下功能配置Modbus端口。
/**
 * 注册从属IP地址
 *
 * @param usIndex 配置中元素的索引
 * @param pcIpStr 要注册的IP地址
 * @param ucSlaveAddress 从属元件索引
 *
 * @return 如果地址注册成功，则为TRUE，否则为FALSE
 */
BOOL xMBTCPPortMasterAddSlaveIp(const USHORT usIndex, const CHAR* pcIpStr, UCHAR ucSlaveAddress);

/**
 * 保留FSM事件句柄和掩码，然后等待主堆栈启动
 *
 * @param xEventHandle 主事件句柄
 * @param xEvent 启动Modbus堆栈FSM的事件掩码
 * @param usTimeout -等待堆栈启动的超时（以滴答为单位）
 *
 * @return 如果堆栈已启动，则为TRUE，否则为FALSE
 */
BOOL xMBTCPPortMasterWaitEvent(EventGroupHandle_t xEventHandle, EventBits_t xEvent, USHORT usTimeout);

/**
 * 设置主端口的网络选项
 *
 * @param pvNetIf netif接口指针
 * @param xIpVersion 主端口的IP版本选项
 * @param xProto 主端口的协议版本选项
 *
 * @return 没有一个
 */
void vMBTCPPortMasterSetNetOpt(void* pvNetIf, eMBPortIpVer xIpVersion, eMBPortProto xProto);

#ifdef __cplusplus
PR_END_EXTERN_C
#endif
#endif

