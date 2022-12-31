/*
 *  版权所有（c）2020，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef OPENTHREAD_PLATFORM_FLASH_H_
#define OPENTHREAD_PLATFORM_FLASH_H_

#include <stdint.h>

#include <openthread/instance.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 此函数用于初始化闪存驱动程序。
 *
 * @param[in] aInstance  OpenThread实例结构。
 *
 */
void otPlatFlashInit(otInstance *aInstance);

/**
 * 此函数用于获取交换空间的大小。
 *
 * @param[in] aInstance  OpenThread实例结构。
 *
 * @returns 交换空间的大小（以字节为单位）。
 *
 */
uint32_t otPlatFlashGetSwapSize(otInstance *aInstance);

/**
 * 此函数清除@p aSwapIndex指示的交换空间。
 *
 * @param[in] aInstance   OpenThread实例结构。
 * @param[in] aSwapIndex  [0，1]中表示交换空间的值。
 *
 */
void otPlatFlashErase(otInstance *aInstance, uint8_t aSwapIndex);

/**
 * This function reads @p a将字节大小调整为@p aData。
 *
 * @param[in]  aInstance   OpenThread实例结构。
 * @param[in]  aSwapIndex  [0，1]中表示交换空间的值。
 * @param[in]  aOffset     交换空间内的字节偏移量。
 * @param[out] aData       用于读取的数据缓冲区指针。
 * @param[in]  aSize       要读取的字节数。
 *
 */
void otPlatFlashRead(otInstance *aInstance, uint8_t aSwapIndex, uint32_t aOffset, void *aData, uint32_t aSize);

/**
 * This function writes @p a@p aData中的大小字节。
 *
 * @param[in]  aInstance   OpenThread实例结构。
 * @param[in]  aSwapIndex  [0，1]中表示交换空间的值。
 * @param[in]  aOffset     交换空间内的字节偏移量。
 * @param[out] aData       指向要写入的数据的指针。
 * @param[in]  aSize       要写入的字节数。
 *
 *
 */
void otPlatFlashWrite(otInstance *aInstance, uint8_t aSwapIndex, uint32_t aOffset, const void *aData, uint32_t aSize);

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_PLATFORM_FLASH_H_

