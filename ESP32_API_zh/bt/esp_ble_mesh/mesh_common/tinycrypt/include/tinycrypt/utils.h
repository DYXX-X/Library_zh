/* 实用程序。h-TinyCrypt接口到依赖于平台的运行时操作*/

/*
 *  英特尔公司版权所有（C）2017，保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 *    -源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。
 *
 *    -二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。
 *
 *    -未经事先书面许可，不得使用“英特尔公司”的名称或其贡献者的名称来支持或推广源自此软件的产品。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 与平台相关的运行时操作的接口。
 *
 */

#ifndef __BLE_MESH_TC_UTILS_H__
#define __BLE_MESH_TC_UTILS_H__

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 将缓冲区“from”复制到缓冲区“to”。
 * @return 如果：from_len>to_len，则返回TC_CRYPTO_SUCCESS（1）返回TC_CRYPTO_FAIL（0）。
 *
 * @param to OUT—目标缓冲区
 * @param to_len IN—目标缓冲区的长度
 * @param from IN——原始缓冲区
 * @param from_len IN——原始缓冲区的长度
 */
unsigned int _copy(uint8_t *to, unsigned int to_len,
                   const uint8_t *from, unsigned int from_len);

/**
 * @brief 将缓冲区中的值“val”设置为“to”，“len”次。
 *
 * @param to OUT—目标缓冲区
 * @param val IN—要在“to”中设置的值
 * @param len IN—复制值的次数
 */
void _set(void *to, uint8_t val, unsigned int len);

/**
 * @brief 将缓冲区中的值“val”设置为“”，“len”次，这样不会有被编译器优化的风险。如果编译器未设置__GNUC__并且优化级别删除了内存集，则可能需要实现_Set_secure函数并定义TINYCRYPT_ARCH_HAS_Set_Set_secure，这样可以确保内存集不会被优化。
 *
 * @param to OUT—目标缓冲区
 * @param val IN—要在“to”中设置的值
 * @param len IN—复制值的次数
 */
#ifdef TINYCRYPT_ARCH_HAS_SET_SECURE
extern void _set_secure(void *to, uint8_t val, unsigned int len);
#else /* ! TINYCRYPT_ARCH_HAS_SET_SECURE */
static inline void _set_secure(void *to, uint8_t val, unsigned int len)
{
    (void) memset(to, val, len);
#ifdef __GNUC__
    __asm__ __volatile__("" :: "g"(to) : "memory");
#endif /* __GNUC__ */
}
#endif /* TINYCRYPT_ARCH_HAS_SET_SECURE */

/*
 * @brief AES特有的倍增函数，它利用AES使用的有限域。
 * @return 返回^2
 *
 * @param a IN/OUT—要加倍的值
 */
uint8_t _double_byte(uint8_t a);

/*
 * @brief 用于比较两个字节序列是否相等的常数时间算法
 * @return 如果等于，则返回0，否则返回非零
 *
 * @param a IN—字节序列a
 * @param b IN—字节序列b
 * @param size IN——序列a和b的大小
 */
int _compare(const uint8_t *a, const uint8_t *b, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* __BLE_MESH_TC_UTILS_H__ */

