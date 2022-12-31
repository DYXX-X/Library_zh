/*
 *  版权所有（c）2020，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file 此文件包含用于验证运行时条件的宏。
 */

#ifndef PLATFORM_UTILS_ENCODING_H
#define PLATFORM_UTILS_ENCODING_H

#include <stdint.h>

/**
 * 将存储为小端字节数组的64位无符号整数转换为uint64_t。
 *
 * 允许数组进行字节对齐，以便通过此函数加载uint64_t值，避免因未对齐访问而导致处理器异常。
 *
 * @param[in]  aSource  字节数组。
 *
 * @returns 64位值作为uint64_t。
 *
 */
static inline uint64_t otEncodingReadUint64Le(const uint8_t *aSource)
{
    uint64_t value = 0;

    value |= (uint64_t)aSource[0];
    value |= ((uint64_t)aSource[1]) << 8;
    value |= ((uint64_t)aSource[2]) << 16;
    value |= ((uint64_t)aSource[3]) << 24;
    value |= ((uint64_t)aSource[4]) << 32;
    value |= ((uint64_t)aSource[5]) << 40;
    value |= ((uint64_t)aSource[6]) << 48;
    value |= ((uint64_t)aSource[7]) << 56;

    return value;
}

#endif // PLATFORM_UTILS_ENCODING_H

