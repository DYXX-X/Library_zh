/****************************************************************************
** 版权所有（C）2017 Intel Corporation
**
** 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
**
** 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/

#ifndef CBOR_UTF8_H
#define CBOR_UTF8_H

#include "compilersupport_p.h"

#include <stdint.h>

static inline uint32_t get_utf8(const uint8_t **buffer, const uint8_t *end)
{
    int charsNeeded;
    uint32_t uc, min_uc;
    uint8_t b;
    ptrdiff_t n = end - *buffer;
    if (n == 0)
        return ~0U;

    uc = *(*buffer)++;
    if (uc < 0x80) {
        /* 单字节UTF-8*/
        return uc;
    }

    /* 多字节UTF-8，解码*/
    if (unlikely(uc <= 0xC1))
        return ~0U;
    if (uc < 0xE0) {
        /* 双字节UTF-8*/
        charsNeeded = 2;
        min_uc = 0x80;
        uc &= 0x1f;
    } else if (uc < 0xF0) {
        /* 三字节UTF-8*/
        charsNeeded = 3;
        min_uc = 0x800;
        uc &= 0x0f;
    } else if (uc < 0xF5) {
        /* 四字节UTF-8*/
        charsNeeded = 4;
        min_uc = 0x10000;
        uc &= 0x07;
    } else {
        return ~0U;
    }

    if (n < charsNeeded)
        return ~0U;

    /* 第一个连续字符*/
    b = *(*buffer)++;
    if ((b & 0xc0) != 0x80)
        return ~0U;
    uc <<= 6;
    uc |= b & 0x3f;

    if (charsNeeded > 2) {
        /* 第二个连续字符*/
        b = *(*buffer)++;
        if ((b & 0xc0) != 0x80)
            return ~0U;
        uc <<= 6;
        uc |= b & 0x3f;

        if (charsNeeded > 3) {
            /* 第三个连续字符*/
            b = *(*buffer)++;
            if ((b & 0xc0) != 0x80)
                return ~0U;
            uc <<= 6;
            uc |= b & 0x3f;
        }
    }

    /* 超长序列？代理对？超出或超出范围？*/
    if (uc < min_uc || uc - 0xd800U < 2048U || uc > 0x10ffff)
        return ~0U;

    return uc;
}

#endif /* CBOR_UTF8_H */

