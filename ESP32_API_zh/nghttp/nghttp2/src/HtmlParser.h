/*
 * nghttp2-HTTP/2 C库
 *
 * 版权所有（c）2012 Tatsuhiro Tsujikawa
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef HTML_PARSER_H
#define HTML_PARSER_H

#include "nghttp2_config.h"

#include <vector>
#include <string>

#ifdef HAVE_LIBXML2

#  include <libxml/HTMLparser.h>

#endif // HAVE_LIBXML2

namespace nghttp2 {

enum ResourceType {
  REQ_CSS = 1,
  REQ_JS,
  REQ_UNBLOCK_JS,
  REQ_IMG,
  REQ_OTHERS,
};

struct ParserData {
  std::string base_uri;
  std::vector<std::pair<std::string, ResourceType>> links;
  // >0，如果我们在“head”元素内。
  int inside_head;
  ParserData(const std::string &base_uri);
};

#ifdef HAVE_LIBXML2

class HtmlParser {
public:
  HtmlParser(const std::string &base_uri);
  ~HtmlParser();
  int parse_chunk(const char *chunk, size_t size, int fin);
  const std::vector<std::pair<std::string, ResourceType>> &get_links() const;
  void clear_links();

private:
  int parse_chunk_internal(const char *chunk, size_t size, int fin);

  std::string base_uri_;
  htmlParserCtxtPtr parser_ctx_;
  ParserData parser_data_;
};

#else // !HAVE_LIBXML2

class HtmlParser {
public:
  HtmlParser(const std::string &base_uri) {}
  int parse_chunk(const char *chunk, size_t size, int fin) { return 0; }
  const std::vector<std::pair<std::string, ResourceType>> &get_links() const {
    return links_;
  }
  void clear_links() {}

private:
  std::vector<std::pair<std::string, ResourceType>> links_;
};

#endif // !HAVE_LIBXML2

} // 命名空间nghttp2

#endif // HTML_PARSER_H

