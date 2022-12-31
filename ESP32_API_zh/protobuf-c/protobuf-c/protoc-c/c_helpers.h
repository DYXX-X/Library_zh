// 协议缓冲区-Google的数据交换格式
// 版权所有2008谷歌公司。保留所有权利。
// http://code.google.com/p/protobuf/
//
// 以源代码和二进制形式重新分发和使用，无论有无
// 如果满足以下条件，则允许进行修改
// 遇见：
//
//     *源代码的重新分发必须保留上述版权
// 注意，此条件列表和以下免责声明。
//     *二进制形式的重新分发必须复制上述内容
// 版权声明、本条件列表和以下免责声明
// 随
// 分配
//     *既没有谷歌公司的名称，也没有谷歌公司
// 贡献者可用于支持或推广源自
// 本软件未经事先书面许可。
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// 作者：kenton@google.com（Kenton Varda）
//  基于原始协议缓冲区设计
//  Sanjay Ghemawat、Jeff Dean和其他人。

// 版权所有（c）2008-2013，Dave Benson。保留所有权利。
//
// 以源代码和二进制形式重新分发和使用，无论有无
// 如果满足以下条件，则允许进行修改
// 遇见：
//
//     *源代码的重新分发必须保留上述版权
// 注意，此条件列表和以下免责声明。
//
//     *二进制形式的重新分发必须复制上述内容
// 版权声明、本条件列表和以下免责声明
// 随
// 分配
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// DaveBenson修改为实现C代码。

#ifndef GOOGLE_PROTOBUF_COMPILER_C_HELPERS_H__
#define GOOGLE_PROTOBUF_COMPILER_C_HELPERS_H__

#include <string>
#include <vector>
#include <sstream>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/io/printer.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace c {

// 返回给定类型的非嵌套类型名称。如果“合格”
// true，则在类型前面加上完整的名称空间。例如，如果您有：
//   包foo.bar；
//   消息Baz｛消息Qux｛｝｝
// 则Qux的限定ClassName为：
//   食品__酒吧__巴兹_Qux
// 而非限定版本为：
//   巴兹·库克斯
string ClassName(const Descriptor* descriptor, bool qualified);
string ClassName(const EnumDescriptor* enum_descriptor, bool qualified);

// ---从存根处借来的---
template <typename T> string SimpleItoa(T n) {
  std::stringstream stream;
  stream << n;
  return stream.str();
}

string SimpleFtoa(float f);
string SimpleDtoa(double f);
void SplitStringUsing(const string &str, const char *delim, std::vector<string> *out);
string CEscape(const string& src);
string StringReplace(const string& s, const string& oldsub, const string& newsub, bool replace_all);
inline bool HasSuffixString(const string& str, const string& suffix) { return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0; }
inline string StripSuffixString(const string& str, const string& suffix) { if (HasSuffixString(str, suffix)) { return str.substr(0, str.size() - suffix.size()); } else { return str; } }
char* FastHexToBuffer(int i, char* buffer);


// 获取C代码中应用于此字段的（非限定）名称。
// 名称被强制为小写，以模拟proto1行为。人
// 原型字段名称应使用小写加下划线样式
// 无论如何，通常这只返回field->name（）。
string FieldName(const FieldDescriptor* field);

// 获取已弃用字段的宏字符串
string FieldDeprecated(const FieldDescriptor* field);

// 返回定义字段的范围（对于扩展，这是
// 不同于该字段所应用的消息类型）。
inline const Descriptor* FieldScope(const FieldDescriptor* field) {
  return field->is_extension() ?
    field->extension_scope() : field->containing_type();
}

// 将CamelCase类名转换为全大写
// 用下划线分隔单词，例如MyClass变为MY_CLASS。
string CamelToUpper(const string &class_name);
string CamelToLower(const string &class_name);

// 小写，加下划线的名称改为驼色
string ToCamel(const string &name);

// 小写字符串
string ToLower(const string &class_name);
string ToUpper(const string &class_name);

// full_name（）改为小写，带下划线
string FullNameToLower(const string &full_name);
string FullNameToUpper(const string &full_name);

// full_name（）到c-typename（对于包使用下划线，否则使用驼色大小写）
string FullNameToC(const string &class_name);

// 拆分、缩进、格式化和打印注释行
void PrintComment (io::Printer* printer, string comment);

// 创建一个与输入长度相同的空格字符串
string ConvertToSpaces(const string &input);

// 从文件名末尾删除“.proto”或“.protodevel”。
string StripProto(const string& filename);

// 获取原始类型的C++类型名称（例如“double”、“：：google:：protobuf:：int32”等）。
// 注意：非内置类型名称将被限定，这意味着它们将开始
// 用一个：：。如果将该类型用作模板参数
// 需要确保<和：：之间有一个空格，因为
// 荒谬的C++标准将“<：”定义为“[”的同义词。
const char* PrimitiveTypeName(FieldDescriptor::CppType type);

// 以CamelCase格式获取声明的类型名称，例如用于
// WireFormat的方法。例如，TYPE_INT32变为“INT32”。
const char* DeclaredTypeMethodName(FieldDescriptor::Type type);

// 将文件名转换为有效标识符。
string FilenameIdentifier(const string& filename);

// 返回给定文件的BuildDescriptors（）函数的名称。
string GlobalBuildDescriptorsName(const string& filename);

// return“required”、“optional”或“repeated”
string GetLabelName(FieldDescriptor::Label label);


// 为一堆排序值写入IntRanges条目。
// 返回要搜索的范围数。
unsigned WriteIntRanges(io::Printer* printer, int n_values, const int *values, const string &name);

struct NameIndex
{
  unsigned index;
  const char *name;
};
int compare_name_indices_by_name(const void*, const void*);

// 返回包含字段的文件的语法版本。
// 这个包装器需要能够针对protobuf2进行编译。
inline int FieldSyntax(const FieldDescriptor* field) {
#ifdef HAVE_PROTO3
  return field->file()->syntax() == FileDescriptor::SYNTAX_PROTO3 ? 3 : 2;
#else
  return 2;
#endif
}

}  // 命名空间c
}  // 命名空间编译器
}  // 命名空间protobuf

}  // 名称空间google
#endif  // GOOGLE_PROTOBUF_COMPILER_C_HELPERS_H__

