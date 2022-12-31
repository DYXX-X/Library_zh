/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 该文件包括消息池的平台抽象。
 */

#ifndef OPENTHREAD_PLATFORM_MESSAGEPOOL_H_
#define OPENTHREAD_PLATFORM_MESSAGEPOOL_H_

#include <stdint.h>

#include <openthread/message.h>

/**
 * @addtogroup 平台消息池
 *
 * @brief 该模块包括消息池的平台抽象。
 *
 * @{
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 此结构表示OpenThread消息缓冲区。
 *
 */
typedef struct otMessageBuffer
{
    struct otMessageBuffer *mNext; ///<指向下一个缓冲区的指针。
} otMessageBuffer;

/**
 * 初始化平台实现的消息池。
 *
 * 启用“OPENTHREAD_CONFIG_PLATFORM_MESSAGE_MANAGEMENT”时使用此函数。
 *
 * @param[in] aInstance            指向OpenThread实例的指针。
 * @param[in] aMinNumFreeBuffers   uint16包含OpenThread所需的最小可用缓冲区数。
 * @param[in] aBufferSize          缓冲区对象的字节大小。
 *
 */
void otPlatMessagePoolInit(otInstance *aInstance, uint16_t aMinNumFreeBuffers, size_t aBufferSize);

/**
 * 从平台管理的缓冲池中分配缓冲区。
 *
 * 启用“OPENTHREAD_CONFIG_PLATFORM_MESSAGE_MANAGEMENT”时使用此函数。
 *
 * 返回的缓冲区实例必须至少有“aBufferSize”字节（在“otPlatMessagePoolInit（）”中指定）。
 *
 * @param[in] aInstance            指向OpenThread实例的指针。
 *
 * @returns 指向缓冲区的指针，如果没有缓冲区，则返回NULL。
 *
 */
otMessageBuffer *otPlatMessagePoolNew(otInstance *aInstance);

/**
 * 此函数用于将缓冲区释放回平台管理的缓冲池。
 *
 * 启用“OPENTHREAD_CONFIG_PLATFORM_MESSAGE_MANAGEMENT”时使用此函数。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 * @param[in]  aBuffer    要释放的缓冲区。
 *
 */
void otPlatMessagePoolFree(otInstance *aInstance, otMessageBuffer *aBuffer);

/**
 * 获取可用缓冲区的数量。
 *
 * 启用“OPENTHREAD_CONFIG_PLATFORM_MESSAGE_MANAGEMENT”时使用此函数。
 *
 * @param[in]  aInstance  指向OpenThread实例的指针。
 *
 * @returns OpenThread当前可用的可用缓冲区数。
 *
 */
uint16_t otPlatMessagePoolNumFreeBuffers(otInstance *aInstance);

#ifdef __cplusplus
} // 外部“C”
#endif

/**
 * @}
 *
 */

#endif // OPENTHREAD_PLATFORM_MESSAGEPOOL_H_

