/****************************************************************************
** 版权所有（C）2015 Intel Corporation
**
** 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
**
** 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/

#ifndef CBORJSON_H
#define CBORJSON_H

#include "cbor.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 转换为JSON*/
enum CborToJsonFlags
{
    CborConvertAddMetadata = 1,
    CborConvertTagsToObjects = 2,
    CborConvertIgnoreTags = 0,

    CborConvertObeyByteStringTags = 0,
    CborConvertByteStringsToBase64Url = 4,

    CborConvertRequireMapStringKeys = 0,
    CborConvertStringifyMapKeys = 8,

    CborConvertDefaultFlags = 0
};

CBOR_API CborError cbor_value_to_json_advance(FILE *out, CborValue *value, int flags);
CBOR_INLINE_API CborError cbor_value_to_json(FILE *out, const CborValue *value, int flags)
{
    CborValue copy = *value;
    return cbor_value_to_json_advance(out, &copy, flags);
}

#ifdef __cplusplus
}
#endif

#endif /* CBORJSON_H */


