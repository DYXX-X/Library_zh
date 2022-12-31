/*
                            ____ __ ___ \\/__ __ __ | | _/_ \\/|'_ \/_ ` | __ | | __//\ | | _）|（_ | | | _ \ ___//\ \.__/\ __，_ | \ __ | | | | __ | XML解析器

   版权所有（c）1997-2000 Thai Open Source Software Center Ltd版权所有（c）2000 Clark Cooper<coopercc@users.sourceforge.net>版权所有（c）2002 Fred L.Drake，Jr<fdrake@users.sourceforge.net>版权所有（c）2002-2005 Karl Waclawek<karl@waclawek.net>版权所有（c）2016-2017 Sebastian Pipping<sebastian@pipping.org>版权所有（c）2017 Rhodori James<rhodri@wildebeest.org.uk>根据MIT许可证获得许可：

   特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：

   上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。

   THE  SOFTWARE  IS  PROVIDED  "AS  IS",  WITHOUT  WARRANTY  OF  ANY  KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef XmlTok_INCLUDED
#define XmlTok_INCLUDED 1

#ifdef __cplusplus
extern "C" {
#endif

/* XmlContentTok可以返回以下令牌*/
#define XML_TOK_TRAILING_RSQB                                                  \
  -5 /* ]或]]在扫描结束时；可能是\非法]]>序列的开始*/
/* XmlPrologTok和XmlContentTok都可以返回以下令牌。
*/
#define XML_TOK_NONE -4 /* 要扫描的字符串为空*/
#define XML_TOK_TRAILING_CR                                                    \
  -3                            /* 扫描结束时的CR；\可能是CRLF序列的一部分*/
#define XML_TOK_PARTIAL_CHAR -2 /* 多字节序列的一部分*/
#define XML_TOK_PARTIAL -1      /* 仅标记的一部分*/
#define XML_TOK_INVALID 0

/* XmlContentTok返回以下标记：；其中一些还由XmlAttributeValueTok、XmlEntityTok和XmlCdataSectionTok返回。
*/
#define XML_TOK_START_TAG_WITH_ATTS 1
#define XML_TOK_START_TAG_NO_ATTS 2
#define XML_TOK_EMPTY_ELEMENT_WITH_ATTS 3 /* 空元素标记<e/>*/
#define XML_TOK_EMPTY_ELEMENT_NO_ATTS 4
#define XML_TOK_END_TAG 5
#define XML_TOK_DATA_CHARS 6
#define XML_TOK_DATA_NEWLINE 7
#define XML_TOK_CDATA_SECT_OPEN 8
#define XML_TOK_ENTITY_REF 9
#define XML_TOK_CHAR_REF 10 /* 数字字符引用*/

/* XmlPrologTok和XmlContentTok都可以返回以下令牌。
*/
#define XML_TOK_PI 11       /* 处理指令*/
#define XML_TOK_XML_DECL 12 /* XML decl或文本decl*/
#define XML_TOK_COMMENT 13
#define XML_TOK_BOM 14 /* 字节顺序标记*/

/* 以下令牌仅由XmlPrologTok返回*/
#define XML_TOK_PROLOG_S 15
#define XML_TOK_DECL_OPEN 16  /* <!食品*/
#define XML_TOK_DECL_CLOSE 17 /* > */
#define XML_TOK_NAME 18
#define XML_TOK_NMTOKEN 19
#define XML_TOK_POUND_NAME 20 /* #名称*/
#define XML_TOK_OR 21         /* | */
#define XML_TOK_PERCENT 22
#define XML_TOK_OPEN_PAREN 23
#define XML_TOK_CLOSE_PAREN 24
#define XML_TOK_OPEN_BRACKET 25
#define XML_TOK_CLOSE_BRACKET 26
#define XML_TOK_LITERAL 27
#define XML_TOK_PARAM_ENTITY_REF 28
#define XML_TOK_INSTANCE_START 29

/* 以下内容仅出现在元素类型声明中*/
#define XML_TOK_NAME_QUESTION 30        /* 名称*/
#define XML_TOK_NAME_ASTERISK 31        /* 姓名**/
#define XML_TOK_NAME_PLUS 32            /* 名称+*/
#define XML_TOK_COND_SECT_OPEN 33       /* <![ */
#define XML_TOK_COND_SECT_CLOSE 34      /* ]]> */
#define XML_TOK_CLOSE_PAREN_QUESTION 35 /* )? */
#define XML_TOK_CLOSE_PAREN_ASTERISK 36 /* )* */
#define XML_TOK_CLOSE_PAREN_PLUS 37     /* )+ */
#define XML_TOK_COMMA 38

/* 以下令牌仅由XmlAttributeValueTok返回*/
#define XML_TOK_ATTRIBUTE_VALUE_S 39

/* 以下令牌仅由XmlCdataSectionTok返回*/
#define XML_TOK_CDATA_SECT_CLOSE 40

/* 在命名空间处理中，XmlPrologTok将返回带有冒号的名称。
*/
#define XML_TOK_PREFIXED_NAME 41

#ifdef XML_DTD
#  define XML_TOK_IGNORE_SECT 42
#endif /* XML_DTD */

#ifdef XML_DTD
#  define XML_N_STATES 4
#else /* 不是XML_DTD*/
#  define XML_N_STATES 3
#endif /* 不是XML_DTD*/

#define XML_PROLOG_STATE 0
#define XML_CONTENT_STATE 1
#define XML_CDATA_SECTION_STATE 2
#ifdef XML_DTD
#  define XML_IGNORE_SECTION_STATE 3
#endif /* XML_DTD */

#define XML_N_LITERAL_TYPES 2
#define XML_ATTRIBUTE_VALUE_LITERAL 0
#define XML_ENTITY_VALUE_LITERAL 1

/* 传递给XmlUtf8Encode的缓冲区大小必须至少为。*/
#define XML_UTF8_ENCODE_MAX 4
/* 传递给XmlUtf16Encode的缓冲区大小必须至少为。*/
#define XML_UTF16_ENCODE_MAX 2

typedef struct position {
  /* 第一行和第一列是0而不是1*/
  XML_Size lineNumber;
  XML_Size columnNumber;
} POSITION;

typedef struct {
  const char *name;
  const char *valuePtr;
  const char *valueEnd;
  char normalized;
} ATTRIBUTE;

struct encoding;
typedef struct encoding ENCODING;

typedef int(PTRCALL *SCANNER)(const ENCODING *, const char *, const char *,
                              const char **);

enum XML_Convert_Result {
  XML_CONVERT_COMPLETED = 0,
  XML_CONVERT_INPUT_INCOMPLETE = 1,
  XML_CONVERT_OUTPUT_EXHAUSTED
  = 2 /* 因此潜在的剩余输入*/
};

struct encoding {
  SCANNER scanners[XML_N_STATES];
  SCANNER literalScanners[XML_N_LITERAL_TYPES];
  int(PTRCALL *nameMatchesAscii)(const ENCODING *, const char *, const char *,
                                 const char *);
  int(PTRFASTCALL *nameLength)(const ENCODING *, const char *);
  const char *(PTRFASTCALL *skipS)(const ENCODING *, const char *);
  int(PTRCALL *getAtts)(const ENCODING *enc, const char *ptr, int attsMax,
                        ATTRIBUTE *atts);
  int(PTRFASTCALL *charRefNumber)(const ENCODING *enc, const char *ptr);
  int(PTRCALL *predefinedEntityName)(const ENCODING *, const char *,
                                     const char *);
  void(PTRCALL *updatePosition)(const ENCODING *, const char *ptr,
                                const char *end, POSITION *);
  int(PTRCALL *isPublicId)(const ENCODING *enc, const char *ptr,
                           const char *end, const char **badPtr);
  enum XML_Convert_Result(PTRCALL *utf8Convert)(const ENCODING *enc,
                                                const char **fromP,
                                                const char *fromLim, char **toP,
                                                const char *toLim);
  enum XML_Convert_Result(PTRCALL *utf16Convert)(const ENCODING *enc,
                                                 const char **fromP,
                                                 const char *fromLim,
                                                 unsigned short **toP,
                                                 const unsigned short *toLim);
  int minBytesPerChar;
  char isUtf8;
  char isUtf16;
};

/* 扫描从ptr开始的字符串，直到下一个完整令牌结束，但不要扫描超过eptr。返回给定令牌类型的整数。

   ptr==eptr时返回XML_TOK_NONE；不会设置nextTokPtr。

   当字符串不包含完整令牌时，返回XML_TOK_PARTIAL；不会设置nextTokPtr。

   当字符串未启动有效令牌时，返回XML_TOK_INVALID；nextTokPtr将被设置为指向使令牌无效的字符。

   否则，字符串以有效令牌开头；nextTokPtr将被设置为指向该令牌末尾的字符。

   每个数据字符算作一个令牌，但相邻的数据字符可以一起返回。类似地，对于文本、注释和处理指令之外的序言中的字符。
*/

#define XmlTok(enc, state, ptr, end, nextTokPtr)                               \
  (((enc)->scanners[state])(enc, ptr, end, nextTokPtr))

#define XmlPrologTok(enc, ptr, end, nextTokPtr)                                \
  XmlTok(enc, XML_PROLOG_STATE, ptr, end, nextTokPtr)

#define XmlContentTok(enc, ptr, end, nextTokPtr)                               \
  XmlTok(enc, XML_CONTENT_STATE, ptr, end, nextTokPtr)

#define XmlCdataSectionTok(enc, ptr, end, nextTokPtr)                          \
  XmlTok(enc, XML_CDATA_SECTION_STATE, ptr, end, nextTokPtr)

#ifdef XML_DTD

#  define XmlIgnoreSectionTok(enc, ptr, end, nextTokPtr)                       \
    XmlTok(enc, XML_IGNORE_SECTION_STATE, ptr, end, nextTokPtr)

#endif /* XML_DTD */

/* 这用于对XmlTok已返回的文本内容执行第二级标记化。
*/
#define XmlLiteralTok(enc, literalType, ptr, end, nextTokPtr)                  \
  (((enc)->literalScanners[literalType])(enc, ptr, end, nextTokPtr))

#define XmlAttributeValueTok(enc, ptr, end, nextTokPtr)                        \
  XmlLiteralTok(enc, XML_ATTRIBUTE_VALUE_LITERAL, ptr, end, nextTokPtr)

#define XmlEntityValueTok(enc, ptr, end, nextTokPtr)                           \
  XmlLiteralTok(enc, XML_ENTITY_VALUE_LITERAL, ptr, end, nextTokPtr)

#define XmlNameMatchesAscii(enc, ptr1, end1, ptr2)                             \
  (((enc)->nameMatchesAscii)(enc, ptr1, end1, ptr2))

#define XmlNameLength(enc, ptr) (((enc)->nameLength)(enc, ptr))

#define XmlSkipS(enc, ptr) (((enc)->skipS)(enc, ptr))

#define XmlGetAttributes(enc, ptr, attsMax, atts)                              \
  (((enc)->getAtts)(enc, ptr, attsMax, atts))

#define XmlCharRefNumber(enc, ptr) (((enc)->charRefNumber)(enc, ptr))

#define XmlPredefinedEntityName(enc, ptr, end)                                 \
  (((enc)->predefinedEntityName)(enc, ptr, end))

#define XmlUpdatePosition(enc, ptr, end, pos)                                  \
  (((enc)->updatePosition)(enc, ptr, end, pos))

#define XmlIsPublicId(enc, ptr, end, badPtr)                                   \
  (((enc)->isPublicId)(enc, ptr, end, badPtr))

#define XmlUtf8Convert(enc, fromP, fromLim, toP, toLim)                        \
  (((enc)->utf8Convert)(enc, fromP, fromLim, toP, toLim))

#define XmlUtf16Convert(enc, fromP, fromLim, toP, toLim)                       \
  (((enc)->utf16Convert)(enc, fromP, fromLim, toP, toLim))

typedef struct {
  ENCODING initEnc;
  const ENCODING **encPtr;
} INIT_ENCODING;

int XmlParseXmlDecl(int isGeneralTextEntity, const ENCODING *enc,
                    const char *ptr, const char *end, const char **badPtr,
                    const char **versionPtr, const char **versionEndPtr,
                    const char **encodingNamePtr,
                    const ENCODING **namedEncodingPtr, int *standalonePtr);

int XmlInitEncoding(INIT_ENCODING *, const ENCODING **, const char *name);
const ENCODING *XmlGetUtf8InternalEncoding(void);
const ENCODING *XmlGetUtf16InternalEncoding(void);
int FASTCALL XmlUtf8Encode(int charNumber, char *buf);
int FASTCALL XmlUtf16Encode(int charNumber, unsigned short *buf);
int XmlSizeOfUnknownEncoding(void);

typedef int(XMLCALL *CONVERTER)(void *userData, const char *p);

ENCODING *XmlInitUnknownEncoding(void *mem, int *table, CONVERTER convert,
                                 void *userData);

int XmlParseXmlDeclNS(int isGeneralTextEntity, const ENCODING *enc,
                      const char *ptr, const char *end, const char **badPtr,
                      const char **versionPtr, const char **versionEndPtr,
                      const char **encodingNamePtr,
                      const ENCODING **namedEncodingPtr, int *standalonePtr);

int XmlInitEncodingNS(INIT_ENCODING *, const ENCODING **, const char *name);
const ENCODING *XmlGetUtf8InternalEncodingNS(void);
const ENCODING *XmlGetUtf16InternalEncodingNS(void);
ENCODING *XmlInitUnknownEncodingNS(void *mem, int *table, CONVERTER convert,
                                   void *userData);
#ifdef __cplusplus
}
#endif

#endif /* 不是XmlTok_INCLUDED*/

