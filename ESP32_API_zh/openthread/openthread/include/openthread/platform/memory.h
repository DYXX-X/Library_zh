/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 该文件包括动态内存分配的平台抽象。
 */

#ifndef OPENTHREAD_PLATFORM_MEMORY_H_
#define OPENTHREAD_PLATFORM_MEMORY_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup 平板存储器
 *
 * @brief 该模块包括动态内存分配的平台抽象。
 *
 * @{
 *
 */

/*
 * OpenThread仅在支持多个并发实例时需要动态内存分配，例如MbedTL。
 */

/**
 * 动态分配新内存。在支持它的平台上，应该重定向到calloc。对于那些不支持calloc的，应该支持相同的功能：
 *
 *   “calloc（）函数连续为count个对象分配足够的空间，每个对象的内存大小为字节，并返回一个指向已分配内存的指针。已分配的内存由值为零的字节填充。”
 *
 * OPENTHREAD_CONFIG_HEAP_EXTERNAL_ENABLE需要此功能。
 *
 * @param[in] aNum   要分配的块数
 * @param[in] aSize  要分配的每个块的大小
 *
 * @retval void*指向分配内存前面的指针
 * @retval NULL分配请求的内存失败。
 */
void *otPlatCAlloc(size_t aNum, size_t aSize);

/**
 * 释放动态分配的内存。
 *
 * OPENTHREAD_CONFIG_HEAP_EXTERNAL_ENABLE需要此功能。
 *
 * @param[in] aPtr  内存块要释放的指针。指针可能为空。
 */
void otPlatFree(void *aPtr);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_PLATFORM_MEMORY_H_

