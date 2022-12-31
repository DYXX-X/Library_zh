/* 版权所有Joyent，Inc.和其他Node贡献者。保留所有权利。
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef url_parser_h
#define url_parser_h
#ifdef __cplusplus
extern "C" {
#endif

/* 每当您更改这些时，还要更新Makefile中的SONAME。*/
#define HTTP_PARSER_VERSION_MAJOR 2
#define HTTP_PARSER_VERSION_MINOR 9
#define HTTP_PARSER_VERSION_PATCH 1

#include <stddef.h>
#if defined(_WIN32) && !defined(__MINGW32__) && \
  (!defined(_MSC_VER) || _MSC_VER<1600) && !defined(__WINE__)
#include <BaseTsd.h>
typedef __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

/* 使用-DHTTP_PARTSER_STRICT=0进行编译以减少检查，但运行速度更快
 */
#ifndef HTTP_PARSER_STRICT
# define HTTP_PARSER_STRICT 1
#endif

enum http_parser_url_fields
  { UF_SCHEMA           = 0
  , UF_HOST             = 1
  , UF_PORT             = 2
  , UF_PATH             = 3
  , UF_QUERY            = 4
  , UF_FRAGMENT         = 5
  , UF_USERINFO         = 6
  , UF_MAX              = 7
  };


/* http_parser_parse_url（）的结果结构。
 *
 * 如果field_set设置了相关（1<<UF_）位，则调用方应使用UF_*值索引field_data[]。作为对客户端的礼貌（并且因为我们可能还剩下填充），我们将任何端口转换为uint16_t。
 */
struct http_parser_url {
  uint16_t field_set;           /* （1<<UF_*）值的位掩码*/
  uint16_t port;                /* 转换的UF_PORT字符串*/

  struct {
    uint16_t off;               /* 字段开始的缓冲区偏移量*/
    uint16_t len;               /* 磨合缓冲区长度*/
  } field_data[UF_MAX];
};

/* 将所有http_parser_url成员初始化为0*/
void http_parser_url_init(struct http_parser_url *u);

/* 解析URL；失败时返回非零*/
int http_parser_parse_url(const char *buf, size_t buflen,
                          int is_connect,
                          struct http_parser_url *u);
#ifdef __cplusplus
}
#endif
#endif

