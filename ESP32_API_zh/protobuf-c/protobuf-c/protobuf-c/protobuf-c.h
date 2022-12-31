/*
 * 版权所有（c）2008-2017，Dave Benson和protobuf-c作者。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 *     *源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。
 *
 *     *二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*! \文件\主页介绍
 *
 * 这是[protobuf-c]，是[ProtocolBuffers]的c实现。
 *
 * 此文件定义了“libprotobuf-c”支持库的公共API。该API包括可由客户端代码直接使用的接口以及由“protocol-c”编译器生成的代码使用的接口。
 *
 * “libprotobuf-c”支持库执行协议缓冲区消息的实际序列化和反序列化。它与“proto-c”编译器从.proto文件生成的结构、定义和元数据交互。
 *
 * \作者Dave Benson和“protobuf-c”作者。
 *
 * \版权2008-2014。根据[BSD-2条款]许可证条款许可。
 *
 * [protobuf-c]：https://github.com/protobuf-c/protobuf-c[协议缓冲区]：https://developers.google.com/protocol-buffers/[BSD-2条款]：http://opensource.org/licenses/BSD-2-Clause
 *
 * \页面gencode生成的代码
 *
 * 对于每个枚举，我们生成一个C枚举。对于每条消息，我们生成一个C结构，该结构可以转换为“ProtobufCMessage”。
 *
 * 对于每个枚举和消息，我们生成一个描述符对象，该对象允许我们对结构实现某种反射。
 *
 * 首先，一些命名约定：
 *
 * -枚举、消息和服务的类型名称为camel-case（表示WordsAreCrammedTogether），但使用双下划线分隔作用域。例如，下面的`。proto`文件：
 *
~~{.proto}包foo。酒吧消息BazBah｛可选int32 val＝1；｝~~~
 *
 * 将生成C类型“Foo__Bar__BazBah”。
 *
 * -函数和全局变量的标识符都是小写的，用单个下划线分隔驼色大小写的单词。例如，“protocol-c”为上述示例生成的函数原型之一：
 *
~~{.c}Foo__Bar__BazBah Foo__Bar__baz_bah__unpack（ProtobufCAallocater，size_t len，const uint8_t数据）~~~
 *
 * -枚举值的标识符包含嵌入包名称和枚举类型名称的大写前缀。
 *
 * -双下划线用于分隔标识符名称的其他组件。
 *
 * 例如，在上述解包函数的名称中，包名为`foo。bar'变为'foo__bar'，消息名BazBah变为'baz_bah'，方法名为'unpack'。这些都用双下划线连接，形成C标识符“foo__bar__baz_bah__unpack”。
 *
 * 我们还为消息和枚举生成描述符对象。这些在`.pb-c中声明。h`文件：
 *
~~{.c}外部常量ProtobufCMessageDescriptor foo__bar__baz_bah__描述符~~~
 *
 * 消息结构都以“ProtobufCMessageDescriptor*”开头，这足以将它们转换为“ProtobufCMessage”。
 *
 * 对于“。proto文件，我们生成了许多函数和宏。每个函数名都包含基于包名和消息名的前缀，以便使其成为唯一的C标识符。
 *
 * -“初始化”。静态初始化消息对象，初始化其描述符并将其字段设置为默认值。protobuf-c库无法处理未初始化的消息。
 *
~~{.c}#定义FOO__BAR__BAZ_BAH__INIT\｛PROTOBUF_c_MESSAGE_INIT（&FOO__BAR__BAZ_BAH__descriptor），0｝~~~
 * -“init（）”。初始化消息对象，初始化其描述符并将其字段设置为默认值。protobuf-c库无法处理未初始化的消息。
 *
~~{.c}void foo__bar__baz_bah__init（foo__bar__BazBah消息）~~~
 * -“解包（）”。解压缩特定消息格式的数据。注意，“allocater”参数通常为“NULL”，表示系统的“malloc（）”和“free（））”函数应用于动态分配内存。
 *
~~{.c}Foo__Bar__BazBah Foo__Bar__baz_bah__unpack（ProtobufCAallocater，size_t len，const uint8_t数据）~~~
 *
 * -`free_unpacked（）`。释放使用“unpack（）”方法获得的消息对象。允许释放“NULL”（与“free（）”相同）。
 *
~~{.c}void foo__bar__baz_bah__free_unpacked（foo__bar__BazBah消息，ProtobufCAllocater分配器）~~~
 *
 * -`get_packed_size（）`。计算消息对象的序列化表示形式的字节长度。
 *
~~{.c}size_t foo__bar__baz_bah__get_packed_size（常量foo__bar__BazBah消息）~~~
 *
 * -“pack（）”。将消息对象打包到预先分配的缓冲区中。假设缓冲区足够大。（首先使用`get_packed_size（）`。）
 *
~~{.c}size_t foo__bar__baz_bah__pack（常量foo__bar__BazBah消息，uint8_t out）~~~
 *
 * -`pack_to_buffer（）`。将消息打包到“虚拟缓冲区”中。这是一个对象，它定义了一个“追加字节”回调，以在序列化数据时使用数据。
 *
~~{.c}size_t foo__bar__baz_bah__pack_to_buffer（常量foo__bar__BazBah消息，ProtobuffCBuffer缓冲区）~~~
 *
 * \页面包打包和解包消息
 *
 * 要打包消息，首先使用protobuf_c_message_get_packed_size（）计算消息的打包大小，然后分配至少该大小的缓冲区，然后调用protobuf_c_message_pack（）。
 *
 * 或者，可以在不首先计算最终大小的情况下对消息进行序列化。使用protobuf_c_message_pack_to_buffer（）函数，并提供一个ProtobuffCBuffer对象，该对象实现一个使用数据的“追加”方法。
 *
 * 要解压缩消息，请调用protobuf_c_message_unpack（）函数。可以将结果强制转换为与消息描述符匹配的类型的对象。
 *
 * 解包消息的结果应该使用protobuf_c_message_free_unpacked（）释放。
 */

#ifndef PROTOBUF_C_H
#define PROTOBUF_C_H

#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
# define PROTOBUF_C__BEGIN_DECLS	extern "C" {
# define PROTOBUF_C__END_DECLS		}
#else
# define PROTOBUF_C__BEGIN_DECLS
# define PROTOBUF_C__END_DECLS
#endif

PROTOBUF_C__BEGIN_DECLS

#if defined(_WIN32) && defined(PROTOBUF_C_USE_SHARED_LIB)
# ifdef PROTOBUF_C_EXPORT
#  define PROTOBUF_C__API __declspec(dllexport)
# else
#  define PROTOBUF_C__API __declspec(dllimport)
# endif
#else
# define PROTOBUF_C__API
#endif

#if !defined(PROTOBUF_C__NO_DEPRECATED) && \
	((__GNUC__ > 3) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1))
# define PROTOBUF_C__DEPRECATED __attribute__((__deprecated__))
#else
# define PROTOBUF_C__DEPRECATED
#endif

#ifndef PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE
 #define PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(enum_name) \
  , _##enum_name##_IS_INT_SIZE = INT_MAX
#endif

#define PROTOBUF_C__SERVICE_DESCRIPTOR_MAGIC    0x14159bc3
#define PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC    0x28aaeef9
#define PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC       0x114315af

/* 用于初始值设定项的空字符串*/
extern const char protobuf_c_empty_string[];

/**
 * \defgroup api公共api
 *
 * 这是“libprotobuf-c”的公共API。这些接口是稳定的，并且受到语义版本控制的保证。
 *
 * @{
 */

/**
 * “ProtobufCFieldDescriptor”中“flags”字的值。
 */
typedef enum {
	/**设置字段是否重复并使用“打包”选项标记。*/
	PROTOBUF_C_FIELD_FLAG_PACKED		= (1 << 0),

	/**设置字段是否标记为“已弃用”选项。*/
	PROTOBUF_C_FIELD_FLAG_DEPRECATED	= (1 << 1),

	/**设置字段是否为oneof（联合）的成员。*/
	PROTOBUF_C_FIELD_FLAG_ONEOF		= (1 << 2),
} ProtobufCFieldFlag;

/**
 * 消息字段规则。
 *
 * \请参阅协议缓冲区文档中的[定义消息类型]。
 *
 * [定义消息类型]：https://developers.google.com/protocol-buffers/docs/proto#simple
 */
typedef enum {
	/**格式正确的消息必须正好包含其中一个字段。*/
	PROTOBUF_C_LABEL_REQUIRED,

	/**
	 * 格式良好的消息可以有零个或一个此字段（但不能超过一个）。
	 */
	PROTOBUF_C_LABEL_OPTIONAL,

	/**
	 * 该字段可以在格式良好的消息中重复任意次数（包括零次）。将保留重复值的顺序。
	 */
	PROTOBUF_C_LABEL_REPEATED,

	/**
	 * 此字段没有标签。这仅在proto3中有效，并且等同于OPTIONAL，但不会引用“has”量词。
	 */
	PROTOBUF_C_LABEL_NONE,
} ProtobufCLabel;

/**
 * 字段值类型。
 *
 * \请参阅协议缓冲区文档中的[标量值类型]。
 *
 * [标量值类型]：https://developers.google.com/protocol-buffers/docs/proto#scalar
 */
typedef enum {
	PROTOBUF_C_TYPE_INT32,      /**<整数32*/
	PROTOBUF_C_TYPE_SINT32,     /**<有符号int32*/
	PROTOBUF_C_TYPE_SFIXED32,   /**<有符号int32（4字节）*/
	PROTOBUF_C_TYPE_INT64,      /**<int64*/
	PROTOBUF_C_TYPE_SINT64,     /**<有符号int64*/
	PROTOBUF_C_TYPE_SFIXED64,   /**<有符号int64（8字节）*/
	PROTOBUF_C_TYPE_UINT32,     /**<无符号int32*/
	PROTOBUF_C_TYPE_FIXED32,    /**<无符号int32（4字节）*/
	PROTOBUF_C_TYPE_UINT64,     /**<无符号int64*/
	PROTOBUF_C_TYPE_FIXED64,    /**<无符号int64（8字节）*/
	PROTOBUF_C_TYPE_FLOAT,      /**<浮动*/
	PROTOBUF_C_TYPE_DOUBLE,     /**<双倍*/
	PROTOBUF_C_TYPE_BOOL,       /**<布尔值*/
	PROTOBUF_C_TYPE_ENUM,       /**<枚举类型*/
	PROTOBUF_C_TYPE_STRING,     /**<UTF-8或ASCII字符串*/
	PROTOBUF_C_TYPE_BYTES,      /**<任意字节序列*/
	PROTOBUF_C_TYPE_MESSAGE,    /**<嵌套消息*/
} ProtobufCType;

/**
 * 现场导线类型。
 *
 * \请参阅协议缓冲区文档中的[Message Structure]。
 *
 * [消息结构]：https://developers.google.com/protocol-buffers/docs/encoding#structure
 */
typedef enum {
	PROTOBUF_C_WIRE_TYPE_VARINT = 0,
	PROTOBUF_C_WIRE_TYPE_64BIT = 1,
	PROTOBUF_C_WIRE_TYPE_LENGTH_PREFIXED = 2,
	/* 不支持“起始组”和“结束组”导线类型。*/
	PROTOBUF_C_WIRE_TYPE_32BIT = 5,
} ProtobufCWireType;

struct ProtobufCAllocator;
struct ProtobufCBinaryData;
struct ProtobufCBuffer;
struct ProtobufCBufferSimple;
struct ProtobufCEnumDescriptor;
struct ProtobufCEnumValue;
struct ProtobufCEnumValueIndex;
struct ProtobufCFieldDescriptor;
struct ProtobufCIntRange;
struct ProtobufCMessage;
struct ProtobufCMessageDescriptor;
struct ProtobufCMessageUnknownField;
struct ProtobufCMethodDescriptor;
struct ProtobufCService;
struct ProtobufCServiceDescriptor;

typedef struct ProtobufCAllocator ProtobufCAllocator;
typedef struct ProtobufCBinaryData ProtobufCBinaryData;
typedef struct ProtobufCBuffer ProtobufCBuffer;
typedef struct ProtobufCBufferSimple ProtobufCBufferSimple;
typedef struct ProtobufCEnumDescriptor ProtobufCEnumDescriptor;
typedef struct ProtobufCEnumValue ProtobufCEnumValue;
typedef struct ProtobufCEnumValueIndex ProtobufCEnumValueIndex;
typedef struct ProtobufCFieldDescriptor ProtobufCFieldDescriptor;
typedef struct ProtobufCIntRange ProtobufCIntRange;
typedef struct ProtobufCMessage ProtobufCMessage;
typedef struct ProtobufCMessageDescriptor ProtobufCMessageDescriptor;
typedef struct ProtobufCMessageUnknownField ProtobufCMessageUnknownField;
typedef struct ProtobufCMethodDescriptor ProtobufCMethodDescriptor;
typedef struct ProtobufCService ProtobufCService;
typedef struct ProtobufCServiceDescriptor ProtobufCServiceDescriptor;

/**布尔类型。*/
typedef int protobuf_c_boolean;

typedef void (*ProtobufCClosure)(const ProtobufCMessage *, void *closure_data);
typedef void (*ProtobufCMessageInit)(ProtobufCMessage *);
typedef void (*ProtobufCServiceDestroy)(ProtobufCService *);

/**
 * 用于定义自定义内存分配器的结构。
 */
struct ProtobufCAllocator {
	/**分配内存的函数。*/
	void		*(*alloc)(void *allocator_data, size_t size);

	/**释放内存的功能。*/
	void		(*free)(void *allocator_data, void *pointer);

	/**传递给“alloc”和“free”函数的不透明指针。*/
	void		*allocator_data;
};

/**
 * protobuf“bytes”标量类型的结构。
 *
 * “ProtobufCBinaryData”中包含的数据是任意字节序列。它可能包含嵌入的“NUL”字符，不需要以“NUL“结尾。
 */
struct ProtobufCBinaryData {
	size_t	len;        /**<“数据”字段中的字节数。*/
	uint8_t	*data;      /**<数据字节。*/
};

/**
 * 用于定义虚拟仅追加缓冲区的结构。由protobuf_c_message_pack_to_buffer（）用于抽象序列化字节的消耗。
 *
 * `ProtobufCBuffer`“子类”可以在堆栈上定义。例如，要写入“FILE”对象：
 *
~~{.c}typedef结构｛ProtobufCBuffer base；FILE fp；｝缓冲区追加到文件；

静态voidmy_buffer_file_append（ProtobuffCBuffer缓冲区，size_t len，const uint8_t数据）｛BufferAppendToFile file_buf=（BufferAppendToFile）缓冲区；fwrite（data，len，1，file_buf->fp）；//XXX：无错误处理！｝~~~
 *
 * 要使用这种新型ProtobufCBuffer，可以按如下方式调用：
 *
~~{.c}…BufferAppendToFile tmp=｛0｝；tmp.基础。append=my_buffer_file_append；tmp。fp=fp；protobuf_c_message_pack_to_buffer（&message，&tmp）~~~
 */
struct ProtobufCBuffer {
	/**追加函数。使用存储在“data”中的“len”字节。*/
	void		(*append)(ProtobufCBuffer *buffer,
				  size_t len,
				  const uint8_t *data);
};

/**
 * “ProtobufCBuffer”的简单缓冲区“子类”。
 *
 * “ProtobufCBufferSimple”对象在堆栈上声明，并使用用户提供的临时缓冲区进行初始分配。它使用动态分配的内存执行指数调整。可以按如下方式创建和使用“ProtobufCBufferSimple”对象：
 *
~~{.c}uint8_t焊盘[128]；ProtobufCBufferSimple=PROTOBUF_C_BUFFER_simple_INIT（焊盘）；ProtobufCBuffer缓冲区=（ProtobuffCBuffer）&simple~~~
 *
 * `缓冲区”现在可以与“protobuf_c_message_pack_to_buffer（）”一起使用。消息序列化为“ProtobufCBufferSimple”对象后，可以从“”访问序列化的数据字节。数据字段。
 *
 * 要释放“ProtobufCBufferSimple”对象（如果有）分配的内存，请对该对象调用PROTOBUF_C_BUFFER_SIMPLE_CLEAR（），例如：
 *
~~{.c}PROTOBUF_c_BUFFER_SIMPLE_CLEAR（简单）~~~
 *
 * \参见PROTOBUF_C_BUFFER_SIMPLE_INIT\参见PROTOBUF_C_BUFER_SIMPLE_CLEAR
 */
struct ProtobufCBufferSimple {
	/**“基类”。*/
	ProtobufCBuffer		base;
	/**“data”中分配的字节数。*/
	size_t			alloced;
	/**当前存储在“data”中的字节数。*/
	size_t			len;
	/**数据字节。*/
	uint8_t			*data;
	/**是否必须释放“数据”。*/
	protobuf_c_boolean	must_free_data;
	/**要使用的分配器。可以为NULL以指示系统分配器。*/
	ProtobufCAllocator	*allocator;
};

/**
 * 将枚举作为一个整体及其所有值进行描述。
 */
struct ProtobufCEnumDescriptor {
	/**检查Magic值以确保正确使用API。*/
	uint32_t			magic;

	/**限定名称（例如，“namespace.Type”）。*/
	const char			*name;
	/**.proto文件中给出的非限定名称（例如，“Type”）。*/
	const char			*short_name;
	/**生成的C代码中使用的标识符。*/
	const char			*c_name;
	/**点分隔的命名空间。*/
	const char			*package_name;

	/**对“values”中的元素进行编号。*/
	unsigned			n_values;
	/**按数值排序的不同值数组。*/
	const ProtobufCEnumValue	*values;

	/**“values_by_name”中的元素数。*/
	unsigned			n_value_names;
	/**按名称排序的命名值数组，包括别名。*/
	const ProtobufCEnumValueIndex	*values_by_name;

	/**“value_ranges”中的元素数。*/
	unsigned			n_value_ranges;
	/**值范围，以便通过数值更快地查找。*/
	const ProtobufCIntRange		*value_ranges;

	/**保留供将来使用。*/
	void				*reserved1;
	/**保留供将来使用。*/
	void				*reserved2;
	/**保留供将来使用。*/
	void				*reserved3;
	/**保留供将来使用。*/
	void				*reserved4;
};

/**
 * 表示枚举的单个值。
 */
struct ProtobufCEnumValue {
	/**在.proto文件中标识此值的字符串。*/
	const char	*name;

	/**在生成的C代码中标识此值的字符串。*/
	const char	*c_name;

	/**在.proto文件中指定的数值。*/
	int		value;
};

/**
 * 由“ProtobufCEnumDescriptor”用于查找枚举值。
 */
struct ProtobufCEnumValueIndex {
	/**枚举值的名称。*/
	const char      *name;
	/**值[]数组的索引。*/
	unsigned        index;
};

/**
 * 描述消息中的单个字段。
 */
struct ProtobufCFieldDescriptor {
	/**.proto文件中给定的字段名称。*/
	const char		*name;

	/**.proto文件中给出的字段的标记值。*/
	uint32_t		id;

	/**字段是“REQUIRED”、“OPTIONAL”还是“REPEATED”。*/
	ProtobufCLabel		label;

	/**字段的类型。*/
	ProtobufCType		type;

	/**
	 * 消息的C结构的限定符字段（可选成员的“has_MEMBER”字段或重复成员的“n_MEMBER”字段或其中一个的case enum）的字节偏移量。
	 */
	unsigned		quantifier_offset;

	/**
	 * 成员本身的消息C结构中的字节偏移量。
	 */
	unsigned		offset;

	/**
	 * 特定于类型的描述符。
	 *
	 * 如果“类型”为“PROTOBUF_C_type_ENUM”，则“描述符”指向对应的“ProtobufCEnumDescriptor”。
	 *
	 * 如果“类型”是“PROTOBUF_C_type_MESSAGE”，则“描述符”指向对应的“ProtobufCMessageDescriptor”。
	 *
	 * 否则，此字段为空。
	 */
	const void		*descriptor; /* 对于MESSAGE和ENUM类型*/

	/**此字段的默认值（如果已定义）。可能为NULL。*/
	const void		*default_value;

	/**
	 * 一个标志词。可以设置“ProtobufCFieldFlag”枚举中定义的零位或更多位。
	 */
	uint32_t		flags;

	/**保留供将来使用。*/
	unsigned		reserved_flags;
	/**保留供将来使用。*/
	void			*reserved2;
	/**保留供将来使用。*/
	void			*reserved3;
};

/**
 * 帮助器结构，用于在键大部分是连续值的情况下优化int=>索引查找，因为它们可能用于枚举和字段。
 *
 * 数据结构要求对原始数组中的值进行排序。
 */
struct ProtobufCIntRange {
	int             start_value;
	unsigned        orig_index;
	/*
	 * 注意：可以通过查看下一个元素的orig_index来推断范围中的值的数量。添加了一个虚拟元素以简化此操作。
	 */
};

/**
 * 消息的实例。
 *
 * `ProtobufCMessage`是所有消息的轻量级“基类”。
 *
 * 特别是，“ProtobufCMessage”没有任何相关的分配策略。这是因为在堆栈上创建“ProtobufCMessage”对象很常见。事实上，这就是我们建议发送消息的方式。如果对象是从堆栈中分配的，那么就不会真正发生内存泄漏。
 *
 * 这意味着对protobuf_c_message_unpack（）等返回“ProtobufCMessage”的函数的调用必须与对自由函数的调用配对，如protobuf_c_message_free_unpacked（）。
 */
struct ProtobufCMessage {
	/**此消息类型的描述符。*/
	const ProtobufCMessageDescriptor	*descriptor;
	/**“unknown_fields”中的元素数。*/
	unsigned				n_unknown_fields;
	/**解析器无法识别的字段。*/
	ProtobufCMessageUnknownField		*unknown_fields;
};

/**
 * 描述消息。
 */
struct ProtobufCMessageDescriptor {
	/**检查Magic值以确保正确使用API。*/
	uint32_t			magic;

	/**限定名称（例如，“namespace.Type”）。*/
	const char			*name;
	/**.proto文件中给出的非限定名称（例如，“Type”）。*/
	const char			*short_name;
	/**生成的C代码中使用的标识符。*/
	const char			*c_name;
	/**点分隔的命名空间。*/
	const char			*package_name;

	/**
	 * 表示此类型消息实例的C结构的字节大小。
	 */
	size_t				sizeof_message;

	/**“字段”中的元素数。*/
	unsigned			n_fields;
	/**字段描述符，按标记号排序。*/
	const ProtobufCFieldDescriptor	*fields;
	/**用于按名称查找字段。*/
	const unsigned			*fields_sorted_by_name;

	/**“field_ranges”中的元素数。*/
	unsigned			n_field_ranges;
	/**用于按id查找字段。*/
	const ProtobufCIntRange		*field_ranges;

	/**消息初始化功能。*/
	ProtobufCMessageInit		message_init;

	/**保留供将来使用。*/
	void				*reserved1;
	/**保留供将来使用。*/
	void				*reserved2;
	/**保留供将来使用。*/
	void				*reserved3;
};

/**
 * 未知消息字段。
 */
struct ProtobufCMessageUnknownField {
	/**标签号。*/
	uint32_t		tag;
	/**字段的导线类型。*/
	ProtobufCWireType	wire_type;
	/**“data”中的字节数。*/
	size_t			len;
	/**现场数据。*/
	uint8_t			*data;
};

/**
 * 方法描述符。
 */
struct ProtobufCMethodDescriptor {
	/**方法名称。*/
	const char				*name;
	/**输入消息描述符。*/
	const ProtobufCMessageDescriptor	*input;
	/**输出消息描述符。*/
	const ProtobufCMessageDescriptor	*output;
};

/**
 * 服务
 */
struct ProtobufCService {
	/**服务描述符。*/
	const ProtobufCServiceDescriptor *descriptor;
	/**函数调用服务。*/
	void (*invoke)(ProtobufCService *service,
		       unsigned method_index,
		       const ProtobufCMessage *input,
		       ProtobufCClosure closure,
		       void *closure_data);
	/**函数来销毁服务。*/
	void (*destroy)(ProtobufCService *service);
};

/**
 * 服务描述符。
 */
struct ProtobufCServiceDescriptor {
	/**检查Magic值以确保正确使用API。*/
	uint32_t			magic;

	/**服务名称。*/
	const char			*name;
	/**服务名称的短版本。*/
	const char			*short_name;
	/**服务名称的C标识符。*/
	const char			*c_name;
	/**程序包名称。*/
	const char			*package;
	/**“methods”中的元素数。*/
	unsigned			n_methods;
	/**方法描述符，按照.proto文件中定义的顺序。*/
	const ProtobufCMethodDescriptor	*methods;
	/**方法的排序索引。*/
	const unsigned			*method_indices_by_name;
};

/**
 * 获取protobuf-c库的版本。请注意，这是针对链接的库的版本，而不是针对编译的头的版本。
 *
 * \返回包含protobuf-c版本号的字符串。
 */
PROTOBUF_C__API
const char *
protobuf_c_version(void);

/**
 * 获取protobuf-c库的版本。请注意，这是针对链接的库的版本，而不是针对编译的头的版本。
 *
 * \返回一个32位无符号整数，包含protobuf-c的版本号，以10为基数表示为（MAJOR1E6）+（MINOR1E3）+PATCH。
 */
PROTOBUF_C__API
uint32_t
protobuf_c_version_number(void);

/**
 * protobuf-c标头的版本，表示为使用与protobuf_c_version（）相同格式的字符串。
 */
#define PROTOBUF_C_VERSION		"1.3.0"

/**
 * protobuf-c标头的版本，用与protobuf_c_version_number（）相同的格式表示为整数。
 */
#define PROTOBUF_C_VERSION_NUMBER	1003000

/**
 * 与当前版本的protobuf-c标头一起工作的最小proto-c版本。
 */
#define PROTOBUF_C_MIN_COMPILER_VERSION	1000000

/**
 * 按名称从“ProtobufCEnumDescriptor”中查找“ProtobufCEnumValue”。
 *
 * \param desc `ProtobufCEnumDescriptor`对象。\param name要匹配的对应“ProtobufCEnumValue”对象的“name”字段。\返回`ProtobufCEnumValue`对象。\retval NULL如果未找到或设置了optimize_for=CODE_SIZE选项。
 */
PROTOBUF_C__API
const ProtobufCEnumValue *
protobuf_c_enum_descriptor_get_value_by_name(
	const ProtobufCEnumDescriptor *desc,
	const char *name);

/**
 * 按数值从“ProtobufCEnumDescriptor”中查找“ProtobufCEnumValue”。
 *
 * \param desc `ProtobufCEnumDescriptor`对象。\param value要匹配的对应“ProtobufCEnumValue”对象的“value”字段。
 *
 * \返回`ProtobufCEnumValue`对象。\retval NULL如果找不到。
 */
PROTOBUF_C__API
const ProtobufCEnumValue *
protobuf_c_enum_descriptor_get_value(
	const ProtobufCEnumDescriptor *desc,
	int value);

/**
 * 按字段名称从“ProtobufCMessageDescriptor”中查找“ProtobufCFieldDescriptor”。
 *
 * \param desc `ProtobufCMessageDescriptor`对象。\param name字段的名称。\返回`ProtobufCFieldDescriptor`对象。\retval NULL如果未找到或设置了optimize_for=CODE_SIZE选项。
 */
PROTOBUF_C__API
const ProtobufCFieldDescriptor *
protobuf_c_message_descriptor_get_field_by_name(
	const ProtobufCMessageDescriptor *desc,
	const char *name);

/**
 * 根据字段的标记值从“ProtobufCMessageDescriptor”中查找“ProtobufCFieldDescriptor”。
 *
 * \param desc `ProtobufCMessageDescriptor`对象。\param value字段的标记值。\返回`ProtobufCFieldDescriptor`对象。\retval NULL如果找不到。
 */
PROTOBUF_C__API
const ProtobufCFieldDescriptor *
protobuf_c_message_descriptor_get_field(
	const ProtobufCMessageDescriptor *desc,
	unsigned value);

/**
 * 确定存储串行消息所需的字节数。
 *
 * \param message要序列化的消息对象。\return字节数。
 */
PROTOBUF_C__API
size_t
protobuf_c_message_get_packed_size(const ProtobufCMessage *message);

/**
 * 将消息从其内存表示序列化。
 *
 * 此函数将消息的串行字节存储在预先分配的缓冲区中。
 *
 * \param message要序列化的消息对象。\param[out]out Buffer以存储串行消息的字节。此缓冲区必须有足够的空间来存储打包的消息。使用protobuf_c_message_get_packed_size（）确定所需的字节数。\return“out”中存储的字节数。
 */
PROTOBUF_C__API
size_t
protobuf_c_message_pack(const ProtobufCMessage *message, uint8_t *out);

/**
 * 将消息从其内存表示序列化到虚拟缓冲区。
 *
 * 此函数调用“ProtobufCBuffer”对象的“append”方法来使用串行器生成的字节。
 *
 * \param message要序列化的消息对象。\param buffer虚拟缓冲区对象。\return传递到虚拟缓冲区的字节数。
 */
PROTOBUF_C__API
size_t
protobuf_c_message_pack_to_buffer(
	const ProtobufCMessage *message,
	ProtobufCBuffer *buffer);

/**
 * 将串行消息解压缩为内存表示。
 *
 * \param descriptor消息描述符。\param allocater `ProtobufCAllocater`用于内存分配。可以为NULL以指定默认分配器。\param len串行消息的字节长度。\param data指向串行化消息的指针。\return未打包的消息对象。\retval NULL如果在解压缩过程中发生错误。
 */
PROTOBUF_C__API
ProtobufCMessage *
protobuf_c_message_unpack(
	const ProtobufCMessageDescriptor *descriptor,
	ProtobufCAllocator *allocator,
	size_t len,
	const uint8_t *data);

/**
 * 释放未打包的邮件对象。
 *
 * 此函数应用于释放调用protobuf_c_message_unpack（）所使用的内存。
 *
 * \param message要释放的消息对象。可能为NULL。\用于内存释放的param分配器`ProtobufCAllocator`。可以为NULL以指定默认分配器。
 */
PROTOBUF_C__API
void
protobuf_c_message_free_unpacked(
	ProtobufCMessage *message,
	ProtobufCAllocator *allocator);

/**
 * 检查消息对象的有效性。
 *
 * 确保所有必填字段（`PROTOBUF_C_LABEL_required`）都存在。递归检查嵌套消息。
 *
 * \retval TRUE消息有效。\retval FALSE消息无效。
 */
PROTOBUF_C__API
protobuf_c_boolean
protobuf_c_message_check(const ProtobufCMessage *);

/**消息初始化器。*/
#define PROTOBUF_C_MESSAGE_INIT(descriptor) { descriptor, 0, NULL }

/**
 * 从消息描述符初始化消息对象。
 *
 * \param descriptor消息描述符。\param message分配的内存块大小为“descriptor->sizeof_message”。
 */
PROTOBUF_C__API
void
protobuf_c_message_init(
	const ProtobufCMessageDescriptor *descriptor,
	void *message);

/**
 * 免费服务。
 *
 * \param service要释放的服务对象。
 */
PROTOBUF_C__API
void
protobuf_c_service_destroy(ProtobufCService *service);

/**
 * 按名称查找“ProtobufCMethodDescriptor”。
 *
 * \param desc服务描述符。\param name方法的名称。
 *
 * \返回`ProtobufCMethodDescriptor`对象。\retval NULL如果未找到或设置了optimize_for=CODE_SIZE选项。
 */
PROTOBUF_C__API
const ProtobufCMethodDescriptor *
protobuf_c_service_descriptor_get_method_by_name(
	const ProtobufCServiceDescriptor *desc,
	const char *name);

/**
 * 初始化“ProtobufCBufferSimple”对象。
 */
#define PROTOBUF_C_BUFFER_SIMPLE_INIT(array_of_bytes)                   \
{                                                                       \
	{ protobuf_c_buffer_simple_append },                            \
	sizeof(array_of_bytes),                                         \
	0,                                                              \
	(array_of_bytes),                                               \
	0,                                                              \
	NULL                                                            \
}

/**
 * 清除“ProtobufCBufferSimple”对象，释放所有分配的内存。
 */
#define PROTOBUF_C_BUFFER_SIMPLE_CLEAR(simp_buf)                        \
do {                                                                    \
	if ((simp_buf)->must_free_data) {                               \
		if ((simp_buf)->allocator != NULL)                      \
			(simp_buf)->allocator->free(                    \
				(simp_buf)->allocator,                  \
				(simp_buf)->data);			\
		else                                                    \
			free((simp_buf)->data);                         \
	}                                                               \
} while (0)

/**
 * “ProtobufCBufferSimple”的“append”方法。
 *
 * \param buffer要附加到的缓冲区对象。实际上必须是“ProtobufCBufferSimple”对象。\param len“data”中的字节数。\param data要附加的数据。
 */
PROTOBUF_C__API
void
protobuf_c_buffer_simple_append(
	ProtobufCBuffer *buffer,
	size_t len,
	const unsigned char *data);

PROTOBUF_C__API
void
protobuf_c_service_generated_init(
	ProtobufCService *service,
	const ProtobufCServiceDescriptor *descriptor,
	ProtobufCServiceDestroy destroy);

PROTOBUF_C__API
void
protobuf_c_service_invoke_internal(
	ProtobufCService *service,
	unsigned method_index,
	const ProtobufCMessage *input,
	ProtobufCClosure closure,
	void *closure_data);

/**@}*/

PROTOBUF_C__END_DECLS

#endif /* PROTOBUF_C_H */

