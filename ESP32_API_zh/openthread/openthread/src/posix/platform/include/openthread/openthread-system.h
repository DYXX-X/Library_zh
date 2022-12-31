/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 该文件定义OpenThread示例应用程序所需的平台特定函数。
 */

#ifndef OPENTHREAD_SYSTEM_H_
#define OPENTHREAD_SYSTEM_H_

#include <setjmp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/select.h>

#include <openthread/error.h>
#include <openthread/instance.h>
#include <openthread/platform/misc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 此枚举表示SPI接口的默认参数。
 *
 */
enum
{
    OT_PLATFORM_CONFIG_SPI_DEFAULT_MODE           = 0,       ///<默认SPI模式：CPOL=0，CPHA=0。
    OT_PLATFORM_CONFIG_SPI_DEFAULT_SPEED_HZ       = 1000000, ///<默认SPI速度（赫兹）。
    OT_PLATFORM_CONFIG_SPI_DEFAULT_CS_DELAY_US    = 20,      ///<SPI CûSğ断言后的默认延迟，单位：µsec。
    OT_PLATFORM_CONFIG_SPI_DEFAULT_RESET_DELAY_MS = 0, ///<断言后的默认延迟，以毫秒为单位。
    OT_PLATFORM_CONFIG_SPI_DEFAULT_ALIGN_ALLOWANCE =
        16, ///<从MISO帧开始剪辑的默认最大0xFF字节数。
    OT_PLATFORM_CONFIG_SPI_DEFAULT_SMALL_PACKET_SIZE =
        32,                                ///<我们可以在单个事务中接收的默认最小SPI数据包大小。
    OT_PLATFORM_CONFIG_MAX_RADIO_URLS = 2, ///<无线电URL的最大数量。
};

/**
 * 此结构表示特定于平台的配置。
 *
 */
typedef struct otPlatformConfig
{
    const char *mBackboneInterfaceName;                        ///<骨干网络接口名称。
    const char *mInterfaceName;                                ///<线程网络接口名称。
    const char *mRadioUrls[OT_PLATFORM_CONFIG_MAX_RADIO_URLS]; ///<无线电URL。
    uint8_t     mRadioUrlNum;                                  ///<无线电URL的数量。
    int         mRealTimeSignal;                               ///<微秒计时器的实时信号。
    uint32_t    mSpeedUpFactor;                                ///<加速系数。
} otPlatformConfig;

/**
 * 此函数执行OpenThread驱动程序的所有平台特定初始化，并初始化OpenThread实例。
 *
 * @note OpenThread库不调用此函数。相反，当OpenThread驱动程序的初始化最合适时，系统/ROS应该调用此函数。
 *
 * @param[in]  aPlatformConfig  平台配置结构。
 *
 * @returns 指向OpenThread实例的指针。
 *
 */
otInstance *otSysInit(otPlatformConfig *aPlatformConfig);

/**
 * 此函数完成OpenThread实例，并为OpenThread的驱动程序执行所有特定于平台的去初始化。
 *
 * @note OpenThread库不调用此函数。相反，当OpenThread驱动程序的去初始化最合适时，系统/ROS应该调用此函数。
 *
 */
void otSysDeinit(void);

/**
 * 此结构表示基于select（）的主循环的上下文。
 *
 */
typedef struct otSysMainloopContext
{
    fd_set         mReadFdSet;  ///<读取的文件描述符。
    fd_set         mWriteFdSet; ///<写入文件描述符。
    fd_set         mErrorFdSet; ///<错误文件描述符。
    int            mMaxFd;      ///<最大文件描述符。
    struct timeval mTimeout;    ///<超时。
} otSysMainloopContext;

/**
 * 此函数使用OpenThread驱动程序使用的文件描述符更新文件描述符集。
 *
 * @param[in]       aInstance   OpenThread实例结构。
 * @param[inout]    aMainloop   指向主循环上下文的指针。
 *
 */
void otSysMainloopUpdate(otInstance *aInstance, otSysMainloopContext *aMainloop);

/**
 * 此函数轮询OpenThread的主循环。
 *
 * @param[inout]    aMainloop   指向主循环上下文的指针。
 *
 * @returns select（）返回的值。
 *
 */
int otSysMainloopPoll(otSysMainloopContext *aMainloop);

/**
 * 此函数为OpenThread的示例应用程序执行所有特定于平台的处理。
 *
 * @note OpenThread库不调用此函数。相反，当处理OpenThread的驱动程序最合适时，系统/ROS应该在主循环中调用此函数。
 *
 * @param[in]   aInstance   OpenThread实例结构。
 * @param[in]   aMainloop   指向主循环上下文的指针。
 *
 */
void otSysMainloopProcess(otInstance *aInstance, const otSysMainloopContext *aMainloop);

/**
 * 此方法返回无线电url帮助字符串。
 *
 * @returns 无线电url帮助字符串。
 *
 */
const char *otSysGetRadioUrlHelpString(void);

extern otPlatResetReason gPlatResetReason;

/**
 * 此方法返回线程网络接口名称。
 *
 * @returns 线程网络接口名称。
 *
 */
const char *otSysGetThreadNetifName(void);

/**
 * 此方法返回线程网络接口索引。
 *
 * @returns 线程网络接口索引。
 *
 */
unsigned int otSysGetThreadNetifIndex(void);

#ifdef __cplusplus
} // 外部“C”结尾
#endif

#endif // OPENTHREAD_SYSTEM_H_

