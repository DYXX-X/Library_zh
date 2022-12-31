/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件包括特定于平台的初始化器。
 */

#ifndef PLATFORM_SIMULATION_H_
#define PLATFORM_SIMULATION_H_

#include <openthread-core-config.h>
#include <openthread/config.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <poll.h>
#include <signal.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>

#include <openthread/instance.h>

#include "openthread-core-config.h"
#include "platform-config.h"

enum
{
    OT_SIM_EVENT_ALARM_FIRED        = 0,
    OT_SIM_EVENT_RADIO_RECEIVED     = 1,
    OT_SIM_EVENT_UART_WRITE         = 2,
    OT_SIM_EVENT_RADIO_SPINEL_WRITE = 3,
    OT_SIM_EVENT_OTNS_STATUS_PUSH   = 5,
    OT_EVENT_DATA_MAX_SIZE          = 1024,
};

OT_TOOL_PACKED_BEGIN
struct Event
{
    uint64_t mDelay;
    uint8_t  mEvent;
    uint16_t mDataLength;
    uint8_t  mData[OT_EVENT_DATA_MAX_SIZE];
} OT_TOOL_PACKED_END;

enum
{
    MAX_NETWORK_SIZE = OPENTHREAD_SIMULATION_MAX_NETWORK_SIZE,
};

/**
 * 唯一节点ID。
 *
 */
extern uint32_t gNodeId;

/**
 * 此函数初始化OpenThread使用的报警服务。
 *
 */
void platformAlarmInit(uint32_t aSpeedUpFactor);

/**
 * 此函数检索报警触发前的剩余时间。
 *
 * @param[out]  aTimeout  指向timeval结构的指针。
 *
 */
void platformAlarmUpdateTimeout(struct timeval *aTimeout);

/**
 * 此功能执行报警驱动程序处理。
 *
 * @param[in]  aInstance  OpenThread实例结构。
 *
 */
void platformAlarmProcess(otInstance *aInstance);

/**
 * 此函数将持续时间返回到下一个报警事件时间（以微秒为单位）
 *
 * @returns 下一个报警事件的持续时间（以微秒为单位）。
 *
 */
uint64_t platformAlarmGetNext(void);

/**
 * 此函数返回当前报警时间。
 *
 * @returns 当前报警时间。
 *
 */
uint64_t platformAlarmGetNow(void);

/**
 * 此函数将报警时间提前@p aDelta。
 *
 * @param[in]  aDelta  提前的时间。
 *
 */
void platformAlarmAdvanceNow(uint64_t aDelta);

/**
 * 此函数初始化OpenThread使用的无线电服务。
 *
 */
void platformRadioInit(void);

/**
 * 此函数关闭OpenThread使用的无线电服务。
 *
 */
void platformRadioDeinit(void);

/**
 * 此功能输入接收的无线电帧。
 *
 * @param[in]  aInstance   指向OpenThread实例的指针。
 * @param[in]  aBuf        指向接收到的无线帧的指针。
 * @param[in]  aBufLength  接收的无线帧的大小。
 *
 */
void platformRadioReceive(otInstance *aInstance, uint8_t *aBuf, uint16_t aBufLength);

/**
 * 此函数使用无线电驱动程序使用的文件描述符更新文件描述符集。
 *
 * @param[inout]  aReadFdSet   指向读取文件描述符的指针。
 * @param[inout]  aWriteFdSet  指向写入文件描述符的指针。
 * @param[inout]  aMaxFd       指向最大文件描述符的指针。
 *
 */
void platformRadioUpdateFdSet(fd_set *aReadFdSet, fd_set *aWriteFdSet, int *aMaxFd);

/**
 * 此功能执行无线电驱动程序处理。
 *
 * @param[in]  aInstance    OpenThread实例结构。
 * @param[in]  aReadFdSet   指向读取文件描述符的指针。
 * @param[in]  aWriteFdSet  指向写入文件描述符的指针。
 *
 */
void platformRadioProcess(otInstance *aInstance, const fd_set *aReadFdSet, const fd_set *aWriteFdSet);

/**
 * 此函数初始化OpenThread使用的随机数服务。
 *
 */
void platformRandomInit(void);

/**
 * 此函数使用UART驱动程序使用的文件描述符更新文件描述符集。
 *
 * @param[inout]  aReadFdSet   指向读取文件描述符的指针。
 * @param[inout]  aWriteFdSet  指向写入文件描述符的指针。
 * @param[inout]  aMaxFd       指向最大文件描述符的指针。
 *
 */
void platformUartUpdateFdSet(fd_set *aReadFdSet, fd_set *aWriteFdSet, fd_set *aErrorFdSet, int *aMaxFd);

/**
 * 此功能执行无线电驱动程序处理。
 *
 */
void platformUartProcess(void);

/**
 * 此函数用于恢复Uart。
 *
 */
void platformUartRestore(void);

/**
 * 此函数发送模拟事件。
 *
 * @param[in]   aEvent  指向要发送的模拟事件的指针
 *
 */
void otSimSendEvent(const struct Event *aEvent);

/**
 * 此函数通过模拟发送Uart数据。
 *
 * @param[in]   aData       指向UART数据的指针。
 * @param[in]   aLength     UART数据长度。
 *
 */
void otSimSendUartWriteEvent(const uint8_t *aData, uint16_t aLength);

/**
 * 此功能检查无线电发射是否挂起。
 *
 * @returns 无线电发射是否待定。
 *
 */
bool platformRadioIsTransmitPending(void);

#if OPENTHREAD_CONFIG_RADIO_LINK_TREL_ENABLE

/**
 * 此函数初始化TREL服务。
 *
 * @param[in] aSpeedUpFactor   时间加速因子。
 *
 */
void platformTrelInit(uint32_t aSpeedUpFactor);

/**
 * 此功能关闭TREL服务。
 *
 */
void platformTrelDeinit(void);

/**
 * 此函数使用TREL使用的文件描述符更新文件描述符集。
 *
 * @param[inout]  aReadFdSet   指向读取文件描述符的指针。
 * @param[inout]  aWriteFdSet  指向写入文件描述符的指针。
 * @param[inout]  aTimeout     指向超时的指针。
 * @param[inout]  aMaxFd       指向最大文件描述符的指针。
 *
 */
void platformTrelUpdateFdSet(fd_set *aReadFdSet, fd_set *aWriteFdSet, struct timeval *aTimeout, int *aMaxFd);

/**
 * 此函数执行TREL处理。
 *
 * @param[in]  aInstance    OpenThread实例结构。
 * @param[in]  aReadFdSet   指向读取文件描述符的指针。
 * @param[in]  aWriteFdSet  指向写入文件描述符的指针。
 *
 */
void platformTrelProcess(otInstance *aInstance, const fd_set *aReadFdSet, const fd_set *aWriteFdSet);

#endif // OPENTHREAD_CONFIG_RADIO_LINK_TREL_ENABLE

#endif // PLATFORM_SIMULATION_H_

