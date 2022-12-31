/*
 * nghttp2-HTTP/2 C库
 *
 * 版权所有（c）2013 Tatsuhiro Tsujikawa
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef NGHTTP2_HD_HUFFMAN_H
#define NGHTTP2_HD_HUFFMAN_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif /* HAVE_CONFIG_H */

#include <nghttp2/nghttp2.h>

typedef enum {
  /* FSA接受这种状态作为霍夫曼编码序列的结束。*/
  NGHTTP2_HUFF_ACCEPTED = 1 << 14,
  /* 此状态发出符号*/
  NGHTTP2_HUFF_SYM = 1 << 15,
} nghttp2_huff_decode_flag;

typedef struct {
  /* fstate是当前huffman解码状态，它实际上是具有nghttp2_huff_decode_flag OR-ed的内部huffman树的节点ID。我们有257个叶节点，但它们与根节点相同，只是发出一个符号，因此我们有256个内部节点[1..255]，包括在内。节点ID 256是一个特殊的节点，它是一个表示解码失败的终端状态。*/
  uint16_t fstate;
  /* 如果NGHTTP2_HUFF_SYM标志已设置，则为符号*/
  uint8_t sym;
} nghttp2_huff_decode;

typedef nghttp2_huff_decode huff_decode_table_type[16];

typedef struct {
  /* fstate是当前huffman解码状态。*/
  uint16_t fstate;
} nghttp2_hd_huff_decode_context;

typedef struct {
  /* 此代码中的位数*/
  uint32_t nbits;
  /* 与LSB对齐的霍夫曼代码*/
  uint32_t code;
} nghttp2_huff_sym;

extern const nghttp2_huff_sym huff_sym_table[];
extern const nghttp2_huff_decode huff_decode_table[][16];

#endif /* NGHTTP2_HD_HUFFMAN_H */

