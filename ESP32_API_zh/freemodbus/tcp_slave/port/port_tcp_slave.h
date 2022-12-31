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

#include "lwip/opt.h"
#include "lwip/sys.h"
#include "port.h"
#include "esp_modbus_common.h"      // 用于网络选项的常见类型

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
    int xIndex;                     /*!< Modbus信息索引*/
    int xSockId;                    /*!< 套接字id*/
    int xError;                     /*!< TCP/UDP套接字错误*/
    const char* pcIpAddr;           /*!< TCP/UDP IP地址（字符串）*/
    UCHAR* pucTCPBuf;               /*!< 缓冲区指针*/
    USHORT usTCPBufPos;             /*!< 缓冲器有效位置*/
    USHORT usTCPFrameBytesLeft;     /*!< 缓冲区剩余字节以接收事务*/
    int64_t xSendTimeStamp;         /*!< 发送请求时间戳*/
    int64_t xRecvTimeStamp;         /*!< 接收响应时间戳*/
    USHORT usTidCnt;                /*!< 数据包中的最后一个TID计数器*/
} MbClientInfo_t;

typedef struct {
    TaskHandle_t xMbTcpTaskHandle;      /*!< 服务器任务句柄*/
    xQueueHandle xRespQueueHandle;      /*!< 响应队列句柄*/
    MbClientInfo_t* pxCurClientInfo;    /*!< 当前客户端信息*/
    MbClientInfo_t** pxMbClientInfo;    /*!< 指向有关已连接客户端的信息的指针*/
    USHORT usPort;                      /*!< TCP/UDP端口号*/
    CHAR* pcBindAddr;                   /*!< 要绑定的IP地址*/
    eMBPortProto eMbProto;              /*!< 端口使用的协议类型*/
    USHORT usClientCount;               /*!< 客户端连接计数*/
    void* pvNetIface;                   /*!< 端口的网络netif接口指针*/
    eMBPortIpVer xIpVer;                /*!< IP协议版本*/
} MbSlavePortConfig_t;

/* -----------------------功能原型------------------------------*/

/**
 * 设置TCP/UDP Modbus端口通信选项的功能
 *
 * @param pvNetIf netif接口指针
 * @param xIpVersion IP版本
 * @param xProto 协议类型选项
 * @param pcBindAddr IP绑定地址
 *
 * @return 错误代码
 */
void vMBTCPPortSlaveSetNetOpt(void* pvNetIf, eMBPortIpVer xIpVersion, eMBPortProto xProto, CHAR* pcBindAddr);

#ifdef __cplusplus
PR_END_EXTERN_C
#endif
#endif

