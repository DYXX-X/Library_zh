/*
                            ____ __ ___ \\/__ __ __ | | _/_ \\/|'_ \/_ ` | __ | | __//\ | | _）|（_ | | | _ \ ___//\ \.__/\ __，_ | \ __ | | | | __ | XML解析器

   版权所有（c）1997-2000 Thai Open Source Software Center Ltd版权所有（c）2000 Clark Cooper<coopercc@users.sourceforge.net>版权所有（c）2000-2005 Fred L.Drake，Jr<fdrake@users.sourceforge.net>版权所有（c）2001-2002 Greg Stein<gstein@users.sourceforge.net>版权所有（c）2002-2016 Karl Waclawek<karl@waclawek.net>版权所有（c）2016-2022 Sebastian Pipping<sebastian@pipping.org>版权所有（c）2016 Cristian Rodríguez<crrodriguez@opensuse.org>版权所有（c）2016 Thomas Beutlich<tc@tbeu.de>版权所有（c）2017 Rhodori James<rhodri@wildebeest.org.uk>根据MIT许可证获得许可：

   特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：

   上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。

   THE  SOFTWARE  IS  PROVIDED  "AS  IS",  WITHOUT  WARRANTY  OF  ANY  KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef Expat_INCLUDED
#define Expat_INCLUDED 1

#include <stdlib.h>
#include "expat_external.h"

#ifdef __cplusplus
extern "C" {
#endif

struct XML_ParserStruct;
typedef struct XML_ParserStruct *XML_Parser;

typedef unsigned char XML_Bool;
#define XML_TRUE ((XML_Bool)1)
#define XML_FALSE ((XML_Bool)0)

/* XML_Status枚举提供了几个API函数的可能返回值。预处理器#defines包含在内，因此可以将此节添加到仍然需要支持旧版本Expat 1.95.x的代码中：

   #ifndef XML_STATUS_OK#define XML_STATUS _OK 1#define XML _STATUS_ERROR 0#endif

   否则，#define hackery非常难看，可能会被删除。
*/
enum XML_Status {
  XML_STATUS_ERROR = 0,
#define XML_STATUS_ERROR XML_STATUS_ERROR
  XML_STATUS_OK = 1,
#define XML_STATUS_OK XML_STATUS_OK
  XML_STATUS_SUSPENDED = 2
#define XML_STATUS_SUSPENDED XML_STATUS_SUSPENDED
};

enum XML_Error {
  XML_ERROR_NONE,
  XML_ERROR_NO_MEMORY,
  XML_ERROR_SYNTAX,
  XML_ERROR_NO_ELEMENTS,
  XML_ERROR_INVALID_TOKEN,
  XML_ERROR_UNCLOSED_TOKEN,
  XML_ERROR_PARTIAL_CHAR,
  XML_ERROR_TAG_MISMATCH,
  XML_ERROR_DUPLICATE_ATTRIBUTE,
  XML_ERROR_JUNK_AFTER_DOC_ELEMENT,
  XML_ERROR_PARAM_ENTITY_REF,
  XML_ERROR_UNDEFINED_ENTITY,
  XML_ERROR_RECURSIVE_ENTITY_REF,
  XML_ERROR_ASYNC_ENTITY,
  XML_ERROR_BAD_CHAR_REF,
  XML_ERROR_BINARY_ENTITY_REF,
  XML_ERROR_ATTRIBUTE_EXTERNAL_ENTITY_REF,
  XML_ERROR_MISPLACED_XML_PI,
  XML_ERROR_UNKNOWN_ENCODING,
  XML_ERROR_INCORRECT_ENCODING,
  XML_ERROR_UNCLOSED_CDATA_SECTION,
  XML_ERROR_EXTERNAL_ENTITY_HANDLING,
  XML_ERROR_NOT_STANDALONE,
  XML_ERROR_UNEXPECTED_STATE,
  XML_ERROR_ENTITY_DECLARED_IN_PE,
  XML_ERROR_FEATURE_REQUIRES_XML_DTD,
  XML_ERROR_CANT_CHANGE_FEATURE_ONCE_PARSING,
  /* 在1.95.7中添加。*/
  XML_ERROR_UNBOUND_PREFIX,
  /* 在1.95.8中添加。*/
  XML_ERROR_UNDECLARING_PREFIX,
  XML_ERROR_INCOMPLETE_PE,
  XML_ERROR_XML_DECL,
  XML_ERROR_TEXT_DECL,
  XML_ERROR_PUBLICID,
  XML_ERROR_SUSPENDED,
  XML_ERROR_NOT_SUSPENDED,
  XML_ERROR_ABORTED,
  XML_ERROR_FINISHED,
  XML_ERROR_SUSPEND_PE,
  /* 在2.0中添加。*/
  XML_ERROR_RESERVED_PREFIX_XML,
  XML_ERROR_RESERVED_PREFIX_XMLNS,
  XML_ERROR_RESERVED_NAMESPACE_URI,
  /* 增加2.2.1。*/
  XML_ERROR_INVALID_ARGUMENT,
  /* 在2.3.0中添加。*/
  XML_ERROR_NO_BUFFER,
  /* 在2.4.0中添加。*/
  XML_ERROR_AMPLIFICATION_LIMIT_BREACH
};

enum XML_Content_Type {
  XML_CTYPE_EMPTY = 1,
  XML_CTYPE_ANY,
  XML_CTYPE_MIXED,
  XML_CTYPE_NAME,
  XML_CTYPE_CHOICE,
  XML_CTYPE_SEQ
};

enum XML_Content_Quant {
  XML_CQUANT_NONE,
  XML_CQUANT_OPT,
  XML_CQUANT_REP,
  XML_CQUANT_PLUS
};

/* 如果类型==XML_CTYPE_EMPTY或XML_CTYPE-ANY，则量程将为XML_CQUANT_NONE，其他字段将为零或NULL。如果type==XML_CTYPE_MIXED，则quant将为NONE或REP，numchildren将包含可以混合的元素数，并且children指向XML_Content单元格数组，这些单元格将全部为XML_CTYPE_NAME类型，没有量化。

   如果type==XML_CTYPE_NAME，则名称指向名称，numchildren字段将为零，children字段为NULL。quant字段指示放置在名称上的任何量词。

   CHOICE和SEQ的名称为NULL，numchildren中的子级数和子级数将递归地指向XML_Content单元格数组。

   EMPTY、ANY和MIXED类型仅出现在顶层。
*/

typedef struct XML_cp XML_Content;

struct XML_cp {
  enum XML_Content_Type type;
  enum XML_Content_Quant quant;
  XML_Char *name;
  unsigned int numchildren;
  XML_Content *children;
};

/* 这是为元素声明调用的。有关模型参数的描述，请参见上文。完成模型后，调用方有责任释放模型。
*/
typedef void(XMLCALL *XML_ElementDeclHandler)(void *userData,
                                              const XML_Char *name,
                                              XML_Content *model);

XMLPARSEAPI(void)
XML_SetElementDeclHandler(XML_Parser parser, XML_ElementDeclHandler eldecl);

/* 为*each*属性调用Attlist声明处理程序。因此，一个声明了多个属性的Attlist声明将生成对该处理程序的多个调用。在“#IMPLIED”或“#REQUIRED”关键字的情况下，“默认”参数可能为NULL。在“#REQUIRED”的情况下，“isrequired”参数将为true，默认值为NULL。如果“isrequired”为true，默认值为非NULL，则这是“#FIXED”默认值。
*/
typedef void(XMLCALL *XML_AttlistDeclHandler)(
    void *userData, const XML_Char *elname, const XML_Char *attname,
    const XML_Char *att_type, const XML_Char *dflt, int isrequired);

XMLPARSEAPI(void)
XML_SetAttlistDeclHandler(XML_Parser parser, XML_AttlistDeclHandler attdecl);

/* XML声明处理程序用于*同时*XML声明和文本声明。区分的方法是文本声明的版本参数将为NULL。对于XML声明，编码参数可以为NULL。独立参数将为-1、0或1，分别表示声明中没有独立参数、该参数为no或yes。
*/
typedef void(XMLCALL *XML_XmlDeclHandler)(void *userData,
                                          const XML_Char *version,
                                          const XML_Char *encoding,
                                          int standalone);

XMLPARSEAPI(void)
XML_SetXmlDeclHandler(XML_Parser parser, XML_XmlDeclHandler xmldecl);

typedef struct {
  void *(*malloc_fcn)(size_t size);
  void *(*realloc_fcn)(void *ptr, size_t size);
  void (*free_fcn)(void *ptr);
} XML_Memory_Handling_Suite;

/* 构造一个新的解析器；encoding是外部协议指定的编码，如果没有指定，则为NULL。
*/
XMLPARSEAPI(XML_Parser)
XML_ParserCreate(const XML_Char *encoding);

/* 构造一个新的解析器和命名空间处理器。将扩展属于命名空间的元素类型名称和属性名称；从不展开非固定属性名称；只有在存在默认命名空间时，才会展开非固定元素类型名称。扩展的名称是名称空间URI、名称空间分隔符和名称的本地部分的串联。如果命名空间分隔符为“\0”，则命名空间URI和本地部分将在没有任何分隔符的情况下连接。将分隔符“\0”与命名空间三元组一起使用是一个编程错误（请参阅XML_SetReturnNSTriplet）。
*/
XMLPARSEAPI(XML_Parser)
XML_ParserCreateNS(const XML_Char *encoding, XML_Char namespaceSeparator);

/* 使用memsuite引用的内存管理套件构造一个新的解析器。如果memsuite为NULL，则使用标准库内存套件。如果namespaceSeparator为非NULL，它将创建一个具有如上所述的命名空间处理的解析器。指向的字符将用作命名空间分隔符。

   用于创建的解析器的所有其他内存操作将来自给定的套件。
*/
XMLPARSEAPI(XML_Parser)
XML_ParserCreate_MM(const XML_Char *encoding,
                    const XML_Memory_Handling_Suite *memsuite,
                    const XML_Char *namespaceSeparator);

/* 准备要重用的解析器对象。当内存分配开销过高时，例如当需要解析大量小文档时，这一点尤为重要。除未知的EncodingHandler外，所有处理程序都将从解析器中清除。解析器的外部状态被重新初始化，ns和ns_triples的值除外。

   在扩展1.95.3中添加。
*/
XMLPARSEAPI(XML_Bool)
XML_ParserReset(XML_Parser parser, const XML_Char *encoding);

/* atts是名称/值对的数组，以0结尾；名称和值以0结尾。
*/
typedef void(XMLCALL *XML_StartElementHandler)(void *userData,
                                               const XML_Char *name,
                                               const XML_Char **atts);

typedef void(XMLCALL *XML_EndElementHandler)(void *userData,
                                             const XML_Char *name);

/* s不是0终止的。*/
typedef void(XMLCALL *XML_CharacterDataHandler)(void *userData,
                                                const XML_Char *s, int len);

/* 目标和数据已0终止*/
typedef void(XMLCALL *XML_ProcessingInstructionHandler)(void *userData,
                                                        const XML_Char *target,
                                                        const XML_Char *data);

/* 数据已0终止*/
typedef void(XMLCALL *XML_CommentHandler)(void *userData, const XML_Char *data);

typedef void(XMLCALL *XML_StartCdataSectionHandler)(void *userData);
typedef void(XMLCALL *XML_EndCdataSectionHandler)(void *userData);

/* 对于XML文档中没有适用处理程序的任何字符，都会调用此函数。这包括作为标记的一部分而未报告的字符（注释、标记声明），或作为构造的一部分但未提供处理程序的字符。这些字符的传递方式与XML文档中的完全相同，只是它们将以UTF-8或UTF-16编码。注意，字节顺序标记字符不会传递给默认处理程序。对于如何在对默认处理程序的调用之间划分字符没有任何保证：例如，注释可能会在多个调用之间拆分。
*/
typedef void(XMLCALL *XML_DefaultHandler)(void *userData, const XML_Char *s,
                                          int len);

/* 在解析任何DTD或内部子集之前，这将在DOCTYPE声明的开始时调用。
*/
typedef void(XMLCALL *XML_StartDoctypeDeclHandler)(void *userData,
                                                   const XML_Char *doctypeName,
                                                   const XML_Char *sysid,
                                                   const XML_Char *pubid,
                                                   int has_internal_subset);

/* 当遇到关闭>时，但在处理任何外部子集之后，这将在DOCTYPE声明的开始时调用。
*/
typedef void(XMLCALL *XML_EndDoctypeDeclHandler)(void *userData);

/* 这是实体声明的调用。如果实体是参数实体，则is_parameter_entity参数将为非零，否则为零。

   对于内部实体（<！ENTITY foo“bar”>），值将为非NULL，systemId、publicID和notationName将为NULL。值字符串不是以空结尾的；长度在value_length参数中提供。由于长度值为零是合法的，因此不要使用此参数来测试内部实体。

   对于外部实体，值将为NULL，systemId将为非NULL。除非提供了公共标识符，否则publicId参数将为NULL。notationName参数仅对未分析的实体声明具有非NULL值。

   注意，is_parameter_entity不能更改为XML_Bool，因为这会破坏二进制兼容性。
*/
typedef void(XMLCALL *XML_EntityDeclHandler)(
    void *userData, const XML_Char *entityName, int is_parameter_entity,
    const XML_Char *value, int value_length, const XML_Char *base,
    const XML_Char *systemId, const XML_Char *publicId,
    const XML_Char *notationName);

XMLPARSEAPI(void)
XML_SetEntityDeclHandler(XML_Parser parser, XML_EntityDeclHandler handler);

/* OBSOLETE--OBOLETE--已废弃此处理程序已被上面的EntityDeclHandler取代。这里提供它是为了向后兼容。

   这是对未分析（NDATA）实体的声明所调用的。基参数是XML_SetBase设置的任何参数。entityName、systemId和notationName参数永远不会为NULL。其他论点可能是。
*/
typedef void(XMLCALL *XML_UnparsedEntityDeclHandler)(
    void *userData, const XML_Char *entityName, const XML_Char *base,
    const XML_Char *systemId, const XML_Char *publicId,
    const XML_Char *notationName);

/* 这被称为符号声明。基参数是XML_SetBase设置的任何参数。符号Name永远不会为空。其他参数可以是。
*/
typedef void(XMLCALL *XML_NotationDeclHandler)(void *userData,
                                               const XML_Char *notationName,
                                               const XML_Char *base,
                                               const XML_Char *systemId,
                                               const XML_Char *publicId);

/* 启用命名空间处理后，对每个命名空间声明调用一次。对start和end元素处理程序的调用发生在对start和end命名空间声明处理程序的呼叫之间。对于xmlns属性，前缀将为NULL。对于xmlns=“”属性，uri将为NULL。
*/
typedef void(XMLCALL *XML_StartNamespaceDeclHandler)(void *userData,
                                                     const XML_Char *prefix,
                                                     const XML_Char *uri);

typedef void(XMLCALL *XML_EndNamespaceDeclHandler)(void *userData,
                                                   const XML_Char *prefix);

/* 如果文档不是独立的，即它有一个外部子集或对参数实体的引用，但没有standalone=“yes”，则调用此选项。如果此处理程序返回XML_STATUS_ERROR，则处理将不会继续，解析器将返回XML_ERROR_not_STANDALONE错误。如果启用了参数实体解析，那么除了上面的条件之外，只有在实际读取了被引用的实体时才会调用此处理程序。
*/
typedef int(XMLCALL *XML_NotStandaloneHandler)(void *userData);

/* 这是为引用外部解析的通用实体而调用的。未自动分析引用的实体。应用程序可以立即或稍后使用XML_ExternalEntityParserCreate解析它。

   解析器参数是解析包含引用的实体的解析器；它可以作为解析器参数传递给XML_ExternalEntityParserCreate。systemId参数是实体声明中指定的系统标识符；它将不为NULL。

   基参数是系统标识符，如果systemId是相对的，则应将其用作解析systemId的基；这由XML_SetBase设置；它可以是NULL。

   publicId参数是实体声明中指定的公共标识符，如果未指定，则为NULL；公共标识符中的空白将按照XML规范的要求进行规范化。

   context参数以XML_ExternalEntityParserCreate的context参数所期望的格式指定解析上下文；上下文只有在处理程序返回之前才有效，所以如果稍后要解析被引用的实体，则必须复制它。只有当实体是参数实体时，上下文才为NULL。

   如果由于处理外部实体时出现致命错误而不应继续处理，则处理程序应返回XML_STATUS_ERROR。在这种情况下，调用解析器将返回XML_ERROR_EXTERNAL_ENTITY_HANDLING错误。

   注意，与其他处理程序不同，第一个参数是解析器，而不是userData。
*/
typedef int(XMLCALL *XML_ExternalEntityRefHandler)(XML_Parser parser,
                                                   const XML_Char *context,
                                                   const XML_Char *base,
                                                   const XML_Char *systemId,
                                                   const XML_Char *publicId);

/* 这在两种情况下调用：1）遇到未读取声明的实体引用，这不是错误。2） 读取内部实体引用，但未展开，因为已调用XML_SetDefaultHandler。注意：无法报告声明中跳过的参数实体和属性值中跳过的常规实体，因为事件将与声明或属性值的报告不同步
*/
typedef void(XMLCALL *XML_SkippedEntityHandler)(void *userData,
                                                const XML_Char *entityName,
                                                int is_parameter_entity);

/* 该结构由XML_UnknownEncodingHandler填充，以向解析器提供关于解析器未知的编码的信息。

   map[b]成员提供关于第一个字节为b的字节序列的信息。

   如果map[b]是c，其中c>=0，则b本身编码Unicode标量值c。

   如果map[b]为-1，则字节序列格式不正确。

   如果map[b]是-n，其中n>=2，那么b是编码单个Unicode标量值的n字节序列的第一个字节。

   数据成员将作为第一个参数传递给convert函数。

   转换函数用于转换多字节序列；s将指向一个n字节序列，其中map[（unsigned char）s]==-n。convert函数必须返回此字节序列表示的Unicode标量值，如果字节序列格式不正确，则返回-1。

   如果编码是单字节编码，即map[b]>=-1（对于所有字节b），则转换函数可能为NULL。

   当解析器完成编码后，如果release不为NULL，它将调用release，并将其传递给数据成员；一旦调用了release，就不会再次调用convert函数。

   Expat对使用此机制支持的编码设置了某些限制。

   1.格式良好的XML文档中可以出现的每个ASCII字符，但字符除外

      $@\^`{}~

      必须由单个字节表示，并且该字节必须与ASCII中表示该字符的字节相同。

   2.任何字符都不需要超过4个字节来编码。

   3.所有编码的字符必须具有Unicode标量值<=0xFFFF（即，不允许使用UTF-16中的替代字符编码的字符）。注意，此限制不适用于UTF-8和UTF-16的内置支持。

   4.Unicode字符不能由多个不同的字节序列编码。
*/
typedef struct {
  int map[256];
  void *data;
  int(XMLCALL *convert)(void *data, const char *s);
  void(XMLCALL *release)(void *data);
} XML_Encoding;

/* 这是为解析器未知的编码调用的。

   encodingHandlerData参数是作为第二个参数传递给XML_SetUnknownEncodingHandler的参数。

   name参数提供编码声明中指定的编码名称。

   如果回调可以提供有关编码的信息，它必须填写XML_encoding结构，并返回XML_STATUS_OK。否则它必须返回XML_STATUS_ERROR。

   如果信息没有描述合适的编码，那么解析器将返回XML_ERROR_UNKNOWN_encoding错误。
*/
typedef int(XMLCALL *XML_UnknownEncodingHandler)(void *encodingHandlerData,
                                                 const XML_Char *name,
                                                 XML_Encoding *info);

XMLPARSEAPI(void)
XML_SetElementHandler(XML_Parser parser, XML_StartElementHandler start,
                      XML_EndElementHandler end);

XMLPARSEAPI(void)
XML_SetStartElementHandler(XML_Parser parser, XML_StartElementHandler handler);

XMLPARSEAPI(void)
XML_SetEndElementHandler(XML_Parser parser, XML_EndElementHandler handler);

XMLPARSEAPI(void)
XML_SetCharacterDataHandler(XML_Parser parser,
                            XML_CharacterDataHandler handler);

XMLPARSEAPI(void)
XML_SetProcessingInstructionHandler(XML_Parser parser,
                                    XML_ProcessingInstructionHandler handler);
XMLPARSEAPI(void)
XML_SetCommentHandler(XML_Parser parser, XML_CommentHandler handler);

XMLPARSEAPI(void)
XML_SetCdataSectionHandler(XML_Parser parser,
                           XML_StartCdataSectionHandler start,
                           XML_EndCdataSectionHandler end);

XMLPARSEAPI(void)
XML_SetStartCdataSectionHandler(XML_Parser parser,
                                XML_StartCdataSectionHandler start);

XMLPARSEAPI(void)
XML_SetEndCdataSectionHandler(XML_Parser parser,
                              XML_EndCdataSectionHandler end);

/* 这将设置默认处理程序，并禁止内部实体的扩展。这些实体引用将传递给默认处理程序，如果设置了实体处理程序，则传递给跳过的实体处理程序。
*/
XMLPARSEAPI(void)
XML_SetDefaultHandler(XML_Parser parser, XML_DefaultHandler handler);

/* 这将设置默认处理程序，但不会禁止内部实体的扩展。实体引用将不会传递给默认处理程序。
*/
XMLPARSEAPI(void)
XML_SetDefaultHandlerExpand(XML_Parser parser, XML_DefaultHandler handler);

XMLPARSEAPI(void)
XML_SetDoctypeDeclHandler(XML_Parser parser, XML_StartDoctypeDeclHandler start,
                          XML_EndDoctypeDeclHandler end);

XMLPARSEAPI(void)
XML_SetStartDoctypeDeclHandler(XML_Parser parser,
                               XML_StartDoctypeDeclHandler start);

XMLPARSEAPI(void)
XML_SetEndDoctypeDeclHandler(XML_Parser parser, XML_EndDoctypeDeclHandler end);

XMLPARSEAPI(void)
XML_SetUnparsedEntityDeclHandler(XML_Parser parser,
                                 XML_UnparsedEntityDeclHandler handler);

XMLPARSEAPI(void)
XML_SetNotationDeclHandler(XML_Parser parser, XML_NotationDeclHandler handler);

XMLPARSEAPI(void)
XML_SetNamespaceDeclHandler(XML_Parser parser,
                            XML_StartNamespaceDeclHandler start,
                            XML_EndNamespaceDeclHandler end);

XMLPARSEAPI(void)
XML_SetStartNamespaceDeclHandler(XML_Parser parser,
                                 XML_StartNamespaceDeclHandler start);

XMLPARSEAPI(void)
XML_SetEndNamespaceDeclHandler(XML_Parser parser,
                               XML_EndNamespaceDeclHandler end);

XMLPARSEAPI(void)
XML_SetNotStandaloneHandler(XML_Parser parser,
                            XML_NotStandaloneHandler handler);

XMLPARSEAPI(void)
XML_SetExternalEntityRefHandler(XML_Parser parser,
                                XML_ExternalEntityRefHandler handler);

/* 如果在这里为arg指定了非NULL值，那么它将作为第一个参数传递给外部实体ref处理程序，而不是解析器对象。
*/
XMLPARSEAPI(void)
XML_SetExternalEntityRefHandlerArg(XML_Parser parser, void *arg);

XMLPARSEAPI(void)
XML_SetSkippedEntityHandler(XML_Parser parser,
                            XML_SkippedEntityHandler handler);

XMLPARSEAPI(void)
XML_SetUnknownEncodingHandler(XML_Parser parser,
                              XML_UnknownEncodingHandler handler,
                              void *encodingHandlerData);

/* 这可以在开始元素、结束元素、处理指令或字符数据的处理程序中调用。它会将相应的标记传递给默认处理程序。
*/
XMLPARSEAPI(void)
XML_DefaultCurrent(XML_Parser parser);

/* 如果do_nst为非零，并且名称空间处理有效，并且名称具有前缀（即显式名称空间限定符），则该名称将作为单个字符串中的三元组返回，该字符串由创建解析器时指定的分隔符分隔：URI+sep+local_name+sep+prefix。

   如果do_nst为零，则无论名称是否具有前缀，都将以默认方式（URI+sep+local_name）返回名称空间信息。

   注意：在XML_Parse或XML_ParseBuffer之后调用XML_SetReturnNSTriplet无效。
*/

XMLPARSEAPI(void)
XML_SetReturnNSTriplet(XML_Parser parser, int do_nst);

/* 此值作为userData参数传递给回调。*/
XMLPARSEAPI(void)
XML_SetUserData(XML_Parser parser, void *userData);

/* 返回XML_SetUserData或NULL设置的最后一个值。*/
#define XML_GetUserData(parser) (*(void **)(parser))

/* 这相当于向XML_ParserCreate提供编码参数。成功时，XML_SetEncoding返回非零，否则返回零。注意：在XML_Parse或XML_ParseBuffer之后调用XML_SetEncoding无效，并返回XML_STATUS_ERROR。
*/
XMLPARSEAPI(enum XML_Status)
XML_SetEncoding(XML_Parser parser, const XML_Char *encoding);

/* 如果调用此函数，则解析器将作为第一个参数传递给回调，而不是userData。用户数据仍然可以使用XML_GetUserData访问。
*/
XMLPARSEAPI(void)
XML_UseParserAsHandlerArg(XML_Parser parser);

/* 如果将useDTD==XML_TRUE传递给此函数，则解析器将假设存在外部子集，即使文档中未指定任何子集。在这种情况下，解析器将调用systemId参数值为NULL的externalEntityRefHandler（publicId和context参数也将为NULL）。注意：为了检查WFC:EntityDeclared，传递useDTD==XML_TRUE将使解析器的行为如同文档具有带有外部子集的DTD一样。注意：如果调用了此函数，则必须在第一次调用XML_Parse或XML_ParseBuffer之前执行此操作，因为在这之后它将不起作用。返回XML_ERROR_CANT_CHANGE_FEATURE_ONCE_PARSING。注意：如果文档根本没有DOCTYPE声明，则不会调用startDoctypeDeclHandler和endDoctypeDecalHandler，尽管正在解析外部子集。注意：如果编译Expat时未定义XML_DTD，则返回XML_ERROR_FEATURE_REQUIRES_XML_DTD。注意：如果解析器==NULL，则返回XML_ERROR_INVALID_ARGUMENT。
*/
XMLPARSEAPI(enum XML_Error)
XML_UseForeignDTD(XML_Parser parser, XML_Bool useDTD);

/* 设置用于解析声明中系统标识符中的相对URI的基。解析相对标识符留给应用程序：此值将作为XML_ExternalEntityRefHandler、XML_NotationDeclHandler和XML_UnparsedEntityDeclHandler的基参数传递。将复制基参数。如果内存不足，则返回XML_STATUS_ERROR，否则返回XML_STSTATUS_OK。
*/
XMLPARSEAPI(enum XML_Status)
XML_SetBase(XML_Parser parser, const XML_Char *base);

XMLPARSEAPI(const XML_Char *)
XML_GetBase(XML_Parser parser);

/* 返回上次调用XML_StartElementHandler时传递的属性/值对的数量，这些属性/值是在开始标记中指定的，而不是默认值。每个属性/值对计数为2；因此，这对应于传递给XML_StartElementHandler的atts数组的索引。如果解析器==NULL，则返回-1。
*/
XMLPARSEAPI(int)
XML_GetSpecifiedAttributeCount(XML_Parser parser);

/* 返回上次调用XML_StartElementHandler时传递的ID属性的索引，如果没有ID属性或解析器==NULL，则返回-1。每个属性/值对计数为2；因此，这对应于传递给XML_StartElementHandler的atts数组的索引。
*/
XMLPARSEAPI(int)
XML_GetIdAttributeIndex(XML_Parser parser);

#ifdef XML_ATTR_INFO
/* 属性名称和值的开始和结束的源文件字节偏移量。价值指数不包括周围的报价；因此，在UTF-8源文件中，属性值“blah”将产生：info->valueEnd-info->valueStart=4字节。
*/
typedef struct {
  XML_Index nameStart;  /* 偏移到属性名称的开头。*/
  XML_Index nameEnd;    /* 属性名称最后一个字节后的偏移量。*/
  XML_Index valueStart; /* 偏移到属性值的开头。*/
  XML_Index valueEnd;   /* 属性值最后一个字节后的偏移量。*/
} XML_AttrInfo;

/* 返回上次调用XML_StartElementHandler时传递的属性/值对的XML_AttrInfo结构数组，这些属性/值是在开始标记中指定的，而不是默认值。每个属性/值对计数为1；因此，数组中的条目数为XML_GetSpecifiedAttributeCount（解析器）/2。
*/
XMLPARSEAPI(const XML_AttrInfo *)
XML_GetAttributeInfo(XML_Parser parser);
#endif

/* 分析一些输入。如果检测到致命错误，则返回XML_STATUS_ERROR。对XML_Parse的最后一次调用必须为isFinal true；对于此调用（或任何其他调用），len可以为零。

   尽管这些函数的返回值一直被描述为布尔值，但至少对于1.95.x系列，实现始终只返回一个XML_Status值。
*/
XMLPARSEAPI(enum XML_Status)
XML_Parse(XML_Parser parser, const char *s, int len, int isFinal);

XMLPARSEAPI(void *)
XML_GetBuffer(XML_Parser parser, int len);

XMLPARSEAPI(enum XML_Status)
XML_ParseBuffer(XML_Parser parser, int len, int isFinal);

/* 停止分析，导致XML_Parse（）或XML_ParseBuffer（）返回。必须从回调处理程序中调用，除非中止（可恢复=0）已挂起的解析器。一些回电可能仍然会跟进，因为否则他们会迷路。示例：
   -endElementHandler（）表示在startElementHandler中停止时的空元素，
   -endNameSpaceDeclHandler（）（当在endElementHandler（（）中停止时），可能还有其他。

   可以从大多数处理程序调用，包括与DTD相关的回调，但解析外部参数实体并可恢复时除外！=0。成功时返回XML_STATUS_OK，否则返回XML_STASUS_ERROR。可能的错误代码：
   -XML_ERROR_SUSPENDED：挂起已挂起的解析器时。
   -XML_ERROR_FINISHED：解析器已经完成时。
   -XML_ERROR_SUSPEND_PE：分析外部PE时挂起。

   可恢复时！=0（true），则解析被挂起，即XML_Parse（）和XML_ParseBuffer（）返回XML_STATUS_SSUSPENDED。否则，解析将中止，即XML_Parse（）和XML_ParseBuffer（）返回XML_STATUS_ERROR_aborted错误代码。

   *Note*: 这将仅应用于当前解析器实例，也就是说，如果存在父解析器，那么当externalEntityRefHandler（）返回时，它将继续解析。如果要完全停止解析，则由externalEntityRefHandler（）的实现在父解析器上调用XML_StopParser（）（递归）。

   挂起时，可以通过调用XML_ResumeParser（）恢复解析。
*/
XMLPARSEAPI(enum XML_Status)
XML_StopParser(XML_Parser parser, XML_Bool resumable);

/* 使用XML_StopParser（）挂起后继续分析。不能从处理程序回调中调用。返回与XML_Parse（）或XML_ParseBuffer（）相同的状态代码。可能出现其他错误代码XML_error_NOT_SUSPENDED。

   *Note*: 这必须首先在嵌套最深的子解析器实例上调用，并且只有在子解析器完成后才在其父解析器上调用，以递归方式应用，直到文档实体的解析器重新启动。也就是说，父解析器不会自行恢复，由应用程序在适当的时候调用XML_ResumeParser（）。
*/
XMLPARSEAPI(enum XML_Status)
XML_ResumeParser(XML_Parser parser);

enum XML_Parsing { XML_INITIALIZED, XML_PARSING, XML_FINISHED, XML_SUSPENDED };

typedef struct {
  enum XML_Parsing parsing;
  XML_Bool finalBuffer;
} XML_ParsingStatus;

/* 返回解析器在初始化、解析、完成或暂停以及处理最终缓冲区方面的状态。XXX XML_Parse（）和XML_ParseBuffer（）应返回XML_ParsingStatus，XXX应使用XML_FINISHED_OK或XML_FINISHED_ERROR替换XML_FINISHID
*/
XMLPARSEAPI(void)
XML_GetParsingStatus(XML_Parser parser, XML_ParsingStatus *status);

/* 创建一个XML_Parser对象，该对象可以解析外部通用实体；context是以“\0”结尾的字符串，指定解析上下文；编码是一个以“\0”结尾的字符串，给出外部指定编码的名称，如果没有外部指定编码，则为NULL。上下文字符串由一系列由formfeed（\f）分隔的标记组成；由名称组成的令牌指定该名称的通用实体是开放的；prefix=uri形式的令牌指定特定前缀的名称空间；形式为=uri的标记指定默认名称空间。这可以在第一次调用ExternalEntityRefHandler之后的任何时候调用，只要解析器尚未释放。新解析器是完全独立的，可以安全地在单独的线程中使用。处理程序和userData是从解析器参数初始化的。如果内存不足，则返回NULL。否则返回一个新的XML_Parser对象。
*/
XMLPARSEAPI(XML_Parser)
XML_ExternalEntityParserCreate(XML_Parser parser, const XML_Char *context,
                               const XML_Char *encoding);

enum XML_ParamEntityParsing {
  XML_PARAM_ENTITY_PARSING_NEVER,
  XML_PARAM_ENTITY_PARSING_UNLESS_STANDALONE,
  XML_PARAM_ENTITY_PARSING_ALWAYS
};

/* 控制参数实体（包括外部DTD子集）的解析。如果启用了参数实体的解析，则对外部参数实体（包括外部DTD子集）的引用将传递给XML_SetExternalEntityRefHandler设置的处理程序。传递的上下文将为0。

   与外部通用实体不同，外部参数实体只能同步解析。如果要解析外部参数实体，则必须在调用外部实体ref处理程序时对其进行解析：在此调用期间必须执行XML_ExternalEntityParserCreate、XML_Parse/XML_ParseBuffer和XML_ParserFree调用的完整序列。调用XML_ExternalEntityParserCreate为外部参数实体创建解析器后（此调用的上下文必须为0），在新创建的解析器上调用XML_ParserFree之前，对旧解析器进行任何调用都是非法的。如果编译库时不支持参数实体解析（即未定义XML_DTD），则如果请求解析参数实体，XML_SetParamEntityParsing将返回0；否则它将返回非零。注意：如果XML_SetParamEntityParsing是在XML_Parse或XML_ParseBuffer之后调用的，那么它将无效，并且始终返回0。注意：如果解析器==NULL，则函数将不执行任何操作并返回0。
*/
XMLPARSEAPI(int)
XML_SetParamEntityParsing(XML_Parser parser,
                          enum XML_ParamEntityParsing parsing);

/* 设置用于内部哈希计算的哈希盐。基于预测哈希函数行为，有助于防止DoS攻击。在开始分析之前必须调用此函数。如果成功，则返回1；如果在分析开始后调用，则返回0。注意：如果解析器==NULL，则函数将不执行任何操作并返回0。
*/
XMLPARSEAPI(int)
XML_SetHashSalt(XML_Parser parser, unsigned long hash_salt);

/* 如果XML_Parse或XML_ParseBuffer返回了XML_STATUS_ERROR，则XML_GetErrorCode返回有关错误的信息。
*/
XMLPARSEAPI(enum XML_Error)
XML_GetErrorCode(XML_Parser parser);

/* 这些函数返回有关当前解析位置的信息。它们可以从任何调用的回调中调用，以报告一些解析事件；在这种情况下，位置是生成事件的字符序列中第一个字符的位置。当从文档序言中的声明生成的回调调用时，所标识的位置没有定义得那么清晰，但将位于相关标记内。当在回调函数外部调用时，所指示的位置将刚好超过最后一个解析事件（无论是否有关联的回调）。

   也可以在调用XML_Parse或XML_ParseBuffer返回后调用它们。如果返回值是XML_STATUS_ERROR，则位置是检测到错误的字符的位置；否则，该位置是最后一个解析事件的位置，如上所述。

   注意：XML_GetCurrentLineNumber和XML_GetCurrent ColumnNumber返回0表示错误。注意：XML_GetCurrentByteIndex返回-1表示错误。
*/
XMLPARSEAPI(XML_Size) XML_GetCurrentLineNumber(XML_Parser parser);
XMLPARSEAPI(XML_Size) XML_GetCurrentColumnNumber(XML_Parser parser);
XMLPARSEAPI(XML_Index) XML_GetCurrentByteIndex(XML_Parser parser);

/* 返回当前事件中的字节数。如果事件位于内部实体中，则返回0。
*/
XMLPARSEAPI(int)
XML_GetCurrentByteCount(XML_Parser parser);

/* 如果定义了XML_CONTEXT_BYTES，则返回输入缓冲区，将offset指向的整数设置为当前解析位置在此缓冲区内的偏移量，并将size指向的整数设为此缓冲区的大小（输入字节数）。否则返回NULL指针。如果解析不活动，也会返回NULL指针。

   注意：返回的字符指针不应在进行调用的处理程序之外使用。
*/
XMLPARSEAPI(const char *)
XML_GetInputContext(XML_Parser parser, int *offset, int *size);

/* 与早期版本向后兼容。*/
#define XML_GetErrorLineNumber XML_GetCurrentLineNumber
#define XML_GetErrorColumnNumber XML_GetCurrentColumnNumber
#define XML_GetErrorByteIndex XML_GetCurrentByteIndex

/* 释放传递给元素声明处理程序的内容模型*/
XMLPARSEAPI(void)
XML_FreeContentModel(XML_Parser parser, XML_Content *model);

/* 暴露Expat中使用的内存处理函数*/
XMLPARSEAPI(void *)
XML_ATTR_MALLOC
XML_ATTR_ALLOC_SIZE(2)
XML_MemMalloc(XML_Parser parser, size_t size);

XMLPARSEAPI(void *)
XML_ATTR_ALLOC_SIZE(3)
XML_MemRealloc(XML_Parser parser, void *ptr, size_t size);

XMLPARSEAPI(void)
XML_MemFree(XML_Parser parser, void *ptr);

/* 释放解析器使用的内存。*/
XMLPARSEAPI(void)
XML_ParserFree(XML_Parser parser);

/* 返回描述错误的字符串。*/
XMLPARSEAPI(const XML_LChar *)
XML_ErrorString(enum XML_Error code);

/* 返回包含此expat版本号的字符串*/
XMLPARSEAPI(const XML_LChar *)
XML_ExpatVersion(void);

typedef struct {
  int major;
  int minor;
  int micro;
} XML_Expat_Version;

/* 返回XML_Expat_Version结构，其中包含此版本Expat的数字版本号信息。
*/
XMLPARSEAPI(XML_Expat_Version)
XML_ExpatVersionInfo(void);

/* 在Expat 1.95.5中添加。*/
enum XML_FeatureEnum {
  XML_FEATURE_END = 0,
  XML_FEATURE_UNICODE,
  XML_FEATURE_UNICODE_WCHAR_T,
  XML_FEATURE_DTD,
  XML_FEATURE_CONTEXT_BYTES,
  XML_FEATURE_MIN_SIZE,
  XML_FEATURE_SIZEOF_XML_CHAR,
  XML_FEATURE_SIZEOF_XML_LCHAR,
  XML_FEATURE_NS,
  XML_FEATURE_LARGE_SIZE,
  XML_FEATURE_ATTR_INFO,
  /* 在扩展2.4.0中添加。*/
  XML_FEATURE_BILLION_LAUGHS_ATTACK_PROTECTION_MAXIMUM_AMPLIFICATION_DEFAULT,
  XML_FEATURE_BILLION_LAUGHS_ATTACK_PROTECTION_ACTIVATION_THRESHOLD_DEFAULT
  /* 必须将其他功能添加到此枚举的末尾。*/
};

typedef struct {
  enum XML_FeatureEnum feature;
  const XML_LChar *name;
  long int value;
} XML_Feature;

XMLPARSEAPI(const XML_Feature *)
XML_GetFeatureList(void);

#ifdef XML_DTD
/* 在扩展2.4.0中添加。*/
XMLPARSEAPI(XML_Bool)
XML_SetBillionLaughsAttackProtectionMaximumAmplification(
    XML_Parser parser, float maximumAmplificationFactor);

/* 在扩展2.4.0中添加。*/
XMLPARSEAPI(XML_Bool)
XML_SetBillionLaughsAttackProtectionActivationThreshold(
    XML_Parser parser, unsigned long long activationThresholdBytes);
#endif

/* Expat遵循语义版本控制约定。看见http://semver.org.
*/
#define XML_MAJOR_VERSION 2
#define XML_MINOR_VERSION 4
#define XML_MICRO_VERSION 3

#ifdef __cplusplus
}
#endif

#endif /* 非Expat_CLUDED*/

