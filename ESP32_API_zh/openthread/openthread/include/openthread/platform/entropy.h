/*
 *  版权所有（c）2019，The OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 该文件包括熵生成的平台抽象。
 */

#ifndef OPENTHREAD_PLATFORM_ENTROPY_H_
#define OPENTHREAD_PLATFORM_ENTROPY_H_

#include <stdint.h>

#include <openthread/error.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup 平板熵
 *
 * @brief 该模块包括熵生成的平台抽象。
 *
 * @{
 *
 */

/**
 * 用熵填充缓冲区。
 *
 * 此功能必须使用真随机数生成器（TRNG）实现。
 *
 * @param[out]  aOutput              指向真正随机值所在位置的指针。不能为NULL。
 * @param[in]   aOutputLength        @p aBuffer的大小。
 *
 * @retval OT_ERROR_NONE成功用真随机值填充@p aBuffer。
 * @retval OT_ERROR_FAILED无法用真随机值填充@p aBuffer。
 * @retval OT_ERROR_INVALID_ARGS@p aBuffer设置为NULL。
 *
 */
otError otPlatEntropyGet(uint8_t *aOutput, uint16_t aOutputLength);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”结尾
#endif

#endif // OPENTHREAD_PLATFORM_ENTROPY_H_

