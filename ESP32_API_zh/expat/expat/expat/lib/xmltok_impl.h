/*
                            ____ __ ___ \\/__ __ __ | | _/_ \\/|'_ \/_ ` | __ | | __//\ | | _）|（_ | | | _ \ ___//\ \.__/\ __，_ | \ __ | | | | __ | XML解析器

   版权所有（c）1997-2000 Thai Open Source Software Center Ltd版权所有（c）2000 Clark Cooper<coopercc@users.sourceforge.net>版权所有（c）2017-2019 Sebastian Pipping<sebastian@pipping.org>根据MIT许可证获得许可：

   特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：

   上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。

   THE  SOFTWARE  IS  PROVIDED  "AS  IS",  WITHOUT  WARRANTY  OF  ANY  KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

enum {
  BT_NONXML,   /* e、 g.非字符FFFF*/
  BT_MALFORM,  /* 非法，关于编码*/
  BT_LT,       /* 小于=“<”*/
  BT_AMP,      /* 安培数=“&”*/
  BT_RSQB,     /* 右方括号=“[”*/
  BT_LEAD2,    /* 2字节UTF-8字符的前导字节*/
  BT_LEAD3,    /* 3字节UTF-8字符的前导字节*/
  BT_LEAD4,    /* 4字节UTF-8字符的前导字节*/
  BT_TRAIL,    /* 例如4字节字符的第二个16位单元。*/
  BT_CR,       /* 回车符=“\r”*/
  BT_LF,       /* 换行符=“\n”*/
  BT_GT,       /* 大于=“>”*/
  BT_QUOT,     /* 引号character=“\”“*/
  BT_APOS,     /* apothrophe=“'”*/
  BT_EQUALS,   /* 等号=“=”*/
  BT_QUEST,    /* 问号=“？”*/
  BT_EXCL,     /* 感叹号=“！”*/
  BT_SOL,      /* solidus，斜线=“/”*/
  BT_SEMI,     /* 分号=“；”*/
  BT_NUM,      /* 数字符号=“#”*/
  BT_LSQB,     /* 左方括号=“[”*/
  BT_S,        /* 空白，例如“\t”，“[，”\r“]*/
  BT_NMSTRT,   /* 非十六进制名称起始字母=“G”..“Z”+“G”..“Z”+“_”*/
  BT_COLON,    /* 冒号=“：”*/
  BT_HEX,      /* 十六进制字母=“A”..“F”+“A”..“F”*/
  BT_DIGIT,    /* digit=“0”..“9”*/
  BT_NAME,     /* 点和中间点=“.”+chr（0xb7）*/
  BT_MINUS,    /* 减=“-”*/
  BT_OTHER,    /* 已知不是名称或名称开头字符*/
  BT_NONASCII, /* 可能是名称或名称开头字符*/
  BT_PERCNT,   /* 百分号=“%”*/
  BT_LPAR,     /* 左括号=“（”*/
  BT_RPAR,     /* 右括号=“（”*/
  BT_AST,      /* 星号=“*”*/
  BT_PLUS,     /* 加号=“+”*/
  BT_COMMA,    /* 逗号=“，”*/
  BT_VERBAR    /* 竖条=“|”*/
};

#include <stddef.h>

