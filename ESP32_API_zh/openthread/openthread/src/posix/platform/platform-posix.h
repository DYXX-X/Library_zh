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

#ifndef PLATFORM_POSIX_H_
#define PLATFORM_POSIX_H_

#include "openthread-posix-config.h"

#include <errno.h>
#include <net/if.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>

#include <openthread/error.h>
#include <openthread/instance.h>
#include <openthread/ip6.h>
#include <openthread/openthread-system.h>
#include <openthread/platform/time.h>

#include "common/logging.hpp"

#include "lib/platform/exit_code.h"
#include "lib/url/url.hpp"

/**
 * @def OPENTHREAD_POSIX_VIRTUAL_TIME
 *
 * 此设置配置是否使用虚拟时间。
 *
 */
#ifndef OPENTHREAD_POSIX_VIRTUAL_TIME
#define OPENTHREAD_POSIX_VIRTUAL_TIME 0
#endif

/**
 * 这是守护程序模式使用的套接字名称。
 *
 */
#define OPENTHREAD_POSIX_DAEMON_SOCKET_NAME OPENTHREAD_POSIX_CONFIG_DAEMON_SOCKET_BASENAME ".sock"

#ifdef __cplusplus
extern "C" {
#endif

enum
{
    OT_SIM_EVENT_ALARM_FIRED        = 0,
    OT_SIM_EVENT_RADIO_RECEIVED     = 1,
    OT_SIM_EVENT_UART_WRITE         = 2,
    OT_SIM_EVENT_RADIO_SPINEL_WRITE = 3,
    OT_EVENT_DATA_MAX_SIZE          = 1024,
};

OT_TOOL_PACKED_BEGIN
struct VirtualTimeEvent
{
    uint64_t mDelay;
    uint8_t  mEvent;
    uint16_t mDataLength;
    uint8_t  mData[OT_EVENT_DATA_MAX_SIZE];
} OT_TOOL_PACKED_END;

struct RadioProcessContext
{
    const fd_set *mReadFdSet;
    const fd_set *mWriteFdSet;
};

/**
 * 此函数初始化OpenThread使用的报警服务。
 *
 * @param[in]  aSpeedUpFactor   加速系数。
 * @param[in]  aRealTimeSignal  微秒报警的实时信号。
 *
 */
void platformAlarmInit(uint32_t aSpeedUpFactor, int aRealTimeSignal);

/**
 * 此函数检索报警触发前的剩余时间。
 *
 * @param[out]  aTimeval  指向timeval结构的指针。
 *
 */
void platformAlarmUpdateTimeout(struct timeval *tv);

/**
 * 此功能执行报警驱动程序处理。
 *
 * @param[in]  aInstance  OpenThread实例结构。
 *
 */
void platformAlarmProcess(otInstance *aInstance);

/**
 * 此函数返回下一个报警事件时间。
 *
 * @returns 下一次报警火灾时间。
 *
 */
int32_t platformAlarmGetNext(void);

#ifndef MS_PER_S
#define MS_PER_S 1000
#endif
#ifndef US_PER_MS
#define US_PER_MS 1000
#endif
#ifndef US_PER_S
#define US_PER_S (MS_PER_S * US_PER_MS)
#endif
#ifndef NS_PER_US
#define NS_PER_US 1000
#endif

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
 * @note 即使当@p aPlatformConfig->mResetRadio为false时，仍会从RCP中发生重置事件（即[PSPINEL_STATUS_reset_BEGIN，SPINEL_ATUS_reset_END]之间的PROP_LAST_STATUS）。
 *
 * @param[in]   aUrl  指向以空结尾的无线电URL的指针。
 *
 */
void platformRadioInit(const char *aUrl);

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
 * @param[inout]  aTimeout     指向超时的指针。
 *
 */
void platformRadioUpdateFdSet(fd_set *aReadFdSet, fd_set *aWriteFdSet, int *aMaxFd, struct timeval *aTimeout);

/**
 * 此功能执行无线电驱动程序处理。
 *
 * @param[in]   aInstance       指向OpenThread实例的指针。
 * @param[in]   aReadFdSet      指向读取文件描述符的指针。
 * @param[in]   aWriteFdSet     指向写入文件描述符的指针。
 *
 */
void platformRadioProcess(otInstance *aInstance, const fd_set *aReadFdSet, const fd_set *aWriteFdSet);

/**
 * 此函数初始化OpenThread使用的随机数服务。
 *
 */
void platformRandomInit(void);

/**
 * 此函数初始化OpenThread使用的日志记录服务。
 *
 * @param[in] aName   将在每个日志行前面加上前缀的名称字符串。
 *
 */
void platformLoggingInit(const char *aName);

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
 * @param[in]   aReadFdSet      指向读取文件描述符的指针。
 * @param[in]   aWriteFdSet     指向写入文件描述符的指针。
 * @param[in]   aErrorFdSet     指向错误文件描述符的指针。
 *
 */
void platformUartProcess(const fd_set *aReadFdSet, const fd_set *aWriteFdSet, const fd_set *aErrorFdSet);

/**
 * 此函数初始化平台netif。
 *
 * @note 在创建OpenThread实例之前调用此函数。
 *
 * @param[in]   aInterfaceName  指向线程网络接口名称的指针。
 *
 */
void platformNetifInit(const char *aInterfaceName);

/**
 * 此函数设置平台netif。
 *
 * @note 在创建OpenThread实例后调用此函数。
 *
 * @param[in]   aInstance       指向OpenThread实例的指针。
 *
 */
void platformNetifSetUp(void);

/**
 * 此函数用于删除平台netif。
 *
 * @note 在销毁OpenThread实例之前调用此函数。
 *
 */
void platformNetifTearDown(void);

/**
 * 此函数取消初始化平台netif。
 *
 * @note 在OpenThread实例被销毁后调用此函数。
 *
 */
void platformNetifDeinit(void);

/**
 * 此函数使用平台netif模块使用的文件描述符更新文件描述符集。
 *
 * @param[inout]  aReadFdSet    指向读取文件描述符的指针。
 * @param[inout]  aWriteFdSet   指向写入文件描述符的指针。
 * @param[inout]  aErrorFdSet   指向错误文件描述符的指针。
 * @param[inout]  aMaxFd        指向最大文件描述符的指针。
 *
 */
void platformNetifUpdateFdSet(fd_set *aReadFdSet, fd_set *aWriteFdSet, fd_set *aErrorFdSet, int *aMaxFd);

/**
 * 此函数执行平台netif处理。
 *
 * @param[in]   aReadFdSet      指向读取文件描述符的指针。
 * @param[in]   aWriteFdSet     指向写入文件描述符的指针。
 * @param[in]   aErrorFdSet     指向错误文件描述符的指针。
 *
 */
void platformNetifProcess(const fd_set *aReadFdSet, const fd_set *aWriteFdSet, const fd_set *aErrorFdSet);

/**
 * 此函数用于向平台netif通知状态更改。
 *
 * @param[in]   aInstance       指向OpenThread实例的指针。
 * @param[in]   aFlags          表示状态更改事件的标志。
 *
 */
void platformNetifStateChange(otInstance *aInstance, otChangedFlags aFlags);

/**
 * 此函数用于初始化虚拟时间模拟。
 *
 * @params[in]  aNodeId     此模拟设备的节点id。
 *
 */
void virtualTimeInit(uint16_t aNodeId);

/**
 * 此函数用于取消初始化虚拟时间模拟。
 *
 */
void virtualTimeDeinit(void);

/**
 * 此函数执行虚拟时间模拟处理。
 *
 * @param[in]   aInstance       指向OpenThread实例的指针。
 * @param[in]   aReadFdSet      指向读取文件描述符的指针。
 * @param[in]   aWriteFdSet     指向写入文件描述符的指针。
 *
 */
void virtualTimeProcess(otInstance *  aInstance,
                        const fd_set *aReadFdSet,
                        const fd_set *aWriteFdSet,
                        const fd_set *aErrorFdSet);

/**
 * 此函数使用虚拟时间模拟使用的文件描述符更新文件描述符集。
 *
 * @param[inout]  aReadFdSet   指向读取文件描述符的指针。
 * @param[inout]  aWriteFdSet  指向写入文件描述符的指针。
 * @param[inout]  aErrorFdSet  指向错误文件描述符的指针。
 * @param[inout]  aMaxFd       指向最大文件描述符的指针。
 * @param[inout]  aTimeout     指向超时的指针。
 *
 */
void virtualTimeUpdateFdSet(fd_set *        aReadFdSet,
                            fd_set *        aWriteFdSet,
                            fd_set *        aErrorFdSet,
                            int *           aMaxFd,
                            struct timeval *aTimeout);

/**
 * 此函数发送虚拟时间模拟的无线电尖晶石事件。
 *
 * @param[in] aData     指向尖晶石框架的指针。
 * @param[in] aLength   尖晶石框架的长度。
 *
 */
void virtualTimeSendRadioSpinelWriteEvent(const uint8_t *aData, uint16_t aLength);

/**
 * 此函数接收虚拟时间模拟事件。
 *
 * @param[out]  aEvent  指向接收事件的事件的指针。
 *
 */
void virtualTimeReceiveEvent(struct VirtualTimeEvent *aEvent);

/**
 * 此函数通过虚拟时间模拟发送休眠事件。
 *
 * @param[in]   aTimeout    指向睡眠时间的指针。
 *
 */
void virtualTimeSendSleepEvent(const struct timeval *aTimeout);

/**
 * 此函数执行虚拟时间模拟的无线电尖晶石处理。
 *
 * @param[in]   aInstance   指向OpenThread实例的指针。
 * @param[in]   aEvent      指向当前事件的指针。
 *
 */
void virtualTimeRadioSpinelProcess(otInstance *aInstance, const struct VirtualTimeEvent *aEvent);

enum SocketBlockOption
{
    kSocketBlock,
    kSocketNonBlock,
};

/**
 * 此函数初始化平台TREL UDP6驱动程序。
 *
 * @param[in]   aInterfaceName   网络接口的名称。
 *
 */
void platformTrelInit(const char *aInterfaceName);

/**
 * 此功能关闭平台TREL UDP6平台驱动程序。
 *
 */
void platformTrelDeinit(void);

/**
 * 此函数使用TREL驱动程序使用的文件描述符更新文件描述符集。
 *
 * @param[inout]  aReadFdSet   指向读取文件描述符的指针。
 * @param[inout]  aWriteFdSet  指向写入文件描述符的指针。
 * @param[inout]  aMaxFd       指向最大文件描述符的指针。
 * @param[inout]  aTimeout     指向超时的指针。
 *
 */
void platformTrelUpdateFdSet(fd_set *aReadFdSet, fd_set *aWriteFdSet, int *aMaxFd, struct timeval *aTimeout);

/**
 * 此函数执行TREL驱动程序处理。
 *
 * @param[in]   aInstance       指向OpenThread实例的指针。
 * @param[in]   aReadFdSet      指向读取文件描述符的指针。
 * @param[in]   aWriteFdSet     指向写入文件描述符的指针。
 *
 */
void platformTrelProcess(otInstance *aInstance, const fd_set *aReadFdSet, const fd_set *aWriteFdSet);

/**
 * 此函数创建设置了SOCK_CLOEXEC标志的套接字。
 *
 * @param[in]   aDomain       通信域。
 * @param[in]   aType         沟通的语义。
 * @param[in]   aProtocol     要使用的协议。
 * @param[in]   aBlockOption  是否添加非块标志。
 *
 * @returns 创建的套接字的文件描述符。
 *
 * @retval  -1无法创建套接字。
 *
 */
int SocketWithCloseExec(int aDomain, int aType, int aProtocol, SocketBlockOption aBlockOption);

/**
 * 线程网络接口的名称。
 *
 */
extern char gNetifName[IFNAMSIZ];

/**
 * 线程网络接口的索引。
 *
 */
extern unsigned int gNetifIndex;

/**
 * 此函数用于初始化平台骨干网络。
 *
 * @note 在创建OpenThread实例之前调用此函数。
 *
 * @param[in]   aInterfaceName  指向线程网络接口名称的指针。
 *
 */
void platformBackboneInit(const char *aInterfaceName);

/**
 * 此功能设置平台骨干网络。
 *
 * @note 在创建OpenThread实例后调用此函数。
 *
 * @param[in]   aInstance       指向OpenThread实例的指针。
 *
 */
void platformBackboneSetUp(void);

/**
 * 此功能可拆除平台主干网络。
 *
 * @note 在销毁OpenThread实例之前调用此函数。
 *
 */
void platformBackboneTearDown(void);

/**
 * 此功能关闭平台骨干网络。
 *
 * @note 在OpenThread实例被销毁后调用此函数。
 *
 */
void platformBackboneDeinit(void);

/**
 * 此功能用于向平台骨干网络通知状态更改。
 *
 * @param[in]   aInstance       指向OpenThread实例的指针。
 * @param[in]   aFlags          表示状态更改事件的标志。
 *
 */
void platformBackboneStateChange(otInstance *aInstance, otChangedFlags aFlags);

/**
 * 指向OpenThread实例的指针。
 *
 */
extern otInstance *gInstance;

/**
 * 骨干网络接口的名称。
 *
 */
extern char gBackboneNetifName[IFNAMSIZ];

/**
 * 骨干网络接口的索引。
 *
 */
extern unsigned int gBackboneNetifIndex;

/**
 * 此函数指示基础结构接口是否正在运行。
 *
 * @returns 如果基础结构接口正在运行，则为TRUE，否则为FALSE。
 *
 */
bool platformInfraIfIsRunning(void);

#ifdef __cplusplus
}
#endif
#endif // PLATFORM_POSIX_H_

